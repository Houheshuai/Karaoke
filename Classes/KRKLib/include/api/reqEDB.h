/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : reqEDB.h
** Revision : 1.00											
**																	
** Description: multak edb request API
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

#ifndef _REQEDB_H_
#define _REQEDB_H_

#include <lib/ezbase/ez_req.h>
#include <lib/edb/edb.h>
#include <lib/edb/dbapp.h>

#define MAX_DB_INT_PARA				4

/*
* parameter to initialize a new edb request object
*/
typedef struct
{
	DB_HANDLE*					db;
	int 									intPara[MAX_DB_INT_PARA];
	ezReqRecCallback_t		reqRecCallback;
	
} edbInitPara_t;

/*
* edb request type define
*/
typedef struct s_edbReq edbReq_t;

typedef void 						(*edb_setIntFilter_t)(FILTER_PARAM* , int, int, int, int);
typedef void 						(*edb_setStrFilter_t)(FILTER_PARAM*, char*, int, int);
typedef TABLE_HANDLE* (*edb_reqTable_t)(edbReq_t*, char*, FILTER_PARAM*);
typedef int 						(*edb_reqSQLExecute_t)(edbReq_t*, char*);
typedef int 						(*edb_reqSQLFileExecute_t)(edbReq_t*, char*, DB_SHOWPROCESS_CALLBACK, int);

/*
* edb request struct
*/
struct s_edbReq
{
	ezHandleReqRec_t				handleRec;
	DB_HANDLE*						db;

	/* 
	* edb request methods 
	*/

	/*
	 * method name		: setIntFilter
	 * Arguments			: filter - input filter parameter, this parameter will be modified and output
	 *									intPara1 - first integer parameter 
	 *									intPara2 - second integer parameter 
	 *									reset - filter reset flag
	 *									size - interger value size, 1/2/4 bytes
	 * Return 				: none
	 * Description			: setup filter by integer parameter
	*/
	edb_setIntFilter_t				setIntFilter;
	
	/*
	 * method name		: setStrFilter
	 * Arguments			: filter - input filter parameter, this parameter will be modified and output
	 *									strPara - string parameter 
	 *									crt - 1: find the string equal to strPara, 0: find the string bigger than strPara
	 *									reset - filter reset flag
	 * Return 				: none
	 * Description			: setup filter by string parameter
	*/
	edb_setStrFilter_t				setStrFilter;
	
	/*
	 * method name		: reqTable
	 * Arguments			: req - edb request object
	 *									tableName - table name string
	 *									filter -	filter table parameter
	 * Return 				: req table address
	 * Description			: query table by input tablename and filter parameters
	*/
	edb_reqTable_t					reqTable;
	
	/*
	 * method name		: SQLExecute
	 * Arguments			: req - edb request object
	 *									SQLStr - SQL string
	 * Return 				: 0 - succ, <> - fail
	 * Description			: execute a SQL script on db
	*/
	edb_reqSQLExecute_t		SQLExecute;

	/*
	 * method name		: SQLFileExecute
	 * Arguments			: req - edb request object
	 *									SQLFile - SQL script file
	 *									callback - callback in execute process
	 *									cachesz - file cache size in one time fread
	 * Return 				: 0 - succ, <> - fail
	 * Description			: execute a SQL script file on db
	*/
	edb_reqSQLFileExecute_t	SQLFileExecute;
	
};

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: edb_reqInit
 * Arguments      	: req - edb request object
 *									para - edb initialize parameter
 * Return         	: req object address
 * Description    	: initialize a new req object
 *					
*/
extern edbReq_t* edb_reqInit(edbReq_t* req, edbInitPara_t* para);

/*
 * Function name  	: edb_reqDeinit
 * Arguments      	: req - edb request object
 * Return         	: none
 * Description    	: deinitialize an edb req object
 *					
*/
extern void edb_reqDeinit(edbReq_t* req);

/*
 * Function name  	: edb_reqNew
 * Arguments      	: reqCallback - request record callback function
 * Return         	: edb req object address
 * Description    	: create a new edb req object
 *					
*/
extern edbReq_t* edb_reqNew(edbInitPara_t* para);

/*
 * Function name  	: edb_reqFree
 * Arguments      	: req - edb request object
 * Return         	: none
 * Description    	: free an edb req object
 *					
*/
extern void edb_reqFree(edbReq_t* req);


#ifdef __cplusplus
}
#endif 

#endif


