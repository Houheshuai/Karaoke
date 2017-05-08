/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_req.h
** Revision : 1.00											
**																	
** Description: universal data request functions, support multi-thread
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
**	if you define [ ezHandleReqRec_t* handle],  call function [ez_reqNew] to create it
**	if you define [ ezHandleReqRec_t handle],  call function [ez_reqInit] to initialize it, don't need [ez_reqNew]
**	call [ez_reqFree] to release resources in [ez_reqNew]
**	call [ez_reqDeinit] to release resources in [ez_reqInit]
**	call [handle->start] to start a request after [ez_reqNew] or [ez_reqInit]
**	call [handle->reqPage] to request one page data after [handle->start]
**	call [handle->reqCallback] to request data from special position and count
**	call [handle->stop] to finish request data process, cache buffer of request data will be released
**	call [ez_reqFree] to release request resouces if you called [ez_reqNew] before
**	call [ez_reqDeinit] to release request resouces if you called [ez_reqInit] before
**
*/

#ifndef _EZREQ_H_
#define _EZREQ_H_

#include <lib/ezbase/ez_notify.h>

#define EZ_REQ_MAX_STRPARA_SZ			128
#define EZ_REQ_MAX_INTPARA_SZ			4
#define EZ_REQ_START_FLAG					(-1)

/*
* fast convert to ezReq_t
*/
#define ezReq(req) 										((ezReq_t*)req)

/*
* fast convert to ezHandleReqRec_t
*/
#define ezHandleReqRec(handle) 			((ezHandleReqRec_t*)handle)

/*
*	struct of request result  
*/
typedef struct {
	void*							Buffer;
	int								para1;
	int								para2;
	int								para3;

} ezReqResult_t;

/*
*	struct of request command  
*/
typedef struct {
	int								cmd;
	int								subCmd;
	int								intPara[EZ_REQ_MAX_INTPARA_SZ];
	char							strPara[EZ_REQ_MAX_STRPARA_SZ];

	int 							curStartItem;
	int 							focusIndex;

	char							strParaEx[EZ_REQ_MAX_STRPARA_SZ];
	char							SongName[EZ_REQ_MAX_STRPARA_SZ];
} ezReqCmd_t;

/*
*	struct of request  
*/
typedef struct {

	ezNotifyHandle_t			reqNotify;				/* inherit notify, don't modify the position */
	ezReqCmd_t				reqCmd;					/* request command detail */
	ezReqResult_t				reqResult;				/* request result data and parameters */

} ezReq_t;

/*
*	ezHandleReqRec_t type define
*/
typedef struct s_ezHandleReqRec ezHandleReqRec_t;

/* 
* req record callback function
*/
typedef int 					(*ezReqRecCallback_t)(ezHandleReqRec_t*, int, int);

/* 
* req methods 
*/
typedef int 					(*ez_reqMethod_start_t)(ezHandleReqRec_t*, ezReqCmd_t*, int);
typedef void 					(*ez_reqMethod_stop_t)(ezHandleReqRec_t*);
typedef int 					(*ez_reqMethod_reqPage_t)(ezHandleReqRec_t*, int, int);
typedef int 					(*ez_reqMethod_reqNextPage_t)(ezHandleReqRec_t*);
typedef int 					(*ez_reqMethod_reqPrevPage_t)(ezHandleReqRec_t*);

/*
*	req base structure
*/
struct s_ezHandleReqRec {

	ezReq_t						req;

	ezReqRecCallback_t	reqCallback;			/* request record callback function */
	
	int								curPage;
	int								totalPage;
	int								totalItems;
	int								onePageItems;
	int								cursor;
	int								pageLoop;

	/* 
	* req methods 
	*/
	
	/*
	 * Method name		: start
	 * Arguments			: handle - request handle
	 *									cmd - input request command
	 *									onePageItems - one page items count
	 * Return 				: result record count
	 * Description			: start a new request
	*/
	ez_reqMethod_start_t					start;

	/*
	 * Method name		: stop
	 * Arguments			: handle - request handle
	 * Return 				: none
	 * Description			: stop a new request
	*/
	ez_reqMethod_stop_t					stop;

	/*
	 * Method name		: reqPage
	 * Arguments			: handle - req object pointer
	 *									reqStart - request data start address
	 *									cursor - cursor to calc new page number
	 * Return 				: result record count
	 * Description			:  request one page record from 'reqStart'
	*/
	ez_reqMethod_reqPage_t			reqPage;

	/*
	 * Method name		: reqNextPage
	 * Arguments			: handle - req object pointer
	 * Return 				: result record count
	 * Description			:  request next page record by current page parameters
	*/
	ez_reqMethod_reqNextPage_t	reqNextPage;

	/*
	 * Method name		: reqPrevPage
	 * Arguments			: handle - req object pointer
	 * Return 				: result record count
	 * Description			:  request previous page record by current page parameters
	*/
	ez_reqMethod_reqPrevPage_t	reqPrevPage;
	
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_reqInit
 * Arguments      	: handle - req object pointer
 *									reqCallback - request record callback function
 * Return         	: req object address
 * Description    	: initialize a new req object
 *					
*/
extern ezHandleReqRec_t* ez_reqInit(ezHandleReqRec_t* handle, ezReqRecCallback_t reqCallback);

/*
 * Function name  	: ez_reqDeinit
 * Arguments      	: handle - req object pointer
 * Return         	: req object pointer, null is failure
 * Description    	: deinitialize a req object
 *					
*/
extern void ez_reqDeinit(ezHandleReqRec_t* handle);

/*
 * Function name  	: ez_reqNew
 * Arguments      	: reqCallback - request record callback function
 * Return         	: req object address
 * Description    	: create a new req object
 *					
*/
extern ezHandleReqRec_t* ez_reqNew(ezReqRecCallback_t reqCallback);

/*
 * Function name  	: ez_reqFree
 * Arguments      	: handle - req object pointer
 * Return         	: req object pointer, null is failure
 * Description    	: free a req object
 *					
*/
extern void ez_reqFree(ezHandleReqRec_t* handle);

#ifdef __cplusplus
}
#endif

#endif

