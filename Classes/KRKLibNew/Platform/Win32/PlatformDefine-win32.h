#ifndef __PLATFORMDEFINE_H__
#define __PLATFORMDEFINE_H__

#include "platform/PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_WIN32

#ifdef __MINGW32__
#include <string.h>
#endif

#include <assert.h>

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif //s TARGET_PLATFORM == PLATFORM_WIN32

#endif // __PLATFORMDEFINE_H__
