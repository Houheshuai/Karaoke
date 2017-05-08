//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormProgSong.cpp
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
#include "FormProgSong.h"
#include "FormProgSong.res.h"
#include "Widgets/M3D_PageListView.h"
#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_ScrollBar.h"
#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"


namespace	CEGUI
{

enum{
	SongType_ID,
	SongName_ID,
	Line_ID,
	Prog_ID,
	Favor_ID,
	SongOrder_ID,
};

static String ProgCountTimer("ProgCountTimer");

const String FormProgSong::EventNamespace("FormProgSong");
const String FormProgSong::WidgetTypeName("FormProgSong");

//----------------------------------------------------------------------------//
FormProgSong::FormProgSong(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormProgSong::~FormProgSong(void)
{

}

//----------------------------------------------------------------------------//
void FormProgSong::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormProgSong::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormProgSong::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	
	destroyTimer(ProgCountTimer);
	createTimer(ProgCountTimer, 1000, true, 0);
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormProgSong::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
	
	destroyTimer(ProgCountTimer);
}

//----------------------------------------------------------------------------//
void FormProgSong::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_songlist = static_cast<M3D_PageListView *>(getChild(Res_FormProgSong::SongList));
	d_songlist->setCircleEnable(false);
	d_songlist->setFocusBarResID(Res_FormProgSong::FocusBar);
	d_songlist->onDataFill = CALLBACK_2(FormProgSong::handleReloadData, this);
	d_songlist->onPageChange = CALLBACK_2(FormProgSong::handlePageChange, this);
	d_songlist->setOnFocusChangeListener(CALLBACK_2(FormProgSong::handleFocusChange, this));

	d_scrollbar = static_cast<M3D_ScrollBar*>(d_songlist->getChild(Res_FormProgSong::ScrollBar));
	d_scrollbar->setPageValue(1);
	
	d_progcount = static_cast<M3D_Label*>(getChild(Res_FormProgSong::ProgCount));
	d_count = static_cast<M3D_Label*>(d_progcount->getChild(Res_FormProgSong::Count));
	d_focusbar = static_cast<M3D_Label*>(getChild(Res_FormProgSong::SongList)->getChild(Res_FormProgSong::FocusBar));

	ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	d_initCount = reqDB->ReqReservedSongCount();
	char str[16];
	sprintf(str, "%d", d_initCount);
	d_count->setString(str);

	createTimer(ProgCountTimer, 1000, true, 0);
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormProgSong::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormProgSong::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	setupBinding(true);
	d_songlist->activate();
}

//----------------------------------------------------------------------------//
void FormProgSong::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormProgSong::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormProgSong::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormProgSong::onTimeout(EventArgs& e)
{
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
	}
}	

//----------------------------------------------------------------------------//
void FormProgSong::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_FAVORITE:
		handleFavoClicked();
		break;/*
	case M3D_UI_KEY_PLAY:
		handleInsertClicked();
		break;*/
	case M3D_UI_KEY_DELETE:
		handleDeleteClicked();
		break;
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
void FormProgSong::initFormData(void)
{
	for(int i = 0; i < d_songlist->getChildAtIdx(0)->getChildCount(); i++)
	{
		Window* item = d_songlist->getChildAtIdx(0)->getChildAtIdx(i);
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->setBGImage(0);

		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
	}
}


//----------------------------------------------------------------------------//
void FormProgSong::setupBinding(bool firsttime)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	assert(reqDb != NULL);
	
	handleM3DRec* handle = &(reqDb->handle);
	M3D_Log* mlog = getApp()->getFormLog(getID());
	handle->reqCmd.type = REQDB_TYPE_RESERVED;
	handle->reqCmd.intPara = mlog->getParamInt("Position", 0);
	handle->reqCmd.itemIndex = 0;
	memset(handle->reqCmd.strPara, 0, sizeof(handle->reqCmd.strPara));		
	
	d_dataCount = reqDb->reqInit(reqDb->handle.reqCmd, d_songlist->getPageSize());

	d_songlist->setTotalItemCount(d_dataCount);
	d_songlist->jumpToTop();

}

//----------------------------------------------------------------------------//
void FormProgSong::handleReloadData(M3D_Item *item, int position)
{
	if(position >= 0 && position < d_dataCount)
	{
		ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

		reqDb->reqRec(position, 1);
		SongListBindingStruct_t& song = reqDb->bindingRec.items[0].song;
		
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->show();
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->setBGImage(SongTypeImage_ID + song.SongType);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->show();
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(ProgImage_ID + song.Resv);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->show();
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->setBGImage(FavoImage_ID + song.Favo);

		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString(song.SongName);
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString(song.OrderChar);
	}
	else
	{
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->hide();  //->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->hide();  //->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->hide();  //->setBGImage(0);

		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
	}
}

//----------------------------------------------------------------------------//
void FormProgSong::handlePageChange(int currentPage, int totalPage)
{
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);
}

//----------------------------------------------------------------------------//
void FormProgSong::handleMenuClicked(M3D_Item *item, int position)
{		
	switch (position)
	{
		default:
			break;
	}
}

//----------------------------------------------------------------------------//
bool FormProgSong::handleFavoClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;
		
	reqDb->reqRec(tag, 1);
	if(reqDb->ReqFavoSongAdd(reqDb->bindingRec.items[0].song.SongIndex))
	{
		reqDb->reqRec(tag, 1);
		M3D_Item* item = d_songlist->getFocusItem();
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->setBGImage(FavoImage_ID + 1);
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------//
bool FormProgSong::handleInsertClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
	
	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;

	if(!reqDb->ReqReservedSongTopByIndex(tag))
		return false;

	setupBinding(true);
	
	return true;
}

//----------------------------------------------------------------------------//
bool FormProgSong::handleDeleteClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;
		
	reqDb->reqRec(tag, 1);
	reqDb->ReqReservedSongDeleteByIndex(tag);
	setupBinding(true);
	
	return true;
}
void FormProgSong::handleFocusChange(M3D_Item *item, int position)
{		
	refreshFocusInfo(true);
}

bool FormProgSong::refreshFocusInfo(bool refreshSingerName)
{
	if(d_dataCount <= 0) {
		d_focusbar->hide();
		return false;
	}
	else 
		d_focusbar->show();

	if(isDisabled(true))
		return false;

	//d_songlist->refreshRollStyle();

	return false;
}

}