#ifndef _GUI_IAL_H_
#define _GUI_IAL_H_

#define DEFAULT_MULTI_CLICK_TIMEOUT		500//ms
#define DEFAULT_SINGLE_CLICK_TIMEOUT		0
#define DEFAULT_MULTI_CLICK_AREASIZE		0x2020//width=0x08, height=0x08

#define MouseDragSense		60

typedef enum
{
	MouseEvent_None,
	MouseEvent_WheelScroll,			/* wheel scroll */
	MouseEvent_Move,				/* just move, no button down */
	MouseEvent_LeftButtonUp,		/* release left button */
	MouseEvent_LeftButtonDown,		/* press left button */
	MouseEvent_RightButtonUp,		/* release right button */
	MouseEvent_RightButtonDown,	/* press right button */
	
	MouseEvent_Count,
	
} MouseEvents_et;

typedef enum
{
	IAL_DISABLED = 0,	/* disable key input to GUI */
	IAL_ENABLED,		/* only GUI response key input */
	IAL_BYPASS,			/* not only GUI response key input */
	
} IALConfig_et;

/*!
\brief
	struct to give scope to scan code enumeration.
*/

	// enumeration of scan codes.  Customised from table taken from Ogre, which took them from DirectInput...
typedef enum 
{
	UIKey_None						=0x0,
	UIKey_Tab							=0x01,
	UIKey_Enter						=0x02,		/* Enter on main keyboard */
	UIKey_Backspace 				=0x03,		/* backspace */
	UIKey_Space 						=0x04,
	UIKey_Mute						=0x05,		/* Mute */
	UIKey_PlayPause 				=0x06,		/* Play / Pause */
	UIKey_Stop						=0x07,		/* Stop */
	UIKey_Pause 						=0x08,		/* Pause */
	UIKey_VolumeDown		=0x09,		/* Volume - */
	UIKey_VolumeUp				=0x0A,		/* Volume + */
	UIKey_Home						=0x0B,		/* Home on arrow keypad */
	UIKey_End 							=0x0C,		/* End on arrow keypad */
	UIKey_ArrowUp 				=0x0D,		/* UpArrow on arrow keypad */
	UIKey_ArrowDown 			=0x0E,		/* DownArrow on arrow keypad */
	UIKey_ArrowLeft 				=0x0F,		/* LeftArrow on arrow keypad */
	UIKey_ArrowRight			=0x10,		/* RightArrow on arrow keypad */
	UIKey_PageUp					=0x11,		/* PgUp on arrow keypad */
	UIKey_PageDown				=0x12,		/* PgDn on arrow keypad */
	UIKey_Insert						=0x13,		/* Insert on arrow keypad */
	UIKey_Delete						=0x14,		/* Delete on arrow keypad */
	UIKey_Menu 						=0x15,		/* AppMenu key */
	UIKey_Power 					=0x16,		/* System Power */
	UIKey_Esc	 						=0x17,		/* esc button */
	UIKey_Wake						=0x18,		/* System Wake */
	
	UIKey_F1							=0x19,
	UIKey_F2							=0x1A,
	UIKey_F3							=0x1B,
	UIKey_F4							=0x1C,
	UIKey_F5							=0x1D,
	UIKey_F6							=0x1E,
	UIKey_F7							=0x1F,
	UIKey_F8							=0x20,
	UIKey_F9							=0x21,
	UIKey_F10							=0x22,
	UIKey_F11 							=0x23,
	UIKey_F12 							=0x24,
	UIKey_F13 							=0x25,
	UIKey_F14 							=0x26,	
	UIKey_F15 							=0x27,
	
	UIKey_0								='0',
	UIKey_1								='1',
	UIKey_2								='2',
	UIKey_3								='3',
	UIKey_4								='4',
	UIKey_5								='5',
	UIKey_6								='6',
	UIKey_7								='7',
	UIKey_8								='8',
	UIKey_9								='9',
	
	UIKey_A 							='A',
	UIKey_B 							='B',
	UIKey_C 							='C',
	UIKey_D 							='D',
	UIKey_E 							='E',
	UIKey_F 							='F',
	UIKey_G 							='G',
	UIKey_H 							='H',
	UIKey_I 							='I',
	UIKey_J 							='J',
	UIKey_K 							='K',
	UIKey_L 							='L',
	UIKey_M 						='M',
	UIKey_N 						='N',
	UIKey_O 							='O',
	UIKey_P 							='P',
	UIKey_Q               			='Q',
	UIKey_R 							='R',
	UIKey_S 							='S',
	UIKey_T 							='T',
	UIKey_U 							='U',
	UIKey_V 							='V',
	UIKey_W							='W',
	UIKey_Y							='Y',
	UIKey_X 							='X',
	UIKey_Z 							='Z',
	
	UIKey_Prev						=0x60,
	UIKey_Next					=0x61,
	UIKey_Vocal					=0x62,
	UIKey_Bgv						=0x63,
	UIKey_Setup					=0x64,
	UIKey_Scene					=0x65,
	UIKey_Replay 				=0x66,
	UIKey_Repeat				=0x67,
	UIKey_Display				=0x68,
	UIKey_Title						=0x69,
	UIKey_Goto					=0x6A,
	UIKey_Program				=0x6B,
	UIKey_Sound					=0x6C,
	UIKey_Close					=0x6D,
	UIKey_Skin						=0x6E,

	UIKey_PowerKey		,	/*F1 key*/
	UIKey_Applause		,	/*F2 key*/
	UIKey_Face			,	/*F3 key*/
	UIKey_ExitKRK		,	/*F4 key*/


	UIKey_Singer		,	/*F7 key*/
	UIKey_Spell			,	/*F8 Key*/
	UIKey_FB			,	/*< key*/
	UIKey_FF			,	/*> key*/
	UIKey_WDCNT,
	UIKey_RESLIST,
	UIKey_WDCNTADD,
	UIKey_WDCNTDEC,
	UIKey_TUNING,
	UIKey_Toplist,
	UIKey_ADDVANCE,

	
	UIKey_KeyUp					=0x80,
	UIKey_KeyDown			=0x81,
	UIKey_KeyOrigin			=0x82,
	
	UIKey_Score			,	/*F3 key*/
	UIKey_Record		,	/*F7 key*/
	UIKey_Favorit			,	/*F8 Key*/
	
	UIKey_TempoUp			,	/*< key*/
	UIKey_TempoDown			,	/*> key*/

	UIKey_Ifun,
	UIKey_IM,
	UIKey_EQFreq,
	UIKey_Male,		
	UIKey_FeMale,

	UIKey_WMIC_Up,
	UIKey_WMIC_Down,
	UIKey_WMIC_Left,
	UIKey_WMIC_Right,
	UIKey_WMIC_Enter,

	UIKey_Return,

	UIKey_Customer_Code = 0x1000,
	
	UIKey_Max = 0x7fffffff,
} UIKeyScan;


/*!
\brief
    Enumeration of mouse buttons
*/
typedef enum 
{
    //! The left mouse button.
    ezLeftButton = 0,
    //! The right mouse button.
    ezRightButton,
    //! The middle mouse button.
    ezMiddleButton,
    //! The first 'extra' mouse button.
    ezX1Button,
    //! The second 'extra' mouse button.
    ezX2Button,
    //! Value that equals the number of mouse buttons supported by CEGUI.
    ezMouseButtonCount,
    //! Value set for no mouse button.  NB: This is not 0, do not assume!
    ezNoButton
    
} ezMouseButton;

/*!
\brief
    direction of mouse drag
*/
typedef enum 
{
	//! no direction
	MouseDragNone,
    //! drag to up
    MouseDragUp,
    //! drag to down
    MouseDragDown,
    //! drag to left
    MouseDragLeft,
    //! drag to right
    MouseDragRight,

} ezMouseDragDir;

/*!
\brief
	System key flag values
*/
typedef enum 
{
	ezSysKeyNone = 0,
	ezLeftMouse		= 0x0001,			//!< The left mouse button.
	ezRightMouse		= 0x0002,			//!< The right mouse button.
	ezShift			= 0x0004,			//!< Either shift key.
	ezControl			= 0x0008,			//!< Either control key.
	ezMiddleMouse		= 0x0010,			//!< The middle mouse button.
	ezX1Mouse			= 0x0020,			//!< The first 'extra' mouse button
	ezX2Mouse			= 0x0040,			//!< The second 'extra' mouse button.
	ezAlt				= 0x0080			//!< Either alt key.
} ezSystemKey;

typedef struct 
{
	ezPoint pos;
	
} ezMouseCursor_t;

/*!
\brief
	customer defined key map
*/
typedef struct 
{
	int cust_key;
	int ui_key;
	
}ezCustKeyMap_t;

/*!
\brief
	key&Mouse event callback
*/
typedef int (* ezIALEventCallback_t)(unsigned int, unsigned int, void*);

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_getMouseCoordinate
 * Arguments      	: X - Mouse Cursor x position
 *				 				: Y - Mouse Cursor y position
 *				 				: Z - Mouse Cursor z position
 * Return         	: none
 * Description    	: Get current mouse position
 *					
*/
extern void ez_getMouseCoordinate(short* X, short* Y, short* Z);

extern void ez_setMouseCoordinate(short x, short y, short z);

/*
 * Function name  	: ez_calcMouseDragDir
 * Arguments      	: x - Mouse Cursor x position
 *				 				: y - Mouse Cursor y position
 * Return         	: none
 * Description    	: Get current mouse drag direction
 *					
*/
extern ezMouseDragDir ez_calcMouseDragDir(int dx, int dy);

/*
 * Function name  	: ez_getMouseDragDir
 * Arguments      	: x - Mouse Cursor x position
 *				 				: y - Mouse Cursor y position
 * Return         	: none
 * Description    	: Get current mouse drag direction
 *					
*/
extern ezMouseDragDir ez_getMouseDragDir(int x, int y);

/*
 * Function name  	: ez_resetMouseDrag
 * Arguments      	: none
 * Return         	: none
 * Description    	: reset mouse drag
 *					
*/
extern void ez_resetMouseDrag(void);

/*
 * Function name  	: ez_IALInit
 * Arguments      	: param - application handle
 * Return         	: 0-succ, <>0-error code
 * Description    	: initialize ez IAL
 *					
*/
extern int ez_IALInit(unsigned long param);

/*
 * Function name  	: ez_IALFree
 * Arguments      	: param - application handle
 * Return         	: 0-succ, <>0-error code
 * Description    	: free ez IAL
 *					
*/
extern int ez_IALFree(unsigned long param);

#ifdef __cplusplus
}
#endif

#endif

