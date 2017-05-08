#include <malloc.h>
#include <unistd.h>
#include "AACEncJava.h"

#define AAC_ENC_JAVA_MAX_BUF_SIZE		16384


//#include <android/log.h>
//#define aacenc_printf(...) __android_log_print(ANDROID_LOG_INFO, "zhaolj", __VA_ARGS__)
#define aacenc_printf(...)

typedef struct tagAAC_ENC_JAVA_INFO
{
	AAC_ENC_JAVA_PARAM	Param;
	unsigned long		SampleRate;
	unsigned long		Channels;
	
	jmethodID					midInput;
	jmethodID					midOutput;
	
}AAC_ENC_JAVA_INFO;

int AACEncJava_Open (AAC_ENC_JAVA_HANDLE Handle, unsigned long SampleRate, unsigned long Channels, unsigned long BitRate)
{
	AAC_ENC_JAVA_INFO *pInfo = (AAC_ENC_JAVA_INFO *)Handle;
	JNIEnv* Env;
	jmethodID Prepare;

	pInfo->SampleRate = SampleRate;
	pInfo->Channels = Channels;
	
	pInfo->Param.Jvm->AttachCurrentThread (&Env, NULL);

	aacenc_printf("AACEncJava_Open\n");
	Prepare = Env->GetStaticMethodID (pInfo->Param.Class, "AudioEncode_Prepare", "(Ljava/lang/String;IIII)V");
	pInfo->midInput = Env->GetStaticMethodID (pInfo->Param.Class, "GetAudioInputBuffer", "()Ljava/nio/ByteBuffer;");
	pInfo->midOutput = Env->GetStaticMethodID (pInfo->Param.Class, "OfferAudioEncoder", "(II)Ljava/nio/ByteBuffer;");
	aacenc_printf("Prepare 1 = %p, %d, BitRate = %d, SampleRate = %d, Channels = %d\n",Prepare,Prepare, BitRate, SampleRate, Channels);

	jstring strFilePath = Env->NewStringUTF ((char *)"");///mnt/sda/sda1/Karaoke/11.aac
	Env->CallStaticVoidMethod (pInfo->Param.Class, Prepare, strFilePath, SampleRate, Channels, BitRate, AAC_ENC_JAVA_MAX_BUF_SIZE);
	
	aacenc_printf("Prepare 2 \n");
	pInfo->Param.Jvm->DetachCurrentThread ();
	
	return 0;
}

void AACEncJava_Close (AAC_ENC_JAVA_HANDLE Handle)
{
	AAC_ENC_JAVA_INFO *pInfo = (AAC_ENC_JAVA_INFO *)Handle;
	JNIEnv* Env;
	jmethodID Stop;
	
	aacenc_printf("AACEncJava_Close \n");
	
	pInfo->Param.Jvm->AttachCurrentThread (&Env, NULL);

	Stop = Env->GetStaticMethodID (pInfo->Param.Class, "AudioEncoder_Stop", "()V");

	Env->CallStaticVoidMethod (pInfo->Param.Class, Stop);
	
	pInfo->Param.Jvm->DetachCurrentThread ();

	aacenc_printf("AACEncJava_Close end\n");
	
	return;
}

void AACEncJava_Proc (AAC_ENC_JAVA_HANDLE Handle, void *SrcData, unsigned long *SrcSize, void *DestData, unsigned long *DestSize)
{
	AAC_ENC_JAVA_INFO *pInfo = (AAC_ENC_JAVA_INFO *)Handle;
	JNIEnv* Env;
	unsigned long mSize, mTimes;
	
	pInfo->Param.Jvm->AttachCurrentThread (&Env, NULL);

	aacenc_printf("in 1\n");
	// ��������
	jobject j_buffer (Env->CallStaticObjectMethod (pInfo->Param.Class, pInfo->midInput));
	if(j_buffer != NULL)
	{
		unsigned char *data = static_cast<unsigned char*>(Env->GetDirectBufferAddress (j_buffer));
		if(data != NULL)
		{
			size_t capacity = (size_t)Env->GetDirectBufferCapacity (j_buffer);
			if (*SrcSize > capacity)
			{
				*SrcSize = capacity;
			}
			aacenc_printf("in 2t\n");
			memcpy (data, SrcData, *SrcSize);
		}
		else
		{
			*SrcSize = 0;
		}
		Env->DeleteLocalRef (j_buffer);
	}
	else
	{
		*SrcSize = 0;
	}

	aacenc_printf("out 1\n");
	
	// �������
	mSize = *SrcSize;
	mTimes = (unsigned long long)mSize * 1000000 / pInfo->SampleRate / pInfo->Channels / 2;
	jobject j_bufferOut (Env->CallStaticObjectMethod (pInfo->Param.Class, pInfo->midOutput, *SrcSize, mTimes));
	if(j_bufferOut != NULL)
	{
		unsigned char *dataOut = static_cast<unsigned char*>(Env->GetDirectBufferAddress (j_bufferOut));
		if(dataOut != NULL)
		{
			size_t capacityOut = (size_t)Env->GetDirectBufferCapacity (j_bufferOut);
			memcpy (DestData, dataOut, capacityOut);
			*DestSize = capacityOut;
		}
		else
		{
			*DestSize = 0;
		}
		Env->DeleteLocalRef (j_bufferOut);
	}
	else
	{
		*DestSize = 0;
	}

	aacenc_printf("out 2\n");
	pInfo->Param.Jvm->DetachCurrentThread ();
	
	aacenc_printf("out 3\n");
	return;

}

AAC_ENC_JAVA_HANDLE AACEncJava_Init (AAC_ENC_JAVA_PARAM *Param)
{
	AAC_ENC_JAVA_INFO *pInfo;

	pInfo = (AAC_ENC_JAVA_INFO *)malloc (sizeof (AAC_ENC_JAVA_INFO));
	if (pInfo == NULL)
	{
		return NULL;
	}

	memcpy (&(pInfo->Param), Param, sizeof (AAC_ENC_JAVA_PARAM));

	return pInfo;
}

void AACEncJava_Deinit (AAC_ENC_JAVA_HANDLE Handle)
{
	free (Handle);

	return;
}

