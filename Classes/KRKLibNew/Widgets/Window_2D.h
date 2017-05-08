//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : Window_2D.h
//																	
// Description: 3D GUI basic window class
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#ifndef _FIRSTWINDOW_WINDOWS2D_H_
#define _FIRSTWINDOW_WINDOWS2D_H_

#include "CEGUI/CEGUI.h"
#include "Resource/Readres.h"
#include "Math/Geometry.h"
#include <functional>
#include <vector>
#include <unordered_map>

class Layer;
class Sprite;
class Rect;
class Vec2;
class StringBitmapNew;
class Image;

namespace CEGUI
{
enum Text_Align_
{
	ALIGNTYPE_NONE,
	ALIGNTYPE_XLEFT_YMIDDLE,		// 1
	ALIGNTYPE_XMIDDLE_YMIDDLE,
	ALIGNTYPE_XRIGHT_YMIDDLE,
	ALIGNTYPE_XLEFT_YUP,			// 4
	ALIGNTYPE_XMIDDLE_YUP,
	ALIGNTYPE_XRIGHT_YUP,
	ALIGNTYPE_XLEFT_YBOTTOM,		// 7
	ALIGNTYPE_XMIDDLE_YBOTTOM,
	ALIGNTYPE_XRIGHT_YBOTTOM
};

typedef enum {
	wndFocusMove_left,
	wndFocusMove_right,
	wndFocusMove_up,
	wndFocusMove_down,
} wndFocusMoveDirection_et;

enum {
	Reserved_Define_FocusImageID = 0,
	Reserved_Define_FocusEnableID = 1,
	Reserved_Define_InvisibleID = 2,

	Reserved_Define_Count = 3,
};

enum WidgetDirection
{
	Direction_LeftRight,
	Direction_UpDown,
};

enum Scroll_Animation_Type
{
	Scroll_Animation_None = 0,
	Scroll_Standard = 0x4001,
	Scroll_Type_RollBubbles,
};

enum Touch_Event_Type
{
	Action_Down = 0,
	Action_Move,
	Action_Up,
	Action_Cancel,
};

#define MAX_ASYNC_CAHCE		5

class TimerEventArgs : public WindowEventArgs
{
public:
    TimerEventArgs(Window* window, String& name, uint para) :
        WindowEventArgs(window),
        d_para(para)
    {d_name = name;}

	String			d_name; //! action id
	uint 				d_para; //! action play type
};

class WindowTimer 
{
public:
	WindowTimer() {};
	WindowTimer(String& name, float timeout, bool loop, uint para) :
		d_name(name),
		d_timeout(timeout),
		d_loop(loop),
		d_para(para),
		d_timer(0)
	{};

	String			d_name;
	uint				d_para;
	float				d_timer;		//! elapsed time, ms
	float				d_timeout; 	//! timeout time, ms
	bool				d_loop; 			//! is loop timer?
};

class OFNEventArgs : public WindowEventArgs
{
public:
    OFNEventArgs(Window* window, int dx, int dy) :
        WindowEventArgs(window),
        d_dx(dx),
        d_dy(dy)
    {
		
	}

	int 					d_dx; //! curent delta x
	int					 	d_dy; //! current delta y
	int						d_dtime;//! current delta time (ms)
	int 					d_ds; //! curent delta s
	
	int						d_total_dx;//! total delta x, from touch on to touch off
	int 					d_total_dy;//! total delta y, from touch on to touch off

	int 					d_last_move_direct_x; // last several move x, direct is same
	int 					d_last_move_direct_y; // last several move x, direct is same

	int						d_total_dsx; // segma abs dx
	int						d_total_dsy; // segma abs dy

	int						d_total_time;//! total time, from touch on to touch off
	int						d_total_ds;//! total delta s, from touch on to touch off

	unsigned char			index;

	float					d_ratioXY;
};

class Window_2D : public Window
{
public:
	Window_2D(const String& name, const String& type);
	virtual ~Window_2D(void);

	static const String EventNamespace;
	static const String WidgetTypeName;
	static const String EventTimeOut;
	
	//Show Hide触发
    virtual void onShown(WindowEventArgs& e);
    virtual void onHidden(WindowEventArgs& e);

	//SetEnable触发
    virtual void onEnabled(WindowEventArgs& e);
    virtual void onDisabled(WindowEventArgs& e);

	//UpdateSelf
    virtual void updateSelf(float elapsed);

	//Impl触发Event
    virtual void addChild_impl(Window* wnd);
    virtual void removeChild_impl(Window* wnd);
    virtual void onZChange_impl(void);
    virtual bool moveToFront_impl(bool wasClicked);

    virtual void onChildAdded(WindowEventArgs& e);
    virtual void onChildRemoved(WindowEventArgs& e);
	virtual void onZChanged(WindowEventArgs& e);
	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void onTimeout(EventArgs& e);

	//===========================================================//
	//输入设备相关，鼠标，按键，OFN
	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);

	virtual void onOFNMove(OFNEventArgs& e);
	virtual void onOFNTouchOn(OFNEventArgs& e);
	virtual void onOFNTouchOff(OFNEventArgs& e);
	virtual void onOFNKeyDown(OFNEventArgs& e);
	virtual void onOFNKeyUp(OFNEventArgs& e);
	virtual void onOFNClick(OFNEventArgs& e);


	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	//===========================================================//
	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow(void);

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void onActionStart(void);
	virtual void onActionEnd(void);
	virtual void setLocalZorder(float order);

	//绘图相关
	virtual Layer	*createContainer(WndRes_t *wndRes = NULL, Window_2D *parent = NULL);
	
	//==========================================================//
	Layer	*getContainer(){return d_container;};
	void	setContainer(Layer *container){d_container = container;};

	void   setBGImage(uint resID, Rect showArea, float alpha=1.0f, Vec2 anchorPoint = Vec2(0.5f, 0.5f));
	void   setBGImage(String imageFilePath);
	void   setBGImage(uint resID);

	void   setString(uint resStringID, uint resStyleID, bool hideBeforeString = false);
	void   setString(String text, bool hideBeforeString = false);
	String getString(){return d_text;};
	StyleProperty_t* getStyle(){return d_style;};

	void   pushStringBitmap(StringBitmapNew *strBmp);
	void   pushImageBitmap(Image *imgBmp);

	void   setBGAlpha(float alpha);

	//===================================================================================//
	Rect   getWindowArea(){return d_windowArea;};
	Window* findNextFocusWidget(Window* activeWnd, wndFocusMoveDirection_et direction);
	void   setFocusMoveable(bool focusMove);
	//==================================================================================//
	void   moveOffset(float x, float y);

	void    addChildSprite(Sprite *sp, int localZorder);
	int	 	getChildSpriteCount() {return d_childSprite.size();};
	Sprite* getChildSpriteAtIdx(int i) { return d_childSprite.at(i);};

	bool createTimer(String& name, float timeout, bool loop, uint para);
	void destroyTimer(String& name);	
	void resetTimer(String& name);
	void cleanTimer(void);
	void updateTimer(float elapsed);

	void blink(float durations, int times);

	int getStringBitmapWidth(void);
	int getStringBitmapHeight(void);

	void    focus();
	void    unfocus();

	void    setStringShiftable(bool shiftFlag, float shiftPixelRate = 0.02f, bool focusNeed = true);

	void	setZOrderTop(bool _top){d_reserveTop = _top;};

	void	setStringShadowOffset(float x, float y);

public:
	bool			d_reserveTop;

private:
	//
	uint d_normalResID;
	uint d_focusResID;
	uint d_saveResID;

	Vec4	colourConvert(uint color);
	bool	moveFocus(wndFocusMoveDirection_et direction);

	Layer*				d_container;
	//Layer*			d_parentContainer;
	Rect				d_windowArea;         //左下角为原点的坐标系
	Rect				d_hitArea;			  //左上角
	Rect				d_windowCenterArea;         //左下角为原点的坐标系
	String				d_text;				  //显示的字符串
	String				d_textCache;
	StyleProperty_t*	d_style;
	uint				d_resID;

	Sprite*				d_spriteString;
	Sprite*				d_spriteShadow;
	float				d_shadowOffsetX;
	float				d_shadowOffsetY;
	Sprite*				d_spriteImage;

	std::vector<Sprite *> d_childSprite;

	StringBitmapNew*    d_stringBufferQueue[MAX_ASYNC_CAHCE];
	Image*				d_imageBufferQueue[MAX_ASYNC_CAHCE];

	int				d_stringReadPos;
	int				d_stringWritePos;
	int				d_imageReadPos;
	int				d_imageWritePos;

	bool			d_keyMoveFocus;
	bool			d_actionStartFlag[2];

	//typedef std::vector<TimerEventArgs> TimerEventList;
	//typedef std::vector<WindowTimer> wndTimerList;

	typedef std::vector<TimerEventArgs> timerEventList;
	typedef std::unordered_map<String, WindowTimer> wndTimerList;

	wndTimerList d_timerList;

	bool			d_shiftFlag;
	bool			d_shiftNeed;
	bool			d_activeManual;
	Rect			d_shiftRectNow;
	Rect			d_shiftRectTotal;
	float			d_shiftPixel;
	bool			d_focusNeed;

	bool			d_hideBeforeString;

	bool			d_shadowStringEnabled;

	Window_2D& operator=(const Window_2D&) {return *this;}
};

}

#endif
