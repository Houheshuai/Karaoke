//#include "platform/android/CCGLViewImpl-android.h"
#include "Event/EventKeyboard.h"
#include "Event/EventTouch.h"
#include "Event/EventMouse.h"


#include <android/log.h>
#include <jni.h>
#include <unordered_map>

void android_keycode_event(int keycode, int isPressed) __attribute__((weak));

extern "C" {
    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeTouchesBegin(JNIEnv * env, jclass thiz, jint id, jfloat x, jfloat y) {
        //intptr_t idlong = id;
        //Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &idlong, &x, &y);
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeTouchesEnd(JNIEnv * env, jclass thiz, jint id, jfloat x, jfloat y) {
        //intptr_t idlong = id;
        //Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &idlong, &x, &y);
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeTouchesMove(JNIEnv * env, jclass thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        /*int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t idlong[size];
        for(int i = 0; i < size; i++)
            idlong[i] = id[i];

        Director::getInstance()->getOpenGLView()->handleTouchesMove(size, idlong, x, y);*/
    }

    JNIEXPORT void JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeTouchesCancel(JNIEnv * env, jclass thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        /*int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t idlong[size];
        for(int i = 0; i < size; i++)
            idlong[i] = id[i];

        Director::getInstance()->getOpenGLView()->handleTouchesCancel(size, idlong, x, y);*/
    }

#define KEYCODE_BACK 0x04
#define KEYCODE_MENU 0x52
#define KEYCODE_DPAD_UP 0x13
#define KEYCODE_DPAD_DOWN 0x14
#define KEYCODE_DPAD_LEFT 0x15
#define KEYCODE_DPAD_RIGHT 0x16
#define KEYCODE_ENTER 0x42
#define KEYCODE_PLAY  0x7e
#define KEYCODE_DPAD_CENTER  0x17
    
    
    static std::unordered_map<int, EventKeyboard::KeyCode> g_keyCodeMap = {
        { KEYCODE_BACK , EventKeyboard::KeyCode::KEY_ESCAPE},
        { KEYCODE_MENU , EventKeyboard::KeyCode::KEY_MENU},
        { KEYCODE_DPAD_UP  , EventKeyboard::KeyCode::KEY_DPAD_UP },
        { KEYCODE_DPAD_DOWN , EventKeyboard::KeyCode::KEY_DPAD_DOWN },
        { KEYCODE_DPAD_LEFT , EventKeyboard::KeyCode::KEY_DPAD_LEFT },
        { KEYCODE_DPAD_RIGHT , EventKeyboard::KeyCode::KEY_DPAD_RIGHT },
        { KEYCODE_ENTER  , EventKeyboard::KeyCode::KEY_ENTER},
        { KEYCODE_PLAY  , EventKeyboard::KeyCode::KEY_PLAY},
        { KEYCODE_DPAD_CENTER  , EventKeyboard::KeyCode::KEY_DPAD_CENTER},
        
    };
    
    JNIEXPORT jboolean JNICALL Java_com_multak_Karaoke_KaraokeLib_nativeKeyEvent(JNIEnv * env, jclass thiz, jint keyCode, jint isPressed) {
        //Director* pDirector = Director::getInstance();
        
        //auto iterKeyCode = g_keyCodeMap.find(keyCode);
        //if (iterKeyCode == g_keyCodeMap.end()) {
        //    return JNI_FALSE;
        //}
        
        //EventKeyboard::KeyCode _Key = g_keyCodeMap.at(keyCode);
        //EventKeyboard event(_Key, isPressed);
        //Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		android_keycode_event(keyCode, isPressed);
        return JNI_TRUE;
        
    }}
