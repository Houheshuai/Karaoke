/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : config_service.h
** Revision : 1.00											
**																	
** Description: configuration service module
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
**	load 
**			easy partern:		hdle->exec(hdle, "load", "/mnt/sdcard/KARAOKE/config.xml");
**			normal partern: 	
**											hdle->setCmdPara(hdle, "load", "filepath", "/mnt/sdcard/KARAOKE/config.xml");
**											hdle->exec(hdle, "load", NULL);
**
** ----------------------------------------------------------
**	unload 
**			easy partern:		hdle->exec(hdle, "unload", "1");
**			normal partern: 	
**											hdle->setCmdPara(hdle, "unload", "autosave", "1");
**											hdle->exec(hdle, "unload", NULL);
**
** ----------------------------------------------------------
**	getval 
**											vol = hdle->exec(hdle, "getval", "TotalVol");
**
** ----------------------------------------------------------
**	setval 
**											hdle->setCmdPara(hdle, "setval", "TotalVol", "100");
**											hdle->setCmdPara(hdle, "setval", "AccomlVol", "100");
**											hdle->setCmdPara(hdle, "setval", "KeyVol", "100");
**											hdle->exec(hdle, "setval", NULL);
**
** ----------------------------------------------------------
**	save 
**											hdle->exec(hdle, "save", NULL);
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

#ifndef _SERVICE_CONFIG_H_
#define _SERVICE_CONFIG_H_

#include <lib/ezbase/ez_service.h>

/*
*========================================
*	config service commands
*========================================
*/
#define CONF_CMD_LOAD								"load"
#define CONF_CMD_UNLOAD						"unload"
#define CONF_CMD_SAVE								"save"
#define CONF_CMD_GETVAL							"getvalue"
#define CONF_CMD_GEDEFAULTTVAL				"getdefaultvalue"
#define CONF_CMD_GETMAXVAL					"getmaxvalue"
#define CONF_CMD_GETMINVAL					"getminvalue"
#define CONF_CMD_SETVAL							"setvalue"
#define CONF_CMD_GETSTRVAL					"getstrvalue"
#define CONF_CMD_SETSTRVAL					"setstrvalue"

/*
*	load cmd parameters name
*/
#define CONF_CMD_LOAD_FILEPATH			"filepath"					// format: filepath=/mnt/sdcard/xxx/....xml

/*
*	unload cmd parameters name
*/
#define CONF_CMD_UNLOAD_AUTOSAVE	"autosave"					// format: autosave=1

/*
*	getstrvalue cmd parameters name
*/
#define CONF_CMD_GETSTRVALUE_VALUE	"value"						// format: value=xxxxxx

/*
*========================================
*	config service events
*========================================
*/
#define CONF_EVENT_LOAD							CONF_CMD_LOAD
#define CONF_EVENT_UNLOAD						CONF_CMD_UNLOAD
#define CONF_EVENT_SAVE							CONF_CMD_SAVE
#define CONF_EVENT_GETVAL						CONF_CMD_GETVAL
#define CONF_EVENT_GETMAXVAL				CONF_CMD_GETMAXVAL
#define CONF_EVENT_GETMINVAL				CONF_CMD_GETMINVAL
#define CONF_EVENT_SETVAL						CONF_CMD_SETVAL
#define CONF_EVENT_GETSTRVAL				CONF_CMD_GETSTRVAL
#define CONF_EVENT_SETSTRVAL					CONF_CMD_SETSTRVAL

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: DECLARE SERVICE REGISTRY */
EZ_SERVICE_REGISTRY_DECLARE(configService);
/* TODO END */

#ifdef __cplusplus
}
#endif

#endif

