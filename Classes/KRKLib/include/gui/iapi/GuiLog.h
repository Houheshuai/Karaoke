/*
** make a GUI application easy and clear							
**
** Filename : GuiLog.h
**																	
** Description: form log management
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
*/

#ifndef _GUI_LOG_H_
#define _GUI_LOG_H_

#include <gui/widgets/CApplication.h>

typedef struct s_FormLog
{
	void*					log;
	int						logsz;
	int						formId;
	
} formLogEntry_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_getFormLogSize
 * Arguments      		: app - application handle, formId - form widgetID
 * Return         			: log data size in bytes
 * Description    		: find form log data size in log pool
 *					
*/
extern int ez_getFormLogSize(CApplication_t* app, ezWidgetID_t formId);

/*
 * Function name  	: ez_getFormLog
 * Arguments      		: app - application handle, formId - form widgetID
 * Return         			: log data address
 * Description    		: find form log data in log pool
 *					
*/
extern void* ez_getFormLog(CApplication_t* app, ezWidgetID_t formId);

/*
 * Function name  	: ez_addFormLog
 * Arguments      		: app - application handle
 *										formId - form widgetID
 *									: log - log data address
 *									: logsz - log data size in bytes
 * Return         			: 0 - succ, <>0 err code 
 * Description    		: set form log data
 *					
*/
extern int ez_addFormLog(CApplication_t* app, ezWidgetID_t formId, void* log, int logsz);

/*
 * Function name  	: ez_removeFormLog
 * Arguments      		: app - application handle, formId - form widget ID
 * Return         			: 0 - succ, form log not found
 * Description    		: remove form log data in log pool
 *					
*/
extern int ez_removeFormLog(CApplication_t* app, ezWidgetID_t formId);

/*
 * Function name  	: ez_cleanupFormLog
 * Arguments      		: app - application handle
 * Return         			: none
 * Description    		: cleanup all form log data in pool
 *					
*/
extern void ez_cleanupFormLog(CApplication_t* app);

/*
 * Function name  	: ez_initFormLogList
 * Arguments      		: app - input application handle
 *								: count - form log count
 * Return         			: 0 - succ, <>0 - fail
 * Description    		: inilialize form log list buffer
 *					
*/
extern int ez_initFormLogList(CApplication_t* app, int count);

/*
 * Function name  	: ez_freeFormLogList
 * Arguments      		: app - input application handle
 *								: count - form log count
 * Return         			: none
 * Description    		: free form log list buffer
 *					
*/
extern void ez_freeFormLogList(CApplication_t* app);

#ifdef __cplusplus
}
#endif

#endif

