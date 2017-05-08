#ifndef _REQMUKLST_H_
#define _REQMUKLST_H_

#define MAXSONGNAME					48		//歌名最大长度
#define MAXSINGERNAME				24		//歌星名最大长度
#define LYRICWRITERNAME				MAXSINGERNAME	//作词
#define COMPOSERNAME				MAXSINGERNAME	//作词
#define MAXUNICODESONGNAME			96
#define MEDIA_MAX_TYPE_NUMBER		7
#define MAXSORTSTRING				10

typedef struct tag_muk_lst_t muk_lst_t;
typedef struct tag_mark_lst_t mark_lst_t;

#ifdef WIN32
#pragma pack(push,1)
#elif (defined _ARMRVDS_)
__packed
#else
#pragma pack(1)
#endif

struct tag_muk_lst_t
{
	unsigned int	SongNumber;
	unsigned char	SongName[MAXSONGNAME];
	unsigned char	SingerName[MAXSINGERNAME];
	unsigned char	LyricName[LYRICWRITERNAME];
	unsigned char	ComposerName[COMPOSERNAME];

	unsigned short  Language;
	unsigned short  SongNameAlpha;

	unsigned char   TypeNumber;
	unsigned char	SongType[MEDIA_MAX_TYPE_NUMBER];

	unsigned char   SingerSex;
	unsigned char   SingerArea;
	unsigned short	SingerNameAlpha;

	unsigned char	FileType;
	unsigned char	SubFileType;
	unsigned char	SortString[MAXSORTSTRING];

	//unicode 歌名
	unsigned char	SongNameUnicode[MAXUNICODESONGNAME];
	unsigned char	Reserve1[8];
};
struct tag_mark_lst_t
{
	mark_head_t head;
};

#ifdef WIN32
#pragma pack(pop)
#elif (defined _ARMRVDS_)
#else
#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif
	/**
	*	请求lst中的数据，成功返回 1 失败返回 0
	*/
	int muklst_muk_get_data(req_table_t *prt,muk_t *pmuk);
#ifdef __cplusplus
}
#endif

#endif
