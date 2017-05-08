/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : system_service.h
** Revision : 1.00											
**																	
** Description: system api service module
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
************************ HOWTO *******************************
** 
** CMD DEMES
**
** ----------------------------------------------------------
**	init 
**											hdle->setCmdPara(hdle, "init", "screenwidth", "1280");
**											hdle->setCmdPara(hdle, "init", "screenheight", "720");
**											hdle->setCmdPara(hdle, "init", "respath", "/mnt/sdcard/KARAOKE/RES/");
**											hdle->exec(hdle, "init", NULL);
**
** ----------------------------------------------------------
**	deinit 
**											hdle->exec(hdle, "deinit", NULL);
**
** ----------------------------------------------------------
**	clearscreen 
**											hdle->exec(hdle, "clearscreen", NULL);
**
** ----------------------------------------------------------
**	setscreen 
**											hdle->setCmdPara(hdle, "setscreen", "screenx", "0");
**											hdle->setCmdPara(hdle, "setscreen", "screeny", "0");
**											hdle->setCmdPara(hdle, "setscreen", "screenwidth", "1280");
**											hdle->setCmdPara(hdle, "setscreen", "screenheight", "720");
**											hdle->exec(hdle, "setscreen", NULL);
**
** ----------------------------------------------------------
**
** EVENT DEMES
**
**	don't need event hander in config service, all operation is realtime done
**	you can call queryEvent to get cmd result, 0: fail, 1: succ, -1: no event
**
** ----------------------------------------------------------
*/

#ifndef _SYSTEM_SERVICE_H_
#define _SYSTEM_SERVICE_H_

#include <lib/ezbase/ez_service.h>

/*
*========================================
*	system service commands
*========================================
*/
#define SYS_CMD_INIT									"init"
#define SYS_CMD_DEINIT								"deinit"
#define SYS_CMD_INITGL								"initGL"
#define SYS_CMD_DEINITGL							"deinitGL"
#define SYS_CMD_CLEARSCR							"clearscreen"
#define SYS_CMD_SETSCR								"setscreen"
#define SYS_CMD_SHOWSCRBG					"showscreenbg"
#define SYS_CMD_HIDESCRBG						"hidescreenbg"
#define SYS_CMD_RENDERSCRBG					"renderscreenbg"
#define SYS_CMD_XCOPY								"xcopy"
#define SYS_CMD_XREMOVE							"xremove"

/*
*	init cmd parameters name
*/
#define SYS_CMD_INIT_RESPATH					"respath"					// format: respath=/mnt/sdcard/KARAOKE/RES/
#define SYS_CMD_INIT_RES_W						"reswidth"				// format: reswidth=1280
#define SYS_CMD_INIT_RES_H						"resheight"				// format: resheight=720

#define SYS_CMD_INITGL_SCR_W						"screenwidth"			// format: screenwidth=1280
#define SYS_CMD_INITGL_SCR_H						"screenheight"		// format: screenheight=720

/*
*	setscreensize cmd parameters name
*/
#define SYS_CMD_SETSCRSIZE_X					"screenx"					// format: screenx=0
#define SYS_CMD_SETSCRSIZE_Y					"screeny"					// format: screeny=0
#define SYS_CMD_SETSCRSIZE_W					"screenwidth"			// format: screenwidth=1280
#define SYS_CMD_SETSCRSIZE_H					"screenheight"		// format: screenheight=720

/*
*	xcopy cmd parameters name
*/
#define SYS_CMD_XCOPY_SRC					"src"					// format: src=/mnt/sdcard/file1.bin
#define SYS_CMD_XCOPY_DST					"dst"				// format: dst=/mnt/sdcard/file2.bin

/*
*========================================
*	system service events
*========================================
*/
#define SYS_EVENT_INIT									SYS_CMD_INIT
#define SYS_EVENT_DEINIT							SYS_CMD_DEINIT
#define SYS_EVENT_INITGL								SYS_CMD_INITGL
#define SYS_EVENT_DEINITGL						SYS_CMD_DEINITGL
#define SYS_EVENT_CLEARSCR						SYS_CMD_CLEARSCR
#define SYS_EVENT_SETSCR							SYS_CMD_SETSCR
#define SYS_EVENT_SHOWSCRBG					SYS_CMD_SHOWSCRBG
#define SYS_EVENT_HIDESCRBG					SYS_CMD_HIDESCRBG
#define SYS_EVENT_RENDERSCRBG				SYS_CMD_RENDERSCRBG
#define SYS_EVENT_XCOPY							SYS_CMD_XCOPY
#define SYS_EVENT_XREMOVE						SYS_CMD_XREMOVE

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: DECLARE SERVICE REGISTRY */
EZ_SERVICE_REGISTRY_DECLARE(systemService);
/* TODO END */

#ifdef __cplusplus
}
#endif

#endif

