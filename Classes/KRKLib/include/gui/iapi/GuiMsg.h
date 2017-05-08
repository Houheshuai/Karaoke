#ifndef _GUI_MSG_H_
#define _GUI_MSG_H_

/* 
* Marco to implement message process
*/
#define EZGUI_MSGPROC_DECLARE(CLASS)	extern int CLASS##_MsgProc(GuiMsg_et Msg, CWidget_t *widget, unsigned long wparam, unsigned long lparam)
#define EZGUI_REGISTER_CLASS(CLASS)	{CLASS##_CID, sizeof(CLASS##_t), CLASS##_MsgProc}
#define EZGUI_BEGIN_MSG_MAP(CLASS)		int CLASS##_MsgProc(GuiMsg_et Msg, CWidget_t *widget, unsigned long wparam, unsigned long lparam) { switch (Msg) { 
#define EZGUI_ADD_MSG(Msg, msgProc)		case Msg: return msgProc(widget, wparam, lparam);
#define EZGUI_END_MSG_MAP(BASECLASS)	default : return BASECLASS##_MsgProc(Msg, widget, wparam, lparam); } }

/* 
* GUI Messages 
*/
typedef enum
{
	/* TODO: ADD NEW MSG ID */
	EZGUI_MSG_NONE,
	EZGUI_MSG_INIT,									/* common control init */
	EZGUI_MSG_DEINIT,								/* common control free */
	EZGUI_MSG_MOUSEEVENT,					/* mouse event happened */
	EZGUI_MSG_KEYPRESS,       					/* IR/Keyboard press */
	EZGUI_MSG_CHANGE_SKIN, 					/* change GUI skin, load new skin resources */
	EZGUI_MSG_PART_MOUNTED,				/* partition mounted */
	EZGUI_MSG_PART_UNMOUNTED, 			/* partition unmounted */
	EZGUI_MSG_CONNECT_TO_PC, 			/* device connect to PC */
	EZGUI_MSG_DISCONNECT_FROM_PC,	/* device disconnect from PC */
	EZGUI_MSG_STARTUP, 							/* startup GUI main window */
	EZGUI_MSG_POWEROFF,						/* power off */
	EZGUI_MSG_ENTER_STANDBY, 					/* enter standby mode */
	EZGUI_MSG_EXIT_STANDBY,					/* exit standby mode */
	EZGUI_MSG_PAIR,							/*pair wireless mic*/
	EZGUI_MSG_HDMI_PLUGIN, 			/* HDMI plug in */
	EZGUI_MSG_HDMI_PLUGOUT, 			/* HDMI plug out */
	/* TODO END */
	
	EZGUI_MSG_TOTAL_CNT
}GuiMsg_et;

typedef int (*EZGUI_MSG_PROC)(GuiMsg_et, CWidget_t *, unsigned long, unsigned long);

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CWidget);
/* TODO END */

/*
 * Function name  	: ez_postMsg
 * Arguments      	: msg - gui message
 *					obj - control which accept this message
 					wparam - send message parameter
 * Return         	: 1 - succ, 0 -fail
 * Description    	: send message to one control
 *					
*/
extern int ez_postMsg(GuiMsg_et msg, CWidget_t *obj, unsigned long wparam, unsigned long lparam);

/*
 * Function name  	: ez_postMsgToActive
 * Arguments      	: msg - gui message
 *					obj - control which accept this message
 					wparam - send message parameter
 * Return         	: 0-succ, <>0-error code
 * Description    	: send message to focus window
 *					
*/
extern int ez_postMsgToActive(GuiMsg_et msg, CWidget_t *obj, unsigned long wparam, unsigned long lparam);

/*
 * Function name  	: ez_sendMsg
 * Arguments      	: app - application handle
 *									MsgID - gui message ID
 *                     			MsgValue - message attached value
 *									Param -  message attached parameter
 * Return         	: 0-succ, <>0-error code
 * Description    	: send message to GUI
 *					
*/
extern int ez_sendMsg(void* app, unsigned int MsgID, unsigned int MsgValue, unsigned int Param);

#ifdef __cplusplus
}
#endif

#endif

