/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_service.h
** Revision : 1.00											
**																	
** Description: a service module for multi-thread safe callback
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

#ifndef _EZSERVICE_H_
#define _EZSERVICE_H_

#include <k_define.h>
#include <lib/ezbase/ez_map.h>

#define _WARN_NO_INIT(name) {service_printf("==================================\n");\
															service_printf("= call init first: service[%s]\n", name);\
															service_printf("==================================\n");}

#define _WARN_NO_PARA(name, para) {service_printf("==================================\n");\
															service_printf("= no para : service[%s], para[%s]\n", name, para);\
															service_printf("==================================\n");}

#define _WARN_NO_VALUE(name, para) {service_printf("==================================\n");\
															service_printf("= no value : service[%s], para[%s]\n", name, para);\
															service_printf("==================================\n");}

#define EZ_SERVICE_MAX_NAME_LEN 							(32)
#define EZ_SERVICE_SYNC_TIMEOUT 							(16000)
#define EZ_SERVICE_BEGIN_CMD_EXEC_MAP(srv)		ezServiceRegistry_t srv[] = {
#define EZ_SERVICE_ADD_CMD_EXEC(name, exec)		{name,exec},
#define EZ_SERVICE_END_CMD_EXEC_MAP()				{"NULL",NULL}};

#define EZ_SERVICE_REGISTRY_DECLARE(srv)				extern ezServiceRegistry_t srv[]

/*
* fast convert to ezServiceHandle_t
*/
#define ezServiceHandle(hdle) 										((ezServiceHandle_t*)hdle)

typedef enum
{
	ezService_Succ = KRK_RET_SUCC,
	ezService_Err = KRK_RET_ERR,
	
} ezServiceReturn_et;

typedef enum
{
	ezServiceEvent_None = -1,
	ezServiceEvent_Fail = 0,
	ezServiceEvent_Succ = 1,
	
} ezServiceEventResult_et;

typedef enum
{
	ezServiceEventState_Fired = 0,
	ezServiceEventState_InQueue = 1,
	
} ezServiceEventState_et;

/*
*	service handle type define
*/
typedef struct s_ServiceValMap 
{
	int 						intval;
	const char*			strval;
} ezServiceValMap_t;

/*
*	service handle type define
*/
typedef struct s_ezServiceHandle ezServiceHandle_t;

/* 
* event callback argument 
*/
typedef struct {
	ezServiceHandle_t*		owner;		/* which service fire this event */
	const char*						event;			/* event name */
	int									result;			/* event result */
	unsigned int					handled;		/* handled times */
	
} ServiceEventCBArgs_t;

/* 
* service event callback handle 
*/
typedef int (*handleServiceEventCallback_t)(ServiceEventCBArgs_t*);

/* 
* service cmd execution callback in registry
*/
typedef int (*ezServiceRegistry_exec_t)(ezServiceHandle_t*, const char*, const char*);

/* 
* service externel registry
*/
typedef struct 
{
	const char*							name;
	ezServiceRegistry_exec_t	exec;
} ezServiceRegistry_t;

/* 
* service command parameter
*/
typedef struct 
{
	char*									name;
	char*									value;
	
} ezServicePara_t;

/* 
* service internel cmd map
*/
typedef struct 
{
	char										name[EZ_SERVICE_MAX_NAME_LEN];	// cmd name
	ezServiceRegistry_exec_t	exec; // cmd execution function
	int										sync; // 0 - Asynchronous, 1 - synchronous
	ezMap_t*							para; // cmd execution paramters
	
} ezServiceCmd_t;

/* 
* service internel cmd map
*/
typedef struct 
{
	char													name[EZ_SERVICE_MAX_NAME_LEN]; // event name
	handleServiceEventCallback_t		Callback; // event notify callback
	ezServiceEventResult_et				result;
	ezMap_t*										para; // event notify parameters
	
} ezServiceEvent_t;

/* 
* service method functions 
*/
typedef ezServiceReturn_et 	(*ezServiceMethod_exec_t)(ezServiceHandle_t*, const char*, const char*);
typedef int								(*ezServiceMethod_query_t)(ezServiceHandle_t*, const char*);
typedef ezServiceReturn_et 	(*ezServiceMethod_push_t)(ezServiceHandle_t*, const char*, ezServiceEventResult_et);
typedef ezServiceReturn_et 	(*ezServiceMethod_clear_t)(ezServiceHandle_t*, const char*);
typedef ezServiceReturn_et 	(*ezServiceMethod_clearall_t)(ezServiceHandle_t*);
typedef ezServiceReturn_et 	(*ezServiceMethod_setpara_t)(ezServiceHandle_t*, const char*, const char*, const char*);
typedef ezServicePara_t* 		(*ezServiceMethod_getpara_t)(ezServiceHandle_t* , const char* , int);
typedef int								(*ezServiceMethod_getparacount_t)(ezServiceHandle_t*, const char*);
typedef const char* 				(*ezServiceMethod_getparavalue_t)(ezServiceHandle_t* , const char* , const char* );
typedef const char* 				(*ezServiceMethod_getparavalueat_t)(ezServiceHandle_t* , const char* , int);
typedef int				 				(*ezServiceMethod_getparavalueint_t)(ezServiceHandle_t* , const char* , const char*, int*);
typedef int				 				(*ezServiceMethod_getparavaluestr_t)(ezServiceHandle_t* , const char* , const char*, char*, int);
typedef int				 				(*ezServiceMethod_getparavaluefrommap_t)(ezServiceHandle_t* , const char* , const char*, ezServiceValMap_t*, int, int*);
typedef ezServiceReturn_et 	(*ezServiceMethod_removepara_t)(ezServiceHandle_t*, const char*, const char*);
typedef ezServiceReturn_et 	(*ezServiceMethod_clearpara_t)(ezServiceHandle_t*, const char*);
typedef ezServiceReturn_et 	(*ezServiceMethod_setcallback_t)(ezServiceHandle_t*, const char*, handleServiceEventCallback_t);
typedef handleServiceEventCallback_t 	(*ezServiceMethod_getcallback_t)(ezServiceHandle_t*, const char*);
typedef int								(*ezServiceMethod_update_t)(ezServiceHandle_t*, int);
typedef void 							(*ezServiceMethod_setUserUpdate_t)(ezServiceHandle_t*, ezServiceMethod_update_t);
typedef ezServiceReturn_et (*ezServiceMethod_setThread_t)(ezServiceHandle_t*, int);

/*
*	service base structure
*/
struct s_ezServiceHandle {

	char													name[EZ_SERVICE_MAX_NAME_LEN];
	void*												owner; // service owner
	void*												doer; // service doer
	void*												lock;
	void*												synclock;
	void*												task;
	ezMap_t*										cmdList;
	ezMap_t*										eventList;
	ezMap_t*										pendingEvents;
	ezServiceMethod_update_t			user_update;
	int													syncTimeout;
	
	/* 
	* ezService methods 
	*/

	/*
	 * Method name		: exec
	 * Arguments			: hdle - service object pointer
	 *										name - cmd name string
	 *										para -  para string
	 * Return 				: 0 - succ, <>0 - error code
	 * Description			:  execute a service command
	*/
	ezServiceMethod_exec_t 					exec;
	
	/*
	 * Method name		: sync
	 * Arguments			: hdle - service object pointer
	 *										name - cmd name string
	 *										para -  para string
	 * Return 				: 0 - succ, <>0 - error code
	 * Description			:  execute a service command in sync mode, block here until finished
	*/
	ezServiceMethod_exec_t					sync;

	/*
	 * Method name		: queryEvent
	 * Arguments			: hdle - service object pointer
	 *										name- event name string, query the feedback of this event
	 * Return 				: -1: no event , 0 - found event, result is fail, 1 - found event, result is succ
	 * Description			:  query a cmd feedback event
	*/
	ezServiceMethod_query_t 				queryEvent;

	/*
	 * Method name		: pushEvent
	 * Arguments			: hdle - service object pointer
	 *										name- event name string, query the feedback of this event
	 * Return 				: 0 - event found, <>0 error code
	 * Description			:  push event to list
	*/
	ezServiceMethod_push_t 					pushEvent;
	
	/*
	 * Method name		: fireEvent
	 * Arguments			: hdle - service object pointer
	 *										name- event name string, query the feedback of this event
	 * Return 				: 0 - succ, <>0 - error code
	 * Description			:  call event callback function
	*/
	ezServiceMethod_clear_t 					fireEvent;

	/*
	 * Method name		: removeEvent
	 * Arguments			: hdle - service object pointer
	 *										name- event name string, query the feedback of this event
	 * Return 				: 0 - succ, <>0 - error code
	 * Description			:  remove pending event
	*/
	ezServiceMethod_clear_t 					removeEvent;

	/*
	 * Method name		: clearEvents
	 * Arguments			: hdle - service object pointer
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  clear all event feedback info
	 *					
	*/
	ezServiceMethod_clearall_t				clearEvents;

	/*
	 * Method name		: setCmdPara
	 * Arguments			: hdle - service object pointer
	 *										cmd - cmd name string
	 *										para - para name string
	 *										value - para value string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  add a parameter to a cmd, if para already exist, replace it
	*/
	ezServiceMethod_setpara_t				setCmdPara;

	/*
	 * Method name		: getCmdPara
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										pos - para position in list
	 * Return 				: parameter
	 * Description			:  get cmd parameter by position
	*/
	ezServiceMethod_getpara_t				getCmdPara;

	/*
	 * Method name		: getCmdParaCount
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 * Return 				: cmd parameter count
	 * Description			:  get cmd parameter count
	*/
	ezServiceMethod_getparacount_t	getCmdParaCount;
	
	/*
	 * Method name		: getCmdParaValue
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 * Return 				: value string
	 * Description			:  get cmd parameter value by name
	*/
	ezServiceMethod_getparavalue_t		getCmdParaValue;

	/*
	 * Method name		: getCmdParaValueAt
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										pos - value in this position
	 * Return 				: value string
	 * Description			:  get cmd parameter value by position
	*/
	ezServiceMethod_getparavalueat_t getCmdParaValueAt;

	/*
	 * Method name		: getCmdParaValueInt
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										intval - output integer value address
	 * Return 				: 0 - succ, -1 -  error
	 * Description			:  get cmd parameter value by name, and convert string to integer
	*/
	ezServiceMethod_getparavalueint_t getCmdParaValueInt;

	/*
	 * Method name		: getCmdParaValueStr
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										strval - output string value address
	 *										maxsz - max size of output string
	 * Return 				: 0: succ, -1: error
	 * Description			:  get cmd parameter value by name, and copy string to output value string
	*/
	ezServiceMethod_getparavaluestr_t getCmdParaValueStr;

	/*
	 * Method name		: getCmdParaValueFromMap
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										valmap - int to string map
	 *										mapsz - sizeof(valmap)
	 *										intval - output integer value address
	 * Return 				: 0 - succ, -1 -  error
	 * Description			:  get cmd parameter value by name, and map string to int
	*/
	ezServiceMethod_getparavaluefrommap_t getCmdParaValueFromMap;
	
	/*
	 * Method name		: removeCmdPara
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  remove a parameter from a cmd
	*/
	ezServiceMethod_removepara_t		removeCmdPara;
	
	/*
	 * Method name		: clearCmdPara
	 * Arguments			: hdle - service object pointer
	 *										name - cmd name string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  clear all saved parameters of a cmd
	*/
	ezServiceMethod_clearpara_t			clearCmdPara;
	
	/*
	 * Method name		: setEventPara
	 * Arguments			: hdle - service object pointer
	 *										eventname - event name string
	 *										paraname - para name string
	 *										value - para value string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  add a parameter to a cmd, if para already exist, replace it
	*/
	ezServiceMethod_setpara_t				setEventPara;

	/*
	 * Function name		: getEventPara
	 * Arguments			: hdle - service object pointer
	 *										eventname - event name string
	 *										pos - para position in para list
	 * Return 				: parameter
	 * Description			:  get event parameter by position
	*/
	ezServiceMethod_getpara_t				getEventPara;

	/*
	 * Function name		: getEventParaCount
	 * Arguments			: hdle - service object pointer
	 *										eventname - event name string
	 * Return 				: parameter count
	 * Description			:  get event parameter count
	*/
	ezServiceMethod_getparacount_t	getEventParaCount;

	/*
	 * Method name		: getEventParaValue
	 * Arguments			: hdle - service object pointer
	 *										eventname - event name string
	 *										paraname - para name string
	 * Return 				: value string
	 * Description			:  get event parameter value by name
	*/
	ezServiceMethod_getparavalue_t		getEventParaValue;

	/*
	 * Method name		: getEventParaValueAt
	 * Arguments			: hdle - service object pointer
	 *										eventname - cmd name string
	 *										pos - value in this position
	 * Return 				: value string
	 * Description			:  get event parameter value by position
	*/
	ezServiceMethod_getparavalueat_t getEventParaValueAt;

	/*
	 * Method name		: getEventParaValueInt
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										intval - output integer value address
	 * Return 				: 0 - succ, -1 -  error
	 * Description			:  get event parameter value by name, and convert string to integer
	*/
	ezServiceMethod_getparavalueint_t getEventParaValueInt;

	/*
	 * Method name		: getEventParaValueStr
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										strval - output string value address
	 *										maxsz - max size of output string
	 * Return 				: 0: succ, -1: error
	 * Description			:  get event parameter value by name, and copy string to output value string
	*/
	ezServiceMethod_getparavaluestr_t getEventParaValueStr;

	/*
	 * Method name		: getEventParaValueFromMap
	 * Arguments			: hdle - service object pointer
	 *										cmdname - cmd name string
	 *										paraname - para name string
	 *										valmap - int to string map
	 *										mapsz - sizeof(valmap)
	 *										intval - output integer value address
	 * Return 				: 0 - succ, -1 -  error
	 * Description			:  get event parameter value by name, and map string to int
	*/
	ezServiceMethod_getparavaluefrommap_t getEventParaValueFromMap;
	
	/*
	 * Method name		: removeEventPara
	 * Arguments			: hdle - service object pointer
	 *										eventname - event name string
	 *										paraname - para name string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  remove a parameter from a cmd
	*/
	ezServiceMethod_removepara_t		removeEventPara;
	
	/*
	 * Method name		: clearEventPara
	 * Arguments			: hdle - service object pointer
	 *										name - event name string
	 * Return 				: 0 - succ, <>0 error code
	 * Description			:  clear all saved parameters of a cmd
	*/
	ezServiceMethod_clearpara_t			clearEventPara;
	
	/*
	 * Method name		: setEventCallback
	 * Arguments			: hdle - service object pointer
	 *										name - event name string
	 *										cb - event callback
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  add event callback function, if you add callback function to event
	 *											you can not query anything by query or result method.
	*/
	ezServiceMethod_setcallback_t		setEventCallback;
	
	/*
	 * Method name		: getEventCallback
	 * Arguments			: hdle - service object pointer
	 *										name - event name string
	 * Return 					: cb function
	 * Description			:  get event callback function
	*/
	ezServiceMethod_getcallback_t		getEventCallback;
	
	/*
	 * Method name		: update
	 * Arguments			: hdle - service object pointer, timeElapsed - elapsed time, ms
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  service self update
	*/
	ezServiceMethod_update_t				update;

	/*
	 * Method name		: setThread
	 * Arguments			: hdle - service object pointer
	 *										onoff - thread on/off flag
	 * Return 					: 0 - succ, <>0 error code
	 * Description			:  set service update in single thread mode
	*/
	ezServiceMethod_setThread_t			setThread;

	/*
	 * Method name		: setUserUpdate
	 * Arguments			: hdle - service object pointer
	 *										cb - user update callback function
	 * Return 					: none
	 * Description			:  set user update callback function, it will be folk in service update
	*/
	ezServiceMethod_setUserUpdate_t	setUserUpdate;
	
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_serviceInit
 * Arguments      	: hdle - input service object, owner - service owner, registry - cmd registry
 * Return         	: service object pointer, null is failure
 * Description    	: init a new service object
 *					
*/
extern ezServiceHandle_t* ez_serviceInit(ezServiceHandle_t* hdle, const char* name, void * owner, ezServiceRegistry_t* registry);

/*
 * Function name  	: ez_serviceDeinit
 * Arguments      	: hdle - input service object pointer
 * Return         	: none
 * Description    	: deinitialize a service object
 *					
*/
extern void ez_serviceDeinit(ezServiceHandle_t* hdle);

/*
 * Function name  	: ez_serviceNew
 * Arguments      	: name - service name, owner - service owner, registry - cmd registry
 * Return         	: service object pointer, null is failure
 * Description    	: create a new service object
 *					
*/
extern ezServiceHandle_t* ez_serviceNew(const char* name, void* owner, ezServiceRegistry_t* registry);

/*
 * Function name  	: ez_serviceFree
 * Arguments      	: hdle - notify object pointer
 * Return         	: 0 - succ, <>0 - error code
 * Description    	: free a notify object
 *					
*/
extern int ez_serviceFree(ezServiceHandle_t* hdle);

#ifdef __cplusplus
}
#endif

#endif

