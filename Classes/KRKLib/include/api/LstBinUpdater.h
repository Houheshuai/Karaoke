/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : LstBinUpdater.h
** Revision : 1.00											
**																	
** Description: songlist.bin update api
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

#ifndef _LST_UPDATER_H_
#define _LST_UPDATER_H_

#include <lib/update/reqData.h>
#include <lib/update/ReqConvSql.h>

#define LST_UPDATE_PATH_SZ		128

/*
* update event type
*/
enum
{
	LU_EVENT_FINISHED = -1,
	LU_EVENT_NONE = 0,
	LU_EVENT_BEGIN,
	LU_EVENT_PERCENT,
	LU_EVENT_END,
	LU_EVENT_ERR,
};

typedef int (*updateLstBinEventCbf)(int,void*, void*);
typedef	updateLstBinEventCbf updateLstBinCb_t;

/*
* muk update input parameter
*/
typedef struct 
{
	int 									db_type;													/* 0- edb, 1-sqlite db*/
	char 								db_src[LST_UPDATE_PATH_SZ];				/* source db path */
	char 								db_dest[LST_UPDATE_PATH_SZ];			/* destiny db path */
	char 								db_tmp[LST_UPDATE_PATH_SZ];			/* tmp db path, dest will be copy to tmp */
	char									lst_path[LST_UPDATE_PATH_SZ];			/* muk files folder */
	updateLstBinCb_t			event_cb;													/* update event callback function */
	int									charset;														/* request name string charset */
	int									req_songname;										/* request songname file */			
	int									def_songname;										/* default songname file */			
	void* 								userdata;													/* user data used in event cb */
	int									copybufsz;												/* copy file buffer size in bytes */

	sql_add_field_t*				db_fields;													/* table fields in database */
	const char*					db_name;													/* db file name */
	const char*					table_main;												/* main table name */
	const char*					table_singer;											/* singer table name */
	const char*					field_singer_id;										/* singer id field name */
	const char*					field_singer_name;									/* singer name field name */
	int									field_count;												/* field count in table */
	unsigned int					new_singer_index;										/* new singer start index */

	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;
	int									sql_cachesz;
	const char*					field_song_lantype;	
	int									cn_firstword;										/* force get chinese first word */
#ifdef SUPPORT_PERSANG_EDB //Persang db album function    SUPPORT_PERSANG_FUNCTION
	unsigned int 			   	new_album_index;                             /* new album start index */
	const char*					table_album;								  /* album table name */
	const char*					field_album_id;							  /* album id field name */
	const char*					field_album_name;						  /* album name field name */
#endif 
} updateLstBinPara_t;

/*
* muk update input parameter ex
*/
typedef struct 
{
	int 								db_type;													/* 0- edb, 1-sqlite db*/
	char 							db_src[LST_UPDATE_PATH_SZ];				/* source db path */
	char 							db_dest[LST_UPDATE_PATH_SZ];			/* destiny db path */
	char 							db_tmp[LST_UPDATE_PATH_SZ];			/* tmp db path, dest will be copy to tmp */
	char								lst_path[LST_UPDATE_PATH_SZ];			/* muk files folder */
	updateLstBinCb_t					event_cb;													/* update event callback function */
	int								charset;														/* request name string charset */
	int								req_songname;										/* request songname file */			
	int								def_songname;										/* default songname file */			
	void* 							userdata;													/* user data used in event cb */
	int								copybufsz;												/* copy file buffer size in bytes */

	const char*						db_name;													/* db file name */
	int									table_count;													/* table count in db */
	sql_add_field_ex_t*				db_fields;													/* table fields in database */
	const char**						table_list;													/* main table list */
	const char*							table_version;												/* version table name */
	const tableMasterParam_t*			table_keyword;											/* key word in each table */
	const char*						field_db_proj;											/* db info project field name */
	const char*						field_db_version;											/* db info project field name */
	const char*						field_singer_id;											/* singer id field name */
	const char*						field_singer_name;										/* singer name field name */
	int									field_count;													/* field count in table */
	const char*						db_info_project;											/* db info project name */
	unsigned int					new_singer_index;										/* new singer start index */

	const char*						drop_sql;
	const char*						insert_sql;
	const char*						create_sql;
	const char*						select_sql;
	int									sql_cachesz;		

} updateLstBinParaEx_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: updateLstBin
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update songlist.bin to local db
 *					
*/
extern int updateLstBin(updateLstBinPara_t* para);

extern int updateLstBinEx(updateLstBinParaEx_t* para);

#ifdef __cplusplus
}
#endif 

#endif


