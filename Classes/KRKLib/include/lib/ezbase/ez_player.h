/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_player.h
** Revision : 1.00											
**																	
** Description: basic player functions, support multi-thread
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
**	if you define [ ezPlayer_t* player],  call function [ez_playerNew] to create it
**	if you define [ ezPlayer_t player],  call function [ez_playerInit] to initialize it, don't need [ez_playerNew]
**	call [ez_playerFree] to release resources in [ez_playerNew]
**	call [ez_playerDeinit] to release resources in [ez_playerInit]
**	
*/

#ifndef _EZPLAYER_H_
#define _EZPLAYER_H_

#include <k_define.h>
#include <lib/ezbase/ez_notify.h>

/* 
* 5s time out for waiting player notify in sync mode 
*/
#define PLAYER_NOTIFY_TIMEOUT				10000		

/*
* the maximum full path string length of input play file
*/
#define PLAY_FILE_PATH_SZ						256

/*
* maximum integer parameter count
*/
#define PLAY_INTPARA_CNT							8

/*
* fast convert from customized player to ezPlayer
*/
#define ezPlayer(player) 								((ezPlayer_t*)player)

typedef enum {

	EZPLAYER_SUCC = KRK_RET_SUCC,
	EZPLAYER_ERROR = KRK_RET_ERR,
	
} ezPlayerReturn_et;

/*
*	player state
*/
typedef enum {

	EZPLAYER_STATE_DUMMY = -1,
	EZPLAYER_STATE_STOPPED = 0,
	EZPLAYER_STATE_PAUSED,
	EZPLAYER_STATE_STOPPING,
	EZPLAYER_STATE_PAUSING,
	EZPLAYER_STATE_PARSING,
	EZPLAYER_STATE_RESUMING,
	EZPLAYER_STATE_SEEKING,
	EZPLAYER_STATE_PLAYING,
	
} ezPlayerState_et;

/*
*	player control commands
*/
typedef enum {

	EZPLAYER_CMD_NONE = 0,

	EZPLAYER_CMD_PLAY,							/* play */
	EZPLAYER_CMD_PAUSE,							/* pause */
	EZPLAYER_CMD_RESUME,						/* resume play */
	EZPLAYER_CMD_STOP,							/* stop */
	EZPLAYER_CMD_REPLAY,						/* play again */
	EZPLAYER_CMD_NEXT,							/* play next */
	EZPLAYER_CMD_PREV,							/* play previous */
	EZPLAYER_CMD_FF,								/* fast forward */
	EZPLAYER_CMD_FB,								/* fast backward */
	EZPLAYER_CMD_SETPLAYLIST,				/* set play list */
	EZPLAYER_CMD_SETPLAYPOS, 			/* set current play position in play list */
	EZPLAYER_CMD_SETVOL,						/* set a special volume */
	EZPLAYER_CMD_SETAUDCHN,				/* set audio channel */
	EZPLAYER_CMD_SETAUDSTREAM,		/* set audio stream */
	EZPLAYER_CMD_SETRECORD,				/* set record on/off */
	EZPLAYER_CMD_SETPLAYMODE,			/* set play mode */
	EZPLAYER_CMD_SETVOCAL,					/* set vocal fade */
	EZPLAYER_CMD_SETMUTE,					/* set mute */
	EZPLAYER_CMD_PLAYWAV,					/* play effect wav sound */
	EZPLAYER_CMD_CHKFMT, 					/* check file format is supported or not */
	
	EZPLAYER_CMD_COUNT
	
}ezPlayerCmd_et;

/*
*	player notify
*/
typedef enum {

	EZPLAYER_NOTIFY_NONE = 0,

	EZPLAYER_NOTIFY_PLAY,							/* play */     //      1
	EZPLAYER_NOTIFY_PAUSE,						/* pause */   //   2
	EZPLAYER_NOTIFY_RESUME, 					/* resume play */  //   3
	EZPLAYER_NOTIFY_STOP,							/* stop */    //   4
	EZPLAYER_NOTIFY_REPLAY,						/* replay */    //   5
	EZPLAYER_NOTIFY_NEXT,							/* play next */   //   6
	EZPLAYER_NOTIFY_PREV,							/* play previous */   //   7
	EZPLAYER_NOTIFY_FF,								/* fast forward */    //  8
	EZPLAYER_NOTIFY_FB,								/* fast backward */   //   9
	EZPLAYER_NOTIFY_SETPLAYLIST, 			/* set play list */               // 10
	EZPLAYER_NOTIFY_SETPLAYPOS,			/* set current play position in play list */   //  11
	EZPLAYER_NOTIFY_SETVOL,						/* set a special volume */    //  12
	EZPLAYER_NOTIFY_SETAUDCHN,				/* set audio channel */      //  13   
	EZPLAYER_NOTIFY_SETAUDSTREAM,		/* set audio stream */              // 14
	EZPLAYER_NOTIFY_SETRECORD,				/* set record on/off */      // 15
	EZPLAYER_NOTIFY_SETPLAYMODE,		/* set play mode */                     //   16
	EZPLAYER_NOTIFY_SETVOCAL,				/* set vocal fade */              //   17
	EZPLAYER_NOTIFY_SETMUTE,					/* set mute */             //   18
	EZPLAYER_NOTIFY_PLAYWAV,					/* play effect wav sound */      // 19
	EZPLAYER_NOTIFY_CHKFMT,					/* check file format is supported or not */    //  20
	EZPLAYER_NOTIFY_ERROR, 						/* error in playing process */		//	 4
	EZPLAYER_NOTIFY_UPDATE,						/* update player view */		//	 4

	EZPLAYER_NOTIFY_COUNT
	
}ezPlayerNotify_et;

/*
*	volume type
*/
typedef enum {

	EZPLAYER_VOL_TOTAL = 0,
	EZPLAYER_VOL_VOICE,
	EZPLAYER_VOL_REVERB,
	EZPLAYER_VOL_MIDI,
	EZPLAYER_VOL_ACCOMANY,
	EZPLAYER_VOL_MICL,
	EZPLAYER_VOL_MICR,
	EZPLAYER_VOL_WMICL,
	EZPLAYER_VOL_WMICR,
	EZPLAYER_VOL_RHYTHM,
	EZPLAYER_VOL_REC,
	EZPLAYER_VOL_ECHO,
	EZPLAYER_VOL_DELAY,
	EZPLAYER_VOL_TONE,
	EZPLAYER_VOL_TEMPO,
	EZPLAYER_VOL_MUSIC,

	EZPLAYER_VOL_BBEEN,
	EZPLAYER_VOL_BBELEVEL,
	EZPLAYER_VOL_AGCEN,
	EZPLAYER_VOL_AGCGAIN,
	EZPLAYER_VOL_MICIN,
	
	EZPLAYER_VOL_EQ100,
	EZPLAYER_VOL_EQ1K,
	EZPLAYER_VOL_EQ5K,
	
	EZPLAYER_VOL_COUNT
	
} ezPlayerVolType_et;

/*
*	audio channel type
*/
typedef enum {

	EZPLAYER_AUDCHN_STEREO = 0,
	EZPLAYER_AUDCHN_LEFT ,
	EZPLAYER_AUDCHN_RIGHT,
} ezPlayerAudChannel_et;

/*
*	record setup option
*/
typedef enum {

	EZPLAYER_REC_OFF = 0,
	EZPLAYER_REC_ON,
	
} ezPlayerRecOption_et;

/*
*	repeat setup option
*/
typedef enum {

	EZPLAYER_REPEAT_OFF = 0,
	EZPLAYER_REPEAT_ON,
	
} ezPlayerRepeatOption_et;

/*vocal mode*/
typedef enum
{
	EZPLAYER_VOCAL_ON,
	EZPLAYER_VOCAL_OFF,
	EZPLAYER_VOCAL_AUTO,
}ezPlayerVocalOption_et;


typedef enum
{
	EZPLAYER_MUTE_OFF,
	EZPLAYER_MUTE_ON,
}ezPlayerMuteOption_et;

/*
*	play mode
*/
typedef enum
{
	EZPLAYER_MODE_NORMAL = 0,
	EZPLAYER_MODE_REPEAT,
	EZPLAYER_MODE_CONTINUE,
	EZPLAYER_MODE_RANDOM,
	EZPLAYER_MODE_COUNT,
} ezPlayerPlayMode_et;
/*
*	lyric
*/
typedef enum
{
	EZPLAYER_LYRIC_OFF = 0,					// all lines off
	EZPLAYER_LYRIC_ON,							// all lines on
	EZPLAYER_LYRIC_MAIN_ON,				// main lines on, label off
	EZPLAYER_LYRIC_LABEL_ON,				// label lines on, main lines off
} ezPlayerLyric_et;

/*
*	ifun
*/
typedef enum
{
	EZPLAYER_IFUN_OFF = 0,
	EZPLAYER_IFUN_ON = 1,
} ezPlayerIfun_et;

/*
*	score
*/
typedef enum
{
	EZPLAYER_SCORE_OFF = 0,
	EZPLAYER_SCORE_ON,	
	// not really options
	EZPLAYER_SCORE_VIEW_OFF = 2,
	EZPLAYER_SCORE_VIEW_ON = 3,
} ezPlayerScore_et;
/*
  	cheer
*/
typedef enum
{
	EZPLAYER_CHEER_OFF = 0,
	EZPLAYER_CHEER_ON,
} ezPlayerCheerOption_et;

/*
*	fast speed mode
*/
typedef enum
{

	EZPLAYER_FB_X32 = -5,
	EZPLAYER_FB_X16 = -4,
	EZPLAYER_FB_X8 = -3,
	EZPLAYER_FB_X4 = -2,
	EZPLAYER_FB_X2 = -1,

	EZPLAYER_SPEED_X0 = 0,

	EZPLAYER_FF_X2 = 1,
	EZPLAYER_FF_X4 = 2,
	EZPLAYER_FF_X8 = 3,
	EZPLAYER_FF_X16 = 4,
	EZPLAYER_FF_X32 = 5,
	
} ezPlayerFFMode_et;

#if 0
typedef enum
{
	EZPLAYER_ABREPEAT_IDLE,
	EZPLAYER_ABREPEAT_POINT_A,
	EZPLAYER_ABREPEAT_POINT_B,
	EZPLAYER_ABREPEAT_STOP,
}ezPlayerABREPEAT_et;
#endif
/*
*	volume value data type
*/
typedef int ezPlayerVolValue_t;

/*
*	audio stream value data type
*/
typedef int ezPlayerAudStream_t;

/*
*	set volume parameter
*/
typedef struct 
{
	short								volType;											/* volume type */
	short								volValue;											/* volume value */

} ezSetVolPara_t;

/*
*	set vocal parameter
*/
typedef struct 
{
	short								vocalChannel;									/* 0: left channel is vocal or stream No.0 is vocal, >0: right channel or channel No.X */
	short								vocalValue;										/* see 'ezPlayerVocalOption_et' */

} ezSetVocalPara_t;

/*
*	set mic parameter
*/
typedef struct 
{
	int		inChannels;
	int 		outChannels;
	int		inRate;
	int 		outRate;
	int 		inLatency;
	int		outLatency;
	char		waveTable[PLAY_FILE_PATH_SZ];
} ezSetMicPara_t;

/*
*	setting mask
*/
typedef struct 
{
	int		vol:1;
	int		vocal:1;
	int		aud_channel:1;
	int		aud_stream:1;
	int		playmode:1;
	int		mute:1;
	int		rec:1;
	
} playerSettingMask_t;

/*
*	player list
*/
typedef struct 
{
	int totalCount;
	int curPos;
	ezVector_t* list;
	
} ezPlayerPlayList_t;

/*
*	player info
*/
typedef struct 
{
	char 									filePath[PLAY_FILE_PATH_SZ];		/* file full path */
	int					 					volval[EZPLAYER_VOL_COUNT];		/* volume setup values */
	
	ezPlayerState_et					state;													/* player state */
	ezPlayerState_et					bakState;											/* backup player state */
	ezPlayerPlayMode_et			mode;													/* play mode */
	ezPlayerVocalOption_et	vocal;
	ezPlayerMuteOption_et		mute;
	ezPlayerAudChannel_et		audChannel;										/* current audio channel option */
	ezPlayerLyric_et					lyric;													/* lyric state */
	ezPlayerIfun_et        			ifun;														/* ifun state */
	ezPlayerScore_et				score;													/* score state*/
	ezPlayerRecOption_et		rec;														/* record state */
	ezPlayerFFMode_et			ffMode;												/* FF/FB mode */
	int										fileType;												/* file type */
	int										audStream;										/* current audio stream option */
	int										audStreamCnt;									/* audio stream count */
	int										vocalChannel;									/* 0- left vocal, 1 - right vocal */
	ezSetMicPara_t					micPara;
	int										title;													/* 1- title on, 0-title off */
	
	int										bakSetType;										/* backup old setting type before set new one */
	int										bakSetValue;										/* backup old setting value before set new one */

	int										reserved[8];
	
} ezPlayerInf_t;

/*
*	ezPlayer user file operation parameters
*/
typedef struct
{
    FILE* fp;
    void *buffer;
    unsigned int size;
    unsigned int pos;
		
}ezPlayerUserFileOpPara_t;

/*
*	ezPlayer type define
*/
typedef struct s_handlePlayer ezPlayer_t;

/* 
* player notify callback function
*/
typedef void (*ezPlayerNotifyCallback_t)(ezPlayer_t*, int, int, int);

/* 
* player control callback function
*/
typedef int (*ezPlayerCtrlCallback_t)(ezPlayer_t*, int, void*);

/* 
* player method function
*/
typedef int (*ezPlayerCtrlMethod_t)(ezPlayer_t*, void*);

/* 
* player method function
*/
typedef int (*ezPlayerCtrlGetMethod_t)(ezPlayer_t*,void *);


/* 
* player update function
*/
typedef ezNotify_t (*ezPlayerUpdate_t)(ezPlayer_t*, unsigned int);

/*
* user file operation callback function
*/
typedef int (*ezPlayerUserFileCallback_t)(ezPlayerUserFileOpPara_t*);

/*
*	req base structure
*/
struct s_handlePlayer {

	ezNotifyHandle_t					reqNotify;				/* inherit notify, don't modify the position */

	ezPlayerNotifyCallback_t	notifyCallback;	/* notify callback function for multi-thread */
	ezPlayerNotifyCallback_t	notifyCallImp;	/* notify callback function, this callback is called at once in caller thread */
	ezPlayerUserFileCallback_t userFileCallback;
	ezPlayerCtrlCallback_t		playCtrl;				/* player control callback function */
	ezPlayerInf_t						playInf;
	ezPlayerPlayList_t				playList;
	int										initialized;				/* 1: player already be initialized, 0: not initialized */
	void* 									extraInf;
	void*									param;
	void*									owner;					/* the owner of this player, normally is a form window */
	//int									realstop;//status for thread, just means the last stop action is finished, not means player is stoping now
	int								playerStatus;
	/*
	*	ez player control methods 
	*/

	/*
	 * Method name		: play
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayPara_t]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play
	*/
	ezPlayerCtrlMethod_t			play;

	/*
	 * Method name		: pause
	 * Arguments			: player - input player 
	 *									para - input play parameter, normally is NULL
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: pause
	*/
	ezPlayerCtrlMethod_t			pause;
	
	/*
	 * Method name		: stop
	 * Arguments			: player - input player 
	 *									para - input play parameter, , normally is NULL
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: stop
	*/
	ezPlayerCtrlMethod_t			stop;
	
	/*
	 * Method name		: replay
	 * Arguments			: player - input player 
	 *									para - input play parameter, , normally is NULL
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: replay
	*/
	ezPlayerCtrlMethod_t			replay;
	
	/*
	 * Method name		: next
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayPara_t]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play next song
	*/
	ezPlayerCtrlMethod_t			next;

	/*
	 * Method name		: prev
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayPara_t]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play prev song
	*/
	ezPlayerCtrlMethod_t			prev;
	
	/*
	 * Method name		: FF
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerFFMode_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play fast forward
	*/
	ezPlayerCtrlMethod_t			FF;
	
	/*
	 * Method name		: FB
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerFFMode_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play fast backward
	*/
	ezPlayerCtrlMethod_t			FB;

	/*
	 * Method name		: setPlayPos
	 * Arguments			: player - input player 
	 *									para - play position
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set play position in playlist
	*/
	ezPlayerCtrlMethod_t			setPlayPos;

	/*
	 * Method name		: setPlayList
	 * Arguments			: player - input player 
	 *									para - folder path
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set play playlist byparsing input folder
	*/
	ezPlayerCtrlMethod_t			setPlayList;

	/*
	 * Method name		: playWav
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be path of wav file
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play effect wav sound 
	*/
	ezPlayerCtrlMethod_t			playWav;

	/*
	 * Method name		: chkFmt
	 * Arguments				: player - input player 
	 *									para - input parameter
	 * Return 					: none
	 * Description			: check file format is support or not in this player
	 *					
	*/
	ezPlayerCtrlMethod_t			chkFmt;

	/*
	 * Method name		: setVol
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezSetVolPara_t]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set volume
	*/
	ezPlayerCtrlMethod_t			setVol;

	/*
	 * Method name		: setAudChannel
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerAudChannel_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: select audio channel
	*/
	ezPlayerCtrlMethod_t			setAudChannel;
	
	/*
	 * Method name		: setAudStream
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be audio stream No.
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: select audio stream
	*/
	ezPlayerCtrlMethod_t			setAudStream;

	/*
	 * Method name		: setRec
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerRecOption_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set record on/off
	*/
	ezPlayerCtrlMethod_t			setRec;
	
	/*
	 * Method name		: setPlayMode
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerPlayMode_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set play mode
	*/
	ezPlayerCtrlMethod_t			setPlayMode;
	
	/*
	 * Method name		: setVocal
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerPlayMode_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set play mode
	*/
	ezPlayerCtrlMethod_t			setVocal;
	ezPlayerCtrlMethod_t			setMute;

	/*
	 * Method name		: setPlayMode
	 * Arguments			: player - input player 
	 *									para - input play parameter, should be type of [ezPlayerPlayMode_et]
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set play mode
	*/
	ezPlayerCtrlGetMethod_t			getVol;
	ezPlayerCtrlGetMethod_t			getRec;
	ezPlayerCtrlGetMethod_t			getMute;
	ezPlayerCtrlGetMethod_t			getPlayMode;
	ezPlayerCtrlGetMethod_t			getVocal;
	/*
	 * Method name		: update
	 * Arguments			: player - input player 
	 *									timeElapsed - time elapsed, unit(ms)
	 * Return 				: none
	 * Description			: player self-update, it should be call in period, you can put it in a single thread or a timer or GUI rendor
	*/
	ezPlayerUpdate_t				update;
	
	void*							frameSprite;
	
};


#define EZPLAYER_ON_PLAY(player)  			(ezPlayer(player)->playInf.state == EZPLAYER_STATE_PLAYING)
#define EZPLAYER_ON_STOP(player)  			(ezPlayer(player)->playInf.state == EZPLAYER_STATE_STOPPED)
#define EZPLAYER_ON_PAUSE(player)  			(ezPlayer(player)->playInf.state == EZPLAYER_STATE_PAUSED)
#define EZPLAYER_ON_PLAYPAUSE(player)  (EZPLAYER_ON_PLAY(player) || EZPLAYER_ON_PAUSE(player))


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_playerUpdate
 * Arguments      	: player - input player 
 *									timeElapsed - time elapsed, unit(ms)
 * Return         	: notify data
 * Description    	: player self-update, it should be call in period, you can put it in a single thread or a timer or GUI rendor
 *					
*/
extern ezNotify_t ez_playerUpdate(ezPlayer_t* player, unsigned int timeElapsed);

/*
 * Function name  	: ez_playerSetVol
 * Arguments      	: player - input player 
 *									para - input parameter
 * Return         	: none
 * Description    	: setup volume
 *					
*/
extern int ez_playerCtrl(ezPlayer_t* player, void* para, int cmd, int notifyId, ezPlayerState_et midState, ezPlayerState_et newState);

/*
 * Function name  	: ez_playerInit
 * Arguments      	: player - input player 
 *									playCallback - input player control callback
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new player object
 *					
*/
extern ezPlayer_t* ez_playerInit(ezPlayer_t* player, ezPlayerCtrlCallback_t playCallback);

/*
 * Function name  	: ez_playerDeinit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a player object
 *					
*/
extern void ez_playerDeinit(ezPlayer_t* player);

/*
 * Function name  	: ez_playerNew
 * Arguments      	: playCallback - input player control callback
 * Return         	: req object address
 * Description    	: create a new player object
 *					
*/
extern ezPlayer_t* ez_playerNew(ezPlayerCtrlCallback_t playCallback);

/*
 * Function name  	: ez_playerFree
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: free a player object
 *					
*/
extern void ez_playerFree(ezPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

