//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormSinger.cpp
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
#include "FormSinger.h"
#include "FormSinger.res.h"
#include "Widgets/M3D_PageListView.h"
#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_ScrollBar.h"
#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"


namespace	CEGUI
{

	static const int SingerImage = 0x2124;

	enum{
		SingerType_ID,
		SingerName_ID,
		Line_ID,
	};

	static String Confirm("Confirm");
	static String ProgCountTimer("ProgCountTimer");

	const String FormSinger::EventNamespace("FormSinger");
	const String FormSinger::WidgetTypeName("FormSinger");

	//----------------------------------------------------------------------------//
	FormSinger::FormSinger(const String& type, const String& name):
	M3D_Form(type, name)
	{

	}

	//----------------------------------------------------------------------------//
	FormSinger::~FormSinger(void)
	{

	}

	//----------------------------------------------------------------------------//
	void FormSinger::constructWindow(WndRes_t *wndRes)
	{
		M3D_Form::constructWindow(wndRes);
	}

	//----------------------------------------------------------------------------//
	void FormSinger::destructWindow(void)
	{
		M3D_Form::destructWindow();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onShown(WindowEventArgs& e)
	{
		M3D_Form::onShown(e);	

		destroyTimer(ProgCountTimer);
		createTimer(ProgCountTimer, 1000, true, 0);

		initFormData();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onHidden(WindowEventArgs& e)
	{
		M3D_Form::onHidden(e);

		destroyTimer(ProgCountTimer);
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onCreated(void)
	{
		M3D_Form::onCreated();

		d_singerlist = static_cast<M3D_PageListView *>(getChild(Res_FormSinger::SingerList));
		d_singerlist->setCircleEnable(false);
		d_singerlist->setFocusBarResID(Res_FormSinger::FocusBar);
		d_singerlist->onDataFill = CALLBACK_2(FormSinger::handleReloadData, this);
		d_singerlist->onPageChange = CALLBACK_2(FormSinger::handlePageChange, this);
		d_singerlist->setOnClickListener(CALLBACK_2(FormSinger::handleListClicked, this));
		d_singerlist->setOnFocusChangeListener(CALLBACK_2(FormSinger::handleFocusChange, this));

		d_scrollbar = static_cast<M3D_ScrollBar*>(d_singerlist->getChild(Res_FormSinger::ScrollBar));
		d_scrollbar->setPageValue(1);
		d_focusbar = static_cast<M3D_Label*>(d_singerlist->getChild(Res_FormSinger::FocusBar));
		d_displaypic = static_cast<M3D_Label*>(getChild(Res_FormSinger::DisplayWindow)->getChild(Res_FormSinger::DisplayPic));
		d_searchlable = static_cast<M3D_Label*>(getChild(Res_FormSinger::T9));
		d_searchstr = static_cast<M3D_Label*>(d_searchlable->getChild(Res_FormSinger::T9string));

		d_progcount = static_cast<M3D_Label*>(getChild(Res_FormSinger::ProgCount));
		d_count = static_cast<M3D_Label*>(d_progcount->getChild(Res_FormSinger::Count));

		ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		d_initCount = reqDB->ReqReservedSongCount();
		char str[16];
		sprintf(str, "%d", d_initCount);
		d_count->setString(str);

		createTimer(ProgCountTimer, 1000, true, 0);
		
		initFormData();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onDestroyed(void)
	{	
		M3D_Form::onDestroyed();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onActivated(ActivationEventArgs& e)
	{
		M3D_Form::onActivated(e);

		setupBinding(true);
		d_singerlist->activate();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onDeactivated(ActivationEventArgs& e)
	{
		M3D_Form::onDeactivated(e);
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onActionStart(void)
	{
		M3D_Form::onActionStart();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onActionEnd(void)
	{
		M3D_Form::onActionEnd();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::onTimeout(EventArgs& e)
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

	//----------------------------------------------------------------------------//
	void FormSinger::onCharacter(KeyEventArgs& e)
	{
		if (isDisabled() || !isActive())
			return;

		switch (e.codepoint) 
		{
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
			if (d_searchlable->isVisible())
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
		case M3D_UI_KEY_DELETE:
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
		case M3D_UI_KEY_RETURN:
			{	
				M3D_Log* mlog = getApp()->getFormLog(getID());
				getApp()->transitionForm(mlog->getParamInt("LastForm", FrmMain_ID), getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT);
			}
			break;/*
		case M3D_UI_KEY_FAVO:
			{
				getApp()->transitionForm(FrmShortFavoSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			}
			break;
		case M3D_UI_KEY_SELECTED:
			{
				getApp()->transitionForm(FrmProgSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			}
			break;
		case M3D_UI_KEY_MTV:
			{
				getApp()->transitionForm(FrmMTV_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			}
			break;
		case M3D_UI_KEY_NEWSONG:
			{
				getApp()->transitionForm(FrmNewSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			}
			break;
		case M3D_UI_KEY_SETUP:
			{
				getApp()->transitionForm(FrmSetup_ID, getID(), FORM_TRANSITION_ANIMATION::ANIMATION_NONE);
			}
			break;*/
		default:
			break;
		}

		M3D_Form::onCharacter(e);
	}

	//----------------------------------------------------------------------------//
	void FormSinger::initFormData(void)
	{
		d_searchstr->setString("");
		d_displaypic->setImage(0);
		for(int i = 0; i < d_singerlist->getChildAtIdx(0)->getChildCount(); i++)
		{
			Window* item = d_singerlist->getChildAtIdx(0)->getChildAtIdx(i);
			static_cast<Window_2D *>(item->getChildAtIdx(SingerType_ID))->setBGImage(0);
			static_cast<Window_2D *>(item->getChildAtIdx(SingerName_ID))->setString("");
		}
	}

	//----------------------------------------------------------------------------//
	void FormSinger::setupBinding(bool firsttime)
	{
		ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		assert(reqDb != NULL);

		handleM3DRec* handle = &(reqDb->handle);
		if(firsttime)
		{
			M3D_Log* mlog = getApp()->getFormLog(getID());
			handle->reqCmd.type = REQDB_TYPE_SINGER;
			handle->reqCmd.subType = mlog->getParamInt("SubType", REQDB_SUBTYPE_SINGER_MALE);
			handle->reqCmd.intPara = mlog->getParamInt("Position", 0);
			handle->reqCmd.itemIndex = 0;
			sprintf(handle->reqCmd.strPara, "%s", mlog->getParamString("StrPara", "").c_str());

			d_displaypic->setImage(SingerImage + (handle->reqCmd.subType - REQDB_SUBTYPE_SINGER_MALE));

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
		d_dataCount = reqDb->reqInit(reqDb->handle.reqCmd, d_singerlist->getPageSize());
		if (d_dataCount <= 0) {
			d_singerlist->clearItem();
		}
		
		d_singerlist->setTotalItemCount(d_dataCount);
		d_singerlist->jumpToTop();
	}

	//----------------------------------------------------------------------------//
	void FormSinger::handleReloadData(M3D_Item *item, int position)
	{
		if(position >= 0 && position < d_dataCount)
		{
			ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

			reqDb->reqRec(position, 1);
			SingerListBindingStruct_t& singer = reqDb->bindingRec.items[0].singer;
			String singername = singer.SingerName;

			static_cast<Window_2D *>(item->getChildAtIdx(SingerType_ID))->setBGImage(SingerTypeImage_ID + reqDb->handle.reqCmd.subType);
			static_cast<Window_2D *>(item->getChildAtIdx(SingerName_ID))->setString(singername);
		}
		else
		{
			static_cast<Window_2D *>(item->getChildAtIdx(SingerType_ID))->setBGImage(0);
			static_cast<Window_2D *>(item->getChildAtIdx(SingerName_ID))->setString("");
		}
	}

	//----------------------------------------------------------------------------//
	void FormSinger::handlePageChange(int currentPage, int totalPage)
	{
		d_scrollbar->setMaxValue(totalPage);
		d_scrollbar->setValue(currentPage);
	}

	//----------------------------------------------------------------------------//
	void FormSinger::handleListClicked(M3D_Item *item, int position)
	{	
		ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

		if(position >= 0 && position < d_dataCount)
		{
			reqDb->reqRec(position, 1);

			unsigned int SingerID = reqDb->bindingRec.items[0].singer.SingerIndex;
			if(SingerID == -1)
				return;

			M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
			mlog->setParamInt("Type", REQDB_TYPE_SINGERSONG);
			mlog->setParamInt("SubType", SingerID);
			mlog->setParamInt("Position", 0);
			mlog->setParamString("StrPara", "");
			mlog->setParamString("Title", reqDb->bindingRec.items[0].singer.SingerName);

			getApp()->transitionForm(FrmSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);

		}
	}
	void FormSinger::handleFocusChange(M3D_Item *item, int position)
	{		
		refreshFocusInfo(true);
	}

	bool FormSinger::refreshFocusInfo(bool refreshSingerName)
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

		//d_songlist->refreshRollStyle();
		return false;
	}
}