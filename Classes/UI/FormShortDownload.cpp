//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortDownload.cpp
//																	
// Description: 
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#include "CEGUI.h"
#include "appKRK.h"
#include "FormID.res.h"
#include "FormShortDownload.h"
#include "FormShortDownload.res.h"
#include "Widgets/M3D_PageListView.h"
#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_ListView.h"
#include "Widgets/M3D_ScrollBar.h"
#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"

namespace	CEGUI
{
	enum{
		ItemMp3_ID,
		ItemMTV_ID,
		ItemMovie_ID,
		ItemMp3_ID1,
		ItemMTV_ID1,
		ItemMovie_ID1,
		ItemMp3_ID2,
		ItemMTV_ID2,
		ItemMovie_ID2
	};

static String ProgCountTimer("ProgCountTimer");

const String FormShortDownload::EventNamespace("FormShortDownload");
const String FormShortDownload::WidgetTypeName("FormShortDownload");

//----------------------------------------------------------------------------//
FormShortDownload::FormShortDownload(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormShortDownload::~FormShortDownload(void)
{

}

//----------------------------------------------------------------------------//
void FormShortDownload::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortDownload::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortDownload::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	/*
	destroyTimer(ProgCountTimer);
	createTimer(ProgCountTimer, 1000, true, 0);
	
	initFormData();*/
}

//----------------------------------------------------------------------------//
void FormShortDownload::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
	
	//destroyTimer(ProgCountTimer);
}

//----------------------------------------------------------------------------//
void FormShortDownload::onCreated(void)
{
	M3D_Form::onCreated();

	d_menu = static_cast<M3D_ListView *>(getChild(Res_FormShortDownload::Menu));
	d_menu->setCircleEnable(true);
	d_menu->setHeight(UDim(0.5, 0.5));
	d_menu->setScrollOneItemTime(0.3f);
	d_menu->setOnClickListener(CALLBACK_2(FormShortDownload::handleMenuClicked, this));
	d_menu->setScrollAnimationType(Scroll_Animation_Type::Scroll_Type_RollBubbles);
		/*
	createTimer(ProgCountTimer, 1000, true, 0);
	initFormData();*/
}

//----------------------------------------------------------------------------//
void FormShortDownload::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortDownload::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);
	
	//setupBinding(true);
	d_menu->activate();
}

//----------------------------------------------------------------------------//
void FormShortDownload::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortDownload::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormShortDownload::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormShortDownload::onTimeout(EventArgs& e)
{/*
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == ProgCountTimer)
	{
		ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		if (d_initCount != reqDB->ReqReservedSongCount())
		{
			d_initCount = reqDB->ReqReservedSongCount();
			char str[16];
			sprintf(str, "%d", d_initCount);
			d_count->setString(str);
		}
	}*/
}	

//----------------------------------------------------------------------------//
void FormShortDownload::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_RETURN:
		{	
			M3D_Log* mlog = getApp()->getFormLog(getID());
			getApp()->transitionForm(mlog->getParamInt("LastForm", FrmShortMain_ID), getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
		}
		break;
	case M3D_UI_KEY_SETUP:
		{
			getApp()->transitionForm(FrmSetup_ID, getID(), FORM_TRANSITION_ANIMATION::ANIMATION_NONE);
		}
		break;
	default:
		break;
	}
		
	M3D_Form::onCharacter(e);
}

//----------------------------------------------------------------------------//
void FormShortDownload::initFormData(void)
{
	
}

//----------------------------------------------------------------------------//
void FormShortDownload::setupBinding(bool firsttime)
{/*
	ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	assert(reqDb != NULL);
	
	handleM3DRec* handle = &(reqDb->handle);
	if(firsttime)
	{
	}
	else
	{
	}
	
	d_songlist->setTotalItemCount(0);
	d_songlist->jumpToTop();*/
}

//----------------------------------------------------------------------------//
void FormShortDownload::handleReloadData(M3D_Item *item, int position)
{

}

//----------------------------------------------------------------------------//
void FormShortDownload::handlePageChange(int currentPage, int totalPage)
{/*
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);*/
}

//----------------------------------------------------------------------------//
	void FormShortDownload::handleMenuClicked(M3D_Item *item, int position)
	{		
		int informID = 0;
		switch (position) {
		case ItemMp3_ID :
		case ItemMp3_ID1:
		case ItemMp3_ID2:
			informID = FrmShortMp3_ID;
			break;
		case ItemMTV_ID:
		case ItemMTV_ID1:
		case ItemMTV_ID2:
			informID = FrmShortMTV_ID;
			break;
		case ItemMovie_ID:
		case ItemMovie_ID1:
		case ItemMovie_ID2:
			informID = FrmShortMovie_ID;
			break;
		default:
			break;
		}
		if (informID > 0) {
			getApp()->transitionForm(informID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
	}
}