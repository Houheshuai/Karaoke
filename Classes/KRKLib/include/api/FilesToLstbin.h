/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : FilesToLstbin.h
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

#ifndef _FILESTOLSTBIN_H_
#define _FILESTOLSTBIN_H_

#include <lib/ezbase/ez_vector.h>
#include <lib/update/ReqData.h>
#include <lib/update/ReqLstBin.h>

#define FL_PATH_SZ		1024

//#define MV_SONGID_START 1000000
//#define MV_SONGID_END 99999999
#define CDG_SONGID_START	100000  //80000
#define CDG_SONGID_END		799999//99999
/*
* files to songlist.bin event type
*/
enum
{
	FL_EVENT_NONE = 0,
	FL_EVENT_BEGIN,
	FL_EVENT_PERCENT,
	FL_EVENT_END,
	FL_EVENT_ERR,
};
enum {
	SplitType_None = 0,
	SplitType_Single,				// '-'
	SplitType_Double,			// double char '-'
	SplitType_Path,					// path split '/'
};

typedef struct 
{
	char name[FL_PATH_SZ];
} parseFileName_t;

/*
* songlist.bin file context in memory
*/
typedef struct 
{
	ezVector_t* infoItems;
	ezVector_t* nameItems;
	ezVector_t* pathItems;
	int				startIndex;
} lstbinContext_t;


/*
* language info input to module
*/
typedef struct 
{
	char languageName[32];
	int	languageId;
	
} languageInfo_t;

/*
* name info parsed from file name
*/
typedef struct 
{
	char songName[96];
	char singerName[48];
	int songid;
	int language;
	
} nameInfo_t;

typedef struct tagFilesToLstbinPara filesToLstBinPara_t;

typedef int (*filesToLstBinEventCbf)(int,void*, void*);
typedef	filesToLstBinEventCbf filesToLstBinCb_t;

typedef int (*fmt_check_cb)(const char* fn);
typedef int (*parse_name_cb)(const char* name, nameInfo_t* info, filesToLstBinPara_t* para);

/*
* files parse to songlist.bin input parameters
*/
struct tagFilesToLstbinPara
{
	const char* 					srcdir;						/* source files folder */
	const char* 					lstbinfile;				/* destiny songlist.bin path */
	const char* 					namefile;				/* destiny songname.bin path */
	languageInfo_t*				languages;
	int									languageCount;
	
	fmt_check_cb					fmt_chk;					/* check suffix callback */
	parse_name_cb				name_parser;			/* file name parser callback */

	int									startIndex;				/* start songindex */
	int									intelligent;				/* get singer name intelligent */
	void*								singerCache;			/* singer names cache */
	
	const char* 					pathfile;				/* destiny songname1.bin path */
//	singer_namechk_cb		singer_cb;
	
};

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name		: allocLstbinOrderIndex
 * Arguments				: indexfile - path of file "SONGLIST.BIN"
 * Return 					: 0 - succ, <>0 error code
 * Description			: alloc an orderindex 
 *					
*/
extern int allocLstbinOrderIndex(const char* indexfile);

/*
 * Function name  	: getLstbinFirstOrderIndex
 * Arguments      	: binfile - path of file "SONGLIST.BIN"
 * Return         	: 0 - succ, <>0 error code
 * Description    	: get the first OrderIndex value in SONGLIST.BIN
 *					
*/
extern int getLstbinFirstOrderIndex(const char* binfile);

/*
 * Function name  	: getLstbinSongFilePath
 * Arguments      	: binfile - path of file "SONGLIST.BIN"
 * Return         	: 1 - succ, 0 -fail
 * Description    	: get the song path from SONGNAME.BIN&SONGLIST.BIN
 *					
*/
extern int getLstbinSongFilePath(const char* binfile, const char* namefile, char* songPath, int maxsz, int songId);
/*
 * Function name  	: exportCDGList
 * Arguments      	: binfile - path of file "Songlist.BIN" "songname.bin" "cdglist.bin"
 * Return         	: number of CDG songs
 * Description    	: Export CDG list
 *					
*/
extern int exportCDGList(const char* binfile, const char* namefile,const char* listfile);

/*
 * Function name  	: filesToLstBin
 * Arguments      	: para - input update parameters
 * Return         	: 0 - succ, <>0 error code
 * Description    	: parse files info from file name and save in songlist.bin
 *					
*/
extern int filesToLstBin(filesToLstBinPara_t* para);
extern void singerNameExtract(const char* singerName);

#ifdef __cplusplus
}
#endif 

#endif


