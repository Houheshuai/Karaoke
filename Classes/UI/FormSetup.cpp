//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormSetup.cpp
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
#include "FormSetup.h"
#include "FormSetup.res.h"
#include "FormPlay.h"
//#include "FormOtherPlay.h"
#include "Widgets/M3D_PageListView.h"
//#include "Widgets/M3D_Item.h"
#include "Widgets/M3D_Label.h"
#include "Widgets/M3D_ListView.h"
#include "Widgets/M3D_ScrollBar.h"
#include "M3D_Config.h"

//----------------------------------------------------------------------------//
//	set music effect
//----------------------------------------------------------------------------//

static int BBEEffectStatus;
static int ReverbEffectStatus;
 int mainMenuNoFocus[12] = {0x2300, 0x2302, 0x2310, 0x2320, 0x2330, 0x2304, 
	0x2340, 0x2306, 0x2308, 0x230a, 0x2351};
 int mainMenuFocus[12] = {0x2301, 0x2303, 0x2315, 0x2325, 0x2335, 0x2305, 
	0x2345, 0x2307, 0x2309, 0x230b, 0x2356};

const int ReverbMenuNoFocus[4] = {0x2510, 0x2512, 0x2514};
const int ReverbMenuFocus[4] = {0x2511, 0x2525, 0x2515};

enum{
	Reverb_Effect_WetDry,
	Reverb_Effect_Pan,
	Reverb_Effect_Time,
	Reverb_Effect_I_Del,
	Reverb_Effect_DelRR,
	Reverb_Effect_LPF,
	Reverb_Effect_HPF,
	Reverb_Effect_Damp,
	Reverb_Effect_TYPE,
	Reverb_Effect_RSize,
	Reverb_Effect_Count,
};

enum REVERB_PAR
{
	REVERB_PAR_VOLUME,
	REVERB_PAR_PAN,
	REVERB_PAR_TIME,
	REVERB_PAR_DELAY,
	REVERB_PAR_DELAYFB,
	REVERB_PAR_LPF = 7,
	REVERB_PAR_HPF,
	REVERB_PAR_LOHIDAMP,
	REVERB_PAR_TYPE,
	REVERB_PAR_ROOMSIZE,
};

struct PAR
{
   int Par;
   int Val;
};

struct DataConfig{
	int curvalue;
	int defvalue;
	int minvalue;
	int maxvalue;
	int type;
};

DataConfig ReverbEffectConfig[Reverb_Effect_Count] = 
{
	{80, 80, 0, 127, REVERB_PAR_VOLUME},
	{64, 64, 0, 127, REVERB_PAR_PAN},
	{63, 63, 0, 127, REVERB_PAR_TIME},
	{24, 24, 0, 127, REVERB_PAR_DELAY},
	{0, 0, 0, 127, REVERB_PAR_DELAYFB},
	{4002, 4002, 20, 26000, REVERB_PAR_LPF},
	{27, 27, 20, 20000, REVERB_PAR_HPF},
	{83, 83, 64, 127, REVERB_PAR_LOHIDAMP},
	{1, 1, 0, 1, REVERB_PAR_TYPE},
	{64, 64, 0, 127, REVERB_PAR_ROOMSIZE},
};

const int ReverbEffectPreset[4][12] = {
	{84, 64, 43, 24, 0, 4002, 27, 83, 1, 65},
	{95, 64, 23, 60, 71, 14722, 21, 64, 1, 64},
	{103, 64, 51, 10, 0, 25040, 81, 78, 1, 64},
	{76, 64, 31, 0, 0, 25040, 21, 106, 1, 30},
};

enum {
	IMAGE_BBE_OFF_UNFOCUS_ID = 0x2320,
	IMAGE_BBE_OFF_FOCUS_ID = 0x2325,
	IMAGE_BBE_ON_UNFOCUS_ID = 0x2321,
	IMAGE_BBE_ON_FOCUS_ID = 0x2326,
	IMAGE_CHORUSEFFECT_OFF_UNFOCUS_ID = 0x2330,
	IMAGE_CHORUSEFFECT_OFF_FOCUS_ID = 0x2335,
	IMAGE_CHORUSEFFECT_DUET_UNFOCUS_ID = 0x2331,
	IMAGE_CHORUSEFFECT_DUET_FOCUS_ID = 0x2336,
	IMAGE_CHORUSEFFECT_GROUP_UNFOCUS_ID = 0x2332,
	IMAGE_CHORUSEFFECT_GROUP_FOCUS_ID = 0x2337,
	IMAGE_BGTYPE_PICTURE_UNFOCUS_ID = 0x2350,
	IMAGE_BGTYPE_VIDEO_UNFOCUS_ID,
	IMAGE_BGTYPE_CAMERA_UNFOCUS_ID,
	IMAGE_BGTYPE_PICTURE_FOCUS_ID = 0x2355,
	IMAGE_BGTYPE_VIDEO_FOCUS_ID,
	IMAGE_BGTYPE_CAMERA_FOCUS_ID,

	IMAGE_SCROLLBAR_LINE_ENABLE_ID = 0x2410,
	IMAGE_SCROLLBAR_LINE_DISABLE_ID,
	IMAGE_SCROLLBAR_MOVEBALL_UNFOCUS_ID,
	IMAGE_SCROLLBAR_MOVEBALL_FOCUS_ID,
	IMAGE_SCROLLBAR_MOVEBALL_DISABLE_ID,
	IMAGE_SCROLLBAR_BG_UNFOCUS_ID,
	IMAGE_SCROLLBAR_BG_FOCUS_ID,
	IMAGE_SCROLLBAR_BG_DISABLE_ID,
	IMAGE_SCROLLBAR_MOVE_UNFOCUS_ID,
	IMAGE_SCROLLBAR_MOVE_FOCUS_ID,
	IMAGE_SCROLLBAR_MOVE_DISABLE_ID,

	IMAGE_MICLIST_NAME_UNFOCUS_ID = 0x2420,
	IMAGE_MICLIST_NAME_FOCUS_ID = 0x2430,

	IMAGE_TUNNINGLIST_NAME_UNFOCUS_ID = 0x2440,
	IMAGE_TUNNINGLIST_NAME_FOCUS_ID = 0x2450,

	IMAGE_REVERBSETTINGLIST_PRESET_TYPE_ID = 0x2461,

	IMAGE_REVERBSETTINGLIST_NAME_UNFOCUS_ID = 0x2470,
	IMAGE_REVERBSETTINGLIST_NAME_FOCUS_ID = 0x2480,
	IMAGE_REVERBSETTINGLIST_NAME_DISABLE_ID = 0x2490,

	IMAGE_BBESETTINGLIST_NAME_UNFOCUS_ID = 0x24a0,
	IMAGE_BBESETTINGLIST_NAME_FOCUS_ID = 0x24b0,

	IMAGE_WIRELESSMICLIST_NAME_UNFOCUS_ID = 0x24c0,
	IMAGE_WIRELESSMICLIST_NAME_FOCUS_ID = 0x24d0,

};

namespace	CEGUI
{	
static const int BGTypeImage_ID = 0x2169;
static const int FontTypeImage_ID = 0x21d0;
static const int SwitchImage_ID = 0x2171;
static const int BBEImage_ID = 0x2540;
static const int ReverbImage_ID = 0x2560;

enum{
	Preset_Off,
	Preset_1,
	Preset_2,
	Preset_3,
	Preset_4,
};
enum{
	Scrollbar_ID = 1
};

/*
enum{
	ACTIVEWND_MENU,
	ACTIVEWND_BG,
	ACTIVEWND_FONT,
	ACTIVEWND_BBE,
	ACTIVEWND_REVERB,
};
/*
enum{
	BG_ID,
	FONT_ID,
	CENTER_ID,
	TITLE_ID,
	RANDOM_ID,
	BBE_ID,
	REVERB_ID,
};*/
enum{
	PRESETS_ID,
	SETTINGS_ID,
	DEFAULT_ID
};
enum{
	ACTIVEWND_MIC,
	ACTIVEWND_TUNNING,
	ACTIVEWND_REVERB,
	ACTIVEWND_BBE,
	ACTIVEWND_CHORUS,
	ACTIVEWND_WIRE,
	ACTIVEWND_LYRICS,
	ACTIVEWND_SCORE,
	ACTIVEWND_TITLE,
	ACTIVEWND_AGC,
	ACTIVEWND_BG,
	ACTIVEWND_MENU,
	ACTIVEWND_PRE,
	ACTIVEWND_REVSET,
	ACTIVEWND_BBESET,
};
enum{
	MIC_ID,
	TUNNING_ID,
	REVERB_ID,
	BBE_ID,
	CHORUS_ID,
	WIRE_ID,
	LYRICS_ID,
	SCORE_ID,
	TITLE_ID,
	AGC_ID,
	BG_ID,
};
/*
enum{
	Video_ID,
	Pic_ID,
	MyVideo_ID,
	MyPic_ID,
};
*/
enum{
	Default_ID,
	Segoe_ID,
	Roman_ID,
};

enum{
	BBEOFF_ID,
	BBEON_ID,
	BBESETTINGS_ID,
};
enum {
	CHORUSOFF_ID,
	CHORUSDUET_ID,
	CHORUSGROUP_ID
};
enum{
	Picture_ID,
	Video_ID,
	Camera_ID,
};
static const char* Item_Name[] = {
	"BGType",
	"FontType",
	"Center",
	"Title",
	"Random",
};

static String SetupReturnTimer("SetupReturnTimer");

const String FormSetup::EventNamespace("FormSetup");
const String FormSetup::WidgetTypeName("FormSetup");

//----------------------------------------------------------------------------//
FormSetup::FormSetup(const String& type, const String& name):
M3D_Form(type, name)
{
	d_scoreClicked = 0;
	d_titleClicked = 0;
	d_agcClicked = 0;
}

//----------------------------------------------------------------------------//
FormSetup::~FormSetup(void)
{

}
//----------------------------------------------------------------------------//

void FormSetup::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormSetup::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormSetup::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);
	
	resetTimer(SetupReturnTimer);
}

//----------------------------------------------------------------------------//
void FormSetup::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormSetup::onCreated(void)
{
	M3D_Form::onCreated();
		
	d_menu = static_cast<M3D_PageListView *>(getChild(Res_FormSetup::Menu));
	d_menu->setCircleEnable(false);
	d_menu->setFocusBarResID(Res_FormSetup::MenuFocusBar);
	d_menu->setOnFocusChangeListener(CALLBACK_2(FormSetup::handleMenuFoucusChange, this));
	d_menu->setOnClickListener(CALLBACK_2(FormSetup::handleMenuClicked, this));
	
	d_menufocusbar = static_cast<M3D_Label*>(d_menu->getChild(Res_FormSetup::MenuFocusBar));

	d_MICMenu = static_cast<M3D_PageListView *>(getChild(Res_FormSetup::MICMenu));
	d_MICMenu->setCircleEnable(false);
	d_MICMenu->setFocusBarResID(Res_FormSetup::MICMenuFocusBar);
	
	d_MICMenu->setOnFocusChangeListener(CALLBACK_2(FormSetup::handleMicListFoucusChange, this));
	
	d_micMenuFocusBar = static_cast<M3D_Label*>(d_MICMenu->getChild(Res_FormSetup::MICMenuFocusBar));
	d_micMenuFocusBar->hide();

	d_tuningMenu = static_cast<M3D_PageListView *>(getChild(Res_FormSetup::TuningMenu));
	d_tuningMenu->setCircleEnable(false);
	d_tuningMenu->setFocusBarResID(Res_FormSetup::TunMenuFocusBar);
	d_tuningMenuFocusBar = static_cast<M3D_Label*>(d_tuningMenu->getChild(Res_FormSetup::TunMenuFocusBar));
	d_tuningMenuFocusBar->hide();

	d_reverbMenu = static_cast<M3D_PageListView *>(getChild(Res_FormSetup::ReverbMenu));
	d_reverbMenu->setCircleEnable(false);
	d_reverbMenu->setFocusBarResID(Res_FormSetup::RevMenuFocusbar);
	d_reverbMenu->setOnFocusChangeListener(CALLBACK_2(FormSetup::handleReverbMenuFoucusChange, this));
	d_reverbMenu->setOnClickListener(CALLBACK_2(FormSetup::handleReverbMenuClicked, this));
	d_reverbMenuFocusBar = static_cast<M3D_Label*>(d_reverbMenu->getChild(Res_FormSetup::RevMenuFocusbar));
	d_reverbMenuFocusBar->hide();

	d_presetsMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::PresetsMenu));
	d_presetsMenu->setCircleEnable(false);
	d_presetsMenu->setFocusBarResID(Res_FormSetup::PreMenuFocusBar);
	d_presetsMenu->hide();
	d_presetMenuFocusBar = static_cast<M3D_Label*>(d_presetsMenu->getChild(Res_FormSetup::PreMenuFocusBar));
	d_presetMenuFocusBar->hide();

	d_RevSetMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::RevSetMenu));
	d_RevSetMenu->setCircleEnable(false);
	d_RevSetMenu->setFocusBarResID(Res_FormSetup::RevSetMenuFocusBar);
	d_RevSetMenu->hide();
	d_RevSetMenuFocusBar = static_cast<M3D_Label*>(d_RevSetMenu->getChild(Res_FormSetup::RevSetMenuFocusBar));
	d_RevSetMenuFocusBar->hide();

	d_BBEMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::BBEMenu));
	d_BBEMenu->setCircleEnable(false);
	d_BBEMenu->setFocusBarResID(Res_FormSetup::BBEMenuFocusBar);
	d_BBEMenu->setOnFocusChangeListener(CALLBACK_2(FormSetup::handleBBEMenuFoucusChange, this));
	d_BBEMenu->setOnClickListener(CALLBACK_2(FormSetup::handleBBEMenuClicked, this));
	d_BBEMenu->hide();
	d_BBEMenuFocusBar = static_cast<M3D_Label*>(d_BBEMenu->getChild(Res_FormSetup::BBEMenuFocusBar));
	d_BBEMenuFocusBar->hide();

	d_BBeSetMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::BBESetMenu));
	d_BBeSetMenu->setCircleEnable(false);
	d_BBeSetMenu->setFocusBarResID(Res_FormSetup::BBESetMenuFocBar);
	d_BBeSetMenu->hide();
	d_BBeSetMenuFocusBar = static_cast<M3D_Label*>(d_BBeSetMenu->getChild(Res_FormSetup::BBESetMenuFocBar));
	d_BBeSetMenuFocusBar->hide();

	d_ChorusMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::ChorusMenu));
	d_ChorusMenu->setCircleEnable(false);
	d_ChorusMenu->setFocusBarResID(Res_FormSetup::ChorusMenuFocusBar);
	d_ChorusMenu->setOnClickListener(CALLBACK_2(FormSetup::handleChorusMenuClicked, this));
	d_ChorusMenu->hide();
	d_ChorusMenuFocusBar = static_cast<M3D_Label*>(d_ChorusMenu->getChild(Res_FormSetup::ChorusMenuFocusBar));
	d_ChorusMenuFocusBar->hide();

	d_wirelessMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::WirelessMenu));
	d_wirelessMenu->setCircleEnable(false);
	d_wirelessMenu->setFocusBarResID(Res_FormSetup::WireMenuFocBar);
	d_wirelessMenu->hide();
	d_wirelessMenuFocusBar = static_cast<M3D_Label*>(d_wirelessMenu->getChild(Res_FormSetup::WireMenuFocBar));
	d_wirelessMenuFocusBar->hide();

	d_lyricsMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::LyricsMenu));
	d_lyricsMenu->setCircleEnable(false);
	d_lyricsMenu->setFocusBarResID(Res_FormSetup::LyricsMenuFocBar);
	d_lyricsMenu->hide();
	d_lyricsMenuFocusBar = static_cast<M3D_Label*>(d_lyricsMenu->getChild(Res_FormSetup::LyricsMenuFocBar));
	d_lyricsMenuFocusBar->hide();

	d_BGMenu = static_cast<M3D_PageListView*>(getChild(Res_FormSetup::BGMenu));
	d_BGMenu->setCircleEnable(false);
	d_BGMenu->setFocusBarResID(Res_FormSetup::BGMenuFocBar);
	d_BGMenu->setOnClickListener(CALLBACK_2(FormSetup::handleBGMenuClicked, this));
	d_BGMenu->hide();
	d_BGMenuFocusBar = static_cast<M3D_Label*>(d_BGMenu->getChild(Res_FormSetup::BGMenuFocBar));
	d_BGMenuFocusBar->hide();

	initData();
	handleScoreClicked();
	handleTitleClicked();
	handleAgcClicked();
	createTimer(SetupReturnTimer, 15000, false, 0);
}

//----------------------------------------------------------------------------//
void FormSetup::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormSetup::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);
	
	d_menu->jumpToTop();
	d_menu->activate();
	d_selectedmenu = ACTIVEWND_MENU;
}

//----------------------------------------------------------------------------//
void FormSetup::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormSetup::onActionStart(void)
{
	M3D_Form::onActionStart();
}

void FormSetup::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormSetup::onTimeout(EventArgs& e)
{/*
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == SetupReturnTimer)
	{
		if(d_selectedmenu != ACTIVEWND_MENU)
		{
			switch(d_selectedmenu)
			{
			case ACTIVEWND_BG:
				d_bgfocusbar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				break;
			case ACTIVEWND_FONT:
				d_fontfocusbar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				break;
			case ACTIVEWND_BBE:
				d_bbefocusbar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				break;
			case ACTIVEWND_REVERB:
				d_reverbfocusbar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				break;
			default:
				break;
			}
		}
		handleExitSetup();
	}*/
}
//----------------------------------------------------------------------------//
void FormSetup::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{/*
	case M3D_UI_KEY_PLAY:
		//static_cast<appKRK*>(getApp())->playNextSong();
		getApp()->transitionForm(FrmPlay_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		break;*/
	case M3D_UI_KEY_RETURN:
		if(d_selectedmenu == ACTIVEWND_MENU)
		{
			M3D_Log* mlog = getApp()->getFormLog(getID());
			getApp()->transitionForm(FrmNumSong_ID, getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
			//handleExitSetup();
		}
		else
		{
			switch(d_selectedmenu)
			{
			case ACTIVEWND_MIC:
				d_micMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(MIC_ID))->setImage(mainMenuFocus[MIC_ID]);
				break;
			case ACTIVEWND_REVERB:
				d_reverbMenuFocusBar->hide();
				d_presetsMenu->hide();
				d_RevSetMenu->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(REVERB_ID))->setImage(mainMenuFocus[REVERB_ID]);
				break;
			case ACTIVEWND_TUNNING:
				d_tuningMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(TUNNING_ID))->setImage(mainMenuFocus[TUNNING_ID]);
				break;
			case ACTIVEWND_PRE:
				d_presetMenuFocusBar->hide();
				d_reverbMenuFocusBar->show();
				d_reverbMenu->activate();
				d_selectedmenu = ACTIVEWND_REVERB;
				break;
			case ACTIVEWND_BBE:
				d_BBEMenuFocusBar->hide();
				d_BBeSetMenu->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID))->setImage(mainMenuFocus[BBE_ID]);
				break;
			case ACTIVEWND_BBESET:
				d_BBeSetMenuFocusBar->hide();
				d_BBEMenuFocusBar->show();
				d_BBEMenu->activate();
				d_selectedmenu = ACTIVEWND_BBE;
				break;
			case ACTIVEWND_REVSET:
				d_RevSetMenuFocusBar->hide();
				d_reverbMenuFocusBar->show();
				d_reverbMenu->activate();
				d_selectedmenu = ACTIVEWND_REVERB;
				break;
			case ACTIVEWND_CHORUS:
				d_ChorusMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CHORUS_ID))->setImage(mainMenuFocus[CHORUS_ID]);
				break;
			case ACTIVEWND_WIRE:
				d_wirelessMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(WIRE_ID))->setImage(mainMenuFocus[WIRE_ID]);
				break;
			case ACTIVEWND_LYRICS:
				d_lyricsMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(LYRICS_ID))->setImage(mainMenuFocus[LYRICS_ID]);
				break;
			case ACTIVEWND_BG:
				d_BGMenuFocusBar->hide();
				d_menufocusbar->show();
				d_menu->activate();
				d_selectedmenu = ACTIVEWND_MENU;
				static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID))->setImage(mainMenuFocus[BG_ID]);
				break;
			default:
				break;
			}
		}
		break;
	case M3D_UI_KEY_LEFT:
	{
		if (d_selectedmenu == ACTIVEWND_MIC) {
			handleMicListOnCharacter(e);
		}
	}
		break;
	case M3D_UI_KEY_RIGHT:
		{

		}
		break;
	case M3D_UI_KEY_STOP:
		{
			appKRK* app = static_cast<appKRK*>(getApp());
			//app->stop();
		}
	default:
		break;
	}
		
	M3D_Form::onCharacter(e);
}

//----------------------------------------------------------------------------//
void FormSetup::anyKeyDown(void)
{
	resetTimer(SetupReturnTimer);
}

//----------------------------------------------------------------------------//
void FormSetup::initData(void)
{
	MKConfig* config = MKConfig::getSingletonPtr();

	int value = config->getValue("BGType");
	M3D_Label* label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID)->getChildAtIdx(0));
	//label->setImage(BGTypeImage_ID + value);

	value = config->getValue("FontFiles");
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(FONT_ID)->getChildAtIdx(0));
	//label->setImage(FontTypeImage_ID + value);
		
	value = config->getValue("Center");
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CENTER_ID)->getChildAtIdx(1));
	//label->setImage(SwitchImage_ID - value);
		
	value = config->getValue("Title");
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(TITLE_ID)->getChildAtIdx(1));
	//label->setImage(SwitchImage_ID - value);
		
	value = config->getValue("Random");
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(RANDOM_ID)->getChildAtIdx(1));
	//label->setImage(SwitchImage_ID - value);
	
	value = BBEEffectStatus;
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID)->getChildAtIdx(0));
	//label->setImage(BBEImage_ID + value);
	
	value = ReverbEffectStatus;
	//label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(REVERB_ID)->getChildAtIdx(0));
	//label->setImage(ReverbImage_ID + value);
	
}

//----------------------------------------------------------------------------//
void FormSetup::handleMenuFoucusChange(M3D_Item *item, int position)
{
	for (int i = 0; i < 11; ++i) {
		M3D_DebugPrint("----------%d-----------", d_menu->getChildCount());
		if (i != position)
			static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(i))->setImage(mainMenuNoFocus[i]);
			//static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID)->getChildAtIdx(0))->setBGImage(mainMenuFocus[BG_ID]);
		else
			static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(i))->setImage(mainMenuFocus[i]);
	}
	d_MICMenu->hide();
	d_tuningMenu->hide();
	d_reverbMenu->hide();
	d_BBEMenu->hide();
	d_ChorusMenu->hide();
	d_wirelessMenu->hide();
	d_lyricsMenu->hide();
	d_BGMenu->hide();
	switch (position)
	{
	case MIC_ID:
		d_MICMenu->show();
		break;
	case TUNNING_ID:
		d_tuningMenu->show();
		break;
	case REVERB_ID:
		d_reverbMenu->show();
		break;
	case BBE_ID:
		d_BBEMenu->show();
		break;
	case CHORUS_ID:
		d_ChorusMenu->show();
		break;
	case WIRE_ID:
		d_wirelessMenu->show();
		break;
	case LYRICS_ID:
		d_lyricsMenu->show();
		break;
	case BG_ID:
		d_BGMenu->show();
		break;
	default:
		break;
	}
}

void FormSetup::handleMenuClicked(M3D_Item *item, int position)
{		
	switch (position)
	{
	case MIC_ID:
		d_menufocusbar->hide();
		d_micMenuFocusBar->show();
		d_MICMenu->jumpToTop();
		d_MICMenu->activate();
		d_selectedmenu = ACTIVEWND_MIC;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(MIC_ID))->setImage(mainMenuNoFocus[MIC_ID]);
		break;
	case TUNNING_ID:
		d_menufocusbar->hide();
		d_tuningMenuFocusBar->show();
		d_tuningMenu->jumpToTop();
		d_tuningMenu->activate();
		d_selectedmenu = ACTIVEWND_TUNNING;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(TUNNING_ID))->setImage(mainMenuNoFocus[TUNNING_ID]);
		break;
	case REVERB_ID:
		d_menufocusbar->hide();
		d_reverbMenuFocusBar->show();
		d_reverbMenu->jumpToTop();
		d_reverbMenu->activate();
		d_selectedmenu = ACTIVEWND_REVERB;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(REVERB_ID))->setImage(mainMenuNoFocus[REVERB_ID]);
		break;
	case BBE_ID:
		d_menufocusbar->hide();
		d_BBEMenuFocusBar->show();
		d_BBEMenu->jumpToTop();
		d_BBEMenu->activate();
		d_selectedmenu = ACTIVEWND_BBE;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID))->setImage(mainMenuNoFocus[BBE_ID]);
		break;
	case CHORUS_ID:
		d_menufocusbar->hide();
		d_ChorusMenuFocusBar->show();
		d_ChorusMenu->jumpToTop();
		d_ChorusMenu->activate();
		d_selectedmenu = ACTIVEWND_CHORUS;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CHORUS_ID))->setImage(mainMenuNoFocus[CHORUS_ID]);
		break;
	case SCORE_ID:
		handleScoreClicked();
		break;
	case TITLE_ID:
		handleTitleClicked();
		break;
	case AGC_ID:
		handleAgcClicked();
		break;
	case WIRE_ID:
		d_menufocusbar->hide();
		d_wirelessMenuFocusBar->show();
		d_wirelessMenu->jumpToTop();
		d_wirelessMenu->activate();
		d_selectedmenu = ACTIVEWND_WIRE;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(WIRE_ID))->setImage(mainMenuNoFocus[WIRE_ID]);
		break;
	case LYRICS_ID:
		d_menufocusbar->hide();
		d_lyricsMenuFocusBar->show();
		d_lyricsMenu->jumpToTop();
		d_lyricsMenu->activate();
		d_selectedmenu = ACTIVEWND_LYRICS;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(LYRICS_ID))->setImage(mainMenuNoFocus[LYRICS_ID]);
		break;
	case BG_ID:
		d_menufocusbar->hide();
		d_BGMenuFocusBar->show();
		d_BGMenu->jumpToTop();
		d_BGMenu->activate();
		d_selectedmenu = ACTIVEWND_BG;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID))->setImage(mainMenuNoFocus[BG_ID]);
		break;
		/*
			break;
		case CENTER_ID:
		case TITLE_ID:
		case RANDOM_ID:
			{
				MKConfig* config = MKConfig::getSingletonPtr();
				int value = config->getValue(Item_Name[position]);
				M3D_CHANGEVALUE(value, 1);
				config->setValue(Item_Name[position], value);
				M3D_Label * label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(position)->getChildAtIdx(1));
				label->setImage(SwitchImage_ID - value);
				handleOptionChange(position);
			}
			break;*/
		default:
			break;
	}
}

//----------------------------------------------------------------------------//
void FormSetup::handleBGTypeClicked(M3D_Item *item, int position)
{		/*
	MKConfig* config = MKConfig::getSingletonPtr();
	int LastBGType = config->getValue("BGType");
		
	switch (position)
	{
		case Video_ID:
		case MyVideo_ID:
			if(LastBGType == Pic_ID || LastBGType == MyPic_ID || LastBGType != position)
			{
				appKRK* app = static_cast<appKRK*>(getApp());
				app->stopUIbg();
				
				config->setValue("BGType", position);
				app->playUIbg();
			}
			break;
		case Pic_ID:
		case MyPic_ID:
			if(LastBGType == Video_ID || LastBGType == MyVideo_ID || LastBGType != position)
			{
				appKRK* app = static_cast<appKRK*>(getApp());
				app->stopUIbg();
				
				config->setValue("BGType", position);
				app->playUIbg();
			}
			break;
		default:
			break;
	}
	
	M3D_Label* label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID)->getChildAtIdx(0));
	if(position < 2)
		label->setImage(BGTypeImage_ID + position);
	else
		label->setImage(BGTypeImage_ID + position + 1);*/
}

//----------------------------------------------------------------------------//
void FormSetup::handleFontTypeClicked(M3D_Item *item, int position)
{		/*
	MKConfig* config = MKConfig::getSingletonPtr();
	int LastFontType = config->getValue("FontFiles");
	config->setValue("FontFiles", position);
	
	MKPlayer* player = MKPlayer::getSingletonPtr();
	switch (position)
	{
		case Default_ID:
			player->setLyricFont("ArialUni");
			break;
		case Segoe_ID:
			player->setLyricFont("Segoe");
			break;
		case Roman_ID:
			player->setLyricFont("Times");
			break;
		default:
			break;
	}
	
	M3D_Label* label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(FONT_ID)->getChildAtIdx(0));
	label->setImage(FontTypeImage_ID + position);*/
}

	
//----------------------------------------------------------------------------//
void FormSetup::handleBBEListClicked(M3D_Item *item, int position)
{/*
	MKPlayer* player = MKPlayer::getSingletonPtr();
	if(player)
	{
		if(position == Preset_Off)
		{
			if(BBEEffectStatus != Preset_Off)
			{
				player->setVol(PLY_CMD_SET_BBE_EN, 0);
				BBEEffectStatus = Preset_Off;
			}
		}
		else
		{
			if(BBEEffectStatus == Preset_Off)
			{
				player->setVol(PLY_CMD_SET_BBE_EN, 1);
			}
			if(BBEEffectStatus != position)
			{
				player->setVol(PLY_CMD_SET_BBE_LEVEL, 40 * position);
				BBEEffectStatus = position;
			}
		}
		M3D_Label* label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID)->getChildAtIdx(0));
		label->setImage(BBEImage_ID + position);
	}*/
}

//----------------------------------------------------------------------------//
void FormSetup::handleReverbListClicked(M3D_Item *item, int position)
{/*
	MKPlayer* player = MKPlayer::getSingletonPtr();
	if(player)
	{
		if(position == Preset_Off)
		{
			if(ReverbEffectStatus != Preset_Off)
			{
				player->setVol(PLY_CMD_SET_REVERB_ENABLE, 0);
				ReverbEffectStatus = Preset_Off;
			}
		}
		else
		{
			if(ReverbEffectStatus == Preset_Off)
			{
				player->setVol(PLY_CMD_SET_REVERB_ENABLE, 1);
			}
			if(ReverbEffectStatus != position)
			{
				for(int i = Reverb_Effect_WetDry; i < Reverb_Effect_Count; i++)
				{
					ReverbEffectConfig[i].curvalue = ReverbEffectPreset[position - Preset_1][i];
					PAR para = {ReverbEffectConfig[i].type, ReverbEffectConfig[i].curvalue};	
					player->setVol(PLY_CMD_SET_REVERB_CHANGE_PAR, (int)&para);
				}
				ReverbEffectStatus = position;
			}
		}
		M3D_Label* label = static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(REVERB_ID)->getChildAtIdx(0));
		label->setImage(ReverbImage_ID + position);
	}*/
}

//----------------------------------------------------------------------------//
void FormSetup::handleOptionChange(int type)
{/*
	MKConfig* config = MKConfig::getSingletonPtr();
	M3D_Log* log = getApp()->getFormLog(getID());
	int lastFormID = log->getParamInt("LastForm", 0);
	switch(type)
	{
	case CENTER_ID:
		if(lastFormID == FrmPlay_ID)
		{
			appKRK *app = (appKRK *)getApp();
			app->setLyricStatus(config->getValue(Item_Name[CENTER_ID]));
		}
		break;
	case TITLE_ID:
		if(lastFormID == FrmPlay_ID)
		{
			FormPlay* form = static_cast<FormPlay*>(getApp()->getForm(FrmPlay_ID));
			form->setTitleStatus(config->getValue(Item_Name[TITLE_ID]));
		}
	default:
		break;
	}*/
}

//----------------------------------------------------------------------------//
void FormSetup::handleExitSetup(void)   //¼¸ÃëºóÒþ²Ø
{
	appKRK* app = static_cast<appKRK*>(getApp());/*
	if(app->getPlayState() == PLY_EVENT_GETSTATE_STATE_STOPPED)
	{
		app->transitionForm(FrmNumSong_ID, getID(), FORM_TRANSITION_ANIMATION::ANIMATION_NONE, false);
	}
	else
	{
		app->hideForm(FrmSetup_ID);/*
		getApp()->getForm(FrmPlay_ID)->activate();
	}*/
}
void FormSetup::handleReverbMenuFoucusChange(M3D_Item *item, int position)
{/*
	for (int i = 0; i < 3; ++i) {
		
		if (i != position)
			static_cast<M3D_Label*>(d_ReverbMenu->getChildAtIdx(0)->getChildAtIdx(i)->getChildAtIdx(0))->setImage(ReverbMenuNoFocus[i]);
		else
			static_cast<M3D_Label*>(d_ReverbMenu->getChildAtIdx(0)->getChildAtIdx(i)->getChildAtIdx(0))->setImage(ReverbMenuFocus[i]);
	}*/
	d_presetsMenu->hide();
	d_RevSetMenu->hide();
	switch (position)
	{
	case PRESETS_ID:
		d_presetsMenu->show();
		break;
	case SETTINGS_ID:
		d_RevSetMenu->show();
		break;
	default:
		break;
	}
}


void FormSetup::handleReverbMenuClicked(M3D_Item *item, int position)
{
	switch (position)
	{
	case PRESETS_ID:
		d_reverbMenuFocusBar->hide();
		d_presetMenuFocusBar->show();
		d_presetsMenu->show();
		d_presetsMenu->jumpToTop();
		d_presetsMenu->activate();
		d_selectedmenu = ACTIVEWND_PRE;
		break;
	case SETTINGS_ID:
		d_reverbMenuFocusBar->hide();
		d_RevSetMenuFocusBar->show();
		d_RevSetMenu->jumpToTop();
		d_RevSetMenu->activate();
		d_selectedmenu = ACTIVEWND_REVSET;
		break;
	default:
		break;
	}
}

void FormSetup::handleBBEMenuFoucusChange(M3D_Item *item, int position)
{
	d_BBeSetMenu->hide();
	switch (position)
	{
	case BBESETTINGS_ID:
		d_BBeSetMenu->show();
		break;
	default:
		break;
	}
}

void FormSetup::handleBBEMenuClicked(M3D_Item *item, int position)
{
	switch (position)
	{
	case BBESETTINGS_ID:
		d_BBEMenuFocusBar->hide();
		d_BBeSetMenuFocusBar->show();
		d_BBeSetMenu->jumpToTop();
		d_BBeSetMenu->activate();
		d_selectedmenu = ACTIVEWND_BBESET;
		break;
	case BBEON_ID:
		mainMenuFocus[BBE_ID] = IMAGE_BBE_ON_FOCUS_ID;
		mainMenuNoFocus[BBE_ID] = IMAGE_BBE_ON_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID))->setImage(mainMenuNoFocus[BBE_ID]);
		break;
	case BBEOFF_ID:
		mainMenuFocus[BBE_ID] = IMAGE_BBE_OFF_FOCUS_ID;
		mainMenuNoFocus[BBE_ID] = IMAGE_BBE_OFF_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BBE_ID))->setImage(mainMenuNoFocus[BBE_ID]);
		break;
	default:
		break;
	}
}
void FormSetup::handleScoreClicked(void)
{
	static_cast<M3D_ListView*>(d_menu->getChildAtIdx(0)->getChildAtIdx(SCORE_ID)->getChildAtIdx(1))->setImage(0x2390 + d_scoreClicked);
	d_scoreClicked = !d_scoreClicked;
}

void FormSetup::handleTitleClicked(void)
{
	static_cast<M3D_ListView*>(d_menu->getChildAtIdx(0)->getChildAtIdx(TITLE_ID)->getChildAtIdx(1))->setImage(0x2390 + d_titleClicked);
	d_titleClicked = !d_titleClicked;
}

void FormSetup::handleAgcClicked(void)
{
	static_cast<M3D_ListView*>(d_menu->getChildAtIdx(0)->getChildAtIdx(AGC_ID)->getChildAtIdx(1))->setImage(0x2390 + d_agcClicked);
	d_agcClicked = !d_agcClicked;
}
//----------------------------------------------------------------------------//
void FormSetup::handleMicListFoucusChange(M3D_Item *item, int position)
{
	//M3D_ListView *view = static_cast<M3D_ListView*>(d_MICMenu->getFocusItem());//   getLastFocusView();
	
	//if(view)
	{
		//static_cast<M3D_Item *>(view->getChild(Name_ID))->setBgImage(IMAGE_MICLIST_NAME_UNFOCUS_ID + view->getID() - 1);
		//static_cast<M3D_Item *>(view->getChild(ScrollbarBG_ID))->setBgImage(IMAGE_SCROLLBAR_BG_UNFOCUS_ID);
		M3D_ScrollBar* scrollbar = static_cast<M3D_ScrollBar *>(d_MICMenu->getChildAtIdx(0)->getChildAtIdx(position)->getChildAtIdx(1));  //view->getChildAtIdx(Scrollbar_ID));
		static_cast<M3D_Label *>(scrollbar->getChildAtIdx(0))->setImage(IMAGE_SCROLLBAR_MOVEBALL_UNFOCUS_ID);
		scrollbar->setBGImage(IMAGE_SCROLLBAR_MOVE_UNFOCUS_ID);
		//view->getChild(Line_ID)->hide();
	}
	/*
	view = d_miclist->getFocusView();
	if(view)
	{
		static_cast<Window_3D*>(view->getChild(Name_ID))->setBgImage(IMAGE_MICLIST_NAME_FOCUS_ID + view->getID() - 1);
		static_cast<Window_3D*>(view->getChild(ScrollbarBG_ID))->setBgImage(IMAGE_SCROLLBAR_BG_FOCUS_ID);
		M3D_ScrollBar* scrollbar = static_cast<M3D_ScrollBar *>(view->getChild(ScrollbarBG_ID)->getChild(Scrollbar_ID));
		static_cast<Window_3D*>(scrollbar->getChildAtIdx(0))->setBgImage(IMAGE_SCROLLBAR_MOVEBALL_FOCUS_ID);
		scrollbar->setMoveImg(IMAGE_SCROLLBAR_MOVE_FOCUS_ID);
		view->getChild(Line_ID)->show();
	}
	return true;*/
}
bool FormSetup::handleMicListOnCharacter(const CEGUI::EventArgs& e)
{
	//if(d_activeWndID != MicList_ID)
		//return false;

	//Window_3D* focusView = d_miclist->getFocusView();
	//if(focusView == NULL)
		//return false;
	int position = d_MICMenu->getFocusDataIndex();
	M3D_ScrollBar* scrollbar = static_cast<M3D_ScrollBar *>(d_MICMenu->getChildAtIdx(0)->getChildAtIdx(position)->getChildAtIdx(1));
	//M3D_ScrollBar* scrollbar = static_cast<M3D_ScrollBar *>(focusView->getChild(ScrollbarBG_ID)->getChild(Scrollbar_ID));
	KeyEventArgs& ke = (KeyEventArgs&)e;

	//if(ke.codepoint == M3D_UI_KEY_LEFT || ke.codepoint == M3D_UI_KEY_RIGHT)
		scrollbar->onCharacter(ke);
	//else
		//onCharacter(ke);

	return true;
}
void FormSetup::handleBGMenuClicked(M3D_Item *item, int position)
{		
	switch (position)
	{
	case Picture_ID:
		mainMenuFocus[BG_ID] = IMAGE_BGTYPE_PICTURE_FOCUS_ID;
		mainMenuNoFocus[BG_ID] = IMAGE_BGTYPE_PICTURE_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID))->setImage(mainMenuNoFocus[BG_ID]);
		break;
	case Video_ID:
		mainMenuFocus[BG_ID] = IMAGE_BGTYPE_VIDEO_FOCUS_ID;
		mainMenuNoFocus[BG_ID] = IMAGE_BGTYPE_VIDEO_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID))->setImage(mainMenuNoFocus[BG_ID]);
		break;
	case Camera_ID:
		mainMenuFocus[BG_ID] = IMAGE_BGTYPE_CAMERA_FOCUS_ID;
		mainMenuNoFocus[BG_ID] = IMAGE_BGTYPE_CAMERA_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(BG_ID))->setImage(mainMenuNoFocus[BG_ID]);
		break;
	default:
		break;
	}
}

void FormSetup::handleChorusMenuClicked(M3D_Item *item, int position)
{
	switch (position) {
	case CHORUSOFF_ID:
		mainMenuFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_OFF_FOCUS_ID;
		mainMenuNoFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_OFF_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CHORUS_ID))->setImage(mainMenuNoFocus[CHORUS_ID]);
		break;
	case CHORUSDUET_ID:
		mainMenuFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_DUET_FOCUS_ID;
		mainMenuNoFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_DUET_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CHORUS_ID))->setImage(mainMenuNoFocus[CHORUS_ID]);
		break;
	case CHORUSGROUP_ID:
		mainMenuFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_GROUP_FOCUS_ID;
		mainMenuNoFocus[CHORUS_ID] = IMAGE_CHORUSEFFECT_GROUP_UNFOCUS_ID;
		static_cast<M3D_Label*>(d_menu->getChildAtIdx(0)->getChildAtIdx(CHORUS_ID))->setImage(mainMenuNoFocus[CHORUS_ID]);
		break;
	default:
		break;
	}
}

}