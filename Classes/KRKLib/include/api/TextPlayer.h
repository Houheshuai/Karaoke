/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : TextPlayer.h
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

#ifndef _TEXTPLAYER_H_
#define _TEXTPLAYER_H_

#include <lib/ezbase/ez_player.h>
#include <gui/iapi/GuiString.h>
#include <gui/iapi/GuiRes.h>

typedef struct s_textPlayer TextPlayer_t;
typedef int (*TextPlayerDraw_t)(TextPlayer_t*);
typedef int (*TextPlayerScroll_t)(TextPlayer_t*);
typedef int (*TextPlayerPage_t)(TextPlayer_t*);
typedef int (*TextPlayerSetPath_t)(TextPlayer_t*, char*);

/*
* text display parameter
*/
typedef struct {

	int									render;
	int									distanceInlines;
	int									charset;
	ResStyleProperty_t*		style;
	gdi_rect_t						bgArea;
	int									linePerPage;
	int									charPerLine;
	
} TextPlayerDisplayPara_t;


/*
* text play parameter
*/
typedef struct {

	ezString_t* 							ezstr;
	ezVector_t*							lyric;
	int											lyricSum;
	int											lyricCurrent;
	int											visible;
		
} TextPlayerPlayPara_t;

/*
*	req base structure
*/
struct s_textPlayer{

	ezPlayer_t								player;/* inherit ezPlayer, don't modify the position */		
	TextPlayerPlayPara_t				playPara;
	TextPlayerDisplayPara_t	 * 	displayPara;

	TextPlayerScroll_t					scrollUp;
	TextPlayerScroll_t					scrollDown;
	TextPlayerPage_t					pageUp;
	TextPlayerPage_t					pageDown;
	TextPlayerDraw_t					reDraw;
	TextPlayerDraw_t					clean;
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: TextPlayerInit
 * Arguments      	: player - input player 
 *									para - input parameter
 *									owner - the owner of the player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Music player object
 *					
*/
extern TextPlayer_t* TextPlayerInit(TextPlayer_t* player, void* para, void* owner);

/*
 * Function name  	: TextPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Music player object
 *					
*/
extern void TextPlayerDeInit(TextPlayer_t* player);

/*
 * Function name  	: TextPlayerNew
 * Arguments      	: para - input parameters
 *									owner - owner of this player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Music player object
 *					
*/
extern TextPlayer_t* TextPlayerNew(void* para, void* owner);

/*
 * Function name  	: TextPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Music player object
 *					
*/
extern void TextPlayerFree(TextPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

