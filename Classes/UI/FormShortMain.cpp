//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortMain.cpp
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
#include "FormShortMain.h"
#include "FormShortMain.res.h"
#include "FormPlay.h"
//#include "FormOtherPlay.h"
#include "Widgets/M3D_ListView.h"
#include "Widgets/M3D_Item.h"
#include "M3D_Config.h"


namespace	CEGUI
{	
enum{
	ItemPinYin_ID,
	ItemArtist_ID,
	ItemLanguage_ID,
	ItemMyHot_ID,
	ItemPopular_ID,
	ItemFavoSong_ID,
	ItemDownload_ID,
	ItemReserved_ID,
	ItemMTV_ID,
	ItemProgSong_ID,
	ItemWriter_ID,
};
static String ReturnTimer("ReturnTimer");

const String FormShortMain::EventNamespace("FormShortMain");
const String FormShortMain::WidgetTypeName("FormShortMain");

//----------------------------------------------------------------------------//
FormShortMain::FormShortMain(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormShortMain::~FormShortMain(void)
{

}
//----------------------------------------------------------------------------//

void FormShortMain::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormShortMain::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormShortMain::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);
	
	resetTimer(ReturnTimer);
}

//----------------------------------------------------------------------------//
void FormShortMain::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormShortMain::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_menu = static_cast<M3D_ListView *>(getChild(Res_FormShortMain::Menu));
	d_menu->setCircleEnable(true);
	d_menu->setScrollOneItemTime(0.2f);
	d_menu->setOnClickListener(CALLBACK_2(FormShortMain::handleMenuClicked, this));
	d_menu->setScrollAnimationType(Scroll_Animation_Type::Scroll_Type_RollBubbles);
	
	createTimer(ReturnTimer, 30000, false, 0);
}

//----------------------------------------------------------------------------//
void FormShortMain::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormShortMain::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	d_menu->activate();
}

//----------------------------------------------------------------------------//
void FormShortMain::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormShortMain::onActionStart(void)
{
	M3D_Form::onActionStart();
}

void FormShortMain::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}
	
//----------------------------------------------------------------------------//
void FormShortMain::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == ReturnTimer)
	{
		handleExitForm();
	}
}

//----------------------------------------------------------------------------//
void FormShortMain::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_RETURN:
		handleExitForm();
		break;
	//case M3D_UI_KEY_SEARCH:
	//	{	
	//		//M3D_Log* mlog = getApp()->getFormLog(FrmShortSingerSong_ID);
	//		mlog->setParamInt("Type", REQDB_TYPE_PINYIN);
	//		mlog->setParamInt("SubType", 0);
	//		mlog->setParamInt("Position", 0);
	//		mlog->setParamString("StrPara", "");
	//		
	//		getApp()->transitionForm(FrmShortSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
	//	}
	//	break;
	//case M3D_UI_KEY_FAVO:
	//	{
	//		getApp()->transitionForm(FrmShortFavoSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
	//	}
	//	break;
	case M3D_UI_KEY_SELECTED:
		{
			//getApp()->transitionForm(FrmShortProgSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
		/*case M3D_UI_KEY_MTV:
		{
		getApp()->transitionForm(FrmShortMTV_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
		case M3D_UI_KEY_NEWSONG:
		{
		getApp()->transitionForm(FrmShortNewSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
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
void FormShortMain::anyKeyDown(void)
{
	resetTimer(ReturnTimer);
}

//----------------------------------------------------------------------------//
void FormShortMain::handleMenuClicked(M3D_Item *item, int position)
{
	M3D_DebugPrint("FormShortMain::handleMenuClicked %d",position);
	int informId = 0;
	switch (position)
	{
	case ItemPinYin_ID:
		{	
			informId = FrmShortSingerSong_ID;
			M3D_Log* mlog = getApp()->getFormLog(FrmShortSingerSong_ID);
			mlog->setParamInt("Type", REQDB_TYPE_PINYIN);
			mlog->setParamInt("SubType", 0);
			mlog->setParamInt("LastForm", getID());
			mlog->setParamInt("Position", 0);
			mlog->setParamString("StrPara", "");
		}
		break;
	case ItemArtist_ID:
		{	
			informId = FrmShortSinger_ID;
			M3D_Log* mlog = getApp()->getFormLog(FrmShortSinger_ID);
			//mlog->setParamInt("SubType", REQDB_SUBTYPE_SINGER_WRITER);
			mlog->setParamInt("LastForm", getID());
			mlog->setParamInt("Position", 0);
			mlog->setParamString("StrPara", "");
		}
		break;
	case ItemLanguage_ID:
		informId = FrmShortLanguage_ID;
		break;
	case ItemDownload_ID:
		informId = FrmShortDownload_ID;
		break;
		/*case ItemSingerSong_ID:
		informId = FrmShortSingerSong_ID;
		break;*/
	
		/*case ItemFavoSong_ID:
		informId = FrmShortFavoSong_ID;
		break;
		case ItemProgSong_ID:
		informId = FrmShortProgSong_ID;
		break;
		case ItemMTV_ID:
		informId = FrmShortMTV_ID;
		break;*/
	/*case ItemNewSong_ID:
		informId = FrmShortNewSong_ID;
		break;*/
		/*case ItemMyHot_ID:
		{
		informId = FrmShortSingerSong_ID;
		M3D_Log* mlog = getApp()->getFormLog(FrmShortSingerSong_ID);
		mlog->setParamInt("Type", REQDB_TYPE_MYHOT_SONG);
		mlog->setParamInt("SubType", 0);
		mlog->setParamInt("LastForm", getID());
		mlog->setParamInt("Position", 0);
		mlog->setParamString("StrPara", "");
		}
		break;*/
	default:
		break;
	}
	if (informId > 0) {		
		getApp()->transitionForm(informId, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT, false);
	}
}

//----------------------------------------------------------------------------//
void FormShortMain::handleExitForm(void)
{
	M3D_App* app = getApp();
	app->hideForm(getID());
	FormPlay* form = static_cast<FormPlay*>(getApp()->getForm(FrmPlay_ID));
	//form->showPlayTitle();
	form->activate();
}

}

