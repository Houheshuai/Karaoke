/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MusPlayer.h
** Revision : 1.00											
**																	
** Description: MusPlayer module
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

#ifndef _MUSPLAYER_H_
#define _MUSPLAYER_H_

#include <lib/ezbase/ez_player.h>
#include <lib/mus/iMusPlayer.h>

/*
* mus file storage mode
*/
typedef enum {

	MusFileMode_Dat = 0,
	MusFileMode_LocMus,
	MusFileMode_NetMus,
	
} MusFileMode_et;

/*
*	req base structure
*/
typedef struct {

	ezPlayer_t						player;				/* inherit ezPlayer, don't modify the position */

	/* Mus player control methods */
	ezPlayerCtrlMethod_t		play;
	ezPlayerCtrlMethod_t		pause;
	ezPlayerCtrlMethod_t		stop;
	ezPlayerCtrlMethod_t		replay;
	ezPlayerCtrlMethod_t		next;
	ezPlayerCtrlMethod_t		prev;
	ezPlayerCtrlMethod_t		setVol;
	ezPlayerCtrlMethod_t		setMute;
	ezPlayerCtrlMethod_t		setVocal;
	ezPlayerCtrlMethod_t		setMicPara;
	ezPlayerCtrlMethod_t		setLyric;
	ezPlayerCtrlMethod_t		setLyricAlign;
	ezPlayerCtrlMethod_t		setLyricDrawEffect;
	ezPlayerCtrlMethod_t		setLyricFont;
	ezPlayerCtrlMethod_t		setIfun;
	ezPlayerCtrlMethod_t		setScore;
	ezPlayerCtrlMethod_t		setStaffEnabled;
	ezPlayerCtrlMethod_t		setLyricEnabled;
	ezPlayerCtrlMethod_t		showTitleInf;
	ezPlayerCtrlMethod_t		autoSeek;
	ezPlayerCtrlMethod_t		derivedRecord;
	ezPlayerCtrlMethod_t		getRecordderivedPercent;
	ezPlayerCtrlMethod_t		playMedia;
	ezPlayerCtrlMethod_t		playEffectMusic;
	ezPlayerCtrlMethod_t		enableEffectMusic;
	ezPlayerCtrlMethod_t		seekTime;
	ezPlayerCtrlMethod_t		getplaytime;
	ezPlayerCtrlMethod_t		getTotalTime;
	ezPlayerCtrlMethod_t		setSongType;
	ezPlayerCtrlMethod_t		setFileParseType;
	ezPlayerCtrlMethod_t		setSoundEffect;
	ezPlayerCtrlMethod_t		setEQFreq;
	ezPlayerCtrlMethod_t		setencodeinf;
	ezPlayerCtrlMethod_t		testLatency;
	ezPlayerCtrlMethod_t		setExtMidiEn;
	ezPlayerCtrlMethod_t		resetExtMidi;
	ezPlayerCtrlMethod_t		playCheerEffect;
	ezPlayerCtrlMethod_t		setSPSoundEffect;
	ezPlayerCtrlMethod_t		setRecFileAudioConfig;
	ezPlayerCtrlMethod_t		getRecFileAudioConfig;

	ezPlayerCtrlMethod_t		initView;
	ezPlayerCtrlMethod_t		freeView;
	ezPlayerCtrlMethod_t		setSeperateUpdate;
	ezPlayerCtrlMethod_t		setViewVisible;
	ezPlayerCtrlMethod_t		updateView;

	ezPlayerCtrlGetMethod_t			getVol;
	ezPlayerCtrlGetMethod_t			getMute;
	ezPlayerCtrlGetMethod_t			getVocal;
	ezPlayerCtrlGetMethod_t			getRec;
	ezPlayerCtrlGetMethod_t			getScore;
	ezPlayerCtrlGetMethod_t			getEQFreq;
	ezPlayerCtrlGetMethod_t			getDefaultQJid;
	ezPlayerCtrlGetMethod_t			getLyricShowPara;
	ezPlayerCtrlGetMethod_t			getStaffShowPara;
	ezPlayerCtrlGetMethod_t			getLyricAlign;
	ezPlayerCtrlGetMethod_t			getLyricDrawEffect;
	ezPlayerCtrlGetMethod_t			getLyricInf;
	ezPlayerCtrlGetMethod_t			getLyricLineInf;
	ezPlayerCtrlGetMethod_t			getStaffSegInf;
	ezPlayerCtrlGetMethod_t			getBufferingFlag;

	ezPlayerUpdate_t			update;

} MusPlayer_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: MusPlayerInit
 * Arguments      	: player - input player 
 *									para - input parameter
 *									owner - the owner of the player
 * Return         	: succ - input player , fail - NULL
 * Description    	: initialize a new Mus player object
 *					
*/
extern MusPlayer_t* MusPlayerInit(MusPlayer_t* player, void* para, void* owner);

/*
 * Function name  	: MusPlayerDeInit
 * Arguments      	: player - input player 
 * Return         	: none
 * Description    	: deinitialize a Mus player object
 *					
*/
extern void MusPlayerDeInit(MusPlayer_t* player);

/*
 * Function name  	: MusPlayerNew
 * Arguments      	: para - input parameters
 *									owner - owner of this player
 * Return         	: succ -new mus player object, fail - NULL
 * Description    	: create a new Mus player object
 *					
*/
extern MusPlayer_t* MusPlayerNew(void* para, void* owner);

/*
 * Function name  	: MusPlayerFree
 * Arguments      	: input mus player object
 * Return         	: none
 * Description    	: free a new Mus player object
 *					
*/
extern void MusPlayerFree(MusPlayer_t* player);

#ifdef __cplusplus
}
#endif

#endif

