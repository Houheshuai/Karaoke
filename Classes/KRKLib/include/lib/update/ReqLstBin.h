#ifndef _REQLSTBIN_H_
#define _REQLSTBIN_H_

#define SL_LIST_FIX_SIZE						8

#define SL_SONGNAME_LEN 96
#define SL_SINGERNAME_LEN 48

typedef enum
{
	SONGNAME_BIN = 0,
	SONGNAME1_BIN = 1,
	SONGNAME2_BIN = 2,
	SONGNAME_MODE1 = 3,     //      SongName.bin ||   SongName1.bin
	
}listbin_songname_t;

typedef struct tag_sl_list_node_t sl_list_node_t;

#ifdef WIN32
#pragma pack(push,1)
#elif (defined _ARMRVDS_)
__packed
#else
#pragma pack(1)
#endif

struct tag_sl_list_node_t
{
	unsigned char OrderIndex[4];
	unsigned char FileType;
	unsigned char SubFileType;
	unsigned char SongNameOffset[3];
	unsigned char LanType;
	unsigned char FontType;
	unsigned char Path[16];
	unsigned char AlphaIndex;
	unsigned int  FileOffset;
	unsigned int  FileLength;

	//add for language like hindi
	unsigned char SongNameUnicodeOffset[3];
	unsigned char SongNameGlyphOffset[3];
	unsigned char SongNameShouPin[6];

	//2010 change position
	unsigned char SortString[10];
	unsigned char TypeNumber;
	// Hindi Category
	unsigned char Bhajanfg;     
	unsigned char Patrioticfg;
	unsigned char Duetfg;
	unsigned char Solofg;
	unsigned char Sufifg;
	unsigned char Romaticfg;
	unsigned char Ghazalfg;
	unsigned char Everfg;
	unsigned char Birthdayfg;
	unsigned char Classicalfg;
	unsigned char Popularfg;
};

#ifdef WIN32
#pragma pack(pop)
#elif (defined _ARMRVDS_)
#else
#pragma pack()
#endif

typedef struct tag_sl_list_t sl_list_t;
struct tag_sl_list_t
{
	int num;
	int size;
	int song_name1_len;
	char *song_name1;
	int song_name2_len;
	char *song_name2;
	int song_name_len;
	char *song_name;
	sl_list_node_t *list;
};

typedef struct tag_lstbin_node_t lstbin_node_t;
typedef struct tag_lstbin_t lstbin_t;
typedef struct tag_listbin_reqpara listbin_req_para_t;

struct tag_lstbin_node_t
{
	sl_list_node_t* node;
	int SongIndex;
	int OrderIndex;
	char SongNameAlpha;
	char SongNameWords;

	int SongNameOffset;
	int SongNameLen;
	int SongNameUnicodeOffset;
	int SongNameUnicodeLen;
	int SongNameGlyphOffset;
	int SongNameGlyphLen;	

	char SongName[SL_SONGNAME_LEN];
	char SongNameEN[SL_SINGERNAME_LEN];
	char SingerName[SL_SONGNAME_LEN];
	char SingerNameEN[SL_SINGERNAME_LEN];
	char SongNameUnicode[SL_SONGNAME_LEN];
	char SongNameGlyph[SL_SONGNAME_LEN];
	char SongNameList[SL_SONGNAME_LEN];
#ifdef SUPPORT_PERSANG_EDB //Persang db album function   SUPPORT_PERSANG_FUNCTION
    char AlbumNameEN[SL_SINGERNAME_LEN];
#endif 
};

struct tag_lstbin_t
{
	int num;
	int charset;
	int req_songname;
	lstbin_node_t *lst;
	sl_list_node_t *sl_lst;
};

struct tag_listbin_reqpara 
{
	listbin_songname_t req_songname;		/* 0: songname.bin, 1: songname1.bin, 2: songname2.bin */
	listbin_songname_t default_songname;		/* if req_songname does not exist, use default_songname */
	int							charset;
	int							cn_firstword;
};

#ifdef __cplusplus
extern "C" {
#endif

int ListBin_ReqData(req_table_t *prt,const char *dir_path, listbin_req_para_t* para);

#ifdef __cplusplus
}
#endif

#endif
