/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : k_debug.h
** Revision : 1.00											
**																	
** Description: global debug switch for seprate functions
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

#ifndef _K_DEBUG_H_
#define _K_DEBUG_H_

/*
*	debug levels
*/
enum
{
	KRK_DEBUG_LEVEL_NONE = (1<<0),		// no debug info
	KRK_DEBUG_LEVEL_APP = (1<<1),			// application level code debug, least debug info
	KRK_DEBUG_LEVEL_LIB = (1<<2),			// library and middle ware level code debug
	KRK_DEBUG_LEVEL_ARCH = (1<<3),		// platform depended code debug
	KRK_DEBUG_LEVEL_QA = (1<<4),				// QA test code debug, check memory leak or critical bundary check
	
	KRK_DEBUG_LEVEL_ALL = 0xFFFF,			// enable all debug code 
};

#ifndef KRK_DEBUG_LEVEL
#define KRK_DEBUG_LEVEL (KRK_DEBUG_LEVEL_APP|KRK_DEBUG_LEVEL_ARCH)
#endif

/* 
*	debug mask define, note that it's bit mask, from 0,0x2,0x4,0x8,...,0x80000000 
*/
enum
{
	KRK_DEBUG_MASK_NONE 			= 0,
	KRK_DEBUG_MASK_AUDIO_IN 		= (1<<0),
	KRK_DEBUG_MASK_AUDIO_OUT 		= (1<<1),
	KRK_DEBUG_MASK_MUS 				= (1<<2),
	KRK_DEBUG_MASK_DB 			= (1<<3),
	KRK_DEBUG_MASK_GUI 				= (1<<4),
	KRK_DEBUG_MASK_FS				= (1<<5),
	KRK_DEBUG_MASK_MEM				= (1<<6),	
	KRK_DEBUG_MASK_OS				= (1<<7), 
	KRK_DEBUG_MASK_GDI				= (1<<8), 
	KRK_DEBUG_MASK_HW			= (1<<9),
	KRK_DEBUG_MASK_MALLOC			= (1<<10),
	KRK_DEBUG_MASK_VIDEO			= (1<<11),
	KRK_DEBUG_MASK_AUDIO			= (1<<12),
	KRK_DEBUG_MASK_KEYINPUT			= (1<<13),
	KRK_DEBUG_MASK_MOUSEINPUT 		= (1<<14),
	KRK_DEBUG_MASK_CHAOSPLAYER		= (1<<15),
	KRK_DEBUG_MASK_LYRIC					= (1<<16),
	KRK_DEBUG_MASK_STAFF					= (1<<17),
	KRK_DEBUG_MASK_SERVICE					= (1<<18),

	KRK_DEBUG_MASK_ASSERT				= (1<<30),
	
	KRK_DEBUG_MASK_ALL				= 0xFFFFFFFF,
};

/*
* Application debug print mask
*/
#if ((KRK_DEBUG_LEVEL&KRK_DEBUG_LEVEL_APP) == KRK_DEBUG_LEVEL_APP)
#define KRK_DEBUG_MASK_APP (KRK_DEBUG_MASK_GUI \
															|KRK_DEBUG_MASK_SERVICE \
															|KRK_DEBUG_MASK_DB \
															|KRK_DEBUG_MASK_KEYINPUT \
															|KRK_DEBUG_MASK_MOUSEINPUT	)
#else
#define KRK_DEBUG_MASK_APP (0)
#endif

/*
* platform depended code debug print mask
*/
#if ((KRK_DEBUG_LEVEL&KRK_DEBUG_LEVEL_ARCH) == KRK_DEBUG_LEVEL_ARCH)
#define KRK_DEBUG_MASK_ARCH (KRK_DEBUG_MASK_MEM \
															|KRK_DEBUG_MASK_GDI \
															|KRK_DEBUG_MASK_FS \
															|KRK_DEBUG_MASK_AUDIO_IN \
															|KRK_DEBUG_MASK_AUDIO_OUT \
															|KRK_DEBUG_MASK_VIDEO \
															|KRK_DEBUG_MASK_AUDIO \
															|KRK_DEBUG_MASK_HW \
															|KRK_DEBUG_MASK_MUS \
															|KRK_DEBUG_MASK_CHAOSPLAYER \
															|KRK_DEBUG_MASK_OS	)
#else
#define KRK_DEBUG_MASK_ARCH (0)
#endif

/*
* library code debug print mask
*/
#if ((KRK_DEBUG_LEVEL&KRK_DEBUG_LEVEL_LIB) == KRK_DEBUG_LEVEL_LIB)
#define KRK_DEBUG_MASK_LIB (KRK_DEBUG_MASK_MALLOC\
															|0)
#else
#define KRK_DEBUG_MASK_LIB (0)
#endif

/*
* QA code debug print mask
*/
#if ((KRK_DEBUG_LEVEL&KRK_DEBUG_LEVEL_QA) == KRK_DEBUG_LEVEL_QA)
#define KRK_DEBUG_MASK_QA (KRK_DEBUG_MASK_ASSERT\
															|0)
#else
#define KRK_DEBUG_MASK_QA (0)
#endif

/* 
*   if you only want to print some special functions debug infomation
*   just modify the KRK_DEBUG_MASK value, you can also use KRK_PRINTF, it prints anyway
*	caution:
*		all commented mask should be moved to bottom, because comment can not be insert into macro define
*		leave a blank line between macro and comment.
*/
#define KRK_DEBUG_MASK		(0 \
							|KRK_DEBUG_MASK_APP \
							|KRK_DEBUG_MASK_ARCH \
							|KRK_DEBUG_MASK_LIB \
							|KRK_DEBUG_MASK_QA \
							|KRK_DEBUG_MASK_CHAOSPLAYER \
							|0)
						
#define audin_printf(...)			if (KRKDebugMask & KRK_DEBUG_MASK_AUDIO_IN) 		(KRK_PRINTF("[AUDIN]-> "), KRK_PRINTF(__VA_ARGS__))
#define audout_printf(...)			if (KRKDebugMask & KRK_DEBUG_MASK_AUDIO_OUT) 	(KRK_PRINTF("[AUDOUT]-> "), KRK_PRINTF(__VA_ARGS__))
#define gui_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_GUI)					(KRK_PRINTF("[GUI]-> "), KRK_PRINTF(__VA_ARGS__))
#define fs_printf(...)					if (KRKDebugMask & KRK_DEBUG_MASK_FS)						(KRK_PRINTF("[FS]-> "), KRK_PRINTF(__VA_ARGS__))
#define mem_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_MEM)					(KRK_PRINTF("[MEM]-> "), KRK_PRINTF(__VA_ARGS__))
#define os_printf(...)					if (KRKDebugMask & KRK_DEBUG_MASK_OS)						(KRK_PRINTF("[OS]-> "), KRK_PRINTF(__VA_ARGS__))
#define gdi_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_GDI)					(KRK_PRINTF("[GDI]-> "), KRK_PRINTF(__VA_ARGS__))
#define media_printf(...)			if (KRKDebugMask & KRK_DEBUG_MASK_VIDEO)				(KRK_PRINTF("[VIDEO]-> "), KRK_PRINTF(__VA_ARGS__))
#define music_printf(...)			if (KRKDebugMask & KRK_DEBUG_MASK_AUDIO)				(KRK_PRINTF("[AUDIO]-> "), KRK_PRINTF(__VA_ARGS__))
#define hw_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_HW)					(KRK_PRINTF("[HW]-> "), KRK_PRINTF(__VA_ARGS__))
#define key_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_KEYINPUT)			(KRK_PRINTF("[KEY]-> "), KRK_PRINTF(__VA_ARGS__))
#define mus_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_MUS)					(KRK_PRINTF("[MUS]-> "), KRK_PRINTF(__VA_ARGS__))
#define cp_printf(...)					if (KRKDebugMask & KRK_DEBUG_MASK_CHAOSPLAYER)	(KRK_PRINTF("[CP]-> "), KRK_PRINTF(__VA_ARGS__))
#define lyric_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_LYRIC)				(KRK_PRINTF("[LYRIC]-> "), KRK_PRINTF(__VA_ARGS__))
#define staff_printf(...)				if (KRKDebugMask & KRK_DEBUG_MASK_STAFF)				(KRK_PRINTF("[STAFF]-> "), KRK_PRINTF(__VA_ARGS__))
#define service_printf(...)			if (KRKDebugMask & KRK_DEBUG_MASK_SERVICE)			(KRK_PRINTF("[SERVICE]-> "), KRK_PRINTF(__VA_ARGS__))

/* open or close debug in run time */
#define K_PRINT_LOG_ON()		krk_print_log_on()
#define K_PRINT_LOG_OFF(logfile)				krk_print_log_off(logfile)

#define K_PRINT_ON(MOD)		{KRKDebugMask |= (unsigned int)KRK_DEBUG_MASK_##MOD;}
#define K_PRINT_OFF(MOD)		{KRKDebugMask &= ~(unsigned int)KRK_DEBUG_MASK_##MOD;}

/* assert */
#if ((defined __FILE__) && (defined __LINE__))

#define KRK_ASSERT(assert_bool) 	if (!(assert_bool) && (KRKDebugMask & KRK_DEBUG_MASK_ASSERT)){\
										int assert_loop = 0;\
										int assert_brk = 1;\
										KRK_PRINTF("assert: tid=%d, file \"%s\", line %d\n", krk_os_task_gettid(NULL),  __FILE__, __LINE__); \
										KRK_OS_DISABLE_SCHEDULE();\
										while(assert_brk) assert_loop++;\
										KRK_OS_ENABLE_SCHEDULE();\
									}

#else

#define KRK_ASSERT(assert_bool) 	if (!(assert_bool) && (KRKDebugMask & KRK_DEBUG_MASK_ASSERT)){\
										int assert_loop = 0;\
										int assert_brk = 1;\
										KRK_PRINTF("-- in assert --\n"); \
										KRK_OS_DISABLE_SCHEDULE();\
										while(assert_brk) assert_loop++;\
										KRK_OS_ENABLE_SCHEDULE();\
									}

#endif

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int KRKDebugMask;

char* krk_print_log_bptr(void);

int krk_print_log_bpos(void);

void krk_print_log_set_bpos(int pos);

void krk_print_log_lock(void);

void krk_print_log_unlock(void);

int krk_print_log_on(void);

int krk_print_log_off(char* logfile);

/*
* print memory data
*
* @param
*		start - start address
*		size - size in integer
*		file - source file which print this memory
*		lineno - line number of this print code
* @return - print memory data in terminal
*/
extern void krk_print_mem(unsigned int* start, int size, char* file, int lineno);

/*
* dump memory data to file
*
* @param
*		start - start address
*		size - size in bytes
*		file - dump memory data to this file
* @return - dump memory data to file
*/
extern void krk_dump_mem(void* start, int size, char* file);

#ifdef __cplusplus
}
#endif

#endif	/*  _K_DEBUG_H_ */

