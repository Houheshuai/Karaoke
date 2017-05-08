/*
** make a GUI application easy and clear							
**
** Filename : GuiApp.h
**																	
** Description: application and widget manager API
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
*/

#ifndef _GUI_APP_H_
#define _GUI_APP_H_

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: ez_getAppRes
 * Arguments      		: app - application handle
 * Return         			: application resource pointer
 * Description    		: get current application resource pointer
 *					
*/
extern ezResource_t* ez_getAppRes(CApplication_t* app);

/*
 * Function name  	: ez_setAppRes
 * Arguments      		: app -application handle
 * Return         			: application resource pointer
 * Description    		: set current application resource pointer
 *					
*/
extern void ez_setAppRes(CApplication_t* app, ezResource_t* res);

/*
 * Function name  	: ez_getAppPath
 * Arguments      		: app - application handle; path - output path, maxlen - path max length
 * Return         			: 0 -succ, <>0 - fail
 * Description    		: get application location full path
 *					
*/
extern int ez_getAppPath(CApplication_t* app, char* path, int maxlen);

/*
 * Function name  	: ez_getForm
 * Arguments      		: app - application handle, formID - form ID
 * Return         			: form pointer address
 * Description    		: get current form pointer address
 *					
*/
extern CWidget_t * ez_getForm(CApplication_t* app, int formID);

/*
 * Function name  	: ez_getApp
 * Arguments      		: none
 * Return         			: application pointer
 * Description    		: get application pointer from widget pointer
 *					
*/
extern CApplication_t * ez_getApp(CWidget_t* widget);

/*
 * Function name  	: ez_CreateWidget
 * Arguments      		: wndRes - resource address, if not create by resource, it's NULL
 *									: classId - widget class id
 *									: parent - parent widget
 * Return         			: widget handle
 * Description    		: create a widget
 *					
*/
extern CWidget_t* ez_createWidget(ResWnd_t* wndRes, ezClassID_t classId, CWidget_t* parent);

/*
 * Function name  	: ez_DestroyWidget
 * Arguments      		: widget - widget pointer
 *									: parent - parent widget
 * Return         			: none
 * Description    		: destroy a widget
 *					
*/
extern void ez_destroyWidget(CWidget_t* widget, CWidget_t* parent);

/*
 * Function name  	: ez_createForm
 * Arguments      		: app - application handle
 *										formId - form widget ID
 * Return         			: form handle
 * Description    		: create form
 *					
*/
extern CWidget_t* ez_createForm(CApplication_t* app, ezWidgetID_t formId);

/*
 * Function name  	: ez_destroyForm
 * Arguments      		: form - form widget 
 * Return         			: 0: succ, <>0: fail
 * Description    		: create form
 *					
*/
extern int ez_destroyForm(CWidget_t* form);

/*
 * Function name  	: ez_destroyForms
 * Arguments      		: app - application handle, list_id - exclude widget id array, id_cnt - count of exclude widget id
 * Return         			: 0: succ, <>0: fail
 * Description    		: destroy forms
 *					
*/
extern int ez_destroyForms(CApplication_t* app, ezWidgetID_t* list_id, int id_cnt);

/*
 * Function name  	: ez_cacheWidgetResource
 * Arguments      	: app - application handle 
 *									formId - form id 
 * Return         		: none
 * Description    		: cache widget resource data in memory, to fast load in future
 *					
*/
extern void ez_cacheFormResource(CApplication_t* app, int formId);

/*
 * Function name  	: ez_cleanupWidgetResource
 * Arguments      	: widget - widget handle
 * Return         		: none
 * Description    		: clean up all resources in widget
 *					
*/
extern void ez_cleanupWidgetResource(CWidget_t * widget);

/*
 * Function name  	: ez_loadWidgetResource
 * Arguments      	: widget - widget handle
 * Return         		: none
 * Description    		: load all resources in widget
 *					
*/
extern void ez_loadWidgetResource(CWidget_t * widget);

/*
 * Function name  	: ez_cleanupAllFormResourceCache
 * Arguments      	: app - application handle 
 * Return         		: none
 * Description    		: cleanup form resouce cache flag
 *					
*/
extern void ez_cleanupAllFormResourceCache(CApplication_t* app);

/*
 * Function name  	: ez_cleanupFormResource
 * Arguments      	: app - application handle 
 *									formId - form id 
 * Return         		: none
 * Description    		: clean up all resources in form
 *					
*/
extern void ez_cleanupFormResource(CApplication_t* app, int formId);

/*
 * Function name  	: ez_loadFormResource
 * Arguments      	: app - application handle 
 *									formId - form id 
 * Return         		: none
 * Description    		: load all resources in form
 *					
*/
extern void ez_loadFormResource(CApplication_t* app, int formId);

/*
 * Function name  	: ez_createApp
 * Arguments      		: ins - app instance
 * Return         			: application handle
 * Description    		: create app
 *					
*/
extern CApplication_t * ez_createApp(const ezAppInstance_t *ins);

/*
 * Function name  	: ez_destroyApp
 * Arguments      		: app - app handle
 * Return         			: application handle
 * Description    		: destroy app
 *					
*/
extern int ez_destroyApp(CApplication_t* app);

/*
 * Function name  	: ez_runApp
 * Arguments      	: ins - Application instance
 *					SysCallKill - system call to kill karaoke app
 * Return         	: application object pointer
 * Description    	: start to run a gui application by instance
 *					
*/
extern CApplication_t * ez_runApp(const ezAppInstance_t *ins);
	
/*
 * Function name  	: ez_stopApp
 * Arguments      	: app - Application object pointer
 * Return         	: none
 * Description    	: stop a gui application
 *					
*/
extern int ez_stopApp(CApplication_t * app);

#ifdef __cplusplus
}
#endif 

#endif

