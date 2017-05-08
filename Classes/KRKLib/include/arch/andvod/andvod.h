/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : andvod.h
** Revision : 1.00											
**																	
** Description:  android platform depended api and head files
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

#ifndef _ANDVOD_H_
#define _ANDVOD_H_

/* TODO: MELIS GLOBAL HEAD FILE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/time.h>
#include <malloc.h>

/* TODO: END */

#ifndef NULL
#define NULL (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define false (0)
#define true (1)

#ifndef abs
#define abs(x) ((x) >= 0 ? (x):-(x))
#endif
/*
#ifndef atoi
#define atoi(a)						myatoi((const char*)(a))
#endif
#ifndef itoa
#define itoa(i,a,f)					myitoa(i,a,f)
#endif
*/

/* TODO: INLINE SYMBOL */
#define KRK_INLINE		
/* TODO: END */

/* TODO: PACKED STRUCT */
#define __krk_struct_pack		__packed
#define __krk_struct_pack_end
/* TODO: END */

/* TODO: ENDIAN TYPE */
#define KRK_ARCH_ENDIAN			KRK_SMALL_ENDIAN
/* TODO: END */

/* TODO: DEBUG FLAG */
#include <android/log.h>
#undef  KRK_PRINTF
#define KRK_PRINTF(...) __android_log_print(ANDROID_LOG_INFO,"KRKLIB",__VA_ARGS__)

//#define KRK_PRINTF(...) 				printf(__VA_ARGS__)
#if EPDK_DEBUG_LEVEL
#define _KRK_DEBUG_
#define KRK_TRACE(...) KRK_PRINTF("[TRACE]:L%d(%s) => ", __LINE__, __FILE__);KRK_PRINTF(__VA_ARGS__)
#else
#define _KRK_ROM_
#define KRK_TRACE(...)
#endif
/* TODO: END */

/* TODO: ENABLE/DISABLE INTERRUPT */
#define KRK_DISABLE_INTERRUPTS	   
#define KRK_ENABLE_INTERRUPTS		
/* TODO: END */

/* TODO: STDIO/STDLIB/MEM API */
/* TODO: END */

/* TODO: MELIS PLATFORM HEAD FILE */
#include <arch/andvod/charset/charset_iconv.h>
#include <arch/andvod/os/mem.h>
#include <arch/andvod/os/os.h>
#include <arch/andvod/fs/fs.h>
#include <arch/andvod/gdi/gdi.h>
#include <arch/andvod/hw/gpio.h>
#include <arch/andvod/hw/audio_input.h>
#include <arch/andvod/hw/audio_output.h>
#include <arch/andvod/hw/mic_bypass.h>
#include <arch/andvod/hw/uart.h>
#include <arch/andvod/hw/irkeys.h>
#include <arch/andvod/hid/mouse.h>
#include <arch/andvod/media/iMediaPlayer.h>
#include <arch/andvod/media/iMusicPlayer.h>
#include <arch/andvod/media/iPicPlayer.h>

/* TODO: END */

#ifdef __cplusplus
extern "C" {
#endif
extern int krk_printf(const char *format, ...);
extern int krk_upgradeFirmware(void* para);
extern int krk_sys_reset(void* para);
extern int krk_hw_init(void* para);
extern int krk_hw_deinit(void);
extern int read_sdc_cid(char* cid, int rdsz);
extern handle_audin_t* audio_in_handle(void);
extern char * itoa(int i, char *a, int r);
#ifdef __cplusplus
}
#endif

#endif

