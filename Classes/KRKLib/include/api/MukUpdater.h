/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MukUpdater.h
** Revision : 1.00											
**																	
** Description: muk update api
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

#ifndef _MUK_UPDATER_H_
#define _MUK_UPDATER_H_

#include <lib/update/reqData.h>
#include <lib/update/ReqConvSql.h>

#define MUK_UPDATE_PATH_SZ		128

/*
* update event type
*/
enum
{
	MU_EVENT_NONE = 0,
	MU_EVENT_BEGIN,
	MU_EVENT_PERCENT,
	MU_EVENT_UPDATE_DB,
	MU_EVENT_END,
	MU_EVENT_ERR,
};

typedef int (*updateMukEventCbf)(int,void*, void*);
typedef	updateMukEventCbf updateMukCb_t;

/*
* muk update input parameter
*/
typedef struct 
{
	int 									db_type;														/* 0- edb, 1-sqlite db*/
	char 								db_src[MUK_UPDATE_PATH_SZ];				/* source db path */
	char 								db_dest[MUK_UPDATE_PATH_SZ];				/* destiny db path */
	char									muk_path[MUK_UPDATE_PATH_SZ];			/* muk files folder */
	char*								tmp_fn;															/* tmp file name */
	updateMukCb_t				event_cb;														/* update event callback function */
	int									req_charset;													/* request name string charset, 0-utf8, 1-unicode */			
	int									def_charset;													/* default name string charset, 0-utf8, 1-unicode */			
	void* 								userdata;														/* user data used in event cb */
	int									copybufsz;													/* copy file buffer size in bytes */

	sql_add_field_t*				db_fields;														/* table fields in database */
	const char*					db_name;														/* db file name */
	const char*					table_main;													/* main table name */
	const char*					table_singer;												/* singer table name */
	const char*					field_singer_id;											/* singer id field name */
	const char*					field_singer_name;										/* singer name field name */
	int									field_count;													/* field count in table */
	unsigned int					new_singer_index;										/* new singer start index */

	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;
	int									sql_cachesz;
	const char*					field_song_lantype;

	int									cn_firstword;										/* force get chinese first word */
	
} updateMukPara_t;

/*
* muk ex update input parameter
*/
typedef struct 
{
	int 							db_type;														/* 0- edb, 1-sqlite db*/
	char 						db_src[MUK_UPDATE_PATH_SZ];				/* source db path */
	char 						db_dest[MUK_UPDATE_PATH_SZ];				/* destiny db path */
	char							muk_path[MUK_UPDATE_PATH_SZ];			/* muk files folder */
	char*						tmp_fn;															/* tmp file name */
	updateMukCb_t		event_cb;														/* update event callback function */
	int							req_charset;													/* request name string charset, 0-utf8, 1-unicode */			
	int							def_charset;													/* default name string charset, 0-utf8, 1-unicode */			
	void* 						userdata;														/* user data used in event cb */
	int							copybufsz;													/* copy file buffer size in bytes */

	const char*					db_name;														/* db file name */
	int								table_count;													/* table count in db */
	sql_add_field_ex_t*			db_fields;														/* table fields in database */
	const char**					table_list;													/* main table list */
	const char*					table_version;												/* version table name */
	const tableMasterParam_t*		table_keyword;											/* key word in each table */
	const char*					field_db_proj;											/* db info project field name */
	const char*					field_db_version;											/* db info project field name */
	const char*					field_singer_id;											/* singer id field name */
	const char*					field_singer_name;										/* singer name field name */
	int								field_count;													/* field count in table */
	const char*					db_info_project;											/* db info project name */
	unsigned int					new_singer_index;										/* new singer start index */

	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;
	int							sql_cachesz;		

} updateMukParaEx_t;

/*
* muk update input parameter
*/
typedef struct 
{
	char 								db_src[MUK_UPDATE_PATH_SZ];				/* source db folder */
	char 								db_dest[MUK_UPDATE_PATH_SZ];				/* destiny db folder */
	char									muk_path[MUK_UPDATE_PATH_SZ];			/* muk files folder */
	char*								tmp_fn;															/* tmp file name */
	int									copybufsz;													/* copy file buffer size in bytes */
	char*								sql_fn;
	char									sql_src[MUK_UPDATE_PATH_SZ];
	
} detectMukPara_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: detectMuk
 * Arguments      	: para - input detect parameters
 * Return         	: 0 - succ and not need to update, <>0 need update muk
 * Description    	: detect new Muk songs to update
 *					
*/
extern int detectMuk(detectMukPara_t* para);

/*
 * Function name  	: updateMuk
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update Muk songs to local db
 *					
*/
extern int updateMuk(updateMukPara_t* para);

/*
 * Function name  	: updateMukEx
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update Muk songs to local db
 *					
*/
extern int updateMukEx(updateMukParaEx_t* para);

#ifdef __cplusplus
}
#endif 

#endif


