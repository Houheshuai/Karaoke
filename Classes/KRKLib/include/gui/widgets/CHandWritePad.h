#ifndef _CHANDWRITEPAD_H_
#define _CHANDWRITEPAD_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
/* TODO END */

#define CHandwritePad_ClassID						8

/* TODO: REGISTER WIDGETS */
#define CHandwritePad_RegWidgets(handwritepad) {\
}
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CHandwritePad_RegMethods(handwritepad) {\
	ezRegMethod(Widget(handwritepad), CHandwritePad, constructor);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, destructor);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, drawSelf);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseClicked);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseMove);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseButtonDown);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseButtonUp);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseLeave);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onMouseEnter);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onKeyPress);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onCreated);\
	ezRegMethod(Widget(handwritepad), CHandwritePad, onDestroyed);\
	ezRegMethod(handwritepad, CHandwritePad, setPen);\
}
/* TODO END */

typedef struct s_CHandwritePad CHandwritePad_t;

/* TODO: TEMPLATE RESOURCE */
enum {
	HandwritePadRes_PenStartImage_ID = 0,
	HandwritePadRes_PenCount_ID,

	HandwritePadRes_PenHeight_ID,
	HandwritePadRes_PenWidth_ID,
	HandwritePadRes_Count,
};
/* TODO END */

/* TODO: TEMPLATE EVENT ID */
enum HandwritePadEventID {
	HandwritePadEvent_onStart = ((CHandwritePad_ClassID<<8) + 1),
	HandwritePadEvent_onStop = ((CHandwritePad_ClassID<<8) + 2),

	HandwritePadEventCount
};
/* TODO END */

/* TODO: TEMPLATE EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

} HandwritePadEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef void (*HandwritepadsetPen_t)(CHandwritePad_t*,int);

/* TODO END */

struct s_CHandwritePad
{

	CWidget_t Widget;
	/* TODO: ATTRIBUTES  */
	ezImage_t*		drawImage;
	ezImage_t*		PenImage;
	int 			iswriting;
	int 			PenHeight;
	int				PenWidth;
	int				PenStartImage;
	int				PenCount;
	int				PenID;
	gdi_texture_t*  texture;
	ezPoint			curPos;
	/* TODO END */
	
	/* TODO: METHODS  */
	HandwritepadsetPen_t  setPen;
	/* TODO END */
	
	/* TODO: EVENTS */
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CHandwritePad);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

