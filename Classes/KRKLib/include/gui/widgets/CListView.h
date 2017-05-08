#ifndef _CLISTVIEW_H_
#define _CLISTVIEW_H_

#include <lib/ezbase/ez_vector.h>

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
#include <gui/widgets/CListItem.h>
/* TODO END */

#define CListView_ClassID						5

/* TODO: REGISTER WIDGETS */
#define CListView_RegWidgets(listview) {\
	ezRegWidget(listview, CWidget, frontItems);\
	ezRegWidget(listview, CWidget, rearItems);\
	ezRegWidget(listview, CWidget, focusBar);\
}
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CListView_RegMethods(listview) {\
	ezRegMethod(Widget(listview), CListView, constructor);\
	ezRegMethod(Widget(listview), CListView, onActivated);\
	ezRegMethod(Widget(listview), CListView, onMouseClicked);\
	ezRegMethod(Widget(listview), CListView, onMouseWheel);\
	ezRegMethod(Widget(listview), CListView, onKeyPress);\
	ezRegMethod(Widget(listview), CListView, onCreated);\
	ezRegMethod(listview, CListView, reset);\
	ezRegMethod(listview, CListView, getItem);\
	ezRegMethod(listview, CListView, getItemIndex);\
	ezRegMethod(listview, CListView, getFocusItem);\
	ezRegMethod(listview, CListView, setFocusItem);\
	ezRegMethod(listview, CListView, setStaticFocus);\
	ezRegMethod(listview, CListView, setItemData);\
	ezRegMethod(listview, CListView, setPageItemCount);\
	ezRegMethod(listview, CListView, setFrontPage);\
	ezRegMethod(listview, CListView, setBackPage);\
	ezRegMethod(listview, CListView, pageRoll);\
	ezRegMethod(listview, CListView, itemRoll);\
	ezRegMethod(listview, CListView, arrowKeyNav);\
	ezRegMethod(listview, CListView, setScrollMode);\
	ezRegMethod(listview, CListView, onPageUpdate);\
	ezRegMethod(listview, CListView, onFocusChanged);\
	ezRegMethod(listview, CListView, onItemScroll);\
	ezRegMethod(listview, CListView, onClicked);\
}
/* TODO END */

typedef struct s_CListView CListView_t;

/*
* ListView items type, we defined front items and rear items
* items will be switch if page roll event happened
*/
typedef enum
{
	CListView_Items_Front = 0,
	CListView_Items_Rear = 1,
	CListView_Items_Count = 2,
	
} ListViewItemsType_t;

/*
* ListView scroll mode
* page mode means scroll page by page when input NAV key or Mouse drag
* item mode means scroll items one by one when input NAV key or Mouse drag
*/
typedef enum
{
	CListView_ScrollNone = -1,
	CListView_ScrollPage = 0,
	CListView_ScrollItem = 1,
	
} ListViewScrollMode_t;

/*
* ListView scroll direction
*/
typedef enum
{
	CListView_ScrollDirUp = 0,
	CListView_ScrollDirDown = 1,
	
} ListViewScrollDir_t;

/*
* ListView scroll X/Y axis
*/
typedef enum
{
	CListView_ScrollYAxis = 0,
	CListView_ScrollXAxis = 1,
	
} ListViewScrollAxis_t;

/*
* ListView scroll effect
* linear effect & nonlinear effect
*/
typedef enum
{
	CListView_ScrollNoEffect = 0,
	CListView_ScrollLinear = 1,
	CListView_ScrollNonlinear = 2,
	
} ListViewScrollEffect_t;

/* TODO: LISTVIEW RESOURCE */
enum {
	ListViewRes_RowCount_ID = 0,				/* display row number */
	ListViewRes_ColumnCount_ID,				/* display column number */
	ListViewRes_ScrollMode_ID,					/* 0: scroll page mode, 1 : slide items mode */
	ListViewRes_ScrollAxis_ID,						/* 0: scroll y axis, 1 : roll x axis */
	
	ListViewRes_Count,
};
/* TODO END */

/* TODO: LISTVIEW EVENT ID */
enum ListViewEventID {
	ListViewEvent_onClicked = ((CListView_ClassID<<8) + 1),
	ListViewEvent_onPageUpdate,
	ListViewEvent_onFocusChanged,
	ListViewEvent_onItemScroll,
	
	ListViewEventCount
};
/* TODO END */

/* TODO: LISTVIEW EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

	int reqStartIndex;
} PageRefreshEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef void (*ListViewreset_t)(CListView_t*);
typedef CListItem_t* (*ListViewgetItem_t)(CListView_t*, int);
typedef int (*ListViewgetItemIndex_t)(CListView_t*, CListItem_t*);
typedef CListItem_t* (*ListViewgetFocusItem_t)(CListView_t*);
typedef void (*ListViewsetFocusItem_t)(CListView_t*, int);
typedef void (*ListViewsetItemData_t)(CListView_t*, int, int);
typedef void (*ListViewsetFrontPage_t)(CListView_t*, void* , unsigned int , unsigned int , int );
typedef void (*ListViewpageRoll_t)(CListView_t*, int);
typedef void (*ListViewsetScrollMode_t)(CListView_t*, ListViewScrollMode_t);
typedef int (*ListViewonPageUpdate_t)(CListView_t*, int);
typedef void (*ListViewonFocusChanged_t)(CListView_t*);
typedef void (*ListViewonItemScroll_t)(CListView_t*, int);
typedef int (*ListViewonarrowKeyNav_t)(CListView_t*, UIKeyScan);
typedef void (*ListViewsetPageItemCount_t)(CListView_t*, int);
/* TODO END */

struct s_CListView
{

	CWidget_t Widget;

	/* TODO: ATTRIBUTES  */
	CWidget_t*								frontItems;						/* front list window */
	CWidget_t*								rearItems;							/* rear list window */
	CWidget_t*								focusBar;							/* focus bar window */
	int											focusItem;						/* focus item index */
	int											rowCount;							/* display row count */
	int											columnCount;					/* display column count */
	ListViewScrollMode_t				scrollMode;						/* see enum ListViewScrollMode_t */
	ListViewScrollAxis_t				scrollAxis;						/* see enum ListViewScrollAxis_t */
	ListViewScrollEffect_t				scrollEffect;						/* see enum ListViewScrollEffect_t */
	int											rollSpeed;							/* the speed is the number of frames to roll one item */
	int											totalSteps;						/* the total number items of a new rolling */
	int											rollSteps;							/* the number of items wait to roll */
	int											listSteps;							/* how many steps front list can move out */
	int											pageItemCount;				/* number of items in one page */
	int											curStartItem;					/* the data index of first item in current page */
	int											totalItems;						/* total data items in list */
	int											frontPageId;						/* we have two list window, this is the front list window ID, [0,1] */
	int											itemWidth;
	int											itemHeight;
	int											itemStartX;
	int											itemStartY;
	int											actionCounter;					/* save action end counter, if count == 2, both front and rear window action ended */
	int											activeItemCount[CListView_Items_Count];
	int											startItemIndex[CListView_Items_Count];
	CWidget_t*								items[CListView_Items_Count];
	int											staticFocus;
	gdi_rect_t								rollMask;							/* list will roll items in this mask rect, out of rect items will be hidden */
	/* TODO END */
	
	/* TODO: METHODS  */
	ListViewreset_t						reset;
	ListViewgetItem_t					getItem;
	ListViewgetItemIndex_t			getItemIndex;
	ListViewgetFocusItem_t			getFocusItem;
	ListViewsetFocusItem_t			setFocusItem;
	ListViewsetFocusItem_t			setStaticFocus;
	ListViewsetItemData_t			setItemData;
	ListViewsetFrontPage_t			setFrontPage;
	ListViewsetFrontPage_t			setBackPage;
	ListViewpageRoll_t					pageRoll;
	ListViewpageRoll_t					itemRoll;
	ListViewonarrowKeyNav_t		arrowKeyNav;
	ListViewsetScrollMode_t		setScrollMode;
	ListViewsetPageItemCount_t	setPageItemCount;
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t				onClicked;
	ListViewonPageUpdate_t		onPageUpdate;
	ListViewonFocusChanged_t	onFocusChanged;
	ListViewonItemScroll_t			onItemScroll;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CListView);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

