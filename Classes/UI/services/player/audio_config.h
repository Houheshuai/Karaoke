/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : audio_config.h
** Revision : 1.00											
**																	
** Description: audio interface config
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
************************ HOWTO *******************************
** 
*/

#ifndef _AUDIO_CONFIG_H_
#define _AUDIO_CONFIG_H_

#include "CP_Audio.h"

#define AUDIO_IF_WIN32					"WIN32"
#define AUDIO_IF_OPENSLES		"OpenSLES"
#define AUDIO_IF_KKEBOX				"KKEBOX"
#define AUDIO_IF_KKEMINI			"KKEMINI"
#define AUDIO_IF_JAVA				"JAVA"
#define AUDIO_IF_AWJAVA				"AWJAVA"

#ifdef __cplusplus
extern "C" {
#endif

extern CP_AudioIFs* audioConfig_initAudioIF(const char* audioIFName);
extern CP_AudioIFs* audioConfig_getAudioIFs(const char* name);
extern CP_AudioIFs* audioConfig_getDefaultAudioIFs(void);
extern int audioConfig_isEmbeddedAudioIFs(void);
extern void audioConfig_getEmbeddedAudioParam(int* inRate, int* outRate, int* inChannels, int* outChannels);
extern void audioConfig_setupIF(int inrate, int outrate, int inchannels, int outchannels);

#ifdef __cplusplus
}
#endif

#endif


