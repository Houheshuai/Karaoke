#ifndef _GUI_GLOBAL_H_
#define _GUI_GLOBAL_H_

#define GUI_RECT_ABS(ParRect, ThisRect)		do {\
												(ThisRect)->X += (ParRect)->X;\
												(ThisRect)->Y += (ParRect)->Y;\
											} while (0)

#define GUI_APP_TASK_STACK_SIZE		(32*1024)
#define GUI_OS_APP_PRORITY					KRK_TASK_PRIORITY_MID
#define GUI_APP_TASK_NAME					"UITASK"
#define GUI_OS_QUEUE_CNT						16	//8

#define gui_malloc(a)		 	calloc(1, a)
#define gui_realloc(a,b)		realloc(a, b)
#define gui_free(a)				{free(a); a=NULL;}

/* file system */

#ifdef _KRK_DEBUG_
#define _UI_DEBUG_
#endif

typedef unsigned int ezWidgetID_t;
typedef unsigned int ezClassID_t;
typedef unsigned int ezResID_t;

#include "GuiEnums.h"
#include "GuiStructs.h"

#define gui_assert(a)				KRK_ASSERT(a)

#ifdef _GUI_APP_
#define EZGUI_APPDEF(a, b) a = b
#else
#define EZGUI_APPDEF(a, b) extern a
#endif

#ifdef _GUI_GLB_
#define EZGUI_GLBDEF(a, b) a = b
#else
#define EZGUI_GLBDEF(a, b) extern a
#endif

#endif

