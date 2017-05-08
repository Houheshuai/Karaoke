#ifndef _M3D_CONFIG_H
#define _M3D_CONFIG_H

#include "GUIBase/M3D_ConfigBase.h"

//Extend Key define
#ifdef _WIN32
#define M3D_UI_KEY_OSD			VK_SHIFT
#define M3D_UI_KEY_SCORE		VK_F4
#define M3D_UI_KEY_BGV			'W' // VK_F5
#define M3D_UI_KEY_RETURN		VK_F9			// key return , F9 on PC
#define M3D_UI_KEY_PAGEUP		VK_PRIOR			//page up on pc
#define M3D_UI_KEY_PAGEDOWN		VK_NEXT			// page down on pc
#define M3D_UI_KEY_SEARCH		VK_F6		// key input method, F6 on PC Keyboard
#define M3D_UI_KEY_PROG			VK_F7		// key prog , F7 on PC keyboard
#define M3D_UI_KEY_SELECTED		VK_F8		// key favo , F8 on PC keyboard
#define M3D_UI_KEY_FAVO		    VK_INSERT		// key favo , INSERT on PC keyboard
//#define M3D_UI_KEY_BACKSPACE	VK_BACK		// key delete , DELETE on PC keyboard
#define M3D_UI_KEY_BKSP	VK_BACK		// key delete , DELETE on PC keyboard
#define M3D_UI_KEY_CLEAR		VK_F10		// key clear input , F10 on PC keyboard
#define M3D_UI_KEY_PLAYPAUSE	VK_F11		// key play pause, F11 on PC keyboard
#define M3D_UI_KEY_PLAY			VK_CONTROL  // key play, left Ctrl on PC keyboard :houhs add
#define M3D_UI_KEY_PAUSE		VK_SPACE	//' 'WINø’∏Ò‘›Õ£ :houhs add
#define M3D_UI_KEY_STOP		    VK_F12		// key stop, F12 on PC keyboard
#define M3D_UI_KEY_HOME			VK_HOME		// key home, home on PC keyboard
#define M3D_UI_KEY_TUNNING		125		// key tunning, end on PC keyboard
#define M3D_UI_KEY_SONGTITLE	126		// key tunning, end on PC keyboard
#define M3D_UI_KEY_SINGER		127		// key tunning, end on PC keyboard
#define M3D_UI_KEY_HUMMING		128		// key tunning, end on PC keyboard
#define M3D_UI_KEY_VOCALON      	129
#define M3D_UI_KEY_VOCALOFF     	130
#define M3D_UI_KEY_FOLLOW       	131
#define M3D_UI_KEY_VOLUP             VK_ADD
#define M3D_UI_KEY_VOLDOWN           VK_SUBTRACT
#define M3D_UI_KEY_MUTE              VK_END
#define M3D_UI_KEY_FF							261
#define M3D_UI_KEY_FR							262
#define M3D_UI_KEY_VOL_ADD						263
#define M3D_UI_KEY_VOL_REDUCE					264
#define M3D_UI_KEY_RADOM						267
#define M3D_UI_KEY_NUM_1	VK_NUMPAD1
#define M3D_UI_KEY_NUM_2	VK_NUMPAD2
#define M3D_UI_KEY_NUM_3	VK_NUMPAD3
#define M3D_UI_KEY_NUM_4	VK_NUMPAD4
#define M3D_UI_KEY_NUM_5	VK_NUMPAD5
#define M3D_UI_KEY_NUM_6	VK_NUMPAD6
#define M3D_UI_KEY_NUM_7	VK_NUMPAD7
#define M3D_UI_KEY_NUM_8	VK_NUMPAD8
#define M3D_UI_KEY_NUM_9	VK_NUMPAD9
#define M3D_UI_KEY_NUM_0	VK_NUMPAD0
#define M3D_UI_KEY_TEMPOUP	VK_F3
#define M3D_UI_KEY_TEMPODOWN VK_F2
#define M3D_UI_KEY_IFUN		'I'
#define M3D_UI_KEY_REPLAY	'R'
#define M3D_UI_KEY_LYRIC	'L'
#define M3D_UI_KEY_MELODYUP		VK_MULTIPLY
#define M3D_UI_KEY_MELODYDOWN	VK_DIVIDE
#define M3D_UI_KEY_MICUP	'M'
#define M3D_UI_KEY_MICDOWN	'N'
#define M3D_UI_KEY_KEYUP	'B'
#define M3D_UI_KEY_KEYDOWN	'V'
#define M3D_UI_KEY_SKIP		'S'
#define M3D_UI_KEY_LASTLABEL	'A'// 'Z'
#define M3D_UI_KEY_NEXTLABEL	'Z'//'X'
#define M3D_UI_KEY_RECORD	'G'
#define M3D_UI_KEY_REPEAT	'T'
#define M3D_UI_KEY_HELP		'X' //'A'
#define M3D_UI_KEY_CANCEL   'C'  // '3/#'  // 'C'
//#define M3D_UI_KEY_DELETE	'D'    // '4/$' // 'D'
#define M3D_UI_KEY_DELETE		VK_BACK
#define M3D_UI_KEY_USBINSERT 	0x31  //  '1/!'
#define M3D_UI_KEY_USBDELETE 	0x32  //  '2/@'
#define M3D_UI_KEY_MENU		'Q'
#define M3D_UI_KEY_SETUP	 0X53 //'U'---'S':houhs reset
#define M3D_UI_KEY_List		'P'
#define M3D_UI_KEY_LEFT		VK_LEFT
#define M3D_UI_KEY_RIGHT	VK_RIGHT
#define M3D_UI_KEY_KARAOKE		0X4E
#define M3D_UI_KEY_FAVORITE		VK_INSERT
//17.5.5/houhs add -------------------------//
#define M3D_UI_KEY_MP3		VK_F1			//
#define M3D_UI_KEY_MTV		VK_F2			//
#define M3D_UI_KEY_MOVIE	VK_F3			//
//------------------------------------------//
#else
typedef enum {
	mKey_Null,		
	mKey_Up,
	mKey_Down,
	mKey_Left,
	mKey_Right,
	mKey_Enter,		
	mKey_Power,
	mKey_Mute,
	mKey_BGV,
	mKey_OSD,
	mKey_NTSC,	//10
	mKey_Home,
	mKey_Repeat,
	mKey_Delete,
	mKey_Copy,
	mKey_Num_1,
	mKey_Num_2,
	mKey_Num_3,
	mKey_Num_4,
	mKey_Num_5,
	mKey_Num_6,			//20
	mKey_Num_7,
	mKey_Num_8,
	mKey_Num_9,
	mKey_PROG,
	mKey_Num_0,
	mKey_BKSP,
	mKey_Karaoke,
	mKey_Selected,
	mKey_Setup,
	mKey_Return,		//30
	mKey_Play,
	mKey_Stop,
	mKey_Pause,
	mKey_Next,
	mKey_Keyup,
	mKey_Keydown,
	mKey_Tempoup,
	mKey_Tempodown,
	mKey_Volup,
	mKey_Voldown,		//40
	mKey_Melodyup,
	mKey_Melodydown,
	mKey_Record,
	mKey_Vocal,
	mKey_Cheer,
	mKey_Prev,
	mKey_MTV,
	mKey_MP3,
	mKey_Movie,
	mKey_Favorite,		//50
	mKey_other_Melodyup,
	mKey_other_Melodydown,
} ShortKey_m ;

#define M3D_UI_KEY_UP			mKey_Up
#define M3D_UI_KEY_DOWN			mKey_Down
#define M3D_UI_KEY_LEFT			mKey_Left
#define M3D_UI_KEY_RIGHT		mKey_Right
#define M3D_UI_KEY_ENTER		mKey_Enter		
#define M3D_UI_KEY_POWER		mKey_Power
#define M3D_UI_KEY_MUTE			mKey_Mute
#define M3D_UI_KEY_BGV			mKey_BGV
#define M3D_UI_KEY_OSD			mKey_OSD
#define M3D_UI_KEY_NTSC			mKey_NTSC
#define M3D_UI_KEY_HOME			mKey_Home
#define M3D_UI_KEY_REPEAT		mKey_Repeat
#define M3D_UI_KEY_DELETE		mKey_Delete
#define M3D_UI_KEY_COPY			mKey_Copy
#define M3D_UI_KEY_NUM_1		mKey_Num_1
#define M3D_UI_KEY_NUM_2		mKey_Num_2
#define M3D_UI_KEY_NUM_3		mKey_Num_3
#define M3D_UI_KEY_NUM_4		mKey_Num_4
#define M3D_UI_KEY_NUM_5		mKey_Num_5
#define M3D_UI_KEY_NUM_6		mKey_Num_6
#define M3D_UI_KEY_NUM_7		mKey_Num_7
#define M3D_UI_KEY_NUM_8		mKey_Num_8
#define M3D_UI_KEY_NUM_9		mKey_Num_9
#define M3D_UI_KEY_PROG			mKey_PROG
#define M3D_UI_KEY_NUM_0		mKey_Num_0
#define M3D_UI_KEY_BKSP			mKey_BKSP
#define M3D_UI_KEY_KARAOKE		mKey_Karaoke
#define M3D_UI_KEY_SELECTED		mKey_Selected
#define M3D_UI_KEY_SETUP		mKey_Setup
#define M3D_UI_KEY_RETURN		mKey_Return
#define M3D_UI_KEY_PLAY			mKey_Play
#define M3D_UI_KEY_STOP			mKey_Stop
#define M3D_UI_KEY_PAUSE		mKey_Pause
#define M3D_UI_KEY_NEXT			mKey_Next
#define M3D_UI_KEY_KEYUP		mKey_Keyup
#define M3D_UI_KEY_KEYDOWN		mKey_Keydown
#define M3D_UI_KEY_TEMPOUP		mKey_Tempoup
#define M3D_UI_KEY_TEMPODOWN	mKey_Tempodown
#define M3D_UI_KEY_VOLUP		mKey_Volup
#define M3D_UI_KEY_VOLDOWN		mKey_Voldown
#define M3D_UI_KEY_MELODY_UP	mKey_Melodyup
#define M3D_UI_KEY_MELODY_DOWN	mKey_Melodydown
#define M3D_UI_KEY_RECORD		mKey_Record
#define M3D_UI_KEY_VOCAL		mKey_Vocal
#define M3D_UI_KEY_CHEER		mKey_Cheer
#define M3D_UI_KEY_PREV			mKey_Prev
#define M3D_UI_KEY_MTV			mKey_MTV
#define M3D_UI_KEY_MP3			mKey_MP3
#define M3D_UI_KEY_MOVIE		mKey_Movie
#define M3D_UI_KEY_FAVORITE		mKey_Favorite
#define M3D_UI_KEY_ECHOUP		mKey_other_Melodyup
#define M3D_UI_KEY_ECHODOWN		mKey_other_Melodydown

/*
typedef enum {
	mKey_Power=ShortKey_m::mKey_BaseTotal,
	mKey_Mute,
	mKey_BGV,
	mKey_OSD,
	mKey_Repeat,			//10
	mKey_Home,
	mKey_Replay,
	mKey_Delete,
	mKey_Skip,
	mKey_Num_0,
	mKey_Num_1,
	mKey_Num_2,
	mKey_Num_3,
	mKey_Num_4,
	mKey_Num_5,
	mKey_Num_6,			//20
	mKey_Num_7,
	mKey_Num_8,
	mKey_Num_9,
	mKey_PROG,
	mKey_Clear,
	mKey_Micup,
	mKey_Micdown,
	mKey_Return,		//30
	mKey_Play,
	mKey_Stop,
	mKey_Pause,
	mKey_Next,
	mKey_Keyup,
	mKey_Keydown,
	mKey_Tempoup,
	mKey_Tempodown,
	mKey_Volup,
	mKey_Voldown,		//40
	mKey_Melodyup,
	mKey_Melodydown,
	mKey_Record,
	mKey_Vocal,
	mKey_LastLabel,
	mKey_NextLabel,
	mKey_Ifun,
	mKey_Score,
	mKey_Lyric,
	mKey_Favorite,		//50
	mKey_Pageup,
	mKey_Pagedown,
	mKey_Help,
	mKey_Menu,
	mKey_Setup,
	mKey_List,
	mKey_Echoup,
	mKey_Echodown,
	mKey_Singer,
} ShortKey_m2;

#define M3D_UI_KEY_POWER	mKey_Power
#define M3D_UI_KEY_MUTE		mKey_Mute
#define M3D_UI_KEY_BGV		mKey_BGV
#define M3D_UI_KEY_OSD		mKey_OSD
#define M3D_UI_KEY_REPEAT	mKey_Repeat
#define M3D_UI_KEY_HOME		mKey_Home
#define M3D_UI_KEY_REPLAY	mKey_Replay
#define M3D_UI_KEY_BACKSPACE	mKey_Delete
#define M3D_UI_KEY_SKIP		mKey_Skip
#define M3D_UI_KEY_NUM_0	mKey_Num_0
#define M3D_UI_KEY_NUM_1	mKey_Num_1
#define M3D_UI_KEY_NUM_2	mKey_Num_2
#define M3D_UI_KEY_NUM_3	mKey_Num_3
#define M3D_UI_KEY_NUM_4	mKey_Num_4
#define M3D_UI_KEY_NUM_5	mKey_Num_5
#define M3D_UI_KEY_NUM_6	mKey_Num_6
#define M3D_UI_KEY_NUM_7	mKey_Num_7
#define M3D_UI_KEY_NUM_8	mKey_Num_8
#define M3D_UI_KEY_NUM_9	mKey_Num_9
#define M3D_UI_KEY_PROG		mKey_PROG
#define M3D_UI_KEY_CLEAR	mKey_Clear
#define M3D_UI_KEY_MICUP	mKey_Micup
#define M3D_UI_KEY_MICDOWN	mKey_Micdown
#define M3D_UI_KEY_BGV		mKey_BGV
#define M3D_UI_KEY_RETURN	mKey_Return
#define M3D_UI_KEY_PLAY		mKey_Play
#define M3D_UI_KEY_STOP		mKey_Stop
#define M3D_UI_KEY_PAUSE	mKey_Pause
#define M3D_UI_KEY_NEXT		mKey_Next
#define M3D_UI_KEY_KEYUP	mKey_Keyup
#define M3D_UI_KEY_KEYDOWN	mKey_Keydown
#define M3D_UI_KEY_TEMPOUP	mKey_Tempoup
#define M3D_UI_KEY_TEMPODOWN	mKey_Tempodown
#define M3D_UI_KEY_VOLUP	mKey_Volup
#define M3D_UI_KEY_VOLDOWN	mKey_Voldown
#define M3D_UI_KEY_MELODYUP	mKey_Melodyup
#define M3D_UI_KEY_MELODYDOWN	mKey_Melodydown
#define M3D_UI_KEY_RECORD	mKey_Record
#define M3D_UI_KEY_VOCAL	mKey_Vocal
#define M3D_UI_KEY_LASTLABEL	mKey_LastLabel
#define M3D_UI_KEY_NEXTLABEL	mKey_NextLabel
#define M3D_UI_KEY_IFUN		mKey_Ifun
#define M3D_UI_KEY_SCORE	mKey_Score
#define M3D_UI_KEY_LYRIC	mKey_Lyric
#define M3D_UI_KEY_FAVO		mKey_Favorite
#define M3D_UI_KEY_PAGEUP	mKey_Pageup
#define M3D_UI_KEY_PAGEDOWN	mKey_Pagedown
#define M3D_UI_KEY_HELP		mKey_Help
#define M3D_UI_KEY_MENU		mKey_Menu
#define M3D_UI_KEY_SETUP	mKey_Setup
#define M3D_UI_KEY_List		mKey_List

#define M3D_UI_KEY_SEARCH 9999
#define M3D_UI_KEY_VOL_ADD 9998
#define M3D_UI_KEY_VOL_REDUCE 9997
#define M3D_UI_KEY_FF 9996
#define M3D_UI_KEY_FR 9995
#define M3D_UI_KEY_RADOM 9994

#define M3D_UI_KEY_CANCEL   M3D_UI_KEY_CLEAR
#define M3D_UI_KEY_DELETE   mKey_Delete //M3D_UI_KEY_HELP
*/
#endif

#endif
