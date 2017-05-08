#ifndef _IMUSICPLAYER_
#define _IMUSICPLAYER_

#include <lib/ezbase/ez_player.h>

#define _MUSIC_VOL_MIN				0
#define _MUSIC_VOL_MAX				256

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
extern int _MusicPlayerPlay(ezPlayer_t* player, char* filePath);

/*
 * Function name  	: _MusicPlayerStop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
extern int _MusicPlayerStop(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MusicPlayerPause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
extern int _MusicPlayerPause(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerResume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MusicPlayerResume(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerNext
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play next media file
 *					
*/
extern int _MusicPlayerNext(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerPrev
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play previous media file
 *					
*/
extern int _MusicPlayerPrev(ezPlayer_t* player);

/*
 * Function name  	: _MusicPlayerSetPlayList
 * Arguments      	: player - input player 
 *									: para - folder path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set play list by parsing input folder
 *					
*/
extern int _MusicPlayerSetPlayList(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MusicPlayerSetPlayPos
 * Arguments      	: player - input player 
 *									: para - new position
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set current position in play list
 *					
*/
extern int _MusicPlayerSetPlayPos(ezPlayer_t* player,void* para);

/*
 * Function name  	: _MusicPlayerChkFmt
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: check audio file format is supported or not
 *					
*/
extern int _MusicPlayerChkFmt(ezPlayer_t* player, void* file);

/*
 * Function name  	: _MusicPlayerSetVol
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int _MusicPlayerSetVol(ezPlayer_t* player, void* vol);

/*
 * Function name  	: _MusicPlayerSetMute
 * Arguments      	: player - input player 
 *									mute - on/off
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set music player mute on/off
 *					
*/
extern int _MusicPlayerSetMute(ezPlayer_t* player, void* mute);

#ifdef __cplusplus
}
#endif

#endif
