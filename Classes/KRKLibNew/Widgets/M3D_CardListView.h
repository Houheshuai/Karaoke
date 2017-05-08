//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_CardListView.h
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
#ifndef _M3D_CARDLISTVIEW_H
#define _M3D_CARDLISTVIEW_H

#include "Window_2D.h"
#include "pthread.h"

#define MAX_CARD_ANIMATION	3

class Action;
namespace CEGUI
{
class M3D_Item;
class M3D_ItemCollection;
class M3D_Label;

class M3D_CardListView:public Window_2D
{
public:
	M3D_CardListView(const String& type, const String& name);
	virtual ~M3D_CardListView(void);

	static const String EventNamespace; 			//!< Namespace for global events
	static const String WidgetTypeName; 			//!< Window factory name

	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow();

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void updateSelf(float elapsed);

	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);

	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	///////////////////////////////////////////////////////////////////////////////////////
	void    setOnClickListener(std::function<void(M3D_Item*, int position)> _onItemClick);
	void    setOnFocusChangeListener(std::function<void(M3D_Item*, int position)> _onFocusChange);

	//////////////////////////////////////////////////////////////////////////////////////
	void	setCardAllUnfocus();

	void    setCardFocus(int position);

	int		getFocusPostion();

	void	setCardAnimationTime(float sec=0.2f);
	void	setCardScaleParam(float x1, float x2, float x3, float y1, float y2, float y3);

	void    setDirection(WidgetDirection _direction){ d_direction = _direction;}

private:

	std::function<void(M3D_Item*, int position)>		onItemClick;
	std::function<void(M3D_Item*, int position)>		onFocusChange;

	int							d_itemCount;
	M3D_ItemCollection*			d_itemCollection;
	std::vector<M3D_Item *>		d_itemQueue;
	std::vector<Rect>			d_itemRect;
	Vec2						d_itemSize;

	int							d_lastFocusItemPostion;
	int							d_cardAnimation;

	float						d_cardAnimationTime;
	float						d_cardAnimationScaleX[MAX_CARD_ANIMATION];
	float						d_cardAnimationScaleY[MAX_CARD_ANIMATION];

	std::vector<float>			d_cardFocusSpeedX;
	std::vector<float>			d_cardFocusSpeedY;

	std::vector<float>			d_beginScaleX;
	std::vector<float>			d_beginScaleY;
	std::vector<float>			d_endScaleX;
	std::vector<float>			d_endScaleY;

	std::vector<float>			d_nowScaleX;
	std::vector<float>			d_nowScaleY;
	std::vector<int>			d_animFlag;

	pthread_mutex_t				d_animMutex;

	WidgetDirection				d_direction;
};


}

#endif
