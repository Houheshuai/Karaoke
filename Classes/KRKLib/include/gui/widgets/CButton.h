#ifndef _CBUTTON_H_
#define _CBUTTON_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
/* TODO END */

#define CButton_ClassID					4

/* TODO: REGISTER WIDGETS */
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CButton_RegMethods(button) {\
	ezRegMethod(Widget(button), CButton, constructor);\
	ezRegMethod(Widget(button), CButton, destructor);\
	ezRegMethod(Widget(button), CButton, drawSelf);\
	ezRegMethod(Widget(button), CButton, setIntValue);\
	ezRegMethod(Widget(button), CButton, setStrValue);\
	ezRegMethod(Widget(button), CButton, setValue);\
	ezRegMethod(Widget(button), CButton, setLayer);\
	ezRegMethod(Widget(button), CButton, transform);\
	ezRegMethod(Widget(button), CButton, onMouseEnter);\
	ezRegMethod(Widget(button), CButton, onMouseLeave);\
	ezRegMethod(Widget(button), CButton, onMouseButtonDown);\
	ezRegMethod(Widget(button), CButton, onMouseButtonUp);\
	ezRegMethod(Widget(button), CButton, onMouseClicked);\
	ezRegMethod(Widget(button), CButton, onDeactivated);\
	ezRegMethod(Widget(button), CButton, onKeyPress);\
	ezRegMethod(button, CButton, setCaption);\
	ezRegMethod(button, CButton, setDownState);\
	ezRegMethod(button, CButton, onClicked);\
	ezRegMethod(button, CButton, onDownChanged);\
}
/* TODO END */

#define CButtonKeyMask		0x1000

typedef struct s_CButton CButton_t;

/* TODO: BUTTON RESOURCE */
enum {
	ButtonRes_activeImage_ID = 0,
	ButtonRes_downImage_ID,
	ButtonRes_onCursorImage_ID,
	ButtonRes_disabledImage_ID,
	ButtonRes_keyCode_ID,
	ButtonRes_singleDown_ID,
	ButtonRes_isDownState_ID,
	
	ButtonRes_Count,
};
/* TODO END */

/* TODO: BUTTON EVENT ID */
enum ButtonEventID {
	ButtonEvent_onClicked = ((CButton_ClassID<<8) + 1),
	ButtonEvent_onDownChanged = ((CButton_ClassID<<8) + 2),

	ButtonEventCount
};
/* TODO END */

/* TODO: BUTTON EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

} ButtonEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef int (*ButtonSetCaption_t)(CButton_t*, char*);
typedef void (*ButtonSetDownState_t)(CButton_t*, unsigned int);
/* TODO END */

struct s_CButton
{

	CWidget_t Widget;

	/* TODO: ATTRIBUTES  */
	ezString_t						caption;
	unsigned int						keyCode;
	unsigned int						singleDown;
	/* TODO END */
	
	/* TODO: METHODS  */
	ButtonSetCaption_t			setCaption;
	ButtonSetDownState_t	setDownState;
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t			onClicked;
	WidgetEventEntry_t			onDownChanged;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CButton);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

