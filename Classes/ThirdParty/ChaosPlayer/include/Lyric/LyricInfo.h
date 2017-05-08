//�ļ�	LyricInfo.h
//����	�����˸����Ϣ�Ľṹ
//����	Chaos
//�汾	V1.00
//����	2011/1/15

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
	int				LineNumber;			//��ʵ�����
	char			*LyricString;		//����ַ���
	int				CurWord;			//��ǰ�������ַ�����λ��
	int				Percent;			//��ǰ�ְٷֱ�
	int				Color;				//��ɫ
	int				SexLable;			//�Ա��ǩ
	unsigned char	*WordInfo;
}M_LYRIC_LINE_INFO;

typedef struct
{
	char			*SongNameLine1;		//��������һ��
	char			*SongNameLine2;		//�������ڶ���
	char			*SongInfoLine1;		//������Ϣ��һ��
	char			*SongInfoLine2;		//������Ϣ�ڶ���
	char			*SongInfoLine3;		//������Ϣ������
	char			*SongInfoLine4;		//������Ϣ������
	char			*SongName2Line1;	//���Ӹ�������һ��
	char			*SongName2Line2;	//���Ӹ������ڶ���
	char			*SongInfo2Line1;	//���Ӹ�����Ϣ��һ��
	char			*SongInfo2Line2;	//���Ӹ�����Ϣ�ڶ���
	char			*SongInfo2Line3;	//���Ӹ�����Ϣ������
	char			*SongInfo2Line4;	//���Ӹ�����Ϣ������
}M_SONG_INFO;

typedef struct
{		
	M_LYRIC_LINE_INFO FirstLine;		//��һ�и����Ϣ
	M_LYRIC_LINE_INFO SecondLine;		//�ڶ��и����Ϣ
	M_LYRIC_LINE_INFO ThirdLine;		//�����и����Ϣ
	M_LYRIC_LINE_INFO FourthLine;		//�����и����Ϣ
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
	int			Line34Flag;				//������������ʾ��־
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
	int		SexLable;			//�Ա��ǩ
}LYRIC_SHOW_INFO_LYRIC_INFO;

#endif

