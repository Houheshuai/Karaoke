LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := android_static

LOCAL_MODULE_FILENAME := libmkdandroid

LOCAL_SRC_FILES := \
	JniHelper.cpp	\
	IMEJni.cpp	\
	RendererJni.cpp	\
	TouchesJni.cpp	\
	javaactivity-android.cpp	\
	FileUtils-android.cpp	\

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../.. \

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

LOCAL_CPPFLAGS := -Wno-extern-c-compat

LOCAL_EXPORT_CPPFLAGS := -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)
