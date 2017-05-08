//----------------------------------------------------------------------------//
// Multak 3D GUI DEMO CODE					
// 
//
// --------------------------------------------------------------------------//

#include "Event/EventListenerCustom.h"
#include "Event/EventCustom.h"

#include "CEGUI.h"
#include "KRKPlayer/VideoManager.h"
#include "Strings.res.h"

#include "FormID.res.h"
#include "Image.res.h"
#include "FormLogParam.h"

#include "FormMain.h"
#include "FormMain.res.h"
#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_Label.h"
#include "Widgets/M3D_CheckBox.h"

#include "Widgets/M3D_PageListView.h"
#include "Widgets/M3D_ListView.h"
#include "appKRK.h"

#include "M3D_Config.h"
#include "GUIBase/M3D_App.h"
#include "Base/StringUtils.h"
#include "KRKLibNew/KRKPlayer/MCodeConvert.h"
namespace	CEGUI
{	
	enum{
		ItemPinYin_ID,
		ItemWriter_ID,
		ItemLanguage_ID,
		ItemSingerType_ID,
		ItemMyHot_ID,
		ItemNewSong_ID,
		ItemFavoSong_ID,
		ItemDownload_ID,
		ItemProgSong_ID,
		ItemMTV_ID,
		ItemRecord_ID,
	};
	static VideoManager* videoHandle;
	static appKRK*	  eventHandle;

    static String TopBarTimer("TopBar");
	static String HitInfoTimer("HitInfo");

	const String FormMain::EventNamespace("FormMain");
	const String FormMain::WidgetTypeName("FormMain");

	//----------------------------------------------------------------------------//
	FormMain::FormMain(const String& type, const String& name):
	M3D_Form(type, name)
	{
	}

	//----------------------------------------------------------------------------//
	FormMain::~FormMain()
	{
	}

	void FormMain::constructWindow(WndRes_t *wndRes)
	{
		M3D_Form::constructWindow(wndRes);

		M3D_DebugPrint("constructWindow");
	}

	void FormMain::destructWindow()
	{
		M3D_Form::destructWindow();

		M3D_DebugPrint("destructWindow");
	}

	void FormMain::onShown(WindowEventArgs& e)
	{
		M3D_Form::onShown(e);
	}

	void FormMain::onHidden(WindowEventArgs& e)
	{
		M3D_Form::onHidden(e);
	}

	//----------------------------------------------------------------------------//
	void FormMain::onCreated()
	{
		M3D_DebugPrint("onCreated FormMain \n");
		M3D_Form::onCreated();
		d_menu = static_cast<M3D_ListView*>(getChild(Res_FormMain::Menu));
		d_menu->setCircleEnable(true);
		d_menu->setScrollOneItemTime(0.3f);
		d_menu->setOnClickListener(CALLBACK_2(FormMain::handleMenuClicked, this));
		d_menu->setScrollAnimationType(Scroll_Animation_Type::Scroll_Type_RollBubbles);
	}

	//----------------------------------------------------------------------------//
	void FormMain::onDestroyed()
	{	
		M3D_Form::onDestroyed();
		M3D_DebugPrint("onDestroyed \n");
	}

	void FormMain::onActivated(ActivationEventArgs& e)
	{
		M3D_Form::onActivated(e);
		
		d_menu->activate();
	}

	void FormMain::onDeactivated(ActivationEventArgs& e)
	{
		M3D_Form::onDeactivated(e);
	}

	void FormMain::onActionStart()
	{
		M3D_Form::onActionStart();
		
		//M3D_DebugPrint("FormMain::onActionStart");
	}

	void FormMain::onActionEnd()
	{
		M3D_Form::onActionEnd();
		//M3D_DebugPrint("FormMain::onActionEnd");
	}
	void FormMain::onTimeout(EventArgs& e)
	{
		TimerEventArgs& te = (TimerEventArgs&)e;
	}

	void FormMain::onCharacter(KeyEventArgs& e)
	{
		M3D_Item *curItem;
		M3D_CheckBox *checkprog;
		bool topflag = false;
		if (isDisabled() || !isActive())
		{
			//M3D_Form::onCharacter(e);
			return;
		}
	
		switch (e.codepoint) 
		{
		case M3D_UI_KEY_ENTER:
			
			break;
		case M3D_UI_KEY_UP:
			
			break;
		case M3D_UI_KEY_DOWN:
			
			break;
		case M3D_UI_KEY_LEFT:
			break;
		case M3D_UI_KEY_RIGHT:
			
			break;
		case M3D_UI_KEY_RETURN:
			{
				M3D_Log* mlog = getApp()->getFormLog(getID());
				getApp()->transitionForm(FrmNumSong_ID, getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
			}
			break;
		default:
			
			break;
		}
		M3D_Form::onCharacter(e);
	}
	void FormMain::DownloadListView_DataFill(M3D_Item *item, int position)
	{
		
		if(position < 0 || position >= d_totalCnt)
		{
		}
		else
		{			
		}
	}
	void FormMain::DownloadListView_ItemClick(M3D_Item *item, int position)
	{
		if (position >= 0 && position < d_totalCnt)
		{				
			M3D_Log *mlog = getApp()->getFormLog(FrmPlay_ID);
			mlog->setParamInt(LogParam::fmParam_BackForm,FrmMain_ID);
			//mlog->setParamInt(LogParam::fmParam_FocusIdx,curFocusIdx);
			mlog->setParamInt(LogParam::fmParam_FocusSongIdx,position);
			String songname = eventHandle->getDLFileNameByPosition(position);
			mlog->setParamString(LogParam::fmParam_DLFileName,songname);
			
			getApp()->transitionForm(FrmPlay_ID, FrmMain_ID, FORM_TRANSITION_ANIMATION::ANIMATION_NONE);
		}
	}
	void FormMain::DownloadListView_FocusChange(M3D_Item *item, int position)
	{
		
	}
	void FormMain::DownloadListView_PageReflash(int currentPage, int totalPage)
	{
	}
	int FormMain::MCodeConvert_GB2312toUTF8(const char* in_utf8, char* out_gb2312, int Len1, int Len2)
	{
		CodeConverter cc = CodeConverter("gb18030","UTF-8");//use gb18030 to instead of gb2312
		cc.convert(in_utf8, &Len1, out_gb2312, &Len2);
		return Len2;
	}
	
	void FormMain::handleMenuClicked(M3D_Item *item, int position)
	{
		M3D_DebugPrint("FormMain::handleMenuClicked %d",position);

		int informId = 0;
		switch (position)
		{
		/*case ItemSingerType_ID:
			informId = FrmSingerType_ID;
			break;*/
		case ItemLanguage_ID:
			informId = FrmLanguage_ID;
			break;
		/*case ItemFavoSong_ID:
			informId = FrmFavoSong_ID;
			break;*/
		case ItemProgSong_ID:
			informId = FrmProgSong_ID;
			break;
		case ItemRecord_ID:
			informId = FrmRecord_ID;
			break;
		case ItemMTV_ID:
			informId = FrmMTV_ID;
			break;
		/*case ItemNewSong_ID:
			informId = FrmNewSong_ID;
			break;*/
		case ItemDownload_ID:
			informId = FrmDownload_ID;
			break;
		case ItemMyHot_ID:
			{
				informId = FrmSingerSong_ID;
				M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
				//mlog->setParamInt("Type", REQDB_TYPE_MYHOT_SONG);
				mlog->setParamInt("SubType", 0);
				mlog->setParamInt("Position", 0);
				mlog->setParamString("StrPara", "");
			}
			break;
		case ItemPinYin_ID:
			{	
				informId = FrmSingerSong_ID;
				M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
				//mlog->setParamInt("Type", REQDB_TYPE_PINYIN);
				mlog->setParamInt("SubType", 0);
				mlog->setParamInt("Position", 0);
				mlog->setParamString("StrPara", "");
			}
			break;
		case ItemWriter_ID:
			{
				informId = FrmSinger_ID;
				M3D_Log* mlog = getApp()->getFormLog(FrmSinger_ID);
				//mlog->setParamInt("SubType", REQDB_SUBTYPE_SINGER_WRITER);
				mlog->setParamInt("Position", 0);
				mlog->setParamString("StrPara", "");
			}
			break;
		
		default:
			break;
		}
		if (informId > 0)
		{
			getApp()->transitionForm(informId, FrmMain_ID, FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
	}
	//----------------------------------------------------------------------------//
}
