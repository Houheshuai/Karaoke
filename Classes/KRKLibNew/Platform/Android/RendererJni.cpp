#include "JniHelper.h"
#include <jni.h>

void android_app_render() __attribute__((weak));
void android_app_onpause() __attribute__((weak));
void android_app_onresume() __attribute__((weak));
void android_app_exit() __attribute__((weak));

extern "C" {

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeRender(JNIEnv* env, jclass c) {
        //cocos2d::Director::getInstance()->mainLoop();
		android_app_render();
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeOnPause(JNIEnv* env, jclass c) {
		android_app_onpause();
        //if (Director::getInstance()->getOpenGLView()) {
                //Application::getInstance()->applicationDidEnterBackground();
                //cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
                //cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
        //}
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeOnResume(JNIEnv* env, jclass c) {
		android_app_onresume();
        //if (Director::getInstance()->getOpenGLView()) {
        //    Application::getInstance()->applicationWillEnterForeground();
        //    cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        //    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
        //}
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeInsertText(JNIEnv* env, jclass thiz, jstring text) {
        //std::string  strValue = cocos2d::StringUtils::getStringUTFCharsJNI(env, text);
        //const char* pszText = strValue.c_str();
        //cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeDeleteBackward(JNIEnv* env, jclass thiz) {
        //cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }

    JNIEXPORT jstring JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeGetContentText(JNIEnv* env, jclass thiz) {
        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK || ! env) {
            return 0;
        }
        //std::string pszText = cocos2d::IMEDispatcher::sharedDispatcher()->getContentText();
        //return cocos2d::StringUtils::newStringUTFJNI(env, pszText);
		return 0;
    }
	
	JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeExit(JNIEnv* env, jclass thiz) {
		android_app_exit();
        //if (Director::getInstance()->getOpenGLView()) {
                //Application::getInstance()->applicationDidEnterBackground();
                //cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
                //cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
        //}
    }
}
