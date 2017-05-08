//文件	LyricInfo.h
//描述	声明了歌词信息的结构
//作者	Chaos
//版本	V1.00
//日期	2011/1/15

#ifndef _LYRIC_INFO_H_
#define _LYRIC_INFO_H_

#define STATUS_WAIT						(0)
#define STATUS_DISPLAY_LYRIC			(1)
#define STATUS_MOVE_LYRIC				(1 << 1)
#define STATUS_DISPLAY_SONGINFO			(1 << 2)
#define STATUS_READY					(1 << 3)
#define STATUS_SONGEND					(1 << 4)
#define STATUS_ERR						(~0x1f)

typedef enum
{
	COLOR_MALE = 0,
	COLOR_FEMALE,
	COLOR_ALLMALE,
	COLOR_LRC,
	COLOR_UNKNOWN,
}M_LYRIC_COLOR;

#define COLOR_DEFAULT		COLOR_UNKNOWN

typedef enum
{
	LYRIC_SEX_NONE,
	LYRIC_SEX_MALE,
	LYRIC_SEX_FEMALE,
	LYRIC_SEX_ALLMALE,
	LYRIC_SEX_MALE_1,
	LYRIC_SEX_MALE_2,
	LYRIC_SEX_MALE_3,
	LYRIC_SEX_MALE_4,
	LYRIC_SEX_FEMALE_1,
	LYRIC_SEX_FEMALE_2,
	LYRIC_SEX_FEMALE_3,
	LYRIC_SEX_FEMALE_4,
}LYRIC_SEX_LABLE;

typedef struct  
{
	int				LineNumber;			//歌词的行数
	char			*LyricString;		//歌词字符串
	int				CurWord;			//当前的字在字符串中位置
	int				Percent;			//当前字百分比
	int				Color;				//颜色
	int				SexLable;			//性别标签
	unsigned char	*WordInfo;
}M_LYRIC_LINE_INFO;

typedef struct
{
	char			*SongNameLine1;		//歌曲名第一行
	char			*SongNameLine2;		//歌曲名第二行
	char			*SongInfoLine1;		//歌曲信息第一行
	char			*SongInfoLine2;		//歌曲信息第二行
	char			*SongInfoLine3;		//歌曲信息第三行
	char			*SongInfoLine4;		//歌曲信息第四行
	char			*SongName2Line1;	//附加歌曲名第一行
	char			*SongName2Line2;	//附加歌曲名第二行
	char			*SongInfo2Line1;	//附加歌曲信息第一行
	char			*SongInfo2Line2;	//附加歌曲信息第二行
	char			*SongInfo2Line3;	//附加歌曲信息第三行
	char			*SongInfo2Line4;	//附加歌曲信息第四行
}M_SONG_INFO;

typedef struct
{		
	M_LYRIC_LINE_INFO FirstLine;		//第一行歌词信息
	M_LYRIC_LINE_INFO SecondLine;		//第二行歌词信息
	M_LYRIC_LINE_INFO ThirdLine;		//第三行歌词信息
	M_LYRIC_LINE_INFO FourthLine;		//第四行歌词信息
}M_LYRIC_INFO;

typedef struct
{
	int Percent;
	int Count;
}M_READY_INFO;

typedef struct
{
	M_SONG_INFO		SongInfo;
	M_LYRIC_INFO	LyricInfo;
	M_READY_INFO	ReadyInfo;
}M_SHOW_INFO;

typedef struct
{
	int			DeltaTime;
	int			LyricStatus;
	int			LyricLanguage;
	int			Line34Flag;				//歌曲三四行显示标志
	M_SHOW_INFO	ShowInfo;
}LYRIC_SHOW_INFO;

typedef struct
{
	int		Language;
	int		Line34Flag;
	M_SONG_INFO		SongInfo;
}LYRIC_SHOW_INFO_SONG_INFO;

typedef struct
{
	int		Language;
	int		Line34Flag;
	int		Number;
	int		Line;
	char	*String;
	int		Color;
	unsigned char	*WordInfo;
	int				WordCount;
	int		SexLable;			//性别标签
}LYRIC_SHOW_INFO_LYRIC_INFO;

#endif

