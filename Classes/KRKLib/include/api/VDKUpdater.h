/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : VDKUpdater.h
** Revision : 1.00											
**																	
** Description: VDK update api
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

#ifndef _VDK_UPDATER_H_
#define _VDK_UPDATER_H_

#include <lib/update/reqData.h>
#include <lib/update/ReqConvSql.h>

#define VDK_UPDATE_PATH_SZ		128

/*
* update event type
*/
enum
{
	VU_EVENT_NONE = 0,
	VU_EVENT_BEGIN,
	VU_EVENT_UPDATE_DB,
	VU_EVENT_UPDATE_DB_ERR,
	VU_EVENT_DECODE_FILE,
	VU_EVENT_DECODE_FILE_ERR,
	VU_EVENT_PERCENT,
	VU_EVENT_END,
};

typedef int (*updateVDKEventCbf)(int,void*, void*);
typedef	updateVDKEventCbf updateVDKCb_t;

/*
* vdk update input parameter
*/
typedef struct 
{
	int 									db_type;														/* 0- edb, 1-sqlite db*/
	char 								db_path[VDK_UPDATE_PATH_SZ];				/* work db path */
	char 								db_backup[VDK_UPDATE_PATH_SZ];			/* backup db path */
	char									vdk_path[VDK_UPDATE_PATH_SZ];			/* vdk files folder */
	char									muk_path[VDK_UPDATE_PATH_SZ];			/* muk files folder */
	updateVDKCb_t				event_cb;														/* update event callback function */
	void* 								userdata;														/* user data used in event cb */
	int									copybufsz;													/* copy file buffer size in bytes */
	int									charset;
	char									sn[12];
	int									sort_default_lan;											/* default sort language */
	int									usedef_lanlist[8];										/* language in this list will use default sort language */
	
	sql_add_field_t*				db_fields;														/* table fields in database */
	const char*					db_name;														/* db file name */
	const char*					table_main;													/* main table name */
	const char*					table_singer;												/* singer table name */
	const char*					field_singer_id;											/* singer id field name */
	const char*					field_singer_name;										/* singer name field name */
	const char*					field_song_index;										/* song id field name */
	int									field_count;													/* field count in table */
	unsigned int					new_singer_index;										/* new singer start index */
	
	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;
	int									sql_cachesz;
	const char*					field_song_lantype;
	
	int									cn_firstword;										/* force get chinese first word */
} updateVDKPara_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: updateVDK
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update VDK songs to local db
 *					
*/
extern int updateVDK(updateVDKPara_t* para);

#ifdef __cplusplus
}
#endif 

#endif


