#ifndef _PLATFORM_AUDIO_RECORD_H_
#define _PLATFORM_AUDIO_RECORD_H_

#include "CP_Audio.h"

#if defined(__cplusplus)
extern "C" {
#endif
	long OutRaw_Avalible();
	AUDIO_IN_HANDLE OutRaw_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
	long OutRaw_Close (AUDIO_IN_HANDLE Handle);
	long OutRaw_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size);

#if defined(__cplusplus)
}
#endif


#endif

