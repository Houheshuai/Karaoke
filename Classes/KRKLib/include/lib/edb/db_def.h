/************************************************************************
**                                                                     
**  Copyright (C) 2011 Multak,Inc.                                    
**  All rights reserved                                               
**        Filename : DB_DEF.h / Project: EDB                          
**        Revision : 1.31                                               
**                                                                     
**   Note: DB_HANDLE file and DB_HANDLE data structure define													   
**                             Author: Wang Jun  
**						  Zhang xiaopeng   
**						  yuchuanxin                  
**                                                      2006.3         
************************************************************************/

/******************************************************************************
*	
*	database consist of one db file, some table files and one string table file
*		----Database---
*		|  dbname.edb  |
*		|  table1.tbl      |
*		|  table2.tbl      |
*		|  ...                |
*		|  dbname.str   |
*		--------------
*	be note that string table file name is same with db file name, only extend name is different
*	
*	format of dbname.edb file
*		DB_HEAD
*		DB_DATA
*	format of table.tbl file 
*		TABLE_HEAD
*		TABLE_KEY_INFO
*		TABLE_DATA
*	format of string table
*		string list, end with zero, must more than 3 bytes one string, and free string will store next free point
*
*************************************************************************************
*/


#ifndef _DB_DEF_H_
#define _DB_DEF_H_

#define DB_VERSION100		"EDB v1.00"
#define DB_VERSION		"EDB v2.01"

typedef	signed char					DB_INT8;
typedef	signed short					DB_INT16;
typedef	signed int						DB_INT32;
typedef	unsigned char					DB_UINT8;
typedef	unsigned short				DB_UINT16;
typedef	unsigned int					DB_UINT32;
typedef	signed int						DB_BOOL;

#ifndef DBEOF
#define DBEOF	FALSE
#endif

#ifndef nDBEOF
#define nDBEOF	TRUE
#endif

/* 使用新的SELECT 语句分析器 */

#define NEW_EXPRESSION_PARSER		1

#define DB_STR_CHAIN_FREE_SPACE		0  /* 节省str文件占用空间，但是会增加删除记录的时间 */

#define DB_SINGLE_FILE           0

#if DB_SINGLE_FILE
#define DB_FILE_ALWAYS_OPEN    0		/* DB Open 后文件一直打开 */
#else
#define DB_FILE_ALWAYS_OPEN    0		/* DB Open 后文件一直打开 */
#endif

#define DB_DSTR_MAIN_KEY		0		/*动态长度字符串作为主键, 暂时不支持*/

#define MAX_KEY_LEN 	255			/*每个字段允许的最大长度*/
#define MAX_KEY_NUM	127			/*最多字段数*/
#define MAX_DB_PATH_LEN	255
#define MAX_TABLE_NUM		127
#define DSTR_KEY_LEN		3	/* dynamic string key length of offset */
#define MAX_SORT_KEYS		2	/* 最多同时排序的字段数目*/
#define DSTR_END_FLAG		0xffffff

#define DB_READ_ONLY 1				/*只读方式打开数据库*/
#define DB_EDIT_MODE 		2				/*可修改方式打开数据库*/
#define DB_INSERT_MODE		3				/* 为增加数据预留内存*/

#define DSTR_READ_LENGTH	32		/* 读动态字符串的最大取值长度*/
#define PER_STRING_LEN 	16		/*估计的string table 预留的每个字符串的长度*/
#define RESERVE_REC_NUM 	1024	/*可修改方式打开数据库时预留的添加纪录条数*/
#define MAX_RECORDS_IN_SET	50000	/* maximum number of records in record set */
#define HASH_RES  3000

/* db record data type */

#define DB_INT_DATA_TYPE	1		/* integer data type, number of bytes */
#define DB_STR_DATA_TYPE	2		/* static length string data type */
#define DB_DSTR_DATA_TYPE	3		/* dynamic length string data type */

#define TABLE_SEARCH_FIRST	1
#define TABLE_SEARCH_LAST	2
#define TABLE_SEARCH_NEXT	3
#define TABLE_SEARCH_PREV	4

/* db status */

#define DB_NORMAL		0		/* not changed */
#define DB_CHANGED		1		/* db context changed */

/* table status */

#define TABLE_NORMAL		0		/* not changed, not deleted */
#define TABLE_CHANGED		1		/* table context changed */
#define TABLE_DELETED		2		/* table already deleted */
#define TABLE_CREATED		4		/* table just be created */

#define TABLE_NO_MAIN_KEY			0xff

#define DB_MAX_NAME_LEN	20	/*数据库,字段，表等的名字的最大长度*/
#define DB_MAX_VALUE_LEN	256
#define SQL_NEW_COL_LEN	32

/* error code */
#define ERR_NONE				0	/* no error */
#define ERR_CREAT_FAILURE		1	/*创建数据库失败*/
#define ERR_OPEN_MODE		 	2	/*要执行的操作与数据库的打开方式不符*/
#define ERR_FILE_NAME_NE	 	3	/*文件名不存在*/
#define ERR_SET_MAIN_KEY	 	4	/*设置主键错误*/
#define ERR_KEY_NAME_NE			5	/*字段名不存在*/
#define ERR_REC_NUM				6	/*纪录条数错误*/
#define ERR_SEL_MODE		 	7	/*选择模式错误*/
#define ERR_DB_READ				8	/* db read file error */
#define ERR_DB_WRITE			9	/*error db read data to file */

#define ERR_KEY_NAME_EMPTY		30	/*字段名不能为空*/
#define ERR_KEY_NAME_ILLEGAL	31	/*字段名非法*/
#define ERR_KEY_TYPE_TAB	 	32	/*字段类型不能为STRINGTAB*/
#define ERR_KEY_NAME_EXIST		33	/*字段名已存在*/
#define ERR_KEY_LEN_ILLEGAL	 	34	/*字段长度错误*/
#define ERR_KEY_TYPE_ILLEGAL 	35	/*字段类型非法*/
#define ERR_NO_TAB				36	/*没有TAB存在*/
#define ERR_TAB_FREE_SIZE		37	/*TAB空闲空间不够*/

#define ERR_MAIN_KEY_REPEAT		40	/*主键值与其他纪录重复*/
#define ERR_NO_REC				41	/*数据库为空*/
#define ERR_NO_RIGHT_REC		42	/*没有符合要求的纪录*/
#define ERR_CAN_NOT_MOVE		43	/*游标不能移动*/
#define ERR_CAN_NOT_DEL_MAIN_KEY	44	/*不能删除主键*/
#define ERR_NO_CHANGE			45	/*没有改变字段信息*/
#define ERR_NOT_IN_FILTER		46	/*不再Filter范围内*/
#define ERR_BUFFER_NULL			47	
#define ERR_MALLOC_FAILURE		48	/*内存分配失败*/
#define ERR_OPEN_FAILURE		49/*打开文件失败*/
#define ERR_FILE_WRITE			50	/*写文件失败*/
#define ERR_STRING_OPENED_EDITABLE	51/* string table 已经以editable 方式打开*/
#define ERR_TABLE_NOT_IN_DB	52 /*无法在db的Tableinfo[] 中找到Table->Head地址*/
#define ERR_STRING_CANT_SORT	53	/* 字符串类型无法排序*/
#define ERR_GET_STRING_POS		54	/*得到string存放的地址错误*/
#define ERR_STRING_TAB_EXIST	55	/*string table 已经存在*/
#define ERR_STING_TAB_NAME_EMPTY 56 /*String_Table_Name 未赋值*/
#define ERR_MAX_TABLE_OVERFLOW	57 
#define ERR_PARSE_SQL				58		/* parse wrong SQL string */
#define ERR_TABLE_SELECT			59
#define ERR_TABLE_NOT_OPEN		60
#define ERR_TABLE_ALREADY_EXISTS	61
#define ERR_KEY_NUM_OVERFLOW		62
#define ERR_KEY_INSERT				63
#define ERR_ORDERBY_FROM_PARSER	64
#define ERR_ANALYSE_NUM			65
#define ERR_ANALYSE_STRING			66
#define ERR_ANALYSE_SYMBOL		67
#define ERR_ANALYSE_WORD			68
#define ERR_STRING_LENGTH_OVERFLOW	69
#define ERR_MERGE_TABLE			70
#define ERR_TABLE_LENGTH_OVERFLOW	71	/*TableLength > file size*/
#define ERR_MAIN_KEY_ERROR			72
#define ERR_TABLE_RELOAD		72


/* db file extend name */

#define DB_FILE_EXT_NAME	".edb"
#define TAB_FILE_EXT_NAME	".tbl"
#define STR_FILE_EXT_NAME	".str"

/* filter mode */
#define FILTER_MODE_NEQUAL		0
#define FILTER_MODE_EQUAL			1
#define FILTER_MODE_BIGEQUAL		2
#define FILTER_MODE_SMALLEQUAL	3
#define FILTER_MODE_BIG			4
#define FILTER_MODE_SMALL			5
#define FILTER_MODE_IN_REGION			6
#define FILTER_MODE_OUT_REGION		7

#define FILTER_ALL					0xff

#define EDB_EOF						0xff	/* end of filter */
#define EDB_TOF						0xfe	/* top of filter */

#define KEY_VALUE_MODE_INT		0
#define KEY_VALUE_MODE_STR		1

#define RECORD_NEW_INDEX_MASK		0x80

#define GET_KEY_VALUE_MODE_INT		KEY_VALUE_MODE_INT
#define GET_KEY_VALUE_MODE_STR		KEY_VALUE_MODE_STR

#define SET_KEY_VALUE_MODE_INT		KEY_VALUE_MODE_INT
#define SET_KEY_VALUE_MODE_STR		KEY_VALUE_MODE_STR

#define DB_TYPE_SMALLENDIAN			0
#define DB_TYPE_BIGENDIAN				1

#define TBL_CLONE_HEAD		0
#define TBL_CLONE_ALL		1

/* data structure in .edb and .tbl file */

typedef struct {
	DB_UINT32	RecNum;		/* total record number in this table */
	DB_UINT16	RecLen; 			/* length of one record */
	DB_UINT8	KeyInfoLen;		/* length of key info structure, for compitable */
	DB_UINT8	KeyNum;		/* total key number */
	DB_UINT8	MainKey;		/* main key id in key info list */
	DB_UINT8	HeadSize;		/* size of table head */
	DB_UINT8	EndianType;		/* big endian or small endian */
	DB_UINT8	Reserved[5];		/* reserved for future */
} TABLE_HEAD;  

typedef struct { 
	DB_UINT16	KeyLen;							/* length of this key in bytes */
	DB_UINT8	KeyType;						/* key data type, integer or string */
	DB_UINT8	SortType; 						/* 0: not sorted, 1: ascend, 2: descend */
	DB_UINT8	KeyName[DB_MAX_NAME_LEN];		/* key name */
} TABLE_KEY_INFO;

typedef struct
{
	DB_UINT16	TotalTableNum;					/* total table number in database, not include string table */
	DB_UINT8  	HeadSize;						/* size of DB_HEAD structure */
	DB_UINT8	DBVersion[10];					/* DB_HANDLE version */
	DB_UINT8	DBName[DB_MAX_NAME_LEN];		/* name string of xxxx.edb */
	DB_INT8		StringTable;						/* string table flag, 0: no, 1: have */
	DB_INT8		EndianType;						/* big endian or small endian */
	DB_INT8		Charset;								/* 0: default charset, 1: utf8 charset */
} DB_HEAD;

typedef struct 
{
	DB_UINT8 	TableName[DB_MAX_NAME_LEN];	/* table name .tbl */
}DB_DATA; 

/* table filter */
typedef struct{
	DB_UINT32 StartRec;			/* start record after filter */
	DB_UINT32 RecNum;			/* record number after filter */
} DB_FILTER;

typedef struct tDBHANDLE DB_HANDLE;

/* table object */
typedef struct {
	DB_DATA 		DBData;					/* table name .tbl */
	DB_UINT32			TableLength;			/* size of table file */
	TABLE_HEAD 		*TableHead;				/* table head */
	TABLE_KEY_INFO 	*KeyInfo; 				/* address of key info */
	DB_UINT32			*KeyOffset;			/* key data offset, for faster read key value */
	DB_UINT8			*Data;					/* address of table data */
	DB_UINT32			DataSize;					/* table data size in bytes */
	DB_UINT32			Cursor;					/* cursor of table record list */
	DB_FILTER 		Filter;					/* table filter, default is whole table */
	DB_UINT32			ResRec;					/* reserve space for add new record, default 1000 record */
	DB_UINT32			MaxIndexVal;			/* index maximum value, if not calc, is 0 */
	DB_UINT8			OpenMode;				/* table operate mode, readonly or not */
	DB_UINT8  			Status;					/* table changed flag */
	DB_UINT8			memtbl;					/* only in memory, don't save to disk */
	DB_UINT8			Reserved;
	DB_HANDLE*		db;
	
} TABLE_HANDLE;

/* DB_HANDLE object */
struct tDBHANDLE {
	TABLE_HANDLE 	*StringTable;	/* address of string table */
	TABLE_HANDLE 	*TableList;		/* address of table list */
	DB_HEAD 		DBHead;			/* DB_HEAD */
	DB_UINT8 			*DBPath;		/* db file path */
	void            *fp;

	DB_INT8 (* SQLExecute)(DB_UINT8*, struct tDBHANDLE*);	/* SQL execute rountine */
	void				*RecordSet;		/* recordset after SQL execute */
	DB_UINT16			TableNum;		/* number of table handle in table list */
	DB_UINT8			OpenMode;		/* reserved for future */
	DB_UINT8			Status;			/* 0: normal, 1: changed */
};

/* record set for table operation */
typedef struct {
	TABLE_HANDLE *Table;
	DB_UINT8 (* First)(TABLE_HANDLE *);
	DB_UINT8 (* Last)(TABLE_HANDLE *);
	DB_UINT8 (* Prev)(TABLE_HANDLE *);
	DB_UINT8 (* Next)(TABLE_HANDLE *);
	DB_UINT8 (* Filter)(DB_HANDLE *,TABLE_HANDLE *,DB_UINT8 *,DB_UINT8 *,DB_UINT8 *);
	DB_UINT8 (* FilterReset)(TABLE_HANDLE *);
} RECORD_SET;

/* filter match parameter */
typedef struct {
    DB_UINT8 	KeyName[DB_MAX_NAME_LEN];		/* key name */
    DB_INT8 	V1[DB_MAX_NAME_LEN];			/* value1 */
    DB_INT8 	V2[DB_MAX_NAME_LEN];			/* value2 */
    DB_UINT8 	SelMod;			/* compare operator.
    						0(v!=v1), 1(v==v1), 2(v>=v1), 3(v<=v1), 
    						4(v>v1), 5(v<v1), 6(v1<v<v2), 7(v<v1||v>v2)
    					*/
    DB_UINT8 Reset;
                            
} FILTER_PARAM;

/*
*	TableSelect()函数的参数，为了简化起见
*	TableName 开头记录目标表的名字，后面跟着字段名
*/
struct tNameChain
{
	DB_UINT8 KeyName[DB_MAX_NAME_LEN];
	struct tNameChain * Next;
};
typedef struct tNameChain NAME_CHAIN;

struct tFilterChain
{
	FILTER_PARAM CurParam;
	struct tFilterChain * Next;
};
typedef struct tFilterChain FILTER_CHAIN;

typedef struct
{
	NAME_CHAIN *NameChain;			/* key name chain */
	DB_UINT8 KeyNum;					/* number of keys to select */
	FILTER_CHAIN * FilterChain;		/* filter parameters chain */
	DB_UINT8 FilterNum;					/* number of filters */
} SELECT_PARA;

/* parameter of function tablesort */
typedef struct 
{
	DB_UINT8 *keyname;					/* key name */
	DB_UINT8 sorttype;					/* 0: sort descending, 1: sort ascending */
} SORT_KEYS;

typedef struct {
	DB_UINT8 *rdbuf;		/* file read buffer */
	DB_UINT8 *linebuf;		/* one line string */
	DB_UINT32 rd;			/* rd pointer in read buffer */
	DB_UINT32 fsize;			/* file size */
	DB_UINT32 total_rd;		/* total read size */
	DB_UINT32 linebufsz;
	DB_UINT32 rdbufsz;
	
} t_FILE_LINE;

typedef struct POS_OFFSET
{
	DB_INT16 keyindex;
	DB_INT16 offset;
} t_POS_OFFSET;


#endif

