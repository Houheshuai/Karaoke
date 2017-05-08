# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_LDLIBS    := -llog

LOCAL_MODULE    := KKInput

LOCAL_CPPFLAGS := \
				-D__linux__	\
				-DEGL_NOT_PRESENT \
				-D_POSIX_SOURCE \
				-DDISABLE_PRINT3D	\
				-D__unix	\
				-DKARAOKE_FUNC	\
				-DBRANCH_8168 \
				-DBUILD_OGLES2	\
				-DNO_NETWORK_FUNC \


APP_LOCAL_CPPFLAGS :=  -DPLATFORM_UNIX -DM3D_UI_IS_LOCAL -DPHONE_KARAOKE -D__ANDROID__
APP_LOCAL_CFLAGS :=  -DPLATFORM_UNIX

LOCAL_CPPFLAGS += $(APP_LOCAL_CPPFLAGS)
LOCAL_CFLAGS += $(APP_LOCAL_CFLAGS)

LOCAL_CFLAGS += -Wfatal-errors -fno-short-enums  


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../thirdparty/kkinput \

LOCAL_SRC_FILES :=  kkinput.cpp	\


include $(BUILD_STATIC_LIBRARY)
