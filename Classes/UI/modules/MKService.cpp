/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKService.cpp
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
#include <stdlib.h>
#include "MKService.h"
#include "serviceMgr.h"

namespace CEGUI
{
const std::string MKService::m_nullstr = "";

MKService::MKService(const std::string& name, void* owner)
{
	m_hdle = serviceMgr_create(name.c_str(), owner);
}

MKService::~MKService(void)
{
	serviceMgr_destroy(m_hdle);
}

//----------------------------------------------------------------------------//
int MKService::setEventCallback(const std::string& eventName, handleServiceEventCallback_t cb)
{
	return m_hdle->setEventCallback(m_hdle, eventName.c_str(), cb);
}

//----------------------------------------------------------------------------//
void MKService::setUserUpdate(ezServiceMethod_update_t cb)
{
	m_hdle->setUserUpdate(m_hdle, cb);
}

//----------------------------------------------------------------------------//
int MKService::exec(const std::string& cmd, const std::string& para)
{
	return m_hdle->exec(m_hdle,cmd.c_str(),para.c_str());
}

//----------------------------------------------------------------------------//
int MKService::sync(const std::string& cmd, const std::string& para)
{
	return m_hdle->sync(m_hdle,cmd.c_str(),para.c_str());
}

//----------------------------------------------------------------------------//
int MKService::queryEvent(const std::string& event)
{
	return m_hdle->queryEvent(m_hdle,event.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::pushEvent(const std::string& event, int result)
{
	return (int)m_hdle->pushEvent(m_hdle,event.c_str(), (ezServiceEventResult_et)result);
}
	
//----------------------------------------------------------------------------//
int MKService::fireEvent(const std::string& event)
{
	return m_hdle->fireEvent(m_hdle,event.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::clearEvents()
{
	return m_hdle->clearEvents(m_hdle);
}
	
//----------------------------------------------------------------------------//
int MKService::setCmdPara(const std::string& cmd, const std::string& para, const std::string& value)
{
	return m_hdle->setCmdPara(m_hdle,cmd.c_str(),para.c_str(),value.c_str());
}
	
//----------------------------------------------------------------------------//
std::string MKService::getCmdParaValue(const std::string& cmd, const std::string& para)
{
	const char* val = m_hdle->getCmdParaValue(m_hdle,cmd.c_str(),para.c_str());
	if (val != NULL)
		return std::string(val);
	else
		return std::string("");
}
	
//----------------------------------------------------------------------------//
std::string MKService::getCmdParaValueAt(const std::string& cmd, int pos)
{
	const char* val = m_hdle->getCmdParaValueAt(m_hdle,cmd.c_str(),pos);
	if (val != NULL)
		return std::string(val);
	else
		return m_nullstr;
}
	
//----------------------------------------------------------------------------//
int MKService::getCmdParaCount(const std::string& cmd)
{
	return m_hdle->getCmdParaCount(m_hdle,cmd.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::removeCmdPara(const std::string& cmd, const std::string& para)
{
	return m_hdle->removeCmdPara(m_hdle,cmd.c_str(),para.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::clearCmdPara(const std::string& cmd)
{
	return m_hdle->clearCmdPara(m_hdle,cmd.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::setEventPara(const std::string& event, const std::string& para, const std::string& value)
{
	return m_hdle->setEventPara(m_hdle,event.c_str(),para.c_str(), value.c_str());
}
	
//----------------------------------------------------------------------------//
std::string MKService::getEventParaValue(const std::string& event, const std::string& para)
{
	const char* val = m_hdle->getEventParaValue(m_hdle,event.c_str(),para.c_str());
	if (val != NULL)
		return std::string(val);
	else
		return m_nullstr;
}
	
//----------------------------------------------------------------------------//
int MKService::getEventParaIntValue(const std::string& event, const std::string& para)
{
	const char* val = m_hdle->getEventParaValue(m_hdle,event.c_str(),para.c_str());
	if (val != NULL)
		return atoi(val);
	else
		return -1;
}
	
//----------------------------------------------------------------------------//
std::string MKService::getEventParaValueAt(const std::string& event, int pos)
{
	const char* val = m_hdle->getEventParaValueAt(m_hdle,event.c_str(),pos);
	if (val != NULL)
		return std::string(val);
	else
		return m_nullstr;
}
	
//----------------------------------------------------------------------------//
int MKService::getEventParaCount(const std::string& event)
{
	return m_hdle->getEventParaCount(m_hdle,event.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::removeEventPara(const std::string& event, const std::string& para)
{
	return m_hdle->removeEventPara(m_hdle,event.c_str(),para.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::clearEventPara(const std::string& event)
{
	return m_hdle->clearEventPara(m_hdle,event.c_str());
}
	
//----------------------------------------------------------------------------//
int MKService::setThread(int onoff)
{
	return m_hdle->setThread(m_hdle,onoff);
}

//----------------------------------------------------------------------------//	
int MKService::update(int timeElapsed)
{
	return m_hdle->update(m_hdle,timeElapsed);
}	
}
