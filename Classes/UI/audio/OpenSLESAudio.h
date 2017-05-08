#ifndef _OPENSLES_AUDIO_H_
#define _OPENSLES_AUDIO_H_

#include "CP_Audio.h"

#if defined(__cplusplus)
extern "C" {
#endif

	AUDIO_IN_HANDLE OpenSLESAudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
	long OpenSLESAudioIn_Close (AUDIO_IN_HANDLE Handle);
	long OpenSLESAudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size);

	AUDIO_OUT_HANDLE OpenSLESAudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
	long OpenSLESAudioOut_Close (AUDIO_OUT_HANDLE Handle);
	long OpenSLESAudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size);

	AUDIO_HANDLE OpenSLESAudio_Init (int samplerate);
	long OpenSLESAudio_Finish (AUDIO_HANDLE Handle);

#if defined(__cplusplus)
}
#endif

#endif

