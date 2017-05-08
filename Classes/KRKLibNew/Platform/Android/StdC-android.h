#ifndef __ANDROID_STD_C_H__
#define __ANDROID_STD_C_H__

#include "platform/PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_ANDROID

#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <cassert>
#include <unistd.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#define US_Sleep(x) usleep(x)

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif  // __ANDROID_STD_C_H__
