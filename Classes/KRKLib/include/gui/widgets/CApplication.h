#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include <gui/widgets/CWidget.h>

#define CApplication_ClassID					1

#define APP_STANDBY_TIMEOUT						0x7FFFFFFF

/*
* application exit event initialized value
*/
#define AppExit_EventNone					-1

/* TODO: REGISTER WIDGETS */
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CApplication_RegMethods(app) {\
	ezRegMethod(app, CApplication, run);\
	ezRegMethod(app, CApplication, stop);\
	ezRegMethod(app, CApplication, exit);\
	ezRegMethod(app, CApplication, setKeyEventCallback);\
	ezRegMethod(app, CApplication, setMouseEventCallback);\
	ezRegMethod(app, CApplication, setKeyMap);\
	ezRegMethod(app, CApplication, onExit);\
}
/* TODO END */

/* TODO: CAPPLICATION EVENT ID */
enum ApplicationEventID {
	ApplicationEvent_onExit = ((CApplication_ClassID<<8) + 1),
	ApplicationEvent_onExited = ((CApplication_ClassID<<8) + 2),

	ApplicationEventCount
};
/* TODO END */

/* application exit event argument */
typedef struct {
	WidgetEventArgs_t		we;

	WidgetEventEntry_t	eventEntry;
	int								exitEvent;
	
} AppExitEventArgs_t;

/*
* application state
*/
typedef enum
{
	GuiAppState_Stopped = 0,
	GuiAppState_Running,
	
}GuiAppState_et;

/*
* DemoSong state
*/
typedef enum{

	StandBy_Off = 0,
	StandBy_On,

}StandByState_et;

typedef struct s_CApplication CApplication_t;

typedef int (*AppUserParseUIKey_t)(CApplication_t *, int uikey);
typedef void (*AppSetIALEventCallback_t)(CApplication_t *, ezIALEventCallback_t callback);
typedef void (*AppSetIALKeyMap_t)(CApplication_t *, ezCustKeyMap_t*, int);
typedef int (*AppRun_t)(CApplication_t *);
typedef int (*AppExit_t)(CApplication_t *, int);

typedef struct 
{
	unsigned int					d_timer;			//!< Timer used to track clicks for this button.
	int								d_click_count;		//!< count of clicks made so far.
	gdi_rect_t					d_click_area;		//!< area used to detect multi-clicks
	CWidget_t*         		d_target_window;    //!< target window for any events generated.
	
} MouseClickTracker;

#include <gui/iapi/GuiLog.h>

struct s_CApplication
{
	CWidget_t 				Widget;
	
	/* TODO: CONTROL ATTRIBUTES  */
	const char*						AppName;
	krk_os_task_t*					Task;
	krk_os_sema_t*					Sema;
	krk_os_msgqueue_t*			Queue;
	GuiAppState_et					state;
	void*									formClassRegistry;
	int										formClassRegistryCount;
	formLogEntry_t*					formLogRegistry;
	int										formLogRegistryCount;
	ezResource_t*					Resource;
	ezWidgetID_t						startupForm;
	CWidget_t*							modalTarget;
	CWidget_t*							captureWidget;
	CWidget_t**						deadPool;
	unsigned int						deadCount;
	unsigned int						deadSize;

	unsigned long						runTime;
	signed long							standbyTime;
	signed long							standbyTimeOut;
	signed int							standbyExitKey;
	int									StandByState;
	
	/* mouse&key parameter */
	ezImage_t*							cursorImage;
	ezMouseCursor_t				mouseCursor;
	CWidget_t*							widgetWithMouse;
	IALConfig_et						IALConfig;
	unsigned int						enableMouse;
	unsigned int						enableKey;
	ezIALEventCallback_t			keyEventCallback;
	ezIALEventCallback_t			mouseEventCallback;

	UIKeyScan							mouseToKey[ezMouseButtonCount];
	unsigned int						sysKeys;
	ezPoint								dragStartPos;
	unsigned int						isDrag;
	ezMouseDragDir				dragDir;
	ezCustKeyMap_t*				custKeyMap;
	int										custKeyMapSize;
	AppUserParseUIKey_t			usrKeyParser;			// parse ui key callback, use can define it's owner key parser in this callback
	
	unsigned int						click_timeout;
	unsigned int						dblclick_timeout;
	ezVector2							dblclick_size;
	MouseClickTracker 			click_trackers[ezMouseButtonCount];
	
	unsigned int						singleTask;
	unsigned int						fakeRender;
	int										exitEvent;
	int										disableCDEvent;		// disable form oncreated and ondestroyed event
	/* TODO END */
	
	/* TODO: CONTROL METHODS  */
	AppRun_t										run;
	AppRun_t										stop;
	AppExit_t										exit;
	AppSetIALEventCallback_t			setKeyEventCallback;
	AppSetIALEventCallback_t			setMouseEventCallback;
	AppSetIALKeyMap_t					setKeyMap;
	/* TODO END */
	
	/* TODO: CONTROL USER OVERRIDE EVENTS */
	WidgetEventEntry_t			onExit;
	/* TODO END */
	
} ;

typedef struct 
{
	GuiMsg_et	MsgID;
	unsigned int 	MsgValue;
	unsigned int	Param;      
}GuiAppMsg_st;

#ifdef __cplusplus
extern "C" {
#endif 

EZGUI_MSGPROC_DECLARE(CApplication);

#ifdef __cplusplus
}
#endif 

#endif
