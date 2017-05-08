//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormLanguage.h
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

#ifndef _FORMLANGUAGE_H_
#define _FORMLANGUAGE_H_

#include "Widgets/M3D_Form.h"


namespace CEGUI
{
	class M3D_ListView;
	class M3D_Item;
	class FormLanguage:public M3D_Form
	{
	public:

		FormLanguage(const String& type, const String& name);
		virtual ~FormLanguage(void);

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

		virtual void onCharacter(KeyEventArgs& e);

	private:
		void handleMenuClicked(M3D_Item *item, int position);

		M3D_ListView*	d_menu;

	};

}

#endif
