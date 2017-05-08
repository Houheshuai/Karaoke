/*********************************************************************
**																	
**  Copyright (C) 2011 Multak,Inc.									
**  All rights reserved												
**        Filename : db_fopr.h/ Project: EDB							
**        Revision : 1.31											
**																	
**   Note: file operation api		
**
**								Author: yucx
**														2010.8	
*********************************************************************/

#ifndef _DB_FOPR_H_
#define _DB_FOPR_H_

#if DB_SINGLE_FILE

#define DB_FILE_MAX_NUM			128

typedef struct s_DBFileInf{
	DB_UINT8 FileName[DB_MAX_NAME_LEN];		/* file name, include extend name */
	DB_UINT32 FileStartBlock;					/* file offset in edb file */
	DB_UINT32 FileEndBlock;					/* file offset in edb file */
	DB_UINT32 FileSize;						/* file size in byte */
	DB_UINT8 State;							/* 0x80 - deleted  */
	DB_UINT8 Reserved[3];
	
} DBFileInf_st;

typedef struct s_DBFileHead{
	DB_INT32 HeadSize;			/* edb file head size */
	DB_UINT32 TotalFileLength;  /* edb file size */
	DB_UINT32 FileCount;						/* total file count in edb */
	DB_UINT32 MaxCount;
	DB_UINT8 EndianType;						/* endian type, 0 - small, 1 - big */
	DB_UINT8 Reserved[3];
	DBFileInf_st *FileInf;		/* file info list */
} DBFileHead_st;

struct s_DBFileHandle{
	DB_FILE  fp;				/* file pointer of edb file */
	DB_INT32 Mode;				/* file open mode */
	DB_INT32 Handle;			/* file handle, index of FileInf[] in DBFileHead_st */
	DB_UINT32 Position;			/* file position in edb file */
	DB_UINT32 FileLength;		/* file length in byte */
	DBFileHead_st *FileHead;	/* file head info */
	DB_UINT32 Dirty;			/* 1 - file is written, 0 - only read  */
};
	
typedef struct s_DBFileHandle * DB_FILE_P;

#ifdef __cplusplus
extern "C" {
#endif 

/*
*	remove table file
*	@name : table file name
*	return : 0 - success, !=0 - err code
*/
DB_INT32  
db_table_fremove(DB_HANDLE *db, DB_UINT8 *name);

/*
*	close table file
*	@tabf : table file 
*	return : 0 - success, !=0 - err code
*/
DB_INT32  
db_table_fclose(DB_FILE_P tabf);

/*
*	open table file
*	@dbf : edb file handle
*	@name : table file name, no path
*	@mode : open mode, DB_READ_ONLY or DB_EDIT_MODE or DB_INSERT_MODE
*	return : file handle
*/
DB_FILE_P 
db_table_fopen(DB_HANDLE *db, DB_UINT8 *name,DB_UINT32 size);

/*
*	read table file size
*	@fp : table file handle
*	return : file size in byte
*/
DB_UINT32  
db_fsize(DB_FILE_P tabf);

/*
*	seek in table or db file
*	@tabf : table file handle
*	@pos : new position to seek
*	@mode : 0-from beginning, 1-from current position, 2-from endding
*	return : new position, -1 is error
*/
DB_INT32  
db_fseek(DB_FILE_P tabf, DB_INT32 pos, DB_UINT32 mode);

/*
*	read db file 
*	@buf : read data buffer
*	@len1 : length
*	@len2 : length
*	@fp : db file handle
*	return : read length
*/
DB_UINT32  
db_fread(DB_UINT8 *buf, DB_UINT32 len1, DB_UINT32 len2, DB_FILE_P tabf);

/*
*	write db file 
*	@buf : read data buffer
*	@len1 : length
*	@len2 : length
*	@fp : db file handle
*	return : write length
*/
DB_UINT32  
db_fwrite(DB_UINT8 *buf, DB_UINT32 len1, DB_UINT32 len2, DB_FILE_P tabf);

/*
*	close edb file
*	@fp : db file handle
*	return : 0 - success, !=0 - error code
*/
 
DB_UINT8 
db_fclose(DB_FILE_P dbf);
	
/*
*	open db or table file
*	@db : database handle
*	@file_name : table file name, no path
*	@mode : open mode, DB_READ_ONLY or DB_EDIT_MODE
*	return : file handle
*/
DB_FILE_P 
db_fopen(DB_UINT8 *name,DB_INT32 mode);

/*
*	create edb file
*	@name : db file name
*	return : file handle
*/
DB_FILE_P 
db_fcreate(DB_UINT8 *name);

#ifdef __cplusplus
}
#endif 

#endif

#endif

