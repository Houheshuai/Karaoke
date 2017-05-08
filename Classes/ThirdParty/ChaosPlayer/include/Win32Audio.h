#ifndef _WIN32_AUDIO_H_
#define _WIN32_AUDIO_H_

#include "CP_Audio.h"

#if defined(__cplusplus)
extern "C" {
#endif

AUDIO_IN_HANDLE Win32AudioIn_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
long Win32AudioIn_Close (AUDIO_IN_HANDLE Handle);
long Win32AudioIn_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size);

AUDIO_OUT_HANDLE Win32AudioOut_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param);
long Win32AudioOut_Close (AUDIO_OUT_HANDLE Handle);
long Win32AudioOut_Write (AUDIO_OUT_HANDLE Handle, void *BufAddr, unsigned long Size);

AUDIO_HANDLE Win32Audio_Init (void);
int Win32Audio_Finish (AUDIO_HANDLE Handle);

#if defined(__cplusplus)
}
#endif

#endif

