//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_ScrollBar.h
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
#ifndef _M3D_SCROLL_BAR_H
#define _M3D_SCROLL_BAR_H

#include "Window_2D.h"

namespace CEGUI
{
class M3D_ScrollBar:public Window_2D
{
public:
	M3D_ScrollBar(const String& type, const String& name);
	virtual ~M3D_ScrollBar(void);

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

	void    setDirection(WidgetDirection _direction){ d_direction = _direction;}

	void	setAlpha(float alpha);

	void	setMaxValue(int maxValue);
	void	setMinValue(int minValue);
	void	setPageValue(int pageValue);

	void    setValue(int value);

private:
	
	Sprite		*d_barSprite;
	Sprite		*d_barInsideSprite;
	uint		d_barResID;
	uint		d_barInsideResID;

	int			d_maxValue;
	int			d_minValue;
	int			d_pageValue;

	int			d_value;

	float		d_minBarSize;
	float		d_maxBarSize;
	float		d_barSize;

	Rect		d_barRect;

	WidgetDirection d_direction;
};

}

#endif
