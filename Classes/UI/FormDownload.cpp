//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormDownload.cpp
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
#include "FormDownload.h"
#include "FormDownload.res.h"
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

const String FormDownload::EventNamespace("FormDownload");
const String FormDownload::WidgetTypeName("FormDownload");

//----------------------------------------------------------------------------//
FormDownload::FormDownload(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormDownload::~FormDownload(void)
{

}

//----------------------------------------------------------------------------//
void FormDownload::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormDownload::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormDownload::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	/*
	destroyTimer(ProgCountTimer);
	createTimer(ProgCountTimer, 1000, true, 0);
	
	initFormData();*/
}

//----------------------------------------------------------------------------//
void FormDownload::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
	
	//destroyTimer(ProgCountTimer);
}

//----------------------------------------------------------------------------//
void FormDownload::onCreated(void)
{
	M3D_Form::onCreated();

	d_menu = static_cast<M3D_ListView *>(getChild(Res_FormDownload::Menu));
	d_menu->setCircleEnable(true);
	d_menu->setHeight(UDim(0.5, 0.5));
	d_menu->setScrollOneItemTime(0.3f);
	d_menu->setOnClickListener(CALLBACK_2(FormDownload::handleMenuClicked, this));
	d_menu->setScrollAnimationType(Scroll_Animation_Type::Scroll_Type_RollBubbles);

		/*

	createTimer(ProgCountTimer, 1000, true, 0);
	
	initFormData();*/
}

//----------------------------------------------------------------------------//
void FormDownload::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormDownload::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);
	
	//setupBinding(true);
	d_menu->activate();
}

//----------------------------------------------------------------------------//
void FormDownload::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormDownload::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormDownload::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormDownload::onTimeout(EventArgs& e)
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
void FormDownload::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_RETURN:
		{	
			M3D_Log* mlog = getApp()->getFormLog(getID());
			getApp()->transitionForm(mlog->getParamInt("LastForm", FrmMain_ID), getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
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
void FormDownload::initFormData(void)
{
	
}

//----------------------------------------------------------------------------//
void FormDownload::setupBinding(bool firsttime)
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
void FormDownload::handleReloadData(M3D_Item *item, int position)
{

}

//----------------------------------------------------------------------------//
void FormDownload::handlePageChange(int currentPage, int totalPage)
{/*
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);*/
}

//----------------------------------------------------------------------------//
	void FormDownload::handleMenuClicked(M3D_Item *item, int position)
	{		
		/*M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
		mlog->setParamInt("Type", REQDB_TYPE_LANGUAGE_SONG);
		mlog->setParamInt("SubType", SubType[position]);
		mlog->setParamInt("Position", 0);
		mlog->setParamString("StrPara", "");*/

		int informID = 0;
		switch (position) {
		case ItemMp3_ID :
		case ItemMp3_ID1:
		case ItemMp3_ID2:
			informID = FrmDownloadMp3_ID;
			break;
		case ItemMTV_ID:
		case ItemMTV_ID1:
		case ItemMTV_ID2:
			informID = FrmDownloadMTV_ID;
			break;
		case ItemMovie_ID:
		case ItemMovie_ID1:
		case ItemMovie_ID2:
			informID = FrmDownloadMovie_ID;
			break;
		default:
			break;
		}
		if (informID > 0) {
			//设置数据，跳到FormDownloadMovie
			getApp()->transitionForm(informID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
	}
}