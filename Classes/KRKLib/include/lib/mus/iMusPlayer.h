/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MediaPlayer.h
** Revision : 1.00											
**																	
** Description: Picture Player module
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

#ifndef _IMUSLAYER_H_
#define _IMUSLAYER_H_

#include <lib/ezbase/ez_player.h>
#include "iLyric.h"
#include "iStaff.h"
#include "iMusConfig.h"
#include "iCDGLyric.h"

/*
*	mus player control commands
*/
typedef enum {

	MUSPLAYER_CMD_DUMMY = EZPLAYER_CMD_NONE + 0x1000,

	MUSPLAYER_CMD_SETMICPARA,				/* set system para*/
	MUSPLAYER_CMD_SETLYRIC,					/* set lyric on off */
	MUSPLAYER_CMD_SHOWTITLEINF,			/* show title on off */
	MUSPLAYER_CMD_SETIFUN,					/* set ifun on off */
	MUSPLAYER_CMD_SETSCORE,					/* set score on off */
	
}MusPlayerCmd_et;

/*
*	player notify
*/
typedef enum {

	MUSPLAYER_NOTIFY_NONE = EZPLAYER_NOTIFY_NONE + 0x1000,

	MUSPLAYER_NOTIFY_SETMICPARA, 			/* set mic para */
	MUSPLAYER_NOTIFY_SETLYRIC,					/* set lyric on off */
	MUSPLAYER_NOTIFY_SHOWTITLEINF,		/* show title on off */
	MUSPLAYER_NOTIFY_SETIFUN,					/* set ifun on off */
	MUSPLAYER_NOTIFY_SETSCORE,					/* set score on off */
	MUSPLAYER_NOTIFY_TITLEINF_BEGIN,		/* start to show song title */
	MUSPLAYER_NOTIFY_TITLEINF_END,			/* start to hide song title */
	MUSPLAYER_NOTIFY_INTERLUDE_BEGIN, 	/* start interlude */
	MUSPLAYER_NOTIFY_INTERLUDE_END, 		/* end interlude */
	MUSPLAYER_NOTIFY_ENDLUDE_BEGIN, 	/* start endlude */
	MUSPLAYER_NOTIFY_PRELUDE_END, 		/* end prelude */
	MUSPLAYER_NOTIFY_AUTOSEEK_BEGIN, 	/* start to seek chapter */
	MUSPLAYER_NOTIFY_AUTOSEEK_END,			/* finish seek chapter */
	MUSPLAYER_NOTIFY_AUTOSEEK_LAST,			/* last chapter, can not seek */
	MUSPLAYER_NOTIFY_AUTOSEEK_ERR,		/* seek error */
	MUSPLAYER_NOTIFY_STAFFSHOW, 			/* staff displaying */
	MUSPLAYER_NOTIFY_STAFFHIDE, 				/* staff hide */
	MUSPLAYER_NOTIFY_SETLYRICALIGN,					/* set lyric align type */
	MUSPLAYER_NOTIFY_SETLYRICEFFECT, 				/* set lyric draw effect */
	MUSPLAYER_NOTIFY_LYRICCHANGE,				/* lyric string changed */
	MUSPLAYER_NOTIFY_LYRICPERCENT,			/* get lyric brush percentage */
	MUSPLAYER_NOTIFY_LATENCYVALUE,			/* get lyric brush percentage */
	MUSPLAYER_NOTIFY_SAVE_FILE,			/* end of save online file notify */
	MUSPLAYER_NOTIFY_SEEK_TIME,	/* seek time */

	MUSPLAYER_NOTIFY_INIT_VIEW,		/* init view */
	MUSPLAYER_NOTIFY_DEINIT_VIEW, 	/* deinit view */

	MUSPLAYER_NOTIFY_STAFF_ADDSEG, 	/* staff add segment */
	MUSPLAYER_NOTIFY_DRAW_HINTBALL,	/* draw hint ball */
	MUSPLAYER_NOTIFY_CLEAR_HINTBALL,	/* clear hint ball */
	MUSPLAYER_NOTIFY_LYRIC_LOADED,		/* lyric loaded */
	//............
	MUSPLAYER_NOTIFY_SEND_SEXTYPE,
	//............

	MUSPLAYER_NOTIFY_COUNT,
}MusPlayerNotify_et;

/*
*	player song mode
*/
typedef enum {
	MusPlayMode_Song,
	MusPlayMode_Rec,
	
}MusPlayMode_et;

/*
*	player score level
*/
typedef enum {
	MusScoreLevel_Easy = 0,
	MusScoreLevel_Normal,
	MusScoreLevel_Hard,
}MusScoreLevel_et;

/*
*	player score set option
*/
typedef enum {
	MusScoreSet_OnOff = 0,
	MusScoreSet_Level,
	MusScoreSet_AdjustCB,
}MusScoreSet_et;

/*
*	player ifun set option
*/
typedef enum {
	MusIfunSet_OnOff = 0,
	MusIfunSet_View,
	MusIfunSet_Num,
	
}MusIfunSet_et;

/*
*	set ifun parameter
*/
typedef struct 
{
	short								optionType;							/* 0: left channel is vocal or stream No.0 is vocal, >0: right channel or channel No.X */
	short								value;										/* see 'ezPlayerVocalOption_et' */

} ezSetIfunPara_t;

/*
*	set EQ Freq parameter
*/
typedef struct 
{
	short								Type;										/* EQ Freq Type */
	short								value;										/* EQ Rreq Value */

} ezSetEQPara_t;

typedef struct
{
	int		cheeroption;
	int		cheervalue[4];
}ezSetCheerPara_t;

typedef struct {
	int 		Xkey;
	int		EncodeBytes;
}ezSetEncodeinf_t;

typedef struct
{
	char 						songName[PLAY_FILE_PATH_SZ];
	char							filePath[PLAY_FILE_PATH_SZ];
	char							savePath[PLAY_FILE_PATH_SZ];
	unsigned int			filesize;
	char							recPath[PLAY_FILE_PATH_SZ];
#ifdef WIN32
	char							ifunPath[PLAY_FILE_PATH_SZ];
#endif
	int 							songIndex;
	int							playMode;		// see. MusPlayMode_et
	int							scoreLevel;		// see. MusScoreLevel_et
	int							songType;
	int							recOn;
	int							staffOn;
	int							scoreOn;
	int							lyricOn;
	char							cidKey[12];
	void*						privateKey;
	int							okfProductID;
	int							MukSubFileType;
	int							mixMode;		// mix mp3 & rec
	int							recFmt;			// 0 -adpcm, 1-sbc, 3-mp3, 4-aac
	int							recEncFmt;			// 0 -adpcm, 1-sbc, 3-mp3, 4-aac
	int							recIndex;
	char						filePathext[PLAY_FILE_PATH_SZ];
}iMusPlayerSongInfo_st;

typedef struct
{
	char							recPath[PLAY_FILE_PATH_SZ];
	int							accomVol;
	int							recVol;
	int							echoVol;
	int							reverb;
	int							latency;
	
} iMusPlayerRecFileAudioConfig_st;

/*
* mus score parameter
*/
typedef struct {

	MusScoreSet_et setOption;
	int value;
		
} iMusPlayerScorePara_t;

/*
* mus player parameter for playing
*/
typedef struct {

	iMusPlayerSongInfo_st songInfo;
	char							micbypass;
	int							seekFlag;
	int							titlestate;
	short						interlude_lyric;
	short						interlude_staff;
	void*						extParam;
	
	MULTAK_LYRIC*		lyricHdle;
	MULTAK_STAFF*	staffHdle;
	void *						playerHdle;
	void *						effectPlayerHdle;
	void *						audioHdle;
	void *						audioIF;
	void *						drawMutex;		// lyric and staff don't draw at same time, for staff smooth
	void *						drawBgMutex;	// lyric and staff draw bg mutex, staff bg and lyric titles area is overlap
	void *						interludeMutex; // lyric and staff interlude callback mutex
	void *						playerRes;			// player resource handle
	void *						lyricInf;				// lyric info from alter load callback
	ezNotifyHandle_t*	cpNotify;			// chaosplayer notify
	ezNotifyHandle_t*	effNotify;			// effect music notify
	
	int 							isExtMidi;			// 1 - ext midi, 0 - internel midi
	int 							disableLyric; 	//disable lyric when play start
	int 							disableStaff; 	//disable staff when play start
	int 							staffNum; 	//	1-single player, 2-2 player
	int 							inLatency;		// audio input latency
	int 							outLatency; // audio output latency
	int 							inRate; // audio in samplerate 
	int 							outRate; // audio out samplerate 
	int 							inChannel; // audio in channels 
	int 							outChannel; // audio out channels 
	int							auto_samplerate;		// auto set player sample rate according to song sample rate
	int							okfProduceID;
	int							fastMode;
	int							audioIFExt; // control audio IF init&deinit externel
	int							stopWait;// wait sub module stop
	int							deinitWait;// don't do anything when deinit
	int							score;
	int							seperateUpdate;
	int							updateThreadid;
	int							viewReady;
	int							spSound;
	int							effectPlayState;
	
	int 						enableCDGRender; 	//enable cdg render
	int							fontNumber;
} iMusPlayerPlayPara_t;

/*
* mus player externel input configuration
*/
typedef struct {
	char									resFile[PLAY_FILE_PATH_SZ];		// if set by res file, lyric&staff show parameter dont' need to set
	int									UILanguage;
	void*								audioIF;
	void*								audioHandle;
	int									visible; // 0-don't display staff&lyric, but staff&lyric info is analysised, 1-display
	
} iMusPlayerExtConfig_t;

/*
* mus player derive record input parameters
*/
typedef struct {
	char 					songName[PLAY_FILE_PATH_SZ];
	char 					singerName[PLAY_FILE_PATH_SZ];
	char 					albumName[PLAY_FILE_PATH_SZ];
	int 						songIndex;
	int						songType;
	char						filePath[PLAY_FILE_PATH_SZ];
	char						recPath[PLAY_FILE_PATH_SZ];
	char						wavePath[PLAY_FILE_PATH_SZ];
	unsigned int		filesize;
	char						cidKey[12];
	void*					privateKey;
	int						ringFlag;				// 1, PLAYER_RING_MODE_FIRST_LYRIC, 0, PLAYER_RING_MODE_OFF
	int						lameFlag;			// 1, mp3 lame encoder, 0, mp3 shine encoder
	int						mixFlag;
	
	int						EchoVol;
	int						MusVol;
	int						MelodyVol;
	int						ReverbVol;
	int						Key;
	int						Tempo;
	int						RecVol;
	int						BitRate;
	int						spSound;
}iMusPlayerRecordDerived_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: _MusPlayerInitView
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - error code
 * Description    	: initialize lyric & staff display
 *					
*/
extern int _MusPlayerInitView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerFreeView
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize lyric & staff
 *					
*/
extern int _MusPlayerFreeView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerSetSeperateUpdate
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set mus view update method
 *					
*/
extern int _MusPlayerSetSeperateUpdate(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerSetViewVisible
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set mus view visible
 *					
*/
extern int _MusPlayerSetViewVisible(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerInit
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Mus player object
 *					
*/
extern int _MusPlayerInit(ezPlayer_t* player);

/*
 * Function name  	: _MusPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Mus player object
 *					
*/
extern void _MusPlayerDeInit(ezPlayer_t* player);

/*
 * Function name  	: _MusPlayerPlay
 * Arguments      	: player - input player 
 *									filePath - file full path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play media file
 *					
*/
extern int _MusPlayerPlay(ezPlayer_t* player, void* para);


/*
 * Function name  	: _MusPlayerStop
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
extern int _MusPlayerStop(ezPlayer_t* player);


/*
 * Function name  	: _MusPlayerPause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
extern int _MusPlayerPause(ezPlayer_t* player);


/*
 * Function name  	: _MusPlayerResume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MusPlayerResume(ezPlayer_t* player);

/*
 * Function name  	: _MusPlayerUpdate
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update mus
 *					
*/
extern void _MusPlayerUpdate(ezPlayer_t* player, unsigned int timeElapsed);

/*
 * Function name  	: _MusPlayerUpdateView
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update mus view
 *					
*/
extern int _MusPlayerUpdateView(ezPlayer_t* player, void* iPara);

/*
 * Function name  	: _MusPlayerSetVol
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set volume
 *					
*/
extern int _MusPlayerSetVol(ezPlayer_t* player, void * para);
extern int _MusPlayerSetMute(ezPlayer_t* player, void * para);
extern int _MusPlayerSetVocal(ezPlayer_t* player, void * para);
extern int _MusPlayerSetMicPara(ezPlayer_t* player, void * para);
extern int _MusPlayerSetLyric(ezPlayer_t* player, void * para);
extern int _MusPlayerSetLyricAlign(ezPlayer_t* player, void * para);
extern int _MusPlayerSetLyricDrawEffect(ezPlayer_t* player, void * para);
extern int _MusPlayerShowTitleInf(ezPlayer_t* player, void * para);
extern int _MusPlayerSetIfun(ezPlayer_t* player, void * para);
extern int _MusPlayerSetScore(ezPlayer_t* player, void * para);
extern int _MusPlayerAutoSeek(ezPlayer_t* player, void * para);
extern int _MusPlayerDerivedRecord(ezPlayer_t* player, void * para);
extern int _MusPlayerGetRecordderivedPercent(ezPlayer_t* player, void * para);
extern int _MusPlayerPlayMedia (ezPlayer_t* player, void * para);
extern int _MusPlayerSeekTime(ezPlayer_t* player, void * para);
extern int _MusPlayerGetPlayTime(ezPlayer_t* player, void * para);
extern int _MusPlayerGetTotalTime(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerSetStaffEnabled
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set mus staff module enabled
 *					
*/
extern int _MusPlayerSetStaffEnabled(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerSetLyricEnabled
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set mus lyric module enabled
 *					
*/
extern int _MusPlayerSetLyricEnabled(ezPlayer_t* player, void* para);
extern int _MusPlayerSetLyricFont(ezPlayer_t* player, void* para);

extern int _MusPlayerSetSongType(ezPlayer_t* player, void * para);
extern int _MusPlayerSetFileParseType(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerGetLyricAlign
 * Arguments      	: player - input player 
 *									
 * Return         	: lyric align type
 * Description    	: get lyric align type
 *					
*/
extern int _MusPlayerGetLyricAlign (ezPlayer_t* player, int dummy);
extern int _MusPlayerGetLyricDrawEffect (ezPlayer_t* player, int dummy);

/*
 * Function name  	: _MusPlayerGetLyricShowPara
 * Arguments      	: player - input player 
 *									
 * Return         	: lyric show parameters
 * Description    	: get lyric show parameters
 *					
*/
extern int _MusPlayerGetLyricShowPara (ezPlayer_t* player, int dummy);

/*
 * Function name  	: _MusPlayerGetLyricInfo
 * Arguments      	: player - input player 
 *									
 * Return         	: 0-succ, <>0-fail
 * Description    	: get lyric realtime info
 *					
*/
extern int _MusPlayerGetLyricInfo (ezPlayer_t* player, void* para);

/*
 * Function name  	: _MusPlayerGetLyricLineInfo
 * Arguments      	: player - input player 
 *									
 * Return         	: 0-succ, <>0-fail
 * Description    	: get lyric line info by line number
 *					
*/
extern int _MusPlayerGetLyricLineInfo (ezPlayer_t* player, LYRIC_SHOW_INFO_LYRIC_INFO* pinf);

/*
 * Function name  	: _MusPlayerGetStaffInfo
 * Arguments      	: player - input player 
 *									
 * Return         	: 0-succ, <>0-fail
 * Description    	: get staff realtime info
 *					
*/
extern int _MusPlayerGetStaffInfo (ezPlayer_t* player, IFUN_DISPLAY_INFO* pinf);

/*
 * Function name  	: _MusPlayerGetStaffShowPara
 * Arguments      	: player - input player 
 *									
 * Return         	: staff show parameters
 * Description    	: get staff show parameters
 *					
*/
extern int _MusPlayerGetStaffShowPara (ezPlayer_t* player, int dummy);

/*
 * Function name  	: _MusPlayerGetBufferingFlag
 * Arguments      	: player - input player 
 *									
 * Return         	: 0 - no buffering, 1 - buffering
 * Description    	: get staff show parameters
 *					
*/
extern int _MusPlayerGetBufferingFlag (ezPlayer_t* player, int dummy);

/*
 * Function name  	: _MusPlayerGetScore
 * Arguments      	: player - input player 
 *					
 * Return         	: score value
 * Description    	: get score value
 *					
*/
extern int _MusPlayerGetScore(ezPlayer_t* player, int para);

/*
 * Function name  	: _MusPlayerEnableEffectMusic
 * Arguments      	: player - input player 
 *									para - input music file path
 * Return         	: 
 * Description    	: enable effect music player
 *					
*/
extern int _MusPlayerEnableEffectMusic (ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerPlayEffectMusic
 * Arguments      	: player - input player 
 *									para - input music file path
 * Return         	: 
 * Description    	: play effect music, like applause wave
 *					
*/
extern int _MusPlayerPlayEffectMusic (ezPlayer_t* player, void * para);
/*
 * Function name  	: _MusPlayerPlayCheerEffect
 * Arguments      	: player - input player 
 *					para start/end  EQ Value
 * Return         	: 
 * Description    	: play cheer effect 
 *					
*/
extern int _MusPlayerPlayCheerEffect (ezPlayer_t* player,void*para);

/*
 * Function name  	: _MusPlayerSetSoundEffect
 * Arguments      	: player - input player 
 *									para - input music file path
 * Return         	: 
 * Description    	: set sound effect
 *					
*/
extern int _MusPlayerSetSoundEffect (ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerSetEQFreq
 * Arguments      	: player - input player 
 *									para - EQ parameter, {Type, Value}
 * Return         	: 
 * Description    	: set EQ
 *					
*/
extern int _MusPlayerSetEQFreq (ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerGetEQFreq
 * Arguments      	: player - input player 
 *									EQType - EQ type
 * Return         	: EQ value
 * Description    	: get EQ
 *					
*/
extern int _MusPlayerGetEQFreq (ezPlayer_t* player, int EQType);

/*
 * Function name  	: _MusPlayerGetDefaultQJ_ID
 * Arguments      	: player - input player 
 *									
 * Return         	: tonemake
 * Description    	: get QJ_ID
 *					
*/

extern int _MusPlayerGetDefaultQJ_ID (ezPlayer_t* player, int para);
/*
 * Function name  	: _MusPlayerSetEncodeInfo
 * Arguments      	: player - input player 
 *				  para -encodeinf
 * Return         	: 
 * Description    	: set EQ
 *					
*/
extern int _MusPlayerSetEncodeInfo(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerTestLatency
 * Arguments      	: player - input player 
 *				  para -encodeinf
 * Return         	: 
 * Description    	: test audio hardware latency
 *					
*/
extern int _MusPlayerTestLatency(ezPlayer_t* player, void * para);
extern int _MusPlayerExtMidiEnable(ezPlayer_t* player, void * para);
extern int _MusPlayerExtMidiReset(ezPlayer_t* player, void* para);
extern int _MusPlayerSetSPSoundEffect(ezPlayer_t* player, void* para);
extern int _MusPlayerSetRecFileAudioConfig(ezPlayer_t* player, void* para);
extern int _MusPlayerGetRecFileAudioConfig(ezPlayer_t* player, void* para);


#if 0
/*
 * Function name  	: _MusPlayerSetXKey
 * Arguments      	: player - input player 
 *				  para -x_key
 * Return         	: 
 * Description    	: set EQ
 *					
*/
extern int _MusPlayerSetXKey (ezPlayer_t* player, void * para);

/*
 * Function name  	: _MusPlayerSetEncodeBytes
 * Arguments      	: player - input player 
 *				  para -encodebytes
 * Return         	: 
 * Description    	: set EQ
 *					
*/
extern int _MusPlayerSetEncodeBytes (ezPlayer_t* player, void * para);
#endif
#ifdef __cplusplus
}
#endif

#endif

