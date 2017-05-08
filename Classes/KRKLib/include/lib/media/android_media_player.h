/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : android_media_player.h
** Revision : 1.00											
**																	
** Description: android mediaplayer
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

#ifndef _ANDROID_MP_H_
#define _ANDROID_MP_H_

#include <k_global.h>

/*
 * Function name  	: android_player_update
 * Arguments      	: player - input player 
 *									timeElapsed - elapsed time in ms
 * Return         	: none
 * Description    	: update ffmpeg view
 *					
*/
int android_player_update(ezPlayer_t* player, void* iPara);

/*
 * Function name  	: android_player_init
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new ffmpeg player object
 *					
*/
ezPlayer_t* android_player_init(ezPlayer_t* player);

/*
 * Function name  	: android_player_deinit
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, -1, do nothing
 * Description    	: deinitialize a ffmpeg player object
 *					
*/
int android_player_deinit(ezPlayer_t* player);

/*
 * Function name  	: android_player_play
 * Arguments      	: player - input player 
 *									ppara - input play parameters
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play media file
 *					
*/
int android_player_play(ezPlayer_t* player, void* ppara);

/*
 * Function name  	: android_player_stop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop media file
 *					
*/
int android_player_stop(ezPlayer_t* player,void* para);

/*
 * Function name  	: android_player_pause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause media file
 *					
*/
int android_player_pause(ezPlayer_t* player);

/*
 * Function name  	: android_player_resume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume media file from pause
 *					
*/
int android_player_resume(ezPlayer_t* player);

/*
 * Function name  	: android_player_next
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play next media file
 *					
*/
int android_player_next(ezPlayer_t* player);

/*
 * Function name  	: android_player_prev
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play previous media file
 *					
*/
int android_player_prev(ezPlayer_t* player);

/*
 * Function name  	: android_player_setvol
 * Arguments      	: player - input player 
 *									para - vol value& type
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set volume
 *					
*/
int android_player_setvol(ezPlayer_t* player, void* para);

/*
 * Function name  	: android_player_setvocal
 * Arguments      	: player - input player 
 *									para - vocal parameter
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set vocal
 *					
*/
int android_player_setvocal(ezPlayer_t* player, void* para);

/*
 * Function name  	: android_player_setnoaudio
 * Arguments      	: player - input player 
 *									para - 1 or 0
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set noaudio
 *
*/
int android_player_setnoaudio(ezPlayer_t* player, int para);

//new add
int android_player_getplaytime(ezPlayer_t* player, void * para);

int android_player_gettotaltime(ezPlayer_t* player, void * para);

int android_player_getscore(ezPlayer_t* player, void* para);

int android_player_getplayerstatus(ezPlayer_t* player);

int	android_player_start(ezPlayer_t* player);

#endif

