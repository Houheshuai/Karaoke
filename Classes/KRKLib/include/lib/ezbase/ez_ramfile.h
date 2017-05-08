/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_ramfile.h
** Revision : 1.00											
**																	
** Description: memory file tountine
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
************************ HOWTO *******************************
** 
**
*/

#ifndef _EZRAMFILE_H_
#define _EZRAMFILE_H_

typedef enum
{
	RF_MODE_SINGLE_BUF = (1<<0),
	RF_MODE_CIRCLE_BUF = (1<<1),
	RF_MODE_READ = (1<<2),
	RF_MODE_WRITE = (1<<3)
	
} ezRamFileMode_t;

typedef void* (*rf_fopen_t)(const char * filename, const char * mode);
typedef int (*rf_fclose_t)(void* fp);
typedef int (*rf_fread_t)(void * ptr, unsigned int size, unsigned int nmemb, void * stream);
typedef int (*rf_fwrite_t)(void * ptr, unsigned int size, unsigned int nmemb, void * stream);
typedef int (*rf_fseek_t)(void * stream, unsigned int offset, int whence);
typedef int (*rf_fsize_t)(void * stream);

typedef struct 
{
	rf_fopen_t 	rf_fopen;
	rf_fclose_t 	rf_fclose;
	rf_fread_t 	rf_fread;
	rf_fwrite_t 	rf_fwrite;
	rf_fseek_t 	rf_fseek;
	rf_fsize_t 		rf_fsize;
} ezRamFileOprs_t;

/*
*	vector base structure
*/
typedef struct {
	void*	fileBuf;					/* file data buffer address */
	void*	filelock;					/* multi-thread lock for file access */
	void*	mountpoint;			/* file storage mount point */
	void*	filename;				/* file name string */
	void*	fp_usr;					/* usr file hdle, use in circle buffer mode */
	int		bufsz;						/* file buffer size in bytes */
	int 		datasz;					/* file data size in bytes */
	int		offset;					/* current access offset in file buffer */
	int		offset_usr;			/* use in circle buffer mode, save usr rw offset */
	int		mode;
	int		refercount;			/* file open counter */
	int		inputbuf;				/* buf malloc externel, must be free externel*/
	int		buf_ratio;				/* bufsz/buf_ratio is block size of a single fread/fwrite */
	ezRamFileOprs_t*	fileoprs;
} ezRamFile_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_ramfile_mount
 * Arguments      	: name - ram partition name
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: mount a ram file partition
 *					
*/
extern int ez_ramfile_mount(const char* name);

/*
 * Function name  	: ez_ramfile_unmount
 * Arguments      	: name - ram partition name
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: unmount a ram file partition
 *					
*/
extern int ez_ramfile_unmount(const char* name);

/*
 * Function name  	: ez_ramfile_load
 * Arguments      	: rf - ram filehandle, name - load this file to ram file
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: load file data to ram file
 *					
*/
extern int ez_ramfile_load(ezRamFile_t* rf, const char* name);

/*
 * Function name  	: ez_ramfile_dump
 * Arguments      	: rf - ram filehandle, name - dump ram file to this disk file
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: dump ramfile to disc file
 *					
*/
extern int ez_ramfile_dump(ezRamFile_t* rf, const char* name);

/*
 * Function name  	: ez_ramfile_new
 * Arguments      	: name - ram file name, bufsz - ram buffer size, mode - ramfile mode, see. ezRamFileMode_t
 * Return         	: vector pointer
 * Description    	: create a ram file
 *					
*/
extern ezRamFile_t* ez_ramfile_new(const char* name, char* buf, int bufsz, int mode);

/*
 * Function name  	: ez_ramfile_free
 * Arguments      	: ramfile pointer
 * Return         	: none
 * Description    	: destroy a ramfile
 *					
*/
extern void ez_ramfile_free(ezRamFile_t* rf);

/*
 * Function name  	: ez_ramfile_set_fileoprs
 * Arguments      	: name - ram file name, bufsz - ram buffer size, mode - ramfile mode, see. ezRamFileMode_t
 * Return         	: none
 * Description    	: set file operation callback functions
 *					
*/
extern void ez_ramfile_set_fileoprs(ezRamFile_t* rf, ezRamFileOprs_t* foprs);

/*
 * Function name  	: ez_ramfile_reset_fileoprs
 * Arguments      	: 
 * Return         	: none
 * Description    	: reset file operation callback functions to default
 *					
*/
extern void ez_ramfile_reset_fileoprs(ezRamFile_t* rf);

/*
 * Function name  	: ez_ramfile_open
 * Arguments      	: name - ram file name, mode - 0:read, 1:write
 * Return         	: ram file pointer
 * Description    	: open a ram file
 *					
*/
extern ezRamFile_t* ez_ramfile_open(const char* name);

/*
 * Function name  	: ez_ramfile_close
 * Arguments      	: rf - ram file pointer
 * Return         	: 0 - succ, <>0 - fail
 * Description    	: close a ram file
 *					
*/
extern int ez_ramfile_close(ezRamFile_t* rf);

/*
 * Function name  	: ez_ramfile_read
 * Arguments      	: rf - ram file pointer, buf - buffer address, size - size in bytes
 * Return         	: actually read size 
 * Description    	: read data from ram file
 *					
*/
extern unsigned int ez_ramfile_read(ezRamFile_t* rf, void* buf, unsigned int size);

/*
 * Function name  	: ez_ramfile_write
 * Arguments      	: rf - ram file pointer, buf - buffer address, size - size in bytes
 * Return         	: actually write size 
 * Description    	: write data to ram file
 *					
*/
extern unsigned int ez_ramfile_write(ezRamFile_t* rf, void* buf, unsigned int size);

/*
 * Function name  	: ez_ramfile_seek
 * Arguments      	: rf - ram file pointer, offset - seek offset, opr - same with fseek parameter
 * Return         	: 0 - succ, -1 - err
 * Description    	: seek in ram file
 *					
*/
extern int ez_ramfile_seek(ezRamFile_t* rf, int offset, int opr);

/*
 * Function name  	: ez_ramfile_tell
 * Arguments      	: rf - ram file pointer
 * Return         	: current position
 * Description    	: get file current position
 *					
*/
extern unsigned int ez_ramfile_tell(ezRamFile_t* rf);

/*
 * Function name  	: ez_ramfile_set_buf_ratio
 * Arguments      	: ramfile pointer
 * Return         	: 0 - succ, <>0 err code
 * Description    	: create a ram file
 *					
*/
extern int ez_ramfile_set_buf_ratio(ezRamFile_t* rf, int buf_ratio);

#ifdef __cplusplus
}
#endif

#endif

