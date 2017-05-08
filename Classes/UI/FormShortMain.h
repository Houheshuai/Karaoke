//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormShortMain.h
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

#ifndef _FORMSHORTMAIN_H_
#define _FORMSHORTMAIN_H_

#include "Widgets/M3D_Form.h"


namespace CEGUI
{
class M3D_ListView;
class M3D_Item;
class FormShortMain:public M3D_Form
{
public:

	FormShortMain(const String& type, const String& name);
	virtual ~FormShortMain(void);

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
	void handleMenuClicked(M3D_Item *item, int position);
	void handleExitForm(void);
	
	M3D_ListView*	d_menu;

};

}

#endif
