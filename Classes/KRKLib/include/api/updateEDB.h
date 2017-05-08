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

#ifndef _UPDATEEDB_H_
#define _UPDATEEDB_H_

#include <lib/edb/sort.h>
#include <lib/edb/edb.h>
#include <lib/edb/dbapp.h>
#include <lib/update/ReqConvSql.h>

#define EDB_UPDATE_PATH_SZ		128

typedef struct 
{
	sql_table_t*					tabledata;
	const char* 					db_path;											// source db path 
	int						cachesz;													// sql execute cache size
	int						resv_count;		// DBInit parameter, reserved record count in insert mode
	unsigned int					new_singer_index;						//  new singer start index
	
	const char*					db_name;		// db file name 
	const char*					table_main;		// main table name
	const char*					table_singer;			// singer table name 
	const char*					field_singer_id;		// singer id field name 
	const char*					field_singer_name;		// singer name field name  

	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;
	const char*					field_song_lantype;
#ifdef SUPPORT_PERSANG_EDB  // Persang db album function   SUPPORT_PERSANG_FUNCTION
	unsigned int				new_album_index;				/*new album start index*/
	const char* 				table_album;					/* album table name*/
	const char*					field_album_id;               /*album id field name*/
	const char*                 field_album_name;             /*album name field name*/
#endif	
} updateEDBPara_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: updateEDB
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update table data to EDB database
 *					
*/
extern int updateEDB(updateEDBPara_t* para);

#ifdef __cplusplus
}
#endif 

#endif


