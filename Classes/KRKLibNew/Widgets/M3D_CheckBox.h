//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_CheckBox.h
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

#ifndef _M3D_CHECKBOX_H
#define _M3D_CHECKBOX_H

#include "Window_2D.h"

namespace CEGUI
{

class M3D_CheckBox:public Window_2D
{
public:
	M3D_CheckBox(const String& type, const String& name);
	virtual ~M3D_CheckBox(void);

	static const String EventNamespace; 			//!< Namespace for global events
	static const String WidgetTypeName; 			//!< Window factory name

	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow();

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void updateSelf(float elapsed);

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);

	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	void	setImage(uint resID);
	void	setAlpha(float alpha);

	void	setChecked(bool checked);
	bool    getChecked() {return d_checked;};
private:
	uint d_checkedResID;
	uint d_uncheckedResID;

	bool d_checked;

	Sprite *d_spriteChecked;
};


}

#endif
