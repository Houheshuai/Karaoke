/*********************************************************************
**																	**
**  Copyright (C) 2011 Multak,Inc.									**
**  All rights reserved												**
**        Filename : edb.h/ Project: EDB							**
**        Revision : 1.31											**
**																	**
**   Note: Apply API to control database.							**
**											Author: Wang Jun		**
**														2006.4		**
*********************************************************************/
#ifndef _EDB_H_
#define _EDB_H_

#include <lib/edb/db_def.h>
#include <lib/edb/db_config.h>

#if NEW_EXPRESSION_PARSER > 0
#include <lib/edb/anly.h>
#endif

#define TABLE_NO_SORT			0
#define TABLE_SORT_ASCEND		1
#define TABLE_SORT_DESCEND	2

typedef struct {
	DB_UINT32 db_reserve_rec_num;	/* 插入模式打开db的时候预留的记录数*/
	DB_UINT32 max_rec_set;	/* 创建recordset的时候预留的记录数 */
	DB_UINT8 enable_rec_del;/* 允许记录删除*/
	DB_UINT8 dstr_rd_len; /*动态字符串预留最大空间*/
	DB_UINT8  index_auto_create; /* 记录插入时主键索引自动产生*/
} _t_db_internal_para;

#ifdef __cplusplus
extern "C" {
#endif 

extern _t_db_internal_para db_para;

extern void 
DBFree(DB_HANDLE *db);

extern DB_HANDLE *
DBNew(DB_UINT8 *file_name);

extern void 
DBUndo(DB_HANDLE *db);

/* DB interface */
extern DB_UINT8 
DBClose(DB_HANDLE *db);

extern DB_HANDLE * 
DBOpen(DB_UINT8 *file_name, DB_INT8 mode);

extern DB_HANDLE *
DBCreate(DB_UINT8 *file_name);

/*
*	Database initial, set reserve record number, you can add other options in future
*/
extern void 
DBInit(DB_UINT16 RsvRecNum, DB_UINT8 DStrLength);

/*
*	Enable delete string in string table when delete record in table
*/
extern void 
DBStrRecDelEnable(void);

/*
*	Don't delete string in string table when delete record in table
*/
extern void 
DBStrRecDelDisable(void);

/*
*	Enable mark new index by 0x80 when insert new record
*/
extern void 
DBIndexAutoCreateEnable(void);

/*
*	disable mark new index by 0x80 when insert new record
*/
extern void 
DBIndexAutoCreateDisable(void);


extern TABLE_HANDLE *
DBGetTableHandleByName(DB_HANDLE *db, DB_UINT8 *table_name);

extern DB_BOOL 
DBCheckTableOpened(TABLE_HANDLE *table);

extern DB_UINT8 
DBGetDStrRdLength(void);

/* View */

/*
*	create a view of table in database
*	note that view is a copy of table, you must open a table first then create a view
*	and free a view before close table
*	@db : database handle
*	@tbl : table handle
*	return : view handle
*/
extern void * 
ViewFree(TABLE_HANDLE *view);

/*
*	create a view of table in database
*	note that view is a copy of table, you must open a table first then create a view
*	and free a view before close table
*	@db : database handle
*	@tbl : table handle
*	return : view handle
*/
extern TABLE_HANDLE * 
ViewCreate(DB_HANDLE *db, TABLE_HANDLE *tbl);

extern void 
TableFree(TABLE_HANDLE *table);

/*
*	create table in memory by table name
*/
extern TABLE_HANDLE * 
TableNew(DB_HANDLE *db,DB_UINT8 * table_name);

/*
*	open a table in database
*	@db : database handle
*	@file_name : table file name, no path
*	@mode : open mode, DB_READ_ONLY or DB_EDIT_MODE
*	return : table handle
*/
extern TABLE_HANDLE * 
TableOpen(DB_HANDLE *db,DB_UINT8 *table_name,DB_INT8 mode);

/*
*	create table and open it by table name
*/
extern TABLE_HANDLE * 
TableCreate(DB_HANDLE *db,DB_UINT8 *table_name);

extern DB_UINT8 
TableClose(DB_HANDLE *db,TABLE_HANDLE *table);	
/*
*	TABLE rountines
*	open/create/close/delete/select/search/sort/filter
*/

extern DB_UINT8 
TableSave(DB_HANDLE *db,TABLE_HANDLE* table);

extern DB_UINT8 
TableDelete(DB_HANDLE *db, DB_UINT8 *table_name);
/*
*	search one record in table
*	@key_name : key name, search in this key
*	@value : key value
*	@mode : next, prev, last, first
*/
DB_UINT8 
TableSearch(DB_HANDLE *db,TABLE_HANDLE *table,DB_UINT8 *key_name,DB_INT8 *value,DB_UINT8 mode);
/*
*	copy table, table key number and order must be the same
*/
extern DB_UINT8  
TableCopy(TABLE_HANDLE *dest, TABLE_HANDLE *src);

extern void 
TableUndo(TABLE_HANDLE *tbl);

extern DB_UINT8   
TableRen(DB_HANDLE *db, TABLE_HANDLE *tbl, DB_UINT8 *name);

#if NEW_EXPRESSION_PARSER > 0

/*
*	select records from sourc table and create new table with those records
*	@db : database handle
*	@TableSrc : source table handle
*	@TableDest : new table handle
*	@FieldForest : forest of fields in sql string
*	@ConditionForest : forest of conditions in sql string
*/
extern DB_UINT8 
TableSelect(DB_HANDLE *db,TABLE_HANDLE* TableSrc,TABLE_HANDLE* TableDest, INQUIRE_FOREST* FieldForest, INQUIRE_FOREST* ConditionForest);

#else
/*
*	select records from sourc table and create new table with those records
*	@db : database handle
*	@TableSrc : source table handle
*	@TableDest : new table handle
*	@Sel_para : select parameters
*/
extern DB_UINT8 
TableSelect(DB_HANDLE *db,TABLE_HANDLE* TableSrc,TABLE_HANDLE* TableDest,SELECT_PARA Sel_para);

#endif
/*
*	sort table by key, find key by key index
*/
extern DB_UINT8 
TableSortByIndex(DB_HANDLE *db, TABLE_HANDLE *table,DB_UINT8 index,DB_INT8 mode, DB_UINT32 startrec, DB_UINT32 recnum);


/*
*	sort table by key, find key by key index, sort dstr type by offset, not real string
*/
extern DB_UINT8 
TableSortByIndexFast(DB_HANDLE *db, 
						TABLE_HANDLE *table,
						DB_UINT8 index,
						DB_INT8 mode, 
						DB_UINT32 startrec, 
						DB_UINT32 recnum);

/*
*	sort table by key "key_name", can sort by multi-key
*	arguments:
*	@db : db handle
*	@table : table handle
*	@keys : key list
*	@keynum : number of keys sort by
*/
extern DB_UINT8 
TableSort(DB_HANDLE *db, TABLE_HANDLE *table, SORT_KEYS *keys, DB_UINT8 keynum);

/*
*	delete sort flag in table head, table will be sorted again next time
*	arguments:
*	@table : table handle
*/
extern void 
TableSortUndo(TABLE_HANDLE *table);

/*
*	function : set filter of table by key "key_name", key value range is "begin" and "end"
*			table should be sort by key "key_name" by assending
*	arguments :
*	@ db : db handle
*	@ table : table handle
*	@ key_name : key name string
*	@ begin : minmum value of filter range
*	@ end : maximum value of filter range
*/
extern DB_UINT8 
TableFilter(DB_HANDLE *db,TABLE_HANDLE *table,DB_UINT8 *key_name,DB_UINT8 *begin,DB_UINT8 *end);

/*
*	get key value of record No.n and compare with input filter parameter
*	@n : record index
*	@CurParam : input filter parameter to do compare
*/
extern DB_UINT8 
TableSelectOneRec(DB_HANDLE *db,TABLE_HANDLE* table, DB_UINT32 n, FILTER_PARAM *CurParam);

/*
*	add a new filter parameter to FILTER_CHAIN
*/
extern DB_UINT8 
TableSelectAddParam(SELECT_PARA *SelParam,FILTER_PARAM *NewFilter);

/*
*	Add a new key name to NAME_CHAIN
*/
extern DB_UINT8 
TableSelectAddKeyName(SELECT_PARA *SelParam,DB_UINT8* KeyName);

extern void 
TableSelectFreeParam(SELECT_PARA *SelParam);

extern DB_UINT8 
TableFilterReset(TABLE_HANDLE *table);

extern DB_UINT8 
TableSetCursor(TABLE_HANDLE *table,DB_UINT32 n);

extern DB_UINT8 
KeyGetIndexByName(TABLE_HANDLE* table,DB_UINT8 *key_name);

extern DB_UINT32 
keyGetLenByIndex(TABLE_HANDLE *table,DB_UINT8 index);

extern DB_INT8 
KeyGetTypeByIndex(TABLE_HANDLE* table,DB_UINT8 index);

extern DB_UINT8 
KeySetValueByIndex(DB_HANDLE *db,TABLE_HANDLE* table,DB_UINT8 index,DB_UINT8 * data, DB_INT8 mode);

extern DB_UINT8 
TableFilterSetCursor(TABLE_HANDLE *table,DB_UINT32 n);

/* Key interface */

/*
*	add a new key
*	@key_info : new key data
*/
extern DB_UINT8 
KeyInsert(DB_HANDLE *db,TABLE_HANDLE *table, TABLE_KEY_INFO *key_info);

extern DB_UINT8 
KeyDelete(DB_HANDLE *db,TABLE_HANDLE *table, DB_UINT8 *key_name);

/*
*	modify key info
*	@key_name : key name
*	@key_info : new info
*/
extern DB_UINT8 
KeyModify(DB_HANDLE *db,TABLE_HANDLE *table, DB_UINT8 *key_name,TABLE_KEY_INFO *key_info);

/*
*	set key value by key name
*	@db : database handle
*	@table : table handle
*	@key_name : key name string
*	@data : key value buffer
*/
extern DB_UINT8
KeySetValue(DB_HANDLE *db,TABLE_HANDLE* table,DB_UINT8 *key_name,DB_UINT8* data, DB_INT8 mode);

extern DB_UINT8
KeyGetValue(DB_HANDLE *db,TABLE_HANDLE* table,DB_UINT8 *key_name,DB_UINT8* data, DB_INT8 mode);

extern DB_UINT8 * 
KeyGetNameByIndex(TABLE_HANDLE *table,DB_UINT8 index);

DB_UINT8 
KeyGetValue(DB_HANDLE *db,TABLE_HANDLE *table, DB_UINT8 *key_name, DB_UINT8 *buffer, DB_INT8 mode);

extern DB_UINT32 
KeyGetIntegerValueByIndex(DB_HANDLE *db,TABLE_HANDLE *table, DB_UINT8 index);

extern DB_UINT32 
KeyGetIntegerValue(DB_HANDLE *db, TABLE_HANDLE* table,DB_UINT8* key_name);

extern DB_UINT8 
KeyGetValueByIndex(DB_HANDLE *db,TABLE_HANDLE* table, DB_UINT8 index, DB_UINT8* buffer, DB_INT8 mode);

extern DB_UINT8 
KeyGetValueByIndex2(DB_HANDLE *db,TABLE_HANDLE* table, DB_UINT8 index, DB_UINT8* buffer, DB_INT8 mode,DB_UINT32 keyoffset,DB_UINT16 keylen);

extern DB_INT8 
KeyGetTypeByName(TABLE_HANDLE* table,DB_UINT8 *key_name);

/*
*	get key index by search key name
*/
extern DB_INT8
keyGetIndexByName(TABLE_HANDLE *table, DB_UINT8 *key_name);

extern DB_INT16 
KeyGetLenByName(TABLE_HANDLE* table,DB_UINT8 *key_name);

/* Record interface */

/*
*	Insert a record with zero data
*/
extern DB_UINT8 
RecordInsert(DB_HANDLE *db,TABLE_HANDLE* table);

extern DB_UINT8 
RecordInsertLast(DB_HANDLE *db,TABLE_HANDLE* table);

extern DB_UINT8 
RecordAppend(DB_HANDLE *db,TABLE_HANDLE* table);

extern DB_UINT8 
RecordDelete(DB_HANDLE *db,TABLE_HANDLE* table);

/*mode 0:the same withRecordDelete
		1:fast delete
		other reserved
*/
DB_UINT8 
RecordDeleteEx(DB_HANDLE *db,TABLE_HANDLE* table, DB_INT8 mode);

/*move current record to destPos*/

extern DB_UINT8 
RecordSwap(DB_HANDLE *db, TABLE_HANDLE* table, DB_UINT32 destPos);

/*insert  destPos record to current record  */
extern DB_UINT8 
RecordMove(DB_HANDLE *db, TABLE_HANDLE* table, DB_UINT32 destPos);

extern DB_UINT8 
RecordPrev(TABLE_HANDLE *table);

extern DB_UINT8 
RecordNext(TABLE_HANDLE *table);

extern DB_UINT8 
RecordFirst(TABLE_HANDLE *table);

extern DB_UINT8 
RecordLast(TABLE_HANDLE *table);

/* RecordSet interface */
extern void 
RecordSetFree(RECORD_SET * RecSet);

extern RECORD_SET *
RecordSetCreate(DB_HANDLE * db, DB_UINT16 MaxRecords, DB_UINT8 *table_name);

extern DB_UINT8 
RecordSetToTable(RECORD_SET *RecSet, DB_HANDLE *db, DB_UINT8 *tablename);

extern TABLE_HANDLE * 
StringTableNew(DB_HANDLE *db, DB_INT8 mode, DB_INT32 poolsz);

DB_UINT8 
StringTableClose(DB_HANDLE *db);

DB_UINT8 
StringTableOpen(DB_HANDLE *db,DB_INT8 mode);

/*
*	get filename without path from a full path,like: "d:\\dir\\filename.ext" to "filename.ext"
*/
extern DB_UINT8 *
ExtractFileName(DB_UINT8 *fullpath);

extern DB_UINT32 
TableFilterNoSort(DB_HANDLE *db,TABLE_HANDLE *table,DB_UINT8 *key_name,DB_UINT8 *begin,DB_UINT8 *end);

#if DB_DEBUG > 0
extern void 
db_error_print(DB_INT8 err_code);
#define _db_error_print(a) db_error_print(a)
#else
#define _db_error_print(a)
#endif

#ifdef __cplusplus
}
#endif 

#endif
