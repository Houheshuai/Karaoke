/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : recencoder.h
** Revision : 1.00											
**																	
** Description: rec file encoder module
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
*/

#ifndef _RECENCODER_H_
#define _RECENCODER_H_

#include <lib/ezbase/ez_vector.h>
#include <Lyric/ChaosLyric.h>
#include <Lyric/LyricInfo.h>
#include <ChaosPlayer.h>

/*
*	rec encoder notify
*/
typedef enum {

	RECENCODER_NOTIFY_NONE = 0,

	RECENCODER_NOTIFY_PLAY, 
	RECENCODER_NOTIFY_PAUSED, 
	RECENCODER_NOTIFY_RESUMED, 
	RECENCODER_NOTIFY_STOPPED,

	RECENCODER_NOTIFY_COUNT,
}RecEncoderNotify_et;

/*
* rec encoder event callback
*/
typedef void (*recEncNotifyCallback_t)(void*, int, int, int);

/*
* Rec encoder initilize parameters
*/
typedef struct {
	char										cidKey[12];
	void*									privateKey;
	int										ringFlag;				// 1, PLAYER_RING_MODE_FIRST_LYRIC, 0, PLAYER_RING_MODE_OFF
	int										lameFlag;			// 1, mp3 lame encoder, 0, mp3 shine encoder
	int										latency;
	int										outlatency;
	int										bitrate;
	int										spSound;

	void*									owner;
	recEncNotifyCallback_t 		cb;
	
}RecEncoderInitPara_t;

/*
* Rec encoder encode parameters
*/
typedef struct {
	char 					songName[PLAY_FILE_PATH_SZ];
	char 					singerName[PLAY_FILE_PATH_SZ];
	char 					albumName[PLAY_FILE_PATH_SZ];
	char						filePath[PLAY_FILE_PATH_SZ];
	char						recPath[PLAY_FILE_PATH_SZ];
	char						wavePath[PLAY_FILE_PATH_SZ];
	int 						songIndex;
	int						songType;

	int						EchoVol;
	int						MusVol;
	int						MelodyVol;
	int						ReverbVol;
	int						Key;
	int						Tempo;
	int						RecVol;

	int						mixFlag;
	int						latency;
	int						outLatency;
	
}RecEncoderEncPara_t;

#ifdef __cplusplus
extern "C" {
#endif

extern void* recencoder_init(RecEncoderInitPara_t* para);
extern int recencoder_deinit(void* hdle);
extern int recencoder_create(void* hdle, RecEncoderEncPara_t* para);
extern int recencoder_destroy(void* hdle, int id);
extern int recencoder_pause(void* hdle, int id);
extern int recencoder_resume(void* hdle, int id);
extern int recencoder_stop(void* hdle, int id);
extern int recencoder_getpercent(void* hdle, int id);

#ifdef __cplusplus
}
#endif

#endif

