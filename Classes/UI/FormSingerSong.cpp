//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormSingerSong.cpp
//																	
// Description: 
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//

#include "CEGUI.h"
#include "appKRK.h"
#include "FormID.res.h"
#include "FormSingerSong.h"
#include "FormSingerSong.res.h"
#include "Widgets/M3D_PageListView.h"
#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_ScrollBar.h"
#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"
#include "Image.res.h"
#include "Strings.res.h"
#include "FormLogParam.h"

#include "Base/StringUtils.h"
#include "KRKLibNew/KRKPlayer/MCodeConvert.h"
#include <krklib.h>
#include "Event/EventListenerCustom.h"
#include "Event/EventCustom.h"
//#include "KRKPlayer/VideoManager.h"
#include "MKConfig.h"

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
	static String ProgCountTimer("ProgCountTimer");
	const String FormSingerSong::EventNamespace("FormSingerSong");
	const String FormSingerSong::WidgetTypeName("FormSingerSong");
	//----------------------------------------------------------------------------//
	FormSingerSong::FormSingerSong(const String& type, const String& name):
		M3D_Form(type, name), d_initCount(0)
		{

		}
	//----------------------------------------------------------------------------//
	FormSingerSong::~FormSingerSong()
	{
	}

//----------------------------------------------------------------------------//

	void FormSingerSong::constructWindow(WndRes_t *wndRes)
	{
		M3D_Form::constructWindow(wndRes);

		M3D_DebugPrint("constructWindow");
	}

//----------------------------------------------------------------------------//
	void FormSingerSong::destructWindow()
	{
		M3D_Form::destructWindow();

		M3D_DebugPrint("destructWindow");
	}

//----------------------------------------------------------------------------//
	void FormSingerSong::onShown(WindowEventArgs& e)
	{
		M3D_Form::onShown(e);
		
		destroyTimer(ProgCountTimer);
		createTimer(ProgCountTimer, 1000, true, 0);
	
		initFormData();
	}

	//----------------------------------------------------------------------------//
	void FormSingerSong::onHidden(WindowEventArgs& e)
	{
		M3D_Form::onHidden(e);
	}

	//----------------------------------------------------------------------------//
    void FormSingerSong::onCreated()
	{
		M3D_Form::onCreated();	

		d_songlist = static_cast<M3D_PageListView *>(getChild(Res_FormSingerSong::SongList));
		d_songlist->setCircleEnable(false);
		d_songlist->setFocusBarResID(Res_FormSingerSong::FocusBar);
		d_songlist->onDataFill = CALLBACK_2(FormSingerSong::handleReloadData, this);
		d_songlist->onPageChange = CALLBACK_2(FormSingerSong::handlePageChange, this);
		d_songlist->setOnClickListener(CALLBACK_2(FormSingerSong::handleListClicked, this));
		d_songlist->setOnFocusChangeListener(CALLBACK_2(FormSingerSong::handleFocusChange, this));

		d_scrollbar = static_cast<M3D_ScrollBar*>(d_songlist->getChild(Res_FormSingerSong::ScrollBar));
		d_scrollbar->setPageValue(1);

		d_displaypic = static_cast<M3D_Label*>(getChild(Res_FormSingerSong::DisplayWindow)->getChild(Res_FormSingerSong::DisplayPic));
		d_searchlable = static_cast<M3D_Label*>(getChild(Res_FormSingerSong::T9));
		d_searchstr = static_cast<M3D_Label*>(d_searchlable->getChild(Res_FormSingerSong::T9string));
		d_singerName = static_cast<M3D_Label*>(getChild(Res_FormSingerSong::DisplayWindow)->getChild(Res_FormSingerSong::DisplayName));
		d_focusbar = static_cast<M3D_Label*>(getChild(Res_FormSingerSong::SongList)->getChild(Res_FormSingerSong::FocusBar));

		d_progcount = static_cast<M3D_Label*>(getChild(Res_FormSingerSong::ProgCount));
		d_count = static_cast<M3D_Label*>(d_progcount->getChild(Res_FormSingerSong::Count));

		ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		d_initCount = reqDB->ReqReservedSongCount();
		char str[16];
		sprintf(str, "%d", d_initCount);
		d_count->setString(str);

		createTimer(ProgCountTimer, 1000, true, 0);
		initFormData();
	}

	//----------------------------------------------------------------------------//
	void FormSingerSong::onDestroyed()
	{	
		M3D_Form::onDestroyed();
		M3D_DebugPrint("onDestroyed");
	}

	void FormSingerSong::onActivated(ActivationEventArgs& e)
	{
		M3D_Form::onActivated(e);

		setupBinding(true);
		d_songlist->activate();
	}

	void FormSingerSong::onDeactivated(ActivationEventArgs& e)
	{
		M3D_Form::onDeactivated(e);		
	}

	void FormSingerSong::onActionStart()
	{
		M3D_Form::onActionStart();
		//M3D_DebugPrint("FormPlay::onActionStart");
	}

	void FormSingerSong::onActionEnd()
	{
		M3D_Form::onActionEnd();
		//M3D_DebugPrint("FormPlay::onActionEnd");
	}
	void FormSingerSong::onTimeout(EventArgs& e)
	{
		TimerEventArgs& te = (TimerEventArgs&)e;
		if(te.d_name == Confirm)
		{
			d_confirm = true; 
			setupBinding(false);
		}
		else if(te.d_name == ProgCountTimer)
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
	void FormSingerSong::onCharacter(KeyEventArgs& e)
	{
		if (isDisabled() || !isActive())
			return;
		switch (e.codepoint) {
		case M3D_UI_KEY_A:
		case M3D_UI_KEY_B:
		case M3D_UI_KEY_C:
		case M3D_UI_KEY_D:
		case M3D_UI_KEY_E:
		case M3D_UI_KEY_F:
		case M3D_UI_KEY_G:
		case M3D_UI_KEY_H:
		case M3D_UI_KEY_I:
		case M3D_UI_KEY_J:
		case M3D_UI_KEY_K:
		case M3D_UI_KEY_L:
		case M3D_UI_KEY_M:
		case M3D_UI_KEY_N:
		case M3D_UI_KEY_O:
		case M3D_UI_KEY_P:
		case M3D_UI_KEY_Q:
		case M3D_UI_KEY_R:
		case M3D_UI_KEY_S:
		case M3D_UI_KEY_T:
		case M3D_UI_KEY_U:
		case M3D_UI_KEY_V:
		case M3D_UI_KEY_W:
		case M3D_UI_KEY_X:
		case M3D_UI_KEY_Y:
		case M3D_UI_KEY_Z:
		{
			//resetTimer(Confirm);
			const char str = Key_T26[e.codepoint - M3D_UI_KEY_A];
			d_str[++d_curPos] = str;
			d_str[d_curPos + 1] = '\0';
			d_searchstr->setString(d_str);
			destroyTimer(Confirm);
			createTimer(Confirm, 800.f, false, 0);
		}
		break;
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
				int indexOfKey_T9 = 0;
				#ifdef WIN32
					indexOfKey_T9 = e.codepoint - M3D_UI_KEY_NUM_0;
				#else
					indexOfKey_T9 = e.codepoint - M3D_UI_KEY_NUM_1;
				#endif
				if(d_lastKey == e.codepoint && !d_confirm)
				{
					resetTimer(Confirm);
					const char* str = Key_T9[indexOfKey_T9];
					if(str[++d_lastKeyIndex] == '\0')
						d_lastKeyIndex = 0;
					d_str[d_curPos] = str[d_lastKeyIndex];
					d_searchstr->setString(d_str);
				}
				else if(d_curPos < Max_StrPara - 2)
				{
					d_lastKey = e.codepoint;
					const char* str = Key_T9[indexOfKey_T9];
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
				break;/*
	case M3D_UI_KEY_FAVO:
		handleFavoClicked();
		break;
	case M3D_UI_KEY_PROG:
		handleProgClicked();
		break;
	case M3D_UI_KEY_PLAY:
		{
			ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
			if (reqDb->ReqReservedSongCount() <= 0)
				handlePlayClicked();
			else
				handleInsertClicked();
		}
		break;*/
		case M3D_UI_KEY_RETURN:
			{
				M3D_Log* mlog = getApp()->getFormLog(getID());
				getApp()->transitionForm(mlog->getParamInt("LastForm", FrmMain_ID), getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
			}
			break;
		default:
			break;

		}
	}
	void FormSingerSong::initFormData(void)
	{
		d_singerName->setString("");
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

	void FormSingerSong::setFormData(int type, int subtype)
	{
		switch(type)
		{
		case REQDB_TYPE_SINGERSONG:
			d_displaypic->setImage(0x210b);
			d_searchlable->show();
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
	void FormSingerSong::setupBinding(bool firsttime)
	{
		ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		assert(reqDb != NULL);

		handleM3DRec* handle = &(reqDb->handle);
		if(firsttime)
		{
			M3D_Log* mlog = getApp()->getFormLog(getID());
			handle->reqCmd.type = mlog->getParamInt("Type", REQDB_TYPE_PINYIN);
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
		if (d_dataCount <= 0) {
			d_singerName->hide();
			d_songlist->clearItem();
		}
		else 
			d_singerName->show();
		d_songlist->setTotalItemCount(d_dataCount);
		d_songlist->jumpToTop();

	}
	void FormSingerSong::handleReloadData(M3D_Item *item, int position)
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
			//houhs：背景ID 0 找不到，有可能出现bug，所以设置hide
			static_cast<Window_2D *>(item->getChildAtIdx(SongType_ID))->hide();  //->setBGImage(0);
			static_cast<Window_2D *>(item->getChildAtIdx(Prog_ID))->hide();  //->setBGImage(0);
			static_cast<Window_2D *>(item->getChildAtIdx(Favor_ID))->hide();  //->setBGImage(0);

			static_cast<Window_2D *>(item->getChildAtIdx(SongName_ID))->setString("");
			static_cast<Window_2D *>(item->getChildAtIdx(SongOrder_ID))->setString("");
		}
	}
	void FormSingerSong::handlePageChange(int currentPage, int totalPage)
	{
		d_scrollbar->setMaxValue(totalPage);
		d_scrollbar->setValue(currentPage);
	}

	void FormSingerSong::handleListClicked(M3D_Item *item, int position)
	{	
		ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

		if (reqDb->ReqReservedSongCount() == 0)
			handlePlayClicked();
		else
			handleProgClicked();
	}
	bool FormSingerSong::handleFavoClicked(void)
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
	bool FormSingerSong::handleProgClicked(void)
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
	bool FormSingerSong::handlePlayClicked(void)
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
		
			//static_cast<appKRK*>(getApp())->playNextSong();
			getApp()->transitionForm(FrmPlay_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			return true;
		}
		return false;
	}

	//----------------------------------------------------------------------------//
	bool FormSingerSong::handleInsertClicked(void)
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

	void FormSingerSong::handleFocusChange(M3D_Item *item, int position)
	{		
		refreshFocusInfo(true);
	}

	bool FormSingerSong::refreshFocusInfo(bool refreshSingerName)
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
	void FormSingerSong::updateSinger(void)
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