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

#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include <lib/ezbase/ez_player.h>

/*
* picture play parameter
*/
typedef struct {

	char 								filePath[PLAY_FILE_PATH_SZ];
		
} MediaPlayerPlayPara_t;

typedef struct s_MediaPlayer MediaPlayer_t;
typedef int (*MediaPlayerCtrlMethod_t)(MediaPlayer_t*, int);

/*
*	req base structure
*/
struct s_MediaPlayer{

	ezPlayer_t						player;				/* inherit ezPlayer, don't modify the position */
	
	/*
	 * Method name		: setNoAudio
	 * Arguments			: player - input player 
	 *									setting - 1, no audio output, 0, audio output
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: don't output audio when play a media file
	*/
	MediaPlayerCtrlMethod_t		setNoAudio;
	MediaPlayerCtrlMethod_t		setSwitchMode;
	ezPlayerCtrlMethod_t			setMicPara;
	ezPlayerCtrlMethod_t			getplaytime;
	ezPlayerCtrlMethod_t			getTotalTime;
	ezPlayerCtrlMethod_t			getScore;
	ezPlayerCtrlMethod_t			initView;
	ezPlayerCtrlMethod_t			freeView;
	ezPlayerCtrlMethod_t			updateView;
	ezPlayerCtrlMethod_t			setSeperateUpdate;
	
} ;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: MediaPlayerInit
 * Arguments      	: player - input player 
 *									para - input parameter
 *									owner - the owner of the player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Media player object
 *					
*/
extern MediaPlayer_t* MediaPlayerInit(MediaPlayer_t* player, void* para, void* owner);

/*
 * Function name  	: MediaPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Media player object
 *					
*/
extern void MediaPlayerDeInit(MediaPlayer_t* player);

/*
 * Function name  	: MediaPlayerNew
 * Arguments      	: para - input parameters
 *									owner - owner of this media player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Media player object
 *					
*/
extern MediaPlayer_t* MediaPlayerNew(void* para, void* owner);

/*
 * Function name  	: MediaPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Media player object
 *					
*/
extern void MediaPlayerFree(MediaPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

