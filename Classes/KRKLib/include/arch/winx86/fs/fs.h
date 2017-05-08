/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : fs.h
** Revision : 1.00											
**																	
** Description: filesytem data and api on winx86 platform
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
#include <io.h>
#include <direct.h>
#include <conio.h>
#include <ctype.h> 

#define DT_DIR 1

struct dirent
{
	long d_ino; /* inode number 索引节点号 */
	unsigned long d_off; /* offset to this dirent 在目录文件中的偏移 */
	unsigned short d_reclen;/* length of this d_name 文件名长 */
	unsigned char d_type; /* the type of d_name 文件类型 */
	char d_name [256];/* file name (null-terminated) 文件名，最长255字符 */
};

typedef struct _finddata_t DIRENT;
typedef struct {
	DIRENT dirent;
	struct dirent entry;
	intptr_t dir;
	int firstflag;
}DIR;

/* TODO: PATH SPLIT SYMBOL */
#define KRK_PATH_SPLIT	'/'
#define KRK_CHK_PATH_SPLIT(ch) 	((ch)=='\\' || (ch)=='/')
/* TODO: END */

#define KRK_TMP_PATH						"e:/"

/* TODO: FILE SYSTEM API */
#define krk_fs_init(a)						win_fs_init(a)
#define krk_fs_deinit()						win_fs_deinit()
#define opendir(dirname)				win_opendir((const char *)(dirname))
#define closedir(dir)						win_closedir(dir)
#define readdir(dir)						win_readdir(dir)
#define krk_entryisdir(dirent)				win_entry_is_dir(dirent)
#define krk_get_entry_name(dirent)	win_get_entry_name(dirent)
#define fsync(fp)							

#define krk_format(partname, fsname, para)		//_format((const char *)partname,(const char *)fsname,(__hdle)para)
#define mkdir(dir, mod)							_mkdir(dir)
#define rmdir(dir)							_rmdir(dir)
#define krk_fsize(fp)						win_fsize(fp)
#define krk_fs_freespace(mountpoint)		win_fs_freespace(mountpoint)
/* TODO: END */

#ifdef __cplusplus
extern "C" {
#endif 

extern DIR* win_opendir(const char* dirname);

extern int win_closedir(DIR* dir);

extern struct dirent* win_readdir(DIR* dir);

extern int win_entry_is_dir(struct dirent* entry);

extern char* win_get_entry_name(struct dirent* entry);

extern unsigned int win_fsize(FILE* fp);

extern int win_fcopy(char *src, char *dest, char *buffer, int buf_size);

extern unsigned long win_fs_freespace(const char *mountpoint);

extern int win_fs_init(int para);

extern void win_fs_deinit(void);

#ifdef __cplusplus
}
#endif 

#endif
