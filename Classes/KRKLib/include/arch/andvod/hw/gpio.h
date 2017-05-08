/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : gpio.h
** Revision : 1.00											
**																	
** Description: gpio set api on linux
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

#ifndef _GPIO_H_
#define _GPIO_H_

/* TODO: GPIO INITIALIZE */
#define KRK_GPIO_INIT(para)								do {\
																					melis_gpio_init(para);\
																			}while(0);

#define KRK_GPIO_DEINIT()							do {\
																					melis_gpio_deinit();\
																			}while(0);
/* TODO: END */

/* TODO: GPIO SET MODE */
#define KRK_GPIO_SET_MODE(id, mode)	melis_gpio_set_mode(id, mode)
/* TODO: END */

/* TODO: GPIO SET/GET VALUE */
#define KRK_GPIO_SET_VALUE(id, value)	melis_gpio_set_value(id, value)
#define KRK_GPIO_GET_VALUE(id)				melis_gpio_get_value(id)
/* TODO: END */

#define KRK_MAX_GPIO		32

typedef enum
{
	GPIO_MODE_INPUT = 0,
	GPIO_MODE_OUTPUT= 1
	
} krk_gpio_mode_et;

typedef struct 
{
	int			count;
	const char* 	names[KRK_MAX_GPIO];
} krk_gpio_configin_t;

typedef int krk_gpio_hdle;

typedef struct 
{
	krk_gpio_hdle 	hdle;
	char 				name[32];
} krk_gpio_t;

#ifdef __cplusplus
extern "C" {
#endif 

extern void melis_gpio_init(void* configin);

extern void melis_gpio_deinit(void);

extern void melis_gpio_set_value(int id, int value);

extern int melis_gpio_get_value(int id);

extern void melis_gpio_set_mode(int id, krk_gpio_mode_et mode);

//extern void Set_Auth_PIN(unsigned char PA, unsigned char PB);

extern int open_gpio_dev(void);

extern int close_gpio_dev(void);

extern void Set_MK970_PIN(
	unsigned char p0dir, unsigned char p0level,
	unsigned char p1dir, unsigned char p1level
	);

#ifdef __cplusplus
}
#endif 

#endif
