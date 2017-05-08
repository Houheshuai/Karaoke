#ifndef __PLATFORM_MACROS_H__
#define __PLATFORM_MACROS_H__

/**
 * Define some platform specific macros.
 */
#include "platform/PlatformConfig.h"
#include "platform/PlatformDefine.h"

//¼ì²é±àÒë´íÎó
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
  #if __has_attribute(format)
  #define FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
  #endif // __has_attribute(format)
#else
#define FORMAT_PRINTF(formatPos, argPos)
#endif

#endif // __PLATFORM_MACROS_H__
