/***********************************************************
*
*	Description : update aqlite3 db
*	Filename : updateSqlite3.h
*	Writer : by chenzh
*	Time : 2013-9-25
*
***********************************************************/

#ifndef _UPDATE_SQLITE_3_H_
#define _UPDATE_SQLITE_3_H_

#include <stdio.h>
#include <malloc.h>
#include <sqlite3.h>

#include <lib/edb/edb.h>
#include <lib/edb/dbapp.h>
#include <lib/update/ReqConvSql.h>

#define SQLITE_UPDATE_PATH		256
#define SQLITE_BUFFER_SIZE		512
#define SQL_TABLE_NAME_MAX		20

#define SPARE_SINGER_ID		999999

#define SQL_TABLESONGTYPE "TableSongType"
#define SQL_TABLESONGSINGER "TableSongSinger1"
#define SQL_TABLE_SONG "TableSong"
#define SQL_FIELD_SONGID "SongIndex"

typedef void (*FUNC_COPY_SONG)(int songid);
typedef void (*FUNC_DELETE_SONG)(int songid);

enum
{
	SQL_EVENT_NONE = 0,
	SQL_EVENT_BEGIN,
	SQL_EVENT_PERCENT,
	SQL_EVENT_END,
	SQL_EVENT_ERR,
};
typedef int (*updateSqlite3EventCbf)(int, void*, void*);
typedef	updateSqlite3EventCbf updateSqlBinCb_t;

typedef struct 
{
	//sql_table_ex_t*				tabledata;
	const char* 					db_path;														/* source db path */
	int									cachesz;														/* sql execute cache size */
	int									resv_count;													/* DBInit parameter, reserved record count in insert mode */
	//unsigned int				new_singer_index;										/* new singer start index */
	
	const char*					db_name;														/* db file name */
	//int							table_count;													/* table count in db */
	//const char**			table_list;													/* main table name */
	const char*					table_version;											/* version table name */
	const char*					field_db_proj;											/* db info project field name */
	const char*					field_db_version;											/* db info version field name */
	//const char*					field_singer_id;											/* singer id field name */
	//const char*					field_singer_name;										/* singer name field name */
	const char*					db_info_project;											/* db info project name */

	const char*					drop_sql;
	const char*					insert_sql;
	const char*					create_sql;
	const char*					select_sql;

	FUNC_COPY_SONG				func_copy_song;

	updateSqlBinCb_t			event_cb;
	void*						userdata;
} updateSqlite3Para_t;

typedef struct 
{
	const char*					db_file_path;

	const char*					table_song;
	const char*					table_songsinger;
	const char*					table_songtype;
	const char*					table_singer;
	const char*					table_dbinfo;

	const char*					field_songid;
	const char*					field_singerid;
	const char*					field_projectname;
	const char*					field_dbversion;

	const char*					value_projectname;

	int*								listsongid;			//for delete song id
	int								listcount;			//for delete song count

	FUNC_DELETE_SONG			func_del_song;
	
} deleteSqlite3Para_t;

typedef struct
{
	const char*					db_file_path;

	const char**				table_list;
	const int					tablelist_count;
	const char*					table_dbinfo;

	const char*					field_projectname;
	const char*					field_dbversion;

	const char*					value_projectname;

} deleteAllSqlite3Para_t;

/*
* for string buff
*/
struct updateSqlite3Buff
{
	char buff[SQLITE_BUFFER_SIZE];
	int index;
	struct updateSqlite3Buff *prev;
	struct updateSqlite3Buff *next;
};

typedef struct updateSqlite3Buff updateSqlite3Buff_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
* open the sqlite3 db
*/
extern int sqlite3_db_open(const char *path);

/*
* close the sqlite3 db
*/
extern void sqlite3_db_close(void);

/*
* get the biggest singerIndex
* return : the max singerIndex
*/
extern int sqlite3_get_max_singer_index(void);

/*
* get the singerIndex by singerName
* return : the singerIndex
*/
extern int sqlite3_get_singer_index_by_name(const char* singerindex, const char* tablesinger, const char* singername, const char* namestr);

/*
* check the value is or not be used
* return : 0 is OK, other is ERROR
*/
extern int sqlite3_check_the_value(const char *tablename, const char *param, const char* charvalue);

/*
 * Function name  	: updateSqlite3
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: update table data to Sqlite3 database
 *					
*/
extern int updateSqlite3(updateSqlite3Para_t* para);

/*
 * Function name  	: deleteSqlite3
 * Arguments      	: para - input delete parameters
 * Description    	: delete info form db
 *					
*/
extern int deleteSqlite3(deleteSqlite3Para_t* para);

/*
 * Function name  	: deleteAllSqlite3
 * Arguments      	: para - input delete all parameters
 * Description    	: delete all songs form db
 *					
*/
extern int deleteAllSqlite3(deleteAllSqlite3Para_t* para);

extern int get_percent();


#ifdef __cplusplus
}
#endif 

#endif
