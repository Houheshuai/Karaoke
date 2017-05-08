#include "MultakSettings.h"
#include "PVRCore/Log.h"

#ifdef _WIN32
	
#else
#include <jni.h>
extern JavaVM *g_jvm;
extern jclass g_cls_settings;				// class for JavaVideo
extern JNIEnv* getJNIEnv();

jmethodID m_SetDisplayOutputMode;
jmethodID m_SetAudioOutputMode;
jmethodID m_GetAudioOutputMode;
jmethodID m_GetCurDisplayOutputMode;
jmethodID m_IsHdmiMode;
jmethodID m_SetDualScreenMode;
jmethodID m_ResetActivity;
jmethodID m_StartWifiActivity;
#endif

MultakSettings *MultakSettings::p_instance_ = nullptr;

MultakSettings::MultakSettings()
{
#ifdef _WIN32

#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (g_jvm == NULL || g_cls_settings == NULL) {
		pvr::Log(pvr::Log.Information, "MultakSettings not available");
		return;
	}

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}

	m_SetDisplayOutputMode = env->GetStaticMethodID(g_cls_settings, "SetDisplayOutputMode", "(I)V");
	m_SetAudioOutputMode = env->GetStaticMethodID(g_cls_settings, "SetAudioOutputMode", "(I)V");
	m_GetAudioOutputMode = env->GetStaticMethodID(g_cls_settings, "GetAudioOutputMode", "()I");
	m_GetCurDisplayOutputMode = env->GetStaticMethodID(g_cls_settings, "GetCurDisplayOutputMode", "()I");
	m_IsHdmiMode = env->GetStaticMethodID(g_cls_settings, "IsHdmiMode", "()I");
	m_SetDualScreenMode = env->GetStaticMethodID(g_cls_settings, "SetDualScreenMode", "(I)V");
	m_ResetActivity = env->GetStaticMethodID(g_cls_settings, "ResetActivity", "()V");
	m_StartWifiActivity = env->GetStaticMethodID(g_cls_settings, "StartWifiActivity", "()V");
	if (detatch)
		g_jvm->DetachCurrentThread ();

#endif
}

MultakSettings::~MultakSettings()
{
	
}

void MultakSettings::SetVideoOutputMode(enum VideoOutputMode vMode)
{
#ifdef _WIN32

#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}
	
	if(vMode == VideoOutputMode::VideoOutput_NTSC)
	{
		env->CallStaticVoidMethod(g_cls_settings, m_SetDisplayOutputMode, 0);
	}
	else if(vMode == VideoOutputMode::VideoOutput_PAL)
	{
		env->CallStaticVoidMethod(g_cls_settings, m_SetDisplayOutputMode, 1);
	}
	else
	{
		env->CallStaticVoidMethod(g_cls_settings, m_SetDisplayOutputMode, 3);
	}

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}
#endif
}

enum VideoOutputMode MultakSettings::GetVideoOutputMode()
{
#ifdef _WIN32
	return VideoOutputMode::VideoOutput_HDMI;
#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}

	VideoOutputMode ret = VideoOutputMode::VideoOutput_HDMI;

	int videoMode = env->CallStaticIntMethod(g_cls_settings, m_GetCurDisplayOutputMode);
	if(videoMode == 0)
	{
		ret = VideoOutputMode::VideoOutput_NTSC;
	}
	else if(videoMode == 1)
	{
		ret = VideoOutputMode::VideoOutput_PAL;
	}

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}

	return ret;
#endif	
	
}

void MultakSettings::SetAudioOutputMode(enum AudioOutputMode aMode)
{
#ifdef _WIN32

#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;
	int hdmiMode = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}

	hdmiMode = env->CallStaticIntMethod(g_cls_settings, m_IsHdmiMode);

	if(aMode == AudioOutputMode::AudioOutput_HDMI)
	{
		if(hdmiMode == 1)
		{
			env->CallStaticVoidMethod(g_cls_settings, m_SetAudioOutputMode, 1);
		}
		else
		{
			env->CallStaticVoidMethod(g_cls_settings, m_SetAudioOutputMode, 0);
		}
	}
	else if(aMode == AudioOutputMode::AudioOutput_Codec)
	{
		env->CallStaticVoidMethod(g_cls_settings, m_SetAudioOutputMode, 0);
	}

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}
#endif	

}

enum AudioOutputMode MultakSettings::GetAudioOutputMode()
{
#ifdef _WIN32

	return AudioOutputMode::AudioOutput_HDMI;
#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}

	AudioOutputMode ret = AudioOutputMode::AudioOutput_Codec;

	int audioMode = env->CallStaticIntMethod(g_cls_settings, m_GetAudioOutputMode);
	if(audioMode == 1)
	{
		ret = AudioOutputMode::AudioOutput_HDMI;
	}

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}

	return ret;
#endif
}

void MultakSettings::SetDualScreenMode(enum ScreenMode sMode)
{
#ifdef _WIN32

#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}
	
	env->CallStaticVoidMethod(g_cls_settings, m_SetDualScreenMode, sMode);
	//Reset
	env->CallStaticVoidMethod(g_cls_settings, m_ResetActivity);

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}
#endif

}

void MultakSettings::ResetActivity()
{
#ifdef _WIN32
	pvr::Log(pvr::Log.Information, "MultakSettings ResetActivity");
#else
	JNIEnv* env = getJNIEnv();
	int detatch = 0;

	if (env == NULL) {
		detatch = 1;
		g_jvm->AttachCurrentThread (&env, NULL);
	}

	env->CallStaticVoidMethod(g_cls_settings, m_ResetActivity);

	if (detatch) {
		g_jvm->DetachCurrentThread ();
	}

#endif

}