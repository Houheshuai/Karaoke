/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : arch.h
** Revision : 1.00											
**																	
** Description: platform config parameters
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


#ifndef _ARCH_CONFIG_H_
#define _ARCH_CONFIG_H_

#define RES_RESO_WIDTH 1280
#define RES_RESO_HEIGHT 720

/* TODO: SETUP YOUR GPIOS */

/*
*	GPIO set of auth chip
*/
#define KRK_AUTH_SET_CS				KRK_GPIO_SET_VALUE(GPIO_AUTH_CS_ID, 1)
#define KRK_AUTH_CLR_CS				KRK_GPIO_SET_VALUE(GPIO_AUTH_CS_ID, 0)
#define KRK_AUTH_SET_CLK				KRK_GPIO_SET_VALUE(GPIO_AUTH_CLK_ID, 1)
#define KRK_AUTH_CLR_CLK				KRK_GPIO_SET_VALUE(GPIO_AUTH_CLK_ID, 0)
#define KRK_AUTH_SET_DAT				KRK_GPIO_SET_VALUE(GPIO_AUTH_DAT_ID, 1)
#define KRK_AUTH_CLR_DAT				KRK_GPIO_SET_VALUE(GPIO_AUTH_DAT_ID, 0)
#define KRK_AUTH_GET_DAT			KRK_GPIO_GET_VALUE(GPIO_AUTH_DAT_ID)

/* TODO: END */

typedef enum
{
	/* TODO: ADD GPIO ID */
	GPIO_AUTH_CS_ID = 0,
	GPIO_AUTH_CLK_ID,
	GPIO_AUTH_DAT_ID,

	/* TODO: END */

	GPIO_TOTAL_COUNT,
		
} krk_gpio_id_et;

#ifdef __cplusplus
extern "C" {
#endif 

extern int krk_arch_init(const char* resPath, int w, int h);

extern int krk_arch_deinit(void);

extern int krk_disp_init(const char* resPath, int w, int h);

extern int krk_disp_deinit(void);

#ifdef __cplusplus
}
#endif 

#endif

