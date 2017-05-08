//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortFavoSong.cpp
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
#include "FormShortFavoSong.h"
#include "FormShortFavoSong.res.h"
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

static String Confirm("Confirm");

const String FormShortFavoSong::EventNamespace("FormShortFavoSong");
const String FormShortFavoSong::WidgetTypeName("FormShortFavoSong");

//----------------------------------------------------------------------------//
FormShortFavoSong::FormShortFavoSong(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormShortFavoSong::~FormShortFavoSong(void)
{

}

//----------------------------------------------------------------------------//
void FormShortFavoSong::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortFavoSong::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_songlist = static_cast<M3D_PageListView *>(getChild(Res_FormShortFavoSong::SongList));
	d_songlist->setCircleEnable(false);
	d_songlist->setFocusBarResID(Res_FormShortFavoSong::FocusBar);
	d_songlist->onDataFill = CALLBACK_2(FormShortFavoSong::handleReloadData, this);
	d_songlist->onPageChange = CALLBACK_2(FormShortFavoSong::handlePageChange, this);
	d_songlist->setOnClickListener(CALLBACK_2(FormShortFavoSong::handleListClicked, this));

	d_scrollbar = static_cast<M3D_ScrollBar*>(d_songlist->getChild(Res_FormShortFavoSong::ScrollBar));
	d_scrollbar->setPageValue(1);

	d_searchstr = static_cast<M3D_Label*>(getChild(Res_FormShortFavoSong::T9)->getChild(Res_FormShortFavoSong::T9string));
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	setupBinding(true);
	d_songlist->activate();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == Confirm)
	{
		d_confirm = true;
		setupBinding(false);
	}
}	

//----------------------------------------------------------------------------//
void FormShortFavoSong::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_NUM_0:
	case M3D_UI_KEY_NUM_1:
	case M3D_UI_KEY_NUM_2:
	case M3D_UI_KEY_NUM_3:
	case M3D_UI_KEY_NUM_4:
	case M3D_UI_KEY_NUM_5:
	case M3D_UI_KEY_NUM_6:
	case M3D_UI_KEY_NUM_7:
	case M3D_UI_KEY_NUM_8:
	case M3D_UI_KEY_NUM_9:
		if(d_lastKey == e.codepoint && !d_confirm)
		{
			resetTimer(Confirm);
			const char* str = Key_T9[e.codepoint - M3D_UI_KEY_NUM_0];
			if(str[++d_lastKeyIndex] == '\0')
				d_lastKeyIndex = 0;
			d_str[d_curPos] = str[d_lastKeyIndex];
			d_searchstr->setString(d_str);
		}
		else if(d_curPos < Max_StrPara - 2)
		{
			d_lastKey = e.codepoint;
			const char* str = Key_T9[e.codepoint - M3D_UI_KEY_NUM_0];
			d_str[++d_curPos] = str[d_lastKeyIndex = 0];
			d_str[d_curPos + 1] = '\0';
			d_searchstr->setString(d_str);
			d_confirm = false;
			destroyTimer(Confirm);
			createTimer(Confirm, 800.f, false, 0);
		}
		break;
	case M3D_UI_KEY_BKSP:
		if(d_curPos >= 0)
		{
			d_lastKey = -1;
			d_str[d_curPos--] = '\0';
			d_searchstr->setString(d_str);
			d_confirm = true;
			destroyTimer(Confirm);
			createTimer(Confirm, 800.f, false, 0);
		}
		break;
	case M3D_UI_KEY_PROG:
		handleProgClicked();
		break;
	case M3D_UI_KEY_PLAY:
		handleInsertClicked();
		break;
	/*case M3D_UI_KEY_DELETE:
		handleDeleteClicked();
		break;*/
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
	case M3D_UI_KEY_STOP:
		{
			appKRK* app = static_cast<appKRK*>(getApp());
			app->stop();
		}
		break;
	default:
		break;
	}
		
	M3D_Form::onCharacter(e);
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::initFormData(void)
{
	d_searchstr->setString("");
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
void FormShortFavoSong::setupBinding(bool firsttime)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	assert(reqDb != NULL);
	
	handleM3DRec* handle = &(reqDb->handle);
	if(firsttime)
	{
		M3D_Log* mlog = getApp()->getFormLog(getID());
		handle->reqCmd.type = REQDB_TYPE_FAVSONG;
		handle->reqCmd.intPara = mlog->getParamInt("Position", 0);
		handle->reqCmd.itemIndex = 0;
		sprintf(handle->reqCmd.strPara, "%s", mlog->getParamString("StrPara", "").c_str());
		
		d_lastKey = -1;
		d_lastKeyIndex = -1;
		d_confirm = true;
		d_curPos = strlen(handle->reqCmd.strPara) - 1;
		sprintf(d_str, "%s", handle->reqCmd.strPara);
	}
	else
	{
		sprintf(handle->reqCmd.strPara, "%s", d_str);
	}
	d_dataCount = reqDb->reqInit(reqDb->handle.reqCmd, d_songlist->getPageSize());

	d_songlist->setTotalItemCount(d_dataCount);
	d_songlist->jumpToTop();

}

//----------------------------------------------------------------------------//
void FormShortFavoSong::handleReloadData(M3D_Item *item, int position)
{
	if(position >= 0 && position < d_dataCount)
	{
		ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

		reqDb->reqRec(position, 1);
		SongListBindingStruct_t& song = reqDb->bindingRec.items[0].song;
		
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->setBGImage(SongTypeImage_ID + song.SongType);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(ProgImage_ID + song.Resv);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->setBGImage(FavoImage_ID + song.Favo);
		
		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString(song.SongName);
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString(song.OrderChar);
	}
	else
	{
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->setBGImage(0);
		
		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
	}
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::handlePageChange(int currentPage, int totalPage)
{
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);
}

//----------------------------------------------------------------------------//
void FormShortFavoSong::handleListClicked(M3D_Item *item, int position)
{		
	handleProgClicked();
}

//----------------------------------------------------------------------------//
bool FormShortFavoSong::handleProgClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;
		
	reqDb->reqRec(tag, 1);
#ifndef RES_ADD_NOT_REQ_DB
	if(reqDb->ReqReservedSongAdd(reqDb->bindingRec.items[0].song.SongIndex))
#else
	if(reqDb->ReqReservedSongAdd(&reqDb->bindingRec.items[0].song))
#endif
	{
		M3D_Item* item = d_songlist->getFocusItem();
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(ProgImage_ID + 1);
		return true;
	}
	
	return false;
}

//----------------------------------------------------------------------------//
bool FormShortFavoSong::handleInsertClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;
		
	reqDb->reqRec(tag, 1);
#ifndef CAN_RESERVED_SAME_SONG
	reqDb->ReqReservedSongDelete(reqDb->bindingRec.items[0].song.SongIndex);
#endif
	if(reqDb->ReqReservedSongInsert(reqDb->bindingRec.items[0].song.SongIndex))
	{
		reqDb->reqRec(tag, 1);
		M3D_Item* item = d_songlist->getFocusItem();
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(ProgImage_ID + 1);
		return true;
	}
	
	return false;
}

//----------------------------------------------------------------------------//
bool FormShortFavoSong::handleDeleteClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	int tag = d_songlist->getFocusDataIndex();
	if (tag == -1)
		return false;
		
	reqDb->reqRec(tag, 1);
	reqDb->ReqFavoSongDelete(reqDb->bindingRec.items[0].song.SongIndex);
	setupBinding(true);
	
	return true;
}

}

