/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : mem.h
** Revision : 1.00											
**																	
** Description: hardware memmory map and heap management for karaoke
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

#ifndef _MEM_H_
#define _MEM_H_

#define KRK_MEM_DEBUG		0 // 1

/* TODO: HEAP MALLOC API */
#define KRK_MAX_HEAP	1

#if KRK_MEM_DEBUG
#define krk_sys_realloc(addr, size) 		winx86_realloc(addr, size, __FILE__, __LINE__)
#define krk_sys_free(addr) 				winx86_free((void*)addr, __FILE__, __LINE__)
#define krk_sys_malloc(bytes) 		winx86_malloc(bytes, __FILE__, __LINE__)
#define krk_sys_calloc(count, size) 		winx86_calloc(count, size, __FILE__, __LINE__)
#else
#define krk_sys_realloc(addr, size) 		winx86_realloc(addr, size, NULL, 0)
#define krk_sys_free(addr) 				winx86_free((void*)addr, NULL, 0)
#define krk_sys_malloc(bytes) 		winx86_malloc(bytes, NULL, 0)
#define krk_sys_calloc(count, size) 		winx86_calloc(count, size, NULL, 0)
#endif

#define krk_sys_freespace()			winx86_mem_freespace()
#define krk_sys_heap_chk()				1

#define krk_app_realloc(addr, size) 		krk_sys_realloc(addr, size)
#define krk_app_calloc(count, size) 		krk_sys_calloc(count, size)
#define krk_app_malloc(bytes) 		krk_sys_malloc(bytes)
#define krk_app_free(addr) 				krk_sys_free(addr)
#define krk_app_freespace()			krk_sys_freespace()
#define krk_app_heap_chk()			1
#define krk_app_get_safe_freespace()			1000000
#define krk_app_set_safe_freespace(fs)			

#define KRK_PRINT_FREEMEM()				{mem_printf("===========================================\n");\
																	mem_printf("= Free Memory Size : %d\n", krk_app_freespace());\
																	mem_printf("===========================================\n");}
/* TODO: END */

#if (KRK_MEM_DEBUG==1)
#undef malloc
#define malloc(x)			krk_app_malloc(x)
#define calloc(n, x)		krk_app_calloc(n,x)
#define realloc(p,x)		krk_app_realloc(p,x)
#define free(x)				krk_app_free(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/*
* calloc physical memory in winx86 system pool
*
* @param
*		size- malloc buffer size in bytes
* @return - malloc buffer address
*/
extern void* winx86_realloc(void* addr, unsigned int size, char* file, int lineno);

/*
* calloc physical memory in winx86 system pool
*
* @param
*		size- malloc buffer size in bytes
* @return - malloc buffer address
*/
extern void* winx86_calloc(unsigned int count, unsigned int size, char* file, int lineno);

/*
* malloc physical memory in winx86 system pool
*
* @param
*		size- malloc buffer size in bytes
* @return - malloc buffer address
*/
extern void* winx86_malloc(unsigned int size, char* file, int lineno);

/*
* free physical memory to winx86 system pool
*
* @param
*		ptr- free buffer address
* @return - none
*/
extern void winx86_free(void* ptr, char* file, int lineno);

/*
* get free physical memory size
*
* @param
*		none
* @return - memory size in bytes
*/
extern unsigned int winx86_mem_freespace(void);

/*
* initialize karaoke memory map
*
* @params
*		heap_size- custom heap size
* @return - 0: succ, <>0 error code 
*/
extern int krk_mem_init(int heap_size);

/*
* deinitialize karaoke memory map
*
* @param
*		none
* @return - 0: succ, <>0 error code 
*/
extern int krk_mem_deinit(void);

#ifdef __cplusplus
}
#endif 

#endif


