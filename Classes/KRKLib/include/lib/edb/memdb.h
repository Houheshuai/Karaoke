/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : mem_db.h
** Revision : 1.00											
**																	
** Description: a simple database in memory, based on EDB module
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
**
*/

#ifndef _MEM_DB_H_
#define _MEM_DB_H_

#include <lib/edb/edb.h>

/*
*	table create parameters
*/
typedef struct {
	int 								keyCount;				/* count of key in creating table */
	int								recCount;				/* count of maximum record in creating table */
	TABLE_KEY_INFO*		keyInf;					/* keyInfo */
	const char*					tableName;			/* table name string */
	
} memdb_table_para_t;

/*
*	mem_db create parameters
*/
typedef struct {
	int 					poolsz;					/* pool buffer size for dynamic length strings */
	const char* 	tmpFileName;		/* database tmp file name string */
	
} memdb_para_t;

/*
*	mem_db base structure
*/
typedef struct {
	DB_HANDLE* 	db_hdle;
	int 					poolsz;					/* pool buffer size for dynamic length strings */
	
} memdb_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: memdb_table_new
 * Arguments      	: mdb - memdb handle
 *									para - create parameter
 * Return         	: memdb pointer
 * Description    	: new a table in memdb
 *					
*/
extern TABLE_HANDLE* memdb_table_new(memdb_t*mdb, memdb_table_para_t* para);

/*
 * Function name  	: memdb_table_free
 * Arguments      	: tbl - table handle
 * Return         	: none
 * Description    	: free a table in memdb
 *					
*/
extern void memdb_table_free(TABLE_HANDLE* tbl);

/*
 * Function name  	: memdb_new
 * Arguments      	: para - create parameter
 * Return         	: memdb pointer
 * Description    	: new a memdb
 *					
*/
extern memdb_t* memdb_new(memdb_para_t* para);

/*
 * Function name  	: memdb_free
 * Arguments      	: memdb pointer
 * Return         	: none
 * Description    	: free a memdb
 *					
*/
extern void memdb_free(memdb_t* mdb);

#ifdef __cplusplus
}
#endif

#endif

