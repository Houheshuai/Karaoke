//---------------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Log.h
//																	
// Description: log form special information to other form use
// 
//---------------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//---------------------------------------------------------------------------------//
//
#ifndef _M3D_LOG_H_
#define _M3D_LOG_H_

#include "CEGUI/CEGUIString.h"
#include "CEGUI/CEGUIWindow.h"

#include <unordered_map>

namespace	CEGUI
{

class M3D_Log
{
public:
	M3D_Log(void);
	~M3D_Log(void);

	void reset();

	void setParamInt(std::string key, int value);
	void setParamFloat(std::string key, float value);
	void setParamString(std::string key, std::string value);

	int getParamInt(std::string key, int defaultValue);
	float getParamFloat(std::string key, float defaultValue);
	std::string getParamString(std::string key, std::string defaultValue);
	

private:
	std::unordered_map<std::string, int> d_ParamMapInt;
	std::unordered_map<std::string, float> d_ParamMapFloat;
	std::unordered_map<std::string, std::string> d_ParamMapString;
};

}
#endif

