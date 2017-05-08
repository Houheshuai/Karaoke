//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Widgets.h
//																	
// Description: register new widget to this head file
//                       you have 3 items to add:
//                           1. M3D_ADD_WIDGET(M3D_WidgetName)  ---> register widget
//                           2. CID_M3D_WidgetName = 0xXXXX         ---> add widget class id
//                           3. #include "M3D_WidgetName.h"                  ---> add widget class head file
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#ifndef _M3D_WIDGETS_H_
#define _M3D_WIDGETS_H_

namespace CEGUI
{
#define M3D_ADD_WIDGET(WidgetName)		M3D_WindowManager::getSingletonPtr()->registerWidget<WidgetName>(CID_##WidgetName)
#define M3D_REGISTER_FORM(name)			M3D_ADD_WIDGET(name)

//! TODO : REGISTER WIDGET CLASS
#define M3D_REGISTER_WIDGETS() {\
	M3D_ADD_WIDGET(M3D_GUISheet);\
	M3D_ADD_WIDGET(M3D_Label);\
	M3D_ADD_WIDGET(M3D_CheckBox);\
	M3D_ADD_WIDGET(M3D_Button);\
	M3D_ADD_WIDGET(M3D_ListView);\
	M3D_ADD_WIDGET(M3D_Item);\
	M3D_ADD_WIDGET(M3D_ItemCollection);\
	M3D_ADD_WIDGET(M3D_ScrollBar);\
	M3D_ADD_WIDGET(M3D_PageListView);\
	M3D_ADD_WIDGET(M3D_SlipListView);\
	M3D_ADD_WIDGET(M3D_CardListView);\
}


//! TODO END

//! TODO : ADD WIDGET CLASS ID
enum
{
	CID_M3D_NONE = 0,

	// TODO : add new widget class id below
	CID_M3D_GUISheet = 0x0001,
	CID_M3D_Label = 0x0002,
	CID_M3D_CheckBox = 0x0003,
	CID_M3D_Button = 0x0004,
	CID_M3D_ListView = 0x0005,
	CID_M3D_Item = 0x0006,
	CID_M3D_ItemCollection = 0x0007,
	CID_M3D_ScrollBar = 0x0008,
	CID_M3D_PageListView = 0x0009,
	CID_M3D_SlipListView = 0x000A,
	CID_M3D_CardListView = 0x000B,
	
	CID_M3D_Max_Widgets = 0x1000
};
//! TODO END

}

//! TODO : ADD WIDGET HEAD FILE
#ifdef _M3D_WINMGR_C_
#include "M3D_GUISheet.h"
#include "M3D_Label.h"
#include "M3D_CheckBox.h"
#include "M3D_Button.h"
#include "M3D_ListView.h"
#include "M3D_Item.h"
#include "M3D_ItemCollection.h"
#include "M3D_ScrollBar.h"
#include "M3D_PageListView.h"
#include "M3D_SlipListView.h"
#include "M3D_CardListView.h"

#endif
//! TODO END
#endif

