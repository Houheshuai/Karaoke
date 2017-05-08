/*!*********************************************************************************************************************
\file         PVRCore\Log.h
\author       PowerVR by Imagination, Developer Technology Team
\copyright    Copyright (c) Imagination Technologies Limited.
\brief         This file contains Logging functionality. Look here if plan to use custom logging. Default logging accessed through
              the global Log functor (Log("a message")).
***********************************************************************************************************************/
#pragma once
namespace pvr {

	//!\cond NO_DOXYGEN
struct PointerLocationStore
{
	short x; short y;
};
//!\endcond

/*!*********************************************************************************************************************
\brief        Mouse pointer coordinates.
***********************************************************************************************************************/
class PointerLocation : public PointerLocationStore
{
public:
	PointerLocation() { }
	PointerLocation(const PointerLocationStore& st) : PointerLocationStore(st) { }
	PointerLocation(short x, short y) { this->x = x; this->y = y; }
};

/*!*********************************************************************************************************************
\brief        Enumeration representing a simplified, unified input event designed to unify simple actions across different
devices.
***********************************************************************************************************************/
namespace SimplifiedInput {
/*!*********************************************************************************************************************
\brief        Enumeration representing a simplified, unified input event designed to unify simple actions across different
devices.
***********************************************************************************************************************/
enum Enum
{
	NONE = 0,
	Left = 1,  //!<Left arrow, Swipe left
	Right = 2, //!<Right arrow, Swipe left
	Up = 3,		//!<Up arrow, Swipe left
	Down = 4,	//!<Down arrow, Swipe left
	ActionClose = 5, //!<Esc, Q, Android back, iOS home
	Action1 = 6,	 //!<Space, Enter, Touch screen center
	Action2 = 7,	//!<Key 1, Touch screen left side
	Action3 = 8,	//!<Key 2, Touch screen right side
};
};

/*!*********************************************************************************************************************
\brief        Enumeration representing a System Event (quit, Gain focus, Lose focus).
***********************************************************************************************************************/
namespace SystemEvent {
enum Enum
{
	SystemEvent_Quit, SystemEvent_LoseFocus, SystemEvent_GainFocus
};
}

/*!*********************************************************************************************************************
\brief        Enumeration representing a Keyboard Key.
***********************************************************************************************************************/
namespace Keys {

//Whenever possible, keys get ASCII values of their default (non-shifted) values of a default US keyboard.
enum Enum : unsigned char
{
	Backspace = 0x08,
	Tab = 0x09,
	Return = 0x0D,

	Shift = 0x10, Control = 0x11, Alt = 0x12,

	Pause = 0x13,
	PrintScreen = 0x2C,
	CapsLock = 0x14,
	Escape = 0x1B,
	Space = 0x20,

	PageUp = 0x21, PageDown = 0x22, End = 0x23, Home = 0x24,

	Left = 0x25, Up = 0x26, Right = 0x27, Down = 0x28,

	Insert = 0x2D, Delete = 0x2E,

	//ASCII-Based
	Key0 = 0x30, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,

	A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M,
	N = 0x4E, O, P, Q, R, S, T, U, V, W, X, Y, Z,


	Num0 = 0x60, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, NumPeriod,

	F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

	SystemKey1 = 0x5B, SystemKey2 = 0x5D,
	WindowsKey = 0x5B, MenuKey = 0x5D, //ALIASES

	NumMul = 0x6A, NumAdd = 0x6B, NumSub = 0x6D, NumDiv = 0x6E,
	NumLock = 0x90, ScrollLock = 0x91,

	Semicolon = 0xBA, Equals = 0xBB, Minus = 0xBD,

	Slash = 0xBF,

	Comma = 0xBC, Period = 0xBE,

	Backquote = 0xC0,

	SquareBracketLeft = 0xDB, SquareBracketRight = 0xDD, Quote = 0xDE, Backslash = 0xDC,

	MaxNumberOfKeyCodes,
	Unknown = 0xFF


};

}
}