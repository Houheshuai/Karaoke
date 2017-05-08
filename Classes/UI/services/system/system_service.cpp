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
*/

#include <k_global.h>
#include <lib/ezbase/ez_config.h>
#include <system/system_service.h>
#include "archConfig.h"

#include "CEGUI.h"

#define _WARN_NO_INITGL(name) {service_printf("==================================\n");\
															service_printf("= call initGL first: service[%s]\n", name);\
															service_printf("==================================\n");}

#define SYS_RES_PATH_MAX 256

/*
*========================================
*	system service handle
*========================================
*/
typedef struct 
{
	char 					resPath[SYS_RES_PATH_MAX];
	int						screenWidth;
	int						screenHeight;
	gdi_texture_t 		bgPic;
	
	
} systemServiceHandle_t;

//----------------------------------------------------------------------------//
static int system_service_init(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	const char* respath = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_INIT_RESPATH);
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int scrw = 0;
	int scrh = 0;
	int resw = 0;
	int resh = 0;
	
	if (respath == NULL)
		respath = para;
	
	if (hdle->doer == NULL)
	{
		if (respath != NULL)
		{
			systemServiceHandle_t* syshdle = (systemServiceHandle_t*)calloc(1, sizeof(systemServiceHandle_t));
			const char * pval;
			pval = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_INIT_RES_W);
			if (pval != NULL)
			{
				resw = atoi(pval);
			}
			pval = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_INIT_RES_H);
			if (pval != NULL)
			{
				resh = atoi(pval);
			}

			if (krk_arch_init(respath, resw, resh) != KRK_RET_SUCC)
			{
				hdle->pushEvent(hdle, SYS_EVENT_INIT, ezServiceEvent_Fail);
				return ezService_Err;
			}
			strncpy(syshdle->resPath, respath, sizeof(syshdle->resPath));
			hdle->doer = (void*)syshdle;
			result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, SYS_CMD_INIT_RESPATH);
		}
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= service already initialized: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, SYS_EVENT_INIT, result);
	return (hdle->doer != NULL)? ezService_Succ : ezService_Err;
}

//----------------------------------------------------------------------------//
static int system_service_deinit(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		krk_arch_deinit();
		free(hdle->doer);
		hdle->doer = NULL;
		result = ezServiceEvent_Succ;
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= service already deinitialized: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, SYS_EVENT_DEINIT, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_initGL(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
		
	if (hdle->doer != NULL)
	{
		systemServiceHandle_t* syshdle = (systemServiceHandle_t*)(hdle->doer);
		int scrw, scrh;
		
		const char* pval = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_INITGL_SCR_W);
		if (pval != NULL)
		{
			scrw = atoi(pval);
		}
		else
		{
			_WARN_NO_PARA(hdle->name, SYS_CMD_INITGL_SCR_W);
			hdle->pushEvent(hdle, SYS_EVENT_INIT, ezServiceEvent_Fail);
			return ezService_Err;
		}
		pval = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_INITGL_SCR_H);
		if (pval != NULL)
		{
			scrh = atoi(pval);
		}
		else
		{
			_WARN_NO_PARA(hdle->name, SYS_CMD_INITGL_SCR_H);
			hdle->pushEvent(hdle, SYS_EVENT_INIT, ezServiceEvent_Fail);
			return ezService_Err;
		}

		syshdle->screenWidth = scrw;
		syshdle->screenHeight = scrh;
		
		//new CEGUI::OpenGL_GDI();

		result = ezServiceEvent_Succ;
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= service already initialized: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, SYS_EVENT_INITGL, result);
	return (result == ezServiceEvent_Succ)? ezService_Succ : ezService_Err;
}

//----------------------------------------------------------------------------//
static int system_service_deinitGL(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		systemServiceHandle_t* syshdle = (systemServiceHandle_t*)(hdle->doer);
		if (syshdle->bgPic.texture != NULL)
			gdi_release_imgtexture(&syshdle->bgPic);
		result = ezServiceEvent_Succ;


		/*
		CEGUI::OpenGL_GDI* gdi = (CEGUI::OpenGL_GDI*)(CEGUI::M3D_GDI::getSingletonPtr());
		if (gdi != NULL)
		{
			delete gdi;
			
		}
		else
		{
			service_printf("==================================\n");
			service_printf("= GL display already deinitialized: service[%s]\n", hdle->name);
			service_printf("==================================\n");
		}*/
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= service already deinitialized: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, SYS_EVENT_DEINITGL, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_clearscr(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		result = ezServiceEvent_Succ;

		/*
		CEGUI::OpenGL_GDI* gdi = (CEGUI::OpenGL_GDI*)(CEGUI::M3D_GDI::getSingletonPtr());
		if (gdi != NULL)
		{
			gdi->clearScreen();	
		}
		else
		{
			_WARN_NO_INITGL(hdle->name);
		}*/
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, SYS_EVENT_CLEARSCR, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_setscr(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		/*CEGUI::OpenGL_GDI* gdi = (CEGUI::OpenGL_GDI*)(CEGUI::M3D_GDI::getSingletonPtr());
		if (gdi != NULL)
		{
			int x, y, w, h;
			const char* pvalue = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_SETSCRSIZE_X);
			if (pvalue != NULL)
			{
				x = atoi(pvalue);
			}
			else
			{
				_WARN_NO_PARA(hdle->name,SYS_CMD_SETSCRSIZE_X);
				hdle->pushEvent(hdle, SYS_EVENT_SETSCR, ezServiceEvent_Fail);
				return ezService_Err;
			}
			pvalue = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_SETSCRSIZE_Y);
			if (pvalue != NULL)
			{
				y = atoi(pvalue);
			}
			else
			{
				_WARN_NO_PARA(hdle->name,SYS_CMD_SETSCRSIZE_Y);
				hdle->pushEvent(hdle, SYS_EVENT_SETSCR, ezServiceEvent_Fail);
				return ezService_Err;
			}
			pvalue = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_SETSCRSIZE_W);
			if (pvalue != NULL)
			{
				w = atoi(pvalue);
			}
			else
			{
				_WARN_NO_PARA(hdle->name,SYS_CMD_SETSCRSIZE_W);
				hdle->pushEvent(hdle, SYS_EVENT_SETSCR, ezServiceEvent_Fail);
				return ezService_Err;
			}
			pvalue = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_SETSCRSIZE_H);
			if (pvalue != NULL)
			{
				h = atoi(pvalue);
			}
			else
			{
				_WARN_NO_PARA(hdle->name,SYS_CMD_SETSCRSIZE_H);
				hdle->pushEvent(hdle, SYS_EVENT_SETSCR, ezServiceEvent_Fail);
				return ezService_Err;
			}
			gdi->setScreen(x, y, w, h);
			result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_INITGL(hdle->name);
		}*/
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, SYS_EVENT_SETSCR, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_showscrbg(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		systemServiceHandle_t* syshdle = (systemServiceHandle_t*)hdle->doer;
		if (para != NULL)
		{
			gdi_release_imgtexture(&syshdle->bgPic);
			gdi_load_imgtexture(para, &(syshdle->bgPic));
			syshdle->bgPic.x = 0.0f;
			syshdle->bgPic.y = 0.0f;
			syshdle->bgPic.width = 1.0f;
			syshdle->bgPic.height = 1.0f;
		}
		result = ezServiceEvent_Succ;

		/*
		CEGUI::OpenGL_GDI* gdi = (CEGUI::OpenGL_GDI*)(CEGUI::M3D_GDI::getSingletonPtr());
		if (gdi != NULL)
		{
			
		}
		else
		{
			_WARN_NO_INITGL(hdle->name);
		}*/
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, SYS_EVENT_SHOWSCRBG, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_hidescrbg(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (hdle->doer != NULL)
	{
		systemServiceHandle_t* syshdle = (systemServiceHandle_t*)hdle->doer;
		if (para != NULL)
		{
			gdi_release_imgtexture(&syshdle->bgPic);
		}
		result = ezServiceEvent_Succ;

		/*
		CEGUI::OpenGL_GDI* gdi = (CEGUI::OpenGL_GDI*)(CEGUI::M3D_GDI::getSingletonPtr());
		if (gdi != NULL)
		{
			
		}
		else
		{
			_WARN_NO_INITGL(hdle->name);
		}*/
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, SYS_EVENT_HIDESCRBG, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int system_service_renderscrbg(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	if (hdle->doer != NULL)
	{
		systemServiceHandle_t* syshdle = (systemServiceHandle_t*)hdle->doer;
		Trape4 bgTrape;
		
		bgTrape.lt.x = 0;
		bgTrape.lt.y = 0;
		bgTrape.lb.x = 0;
		bgTrape.lb.y = RES_RESO_HEIGHT;
		bgTrape.rt.x = RES_RESO_WIDTH;
		bgTrape.rt.y = 0;
		bgTrape.rb.x = RES_RESO_WIDTH;
		bgTrape.rb.y = RES_RESO_HEIGHT;

		gdi_draw_texture(&syshdle->bgPic, &bgTrape, 1.0f, &syshdle);
		return 0;
	}
	return -1;
}

//----------------------------------------------------------------------------//
static int system_service_xcopy(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	if (hdle->doer != NULL)
	{
		const char* src = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_XCOPY_SRC);
		const char* dst = hdle->getCmdParaValue(hdle, cmdname, SYS_CMD_XCOPY_DST);
		int ret;
		
		if (src == NULL) {
			service_printf("system_service_xcopy -> NO SRC \n");
			hdle->pushEvent(hdle, SYS_EVENT_XCOPY, ezServiceEvent_Fail);
			return ezService_Err;
		}
		if (dst == NULL) {
			service_printf("system_service_xcopy -> NO DST \n");
			hdle->pushEvent(hdle, SYS_EVENT_XCOPY, ezServiceEvent_Fail);
			return ezService_Err;
		}
		ret = krk_xcopy(dst, src, 1024*256, NULL);
		hdle->pushEvent(hdle, SYS_EVENT_XCOPY, (ret==ezService_Succ)? ezServiceEvent_Succ : ezServiceEvent_Fail);
		return ret;
	}
	hdle->pushEvent(hdle, SYS_EVENT_XCOPY, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int system_service_xremove(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	if (hdle->doer != NULL)
	{
		int ret;
		
		if (para == NULL) {
			service_printf("system_service_remove -> NO PARA \n");
			hdle->pushEvent(hdle, SYS_EVENT_XREMOVE, ezServiceEvent_Fail);
			return ezService_Err;
		}
		
		ret = krk_xremove(para);
		hdle->pushEvent(hdle, SYS_EVENT_XREMOVE, (ret==ezService_Succ)? ezServiceEvent_Succ : ezServiceEvent_Fail);
		return ret;
	}
	hdle->pushEvent(hdle, SYS_EVENT_XREMOVE, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
EZ_SERVICE_BEGIN_CMD_EXEC_MAP(systemService) 
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_INIT,						system_service_init)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_DEINIT,					system_service_deinit)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_INITGL,					system_service_initGL)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_DEINITGL,				system_service_deinitGL)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_CLEARSCR,			system_service_clearscr)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_SETSCR,				system_service_setscr)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_SHOWSCRBG,		system_service_showscrbg)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_HIDESCRBG,			system_service_hidescrbg)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_RENDERSCRBG,	system_service_renderscrbg)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_XCOPY,					system_service_xcopy)
	EZ_SERVICE_ADD_CMD_EXEC(SYS_CMD_XREMOVE,			system_service_xremove)
EZ_SERVICE_END_CMD_EXEC_MAP()
//----------------------------------------------------------------------------//

