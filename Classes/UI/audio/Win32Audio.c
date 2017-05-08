#include <windows.h>
#include <process.h>

#include "Win32Audio.h"

#define WIN32_AUDIO_NUMBER_OF_BUFFERS	2
#define WIN32_AUDIO_PROC_SIZE				6400
#define WIN32_AUDIO_BUF_SIZE				51200

typedef struct tagWIN32_AUDIO_BUFFER
{
	WAVEHDR			WaveHeader;
	HANDLE			EventHandle;
	int				Playing;
	unsigned long	PcmLength;
	unsigned char	*PcmData;
	unsigned long	PcmDataSize;
}WIN32_AUDIO_BUFFER;

typedef struct tagWIN32_AUDIO_SRC_INFO
{
	unsigned short			Channels;
	unsigned short			SampleRate;
	FuncAudioCallBack		CallBack;
	void					*User;

	HANDLE					Handle;
	int						ThreadExitFlag;

	int						Opened;
	int						bIndex;
	HWAVEIN					WaveHandle;
	WIN32_AUDIO_BUFFER		Buffer[WIN32_AUDIO_NUMBER_OF_BUFFERS];

	unsigned char			*BufAddr;
	unsigned long			Write;
	unsigned long			Read;
}WIN32_AUDIO_SRC_INFO;

typedef struct tagWIN32_AUDIO_SINK_INFO
{
	unsigned short			Channels;
	unsigned short			SampleRate;
	FuncAudioCallBack		CallBack;
	void					*User;

	HANDLE					Handle;
	int						ThreadExitFlag;

	int						Opened;
	int						bIndex;
	int						Paused;
	HWAVEOUT				WaveHandle;
	WIN32_AUDIO_BUFFER		Buffer[WIN32_AUDIO_NUMBER_OF_BUFFERS];
	
	unsigned char			*BufAddr;
	unsigned long			Write;
	unsigned long			Read;
}WIN32_AUDIO_SINK_INFO;

static int Win32AudioSrc_PlayerInit (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo)
{
	int i;

	pWin32AudioSrcInfo->Opened = 0;

	for (i = 0; i < WIN32_AUDIO_NUMBER_OF_BUFFERS; ++i)
	{
		pWin32AudioSrcInfo->Buffer[i].EventHandle = CreateEvent (0, FALSE /* manual reset */, FALSE /* initial state */, 0);
		if (pWin32AudioSrcInfo->Buffer[i].EventHandle == NULL)
		{
			while (i--)
			{
				CloseHandle (pWin32AudioSrcInfo->Buffer[i].EventHandle);
			}

			return -1;
		}

		pWin32AudioSrcInfo->Buffer[i].Playing = 0;
		pWin32AudioSrcInfo->Buffer[i].PcmLength = 0;
	}

	/* try to obtain high priority status */
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	return 0;
}

static void CALLBACK Win32AudioSrc_AudioCallback (HWAVEIN Handle, UINT Message, DWORD Data, DWORD Param1, DWORD Param2)
{
	WAVEHDR					*Header;
	WIN32_AUDIO_BUFFER	*Buffer;

	switch (Message) {
	case WIM_DATA:
		Header = (WAVEHDR *)Param1;
		Buffer = (WIN32_AUDIO_BUFFER *)Header->dwUser;

		if (SetEvent(Buffer->EventHandle) == 0)
		{
			/* error */
		}
		break;

	case WIM_OPEN:
	case WIM_CLOSE:
		break;
	}

	return;
}

static void Win32AudioSrc_AudioSetFormat (WAVEFORMATEX *Format, unsigned short Channels, unsigned short Speed, unsigned short Bits)
{
	unsigned short BlockAL;
	unsigned long BytesPS;

	BlockAL = Channels * Bits / 8;
	BytesPS = Speed * BlockAL;

	Format->wFormatTag      = WAVE_FORMAT_PCM;
	Format->nChannels       = Channels;
	Format->nSamplesPerSec  = Speed;
	Format->nAvgBytesPerSec = BytesPS;
	Format->nBlockAlign     = BlockAL;
	Format->wBitsPerSample  = Bits;
	Format->cbSize          = 0;

	return;
}

static int Win32AudioSrc_AudioOpenDev (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo, HWAVEIN *Handle, unsigned short Channels, unsigned short Speed, unsigned short Depth)
{
	WAVEFORMATEX Format;
	MMRESULT Error;

	Win32AudioSrc_AudioSetFormat(&Format, Channels, Speed, Depth);

	Error = waveInOpen (Handle, WAVE_MAPPER, &Format, (DWORD)Win32AudioSrc_AudioCallback, 0, CALLBACK_FUNCTION);
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	pWin32AudioSrcInfo->Opened = 1;

	return 0;
}

static int Win32AudioSrc_AudioCloseDev (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo, HWAVEIN Handle)
{
	MMRESULT Error;

	pWin32AudioSrcInfo->Opened = 0;

	Error = waveInClose(Handle);
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	return 0;
}

static long Win32AudioSrc_AudioReadDev (HWAVEIN Handle, WIN32_AUDIO_BUFFER *Buffer)
{
	MMRESULT Error;

	Buffer->WaveHeader.lpData			= (LPSTR)Buffer->PcmData;
	Buffer->WaveHeader.dwBufferLength	= Buffer->PcmDataSize;
	Buffer->WaveHeader.dwBytesRecorded	= 0;
	Buffer->WaveHeader.dwUser			= (DWORD)Buffer;
	Buffer->WaveHeader.dwFlags			= 0;

	Error = waveInPrepareHeader(Handle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	Error = waveInAddBuffer(Handle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	Buffer->Playing = 1;

	return 0;
}

static long Win32AudioSrc_AudioWait (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo, WIN32_AUDIO_BUFFER *Buffer, unsigned long MS)
{
	MMRESULT Error;

	if (!Buffer->Playing)
	{
		return 0;
	}

	switch (WaitForSingleObject (Buffer->EventHandle, MS))
	{
	case WAIT_OBJECT_0:
		break;

	case WAIT_ABANDONED:
		return -1;

	case WAIT_TIMEOUT:
		return -1;

	case WAIT_FAILED:
	default:
		return -1;
	}

	Buffer->Playing = 0;

	Error = waveInUnprepareHeader(pWin32AudioSrcInfo->WaveHandle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	return 0;
}

static long Win32AudioSrc_AudioConfig (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo)
{
	if (Win32AudioSrc_AudioOpenDev (pWin32AudioSrcInfo, &pWin32AudioSrcInfo->WaveHandle, pWin32AudioSrcInfo->Channels, pWin32AudioSrcInfo->SampleRate, 16) == -1)
	{
		return -1;
	}

	return 0;
}

static int Win32AudioSrc_PlayerFinish (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo)
{
	int	i;
	int	Result = 0;

	if (pWin32AudioSrcInfo->Opened)
	{
		if (Win32AudioSrc_AudioCloseDev (pWin32AudioSrcInfo, pWin32AudioSrcInfo->WaveHandle) == -1)
		{
			Result = -1;
		}
	}

	/* restore priority status */
	SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_NORMAL);
	SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);

	for (i = 0; i < WIN32_AUDIO_NUMBER_OF_BUFFERS; ++i)
	{
		if (CloseHandle (pWin32AudioSrcInfo->Buffer[i].EventHandle) == 0 && Result == 0)
		{
			Result = -1;
		}
	}

	return Result;
}

static int Win32AudioSrc_Open (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo)
{
	WIN32_AUDIO_BUFFER	*InBuffer;
	
	Win32AudioSrc_PlayerInit (pWin32AudioSrcInfo);

	Win32AudioSrc_AudioConfig (pWin32AudioSrcInfo);

	InBuffer = &pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex];
	Win32AudioSrc_AudioReadDev (pWin32AudioSrcInfo->WaveHandle, InBuffer);
	pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex].PcmLength = 0;
	pWin32AudioSrcInfo->bIndex = (pWin32AudioSrcInfo->bIndex + 1) % WIN32_AUDIO_NUMBER_OF_BUFFERS;

	InBuffer = &pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex];
	Win32AudioSrc_AudioReadDev (pWin32AudioSrcInfo->WaveHandle, InBuffer);
	pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex].PcmLength = 0;
	pWin32AudioSrcInfo->bIndex = (pWin32AudioSrcInfo->bIndex + 1) % WIN32_AUDIO_NUMBER_OF_BUFFERS;

	waveInStart (pWin32AudioSrcInfo->WaveHandle);

	return 0;
}

static int Win32AudioSrc_Close (WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo)
{
	waveInStop (pWin32AudioSrcInfo->WaveHandle);
	Win32AudioSrc_PlayerFinish (pWin32AudioSrcInfo);

	return 0;
}

static void Win32AudioSrc_Thread (void *Data)
{
	WIN32_AUDIO_SRC_INFO	*pWin32AudioSrcInfo = (WIN32_AUDIO_SRC_INFO *)Data;
	WIN32_AUDIO_BUFFER	*InBuffer;

	while (1)
	{
		if (pWin32AudioSrcInfo->ThreadExitFlag == 1)
		{
			if (pWin32AudioSrcInfo->Opened == 1)
			{
				Win32AudioSrc_Close (pWin32AudioSrcInfo);
			}
			break;
		}
		
		if (pWin32AudioSrcInfo->Opened == 0)
		{
			Win32AudioSrc_Open (pWin32AudioSrcInfo);
		}

		InBuffer = &pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex];

		/* wait for block to finish playing */
		if (InBuffer->PcmLength == 0 && Win32AudioSrc_AudioWait (pWin32AudioSrcInfo, InBuffer, INFINITE) == -1)
		{
			Sleep (10);
			continue;
		}

		if (pWin32AudioSrcInfo->CallBack == NULL)
		{
			memcpy (pWin32AudioSrcInfo->BufAddr + pWin32AudioSrcInfo->Write, InBuffer->PcmData, InBuffer->PcmDataSize);
			if (pWin32AudioSrcInfo->Write + InBuffer->PcmDataSize == WIN32_AUDIO_BUF_SIZE)
			{
				pWin32AudioSrcInfo->Write = 0;
			}
			else
			{
				pWin32AudioSrcInfo->Write += InBuffer->PcmDataSize;
			}
		}
		else
		{
			pWin32AudioSrcInfo->CallBack (pWin32AudioSrcInfo->User, InBuffer->PcmData);
		}

		Win32AudioSrc_AudioReadDev (pWin32AudioSrcInfo->WaveHandle, InBuffer);
		pWin32AudioSrcInfo->Buffer[pWin32AudioSrcInfo->bIndex].PcmLength = 0;
		pWin32AudioSrcInfo->bIndex = (pWin32AudioSrcInfo->bIndex + 1) % WIN32_AUDIO_NUMBER_OF_BUFFERS;
	}

	_endthread();
}

AUDIO_IN_HANDLE Win32AudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo;

	if (Param->CallBack == NULL)
	{
		pWin32AudioSrcInfo = (WIN32_AUDIO_SRC_INFO *)malloc(sizeof(WIN32_AUDIO_SRC_INFO) + WIN32_AUDIO_PROC_SIZE * 2 + WIN32_AUDIO_BUF_SIZE);
	}
	else
	{
		pWin32AudioSrcInfo = (WIN32_AUDIO_SRC_INFO *)malloc(sizeof(WIN32_AUDIO_SRC_INFO) + Param->FrameCount * Param->Channels * 2 * 2);
	}
	if (pWin32AudioSrcInfo == NULL)
	{
		return NULL;
	}

	pWin32AudioSrcInfo->Channels = (unsigned short)Param->Channels;
	pWin32AudioSrcInfo->SampleRate = (unsigned short)Param->SampleRate;
	if (Param->CallBack == NULL)
	{
		pWin32AudioSrcInfo->CallBack = NULL;
		pWin32AudioSrcInfo->Buffer[0].PcmDataSize = WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSrcInfo->Buffer[1].PcmDataSize = WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSrcInfo->Buffer[0].PcmData = (unsigned char *)pWin32AudioSrcInfo + sizeof(WIN32_AUDIO_SRC_INFO);
		pWin32AudioSrcInfo->Buffer[1].PcmData = pWin32AudioSrcInfo->Buffer[0].PcmData + WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSrcInfo->BufAddr = pWin32AudioSrcInfo->Buffer[1].PcmData + WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSrcInfo->Read = 0;
		pWin32AudioSrcInfo->Write = 0;
	}
	else
	{
		pWin32AudioSrcInfo->CallBack = Param->CallBack;
		pWin32AudioSrcInfo->User = Param->User;
		pWin32AudioSrcInfo->Buffer[0].PcmDataSize = Param->FrameCount * Param->Channels * 2;
		pWin32AudioSrcInfo->Buffer[1].PcmDataSize = pWin32AudioSrcInfo->Buffer[0].PcmDataSize;
		pWin32AudioSrcInfo->Buffer[0].PcmData = (unsigned char *)pWin32AudioSrcInfo + sizeof(WIN32_AUDIO_SRC_INFO);
		pWin32AudioSrcInfo->Buffer[1].PcmData = pWin32AudioSrcInfo->Buffer[0].PcmData + pWin32AudioSrcInfo->Buffer[0].PcmDataSize;
	}

	pWin32AudioSrcInfo->Opened = 0;
	pWin32AudioSrcInfo->bIndex = 0;

	pWin32AudioSrcInfo->ThreadExitFlag = 0;
	pWin32AudioSrcInfo->Handle = (HANDLE)_beginthread (Win32AudioSrc_Thread, 0, pWin32AudioSrcInfo);
	if (pWin32AudioSrcInfo->Handle == (HANDLE)(-1))
	{
		free (pWin32AudioSrcInfo);
		return NULL;
	}

	return (AUDIO_IN_HANDLE)pWin32AudioSrcInfo;
}

long Win32AudioIn_Close (AUDIO_IN_HANDLE Handle)
{
	WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo = (WIN32_AUDIO_SRC_INFO *)Handle;
	
	pWin32AudioSrcInfo->ThreadExitFlag = 1;
	WaitForSingleObject(pWin32AudioSrcInfo->Handle, INFINITE);

	free (pWin32AudioSrcInfo);

	return 0;
}

long Win32AudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	WIN32_AUDIO_SRC_INFO *pWin32AudioSrcInfo = (WIN32_AUDIO_SRC_INFO *)Handle;
	unsigned long Write, Free;

	Write = pWin32AudioSrcInfo->Write;
	if (Write < pWin32AudioSrcInfo->Read)
	{
		Free = Write + WIN32_AUDIO_BUF_SIZE - pWin32AudioSrcInfo->Read;
	}
	else
	{
		Free = Write - pWin32AudioSrcInfo->Read;
	}

	if (Free < Size)
	{
		Size = Free;
	}

	if (pWin32AudioSrcInfo->Read + Size > WIN32_AUDIO_BUF_SIZE)
	{
		memcpy (BufAddr, pWin32AudioSrcInfo->BufAddr + pWin32AudioSrcInfo->Read, WIN32_AUDIO_BUF_SIZE - pWin32AudioSrcInfo->Read);
		memcpy ((unsigned char *)BufAddr + (WIN32_AUDIO_BUF_SIZE - pWin32AudioSrcInfo->Read), pWin32AudioSrcInfo->BufAddr, Size - (WIN32_AUDIO_BUF_SIZE - pWin32AudioSrcInfo->Read));
		pWin32AudioSrcInfo->Read = pWin32AudioSrcInfo->Read + Size - WIN32_AUDIO_BUF_SIZE;
	}
	else
	{
		memcpy (BufAddr, pWin32AudioSrcInfo->BufAddr + pWin32AudioSrcInfo->Read, Size);
		pWin32AudioSrcInfo->Read += Size;
	}

	return Size;
}

static int Win32AudioSink_PlayerInit (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	int i;

	pWin32AudioSinkInfo->Opened = 0;

	for (i = 0; i < WIN32_AUDIO_NUMBER_OF_BUFFERS; ++i)
	{
		pWin32AudioSinkInfo->Buffer[i].EventHandle = CreateEvent(0, FALSE /* manual reset */, FALSE /* initial state */, 0);
		if (pWin32AudioSinkInfo->Buffer[i].EventHandle == NULL)
		{
			while (i--)
			{
				CloseHandle(pWin32AudioSinkInfo->Buffer[i].EventHandle);
			}

			return -1;
		}

		pWin32AudioSinkInfo->Buffer[i].Playing = 0;
		pWin32AudioSinkInfo->Buffer[i].PcmLength = 0;
	}

	/* try to obtain high priority status */
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	return 0;
}

static void CALLBACK Win32AudioSink_AudioCallback (HWAVEOUT Handle, UINT Message, DWORD Data, DWORD Param1, DWORD Param2)
{
	WAVEHDR					*Header;
	WIN32_AUDIO_BUFFER	*Buffer;

	switch (Message) {
	case WOM_DONE:
		Header = (WAVEHDR *)Param1;
		Buffer = (WIN32_AUDIO_BUFFER *)Header->dwUser;

		if (SetEvent(Buffer->EventHandle) == 0)
		{
			/* error */
		}
		break;

	case WOM_OPEN:
	case WOM_CLOSE:
		break;
	}

	return;
}

static void Win32AudioSink_AudioSetFormat (WAVEFORMATEX *Format, unsigned short Channels, unsigned short Speed, unsigned short Bits)
{
	unsigned short BlockAL;
	unsigned long BytesPS;

	BlockAL = Channels * Bits / 8;
	BytesPS = Speed * BlockAL;

	Format->wFormatTag      = WAVE_FORMAT_PCM;
	Format->nChannels       = Channels;
	Format->nSamplesPerSec  = Speed;
	Format->nAvgBytesPerSec = BytesPS;
	Format->nBlockAlign     = BlockAL;
	Format->wBitsPerSample  = Bits;
	Format->cbSize          = 0;

	return;
}

static int Win32AudioSink_AudioOpenDev (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo, HWAVEOUT *Handle, unsigned short Channels, unsigned short Speed, unsigned short Depth)
{
	WAVEFORMATEX Format;
	MMRESULT Error;

	Win32AudioSink_AudioSetFormat(&Format, Channels, Speed, Depth);

	Error = waveOutOpen (Handle, WAVE_MAPPER, &Format, (DWORD)Win32AudioSink_AudioCallback, 0, CALLBACK_FUNCTION);
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	pWin32AudioSinkInfo->Opened = 1;

	return 0;
}

static int Win32AudioSink_AudioCloseDev (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo, HWAVEOUT Handle)
{
	MMRESULT Error;

	pWin32AudioSinkInfo->Opened = 0;

	Error = waveOutClose(Handle);
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	return 0;
}

static int Win32AudioSink_AudioSetPause (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo, int Flag)
{
	MMRESULT Error;

	if (Flag && !pWin32AudioSinkInfo->Paused)
	{
		Error = waveOutPause (pWin32AudioSinkInfo->WaveHandle);
		if (Error != MMSYSERR_NOERROR)
		{
			return -1;
		}
	}
	else if (!Flag && pWin32AudioSinkInfo->Paused)
	{
		Error = waveOutRestart (pWin32AudioSinkInfo->WaveHandle);
		if (Error != MMSYSERR_NOERROR)
		{
			return -1;
		}
	}

	pWin32AudioSinkInfo->Paused = Flag;

	return 0;
}

static int Win32AudioSink_AudioWriteDev (HWAVEOUT Handle, WIN32_AUDIO_BUFFER *Buffer)
{
	MMRESULT Error;

	Buffer->WaveHeader.lpData         = (LPSTR)Buffer->PcmData;
	Buffer->WaveHeader.dwBufferLength = Buffer->PcmLength;
	Buffer->WaveHeader.dwUser         = (DWORD)Buffer;
	Buffer->WaveHeader.dwFlags        = 0;

	Error = waveOutPrepareHeader(Handle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	Error = waveOutWrite(Handle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	Buffer->Playing = 1;

	return 0;
}

static int Win32AudioSink_AudioWait (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo, WIN32_AUDIO_BUFFER *Buffer, unsigned long MS)
{
	MMRESULT Error;

	if (!Buffer->Playing)
	{
		return 0;
	}

	switch (WaitForSingleObject (Buffer->EventHandle, MS))
	{
	case WAIT_OBJECT_0:
		break;

	case WAIT_ABANDONED:
		return -1;

	case WAIT_TIMEOUT:
		return -1;

	case WAIT_FAILED:
	default:
		return -1;
	}

	Buffer->Playing = 0;

	Error = waveOutUnprepareHeader(pWin32AudioSinkInfo->WaveHandle, &Buffer->WaveHeader, sizeof(Buffer->WaveHeader));
	if (Error != MMSYSERR_NOERROR)
	{
		return -1;
	}

	return 0;
}

static int Win32AudioSink_AudioDrain (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	int i;
	int Result = 0;

	if (Win32AudioSink_AudioSetPause (pWin32AudioSinkInfo, 0) == -1)
	{
		Result = -1;
	}

	if (pWin32AudioSinkInfo->Buffer[pWin32AudioSinkInfo->bIndex].PcmLength && Win32AudioSink_AudioWriteDev (pWin32AudioSinkInfo->WaveHandle, &pWin32AudioSinkInfo->Buffer[pWin32AudioSinkInfo->bIndex]) == -1)
	{
		Result = -1;
	}

	for (i = 0; i < WIN32_AUDIO_NUMBER_OF_BUFFERS; ++i)
	{
		if (Win32AudioSink_AudioWait(pWin32AudioSinkInfo, &pWin32AudioSinkInfo->Buffer[i], INFINITE) == -1)
		{
			Result = -1;
		}
	}

	pWin32AudioSinkInfo->Buffer[pWin32AudioSinkInfo->bIndex].PcmLength = 0;

	return Result;
}

static int Win32AudioSink_AudioConfig (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	if (Win32AudioSink_AudioOpenDev (pWin32AudioSinkInfo, &pWin32AudioSinkInfo->WaveHandle, pWin32AudioSinkInfo->Channels, pWin32AudioSinkInfo->SampleRate, 16) == -1)
	{
		return -1;
	}

	return 0;
}

static int Win32AudioSink_PlayerFinish (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	int i;
	int	Result = 0;

	if (pWin32AudioSinkInfo->Opened)
	{
		if (Win32AudioSink_AudioDrain(pWin32AudioSinkInfo) == -1)
		{
			Result = -1;
		}
		if (Win32AudioSink_AudioCloseDev(pWin32AudioSinkInfo, pWin32AudioSinkInfo->WaveHandle) == -1)
		{
			Result = -1;
		}
	}

	/* restore priority status */
	SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_NORMAL);
	SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);

	for (i = 0; i < WIN32_AUDIO_NUMBER_OF_BUFFERS; ++i)
	{
		if (CloseHandle (pWin32AudioSinkInfo->Buffer[i].EventHandle) == 0 && Result == 0)
		{
			Result = -1;
		}
	}

	return Result;
}

static void Win32AudioSink_Open (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	Win32AudioSink_PlayerInit (pWin32AudioSinkInfo);
	Win32AudioSink_AudioConfig (pWin32AudioSinkInfo);
	
	return;
}

static void Win32AudioSink_Close (WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo)
{
	Win32AudioSink_PlayerFinish (pWin32AudioSinkInfo);

	return;
}

static void Win32AudioSink_Thread (void *Data)
{
	WIN32_AUDIO_SINK_INFO	*pWin32AudioSinkInfo = (WIN32_AUDIO_SINK_INFO *)Data;
	WIN32_AUDIO_BUFFER *OutBuffer;
	unsigned long			Available;
	unsigned long			Write;

	while (1)
	{
		if (pWin32AudioSinkInfo->ThreadExitFlag == 1)
		{
			if (pWin32AudioSinkInfo->Opened == 1)
			{
				Win32AudioSink_Close (pWin32AudioSinkInfo);
			}
			break;
		}

		if (pWin32AudioSinkInfo->Opened == 0)
		{
			Win32AudioSink_Open (pWin32AudioSinkInfo);
		}

		OutBuffer = &pWin32AudioSinkInfo->Buffer[pWin32AudioSinkInfo->bIndex];

		/* wait for block to finish playing */
		if (OutBuffer->PcmLength == 0 && Win32AudioSink_AudioWait(pWin32AudioSinkInfo, OutBuffer, INFINITE) == -1)
		{
			Sleep (10);
			continue;
		}

		if (pWin32AudioSinkInfo->CallBack == NULL)
		{
			Write = pWin32AudioSinkInfo->Write;
			if (Write < pWin32AudioSinkInfo->Read)
			{
				Available = Write + WIN32_AUDIO_BUF_SIZE - pWin32AudioSinkInfo->Read;
			}
			else
			{
				Available = Write - pWin32AudioSinkInfo->Read;
			}
			if (Available >= OutBuffer->PcmDataSize)
			{
				memcpy (OutBuffer->PcmData, pWin32AudioSinkInfo->BufAddr + pWin32AudioSinkInfo->Read, OutBuffer->PcmDataSize);
				if (pWin32AudioSinkInfo->Read + OutBuffer->PcmDataSize == WIN32_AUDIO_BUF_SIZE)
				{
					pWin32AudioSinkInfo->Read = 0;
				}
				else
				{
					pWin32AudioSinkInfo->Read += OutBuffer->PcmDataSize;
				}
			}
			else
			{
				memset (OutBuffer->PcmData, 0, OutBuffer->PcmDataSize);
			}
		}
		else
		{
			memset (OutBuffer->PcmData, 0, OutBuffer->PcmDataSize);
			pWin32AudioSinkInfo->CallBack (pWin32AudioSinkInfo->User, OutBuffer->PcmData);
		}

		if (Win32AudioSink_AudioSetPause(pWin32AudioSinkInfo, 0) == -1)
		{
			Sleep (10);
			continue;
		}

		OutBuffer->PcmLength = OutBuffer->PcmDataSize;

		Win32AudioSink_AudioWriteDev (pWin32AudioSinkInfo->WaveHandle, OutBuffer);
		pWin32AudioSinkInfo->bIndex = (pWin32AudioSinkInfo->bIndex + 1) % WIN32_AUDIO_NUMBER_OF_BUFFERS;
		pWin32AudioSinkInfo->Buffer[pWin32AudioSinkInfo->bIndex].PcmLength = 0;
	}

	_endthread();
}

AUDIO_OUT_HANDLE Win32AudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo;

	if (Param->CallBack == NULL)
	{
		pWin32AudioSinkInfo = (WIN32_AUDIO_SINK_INFO *)malloc(sizeof(WIN32_AUDIO_SINK_INFO) + WIN32_AUDIO_PROC_SIZE * 2 + WIN32_AUDIO_BUF_SIZE);
	}
	else
	{
		pWin32AudioSinkInfo = (WIN32_AUDIO_SINK_INFO *)malloc(sizeof(WIN32_AUDIO_SINK_INFO) + Param->FrameCount * Param->Channels * 2 * 2);
	}
	if (pWin32AudioSinkInfo == NULL)
	{
		return NULL;
	}

	pWin32AudioSinkInfo->Channels = (unsigned short)Param->Channels;
	pWin32AudioSinkInfo->SampleRate = (unsigned short)Param->SampleRate;
	if (Param->CallBack == NULL)
	{
		pWin32AudioSinkInfo->CallBack = NULL;
		pWin32AudioSinkInfo->Buffer[0].PcmDataSize = WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSinkInfo->Buffer[1].PcmDataSize = WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSinkInfo->Buffer[0].PcmData = (unsigned char *)pWin32AudioSinkInfo + sizeof(WIN32_AUDIO_SINK_INFO);
		pWin32AudioSinkInfo->Buffer[1].PcmData = pWin32AudioSinkInfo->Buffer[0].PcmData + WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSinkInfo->BufAddr = pWin32AudioSinkInfo->Buffer[1].PcmData + WIN32_AUDIO_PROC_SIZE;
		pWin32AudioSinkInfo->Read = 0;
		pWin32AudioSinkInfo->Write = 0;
	}
	else
	{
		pWin32AudioSinkInfo->CallBack = Param->CallBack;
		pWin32AudioSinkInfo->User = Param->User;
		pWin32AudioSinkInfo->Buffer[0].PcmDataSize = Param->FrameCount * Param->Channels * 2;
		pWin32AudioSinkInfo->Buffer[1].PcmDataSize = pWin32AudioSinkInfo->Buffer[0].PcmDataSize;
		pWin32AudioSinkInfo->Buffer[0].PcmData = (unsigned char *)pWin32AudioSinkInfo + sizeof(WIN32_AUDIO_SINK_INFO);
		pWin32AudioSinkInfo->Buffer[1].PcmData = pWin32AudioSinkInfo->Buffer[0].PcmData + pWin32AudioSinkInfo->Buffer[0].PcmDataSize;
	}

	pWin32AudioSinkInfo->Opened = 0;
	pWin32AudioSinkInfo->bIndex = 0;
	pWin32AudioSinkInfo->Paused = 0;
	pWin32AudioSinkInfo->Read = 0;
	pWin32AudioSinkInfo->Write = 0;

	pWin32AudioSinkInfo->ThreadExitFlag = 0;
	pWin32AudioSinkInfo->Handle = (HANDLE)_beginthread (Win32AudioSink_Thread, 0, pWin32AudioSinkInfo);
	if (pWin32AudioSinkInfo->Handle == (HANDLE)(-1))
	{
		free (pWin32AudioSinkInfo);
		return NULL;
	}

	return (AUDIO_OUT_HANDLE)pWin32AudioSinkInfo;
}

long Win32AudioOut_Close (AUDIO_OUT_HANDLE Handle)
{
	WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo = (WIN32_AUDIO_SINK_INFO *)Handle;
	
	pWin32AudioSinkInfo->ThreadExitFlag = 1;
	WaitForSingleObject(pWin32AudioSinkInfo->Handle, INFINITE);

	free (pWin32AudioSinkInfo);

	return 0;
}

long Win32AudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	WIN32_AUDIO_SINK_INFO *pWin32AudioSinkInfo = (WIN32_AUDIO_SINK_INFO *)Handle;
	unsigned long Read, Free;

	Read = pWin32AudioSinkInfo->Read;
	if (pWin32AudioSinkInfo->Write < Read)
	{
		Free = Read - pWin32AudioSinkInfo->Write;
	}
	else
	{
		Free = WIN32_AUDIO_BUF_SIZE - (pWin32AudioSinkInfo->Write - Read); 
	}
	if (Free < Size)
	{
		Size = Free;
	}

	if (pWin32AudioSinkInfo->Write + Size > WIN32_AUDIO_BUF_SIZE)
	{
		memcpy (pWin32AudioSinkInfo->BufAddr + pWin32AudioSinkInfo->Write, BufAddr, WIN32_AUDIO_BUF_SIZE - pWin32AudioSinkInfo->Write);
		memcpy (pWin32AudioSinkInfo->BufAddr, (unsigned char *)BufAddr + (WIN32_AUDIO_BUF_SIZE - pWin32AudioSinkInfo->Write), Size - (WIN32_AUDIO_BUF_SIZE - pWin32AudioSinkInfo->Write));
		pWin32AudioSinkInfo->Write = pWin32AudioSinkInfo->Write + Size - WIN32_AUDIO_BUF_SIZE;
	}
	else
	{
		memcpy (pWin32AudioSinkInfo->BufAddr + pWin32AudioSinkInfo->Write, BufAddr, Size);
		pWin32AudioSinkInfo->Write += Size;
	}

	return Size;
}

AUDIO_HANDLE Win32Audio_Init ()
{
	return (AUDIO_HANDLE)1;
}

int Win32Audio_Finish (AUDIO_HANDLE Handle)
{
	return 0;
}

