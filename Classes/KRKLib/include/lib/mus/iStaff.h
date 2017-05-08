#ifndef _ISTAFF_H_
#define _ISTAFF_H_

#include <k_global.h>
#include <lib/ezbase/ez_notify.h>
#include <gui/iapi/GuiImage.h>
#include <iFun/iFunInfo.h>
#include <Rec/Record.h>
#include <ChaosPlayer.h>

#define MAX_STAFF_LEVEL	3
#define MAX_STAFF_ARRAY		100
#define MAX_BONUS_ARRAY		50
#define STAFF_NODE_KEY_COUNT		40//37
#define STAFF_SCORE_COUNT			3
#define BONUS_COUNT					(IFUN_BONUS_5POINTS_TYPE4-IFUN_BONUS_60POINTS+1)
#define IMG_FILENAME_MAX_SZ		256
#define MAX_STAFF_SEG_IMG	(STAFF_IMG_RIGHT+1) // left/mid/right
#define MAX_STAFF_LANGUAGE	16
#define BONUS_TIME		1000

#define MAX_PARTICLE_NUM		30
#define MAX_PARTICLE_GROUP		30
#define PARTICLE_BRUSH_TIME		700
#define PARTICLE_BRUSH_COUNT	40
#define STAFF_EAR_WIDTH	16	//(8*2)	//25
#define MINI_PARTICLE_NUM	5
#define PARTICLE_DIS_TIME	417
#define PARTICLE_COUNT		2

#define STAFF_RET_SUCC 0
#define STAFF_RET_ERR -1

enum
{
	PARTICLE_TYPE_SIN,
	PARTICLE_TYPE_UNSIN,
	PARTICLE_TYPE_BANG,
	PARTICLE_TYPE_VORTEX,
	PARTICLE_TYPE_COUNT
};

/*
*	Staff Notifys
*/
typedef enum
{
	StaffNotify_None = 0,
	StaffNotify_Play,
	StaffNotify_Stop,
	StaffNotify_Show,	
	StaffNotify_StaffNum, 
	StaffNotify_ScoreLevel, 
	StaffNotify_ScoreShow, 
	StaffNotify_ScoreAdjust, 
	StaffNotify_DrawEffect, 
	StaffNotify_ReverseOrder, 
	StaffNotify_NoDrawer, 
	
	StaffNotify_DrawBgBegin,
	StaffNotify_DrawBgEnd,
	StaffNotify_DrawSegBegin,
	StaffNotify_DrawSegEnd,
	StaffNotify_CleanAll,

	StaffNotify_AddSegment,
	
	
} StaffNotify_et;

typedef enum
{
	STAFF_IDLE,
	STAFF_PLAYING,
}StaffStatus_et;

enum
{
	STAFF_SHOW_SEG,		
	STAFF_SHOW_NONE,	
	STAFF_SHOW_GOOD,	
	STAFF_SHOW_BAD,		
	
	STAFF_SHOW_TYPE_COUNT,
};

enum
{
	STAFF_IMG_LEFT = 0,
	STAFF_IMG_MID,
	STAFF_IMG_RIGHT,
};

typedef enum
{
	STAFF_SHOW_OFF = 0,
	STAFF_SHOW_ON
} StaffShow_et;

typedef enum
{
	STAFF_MODE_SINGLE= 0,
	STAFF_MODE_SEPERATE
} StaffShowMode_et;

typedef enum
{
	SCORE_SHOW_OFF = 0,
	SCORE_SHOW_ON
} ScoreShow_et;

typedef enum 
{
	STAFF_MSG_DUMMY = 0,
	STAFF_MSG_START,
	STAFF_MSG_STOP,
	STAFF_MSG_SHOW,
	STAFF_MSG_SCORESHOW,
	STAFF_MSG_SCOREADJUST,
	STAFF_MSG_SHOWNUM,
	STAFF_MSG_SETEFFECT,
	STAFF_MSG_REVERSEORDER,
	STAFF_MSG_SETSCORELEVEL,
	
} StaffMsg_et;

typedef struct 
{
	StaffMsg_et id;
	int				para;
} StaffMsg_t;

/*
*	callback function to send notify to owner of staff module, normally it's MusPlayer
*/
typedef int (* staffOwnerCallback_t)(void* /*owner*/, int /*notifyId*/, int /*para*/);

/*
*	callback function to adjust score value, some one want to get higher
*/
typedef int (* staffScoreAjustCallback_t)(int /*score*/);
/*
*	callback function to notify staff do something in interlude
*/
typedef int (* staffInterludeCallback_t)(void* /*staff handle*/);

typedef struct
{
	unsigned int SegMode;			//seg, none, good, bad
	unsigned int SegYNoteKey;
	unsigned int SegXBegin;		//ticks
	unsigned int SegLen;		//ticks
	unsigned int SegHeadDraw;		//current segment need draw from head
	unsigned int res[3];
}M_STAFF_SEG_INFO;

typedef struct
{
	short leftOffsetX;
	short midOffsetX;
	short midLength;
	short rightOffsetX;
	short OffsetY;
	short StaffType;
	short Index;
}STAFF_ARRAY_INFO;

typedef struct
{
	short offsetX;
	short offsetY;
	short BonusType;
	short reserved;
	int BonusTime;	
}BONUS_ARRAY_INFO;

typedef struct
{
	int StartTime;
	int StartPosX;
	int StartPosY;
	
	//MULTAK_ICON *Pic[MINI_PARTICLE_NUM];
	ezImage_t*   Pic[MINI_PARTICLE_NUM];
	float Scale[MINI_PARTICLE_NUM];
	float Alpha[MINI_PARTICLE_NUM];
	
	int HP[MINI_PARTICLE_NUM];
	float SpeedX[MINI_PARTICLE_NUM];
	float SpeedY[MINI_PARTICLE_NUM];
	float AccX[MINI_PARTICLE_NUM];
	float AccY[MINI_PARTICLE_NUM];
}PARTICLE_DATA;

typedef struct
{
	int Type;
	unsigned int Seed;
	int StartTime;
	int SourceX;
	int SourceY;
	int Length;
	int PositionX;
	int PositionY;
	PARTICLE_DATA *ParticleData[MAX_PARTICLE_NUM];
	int ParticleNum;
	int CurUnit;
}PARTICLE_GROUP;

typedef struct
{
	//
	short					xBgLeft;
	short					yBgTop;
	short					wBg;
	short					hBg;
	//FreeStyle/
	short					xFreeStyleLeft;			//
	short					yFreeStyleTop;			//
	short					wFreeStyle;
	short					hFreeStyle;	
	///
	short					xLine;			///
	short					yLastLine;			///
	short					wLine;			///
	short					hLine;		//

	//score
	short					xScoreNumBg;
	short					yScoreNumBg;
	short					wScoreNumBg;
	short					hScoreNumBg;
	
	short					xScoreNum;
	short					yScoreNum;
	short					wScoreNum;
	short					hScoreNum;
	
	short					xScoreBar;
	short					yScoreBar;
	short					wScoreBar;
	short					hScoreBar;
	
	//seg
	short					hSeg[MAX_STAFF_LEVEL];
	short					wSeg[MAX_STAFF_SEG_IMG];

	//bonus
	short					hBonus[BONUS_COUNT];
	short					wBonus[BONUS_COUNT];
	
	//pk
	short				StaffOffsetX;
	short				StaffOffsetY;

	//particle
	short 				hParticles[PARTICLE_COUNT];
	short 				wParticles[PARTICLE_COUNT];
}StaffPos_st;

typedef struct
{
	int					renderMode;
	
	StaffPos_st*		posSingle;
	StaffPos_st*		posPK;

	// staff image root path
	char *					StaffPicPath;

	// staff image file path
	char **				StaffBgPath;
	char **				StaffFreeStylePath;
	char **				StaffSegPath;
	char **				StaffGoodPath;
	char **				StaffBadPath;
	char **				StaffScoreNumBg;
	char **				StaffScoreNumPath;
	char **				StaffScoreBarPath;
	char ** 			StaffBonusPath;
	char **				StaffParticlePath;
	char **				StaffSegLinePath;
	char **				StaffSegLinePKPath;
		
	char **				StaffBgPK0Path;		// PK left bg
	char **				StaffBgPK1Path;		// PK right bg
	char **				StaffSegPK0Path;	// PK left good
	char **				StaffSegPK1Path;	// PK right good
	char **				StaffGoodPK0Path;	// PK left good
	char **				StaffGoodPK1Path;	// PK right good
	char **				StaffBadPK0Path;	// PK left bad
	char **				StaffBadPK1Path;	// PK right bad

	// staff resource file handle
	void* 			res;
	
	// staff image resource id
	int				StaffBgResID;
	int				StaffFreeStyleResID;
	int				StaffSegResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];    // 9
	int				StaffGoodResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];
	int				StaffBadResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];
	int				StaffScoreNumBgResID;
	int				StaffScoreNumResID[10];
	int				StaffScoreBarResID[10];
	int				StaffBonusResID[BONUS_COUNT];   // 7
	int				StaffSegLineResID;
	int				StaffSegLinePKResID;

	int				StaffBgPK0ResID;		// PK left bg
	int				StaffBgPK1ResID;		// PK right bg
	int				StaffSegPK0ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK left good
	int				StaffSegPK1ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK right good
	int				StaffGoodPK0ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK left good
	int				StaffGoodPK1ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK right good
	int				StaffBadPK0ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK left bad
	int				StaffBadPK1ResID[MAX_STAFF_LEVEL*MAX_STAFF_SEG_IMG];	// PK right bad
	
	int				fastDraw;
	int				scoreUpdateTime;
	int				StaffParticlesResID[PARTICLE_COUNT];       
	int				prioAdjust;
	int				drawEffect;
}StaffShowInfo_st;

typedef struct
{
	StaffPos_st*		pos;
	
	ezImage_t*			StaffBg[MAX_VOCAL_COUNT];
	ezImage_t*			StaffSegLine[MAX_VOCAL_COUNT];
	ezImage_t*			FreeStyle;
	ezImage_t*			StaffSeg[MAX_VOCAL_COUNT][STAFF_SHOW_TYPE_COUNT][MAX_STAFF_SEG_IMG];
	ezImage_t*			StaffScoreNumBg;
	ezImage_t*			StaffScoreNum[10];
	ezImage_t*			StaffScoreBar[10];
	ezImage_t*			StaffBonus[BONUS_COUNT];
	ezImage_t*			StaffParticles[PARTICLE_COUNT];
	ezImage_t*			StaffInterlude;
	short				StaffOctaveGapTable[STAFF_NODE_KEY_COUNT];
	
	StaffShowInfo_st*	StaffImgPara;
}StaffParam_st;

/*
* parameters to initialize staff module
*/
typedef struct 
{
	void *showInfo;
	void *playerHandle;
	void *owner;
	staffOwnerCallback_t owner_cb;
	int multithread;
	
} StaffInitPara_t;

typedef struct
{
	int						ShowLineFlag;
	
	int 						showBg;
	int 						showFreeStyle;
	int						FreeStyleDrawedFlag;
	
	IFUN_DISPLAY_INFO	iFunInfo;
	unsigned int		LastLineNo;
	
	short 					StaffCount[MAX_VOCAL_COUNT];
	short 					BonusCount[MAX_VOCAL_COUNT];
	short					ParticleCount[MAX_VOCAL_COUNT];
	short					LastVocalCount[MAX_VOCAL_COUNT];
	short					LastVocalLength[MAX_VOCAL_COUNT];
	unsigned int		PrevType[MAX_VOCAL_COUNT];
	unsigned int		PrevNote[MAX_VOCAL_COUNT];
	unsigned int		PrevEnd[MAX_VOCAL_COUNT];
	
	STAFF_ARRAY_INFO 		StaffArray[MAX_VOCAL_COUNT][MAX_STAFF_ARRAY];
	BONUS_ARRAY_INFO	BonusArray[MAX_VOCAL_COUNT][MAX_BONUS_ARRAY];
	PARTICLE_GROUP	 	ParticleGroup[MAX_VOCAL_COUNT][MAX_PARTICLE_GROUP];

	int				LastScore[MAX_VOCAL_COUNT];

	//renderMode == 0
	int 				lastShowStaffNum[MAX_VOCAL_COUNT];

	int				interlude;
	
	int				particlefreecnt;
	
	unsigned int 	StaffTime;
	int				BgTime;
	int				SegTime;

}StaffInfo_st;

typedef struct tagMULTAK_STAFF
{
	StaffStatus_et						status;
	int										multithread;
	krk_os_task_t						task;
	krk_os_sema_t 					ctrlLock;
	krk_os_sema_t 					drawLock;
	ezNotifyHandle_t*				ctrlNotify;
	ezNotifyHandle_t*				drawNotify;
	
	unsigned int						scoretimer;
	unsigned int						scoreTimeOut;
	ScoreShow_et 					showScore;	//niuxb,control whether show score or not
	int										ifunLevel;
	int										drawEffectType;

	void *									owner;
	staffOwnerCallback_t		owner_cb;
	staffScoreAjustCallback_t score_cb;
	staffInterludeCallback_t	beginInterlude_cb;
	staffInterludeCallback_t	endInterlude_cb;
	
	StaffShow_et						show;
	
	StaffParam_st						para;
	StaffInfo_st							info;
	int 										StaffNum;

	void *									PlayerHandle;

	int										reverseOrder;
	int										reloadRes;
	int										noDrawer;		// 1- only get staff info, don't draw
	
}MULTAK_STAFF;

#ifdef __cplusplus
extern "C" {
#endif

extern MULTAK_STAFF * StaffNew(StaffInitPara_t* para);
extern void StaffFree(MULTAK_STAFF * staff);
extern void StaffInit(MULTAK_STAFF *pStaff, StaffInitPara_t* para);
extern void StaffUninit(MULTAK_STAFF *pStaff);
extern void StaffFreeView(MULTAK_STAFF * staff);
extern void StaffInitView(MULTAK_STAFF * staff);
extern void StaffPlay(MULTAK_STAFF *pStaff, int staffNum);
extern void StaffStop(MULTAK_STAFF *pStaff);
extern int StaffUpdate(MULTAK_STAFF *pStaff);
extern int StaffUpdateView(MULTAK_STAFF *pStaff);
extern void StaffScoreShow(MULTAK_STAFF *pStaff, int show);
extern void StaffScoreShowExt(MULTAK_STAFF *pStaff, int show);
extern void StaffSetScoreLevel(MULTAK_STAFF *pStaff, int level);
extern void StaffSetNotDrawer(MULTAK_STAFF *pStaff, int flag);
extern void StaffShow(MULTAK_STAFF *pStaff, int show);
extern void StaffShowExt(MULTAK_STAFF *pStaff, int show);
extern void StaffShowNum(MULTAK_STAFF *pStaff, int num);
extern void StaffShowNumExt(MULTAK_STAFF *pStaff, int num);
extern void StaffSetScoreAdjustCB(MULTAK_STAFF *pStaff, int cb);
extern void StaffSetScoreAdjustCBExt(MULTAK_STAFF *pStaff, int cb);
extern void StaffReverseOrder(MULTAK_STAFF *pStaff, int flag);

#ifdef __cplusplus
}
#endif

#endif

