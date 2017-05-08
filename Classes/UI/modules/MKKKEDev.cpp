/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKKKEDev.cpp
** Revision : 1.00											
**																	
** Description: kkedev api base on kkedev service
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
#include "MKKKEDev.h"

namespace CEGUI
{

template<> MKKKEDev* MKSingleton<MKKKEDev>::ms_Singleton = 0;

const std::string MKKKEDev::m_name = "kkedev";

// - commands
const std::string MKKKEDev::m_cmdInit = "init";
const std::string MKKKEDev::m_cmdDeinit = "deinit";
const std::string MKKKEDev::m_cmdDevChanged = "devchanged";
const std::string MKKKEDev::m_cmdDevDetect = "detect";
const std::string MKKKEDev::m_cmdPair = "pair";
const std::string MKKKEDev::m_cmdCheck = "check";
const std::string MKKKEDev::m_cmdSetVol = "setvol";
const std::string MKKKEDev::m_cmdSetEcho = "setecho";
const std::string MKKKEDev::m_cmdSetSampleRate = "setsamplerate";
const std::string MKKKEDev::m_cmdGetDevInf = "getdevinf";
const std::string MKKKEDev::m_cmdGetStatus = "getstatus";
const std::string MKKKEDev::m_cmdGetVersion = "getversion";
const std::string MKKKEDev::m_cmdGetSN = "getsn";
const std::string MKKKEDev::m_cmdGetType = "gettype";
const std::string MKKKEDev::m_cmdGetChannel = "getchannel";

// - events
const std::string MKKKEDev::m_eventPlugin = "plugin";
const std::string MKKKEDev::m_eventPlugout = "plugout";
const std::string MKKKEDev::m_eventPair = "pair";

// - parameters
const std::string MKKKEDev::m_ParaVersion = "version";
const std::string MKKKEDev::m_ParaModule = "module";
const std::string MKKKEDev::m_ParaSN = "sn";
const std::string MKKKEDev::m_ParaCustID = "custid";
const std::string MKKKEDev::m_ParaEchoCanChange = "echoenabled";
const std::string MKKKEDev::m_ParaVolCanChange	 = "volenabled";
const std::string MKKKEDev::m_ParaMusicFromDev = "musicfromdev";
const std::string MKKKEDev::m_ParaConnectStatus = "connectstatus";
const std::string MKKKEDev::m_ParaWMICSupport = "wirelesssupport";
const std::string MKKKEDev::m_ParaSampleRate = "samplerate";
const std::string MKKKEDev::m_Para32KSampleRate = "32K";
const std::string MKKKEDev::m_Para44KSampleRate = "44K";
const std::string MKKKEDev::m_Para48KSampleRate = "48K";
const std::string MKKKEDev::m_ParaInChannels = "inchannels";
const std::string MKKKEDev::m_ParaOutChannels = "outchannels";

// - parameter values of 'getAudioType' 
const std::string MKKKEDev::m_audiotype_kkebox = "kkebox";
const std::string MKKKEDev::m_audiotype_kkemini = "kkemini";

MKKKEDev::MKKKEDev(void* owner) : MKService(m_name, owner)
{
}

MKKKEDev::~MKKKEDev(void)
{
}

//----------------------------------------------------------------------------//
int MKKKEDev::init(const std::string& channel)
{
	return exec(m_cmdInit, channel);
}

//----------------------------------------------------------------------------//
int MKKKEDev::deinit()
{
	return exec(m_cmdDeinit, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKKKEDev::devHIDPlugin()
{
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::devHIDPlugout()
{
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::devChanged()
{
	return exec(m_cmdDevChanged, m_nullstr);
}

//----------------------------------------------------------------------------//
//- 0 - valid dev, <>0 - not valid
//----------------------------------------------------------------------------//
int MKKKEDev::devDetect(const std::string& path)
{
	return exec(m_cmdDevDetect, path);
}

//----------------------------------------------------------------------------//
int MKKKEDev::pair()
{
	return exec(m_cmdPair, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKKKEDev::cancelPair()
{
	return exec(m_cmdPair, "cancel");
}

//----------------------------------------------------------------------------//
//- 0: valid dev, -1: unvalid, -2: no write permission
//----------------------------------------------------------------------------//
int MKKKEDev::check(const std::string& path)
{
	return exec(m_cmdCheck, path);
}

//----------------------------------------------------------------------------//
int MKKKEDev::setVol(int vol)
{
	return exec(m_cmdSetVol, MKString::valueOf(vol));
}

//----------------------------------------------------------------------------//
int MKKKEDev::setEcho(int echo)
{
	return exec(m_cmdSetEcho, MKString::valueOf(echo));
}

//----------------------------------------------------------------------------//
int MKKKEDev::setSampleRate(int samplerate)
{
	return exec(m_cmdSetSampleRate, MKString::valueOf(samplerate));
}

//----------------------------------------------------------------------------//
int MKKKEDev::getSampleRate()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaSampleRate);
	}
	return 0;
}

//----------------------------------------------------------------------------//
//- 1 - connected, 0 - disconnected
//----------------------------------------------------------------------------//
int MKKKEDev::getStatus()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaConnectStatus);
	}
	return 0;
}

//----------------------------------------------------------------------------//
std::string MKKKEDev::getVersion()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetDevInf, m_ParaVersion);
	}
	else
		return "";
}

//----------------------------------------------------------------------------//
std::string MKKKEDev::getSN()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetDevInf, m_ParaSN);
	}
	return "";
}

//----------------------------------------------------------------------------//
//0x10 - kke box
//0x11 - letv box
//0x12 - letv mini
//0x13 - kke mini wireless
//0x14 - kke cable
//----------------------------------------------------------------------------//
int MKKKEDev::getModule()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaModule);
	}
	return 0;
}

//----------------------------------------------------------------------------//
const std::string& MKKKEDev::getAudioType()
{
	if (isMusicFromTVMate() == 1)
		return m_audiotype_kkemini;
	else
		return m_audiotype_kkebox;
}

//----------------------------------------------------------------------------//
std::string MKKKEDev::getChannel()
{
	if (exec(m_cmdGetChannel, m_nullstr) == 0)
		return getEventParaValue(m_cmdGetChannel, m_ParaCustID);
	else
		return "";
}

//----------------------------------------------------------------------------//
int MKKKEDev::isEchoCanChange()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaEchoCanChange);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::isVolCanChange()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaVolCanChange);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::isMusicFromTVMate()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaMusicFromDev);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::isWirelessSupport()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaWMICSupport);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::is32KSampleRate()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_Para32KSampleRate);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::is44KSampleRate()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_Para44KSampleRate);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::is48KSampleRate()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_Para48KSampleRate);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::getInChannels()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaInChannels);
	}
	return 0;
}

//----------------------------------------------------------------------------//
int MKKKEDev::getOutChannels()
{
	if (exec(m_cmdGetDevInf, m_nullstr) == 0)
	{
		return getEventParaIntValue(m_cmdGetDevInf, m_ParaOutChannels);
	}
	return 0;
}

}