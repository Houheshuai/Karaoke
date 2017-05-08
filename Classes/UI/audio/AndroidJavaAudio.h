#ifndef _ANDROID_JAVA_AUDIO_H_
#define _ANDROID_JAVA_AUDIO_H_

#include "CP_Audio.h"

#include <jni.h>
typedef struct tagANDROID_JAVA_AUDIO_PARAM
{
	JavaVM	*Jvm;
	jclass	Class;
	int		InSampleRate;
	int		OutSampleRate;
	int		InChannels;
	int		OutChannels;
}ANDROID_JAVA_AUDIO_PARAM;


int AndroidJavaAudio_Set (AUDIO_HANDLE Handle, int Cmd, int Data);

AUDIO_IN_HANDLE AndroidJavaAudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
long AndroidJavaAudioIn_Close (AUDIO_IN_HANDLE Handle);
long AndroidJavaAudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size);

AUDIO_OUT_HANDLE AndroidJavaAudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
long AndroidJavaAudioOut_Close (AUDIO_OUT_HANDLE Handle);
long AndroidJavaAudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size);

AUDIO_HANDLE AndroidJavaAudio_Init (int samplerate);
int AndroidJavaAudio_Finish (AUDIO_HANDLE Handle);

#endif

