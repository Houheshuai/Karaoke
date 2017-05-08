//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormMain.h
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

#ifndef _FORMMAIN_H_
#define _FORMMAIN_H_

#include "Widgets/M3D_Form.h"

namespace CEGUI
{
    class M3D_Item;
	/*
	class M3D_Label;
	class M3D_PageListView;
	class M3D_Log;*/
	class M3D_ListView;

	class FormMain:public M3D_Form
	{
	public:

		FormMain(const String& type, const String& name);
		virtual ~FormMain();

		static const String EventNamespace; 			//!< Namespace for global events
		static const String WidgetTypeName; 			//!< Window factory name

		virtual void constructWindow(WndRes_t *wndRes);
		virtual void destructWindow();

	    virtual void onShown(WindowEventArgs& e);
		virtual void onHidden(WindowEventArgs& e);

		virtual void onCreated();
		virtual void onDestroyed();

		virtual void onActivated(ActivationEventArgs& e);
		virtual void onDeactivated(ActivationEventArgs& e);

		virtual void onActionStart();
		virtual void onActionEnd(); 
		virtual void onTimeout(EventArgs& e);

		virtual void onCharacter(KeyEventArgs& e);
		int MCodeConvert_GB2312toUTF8(const char* in_utf8, char* out_gb2312, int Len1, int Len2);

	private:
	
		M3D_ListView *d_menu;
		void handleMenuClicked(M3D_Item *item, int position);
		
		//edb
		int 		d_totalCnt;
		
		void DownloadListView_DataFill(M3D_Item *item, int position);
		void DownloadListView_ItemClick(M3D_Item *item, int position);
		
		void DownloadListView_FocusChange(M3D_Item *item, int position);
		void DownloadListView_PageReflash(int currentPage, int totalPage);
	};

}

#endif
