//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Event.h
//																	
// Description: multak 3D GUI about all events define
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#pragma once

#ifndef _M3D_EVENT_H_
#define _M3D_EVENT_H_

#include "CEGUI/CEGUIInputEvent.h"

//! 3D UI events define
typedef enum
{
	M3D_EVENT_NONE = 0,
	M3D_EVENT_MOUSE,
	M3D_EVENT_KEYBOARD,
	M3D_EVENT_ACTIVE_SYNC,
	M3D_EVENT_REFRESH_MEDIAPLAYER_TIME,
	M3D_EVENT_OFN,
	M3D_EVENT_KEYDOWN,
	M3D_EVENT_KEYUP,
} M3D_Event_et;

//! 3D UI MOUSE events define
typedef enum
{
	M3D_MOUSEEVENT_NONE = 0,
	M3D_MOUSEEVENT_UP,
	M3D_MOUSEEVENT_DOWN,
	M3D_MOUSEEVENT_MOVE,
	M3D_MOUSEEVENT_POS,
	M3D_MOUSEEVENT_CLICK,
	
} M3D_MouseEvent_et;

//! 3D UI OFN events define
typedef enum
{
	M3D_OFNEVENT_NONE = 0,
	M3D_OFNEVENT_TOUCHON = (1<<1),
	M3D_OFNEVENT_TOUCHOFF = (1<<2),
	M3D_OFNEVENT_KEYDOWN = (1<<3),
	M3D_OFNEVENT_KEYUP = (1<<4),
	M3D_OFNEVENT_MOVE = (1<<5),
	
} M3D_OFNEvent_et;

//! 3D UI OFN events define
typedef enum
{
	M3D_OFNKEY_NONE = 0,
	M3D_OFNKEY_UP,
	M3D_OFNKEY_DOWN,
	M3D_OFNKEY_LEFT,
	M3D_OFNKEY_RIGHT,
	M3D_OFNKEY_ENTER,
	
} M3D_OFNSIMKey_et;

//! 3D UI MOUSE event parameter
typedef struct 
{
	M3D_MouseEvent_et			type;
	CEGUI::MouseButton			button;
	float									x;
	float									y;
	
} M3D_MouseEventPara_t;

//! 3D UI KB event parameter
typedef struct 
{
	int					 				keycode;
	
} M3D_KBEventPara_t;

//! 3D UI OFN event parameter
typedef struct 
{
	int									dt;
	int					 				dx;
	int					 				dy;
	unsigned char		 				touch;
	unsigned char						key;
	unsigned char			 			index;	
	unsigned char 		 				event;
} M3D_OFNEventPara_t;

//! 3D UI active sync parameter
typedef struct 
{
	int					 				synctype;
	int									para1;
	int									para2;
} M3D_SyncEventPara_t;

//! 3D UI active sync parameter
typedef struct 
{
	int									totalTime;
	int									curTime;
} M3D_MediaReTime_t;


//! 3D UI event parameter
typedef union
{
	M3D_MouseEventPara_t 			mouse;
	M3D_KBEventPara_t				kb;
	M3D_SyncEventPara_t				activeSync;
	M3D_MediaReTime_t				MediaPlayerReTime;
	M3D_OFNEventPara_t				ofn;
} M3D_Event_Para_t;

//! 3D UI  MOUSE or KB event 
typedef struct
{
	M3D_Event_et					type;
	M3D_Event_Para_t			para;
	
} M3D_Event_t;

#endif


