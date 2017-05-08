//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Action.cpp
//																	
// Description: basic class for action running
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#pragma once

#ifndef M3D_ACTION_H
#define M3D_ACTION_H

namespace CEGUI
{

enum FORM_TRANSITION_ANIMATION
{
	ANIMATION_NONE = 0,

	FADEIN_FADEOUT = 0x4001,
	LEFTIN_LEFTOUT,
	RIGHTIN_RIGHTOUT,
	TURNIN_TURNOUT,

};

class M3D_Action
{
public:
	M3D_Action();
	~M3D_Action();

	//¶¯»­²ÎÊý
	FORM_TRANSITION_ANIMATION actionType;



};

}

#endif
