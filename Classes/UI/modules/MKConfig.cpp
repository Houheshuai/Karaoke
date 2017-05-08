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

#include "MKString.h"
#include "MKConfig.h"
namespace CEGUI
{
template<> MKConfig* MKSingleton<MKConfig>::ms_Singleton = 0;

const std::string MKConfig::m_name = "config";

// - commands
const std::string MKConfig::m_cmdSave = "save";
const std::string MKConfig::m_cmdLoad = "load";
const std::string MKConfig::m_cmdUnload = "unload";
const std::string MKConfig::m_cmdGetValue = "getvalue";
const std::string MKConfig::m_cmdGetDefaultValue = "getdefaultvalue";
const std::string MKConfig::m_cmdGetMaxValue = "getmaxvalue";
const std::string MKConfig::m_cmdGetMinValue = "getminvalue";
const std::string MKConfig::m_cmdGetStrValue = "getstrvalue";
const std::string MKConfig::m_cmdSetValue = "setvalue";
const std::string MKConfig::m_cmdSetStrValue = "setstrvalue";

// - command parameters
const std::string MKConfig::m_paraSave = "1";
const std::string MKConfig::m_paraNoSave = "0";
const std::string MKConfig::m_paraValue = "value";

MKConfig::MKConfig(void* owner) : MKService(m_name, owner)
{
}

MKConfig::~MKConfig(void)
{
}

//----------------------------------------------------------------------------//
int MKConfig::save()
{
	return exec(m_cmdSave, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKConfig::load(const std::string& filePath)
{
	return exec(m_cmdLoad, filePath);
}

//----------------------------------------------------------------------------//
int MKConfig::unload(int save)
{
	if (save)
		return exec(m_cmdUnload, m_paraSave);
	else
		return exec(m_cmdUnload, m_paraNoSave);
}

//----------------------------------------------------------------------------//
int MKConfig::getValue(const std::string& option)
{
	return exec(m_cmdGetValue, option);
}

//----------------------------------------------------------------------------//
int MKConfig::getDefaultValue(const std::string& option)
{
	return exec(m_cmdGetDefaultValue, option);
}

//----------------------------------------------------------------------------//
int MKConfig::getMaxValue(const std::string& option)
{
	return exec(m_cmdGetMaxValue, option);
}

//----------------------------------------------------------------------------//
int MKConfig::getMinValue(const std::string& option)
{
	return exec(m_cmdGetMinValue, option);
}

//----------------------------------------------------------------------------//
std::string MKConfig::getStringValue(const std::string& option)
{		
	if (exec(m_cmdGetStrValue, option) == 0)
		return getEventParaValue(m_cmdGetStrValue, m_paraValue);
	else
		return "";
}

//----------------------------------------------------------------------------//
int MKConfig::setValue(const std::string& option, int value)
{
	setCmdPara(m_cmdSetValue, option, MKString::valueOf(value));
	return exec(m_cmdSetValue, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKConfig::setStringValue(const std::string& option, const std::string& value)
{
	setCmdPara(m_cmdSetStrValue, option, value);
	return exec(m_cmdSetStrValue, m_nullstr);
}
}
