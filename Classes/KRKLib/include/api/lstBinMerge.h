/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : DBCombiner.h
** Revision : 1.00											
**																	
** Description: DB update api
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by ...
**
*/

#ifndef _LSTBINMERGE_H_
#define _LSTBINMERGE_H_

#define LSTBIN_MERGE_PATH_SZ		128

/*
* maximum songlist.bin files supports
*/
#define MAX_LSTBIN_CNT				8

/*
*	output parameter of lstbinToMemory
*/
typedef struct 
{
	char* mlist;
	char* mname;
	char* muniname;
	unsigned int* mindex;
	unsigned int totalcount;
	unsigned int namesz;
	unsigned int nodesize;
	unsigned int uninamesz;
} lstbinDumpMem_t;

enum
{
	MERGE_SONGNAME,
	MERGE_SONGNAME1,
	MERGE_SONGNAME2,
	MERGE_SONGNAME_MODE1,    // both songname.bin and songname1.bin
	MERGE_ALL,
};

enum
{
	MERGE_TYPE_SORT = 0,		/* sort by index */
	MERGE_TYPE_CHKSUM,		/* create a chksum file for all songlist.bin, use for check files change */
};

/*
* songlist.bin merge input parameter
*/
typedef struct 
{
	int		lstbin_cnt;
	char*  lstbin_path[MAX_LSTBIN_CNT];
	char*	lstbin_name;									/* path to save merged songlist.bin */
	char*	songname;									/* whether to merge songname.bin,songname1.bin,songname2.bin*/
	char*      unisongname;
	char		merged_path[LSTBIN_MERGE_PATH_SZ];			/* path to save merged songlist.bin */
	int		songname_type;
	int		merge_type;
	char*	chkfile_name;
	
} lstbinMergePara_t;

#ifdef __cplusplus
extern "C" {
#endif 

extern int lstbinMerge(lstbinMergePara_t* uPara);

#ifdef __cplusplus
}
#endif 

#endif


