#ifndef __WIN32_STD_C_H__
#define __WIN32_STD_C_H__

#include "platform/PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_WIN32

#include <BaseTsd.h>
#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

//#include "platform/PlatformMacros.h"
#include <float.h>

// for math.h on win32 platform
#ifndef __MINGW32__

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if !defined(isnan)
    #define isnan   _isnan
#endif

#if _MSC_VER < 1900
#ifndef snprintf
#define snprintf _snprintf
#endif
#endif

#endif // __MINGW32__

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef M_PI
  #define M_PI      3.14159265358
#endif
#ifndef M_PI_2
  #define M_PI_2    1.57079632679
#endif
// for MIN MAX and sys/time.h on win32 platform
#ifdef __MINGW32__
#include <sys/time.h>
#endif // __MINGW32__

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX


#if _MSC_VER >= 1600 || defined(__MINGW32__)
    #include <stdint.h>
#else
    #include "./compat/stdint.h"
#endif

#define _WINSOCKAPI_
#ifndef NOMINMAX
  #define NOMINMAX
#endif
// Structure timeval has define in winsock.h, include windows.h for it.
#include <windows.h>

#ifndef __MINGW32__

#include <WinSock2.h>

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *, struct timezone *);

#define US_Sleep(x) Sleep(x/1000)

#else

#undef _WINSOCKAPI_
#include <winsock2.h>

// Conflicted with math.h isnan
#include <cmath>
using std::isnan;

inline int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count,
                 const char *format, va_list argptr) {
  return vsnprintf(buffer, sizeOfBuffer, format, argptr);
}

#ifndef __clang__
inline errno_t strcpy_s(char *strDestination, size_t numberOfElements,
        const char *strSource) {
    strcpy(strDestination, strSource);
    return 0;
}
#endif
#endif // __MINGW32__

// Conflicted with cocos2d::MessageBox, so we need to undef it.
#ifdef MessageBox
#undef MessageBox
#endif

// Conflicted with ParticleSystem::PositionType::RELATIVE, so we need to undef it.
#ifdef RELATIVE
#undef RELATIVE
#endif

// Conflicted with CCBReader::SizeType::RELATIVE and CCBReader::ScaleType::RELATIVE, so we need to undef it.
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif

// Conflicted with HttpRequest::Type::DELETE, so we need to undef it.
#ifdef DELETE
#undef DELETE
#endif

#undef min
#undef max

#endif // TARGET_PLATFORM == PLATFORM_WIN32

#endif  // __WIN32_STD_C_H__



