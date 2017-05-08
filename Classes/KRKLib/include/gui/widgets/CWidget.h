#ifndef _CWIDGET_H_
#define _CWIDGET_H_

#define CWidget_ClassID										2

/* TODO: REGISTER MARCO */
#define CWidget_RegMethod(widget, Name)				ezRegMethod(widget, CWidget, Name)

#define CWidget_RegMethods(widget) {\
	CWidget_RegMethod(widget, constructor);\
	CWidget_RegMethod(widget, destructor);\
	CWidget_RegMethod(widget, transform);\
	CWidget_RegMethod(widget, setModalState);\
	CWidget_RegMethod(widget, getModalState);\
	CWidget_RegMethod(widget, setIntValue);\
	CWidget_RegMethod(widget, setStrValue);\
	CWidget_RegMethod(widget, setValue);\
	CWidget_RegMethod(widget, bindRecord);\
	CWidget_RegMethod(widget, setRecord);\
	CWidget_RegMethod(widget, setVisible);\
	CWidget_RegMethod(widget, enable);\
	CWidget_RegMethod(widget, disable);\
	CWidget_RegMethod(widget, drawSelf);\
	CWidget_RegMethod(widget, updateSelf);\
	CWidget_RegMethod(widget, activate);\
	CWidget_RegMethod(widget, deactivate);\
	CWidget_RegMethod(widget, createTimer);\
	CWidget_RegMethod(widget, destroyTimer);\
	CWidget_RegMethod(widget, resetTimer);\
	CWidget_RegMethod(widget, cleanupTimer);\
	CWidget_RegMethod(widget, startAction);\
	CWidget_RegMethod(widget, endAction);\
	CWidget_RegMethod(widget, setLayer);\
	CWidget_RegMethod(widget, onMouseWheel);\
	CWidget_RegMethod(widget, onMouseDragStart);\
	CWidget_RegMethod(widget, onMouseDragOver);\
	CWidget_RegMethod(widget, onMouseDragDrop);\
	CWidget_RegMethod(widget, onMouseMove);\
	CWidget_RegMethod(widget, onMouseEnter);\
	CWidget_RegMethod(widget, onMouseLeave);\
	CWidget_RegMethod(widget, onMouseButtonUp);\
	CWidget_RegMethod(widget, onMouseButtonDown);\
	CWidget_RegMethod(widget, onMouseClicked);\
	CWidget_RegMethod(widget, onMouseDoubleClicked);\
	CWidget_RegMethod(widget, onKeyUp);\
	CWidget_RegMethod(widget, onKeyDown);\
	CWidget_RegMethod(widget, onKeyPress);\
	CWidget_RegMethod(widget, onActivated);\
	CWidget_RegMethod(widget, onDeactivated); \
	CWidget_RegMethod(widget, onCaptureLost);\
	CWidget_RegMethod(widget, onCaptureGained); \
	CWidget_RegMethod(widget, onCreated);\
	CWidget_RegMethod(widget, onDestroyed);\
	CWidget_RegMethod(widget, onDraw);\
	CWidget_RegMethod(widget, onShown);\
	CWidget_RegMethod(widget, onHidden);\
	CWidget_RegMethod(widget, onTimeOut);\
	CWidget_RegMethod(widget, onStartAction);\
	CWidget_RegMethod(widget, onEndAction);\
}
/* TODO END */

#define Widget(p)		((CWidget_t*)((p)))
#define _val(a)		((unsigned long)(a))

typedef struct s_CWidget CWidget_t;

/* Widget state list */
typedef enum
{
	Widget_State_Normal = 0, 			/* normal state, not active, no cursor enter */
	Widget_State_Disabled,					/* disabled, no event response */
	Widget_State_OnCursor,				/* cursor enter into it */
	Widget_State_Down,			 			/* mouse is down on the widget */
	Widget_State_Activated,				/* widget is on focus */
	Widget_State_Debug, 					/* in debug mode */

	Widget_State_Count,
	
} WidgetState_et;

/* Widget event list */
typedef enum  {

	/*
	 * Mouse Events
	 */
	WidgetEvent_onMouseWheel = 0,
	WidgetEvent_onMouseDragStart,
	WidgetEvent_onMouseDragOver,
	WidgetEvent_onMouseDragDrop,
	WidgetEvent_onMouseMove,
	WidgetEvent_onMouseEnter,
	WidgetEvent_onMouseLeave,
	WidgetEvent_onMouseButtonUp,
	WidgetEvent_onMouseButtonDown,
	WidgetEvent_onMouseClicked,
	WidgetEvent_onMouseDoubleClicked,
	
	/*
	 * Key Events
	 */
	WidgetEvent_onKeyUp,
	WidgetEvent_onKeyDown,
	WidgetEvent_onKeyPress,
	
	/*
	 * Active Events
	 */
	WidgetEvent_onActivated,
	WidgetEvent_onDeactivated,
	
	/*
	 * Input capture Events
	 */
	WidgetEvent_onCaptureLost,
	WidgetEvent_onCaptureGained,
	
	/*
	 * Show&hide Events
	 */
	WidgetEvent_onShown,
	WidgetEvent_onHidden,
	
	/*
	 * Timer
	 */
	WidgetEvent_onTimeOut,

	/*
	 * Timer
	 */
	WidgetEvent_onStartAction,
	WidgetEvent_onEndAction,

	/*
	 * Redraw event
	 */
	WidgetEvent_onDraw,
	
	/*
	 * Create/destroy event
	 */
	WidgetEvent_onCreated,
	WidgetEvent_onDestroyed,
	
	WidgetEventCount
	
} WidgetEventID;

/* widget key navigation enable flag */
enum 
{
	WidgetKeyNav_None = 0,
	WidgetKeyNav_Up = (1<<0),
	WidgetKeyNav_Down = (1<<1),
	WidgetKeyNav_Left = (1<<2),
	WidgetKeyNav_Right = (1<<3),

	WidgetKeyNav_All = 0xff
};

/* widget event argument */
typedef struct {
	unsigned int 				handled;
	unsigned int					para;
	CWidget_t*					widget;	
	CWidget_t*					otherWidget;	
} WidgetEventArgs_t;

/* mouse event argument */
typedef struct {
	WidgetEventArgs_t		we;

	ezPoint 							position; 	//!< holds current mouse position.
	ezVector2 						moveDelta;		//!< holds variation of mouse position from last mouse input
	ezMouseButton 			button; 		//!< one of the MouseButton enumerated values describing the mouse button causing the event (for button inputs only)
	ezSystemKey					sysKeys;		//!< current state of the system keys and mouse buttons.
	ezMouseDragDir			dragDir;		//! < mouse drag direction
	int								dragTime; //! ms
	int								wheelChange;	//!< Holds the amount the scroll wheel has changed.
	unsigned int					clickCount; 		//!< Holds number of mouse button down events currently counted in a multi-click sequence (for button inputs only).
	
} MouseEventArgs_t;

/* keyboard event argument */
typedef struct {
	WidgetEventArgs_t		we;

	unsigned int			codepoint;		//!< user code
	UIKeyScan			scancode;		//!< hardware scan code
	ezSystemKey					sysKeys;		//!< current state of the system keys and mouse buttons.

} KeyEventArgs_t;

#define MAX_TIMER_NAME_STR  16

/* timer event argument */
typedef struct {
	WidgetEventArgs_t		we;
	char								name[MAX_TIMER_NAME_STR];
	unsigned int				timeElapsed;

} TimerEventArgs_t;

typedef struct s_ezTimer ezTimer_t;

struct s_ezTimer
{
	char          			name[MAX_TIMER_NAME_STR];	/* timer name */
	unsigned int 		outTime;										/* the limit time to send time message */
	unsigned int			curTime;										/* Current time */	
	unsigned int			loop;												/* timer restart after time out */
	unsigned int			para;												/* timer parameter */
	ezTimer_t* 			next;												/* which Wnd should get this time message */
	
};

/* TODO: METHOD FUNCTION TYPE */
typedef void (*WidgetEventEntry_t)(WidgetEventArgs_t*);
typedef void (*WidgetdrawSelf_t)(CWidget_t*, unsigned long);
typedef void (*WidgetupdateSelf_t)(CWidget_t*, unsigned int);
typedef void (*Widgetactivated_t)(CWidget_t*);
typedef void (*WidgetsetModalState_t)(CWidget_t*, int);
typedef int (*WidgetgetModalState_t)(CWidget_t * );
typedef int (*Widgetconstructor_t)(CWidget_t*, ResWnd_t*);
typedef int (*Widgetdestructor_t)(CWidget_t*);
typedef int (*WidgetsetIntValue_t)(CWidget_t *, int);
typedef int (*WidgetsetStrValue_t)(CWidget_t *, char*);
typedef int (*WidgetsetValue_t)(CWidget_t *, void*);
typedef int (*WidgetbindRecord_t)(CWidget_t * , const int , bindField_t *);
typedef int (*WidgetsetRecord_t)(CWidget_t *, void*);
typedef void (*WidgetsetVisible_t)(CWidget_t *, int);
typedef int (*WidgetcreateTimer_t)(CWidget_t *, const char*, unsigned int, unsigned int, unsigned int);
typedef int (*WidgetdestroyTimer_t)(CWidget_t *, const char *);
typedef int (*WidgetresetTimer_t)(CWidget_t *, const char *);
typedef int (*WidgetcleanupTimer_t)(CWidget_t *);
typedef void (*Widgetenable_t)(CWidget_t*, int);
typedef int (*WidgetstartAction_t)(CWidget_t*, ezActionPara_t*);
typedef int (*WidgetstopAction_t)(CWidget_t*);
typedef int (*WidgetendAction_t)(CWidget_t*);
typedef void (*Widgettransform_t)(CWidget_t*, int);
typedef int (*WidgetsetLayer_t)(CWidget_t *, int);
/* TODO END */

/* event handle registry */
typedef struct {
	WidgetEventEntry_t eventHandle;
	unsigned int 			 eventID;
} eventRegistry_t;

struct s_CWidget
{
	ezWidgetID_t						widgetID;				/* widget unique id */
	ezClassID_t							classID;					/* widget class id */
	void*									msgProc; 				/* widget message process rountine */
	CWidget_t*							parent;					/* widger parent */
	CWidget_t*							root;						/* root application */
	ResWnd_t*							wndRes;
	
	CWidget_t**						children;
	unsigned int							childCount;
	unsigned int 						childMax;
	
	CWidget_t**						drawList;
	unsigned int							drawCount;
	unsigned int 						drawMax;
	
	eventRegistry_t*					eventRegistry;
	unsigned int							eventCount;
	unsigned int 						eventMax;

	WidgetState_et					state;

	ezTimer_t*							timer;
	ezAction_t*							action;
	
	ezImage_t*							bgImage;
	ezImage_t*							downImage;
	ezImage_t*							onCursorImage;
	ezImage_t*							activeImage;
	ezImage_t*							disableImage;

	unsigned int							fieldNum;
	bindField_t *						fieldList;
	
	gdi_rect_t							area;						/* control display rect, relative dim */
	gdi_rect_t							absArea;				/* control display rect, absolute dim */
	gdi_rect_t							originArea;						/* original area before do action */
	gdi_rect_t							mask;						/* window mask region */
	Trape4									trape;
	float										alpha;
	unsigned int							layer;						/* gdi layer handle, if it's not zero, this widget have a seperate layer */
	unsigned char						enableMask;				/* enable window layer mask rect */
	unsigned char						active;					/* control is focused or not */
	unsigned char						visible;					/* don't show control when visable is false */
	unsigned char 					enabled;				/* control is actived and response message */
	unsigned char 					redraw;					/* widget need draw again */
	unsigned char 					alwaysOnTop;
	unsigned char						keyNavFocus;		/* up,down,left,right key to navigate focus */
	unsigned char						keyNavLoop;			/* loop navigate when you press key on a same direction */
	unsigned char						enableEnterLeave; /* enable mouse enter&leave event */
	unsigned char						resPreLoad;			/* 1- load resource in constructor, 0 - load resource when redraw */
	unsigned char						mousePassThough;		/* skip mouse hit */
	char										name[29];

	/* TODO END */
	
	/* TODO: METHODS  */
	WidgetdrawSelf_t				drawSelf;
	Widgetactivated_t				activate;
	WidgetupdateSelf_t				updateSelf;
	Widgettransform_t				transform;
	Widgetactivated_t				deactivate;
	WidgetsetModalState_t		setModalState;
	WidgetgetModalState_t		getModalState;
	Widgetconstructor_t			constructor;
	Widgetdestructor_t			destructor;
	WidgetsetIntValue_t			setIntValue;
	WidgetsetStrValue_t			setStrValue;
	WidgetsetValue_t				setValue;
	WidgetbindRecord_t			bindRecord;
	WidgetsetRecord_t				setRecord;
	WidgetsetVisible_t				setVisible;
	Widgetenable_t					enable;
	Widgetenable_t					disable;
	WidgetcreateTimer_t			createTimer;
	WidgetdestroyTimer_t		destroyTimer;
	WidgetresetTimer_t			resetTimer;
	WidgetcleanupTimer_t		cleanupTimer;
	WidgetstartAction_t				startAction;
	WidgetstopAction_t				stopAction;
	WidgetendAction_t				endAction;
	WidgetsetLayer_t				setLayer;
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t 			onMouseWheel;
	WidgetEventEntry_t 			onMouseDragStart;
	WidgetEventEntry_t 			onMouseDragOver;
	WidgetEventEntry_t			onMouseDragDrop;
	WidgetEventEntry_t 			onMouseMove;
	WidgetEventEntry_t 			onMouseEnter;
	WidgetEventEntry_t 			onMouseLeave;
	WidgetEventEntry_t			onMouseButtonUp;
	WidgetEventEntry_t 			onMouseButtonDown;
	WidgetEventEntry_t 			onMouseClicked;
	WidgetEventEntry_t 			onMouseDoubleClicked;
	WidgetEventEntry_t 			onKeyUp;
	WidgetEventEntry_t 			onKeyDown;
	WidgetEventEntry_t 			onKeyPress;
	WidgetEventEntry_t 			onActivated;
	WidgetEventEntry_t 			onDeactivated;
	WidgetEventEntry_t			onCaptureLost;
	WidgetEventEntry_t			onCaptureGained;
	WidgetEventEntry_t			onCreated;
	WidgetEventEntry_t			onDestroyed;
	WidgetEventEntry_t			onDraw;
	WidgetEventEntry_t			onShown;
	WidgetEventEntry_t			onHidden;
	WidgetEventEntry_t			onTimeOut;
	WidgetEventEntry_t			onStartAction;
	WidgetEventEntry_t			onEndAction;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: CWidget_drawSelf
 * Arguments      	: widget - control handle
 *								para -  input parameter
 * Return         	: none
 * Description    	: paint the widget
 *					
*/
extern void CWidget_drawSelf(CWidget_t *widget, unsigned long para);

/*
 * Function name  	: CWidget_updateSelf
 * Arguments      	: widget - control handle
 *								timeElapsed -  time elapsed, ms
 * Return         	: none
 * Description    	: update widget
 *					
*/
extern void CWidget_updateSelf(CWidget_t *widget, unsigned int timeElapsed);

/*
 * Function name  	: CWidget_activate
 * Arguments      	: widget - control handle
 * Return         	: none
 * Description    	: widget get focus
 *					
*/
extern void CWidget_activate(CWidget_t *widget);

/*
 * Function name  	: CWidget_deactivate
 * Arguments      	: widget - control handle
 * Return         	:  none
 * Description    	: widget lose focus
 *					
*/
extern void CWidget_deactivate(CWidget_t *widget);

/*
 * Function name  	: CWidget_onActivated
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event on widget is activated
 *					
*/
extern void CWidget_onActivated(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onDeactivated
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event on widget is deactivated
 *					
*/
extern void CWidget_onDeactivated(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onCaptureLost
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event on widget lost input capture
 *					
*/
extern void CWidget_onCaptureLost(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onCaptureGained
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event on widget gain input capture
 *					
*/
extern void CWidget_onCaptureGained(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onDraw
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event after widget is redrawed
 *					
*/
extern void CWidget_onDraw(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onShown
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event after widget changed from hide to show
 *					
*/
extern void CWidget_onShown(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onHidden
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: event after widget changed from show to hide
 *					
*/
extern void CWidget_onHidden(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseMove
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: move cursor from one widget to another
 *					
*/
extern void CWidget_onMouseMove(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseEnter
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: cursor enter into one widget
 *					
*/
extern void CWidget_onMouseEnter(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseLeave
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: cursor leave from one widget
 *					
*/
extern void CWidget_onMouseLeave(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseDragOver
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: drag cursor on a widget
 *					
*/
extern void CWidget_onMouseDragOver(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseDragDrop
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: drop cursor on a widget
 *					
*/
extern void CWidget_onMouseDragDrop(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseButtonUp
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: mouse button up on a widget
 *					
*/
extern void CWidget_onMouseButtonUp(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseButtonDown
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: mouse button up down a widget
 *					
*/
extern void CWidget_onMouseButtonDown(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseClicked
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: mouse button clicked on a widget
 *					
*/
extern void CWidget_onMouseClicked(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseDoubleClicked
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: mouse button double clicked on a widget
 *					
*/
extern void CWidget_onMouseDoubleClicked(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onMouseWheel
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: mouse wheel scroll on a widget
 *					
*/
extern void CWidget_onMouseWheel(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onKeyUp
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: key up on a widget
 *					
*/
extern void CWidget_onKeyUp(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onKeyDown
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: key down on a widget
 *					
*/
extern void CWidget_onKeyDown(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onKeyPress
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: key press on a widget
 *					
*/
extern void CWidget_onKeyPress(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_setIntValue
 * Arguments      	: widget - input widget
 *								: intValue - input int value
 * Return         	: 1 - true, 0 - false
 * Description    	: set widget bunding integer value
 *					
*/
extern int CWidget_setIntValue(CWidget_t* widget, int intValue);

/*
 * Function name  	: CWidget_setStrValue
 * Arguments      	: widget - input widget
 *								: strValue - input string value
 * Return         	: 1 - true, 0 - false
 * Description    	: set widget bunding string value
 *					
*/
extern int CWidget_setStrValue(CWidget_t* widget, char* strValue);

/*
 * Function name  	: CWidget_setValue
 * Arguments      	: widget - input widget
 *								: layer - input gdi layer id
 * Return         	: 1 - true, 0 - false
 * Description    	: set widget display layer
 *					
*/
extern int CWidget_setLayer(CWidget_t* widget, int layer);

/*
 * Function name  	: CWidget_bindRecord
 * Arguments      	: widget - widget handle
 *								: fieldNum - bunding record field number
 *								: pFieldList - field info list
 * Return         		: none
 * Description    		: set widget bunding record data structure
 *					
*/
extern int CWidget_bindRecord(CWidget_t* widget, const int fieldNum, bindField_t *pFieldList);

/*
 * Function name  	: CWidget_setRecord
 * Arguments      	: widget - widget handle
 *								: pRecord - record data address
 * Return         		: none
 * Description    		: set widget bunding record data structure
 *					
*/
extern int CWidget_setRecord(CWidget_t* widget, void* pRecord);

/*
 * Function name  	: CWidget_setVisible
 * Arguments      	: widget - input widget
 *								: setting - visible setting
 * Return         	: none
 * Description    	: set widget visible attribute
 *					
*/
extern void CWidget_setVisible(CWidget_t* widget, int setting);

/*
 * Function name  	: CWidget_transform
 * Arguments      	: widget - input widget
 *									isChild - set children or not
 * Return         	: true or false
 * Description    	: transform widget trape
 *					
*/
extern void CWidget_transform(CWidget_t* widget, int isChild);

/*
 * Function name  	: CWidget_Constructor
 * Arguments      	: wndRes - window resource data address
 * Return         	: 0-succ, <>0-error code
 * Description    	: Construct widget by resource
 *					
*/
extern int CWidget_constructor(CWidget_t* widget, ResWnd_t* wndRes);

/*
 * Function name  	: CWidget_Destructor
 * Arguments      	: widget - input widget
 * Return         	: 0-succ, <>0-error code
 * Description    	: free widget resource
 *					
*/
extern int CWidget_destructor(CWidget_t* widget);

/*
 * Function name  	: CWidget_onCreated
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: callback after created widget
 *					
*/
extern void CWidget_onCreated(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_onDestroyed
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: callback after destroyed widget
 *					
*/
extern void CWidget_onDestroyed(WidgetEventArgs_t* args);

/*
 * Function name  	: CWidget_init
 * Arguments      	: widget - control handle
 *					  wparam - input parameter
 *					lparam -  input parameter
 * Return         	: 0-succ, <>0-error code
 * Description    	: Create widget
 *					
*/
extern int CWidget_init(CWidget_t *widget, unsigned long wparam, unsigned long lparam);

/*
 * Function name  	: CWidget_deInit
 * Arguments      	: widget - control handle
 *					  wparam - input parameter
 *					lparam -  input parameter
 * Return         	: 0-succ, <>0-error code
 * Description    	: destroy widget
 *					
*/
extern int CWidget_deInit(CWidget_t *widget, unsigned long wparam, unsigned long lparam);


#ifdef __cplusplus
}
#endif 

#endif

