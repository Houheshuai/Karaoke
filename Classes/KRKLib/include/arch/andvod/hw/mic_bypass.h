/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : mic_bypass.h
** Revision : 1.00											
**																	
** Description: set F20 MIC data bypass
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

#ifndef _MIC_BYPASS_H_
#define _MIC_BYPASS_H_

#define MIC_BYPASS_MAX_VOL		100
#define MIC_BYPASS_MAX_ECHO_VOL 128

/*
* mic bypass volume type
*/
typedef enum
{
	MIC_VOL_NONE = 0,
	MIC_VOL_WIRED_LEFT = 1,
	MIC_VOL_WIRED_RIGHT = 2,
	MIC_VOL_WIRELESS_LEFT = 3,
	MIC_VOL_WIRELESS_RIGHT = 4,
	
} mic_vol_type_et;

/*
* mic bypass state
*/
typedef enum
{
	MIC_BYPASS_OFF,
	MIC_BYPASS_ON,
	
} mic_bypass_state_et;

#ifdef __cplusplus
extern "C" {
#endif 

/*
* set mic debug parameter
*
* @param 
*		
* @return - 0 - succ, <>0 error code
*/
extern int mic_set_debug(void* para);

/*
* open/close wired mic
*
* @param 1:on, 0:off
*		none
* @return - 0 - succ, <>0 error code
*/
extern int mic_wired_on(int onoff);

/*
* open/close mic bypass function
*
* @param 1:on, 0:off
*		none
* @return - 0 - succ, <>0 error code
*/
extern int mic_bypass_on(int onoff);

/*
* open/close wireless mic
*
* @param 1:on, 0:off
*		none
* @return - 0 - succ, <>0 error code
*/
extern int mic_wireless_on(int onoff);

/*
* check mic bypass on/off state
*
* @param
*		none
* @return - 1 - on, 0 off
*/
extern int mic_bypass_get_state(void);

/*
* check mic bypass on/off state
*
* @param
*		vol : 0~100
*		type : see. mic_vol_type_et
* @return - 1 - on, 0 off
*/
extern int mic_bypass_set_vol(int vol, int type);

/*
* set mic echo volume
*
* @param
*		vol : 0~128
* @return - 1 - on, 0 off
*/
extern int mic_bypass_set_echo(int vol);

/*
* wireless mic key process
*
* @param uiapp - UI application handler
*								keymap - wireless mic key map
*								count - wireless mic key count
*		none
* @return - 0 - succ, <>0 error code
*/
extern int mic_wireless_keyproc(void* uiapp, void* keymap, unsigned int count);

/*
* check mic mute or not
*
* @param
*		vol : 0~100
*		type : see. mic_vol_type_et
* @return - 1 - mute, 0 unmute
*/
extern int mic_bypass_check_mute(int type);

//extern int mic_wireless_startpair(void);

#ifdef __cplusplus
}
#endif 

#endif


