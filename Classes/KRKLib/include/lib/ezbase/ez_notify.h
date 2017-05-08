/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_notify.h
** Revision : 1.00											
**																	
** Description: universal notify functions, support multi-thread
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
**	if you define [ ezNotifyHandle_t* handle],  call function [ez_notifyNew] to create it
**	if you define [ ezNotifyHandle_t handle],  call function [ez_notifyInit] to initialize it, don't need [ez_notifyNew]
**	call [ez_notifyFree] to release resources in [ez_notifyNew]
**	call [ez_notifyDeinit] to release resources in [ez_notifyInit]
**
**	notify query methods:
**		call [query] to query a notify in asynchronous mode
**		call [wait] to query a notify in synchronous mode
**
**	notify read method:
**		call [pop] to pop a notify on the top of list
**
**	notify write method:
**		call [push] to push a notify to the end of list
**
**	notify clear method:
**		call [clear]  to clear all notify in the list
**
**	notify erase method:
**		call [erase]  to erase notify in special position of the list
**
**	event methods
**		call [addEvent] to register event handle function to a notify ID
**		call [removeEvent] to unregister event handle function from a notify ID
**		call [fireEvent] to call the event handle function register to a notify ID
**		call [clearEvent] to clear all registered event handle functions
**	
**	synchonous mode setting and check
**		[isSync]
**		[setSync]
*/

#ifndef _EZNOTIFY_H_
#define _EZNOTIFY_H_

#include <k_define.h>
#include <lib/ezbase/ez_map.h>

/*
* fast convert to ezNotifyObj_t
*/
#define ezNotifyHandle(handle) 										((ezNotifyHandle_t*)handle)

#define EZ_NOTIFY_PARA_SZ	4

typedef enum
{
	ezNotify_Succ = KRK_RET_SUCC,
	ezNotify_Err = KRK_RET_ERR,
	
} ezNotifyReturn_et;

typedef enum
{
	ezNotifyConfig_none = 0,
	ezNotifyConfig_sycn = (1<<0),											/* 1: wait notify in block mode, 0: not block mode */
	ezNotifyConfig_pend = (1<<1),											/* 1: pend thread in pop, until one notify arrived, 0: no pend */

	ezNotifyConfig_
	
} ezNotifyConfig_t;

/*
*	notify base structure
*/
typedef struct {
	int 										notifyId;										/* notify id */
	int 										result;										/* notify result, true or false */
	int 										para[EZ_NOTIFY_PARA_SZ];	/* parameters */

} ezNotify_t;

/* 
* notify event argument 
*/
typedef struct {
	ezNotify_t							notify;			/* notify data */
	void*									owner;			/* who own this notify */
	unsigned int							handled;		/* handled times */
	
} NotifyEventArgs_t;

/*
*	notify handle type define
*/
typedef struct s_ezNotifyHandle ezNotifyHandle_t;

/* 
* notify event handle 
*/
typedef int (*handleNotifyCallback_t)(NotifyEventArgs_t*);

/* 
* waiting callback function in sync mode
*/
typedef int (*handleNotifyWaitCallback_t)(ezNotifyHandle_t*, void*);

/* 
* notify method functions 
*/
typedef void 							(*ezNotifyMethod_lock_t)(ezNotifyHandle_t*);
typedef void 							(*ezNotifyMethod_unlock_t)(ezNotifyHandle_t*);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_push_t)(ezNotifyHandle_t*, ezNotify_t*);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_pop_t)(ezNotifyHandle_t*, ezNotify_t*);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_query_t)(ezNotifyHandle_t*, ezNotify_t*, int);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_wait_t)(ezNotifyHandle_t*, ezNotify_t*, int, int);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_erase_t)(ezNotifyHandle_t*, int);
typedef void 							(*ezNotifyMethod_clear_t)(ezNotifyHandle_t*);
typedef int 							(*ezNotifyMethod_getSize_t)(ezNotifyHandle_t*);
typedef ezNotifyReturn_et	(*ezNotifyMethod_fireEvent_t)(ezNotifyHandle_t*, ezNotify_t*);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_addEvent_t)(ezNotifyHandle_t*, int, handleNotifyCallback_t);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_removeEvent_t)(ezNotifyHandle_t*, int);
typedef void 							(*ezNotifyMethod_clearEvent_t)(ezNotifyHandle_t*);
typedef ezNotifyReturn_et 	(*ezNotifyMethod_queryEvent_t)(ezNotifyHandle_t* , int* , handleNotifyCallback_t* , int );
typedef int 							(*ezNotifyMethod_isSync_t)(ezNotifyHandle_t*);
typedef void 							(*ezNotifyMethod_setSync_t)(ezNotifyHandle_t*, int);
typedef void 							(*ez_notifySetWaitCallback_t)(ezNotifyHandle_t* , handleNotifyWaitCallback_t);

/*
*	notify event set
*/
typedef struct {
	int 										notifyId;				/* notify id */
	handleNotifyCallback_t 		handle;					/* notify event handle */
} ezNotifyEventSet_t;

/*
*	notify base structure
*/
struct s_ezNotifyHandle {

	int										mask;
	ezMap_t* 							notifyList;
	ezMap_t*							eventList;

	void*									notifyMutex;
	int 										syncMode;

	void*									waitPara;
	handleNotifyWaitCallback_t wait_cb;
	
	/* 
	* ezNotify methods 
	*/

	/*
	 * Method name		: lock
	 * Arguments			: handle - notify object pointer
	 * Return 				: none
	 * Description			:  a notify object multi-thread lock
	*/
	ezNotifyMethod_lock_t 					lock;

	/*
	 * Method name		: unlock
	 * Arguments			: handle - notify object pointer
	 * Return 				: none
	 * Description			:  a notify object multi-thread lock
	*/
	ezNotifyMethod_unlock_t 				unlock;

	/*
	 * Method name		: push
	 * Arguments			: handle - notify object pointer, notify - input notify data
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  push a notify data to notify list
	*/
	ezNotifyMethod_push_t 					push;

	/*
	 * Method name		: syncPush
	 * Arguments			: handle - notify object pointer, notify - input notify data
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  push a notify data to notify list, wait until it's received
	*/
	ezNotifyMethod_push_t 					syncPush;

	/*
	 * Method name		: pop
	 * Arguments			: handle - notify object pointer, notify - output notify data
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  pop first notify data from notify list
	*/
	ezNotifyMethod_pop_t 					pop;

	/*
	 * Method name		: erase
	 * Arguments				: handle - notify object pointer, pos - erase notify at this position
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  erase special notify data at special position in notify list
	 *					
	*/
	ezNotifyMethod_erase_t				erase;

	/*
	 * Method name		: get
	 * Arguments				: handle - notify object pointer, notify - output notify data, pos - get notify at this position
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  get special notify data at special position in notify list
	 *					
	*/
	ezNotifyMethod_query_t				get;

	/*
	 * Method name		: set
	 * Arguments				: handle - notify object pointer, notify - output notify data, pos - get notify at this position
	 * Return 					: 0 - succ, <>0 error code
	 * Description			: set special notify data at special position in notify list
	 *					
	*/
	ezNotifyMethod_query_t				set;

	/*
	 * Method name		: query
	 * Arguments			: handle - notify object pointer, notify - output notify data, notifyId - input notify ID
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  pop a special notify data from notify list, by notify ID
	*/
	ezNotifyMethod_query_t 				query;
	
	/*
	 * Method name		: search
	 * Arguments			: handle - notify object pointer, notify - output notify data, notifyId - input notify ID
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  search a special notify data from notify list, by notify ID, don't pop it
	*/
	ezNotifyMethod_query_t 				search;

	/*
	 * Method name		: wait
	 * Arguments			: handle - notify object pointer, notify - output notify data, notifyId - input notify ID, timeout - wait time in ms
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  pop a special notify data from notify list, by notify ID, if not exist, waiting
	*/
	ezNotifyMethod_wait_t 					wait;

	/*
	 * Method name		: clear
	 * Arguments			: handle - notify object pointer
	 * Return 				: none
	 * Description			:  clear all notify in list
	*/
	ezNotifyMethod_clear_t 					clear;

	/*
	 * Method name		: ez_notifySize
	 * Arguments				: handle - notify object pointer, notify - output notify data
	 * Return 					: count of notify in list
	 * Description			:  get count of notify in notify list
	 *					
	*/
	ezNotifyMethod_getSize_t					getSize;

	/*
	 * Method name		: fireEvent
	 * Arguments			: handle - notify object pointer, notify - input notify data 
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  fire a notify event by input notify data
	*/
	ezNotifyMethod_fireEvent_t 			fireEvent;

	/*
	 * Method name		: addEvent
	 * Arguments			: handle - notify object pointer, notifyId - notify ID, callback - notify callback function 
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  set a event handle function for a special notifyId
	*/
	ezNotifyMethod_addEvent_t 			addEvent;

	/*
	 * Method name		: removeEvent
	 * Arguments			: handle - notify object pointer, notifyId - notify ID
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  delete a event handle function for a special notifyId
	*/
	ezNotifyMethod_removeEvent_t 	removeEvent;
	
	/*
	 * Method name		: clearEvent
	 * Arguments			: handle - notify object pointer
	 * Return 				: none
	 * Description			:  delete all event handle functions
	*/
	ezNotifyMethod_clearEvent_t 		clearEvent;

	/*
	 * Method name		: queryEvent
	 * Arguments				: handle - notify object pointer, notifyId - output notify ID, callback - output callback, pos - input position in list
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  query event handle from list
	 *					
	*/
	ezNotifyMethod_queryEvent_t		queryEvent;

	/*
	 * Method name		: isSync
	 * Arguments			: handle - notify object pointer
	 * Return 				: 0 - not sync mode, > 0 sync mode
	 * Description			:  check sync mode
	*/
	ezNotifyMethod_isSync_t 				isSync;

	/*
	 * Method name		: setSync
	 * Arguments			: handle - notify object pointer, mode - sync mode
	 * Return 				: none
	 * Description			:  set sync mode
	*/
	ezNotifyMethod_setSync_t 			setSync;

	/*
	 * Method name		: setSyncCallback
	 * Arguments				: handle - notify object pointer, mode - sync mode
	 * Return 					: none
	 * Description			:  set sync mode waiting callback
	 *					
	*/
	ez_notifySetWaitCallback_t			setSyncCallback;
	
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_notifyInit
 * Arguments      	: handle - input notify object, syncmode - work mode config
 * Return         	: notify object pointer, null is failure
 * Description    	: init a new notify object
 *					
*/
extern ezNotifyHandle_t* ez_notifyInit(ezNotifyHandle_t* handle, int mode);

/*
 * Function name  	: ez_notifyDeinit
 * Arguments      	: handle - input notify object pointer
 * Return         	: none
 * Description    	: deinitialize a notify object
 *					
*/
extern void ez_notifyDeinit(ezNotifyHandle_t* handle);

/*
 * Function name  	: ez_notifyNew
 * Arguments      	: syncmode - work mode config
 * Return         	: notify object pointer, null is failure
 * Description    	: create a new notify object
 *					
*/
extern ezNotifyHandle_t* ez_notifyNew(int mode);

/*
 * Function name  	: ez_notifyFree
 * Arguments      	: handle - notify object pointer
 * Return         	: notify object pointer, null is failure
 * Description    	: free a notify object
 *					
*/
extern void ez_notifyFree(ezNotifyHandle_t* handle);

#ifdef __cplusplus
}
#endif

#endif

