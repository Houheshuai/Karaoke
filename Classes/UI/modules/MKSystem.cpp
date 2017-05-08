/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKSystem.h
** Revision : 1.00											
**																	
** Description: MKSystem base on system service
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
************************ HOWTO *******************************
** 
*/

#include "MKString.h"
#include "MKSystem.h"
namespace CEGUI
{
template<> MKSystem* MKSingleton<MKSystem>::ms_Singleton = 0;
const std::string MKSystem::m_name = "system";
int MKSystem::m_bgPicVisible = true;

// - commands
const std::string MKSystem::m_cmdInit = "init";
const std::string MKSystem::m_cmdDeInit = "deinit";
const std::string MKSystem::m_cmdInitGL = "initGL";
const std::string MKSystem::m_cmdDeInitGL = "deinitGL";
const std::string MKSystem::m_cmdClearScreen = "clearscreen";
const std::string MKSystem::m_cmdSetScreen = "setscreen";
const std::string MKSystem::m_cmdAutoFreeTex = "autofreetex";
const std::string MKSystem::m_cmdShowScreenBg = "showscreenbg";
const std::string MKSystem::m_cmdHideScreenBg = "hidescreenbg";
const std::string MKSystem::m_cmdRenderScreenBg = "renderscreenbg";
const std::string MKSystem::m_cmdXCopy = "xcopy";
const std::string MKSystem::m_cmdXRemove = "xremove";

// - command parameters
const std::string MKSystem::m_paraResPath = "respath";
const std::string MKSystem::m_paraScreenWidth = "screenwidth";
const std::string MKSystem::m_paraScreenHeight = "screenheight";
const std::string MKSystem::m_paraResWidth = "reswidth";
const std::string MKSystem::m_paraResHeight = "resheight";
const std::string MKSystem::m_paraScreenX = "screenx";
const std::string MKSystem::m_paraScreenY = "screeny";

MKSystem::MKSystem(void* owner) : MKService(m_name, owner)
{
}

MKSystem::~MKSystem(void)
{
}

//----------------------------------------------------------------------------//
int MKSystem::init(const std::string& resPath, int resWidth, int resHeight)
{
	setCmdPara(m_cmdInit, m_paraResPath, resPath);
	setCmdPara(m_cmdInit, m_paraResWidth, MKString::valueOf(resWidth));
	setCmdPara(m_cmdInit, m_paraResHeight, MKString::valueOf(resHeight));
	return exec(m_cmdInit, m_nullstr);
}

//----------------------------------------------------------------------------//	
int MKSystem::deinit()
{
	int ret = exec(m_cmdDeInit, m_nullstr);
	return ret;
}

//----------------------------------------------------------------------------//
int MKSystem::initGL(int scrw, int scrh)
{
	setCmdPara(m_cmdInitGL, m_paraScreenWidth, MKString::valueOf(scrw));
	setCmdPara(m_cmdInitGL, m_paraScreenHeight, MKString::valueOf(scrh));
	return exec(m_cmdInitGL, m_nullstr);
}

//----------------------------------------------------------------------------//	
int MKSystem::deinitGL()
{
	return exec(m_cmdDeInitGL, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKSystem::clearScreen()
{
	return exec(m_cmdClearScreen, m_nullstr);
}

//----------------------------------------------------------------------------//	
int MKSystem::setScreen(int x, int y, int w, int h)
{
	setCmdPara(m_cmdSetScreen, m_paraScreenX, MKString::valueOf(x));
	setCmdPara(m_cmdSetScreen, m_paraScreenY, MKString::valueOf(y));
	setCmdPara(m_cmdSetScreen, m_paraScreenWidth, MKString::valueOf(w));
	setCmdPara(m_cmdSetScreen, m_paraScreenHeight, MKString::valueOf(h));
	return exec(m_cmdSetScreen, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKSystem::showScreenBgPic(const std::string& path)
{
	return exec(m_cmdShowScreenBg, path);
}

//----------------------------------------------------------------------------//
int MKSystem::hideScreenBgPic()
{
	return exec(m_cmdHideScreenBg, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKSystem::renderScreenBgPic()
{
	if (m_bgPicVisible)
		return exec(m_cmdRenderScreenBg, m_nullstr);
	else
		return -1;
}

//----------------------------------------------------------------------------//
void MKSystem::setBgPicVisible(int setting)
{
	m_bgPicVisible = setting;
}

//----------------------------------------------------------------------------//
int MKSystem::xcopy(const std::string& dst, const std::string& src)
{
	setCmdPara(m_cmdXCopy, "dst", dst);
	setCmdPara(m_cmdXCopy, "src", src);
	return exec(m_cmdXCopy, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKSystem::xremove(const std::string& path)
{
	return exec(m_cmdXRemove, path);
}
}
