#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>

#include "rfmod.h"
#include "AndroidJavaAudio.h"

#include <android/log.h>
#define  LOG_TAG    "javaaudio"
#define  log_for_pro(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define A20_AUDIO_DEV								"/dev/ChaosAudio"

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

#define CHAOS_AUDIO_CMD_GET_TMPBUF					_IOR (CHAOS_AUDIO_MAGIC, 78, int)
#define CHAOS_AUDIO_CMD_RST_TMPBUF					_IOR (CHAOS_AUDIO_MAGIC, 79, int)

#define CHAOS_AUDIO_CMD_WIRELESS_OPEN_DEVICE		_IOR (CHAOS_AUDIO_MAGIC, 90, int)
#define CHAOS_AUDIO_CMD_WIRELESS_CLOSE_DEVICE		_IOR (CHAOS_AUDIO_MAGIC, 91, int)


#define CHAOS_AUDIO_CMD_WIRELESS_START_PAIR			_IOR (CHAOS_AUDIO_MAGIC, 94, int)
#define CHAOS_AUDIO_CMD_WIRELESS_GET_PAIR_STATE		_IOR (CHAOS_AUDIO_MAGIC, 95, int)
#define CHAOS_AUDIO_CMD_WIRELESS_STOP_PAIR			_IOR (CHAOS_AUDIO_MAGIC, 96, int)
#define CHAOS_AUDIO_CMD_WIRELESS_SET_PAIR_CODE		_IOR (CHAOS_AUDIO_MAGIC, 97, int)
#define CHAOS_AUDIO_CMD_WIRELESS_GET_PAIR_CODE		_IOR (CHAOS_AUDIO_MAGIC, 98, int)

#define CHAOS_AUDIO_CMD_WIRELESS_SET_WORKMODE		_IOR (CHAOS_AUDIO_MAGIC, 101, int)
#define CHAOS_AUDIO_CMD_WIRELESS_GET_WORKMODE		_IOR (CHAOS_AUDIO_MAGIC, 102, int)
#define CHAOS_AUDIO_CMD_WIRELESS_SET_SAMPLERATE		_IOR (CHAOS_AUDIO_MAGIC, 103, int)

#define CHAOS_AUDIO_CMD_WIRELESS_TEST_MODE_ENABLE	_IOR (CHAOS_AUDIO_MAGIC, 106, int)
#define CHAOS_AUDIO_CMD_WIRELESS_GET_RSSI			_IOR (CHAOS_AUDIO_MAGIC, 107, int)





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


#define ANDROID_JAVA_AUDIO_DEFAULT_INPUT_VOLUME				256
#define ANDROID_JAVA_AUDIO_MAX_HANDLE						4
#define ANDROID_JAVA_AUDIO_SLEEP_TIME						10000	//10MS
#define ANDROID_JAVA_AUDIO_JAVA_BUF_TIME					100
#define ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE					19200	//100MS
#define ANDROID_JAVA_AUDIO_IN_BUF_TIME						400
#define ANDROID_JAVA_AUDIO_IN_BUF_SIZE						76800	//400MS
#define ANDROID_JAVA_AUDIO_OUT_BUF_TIME						200
#define ANDROID_JAVA_AUDIO_OUT_BUF_SIZE						38400	//200MS

typedef struct tagANDROID_JAVA_AUDIO_IN_INFO
{
	AUDIO_HANDLE		Handle;
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	int					Read;
}ANDROID_JAVA_AUDIO_IN_INFO;

typedef struct tagANDROID_JAVA_AUDIO_SINK_INFO
{
	AUDIO_HANDLE		Handle;
	int					Valid;
	pthread_mutex_t		Mutex;
	FuncAudioCallBack	CallBack;
	void				*User;
	int					Size;
	unsigned char		Buf[ANDROID_JAVA_AUDIO_OUT_BUF_SIZE];
	unsigned char		TempBuf[ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE];
	int					Read;
	int					Write;
}ANDROID_JAVA_AUDIO_OUT_INFO;

typedef struct tagANDROID_JAVA_AUDIO_INFO
{
	int								Handle;

	ANDROID_JAVA_AUDIO_PARAM		*Param;
	pthread_mutex_t					Mutex;

	unsigned long					InVol;

	unsigned long					InChannels;
	unsigned long					InSampleRate;

	unsigned long					InExitFlag;
	pthread_t						InThreadHandle;
	JNIEnv							*InEnv;
	jbyteArray						InByteArray;
	jmethodID						InMid;

	unsigned char					InBuf[ANDROID_JAVA_AUDIO_IN_BUF_SIZE];
	unsigned long					InBufSize;
	unsigned long					InBufWrite;
	unsigned char					InTempBuf[ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE];
	unsigned long					InTempBufSize;

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
	unsigned char					OutTempBuf[ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE];
	unsigned long					OutTempBufSize;
	unsigned long					OutTempBufWrite;

	ANDROID_JAVA_AUDIO_IN_INFO		AudioInInfo[ANDROID_JAVA_AUDIO_MAX_HANDLE];
	ANDROID_JAVA_AUDIO_OUT_INFO		AudioOutInfo[ANDROID_JAVA_AUDIO_MAX_HANDLE];
}ANDROID_JAVA_AUDIO_INFO;

ANDROID_JAVA_AUDIO_PARAM mAudioParam;

extern "C" void chaosaudio_chipdecrypt(unsigned char *SrcData, unsigned char *DestData);
extern int Set_RenderReturn(unsigned long renderval);

static int ChaosAudio_Init (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
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
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_SELECT, ADC_LINEIN);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ADC_GAIN, 3);
		ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_NOISE_AVOID_ENABLE, 0);

		RF_OpenWirelessMic(pAudioInfo->Handle);

		return 0;
	}

	return -1;
}

static int ChaosAudio_Finish (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
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

static void AndroidJavaAudioIn_Gain (signed short *Sample, int SampleCount, int Vol)
{
	int i;
	signed long Val;

	if (Vol == ANDROID_JAVA_AUDIO_DEFAULT_INPUT_VOLUME)
	{
		return;
	}

	for (i = 0; i < SampleCount; i++)
	{
		Val = (*Sample) * Vol / 256;
		if (Val > 32767)
		{
			Val = 32767;
		}
		else if (Val < -32768)
		{
			Val = -32768;
		}
		*Sample++ = (signed short)Val;
	}

	return;
}

static void AndroidJavaAudioIn_Proc (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	ANDROID_JAVA_AUDIO_IN_INFO *pAudioInInfo;
	int i;
	int Delta;

	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
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

static void *AndroidJavaAudio_Src_Thread (void *Data)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Data;
	jbyte *OldData;
	int Ret;

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

			AndroidJavaAudioIn_Gain ((signed short *)pAudioInfo->InTempBuf, Ret / 2, pAudioInfo->InVol);

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

			AndroidJavaAudioIn_Proc (pAudioInfo);
		}

		if (Ret != pAudioInfo->InTempBufSize)
		{
			usleep (ANDROID_JAVA_AUDIO_SLEEP_TIME);
		}
	}

	pAudioInfo->Param->Jvm->DetachCurrentThread ();

	pthread_exit(0);
}

static int AndroidJavaAudio_Src_Open (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->InExitFlag = 0;
	return pthread_create (&pAudioInfo->InThreadHandle, NULL, AndroidJavaAudio_Src_Thread, pAudioInfo);
}

static int AndroidJavaAudio_Src_Close (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->InExitFlag = 1;
	pthread_join (pAudioInfo->InThreadHandle, NULL);
	return 0;
}

static int AndroidJavaAudioIn_Init (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioInInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioInInfo[i].Mutex, NULL);
	}

	Ret = AndroidJavaAudio_Src_Open (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
	}

	return Ret;
}

static int AndroidJavaAudioIn_Finish (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	Ret = AndroidJavaAudio_Src_Close (pAudioInfo);
	if (Ret == 0)
	{
		for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioInInfo[i].Mutex);
		}
	}

	return Ret;
}

static void AndroidJavaAudioOut_Proc (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	ANDROID_JAVA_AUDIO_OUT_INFO *pAudioOutInfo;;
	int i, j;
	int StreamCount;
	signed short *StreamList[ANDROID_JAVA_AUDIO_MAX_HANDLE];
	signed short *DestBuf;
	int Write;
	int Delta;
	int SizeLeft;
	int SampleCount;
	signed long Val;

	StreamCount = 0;
	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
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

void *AndroidJavaAudio_Sink_Thread (void *Data)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Data;
	int Ret;

	pthread_mutex_lock (&pAudioInfo->Mutex);
	pAudioInfo->Param->Jvm->AttachCurrentThread (&pAudioInfo->OutEnv, NULL);
	pAudioInfo->OutByteArray = pAudioInfo->OutEnv->NewByteArray (pAudioInfo->OutTempBufSize);
	pAudioInfo->OutMid = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "audioCB", "([BII)I");
	pAudioInfo->OutAudioTrackPlay = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "AudioTrackPlay", "(I)I");
	pAudioInfo->OutAUdioTrackPause = pAudioInfo->OutEnv->GetStaticMethodID (pAudioInfo->Param->Class, "AudioTrackPause", "(I)I");
	pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutAudioTrackPlay, 1);
	pthread_mutex_unlock (&pAudioInfo->Mutex);

	while (1)
	{
		if (pAudioInfo->OutExitFlag == 1)
		{
			break;
		}

		if (pAudioInfo->OutTempBufWrite < pAudioInfo->OutTempBufSize)
		{
			pAudioInfo->OutEnv->SetByteArrayRegion (pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite, (jbyte *)(pAudioInfo->OutTempBuf + pAudioInfo->OutTempBufWrite));
			Ret = pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutMid, pAudioInfo->OutByteArray, 0, pAudioInfo->OutTempBufSize - pAudioInfo->OutTempBufWrite);
			if (Ret > 0)
			{
				pAudioInfo->OutTempBufWrite += Ret;
			}
			if (pAudioInfo->OutTempBufWrite != pAudioInfo->OutTempBufSize)
			{
				usleep (ANDROID_JAVA_AUDIO_SLEEP_TIME);
			}
		}
		else
		{
			AndroidJavaAudioOut_Proc (pAudioInfo);
			pAudioInfo->OutTempBufWrite = 0;
		}
	}

	pAudioInfo->OutEnv->CallStaticIntMethod (pAudioInfo->Param->Class, pAudioInfo->OutAUdioTrackPause, 1);
	pAudioInfo->Param->Jvm->DetachCurrentThread();

	pthread_exit(0);
}

static int AndroidJavaAudio_Sink_Open (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->OutExitFlag = 0;
	return pthread_create (&pAudioInfo->OutThreadHandle, NULL, AndroidJavaAudio_Sink_Thread, pAudioInfo);
}

static int AndroidJavaAudio_Sink_Close (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	pAudioInfo->OutExitFlag = 1;
	pthread_join (pAudioInfo->OutThreadHandle, NULL);
	return 0;
}

static int AndroidJavaAudioOut_Init (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInfo->AudioOutInfo[i].Valid = 0;
		pthread_mutex_init (&pAudioInfo->AudioOutInfo[i].Mutex, NULL);
	}

	Ret =  AndroidJavaAudio_Sink_Open (pAudioInfo);
	if (Ret != 0)
	{
		for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
		}
	}

	return Ret;
}

static int AndroidJavaAudioOut_Finish (ANDROID_JAVA_AUDIO_INFO *pAudioInfo)
{
	int i;
	int Ret;

	Ret = AndroidJavaAudio_Sink_Close (pAudioInfo);
	if (Ret == 0)
	{
		for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
		{
			pthread_mutex_destroy (&pAudioInfo->AudioOutInfo[i].Mutex);
		}
	}

	return Ret;
}

int AndroidJavaAudio_Set (AUDIO_HANDLE Handle, int Cmd, int Data)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Handle;

	log_for_pro ("A20Audio_Set [%d, %d]!\n", Cmd, Data);
	switch (Cmd)
	{
		case CP_AUDIO_CMD_SET_MIC1_VOL:
			//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_LEFT_VOL, Data);
			break;
		
		case CP_AUDIO_CMD_SET_MIC2_VOL:
			//ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_CODEC_RIGHT_VOL, Data);
			break;
		
		case CP_AUDIO_CMD_SET_WMIC1_VOL:
			ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_LEFT_VOL, Data);
			break;
		
		case CP_AUDIO_CMD_SET_WMIC2_VOL:
			ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_SPI_RIGHT_VOL, Data);
			break;
		
		case CP_AUDIO_CMD_SET_ECHO_VOL:
			ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_VOL, Data);
			ioctl (pAudioInfo->Handle, CHAOS_AUDIO_CMD_SET_ECHO_DELAY, 10);
			break;
	}

	return 0;
}

AUDIO_IN_HANDLE AndroidJavaAudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Handle;
	ANDROID_JAVA_AUDIO_IN_INFO *pAudioInInfo;
	int i;

	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
	{
		pAudioInInfo = pAudioInfo->AudioInInfo + i;

		pthread_mutex_lock (&pAudioInInfo->Mutex);
		if (pAudioInInfo->Valid == 0)
		{
			Param->Channels = pAudioInfo->InChannels;
			Param->SampleRate = pAudioInfo->InSampleRate;
			pAudioInInfo->Handle = Handle;
			pAudioInInfo->CallBack = Param->CallBack;
			pAudioInInfo->User = Param->User;
			pAudioInInfo->Size = Param->FrameCount * Param->Channels * 2;
			if (pAudioInInfo->Size > ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE)
			{
				pAudioInInfo->Size = ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE;
				Param->FrameCount = ANDROID_JAVA_AUDIO_JAVA_BUF_SIZE / Param->Channels / 2;
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

	if (i == ANDROID_JAVA_AUDIO_MAX_HANDLE)
	{
		return NULL;
	}

	return (AUDIO_IN_HANDLE)pAudioInInfo;
}

long AndroidJavaAudioIn_Close (AUDIO_IN_HANDLE Handle)
{
	ANDROID_JAVA_AUDIO_IN_INFO *pAudioInInfo = (ANDROID_JAVA_AUDIO_IN_INFO *)Handle;

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

long AndroidJavaAudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	ANDROID_JAVA_AUDIO_IN_INFO *pAudioInInfo = (ANDROID_JAVA_AUDIO_IN_INFO *)Handle;
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo;
	int Write, Delta;

	pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)pAudioInInfo->Handle;
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

AUDIO_OUT_HANDLE AndroidJavaAudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Handle;
	ANDROID_JAVA_AUDIO_OUT_INFO *pAudioOutInfo;
	int i;

	for (i = 0; i < ANDROID_JAVA_AUDIO_MAX_HANDLE; i++)
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

	if (i == ANDROID_JAVA_AUDIO_MAX_HANDLE)
	{
		return NULL;
	}

	return (AUDIO_OUT_HANDLE)pAudioOutInfo;
}

long AndroidJavaAudioOut_Close (AUDIO_OUT_HANDLE Handle)
{
	ANDROID_JAVA_AUDIO_OUT_INFO *pAudioOutInfo = (ANDROID_JAVA_AUDIO_OUT_INFO *)Handle;

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

long AndroidJavaAudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	ANDROID_JAVA_AUDIO_OUT_INFO *pAudioOutInfo = (ANDROID_JAVA_AUDIO_OUT_INFO *)Handle;
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo;
	int Free, Read;

	pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)pAudioOutInfo->Handle;
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

AUDIO_HANDLE AndroidJavaAudio_Init (int samplerate)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo;
	ANDROID_JAVA_AUDIO_PARAM *Param = &mAudioParam;
	int Ret;

	pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)malloc (sizeof (ANDROID_JAVA_AUDIO_INFO));
	if (pAudioInfo == NULL)
	{
		return NULL;
	}

	pAudioInfo->Param = Param;
	pthread_mutex_init (&pAudioInfo->Mutex, NULL);

	pAudioInfo->InVol = ANDROID_JAVA_AUDIO_DEFAULT_INPUT_VOLUME;

	pAudioInfo->InChannels = pAudioInfo->Param->InChannels;
	pAudioInfo->InSampleRate = pAudioInfo->Param->InSampleRate * 100;
	pAudioInfo->InExitFlag = 0;
	pAudioInfo->InEnv = NULL;
	pAudioInfo->InBufSize = ANDROID_JAVA_AUDIO_IN_BUF_TIME * pAudioInfo->InSampleRate * pAudioInfo->InChannels * 2 / 1000;
	pAudioInfo->InBufWrite = 0;
	pAudioInfo->InTempBufSize = ANDROID_JAVA_AUDIO_JAVA_BUF_TIME * pAudioInfo->InSampleRate * pAudioInfo->InChannels * 2 / 1000;

	pAudioInfo->OutChannels = pAudioInfo->Param->OutChannels;
	pAudioInfo->OutSampleRate = pAudioInfo->Param->OutSampleRate * 100;
	pAudioInfo->OutExitFlag = 0;
	pAudioInfo->OutEnv = NULL;
	pAudioInfo->OutBufSize = ANDROID_JAVA_AUDIO_OUT_BUF_TIME * pAudioInfo->OutSampleRate * pAudioInfo->OutChannels * 2 / 1000;
	pAudioInfo->OutTempBufSize = ANDROID_JAVA_AUDIO_JAVA_BUF_TIME * pAudioInfo->OutSampleRate * pAudioInfo->OutChannels * 2 / 1000;
	pAudioInfo->OutTempBufWrite = pAudioInfo->OutTempBufSize;

	Ret = ChaosAudio_Init (pAudioInfo);
	if (Ret != 0)
	{
		return NULL;
	}

	Ret = AndroidJavaAudioIn_Init (pAudioInfo);
	if (Ret != 0)
	{
		pthread_mutex_destroy (&pAudioInfo->Mutex);
		free (pAudioInfo);
		return NULL;
	}

	Ret = AndroidJavaAudioOut_Init (pAudioInfo);
	if (Ret != 0)
	{
		AndroidJavaAudioIn_Finish (pAudioInfo);
		pthread_mutex_destroy (&pAudioInfo->Mutex);
		free (pAudioInfo);
		return NULL;
	}

	return (AUDIO_HANDLE)pAudioInfo;
}

int AndroidJavaAudio_Finish (AUDIO_HANDLE Handle)
{
	ANDROID_JAVA_AUDIO_INFO *pAudioInfo = (ANDROID_JAVA_AUDIO_INFO *)Handle;

	AndroidJavaAudioOut_Finish (pAudioInfo);

	AndroidJavaAudioIn_Finish (pAudioInfo);

	ChaosAudio_Finish(pAudioInfo);

	pthread_mutex_destroy (&pAudioInfo->Mutex);

	free (pAudioInfo);

	Set_RenderReturn(0x270000);	//for javaaudio stop

	return 0;
}

