#ifndef _CIMAGENUM_H_
#define _CIMAGENUM_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
#include <gui/widgets/CLabel.h>
/* TODO END */

#define CImageNum_ClassID					9

/* TODO: REGISTER WIDGETS */
#define CImageNum_RegWidgets(ImageNum) {\
}
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CImageNum_RegMethods(ImageNum) {\
	ezRegMethod(Widget(ImageNum), CImageNum, onCreated);\
	ezRegMethod(Widget(ImageNum), CImageNum, constructor);\
	ezRegMethod(Widget(ImageNum), CImageNum, setIntValue);\
	ezRegMethod(ImageNum, CImageNum, onChanged);\
}
/* TODO END */

typedef struct s_CImageNum CImageNum_t;


/* TODO: ImageNum RESOURCE */
enum {
	ImageNumAlign_None = 0,
	ImageNumAlign_Left,
	ImageNumAlign_Right,
};

/* TODO: ImageNum RESOURCE */
enum {
	ImageNumRes_ImageNum0_ID = 0,
	ImageNumRes_ImageCount_ID,
	ImageNumRes_ImageAlign_ID,
	ImageNumRes_Count,
};
/* TODO END */

/* TODO: KEYBOARD EVENT ID */
enum ImageNumEventID {
	ImageNumEvent_onNumChanged = ((CImageNum_ClassID<<8) + 1),
	
	ImageNumEventCount
};
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
/* TODO END */

struct s_CImageNum
{

	CWidget_t Widget;

	/* TODO: ATTRIBUTES  */
	
	int 						ImageNumInt;
	int						ImageNum0;
	int						ImageCount;	
	int						ImageAlign;
	/* TODO END */
	
	/* TODO: METHODS  */
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t				onChanged;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CImageNum);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif
