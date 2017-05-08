#ifndef _CCLASSES_H_
#define _CCLASSES_H_

/* TODO: ADD NEW CLASS HEAD FILE */
#include "CApplication.h"
#include "CWidget.h"
#include "CLabel.h"
#include "CButton.h"
#include "CListView.h"
#include "CListItem.h"
#include "CKeyboard.h"
#include "CHandwritePad.h"
#include "CImageNum.h"
#include "CGridView.h"
/* TODO END */

/* GUI Class ID */
typedef enum
{
	/* TODO: ADD NEW CLASS ID */
	CApplication_CID = CApplication_ClassID,
	CWidget_CID = CWidget_ClassID,
	CLabel_CID = CLabel_ClassID,
	CButton_CID = CButton_ClassID,
	CListView_CID = CListView_ClassID,
	CListItem_CID = CListItem_ClassID,
	CKeyboard_CID = CKeyboard_ClassID,
	CHandwritePad_CID = CHandwritePad_ClassID,
	CImageNum_CID = CImageNum_ClassID,
	CGridView_CID = CGridView_ClassID,
	/* TODO END */

	Class_CID_Count
	
}GuiClassID_et;

typedef struct
{
	unsigned int		 	classID;
	unsigned int			SizeOfClass;
	EZGUI_MSG_PROC msgProc;
}GuiClassRegistry_st;

/* TODO: ADD NEW CLASS MSG PROC */
#define EZGUI_CLASS_REGISTRY()  {\
	EZGUI_REGISTER_CLASS(CApplication),\
	EZGUI_REGISTER_CLASS(CWidget),\
	EZGUI_REGISTER_CLASS(CLabel),\
	EZGUI_REGISTER_CLASS(CButton),\
	EZGUI_REGISTER_CLASS(CListView),\
	EZGUI_REGISTER_CLASS(CListItem),\
	EZGUI_REGISTER_CLASS(CKeyboard),\
	EZGUI_REGISTER_CLASS(CHandwritePad),\
	EZGUI_REGISTER_CLASS(CImageNum),\
	EZGUI_REGISTER_CLASS(CGridView),\
	}
/* TODO END */

#ifdef __cplusplus
extern "C" {
#endif

EZGUI_GLBDEF (GuiClassRegistry_st ezClassRegistry[Class_CID_Count-CApplication_CID], EZGUI_CLASS_REGISTRY());

/*
 * Function name  	: ez_attachClassMsgMap
 * Arguments      	: app - application handle, obj - control handle
 * Return         	: 0-succ, <>0-error code
 * Description    	: attach message map to widget
 *					
*/
extern int ez_attachClassMsgMap(CApplication_t *app, CWidget_t *obj);

#ifdef __cplusplus
}
#endif

#endif

