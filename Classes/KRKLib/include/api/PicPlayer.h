/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : PicPlayer.h
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

#ifndef _PICPLAYER_H_
#define _PICPLAYER_H_

#include <lib/ezbase/ez_player.h>

/*
* picture play parameter
*/
typedef struct {

	char 								filePath[PLAY_FILE_PATH_SZ];
		
} PicPlayerPlayPara_t;

/*
*	req base structure
*/
typedef struct {

	ezPlayer_t						player;				/* inherit ezPlayer, don't modify the position */

	/*
	 * Method name		: setEffect
	 * Arguments			: player - input player 
	 *									para - input effect parameter, 
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set picture switch effect
	*/
	ezPlayerCtrlMethod_t		setEffect;
	ezPlayerCtrlMethod_t		setShowMode;
	ezPlayerCtrlMethod_t		setIntervalTime;
	ezPlayerCtrlMethod_t		setPackPlayList;
	ezPlayerCtrlMethod_t		initView;
	ezPlayerCtrlMethod_t		freeView;
	ezPlayerCtrlMethod_t		updateView;
	ezPlayerCtrlMethod_t		setSeperateUpdate;
	
} PicPlayer_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: PicPlayerInit
 * Arguments      	: player - input player 
 *									para - input parameter
 *									owner - the owner of the player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Pic player object
 *					
*/
extern PicPlayer_t* PicPlayerInit(PicPlayer_t* player, void* para, void* owner);

/*
 * Function name  	: PicPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Pic player object
 *					
*/
extern void PicPlayerDeInit(PicPlayer_t* player);

/*
 * Function name  	: PicPlayerNew
 * Arguments      	: para - input parameters
 *									owner - owner of this player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Pic player object
 *					
*/
extern PicPlayer_t* PicPlayerNew(void* para, void* owner);

/*
 * Function name  	: PicPlayerFree
 * Arguments      	: input Pic player object
 * Return         	: none
 * Description    	: free a new Pic player object
 *					
*/
extern void PicPlayerFree(PicPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

