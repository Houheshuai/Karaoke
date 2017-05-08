/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : BatchPlayer.h
** Revision : 1.00											
**																	
** Description: a player container
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

#ifndef _BATCH_PLAYER_H_
#define _BATCH_PLAYER_H_

#include <lib/ezbase/ez_vector.h>
#include <lib/ezbase/ez_player.h>

/*
* batchplayer
*/
typedef struct s_batchPlayer BatchPlayer_t;

/*
* player new/free method 
*/
typedef ezPlayer_t* (*PlayerNewMethod_t)(void*, void*);
typedef void (*PlayerFreeMethod_t)(ezPlayer_t*);
typedef void* (*PlayerParseStart_t)(ezPlayer_t*, void*);
typedef void* (*PlayerParseEnd_t)(ezPlayer_t*, void*);

/*
* player registry
*/
typedef struct 
{
	ezPlayer_t*						player;
	
	int				 					type;
	int									multiFlag;
	const char*						suffix;
	
	void*								createPara;
	void*								parsePara;
	
	PlayerNewMethod_t 		createPlayer;
	PlayerFreeMethod_t 		destroyPlayer;
	PlayerParseStart_t			startParse;
	PlayerParseEnd_t			endParse;
	
} playerRegistry_t;

/*
* batch player method
*/
typedef int (*BatchPlayerRegPlayer_t)(BatchPlayer_t*, playerRegistry_t*);
typedef ezPlayer_t* (*BatchPlayerGetPlayer_t)(BatchPlayer_t*);
typedef ezPlayer_t* (*BatchPlayerGetPlayerByType_t)(BatchPlayer_t*, int);
typedef ezPlayerReturn_et (*BatchPlayerSetPlayer_t)(BatchPlayer_t*, int);
typedef int (*BatchPlayerGetPlayerType_t)(BatchPlayer_t*);
typedef int (*BatchPlayerParseType_t)(BatchPlayer_t*, const char*);
typedef ezPlayerReturn_et (*BatchPlayerPlay_t)(BatchPlayer_t*, int, void*);
typedef ezPlayerReturn_et (*BatchPlayerPlayFile_t)(BatchPlayer_t*, const char*, void*);
typedef ezPlayerReturn_et (*BatchPlayerStop_t)(BatchPlayer_t*, void*);
typedef ezNotifyReturn_et (*BatchPlayerAddEvent_t)(BatchPlayer_t*, int, handleNotifyCallback_t);
typedef ezNotifyReturn_et (*BatchPlayerRemoveEvent_t)(BatchPlayer_t*, int);
typedef ezNotify_t (*BatchPlayerUpdate_t)(BatchPlayer_t*, unsigned int);

/*
*	req base structure
*/
struct s_batchPlayer{

	ezVector_t*							playerRegistry;
	int											curPlayer;
	void*										owner;
	ezNotifyHandle_t					notifyHandle;

	BatchPlayerAddEvent_t			addEvent;
	BatchPlayerRemoveEvent_t	removeEvent;
	
	/*
	 * Method name		: regPlayer
	 * Arguments			: player - batchplayer handler
	 *									registry - regist player
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: register player to batch player
	*/
	BatchPlayerRegPlayer_t			regPlayer;

	/*
	 * Method name		: getPlayer
	 * Arguments			: player regist info
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: get current player handle
	*/
	BatchPlayerGetPlayer_t				getPlayer;

	BatchPlayerGetPlayerByType_t	getPlayerByType;
	
	/*
	 * Method name		: setPlayer
	 * Arguments			: input batchplayer handler, type - set new player type
	 * Return 				: 0 - succ, <>0, error
	 * Description			: set current player
	*/
	BatchPlayerSetPlayer_t				setPlayer;

	BatchPlayerGetPlayerType_t		getPlayerType;
	BatchPlayerParseType_t				parsePlayerType;

	BatchPlayerUpdate_t					update;

	BatchPlayerPlay_t						play;
	BatchPlayerPlayFile_t					playFile;
	BatchPlayerStop_t						stop;
	
} ;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: BatchPlayerInit
 * Arguments      	: bgv - bgv player handle
 *									picPath - picture folder path
 *									videoPath - video folder path
 *									owner - owner of this media player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Media player object
 *					
*/
extern BatchPlayer_t* BatchPlayerInit(BatchPlayer_t* player, void* owner);

/*
 * Function name  	: BatchPlayerDeInit
 * Arguments      	: bgv - input player 
 * Return         	: none
 * Description    	: deinitialize a Media player object
 *					
*/
extern void BatchPlayerDeInit(BatchPlayer_t* player);

/*
 * Function name  	: BatchPlayerNew
 * Arguments      	: picPath - picture folder path
 *									videoPath - video folder path
 *									owner - owner of this media player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Media player object
 *					
*/
extern BatchPlayer_t* BatchPlayerNew(void* owner);

/*
 * Function name  	: BatchPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Media player object
 *					
*/
extern void BatchPlayerFree(BatchPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

