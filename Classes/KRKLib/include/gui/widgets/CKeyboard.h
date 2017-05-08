#ifndef _CKEYBOARD_H_
#define _CKEYBOARD_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
#include <gui/widgets/CLabel.h>
/* TODO END */

#define CKeyboard_ClassID					7

/* TODO: REGISTER WIDGETS */
#define CKeyboard_RegWidgets(keyboard) {\
	ezRegWidget(keyboard, CLabel, inputBox);\
	ezRegWidget(keyboard, CWidget, keyPad);\
}
/* TODO END */

/* TODO: REGISTER METHODS&EVENTS */
#define CKeyboard_RegMethods(keyboard) {\
	ezRegMethod(Widget(keyboard), CKeyboard, onActivated);\
	ezRegMethod(Widget(keyboard), CKeyboard, onKeyPress);\
	ezRegMethod(Widget(keyboard), CKeyboard, constructor);\
	ezRegMethod(Widget(keyboard), CKeyboard, onCreated);\
	ezRegMethod(keyboard, CKeyboard, onInputChanged);\
	ezRegMethod(keyboard, CKeyboard, onInputFinished);\
	ezRegMethod(keyboard, CKeyboard, getInput);\
	ezRegMethod(keyboard, CKeyboard, setInput);\
}
/* TODO END */

typedef struct s_CKeyboard CKeyboard_t;

/* TODO: KEYBOARD RESOURCE */
enum {
	KeyboardRes_InputMax_ID = 0,
	
	KeyboardRes_Count,
};
/* TODO END */

/* TODO: KEYBOARD EVENT ID */
enum KeyboardEventID {
	KeyboardEvent_onInputChanged = ((CKeyboard_ClassID<<8) + 1),
	KeyboardEvent_onInputFinished = ((CKeyboard_ClassID<<8) + 2),
	
	KeyboardEventCount
};
/* TODO END */

/* TODO: KEYBOARD EVENT ID */
typedef struct {
	WidgetEventArgs_t		we;

} KeyboardEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef char* (*KeyboardgetInput_t)(CKeyboard_t*);
typedef void (*KeyboardsetInput_t)(CKeyboard_t*, char*, int);
/* TODO END */

struct s_CKeyboard
{

	CWidget_t Widget;

	/* TODO: ATTRIBUTES  */
	CLabel_t*								inputBox;
	CWidget_t*								keyPad;
	int											inputMax;
	int											capsLock;											
	/* TODO END */
	
	/* TODO: METHODS  */
	KeyboardgetInput_t				getInput;
	KeyboardsetInput_t				setInput;
	/* TODO END */
	
	/* TODO: EVENTS */
	WidgetEventEntry_t				onInputChanged;
	WidgetEventEntry_t				onInputFinished;
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CKeyboard);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif

