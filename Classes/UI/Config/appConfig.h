#ifndef _APPCONFIG_H_
#define _APPCONFIG_H_

// resource
#ifdef _WIN32
#define M3D_ROOT_PATH				"../../"
#define M3D_RES_FILE_PATH			"RES/"
#define M3D_FONT_PATH				"C:/WINDOWS/Fonts/"
#define M3D_LOCALINFO_PATH			"../KARAOKE/"
#define M3D_REGION_FILE				"region.dat"
#else
#define M3D_ROOT_PATH				""
#define M3D_RES_FILE_PATH			"/RES/"	//"/Game/"
//font
#define M3D_FONT_PATH				"/system/fonts/"
#define M3D_LOCALINFO_PATH			"../"
#define M3D_REGION_FILE				"/mnt/sdcard/region.dat"
#endif

// ͬĿ¼
#define M3D_RECORDSONG_PATH			"REC/"
#define M3D_SONG_PATH				"SONG/"
#define M3D_OKF_PATH				"okf/"
#define M3D_NET_PATH				"NET/"
#define M3D_PIC_PATH				 "PIC/"
#define M3D_BGV_PATH				 "BGV/"
#define M3D_BGVMP3_PATH					"BGVMP3/"

#define M3D_CONFIG_PATH				"CFG/"
#define M3D_USERSONG_PATH			"USER/"
#define M3D_SINGERPIC_PATH			"SINGER/"

#define M3D_RECORDFILE_SUFFIXAL	         ".rec"	//	".mp3"
#define M3D_SINGERPIC_SUFFIXAL		".png"
#define M3D_CONFIG_FILE				"config.bin"
#define M3D_CONFIG_KARAOKE_FILE		"Setting.bin"
#define M3D_CONFIG_PROG_ID_FILE			"ProgIdEx.bin"
#define M3D_CONFIG_SONGINFO_FILE		"SongPlayInfo.bin"
#define M3D_CONFIG_MYHOT_FILE			"MyHot.bin"
#define M3D_CONFIG_FAVO_FILE			"Favo.bin"



#define M3D_LOCALINFO_FILE			"MyInfo2.bin"
#define M3D_HARDWAREINFO_FILE			"UUID.bin"
#define M3D_SHAREPIC_PATH			"SharePic/"
#define M3D_SCORE_SHARE_PIC_FILE	"REC/score.png"
#ifdef _WIN32
#define M3D_HARDWAREINFO_FILE			"UUID.bin"
#define M3D_RECDELAY_FILE			"recDelayTimePC.bin"
#else
#define M3D_RECDELAY_FILE			"recDelayTime2.bin"
#endif
#define M3D_NETAPP_CACHE_PATH		"../ShareSong/"


// resource file
#define M3D_RES_FILE_NAME			"M3D.res"
#define M3D_RES_FILE_NAME_CN			"M3D_CN.res"
#define M3D_RES_FILE_NAME_EN			"M3D_EN.res"

//sqlite db file
#define M3D_DATABASE_FILE_NAME			"song.db"
//sqlite db file
#define M3D_DATABASE_SID_FILE_NAME			"songid.db"
//local db file	favoID+netID
#define M3D_DATABASE_LOCAL_FILE_NAME			"local.db"

// all song list file		????
#define M3D_SONGLIST_FILE_NAME		"rmsonglist.bin"

#define M3D_EMPTY_SQLITE_DB_NAME    "cookara.db.source"
#define M3D_EMPTY_SQLITE_DB_VER    "cookara.db.source.txt"

// default click area size
#define M3D_CLICK_AREA_SZ		30.0f			// 20 -> 30, cllick are add 50%

#define M3D_CAMERA_DEV			"/dev/video0"

#define M3D_UI_IS_REMOTE


#define NETWORK_ON		1
#define THEMATIC_COUNT 2

#ifdef _WIN32
#define POWERDOWN_MODE
#endif

#include <gui/iapi/GuiBase.h>
#include <lib/ezbase/ez_config.h>

#define MIC_VERSION								"F.1.17.5"

#define VOD_RES_PATH							"d:/ResMIC/"
#define VOD_KARAOKE_PATH_INT		"e:/KARAOKE/"
#define VOD_UPDATE_PATH					"F:/UPDATE/"
#define VOD_KARAOKE_PATH_EXT    	"F:/KARAOKE/"
#define VOD_MYPHOTO_PATH 				"F:/KARAOKE/BGV/"
#define VOD_MYDOWNLOAD_PATH 		"F:/KARAOKE/DOWNLOAD/"
#define VOD_UPDATESONG_PATH 		"F:/KARAOKE/UPDATE/"
#define VOD_SYSDB_PATH						"F:/KARAOKE/SYS/"
#define VOD_MYBGV_PATH 					"F:/KARAOKE/BGV/"
#define VOD_INTBGV_PATH					"E:/KARAOKE/BGV"				
#define VOD_INTPHOTO_PATH				"d:/jpg"				

#define MIC_DB_NAME							"temp_db/vod.edb"

#define MIC_TEMPDB_PATH					"temp_db/"
#define MIC_REC_PATH						"REC/"			//	"rec\\"
#define MIC_CAMERA_PATH						"Camera/"			//	"rec\\"
#define MIC_SONG_PATH						"SONG/"
#define MIC_FAV_PATH							"fav/"
#define MIC_DB_PATH								"db/"
#define MIC_CDG_PATH							"cdg/"
#define MIC_HELP_PATH						"help/"
#define MIC_BGV_PATH							"bgv/"
#define MIC_SINGERPIC_PATH					"singerpic/"
#define MIC_SINGERPIC_PATH_480P 			"singerpic/480p/"
#define MIC_SINGERPIC_PATH_720P 			"singerpic/720p/"
#define MIC_SINGERINFO_PATH				"singerinfo/"

#define SONGLIST_SQL							"SongList.sql"
#define SONGLIST_FILE							"SongList.bin"
#define SONGNAME_FILE						"SongName.bin"
#define SONGNAME1_FILE						"SongName1.bin"
#define SONGNAME2_FILE						"SongName2.bin"

#define SONGLIST_CHKSUMFILE			"SongList.chk"

#define MIC_FAVLIST_FILE					"favsonglist.txt"
#define MIC_RECLIST_FILE					"recordsonglist.txt"
#define MIC_RESERVELIST_FILE					"reservedsonglist.txt"
#define MIC_WAVETABEL_FILE				"wavetable.bin"	//"WavTable/File01.tvs"
#define MIC_LOGO_FILE           			"AVILOGO.avi"
#define MIC_REC_WAVE_PATH				"rec_wave/"

#define MIC_MUK_TMPNAME_FILE		"songname.bin"
#define MIC_CONFIG_FILE						"config.xml"

#define LOGO_HWTEST_FILE 				"all720p/bg.bmp"
#define MIC_SDCID_FILE						"f:/sdcid.txt"
#define UPDATE_PRODUCE 					"PRODUCE.BIN"
#define PACK_BGV_FILE							"SYSBG.PAK"

#define SN_NAME										"SNdata.txt"
#define SN_NAME_BACKUP			"song.lst"

#define KEYMAP_FILE							"keymap.xml"

#define PAIRCODE_FILE							"d:\\codecfg.bin"
#define PAIRCODE_FILE_BAK					"e:\\codecfg.bin"

#define MIC_RES_FILE_STR_MAX	128

#define AbsVolumn(a, b, c, d, e) 	(((a) - (e)) * ((b) - (c)) / ((d) - (e)) + (c))
#define AbsTempo(a, b, c, d, e)		(b - ((a) - (e)) * ((b) - (c)) / ((d) - (e)))
#define HdmiVolumnAdjust(vol)				(vol)//*16/10)
#define WMICVolumnAdjust(vol)				(vol)//*5/6)

#define MAX_MUSIC_VOLUMN 		100			// max mp3 volume of MUK file
#define MAX_MIDI_VOLUMN 		100			// max midi volume of MUK file
#define MAX_MM_VOLUMN 			100			// max multimedia file volume
#define MAX_MIC_VOLUMN 			100			// max mic volume 
#define MAX_ECHO_VOLUMN 		100			// max echo volume
#define MIN_VOLUMN 						0				// all min vol are 0

#define MAX_MUS_KEY					6
#define MIN_MUS_KEY					(-6)
#define MAX_MM_KEY						6
#define MIN_MM_KEY						(-6)

#define MAX_MUS_TEMPO				800		//1200
#define MIN_MUS_TEMPO				1200	//800

// UI adjust level 0~10
#define MAX_VOL_UI_LEVEL			10
#define MIN_VOL_UI_LEVEL			0


/*
*
*/
typedef enum
{
	appMIC_Customer_Multak = 0,
	appMIC_Customer_Persang,
	appMIC_Customer_Russia,
	appMIC_Customer_NKorea,
	appMIC_Customer_Arab,

	appMIC_Customer_Count,
	
}appMICCustomer_et;

/*
* MIC application UI display option values
*	if you change the order blow, you must change <DisplaySizeOptionValue_et> the same
*/

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
	BGVTypeValue_off = 0,
	BGVTypeValue_images,
	BGVTypeValue_video,
}BackGroundTypeValue_et;
/*
* display output refresh rate of HDMI
*/
typedef enum
{
	DisplayRefreshRate_50hz = 0,
	DisplayRefreshRate_60hz,
	
} DisplayRefreshRate_et;

/*
* MIC application score option values
*/
typedef enum
{
	ScoreOptionValue_Amatear = 0,
	ScoreOptionValue_Good = 1,
	ScoreOptionValue_Professional = 2,
	ScoreOptionValue_Count = 3,
	ScoreOptionValue_Off = 4,
	
} ScoreOptionValue_et;

/*
* MIC application UI language option values
*/

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


/*
* MIC application playmode option values
*/
typedef enum
{
	PlayModeOptionValue_Normal = 0,
	PlayModeOptionValue_Repeat,
	PlayModeOptionValue_Continue,
	PlayModeOptionValue_Random,
	
} PlayModeOptionValue_et;

/*
* MIC application bgv option values
*/
typedef enum
{
	BgvOptionValue_Images = 0,
	BgvOptionValue_Video,
	BgvOptionValue_Count,
	
} BgvOptionValue_et;

/*
* MIC application audio option values
*/
typedef enum
{
	AudioOptionValue_Auto = 0,
	AudioOptionValue_Analog,
	AudioOptionValue_Digital,
	AudioOptionValue_Count,
}AudioOptionValue_et;

/*
* lyric align values
*/
typedef enum
{
	LyricAlignOptionValue_SideToSide = 0,
	LyricAlignOptionValue_Middle,
	LyricAlignOptionValue_Count,
}LyricAlignOptionValue_et;

/*
* AD string values
*/
typedef enum
{
	ADStringsOptionValue_Interlude = 0,
	ADStringsOptionValue_Count,
}ADStringsOptionValue_et;

/*
* MIC application on/off option value
*/
typedef enum
{
	appMIC_OptionValue_None = -1,				// no this option in config.xml
	appMIC_OptionValue_Off = 0,
	appMIC_OptionValue_On = 1,
	
} appMICOptionOnOffValue_t;

/*
* Singer Pic Location option value
*/
typedef enum
{
	SingerPic_Loc_Nand = 0,
	SingerPic_Loc_SDCard,
	SingerPic_Loc_NandAndSD,

	SingerPic_Loc_Count,
	
} SingerPicLocOptionValue_et;

/*
* MIC application SN type
*/
typedef enum
{
	appMIC_SNType_None = -1,				// no this option in config.xml
	appMIC_SNType_CID = 0,
	appMIC_SNType_MachineSN = 1,
	
} appMICSNType_t;

/*
* MIC application Pinyin sort type define
*/
typedef enum
{
	appMIC_PYSortFull = 0,						// sort by full word
	appMIC_PYSortFirst = 1,						// sort by first word
	
} appMICPYSortType_t;

/*
* MIC application configs list
*/
typedef enum
{
	appMIC_Config_Settings = 0,
	appMIC_Config_FontCaches,
	appMIC_Config_KeyMap,

	appMIC_Config_Count,
	
} appMICConfigs_et;
/*
* MIC application font config options
*/
typedef enum
{
	appMIC_FontCache_Option_LanType = 0,
	appMIC_FontCache_Option_FontSize,
	appMIC_FontCache_Option_OutlineWidth,
	appMIC_FontCache_Option_BorderPixel,
	appMIC_FontCache_Option_StartUcs,
	appMIC_FontCache_Option_UcsLength,
	appMIC_FontCache_Option_CacheByGlyphId,

	appMIC_FontCache_Option_Count,
	
} appMICFontCacheOption_et;

/*
* MIC application settings config option list
*/
typedef enum
{
	//setup
	appMIC_Option_Customer = 0,				// customer id
	appMIC_Option_Display,							// tv system options
	appMIC_Option_DisplaySize,					// resolution of tv system options
	appMIC_Option_DisplayValid,					// valid flag of tv system options, only valid options show in setup menu
	appMIC_Option_DisplayRefreshRate,		// display refresh rate, 50hz/60hz
	appMIC_Option_DisplayAutoValue, 			// display option value in auto mode
	appMIC_Option_ScoreLevel,						// score level
	appMIC_Option_Language,						// UI language
	appMIC_Option_AbbLanguage,				// UI language Abbreviations, use for resource file name
	appMIC_Option_PlayMode,						// play mode
	appMIC_Option_Bgv,									// bgv type
	appMIC_Option_Audio,								// audio output IF
	appMIC_Option_FontFiles, 							// font files
	appMIC_Option_FontLan,							// language id of font file, see. krk_font_language_t
	
	//player
	appMIC_Option_MusParseType, 							
	appMIC_Option_Mute,								
	appMIC_Option_KeyVol,
	appMIC_Option_Tempo,
	appMIC_Option_Rhythm,
	appMIC_Option_VoiceVol,
	appMIC_Option_AccomanyVol,
	appMIC_Option_TotalVol,
	appMIC_Option_RecVol,
	appMIC_Option_Echo,
	
	appMIC_Option_MicVol1,
	appMIC_Option_MicVol2,
	appMIC_Option_WMicVol1,
	appMIC_Option_WMicVol2,
	
	appMIC_Option_InChannels,
	appMIC_Option_OutChannels,
	appMIC_Option_InRate,
	appMIC_Option_OutRate,
	appMIC_Option_Latency,

	//not need save
	appMIC_Option_Rec,
	appMIC_Option_VocalType,
	appMIC_Option_ResetVocal,				// reset vocal to default when play new song
	appMIC_Option_Repeat,

	appMIC_Option_Ifun,	//niuxb,ifun switch
	appMIC_Option_Score, //niuxb,score switch
	appMIC_Option_Lyric, //niuxb,lyric switch

	appMIC_Option_StaffNum,			// staff number
	
	appMIC_Option_SearchType,

	appMIC_Option_TestMode,
	appMIC_Option_MyDownload,
	appMIC_Option_GameMenu,
	appMIC_Option_TitleMenu,
	appMIC_Option_TitleMenuLan,				// title menu language
	appMIC_Option_NoTitleInLan, 				// don't display title menu in language list
	appMIC_Option_LanguageListTop, 		// set language id on top of language list
	appMIC_Option_SingerLanMenu,			// show singer language list in singer menu
	appMIC_Option_MUKUpdate,
	appMIC_Option_SNType,				// CID or machine SN

	appMIC_Option_ADStrings,
	appMIC_Option_TvSysDefault,		// default tv system 
	appMIC_Option_NoPICBG, 			// not support PIC BG
	appMIC_Option_PackBGV,				// package bgv jpg files
	
	appMIC_Option_MaxRec,				// maximum record song
	appMIC_Option_MaxFav,				// maximum favorite song
	appMIC_Option_MaxRes,				// maximum reserved song

	appMIC_Option_ShortCutInFormSearch, //Change input type in title list in formSearch
	appMIC_Option_DefaultSongLanguage, //default song/singer language in formsearch
	appMIC_Option_DefaultSingerLanguage, //default song/singer language in formsearch
	
	appMIC_Option_NoRec,									// no record function

	appMIC_Option_MyDownloadUnicodeSort,	// sort mydownload list by unicode
	appMIC_Option_MyDownloadIME,					// 1 - enable mydownload list IME

	appMIC_Option_PinyinSortType,									// 1, sort by first , 0 sort by full
	appMIC_Option_NullSingerName,								// singer name of "NO SINGER" songs
	appMIC_Option_NoSingerSongList,								// language id bit mask of no singer song list
	appMIC_Option_LeaderSong, 										// leader song will display on top of list always
	appMIC_Option_TextPlayerEnable, 								// enable textplayer 
	appMIC_Option_ScoreRank, 											// score rank list
	appMIC_Option_KoreanIME,											// support korean Input Method
	appMIC_Option_NoExtBgv,											// don't support externel card bgv files
	appMIC_Option_PlayBarTimeOut,									// playbar time out, seconds
	appMIC_Option_LyricBrushDelay,									// lyric brush delay time, unit is 10 ms, from 0~255, 0ms~2550ms
	
	appMIC_Option_OKFProductID,									// OKF product ID
	appMIC_Option_UniqueCID, 											// unique CID, all song card use this CID to decode MUK
	appMIC_Option_ProductCID,
	appMIC_Option_IndianSongShow,
	appMIC_Option_SingerPicLocation,								// singer picture files location, 0-nand, 1-sdcard, 2-nand first, then sdcard
	
	appMIC_Option_Count
	
} appMICSettingsOptions_et;

/*
*	appMIC path config type
*/
typedef enum
{
	APPMIC_PATH_RES,									// resource file
	APPMIC_PATH_KARAOKE_INT,					// internel karaoke folder, like nand
	APPMIC_PATH_UPDATE,								// update files folder, normally on usb/sdcard
	APPMIC_PATH_KARAOKE_EXT,					// externel karaoke folder, like usb/sdcard
	APPMIC_PATH_MYPHOTO,							// user photos, normally on usb/sdcard
	APPMIC_PATH_MYDOWNLOAD,					// user media files, normally on usb/sdcard
	APPMIC_PATH_UPDATESONG,					// user update songs, normally on usb/sdcard
	APPMIC_PATH_SYSDB, 								// system db path
	APPMIC_PATH_MYBGV,								// user bgv 
	APPMIC_PATH_INTBGV,								// internel bgv
	APPMIC_PATH_INTPHOTO,							// internel picture bg
	APPMIC_PATH_PIC_INT,
	APPMIC_PATH_VIDEO_INT,
	APPMIC_PATH_PIC_EXT,
	APPMIC_PATH_VIDEO_EXT,
	APPMIC_PATH_CAMERA_INT,
	APPMIC_PATH_CAMERA_EXT,

	APPMIC_PATH_COUNT
	
} appMICPathType_et;

/*
*	appMIC config handler
*/
typedef struct
{
	ezConfig_t* handle;
	const char* configs[appMIC_Config_Count];
	const char* settingOptions[appMIC_Option_Count];
	char curResFile[MIC_RES_FILE_STR_MAX];
	char curKaraPath[MIC_RES_FILE_STR_MAX];
	char curDBPath[MIC_RES_FILE_STR_MAX];
	char pathSetup[APPMIC_PATH_COUNT][MIC_RES_FILE_STR_MAX];
	
} appMICConfig_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: appConfig_setPath
 * Arguments      	: type - path type
 *									Path - path string
 * Return         	: none
 * Description    	: set path
 *					
*/
extern void appConfig_setPath(int type, const char* Path);

/*
 * Function name  	: appConfig_getPath
 * Arguments      	: type - path type
 * Return         	: return True;
 * Description    	: get path string
 *					
*/
extern char *appConfig_getPath(int type);

/*
 * Function name  	: appConfig_checkResPath
 * Arguments      	: resPath - res file path
 * Return         	: 1 - exist, 0 - not exist
 * Description    	: check resource file exist or not
 *					
*/
extern int appConfig_checkResPath(const char* resPath);

/*
 * Function name  	: appConfig_setResPath
 * Arguments      	: resPath - res file path
 * Return         	: true or false
 * Description    	: set resource path
 *					
*/
extern void appConfig_setResPath(const char* resPath);

/*
 * Function name  	: appConfig_setKaraokePath
 * Arguments      	: Path - karaoke path
 * Return         	: none
 * Description    	: set karaoke path
 *					
*/
extern void appConfig_setKaraokePath(const char* Path);

/*
 * Function name  	: appConfig_getKaraokePath
 * Arguments      	: none
 * Return         	: none
 * Description    	: get karaoke path
 *					
*/
extern char* appConfig_getKaraokePath(void);

/*
 * Function name  	: appConfig_setDBPath
 * Arguments      	: Path - karaoke path
 * Return         	: none
 * Description    	: set system db path
 *					
*/
extern void appConfig_setDBPath(const char* Path);

/*
 * Function name  	: appConfig_getDBPath
 * Arguments      	: none
 * Return         	: none
 * Description    	: get system db path
 *					
*/
extern char* appConfig_getDBPath(void);

/*
 * Function name  	: appConfig_changeSkin
 * Arguments      	: app - application handler
 *									lan - language option value
 *									skin - skin option value
 * Return         	: true or false
 * Description    	: set new skin
 *					
*/
extern int appConfig_changeSkin(CApplication_t* app);

/*
 * Function name  	: appConfig_getDisplayOptionValue
 * Arguments      	: width, height - output width and height in pixel size
 * Return         	: true or false
 * Description    	: get display option value
 *					
*/
extern int appConfig_getDisplayOptionValue(void);

/*
 * Function name  	: appConfig_getDisplaySize
 * Arguments      	: width, height - output width and height in pixel size
 * Return         	: true or false
 * Description    	: get display option width and height value
 *					
*/
extern int appConfig_getDisplaySize(int* width, int* height);

/*
 * Function name  	: appConfig_getAudioType
 * Arguments      	: none
 * Return         	: analog or digital
 * Description    	: get audio output type
 *					
*/
extern int appConfig_getAudioType(void);

/*
 * Function name  	: appConfig_getOptionCount
 * Arguments      	: none
 * Return         	: option count
 * Description    	: get option count
 *					
*/
extern int appConfig_getOptionCount(void);

/*
 * Function name  	: appConfig_getOptionItemStr
 * Arguments      	: option - input option id
 * Return         	: option item count
 * Description    	: get option item count
 *					
*/
extern int appConfig_getOptionItemCount(int option);

/*
 * Function name  	: appConfig_getOptionItemStr
 * Arguments      	: option - input option id
 *									itemindex - item index
 * Return         	: option item string address, NULL is error
 * Description    	: get option item string
 *					
*/
extern char* appConfig_getOptionItemStr(int option, int itemindex);

/*
 * Function name  	: appConfig_getOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: get option value
 *					
*/
extern char* appConfig_getOptionTitle(int option);

/*
 * Function name  	: appConfig_getOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: get option value
 *					
*/
extern int appConfig_getOptionValue(int option);

/*
 * Function name  	: appConfig_getOptionDefaultValue
 * Arguments      	: option - input option id
 * Return         	: option default setting value, -1 is error code
 * Description    	: get option default value
 *					
*/
extern int appConfig_getOptionDefaultValue(int option);

/*
 * Function name  	: appConfig_setOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: set new option value
 *					
*/
extern int appConfig_setOptionValue(int option, int value);
/*
 * Function name  	: appConfig_changeOptionValue
 * Arguments      	: option - input option id
 * Return         	: option current setting value, -1 is error code
 * Description    	: change option value in step
 *					
*/
extern int appConfig_changeOptionValue(int option, int step, int circle);

/*
 * Function name  	: appConfig_setOptionValueToDefault
 * Arguments      	: option - input option id
 * Return         	: 0 is success, -1 is error code
 * Description    	: set option value to default
 *					
*/
extern int appConfig_setOptionValueToDefault(int option);

/*
 * Function name  	: appConfig_switch
 * Arguments      	: config - config name id
 * Return         	: true or false
 * Description    	: switch config
 *					
*/
extern int appConfig_switch(int config);

/*
 * Function name  	: appConfig_save
 * Arguments      	: none
 * Return         	: true or false
 * Description    	: save config to file
 *					
*/
extern int appConfig_save(void);

/*
 * Function name  	: appConfig_load
 * Arguments      	: filePath : config file path
 * Return         	: true or false
 * Description    	: load config from file to memory
 *					
*/
extern int appConfig_load(const char* filePath);

/*
 * Function name  	: appConfig_unload
 * Arguments      	: app : application handle
 *									autosave : save config before unload
 * Return         	: true or false
 * Description    	: unload config in memory
 *					
*/
extern int appConfig_unload(int autosave);

//
extern bool appConfig_getSongPath(char *path, int songIndex);
extern bool appConfig_getCDGPath(char *path, int songIndex);
extern bool appConfig_getRecPath(char *path, const char* songname, int songIndex, int recIndex, int type);
extern bool appConfig_getMTVRecPath(char *path, const char *name, int recIndex, int type);
extern bool appConfig_getCameraRecPath(char *path, int songIndex, int recIndex, int type);


#ifdef __cplusplus
}
#endif

#endif

