//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_ListView.h
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
#ifndef _M3D_LISTVIEW_H
#define _M3D_LISTVIEW_H

#include "Window_2D.h"
#include "pthread.h"

class Action;
namespace CEGUI
{
class M3D_Item;
class M3D_ItemCollection;

class M3D_ListView:public Window_2D
{
public:
	M3D_ListView(const String& type, const String& name);
	virtual ~M3D_ListView(void);

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

	void	setImage(uint resID);
	void	setAlpha(float alpha);

	//=====================================================//
	void    clear();

	void	setScrollOneItemTime(float time){d_scrollOneItemTime = time;};
	void    setScrollAnimationType(Scroll_Animation_Type _type){d_scrollAnimationType = _type;};
	//void	setVisibleItems(int _itemsVisible) { d_visibleItems = _itemsVisible;};

	void    setFixedFocusPosition(int position);

	void	setCircleEnable(bool circle){d_circleEnable = circle;};
	bool    getCircleEnable() { return d_circleEnable;}
	void    setReverseCircle(bool reverse){d_reverseEnable = reverse;};

	void	setTotalItemCount(int itemCount);
	int		getTotalItemCount(){return d_itemCount;}

	void    setTopIndex(int index);
	int     getTopIndex() {return d_topIndex;}
	int     getCurrentIndex() {return d_index;}
	
	int     getPageSize();

	void	jumpToTop();
	void	jumpToBottom();

	void	scrollToItem(int itemIndex);

	void	scrollNextPage(float scrollTime = 0.3f);
	void	scrollPrevPage(float scrollTime = 0.3f);

	void    scrollNext(float scrollTime = 0.1f);
	void	scrollPrev(float scrollTime = 0.1f);

	std::function<void(M3D_Item*, int position)>		onDataFill;
	void    setOnClickListener(std::function<void(M3D_Item*, int position)> _onItemClick);
	void    setOnFocusChangeListener(std::function<void(M3D_Item*, int position)> _onFocusChange);

	M3D_Item* getItem(int nIndex){return d_itemQueue[nIndex];};

	void    setDirection(WidgetDirection _direction){ d_direction = _direction;}

	void	recoveryItems();
	void	removeItem(int index);

private:

	void onScrollEnd(M3D_Item *item, Vec2 offsetPos, int *positionPtr);
	void focusChangeCheck();

	std::function<void(M3D_Item*, int position)>		onItemClick;	
	std::function<void(M3D_Item*, int position)>		onFocusChange;

	Action *getScrollAction(M3D_Item *item, Vec2 moveDirection, int *retValue, int graphIndex, int nextGraphIndex);
	void changePosition(M3D_Item *item, Vec2 moveDirection);

	int  d_itemCount;

	M3D_ItemCollection*		d_itemCollection;
	//std::unordered_map<M3D_Item *, bool>		d_itemActionStatus;
	std::vector<M3D_Item *>		d_itemQueue;
	std::vector<float>			d_itemScale;
	std::vector<Rect>			d_itemRect;
	Vec2						d_itemSize;

	std::vector<M3D_Item *>		d_itemQueue_Total;
	std::vector<float>			d_itemScale_Total;
	std::vector<Rect>			d_itemRect_Total;
	
	int							d_itemFrontPostion;
	int							d_scrollStatus;
	pthread_mutex_t				d_scrollMutex;

	int		d_topIndex;	//缓存的Item起始使用的位置
	int		d_index;		//对应的真实数据第一个位置，比如-4
	int		d_previewIndex;

	bool	d_circleEnable;

	int		d_fixedFocusPosition;
	int		d_lastFocusPosition;
	float	d_scrollOneItemTime;
	Scroll_Animation_Type    d_scrollAnimationType;
	
	WidgetDirection d_direction;

	bool	d_itemEqualQueueSize;

	bool	d_reverseEnable;
};


}

#endif
