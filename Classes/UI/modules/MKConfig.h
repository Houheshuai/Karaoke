/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKConfig.h
** Revision : 1.00											
**																	
** Description: MKConfig base on config service
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

#ifndef MKCONFIG_H
#define MKCONFIG_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{
class MKConfig : public MKService , public MKSingleton <MKConfig>
{
public:

	static const std::string m_name;

	// - commands
	static const std::string m_cmdSave;
	static const std::string m_cmdLoad;
	static const std::string m_cmdUnload;
	static const std::string m_cmdGetValue;
	static const std::string m_cmdGetDefaultValue;
	static const std::string m_cmdGetMaxValue;
	static const std::string m_cmdGetMinValue;
	static const std::string m_cmdGetStrValue;
	static const std::string m_cmdSetValue;
	static const std::string m_cmdSetStrValue;

	// - command parameters
	static const std::string m_paraSave;
	static const std::string m_paraNoSave;
	static const std::string m_paraValue;

	MKConfig(void* owner);

	virtual ~MKConfig(void);
	
	//----------------------------------------------------------------------------//
	int save();
	
	//----------------------------------------------------------------------------//
	int load(const std::string& filePath);
	
	//----------------------------------------------------------------------------//
	int unload(int save);
	
	//----------------------------------------------------------------------------//
	int getValue(const std::string& option);
	
	//----------------------------------------------------------------------------//
	int getDefaultValue(const std::string& option);
	
	//----------------------------------------------------------------------------//
	int getMaxValue(const std::string& option);

	//----------------------------------------------------------------------------//
	int getMinValue(const std::string& option);

	//----------------------------------------------------------------------------//
	std::string getStringValue(const std::string& option);
	
	//----------------------------------------------------------------------------//
	int setValue(const std::string& option, int value);
	
	//----------------------------------------------------------------------------//
	int setStringValue(const std::string& option, const std::string& value);
	
};
}
#endif

