#ifndef _GUIBASE_H_
#define _GUIBASE_H_

#include <k_global.h>
#include <gui/GuiGlobal.h>
#include <gui/iapi/GuiRes.h>
#include <gui/iapi/GuiImage.h>
#include <gui/iapi/GuiString.h>
#include <gui/iapi/GuiIAL.h>
#include <gui/iapi/GuiAction.h>
#include <gui/widgets/CWidget.h>
#include <gui/iapi/GuiMsg.h>
#include <gui/widgets/CApplication.h>

#define ez_free(p)								gui_free(p)
#define ez_malloc(sz)								gui_malloc(sz)

#define ezRegWidgetExt(form, ClassName, ChildName, par)		do { \
																											if (par == NULL) \
																											{ \
																												gui_printf("========================================================================\n"); \
																												gui_printf("= WARNNING ... ezRegWidgetExt, parent not exist \n"); \
																												gui_printf("========================================================================\n"); \
																											} \
																											else \
																											{ \
																												form->ChildName = (ClassName##_t*)ez_getChild(ChildName##_ID,(CWidget_t*)(par)); \
																												if (form->ChildName == NULL) { \
																													gui_printf("========================================================================\n"); \
																													gui_printf("= WARNNING ... Widget: %s, children ID = %d, Not find in ResFile \n", Widget(par)->name, ChildName##_ID); \
																													gui_printf("========================================================================\n"); \
																												} \
																												else if (Widget(form->ChildName)->classID != ClassName##_ClassID) { \
																													gui_printf("========================================================================\n"); \
																													gui_printf("= WARNNING ... Widget: %s, ResFile classID = %d, Program classID = %d\n", Widget(form->ChildName)->name, Widget(form->ChildName)->classID, ClassName##_ClassID); \
																													gui_printf("========================================================================\n"); \
																												} \
																											} \
																									} while (0)

#define ezRegWidget(form, ClassName, ChildName)		ezRegWidgetExt(form, ClassName, ChildName, form)

#define ezRegMethod(widget, Type, Name)						widget->Name = Type##_##Name

typedef enum {
	
	widgetFocusMove_left,
	widgetFocusMove_right,
	widgetFocusMove_up,
	widgetFocusMove_down,
	
} widgetFocusMoveDir_et;

struct s_GuiInstances
{
	const char*			AppName;											/* application resource file full path */
	void*					formClassRegistry;							/* class registry of forms&widgets in this application */
	int 						formClassRegistryCount;				/* class total count */
	ezWidgetID_t		startupFormID;									/* startup form when application loading */
	int						singleTask;											/* 1: create a single task for GUI application, 0: not create */
	int						fakeRender;										/* 1: call signalRedraw to redraw window in render, 1: window will automatically redraw in render */
	int						loadAllRes;										/* 1: load all resources to memory when applicatioin run, more memory but faster render performance, 0: load when window created */
	const char*			cursorImage;										/* cursor image file full path */
	int						reserved[4];										/* define it for any function you want */	
};

typedef struct s_GuiInstances ezAppInstance_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_absDim
 * Arguments      	: obj - control handle
 *				  				: x - output absolute x coordinate
 *				  				: y - output absolute y coordinate
 * Return         		: none
 * Description    		: convert relative coordinate to absolute
 *					
*/
extern void ez_absDim(CWidget_t *obj, short *x, short *y);

/*
 * Function name  	: ez_absDimLayer
 * Arguments      	: obj - control handle
 *				  				: x - output absolute x coordinate
 *				  				: y - output absolute y coordinate
 * Return         		: none
 * Description    		: convert relative coordinate to absolute in one graphic layer
 *					
*/
extern void ez_absDimLayer(CWidget_t *obj, short *x, short *y);

/*
 * Function name  	: ez_area2trape
 * Arguments      	: area - input area
 *				  				: trape - output trape
 * Return         		: none
 * Description    		: convert area to trape
 *					
*/
extern void ez_area2trape(gdi_rect_t* area, Trape4* trape);

/*
 * Function name  	: ez_getEffectAlpha
 * Arguments      	: widget - widget handle
 * Return         		: effect alpha value when widget to do drawself
 * Description    		: get the drawable effective alpha of a widget
 *					
*/
extern float ez_getEffectAlpha(CWidget_t *widget);

/*
 * Function name  	: ez_isHit
 * Arguments      	: widget - widget handle
 *								: pos - mouse position
 * Return         		: hit control handle
 * Description    		: search all widgets in parent to find a control in mouse hit rect
 *					
*/
extern int ez_isHit(CWidget_t *widget, ezPoint pos);

/*
 * Function name  	: ez_getHitWidget
 * Arguments      	: widget - input widget
 *								: pos - mouse position
 * Return         		: hit control handle
 * Description    		: search all widgets in application to find a control in mouse hit rect
 *					
*/
extern CWidget_t *ez_getHitWidget(CWidget_t* widget, ezPoint pos);

/*
 * Function name  	: ez_queryEventHandler
 * Arguments      	: widget - widget pointer
 *								: ID - event ID
 * Return         		: none
 * Description    		: query event handler in widget subscribed event registry
 *					
*/
extern WidgetEventEntry_t ez_queryEventHandler(CWidget_t* widget, unsigned int ID);

/*
 * Function name  	: ez_fireEvent
 * Arguments      	: widget - widget pointer
 *								: event - event handle
 *								: ID - event ID
 * Return         		: none
 * Description    		: fire event
 *					
*/
extern void ez_fireEvent(unsigned int ID, WidgetEventArgs_t* args);

/*
 * Function name  	: ez_subscribeEvent
 * Arguments      	: widget - widget pointer
 *								: event - event handle
 *								: ID - event ID
 * Return         		: none
 * Description    		: subscribe event
 *					
*/
extern void ez_subscribeEvent(CWidget_t * widget, WidgetEventEntry_t event, unsigned int ID);


/*
 * Function name  	: ez_moveToBack
 * Arguments      	: widget - widget pointer
 * Return         		: none
 * Description    		: move the widget to the bottom of the render list
 *					
*/
extern void ez_moveToBack(CWidget_t * widget);

/*
 * Function name  	: ez_moveToFront
 * Arguments      	: widget - widget pointer
 * Return         		: 1 - true, 0 - false
 * Description    		: move the widget to the top of the render list
 *					
*/
extern int ez_moveToFront(CWidget_t * widget);

/*
 * Function name  	: ez_setAlwaysOnTop
 * Arguments      	: widget - widget pointer
 * Return         		: none
 * Description    		: pop the widget to the top of the chain
 *					
*/
extern void ez_setAlwaysOnTop(CWidget_t * widget);

/*
 * Function name  	: ez_getClassSize
 * Arguments      	: app - application handle
 *									classId - class ID
 * Return         		: size of class in bytes
 * Description    		: get class size
 *					
*/
extern int ez_getClassSize(CApplication_t* app, ezClassID_t classId);

/*
 * Function name  	: ez_getModalTarget
 * Arguments      		: app - application handle
 * Return         			: modal widget
 * Description    		: get modal widget in application
 *					
*/
extern CWidget_t* ez_getModalTarget(CApplication_t* app);

/*
 * Function name  	: ez_setModalTarget
 * Arguments      		: app- application handler, target - new modal target
 * Return         			: void
 * Description    		: set modal widget in application
 *					
*/
extern void ez_setModalTarget(CApplication_t* app, CWidget_t* target);

/*
 * Function name  	: ez_getCaptureTarget
 * Arguments      		: app - application handle
 * Return         			: modal widget
 * Description    		: get capture input widget in application
 *					
*/
extern CWidget_t* ez_getCaptureWidget(CApplication_t* app);

/*
 * Function name  	: ez_getActiveWidget
 * Arguments      	: parent - parent control handle
 * Return         		: focus control handle
 * Description    		: get active child widget in parent widget
 *					
*/
extern CWidget_t* ez_getActiveWidget(CWidget_t *parent);

/*
 * Function name  	: ez_getActiveSibling
 * Arguments      	: widget - parent widget handle
 * Return         		: focus control handle
 * Description    		: get active widget in parent widget
 *					
*/
extern CWidget_t* ez_getActiveSibling(CWidget_t *widget);

/*
 * Function name  	: ez_getActiveChild
 * Arguments      	: widget - parent widget handle
 * Return         		: focus control handle
 * Description    		: get active child widget in parent widget
 *					
*/
extern CWidget_t* ez_getActiveChild(CWidget_t *widget);

/*
 * Function name  	: ez_addChild
 * Arguments      	: id - childwidget id
 * 				      		: widget - widget pointer
 * Return         		: added child widget
 * Description    		: add a child widget to parent widget
 *					
*/
extern CWidget_t* ez_addChild(CWidget_t* parent, CWidget_t* child);

/*
 * Function name  	: ez_removeChild
 * Arguments      	: parent - parent widget 
 * 				      		: child - child widget
 * Return         		: next widget in list
 * Description    		: add a child widget to parent widget
 *					
*/
extern CWidget_t* ez_removeChild(CWidget_t* parent, CWidget_t* child);

/*
 * Function name  	: ez_isChild
 * Arguments      	: id - childwidget id
 * 				      		: widget - widget pointer
 * Return         		: 1 - true, 0 - false
 * Description    		: check if widget is the child 
 *					
*/
extern int ez_isChild(ezWidgetID_t Id, CWidget_t* widget);

/*
 * Function name  	: ez_isAncestor
 * Arguments      	: widget - source widget 
 * 				      		: target - target widget
 * Return         		: 1 - true, 0 - false
 * Description    		: check if target is the ancestor of source widget 
 *					
*/
extern int ez_isAncestor(CWidget_t* widget, CWidget_t* target);

/*
 * Function name  	: ez_getChildAtIdx
 * Arguments      	: index- index of child list array
 * 				      		: widget - widget pointer
 * Return         		: 1 - true, 0 - false
 * Description    		: get child widget in children list at index
 *					
*/
extern CWidget_t* ez_getChildAtIdx(ezWidgetID_t Index, CWidget_t* widget);

/*
 * Function name  	: ez_getChild
 * Arguments      	: id - childwidget id
 * 				      		: widget - widget pointer
 * Return         		: child widget 
 * Description    		: get child widget by child widget ID
 *					
*/
extern CWidget_t* ez_getChild(ezWidgetID_t Id, CWidget_t* widget);

/*
 * Function name  	: ez_getFormByWidget
 * Arguments      	: widget - widget pointer
 * Return         		: widget's form 
 * Description    		: get widget's form by widget pointer
 *					
*/
extern CWidget_t* ez_getFormByWidget(CWidget_t* widget);

/*
 * Function name  	: ez_moveFocus
 * Arguments      	: widget - widget handle
 *								: dir - move direction
 * Return         		: 1 - true, 0 - false
 * Description    		: search all child widget to find next active one
 *					
*/
extern int ez_moveFocus(CWidget_t* widget, widgetFocusMoveDir_et dir);

/*
 * Function name  	: ez_cleanupDeadPool
 * Arguments      		: app - application handle
 * Return         			: none
 * Description    		: cleanup all widgets in deadpool
 *					
*/
extern void ez_cleanupDeadPool(CApplication_t* app);

/*
 * Function name  	: ez_setLayerVisible
 * Arguments      	: widget - widget handle
 *									setting - 1: show, 0: hide
 * Return         		: none
 * Description    		: setup layer visible
 *					
*/
extern void ez_setLayerVisible(CWidget_t* widget, int setting);

/*
 * Function name  	: ez_setLayerRect
 * Arguments      	: widget - widget handle
 *									lyrrect - layer new rect
 *									mask - layer visiable mask rect
 * Return         		: 0 - succ, <>0 error code
 * Description    		: setup layer size and position
 *					
*/
extern int ez_setLayerRect(CWidget_t* widget, gdi_rect_t lyrrect, gdi_rect_t mask);

/*
 * Function name  	: ez_createLayer
 * Arguments      	: widget - widget handle
 *									para
 * Return         		: 0 - succ, <>0 error code
 * Description    		: create a seperate graphic layer for this widget
 *					
*/
extern int ez_createLayer(CWidget_t* widget, void * para);

/*
 * Function name  	: ez_destroyLayer
 * Arguments      	: widget - widget handle
 *				:scrno - screen number
 * Return         		: 0 - succ, <>0 error code
 * Description    		: destroy the graphic layer in this widget
 *					
*/
extern int ez_destroyLayer(CWidget_t* widget,int scrno);

/*
 * Function name  	: ez_clearWidget
 * Arguments      		: widget - widget address
 * Return         			: none
 * Description    		: clear widget display area
 *					
*/
extern void ez_clearWidget(CWidget_t* widget);

/*
 * Function name  	: ez_signalRedraw
 * Arguments      	: widget - widget handle
 *									isChildren - redraw children if this parameter is true
 * Return         		: none
 * Description    		: set redraw to false
 *					
*/
extern void ez_cancelRedraw(CWidget_t* widget, int isChildren);

/*
 * Function name  	: ez_signalRedraw
 * Arguments      	: widget - widget handle
 *									isChildren - redraw children if this parameter is true
 * Return         		: none
 * Description    		: set redraw
 *					
*/
extern void ez_signalRedraw(CWidget_t* widget, int isChildren);


/*
 * Function name  	: ez_signalBgRedraw
 * Arguments      	: widget - widget handle
 * Return         		: none
 * Description    		: set redraw
 *					
*/
extern void ez_signalBgRedraw(CWidget_t* widget);

/*
 * Function name  	: ez_setResPreLoad
 * Arguments      	: widget - widget handle
 *										value - true: preload on create, false-load on draw
 *										isChildren - set all child windows
 * Return         		: none
 * Description    		: set resPreLoad flag
 *					
*/
extern void ez_setResPreLoad(CWidget_t* widget, int value, int isChildren);

/*
 * Function name  	: ez_render
 * Arguments      	: widget - widget handle
 * Return         		: none
 * Description    		: render widget
 *					
*/
extern void ez_render(CWidget_t* widget);

/*
 * Function name  	: ez_renderGUI
 * Arguments      	: app - application handle
 * Return         		: none
 * Description    		: render GUI
 *					
*/
extern void ez_renderGUI(CApplication_t* app);

/*
 * Function name  	: ez_captureInput
 * Arguments      	: widget - widget handle
 * Return         		: 1 - true, 0 - false
 * Description    		: capture input event to this widget
 *					
*/
extern int ez_captureInput(CWidget_t* widget);

/*
 * Function name  	: ez_releaseInput
 * Arguments      	: widget - widget handle
 * Return         		: none
 * Description    		: release widget capture state
 *					
*/
extern void ez_releaseInput(CWidget_t* widget);

/*
 * Function name  	: ez_releaseInput
 * Arguments      	: app - application handle 
 *									filePath - cursor image file path
 * Return         		: none
 * Description    		: set GUI cursor image 
 *					
*/
extern void ez_setCursorImage(CApplication_t* app, const char* filePath);

/*
 * Function name  	: ez_getMouseTarget
 * Arguments      	: app - application handle
 *									pos - mouse position
 * Return         		: hit control handle
 * Description    		: search all widgets in application to find a control can capture mouse input
 *					
*/
extern CWidget_t *ez_getMouseTarget(CApplication_t* app, ezPoint pos);

/*
 * Function name  	: ez_getKeyboardTarget
 * Arguments      	: app - application handle
 * Return         		: hit control handle
 * Description    		: search all widgets in application to find a control can capture keyboard input
 *					
*/
extern CWidget_t *ez_getKeyboardTarget(CApplication_t*app);

/*
 * Function name  	: ez_updateMouseContainerWidget
 * Arguments      	: app - application handle
 * Return         		: none
 * Description    		: update the widget who contain mouse cursor
 *					
*/
extern void ez_updateMouseContainerWidget(CApplication_t* app);

/*
 * Function name  	: ez_mouseButtonToUIKey
 * Arguments      	: app - application handle
 *									btn - input mouse button id
 *									uiKey - input UI Key value
 * Return         		: mapped UI Key value
 * Description    		: map a mouse button to UI key, if this mouse button is clicked, UI Key will be trigger
 *					
*/
extern UIKeyScan ez_mouseButtonToUIKey(CApplication_t* app, ezMouseButton btn, UIKeyScan uiKey);

/*
 * Function name  	: ez_setupMouseInject
 * Arguments      	: app - application handle 
 *									enabled - true, enable mouse inject, false - disable mouse inject
 * Return         		: none
 * Description    		: setup mouse inject
 *					
*/
extern void ez_setupMouseInject(CApplication_t* app, unsigned int enabled);

/*
 * Function name  	: ez_setupKeyInject
 * Arguments      	: app - application handle 
 *									enabled - true, enable key inject, false - disable key inject
 * Return         		: none
 * Description    		: setup key inject
 *					
*/
extern void ez_setupKeyInject(CApplication_t* app, unsigned int enabled);

/*
 * Function name  	: ez_setMousePassThough
 * Arguments      	: widget - widget handle
 *									enabled - true, enable mouse pass through, false - disable mouse pass though
 * Return         		: none
 * Description    		: setup mouse pass though
 *					
*/
extern void ez_setMousePassThough(CWidget_t* widget, unsigned char enabled);

/*
 * Function name  	: ez_injectMouseMove
 * Arguments      	: app - application handle x, y - mouse position
 * Return         		: none
 * Description    		: inject mouse move data to gui system
 *					
*/
extern void ez_injectMouseMove(CApplication_t* app, int x, int y);

/*
 * Function name  	: ez_injectMouseEvent
 * Arguments      	: app - application handle
 *									event - mouse event
 * Return         		: none
 * Description    		: inject mouse event to gui system
 *					
*/
extern void ez_injectMouseEvent(CApplication_t* app, MouseEvents_et event);

/*
 * Function name  	: ez_injectMouseButtonUp
 * Arguments      	: app - application handle
 *									keycode - input key code
 * Return         		: none
 * Description    		: inject mouse button up data to gui system
 *					
*/
extern void ez_injectKeyPress(CApplication_t* app, unsigned int keycode);

/*
 * Function name  	: ez_injectTimePulse
 * Arguments      	: app - application handle, timeElapsed - input time pulse, ms
 * Return         		: none
 * Description    		: inject time pulse to system
 *					
*/
extern void ez_injectTimePulse(CApplication_t* app, unsigned int timeElapsed);

/*
 * Function name  	: ez_appTaskProc
 * Arguments      	: app - application handle
 * Return         		: none
 * Description    		: application task procedure
 *					
*/
extern void ez_appTaskProc(CApplication_t* app);

/*
 * Function name  	: ez_setStandbyTimeOut
 * Arguments      	: app - application handle, timeElapsed - input time pulse, ms
 * Return         		: none
 * Description    		: set time out of standby mode
 *					
*/
extern void ez_setStandbyTimeOut(CApplication_t* app, int time);


#ifdef __cplusplus
}
#endif

#endif

