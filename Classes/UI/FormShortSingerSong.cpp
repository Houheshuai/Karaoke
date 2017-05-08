//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortSingerSong.cpp
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
#include "FormShortSingerSong.h"
#include "FormShortSingerSong.res.h"
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

const String FormShortSingerSong::EventNamespace("FormShortSingerSong");
const String FormShortSingerSong::WidgetTypeName("FormShortSingerSong");

//----------------------------------------------------------------------------//
FormShortSingerSong::FormShortSingerSong(const String& type, const String& name):
M3D_Form(type, name)
{
}

//----------------------------------------------------------------------------//
FormShortSingerSong::~FormShortSingerSong(void)
{
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortSingerSong::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_songlist = static_cast<M3D_PageListView *>(getChild(Res_FormShortSingerSong::SongList));
	d_songlist->setCircleEnable(false);
	d_songlist->setFocusBarResID(Res_FormShortSingerSong::FocusBar);
	d_songlist->onDataFill = CALLBACK_2(FormShortSingerSong::handleReloadData, this);
	d_songlist->onPageChange = CALLBACK_2(FormShortSingerSong::handlePageChange, this);
	d_songlist->setOnClickListener(CALLBACK_2(FormShortSingerSong::handleListClicked, this));

	d_scrollbar = static_cast<M3D_ScrollBar*>(d_songlist->getChild(Res_FormShortSingerSong::ScrollBar));
	d_scrollbar->setPageValue(1);

	d_displaypic = static_cast<M3D_Label*>(getChild(Res_FormShortSingerSong::DisplayWindow)->getChild(Res_FormShortSingerSong::DisplayPic));
	d_searchlable = static_cast<M3D_Label*>(getChild(Res_FormShortSingerSong::T9));
	d_searchstr = static_cast<M3D_Label*>(d_searchlable->getChild(Res_FormShortSingerSong::T9string));
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	setupBinding(true);
	d_songlist->activate();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == Confirm)
	{
		d_confirm = true;
		setupBinding(false);
	}
}	

//----------------------------------------------------------------------------//
void FormShortSingerSong::onCharacter(KeyEventArgs& e)
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
		if(d_searchlable->isVisible())
		{
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
		}
		break;
	case M3D_UI_KEY_BKSP:
		if(d_searchlable->isVisible())
		{
			if(d_curPos >= 0)
			{
				d_lastKey = -1;
				d_str[d_curPos--] = '\0';
				d_searchstr->setString(d_str);
				d_confirm = true;
				destroyTimer(Confirm);
				createTimer(Confirm, 800.f, false, 0);
			}
		}
		break;
	/*case M3D_UI_KEY_FAVO:
		handleFavoClicked();
		break;
	case M3D_UI_KEY_PROG:
		handleProgClicked();
		break;
	case M3D_UI_KEY_PLAY:
		handleInsertClicked();
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
	default:
		break;
	}
	M3D_Form::onCharacter(e);
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::initFormData(void)
{
	d_searchstr->setString("");
	d_displaypic->setImage(0);
	for(int i = 0; i < d_songlist->getChildAtIdx(0)->getChildCount(); i++)
	{
		Window* item = d_songlist->getChildAtIdx(0)->getChildAtIdx(i);
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->hide(); //setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->hide(); //setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->hide(); //setBGImage(0);

		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
	}
}

//----------------------------------------------------------------------------//
void FormShortSingerSong::setFormData(int type, int subtype)
{
	switch(type)
	{
	case REQDB_TYPE_SINGERSONG:
		d_displaypic->setImage(0x210b);
		d_searchlable->hide();
		break;
	case REQDB_TYPE_PINYIN:
		d_displaypic->setImage(0x210e);
		d_searchlable->show();
		break;
	case REQDB_TYPE_MYHOT_SONG:
		d_displaypic->setImage(0x212a);
		d_searchlable->hide();
		break;
	case REQDB_TYPE_LANGUAGE_SONG:
		switch(subtype)
		{
		case SONG_SUBTYPE_VIE:
			d_displaypic->setImage(0x21ed);
			break;
		case SONG_SUBTYPE_MY:
			d_displaypic->setImage(0x21ee);
			break;
		case SONG_SUBTYPE_RU:
			d_displaypic->setImage(0x21ef);
			break;
		case SONG_SUBTYPE_CN:
			d_displaypic->setImage(0x21e9);
			break;
		case SONG_SUBTYPE_EN:
			d_displaypic->setImage(0x21ea);
			break;
		case SONG_SUBTYPE_JP:
			d_displaypic->setImage(0x21eb);
			break;
		case SONG_SUBTYPE_KR:
			d_displaypic->setImage(0x21ec);
			break;
		default:
			break;
		}
		d_searchlable->show();
		break;
	case REQDB_TYPE_GENRE_SONG:
		d_displaypic->setImage(0x210b);
		d_searchlable->hide();
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------//
void FormShortSingerSong::setupBinding(bool firsttime)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	assert(reqDb != NULL);
	
	handleM3DRec* handle = &(reqDb->handle);
	if(firsttime)
	{
		M3D_Log* mlog = getApp()->getFormLog(getID());
		handle->reqCmd.type = mlog->getParamInt("Type", REQDB_TYPE_SINGERSONG);
		handle->reqCmd.subType = mlog->getParamInt("SubType", 0);
		handle->reqCmd.intPara = mlog->getParamInt("Position", 0);
		handle->reqCmd.itemIndex = 0;
		sprintf(handle->reqCmd.strPara, "%s", mlog->getParamString("StrPara", "").c_str());
		
		setFormData(handle->reqCmd.type, handle->reqCmd.subType);
		
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
void FormShortSingerSong::handleReloadData(M3D_Item *item, int position)
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
		static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->hide(); //setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->hide(); //setBGImage(0);
		static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->hide(); //setBGImage(0);

		static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
		static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
	}
}
//----------------------------------------------------------------------------//
void FormShortSingerSong::handlePageChange(int currentPage, int totalPage)
{
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);
}
//----------------------------------------------------------------------------//
void FormShortSingerSong::handleListClicked(M3D_Item *item, int position)
{		
	handleProgClicked();
}
//----------------------------------------------------------------------------//
bool FormShortSingerSong::handleFavoClicked(void)
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
bool FormShortSingerSong::handleProgClicked(void)
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
		reqDb->reqRec(tag, 1);
		M3D_Item* item = d_songlist->getFocusItem();
		static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->setBGImage(ProgImage_ID + 1);
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------//
bool FormShortSingerSong::handleInsertClicked(void)
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
}

