/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : config_service.c
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
*/

#include <k_global.h>
#include <lib/ezbase/ez_config.h>
#include <config/config_service.h>

#define _WARN_NO_LOAD(name) {service_printf("==================================\n");\
															service_printf("= load config first: service[%s]\n", name);\
															service_printf("==================================\n");}

//----------------------------------------------------------------------------//
static int config_service_load(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	const char* filepath = hdle->getCmdParaValue(hdle, cmdname, CONF_CMD_LOAD_FILEPATH);
	int lan = 0;
	ezServiceEventResult_et result;
	int ret;
	
	if (filepath == NULL)
		filepath = para;
	
	if (hdle->doer == NULL)
	{
		if (filepath != NULL)
		{
			char bak[256];
			sprintf(bak, "%s.bak", filepath);
			
			hdle->doer = ez_config_load(filepath);
			if (hdle->doer == NULL) {
				krk_fcopy(filepath, bak, 32*1024, NULL);
				hdle->doer = ez_config_load(filepath);
				service_printf("NO CONFIG FILE, RECOVER FROM BACKUP\n");
			} else if (!krk_fexist(bak)) {
				krk_fcopy(bak, filepath, 32*1024, NULL);
				service_printf("NO CONFIG BAK FILE, BACKUP\n");
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, CONF_CMD_LOAD_FILEPATH);
		}
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= config load already: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	if (hdle->doer != NULL)
	{
		result = ezServiceEvent_Succ;
		ret = ezService_Succ;
	}
	else
	{
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	hdle->pushEvent(hdle, CONF_EVENT_LOAD, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_unload(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result;
	if (hdle->doer != NULL)
	{
		const char* pvalue = hdle->getCmdParaValue(hdle, cmdname, CONF_CMD_UNLOAD_AUTOSAVE);
		int ret;
		int autosave = 0;

		if (pvalue == NULL)
			pvalue = para;
		if (pvalue != NULL)
			autosave = atoi(pvalue);
			
		ret = ez_config_unload((ezConfig_t*)(hdle->doer), autosave);
		result = ezServiceEvent_Succ;
		hdle->doer = NULL;
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= config unload already: service[%s]\n", hdle->name);
		service_printf("==================================\n");
		result = ezServiceEvent_Fail;
	}
	hdle->pushEvent(hdle, CONF_EVENT_UNLOAD, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int config_service_getval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result;
	int ret;
	
	if (conf != NULL)
	{
		ret = ez_config_get_value(conf, para);
		result = ezServiceEvent_Succ;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	
	hdle->pushEvent(hdle, CONF_EVENT_GETVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_getdefaultval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result;
	int ret;
	
	if (conf != NULL)
	{
		ret = ez_config_get_default(conf, para);
		result = ezServiceEvent_Succ;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	
	hdle->pushEvent(hdle, CONF_EVENT_GETMAXVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_getmaxval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result;
	int ret;
	
	if (conf != NULL)
	{
		ret = ez_config_get_max(conf, para);
		result = ezServiceEvent_Succ;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	
	hdle->pushEvent(hdle, CONF_EVENT_GETMAXVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_getminval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result;
	int ret;
	
	if (conf != NULL)
	{
		ret = ez_config_get_min(conf, para);
		result = ezServiceEvent_Succ;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	
	hdle->pushEvent(hdle, CONF_EVENT_GETMINVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_setval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	
	if (conf != NULL)
	{
		ezServicePara_t* ppara;
		int count = hdle->getCmdParaCount(hdle, cmdname);
		int i;

		KRK_PRINTF("config_service_setval, count=%d\n", count);
		for (i=0; i<count; i++)
		{
			ppara = hdle->getCmdPara(hdle, cmdname, i);
			if (ppara != NULL)
			{
				KRK_PRINTF("config_service_setval, value=%s\n", ppara->value);
				ez_config_set_value(conf, ppara->name, atoi(ppara->value));
				ret++;
			}
		}
		hdle->clearCmdPara(hdle, cmdname);
		ret = ret? ezService_Succ : ezService_Err;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		ret = ezService_Err;
	}
	if (ret == ezService_Succ)
		result = ezServiceEvent_Succ;
	hdle->pushEvent(hdle, CONF_EVENT_SETVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_getstrval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;
	
	if (conf != NULL)
	{
		int val = ez_config_get_value(conf, para);
		char* pvalue = ez_config_get_option_items_str(conf, para, val);
		if (pvalue != NULL)
		{
			hdle->setEventPara(hdle, CONF_EVENT_GETSTRVAL, CONF_CMD_GETSTRVALUE_VALUE, pvalue);
			ret = ezService_Succ;
			result = ezServiceEvent_Succ;
		}
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
	}
	
	hdle->pushEvent(hdle, CONF_EVENT_GETSTRVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_setstrval(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezConfig_t* conf = (ezConfig_t*)(hdle->doer);
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	
	if (conf != NULL)
	{
		ezServicePara_t* ppara;
		int i;

		for (i=0; i<hdle->getCmdParaCount(hdle, cmdname); i++)
		{
			ppara = hdle->getCmdPara(hdle, cmdname, i);
			if (ppara != NULL)
			{
				ez_config_set_strvalue(conf, ppara->name, ppara->value);
				ret++;
			}
		}
		hdle->clearCmdPara(hdle, cmdname);
		ret = ret? ezService_Succ : ezService_Err;
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		ret = ezService_Err;
	}
	if (ret == ezService_Succ)
		result = ezServiceEvent_Succ;
	hdle->pushEvent(hdle, CONF_EVENT_SETSTRVAL, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int config_service_save(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret;
	
	if (hdle->doer != NULL)
	{			
		ret = ez_config_save((ezConfig_t*)(hdle->doer));
	}
	else
	{
		_WARN_NO_LOAD(hdle->name);
		ret = ezService_Err;
	}
	if (ret == ezService_Succ)
		result = ezServiceEvent_Succ;
	hdle->pushEvent(hdle, CONF_EVENT_SAVE, result);
	return ret;
}

//----------------------------------------------------------------------------//
EZ_SERVICE_BEGIN_CMD_EXEC_MAP(configService) 
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_LOAD,				config_service_load)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_UNLOAD,			config_service_unload)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_SAVE,				config_service_save)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_SETVAL,			config_service_setval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_GETVAL,			config_service_getval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_GEDEFAULTTVAL,		config_service_getdefaultval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_GETMAXVAL,	config_service_getmaxval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_GETMINVAL,	config_service_getminval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_SETSTRVAL,		config_service_setstrval)
	EZ_SERVICE_ADD_CMD_EXEC(CONF_CMD_GETSTRVAL,		config_service_getstrval)
EZ_SERVICE_END_CMD_EXEC_MAP()
//----------------------------------------------------------------------------//

