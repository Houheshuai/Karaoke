//文件	iFun.h
//描述	声明了iFun模块的接口
//作者	Chaos
//版本	V1.00
//日期	2012/1/18
//使用方法
//		调用iFun_Init初始化模块
//		调用iFun_Load加载数据
//		不断调用iFun_GetInfoClassic或iFun_GetInfoModern获取iFun信息
//		调用iFun_Unload卸载数据
//		调用iFun_Finish反初始化模块

#ifndef _IFUN_H_
#define _IFUN_H_

#include "iFunInfo.h"

typedef void *IFUN_HANDLE;

typedef struct tagNOTE_INFO
{
	cp_uint16	SongNote;		//音高
	cp_uint16	SongUnit;		//时间
}NOTE_INFO;

typedef struct tagIFUN_STAFF_INFO
{
	NOTE_INFO	*NoteInfo;		//原始数据
	cp_sint32	*NoteWrite;		//原始数据的写指针
}IFUN_STAFF_INFO;

typedef struct tagIFUN_LYRIC_INFO
{
	unsigned long	Language;			//语言信息
	char			*LyricLine1Info;	//第一行歌词信息
	char			*LyricLine2Info;	//第二行歌词信息
}IFUN_LYRIC_INFO;

typedef struct tagIFUN_VOCAL_INFO
{
	cp_Mutex	Mutex;
	cp_sint32	VocalCount;			//有多少个评分输入
	cp_sint32	TickCount;			//有多少个评分采样点
	cp_sint8	*KeyList;			//音调数组
	cp_sint32	*VocalList;			//音高数组
}IFUN_VOCAL_INFO;

typedef struct tagIFUN_LEVEL_INFO
{
	IFUN_LEVEL	Level;
	int			EasyLimit;
	int			NormalLimit;
	int			HardLimit;
}IFUN_LEVEL_INFO;

//函数	iFun_Init
//功能	初始化iFun模块
//返回	成功返回iFun模块句柄，失败返回NULL
IFUN_HANDLE iFun_Init (void *Feedback);

//函数	iFun_Finish
//功能	反初始化iFun模块
//输入	Handle	iFun模块句柄
//返回	成功返回0，失败返回-1
int iFun_Finish (IFUN_HANDLE Handle);

//函数	iFun_Load
//功能	加载iFun数据
//输入	Handle		iFun模块句柄
//		pKey		音调的指针
//		pStaffInfo	五线谱信息
//		pLyricInfo	歌词信息
//		pVocalInfo	人声信息
//返回	成功返回0，失败返回-1
int iFun_Load (IFUN_HANDLE Handle, IFUN_LEVEL_INFO *pLevelInfo, IFUN_STAFF_INFO *pStaffInfo, IFUN_LYRIC_INFO *pLyricInfo, IFUN_VOCAL_INFO *pVocalInfo);

//函数	iFun_Unload
//功能	卸载iFun数据
//输入	Handle		iFun模块句柄
//返回	成功返回0，失败返回-1
int iFun_Unload (IFUN_HANDLE Handle);

//函数	iFun_GetInfo
//功能	获取iFun信息
//输入	Handle		iFun模块句柄
//输出	piFunInfo	当前需要显示的iFun信息
//返回	成功返回0，失败返回-1
int iFun_GetInfo (IFUN_HANDLE Handle, unsigned long Ticks, IFUN_DISPLAY_INFO *piFunInfo, unsigned long InputLatency);

//函数	iFun_GetScore
//功能	获取iFun分数
//输入	Handle		iFun模块句柄
//输出	Score		分数
void iFun_GetScore (IFUN_HANDLE Handle, IFUN_SCORE *Score);

#endif
