#ifndef _CLISTITEM_H_
#define _CLISTITEM_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
/* TODO END */

#define CListItem_ClassID						6

/* TODO: REGISTER METHODS&EVENTS */
#define CListItem_RegMethods(listitem) {\
	ezRegMethod(Widget(listitem), CListItem, onDeactivated);\
	ezRegMethod(Widget(listitem), CListItem, onCreated);\
	ezRegMethod(Widget(listitem), CListItem, constructor);\
	ezRegMethod(Widget(listitem), CListItem, destructor);\
}
/* TODO END */

typedef struct s_CListItem CListItem_t;

/* TODO: LISTITEM RESOURCE */
enum {
	ListItemRes_activeImage_ID = 0,
	ListItemRes_itemValue_ID = 1,
	
	ListItemRes_Count,
};
/* TODO END */

/* TODO: LISTITEM EVENT ID */
enum ListItemEventID {
	ListItemEvent_onClicked = ((CListItem_ClassID<<8) + 1),

	ListItemEventCount
};
/* TODO END */

/* TODO: LISTITEM EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

} ListItemEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
/* TODO END */

struct s_CListItem
{

	CWidget_t Widget;

	/* TODO: ATTRIBUTES  */
	unsigned int 							itemIndex;
	unsigned int							bundingIndex;
	unsigned int							itemValue;
	/* TODO END */
	
	/* TODO: METHODS  */
	/* TODO END */
	
	/* TODO: EVENTS */
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CListItem);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

