#ifndef __EVENT_TYPE_H__
#define __EVENT_TYPE_H__


/**
 * This header is used for defining event types using in NotificationCenter
 */

// The application will come to foreground.
// This message is posted in cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp.
#define EVENT_COME_TO_FOREGROUND    "event_come_to_foreground"

// The renderer[android:GLSurfaceView.Renderer  WP8:Cocos2dRenderer] was recreated.
// This message is used for reloading resources before renderer is recreated on Android/WP8.
// This message is posted in cocos/platform/android/javaactivity.cpp and cocos\platform\wp8-xaml\cpp\Cocos2dRenderer.cpp.
#define EVENT_RENDERER_RECREATED    "event_renderer_recreated"

// The application will come to background.
// This message is used for doing something before coming to background, such as save RenderTexture.
// This message is posted in cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp and cocos\platform\wp8-xaml\cpp\Cocos2dRenderer.cpp.
#define EVENT_COME_TO_BACKGROUND    "event_come_to_background"

/// @endcond
#endif // __EVENT_TYPE_H__
