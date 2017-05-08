/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKService.h
** Revision : 1.00											
**																	
** Description: service base class
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

#ifndef MKSERVICE_H
#define MKSERVICE_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKSingleton.h"

namespace CEGUI
{
class MKService
{

public:

	static const std::string m_nullstr;
	ezServiceHandle_t* m_hdle;

	MKService(const std::string& name, void* owner);

	virtual ~MKService(void);

	//----------------------------------------------------------------------------//
	int setEventCallback(const std::string& eventName, handleServiceEventCallback_t cb);
	
	//----------------------------------------------------------------------------//
	void setUserUpdate(ezServiceMethod_update_t cb);
	
	//----------------------------------------------------------------------------//
	int exec(const std::string& cmd, const std::string& para);
	
	//----------------------------------------------------------------------------//
	int sync(const std::string& cmd, const std::string& para);
	
	//----------------------------------------------------------------------------//
	int queryEvent(const std::string& event);
		
	//----------------------------------------------------------------------------//
	int pushEvent(const std::string& event, int result);
		
	//----------------------------------------------------------------------------//
	int fireEvent(const std::string& event);
		
	//----------------------------------------------------------------------------//
	int clearEvents();
		
	//----------------------------------------------------------------------------//
	int setCmdPara(const std::string& cmd, const std::string& para, const std::string& value);
		
	//----------------------------------------------------------------------------//
	std::string getCmdParaValue(const std::string& cmd, const std::string& para);
		
	//----------------------------------------------------------------------------//
	std::string getCmdParaValueAt(const std::string& cmd, int pos);
		
	//----------------------------------------------------------------------------//
	int getCmdParaCount(const std::string& cmd);
		
	//----------------------------------------------------------------------------//
	int removeCmdPara(const std::string& cmd, const std::string& para);
		
	//----------------------------------------------------------------------------//
	int clearCmdPara(const std::string& cmd);
		
	//----------------------------------------------------------------------------//
	int setEventPara(const std::string& event, const std::string& para, const std::string& value);
		
	//----------------------------------------------------------------------------//
	std::string getEventParaValue(const std::string& event, const std::string& para);

	//----------------------------------------------------------------------------//
	int getEventParaIntValue(const std::string& event, const std::string& para);
		
	//----------------------------------------------------------------------------//
	std::string getEventParaValueAt(const std::string& event, int pos);
		
	//----------------------------------------------------------------------------//
	int getEventParaCount(const std::string& event);
		
	//----------------------------------------------------------------------------//
	int removeEventPara(const std::string& event, const std::string& para);
		
	//----------------------------------------------------------------------------//
	int clearEventPara(const std::string& event);
		
	//----------------------------------------------------------------------------//
	int setThread(int onoff);
	
	//----------------------------------------------------------------------------//	
	int update(int timeElapsed);

};
}
#endif

