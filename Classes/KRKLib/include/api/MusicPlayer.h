/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MusicPlayer.h
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

#ifndef _MUSICPLAYER_H_
#define _MUSICPLAYER_H_

#include <lib/ezbase/ez_player.h>

/*
* picture play parameter
*/
typedef struct {

	char 								filePath[PLAY_FILE_PATH_SZ];
		
} MusicPlayerPlayPara_t;

/*
*	req base structure
*/
typedef struct {

	ezPlayer_t						player;				/* inherit ezPlayer, don't modify the position */
		
} MusicPlayer_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: MusicPlayerInit
 * Arguments      	: player - input player 
 *									para - input parameter
 *									owner - the owner of the player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Music player object
 *					
*/
extern MusicPlayer_t* MusicPlayerInit(MusicPlayer_t* player, void* para, void* owner);

/*
 * Function name  	: MusicPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Music player object
 *					
*/
extern void MusicPlayerDeInit(MusicPlayer_t* player);

/*
 * Function name  	: MusicPlayerNew
 * Arguments      	: para - input parameters
 *									owner - owner of this player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Music player object
 *					
*/
extern MusicPlayer_t* MusicPlayerNew(void* para, void* owner);

/*
 * Function name  	: MusicPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Music player object
 *					
*/
extern void MusicPlayerFree(MusicPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

