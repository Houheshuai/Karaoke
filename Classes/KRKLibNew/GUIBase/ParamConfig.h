#ifndef _PARAMCONFIG_H_
#define _PARAMCONFIG_H_

#include "CEGUI/CEGUIUDim.h"
#include <string>
#include <unordered_map>

namespace CEGUI
{
class ParamConfig
{ 
public: 
	static CEGUISize DesignSize;		//表示设计的分辨率
	static CEGUISize DisplaySize;	//表示窗口大小

	static float ViewPortX;
	static float ViewPortY;
	static float ViewPortW;
	static float ViewPortH;

	//static std::string RootFilePath;
	//static std::string ResFilePath;
	static std::string SysDataPath;
	static std::string AppDataPath;
	static std::string BuildInPath;
	static std::string GameFilePath;
	static std::unordered_map<std::string, std::string> SerialMap;
	static std::string SoftwareVession;
	static std::string SystemDataVession;
	#ifdef PLATFORM_UNIX
	static std::string UIFontName;  
	#endif
				

	static std::string FontName_English;
	static std::string FontName_CJK;
	static std::string FontName_Bengali;
	static std::string FontName_Devanagari;
	static std::string FontName_Gujarati;
	static std::string FontName_Kannada;
	static std::string FontName_Khmer;
	static std::string FontName_Malayalam;
	static std::string FontName_Tamil;
	static std::string FontName_Telugu;
	static std::string FontName_Sinhala;
	static std::string FontName_Arabic;
	static std::string FontName_Gurmukhi;
	static std::string FontName_Reserve;
	//static std::unordered_map<std::string, std::string> UIFontName;	
	
	static int wifiStatus;
	static std::string wifiName;
	static int wifiIntensity;
	static std::string wifiIP;
	
	static std::string BuildInUrl;
	static std::string ExternUrl;
	static std::string OnlineAPKVersion;
	
    static ParamConfig *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static ParamConfig instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    } 

    void count_increase () {count_ ++;} 
    int count () const {return count_;} 

	void SetDisplaySize(int w, int h);

private: 
    ParamConfig ();
    ~ParamConfig ();

    static ParamConfig *p_instance_; 
    int count_; 
}; 


}

#endif

