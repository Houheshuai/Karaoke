//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormLanguage.cpp
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
#include "FormLanguage.h"
#include "FormLanguage.res.h"
#include "Widgets/M3D_ListView.h"
#include "Widgets/M3D_Item.h"
#include "M3D_Config.h"

namespace CEGUI
{
	enum{
		Item_CN_ID,
		Item_EN_ID,
		Item_JP_ID,
		Item_KR_ID,
		Item_VIE_ID,
		Item_MY_ID,
		Item_RU_ID,
		Item_Count=13,
	};
	/*
	const int SubType[Item_Count] = {
		SONG_SUBTYPE_VIE,
		SONG_SUBTYPE_MY,
		SONG_SUBTYPE_RU,
		SONG_SUBTYPE_CN,
		SONG_SUBTYPE_EN,
		SONG_SUBTYPE_JP,
		SONG_SUBTYPE_KR,
	};*/

	const int SubType[Item_Count] = {
		
		SONG_SUBTYPE_PHI,
		SONG_SUBTYPE_CN,
		SONG_SUBTYPE_EN,
		SONG_SUBTYPE_JP, 
		SONG_SUBTYPE_KR,
		SONG_SUBTYPE_VIE,
		SONG_SUBTYPE_TH,
		SONG_SUBTYPE_RU, 
		SONG_SUBTYPE_SP, 
		SONG_SUBTYPE_FR, 
		SONG_SUBTYPE_ID, 
		SONG_SUBTYPE_IN, 
		SONG_SUBTYPE_MY, 
	};

	const String FormLanguage::EventNamespace("FormLanguage");
	const String FormLanguage::WidgetTypeName("FormLanguage");

	//----------------------------------------------------------------------------//
	FormLanguage::FormLanguage(const String& type, const String& name):
	M3D_Form(type, name)
	{

	}

	//----------------------------------------------------------------------------//
	FormLanguage::~FormLanguage(void)
	{

	}
	//----------------------------------------------------------------------------//

	void FormLanguage::constructWindow(WndRes_t *wndRes)
	{
		M3D_Form::constructWindow(wndRes);
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::destructWindow(void)
	{
		M3D_Form::destructWindow();
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onShown(WindowEventArgs& e)
	{
		M3D_Form::onShown(e);
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onHidden(WindowEventArgs& e)
	{
		M3D_Form::onHidden(e);
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onCreated(void)
	{
		M3D_Form::onCreated();
		
		d_menu = static_cast<M3D_ListView *>(getChild(Res_FormLanguage::Menu));
		d_menu->setCircleEnable(true);
		d_menu->setScrollOneItemTime(0.5f);
		d_menu->setOnClickListener(CALLBACK_2(FormLanguage::handleMenuClicked, this));
		d_menu->setScrollAnimationType(Scroll_Animation_Type::Scroll_Type_RollBubbles);
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onDestroyed(void)
	{	
		M3D_Form::onDestroyed();
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onActivated(ActivationEventArgs& e)
	{
		M3D_Form::onActivated(e);

		d_menu->activate();
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onDeactivated(ActivationEventArgs& e)
	{
		M3D_Form::onDeactivated(e);
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onActionStart(void)
	{
		M3D_Form::onActionStart();
	}

	void FormLanguage::onActionEnd(void)
	{
		M3D_Form::onActionEnd();
	}

	//----------------------------------------------------------------------------//
	void FormLanguage::onCharacter(KeyEventArgs& e)
	{
		if (isDisabled() || !isActive())
			return;

		switch (e.codepoint) 
		{
		case M3D_UI_KEY_RETURN:
			{
				getApp()->transitionForm(FrmMain_ID, getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
			}
			break;/*
		case M3D_UI_KEY_SEARCH:
			{	
				M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
				mlog->setParamInt("Type", REQDB_TYPE_PINYIN);
				mlog->setParamInt("SubType", 0);
				mlog->setParamInt("Position", 0);
				mlog->setParamString("StrPara", "");

				getApp()->transitionForm(FrmSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
			}
			break;
		case M3D_UI_KEY_FAVO:
			{
				getApp()->transitionForm(FrmFavoSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
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
	void FormLanguage::handleMenuClicked(M3D_Item *item, int position)
	{
		if(position >= 0 && position < Item_Count)
		{
			M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
			mlog->setParamInt("Type", REQDB_TYPE_LANGUAGE_SONG);
			mlog->setParamInt("SubType", SubType[position]);
			mlog->setParamInt("Position", 0);
			mlog->setParamString("StrPara", "");

			getApp()->transitionForm(FrmSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
	}
}
