/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : arch.c
** Revision : 1.00											
**																	
** Description: platform config parameters
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
*/

#include <k_global.h>
#include <lib/ezbase/ez_config.h>
#include "archConfig.h"
#include "InterfaceFontManager.h"
//#include "appPathManager.h"

#include "GUIBase/ParamConfig.h"

extern "C"
{
#include "AuthHardware.h"
}

extern std::string g_SysDataPath;
extern std::string g_AppDataPath;

static InterfaceFontManager* _FontManager = nullptr;

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
* gdi config input parameters
*/
gdi_configin_t gdi_configin = 
{
	{0, 1280, 720, 0, lyr_TV, 0}, 
	{
		1, 
		7, 
		{
#ifdef _WIN32
			"d:\\res\\fonts\\font.ttf",
			"d:\\res\\fonts\\DroidSans.ttf",
			"d:\\res\\fonts\\font_nk.ttf", 
			"d:\\res\\fonts\\font_fw.ttf", 
			"d:\\res\\fonts\\bengali.ttf", 
			"d:\\res\\fonts\\Telugu.ttf", 
			"d:\\res\\fonts\\Malayalam.ttf", 
#else
			"/mnt/sdcard/KARAOKE/RES/font.ttf",
			"/mnt/sdcard/KARAOKE/RES/DroidSans.ttf",
			"/mnt/sdcard/KARAOKE/RES/font_nk.ttf",
			"/mnt/sdcard/KARAOKE/RES/font_fw.ttf",
			"/mnt/sdcard/KARAOKE/RES/bengali.ttf",
			"/mnt/sdcard/KARAOKE/RES/Telugu.ttf",
			"/mnt/sdcard/KARAOKE/RES/Malayalam.ttf",
#endif

			NULL
		},
		{
			L_CHN, 
			L_ENG,
			L_KOR, 
			L_FANWEN, 
			L_BENGALI, 
			L_TELUGU, 
			L_MALAYALAM, 
			L_CHN
		},
		0,
		NULL
	}
};

/*
* gpio config input parameters
*/
static krk_gpio_configin_t gpio_config = 
{
	GPIO_TOTAL_COUNT,
	
	{
		"auth_cs",
		"auth_clk",
		"auth_dat",
			
	}
};

/*
 * Function name  	: load_font_config
 * Arguments      	: respath - res files path, conf - config file handle , fontconfig - input/output font config parameter
 * Return         	: none
 * Description    	: load font config parameters from config xml
*/
static void load_font_config(const char* respath, ezConfig_t* conf, gdi_font_config_t* fontconfig)
{
	int i;
    std::string tmpfilepath;
	// load font files path in settings config
	fontconfig->filecount = ez_config_get_option_itemcount(conf, "FontFiles");
	gui_printf("fontconfig->filecount = %d\n",fontconfig->filecount);

	GetFontManager(_FontManager);
	if (fontconfig->filecount > 0)
	{
		for (i=0; i<fontconfig->filecount; i++)
		{
			fontconfig->filepath[i] = (char*)calloc(1, 128);
			if (fontconfig->filepath[i] != NULL)
			{
				char *pStr = ez_config_get_option_items_str(conf, "FontFiles", i);
				sprintf((char *)fontconfig->filepath[i], "%s%s", respath, pStr);
				KRK_ASSERT(strlen(fontconfig->filepath[i]) < 128);
				if (!krk_fexist((char *)fontconfig->filepath[i])){
#ifdef _WIN32 
					tmpfilepath = g_AppDataPath+"fonts/";
#else
					tmpfilepath = "/system/fonts/";
#endif
					sprintf((char *)fontconfig->filepath[i], "%s%s", tmpfilepath.c_str(), pStr);
				}
				if(_FontManager != nullptr)
				{
					gui_printf("FontManager--> fontpath[%s] \n",tmpfilepath.c_str());
					switch(i)
					{
					case 0:
						CEGUI::ParamConfig::FontName_Reserve = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Reserve, std::string(fontconfig->filepath[i]));
						break;
					case 1:
						CEGUI::ParamConfig::FontName_English = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_English, std::string(fontconfig->filepath[i]));
						break;
					case 2:
						CEGUI::ParamConfig::FontName_CJK = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_CJK, std::string(fontconfig->filepath[i]));
						break;
					case 3:
						CEGUI::ParamConfig::FontName_Bengali = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Bengali, std::string(fontconfig->filepath[i]));
						break;
					case 4:
						CEGUI::ParamConfig::FontName_Devanagari = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Devanagari, std::string(fontconfig->filepath[i]));
						break;
					case 5:
						CEGUI::ParamConfig::FontName_Gujarati = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Gujarati, std::string(fontconfig->filepath[i]));
						break;
					case 6:
						CEGUI::ParamConfig::FontName_Kannada = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Kannada, std::string(fontconfig->filepath[i]));
						break;
					case 7:
						CEGUI::ParamConfig::FontName_Khmer = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Khmer, std::string(fontconfig->filepath[i]));
						break;
					case 8:
						CEGUI::ParamConfig::FontName_Malayalam = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Malayalam, std::string(fontconfig->filepath[i]));
						break;
					case 9:
						CEGUI::ParamConfig::FontName_Tamil = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Tamil, std::string(fontconfig->filepath[i]));
						break;
					case 10:
						CEGUI::ParamConfig::FontName_Telugu = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Telugu, std::string(fontconfig->filepath[i]));
						break;
					case 11:
						CEGUI::ParamConfig::FontName_Sinhala = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Sinhala, std::string(fontconfig->filepath[i]));
						break;
					case 12:
						CEGUI::ParamConfig::FontName_Arabic = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Arabic, std::string(fontconfig->filepath[i]));
						break;
					case 13:
						CEGUI::ParamConfig::FontName_Gurmukhi = std::string(pStr);
						_FontManager->AddFont(CEGUI::ParamConfig::FontName_Gurmukhi, std::string(fontconfig->filepath[i]));
						break;
					}
				}
				gui_printf("fontconfig->filepath[i] %s\n", fontconfig->filepath[i]);
			}
			fontconfig->fontarea[i] = krk_atoi(ez_config_get_option_items_str(conf, "FontLan", i));
		}

		// load font cache in FontCache config
		if (ez_config_switch(conf, "FontCaches") == EZCONFIG_ERR_NONE)
		{
			fontconfig->fontcache_count = ez_config_get_option_count(conf);
			gui_printf("font cache count in config : %d\n", fontconfig->fontcache_count);
			if (fontconfig->fontcache_count)
			{
				fontconfig->fontcache_conf = (gdi_font_cache_config_t*)calloc(fontconfig->fontcache_count, sizeof(gdi_font_cache_config_t));
				if (fontconfig->fontcache_conf != NULL)
				{
					for (i=0; i<fontconfig->fontcache_count; i++)
					{
						fontconfig->fontcache_conf[i].lantype = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_LanType));
						fontconfig->fontcache_conf[i].fontsize = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_FontSize));
						fontconfig->fontcache_conf[i].outlinewidth = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_OutlineWidth));
						fontconfig->fontcache_conf[i].borderpixel = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_BorderPixel));
						fontconfig->fontcache_conf[i].startucs = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_StartUcs));
						fontconfig->fontcache_conf[i].ucslen = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_UcsLength));
						if (ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_UcsLength) != NULL)
							fontconfig->fontcache_conf[i].cachebyglyphid = krk_atoi(ez_config_get_option_items_str(conf, ez_config_get_option_name(conf, i), appMIC_FontCache_Option_UcsLength));
					}
				}
			}
			ez_config_switch(conf, "Settings");
		}
		else
		{
			gui_printf("= NO FONT CACHE IN CONFIG\n");
		}
	}
	else
	{
		gui_printf("===============================================");
		gui_printf("= WARNNING: NO FONT FILE IN CONFIG FILE\n");
		gui_printf("===============================================");
	}
}

/*
 * Function name  	: unload_font_config
 * Arguments      	: fontconfig - input/output font config parameter
 * Return         	: none
 * Description    	: unload font config parameters
*/
static void unload_font_config(gdi_font_config_t* fontconfig)
{
	if (fontconfig != NULL)
	{
		int i;
		for (i=0; i<fontconfig->filecount; i++)
		{
			if (fontconfig->filepath[i] != NULL)
				free((char *)fontconfig->filepath[i]);
			fontconfig->filepath[i] = NULL;
		}
		if (fontconfig->fontcache_conf != NULL)
			free(fontconfig->fontcache_conf);
		fontconfig->fontcache_conf = NULL;
	}
}

int krk_disp_init(const char* resPath, int w, int h)
{
	gdi_configin_t* gdi_conf = &gdi_configin;
	gdi_lyr_st* gdi_lyr_info = &(gdi_conf->lyr_para);
	ezConfig_t* conf;
	char path[128];
	
	KRK_PRINTF("================ krk_disp_init ================\n");

	sprintf(path, "%sconfig.xml", resPath);
	KRK_PRINTF("================ krk_disp_init ================ path = %s\n",path);

	conf = ez_config_load(path);
	if (conf == NULL)
	{
		KRK_PRINTF("================ krk_disp_init ERR 1 ================\n");
		return KRK_RET_ERR;
	}

	gdi_lyr_info->width = w;
	gdi_lyr_info->height = h;
	
	gdi_lyr_info->height = gdi_lyr_info->height;//niuxb
#if (LYRIC_BRUSH_BY == BRUSH_BY_BITBLT)
	gdi_lyr_info->extraheight = gdi_lyr_info->height/2;
#else
	gdi_lyr_info->extraheight = 0;
#endif
	gdi_lyr_info->lyrtype  = lyr_TV;
	
	KRK_PRINTF("tv_width: %d, tv_height: %d\n", gdi_lyr_info->width, gdi_lyr_info->height); 		

	load_font_config(resPath, conf, &gdi_conf->font_para);
	ez_config_unload(conf, false);
	
	if(krk_gdi_init(gdi_conf) != KRK_RET_SUCC)
	{
		unload_font_config(&gdi_conf->font_para);
		KRK_PRINTF("================ krk_disp_init ERR 2================\n");
		return KRK_RET_ERR;
	}

	KRK_PRINTF("================ krk_disp_init SUCC ================\n");
	return KRK_RET_SUCC;
	
}

int krk_arch_init(const char* resPath, int w, int h)
{
	char path[128];
	
	KRK_PRINTF("================ krk_arch_init ================\n");

	krk_mem_init(0);
	krk_hw_init(&gpio_config);
	krk_os_init();
	krk_fs_init(0);
#ifdef _WIN32
	{
		AUTH_HARDWARE_PARAM Param;
		sprintf(path, "%s%s", resPath, "wavetable.bin");
		KRK_PRINTF("wavetable: %s \n", path);
		
		if (krk_fexist(path))
			Param.WaveTablePath = path;
		else{
			std::string dirpath = g_SysDataPath;
			sprintf(path, "%s%s", dirpath.c_str(), "wavetable.bin");
			Param.WaveTablePath = path;
		}
		AuthHardware_Init (&Param);
	}
#endif
	if (w == 0)
		w = RES_RESO_WIDTH;
	if (h == 0)
		h = RES_RESO_HEIGHT;
	if (krk_disp_init(resPath, w, h) != KRK_RET_SUCC)
	{
		return KRK_RET_ERR;
	}

	KRK_PRINTF("================ krk_arch_init SUCC ================\n");
	return KRK_RET_SUCC;
	
}

int krk_disp_deinit(void)
{
	KRK_PRINTF("================ krk_disp_deinit ================\n");

	krk_gdi_deinit(&gdi_configin);
	unload_font_config(&gdi_configin.font_para);
	return 0;
}

int krk_arch_deinit(void)
{
	KRK_PRINTF("================ krk_arch_deinit ================\n");

	krk_disp_deinit();

	AuthHardware_Finish();
	
	krk_fs_deinit();
	krk_os_deinit();
	krk_hw_deinit();	
	krk_mem_deinit();
	return 0;
}

