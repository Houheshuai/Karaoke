#ifndef _CONFIGPARAM_H
#define _CONFIGPARAM_H

#include <string>

#define MAX_REC_SONG_DEFAULT	   50
#define MAX_FAVO_SONG_DEFAULT	    100
#define MAX_PROG_SONG_DEFAULT	   50 // 10

typedef enum
{
 	OptionSwitch_OFF = 0,
	OptionSwitch_ON,
}OptionSwitch_et;
/*
typedef enum
{
	LanguageOptionValue_EN = 0,
	LanguageOptionValue_CH,
	LanguageOptionValue_RU,
	LanguageOptionValue_NK,
	LanguageOptionValue_VN,
	LanguageOptionValue_INI,
	LanguageOptionValue_Count,
} LanguageOptionValue_et;

typedef enum
{
	DisplayOptionValue_PAL = 0,
	DisplayOptionValue_NTSC,
	DisplayOptionValue_Hdmi480p,
	DisplayOptionValue_Hdmi576p,
	DisplayOptionValue_Hdmi720p,
	DisplayOptionValue_480p,
	DisplayOptionValue_576p,
	DisplayOptionValue_720p,
	DisplayOptionValue_Auto,
	DisplayOptionValue_Count,	
} DisplayOptionValue_et;

typedef enum
{
	AudioOptionValue_Auto = 0,
	AudioOptionValue_Analog,
	AudioOptionValue_Digital,
	AudioOptionValue_Count,
}AudioOptionValue_et;
*/
typedef enum
{
	VocalTypeValue_on = 0,
	VocalTypeValue_off,
	VocalTypeValue_stereo,
	VocalTypeValue_auto,
}VocalTypeValue_et;

typedef enum
{
 	SearchTypeValue_number = 0,
	SearchTypeValue_title,
	SearchTypeValue_singer,
	SearchTypeValue_prog,
	SearchTypeValue_fav,
}SearchTypeValue_et;
/*
typedef enum
{
	BGVTypeValue_off = 0,
	BGVTypeValue_images,
	BGVTypeValue_video,
}BackGroundTypeValue_et;
*/
typedef enum
{
	LyricOptionValue_off = OptionSwitch_OFF,
	LyricOptionValue_on = OptionSwitch_ON,
	LyricOptionValue_main,
	LyricOptionValue_label,
}LyricOptionValue_et;

typedef enum
{
	SongEncode_Type_None = -1,				// no this option in config.xml
	SongEncode_Type_CID = 0,
	SongEncode_Type_MachineSN = 1,
	SongEncode_Type_Both,       // 
} SongEncodeType_t;

typedef enum
{
	StaffNumberValue_None = -1,
	StaffNumberValue_Single = 1,
	StaffNumberValue_PKMode = 2,
}StaffNumberValue_et;

class ConfigParam
{
public:
	static std::string appOption_Customer;
	static std::string appOption_FontFiles;
	//UI
	static std::string appOption_MyDownload;
	static std::string appOption_GameMenu;
	
	static std::string appOption_MaxRec;
	static std::string appOption_MaxFav;
	static std::string appOption_MaxRes;
	
	static std::string appOption_Display;
	static std::string appOption_DisplayAutoValue;
	static std::string appOption_Audio;
	static std::string appOption_Language;
	static std::string appOption_Bgv;
	static std::string appOption_ScoreLevel;
	static std::string appOption_AbbLanguage;
	
	static std::string appOption_VocalType;
	
	static std::string appOption_MusicVol;
	static std::string appOption_MicVol1;
	static std::string appOption_MicVol2;
	static std::string appOption_WMicVol1;
	static std::string appOption_WMicVol2;
	static std::string appOption_Echo;
	static std::string appOption_Tempo;
	static std::string appOption_KeyVol;
	
	static std::string appOption_AccomanyVol;
	static std::string appOption_VoiceVol;
	static std::string appOption_TestMode;
	
	static std::string appOption_Ifun;
	static std::string appOption_Score;
	static std::string appOption_Lyric;
	static std::string appOption_StaffNum;
	static std::string appOption_PlayBarTimeOut;
	
	static std::string appOption_PrivateKey;
	static std::string appOption_SNType;
	static std::string appOption_ProductCID;
	
	static std::string appOption_SearchType;
	
	static std::string appOption_InputLatency;
	static std::string appOption_OutputLatency;
};
#endif
