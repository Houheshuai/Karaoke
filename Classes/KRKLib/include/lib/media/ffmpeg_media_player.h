/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MediaPlayer.c
** Revision : 1.00											
**																	
** Description: MediaPlayer module
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

#ifndef _FFMPEG_MP_H_
#define _FFMPEG_MP_H_

#include <k_global.h>

//#ifdef __cplusplus
//extern "C" {
//#endif

/*
 * Function name  	: ffmpeg_player_updateview
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update ffmpeg view
 *					
*/
extern int ffmpeg_player_updateview(ezPlayer_t* player, void* iPara);

/*
 * Function name  	: ffmpeg_player_initview
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - error code
 * Description    	: initialize media view resource
 *					
*/
extern int ffmpeg_player_initview(ezPlayer_t* player, void* para);

/*
 * Function name  	: ffmpeg_player_freeview
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize media view resource
 *					
*/
extern int ffmpeg_player_freeview(ezPlayer_t* player, void* para);

/*
 * Function name  	: ffmpeg_player_init
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new ffmpeg player object
 *					
*/
extern ezPlayer_t* ffmpeg_player_init(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_deinit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a ffmpeg player object
 *					
*/
extern void ffmpeg_player_deinit(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_play
 * Arguments      	: player - input player 
 *									ppara - input play parameters
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play media file
 *					
*/
extern int ffmpeg_player_play(ezPlayer_t* player, char* ppara);

/*
 * Function name  	: ffmpeg_player_stop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
extern int ffmpeg_player_stop(ezPlayer_t* player,void* para);

/*
 * Function name  	: ffmpeg_player_pause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
extern int ffmpeg_player_pause(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_resume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int ffmpeg_player_resume(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_next
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play next media file
 *					
*/
extern int ffmpeg_player_next(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_prev
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play previous media file
 *					
*/
extern int ffmpeg_player_prev(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_seek
 * Arguments      	: player - input player , time - millisecond time
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: seek time
 *					
*/
extern int ffmpeg_player_seek(ezPlayer_t* player, int time);

/*
 * Function name  	: ffmpeg_player_replay
 * Arguments      	: player - input player 
 *									ppara - input play parameters
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: replay media file
 *					
*/
extern int ffmpeg_player_replay(ezPlayer_t* player);

/*
 * Function name  	: ffmpeg_player_setvol
 * Arguments      	: player - input player 
 *									para - vol value& type
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
extern int ffmpeg_player_setvol(ezPlayer_t* player, void* para);

/*
 * Function name  	: ffmpeg_player_setvocal
 * Arguments      	: player - input player 
 *									para - vocal parameter
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: mute
 *					
*/
extern int ffmpeg_player_setvocal(ezPlayer_t* player, void* para);

/*
 * Function name  	: ffmpeg_player_setnoaudio
 * Arguments      	: player - input player 
 *									setting - 1, no audio output, 0, output audio
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: don't play audio when play a media file
 *					
*/
extern int ffmpeg_player_setnoaudio(ezPlayer_t* player, int setting);

/*
 * Function name  	: ffmpeg_player_setmic, must succus
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set mic parameters
 *					
*/
extern int ffmpeg_player_setmic(ezPlayer_t* player, void * para);

/*
 * Function name  	: ffmpeg_player_getplaytime
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int ffmpeg_player_getplaytime(ezPlayer_t* player, void * para);

/*
 * Function name  	: ffmpeg_player_gettotaltime
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int ffmpeg_player_gettotaltime(ezPlayer_t* player, void * para);

/*
 * Function name  	: ffmpeg_player_getscore
 * Arguments      	: player - input player 
 *					
 * Return         	: 
 * Description    	:
 *					
*/
extern int ffmpeg_player_getscore(ezPlayer_t* player, void * para);

//#ifdef __cplusplus
//}
//#endif

#endif

