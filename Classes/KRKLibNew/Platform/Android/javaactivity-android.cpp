//#include "CCApplication-android.h"
//#include "CCGLViewImpl-android.h"
//#include "Base/CCDirector.h"
//#include "Base/CCEventCustom.h"
#include "Event/EventType.h"
//#include "Base/CCEventDispatcher.h"
//#include "renderer/CCGLProgramCache.h"
//#include "renderer/CCTextureCache.h"
//#include "renderer/ccGLStateCache.h"
//#include "2d/CCDrawingPrimitives.h"
#include "Platform/Android/JniHelper.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

void android_app_init(JNIEnv* env) __attribute__((weak));
void android_view_init(int w, int h) __attribute__((weak));
void android_surfacechanged_init(int w, int h) __attribute__((weak));

extern "C"
{

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    android_app_init(JniHelper::getEnv());
	
    return JNI_VERSION_1_4;
}

JNIEXPORT void Java_com_multak_Karaoke_KaraokeLib_nativeInit(JNIEnv*  env, jclass thiz, jint w, jint h)
{
	android_view_init(w, h);
    /*auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = cocos2d::GLViewImpl::create("Android app");
        glview->setFrameSize(w, h);
        director->setOpenGLView(glview);

        cocos2d::Application::getInstance()->run();
    }
    else
    {
        cocos2d::GL::invalidateStateCache();
        cocos2d::GLProgramCache::getInstance()->reloadDefaultGLPrograms();
        cocos2d::DrawPrimitives::init();
        cocos2d::VolatileTextureMgr::reloadAllTextures();

        cocos2d::EventCustom recreatedEvent(EVENT_RENDERER_RECREATED);
        director->getEventDispatcher()->dispatchEvent(&recreatedEvent);
        director->setGLDefaultValues();
    }
    cocos2d::network::_preloadJavaDownloaderClass();*/
}

/*
JNIEXPORT jintArray Java_org_cocos2dx_lib_Cocos2dxActivity_getGLContextAttrs(JNIEnv*  env, jclass thiz)
{
    cocos2d::Application::getInstance()->initGLContextAttrs(); 
    GLContextAttrs _glContextAttrs = GLView::getGLContextAttrs();
    
    int tmp[6] = {_glContextAttrs.redBits, _glContextAttrs.greenBits, _glContextAttrs.blueBits,
                           _glContextAttrs.alphaBits, _glContextAttrs.depthBits, _glContextAttrs.stencilBits};


    jintArray glContextAttrsJava = env->NewIntArray(6);
        env->SetIntArrayRegion(glContextAttrsJava, 0, 6, tmp); 
    
    return glContextAttrsJava;
}*/

JNIEXPORT void Java_com_multak_Karaoke_KaraokeLib_nativeOnSurfaceChanged(JNIEnv*  env, jclass thiz, jint w, jint h)
{
    //cocos2d::Application::getInstance()->applicationScreenSizeChanged(w, h);
	android_surfacechanged_init(w, h);
}

}

