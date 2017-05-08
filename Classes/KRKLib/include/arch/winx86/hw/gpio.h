/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : gpio.h
** Revision : 1.00											
**																	
** Description: gpio set api on winx86
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
#define KRK_GPIO_INIT()								winx86_gpio_init()
#define KRK_GPIO_DEINIT()							winx86_gpio_deinit()
/* TODO: END */

/* TODO: GPIO SET MODE */
#define KRK_GPIO_SET_MODE(id, mode)	winx86_gpio_set_mode(id, mode)
/* TODO: END */

/* TODO: GPIO SET/GET VALUE */
#define KRK_GPIO_SET_VALUE(id, value)	winx86_gpio_set_value(id, value)
#define KRK_GPIO_GET_VALUE(id)				winx86_gpio_get_value(id)
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

typedef struct 
{
	int hdle;
	char* name;
} winx86_gpio_t;

#ifdef __cplusplus
extern "C" {
#endif 

extern void winx86_gpio_init(void);

extern void winx86_gpio_deinit(void);

extern void winx86_gpio_set_value(int id, int value);

extern int winx86_gpio_get_value(int id);

extern void winx86_gpio_set_mode(int id, krk_gpio_mode_et mode);

extern void Set_MK970_PIN(
	unsigned char p0dir, unsigned char p0level,
	unsigned char p1dir, unsigned char p1level
	);

#ifdef __cplusplus
}
#endif 

#endif
