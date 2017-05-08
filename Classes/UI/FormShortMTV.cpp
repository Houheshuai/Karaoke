//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortMTV.cpp
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
#include "FormShortMTV.h"
#include "FormShortMTV.res.h"
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

const String FormShortMTV::EventNamespace("FormShortMTV");
const String FormShortMTV::WidgetTypeName("FormShortMTV");

//----------------------------------------------------------------------------//
FormShortMTV::FormShortMTV(const String& type, const String& name):
M3D_Form(type, name)
{
}

//----------------------------------------------------------------------------//
FormShortMTV::~FormShortMTV(void)
{
}

//----------------------------------------------------------------------------//
void FormShortMTV::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortMTV::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortMTV::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormShortMTV::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_songlist = static_cast<M3D_PageListView *>(getChild(Res_FormShortMTV::SongList));
	d_songlist->setCircleEnable(false);
	d_songlist->setFocusBarResID(Res_FormShortMTV::FocusBar);
	d_songlist->onDataFill = CALLBACK_2(FormShortMTV::handleReloadData, this);
	d_songlist->onPageChange = CALLBACK_2(FormShortMTV::handlePageChange, this);
	d_songlist->setOnClickListener(CALLBACK_2(FormShortMTV::handleListClicked, this));
	d_songlist->setOnFocusChangeListener(CALLBACK_2(FormShortMTV::handleFocusChange, this));

	d_scrollbar = static_cast<M3D_ScrollBar*>(d_songlist->getChild(Res_FormShortMTV::ScrollBar));
	d_scrollbar->setPageValue(1);
	d_displaypic = static_cast<M3D_Label*>(getChild(Res_FormShortMTV::DisplayWindow)->getChild(Res_FormShortMTV::DisplayPic));
	d_searchlable = static_cast<M3D_Label*>(getChild(Res_FormShortMTV::T9));
	d_searchstr = static_cast<M3D_Label*>(d_searchlable->getChild(Res_FormShortMTV::T9string));
	d_singerName = static_cast<M3D_Label*>(getChild(Res_FormShortMTV::DisplayWindow)->getChild(Res_FormShortMTV::DisplayName));
	d_focusbar = static_cast<M3D_Label*>(getChild(Res_FormShortMTV::SongList)->getChild(Res_FormShortMTV::FocusBar));
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	setupBinding(true);
	d_songlist->activate();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortMTV::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormShortMTV::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == Confirm)
	{
		d_confirm = true;
		setupBinding(false);
	}
}	

//----------------------------------------------------------------------------//
void FormShortMTV::onCharacter(KeyEventArgs& e)
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
	case M3D_UI_KEY_MTV:
		getApp()->hideForm(getID());
		getApp()->getForm(FrmPlay_ID)->activate();
		break;
	default:
		break;
	}
		
	M3D_Form::onCharacter(e);
}

//----------------------------------------------------------------------------//
void FormShortMTV::initFormData(void)
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
void FormShortMTV::setupBinding(bool firsttime)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	assert(reqDb != NULL);
	
	handleM3DRec* handle = &(reqDb->handle);
	if(firsttime)
	{
		M3D_Log* mlog = getApp()->getFormLog(getID());
		handle->reqCmd.type = REQDB_TYPE_DOWNLOAD;
		handle->reqCmd.subType = REQDB_SUBTYPE_MTV;
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
	if (d_dataCount <= 0) {
		d_singerName->hide();
		d_songlist->clearItem();
	}
	else 
		d_singerName->show();

	d_songlist->setTotalItemCount(d_dataCount);
	d_songlist->jumpToTop();
}
void FormShortMTV::setFormData(int type, int subtype)
{
	switch(type)
	{
	case REQDB_TYPE_DOWNLOAD:
		switch (subtype)
		{
		case REQDB_SUBTYPE_MP3:
			d_displaypic->setImage(0x2127);
			break;
		case REQDB_SUBTYPE_MTV:
			d_displaypic->setImage(0x2128);
			break;
		default:
			break;
		}
		d_searchlable->show();
		break;
	case REQDB_TYPE_SINGERSONG:
		d_displaypic->setImage(0x210b);
		d_searchlable->hide();
		break;
	case REQDB_TYPE_PINYIN:
		d_displaypic->setImage(0x210e);
		d_searchlable->hide();
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
			d_displaypic->setImage(0x21f4);
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
		case SONG_SUBTYPE_PHI:
			d_displaypic->setImage(0x21e8);
			break;
		case SONG_SUBTYPE_FR:
			d_displaypic->setImage(0x21f1);
			break;
		case SONG_SUBTYPE_ID:
			d_displaypic->setImage(0x21f2);
			break;
		case SONG_SUBTYPE_IN:
			d_displaypic->setImage(0x21f3);
			break;
		case SONG_SUBTYPE_TH:
			d_displaypic->setImage(0x21ee);
			break;
		case SONG_SUBTYPE_SP:
			d_displaypic->setImage(0x21f0);
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
void FormShortMTV::handleReloadData(M3D_Item *item, int position)
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
void FormShortMTV::handlePageChange(int currentPage, int totalPage)
{
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);
}

//----------------------------------------------------------------------------//
void FormShortMTV::handleListClicked(M3D_Item *item, int position)
{		
	handleProgClicked();
}

//----------------------------------------------------------------------------//
bool FormShortMTV::handleFavoClicked(void)
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
bool FormShortMTV::handleProgClicked(void)
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
bool FormShortMTV::handleInsertClicked(void)
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

void FormShortMTV::handleFocusChange(M3D_Item *item, int position)
{		
	refreshFocusInfo(true);
}

bool FormShortMTV::refreshFocusInfo(bool refreshSingerName)
{
	M3D_DebugPrint("FormSingerSong::refreshFocusInfo\n");

	if(d_dataCount <= 0) {
		d_focusbar->hide();
		return false;
	}
	else 
		d_focusbar->show();

	if(isDisabled(true))
		return false;

	updateSinger();
	//d_songlist->refreshRollStyle();

	return false;
}
void FormShortMTV::updateSinger(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
	int focusItemData = d_songlist->getFocusDataIndex();

	//M3D_DebugPrint("##############tag = [%d]###########\n",tag);
	reqDb->reqRec(focusItemData, 1);
	std::string singerName;
	reqDb->reqSingerNameBySongId(reqDb->bindingRec.items[0].song.SongIndex, &singerName);
	//d_singerName->setCaption((char*)singerName.c_str());
	d_singerName->setString((char*)singerName.c_str());
}
}

