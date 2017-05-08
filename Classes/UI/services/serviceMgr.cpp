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
**
*/

#include <k_global.h>
#include <serviceMgr.h>

//jni services registry map
typedef struct 
{
	const char* 				name;
	ezServiceRegistry_t*  	registry;
	ezServiceHandle_t*	hdle;
} JniServiceRegistry_t;

JniServiceRegistry_t gezServices[] = 
{
	{"system", 			systemService, 		NULL},
	{"config", 			configService, 		NULL},
	{"player", 			playerService, 		NULL},
	{"recencoder",	recencoderService,	NULL},
	/*{"localdb", 			localdbService, 		NULL},
	{"kkedev", 			kkedevService, 		NULL},
	{"net",					netService,				NULL},*/
};

/*
 * Function name  	: serviceMgr_create
 * Arguments      	: name - service name, owner - service owner
 * Return         	: service handle
 * Description    	: create a new service object
 *					
*/
ezServiceHandle_t* serviceMgr_create(const char* name, void* owner)
{
	ezServiceRegistry_t* reg = NULL;
	int i;

	for (i=0; i<sizeof(gezServices)/sizeof(JniServiceRegistry_t); i++)
	{
		if (stricmp(gezServices[i].name, name) == 0)
		{
			reg = gezServices[i].registry;
			break;
		}
	}
	if (reg != NULL)
	{
		gezServices[i].hdle =  ez_serviceNew(name, owner, reg);
		return gezServices[i].hdle;
	}
	else
	{
		return NULL;
	}
}

/*
 * Function name  	: serviceMgr_destroy
 * Arguments      	: hdle - service handle
 * Return         	: 0 - succ, <>0 error code
 * Description    	: destroy a service object
 *					
*/
int serviceMgr_destroy(ezServiceHandle_t* hdle)
{
	if (hdle != NULL)
		return ez_serviceFree(hdle);
	else
		return -1;
}


/*
 * Function name  	: serviceMgr_get
 * Arguments      	: name - service name
 * Return         	: service handle
 * Description    	: get a service handle by service name
 *					
*/
ezServiceHandle_t* serviceMgr_get(const char* name)
{
	ezServiceRegistry_t* reg = NULL;
	int i;

	for (i=0; i<sizeof(gezServices)/sizeof(JniServiceRegistry_t); i++)
	{
		if (stricmp(gezServices[i].name, name) == 0)
		{
			return gezServices[i].hdle;
		}
	}
	return NULL;
}


