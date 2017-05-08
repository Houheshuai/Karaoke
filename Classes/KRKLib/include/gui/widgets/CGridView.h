#ifndef _CGRIDVIEW_H_
#define _CGRIDVIEW_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
/* TODO END */

#define CGridView_ClassID					10

/* TODO: REGISTER WIDGETS */
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CGridView_RegMethods(gridview) {\
	ezRegMethod(Widget(gridview), CGridView, constructor);\
	ezRegMethod(Widget(gridview), CGridView, destructor);\
	ezRegMethod(Widget(gridview), CGridView, setStrValue);\
	ezRegMethod(Widget(gridview), CGridView, onCreated);\
	ezRegMethod(gridview, CGridView, getFocusView);\
	ezRegMethod(gridview, CGridView, onClicked);\
	ezRegMethod(gridview, CGridView, onFocusChanged);\
}
/* TODO END */

typedef struct s_CGridView CGridView_t;

/* TODO: BUTTON RESOURCE */
enum {
	GridViewRes_zoomRate_ID = 0,
	GridViewRes_movingFocus_ID = 1,
	
	GridViewRes_Count,
};
/* TODO END */

/* TODO: BUTTON EVENT ID */
enum GridViewEventID {
	GridViewEvent_onClicked = ((CGridView_ClassID<<8) + 1),
	GridViewEvent_onFocusChanged = ((CGridView_ClassID<<8) + 2),

	GridViewEventCount
};
/* TODO END */

/* TODO: BUTTON EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

} GridViewEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef CWidget_t* (*GridViewGetFocusView_t)(CGridView_t*);
/* TODO END */

struct s_CGridView
{

	CWidget_t 								Widget;

	/* TODO: ATTRIBUTES  */
	int											zoomRate;
	CWidget_t*								movingFocus;
	/* TODO END */
	
	/* TODO: METHODS  */
	GridViewGetFocusView_t		getFocusView;
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t				onClicked;
	WidgetEventEntry_t				onFocusChanged;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CGridView);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

