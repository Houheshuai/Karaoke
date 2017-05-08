//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormSetup.h
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
#pragma once

#ifndef _FORMSETUP_H_
#define _FORMSETUP_H_

#include "Widgets/M3D_Form.h"


namespace CEGUI
{
class M3D_PageListView;
class M3D_Item;
class M3D_Label;
class FormSetup:public M3D_Form
{
public:

	FormSetup(const String& type, const String& name);
	virtual ~FormSetup(void);

	static const String EventNamespace; 			//!< Namespace for global events
	static const String WidgetTypeName; 			//!< Window factory name


	virtual void constructWindow(WndRes_t *wndRes);
	virtual void destructWindow(void);

    virtual void onShown(WindowEventArgs& e);
	virtual void onHidden(WindowEventArgs& e);

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void onActionStart(void);
	virtual void onActionEnd(void); 
	
	virtual void onTimeout(EventArgs& e);

	virtual void onCharacter(KeyEventArgs& e);
	
	virtual void anyKeyDown(void);

private:
	void initData(void);
	
	void handleMenuFoucusChange(M3D_Item *item, int position);
	void handleMenuClicked(M3D_Item *item, int position);
	void handleBGTypeClicked(M3D_Item *item, int position);
	void handleFontTypeClicked(M3D_Item *item, int position);
	void handleBBEListClicked(M3D_Item *item, int position);
	void handleReverbListClicked(M3D_Item *item, int position);
	void handleOptionChange(int type);
	void handleExitSetup(void);
	void handleReverbMenuFoucusChange(M3D_Item *item, int position);
	void handleReverbMenuClicked(M3D_Item *item, int position);
	void handleBBEMenuClicked(M3D_Item *item, int position);
	void handleBBEMenuFoucusChange(M3D_Item *item, int position);
	void handleScoreClicked(void);
	void handleTitleClicked(void);
	void handleAgcClicked(void);
	
	bool handleMicListFocusChange(M3D_Item *item, int position);
	void handleMicListFoucusChange(M3D_Item *item, int position);
	bool handleMicListOnCharacter(const CEGUI::EventArgs& e);
	void handleBGMenuClicked(M3D_Item *item, int position);
	void handleChorusMenuClicked(M3D_Item *item, int position);

	M3D_PageListView*	d_menu;
	M3D_Label*			d_menufocusbar;
	M3D_Label*			d_micMenuFocusBar;
	M3D_PageListView*	d_MICMenu;
	M3D_PageListView*	d_tuningMenu;
	M3D_PageListView*	d_reverbMenu;
	M3D_Label*			d_reverbMenuFocusBar;
	M3D_Label*			d_tuningMenuFocusBar;

	M3D_PageListView*	d_presetsMenu;
	M3D_Label*			d_presetMenuFocusBar;

	M3D_PageListView*	d_BBEMenu;
	M3D_Label*			d_BBEMenuFocusBar;

	M3D_PageListView*	d_RevSetMenu;
	M3D_Label*			d_RevSetMenuFocusBar;

	M3D_PageListView*	d_BBeSetMenu;
	M3D_Label*			d_BBeSetMenuFocusBar;

	M3D_PageListView*	d_ChorusMenu;
	M3D_Label*			d_ChorusMenuFocusBar;

	M3D_PageListView*	d_wirelessMenu;
	M3D_Label*			d_wirelessMenuFocusBar;

	M3D_PageListView*	d_lyricsMenu;
	M3D_Label*			d_lyricsMenuFocusBar;

	M3D_PageListView*	d_BGMenu;
	M3D_Label*			d_BGMenuFocusBar;

	M3D_PageListView*	d_bgtype;
	M3D_Label*			d_bgfocusbar;
	M3D_PageListView*	d_fonttype;
	M3D_Label*			d_fontfocusbar;
	M3D_PageListView*	d_bbelist;
	M3D_Label*			d_bbefocusbar;
	M3D_PageListView*	d_reverblist;
	//M3D_Label*			d_reverbfocusbar;


	int					d_selectedmenu;
	int					d_lastmenu;
	int					d_scoreClicked;
	int					d_titleClicked;
	int					d_agcClicked;

};

}

#endif
