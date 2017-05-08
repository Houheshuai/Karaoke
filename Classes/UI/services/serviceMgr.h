/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : serviceMgr.h
** Revision : 1.00											
**																	
** Description: service manager
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
*/

#ifndef _SERVICE_MGR_H_
#define _SERVICE_MGR_H_

#include <config/config_service.h>
#include <player/player_service.h>
#include <recencoder/recencoder_service.h>
//#include <services/localdb/localdb_service.h>
#include <system/system_service.h>
//#include <services/kkedev/kkedev_service.h>
//#include <services/net/net_service.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: serviceMgr_create
 * Arguments      	: name - service name, owner - service owner
 * Return         	: service handle
 * Description    	: create a new service object
 *					
*/
extern ezServiceHandle_t* serviceMgr_create(const char* name, void* owner);

/*
 * Function name  	: serviceMgr_destroy
 * Arguments      	: hdle - service handle
 * Return         	: 0 - succ, <>0 error code
 * Description    	: destroy a service object
 *					
*/
extern int serviceMgr_destroy(ezServiceHandle_t* hdle);

/*
 * Function name  	: serviceMgr_get
 * Arguments      	: name - service name
 * Return         	: service handle
 * Description    	: get a service handle by service name
 *					
*/
extern ezServiceHandle_t* serviceMgr_get(const char* name);

#ifdef __cplusplus
}
#endif

#endif

