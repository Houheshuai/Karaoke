#include "IMEJni.h"
#include "JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

extern "C" 
{
    void setKeyboardStateJNI(int bOpen) {
        if (bOpen) {
            openKeyboardJNI();
        } else {
            closeKeyboardJNI();
        }
    }

    void openKeyboardJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, "com/multak/lib/MKGLSurfaceView", "openIMEKeyboard", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void closeKeyboardJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, "com/multak/lib/MKGLSurfaceView", "closeIMEKeyboard", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}
