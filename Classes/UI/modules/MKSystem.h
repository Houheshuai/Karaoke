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

#ifndef MKSYSTEM_H
#define MKSYSTEM_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{
class MKSystem : public MKService , public MKSingleton <MKSystem>
{
	
public:

	static const std::string m_name;
	static int m_bgPicVisible;
	
	// - commands
	static const std::string m_cmdInit;
	static const std::string m_cmdDeInit;
	static const std::string m_cmdInitGL;
	static const std::string m_cmdDeInitGL;
	static const std::string m_cmdClearScreen;
	static const std::string m_cmdSetScreen;
	static const std::string m_cmdAutoFreeTex;
	static const std::string m_cmdShowScreenBg;
	static const std::string m_cmdHideScreenBg;
	static const std::string m_cmdRenderScreenBg;
	static const std::string m_cmdXCopy;
	static const std::string m_cmdXRemove;
	
	// - command parameters
	static const std::string m_paraResPath;
	static const std::string m_paraScreenWidth;
	static const std::string m_paraScreenHeight;
	static const std::string m_paraResWidth;
	static const std::string m_paraResHeight;
	static const std::string m_paraScreenX;
	static const std::string m_paraScreenY;

	MKSystem(void* owner);

	virtual ~MKSystem(void);
	
	//----------------------------------------------------------------------------//
	int init(const std::string& resPath, int resWidth, int resHeight);
	
	//----------------------------------------------------------------------------//	
	int deinit();
	
	//----------------------------------------------------------------------------//
	int initGL(int scrw, int scrh);
	
	//----------------------------------------------------------------------------//	
	int deinitGL();
	
	//----------------------------------------------------------------------------//
	int clearScreen();
	
	//----------------------------------------------------------------------------//	
	int setScreen(int x, int y, int w, int h);
	
	//----------------------------------------------------------------------------//
	int showScreenBgPic(const std::string& path);
	
	//----------------------------------------------------------------------------//
	int hideScreenBgPic();
	
	//----------------------------------------------------------------------------//
	int renderScreenBgPic();
	
	//----------------------------------------------------------------------------//
	void setBgPicVisible(int setting);
	
	//----------------------------------------------------------------------------//
	int xcopy(const std::string& dst, const std::string& src);
	
	//----------------------------------------------------------------------------//
	int xremove(const std::string& path);
};
}
#endif

