/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : player_core.h
** Revision : 1.00											
**																	
** Description: player core module
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

#ifndef _PLAYER_CORE_H_
#define _PLAYER_CORE_H_

#include <api/MediaPlayer2.h>
#include <api/MusPlayer.h>
#include <api/BatchPlayer.h>
#include <api/BgvPlayer.h>

/*
* MIC player type define
*/
typedef enum
{
	PLAYER_TYPE_NONE = 0,
	PLAYER_TYPE_VIDEO,
	PLAYER_TYPE_MUSIC,
	PLAYER_TYPE_PICTURE,
	PLAYER_TYPE_MUS,
	
	PLAYER_TYPE_COUNT,
	
} appPlayerType_t;

/*
* MIC player audio type
*/
typedef enum
{
	AUDIO_TYPE_STANDARD = 0,
	AUDIO_TYPE_KKEBOX,
	AUDIO_TYPE_KKEMINI,
	AUDIO_TYPE_EMBEDDED,
	
	AUDIO_TYPE_COUNT,
	
} appAudioType_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: player_core_init
 * Arguments      	: owner - service handle
 *										resFile - player res file path
 *										lan - language option value
 * Return         	: player handle
 * Description    	: initialize player
 *					
*/
extern BatchPlayer_t* player_core_init(void* owner, const char* resFile, int lan);

/*
 * Function name  	: player_core_deinit
 * Arguments      	: player - player handle
 * Return         	: 0 - succ, <>0 error code
 * Description    	: deinitialize player
 *					
*/
extern int player_core_deinit(BatchPlayer_t* player);

/*
 * Function name  	: player_audio_init
 * Arguments      	: audioIFName - audio interface name
 * Return         	: 0 - fail, 1 - standard, 2 - embeded
 * Description    	: initialize audio interface
 *					
*/
extern int player_audio_init(const char* audioIFName);

/*
 * Function name  	: player_audio_deinit
 * Arguments      	: none
 * Return         	: 0 - succ, <>0 error code
 * Description    	: deinitialize audio interface
 *					
*/
extern int player_audio_deinit(void);

/*
 * Function name  	: player_audio_change_if
 * Arguments      	: bp - batchplayer, playRec - playback record flag, audioType - audio IF type
 * Return         	: 0 - succ, <>0 error code
 * Description    	: change audio interface
 *					
*/
extern int player_audio_change_if(BatchPlayer_t* bp, int playRec, int audioType);

/*
 * Function name  	: player_audio_get_cur_if
 * Arguments      	: none
 * Return         	: audio interface
 * Description    	: get current audio interface
 *					
*/
extern void* player_audio_get_cur_if(void);

/*
 * Function name  	: player_audio_get_cur_handle
 * Arguments      	: none
 * Return         	: audio handle
 * Description    	: get current audio handle
 *					
*/
extern void* player_audio_get_cur_handle(void);

/*
 * Function name  	: player_audio_setup
 * Arguments      	: 
 *									inrate - input samplerate
 *									outrate - output samplerate
 *									inchannels - input channels
 *									outchannels - output channels
 * Return         	: 0 - succ, <>0 error code
 * Description    	: setup audio samplerate and channels
 *					
*/
extern int player_audio_setup(int inrate, int outrate, int inchannels, int outchannels);

/*
 * Function name  	: player_audio_get_param
 * Arguments      	: player - player handle
 *									inrate - input samplerate
 *									outrate - output samplerate
 *									inchannels - input channels
 *									outchannels - output channels
 * Return         	: none
 * Description    	: get embedded audio parameters
 *					
*/
extern void player_audio_get_param(int* inrate, int* outrate, int* inchannels, int* outchannels);

#ifdef __cplusplus
}
#endif

#endif

