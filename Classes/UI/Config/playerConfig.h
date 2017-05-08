#ifndef _PLYAER_CONFIG_H_
#define _PLYAER_CONFIG_H_

#include <api/MusPlayer.h>
#include <api/TextPlayer.h>

#ifndef _WIN32
//#define PLAY_MUS_RAMFILE
#endif

// title&info colors
#define LYRIC_TITLE_COLOR							0xFFFFFFFF
#define LYRIC_TITLE_FRAME_COLOR			0x000000FF

#define LYRIC_INFO_COLOR							LYRIC_TITLE_COLOR
#define LYRIC_INFO_FRAME_COLOR			LYRIC_TITLE_FRAME_COLOR

// lyric color
#define LYRIC_NORMAL_COLOR					LYRIC_TITLE_COLOR
#define LYRIC_NORMAL_FRAME_COLOR		LYRIC_TITLE_FRAME_COLOR

#define LYRIC_MALE_BRUSH_COLOR							0x569CE3FF//0x0A3174FF
#define LYRIC_MALE_FRAME_BRUSH_COLOR			0xFFFFFFFF

#define LYRIC_FEMALE_BRUSH_COLOR						0xB01E00FF//0xFF005AFF
#define LYRIC_FEMALE_FRAME_BRUSH_COLOR		0xFFFFFFFF

#define LYRIC_CHORUS_BRUSH_COLOR					0x00C13FFF//0x006A00FF
#define LYRIC_CHORUS_FRAME_BRUSH_COLOR	0xFFFFFFFF

#define LYRIC_NOMALE_BRUSH_COLOR					LYRIC_MALE_BRUSH_COLOR//0x006A00FF
#define LYRIC_NOMALE_FRAME_BRUSH_COLOR		LYRIC_MALE_FRAME_BRUSH_COLOR

// lyric align default side to side
#define LYRIC_UP_ALIGN			1
#define LYRIC_DOWN_ALIGN 	3

// lyric height in 720p 
#define LYRIC_HEIGHT_720P_L4		64
#define LYRIC_LABEL_HEIGHT_720P_L4		51
#define LYRIC_HEIGHT_720P_L2	80
#define LYRIC_LABEL_HEIGHT_720P_L2		2

// lyric height in 480p 
#define LYRIC_HEIGHT_480P_L4		36
#define LYRIC_LABEL_HEIGHT_480P_L4		30
#define LYRIC_HEIGHT_480P_L2		48
#define LYRIC_LABEL_HEIGHT_480P_L2		2

#define PK_VIEW_H 0
#define PK_VIEW_V 1

#ifdef __cplusplus
extern "C" {
#endif

extern void* getMusPlayerPrivateKey(unsigned int customer);

extern void setMusPlayerByConfigFile(int DisplayOptionType);

extern iMusPlayerExtConfig_t *getMusPlayerConfigInfo(int DisplayOptionType);

extern TextPlayerDisplayPara_t *getTextPlayerConfigInfo(int DisplayOptionType);

#ifdef __cplusplus
}
#endif

#endif
