/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : fs.h
** Revision : 1.00											
**																	
** Description: filesytem data and api on linux platform
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
**		...
** 1.01
**       modified by ...
**
*/

#ifndef _FS_H_
#define _FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>      //for mkdir

/* TODO: PATH SPLIT SYMBOL */
#define KRK_PATH_SPLIT	'/'
#define KRK_CHK_PATH_SPLIT(ch) 	((ch)=='\\' || (ch)=='/')
/* TODO: END */

/* TODO: FILE SYSTEM API */
#define krk_fs_init(a)
#define krk_fs_deinit()
#define krk_entryisdir(dirent)		(dirent->d_type == DT_DIR)
#define krk_get_entry_name(dirent)	(dirent->d_name)
#define remove(fn)					unlink(fn)
#define krk_fsize(fp)				_fsize(fp)
#define krk_fs_freespace(mp)		_fs_freespace(mp)
#define krk_format(partname, fsname, para)

/* TODO: END */

#ifdef __cplusplus
extern "C" {
#endif 

extern unsigned int _fsize(FILE *fp);
extern unsigned long _fs_freespace(const char* path);
extern int stricmp(const char *dst, const char *src);


#ifdef __cplusplus
}
#endif 

#endif
