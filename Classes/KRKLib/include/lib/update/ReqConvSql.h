/************************************************************************************** 
** Copyright (C) 2011 Multak,Inc. All rights reserved
**
** Filename : ReqConvSql.h
** Revision : 1.00
**
** Author :  yexf
** Date :  2012-10-18
**
** Description: 
**************************************************************************************

				¹¦ÄÜ£º

				
**************************************************************************************/ 
#ifndef _REQCONVSQL_H_
#define _REQCONVSQL_H_

#include "ReqData.h"
#include <lib/common/krk_common.h>

#define REQ_SUCCESS						0
#define REQ_FAILURE						1

#define SQL_TABLE_LIST				16
#define SQL_NAME_MAX					20
#define SQL_CACHE_CAP					0x200000


/*
* destiny database type
*/
enum
{
	REQ_DB_EDB = 0,
	REQ_DB_SQLITE = 1,
	
};

/*
* table id set by index
*/
enum
{
	ENUM_DB_TABLE_ID_1 = 0x1,
	ENUM_DB_TABLE_ID_2 = 0x2,
	ENUM_DB_TABLE_ID_3 = 0x4,
	ENUM_DB_TABLE_ID_4 = 0x8,
	ENUM_DB_TABLE_ID_5 = 0x10,
	ENUM_DB_TABLE_ID_6 = 0x20,
};

typedef struct tag_sql_add_field_t			sql_add_field_t;
typedef struct tag_sql_field_t			sql_field_t;
typedef struct tag_sql_table_t			sql_table_t;
typedef struct tag_sql_cache_t			sql_cache_t;
typedef int (sql_cache_fputs)(sql_cache_t *,const char *);
typedef sql_cache_fputs *scf;
typedef void (sql_callback)(void *,int,int);
typedef sql_callback	*scb;

typedef struct tag_sql_add_field_ex_t			sql_add_field_ex_t;
typedef struct tag_sql_field_ex_t				sql_field_ex_t;
typedef struct tag_sql_table_ex_t				sql_table_ex_t;

typedef struct tag_sql_singer_struct_t			sql_singer_struct_t;

/*
* set master param in table
*/
typedef struct  
{
	const char* tablename;
	req_field_em emtype;
} tableMasterParam_t;

struct tag_sql_add_field_t
{
	const char *name;
	int field_len;
	req_field_em em_field;
	const char *defaultval;
};

struct tag_sql_add_field_ex_t
{
	const char *name;
	int field_len;
	req_field_em em_field;
	const char *defaultval;
	int table_id;
};

struct tag_sql_cache_t
{
	FILE* fp;
	char *cache;
	int size;
	int cap;
	char *pcur;
	scf pfputs;
};

struct tag_sql_field_t
{	
	int field_len;
	char *default_value;
	req_field_em em_field;
	char field_name[SQL_NAME_MAX];	
	sql_field_t *next;
};

struct tag_sql_field_ex_t
{	
	int field_len;
	char *default_value;
	req_field_em em_field;
	int table_id;
	char field_name[SQL_NAME_MAX];	
	sql_field_ex_t *next;
};

struct tag_sql_table_t
{
	int field_num;
	sql_field_t *field;
	char table_name[SQL_NAME_MAX];
	void *usrdata;
	scb  sql_cb;
};

struct tag_sql_table_ex_t
{
	int field_num;
	sql_field_ex_t *field;
	//char table_name[SQL_TABLE_LIST][SQL_NAME_MAX];
	tableMasterParam_t table_master[SQL_TABLE_LIST];
	void *usrdata;
	scb  sql_cb;
};

struct tag_sql_singer_struct_t
{
	char singername[REQ_FIELD_MAX];
	char singerindex[REQ_FIELD_MAX];
};

#ifdef __cplusplus
extern "C" {
#endif
	void sql_cache_deinit(sql_cache_t *pcache);
	sql_cache_t *sql_cache_init(const char *file_name);
	void sql_table_add(sql_table_t *pst, sql_add_field_t* addfield);
	req_table_t *sql_req_data(sql_table_t *pst,req_type_em type,const char *dir_path,void *para);
	void sql_table_deinit(sql_table_t *pst);
	sql_table_t *sql_table_init(const char *name);
	int sql_table_insert(req_table_t *prt,sql_table_t *pst,sql_cache_t *pcache);
	
	//for Ex
	void sql_table_deinit_Ex(sql_table_ex_t *pst);
	sql_table_ex_t *sql_table_init_Ex(const tableMasterParam_t *name, int count);
	void sql_table_add_Ex(sql_table_ex_t *pst, sql_add_field_ex_t* addfield);
	req_table_t *sql_req_data_Ex(sql_table_ex_t *pst,req_type_em type,const char *dir_path,void *para);
	int sql_table_insert_Ex(req_table_t *prt,sql_table_ex_t *pst,sql_cache_t *pcache,int tablecount);
#ifdef __cplusplus
}
#endif

#endif

