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

#ifndef _CDG_UPDATER_H_
#define _CDG_UPDATER_H_

#include <lib/update/reqData.h>
#include <lib/update/ReqConvSql.h>
#include "FilesToLstbin.h"


#define CDG_UPDATE_PATH_SZ		128

typedef struct
{
	int cdgid;
	char songname[64];
	char singername[32];
}CDGFilePara_t;

typedef struct
{
	int num;
	CDGFilePara_t cdginfo[1];
}CDGSong_list;

//typedef int (*updateMukEventCbf)(int,void*, void*);
//typedef	updateMukEventCbf updateMukCb_t;

/*
* cdg update input parameter
*/
typedef struct 
{
	int 									db_type;														/* 0- edb, 1-sqlite db*/
	char 								db_src[CDG_UPDATE_PATH_SZ];				/* source db path */
	char 								db_dest[CDG_UPDATE_PATH_SZ];				/* destiny db path */
	char									cdg_path[CDG_UPDATE_PATH_SZ];			/* muk files folder */
	char*								tmp_fn;															/* tmp file name */
	//updateMukCb_t				event_cb;														/* update event callback function */
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
	
} updateCdgPara_t;

/*
* cdg update input parameter
*/
#if 1
typedef struct 
{
	char								cdg_path[CDG_UPDATE_PATH_SZ];			/* cdg files folder */
	char 								list_path[CDG_UPDATE_PATH_SZ];				/* source db folder */
	char 								namelst_path[CDG_UPDATE_PATH_SZ];			/* destiny db folder */
	char 								pathlst_path[CDG_UPDATE_PATH_SZ];			/* destiny db folder */
} detectCdgPara_t;
#else
typedef struct 
{
	char 								db_src[CDG_UPDATE_PATH_SZ];				/* source db folder */
	char 								db_dest[CDG_UPDATE_PATH_SZ];			/* destiny db folder */
	char								cdg_path[CDG_UPDATE_PATH_SZ];			/* cdg files folder */
	char*								tmp_fn;									/* tmp file name */
	int									copybufsz;								/* copy file buffer size in bytes */
	char*								sql_fn;
	char								sql_src[CDG_UPDATE_PATH_SZ];
} detectCdgPara_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: updateCDG
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update Muk songs to local db
 *					
*/
extern int updateCDG(updateCdgPara_t* para);


/*
 * Function name  	: detectCDG
 * Arguments      	: para - input detect parameters
 * Return         	: 0 - succ and not need to update, <>0 need update cdg
 * Description    	: detect new CDG songs to update
 *					
*/
extern int detectCDG(detectCdgPara_t* para);

extern int check_MediaFile_Valid(const char* fn);
extern int parser_MediaFile_Nameinfo(const char* name, nameInfo_t* info, filesToLstBinPara_t* para);


#ifdef __cplusplus
}
#endif 

#if 0
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

#ifdef __cplusplus
}
#endif 

#endif

#endif


