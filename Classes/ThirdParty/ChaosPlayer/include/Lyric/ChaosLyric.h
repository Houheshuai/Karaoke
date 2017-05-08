#ifndef _CHAOS_LYRIC_H_
#define _CHAOS_LYRIC_H_

typedef void *CHAOS_LYRIC_HANDLE;

#define CHAOS_LYRIC_MAX_HINT_COUNT		5
#define CHAOS_LYRIC_MAX_LINE_COUNT		4

typedef enum tagCHAOS_LYRIC_UNIT
{
	CHAOS_LYRIC_UNIT_TICK,
	CHAOS_LYRIC_UNIT_MS,
}CHAOS_LYRIC_UNIT;

typedef struct tagCHAOS_LYRIC_SONG_INFO_UNIT
{
	unsigned long				StartTime;
	unsigned long				EndTime;
	char						*SongName1[2];
	char						*SongInfo1[4];
	char						*SongName2[2];
	char						*SongInfo2[4];
}CHAOS_LYRIC_SONG_INFO_UNIT;

typedef struct tagCHAOS_LYRIC_SONG_INFO
{
	unsigned long				InfoCount;
	CHAOS_LYRIC_SONG_INFO_UNIT	*InfoList;
}CHAOS_LYRIC_SONG_INFO;

typedef struct tagCHAOS_LYRIC_HINT_INFO_UNIT
{
	unsigned long				Count;
	unsigned long				StartTime[CHAOS_LYRIC_MAX_HINT_COUNT];
	unsigned long				EndTime[CHAOS_LYRIC_MAX_HINT_COUNT];
}CHAOS_LYRIC_HINT_INFO_UNIT;

typedef struct tagCHAOS_LYRIC_HINT_INFO
{
	unsigned long				HintCount;
	CHAOS_LYRIC_HINT_INFO_UNIT	*HintList;
}CHAOS_LYRIC_HINT_INFO;

typedef enum tagCHAOS_LYRIC_LINE_COLOR
{
	CHAOS_LYRIC_COLOR_MALE,
	CHAOS_LYRIC_COLOR_FEMALE,
	CHAOS_LYRIC_COLOR_ALLMALE,
	CHAOS_LYRIC_COLOR_LRC,
	CHAOS_LYRIC_COLOR_UNKNOWN,
}CHAOS_LYRIC_LINE_COLOR;

typedef enum tagCHAOS_LYRIC_LINE_LABLE
{
	CHAOS_LYRIC_LABLE_NONE,
	CHAOS_LYRIC_LABLE_MALE,
	CHAOS_LYRIC_LABLE_FEMALE,
	CHAOS_LYRIC_LABLE_ALLMALE,
	CHAOS_LYRIC_LABLE_MALE_1,
	CHAOS_LYRIC_LABLE_MALE_2,
	CHAOS_LYRIC_LABLE_MALE_3,
	CHAOS_LYRIC_LABLE_MALE_4,
	CHAOS_LYRIC_LABLE_FEMALE_1,
	CHAOS_LYRIC_LABLE_FEMALE_2,
	CHAOS_LYRIC_LABLE_FEMALE_3,
	CHAOS_LYRIC_LABLE_FEMALE_4,
}CHAOS_LYRIC_LINE_LABLE;

typedef struct tagCHAOS_LYRIC_LINE_WORD_INFO
{
	unsigned long				StartTime;
	unsigned long				EndTime;
	unsigned long				Info;
}CHAOS_LYRIC_LINE_WORD_INFO;

typedef struct tagCHAOS_LYRIC_LINE_INFO_UNIT
{
	unsigned long				StartTime;
	unsigned long				EndTime;
	
	unsigned long				Number;									// 位于所有歌词中的第几句
	char						*Lyric;									// 歌词
	CHAOS_LYRIC_LINE_COLOR		Color;
	CHAOS_LYRIC_LINE_LABLE		Lable;

	unsigned long				WordCount;
	CHAOS_LYRIC_LINE_WORD_INFO	*WordList;
}CHAOS_LYRIC_LINE_INFO_UNIT;

typedef struct tagCHAOS_LYRIC_LINE_INFO
{
	unsigned long				LineCount;
	CHAOS_LYRIC_LINE_INFO_UNIT	*LineList;
}CHAOS_LYRIC_LINE_INFO;

typedef struct tagCHAOS_LYRIC_DISPLAY_INFO
{
	unsigned long				Language;								// 语言
	unsigned long				Line34Flag;
	CHAOS_LYRIC_UNIT			Unit;									// 单位
	unsigned long				EndTime[CHAOS_LYRIC_MAX_LINE_COUNT];

	CHAOS_LYRIC_SONG_INFO		SongInfo;								// 歌曲信息
	CHAOS_LYRIC_HINT_INFO		HintInfo;								// 提示符信息
	CHAOS_LYRIC_LINE_INFO		LineInfo[CHAOS_LYRIC_MAX_LINE_COUNT];	// 歌词信息
}CHAOS_LYRIC_DISPLAY_INFO;

typedef enum tagCHAOS_LYRIC_TYPE
{
	CHAOS_LYRIC_TYPE_LRC,
	CHAOS_LYRIC_TYPE_MUS,
	CHAOS_LYRIC_TYPE_CDG,
}CHAOS_LYRIC_TYPE;

typedef struct tagCHAOS_LYRIC_MUS_DATA
{
	unsigned long				LyricFlag;
	unsigned long				Language;
	char						*InfoData;
	char						*Line1Data;
	char						*Line2Data;
	char						*Line3Data;
	char						*Line4Data;
}CHAOS_LYRIC_MUS_DATA;

typedef struct tagCHAOS_LYRIC_LRC_DATA
{
	unsigned long				Language;
	char						*Data;
	unsigned long				Size;
}CHAOS_LYRIC_LRC_DATA;

typedef struct tagCHAOS_LYRIC_CDG_DATA
{
	char						*Path;
}CHAOS_LYRIC_CDG_DATA;

typedef struct tagCHAOS_LYRIC_DATA_INFO
{
	CHAOS_LYRIC_TYPE			Type;
	CHAOS_LYRIC_MUS_DATA		MUSData;
	CHAOS_LYRIC_LRC_DATA		LRCData;
	CHAOS_LYRIC_CDG_DATA		CDGData;
}CHAOS_LYRIC_DATA_INFO;

CHAOS_LYRIC_HANDLE ChaosLyricInit (CHAOS_LYRIC_DATA_INFO *pDataInfo);
void ChaosLyricDeinit (CHAOS_LYRIC_HANDLE Handle);
CHAOS_LYRIC_DISPLAY_INFO *ChaosLyricGetInfo (CHAOS_LYRIC_HANDLE Handle);

#endif

