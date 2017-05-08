/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : winx86.h
** Revision : 1.00											
**																	
** Description:  winx86 platform depended api and head files
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

#ifndef _WINX86_H_
#define _WINX86_H_

/* TODO: WINDOWS GLOBAL HEAD FILE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 
#include <windows.h>
/* TODO: END */

#undef  FALSE
#define FALSE (0)

#undef  TRUE
#define TRUE (1)

#ifndef NULL
#define NULL (0)
#endif

#ifndef false
#define false (0)
#endif
#ifndef true
#define true (1)
#endif

#ifndef __s32
#define __s32 int
#endif

#ifndef __u32
#define __u32 unsigned int
#endif

/* TODO: INLINE SYMBOL */
#define KRK_INLINE			
/* TODO: END */

/* TODO: PACKED STRUCT */
#define __krk_struct_pack				#pragma pack(push,1)
#define __krk_struct_pack_end	#pragma pack(pop)
/* TODO: END */

/* TODO: ENDIAN TYPE */
#define KRK_ARCH_ENDIAN			KRK_SMALL_ENDIAN
/* TODO: END */

/* TODO: DEBUG FLAG */
#ifdef _DEBUG_
#define _KRK_DEBUG_
#define KRK_PRINTF(...) krk_printf(__VA_ARGS__)
#define KRK_TRACE(...) printf("[TRACE]:L%d(%s) => ", __LINE__, __FILE__);printf(__VA_ARGS__)
#else
#define _KRK_ROM_
#ifdef KRK_UART_PRINT
#define KRK_PRINTF
#define _KRK_ROM_DEBUG_
#else
#define KRK_PRINTF
#endif
#define KRK_TRACE(...) 
#endif
/* TODO: END */

/* TODO: ENABLE/DISABLE INTERRUPT */
#define KRK_DISABLE_INTERRUPTS	   
#define KRK_ENABLE_INTERRUPTS		
/* TODO: END */

/* TODO: MELIS PLATFORM HEAD FILE */
/* karaoke necessary low level api head file on winx86 */
#include <arch/winx86/charset/charset_win.h>
#include <arch/winx86/os/mem.h>
#include <arch/winx86/os/os.h>
#include <arch/winx86/fs/fs.h>
#include <arch/winx86/gdi/gdi.h>
#include <arch/winx86/hw/gpio.h>
#include <arch/winx86/hw/audio_input.h>
#include <arch/winx86/hw/audio_output.h>
#include <arch/winx86/hw/mic_bypass.h>
#include <arch/winx86/hw/uart.h>
#include <arch/winx86/hw/i2c.h>
#include <arch/winx86/hw/irkeys.h>
#include <arch/winx86/hid/mouse.h>
#include <arch/winx86/media/iPicPlayer.h>
#include <arch/winx86/media/iMediaPlayer.h>
#include <arch/winx86/media/iMusicPlayer.h>
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
extern int random(void);

#ifdef __cplusplus
}
#endif
#endif

