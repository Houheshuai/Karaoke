#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "rfmod.h"
#include "A20Audio.h"

#include <android/log.h>
#define  LOG_TAG    "a20audio"
#define  log_for_pro(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

//#define SUPPORT_EXT_MIDI

#define A20_AUDIO_48KHZ_MODE
//#define A20_AUDIO_44KHZ_MODE
//#define A20_AUDIO_32KHZ_MODE

#ifdef A20_AUDIO_48KHZ_MODE
#define A20_AUDIO_DEV								"/dev/ChaosAudio"
#define A20_AUDIO_IN_CHANNELS						4
#define A20_AUDIO_IN_SAMPLE_RATE					48000
#define A20_AUDIO_OUT_CHANNELS					2
#define A20_AUDIO_OUT_SAMPLE_RATE				48000
#define A20_AUDIO_I2S_CHANNELS					2
#define A20_AUDIO_I2S_SAMPLE_RATE				48000
#define A20_AUDIO_OPENSLES_CHANNELS				2
#define A20_AUDIO_OPENSLES_SAMPLE_RATE			SL_SAMPLINGRATE_48
#define A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE		19200	//100MS
#define A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE	19200	//100MS
#define A20_AUDIO_MAX_HANDLE						4
#define A20_AUDIO_IN_BUF_SIZE						153600	//400MS
#define A20_AUDIO_IN_TEMP_BUF_SIZE				76800	//200MS
#define A20_AUDIO_OUT_BUF_SIZE					38400	//200MS
#elif defined A20_AUDIO_44KHZ_MODE
#define A20_AUDIO_DEV								"/dev/ChaosAudio"
#define A20_AUDIO_IN_CHANNELS						4
#define A20_AUDIO_IN_SAMPLE_RATE					44100
#define A20_AUDIO_OUT_CHANNELS					2
#define A20_AUDIO_OUT_SAMPLE_RATE				44100
#define A20_AUDIO_I2S_CHANNELS					2
#define A20_AUDIO_I2S_SAMPLE_RATE				44100
#define A20_AUDIO_OPENSLES_CHANNELS				2
#define A20_AUDIO_OPENSLES_SAMPLE_RATE			SL_SAMPLINGRATE_44_1
#define A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE		17640	//100MS
#define A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE	17640	//100MS
#define A20_AUDIO_MAX_HANDLE						4
#define A20_AUDIO_IN_BUF_SIZE						141120	//400MS
#define A20_AUDIO_IN_TEMP_BUF_SIZE				70560	//200MS
#define A20_AUDIO_OUT_BUF_SIZE					35280	//200MS
#elif defined A20_AUDIO_32KHZ_MODE
#define A20_AUDIO_DEV								"/dev/ChaosAudio"
#define A20_AUDIO_IN_CHANNELS						4
#define A20_AUDIO_IN_SAMPLE_RATE					32000
#define A20_AUDIO_OUT_CHANNELS					2
#define A20_AUDIO_OUT_SAMPLE_RATE				32000
#define A20_AUDIO_I2S_CHANNELS					2
#define A20_AUDIO_I2S_SAMPLE_RATE				32000
#define A20_AUDIO_OPENSLES_CHANNELS				2
#define A20_AUDIO_OPENSLES_SAMPLE_RATE			SL_SAMPLINGRATE_32
#define A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE		12800	//100MS
#define A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE	12800	//100MS
#define A20_AUDIO_MAX_HANDLE						4
#define A20_AUDIO_IN_BUF_SIZE						102400	//400MS
#define A20_AUDIO_IN_TEMP_BUF_SIZE				51200	//200MS
#define A20_AUDIO_OUT_BUF_SIZE					25600	//200MS
#endif

typedef enum tagCHAOS_AUDIO_MODE
{
	CHAOS_AUDIO_MODE_LEFT_CODEC_RIGHT_CODEC,
	CHAOS_AUDIO_MODE_LEFT_SPI_RIGHT_SPI,
	CHAOS_AUDIO_MODE_LEFT_MIXED_RIGHT_MIXED,
	CHAOS_AUDIO_MODE_LEFT_CODEC_RIGHT_MIXED,
	CHAOS_AUDIO_MODE_LEFT_SPI_RIGHT_MIXED,
	CHAOS_AUDIO_MODE_LEFT_MIXED_RIGHT_CODEC,
	CHAOS_AUDIO_MODE_LEFT_SPI_RIGHT_CODEC,
	CHAOS_AUDIO_MODE_LEFT_MIXED_RIGHT_SPI,
	CHAOS_AUDIO_MODE_LEFT_CODEC_RIGHT_SPI,
}CHAOS_AUDIO_MODE;

#define CHAOS_AUDIO_DEV							"/dev/ChaosAudio"

#define CHAOS_AUDIO_MAGIC							'C'
#define CHAOS_AUDIO_CMD_SET_ENABLE				_IOW (CHAOS_AUDIO_MAGIC, 0, int)
#define CHAOS_AUDIO_CMD_SET_MODE					_IOW (CHAOS_AUDIO_MAGIC, 1, int)
#define CHAOS_AUDIO_CMD_SET_CODEC_LEFT_VOL		_IOW (CHAOS_AUDIO_MAGIC, 2, int)		
#define CHAOS_AUDIO_CMD_SET_CODEC_RIGHT_VOL		_IOW (CHAOS_AUDIO_MAGIC, 3, int)
#define CHAOS_AUDIO_CMD_SET_SPI_LEFT_VOL		_IOW (CHAOS_AUDIO_MAGIC, 4, int)
#define CHAOS_AUDIO_CMD_SET_SPI_RIGHT_VOL		_IOW (CHAOS_AUDIO_MAGIC, 5, int)
#define CHAOS_AUDIO_CMD_SET_ECHO_VOL				_IOW (CHAOS_AUDIO_MAGIC, 6, int)
#define CHAOS_AUDIO_CMD_SET_ECHO_DELAY			_IOW (CHAOS_AUDIO_MAGIC, 7, int)
#define CHAOS_AUDIO_CMD_SET_EQ_100HZ_VOL		_IOW (CHAOS_AUDIO_MAGIC, 8, int)
#define CHAOS_AUDIO_CMD_SET_EQ_1KHZ_VOL			_IOW (CHAOS_AUDIO_MAGIC, 9, int)
#define CHAOS_AUDIO_CMD_SET_EQ_5KHZ_VOL			_IOW (CHAOS_AUDIO_MAGIC, 10, int)
#define CHAOS_AUDIO_CMD_SET_BBE_EN				_IOW (CHAOS_AUDIO_MAGIC, 11, int)
#define CHAOS_AUDIO_CMD_SET_BBE_LEVEL			_IOW (CHAOS_AUDIO_MAGIC, 12, int)
#define CHAOS_AUDIO_CMD_LATENCY_START			_IO (CHAOS_AUDIO_MAGIC, 13)
#define CHAOS_AUDIO_CMD_LATENCY_END				_IOR (CHAOS_AUDIO_MAGIC, 14, int)
#define CHAOS_AUDIO_CMD_SET_ADC_SELECT		_IOW (CHAOS_AUDIO_MAGIC, 15, int)
#define CHAOS_AUDIO_CMD_SET_LINE_GAIN		_IOW (CHAOS_AUDIO_MAGIC, 21, int)
#define CHAOS_AUDIO_CMD_SET_MIC1_GAIN		_IOW (CHAOS_AUDIO_MAGIC, 22, int)
#define CHAOS_AUDIO_CMD_SET_MIC2_GAIN		_IOW (CHAOS_AUDIO_MAGIC, 23, int)
#define CHAOS_AUDIO_CMD_SET_ADC_GAIN				_IOW (CHAOS_AUDIO_MAGIC, 16, int)
#define CHAOS_AUDIO_CMD_SET_DAC_GAIN				_IOW (CHAOS_AUDIO_MAGIC, 17, int)
#define CHAOS_AUDIO_CMD_GET_SPI_STATUS			_IOR (CHAOS_AUDIO_MAGIC, 18, int)
#define CHAOS_AUDIO_CMD_GET_VPP					_IOR (CHAOS_AUDIO_MAGIC, 19, int)
#define CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE	_IOW (CHAOS_AUDIO_MAGIC, 20, int)

#define CHAOS_AUDIO_CMD_GET_CODEC_LEFT_VOL		_IOR (CHAOS_AUDIO_MAGIC, 24, int)            
#define CHAOS_AUDIO_CMD_GET_CODEC_RIGHT_VOL		_IOR (CHAOS_AUDIO_MAGIC, 25, int)
#define CHAOS_AUDIO_CMD_GET_SPI_LEFT_VOL		_IOR (CHAOS_AUDIO_MAGIC, 26, int)
#define CHAOS_AUDIO_CMD_GET_SPI_RIGHT_VOL		_IOR (CHAOS_AUDIO_MAGIC, 27, int)
#define CHAOS_AUDIO_CMD_GET_ECHO_VOL			_IOR (CHAOS_AUDIO_MAGIC, 28, int)
#define CHAOS_AUDIO_CMD_GET_ECHO_DELAY			_IOR (CHAOS_AUDIO_MAGIC, 29, int)
#define CHAOS_AUDIO_CMD_GET_EQ_100HZ_VOL		_IOR (CHAOS_AUDIO_MAGIC, 30, int)
#define CHAOS_AUDIO_CMD_GET_EQ_1KHZ_VOL			_IOR (CHAOS_AUDIO_MAGIC, 31, int)
#define CHAOS_AUDIO_CMD_GET_EQ_5KHZ_VOL			_IOR (CHAOS_AUDIO_MAGIC, 32, int)



#define CHAOS_AUDIO_CMD_GET_SEED					_IOR (CHAOS_AUDIO_MAGIC, 77, int)



typedef struct tagA20_AUDIO_IN_INFO
{
	AUDIO_HANDLE		Handle;
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	int					Read;
}A20_AUDIO_IN_INFO;

typedef struct tagA20_AUDIO_SINK_INFO
{
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	unsigned char		Buf[A20_AUDIO_OUT_BUF_SIZE];
	unsigned char		TempBuf[A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE];
	int					Read;
	int					Write;
}A20_AUDIO_OUT_INFO;

typedef struct tagA20_AUDIO_INFO
{
	int								Handle;
	int								UartHandle;

	// engine interfaces
	SLObjectItf						engineObject;
	SLEngineItf						engineEngine;

	// output mix interfaces
	SLObjectItf						outputMixObject;
	SLEnvironmentalReverbItf		outputMixEnvironmentalReverb;

	// recorder interfaces
	SLObjectItf						recorderObject;
	SLRecordItf						recorderRecord;
	SLAndroidSimpleBufferQueueItf	recorderBufferQueue;

	// buffer queue player interfaces
	SLObjectItf						bqPlayerObject;
	SLPlayItf						bqPlayerPlay;
	SLAndroidSimpleBufferQueueItf	bqPlayerBufferQueue;
	SLEffectSendItf					bqPlayerEffectSend;
	SLMuteSoloItf					bqPlayerMuteSolo;
	SLVolumeItf						bqPlayerVolume;

	unsigned char					playerBuffer[A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE];
	unsigned char					recorderBuffer[A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE];

	A20_AUDIO_IN_INFO				AudioInInfo[A20_AUDIO_MAX_HANDLE];
	A20_AUDIO_OUT_INFO				AudioOutInfo[A20_AUDIO_MAX_HANDLE];

	unsigned char					AudioInBuf[A20_AUDIO_IN_BUF_SIZE];
	unsigned char					AudioInTempBuf[A20_AUDIO_IN_TEMP_BUF_SIZE];
	unsigned long					AudioInBufWrite;

	unsigned long					Seed;
}A20_AUDIO_INFO;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

extern void chaosaudio_chipdecrypt(unsigned char *SrcData, unsigned char *DestData);


static int ChaosAudio_Init (A20_AUDIO_INFO *pAudioInfo)
{
	unsigned char Seed[8] = {0};
	int Ret;

	pAudioInfo->Handle = open (A20_AUDIO_DEV, O_RDWR);
	log_for_pro("ChaosAudio_Init _Init[%d]", pAudioInfo->Handle);
	if (pAudioInfo->Handle != -1)
	{
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_SEED, (unsigned long)Seed);
		//log_for_pro ("ChaosAudio_Init1 [%x, %x, %x, %x, %x, %x, %x, %x]\n", Seed[0], Seed[1], Seed[2], Seed[3], Seed[4], Seed[5], Seed[6], Seed[7]);
		chaosaudio_chipdecrypt(Seed, Seed);
		//log_for_pro ("ChaosAudio_Init2 [%x, %x, %x, %x, %x, %x, %x, %x]\n", Seed[0], Seed[1], Seed[2], Seed[3], Seed[4], Seed[5], Seed[6], Seed[7]);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ENABLE, (unsigned long)Seed);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_MODE, CHAOS_AUDIO_MODE_LEFT_MIXED_RIGHT_MIXED);

		RF_OpenWirelessMic(pAudioInfo->Handle);

		return 0;
	}

	return -1;
}

static int ChaosAudio_Finish (A20_AUDIO_INFO *pAudioInfo)
{
	unsigned char Seed[8] = {0};
	if (pAudioInfo->Handle != -1)
	{
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ENABLE, (unsigned long)Seed);
		RF_CloseWirelessMic(pAudioInfo->Handle);
		close (pAudioInfo->Handle);
		return 0;
	}

	return -1;
}

static void A20AudioIn_Proc (A20_AUDIO_INFO *pAudioInfo)
{
	A20_AUDIO_IN_INFO *pAudioInInfo;
	int i;
	int Delta;

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInInfo = pAudioInfo->AudioInInfo + i;
		pthread_mutex_lock (&pAudioInInfo->Mutex);
		if (pAudioInInfo->Valid == 1)
		{
			if (pAudioInInfo->CallBack != NULL)
			{
				if (pAudioInInfo->Read > pAudioInfo->AudioInBufWrite)
				{
					Delta = pAudioInfo->AudioInBufWrite + A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read;
				}
				else
				{
					Delta = pAudioInfo->AudioInBufWrite - pAudioInInfo->Read;
				}
				if (Delta >= pAudioInInfo->Size)
				{
					if (pAudioInInfo->Read + pAudioInInfo->Size > A20_AUDIO_IN_BUF_SIZE)
					{
						memcpy (pAudioInfo->AudioInTempBuf, pAudioInfo->AudioInBuf + pAudioInInfo->Read, A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read);
						memcpy (pAudioInfo->AudioInTempBuf + (A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read), pAudioInfo->AudioInBuf, pAudioInInfo->Size - (A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read));
						pAudioInInfo->Read = pAudioInInfo->Read + pAudioInInfo->Size - A20_AUDIO_IN_BUF_SIZE;
					}
					else
					{
						memcpy (pAudioInfo->AudioInTempBuf, pAudioInfo->AudioInBuf + pAudioInInfo->Read, pAudioInInfo->Size);
						if (pAudioInInfo->Read + pAudioInInfo->Size == A20_AUDIO_IN_BUF_SIZE)
						{
							pAudioInInfo->Read = 0;
						}
						else
						{
							pAudioInInfo->Read += pAudioInInfo->Size;
						}
					}
					pAudioInInfo->CallBack (pAudioInInfo->User, pAudioInfo->AudioInTempBuf);
				}
			}
		}
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
	}

	return;
}

static void OpenSLES_Src_Callback (SLAndroidSimpleBufferQueueItf bq, void *context)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)context;
	int WriteSize;
	SLresult result;

	if (NULL == pAudioInfo)
	{
		log_for_pro ("OpenSLES_Src_Callback context Error!\n");
		return;
	}

	if (bq != pAudioInfo->recorderBufferQueue)
	{
		log_for_pro ("OpenSLES_Src_Callback bq Error!\n");
		return;
	}

	WriteSize = read (pAudioInfo->Handle, pAudioInfo->AudioInTempBuf, A20_AUDIO_IN_TEMP_BUF_SIZE);
	if (pAudioInfo->AudioInBufWrite + WriteSize > A20_AUDIO_IN_BUF_SIZE)
	{
		memcpy (pAudioInfo->AudioInBuf + pAudioInfo->AudioInBufWrite, pAudioInfo->AudioInTempBuf, A20_AUDIO_IN_BUF_SIZE - pAudioInfo->AudioInBufWrite);
		memcpy (pAudioInfo->AudioInBuf, pAudioInfo->AudioInTempBuf + (A20_AUDIO_IN_BUF_SIZE - pAudioInfo->AudioInBufWrite), WriteSize - (A20_AUDIO_IN_BUF_SIZE - pAudioInfo->AudioInBufWrite));
		pAudioInfo->AudioInBufWrite = pAudioInfo->AudioInBufWrite + WriteSize - A20_AUDIO_IN_BUF_SIZE;
	}
	else
	{
		memcpy (pAudioInfo->AudioInBuf + pAudioInfo->AudioInBufWrite, pAudioInfo->AudioInTempBuf, WriteSize);
		if (pAudioInfo->AudioInBufWrite + WriteSize == A20_AUDIO_IN_BUF_SIZE)
		{
			pAudioInfo->AudioInBufWrite = 0;
		}
		else
		{
			pAudioInfo->AudioInBufWrite += WriteSize;
		}
	}

	A20AudioIn_Proc (pAudioInfo);

	result = (*pAudioInfo->recorderBufferQueue)->Enqueue (pAudioInfo->recorderBufferQueue, pAudioInfo->recorderBuffer,
		A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Callback Enqueue Error!\n");
		return;
	}

	return;
}

static int OpenSLES_Src_Open (A20_AUDIO_INFO *pAudioInfo)
{
	const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
	const SLboolean req[1] = {SL_BOOLEAN_TRUE};
	SLresult result;

	SLDataLocator_IODevice loc_dev = {SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
		SL_DEFAULTDEVICEID_AUDIOINPUT, NULL};
	SLDataSource audioSrc = {&loc_dev, NULL};

	SLDataLocator_AndroidSimpleBufferQueue loc_bq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, A20_AUDIO_OPENSLES_CHANNELS, A20_AUDIO_OPENSLES_SAMPLE_RATE,
		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};
	SLDataSink audioSnk = {&loc_bq, &format_pcm};

	result = (*pAudioInfo->engineEngine)->CreateAudioRecorder(pAudioInfo->engineEngine, &pAudioInfo->recorderObject, &audioSrc,
		&audioSnk, 1, id, req);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open CreateAudioRecorder Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderObject)->Realize(pAudioInfo->recorderObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open Realize Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderObject)->GetInterface(pAudioInfo->recorderObject, SL_IID_RECORD, &pAudioInfo->recorderRecord);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open GetInterface Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderObject)->GetInterface(pAudioInfo->recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
		&pAudioInfo->recorderBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open GetInterface Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderBufferQueue)->RegisterCallback(pAudioInfo->recorderBufferQueue, OpenSLES_Src_Callback,
		pAudioInfo);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open RegisterCallback Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderRecord)->SetRecordState(pAudioInfo->recorderRecord, SL_RECORDSTATE_STOPPED);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open SetRecordState1 Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderBufferQueue)->Clear(pAudioInfo->recorderBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open Clear Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderBufferQueue)->Enqueue(pAudioInfo->recorderBufferQueue, pAudioInfo->recorderBuffer,
		A20_AUDIO_OPENSLES_RECORDER_BUF_SIZE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open Enqueue Error!\n");
		return -1;
	}

	result = (*pAudioInfo->recorderRecord)->SetRecordState(pAudioInfo->recorderRecord, SL_RECORDSTATE_RECORDING);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Src_Open SetRecordState2 Error!\n");
		return -1;
	}

	return 0;
}

static int OpenSLES_Src_Close (A20_AUDIO_INFO *pAudioInfo)
{
	if (pAudioInfo->recorderObject != NULL)
	{
		(*pAudioInfo->recorderObject)->Destroy(pAudioInfo->recorderObject);
		pAudioInfo->recorderObject = NULL;
		pAudioInfo->recorderRecord = NULL;
		pAudioInfo->recorderBufferQueue = NULL;
	}

	return 0;
}

static int A20AudioIn_Init (A20_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioInInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioInInfo[i].Mutex, NULL);
	}

	Ret = ChaosAudio_Init (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
		return -1;
	}

	Ret = OpenSLES_Src_Open (pAudioInfo);
	if (Ret != 0)
	{
		ChaosAudio_Finish (pAudioInfo);
		for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
		return -1;
	}

	return 0;
}

static int A20AudioIn_Finish (A20_AUDIO_INFO *pAudioInfo)
{
	int i;

	OpenSLES_Src_Close (pAudioInfo);

	ChaosAudio_Finish (pAudioInfo);

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
	}

	return 0;
}

static void A20AudioOut_Proc (A20_AUDIO_INFO *pAudioInfo)
{
	A20_AUDIO_OUT_INFO *pAudioOutInfo;;
	int i, j;
	int StreamCount;
	signed short *StreamList[A20_AUDIO_MAX_HANDLE];
	signed short *DestBuf;
	int Write;
	int Delta;
	int SizeLeft;
	int SampleCount;
	signed long Val;

	StreamCount = 0;
	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioOutInfo = pAudioInfo->AudioOutInfo + i;
		pthread_mutex_lock (&pAudioOutInfo->Mutex);
		if (pAudioOutInfo->Valid == 1)
		{
			if (pAudioOutInfo->CallBack == NULL)
			{
				Write = pAudioOutInfo->Write;
				if (Write < pAudioOutInfo->Read)
				{
					Delta = Write + A20_AUDIO_OUT_BUF_SIZE - pAudioOutInfo->Read;
				}
				else
				{
					Delta = Write - pAudioOutInfo->Read;
				}
				if (Delta >= A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE)
				{
					memcpy (pAudioOutInfo->TempBuf, pAudioOutInfo->Buf + pAudioOutInfo->Read, A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE);
					if (pAudioOutInfo->Read + A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE == A20_AUDIO_OUT_BUF_SIZE)
					{
						pAudioOutInfo->Read = 0;
					}
					else
					{
						pAudioOutInfo->Read += A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE;
					}
					StreamList[StreamCount++] = (signed short *)pAudioOutInfo->TempBuf;
				}
			}
			else
			{
				SizeLeft = A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE;
				while (SizeLeft > 0)
				{
					Delta = pAudioOutInfo->Size - pAudioOutInfo->Read;
					if (Delta > 0)
					{
						if (Delta >= SizeLeft)
						{
							memcpy (pAudioOutInfo->TempBuf + A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE - SizeLeft, pAudioOutInfo->Buf + pAudioOutInfo->Read, SizeLeft);
							pAudioOutInfo->Read += SizeLeft;
							SizeLeft = 0;
						}
						else
						{
							memcpy (pAudioOutInfo->TempBuf + A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE - SizeLeft, pAudioOutInfo->Buf + pAudioOutInfo->Read, Delta);
							pAudioOutInfo->Read += Delta;
							SizeLeft -= Delta;
						}
					}
					else
					{
						pAudioOutInfo->CallBack (pAudioOutInfo->User, pAudioOutInfo->Buf);
						pAudioOutInfo->Read = 0;
					}
				}
				StreamList[StreamCount++] = (signed short *)pAudioOutInfo->TempBuf;
			}
		}
		pthread_mutex_unlock (&pAudioOutInfo->Mutex);
	}

	if (StreamCount == 0)
	{
		memset (pAudioInfo->playerBuffer, 0, A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE);
	}
	else if (StreamCount == 1)
	{
		memcpy (pAudioInfo->playerBuffer, StreamList[0], A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE);
	}
	else
	{
		SampleCount = A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE / 2;
		DestBuf = (signed short *)pAudioInfo->playerBuffer;
		for (i = 0; i < SampleCount; i++)
		{
			Val = 0;
			for (j = 0; j < StreamCount; j++)
			{
				Val += *StreamList[j]++;
			}

			if (Val > 32767)
			{
				Val = 32767;
			}
			else if (Val < -32768)
			{
				Val = -32768;
			}

			*DestBuf++ = Val;
		}
	}

	return;
}

void OpenSLES_Sink_Callback (SLAndroidSimpleBufferQueueItf bq, void *context)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)context;
	SLresult result;

	if (NULL == pAudioInfo)
	{
		log_for_pro ("OpenSLES_Sink_Callback context Error!\n");
		return;
	}

	if (bq != pAudioInfo->bqPlayerBufferQueue)
	{
		log_for_pro ("OpenSLES_Sink_Callback bq Error!\n");
		return;
	}

	A20AudioOut_Proc (pAudioInfo);

	result = (*pAudioInfo->bqPlayerBufferQueue)->Enqueue (pAudioInfo->bqPlayerBufferQueue, pAudioInfo->playerBuffer, A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Callback Enqueue Error!\n");
		return;
	}

	return;
}

static int OpenSLES_Sink_Open (A20_AUDIO_INFO *pAudioInfo)
{
	const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
		/*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
		/*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
	SLresult result;

	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, A20_AUDIO_OPENSLES_CHANNELS, A20_AUDIO_OPENSLES_SAMPLE_RATE,
		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};
	SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, pAudioInfo->outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	result = (*pAudioInfo->engineEngine)->CreateAudioPlayer(pAudioInfo->engineEngine, &pAudioInfo->bqPlayerObject, &audioSrc, &audioSnk,
		3, ids, req);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open CreateAudioPlayer Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerObject)->Realize(pAudioInfo->bqPlayerObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open Realize Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerObject)->GetInterface(pAudioInfo->bqPlayerObject, SL_IID_PLAY, &pAudioInfo->bqPlayerPlay);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open GetInterface1 Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerObject)->GetInterface(pAudioInfo->bqPlayerObject, SL_IID_BUFFERQUEUE,
		&pAudioInfo->bqPlayerBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open GetInterface2 Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerBufferQueue)->RegisterCallback(pAudioInfo->bqPlayerBufferQueue, OpenSLES_Sink_Callback, pAudioInfo);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open RegisterCallback Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerObject)->GetInterface(pAudioInfo->bqPlayerObject, SL_IID_EFFECTSEND,
		&pAudioInfo->bqPlayerEffectSend);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open GetInterface3 Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerObject)->GetInterface(pAudioInfo->bqPlayerObject, SL_IID_VOLUME, &pAudioInfo->bqPlayerVolume);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open GetInterface4 Error!\n");
		return -1;
	}

	result = (*pAudioInfo->bqPlayerPlay)->SetPlayState(pAudioInfo->bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Open SetPlayState Error!\n");
		return -1;
	}

	A20AudioOut_Proc (pAudioInfo);

	result = (*pAudioInfo->bqPlayerBufferQueue)->Enqueue(pAudioInfo->bqPlayerBufferQueue, pAudioInfo->playerBuffer, A20_AUDIO_OPENSLES_PLAYER_BUF_SIZE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Sink_Callback Enqueue Error!\n");
		return -1;
	}

	return 0;
}

static int OpenSLES_Sink_Close (A20_AUDIO_INFO *pAudioInfo)
{
	if (pAudioInfo->bqPlayerObject != NULL)
	{
		(*pAudioInfo->bqPlayerObject)->Destroy(pAudioInfo->bqPlayerObject);
		pAudioInfo->bqPlayerObject = NULL;
		pAudioInfo->bqPlayerPlay = NULL;
		pAudioInfo->bqPlayerBufferQueue = NULL;
		pAudioInfo->bqPlayerEffectSend = NULL;
		pAudioInfo->bqPlayerMuteSolo = NULL;
		pAudioInfo->bqPlayerVolume = NULL;
	}

	return 0;
}

static int A20AudioOut_Init (A20_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioOutInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioOutInfo[i].Mutex, NULL);
	}

	Ret = OpenSLES_Sink_Open (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
		}
	}

	return Ret;
}

static int A20AudioOut_Finish (A20_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	Ret = OpenSLES_Sink_Close (pAudioInfo);

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
	}

	return Ret;
}

static int OpenSLES_Engine_Init (A20_AUDIO_INFO *pAudioInfo)
{
	const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	SLresult result;

	result = slCreateEngine (&pAudioInfo->engineObject, 0, NULL, 0, NULL, NULL);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Engine_Init slCreateEngine!\n");
		return -1;
	}

	result = (*pAudioInfo->engineObject)->Realize(pAudioInfo->engineObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Engine_Init Realize!\n");
		return -1;
	}

	result = (*pAudioInfo->engineObject)->GetInterface(pAudioInfo->engineObject, SL_IID_ENGINE, &pAudioInfo->engineEngine);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Engine_Init GetInterface!\n");
		return -1;
	}

	result = (*pAudioInfo->engineEngine)->CreateOutputMix(pAudioInfo->engineEngine, &pAudioInfo->outputMixObject, 1, ids, req);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Engine_Init CreateOutputMix!\n");
		return -1;
	}

	result = (*pAudioInfo->outputMixObject)->Realize(pAudioInfo->outputMixObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		log_for_pro ("OpenSLES_Engine_Init Realize!\n");
		return -1;
	}

	result = (*pAudioInfo->outputMixObject)->GetInterface(pAudioInfo->outputMixObject, SL_IID_ENVIRONMENTALREVERB,
		&pAudioInfo->outputMixEnvironmentalReverb);
	if (SL_RESULT_SUCCESS == result)
	{
		result = (*pAudioInfo->outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
			pAudioInfo->outputMixEnvironmentalReverb, &reverbSettings);
	}

	return 0;
}

static int OpenSLES_Engine_Finish (A20_AUDIO_INFO *pAudioInfo)
{
	if (pAudioInfo->engineObject != NULL)
	{
		(*pAudioInfo->engineObject)->Destroy(pAudioInfo->engineObject);
		pAudioInfo->engineObject = NULL;
		pAudioInfo->engineEngine = NULL;
	}

	return 0;
}

long A20Audio_Set (AUDIO_HANDLE Handle, int Cmd, int Data)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)Handle;
	int Ret = 0;

	log_for_pro ("A20Audio_Set [%d, %d]!\n", Cmd, Data);
	switch (Cmd)
	{
	case A20_AUDIO_CMD_SET_MODE:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_MODE, Data);
		break;

	case CP_AUDIO_CMD_SET_MIC1_VOL:
	case A20_AUDIO_CMD_SET_CODEC_LEFT_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_LEFT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_MIC2_VOL:
	case A20_AUDIO_CMD_SET_CODEC_RIGHT_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_RIGHT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_WMIC1_VOL:
	case A20_AUDIO_CMD_SET_SPI_LEFT_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_LEFT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_WMIC2_VOL:
	case A20_AUDIO_CMD_SET_SPI_RIGHT_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_RIGHT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_ECHO_VOL:
	case A20_AUDIO_CMD_SET_ECHO_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_VOL, Data);
		break;

	case A20_AUDIO_CMD_SET_EQ_100HZ_VOL:
		if (Data < -18)
		{
			Data = -18;
		}
		else if (Data > 18)
		{
			Data = 18;
		}
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_EQ_100HZ_VOL, Data + 18);
		break;

	case A20_AUDIO_CMD_SET_EQ_1KHZ_VOL:
		if (Data < -18)
		{
			Data = -18;
		}
		else if (Data > 18)
		{
			Data = 18;
		}
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_EQ_1KHZ_VOL, Data + 18);
		break;

	case A20_AUDIO_CMD_SET_EQ_5KHZ_VOL:
		if (Data < -18)
		{
			Data = -18;
		}
		else if (Data > 18)
		{
			Data = 18;
		}
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_EQ_5KHZ_VOL, Data + 18);
		break;

	case A20_AUDIO_CMD_TEST_LATENCY:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_LATENCY_START, 0);
		break;

	case A20_AUDIO_CMD_GET_LATENCY:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_LATENCY_END, 0);
		break;

	case A20_AUDIO_CMD_GET_SPI_STATUS:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_SPI_STATUS, 0);
		break;

	case A20_AUDIO_CMD_SET_BBE_EN:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_BBE_EN, Data);
		break;

	case A20_AUDIO_CMD_SET_ECHO_DELAY:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_DELAY, Data);
		break;

	case A20_AUDIO_CMD_SET_BBE_LEVEL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_BBE_LEVEL, Data);
		break;

	case A20_AUDIO_CMD_GET_CODEC_LEFT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 0);
		break;
		
	case A20_AUDIO_CMD_GET_CODEC_RIGHT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 1);
		break;
		
	case A20_AUDIO_CMD_GET_SPI_LEFT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 2);
		break;
		
	case A20_AUDIO_CMD_GET_SPI_RIGHT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 3);
		break;

	case A20_AUDIO_CMD_SELECT_INPUT:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_SELECT, Data);
		break;

	case A20_AUDIO_CMD_SET_ADC_GAIN:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_GAIN, Data);
		break;

	case A20_AUDIO_CMD_DENOISE_MODE:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE, Data);
		break;
	}

	return Ret;
}


long A20Audio_Get (AUDIO_HANDLE Handle, int Cmd, int *Data)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)Handle;
	int Ret = 0;

	switch (Cmd)
	{
	case A20_AUDIO_CMD_GET_ECHOVOL:
		*Data = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_ECHO_VOL, 0);
		break;

	case A20_AUDIO_CMD_GET_MICVOL:
		*Data = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_CODEC_LEFT_VOL, 0);
		break;
	}

	return Ret;
}


AUDIO_IN_HANDLE A20AudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)Handle;
	A20_AUDIO_IN_INFO *pAudioInInfo;
	int i;

	log_for_pro("enter A20AudioIn_Open");
	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInInfo = pAudioInfo->AudioInInfo + i;

		pthread_mutex_lock (&pAudioInInfo->Mutex);
		if (pAudioInInfo->Valid == 0)
		{
			Param->Channels = A20_AUDIO_IN_CHANNELS;
			Param->SampleRate = A20_AUDIO_IN_SAMPLE_RATE;
			pAudioInInfo->Handle = Handle;
			pAudioInInfo->CallBack = Param->CallBack;
			pAudioInInfo->User = Param->User;
			pAudioInInfo->Size = Param->FrameCount * Param->Channels * 2;
			pAudioInInfo->Read = pAudioInfo->AudioInBufWrite;
			pAudioInInfo->Valid = 1;
			pthread_mutex_unlock (&pAudioInInfo->Mutex);
			break;
		}
		else
		{
			pthread_mutex_unlock (&pAudioInInfo->Mutex);
		}

	}

	if (i == A20_AUDIO_MAX_HANDLE)
	{
		log_for_pro("exit A20AudioIn_Close failed");
		return NULL;
	}
	log_for_pro("exit A20AudioIn_Close success");

	return (AUDIO_IN_HANDLE)pAudioInInfo;
}

long A20AudioIn_Close (AUDIO_IN_HANDLE Handle)
{
	A20_AUDIO_IN_INFO *pAudioInInfo = (A20_AUDIO_IN_INFO *)Handle;

	log_for_pro("enter A20AudioIn_Close");
	pthread_mutex_lock (&pAudioInInfo->Mutex);
	if (pAudioInInfo->Valid == 1)
	{
		pAudioInInfo->Valid = 0;
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
		log_for_pro("exit A20AudioIn_Close success");
		return 0;
	}
	else
	{
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
		log_for_pro("exit A20AudioIn_Close failed");
		return -1;
	}
}

long A20AudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	A20_AUDIO_IN_INFO *pAudioInInfo = (A20_AUDIO_IN_INFO *)Handle;
	A20_AUDIO_INFO *pAudioInfo;
	int Write, Delta;

	pAudioInfo = (A20_AUDIO_INFO *)pAudioInInfo->Handle;
	if (pAudioInInfo->Valid == 1)
	{
		Write = pAudioInfo->AudioInBufWrite;
		if (pAudioInInfo->Read > Write)
		{
			Delta = Write + A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read;
		}
		else
		{
			Delta = Write - pAudioInInfo->Read;
		}
		if (Delta > Size)
		{
			Delta = Size;
		}
		if (pAudioInInfo->Read + Delta > A20_AUDIO_IN_BUF_SIZE)
		{
			memcpy (BufAddr, pAudioInfo->AudioInBuf + pAudioInInfo->Read, A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read);
			memcpy ((unsigned char *)BufAddr + (A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read), pAudioInfo->AudioInBuf, Delta - (A20_AUDIO_IN_BUF_SIZE - pAudioInInfo->Read));
			pAudioInInfo->Read = pAudioInInfo->Read + Delta - A20_AUDIO_IN_BUF_SIZE;
		}
		else
		{
			memcpy (BufAddr, pAudioInfo->AudioInBuf + pAudioInInfo->Read, Delta);
			if (pAudioInInfo->Read + Delta == A20_AUDIO_IN_BUF_SIZE)
			{
				pAudioInInfo->Read = 0;
			}
			else
			{
				pAudioInInfo->Read += Delta;
			}
		}
		return Delta;
	}
	else
	{
		return -1;
	}
}

AUDIO_OUT_HANDLE A20AudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)Handle;
	A20_AUDIO_OUT_INFO *pAudioOutInfo;
	int i;

	log_for_pro("enter A20AudioOut_Open");

	for (i = 0; i < A20_AUDIO_MAX_HANDLE; i++)
	{
		pAudioOutInfo = pAudioInfo->AudioOutInfo + i;

		pthread_mutex_lock (&pAudioOutInfo->Mutex);
		if (pAudioOutInfo->Valid == 0)
		{
			Param->Channels = A20_AUDIO_OUT_CHANNELS;
			Param->SampleRate = A20_AUDIO_OUT_SAMPLE_RATE;
			pAudioOutInfo->CallBack = Param->CallBack;
			pAudioOutInfo->User = Param->User;
			pAudioOutInfo->Size = Param->FrameCount * Param->Channels * 2;
			if (pAudioOutInfo->Size > A20_AUDIO_OUT_BUF_SIZE)
			{
				pAudioOutInfo->Size = A20_AUDIO_OUT_BUF_SIZE;
				Param->FrameCount = A20_AUDIO_OUT_BUF_SIZE / Param->Channels / 2;
			}
			pAudioOutInfo->Read = pAudioOutInfo->Size;
			pAudioOutInfo->Write = 0;
			pAudioOutInfo->Valid = 1;
			pthread_mutex_unlock (&pAudioOutInfo->Mutex);
			break;
		}
		else
		{
			pthread_mutex_unlock (&pAudioOutInfo->Mutex);
		}

	}

	if (i == A20_AUDIO_MAX_HANDLE)
	{
		log_for_pro("exit A20AudioOut_Open failed");
		return NULL;
	}

	log_for_pro("exit A20AudioOut_Open success");
	return (AUDIO_OUT_HANDLE)pAudioOutInfo;
}

long A20AudioOut_Close (AUDIO_OUT_HANDLE Handle)
{
	A20_AUDIO_OUT_INFO *pAudioOutInfo = (A20_AUDIO_OUT_INFO *)Handle;

	log_for_pro("enter A20AudioOut_Close");
	pthread_mutex_lock (&pAudioOutInfo->Mutex);
	if (pAudioOutInfo->Valid == 1)
	{
		pAudioOutInfo->Valid = 0;
		pthread_mutex_unlock (&pAudioOutInfo->Mutex);
		log_for_pro("exit A20AudioOut_Close success");
		return 0;
	}
	else
	{
		pthread_mutex_unlock (&pAudioOutInfo->Mutex);
		log_for_pro("exit A20AudioOut_Close failed");
		return -1;
	}
}

long A20AudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	A20_AUDIO_OUT_INFO *pAudioOutInfo = (A20_AUDIO_OUT_INFO *)Handle;
	int Free, Read;

	if (pAudioOutInfo->Valid == 1)
	{
		Read = pAudioOutInfo->Read;
		if (Read > pAudioOutInfo->Write)
		{
			Free = Read - pAudioOutInfo->Write;
		}
		else
		{
			Free = A20_AUDIO_OUT_BUF_SIZE - (pAudioOutInfo->Write - Read);
		}
		if (Free > Size)
		{
			Free = Size;
		}
		if (pAudioOutInfo->Write + Free > A20_AUDIO_OUT_BUF_SIZE)
		{
			memcpy (pAudioOutInfo->Buf + pAudioOutInfo->Write, BufAddr, A20_AUDIO_OUT_BUF_SIZE - pAudioOutInfo->Write);
			memcpy (pAudioOutInfo->Buf, (unsigned char *)BufAddr + (A20_AUDIO_OUT_BUF_SIZE - pAudioOutInfo->Write), Free - (A20_AUDIO_OUT_BUF_SIZE - pAudioOutInfo->Write));
			pAudioOutInfo->Write = pAudioOutInfo->Write + Free - A20_AUDIO_OUT_BUF_SIZE;
		}
		else
		{
			memcpy (pAudioOutInfo->Buf + pAudioOutInfo->Write, BufAddr, Free);
			if (pAudioOutInfo->Write + Free == A20_AUDIO_OUT_BUF_SIZE)
			{
				pAudioOutInfo->Write = 0;
			}
			else
			{
				pAudioOutInfo->Write += Free;
			}
		}
		return Free;
	}
	else
	{
		return -1;
	}
}

#define TTY_TEST_DEV							"/dev/ttyS5"
static int A20AudioUart_Init (A20_AUDIO_INFO *pAudioInfo)
{
	struct termios newtio, oldtio;
	
	pAudioInfo->UartHandle = open (TTY_TEST_DEV, O_RDWR|O_NOCTTY|O_NDELAY);
	if (pAudioInfo->UartHandle == -1)
	{
		return -1;
	}

	if (tcgetattr (pAudioInfo->UartHandle, &oldtio) != 0)
	{
		close (pAudioInfo->UartHandle);
		return -1;
	}

	memset (&newtio, 0, sizeof (newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	// 8Bit
	newtio.c_cflag |= CS8;

	// 无校验位
	newtio.c_cflag &= ~PARENB;

	// A20平台B57600实际波特率33000
	cfsetispeed(&newtio, B57600);
	cfsetospeed(&newtio, B57600);

	// 2位停止位
	newtio.c_cflag |= CSTOPB;

	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush (pAudioInfo->UartHandle, TCIFLUSH);

	if ((tcsetattr (pAudioInfo->UartHandle, TCSANOW, &newtio)) != 0)
	{
		close (pAudioInfo->UartHandle);
		return -1;
	}

	return 0;
}

static int A20AudioUart_Finish (A20_AUDIO_INFO *pAudioInfo)
{
	close (pAudioInfo->UartHandle);

	return 0;
}

AUDIO_HANDLE A20Audio_Init (int samplerate)
{
	A20_AUDIO_INFO *pAudioInfo;
	int Ret;

	log_for_pro("enter A20Audio_Init");
	pAudioInfo = (A20_AUDIO_INFO *)malloc (sizeof (A20_AUDIO_INFO));
	if (pAudioInfo == NULL)
	{
		log_for_pro("error malloc A20Audio_Init");
		return NULL;
	}

	pAudioInfo->Handle = -1;
	pAudioInfo->AudioInBufWrite = 0;

#ifdef SUPPORT_EXT_MIDI
	Ret = A20AudioUart_Init (pAudioInfo);
	if (Ret != 0)
	{
		free (pAudioInfo);
		return NULL;
	}
#endif

	Ret = OpenSLES_Engine_Init (pAudioInfo);
	log_for_pro("OpenSLES _Init[%d]", Ret);
	if (Ret != 0)
	{
#ifdef SUPPORT_EXT_MIDI
		A20AudioUart_Finish (pAudioInfo);
#endif
		free (pAudioInfo);
		return NULL;
	}

	Ret = A20AudioIn_Init (pAudioInfo);
	log_for_pro("A20AudioIn _Init[%d]", Ret);
	if (Ret != 0)
	{
		OpenSLES_Engine_Finish (pAudioInfo);
#ifdef SUPPORT_EXT_MIDI
		A20AudioUart_Finish (pAudioInfo);
#endif
		free (pAudioInfo);
		return NULL;
	}

	Ret = A20AudioOut_Init (pAudioInfo);
	log_for_pro("A20AudioOut _Init[%d]", Ret);
	if (Ret != 0)
	{
		A20AudioIn_Finish (pAudioInfo);
		OpenSLES_Engine_Finish (pAudioInfo);
#ifdef SUPPORT_EXT_MIDI
		A20AudioUart_Finish (pAudioInfo);
#endif
		free (pAudioInfo);
		return NULL;
	}

	A20Audio_Set(pAudioInfo->Handle, A20_AUDIO_CMD_SELECT_INPUT, ADC_LINEIN);
	A20Audio_Set(pAudioInfo->Handle, A20_AUDIO_CMD_SET_ADC_GAIN, 3);
	A20Audio_Set(pAudioInfo->Handle, A20_AUDIO_CMD_DENOISE_MODE, 0);

	log_for_pro("exit A20Audio_Init success");

	return (AUDIO_HANDLE)pAudioInfo;
}

long A20Audio_Finish (AUDIO_HANDLE Handle)
{
	A20_AUDIO_INFO *pAudioInfo = (A20_AUDIO_INFO *)Handle;

	log_for_pro("enter A20Audio_Finish");

	A20AudioOut_Finish (pAudioInfo);

	A20AudioIn_Finish (pAudioInfo);

	OpenSLES_Engine_Finish (pAudioInfo);

#ifdef SUPPORT_EXT_MIDI
	A20AudioUart_Finish (pAudioInfo);
#endif

	free (pAudioInfo);

	log_for_pro("exit A20Audio_Finish success");

	return 0;
}

