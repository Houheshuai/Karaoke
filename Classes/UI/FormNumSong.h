//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormNumSong.h
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

#ifndef _FORMNUMSONG_H_
#define _FORMNUMSONG_H_

#include "Widgets/M3D_Form.h"


namespace CEGUI
{
class M3D_Label;
class FormNumSong:public M3D_Form
{
public:

	FormNumSong(const String& type, const String& name);
	virtual ~FormNumSong(void);

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

private:
	
	void showNumber(void);
	void hideNumber(void);
	void setNumber(void);
	bool playSong(void);
	
	bool handleProgClicked(void);
	bool handlePlayClicked(void);
	bool handleInsertClicked(void);
	bool handleEnterClicked(void);
	
	M3D_Label*		d_numbg;
	M3D_Label*		d_songname;
	M3D_Label*		d_progcount;
	M3D_Label*		d_count;
	
	int				d_initCount;
	int				d_num;
	String			d_showname;
	
};

}

#endif
