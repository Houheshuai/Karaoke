//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_SlipListView.h
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
#ifndef _M3D_SLIPLISTVIEW_H
#define _M3D_SLIPLISTVIEW_H

#include "Window_2D.h"

class Action;
namespace CEGUI
{
class M3D_Item;
class M3D_ItemCollection;
class M3D_Label;

class M3D_SlipListView:public Window_2D
{
public:
	M3D_SlipListView(const String& type, const String& name);
	virtual ~M3D_SlipListView(void);

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
	virtual void onMouseMove(MouseEventArgs& e);

	virtual void onOFNMove(OFNEventArgs& e);
	virtual void onOFNTouchOn(OFNEventArgs& e);
	virtual void onOFNTouchOff(OFNEventArgs& e);
	virtual void onOFNKeyDown(OFNEventArgs& e);
	virtual void onOFNKeyUp(OFNEventArgs& e);
	virtual void onOFNClick(OFNEventArgs& e);

	virtual void onTimeout(EventArgs& e);

	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	void	setImage(uint resID);
	void	setAlpha(float alpha);

	//=====================================================//
	void    clear();

	void	setScrollOneItemTime(float time){d_scrollOneItemTime = time;};

	void    setFixedFocusPosition(int position);

	void	setCircleEnable(bool circle){d_circleEnable = circle;};
	bool    getCircleEnable() { return d_circleEnable;}

	void	setTotalItemCount(int itemCount){d_itemCount = itemCount;}
	int		getTotalItemCount(){return d_itemCount;}

	void    setTopIndex(int index);
	int     getTopIndex() {return d_topIndex;}
	int     getCurrentIndex() {return d_index;}
	
	void	jumpToTop();
	void	jumpToBottom();

	void	scrollToItem(int itemIndex);

	void	scrollNextPage();
	void	scrollPrevPage();

	void    scrollNext();
	void	scrollPrev();

	std::function<void(M3D_Item*, int position)>		onDataFill;
	void    setOnClickListener(std::function<void(M3D_Item*, int position)> _onItemClick);
	void    setOnFocusChangeListener(std::function<void(M3D_Item*, int position)> _onFocusChange);

	M3D_Item* getItem(int nIndex){return d_itemQueue[nIndex];};

	void    setDirection(WidgetDirection _direction){ d_direction = _direction;}

	void	setFocusBarResID(int focusLabelResID);

	void    runWithVelocityNext(float durationSeconds = 3.0f);
	void    runWithVelocityPrev(float durationSeconds = 3.0f);
	void	slowDownAndStop();
	void	stopNow();

	float   alignList(float maxS = FLT_MAX);

private:
	void focusChangeCheck();

	std::function<void(M3D_Item*, int position)>		onItemClick;	
	std::function<void(M3D_Item*, int position)>		onFocusChange;

	void onItemTouch(M3D_Item *item, Vec2 vec, Touch_Event_Type type);
	void moveItemDelta(float s, int itemStart, bool limit = true);


	int  d_itemCount;

	M3D_ItemCollection*		d_itemCollection;
	//std::unordered_map<M3D_Item *, bool>		d_itemActionStatus;
	std::vector<M3D_Item *>		d_itemQueue;
	std::vector<float>			d_itemScale;
	std::vector<Rect>			d_itemRect;
	Vec2						d_itemSize;
	int							d_itemFrontPosition;
	int							d_scrollStatus;
	int							d_queueSize;

	int		d_topIndex;	//缓存的Item起始使用的位置
	int		d_index;		//对应的真实数据第一个位置，比如-4
	int		d_previewIndex;

	bool	d_circleEnable;

	int		d_fixedFocusPosition;
	int		d_lastFocusPosition;
	float	d_scrollOneItemTime;
	
	WidgetDirection d_direction;
											
	std::vector<Vec2>						d_focusPositionQueue;
	M3D_Label*								d_focusLastLabel;
	int										d_focusLabelResID;

	float									d_scrollSpeed;


};

}

#endif
