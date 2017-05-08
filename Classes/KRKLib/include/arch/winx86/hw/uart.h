/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : uart.h
** Revision : 1.00											
**																	
** Description: uart api
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

#ifndef _UART_H_
#define _UART_H_

/* TODO: UART HANDLER */
typedef int krk_uart_handle_t;
/* TODO: END */

/* TODO: UART ERROR HANDLER */
#define KRK_UART_ERR_HANDLE		0
/* TODO: END */

typedef enum
{
	/* TODO: ADD UART PORT ID */
	UART_PORT_ID_TP = 0, 	/* touch panel */
	UART_PORT_ID_MIDI,		/* dream MIDI */
	/* TODO: END */

	UART_PORT_ID_COUNT
	
} UART_PORT_ID_et;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: krk_UARTOpen
 * Arguments      	: port - uart port ID
 * Return         	: uart handler
 * Description    	: open uart port by port ID
 *					
*/
extern krk_uart_handle_t krk_UARTOpen(UART_PORT_ID_et port);

/*
 * Function name  	: krk_UARTClose
 * Arguments      	: handle - uart handler
 * Return         	: 0 - succ, <> error code
 * Description    	: close uart port by port ID
 *					
*/
extern int krk_UARTClose(krk_uart_handle_t handle);

/*
 * Function name  	: krk_UARTRead
 * Arguments      	: handle - uart handler
 *									buf - read buffer
 *									sz - read byte size
 * Return         	: actually read size in byte
 * Description    	: read bytes to buffer
 *					
*/
extern int krk_UARTRead(krk_uart_handle_t handle, unsigned char* buf, int sz);

/*
 * Function name  	: krk_UARTWrite
 * Arguments      	: handle - uart handler
 *									buf - write buffer
 *									sz - write byte size
 * Return         	: actually write size in byte
 * Description    	: write bytes to uart Port 
 *					
*/
extern int krk_UARTWrite(krk_uart_handle_t handle, unsigned char* buf, int sz);

#ifdef __cplusplus
}
#endif 

#endif


