/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : iLyric.h
** Revision : 1.00											
**																	
** Description: Lyric player module
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by zhaolj
** 1.01
**       modified by yucx
**
*/

#ifndef _ILYRIC_H_
#define _ILYRIC_H_

#include <k_global.h>
#include <gui/iapi/GuiString.h>
#include <gui/iapi/GuiImage.h>
#include <lib/ezbase/ez_notify.h>
#include <lib/ezbase/ez_player.h>

#include <Lyric/ChaosLyric.h>
#include <Lyric/LyricInfo.h>
#include <ChaosPlayer.h>

/*
*	icon file name maximum length
*/
#define IMG_FILENAME_MAX_SZ		256

/*
*	count of song name & song info
*/
#define SONG_NAME_NUM	2
#define SONG_WORD_NUM	4
#define HINT_BALL_NUM	4
#define SEX_LABEL_NUM	11

#define LYRIC_COLOR_NUM	(COLOR_UNKNOWN+1)

/*
*	error code of lyric module
*/
enum
{
	LYRIC_RET_LOAD_CACHE_FULL = -11,
	LYRIC_RET_ILLEGAL_LINE = -10,
	LYRIC_RET_NOT_READY = -9,
	LYRIC_RET_WRONG_ORDER = -8,
	LYRIC_RET_NOTIFY_NONE = -7,
	LYRIC_RET_LOAD_END = -6,
	LYRIC_RET_LOAD_NONE = -5,
	LYRIC_RET_CTRL_NONE = -4,
	LYRIC_RET_DRAW_NONE = -3,
	LYRIC_RET_BRUSH_NONE = -2,
	LYRIC_RET_PLAY_FAIL = -1,
	LYRIC_RET_SUCC = 0,
};

/*
*	hint ball moving style
*/
enum
{
	HINT_BALL_STYLE_DISPEAR,
	HINT_BALL_STYLE_CHANGE,
	HINT_BALL_STYLE_COUNT,
};

/*
*	lyric display lines
*/
enum
{
	FIRST_LINE = 0,
	SECOND_LINE,
	THIRD_LINE,
	FOURTH_LINE,
	MAX_LINE_NUM
};

/*
*	lyric brush lines
*/
enum
{
	BRUSH_LINE_1 = 0,
	BRUSH_LINE_2,
	BRUSH_LINE_3,
	BRUSH_LINE_4,
	BRUSH_LINE_NUM,
};

/*
*	lyric brush layers
*/
enum
{
	BRUSH_LAYER_1 = 0,
	BRUSH_LAYER_2,
	BRUSH_LAYER_NUM,
};

/*
*	lyric sex label lines
*/
enum
{
	SEXLABEL_LINE_1 = 0,
	SEXLABEL_LINE_2,
	SEXLABEL_LINE_NUM,
};

/*
* lyric word order
*/
enum
{
	LYRIC_WORD_LEFT_RIGHT = 0,
	LYRIC_WORD_RIGHT_LEFT,
};

/*
*	lyric play state
*/
typedef enum
{
	LYRIC_IDLE,
	LYRIC_START,
	LYRIC_PLAYING,
	LYRIC_STOP,
	LYRIC_PAUSE,
}LyricStatus_et;

/*
*	lyric on/off
*/
typedef enum
{
	LYRIC_SHOW_OFF = EZPLAYER_LYRIC_OFF,
	LYRIC_SHOW_ALL = EZPLAYER_LYRIC_ON,
	LYRIC_SHOW_MAIN = EZPLAYER_LYRIC_MAIN_ON,
	LYRIC_SHOW_LABEL = EZPLAYER_LYRIC_LABEL_ON,
	
} LyricShow_et;

/*
*	lyric align type
*/
typedef enum
{
	LyricAlign_Side = 0,
	LyricAlign_Middle = 1,

	LyricAlign_Count,
	
} LyricAlignType_t;

/*
*	title show status
*/
typedef enum
{
	LyricTitle_ShowNone = 0,
	LyricTitle_ShowName = 1,
	LyricTitle_ShowInfo = 2,
	LyricTitle_HideAll = 4,
	
} iLyricTitleStatus_t;

/*
*	Lyric Notifys
*/
typedef enum
{
	LyricNotify_None = 0,
	LyricNotify_PlayLyric,
	LyricNotify_PreStopLyric,
	LyricNotify_StopLyric,
	LyricNotify_PauseLyric,
	LyricNotify_ResumeLyric,
	LyricNotify_LoadLyric,
	LyricNotify_UnLoadLyric,
	LyricNotify_LoadSongInfo,
	LyricNotify_UnLoadSongInfo,
	LyricNotify_ClearLyric,
	LyricNotify_DrawHintBall,
	LyricNotify_ClearHintBall,
	LyricNotify_DrawSongInfo,
	LyricNotify_ClearSongInfo,
	LyricNotify_LyricOnOff,
	LyricNotify_TitleOnOff,
	LyricNotify_InterludeBegin,
	LyricNotify_InterludeEnd,
	LyricNotify_DrawLyricBegin,
	LyricNotify_DrawLyricEnd,
	LyricNotify_SeekLyric,
	LyricNotify_SeekLyricBegin,
	LyricNotify_SeekLyricEnd,
	LyricNotify_ReverseOrder,
	LyricNotify_SetDrawEffect,
	LyricNotify_SetLyricAlign,
	LyricNotify_BrushPercent,
	LyricNotify_LyricChanged,
	LyricNotify_SetNoDrawer,
	LyricNotify_PreludeEnd,
	LyricNotify_EndludeBegin,
	LyricNotify_SetLyricFont,
	//...........
	LyricNotify_SendSexType,
	//...........
	
} LyricNotify_et;

/*
*	Lyric draw effect types
*/
typedef enum
{
	LyricDrawEffect_Normal = 0,
	LyricDrawEffect_GLShadow,
	LyricDrawEffect_GLFrame,
	
	LyricDrawEffect_Count,
	
} LyricDrawEffectType_et;

/*
*	callback function to send notify to owner of lyric module, normally it's MusPlayer
*/
typedef int (* lyricOwnerCallback_t)(void* /*owner*/, int /*notifyId*/, int /*para*/);

/*
*	hintball image file
*/
typedef union
{
	char *DispFile[HINT_BALL_NUM];
	char *ChangFile[HINT_BALL_NUM*2];
	int 	DispFileResID[HINT_BALL_NUM];
	int	ChangFileResID[HINT_BALL_NUM*2];
} HintBallFile_t;

/*
* sex label image files
*/
typedef union 
{
	char *imgFile[SEX_LABEL_NUM];
	int 	imgFileResID[SEX_LABEL_NUM];
} SexLabelFile_t;

/*
*	lyric show parameters, user should initialize it before play lyric, normally, it is defined in playerconfig.c
*/
typedef struct
{
	int					renderMode;			//1:һֱ��

	int					scn_width;			// screen width in pixel
	int					scn_height;			// screen height in pixel
	int					xLeft;
	int					xRight;
	int					w;
	int					ySongName;
	int					ySongName1;
	int					ySongName2;
	int					hSongName;
	int					ySongWord;
	int					hSongWord;
	
	int					ySongName_nosonginfo;	//һ�и���	
	int					ySongName1_nosonginfo;	//���и���
	int					ySongName2_nosonginfo;
	int					hSongName_nosonginfo;
	int					ySongName_zhuyin_nosonginfo;	//һ�и�����Ӧһ�и���ע��
	int					ySongName1_zhuyin_nosonginfo;	//���и�����Ӧ���и���ע��
	int					ySongName2_zhuyin_nosonginfo;
	int					hSongName_zhuyin_nosonginfo;
	
	int					yLyric[MAX_LINE_NUM];
	int					hLyric[MAX_LINE_NUM];
	int					xHintBall;
	int					yHintBall;
	int					wHintBall;
	int					hHintBall;
	int					gapHintBall;
	int 				hintBallStyle;
	void *				SongNameStyle;				//��ע��ʱ������style
	void *				SongNameStyle_nosonginfo;	//��ע��ʱ������style
	void *				SongNameStyle_zhuyin;				//��ע��ʱ������ע��style
	void *				SongInfoStyle;
	void *				LyricStyle[MAX_LINE_NUM][LYRIC_COLOR_NUM];
	void *				BrushStyle[MAX_LINE_NUM][LYRIC_COLOR_NUM];

	HintBallFile_t		*hintBallFile;

	// image file path
	char *				lyricPicPath;

	// res file handle
	void*				res;
	
	char					titleInfoShowNum;			// max line number of song info
	char					lyricBrushNum;				// 2 or 4
	char					songNameShowNum;		// max line number of song name
	char					LyricBorderPixel;
	
	SexLabelFile_t * sexLabelFile;
	int					xSexLabel;					// first line x
	int					ySexLabel;					// first line y
	int					wSexLabel;
	int					hSexLabel;
	int					ySexLabelSec;				// second line y

	char					LyricToZhuyinAlign;		// 0, label and lyric align on left side, 1, label and lyric align on middle
	char 				LyricOverturn;				// 0, label on top of lyric, 1, label on bottom of lyric
	char					LyricCacheCnt;				// how many lines of lyric will be cached 
	char					LyricDrawEffect;
	int 					LyricBrushDelayTime;		// lyric brush delay time, unit -> 1ms
}LyricShowPara_st;

typedef struct
{
	LyricShowPara_st*	LyricShowPara[2];
	ezImage_t*			HintBallImg[HINT_BALL_NUM*2];
	
	unsigned int		BrushLayer[BRUSH_LAYER_NUM];
	gdi_rect_t			BrushLayerRect[BRUSH_LAYER_NUM];
	
	int					ScreenBrushLyricY[BRUSH_LINE_NUM];
	void* 				BrushCursorBuf;

	ezImage_t*			SexLabelImg[SEX_LABEL_NUM];

}LyricParam_st;

typedef struct
{
	LYRIC_SHOW_INFO		LyricShowInfo;

	//song name and info
	int					SongInfoShowFlag;
	int					SongNameCount;
	int					SongInfoCount;
	ezString_t 			SongNameStr[SONG_NAME_NUM];
	ezString_t			SongNameStr_zhuyin[SONG_NAME_NUM];
	ezString_t 			SongInfoStr[SONG_WORD_NUM];

	//lyric and brush
	int					LineNumber[MAX_LINE_NUM];
	ezString_t 			LyricStr[MAX_LINE_NUM];
	ezString_t 			BrushStr[MAX_LINE_NUM];

	//hint ball
	int					HintBallNum;
	int					LastBallNumber;

	int 					brushPrcntLast[BRUSH_LINE_NUM];
	int					brushLyric[MAX_LINE_NUM];			//start to brush flag
	int					showLyric[MAX_LINE_NUM];			//start to show flag
	int					showBallNumber;		//you must show lyric in next turn
	int					showingTitleInf;	//�Ƿ�����ʾtitileinf��״̬,00--none all,01--songname,10--songinfo,11--both
	int					lyricLanguage; // lyric language id
	int					sexLabelId[SEXLABEL_LINE_NUM];
	int 					seekLineNum;			// -1- no seek, <>-1 -seek line number
	int 					line34Flag;				// 1 - have 4 line lyric, 0 - only 2 line lyric

	int					hintTimer;
	int					wordOrder;			// 0 - left to right, 1 - right to left (arab, ...)
	
	int					drawTimer[MAX_LINE_NUM];
	int					brushTimer[MAX_LINE_NUM];
	void*				draw_cb;
	void*				brush_cb;

	// all lyric info list
	ezVector_t* 					lyrics;
	
}LyricInfo_st;

/*
*	node struct of drawlyric queue, define the infomation of draw one line lyric
*/
typedef struct 
{
	int					LineNumber;
	int					DrawLineNumber;
	int					WordNum;
	int					WordPos;
	int					LyricColor;
	int					Adjusted;
	int					LinePercent;
	ezString_t 			LyricStr;
	ezString_t 			BrushStr;
	
} drawLyricInfo_t;

/*
* parameters to initialize lyric module
*/
typedef struct 
{
	void *showInfo[2];
	void *playerHandle;
	void *owner;
	lyricOwnerCallback_t owner_cb;
	int multithread;
	
} LyricInitPara_t;

/*
*	lyric module data struct
*/
typedef struct tagMULTAK_LYRIC
{
	LyricStatus_et				status;

	int									multithread;
	krk_os_task_t					taskbrush;
	krk_os_task_t					taskdraw;
	krk_os_task_t					taskload;
	krk_os_sema_t 				ctrlLock;
	krk_os_sema_t 				drawLock;
	krk_os_sema_t 				brushLock;
	krk_os_sema_t 				loadLock;

	void*								owner;
	lyricOwnerCallback_t		owner_cb;
	
	LyricShow_et					show;
	LyricShow_et					showTitleInf;
	
	// lyric data
	LyricInfo_st						info;
	drawLyricInfo_t*				drawLyric[MAX_LINE_NUM];
	drawLyricInfo_t*				drawedLyric[MAX_LINE_NUM];

	//position
	LyricParam_st					para;

	// control lyric queue
	ezNotifyHandle_t*			ctrlLyric;
	
	// control lyric queue
	ezNotifyHandle_t*			ctrlDrawLyric;

	// loaded lyric string queue
	ezNotifyHandle_t*			loadedLyric;
	
	// prepare to load lyric queue
	ezNotifyHandle_t*			toLoadLyric;
	
	// prepare to unload lyric queue
	ezNotifyHandle_t*			toUnLoadLyric;
	
	// prepare to draw lyric queue
	ezNotifyHandle_t*			toDrawLyric;

	// prepare to draw lyric queue
	ezNotifyHandle_t*			toBrushLyric;

	// current loaded lyric line number
	int									curLoadedLineNum;
	
	// current display lyric line number
	int									curDisplayLineNum;

	// all lyric loaded
	int									allLyricLoaded;

	// draw effect type
	int									drawEffectType;
	
	// mus player handle
	void *								PlayerHandle;

	// no drawer and brusher
	int									noDrawer;
	
}MULTAK_LYRIC;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: LyricNew
 * Arguments      	: para - initialize parameters
 * Return         	: none
 * Description    	: create lyric player module
*/
extern MULTAK_LYRIC* LyricNew(LyricInitPara_t* para);

/*
 * Function name  	: LyricFree
 * Arguments      	: pLyric - lyric handler
 * Return         	: none
 * Description    	: destroy lyric player module
*/
extern void LyricFree(MULTAK_LYRIC* pLyric);

/*
 * Function name  	: LyricInitView
 * Arguments      	: pLyric - lyric handler
 * Return         	: none
 * Description    	: only free textures
*/
extern void LyricInitView(MULTAK_LYRIC* pLyric);

/*
 * Function name  	: LyricFreeView
 * Arguments      	: pLyric - lyric handler
 * Return         	: none
 * Description    	: only free textures
*/
extern void LyricFreeView(MULTAK_LYRIC* pLyric);

/*
 * Function name  	: LyricInit
 * Arguments      	: pLyric - lyric global handler
 *									para - initialize parameters
 * Return         	: none
 * Description    	: initialize lyric player module
*/
extern void LyricInit(MULTAK_LYRIC *pLyric, LyricInitPara_t* para);

/*
 * Function name  	: LyricUninit
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: deinitialize lyric player module
*/
extern void LyricUninit(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricPlay
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: start to play lyric
*/
extern void LyricPlay(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricPreStop
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: prepare to stop lyric
*/
extern void LyricPreStop(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricStop
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: stop lyric
*/
extern void LyricStop(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricPause
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: pause lyric
*/
extern void LyricPause(MULTAK_LYRIC *pLyric); 

/*
 * Function name  	: LyricResume
 * Arguments      	: pLyric - lyric global handler
 * Return         	: none
 * Description    	: pause lyric
*/
extern void LyricResume(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricShow
 * Arguments      	: pLyric - lyric global handler
 *									show - 0:hide, 1:show
 * Return         	: none
 * Description    	: set lyric display or hide
*/
extern void LyricShow(MULTAK_LYRIC *pLyric, int show);

/*
 * Function name  	: LyricShowExt
 * Arguments      	: pLyric - lyric global handler
 *									show - 0:hide, 1:show
 * Return         	: none
 * Description    	: set lyric display or hide, if not in play status, set imediatly
*/
extern void LyricShowExt(MULTAK_LYRIC *pLyric, int show);

/*
 * Function name  	: LyricShowTitleInf
 * Arguments      	: pLyric - lyric global handler
 *									show - 0:hide, 1:show
 * Return         	: none
 * Description    	: set lyric title info display or hide
*/
extern void LyricShowTitleInf(MULTAK_LYRIC *pLyric, int show);

/*
 * Function name  	: LyricShowTitleInfExt
 * Arguments      	: pLyric - lyric global handler
 *									show - 0:hide, 1:show
 * Return         	: none
 * Description    	: set lyric title info display or hide, if not in play status, set imediately
*/
extern void LyricShowTitleInfExt(MULTAK_LYRIC *pLyric, int show);

/*
 * Function name  	: LyricUpdate
 * Arguments      	: pLyric - lyric global handler
 * Return         	: nothing make sense
 * Description    	: only update lyric info
*/
extern int LyricUpdate(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricUpdate
 * Arguments      	: pLyric - lyric global handler
 * Return         	: 0 - updated, <>0 - do nothing
 * Description    	: only update lyric view
*/
extern int LyricUpdateView(MULTAK_LYRIC *pLyric);

/*
 * Function name  	: LyricShow
 * Arguments      	: pLyric - lyric global handler
 *									lineno - seek target lyric line number 
 * Return         	: none
 * Description    	: seek to specified lyric number
*/
extern void LyricSeek(MULTAK_LYRIC *pLyric, int lineno);

/*
 * Function name  	: LyricSetEffect
 * Arguments      	: pLyric - lyric global handler
 *									effectType - 
 * Return         	: none
 * Description    	: set lyric display effect type
*/
extern void LyricSetEffect(MULTAK_LYRIC *pLyric, int effectType);

/*
 * Function name  	: LyricAlign
 * Arguments      	: pLyric - lyric global handler
 *									align - align type 
 * Return         	: none
 * Description    	: set lyric align type
*/
extern void LyricAlign(MULTAK_LYRIC *pLyric, int align);

extern void LyricFont(MULTAK_LYRIC *pLyric, int fontNumber);

/*
 * Function name  	: LyricSetNoDrawer
 * Arguments      	: pLyric - lyric global handler
 *									flag - 1 : no drawer, 0- draw and brush
 * Return         	: none
 * Description    	: only get lyric info , dont' draw and brush
*/
extern void LyricSetNoDrawer(MULTAK_LYRIC *pLyric, int flag);

#ifdef __cplusplus
}
#endif


#endif

