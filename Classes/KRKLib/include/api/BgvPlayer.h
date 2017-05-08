/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : BgvPlayer.h
** Revision : 1.00											
**																	
** Description: background video/picture Player module
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

#ifndef _BGV_PLAYER_H_
#define _BGV_PLAYER_H_

#include <lib/ezbase/ez_vector.h>
#include <api/MediaPlayer2.h>
#include <api/PicPlayer.h>

/*
*	bgv path size
*/
#define MAX_BGV_PATH_SZ				128

/*
*	bgv file type
*/
enum 
{
	BGV_TYPE_NONE = 0,
	BGV_TYPE_PIC, 
	BGV_TYPE_VIDEO
};

/*
*	bgv file mode
*/
enum 
{
	BGV_MODE_FOLDER = 0,
	BGV_MODE_FILE, 
	BGV_MODE_PACKFILE,
};

/*
*	bgv file mode
*/

enum 
{
	BGV_IN_PIC = 11,
	BGV_IN_VIDEO,
	BGV_OUT_PIC,
	BGV_OUT_VIDEO,
};

/*
*	bgv play mode
*/
enum 
{
	BGV_PLAY_FROM_BEGINNING = 0, 
	BGV_PLAY_FROM_LAST_STOPPED,
	BGV_PLAY_FROM_NEXT,
	BGV_PLAY_FROM_RANDOM,
};

/*
*	bgv play state
*/
enum 
{
	BGV_STATE_STOPPED = 0, 
	BGV_STATE_PLAYING,
	BGV_STATE_,
};

typedef struct s_bgvPlayer BgvPlayer_t;
typedef ezPlayerReturn_et (*BgvPlayerCtrlMethod_t)(BgvPlayer_t*, int);
typedef ezPlayerReturn_et (*BgvPlayerCtrlSetPath_t)(BgvPlayer_t*, const char*);
typedef ezPlayerReturn_et (*BgvPlayerCtrlPlayFile_t)(BgvPlayer_t*, const char*);
typedef ezPlayerReturn_et (*BgvPlayerCtrlSetPackList_t)(BgvPlayer_t*, void*);
typedef int (*BgvPlayerGetState_t)(BgvPlayer_t*);

/*
*	req base structure
*/
struct s_bgvPlayer{

	ezPlayer_t*						player;				/* picture/media player handler */
	int									type;					/* 0: picture file, 1-video file */
	int									state;
	char									picPath[MAX_BGV_PATH_SZ];
	char									videoPath[MAX_BGV_PATH_SZ];
	char									filePath[MAX_BGV_PATH_SZ];
	char*								curPath;
	void*								owner;
	int									picLastPos;
	int									videoLastPos;
	int									interrupt;
	int									fileMode;
	ezVector_t*							playerRegistry;
	
	/*
	 * Method name		: setType
	 * Arguments			: player - bgv player 
	 *									type - 0: pic, 1: video
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set bgv file type, only picture or video
	*/
	BgvPlayerCtrlMethod_t		setType;

	/*
	 * Method name		: setPath
	 * Arguments			: player - bgv player 
	 *									path - pic or video folder path
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: set bgv file path, rebuild playlist, must stop before set new path
	*/
	BgvPlayerCtrlSetPath_t		setPath;

	BgvPlayerCtrlSetPackList_t	setPackList;
	
	/*
	 * Method name		: play
	 * Arguments			: player - bgv player 
	 *									para - play mode
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play bgv in folder
	*/
	BgvPlayerCtrlMethod_t		play;
	
	/*
	 * Method name		: playFile
	 * Arguments			: player - bgv player 
	 *									para - play mode
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play single file bgv
	*/
	BgvPlayerCtrlPlayFile_t		playFile;
	
	/*
	 * Method name		: playPackFile
	 * Arguments			: player - bgv player 
	 *									para - play mode
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play package file bgv
	*/
	BgvPlayerCtrlPlayFile_t		playPackFile;
	
	/*
	 * Method name		: play
	 * Arguments			: player - bgv player 
	 *									para - play mode
	 * Return 				: 0 -succ, <>0 - error code
	 * Description			: play bgv
	*/
	BgvPlayerCtrlMethod_t		stop;

	BgvPlayerGetState_t			getState;
	
} ;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: BgvPlayerInit
 * Arguments      	: bgv - bgv player handle
 *									picPath - picture folder path
 *									videoPath - video folder path
 *									owner - owner of this media player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Media player object
 *					
*/
extern BgvPlayer_t* BgvPlayerInit(BgvPlayer_t* bgv, const char* picPath, const char* videoPath, void* owner);

/*
 * Function name  	: BgvPlayerDeInit
 * Arguments      	: bgv - input player 
 * Return         	: none
 * Description    	: deinitialize a Media player object
 *					
*/
extern void BgvPlayerDeInit(BgvPlayer_t* bgv);

/*
 * Function name  	: BgvPlayerNew
 * Arguments      	: picPath - picture folder path
 *									videoPath - video folder path
 *									owner - owner of this media player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Media player object
 *					
*/
extern BgvPlayer_t* BgvPlayerNew(const char* picPath, const char* videoPath, void* owner);

/*
 * Function name  	: BgvPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Media player object
 *					
*/
extern void BgvPlayerFree(BgvPlayer_t* bgv);

#ifdef __cplusplus
}
#endif

#endif

