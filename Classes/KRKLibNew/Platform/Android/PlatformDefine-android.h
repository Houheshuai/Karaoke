#ifndef __PLATFORMDEFINE_H__
#define __PLATFORMDEFINE_H__

#include "platform/PlatformConfig.h"
#if TARGET_PLATFORM == PLATFORM_ANDROID

#include "android/log.h"

#define NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        __android_log_print(ANDROID_LOG_ERROR,                  \
                            "karaoke assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
    }

#define MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        __android_log_print(ANDROID_LOG_ERROR,                      \
                            "karaoke assert",                     \
                            "file:%s function:%s line:%d, %s",      \
                            __FILE__, __FUNCTION__, __LINE__, msg); \
    }

#define MKASSERT(cond) NO_MESSAGE_PSEUDOASSERT(cond)

#define UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif // __PLATFORMDEFINE_H__
