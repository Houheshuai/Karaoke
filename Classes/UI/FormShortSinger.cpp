//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortSinger.cpp
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
#include "FormShortSinger.h"
#include "FormShortSinger.res.h"
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

const String FormShortSinger::EventNamespace("FormShortSinger");
const String FormShortSinger::WidgetTypeName("FormShortSinger");

//----------------------------------------------------------------------------//
FormShortSinger::FormShortSinger(const String& type, const String& name):
M3D_Form(type, name)
{
}

//----------------------------------------------------------------------------//
FormShortSinger::~FormShortSinger(void)
{
}

//----------------------------------------------------------------------------//
void FormShortSinger::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortSinger::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortSinger::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);	
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormShortSinger::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_singerlist = static_cast<M3D_PageListView *>(getChild(Res_FormShortSinger::SingerList));
	d_singerlist->setCircleEnable(false);
	d_singerlist->setFocusBarResID(Res_FormShortSinger::FocusBar);
	d_singerlist->onDataFill = CALLBACK_2(FormShortSinger::handleReloadData, this);
	d_singerlist->onPageChange = CALLBACK_2(FormShortSinger::handlePageChange, this);
	d_singerlist->setOnClickListener(CALLBACK_2(FormShortSinger::handleListClicked, this));

	d_scrollbar = static_cast<M3D_ScrollBar*>(d_singerlist->getChild(Res_FormShortSinger::ScrollBar));
	d_scrollbar->setPageValue(1);
	
	d_displaypic = static_cast<M3D_Label*>(getChild(Res_FormShortSinger::DisplayWindow)->getChild(Res_FormShortSinger::DisplayPic));
	d_searchstr = static_cast<M3D_Label*>(getChild(Res_FormShortSinger::T9)->getChild(Res_FormShortSinger::T9string));
	
	initFormData();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	setupBinding(true);
	d_singerlist->activate();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortSinger::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormShortSinger::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == Confirm)
	{
		d_confirm = true;
		setupBinding(false);
	}
}

//----------------------------------------------------------------------------//
void FormShortSinger::onCharacter(KeyEventArgs& e)
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
	case M3D_UI_KEY_RETURN:
		{	
			M3D_Log* mlog = getApp()->getFormLog(getID());
			getApp()->transitionForm(mlog->getParamInt("LastForm", FrmMain_ID), getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
		}
		break;
	/*case M3D_UI_KEY_FAVO:
		{
			getApp()->transitionForm(FrmShortFavoSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_SELECTED:
		{
			getApp()->transitionForm(FrmProgSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;*/
	/*case M3D_UI_KEY_MTV:
		{
			getApp()->transitionForm(FrmMTV_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_NEWSONG:
		{
			getApp()->transitionForm(FrmNewSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;*/
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
void FormShortSinger::initFormData(void)
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
void FormShortSinger::setupBinding(bool firsttime)
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

	d_singerlist->setTotalItemCount(d_dataCount);
	d_singerlist->jumpToTop();
}

//----------------------------------------------------------------------------//
void FormShortSinger::handleReloadData(M3D_Item *item, int position)
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
void FormShortSinger::handlePageChange(int currentPage, int totalPage)
{
	d_scrollbar->setMaxValue(totalPage);
	d_scrollbar->setValue(currentPage);
}
//----------------------------------------------------------------------------//
void FormShortSinger::handleListClicked(M3D_Item *item, int position)
{	
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	if(position >= 0 && position < d_dataCount)
	{
		reqDb->reqRec(position, 1);

		unsigned int SingerID = reqDb->bindingRec.items[0].singer.SingerIndex;
		if(SingerID == -1)
			return;

		M3D_Log* mlog = getApp()->getFormLog(FrmShortSingerSong_ID);
		mlog->setParamInt("Type", REQDB_TYPE_SINGERSONG);
		mlog->setParamInt("SubType", SingerID);
		mlog->setParamInt("Position", 0);
		mlog->setParamString("StrPara", "");
		mlog->setParamString("Title", reqDb->bindingRec.items[0].singer.SingerName);

		getApp()->transitionForm(FrmShortSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		
	}
}
}

