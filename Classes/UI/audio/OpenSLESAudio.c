#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "OpenSLESAudio.h"

#include <android/log.h>
#define  LOG_TAG    "AUDIOP"
#define  M3D_DebugPrint(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#define OPENSLES_AUDIO_PROC_SIZE			6400
#define OPENSLES_AUDIO_BUF_SIZE			51200

typedef struct tagOPENSLES_AUDIO_SRC_INFO
{
	SLObjectItf						recorderObject;
	SLRecordItf						recorderRecord;
	SLAndroidSimpleBufferQueueItf	recorderBufferQueue;

	unsigned char					*recorderBuffer;
	unsigned long					recorderBufferSize;

	unsigned long					Channels;
	unsigned long					SampleRate;

	FuncAudioCallBack				CallBack;
	void							*User;

	unsigned char					*BufAddr;
	unsigned long					Read;
	unsigned long					Write;
}OPENSLES_AUDIO_SRC_INFO;

typedef struct tagOPENSLES_AUDIO_SINK_INFO
{
	SLObjectItf						bqPlayerObject;
	SLPlayItf						bqPlayerPlay;
	SLAndroidSimpleBufferQueueItf	bqPlayerBufferQueue;
	SLEffectSendItf					bqPlayerEffectSend;
	SLMuteSoloItf					bqPlayerMuteSolo;
	SLVolumeItf						bqPlayerVolume;
	
	unsigned char					*playerBuffer;
	unsigned long					playerBufferSize;

	unsigned long					Channels;
	unsigned long					SampleRate;

	FuncAudioCallBack				CallBack;
	void							*User;

	unsigned char					*BufAddr;
	unsigned long					Read;
	unsigned long					Write;
}OPENSLES_AUDIO_SINK_INFO;

typedef struct tagOPENSLES_AUDIO_INFO
{
	// engine interfaces
	SLObjectItf						engineObject;
	SLEngineItf						engineEngine;
	
	// output mix interfaces
	SLObjectItf						outputMixObject;
	SLEnvironmentalReverbItf		outputMixEnvironmentalReverb;
}OPENSLES_AUDIO_INFO;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

void OpenSLESAudioSrc_Callback (SLAndroidSimpleBufferQueueItf bq, void *context)
{
	OPENSLES_AUDIO_SRC_INFO *pAudioSrcInfo = (OPENSLES_AUDIO_SRC_INFO *)context;
	SLresult result;

	if (NULL == pAudioSrcInfo)
	{
		M3D_DebugPrint ("OpenSLES_Src_Callback context Error!\n");
		return;
	}

	if (bq != pAudioSrcInfo->recorderBufferQueue)
	{
		M3D_DebugPrint ("OpenSLES_Src_Callback bq Error!\n");
		return;
	}

	if (pAudioSrcInfo->CallBack == NULL)
	{
		memcpy (pAudioSrcInfo->BufAddr + pAudioSrcInfo->Write, pAudioSrcInfo->recorderBuffer, pAudioSrcInfo->recorderBufferSize);
		if (pAudioSrcInfo->Write + pAudioSrcInfo->recorderBufferSize == OPENSLES_AUDIO_BUF_SIZE)
		{
			pAudioSrcInfo->Write = 0;
		}
		else
		{
			pAudioSrcInfo->Write += pAudioSrcInfo->recorderBufferSize;
		}
	}
	else
	{
		pAudioSrcInfo->CallBack (pAudioSrcInfo->User, pAudioSrcInfo->recorderBuffer);
	}

    result = (*pAudioSrcInfo->recorderBufferQueue)->Enqueue (pAudioSrcInfo->recorderBufferQueue, pAudioSrcInfo->recorderBuffer,
            pAudioSrcInfo->recorderBufferSize);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Callback Enqueue Error!\n");
		return;
	}

	return;
}

static long OpenSLESAudioSrc_Open (OPENSLES_AUDIO_INFO *pAudioInfo, OPENSLES_AUDIO_SRC_INFO *pAudioSrcInfo)
{
	const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
	const SLboolean req[1] = {SL_BOOLEAN_TRUE};
	SLresult result;

	// configure audio source
	SLDataLocator_IODevice loc_dev = {SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
			SL_DEFAULTDEVICEID_AUDIOINPUT, NULL};
	SLDataSource audioSrc = {&loc_dev, NULL};

	// configure audio sink
	SLDataLocator_AndroidSimpleBufferQueue loc_bq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, pAudioSrcInfo->Channels, pAudioSrcInfo->SampleRate,
		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};
	SLDataSink audioSnk = {&loc_bq, &format_pcm};

	// create audio recorder
	// (requires the RECORD_AUDIO permission)
	result = (*pAudioInfo->engineEngine)->CreateAudioRecorder (pAudioInfo->engineEngine, &pAudioSrcInfo->recorderObject, &audioSrc,
			&audioSnk, 1, id, req);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open CreateAudioRecorder Error!\n");
		return -1;
	}

	// realize the audio recorder
	result = (*pAudioSrcInfo->recorderObject)->Realize (pAudioSrcInfo->recorderObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open Realize Error!\n");
		return -1;
	}

	// get the record interface
	result = (*pAudioSrcInfo->recorderObject)->GetInterface (pAudioSrcInfo->recorderObject, SL_IID_RECORD, &pAudioSrcInfo->recorderRecord);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open GetInterface Error!\n");
		return -1;
	}

	// get the buffer queue interface
	result = (*pAudioSrcInfo->recorderObject)->GetInterface (pAudioSrcInfo->recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
			&pAudioSrcInfo->recorderBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open GetInterface Error!\n");
		return -1;
	}

	// register callback on the buffer queue
	result = (*pAudioSrcInfo->recorderBufferQueue)->RegisterCallback (pAudioSrcInfo->recorderBufferQueue, OpenSLESAudioSrc_Callback,
			pAudioSrcInfo);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open RegisterCallback Error!\n");
		return -1;
	}

    // in case already recording, stop recording and clear buffer queue
    result = (*pAudioSrcInfo->recorderRecord)->SetRecordState (pAudioSrcInfo->recorderRecord, SL_RECORDSTATE_STOPPED);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open SetRecordState1 Error!\n");
		return -1;
	}

    result = (*pAudioSrcInfo->recorderBufferQueue)->Clear (pAudioSrcInfo->recorderBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open Clear Error!\n");
		return -1;
	}

    // enqueue an empty buffer to be filled by the recorder
    // (for streaming recording, we would enqueue at least 2 empty buffers to start things off)
    result = (*pAudioSrcInfo->recorderBufferQueue)->Enqueue(pAudioSrcInfo->recorderBufferQueue, pAudioSrcInfo->recorderBuffer,
            pAudioSrcInfo->recorderBufferSize);
    // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
    // which for this code example would indicate a programming error
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open Enqueue Error!\n");
		return -1;
	}

    // start recording
    result = (*pAudioSrcInfo->recorderRecord)->SetRecordState(pAudioSrcInfo->recorderRecord, SL_RECORDSTATE_RECORDING);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Src_Open SetRecordState2 Error!\n");
		return -1;
	}

	return 0;
}

static long OpenSLESAudioSrc_Close (OPENSLES_AUDIO_SRC_INFO *pAudioSrcInfo)
{
    if (pAudioSrcInfo->recorderObject != NULL) {
        (*pAudioSrcInfo->recorderObject)->Destroy(pAudioSrcInfo->recorderObject);
        pAudioSrcInfo->recorderObject = NULL;
        pAudioSrcInfo->recorderRecord = NULL;
        pAudioSrcInfo->recorderBufferQueue = NULL;
    }

	return 0;
}

AUDIO_IN_HANDLE OpenSLESAudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	OPENSLES_AUDIO_INFO		*pAudioInfo = (OPENSLES_AUDIO_INFO *)Handle;
	OPENSLES_AUDIO_SRC_INFO	*pAudioSrcInfo;
	int						Ret;

	if (Param->CallBack == NULL)
	{
		pAudioSrcInfo = (OPENSLES_AUDIO_SRC_INFO *)malloc(sizeof(OPENSLES_AUDIO_SRC_INFO) + OPENSLES_AUDIO_PROC_SIZE + OPENSLES_AUDIO_BUF_SIZE);
	}
	else
	{
		pAudioSrcInfo = (OPENSLES_AUDIO_SRC_INFO *)malloc(sizeof(OPENSLES_AUDIO_SRC_INFO) + Param->FrameCount * Param->Channels * 2);
	}
	if (pAudioSrcInfo == NULL)
	{
		return NULL;
	}

	pAudioSrcInfo->Channels = Param->Channels;
	switch (Param->SampleRate)
	{
		case 32000:
			pAudioSrcInfo->SampleRate = SL_SAMPLINGRATE_32;
			break;

		case 44100:
			pAudioSrcInfo->SampleRate = SL_SAMPLINGRATE_44_1;
			break;

		case 48000:
			pAudioSrcInfo->SampleRate = SL_SAMPLINGRATE_48;
			break;

		default:
			pAudioSrcInfo->SampleRate = SL_SAMPLINGRATE_44_1;
			Param->SampleRate = 44100;
			break;
	}
	if (Param->CallBack == NULL)
	{
		pAudioSrcInfo->CallBack = NULL;
		pAudioSrcInfo->recorderBuffer = (unsigned char *)pAudioSrcInfo + sizeof(OPENSLES_AUDIO_SRC_INFO);
		pAudioSrcInfo->recorderBufferSize = OPENSLES_AUDIO_PROC_SIZE;
		pAudioSrcInfo->BufAddr = pAudioSrcInfo->recorderBuffer + OPENSLES_AUDIO_PROC_SIZE;
		pAudioSrcInfo->Read = 0;
		pAudioSrcInfo->Write = 0;
	}
	else
	{
		pAudioSrcInfo->CallBack = Param->CallBack;
		pAudioSrcInfo->User = Param->User;
		pAudioSrcInfo->recorderBuffer = (unsigned char *)pAudioSrcInfo + sizeof(OPENSLES_AUDIO_SRC_INFO);
		pAudioSrcInfo->recorderBufferSize = Param->FrameCount * Param->Channels * 2;
	}

	Ret = OpenSLESAudioSrc_Open (pAudioInfo, pAudioSrcInfo);
	if (Ret != 0)
	{
		free (pAudioSrcInfo);
		pAudioSrcInfo = NULL;
	}

	return (AUDIO_IN_HANDLE)pAudioSrcInfo;
}

long OpenSLESAudioIn_Close (AUDIO_IN_HANDLE Handle)
{
	OPENSLES_AUDIO_SRC_INFO	*pAudioSrcInfo = (OPENSLES_AUDIO_SRC_INFO	*)Handle;
	int						Ret;
	
	Ret = OpenSLESAudioSrc_Close (pAudioSrcInfo);
	if (Ret == -1)
	{
		return -1;
	}

	free (pAudioSrcInfo);

	return 0;
}

long OpenSLESAudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	OPENSLES_AUDIO_SRC_INFO *pOpenSLESAudioSrcInfo = (OPENSLES_AUDIO_SRC_INFO *)Handle;
	unsigned long Write, Free;

	Write = pOpenSLESAudioSrcInfo->Write;
	if (Write < pOpenSLESAudioSrcInfo->Read)
	{
		Free = Write + OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSrcInfo->Read;
	}
	else
	{
		Free = Write - pOpenSLESAudioSrcInfo->Read;
	}

	if (Free < Size)
	{
		Size = Free;
	}

	if (pOpenSLESAudioSrcInfo->Read + Size > OPENSLES_AUDIO_BUF_SIZE)
	{
		memcpy (BufAddr, pOpenSLESAudioSrcInfo->BufAddr + pOpenSLESAudioSrcInfo->Read, OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSrcInfo->Read);
		memcpy ((unsigned char *)BufAddr + (OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSrcInfo->Read), pOpenSLESAudioSrcInfo->BufAddr, Size - (OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSrcInfo->Read));
		pOpenSLESAudioSrcInfo->Read = pOpenSLESAudioSrcInfo->Read + Size - OPENSLES_AUDIO_BUF_SIZE;
	}
	else
	{
		memcpy (BufAddr, pOpenSLESAudioSrcInfo->BufAddr + pOpenSLESAudioSrcInfo->Read, Size);
		pOpenSLESAudioSrcInfo->Read += Size;
	}

	return Size;
}

// this callback handler is called every time a buffer finishes playing
void OpenSLESAudioSink_Callback (SLAndroidSimpleBufferQueueItf bq, void *context)
{
	OPENSLES_AUDIO_SINK_INFO	*pAudioSinkInfo = (OPENSLES_AUDIO_SINK_INFO *)context;
	SLresult					result;
	unsigned long				Available;
	unsigned long				Write;

	if (NULL == pAudioSinkInfo)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Callback context Error!\n");
		return;
	}

	if (bq != pAudioSinkInfo->bqPlayerBufferQueue)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Callback bq Error!\n");
		return;
	}
	
	if (pAudioSinkInfo->CallBack == NULL)
	{
		Write = pAudioSinkInfo->Write;
		if (Write < pAudioSinkInfo->Read)
		{
			Available = Write + OPENSLES_AUDIO_BUF_SIZE - pAudioSinkInfo->Read;
		}
		else
		{
			Available = Write - pAudioSinkInfo->Read;
		}
		if (Available >= pAudioSinkInfo->playerBufferSize)
		{
			memcpy (pAudioSinkInfo->playerBuffer, pAudioSinkInfo->BufAddr + pAudioSinkInfo->Read, pAudioSinkInfo->playerBufferSize);
			if (pAudioSinkInfo->Read + pAudioSinkInfo->playerBufferSize == OPENSLES_AUDIO_BUF_SIZE)
			{
				pAudioSinkInfo->Read = 0;
			}
			else
			{
				pAudioSinkInfo->Read += pAudioSinkInfo->playerBufferSize;
			}
		}
		else
		{
			memset (pAudioSinkInfo->playerBuffer, 0, pAudioSinkInfo->playerBufferSize);
		}
	}
	else
	{
		memset (pAudioSinkInfo->playerBuffer, 0, pAudioSinkInfo->playerBufferSize);
		pAudioSinkInfo->CallBack (pAudioSinkInfo->User, pAudioSinkInfo->playerBuffer);
	}

	// enqueue another buffer
	result = (*pAudioSinkInfo->bqPlayerBufferQueue)->Enqueue (pAudioSinkInfo->bqPlayerBufferQueue, pAudioSinkInfo->playerBuffer, pAudioSinkInfo->playerBufferSize);
	// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
	// which for this code example would indicate a programming error
    if (SL_RESULT_SUCCESS != result)
    {
		M3D_DebugPrint ("OpenSLES_Sink_Callback Enqueue Error!\n");
		return;
    }

	return;
}

static long OpenSLESAudioSink_Open (OPENSLES_AUDIO_INFO *pAudioInfo, OPENSLES_AUDIO_SINK_INFO *pAudioSinkInfo)
{
	const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
			/*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
			/*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
	SLresult result;
	unsigned long Write, Available;

	// configure audio source
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, pAudioSinkInfo->Channels, pAudioSinkInfo->SampleRate,
		SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};
	SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, pAudioInfo->outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	result = (*pAudioInfo->engineEngine)->CreateAudioPlayer(pAudioInfo->engineEngine, &pAudioSinkInfo->bqPlayerObject, &audioSrc, &audioSnk,
			3, ids, req);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open CreateAudioPlayer Error!\n");
		return -1;
	}

	// realize the player
	result = (*pAudioSinkInfo->bqPlayerObject)->Realize(pAudioSinkInfo->bqPlayerObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open Realize Error!\n");
		return -1;
	}

	// get the play interface
	result = (*pAudioSinkInfo->bqPlayerObject)->GetInterface(pAudioSinkInfo->bqPlayerObject, SL_IID_PLAY, &pAudioSinkInfo->bqPlayerPlay);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open GetInterface1 Error!\n");
		return -1;
	}

	// get the buffer queue interface
	result = (*pAudioSinkInfo->bqPlayerObject)->GetInterface(pAudioSinkInfo->bqPlayerObject, SL_IID_BUFFERQUEUE,
			&pAudioSinkInfo->bqPlayerBufferQueue);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open GetInterface2 Error!\n");
		return -1;
	}

	// register callback on the buffer queue
	result = (*pAudioSinkInfo->bqPlayerBufferQueue)->RegisterCallback(pAudioSinkInfo->bqPlayerBufferQueue, OpenSLESAudioSink_Callback, pAudioSinkInfo);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open RegisterCallback Error!\n");
		return -1;
	}

	// get the effect send interface
	result = (*pAudioSinkInfo->bqPlayerObject)->GetInterface(pAudioSinkInfo->bqPlayerObject, SL_IID_EFFECTSEND,
			&pAudioSinkInfo->bqPlayerEffectSend);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open GetInterface3 Error!\n");
		return -1;
	}

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
	// get the mute/solo interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
	assert(SL_RESULT_SUCCESS == result);
#endif

	// get the volume interface
	result = (*pAudioSinkInfo->bqPlayerObject)->GetInterface(pAudioSinkInfo->bqPlayerObject, SL_IID_VOLUME, &pAudioSinkInfo->bqPlayerVolume);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open GetInterface4 Error!\n");
		return -1;
	}

	// set the player's state to playing
	result = (*pAudioSinkInfo->bqPlayerPlay)->SetPlayState(pAudioSinkInfo->bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLES_Sink_Open SetPlayState Error!\n");
		return -1;
	}

	if (pAudioSinkInfo->CallBack == NULL)
	{
		Write = pAudioSinkInfo->Write;
		if (Write < pAudioSinkInfo->Read)
		{
			Available = Write + OPENSLES_AUDIO_BUF_SIZE - pAudioSinkInfo->Read;
		}
		else
		{
			Available = Write - pAudioSinkInfo->Read;
		}
		if (Available >= pAudioSinkInfo->playerBufferSize)
		{
			memcpy (pAudioSinkInfo->playerBuffer, pAudioSinkInfo->BufAddr + pAudioSinkInfo->Read, pAudioSinkInfo->playerBufferSize);
			if (pAudioSinkInfo->Read + pAudioSinkInfo->playerBufferSize == OPENSLES_AUDIO_BUF_SIZE)
			{
				pAudioSinkInfo->Read = 0;
			}
			else
			{
				pAudioSinkInfo->Read += pAudioSinkInfo->playerBufferSize;
			}
		}
		else
		{
			memset (pAudioSinkInfo->playerBuffer, 0, pAudioSinkInfo->playerBufferSize);
		}
	}
	else
	{
		memset (pAudioSinkInfo->playerBuffer, 0, pAudioSinkInfo->playerBufferSize);
		pAudioSinkInfo->CallBack (pAudioSinkInfo->User, pAudioSinkInfo->playerBuffer);
	}

	// enqueue another buffer
	result = (*pAudioSinkInfo->bqPlayerBufferQueue)->Enqueue(pAudioSinkInfo->bqPlayerBufferQueue, pAudioSinkInfo->playerBuffer, pAudioSinkInfo->playerBufferSize);
	// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
	// which for this code example would indicate a programming error
    if (SL_RESULT_SUCCESS != result)
    {
		M3D_DebugPrint ("OpenSLES_Sink_Callback Enqueue Error!\n");
		return -1;
    }

	return 0;
}

static long OpenSLESAudioSink_Close (OPENSLES_AUDIO_SINK_INFO *pAudioSinkInfo)
{
	if (pAudioSinkInfo->bqPlayerObject != NULL)
   	{
		(*pAudioSinkInfo->bqPlayerObject)->Destroy(pAudioSinkInfo->bqPlayerObject);
		pAudioSinkInfo->bqPlayerObject = NULL;
		pAudioSinkInfo->bqPlayerPlay = NULL;
		pAudioSinkInfo->bqPlayerBufferQueue = NULL;
		pAudioSinkInfo->bqPlayerEffectSend = NULL;
		pAudioSinkInfo->bqPlayerMuteSolo = NULL;
		pAudioSinkInfo->bqPlayerVolume = NULL;
	}

	return 0;
}

AUDIO_OUT_HANDLE OpenSLESAudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	OPENSLES_AUDIO_INFO			*pAudioInfo = (OPENSLES_AUDIO_INFO *)Handle;
	OPENSLES_AUDIO_SINK_INFO	*pAudioSinkInfo;
	int							Ret;

	if (Param->CallBack == NULL)
	{
		pAudioSinkInfo = (OPENSLES_AUDIO_SINK_INFO *)malloc(sizeof(OPENSLES_AUDIO_SINK_INFO) + OPENSLES_AUDIO_PROC_SIZE + OPENSLES_AUDIO_BUF_SIZE);
	}
	else
	{
		pAudioSinkInfo = (OPENSLES_AUDIO_SINK_INFO *)malloc(sizeof(OPENSLES_AUDIO_SINK_INFO) + Param->FrameCount * Param->Channels * 2);
	}
	if (pAudioSinkInfo == NULL)
	{
		return NULL;
	}

	pAudioSinkInfo->Channels = (unsigned short)Param->Channels;
	switch (Param->SampleRate)
	{
		case 32000:
			pAudioSinkInfo->SampleRate = SL_SAMPLINGRATE_32;
			break;

		case 44100:
			pAudioSinkInfo->SampleRate = SL_SAMPLINGRATE_44_1;
			break;

		case 48000:
			pAudioSinkInfo->SampleRate = SL_SAMPLINGRATE_48;
			break;

		default:
			pAudioSinkInfo->SampleRate = SL_SAMPLINGRATE_44_1;
			Param->SampleRate = 44100;
			break;
	}
	if (Param->CallBack == NULL)
	{
		pAudioSinkInfo->CallBack = NULL;
		pAudioSinkInfo->playerBuffer = (unsigned char *)pAudioSinkInfo + sizeof(OPENSLES_AUDIO_SINK_INFO);
		pAudioSinkInfo->playerBufferSize = OPENSLES_AUDIO_PROC_SIZE;
		pAudioSinkInfo->BufAddr = pAudioSinkInfo->playerBuffer + OPENSLES_AUDIO_PROC_SIZE;
		pAudioSinkInfo->Read = 0;
		pAudioSinkInfo->Write = 0;
	}
	else
	{
		pAudioSinkInfo->CallBack = Param->CallBack;
		pAudioSinkInfo->User = Param->User;
		pAudioSinkInfo->playerBuffer = (unsigned char *)pAudioSinkInfo + sizeof(OPENSLES_AUDIO_SINK_INFO);
		pAudioSinkInfo->playerBufferSize = Param->FrameCount * Param->Channels * 2;
	}

	Ret = OpenSLESAudioSink_Open (pAudioInfo, pAudioSinkInfo);
	if (Ret != 0)
	{
		free (pAudioSinkInfo);
		pAudioSinkInfo = NULL;
	}
		
	return (AUDIO_OUT_HANDLE)pAudioSinkInfo;
}

long OpenSLESAudioOut_Close (AUDIO_OUT_HANDLE Handle)
{
	OPENSLES_AUDIO_SINK_INFO	*pAudioSinkInfo = (OPENSLES_AUDIO_SINK_INFO	*)Handle;
	int 						Ret;
	
	Ret = OpenSLESAudioSink_Close (pAudioSinkInfo);
	if (Ret == -1)
	{
		return -1;
	}

	free (pAudioSinkInfo);

	return 0;
}

long OpenSLESAudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	OPENSLES_AUDIO_SINK_INFO *pOpenSLESAudioSinkInfo = (OPENSLES_AUDIO_SINK_INFO *)Handle;
	unsigned long Read, Free;

	Read = pOpenSLESAudioSinkInfo->Read;
	if (pOpenSLESAudioSinkInfo->Write < Read)
	{
		Free = Read - pOpenSLESAudioSinkInfo->Write;
	}
	else
	{
		Free = OPENSLES_AUDIO_BUF_SIZE - (pOpenSLESAudioSinkInfo->Write - Read); 
	}
	if (Free < Size)
	{
		Size = Free;
	}

	if (pOpenSLESAudioSinkInfo->Write + Size > OPENSLES_AUDIO_BUF_SIZE)
	{
		memcpy (pOpenSLESAudioSinkInfo->BufAddr + pOpenSLESAudioSinkInfo->Write, BufAddr, OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSinkInfo->Write);
		memcpy (pOpenSLESAudioSinkInfo->BufAddr, (unsigned char *)BufAddr + (OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSinkInfo->Write), Size - (OPENSLES_AUDIO_BUF_SIZE - pOpenSLESAudioSinkInfo->Write));
		pOpenSLESAudioSinkInfo->Write = pOpenSLESAudioSinkInfo->Write + Size - OPENSLES_AUDIO_BUF_SIZE;
	}
	else
	{
		memcpy (pOpenSLESAudioSinkInfo->BufAddr + pOpenSLESAudioSinkInfo->Write, BufAddr, Size);
		pOpenSLESAudioSinkInfo->Write += Size;
	}

	return Size;
}


static long OpenSLESAudio_Engine_Init (OPENSLES_AUDIO_INFO *pAudioInfo)
{
	const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	SLresult result;

	// create engine
	result = slCreateEngine (&pAudioInfo->engineObject, 0, NULL, 0, NULL, NULL);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLESAudio_Engine_Init slCreateEngine!\n");
		return -1;
	}

	// realize the engine
	result = (*pAudioInfo->engineObject)->Realize(pAudioInfo->engineObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLESAudio_Engine_Init Realize!\n");
		return -1;
	}

	// get the engine interface, which is needed in order to create other objects
	result = (*pAudioInfo->engineObject)->GetInterface(pAudioInfo->engineObject, SL_IID_ENGINE, &pAudioInfo->engineEngine);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLESAudio_Engine_Init GetInterface!\n");
		return -1;
	}

	// create output mix, with environmental reverb specified as a non-required interface
	result = (*pAudioInfo->engineEngine)->CreateOutputMix(pAudioInfo->engineEngine, &pAudioInfo->outputMixObject, 1, ids, req);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLESAudio_Engine_Init CreateOutputMix!\n");
		return -1;
	}

	// realize the output mix
	result = (*pAudioInfo->outputMixObject)->Realize(pAudioInfo->outputMixObject, SL_BOOLEAN_FALSE);
	if (SL_RESULT_SUCCESS != result)
	{
		M3D_DebugPrint ("OpenSLESAudio_Engine_Init Realize!\n");
		return -1;
	}

	// get the environmental reverb interface
	// this could fail if the environmental reverb effect is not available,
	// either because the feature is not present, excessive CPU load, or
	// the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
	result = (*pAudioInfo->outputMixObject)->GetInterface(pAudioInfo->outputMixObject, SL_IID_ENVIRONMENTALREVERB,
			&pAudioInfo->outputMixEnvironmentalReverb);
	if (SL_RESULT_SUCCESS == result) {
		result = (*pAudioInfo->outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
				pAudioInfo->outputMixEnvironmentalReverb, &reverbSettings);
	}
	// ignore unsuccessful result codes for environmental reverb, as it is optional for this example

	return 0;
}

static long OpenSLESAudio_Engine_Finish (OPENSLES_AUDIO_INFO *pAudioInfo)
{
    // destroy engine object, and invalidate all associated interfaces
    if (pAudioInfo->engineObject != NULL) {
        (*pAudioInfo->engineObject)->Destroy(pAudioInfo->engineObject);
        pAudioInfo->engineObject = NULL;
        pAudioInfo->engineEngine = NULL;
    }

	return 0;
}

AUDIO_HANDLE OpenSLESAudio_Init (int samplerate)
{
	OPENSLES_AUDIO_INFO	*pAudioInfo;
	int					Ret;

	pAudioInfo = (OPENSLES_AUDIO_INFO *)malloc (sizeof (OPENSLES_AUDIO_INFO));
	if (pAudioInfo == NULL)
	{
		return NULL;
	}

	Ret = OpenSLESAudio_Engine_Init (pAudioInfo);
	if (Ret != 0)
	{
		free (pAudioInfo);
		return NULL;
	}

	return (AUDIO_HANDLE)pAudioInfo;
}

long OpenSLESAudio_Finish (AUDIO_HANDLE Handle)
{
	OPENSLES_AUDIO_INFO	*pAudioInfo = (OPENSLES_AUDIO_INFO *)Handle;
	int					Ret;
	
	Ret = OpenSLESAudio_Engine_Finish (pAudioInfo);
	if (Ret != 0)
	{
		return -1;
	}
	
	free (pAudioInfo);

	return 0;
}

