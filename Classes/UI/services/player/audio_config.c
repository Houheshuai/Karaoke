/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : audio_config.cpp
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

#include <k_global.h>
#include "audio_config.h"

//#include <kkedev/kkedev_audio_if.h>

//----------------------------------------------------------------------------//
//- audio interfaces map 
//----------------------------------------------------------------------------//
typedef struct tagAudioIFMap
{
	const char* 				name;
	CP_AudioIFs*				IFs;
	int								inRate;
	int								outRate;
	int								inChannels;
	int								outChannels;
	int								latency;
	
} AudioIFMap_t;

#ifdef _ANDROID_PLATFORM_

#define AUDIO_IF_DEFAULT		AUDIO_IF_JAVA

//----------------------------------------------------------------------------//

#include "OpenSLESAudio.h"

CP_AudioIFs gOpenSLESAudioIFs = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

//----------------------------------------------------------------------------//

//#include "AndroidJavaAudio.h"
#include "AWJavaAudio.h"

extern JavaVM *g_jvm;
extern jclass g_cls_jaudio;

static ANDROID_JAVA_AUDIO_PARAM JAVAAudioParam;

void AndroidJavaAudio_SetParam(ANDROID_JAVA_AUDIO_PARAM* param)
{
	JAVAAudioParam = *param;
}

ANDROID_JAVA_AUDIO_PARAM* AndroidJavaAudio_GetParam(void)
{
	return &JAVAAudioParam;
}

int AndroidJavaAudio_GetInRate(void)
{
	return JAVAAudioParam.InSampleRate;
}

int AndroidJavaAudio_GetInChannel(void)
{
	return JAVAAudioParam.InChannels;
}

AUDIO_HANDLE AWJavaAudio_Init_ex (int samplerate)
{
	mus_printf("AndroidJavaAudio_Init, inrate=%d, outrate=%d, inchannels=%d, outchannels=%d\n", JAVAAudioParam.InSampleRate, JAVAAudioParam.OutSampleRate, JAVAAudioParam.InChannels, JAVAAudioParam.OutChannels);
	return AWJavaAudio_Init(&JAVAAudioParam);
}

CP_AudioIFs gJAVAAudioIFs = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

CP_AudioIFs gKKBoxAudioIFs = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

CP_AudioIFs gKKMiniAudioIFs = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

CP_AudioIFs gAWJavaAudioIFs = 
{
	AWJavaAudioIn_Open,
	AWJavaAudioIn_Close,
	AWJavaAudioIn_Read,
	AWJavaAudioOut_Open,
	AWJavaAudioOut_Close,
	AWJavaAudioOut_Write,
	AWJavaAudio_Init_ex,
	AWJavaAudio_Finish,
	AWJavaAudio_Set,
};

//----------------------------------------------------------------------------//
//- MAP
//----------------------------------------------------------------------------//
AudioIFMap_t gAudioIFMap[] = 
{
	{AUDIO_IF_OPENSLES, &gOpenSLESAudioIFs, 48000, 48000, 2, 2, 100},
	{AUDIO_IF_JAVA, &gJAVAAudioIFs, 48000, 48000, 2, 2, 100},		
	{AUDIO_IF_KKEBOX, &gKKBoxAudioIFs, 48000, 48000, 1, 2, 100},		
	{AUDIO_IF_KKEMINI, &gKKMiniAudioIFs, 48000, 48000, 1, 2, 100},		
	{AUDIO_IF_AWJAVA, &gAWJavaAudioIFs, 48000, 48000, 1, 2, 100},	
};

/*#include <platforms.h>

typedef struct {
	const char* name;
	AudioRegistry_t* reg;
	
} EmbededAudioRegistry_t;

AudioRegistry_t* curEmbededAudio = NULL;

CP_AudioIFs gEmbeddedAudioIFs = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

#ifdef _HIMEDIA_AUDIO_
extern AudioRegistry_t himediaAudioMode;
#endif
extern AudioRegistry_t diyomateAudioMode;
extern AudioRegistry_t meleAudioMode;
extern AudioRegistry_t wxjcAudioMode;
extern AudioRegistry_t ymlAudioMode;
extern AudioRegistry_t TMAudioMode;
extern AudioRegistry_t lenovoMTKAudioMode;

EmbededAudioRegistry_t gEmbeddedAudio[] = 
{
#ifdef _HIMEDIA_AUDIO_
	{"HIMEDIA", &himediaAudioMode},
#endif		
	{"MAILE", &meleAudioMode},
	{"DIYOMATE", &diyomateAudioMode},
	{"WXJC", &wxjcAudioMode},
	{"YML", &ymlAudioMode},
	{"LENOVOMTK", &lenovoMTKAudioMode},
#ifdef _TM_AUDIO_		
	{"TMBOX", &TMAudioMode},
#endif		
};

#elif defined _MELIS_PLATFORM_

#define AUDIO_IF_DEFAULT		AUDIO_IF_F20

#include "F20Audio.h"

CP_AudioIFs gF20AudioIFs = 
{
	F20AudioIn_Open,
	F20AudioIn_Close,
	F20AudioIn_Read,
	F20AudioOut_Open,
	F20AudioOut_Close,
	F20AudioOut_Write,
	F20Audio_Init,
	F20Audio_Finish,
	F20Audio_Set,
#ifdef WM2420
	NULL,
	NULL,
	NULL,
#else
	F20AudioNote_Open,
	F20AudioNote_Close,
	F20AudioNote_Read,
#endif	
};

//----------------------------------------------------------------------------//
//- MAP
//----------------------------------------------------------------------------//
AudioIFMap_t gAudioIFMap[] = 
{
	{AUDIO_IF_F20, &gF20AudioIFs, 32000, 32000, 2, 2, 100},
};
*/

#else

#define AUDIO_IF_DEFAULT				AUDIO_IF_WIN32

#include "Win32Audio.h"
static AUDIO_HANDLE _Win32Audio_Init (int samplerate)
{
	return Win32Audio_Init();
}

CP_AudioIFs gWin32AudioIFs = 
{
	Win32AudioIn_Open,
	Win32AudioIn_Close,
	Win32AudioIn_Read,
	Win32AudioOut_Open,
	Win32AudioOut_Close,
	Win32AudioOut_Write,
	_Win32Audio_Init,
	Win32Audio_Finish,
	NULL,
};

CP_AudioIFs gKKBoxAudioIFs = 
{
// 	KKEAudioSrcOpen,
// 	KKEAudioSrcClose,
// 	KKEAudioSrcRead,
// 	Win32AudioOut_Open,
// 	Win32AudioOut_Close,
// 	Win32AudioOut_Write,
// 	NULL,
// 	NULL,
// 	KKEAudio_Set,
// 	NULL,
// 	NULL,
 	NULL,
};

CP_AudioIFs gKKMiniAudioIFs = 
{
// 	KKEAudioSrcOpen,
// 	KKEAudioSrcClose,
// 	KKEAudioSrcRead,
// 	KKEAudioSinkOpen,
// 	KKEAudioSinkClose,
// 	KKEAudioSinkWrite,
// 	KKEAudio_Init,
// 	KKEAudio_Finish,
// 	KKEAudio_Set,
// 	NULL,
// 	NULL,
 	NULL,
};
//----------------------------------------------------------------------------//
//- MAP
//----------------------------------------------------------------------------//
AudioIFMap_t gAudioIFMap[] = 
{
	{AUDIO_IF_WIN32, &gWin32AudioIFs, 48000, 48000, 2, 2, 100},
	{AUDIO_IF_KKEBOX, &gKKBoxAudioIFs, 48000, 48000, 1, 2, 100}, 	
	{AUDIO_IF_KKEMINI, &gKKMiniAudioIFs, 48000, 48000, 1, 2, 100}, 	
};
#endif

//----------------------------------------------------------------------------//
CP_AudioIFs* audioConfig_initAudioIF(const char* audioIFName)
{
	CP_AudioIFs* audioIF = NULL;
	
#ifdef _ANDROID_PLATFORM_
	ANDROID_JAVA_AUDIO_PARAM* pparam = AndroidJavaAudio_GetParam();
	ANDROID_JAVA_AUDIO_PARAM param = *pparam;
	param.Jvm = g_jvm;
	param.Class = g_cls_jaudio;
	AndroidJavaAudio_SetParam(&param);
#endif		
		
	if (audioIFName != NULL)
		audioIF = audioConfig_getAudioIFs(audioIFName); 	
	
	return audioIF;
}

//----------------------------------------------------------------------------//
CP_AudioIFs* audioConfig_getAudioIFs(const char* name)
{
	int i;

	for (i=0; i<sizeof(gAudioIFMap)/sizeof(AudioIFMap_t); i++)
	{
		if (stricmp(gAudioIFMap[i].name, name) == 0)
			return gAudioIFMap[i].IFs;
	}

/*#ifdef _ANDROID_PLATFORM_
	
	for (i=0; i<sizeof(gEmbeddedAudio)/sizeof(EmbededAudioRegistry_t); i++)
	{
		if (stricmp(gEmbeddedAudio[i].name, name) == 0) 
		{
			AudioRegistry_t* pAudio = gEmbeddedAudio[i].reg;
			CP_AudioIFs* pAudioIf = &gEmbeddedAudioIFs;
			pAudioIf->init = pAudio->init;
			pAudioIf->finish = pAudio->finish;
			pAudioIf->srcopen = pAudio->inopen;
			pAudioIf->srcclose = pAudio->inclose;
			pAudioIf->srcread = pAudio->inread;
			pAudioIf->sinkopen = pAudio->outopen;
			pAudioIf->sinkclose = pAudio->outclose;
			pAudioIf->sinkwrite = pAudio->outwrite;
			pAudioIf->setAudio = pAudio->set;
			curEmbededAudio = pAudio;
			if (pAudio->check() != 0) // auth fail
				pAudioIf = NULL;
			else
				audin_printf("get embedded audio IF: %s\n", name);
			return pAudioIf;
		}
	}

#endif*/

	return audioConfig_getDefaultAudioIFs();
}

//----------------------------------------------------------------------------//
int audioConfig_isEmbeddedAudioIFs(void)
{
/*#ifdef _ANDROID_PLATFORM_
	if (gEmbeddedAudioIFs.init != NULL)
		return true;
	else
		return false;
#else
	return false;
#endif*/
	return false;
}

//----------------------------------------------------------------------------//
void audioConfig_getEmbeddedAudioParam(int* inRate, int* outRate, int* inChannels, int* outChannels)
{
/*#ifdef _ANDROID_PLATFORM_

	if (curEmbededAudio != NULL)
	{
		AudioRegistry_t* pAudio = curEmbededAudio;
		pAudio->request(WHICH_IN_SAMPLERATE, inRate);
		pAudio->request(WHICH_OUT_SAMPLERATE, outRate);
		pAudio->request(WHICH_IN_CHANNELNUM, inChannels);
		pAudio->request(WHICH_OUT_CHANNELNUM, outChannels);
	}

#endif*/
}

//----------------------------------------------------------------------------//
CP_AudioIFs* audioConfig_getDefaultAudioIFs(void)
{
	int i;

	for (i=0; i<sizeof(gAudioIFMap)/sizeof(AudioIFMap_t); i++)
	{
		if (stricmp(gAudioIFMap[i].name, AUDIO_IF_DEFAULT) == 0)
			return gAudioIFMap[i].IFs;
	}
	return NULL;
}

//----------------------------------------------------------------------------//
void audioConfig_setupIF(int inrate, int outrate, int inchannels, int outchannels)
{
#ifdef _ANDROID_PLATFORM_
	ANDROID_JAVA_AUDIO_PARAM* pparam = AndroidJavaAudio_GetParam();
	ANDROID_JAVA_AUDIO_PARAM param = *pparam;

	if (inchannels != -1) param.InChannels = inchannels;
	if (outchannels != -1) param.OutChannels = outchannels;
	if (inrate != -1) param.InSampleRate = inrate;
	if (outrate != -1) param.OutSampleRate = outrate;
	AndroidJavaAudio_SetParam(&param);
#endif

	mus_printf("audioConfig_setupIF, inrate=%d, outrate=%d, inchannels=%d, outchannels=%d\n", inrate, outrate, inchannels, outchannels);
}

