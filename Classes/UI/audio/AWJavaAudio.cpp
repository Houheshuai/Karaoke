#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <termios.h>
#include <sys/ioctl.h>

extern "C"
{
#include "AuthHardware.h"
}


#include "rfmod.h"
#include "AWJavaAudio.h"

#include <android/log.h>
#define  LOG_TAG    "javaaudio"
#define  log_for_pro(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define NO_JAVA_AUDIO_SRC
//#define NO_JAVA_AUDIO_SINK
//#define SUPPORT_EXT_MIDI
//#define WRITE_TO_DEVICE

#define AW_JAVA_AUDIO_MAX_HANDLE						4
#define AW_JAVA_AUDIO_SLEEP_TIME						10000	//10MS


#define AW_JAVA_AUDIO_IN_CHANNELS					4
#define AW_JAVA_AUDIO_IN_TEMP_BUF_TIME				100
#define AW_JAVA_AUDIO_IN_TEMP_BUF_SIZE				38400	//100MS
#define AW_JAVA_AUDIO_IN_BUF_TIME					400
#define AW_JAVA_AUDIO_IN_BUF_SIZE					153600	//400MS

#define AW_JAVA_AUDIO_OUT_TEMP_BUF_TIME				100
#define AW_JAVA_AUDIO_OUT_TEMP_BUF_SIZE				19200	//100MS
#define AW_JAVA_AUDIO_OUT_BUF_TIME					200
#define AW_JAVA_AUDIO_OUT_BUF_SIZE					38400	//200MS


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
#define CHAOS_AUDIO_CMD_SEL_INPUT				_IOW (CHAOS_AUDIO_MAGIC, 15, int)
#define CHAOS_AUDIO_CMD_SET_ADC_GAIN				_IOW (CHAOS_AUDIO_MAGIC, 16, int)
#define CHAOS_AUDIO_CMD_SET_DAC_GAIN				_IOW (CHAOS_AUDIO_MAGIC, 17, int)
#define CHAOS_AUDIO_CMD_GET_SPI_STATUS			_IOR (CHAOS_AUDIO_MAGIC, 18, int)
#define CHAOS_AUDIO_CMD_GET_VPP					_IOR (CHAOS_AUDIO_MAGIC, 19, int)
#define CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE	_IOW (CHAOS_AUDIO_MAGIC, 20, int)
#define CHAOS_AUDIO_CMD_SET_TIME_START			_IOW (CHAOS_AUDIO_MAGIC, 21, int)
#define CHAOS_AUDIO_CMD_SET_TIME_DURATION		_IOW (CHAOS_AUDIO_MAGIC, 22, int)
#define CHAOS_AUDIO_CMD_SET_TIME_TEMPO			_IOW (CHAOS_AUDIO_MAGIC, 23, int)
#define CHAOS_AUDIO_CMD_SET_AGC_ENABLE			_IOW (CHAOS_AUDIO_MAGIC, 24, int)
#define CHAOS_AUDIO_CMD_SET_AGC_GAIN				_IOW (CHAOS_AUDIO_MAGIC, 25, int)
#define CHAOS_AUDIO_CMD_SET_AGC_TARGET			_IOW (CHAOS_AUDIO_MAGIC, 26, int)
#define CHAOS_AUDIO_CMD_GET_SEED					_IOR (CHAOS_AUDIO_MAGIC, 77, int)


#define GD32_CTRL_DEVICE 					"/dev/mu_gd"
#define GD32_CTRL_MAGIC						'G'
#define GD32_CTRL_CMD_SET_DBGUART			_IOW (GD32_CTRL_MAGIC, 5, int)


// ADC SELECT
// 000 LINEINL LINEINR or LINEIN depending on LNRDF
// 001 FMINL FMINR
// 010 MIC1     Default
// 011 MIC2
// 100 MIC1 MIC2
// 101 MIC
// 110 MIXL MIXR
// 111 LINEINL or LINEIN depending on LNRDF MIC1
enum
{
	ADC_LINEIN = 0,
	ADC_FMIN = 1,
	ADC_MIC1 = 2,
	ADC_MIC2 = 3,
	ADC_MIC1_MIC2 = 4,
	ADC_MIC = 5,
	ADC_MIX = 6,
	ADC_LINEINMIC = 7
};




typedef struct tagAW_JAVA_AUDIO_IN_INFO
{
	AUDIO_HANDLE		Handle;
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	int					Read;
}AW_JAVA_AUDIO_IN_INFO;

typedef struct tagAW_JAVA_AUDIO_SINK_INFO
{
	AUDIO_HANDLE		Handle;
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	unsigned char		Buf[AW_JAVA_AUDIO_OUT_BUF_SIZE];
	unsigned char		TempBuf[AW_JAVA_AUDIO_OUT_TEMP_BUF_SIZE];
	int					Read;
	int					Write;
}AW_JAVA_AUDIO_OUT_INFO;

typedef struct tagAW_JAVA_AUDIO_INFO
{
	int								Handle;
	int								UartHandle;
	
	ANDROID_JAVA_AUDIO_PARAM		*Param;
	pthread_mutex_t					Mutex;

	unsigned long					InChannels;
	unsigned long					InSampleRate;

	unsigned long					InExitFlag;
	pthread_t						InThreadHandle;
	JNIEnv							*InEnv;
	jbyteArray						InByteArray;
	jmethodID						InMid;

	unsigned char					InTempBuf[AW_JAVA_AUDIO_IN_TEMP_BUF_SIZE];
	unsigned long					InTempBufSize;
	unsigned char					InBuf[AW_JAVA_AUDIO_IN_BUF_SIZE];
	unsigned long					InBufSize;
	unsigned long					InBufWrite;

	unsigned long					OutChannels;
	unsigned long					OutSampleRate;

	unsigned long					OutExitFlag;
	pthread_t						OutThreadHandle;
	JNIEnv							*OutEnv;
	jbyteArray						OutByteArray;
	jmethodID						OutMid;
	jmethodID						OutAudioTrackPlay;
	jmethodID 						OutAUdioTrackPause;

	unsigned long					OutBufSize;
	unsigned char					OutTempBuf[AW_JAVA_AUDIO_OUT_TEMP_BUF_SIZE];
	unsigned char					OutTempBuf2[AW_JAVA_AUDIO_OUT_TEMP_BUF_SIZE];
	unsigned long					OutTempBufSize;
	unsigned long					OutTempBufWrite;

	AW_JAVA_AUDIO_IN_INFO			AudioInInfo[AW_JAVA_AUDIO_MAX_HANDLE];
	AW_JAVA_AUDIO_OUT_INFO			AudioOutInfo[AW_JAVA_AUDIO_MAX_HANDLE];
}AW_JAVA_AUDIO_INFO;

//ANDROID_JAVA_AUDIO_PARAM mAudioParam;

extern "C" void chaosaudio_chipdecrypt(unsigned char *SrcData, unsigned char *DestData);
//extern int Set_RenderReturn(unsigned long renderval);

static int ChaosAudio_Init (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	unsigned char Seed[8] = {0};
	int Ret;

	if(1)
	{
		int input[4];
		int gd_fd = open(GD32_CTRL_DEVICE, O_RDWR);
		if(gd_fd != -1)
		{
			log_for_pro("set dbg uart 0");
			input[0] = input[1] = input[2] = 1;
			ioctl(gd_fd, GD32_CTRL_CMD_SET_DBGUART, (unsigned long)input);
			close(gd_fd);
		}
		else
		{
			log_for_pro("failed to open %s", GD32_CTRL_DEVICE);
		}
	}

	pAudioInfo->Handle = open (CHAOS_AUDIO_DEV, O_RDWR);
	log_for_pro("ChaosAudio_Init_Init[%d]", pAudioInfo->Handle);
	if (pAudioInfo->Handle != -1)
	{
		//Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_SEED, (unsigned long)Seed);
		//log_for_pro ("ChaosAudio_Init1 [%x, %x, %x, %x, %x, %x, %x, %x]\n", Seed[0], Seed[1], Seed[2], Seed[3], Seed[4], Seed[5], Seed[6], Seed[7]);
		//chaosaudio_chipdecrypt(Seed, Seed);
		//log_for_pro ("ChaosAudio_Init2 [%x, %x, %x, %x, %x, %x, %x, %x]\n", Seed[0], Seed[1], Seed[2], Seed[3], Seed[4], Seed[5], Seed[6], Seed[7]);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ENABLE, (unsigned long)Seed);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_MODE, CHAOS_AUDIO_MODE_LEFT_MIXED_RIGHT_MIXED);
		//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_SELECT, ADC_LINEIN);
		//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_GAIN, 3);
		//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE, 0);

		return 0;
	}

	return -1;
}

static int ChaosAudio_Finish (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	unsigned char Seed[8] = {0};
	if (pAudioInfo->Handle != -1)
	{
		//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ENABLE, (unsigned long)Seed);
		close (pAudioInfo->Handle);
		return 0;
	}

	return -1;
}

static void AWJavaAudioIn_Proc (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	AW_JAVA_AUDIO_IN_INFO *pAudioInInfo;
	int i;
	int Delta;

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInInfo = pAudioInfo->AudioInInfo + i;
		pthread_mutex_lock (&pAudioInInfo->Mutex);
		if (pAudioInInfo->Valid == 1)
		{
			if (pAudioInInfo->CallBack != NULL)
			{
				if (pAudioInInfo->Read > pAudioInfo->InBufWrite)
				{
					Delta = pAudioInfo->InBufWrite + pAudioInfo->InBufSize - pAudioInInfo->Read;
				}
				else
				{
					Delta = pAudioInfo->InBufWrite - pAudioInInfo->Read;
				}
				if (Delta >= pAudioInInfo->Size)
				{
					if (pAudioInInfo->Read + pAudioInInfo->Size > pAudioInfo->InBufSize)
					{
						memcpy (pAudioInfo->InTempBuf, pAudioInfo->InBuf + pAudioInInfo->Read, pAudioInfo->InBufSize - pAudioInInfo->Read);
						memcpy (pAudioInfo->InTempBuf + (pAudioInfo->InBufSize - pAudioInInfo->Read), pAudioInfo->InBuf, pAudioInInfo->Size - (pAudioInfo->InBufSize - pAudioInInfo->Read));
						pAudioInInfo->Read = pAudioInInfo->Read + pAudioInInfo->Size - pAudioInfo->InBufSize;
					}
					else
					{
						memcpy (pAudioInfo->InTempBuf, pAudioInfo->InBuf + pAudioInInfo->Read, pAudioInInfo->Size);
						if (pAudioInInfo->Read + pAudioInInfo->Size == pAudioInfo->InBufSize)
						{
							pAudioInInfo->Read = 0;
						}
						else
						{
							pAudioInInfo->Read += pAudioInInfo->Size;
						}
					}
					pAudioInInfo->CallBack (pAudioInInfo->User, pAudioInfo->InTempBuf);
				}
			}
		}
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
	}

	return;
}

#ifdef NO_JAVA_AUDIO_SRC
static void *AWJavaAudio_Src_Thread (void *Data)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Data;
	jbyte *OldData;
	int Ret;
#ifdef TWO_CHANNELS
	signed short *Src, *Dest;
	int i, Count;
#endif

	while (1)
	{
		if (pAudioInfo->InExitFlag == 1)
		{
			break;
		}

#ifdef TWO_CHANNELS
		Ret = read (pAudioInfo->Handle, pAudioInfo->InTempBuf, pAudioInfo->InTempBufSize * 2);
		Ret = Ret / 2;

		Src = (signed short *)pAudioInfo->InTempBuf;
		Dest = (signed short *)pAudioInfo->InTempBuf;
		Count = Ret / 4;
		for (i = 0; i < Count; i++)
		{
			Src += 2;
			*Dest++ = *Src++;
			*Dest++ = *Src++;
		}
#else
		Ret = read (pAudioInfo->Handle, pAudioInfo->InTempBuf, pAudioInfo->InTempBufSize * 2);
#endif

		if (pAudioInfo->InBufWrite + Ret > pAudioInfo->InBufSize)
		{
			memcpy (pAudioInfo->InBuf + pAudioInfo->InBufWrite, pAudioInfo->InTempBuf, pAudioInfo->InBufSize - pAudioInfo->InBufWrite);
			memcpy (pAudioInfo->InBuf, pAudioInfo->InTempBuf + (pAudioInfo->InBufSize - pAudioInfo->InBufWrite), Ret - (pAudioInfo->InBufSize - pAudioInfo->InBufWrite));
			pAudioInfo->InBufWrite = pAudioInfo->InBufWrite + Ret - pAudioInfo->InBufSize;
		}
		else
		{
			memcpy (pAudioInfo->InBuf + pAudioInfo->InBufWrite, pAudioInfo->InTempBuf, Ret);
			if (pAudioInfo->InBufWrite + Ret == pAudioInfo->InBufSize)
			{
				pAudioInfo->InBufWrite = 0;
			}
			else
			{
				pAudioInfo->InBufWrite += Ret;
			}
		}

		AWJavaAudioIn_Proc (pAudioInfo);

		if (Ret != pAudioInfo->InTempBufSize)
		{
			usleep (AW_JAVA_AUDIO_SLEEP_TIME);
		}
	}

	pthread_exit(0);
}
#else
static void *AWJavaAudio_Src_Thread (void *Data)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Data;
	jbyte *OldData;
	int Ret;
#ifdef TWO_CHANNELS
	signed short *Src, *Dest;
	int i, Count;
#endif

	pthread_mutex_lock (&pAudioInfo->Mutex);
	pAudioInfo->Param->Jvm->AttachCurrentThread (&pAudioInfo->InEnv, NULL);
	pAudioInfo->InByteArray = pAudioInfo->InEnv->NewByteArray (pAudioInfo->InTempBufSize);
	pAudioInfo->InMid = pAudioInfo->InEnv->GetStaticMethodID (pAudioInfo->Param->Class, "audioRecordRead", "([BI)I");
	pthread_mutex_unlock (&pAudioInfo->Mutex);

	while (1)
	{
		if (pAudioInfo->InExitFlag == 1)
		{
			break;
		}

		Ret = pAudioInfo->InEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->InMid, pAudioInfo->InByteArray, pAudioInfo->InTempBufSize);
		if (Ret > 0)
		{
			OldData = (jbyte *)pAudioInfo->InEnv->GetByteArrayElements (pAudioInfo->InByteArray, 0);
			memcpy (pAudioInfo->InTempBuf, (unsigned char *)OldData, Ret);
			pAudioInfo->InEnv->ReleaseByteArrayElements (pAudioInfo->InByteArray, OldData, JNI_ABORT);

#ifdef TWO_CHANNELS
			read (pAudioInfo->Handle, pAudioInfo->InTempBuf, Ret * 2);

			Src = (signed short *)pAudioInfo->InTempBuf;
			Dest = (signed short *)pAudioInfo->InTempBuf;
			Count = Ret / 4;
			for (i = 0; i < Count; i++)
			{
				Src += 2;
				*Dest++ = *Src++;
				*Dest++ = *Src++;
			}
#else
			Ret = Ret * 2;
			read (pAudioInfo->Handle, pAudioInfo->InTempBuf, Ret);
#endif

			if (pAudioInfo->InBufWrite + Ret > pAudioInfo->InBufSize)
			{
				memcpy (pAudioInfo->InBuf + pAudioInfo->InBufWrite, pAudioInfo->InTempBuf, pAudioInfo->InBufSize - pAudioInfo->InBufWrite);
				memcpy (pAudioInfo->InBuf, pAudioInfo->InTempBuf + (pAudioInfo->InBufSize - pAudioInfo->InBufWrite), Ret - (pAudioInfo->InBufSize - pAudioInfo->InBufWrite));
				pAudioInfo->InBufWrite = pAudioInfo->InBufWrite + Ret - pAudioInfo->InBufSize;
			}
			else
			{
				memcpy (pAudioInfo->InBuf + pAudioInfo->InBufWrite, pAudioInfo->InTempBuf, Ret);
				if (pAudioInfo->InBufWrite + Ret == pAudioInfo->InBufSize)
				{
					pAudioInfo->InBufWrite = 0;
				}
				else
				{
					pAudioInfo->InBufWrite += Ret;
				}
			}

			AWJavaAudioIn_Proc (pAudioInfo);
		}

		if (Ret != pAudioInfo->InTempBufSize)
		{
			usleep (AW_JAVA_AUDIO_SLEEP_TIME);
		}
	}

	pAudioInfo->Param->Jvm->DetachCurrentThread ();

	pthread_exit(0);
}
#endif

static int AWJavaAudio_Src_Open (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->InExitFlag = 0;
	return pthread_create (&pAudioInfo->InThreadHandle, NULL, AWJavaAudio_Src_Thread, pAudioInfo);
}

static int AWJavaAudio_Src_Close (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->InExitFlag = 1;
	pthread_join (pAudioInfo->InThreadHandle, NULL);
	return 0;
}

static int AWJavaAudioIn_Init (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioInInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioInInfo[i].Mutex, NULL);
	}

	Ret = ChaosAudio_Init (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
		return -1;
	}

	Ret = AWJavaAudio_Src_Open (pAudioInfo);
	if (Ret != 0)
	{
		ChaosAudio_Finish (pAudioInfo);
		for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
		return -1;
	}

	return Ret;
}

static int AWJavaAudioIn_Finish (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;

	AWJavaAudio_Src_Close (pAudioInfo);

	ChaosAudio_Finish (pAudioInfo);

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
	}

	return 0;
}

static void AWJavaAudioOut_Proc (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	AW_JAVA_AUDIO_OUT_INFO *pAudioOutInfo;;
	int i, j;
	int StreamCount;
	signed short *StreamList[AW_JAVA_AUDIO_MAX_HANDLE];
	signed short *DestBuf;
	int Write;
	int Delta;
	int SizeLeft;
	int SampleCount;
	signed long Val;

	StreamCount = 0;
	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
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
					Delta = Write + pAudioInfo->OutBufSize - pAudioOutInfo->Read;
				}
				else
				{
					Delta = Write - pAudioOutInfo->Read;
				}
				if (Delta >= pAudioInfo->OutTempBufSize)
				{
					memcpy (pAudioOutInfo->TempBuf, pAudioOutInfo->Buf + pAudioOutInfo->Read, pAudioInfo->OutTempBufSize);
					if (pAudioOutInfo->Read + pAudioInfo->OutTempBufSize == pAudioInfo->OutBufSize)
					{
						pAudioOutInfo->Read = 0;
					}
					else
					{
						pAudioOutInfo->Read += pAudioInfo->OutTempBufSize;
					}
					StreamList[StreamCount++] = (signed short *)pAudioOutInfo->TempBuf;
				}
			}
			else
			{
				SizeLeft = pAudioInfo->OutTempBufSize;
				while (SizeLeft > 0)
				{
					Delta = pAudioOutInfo->Size - pAudioOutInfo->Read;
					if (Delta > 0)
					{
						if (Delta >= SizeLeft)
						{
							memcpy (pAudioOutInfo->TempBuf + pAudioInfo->OutTempBufSize - SizeLeft, pAudioOutInfo->Buf + pAudioOutInfo->Read, SizeLeft);
							pAudioOutInfo->Read += SizeLeft;
							SizeLeft = 0;
						}
						else
						{
							memcpy (pAudioOutInfo->TempBuf + pAudioInfo->OutTempBufSize - SizeLeft, pAudioOutInfo->Buf + pAudioOutInfo->Read, Delta);
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
		memset (pAudioInfo->OutTempBuf, 0, pAudioInfo->OutTempBufSize);
	}
	else if (StreamCount == 1)
	{
		memcpy (pAudioInfo->OutTempBuf, StreamList[0], pAudioInfo->OutTempBufSize);
	}
	else
	{
		SampleCount = pAudioInfo->OutTempBufSize / 2;
		DestBuf = (signed short *)pAudioInfo->OutTempBuf;
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

#ifdef NO_JAVA_AUDIO_SINK
void *AWJavaAudio_Sink_Thread (void *Data)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Data;
	int Ret;

	while (1)
	{
		if (pAudioInfo->OutExitFlag == 1)
		{
			break;
		}

		if (pAudioInfo->OutTempBufWrite < pAudioInfo->OutTempBufSize)
		{
			Ret = write (pAudioInfo->Handle, pAudioInfo->OutTempBuf + pAudioInfo->OutTempBufWrite, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite);
			pAudioInfo->OutTempBufWrite += Ret;

			if (pAudioInfo->OutTempBufWrite != pAudioInfo->OutTempBufSize)
			{
				usleep (AW_JAVA_AUDIO_SLEEP_TIME);
			}
		}
		else
		{
			AWJavaAudioOut_Proc (pAudioInfo);
			pAudioInfo->OutTempBufWrite = 0;
		}
	}

	pthread_exit(0);
}
#else
void *AWJavaAudio_Sink_Thread (void *Data)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Data;
	int Ret;

	pthread_mutex_lock (&pAudioInfo->Mutex);
	pAudioInfo->Param->Jvm->AttachCurrentThread (&pAudioInfo->OutEnv, NULL);
	pAudioInfo->OutByteArray = pAudioInfo->OutEnv->NewByteArray (pAudioInfo->OutTempBufSize);
	pAudioInfo->OutMid = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "audioCB", "([BII)I");
	pAudioInfo->OutAudioTrackPlay = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "AudioTrackPlay", "(I)I");
	pAudioInfo->OutAUdioTrackPause = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "AudioTrackPause", "(I)I");
	pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutAudioTrackPlay, 1);
	pthread_mutex_unlock (&pAudioInfo->Mutex);

	memset (pAudioInfo->OutTempBuf2, 0, AW_JAVA_AUDIO_OUT_TEMP_BUF_SIZE);

	while (1)
	{
		if (pAudioInfo->OutExitFlag == 1)
		{
			break;
		}

		if (pAudioInfo->OutTempBufWrite < pAudioInfo->OutTempBufSize)
		{
#ifdef WRITE_TO_DEVICE
			pAudioInfo->OutEnv->SetByteArrayRegion (pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite, (jbyte *)(pAudioInfo->OutTempBuf2 + pAudioInfo->OutTempBufWrite));
			Ret = pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutMid, pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite);
			if (Ret > 0)
			{
				write (pAudioInfo->Handle, pAudioInfo->OutTempBuf + pAudioInfo->OutTempBufWrite, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite);
				pAudioInfo->OutTempBufWrite += Ret;
			}
#else
			pAudioInfo->OutEnv->SetByteArrayRegion (pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite, (jbyte *)(pAudioInfo->OutTempBuf + pAudioInfo->OutTempBufWrite));
			Ret = pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutMid, pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite);
			if (Ret > 0)
			{
				pAudioInfo->OutTempBufWrite += Ret;
			}
#endif
			if (pAudioInfo->OutTempBufWrite != pAudioInfo->OutTempBufSize)
			{
				usleep (AW_JAVA_AUDIO_SLEEP_TIME);
			}
		}
		else
		{
			AWJavaAudioOut_Proc (pAudioInfo);
			pAudioInfo->OutTempBufWrite = 0;
		}
	}

	pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutAUdioTrackPause, 1);
	pAudioInfo->Param->Jvm->DetachCurrentThread();

	pthread_exit(0);
}
#endif

static int AWJavaAudio_Sink_Open (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->OutExitFlag = 0;
	return pthread_create (&pAudioInfo->OutThreadHandle, NULL, AWJavaAudio_Sink_Thread, pAudioInfo);
}

static int AWJavaAudio_Sink_Close (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->OutExitFlag = 1;
	pthread_join (pAudioInfo->OutThreadHandle, NULL);
	return 0;
}

static int AWJavaAudioOut_Init (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioOutInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioOutInfo[i].Mutex, NULL);
	}

	Ret = AWJavaAudio_Sink_Open (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
		}
	}

	return Ret;
}

static int AWJavaAudioOut_Finish (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	Ret = AWJavaAudio_Sink_Close (pAudioInfo);
	if (Ret == 0)
	{
		for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
		}
	}

	return Ret;
}

int AWJavaAudio_Set (AUDIO_HANDLE Handle, int Cmd, int Data)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Handle;
	int Ret = 0;

	switch (Cmd)
	{
	case CP_AUDIO_CMD_SET_MIC1_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_LEFT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_MIC2_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_RIGHT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_WMIC1_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_LEFT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_WMIC2_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_RIGHT_VOL, Data);
		break;

	case CP_AUDIO_CMD_SET_ECHO_VOL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_VOL, Data);
		break;
#if 0
	case AWJAVA_AUDIO_CMD_SET_EQ_100HZ_VOL:
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

	case AWJAVA_AUDIO_CMD_SET_EQ_1KHZ_VOL:
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

	case AWJAVA_AUDIO_CMD_SET_EQ_5KHZ_VOL:
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

	case AWJAVA_AUDIO_CMD_TEST_LATENCY:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_LATENCY_START, 0);
		break;

	case AWJAVA_AUDIO_CMD_GET_LATENCY:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_LATENCY_END, 0);
		break;

	case AWJAVA_AUDIO_CMD_SET_MIC_EN:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SEL_INPUT, Data);
		break;

	case AWJAVA_AUDIO_CMD_GET_SPI_STATUS:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_SPI_STATUS, 0);
		break;

	case AWJAVA_AUDIO_CMD_SET_BBE_EN:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_BBE_EN, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_ECHO_DELAY:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_DELAY, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_BBE_LEVEL:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_BBE_LEVEL, Data);
		break;

	case AWJAVA_AUDIO_CMD_GET_CODEC_LEFT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 0);
		break;
		
	case AWJAVA_AUDIO_CMD_GET_CODEC_RIGHT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 1);
		break;
		
	case AWJAVA_AUDIO_CMD_GET_SPI_LEFT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 2);
		break;
		
	case AWJAVA_AUDIO_CMD_GET_SPI_RIGHT_VPP:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_GET_VPP, 3);
		break;

	case AWJAVA_AUDIO_CMD_SELECT_INPUT:
		Ret = ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SEL_INPUT, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_TIME_START:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_TIME_START, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_TIME_DURATION:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_TIME_DURATION, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_TIME_TEMPO:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_TIME_TEMPO, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_AGC_ENABLE:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_AGC_ENABLE, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_AGC_GAIN:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_AGC_GAIN, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_AGC_TARGET:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_AGC_TARGET, Data);
		break;

	case AWJAVA_AUDIO_CMD_SET_NOISE_AVOID:
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE, Data);
		break;
#endif
	}

	return Ret;
}

AUDIO_IN_HANDLE AWJavaAudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Handle;
	AW_JAVA_AUDIO_IN_INFO *pAudioInInfo;
	int i;

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInInfo = pAudioInfo->AudioInInfo + i;

		pthread_mutex_lock (&pAudioInInfo->Mutex);
		if (pAudioInInfo->Valid == 0)
		{
			Param->Channels = AW_JAVA_AUDIO_IN_CHANNELS;
			Param->SampleRate = pAudioInfo->InSampleRate;
			pAudioInInfo->Handle = Handle;
			pAudioInInfo->CallBack = Param->CallBack;
			pAudioInInfo->User = Param->User;
			pAudioInInfo->Size = Param->FrameCount * Param->Channels * 2;
			if (pAudioInInfo->Size > pAudioInfo->InBufSize)
			{
				pAudioInInfo->Size = pAudioInfo->InBufSize;
				Param->FrameCount = pAudioInfo->InBufSize / Param->Channels / 2;
			}
			pAudioInInfo->Read = pAudioInfo->InBufWrite;
			pAudioInInfo->Valid = 1;
			pthread_mutex_unlock (&pAudioInInfo->Mutex);
			break;
		}
		else
		{
			pthread_mutex_unlock (&pAudioInInfo->Mutex);
		}

	}

	if (i == AW_JAVA_AUDIO_MAX_HANDLE)
	{
		return NULL;
	}

	return (AUDIO_IN_HANDLE)pAudioInInfo;
}

long AWJavaAudioIn_Close (AUDIO_IN_HANDLE Handle)
{
	AW_JAVA_AUDIO_IN_INFO *pAudioInInfo = (AW_JAVA_AUDIO_IN_INFO *)Handle;

	pthread_mutex_lock (&pAudioInInfo->Mutex);
	if (pAudioInInfo->Valid == 1)
	{
		pAudioInInfo->Valid = 0;
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
		return 0;
	}
	else
	{
		pthread_mutex_unlock (&pAudioInInfo->Mutex);
		return -1;
	}
}

long AWJavaAudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	AW_JAVA_AUDIO_IN_INFO *pAudioInInfo = (AW_JAVA_AUDIO_IN_INFO *)Handle;
	AW_JAVA_AUDIO_INFO *pAudioInfo;
	int Write, Delta;

	pAudioInfo = (AW_JAVA_AUDIO_INFO *)pAudioInInfo->Handle;
	if (pAudioInInfo->Valid == 1)
	{
		Write = pAudioInfo->InBufWrite;
		if (pAudioInInfo->Read > Write)
		{
			Delta = Write + pAudioInfo->InBufSize - pAudioInInfo->Read;
		}
		else
		{
			Delta = Write - pAudioInInfo->Read;
		}
		if (Delta > Size)
		{
			Delta = Size;
		}
		if (pAudioInInfo->Read + Delta > pAudioInfo->InBufSize)
		{
			memcpy (BufAddr, pAudioInfo->InBuf + pAudioInInfo->Read, pAudioInfo->InBufSize - pAudioInInfo->Read);
			memcpy ((unsigned char *)BufAddr + (pAudioInfo->InBufSize - pAudioInInfo->Read), pAudioInfo->InBuf, Delta - (pAudioInfo->InBufSize - pAudioInInfo->Read));
			pAudioInInfo->Read = pAudioInInfo->Read + Delta - pAudioInfo->InBufSize;
		}
		else
		{
			memcpy (BufAddr, pAudioInfo->InBuf + pAudioInInfo->Read, Delta);
			if (pAudioInInfo->Read + Delta == pAudioInfo->InBufSize)
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

AUDIO_OUT_HANDLE AWJavaAudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Handle;
	AW_JAVA_AUDIO_OUT_INFO *pAudioOutInfo;
	int i;

	for (i = 0; i < AW_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioOutInfo = pAudioInfo->AudioOutInfo + i;

		pthread_mutex_lock (&pAudioOutInfo->Mutex);
		if (pAudioOutInfo->Valid == 0)
		{
			Param->Channels = pAudioInfo->OutChannels;
			Param->SampleRate = pAudioInfo->OutSampleRate;
			pAudioOutInfo->Handle = Handle;
			pAudioOutInfo->CallBack = Param->CallBack;
			pAudioOutInfo->User = Param->User;
			pAudioOutInfo->Size = Param->FrameCount * Param->Channels * 2;
			if (pAudioOutInfo->Size > pAudioInfo->OutBufSize)
			{
				pAudioOutInfo->Size = pAudioInfo->OutBufSize;
				Param->FrameCount = pAudioInfo->OutBufSize / Param->Channels / 2;
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

	if (i == AW_JAVA_AUDIO_MAX_HANDLE)
	{
		return NULL;
	}

	return (AUDIO_OUT_HANDLE)pAudioOutInfo;
}

long AWJavaAudioOut_Close (AUDIO_OUT_HANDLE Handle)
{
	AW_JAVA_AUDIO_OUT_INFO *pAudioOutInfo = (AW_JAVA_AUDIO_OUT_INFO *)Handle;

	pthread_mutex_lock (&pAudioOutInfo->Mutex);
	if (pAudioOutInfo->Valid == 1)
	{
		pAudioOutInfo->Valid = 0;
		pthread_mutex_unlock (&pAudioOutInfo->Mutex);
		return 0;
	}
	else
	{
		pthread_mutex_unlock (&pAudioOutInfo->Mutex);
		return -1;
	}
}

long AWJavaAudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	AW_JAVA_AUDIO_OUT_INFO *pAudioOutInfo = (AW_JAVA_AUDIO_OUT_INFO *)Handle;
	AW_JAVA_AUDIO_INFO *pAudioInfo;
	int Free, Read;

	pAudioInfo = (AW_JAVA_AUDIO_INFO *)pAudioOutInfo->Handle;
	if (pAudioOutInfo->Valid == 1)
	{
		Read = pAudioOutInfo->Read;
		if (Read > pAudioOutInfo->Write)
		{
			Free = Read - pAudioOutInfo->Write;
		}
		else
		{
			Free = pAudioInfo->OutBufSize - (pAudioOutInfo->Write - Read);
		}
		if (Free > Size)
		{
			Free = Size;
		}
		if (pAudioOutInfo->Write + Free > pAudioInfo->OutBufSize)
		{
			memcpy (pAudioOutInfo->Buf + pAudioOutInfo->Write, BufAddr, pAudioInfo->OutBufSize - pAudioOutInfo->Write);
			memcpy (pAudioOutInfo->Buf, (unsigned char *)BufAddr + (pAudioInfo->OutBufSize - pAudioOutInfo->Write), Free - (pAudioInfo->OutBufSize - pAudioOutInfo->Write));
			pAudioOutInfo->Write = pAudioOutInfo->Write + Free - pAudioInfo->OutBufSize;
		}
		else
		{
			memcpy (pAudioOutInfo->Buf + pAudioOutInfo->Write, BufAddr, Free);
			if (pAudioOutInfo->Write + Free == pAudioInfo->OutBufSize)
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
static int AWJavaAudioUart_Init (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
#if 0
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

	memset(&newtio, 0, sizeof (newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	// 8Bit
	newtio.c_cflag |= CS8;

	// ��У��λ
	newtio.c_cflag &= ~PARENB;

	// A20ƽ̨B57600ʵ�ʲ�����33000
	cfsetispeed(&newtio, B57600);
	cfsetospeed(&newtio, B57600);

	// 2λֹͣλ
	newtio.c_cflag |= CSTOPB;

	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush (pAudioInfo->UartHandle, TCIFLUSH);

	if ((tcsetattr (pAudioInfo->UartHandle, TCSANOW, &newtio)) != 0)
	{
		close (pAudioInfo->UartHandle);
		return -1;
	}
#endif
	return 0;
}

static int AWJavaAudioUart_Finish (AW_JAVA_AUDIO_INFO *pAudioInfo)
{
#if 0
	close (pAudioInfo->UartHandle);
#endif
	return 0;
}

AUDIO_HANDLE AudioHandle = NULL;

AUDIO_HANDLE AWJavaAudio_Init (ANDROID_JAVA_AUDIO_PARAM *Param)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo;
	int Ret;

	log_for_pro("enter AWJavaAudio_Init ");

	pAudioInfo = (AW_JAVA_AUDIO_INFO *)malloc (sizeof (AW_JAVA_AUDIO_INFO));
	if (pAudioInfo == NULL)
	{
		return NULL;
	}
	
#ifdef SUPPORT_EXT_MIDI
	Ret = AWJavaAudioUart_Init (pAudioInfo);
	if (Ret != 0)
	{
		free (pAudioInfo);
		return NULL;
	}
#endif

	pAudioInfo->Param = Param;
	pthread_mutex_init (&pAudioInfo->Mutex, NULL);

	pAudioInfo->InChannels = pAudioInfo->Param->InChannels;
	pAudioInfo->InSampleRate = pAudioInfo->Param->InSampleRate;// * 100;
	pAudioInfo->InExitFlag = 0;
	pAudioInfo->InEnv = NULL;
	pAudioInfo->InBufSize = AW_JAVA_AUDIO_IN_BUF_TIME * pAudioInfo->InSampleRate * AW_JAVA_AUDIO_IN_CHANNELS * 2 / 1000;
	pAudioInfo->InBufWrite = 0;
	pAudioInfo->InTempBufSize = AW_JAVA_AUDIO_IN_TEMP_BUF_TIME * pAudioInfo->InSampleRate * pAudioInfo->InChannels * 2 / 1000;

	pAudioInfo->OutChannels = pAudioInfo->Param->OutChannels;
	pAudioInfo->OutSampleRate = pAudioInfo->Param->OutSampleRate;// * 100;
	pAudioInfo->OutExitFlag = 0;
	pAudioInfo->OutEnv = NULL;
	pAudioInfo->OutBufSize = AW_JAVA_AUDIO_OUT_BUF_TIME * pAudioInfo->OutSampleRate * pAudioInfo->OutChannels * 2 / 1000;
	pAudioInfo->OutTempBufSize = AW_JAVA_AUDIO_OUT_TEMP_BUF_TIME * pAudioInfo->OutSampleRate * pAudioInfo->OutChannels * 2 / 1000;
	pAudioInfo->OutTempBufWrite = pAudioInfo->OutTempBufSize;

	Ret = AWJavaAudioIn_Init (pAudioInfo);
	if (Ret != 0)
	{
		ChaosAudio_Finish (pAudioInfo);
#ifdef SUPPORT_EXT_MIDI
		AWJavaAudioUart_Finish (pAudioInfo);
#endif
		free (pAudioInfo);
		return NULL;
	}

	Ret = AWJavaAudioOut_Init (pAudioInfo);
	if (Ret != 0)
	{
		AWJavaAudioIn_Finish (pAudioInfo);
		ChaosAudio_Finish (pAudioInfo);
#ifdef SUPPORT_EXT_MIDI
		AWJavaAudioUart_Finish (pAudioInfo);
#endif
		free (pAudioInfo);
		return NULL;
	}


	AudioHandle = pAudioInfo;

	RF_OpenWirelessMic(pAudioInfo->Handle);

	{
		char path[32] = {0};
		AUTH_HARDWARE_PARAM Param;
		sprintf(path, "%s%s", "/data/res/", "wavetable.bin");
		log_for_pro("wavetable: %s \n", path);
		
		if (access(path, 0) == 0)
			Param.WaveTablePath = path;
		else
			Param.WaveTablePath = NULL;
		AuthHardware_Init (&Param);
	}

	log_for_pro("success AWJavaAudio_Init ");

	return (AUDIO_HANDLE)pAudioInfo;
}

int AWJavaAudio_Finish (AUDIO_HANDLE Handle)
{
	AW_JAVA_AUDIO_INFO *pAudioInfo = (AW_JAVA_AUDIO_INFO *)Handle;

	log_for_pro("enter AWJavaAudio_Finish ");

	AuthHardware_Finish();

	RF_CloseWirelessMic(pAudioInfo->Handle);

	AudioHandle = NULL;

	AWJavaAudioOut_Finish (pAudioInfo);

	AWJavaAudioIn_Finish (pAudioInfo);

	ChaosAudio_Finish (pAudioInfo);

#ifdef SUPPORT_EXT_MIDI
	AWJavaAudioUart_Finish (pAudioInfo);
#endif

	free (pAudioInfo);

	//Set_RenderReturn(0x270000);	//for javaaudio stop
	log_for_pro("success AWJavaAudio_Finish ");

	return 0;
}

