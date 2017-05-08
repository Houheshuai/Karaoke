//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Item.h
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
#ifndef _M3D_ITEM_H
#define _M3D_ITEM_H

#include "Window_2D.h"

namespace CEGUI
{
class M3D_Item:public Window_2D
{
public:
	M3D_Item(const String& type, const String& name);
	virtual ~M3D_Item(void);

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

	virtual void onMouseButtonDown(MouseEventArgs& e);
	virtual void onMouseButtonUp(MouseEventArgs& e);
	virtual void onMouseMove(MouseEventArgs& e);

	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	void	setImage(std::string imgFilePath);
	void	setImage(uint resID);
	void	setAlpha(float alpha);

	void	setIndex(int index){d_index = index;}
	int		getIndex(){ return d_index;}
	float   getScale() { return d_scale;}

	WndRes_t *getWndRes() {return item_wndRes;} 

	std::function<void(M3D_Item*, int position)>		onItemClick;
	std::function<void(M3D_Item*, Vec2 vec, Touch_Event_Type touch)>		onItemTouch;

private:

	int		d_index;
	float	d_scale;
	
	WndRes_t *item_wndRes;
};

}

#endif
