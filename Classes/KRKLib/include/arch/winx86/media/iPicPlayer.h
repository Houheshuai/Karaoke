#ifndef _IPICPLAYER_
#define _IPICPLAYER_

#include <lib/ezbase/ez_player.h>

enum
{
	PIC_SW_MODE_NONE = 0,
	PIC_SW_MODE_FADE_IN_OUT = 1,
	PIC_SW_MODE_PERSIAN_BLIND_H = 2,		
	PIC_SW_MODE_PERSIAN_BLIND_V = 3,		
	PIC_SW_MODE_SLID_UP 				= 4,
	PIC_SW_MODE_SLID_DOWN 			= 5,	
	PIC_SW_MODE_SLID_LEFT 			= 6,	
	PIC_SW_MODE_SLID_RIGHT			= 7,	
	PIC_SW_MODE_STRETCH_UP			= 8,	
	PIC_SW_MODE_STRETCH_DOWN		= 9,	
	PIC_SW_MODE_STRETCH_LEFT		= 10,	
	PIC_SW_MODE_STRETCH_RIGHT 	= 11,		
	PIC_SW_MODE_MOSAIC					= 12,
	PIC_SW_MODE_ROOM_IN 				= 13,
	PIC_SW_MODE_ROOM_OUT				= 14,

	PIC_SW_MODE_RANDOM = 0xff,
	
};

enum
{
	PIC_SHOW_MODE_ORISIZE = 0,
                              
	PIC_SHOW_MODE_STRETCH = 1,
	PIC_SHOW_MODE_CUTOFF = 2, 
	PIC_SHOW_MODE_AUTO = 3,
	PIC_SHOW_MODE_RATIO = 4,
	PIC_SHOW_MODE_USRDEF = 5,

};

enum
{
	PIC_FILE_TYPE_NORMAL = 0,
	PIC_FILE_TYPE_FOLDER = 1,
	PIC_FILE_TYPE_PACK = 2,
};

#ifdef __cplusplus
 extern "C" {
#endif

/*
 * Function name  	: _PicPlayerInit
 * Arguments      	: player - input player 
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Picture player object
 *					
*/
extern ezPlayer_t* _PicPlayerInit(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Picture player object
 *					
*/
extern void _PicPlayerDeInit(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerInitView
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - error code
 * Description    	: initialize picture view resource
 *					
*/
extern int _PicPlayerInitView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerFreeView
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize picture view resource
 *					
*/
extern int _PicPlayerFreeView(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerUpdateView
 * Arguments      	: player - input player 
 *									ipara - input parameters
 * Return         	: notify data
 * Description    	: pic player view update
 *					
*/
extern int _PicPlayerUpdateView(ezPlayer_t* player, void* ipara);

/*
 * Function name  	: _PicPlayerPlay
 * Arguments      	: player - input player 
 *									filePath - file full path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play picture file
 *					
*/
extern int _PicPlayerPlay(ezPlayer_t* player, char* filePath);

/*
 * Function name  	: _PicPlayerPlayPack
 * Arguments      	: player - input player 
 *									filePath - package file full path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play package picture file
 *					
*/
extern int _PicPlayerPlayPack(ezPlayer_t* player, char* filePath);

/*
 * Function name  	: _PicPlayerStop
 * Arguments      	: player - input player 
 *				: para   repeate none,play next , repeat
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: stop picture file
 *					
*/
extern int _PicPlayerStop(ezPlayer_t* player,void* para);

/*
 * Function name  	: _PicPlayerPause
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: pause picture file
 *					
*/
extern int _PicPlayerPause(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerResume
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: resume picture file from pause
 *					
*/
extern int _PicPlayerResume(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerNext
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play next picture file
 *					
*/
extern int _PicPlayerNext(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerPrev
 * Arguments      	: player - input player 
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: play previous picture file
 *					
*/
extern int _PicPlayerPrev(ezPlayer_t* player);

/*
 * Function name  	: _PicPlayerSetSeperateUpdate
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: set picture view update method
 *					
*/
extern int _PicPlayerSetSeperateUpdate(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerSetPlayList
 * Arguments      	: player - input player 
 *									: para - folder path
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set play list by parsing input folder
 *					
*/
extern int _PicPlayerSetPlayList(ezPlayer_t* player,void* para);

/*
 * Function name  	: _PicPlayerSetPackPlayList
 * Arguments      	: player - input player 
 *									: para - first integer is total count, second is list array
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set play list by pack file play list
 *					
*/
extern int _PicPlayerSetPackPlayList(ezPlayer_t* player,void* para);

/*
 * Function name  	: _PicPlayerSetPlayPos
 * Arguments      	: player - input player 
 *									: para - new position
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set current position in play list
 *					
*/
extern int _PicPlayerSetPlayPos(ezPlayer_t* player,void* para);

/*
 * Function name  	: _PicPlayerSetEffect
 * Arguments      	: player - input player 
 *									para - input effect parameter
 * Return         	: none
 * Description    	: set picture switch effect
 *					
*/
extern int _PicPlayerSetEffect(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerSetShowMode
 * Arguments      	: player - input player 
 *									para - input show mode 
 * Return         	: none
 * Description    	: set picture switch effect
 *					
*/
extern int _PicPlayerSetShowMode(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerSetPlayMode
 * Arguments      	: player - input player 
 *									: para - new mode
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: set play mode
 *					
*/
extern int _PicPlayerSetPlayMode(ezPlayer_t* player,void* para);

/*
 * Function name  	: _PicPlayerSetIntervalTime
 * Arguments      	: player - input player 
 *									para - set time
 * Return         	: none
 * Description    	: set picture interval time
 *					
*/
extern int _PicPlayerSetIntervalTime(ezPlayer_t* player, void* para);

/*
 * Function name  	: _PicPlayerChkFmt
 * Arguments      	: player - input player 
 *									vol - vol value
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: check photo file format is supported or not
 *					
*/
extern int _PicPlayerChkFmt(ezPlayer_t* player, void* file);

#ifdef __cplusplus
}
#endif

#endif
