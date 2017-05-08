//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : ReqDB.h
//																	
// Description: basic class for db access
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#ifndef REQDB_H
#define REQDB_H

//#define A_BUFFER_FOR_NORMAL_LIST
//#define LOAD_LIST_BY_ONE_TABLE
#define USE_LIST_BUFFER_FOR_SOME_LIST

#include <map>
#include <sqlite3.h>
#include <pthread.h>
#include "MKSingleton.h"
#include "GUIBase/M3D_Req.h"

#include "ReqBindingStruct.h"
#include <unordered_map>

namespace CEGUI
{
	
#define SQL_STR_SZ		800
#define SQL_STR_SZ_S	256				//short

#define FAVOSONG_MAX_NUM		300
#define MYHOTSONG_MAX_NUM		100

#define MAX_ABC_COUNT 	28

/*!
\brief
	database request data type
*/
enum {
	REQDB_TYPE_NONE = 0,
	REQDB_TYPE_SINGER,					//! get singer list, param.strParam -> shoupin
	REQDB_TYPE_SINGERSONG,				//! get singer song list, subcmd is singer index
	REQDB_TYPE_FAVSONG, 				//! get favorite song list
	REQDB_TYPE_HOTSONG, 				//! get hot song list
	REQDB_TYPE_NEWSONG, 				//! get new song list
	REQDB_TYPE_PINYIN,					//! get pinyin song list, param.strParam -> shoupin
	REQDB_TYPE_ZIBU,					//! get zibu song list, subcmd is word number
	REQDB_TYPE_LANGUAGE,				//! get language song list, subcmd is language id
	REQDB_TYPE_CLASSIC, 				//!get classic song list, subcmd is classic id
	REQDB_TYPE_MYSONG,					//! get language song list, subcmd is language id
	REQDB_TYPE_RECORDSONG, 				//!get classic song list, subcmd is classic id
	REQDB_TYPE_EASYSONG,				//!get classic song list, subcmd is classic id
	REQDB_TYPE_RESERVED,
	REQDB_TYPE_MP3SONG,
	REQDB_TYPE_SHARESONG,
	REQDB_TYPE_WEBNEWSONG, 				//! get web new song list
	REQDB_TYPE_WEBHOTSONG,				//! get web hot song list
	REQDB_TYPE_WEBCOMPETITIONSONG,		//! get web Competition song list
	REQDB_TYPE_SINGER_TYPE,
	REQDB_TYPE_CUSTOM, 					//! get custom items
	REQDB_TYPE_LANGUAGE_SONG,
	REQDB_TYPE_NUM_SONG,
	REQDB_TYPE_MYHOT_SONG,
	REQDB_TYPE_DOWNLOAD,
	REQDB_TYPE_GENRE_SONG,
	REQDB_TYPE_COUNT
};

/*!
\brief
	database singer type
*/
enum{
	REQDB_SUBTYPE_SINGER_MALE,
	REQDB_SUBTYPE_SINGER_FEMALE,
	REQDB_SUBTYPE_SINGER_BAND,
	REQDB_SUBTYPE_SINGER_ALL,

	REQDB_SUBTYPE_SINGER_COUNT
};

/*!
\brief
	database song type
*/
enum
{
	REQDB_SUBTYPE_POP_SONG,
	REQDB_SUBTYPE_FOLK_SONG,
	REQDB_SUBTYPE_RED_SONG,
	REQDB_SUBTYPE_CHILD_SONG,
	REQDB_SUBTYPE_OPERA_SONG,

    REQDB_SUBTYPE_SONG_COUNT
};

/*!
\brief
	download song type
*/
enum
{
	REQDB_SUBTYPE_MP3,
	REQDB_SUBTYPE_MTV,
	REQDB_SUBTYPE_MOVIE,
	
    REQDB_SUBTYPE_SONGTYPE_COUNT
};

/*!
\brief
	language type
*/
enum
{
	SONG_SUBTYPE_CN = 1,			//����
	SONG_SUBTYPE_EN = 4,			//Ӣ��
	SONG_SUBTYPE_JP = 5,			//����(����)
	SONG_SUBTYPE_KR = 6,			//����
	SONG_SUBTYPE_VIE = 7,			//Խ����
	SONG_SUBTYPE_TH = 8,			//̩��
	SONG_SUBTYPE_RU = 9,			//����(����)
	SONG_SUBTYPE_SP = 11,			//��������
	SONG_SUBTYPE_PHI = 12,			//���ɱ���
	SONG_SUBTYPE_FR = 15,			//����
	SONG_SUBTYPE_ID = 18,			//ӡ��		(ADD LATER)
	SONG_SUBTYPE_JIS = 19,			//����(JIS)
	SONG_SUBTYPE_XLE = 20,			//����(XLE)
	SONG_SUBTYPE_IN = 22,			//ӡ��		(ADD LATER)
	SONG_SUBTYPE_MY = 28,			//��������	(ADD LATER)
};
enum
{
	SONG_LIST_CN,			//����
	SONG_LIST_EN,			//Ӣ��
	SONG_LIST_JP,			//����(����)
	SONG_LIST_KR,			//����
	SONG_LIST_VIE,			//Խ����
	SONG_LIST_TH,			//̩��
	SONG_LIST_RU,			//����(����)
	SONG_LIST_SP,			//��������
	SONG_LIST_PHI,			//���ɱ���
	SONG_LIST_FR,			//����
	SONG_LIST_ID,			//ӡ����
	SONG_LIST_IN,			//ӡ����
	SONG_LIST_MY,			//����������
};

/*!
\brief
	type for numSong (foreign on or off)
*/
enum
{
	SONG_SUBTYPE_FOREIGN_OFF,
	SONG_SUBTYPE_FOREIGN_ON,
};

/*!
\brief
	database sql command list
*/
enum 
{
	REQDB_SQL_NONE = 0,

	REQDB_SQL_ALLSONGINF,
	REQDB_SQL_SONGCOUNT,
	REQDB_SQL_SONGINF,
	REQDB_SQL_SONGINF_BY_INDEX,

	//! singer 
	REQDB_SQL_SINGER_MD_MALE,
	REQDB_SQL_SINGER_MD_FEMALE,
	REQDB_SQL_SINGER_HK_MALE,
	REQDB_SQL_SINGER_HK_FEMALE,
	REQDB_SQL_SINGER_CHN_BAND,
	REQDB_SQL_SINGER_FOREIGN_BAND,
	REQDB_SQL_SINGER_OTHER,
	REQDB_SQL_SINGER_MALE,
	REQDB_SQL_SINGER_FEMALE,
	REQDB_SQL_SINGER_BAND,

	//! song
	REQDB_SQL_SONG_SINGER,
	
	REQDB_SQL_SONG_ZIBU_ALL,
	REQDB_SQL_SONG_ZIBU_SPE,
	REQDB_SQL_SONG_ZIBU_BIG,
	
	REQDB_SQL_SONG_PINYIN,
	REQDB_SQL_SONG_POP,
	REQDB_SQL_SONG_FOLK,
	REQDB_SQL_SONG_RED,
	REQDB_SQL_SONG_CHILD,
	REQDB_SQL_SONG_OPERA,
	REQDB_SQL_SONG_EASY,
	REQDB_SQL_SONG_HOT,
	REQDB_SQL_SONG_NEW,
	REQDB_SQL_SONG_LANGUAGE,
	
	REQDB_SQL_SINGER_CHINA_MALE,
	REQDB_SQL_SINGER_CHINA_FEMALE,
	REQDB_SQL_SINGER_FOREIGN_MALE,
	REQDB_SQL_SINGER_FOREIGN_FEMALE,

	REQDB_SQL_CUSTINFO,
	REQDB_SQL_SID,
	REQDB_SQL_FAVOID,
	REQDB_SQL_NETID,
	REQDB_SQL_MYHOTID,
	
	REQDB_SQL_MP3,
	REQDB_SQL_MTV,
	REQDB_SQL_MOVIE,
	REQDB_SQL_MP3_OR_MTV,
	REQDB_SQL_GET_MP3,
	REQDB_SQL_GET_MTV,

	REQDB_SQL_LAN_CN,
	REQDB_SQL_LAN_EN,
	REQDB_SQL_LAN_JP,
	REQDB_SQL_LAN_KR,
	REQDB_SQL_LAN_VIE,
	REQDB_SQL_LAN_TH,
	REQDB_SQL_LAN_RU,
	REQDB_SQL_LAN_SP,
	REQDB_SQL_LAN_PHI,
	REQDB_SQL_LAN_FR,
	REQDB_SQL_LAN_ID,
	REQDB_SQL_LAN_IN,
	REQDB_SQL_LAN_MY,

	REQDB_SQL_BOOK,
	REQDB_SQL_BOOK_NO_FOREIGN,

	REQDB_SQL_PINYIN_COUNT,
	REQDB_SQL_SONG_LETTER_INDEX_COUNT,

	REQDB_SQL_MY_HOT_SONGID,
	REQDB_SQL_SINGER_BY_SONGID,
	REQDB_SQL_FAVO_LOAD,
};

/*!
\brief
	file type and media type
*/
enum
{
	SONG_FILETYPE_MUS = 1,
	SONG_FILETYPE_KSC = 2,
	SONG_FILETYPE_MTV = 3,
	SONG_FILETYPE_MP3 = 4,
	SONG_FILETYPE_MOVIE = 5,
	SONG_FILETYPE_CDG = 128,
	SONG_FILETYPE_MUK = 255,
};

enum
{
	SONG_MEDIATYPE_MIDI = 1,
	SONG_MEDIATYPE_MIDI_MP3 = 2,
	SONG_MEDIATYPE_MP3 = 3,
	SONG_MEDIATYPE_ACC = 17,
	
	SONG_MEDIATYPE_OKF_MIDI = 129,
	SONG_MEDIATYPE_OKF_ACC = 145,

	SONG_MEDIATYPE_FILE_MP3 = 200,
	SONG_MEDIATYPE_FILE_AVI = 201,

	SONG_MEDIATYPE_MTV_MUS = 254,
};

/*!
\brief
	PLAY_SONG_TYPE for setup form
	0: no play; 1: MP3 play; 2: MIDI play; 3: ACC play; 4: MTV play; 5: MTV replay; 6: other replay;
*/
/*
enum
{
	PLAY_SONG_TYPE_NONE,
	PLAY_SONG_TYPE_MP3,
	PLAY_SONG_TYPE_MIDI,
	PLAY_SONG_TYPE_ACC,
	PLAY_SONG_TYPE_MTV,
	PLAY_SONG_TYPE_MOVIE,
	PLAY_SONG_TYPE_RECORD_MTV,
	PLAY_SONG_TYPE_RECORD_OTHER,
	PLAY_SONG_TYPE_CDG,
};
*/
/*!
\brief
	database song infomation
*/
typedef struct 
{
	int SongIndex;
	int OrderIndex;
	int FileType;				//file type: 1.MIDI 2.KSC 3.MTV 4.MUSIC 5.MOVIE
	int SubFileType;				//song type: 1.MIDI 2.VOCAL_MIDI 3.KSC 4.MPG ...
	char SongName[128];
	char SingerName[128];
	char FirstWord[64];

} ReqDBSongInf_t;

/*!
\brief
	database binding data struct, now only singer and song
*/
typedef union{
	SongListBindingStruct_t song;
	SingerListBindingStruct_t singer;
}DBBindingStruct_t;

typedef struct {
	DBBindingStruct_t items[MAX_BINDREC_COUNT];
} DBBindingRec_t;

class ReqDB : public M3D_Req, public MKSingleton<ReqDB>
{
public:

	
	ReqDB(void* para1, int para2);
		
	virtual ~ReqDB(void);

	/*!
	\brief
		virtual interfaces implement
	*/
	
	static int fileRename(char *name1, char *name2);
	static int fileCopy(char *from, char *to);
	static bool dirFreeSize(const char *dir, unsigned int *freeK);
	static unsigned int dirFreeSize(const char *dir);
	static void DecDataX(unsigned char * pData, unsigned EncLength, unsigned char CustNoHigh, unsigned char CustNoLow);
	virtual int reqInit(M3DReqCmd_t& cmd, int onePageItems);
	virtual int reqDeInit(void);
	virtual int reqRec(int reqStart, int reqCount);
	virtual void* getBindingRec(void) {return bindingRec.items;}
	virtual void* getBindingRec(int id) {return &(bindingRec.items[id]);}
	virtual int getBindingRecLength(void) {return sizeof(DBBindingStruct_t);}
	
	/*!
	\brief
		request song extra infomation, like favorite/reserved/record flag

	\param song
		output song infomation
	*/
	virtual void reqSongExtraInf(SongListBindingStruct_t& song,bool isreserved = false);

	/*!
	\brief
		request song infomation from database

	\param songNo
		input song Number, search it in database
	\param output
		output song infomation

	\return
		0: fail, >0 succ
	*/
	virtual int reqDbSongInf(unsigned int songNo, ReqDBSongInf_t* output);

	virtual int reqInitSongInf(void);
	virtual void reqDeInitSongInf(void);
	virtual int reqMySong(int reqStart, int reqCount);
	virtual int reqRecordSong(int reqStart, int reqCount);
	virtual int reqNewSong(int reqStart, int reqCount);
	virtual int reqHotSong(int reqStart, int reqCount);
	virtual int reqFavorSong(int reqStart, int reqCount);
	virtual int reqMp3Song(int reqStart, int reqCount);
	virtual int reqReservedSong(int reqStart, int reqCount);
	virtual int reqShareSong(int reqStart, int reqCount);
	virtual int reqWebNewSong(int reqStart, int reqCount);
	virtual int reqWebHotSong(int reqStart, int reqCount);
	virtual int reqWebCompetitionSong(int reqStart, int reqCount);
	virtual int reqCustomItems(int reqStart, int reqCount);
	virtual int reqSingerType(int reqStart, int reqCount);
	virtual int reqLanguage(int reqStart, int reqCount);
	virtual int reqLangugeSongCount(int LanguageType);
	virtual int reqNumSong(int reqStart, int reqCount);
	virtual int reqMyHotSong(int reqStart, int reqCount);

	/*!
	\brief
		sync database with remote song number file
	*/
	virtual int reqSyncLocalDB(char* filePath);
	int reqResetSingerSongTotal(void);
	void refreshDBDataBuffer();

	//to req song total by sql enum
	int reqSongTotal(bool firstFlag = false); //0: again; 1: over; 2: do nothing;

	void regSQLString(int type, std::string& sqlString) {SQLTypeNameRegistry[type] = sqlString;}
	bool checkSQLExist(int type) {return (SQLTypeNameRegistry.find(REQDB_SQL_ALLSONGINF) != SQLTypeNameRegistry.end());}
	const char* getSQLString(int type) {return checkSQLExist(type)? SQLTypeNameRegistry[type].c_str() : NULL;}
	
	void setPrivacyFlag(int flag) {d_PrivacyFlag = flag;}
	int getPrivacyFlag() {return d_PrivacyFlag;}

	//pthread for read a buffer
	bool pthreadCreate(void);
	bool pthreadDestroy(void);

	DBBindingRec_t bindingRec;
	int d_ForeignFlag;
	sqlite3* d_db;
	
	int d_pthread_flag;

	int d_tableSongTotal;
	
#ifdef A_BUFFER_FOR_NORMAL_LIST
	int d_NormalListFlag;
	int d_loadSongEndFlag;
	ReqDBSongInf_t* d_pbNormalBuffer;
#endif

protected:

	/*!
	\brief
		find singer picture

	\param num
		num is the position of singer in binding record list
	*/
	bool reqSingerPic(int num);
	
	/*!
	\brief
		internel request handles
		
	\param reqStart
		request start offset in database dataset
	\param reqCount
		request count of record
	*/
	int reqSinger(int reqStart, int reqCount);
	int reqSingerCount(int SingerType);
	int reqSingerSong(int reqStart, int reqCount);
	int reqZibuSong(int reqStart, int reqCount);
	int reqPinyinSong(int reqStart, int reqCount);
	int reqClassicSong(int reqStart, int reqCount);
	int reqEasySong(int reqStart, int reqCount);
	int reqLanguageSong(int reqStart, int reqCount);
	int reqDownload(int reqStart, int reqCount);
	
	/*!
	\brief
		following functions are called when sync database by song number file
	*/
	int reqResetSongAllExist(void);
	int reqResetSingerAllExist(void);
	
	int reqDbSongIndexByIndex(unsigned int index);

	int reqDbSongindexByOrder(unsigned int index);

	int reqDbSongindexByOrderIndex(unsigned int OrderIndex);
	int reqDbOrderindexBySongIndex(unsigned int SongIndex);
	
	int _setSongTblLocalDevice(char* dbPathNew, int deviceId);
	int _updateDBtoNewVersion(char* dbPathNew);
	int _clearSongTblLocalDevice(int deviceId);

	void loadPINYINCount(void);
	void freePINYINCount(void);
	void loadABCcount(void);
	void freeABCcount(void);

	//! SQL string registry
	typedef std::unordered_map<int, std::string> SQLTypeNameMap_t;
	SQLTypeNameMap_t SQLTypeNameRegistry;

	//! internel parameter for database access
	//sqlite3* d_db;
	sqlite3_stmt *g_stmt;
	char *g_ztail;

	//save song table
	char** 		result_buf;
	int 		result_nrow;
	int 		result_ncolumn;

	//! exist flag is updated
	bool updated;

	//! Privacy Flag
	int d_PrivacyFlag;

	//pthread for read a buffer
	pthread_t tableId;

	int d_reqSongTotalFlag;
	bool d_reqAllSongFlag;

	int d_abc[MAX_ABC_COUNT][2];
	
#ifdef A_BUFFER_FOR_NORMAL_LIST
	pthread_t d_ptNormalList;
#endif
};

}

#endif
