//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_PageListView.h
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
#ifndef _M3D_PAGELISTVIEW_H
#define _M3D_PAGELISTVIEW_H

#include "Window_2D.h"
#include "pthread.h"

class Action;
namespace CEGUI
{
class M3D_Label;
class M3D_Item;
class M3D_ItemCollection;

enum PageListView_Scroll_Animation_Type
{
	PageListView_Animation_None = 0,
};

class M3D_PageListView:public Window_2D
{
public:
	M3D_PageListView(const String& type, const String& name);
	virtual ~M3D_PageListView(void);

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

	//=====================================================//
	void	setCircleEnable(bool circle){d_circleEnable = circle;};
	bool    getCircleEnable() { return d_circleEnable;}

	void	setTotalItemCount(int itemCount);
	int		getTotalItemCount(){return d_itemCount;}

	void	clickCurrentSelected();

	int		getPageSize();
	int		getTotalPage();
	int		getCurrentPage();

	void	jumpToTop();
	void	jumpToBottom();
	void    scrollToPage(int _page, int focusPos);
  	//上下Focus
	//每页显示的数量
	void	scrollNextPage(float scrollTime = 0.3f);
	void	scrollPrevPage(float scrollTime = 0.3f);
	void    scrollNext(float scrollTime = 0.1f);
	void	scrollPrev(float scrollTime = 0.1f);

	void	setFocusBarResID(int focusLabelResID);
	//事件
	std::function<void(M3D_Item*, int position)>		onDataFill;
	void    setOnClickListener(std::function<void(M3D_Item*, int position)> _onItemClick);
	void    setOnFocusChangeListener(std::function<void(M3D_Item*, int position)> _onFocusChange);
	std::function<void(int currentPage, int totalPage)>		onPageChange;

	void    setScrollAnimationType(PageListView_Scroll_Animation_Type _type){d_scrollAnimationType = _type;};
  	std::vector<M3D_Item *> getItemQueue() {return d_itemQueue;};

	M3D_Item * getFocusItem();
	int getFocusDataIndex();

	int	    deleteFocusItem();
	int	    clearItem();

	void	setKeepLastFocusWhenDeactive(bool flag) { d_keepLastFocusWhenDeactive = flag;};

private:
	void changePosition(M3D_Item *item, Vec2 moveDirection);
	void focusChangeCheck(bool pagechanged=false);

	M3D_ItemCollection*						d_itemCollection;
	std::vector<M3D_Item *>					d_itemQueue;
	int										d_itemCount;
	//std::vector<M3D_Label *>				d_focusQueue;
	std::vector<Vec2>						d_focusPositionQueue;

	int										d_scrollStatus;
	pthread_mutex_t							d_scrollMutex;

	PageListView_Scroll_Animation_Type		d_scrollAnimationType;

	Vec2									d_itemSize;   //Item的大小

	int										d_topIndex;
	int										d_index;	//当前的index，默认是0
	int										d_previewIndex;
	int										d_itemFrontPostion; //第一项的位置


	bool									d_circleEnable;  //是否循环显示列表

	int										d_pageSize;    //就是可用于显示的集合的一半
	int										d_queueSize;    //
	int										d_totalPage;    //
	int										d_currentPage;    //

	int										d_scrollFocusbarTime;
	int										d_lastFocusPosition;
	int										d_focusPosition;

	bool									d_keepLastFocusWhenDeactive;

	std::function<void(M3D_Item*, int position)>		onItemClick;	
	std::function<void(M3D_Item*, int position)>		onFocusChange;

	M3D_Label*								d_focusLastLabel;
	int										d_focusLabelResID;
	
};

}

#endif
