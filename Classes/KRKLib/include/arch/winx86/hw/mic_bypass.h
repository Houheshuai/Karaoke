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
	MIC_VOL_WIRED_LEFT,
	MIC_VOL_WIRED_RIGHT,
	MIC_VOL_WIRELESS_LEFT,
	MIC_VOL_WIRELESS_RIGHT,
	
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
*		none
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
* check mic mute or not
*
* @param
*		vol : 0~100
*		type : see. mic_vol_type_et
* @return - 1 - mute, 0 unmute
*/
extern int mic_bypass_check_mute(int type);

#ifdef __cplusplus
}
#endif 

#endif


