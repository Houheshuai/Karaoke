/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKKKEDev.h
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

#ifndef MKKKEDEV_H
#define MKKKEDEV_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{

class MKKKEDev : public MKService , public MKSingleton <MKKKEDev>
{

public:
	
	static const std::string m_name;

	// - commands
	static const std::string m_cmdInit;
	static const std::string m_cmdDeinit;
	static const std::string m_cmdDevChanged;
	static const std::string m_cmdDevDetect;
	static const std::string m_cmdPair;
	static const std::string m_cmdCheck;
	static const std::string m_cmdSetVol;
	static const std::string m_cmdSetEcho;
	static const std::string m_cmdSetSampleRate;
	static const std::string m_cmdGetDevInf;
	static const std::string m_cmdGetStatus;
	static const std::string m_cmdGetVersion;
	static const std::string m_cmdGetSN;
	static const std::string m_cmdGetType;
	static const std::string m_cmdGetChannel;

	// - events
	static const std::string m_eventPlugin;
	static const std::string m_eventPlugout;
	static const std::string m_eventPair;

	// - parameters
	static const std::string m_ParaVersion;
	static const std::string m_ParaModule;
	static const std::string m_ParaSN;
	static const std::string m_ParaCustID;
	static const std::string m_ParaEchoCanChange;
	static const std::string m_ParaVolCanChange;
	static const std::string m_ParaMusicFromDev;
	static const std::string m_ParaConnectStatus;
	static const std::string m_ParaWMICSupport;
	static const std::string m_ParaSampleRate;
	static const std::string m_Para32KSampleRate;
	static const std::string m_Para44KSampleRate;
	static const std::string m_Para48KSampleRate;
	static const std::string m_ParaInChannels;
	static const std::string m_ParaOutChannels;
	
	// - parameter values of 'getAudioType'	
	static const std::string m_audiotype_kkebox;
	static const std::string m_audiotype_kkemini;

	MKKKEDev(void* owner);

	virtual ~MKKKEDev(void);
	
	//----------------------------------------------------------------------------//
	int init(const std::string& channel);

	//----------------------------------------------------------------------------//
	int deinit();

	//----------------------------------------------------------------------------//
	int devHIDPlugin();

	//----------------------------------------------------------------------------//
	int devHIDPlugout();

	//----------------------------------------------------------------------------//
	int devChanged();
	
	//----------------------------------------------------------------------------//
	//- 0 - valid dev, <>0 - not valid
	//----------------------------------------------------------------------------//
	int devDetect(const std::string& path);
	
	//----------------------------------------------------------------------------//
	int pair();
	
	//----------------------------------------------------------------------------//
	int cancelPair();
	
	//----------------------------------------------------------------------------//
	//- 0: valid dev, -1: unvalid, -2: no write permission
	//----------------------------------------------------------------------------//
	int check(const std::string& path);
	
	//----------------------------------------------------------------------------//
	int setVol(int vol);
	
	//----------------------------------------------------------------------------//
	int setEcho(int echo);
	
	//----------------------------------------------------------------------------//
	int setSampleRate(int samplerate);
	
	//----------------------------------------------------------------------------//
	int getSampleRate();
	
	//----------------------------------------------------------------------------//
	//- 1 - connected, 0 - disconnected
	//----------------------------------------------------------------------------//
	int getStatus();

	//----------------------------------------------------------------------------//
	std::string getVersion();
	
	//----------------------------------------------------------------------------//
	std::string getSN();
	
	//----------------------------------------------------------------------------//
	//0x10 - kke box
	//0x11 - letv box
	//0x12 - letv mini
	//0x13 - kke mini wireless
	//0x14 - kke cable
	//----------------------------------------------------------------------------//
	int getModule();
	
	//----------------------------------------------------------------------------//
	const std::string& getAudioType();
	
	//----------------------------------------------------------------------------//
	std::string getChannel();
	
	//----------------------------------------------------------------------------//
	int isEchoCanChange();
	
	//----------------------------------------------------------------------------//
	int isVolCanChange();
	
	//----------------------------------------------------------------------------//
	int isMusicFromTVMate();
	
	//----------------------------------------------------------------------------//
	int isWirelessSupport();
	
	//----------------------------------------------------------------------------//
	int is32KSampleRate();
	
	//----------------------------------------------------------------------------//
	int is44KSampleRate();
	
	//----------------------------------------------------------------------------//
	int is48KSampleRate();
	
	//----------------------------------------------------------------------------//
	int getInChannels();
	
	//----------------------------------------------------------------------------//
	int getOutChannels();
	
};

}
#endif
