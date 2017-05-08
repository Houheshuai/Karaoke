#ifndef __PLATFORM_STDC_H__
#define __PLATFORM_STDC_H__

#include "platform/PlatformConfig.h"

#if TARGET_PLATFORM == PLATFORM_MAC
#include "platform/mac/StdC-mac.h"
#elif TARGET_PLATFORM == PLATFORM_IOS
#include "platform/ios/StdC-ios.h"
#elif TARGET_PLATFORM == PLATFORM_ANDROID
#include "platform/android/StdC-android.h"
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform/win32/StdC-win32.h"
#elif TARGET_PLATFORM == PLATFORM_WINRT
#include "platform/winrt/StdC.h"
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include "platform/linux/StdC-linux.h"
#endif

#endif // __PLATFORM_STDC_H__
