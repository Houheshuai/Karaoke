/*
** application config							
**
** Filename : appConfig.c
**																	
** Description: GUI application
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
*/
#include <gui/iapi/GuiBase.h>
#include <gui/iapi/GuiApp.h>
#include <gui/widgets/GuiWidgets.h>
#include <lib/ezbase/ez_config.h>
#include "appConfig.h"

#define isSettingsConfig()	(strcmp(ez_config_get_config_name(appMICConfig.handle), appMICConfig.configs[appMIC_Config_Settings]) == 0)

/* 
* config handler 
*/
static appMICConfig_t appMICConfig = 
{
	NULL, 	/* handle */
		
	{			/* configs */
		"Settings",  
		"FontCaches",
		"KeyMap",
	},
	{			/* setting options */
		"Customer",  
		"Display",  
		"DisplaySize",
		"DisplayValid",
		"DisplayRefreshRate",
		"DisplayAutoValue",
		"ScoreLevel",
		"Language", 
		"AbbLanguage",
		"PlayMode",
		"Bgv",
		"Audio",
		"FontFiles",
		"FontLan",
		
		//player
		"MusParseType",
		"Mute",
		"KeyVol",
		"Tempo",
		"Rhythm",
		"VoiceVol",
		"AccomanyVol",
		"TotalVol",
		"RecVol",
		"Echo",
		"MicVol1",
		"MicVol2",
		"WMicVol1",
		"WMicVol2",
		"InChannels",
		"OutChannels",
		"InRate",
		"OutRate",
		"Latency",
		
		//not need save
		"Rec",
		"VocalType",
		"ResetVocal",
		"Repeat",

		"Ifun",
		"Score",
		"Lyric",

		"StaffNum",
		
		"SearchType",

		"TestMode",
		"MyDownload",
		"GameMenu",
		"TitleMenu",
		"TitleMenuLan",
		"NoTitleInLan",
		"LanguageListTop",
		"SingerLanMenu",
		"MUKUpdate",
		"SNType",

		"ADStrings",
		"TvSysDefault",
		"NoPICBG",
		"PackBGV",

		"MaxRec",
		"MaxFav",
		"MaxRes",

		"ShortCutInFormSearch",
		"DefaultSongLanguage",
		"DefaultSingerLanguage",
		
		"NoRec",
		"MyDownloadUnicodeSort",
		"MyDownloadIME",

		"PinyinSortType",
		"NullSingerName",
		"NoSingerSongList",
		"LeaderSong",
		"TextPlayerEnable",
		"ScoreRank",
		"KoreanIME",
		"NoExtBGV",
		"PlayBarTimeOut",
		"LyricBrushDelay",
		"OKFProductID",
		"UniqueCID",
		"ProductCID",
		"IndianSongShow",
		"SingerPicLocation",
	},
	
	{VOD_RES_PATH},		/* current res file path */
	{VOD_KARAOKE_PATH_INT},		/* current karaoke path */
	{VOD_SYSDB_PATH}, 	/* current karaoke path */
		
	{
		VOD_RES_PATH, 
		VOD_KARAOKE_PATH_INT, 
		VOD_UPDATE_PATH, 
		VOD_KARAOKE_PATH_EXT, 
		VOD_MYPHOTO_PATH,
		VOD_MYDOWNLOAD_PATH,
		VOD_UPDATESONG_PATH,
		VOD_SYSDB_PATH,
		VOD_MYBGV_PATH,
		VOD_INTBGV_PATH,
		VOD_INTPHOTO_PATH,
	},
};

/* 
* setup menu options, these option can not be reset after config load
*	you must add option here if it display in setup menu 
*/
int setupMenuOptions[] = 
{
	appMIC_Option_Display,
	appMIC_Option_ScoreLevel,
	appMIC_Option_Language,
	appMIC_Option_Bgv,
	appMIC_Option_Audio,
	appMIC_Option_PlayMode,	
	appMIC_Option_MyDownload,
	appMIC_Option_GameMenu,
	appMIC_Option_TitleMenu,
	appMIC_Option_DisplayRefreshRate,
	appMIC_Option_DisplayAutoValue,
};

/*
 * Function name  	: appConfig_setPath
 * Arguments      	: type - path type
 *									Path - path string
 * Return         	: none
 * Description    	: set path
 *					
*/
void appConfig_setPath(int type, const char* Path)
{
	appMICConfig_t* appconfig = &appMICConfig;

	if (type < APPMIC_PATH_COUNT)
	{
		memset(appconfig->pathSetup[type], 0, sizeof(appconfig->pathSetup[type]));
		if (Path != NULL)
			strncpy(appconfig->pathSetup[type], Path, sizeof(appconfig->pathSetup[type])-1);
	}
}

/*
 * Function name  	: appConfig_getPath
 * Arguments      	: type - path type
 * Return         	: return True;
 * Description    	: get path string
 *					
*/
char *appConfig_getPath(int type)
{
	if (type < APPMIC_PATH_COUNT && strlen(appMICConfig.pathSetup[type]))
		return appMICConfig.pathSetup[type];
	else
		return NULL;
}

/*
 * Function name  	: appConfig_checkResPath
 * Arguments      	: resPath - res file path
 * Return         	: 1 - exist, 0 - not exist
 * Description    	: check resource file exist or not
 *					
*/
int appConfig_checkResPath(const char* resPath)
{
	appMICConfig_t* appconfig = &appMICConfig;
	int lan = appConfig_getOptionValue(appMIC_Option_Language);
	int disp = appConfig_getDisplayOptionValue();
	char* slan;
	char* sdisp;
			
	if (lan >= LanguageOptionValue_Count)
		lan = LanguageOptionValue_EN;
	if (disp >= DisplayOptionValue_Count)
		disp = DisplayOptionValue_Hdmi720p;
	
	slan = appConfig_getOptionItemStr(appMIC_Option_AbbLanguage, lan);
	sdisp = appConfig_getOptionItemStr(appMIC_Option_DisplaySize, disp);
	
	if (slan != NULL && sdisp != NULL)
		sprintf(appconfig->curResFile, "%s%s%s.res", resPath, slan, sdisp);
	else
		memset(appconfig->curResFile, 0, sizeof(appconfig->curResFile));

	return krk_fexist(appconfig->curResFile);
}

/*
 * Function name  	: appConfig_setResPath
 * Arguments      	: resPath - res file path
 * Return         	: none
 * Description    	: set res path
 *					
*/
void appConfig_setResPath(const char* resPath)
{
	
}

/*
 * Function name  	: appConfig_setKaraokePath
 * Arguments      	: Path - karaoke path
 * Return         	: none
 * Description    	: set karaoke path
 *					
*/
void appConfig_setKaraokePath(const char* Path)
{
	if (Path != NULL)
	{
		appMICConfig_t* appconfig = &appMICConfig;

		memset(appconfig->curKaraPath, 0, sizeof(appconfig->curKaraPath));
		strncpy(appconfig->curKaraPath, Path, sizeof(appconfig->curKaraPath)-1);
	}
}

/*
 * Function name  	: appConfig_getKaraokePath
 * Arguments      	: none
 * Return         	: none
 * Description    	: get karaoke path
 *					
*/
char* appConfig_getKaraokePath(void)
{
	return appMICConfig.curKaraPath;
}

/*
 * Function name  	: appConfig_setDBPath
 * Arguments      	: Path - karaoke path
 * Return         	: none
 * Description    	: set system db path
 *					
*/
void appConfig_setDBPath(const char* Path)
{
	if (Path != NULL)
	{
		appMICConfig_t* appconfig = &appMICConfig;

		memset(appconfig->curDBPath, 0, sizeof(appconfig->curDBPath));
		strncpy(appconfig->curDBPath, Path, sizeof(appconfig->curDBPath)-1);
	}
}

/*
 * Function name  	: appConfig_getDBPath
 * Arguments      	: none
 * Return         	: none
 * Description    	: get system db path
 *					
*/
char* appConfig_getDBPath(void)
{
	return appMICConfig.curDBPath;
}

/*
 * Function name  	: appConfig_changeSkin
 * Arguments      	: app - application handler
 * Return         	: true or false
 * Description    	: change UI skin by language&resolution option value
 *					
*/
int appConfig_changeSkin(CApplication_t* app)
{
	return true;
}

/*
 * Function name  	: appConfig_getAudioType
 * Arguments      	: none
 * Return         	: analog or digital
 * Description    	: get audio output type
 *					
*/
int appConfig_getAudioType(void)
{
	int aud = appConfig_getOptionValue(appMIC_Option_Audio);

	if (aud == AudioOptionValue_Auto)
	{
		int disp = appConfig_getDisplayOptionValue();
		switch (disp)
		{
		case DisplayOptionValue_NTSC: 	
		case DisplayOptionValue_PAL:	
		case DisplayOptionValue_480p: 	
		case DisplayOptionValue_576p: 	
		case DisplayOptionValue_720p:
			aud = AudioOptionValue_Analog;
			break;
		case DisplayOptionValue_Hdmi480p: 	
		case DisplayOptionValue_Hdmi576p: 	
		case DisplayOptionValue_Hdmi720p: 	
		default:
			aud = AudioOptionValue_Digital;
			break;
		}
	}
	return aud;
}

/*
 * Function name  	: appConfig_getDisplayOptionValue
 * Arguments      	: width, height - output width and height in pixel size
 * Return         	: true or false
 * Description    	: get display option value
 *					
*/
int appConfig_getDisplayOptionValue(void)
{
	int ret = appConfig_getOptionValue(appMIC_Option_Display);
	if (ret == DisplayOptionValue_Auto)
		ret = appConfig_getOptionValue(appMIC_Option_DisplayAutoValue);
	return ret;
}

/*
 * Function name  	: appConfig_getDisplaySize
 * Arguments      	: width, height - output width and height in pixel size
 * Return         	: true or false
 * Description    	: get display option width and height value
 *					
*/
int appConfig_getDisplaySize(int* width, int* height)
{
	int value;
	int ret = true;

	if (appMICConfig.handle != NULL)
	{
		value = appConfig_getDisplayOptionValue();
		switch (value)
		{
		case DisplayOptionValue_NTSC: 	
		case DisplayOptionValue_480p:		
		case DisplayOptionValue_Hdmi480p: 	
			*width = 720;
			*height = 480;
			break;
		case DisplayOptionValue_PAL: 	
		case DisplayOptionValue_576p: 	
		case DisplayOptionValue_Hdmi576p: 	
			*width = 720;
			*height = 576;
			break;
		case DisplayOptionValue_720p: 	
		case DisplayOptionValue_Hdmi720p: 	
			*width = 1280;
			*height = 720;
			break;
		default:
			*width = 0;
			*height = 0;
			ret = false;
			break;
		}
	}
	else
		ret = false;
	
	return ret;
}

/*
 * Function name  	: appConfig_getOptionCount
 * Arguments      	: none
 * Return         	: option count
 * Description    	: get option count
 *					
*/
int appConfig_getOptionCount(void)
{
	if (appMICConfig.handle != NULL)
	{
		return ez_config_get_option_count(appMICConfig.handle);
	}
	return -1;
}

/*
 * Function name  	: appConfig_getOptionItemStr
 * Arguments      	: option - input option id
 * Return         	: option item count
 * Description    	: get option item count
 *					
*/
int appConfig_getOptionItemCount(int option)
{
	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				return ez_config_get_option_itemcount(appMICConfig.handle, name);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				return ez_config_get_option_itemcount(appMICConfig.handle, name);
		}
	}
	return -1;
}

/*
 * Function name  	: appConfig_getOptionItemStr
 * Arguments      	: option - input option id
 *									itemindex - item index
 * Return         	: option item string address, NULL is error
 * Description    	: get option item string
 *					
*/
char* appConfig_getOptionItemStr(int option, int itemindex)
{
	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				return ez_config_get_option_items_str(appMICConfig.handle, name, itemindex);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				return ez_config_get_option_items_str(appMICConfig.handle, name, itemindex);
		}
	}
	return NULL;
}

/*
 * Function name  	: appConfig_getOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: get option value
 *					
*/
char* appConfig_getOptionTitle(int option)
{
	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				return ez_config_get_title(appMICConfig.handle, name);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				return ez_config_get_title(appMICConfig.handle, name);
		}
	}
	return NULL;
}

/*
 * Function name  	: appConfig_getOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: get option value
 *					
*/
int appConfig_getOptionValue(int option)
{
	int ret = -1;

	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				ret = ez_config_get_value(appMICConfig.handle, name);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				ret = ez_config_get_value(appMICConfig.handle, name);
		}
	}
	return ret;
}

/*
 * Function name  	: appConfig_getOptionDefaultValue
 * Arguments      	: option - input option id
 * Return         	: option default setting value, -1 is error code
 * Description    	: get option default value
 *					
*/
int appConfig_getOptionDefaultValue(int option)
{
	int ret = -1;

	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				ret = ez_config_get_default(appMICConfig.handle, name);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				ret = ez_config_get_default(appMICConfig.handle, name);
		}
	}
	return ret;
}

/*
 * Function name  	: appConfig_setOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: set new option value
 *					
*/
int appConfig_setOptionValue(int option, int value)
{
	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				return ez_config_set_value(appMICConfig.handle, name, value);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				return ez_config_set_value(appMICConfig.handle, name, value);
		}
	}
	return -1;
}
/*
 * Function name  	: appConfig_changeOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: change option value in step
 *					
*/
int appConfig_changeOptionValue(int option, int step, int circle)
{
	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
				return ez_config_change_value(appMICConfig.handle, name, step, circle);
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
				return ez_config_change_value(appMICConfig.handle, name, step, circle);
		}
	}
	return -1;
}

/*
 * Function name  	: appConfig_setOptionValueToDefault
 * Arguments      	: option - input option id
 * Return         	: 0 is success, -1 is error code
 * Description    	: set option value to default
 *					
*/
int appConfig_setOptionValueToDefault(int option)
{
	int defaultvalue;

	if (appMICConfig.handle != NULL)
	{
		if (isSettingsConfig())
		{
			char name[EZCONFIG_STR_NAME_SZ];
			memset(name, 0, EZCONFIG_STR_NAME_SZ);
			strcpy(name, appMICConfig.settingOptions[option]);
			if (option < appMIC_Option_Count)
			{
				defaultvalue = ez_config_get_default(appMICConfig.handle, name);
				return ez_config_set_value(appMICConfig.handle, name, defaultvalue);
			}
		}
		else
		{
			char* name = ez_config_get_option_name(appMICConfig.handle, option);
			if (name != NULL)
			{
				defaultvalue = ez_config_get_default(appMICConfig.handle, name);
				return ez_config_set_value(appMICConfig.handle, name, defaultvalue);
			}
		}
	}
	return -1;
}

/*
 * Function name  	: appConfig_switch
 * Arguments      	: config - config name id
 * Return         	: true or false
 * Description    	: switch config
 *					
*/
int appConfig_switch(int config)
{
	if (appMICConfig.handle != NULL && config < appMIC_Config_Count)
	{
		char name[EZCONFIG_STR_NAME_SZ];
		memset(name, 0, EZCONFIG_STR_NAME_SZ);
		strcpy(name, appMICConfig.configs[config]);
		return (ez_config_switch(appMICConfig.handle, name) == EZCONFIG_ERR_NONE);
	}
	else
	{
		return false;
	}
}

/*
 * Function name  	: appConfig_save
 * Arguments      	: none
 * Return         	: true or false
 * Description    	: save config to file
 *					
*/
int appConfig_save(void)
{
	return (ez_config_save(appMICConfig.handle) == EZCONFIG_ERR_NONE);
}

/*
 * Function name  	: appConfig_load
 * Arguments      	: filePath : config file path
 * Return         	: true or false
 * Description    	: load config from file to memory
 *					
*/
int appConfig_load(const char* filePath)
{
	appMICConfig.handle = ez_config_load(filePath);
	if (appMICConfig.handle != NULL)
	{
		int i;
		int j;

		if (appConfig_switch(appMIC_Config_Settings) == EZCONFIG_ERR_NO_CONFIG)
		{
			gui_printf("=======================================\n");
			gui_printf("= WARNNING! NO SETTINGS CONFIG IN CONFIG.XML \n");
			gui_printf("=======================================\n");
			KRK_ASSERT(0);
		}
		
		for(i = 0; i < appMIC_Option_Count; i++)
		{
			for (j=0; j<sizeof(setupMenuOptions)/sizeof(int); j++)
			{
				if (setupMenuOptions[j] == i)
					break;
			}
			if (j == sizeof(setupMenuOptions)/sizeof(int))
			{
				appConfig_setOptionValueToDefault(i);
			} 
		}
		return true;
	}
	else
		return false;
}

/*
 * Function name  	: appConfig_unload
 * Arguments      	: app : application handle
 *									autosave : save config before unload
 * Return         	: true or false
 * Description    	: unload config in memory
 *					
*/
int appConfig_unload(int autosave)
{
	if (appMICConfig.handle)
  	        return (ez_config_unload(appMICConfig.handle, autosave) == EZCONFIG_ERR_NONE);
	return false;
}

bool appConfig_getSongPath(char *path, int songIndex)
{
	FILE* fp;
	char temppath[10] = {0};
	sprintf(temppath, "%05d", songIndex);
	temppath[2] = '/';
	temppath[3] = '\0';

	sprintf(path, "%s%s%s%05d%s", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT),(char*)MIC_SONG_PATH, temppath, songIndex, ".MUK");
	fp = fopen(path, "rb");
	if (fp == NULL)
	{
		sprintf(path, "%s%s%s%05d%s", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT),(char*)MIC_SONG_PATH, temppath, songIndex, ".MUS"); 
		fp = fopen(path, "rb");
		if (fp == NULL)
		{
			sprintf(path, "%s%s%s%06d%s", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT),(char*)MIC_SONG_PATH, temppath, songIndex, ".MUK"); 
			fp = fopen(path, "rb");
			if (fp == NULL)
			{
				sprintf(path, "%s%05d%s", appConfig_getPath(APPMIC_PATH_UPDATESONG), songIndex, ".MUK");
				fp = fopen(path, "rb");
				if (fp == NULL)
				{
					sprintf(path, "%s%06d%s", appConfig_getPath(APPMIC_PATH_UPDATESONG), songIndex, ".MUK");
					fp = fopen(path, "rb");
					if (fp == NULL)
					{
						sprintf(path, "%s%s%s%05d%s", appConfig_getPath(APPMIC_PATH_KARAOKE_INT), (char*)MIC_SONG_PATH, temppath, songIndex, ".MUK");
						fp = fopen(path, "rb");
						if (fp == NULL)
						{
							sprintf(path, "%s%s%s%06d%s", appConfig_getPath(APPMIC_PATH_KARAOKE_INT), (char*)MIC_SONG_PATH, temppath, songIndex, ".MUK");
							fp = fopen(path, "rb");
							if (fp == NULL)
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
	return true;
}

#include "api/filesToLstbin.h"
/*
bool appConfig_getCDGPath(char *path, int songIndex)
{
	char cdgpath[256] = {0};
	char lstpath[256] = {0};
	char namepath[256] = {0};
	char songname[256] = {0};
	
	sprintf(cdgpath, "%s%s",appConfig_getPath(APPMIC_PATH_KARAOKE_EXT), MIC_CDG_PATH);
	sprintf(lstpath, "%s%s",cdgpath, CDGLIST_FILE);
	sprintf(namepath, "%s%s",cdgpath, CDGPATH_FILE);
	getLstbinSongFilePath(lstpath, namepath, songname, sizeof(songname), songIndex);
	sprintf(path, "%s%s", cdgpath, songname);
	return true;
}
*/

bool appConfig_getRecPath(char *path, const char* songname, int songIndex, int recIndex, int type)
{
	if(type)
	{
		FILE* fp;
		sprintf(path, "%s%s%d_%d_%s.mp3", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT), MIC_REC_PATH, songIndex, recIndex, songname);
		fp = fopen(path, "rb");
		if (fp == NULL)
		{
			sprintf(path, "%s%s%d_%d_%s.mp3", appConfig_getPath(APPMIC_PATH_KARAOKE_INT), MIC_REC_PATH, songIndex, recIndex, songname);
			fp = fopen(path, "rb");
			if (fp == NULL)
			{
				return false;
			}
		}
		fclose(fp);
	}
	else
	{
		sprintf(path, "%s%s%d_%d_%s.mp3", appConfig_getKaraokePath(), MIC_REC_PATH, songIndex, recIndex, songname);
	}
	return true;
}

bool appConfig_getMTVRecPath(char *path, const char *name, int recIndex, int type)
{
	if(type)
	{
		FILE* fp;
		sprintf(path, "%s%s%s_%d.aac", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT), MIC_REC_PATH, name, recIndex);
		fp = fopen(path, "rb");
		if (fp == NULL)
		{
			sprintf(path, "%s%s%s_%d.aac", appConfig_getPath(APPMIC_PATH_KARAOKE_INT), MIC_REC_PATH, name, recIndex);
			fp = fopen(path, "rb");
			if (fp == NULL)
			{
				return false;
			}
		}
		fclose(fp);
	}
	else
	{
		sprintf(path, "%s%s%s_%d.aac", appConfig_getKaraokePath(), MIC_REC_PATH, name, recIndex);
	}
	return true;
}

bool appConfig_getCameraRecPath(char *path, int songIndex, int recIndex, int type)
{
	if(type)
	{
		char str[256];
		FILE* fp;
		sprintf(path, "%s%s%d_%d", appConfig_getPath(APPMIC_PATH_KARAOKE_EXT), MIC_CAMERA_PATH, songIndex, recIndex);
		sprintf(str,"%s/TimeLine.txt",path);
		fp = fopen(str, "rb");
		if (fp == NULL)
		{
			sprintf(path, "%s%s%d_%d", appConfig_getPath(APPMIC_PATH_KARAOKE_INT), MIC_CAMERA_PATH, songIndex, recIndex);
			sprintf(str,"%s/TimeLine.txt",path);
			fp = fopen(str, "rb");
			if (fp == NULL)
			{
				return false;
			}
		}
		fclose(fp);
	}
	else
	{
		sprintf(path, "%s%s%d_%d", appConfig_getKaraokePath(), MIC_CAMERA_PATH, songIndex, recIndex);
	}
	return true;
}


