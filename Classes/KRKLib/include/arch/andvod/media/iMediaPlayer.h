#ifndef _IMEDIAPLAYER_
#define _IMEDIAPLAYER_

#include <lib/ezbase/ez_player.h>

#ifndef NEED_FFMPEG
#define NEED_FFMPEG
#endif

#define _MEDIA_VOL_MIN				0
#define _MEDIA_VOL_MAX				100

#define _MEDIA_KEY_MAX				6
#define _MEDIA_KEY_ORI				0
#define _MEDIA_KEY_MIN			(-6)

enum {
	MediaSwitchMode_Gap = 0,
	MediaSwitchMode_Smooth,
	MediaSwitchMode_Count,
};

/*
*	player notify
*/
typedef enum {

	MEDIAPLAYER_NOTIFY_NONE = EZPLAYER_NOTIFY_NONE + 0x1000,

	MEDIAPLAYER_NOTIFY_SETMICPARA, 			/* set mic para */
	MEDIAPLAYER_NOTIFY_DEINIT_VIEW, 	/* deinit view */

	MEDIAPLAYER_NOTIFY_COUNT,
	
}MediaPlayerNotify_et;

typedef struct {
	char name[256];
} fileNameEntry_t;

typedef struct
{
	void*	mp;
	void* 	pFrame;

	krk_os_task_t task;
	ezNotifyHandle_t playNotify;
	ezNotifyHandle_t updateNotify;

	void* playerHdle;
	void* audioHdle;
	void* audioIF;
	
	int		noAudioFlag;
	int		noVideoFlag;
	int		hwVideoFlag;
	int		hwAudioFlag;
	int		curAudioTrack;
	int		totalAudioTrack;
	int		extAudio;
	int		viewReady;
	int		renderFlag;
	
	int		inLatency;
	int		outLatency;

	int 		inRate; // audio in samplerate 
	int 		outRate; // audio out samplerate 
	int 		inChannel; // audio in channels 
	int 		outChannel; // audio out channels 
	int 		auto_samplerate;		// auto set player sample rate according to song sample rate

	int		vocalCheckPoint;
	int		vocalTotalPoint;

	int		sdkVersion;
	
} iMMPlayerPara_t;

/*
* mediaplayer input config parameter
*/
typedef struct 
{
	int				switchMode;					// 0, switch by black screen, 1, switch smooth
	int				noAudio;
	int				hwVideo;
	int				hwAudio;
	void* 			audioHdle;
	void* 			audioIF;
	
} iMediaConfig_t;

/*
* mediaplayer play song info parameters
*/
typedef struct
{
	char 						songName[PLAY_FILE_PATH_SZ];
	char							filePath[PLAY_FILE_PATH_SZ];
	char							savePath[PLAY_FILE_PATH_SZ];
	char							recPath[PLAY_FILE_PATH_SZ];
	int							recOn;
	int							noAudio;
	int							noVideo;
	int							hwVideo;
	int							hwAudio;
	int							packFile;
	int							sdkVersion;
	int							seekTime;
	
}iMMPlayerSongInfo_st;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: _MediaPlayerInit
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Media player object
 *					
*/
extern ezPlayer_t* _MediaPlayerInit(ezPlayer_t* player);

/*
 * Function name  	: _MediaPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Media player object
 *					
*/
extern void _MediaPlayerDeInit(ezPlayer_t* player);

/*
 * Function name  	: _MediaPlayerInitView
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - error code
 * Description    	: initialize media view resource
 *					
*/
extern int _MediaPlayerInitView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MediaPlayerFreeView
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize media view resource
 *					
*/
extern int _MediaPlayerFreeView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MediaPlayerUpdateView
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update ffmpeg view
 *					
*/
extern int _MediaPlayerUpdateView(ezPlayer_t* player, void* iPara);

/*
 * Function name  	: _MediaPlayerUpdateView
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update ffmpeg view
 *					
*/
extern int _MediaPlayerUpdateView(ezPlayer_t* player, void* iPara);

/*
 * Function name  	: _MediaPlayerPlay
 * Arguments      	: player - input player 
 *									ppara - input play parameters
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play media file
 *					
*/
extern int _MediaPlayerPlay(ezPlayer_t* player, char* ppara);

/*
 * Function name  	: _MediaPlayerStop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
extern int _MediaPlayerStop(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MediaPlayerNext
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play next media file
 *					
*/
extern int _MediaPlayerNext(ezPlayer_t* player);

/*
 * Function name  	: _MediaPlayerPrev
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play previous media file
 *					
*/
extern int _MediaPlayerPrev(ezPlayer_t* player);

/*
 * Function name  	: _MediaPlayerPause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
extern int _MediaPlayerPause(ezPlayer_t* player);

/*
 * Function name  	: _MediaPlayerResume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MediaPlayerResume(ezPlayer_t* player);

/*
 * Function name  	: _MusPlayerSetSeperateUpdate
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set mus view update method
 *					
*/
extern int _MediaPlayerSetSeperateUpdate(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MediaPlayerSetPlayList
 * Arguments      	: player - input player 
 *									: para - folder path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set play list by parsing input folder
 *					
*/
extern int _MediaPlayerSetPlayList(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MediaPlayerSetPlayPos
 * Arguments      	: player - input player 
 *									: para - new position
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set current position in play list
 *					
*/
extern int _MediaPlayerSetPlayPos(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MediaPlayerPlayWav
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play effect wave sound
 *					
*/
extern int _MediaPlayerPlayWav(ezPlayer_t* player, char* filePath);

/*
 * Function name  	: _MediaPlayerChkFmt
 * Arguments      	: player - input player 
 *									vol - vol value& type
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: check file format s support or not in this player
 *					
*/
extern int _MediaPlayerChkFmt(ezPlayer_t* player, void* file);

/*
 * Function name  	: _MediaPlayerSetVol
 * Arguments      	: player - input player 
 *									para - vol value& type
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MediaPlayerSetVol(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MediaPlayerSetAudChannel
 * Arguments      	: player - input player 
 *									channel - audio channel
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MediaPlayerSetAudChannel(ezPlayer_t* player, void* channel);

/*
 * Function name  	: _MediaPlayerSetAudStream
 * Arguments      	: player - input player 
 *									streamid - audio stream id
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MediaPlayerSetAudStream(ezPlayer_t* player, void* streamid);

/*
 * Function name  	: _MediaPlayerSetMute
 * Arguments      	: player - input player 
 *									mute - mute option value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: mute
 *					
*/
extern int _MediaPlayerSetMute(ezPlayer_t* player, void* mute);

/*
 * Function name  	: _MediaPlayerSetVocal
 * Arguments      	: player - input player 
 *									para - vocal parameter
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: mute
 *					
*/
extern int _MediaPlayerSetVocal(ezPlayer_t* player, void* para);

/*
 * Function name  	: _MediaPlayerSetNoAudio
 * Arguments      	: player - input player 
 *									setting - 1, no audio output, 0, output audio
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: don't play audio when play a media file
 *					
*/
extern int _MediaPlayerSetNoAudio(ezPlayer_t* player, int setting);

/*
 * Function name  	: _MediaPlayerSetSwitchMode
 * Arguments      	: player - input player 
 *									see. MediaSwitchMode_Gap&MediaSwitchMode_Smooth
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set video switch mode
 *					
*/
extern int _MediaPlayerSetSwitchMode(ezPlayer_t* player, int mode);

/*
 * Function name  	: _MediaPlayerSetMicPara, must succus
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set mic parameters
 *					
*/
extern int _MediaPlayerSetMicPara(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MediaPlayerGetPlayTime
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int _MediaPlayerGetPlayTime(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MediaPlayerGetTotalTime
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int _MediaPlayerGetTotalTime(ezPlayer_t* player, void * para);

/*
 * Function name  	: _MediaPlayerGetScore
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int _MediaPlayerGetScore(ezPlayer_t* player, void * para);

#ifdef __cplusplus
}
#endif

#endif
