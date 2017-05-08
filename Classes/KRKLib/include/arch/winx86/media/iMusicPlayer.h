#ifndef _IMUSICPLAYER_
#define _IMUSICPLAYER_

#include <lib/ezbase/ez_player.h>

#define _MUSIC_VOL_MIN				0
#define _MUSIC_VOL_MAX				30

#define _MUSIC_KEY_MAX				6
#define _MUSIC_KEY_ORI				0
#define _MUSIC_KEY_MIN			(-6)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: _MusicPlayerInit
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Music player object
 *					
*/
extern ezPlayer_t* _MusicPlayerInit(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Music player object
 *					
*/
extern void _MusicPlayerDeInit(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerPlay
 * Arguments      	: player - input player 
 *									filePath - file full path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play media file
 *					
*/
extern ezPlayerReturn_et _MusicPlayerPlay(ezPlayer_t* player, char* filePath);

/*
 * Function name  	: _MusicPlayerStop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
extern ezPlayerReturn_et _MusicPlayerStop(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MusicPlayerPause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
extern ezPlayerReturn_et _MusicPlayerPause(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerResume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern ezPlayerReturn_et _MusicPlayerResume(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerChkFmt
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: check audio file format is supported or not
 *					
*/
extern ezPlayerReturn_et _MusicPlayerChkFmt(ezPlayer_t* player, void* file);

/*
 * Function name  	: _MusicPlayerSetVol
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern ezPlayerReturn_et _MusicPlayerSetVol(ezPlayer_t* player, void* vol);

/*
 * Function name  	: _MusicPlayerSetMute
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern ezPlayerReturn_et _MusicPlayerSetMute(ezPlayer_t* player, void* mute);

#ifdef __cplusplus
}
#endif

#endif
