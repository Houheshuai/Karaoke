//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Button.h
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
#ifndef _M3D_BUTTON_H
#define _M3D_BUTTON_H

#include "Window_2D.h"

namespace CEGUI
{

class M3D_Button:public Window_2D
{
public:
	M3D_Button(const String& type, const String& name);
	virtual ~M3D_Button(void);

	static const String EventNamespace; 			//!< Namespace for global events
	static const String WidgetTypeName; 			//!< Window factory name

	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow();

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);

	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	void	setImage(std::string imgFilePath);
	void	setImage(uint resID);
	void	setAlpha(float alpha);

	std::function<void(M3D_Button*)> onButtonClick;

private:
	

};

}

#endif
