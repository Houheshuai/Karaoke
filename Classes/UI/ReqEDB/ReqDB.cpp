//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : ReqDB.cpp
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
#define FOREIFN_FLAG CEGUI::SONG_SUBTYPE_PHI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#ifndef WIN32
#include <sys/vfs.h>
#endif

#include "M3D_Config.h"
#include "GUIBase/M3D_Singleton.h"


#include "krkplayer/MCodeConvert.h"

#include "ReqListBuffer.h"
#include "ReqDB.h"
#include "PVRTString.h"
#include "PVRTResourceFile.h"
#define REQ_TEST

//#define LOAD_DB_AT_ANOTHER_PTHREAD
//#define REQ_BY_PREPARE_V2
#define LOAD_DB_PINYIN_TOTAL
#ifdef LOAD_DB_PINYIN_TOTAL
#define TEST_INDEX_ABC
#endif

#ifdef PLATFORM_UNIX
#include<semaphore.h>
sem_t sem_db_query;
#else
//#include <windows.h>
//HANDLE sem_db_query;
#endif

extern void CloseKeyEventALL(void);
extern void OpenKeyEventALL(void);



namespace CEGUI
{	

template<> CEGUI::ReqDB* MKSingleton<CEGUI::ReqDB>::ms_Singleton = 0;

#ifndef min
#define min(a, b)		((a>b)? b : a)
#endif

#ifndef REQ_BY_PREPARE_V2
#define MAX_BUFFER_COUNT 600
#else
#define MAX_BUFFER_COUNT 50
#endif
#define WAIT_BUFFER_COUNT 200
#define WAIT_SLEEP_TIME 200000

#define SingerIconListFile "SingerIcon/SingerIconList.txt"
#define SingerIconDefaultPath "SingerIcon/PVR/Default.pvr"
#define SingerIconDirPath "SingerIcon/PVR/"

#if 0
#define LETTER_A 'a'
#define LETTER_Z 'z'
#else
#define LETTER_A 'A'
#define LETTER_Z 'Z'
#endif

const SingerListBindingStruct_t SingerRecDummy = {"", 0,-1, "",-1,-1, LETTER_A, -1};
const SongListBindingStruct_t SongListRecDummy = {-1, -1, -1, -1, -1, -1, -1, -1, -1,-1, "","", "", -1,-1,-1,"",-1,-1,""};

template<> ReqDB* M3D_Singleton<ReqDB>::ms_Singleton = 0;

std::vector<std::string> d_sql_cmd;
std::vector<int> d_reGetBufferFlag; //0: wait; 1: req table; 2: req total;
int d_BufferCount=0, d_BufferStart=0;
bool d_reqTotalFlag = false;

static ReqDBSongInf_t *m_cacheTotalPinYinSong = NULL;
static ReqDBSongInf_t *m_cacheTotalOther = NULL;
static int d_QueryStart=0;
static int n_totalReadySongItems = 0;
static int n_totalSongItems = 0;
static int n_querItems = 0;
static int queryFlag = 0;

//----------------------------------------------------------------------------//
void* getDBTableBuffer(void* param)
{
	ReqDB *repDB = (ReqDB *)param;

	while(1)
	{
#ifdef PLATFORM_UNIX
		sem_wait(&sem_db_query);
#else
//		WaitForSingleObject(sem_db_query,INFINITE);
#endif

		d_QueryStart = -1;

		if(repDB->d_pthread_flag == 0)
		{
			return (void *)0;
		}

		int tmpFlag = d_reGetBufferFlag.back();
		std::string tmpCmd = d_sql_cmd.back();
		M3D_DebugPrint("<getDBTableBuffer> d_reGetBufferFlag = [%d]",tmpFlag);
		M3D_DebugPrint("<getDBTableBuffer> d_sql_cmd = [%s]",tmpCmd.c_str());

		sqlite3* d_db = repDB->d_db;  
		if(tmpFlag == 1 || tmpFlag == 3) //req table
		{
			M3D_DebugPrint("pthread get table.  START!\n");
			handleM3DRec& handle = repDB->handle;
			
			if(tmpFlag == 1)
			{
				if(n_totalReadySongItems < n_totalSongItems)
				{
					//Prepare鏌ヨ锛岄殢鏃跺彲浠ラ€€鍑烘煡璇紝濡傛灉宸茬粡鏈夋暟鍊硷紝鍒欎笉璧嬪€硷紝閲嶅叆鍙嶆瑕嗙洊鐩稿悓鐨勫€硷紝娌℃湁闂
					char * errMsg = NULL;
					int i = 0;
					int ret = 0;
					sqlite3_stmt *stmt;

					ret= sqlite3_prepare_v2(d_db, tmpCmd.c_str(), tmpCmd.size(), &stmt, 0);	
					if(ret != SQLITE_OK)
					{
						M3D_DebugPrint("Can't open statement: %s/n", sqlite3_errmsg(d_db));
						d_QueryStart = 0;
					}
					else
					{
						d_QueryStart = 2;
						n_querItems = 0;
						while(sqlite3_step(stmt)==SQLITE_ROW) 
						{
							//songid = sqlite3_column_int(stmt, 0);
							//SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType
							//璧?
							if(m_cacheTotalPinYinSong[d_BufferStart + i].SongIndex > 0)
							{
							}
							else
							{
#ifndef LOAD_LIST_BY_ONE_TABLE
								m_cacheTotalPinYinSong[d_BufferStart + i].SubFileType = sqlite3_column_int(stmt, 6);
#else
								m_cacheTotalPinYinSong[d_BufferStart + i].SubFileType = sqlite3_column_int(stmt, 3);
#endif
								const unsigned char *value = NULL;
								int size = 0;
#ifndef LOAD_LIST_BY_ONE_TABLE
								value = sqlite3_column_text(stmt, 5);
								size = sqlite3_column_bytes(stmt, 5);
								memcpy(m_cacheTotalPinYinSong[d_BufferStart + i].SingerName, value, size);

								value = sqlite3_column_text(stmt, 4);
								size = sqlite3_column_bytes(stmt, 4);
								memcpy(m_cacheTotalPinYinSong[d_BufferStart + i].FirstWord, value, size);
					
								value = sqlite3_column_text(stmt, 3);
								size = sqlite3_column_bytes(stmt, 3);
#else
								value = sqlite3_column_text(stmt, 4);
								size = sqlite3_column_bytes(stmt, 4);
#endif
								memcpy(m_cacheTotalPinYinSong[d_BufferStart + i].SongName, value, size);

								m_cacheTotalPinYinSong[d_BufferStart + i].FileType = sqlite3_column_int(stmt, 2);
								m_cacheTotalPinYinSong[d_BufferStart + i].OrderIndex = sqlite3_column_int(stmt, 1);
								m_cacheTotalPinYinSong[d_BufferStart + i].SongIndex = sqlite3_column_int(stmt, 0);

								n_totalReadySongItems++;
							}
							i++;

							n_querItems++;
							if(d_QueryStart == 1)
							{
								break;
							}
						}
						sqlite3_finalize(stmt);
						d_QueryStart = 0;
					}
				}
				else
				{
					d_QueryStart = 0;
				}
			}
			else
			{
					char * errMsg = NULL;
					int i = 0;
					int ret = 0;
					sqlite3_stmt *stmt;

					ret= sqlite3_prepare_v2(d_db, tmpCmd.c_str(), tmpCmd.size(), &stmt, 0);	
					if(ret != SQLITE_OK)
					{
						M3D_DebugPrint("Can't open statement: %s/n", sqlite3_errmsg(d_db));
						d_QueryStart = 0;
					}
					else
					{
						d_QueryStart = 2;
						n_querItems = 0;
						while(sqlite3_step(stmt)==SQLITE_ROW) 
						{
							//songid = sqlite3_column_int(stmt, 0);
							//SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType
							//锟借祴
							if(m_cacheTotalOther[d_BufferStart + i].SongIndex > 0)
							{
							}
							else
							{
								m_cacheTotalOther[d_BufferStart + i].SubFileType = sqlite3_column_int(stmt, 6);

								const unsigned char *value = NULL;
								int size = 0;

								value = sqlite3_column_text(stmt, 5);
								size = sqlite3_column_bytes(stmt, 5);
								memcpy(m_cacheTotalOther[d_BufferStart + i].SingerName, value, size);

								value = sqlite3_column_text(stmt, 4);
								size = sqlite3_column_bytes(stmt, 4);
								memcpy(m_cacheTotalOther[d_BufferStart + i].FirstWord, value, size);

								value = sqlite3_column_text(stmt, 3);
								size = sqlite3_column_bytes(stmt, 3);
								memcpy(m_cacheTotalOther[d_BufferStart + i].SongName, value, size);

								m_cacheTotalOther[d_BufferStart + i].FileType = sqlite3_column_int(stmt, 2);
								m_cacheTotalOther[d_BufferStart + i].OrderIndex = sqlite3_column_int(stmt, 1);
								m_cacheTotalOther[d_BufferStart + i].SongIndex = sqlite3_column_int(stmt, 0);
							}
							i++;
							n_querItems ++;
						}
						sqlite3_finalize(stmt);

						d_QueryStart = 0;
					}
			}
			//handle.reqResult.para1 = 0;
			//handle.reqResult.para2 = 0;
			handle.reqResult.para3 = d_BufferStart;

			M3D_DebugPrint("pthread get table.  Wait!\n");

		}
		else if(tmpFlag == 2)	//req total
		{
			M3D_DebugPrint("pthread req total.  START!\n");

			int tablerow2 = 0, tablecolumn2 = 0;
			char **tableazResult2; //save inquire result from db	
			char * tableerrMsg2 = NULL;
			handleM3DRec& handle = repDB->handle;
			//sqlite3* d_db = repDB->d_db;
			
			sqlite3_get_table(d_db, tmpCmd.c_str(), &tableazResult2, &tablerow2, &tablecolumn2, &tableerrMsg2);

			if (tableerrMsg2 != NULL)
				sqlite3_free(tableerrMsg2);
			
			handle.totalItems = atoi(tableazResult2[tablecolumn2]);
			M3D_DebugPrint("<getDBTableBuffer> handle.totalItems = [%d]\n",handle.totalItems);

			if (tableerrMsg2 != NULL)
			{
				sqlite3_free_table((char **)tableazResult2);
				tableerrMsg2 = NULL;
			}
			d_reqTotalFlag = true;
		}

		d_reGetBufferFlag.pop_back();
		d_sql_cmd.pop_back();
	}
	return (void *)0;
}

#ifdef A_BUFFER_FOR_NORMAL_LIST
typedef struct
{
	int lastIndex;
	bool nextFlag;
	String strPara;

} normalListInfo_t;

static normalListInfo_t PthCmdNormalInfo = {0,false,""};
static pthread_mutex_t* pLockNormalInfo = NULL;
#ifdef PLATFORM_UNIX
//#include<semaphore.h>
static sem_t SemNormalList;
static sem_t SemStartBind;
#else
//#include <windows.h>
static HANDLE SemNormalList;
static HANDLE SemStartBind;
#endif


//----------------------------------------------------------------------------//
void* reqNormalListBuffer(void* param)
{
	ReqDB* handledb = (ReqDB*)param;
	sqlite3_stmt *stmt;
	int index;
	ReqDBSongInf_t *songbuf;
	int bindflag;

	while(1)
{
#ifdef PLATFORM_UNIX
		sem_wait(&SemNormalList);
#else
		WaitForSingleObject(SemNormalList,INFINITE);
#endif
		if(handledb->d_NormalListFlag == 0)
			break;
		songbuf = handledb->d_pbNormalBuffer;

		pthread_mutex_lock(pLockNormalInfo);
		PthCmdNormalInfo.lastIndex = 0;
		PthCmdNormalInfo.nextFlag = false;
		handledb->d_loadSongEndFlag = 0;
		if(PthCmdNormalInfo.strPara.empty())
		{
			pthread_mutex_unlock(pLockNormalInfo);
			continue;
		}
		sqlite3_prepare_v2(handledb->d_db, PthCmdNormalInfo.strPara.c_str(), PthCmdNormalInfo.strPara.size(), &stmt, 0);
		pthread_mutex_unlock(pLockNormalInfo);

		bindflag = 0;
		index = 0;
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
#ifndef LOAD_LIST_BY_ONE_TABLE
			(songbuf + index)->SongIndex = sqlite3_column_int(stmt, 0);
			(songbuf + index)->OrderIndex = sqlite3_column_int(stmt, 1);
			(songbuf + index)->FileType = sqlite3_column_int(stmt, 2);
			strncpy((songbuf + index)->SongName, (const char*)sqlite3_column_text(stmt, 3), sizeof((songbuf + index)->SongName));
			strncpy((songbuf + index)->FirstWord, (const char*)sqlite3_column_text(stmt, 4), sizeof((songbuf + index)->FirstWord));
			strncpy((songbuf + index)->SingerName, (const char*)sqlite3_column_text(stmt, 5), sizeof((songbuf + index)->SingerName));
			(songbuf + index)->SubFileType = sqlite3_column_int(stmt, 6);
#else
			(songbuf + index)->SongIndex = sqlite3_column_int(stmt, 0);
			(songbuf + index)->OrderIndex = sqlite3_column_int(stmt, 1);
			(songbuf + index)->FileType = sqlite3_column_int(stmt, 2);
			(songbuf + index)->SubFileType = sqlite3_column_int(stmt, 3);
			strncpy((songbuf + index)->SongName, (const char*)sqlite3_column_text(stmt, 4), sizeof((songbuf + index)->SongName));
#endif
			index++;

			//update the songlist total
			handledb->handle.totalItems = index;

			if(bindflag == 0 && index > 120)
			{
#ifdef PLATFORM_UNIX
				sem_post(&SemStartBind);
#else
				ReleaseSemaphore(SemStartBind,1,NULL);
#endif
				bindflag = 1;
			}
			pthread_mutex_lock(pLockNormalInfo);
			PthCmdNormalInfo.lastIndex = index;
			if(PthCmdNormalInfo.nextFlag)
			{
				pthread_mutex_unlock(pLockNormalInfo);
				break;
			}
			pthread_mutex_unlock(pLockNormalInfo);
			
			if(handledb->d_NormalListFlag == 0)
				break;
		}
		sqlite3_finalize(stmt);
		pthread_mutex_lock(pLockNormalInfo);
		if(!PthCmdNormalInfo.nextFlag)
		{
			handledb->d_loadSongEndFlag = 1;
		}
		pthread_mutex_unlock(pLockNormalInfo);
		if(bindflag == 0)
		{
#ifdef PLATFORM_UNIX
			sem_post(&SemStartBind);
#else
			ReleaseSemaphore(SemStartBind,1,NULL);
#endif
			bindflag = 1;
		}
	}
	return NULL;
}
#endif

//----------------------------------------------------------------------------//
ReqDB::ReqDB(void* para1, int para2) : M3D_Req(para1, para2)
{
	String sqlstr;

	d_db = NULL;
	g_stmt = NULL;
	g_ztail = NULL;
	result_buf = NULL;
	result_nrow = 0;
	result_ncolumn = 0;

#ifdef PLATFORM_UNIX
	sem_init(&sem_db_query, 0, 0);
#else
	//sem_db_query = CreateSemaphore(NULL, 0, 100, "sem_db_query");
#endif
	
	updated = false;

	d_PrivacyFlag = 0;
	d_pthread_flag = 0;
	d_reqSongTotalFlag = 0;
	d_reqAllSongFlag = true;

	d_sql_cmd.clear();
	d_reGetBufferFlag.clear(); //0: wait; 1: req table; 2: req total;
	d_BufferCount=0;
	d_BufferStart=0;

	m_cacheTotalPinYinSong = NULL;
	m_cacheTotalOther = NULL;
	d_QueryStart=0;
	n_totalReadySongItems = 0;
	n_totalSongItems = 0;
	n_querItems = 0;
	d_tableSongTotal = 0;
#ifdef A_BUFFER_FOR_NORMAL_LIST
	d_NormalListFlag = 0;
	d_loadSongEndFlag = 1;
	d_pbNormalBuffer = NULL;
#endif

	//
	sqlstr.assign("SELECT ProductID, DBVersion, ProjectName FROM TableDBInfo;");
	regSQLString(REQDB_SQL_CUSTINFO, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SubFileType FROM TableSong;");// song all
	regSQLString(REQDB_SQL_ALLSONGINF, sqlstr);
	sqlstr.assign("SELECT COUNT(SongIndex) FROM TableSong;");// count of songs
	regSQLString(REQDB_SQL_SONGCOUNT, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_PINYIN WHERE SongIndex=%d;");// song info by SongIndex
	regSQLString(REQDB_SQL_SONGINF, sqlstr);
	sqlstr.assign("SELECT SongIndex FROM TableSong ORDER BY FirstWord LIMIT %d;");// SongIndex by Index
	regSQLString(REQDB_SQL_SONGINF_BY_INDEX, sqlstr);

	//singer
	sqlstr.assign("SELECT SingerIndex, SingerName, FirstWord FROM View_SingerMale WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// singer male
	regSQLString(REQDB_SQL_SINGER_MALE, sqlstr);
	sqlstr.assign("SELECT SingerIndex, SingerName, FirstWord FROM View_SingerFeMale WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// singer female
	regSQLString(REQDB_SQL_SINGER_FEMALE, sqlstr);
	sqlstr.assign("SELECT SingerIndex, SingerName, FirstWord FROM View_SingerBand WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// singer female
	regSQLString(REQDB_SQL_SINGER_BAND, sqlstr);

	sqlstr.assign("SELECT TableSong.SongIndex, TableSong.OrderIndex, TableSong.FileType, TableSong.SongName, TableSong.FirstWord, TableSinger.SingerName, TableSong.SubFileType FROM TableSongSinger1, TableSong, TableSinger WHERE TableSongSinger1.SongIndex=TableSong.SongIndex AND TableSongSinger1.SingerIndex=%d AND TableSongSinger1.SingerIndex=TableSinger.SingerIndex AND TableSong.FirstWord>='%s' COLLATE NOCASE and TableSong.FirstWord<='%szz' COLLATE NOCASE ORDER BY TableSong.FirstWord COLLATE NOCASE LIMIT %d OFFSET %d;");// singer song
	regSQLString(REQDB_SQL_SONG_SINGER, sqlstr);
#ifndef LOAD_LIST_BY_ONE_TABLE
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_PINYIN WHERE (LanType = 4 OR LanType = 12) AND FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song pinyin
#else
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName FROM TableSong WHERE (LanType = 4 OR LanType = 12) AND FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song pinyin
#endif
	regSQLString(REQDB_SQL_SONG_PINYIN, sqlstr);

	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LCNSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language CN
	regSQLString(REQDB_SQL_LAN_CN, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LENSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language EN
	regSQLString(REQDB_SQL_LAN_EN, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LJPSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language JP
	regSQLString(REQDB_SQL_LAN_JP, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LKRSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language KR
	regSQLString(REQDB_SQL_LAN_KR, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LVIESong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language VIE
	regSQLString(REQDB_SQL_LAN_VIE, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LTHSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language TH
	regSQLString(REQDB_SQL_LAN_TH, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LRUSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language RU
	regSQLString(REQDB_SQL_LAN_RU, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LSPSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language SP
	regSQLString(REQDB_SQL_LAN_SP, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LPHISong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language PHI
	regSQLString(REQDB_SQL_LAN_PHI, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LFRSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language FR
	regSQLString(REQDB_SQL_LAN_FR, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LIDSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language ID
	regSQLString(REQDB_SQL_LAN_ID, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LINSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language IN
	regSQLString(REQDB_SQL_LAN_IN, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_LMYSong WHERE FirstWord >='%s' and FirstWord<='%szz'  LIMIT %d OFFSET %d;");// song language MY
	regSQLString(REQDB_SQL_LAN_MY, sqlstr);

	//type
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_MP3Song WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// mp3
	regSQLString(REQDB_SQL_MP3, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_MTVSong WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// mtv
	regSQLString(REQDB_SQL_MTV, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_Movie WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// movie
	regSQLString(REQDB_SQL_MOVIE, sqlstr);

	//
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_Popular WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// song popular
	regSQLString(REQDB_SQL_SONG_POP, sqlstr);
	regSQLString(REQDB_SQL_SONG_HOT, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_Hot WHERE Hots>0 AND FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// song MyHot
	regSQLString(REQDB_SQL_MYHOTID, sqlstr);
	sqlstr.assign("SELECT SongIndex, OrderIndex, FileType, SongName, FirstWord, SingerName, SubFileType FROM View_Fav WHERE FirstWord>='%s' and FirstWord<='%szz' LIMIT %d OFFSET %d;");// song favorite
	regSQLString(REQDB_SQL_FAVOID, sqlstr);

	//
	sqlstr.assign("SELECT SongIndex FROM TableSong WHERE (FileType = 4 OR FileType = 3);");// mp3 is 4; mtv is 3
	regSQLString(REQDB_SQL_MP3_OR_MTV, sqlstr);
	sqlstr.assign("SELECT SongIndex FROM TableSong WHERE FileType = 4;");// mp3 is 4
	regSQLString(REQDB_SQL_GET_MP3, sqlstr);
	sqlstr.assign("SELECT SongIndex FROM TableSong WHERE FileType = 3;");// mtv is 3
	regSQLString(REQDB_SQL_GET_MTV, sqlstr);

	//
	sqlstr.assign("SELECT SongIndex, FileType, SongName, SubFileType FROM View_Book WHERE PrivacyFlag<=%d AND OrderIndex=%d;");// num song
	regSQLString(REQDB_SQL_BOOK, sqlstr);
	sqlstr.assign("SELECT SongIndex, FileType, SongName, SubFileType FROM View_Book WHERE PrivacyFlag<=%d AND OrderIndex=%d AND (LanType=4 OR LanType=%d);");// num song no foreign song
	regSQLString(REQDB_SQL_BOOK_NO_FOREIGN, sqlstr);

	//
	sqlstr.assign("SELECT COUNT(SongIndex) FROM TableSong WHERE (LanType = 4 OR LanType = 12) AND FirstWord >='%s' AND FirstWord<='%szz';");// count of songs
	regSQLString(REQDB_SQL_PINYIN_COUNT, sqlstr);
	sqlstr.assign("SELECT COUNT(SongIndex), AlphaIndex FROM TableSong WHERE (LanType = 4 OR LanType = 12) GROUP BY AlphaIndex;");// REQDB_SQL_SONG_LETTER_INDEX_COUNT
	regSQLString(REQDB_SQL_SONG_LETTER_INDEX_COUNT, sqlstr);

	//
	sqlstr.assign("SELECT SongIndex FROM HotSong ORDER BY Hots DESC;");
	regSQLString(REQDB_SQL_MY_HOT_SONGID, sqlstr);
	sqlstr.assign("SELECT TableSinger.SingerName FROM TableSongSinger1,TableSinger WHERE TableSongSinger1.SongIndex = %d AND TableSongSinger1.SingerIndex = TableSinger.SingerIndex;");
	regSQLString(REQDB_SQL_SINGER_BY_SONGID, sqlstr);
	sqlstr.assign("SELECT SongIndex FROM FavoriteSong;");
	regSQLString(REQDB_SQL_FAVO_LOAD, sqlstr);

#ifdef LOAD_DB_AT_ANOTHER_PTHREAD
	pthreadCreate();
#endif
}
	
//----------------------------------------------------------------------------//
ReqDB::~ReqDB(void)
{
	SQLTypeNameRegistry.clear();

#ifdef LOAD_DB_AT_ANOTHER_PTHREAD
	pthreadDestroy();
#endif

#ifdef PLATFORM_UNIX
	sem_destroy(&sem_db_query);
#else
//	CloseHandle(sem_db_query);
#endif

#ifndef USE_LIST_BUFFER_FOR_SOME_LIST
	freePINYINCount();
#endif

	if(m_cacheTotalOther != NULL)
	{
		delete[] m_cacheTotalOther;
		m_cacheTotalOther = NULL;
	}

#ifndef USE_LIST_BUFFER_FOR_SOME_LIST
	freeABCcount();
#endif

#if 0
	reqDeInit();
	//reqDeInitSongInf();
	int ret = sqlite3_close(d_db);
	d_db = NULL;
	assert(ret == SQLITE_OK);
#endif
}

void ReqDB::loadPINYINCount(void)
{
#ifdef LOAD_DB_AT_ANOTHER_PTHREAD
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int row = 0, column = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	
	memset(sql_cmd, 0, sizeof(sql_cmd));
	memset(strpara, 0, sizeof(strpara));
	if (checkSQLExist(REQDB_SQL_PINYIN_COUNT))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_PINYIN_COUNT), strpara, strpara, -1, 0);
	assert(strlen(sql_cmd) < SQL_STR_SZ);

	sqlite3_get_table(d_db, sql_cmd, &azResult, &row, &column, &errMsg);

	if (errMsg != NULL)
		sqlite3_free(errMsg);
	
	handle.totalItems = atoi(azResult[column]);
	sqlite3_free_table(azResult);

	d_tableSongTotal = handle.totalItems;
	if(m_cacheTotalPinYinSong == NULL)
	{
		n_totalSongItems = d_tableSongTotal;
		m_cacheTotalPinYinSong = new ReqDBSongInf_t[n_totalSongItems+1];
		memset(m_cacheTotalPinYinSong, 0, sizeof(ReqDBSongInf_t)*(n_totalSongItems+1));
	}

	memset(sql_cmd, 0, sizeof(sql_cmd));
	if (checkSQLExist(REQDB_SQL_SONG_PINYIN))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_SONG_PINYIN), strpara, strpara, d_tableSongTotal, 0);
	assert(strlen(sql_cmd) < SQL_STR_SZ);
	d_sql_cmd.insert(d_sql_cmd.begin(), std::string(sql_cmd));
	d_reGetBufferFlag.insert(d_reGetBufferFlag.begin(), 1);
	
#ifdef PLATFORM_UNIX
	sem_post(&sem_db_query);
#else
	ReleaseSemaphore(sem_db_query,1,NULL);
#endif
#endif
}

void ReqDB::freePINYINCount(void)
{
#ifdef LOAD_DB_AT_ANOTHER_PTHREAD
	if(m_cacheTotalPinYinSong != NULL)
	{
		delete[] m_cacheTotalPinYinSong;
		m_cacheTotalPinYinSong = NULL;
	}
#endif
}

void ReqDB::loadABCcount(void)
{
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int index;
	int startRow = 0;
	
	memset(sql_cmd, 0, sizeof(sql_cmd));
	memset(d_abc, 0, sizeof(d_abc));

	if (checkSQLExist(REQDB_SQL_SONG_LETTER_INDEX_COUNT))
		sprintf(sql_cmd, "%s",(char *)getSQLString(REQDB_SQL_SONG_LETTER_INDEX_COUNT));
	assert(strlen(sql_cmd) < SQL_STR_SZ);

	sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
	if (errMsg != NULL)
		sqlite3_free(errMsg);

	for (int i = 1; i < nrow + 1; i++)
	{
		index = atoi(azResult[i*ncolumn + 1]);
		index = min(MAX_ABC_COUNT - 1, index);
		d_abc[index][0] = atoi(azResult[i*ncolumn]);
		d_abc[index][1] = startRow;
		startRow += d_abc[index][0];
	}
	sqlite3_free_table(azResult);
}

void ReqDB::freeABCcount(void)
{
}

int ReqDB::fileRename(char *name1, char *name2)
{
	M3D_FILE fp =NULL;
	int ret = -1;
		
	M3D_DebugPrint("fileRename:%s, %s\n", name1, name2);
	if((fp = M3D_fopen(name1, "r")) == NULL)
		return -1;
	else
		M3D_fclose(fp);

	if((fp = M3D_fopen(name2, "r")) != NULL)
	{
		M3D_fclose(fp);
		M3D_fremove(name2);
	}
	
	ret = rename(name1, name2);
	M3D_DebugPrint("fileRename:ret = %d\n", ret);
	return ret;
}

bool ReqDB::dirFreeSize(const char *dir, unsigned int *freeK)
{
	int ret = -1;
#ifndef WIN32

	struct statfs sfs;

	M3D_DebugPrint("dirFreeSize:%s\n", dir);
	if(freeK != NULL)
	{
		ret = statfs(dir, &sfs);
		if(ret >= 0)
			*freeK = ((long long)sfs.f_bsize) * ((long long)sfs.f_bfree)/1024;
		else
			*freeK = 0;
	}

	M3D_DebugPrint("dirFreeSize:ret = %d, sfs.f_bsize = %d, sfs.f_bfree = %d, *freeK = %d\n", ret, sfs.f_bsize, sfs.f_bfree, *freeK);
#else
	*freeK = (1024*1024);
	ret = 0;
#endif
	return (ret >= 0);
}

unsigned int ReqDB::dirFreeSize(const char *dir)
{
	unsigned int ret = 0;
#ifndef WIN32

	struct statfs sfs;

	M3D_DebugPrint("dirFreeSize:%s\n", dir);
	{
		ret = statfs(dir, &sfs);
		if(ret >= 0)
			ret = (unsigned int)(((long long)sfs.f_bsize) * ((long long)sfs.f_bfree)/1024);
		else
			ret = 0;
	}

	M3D_DebugPrint("dirFreeSize:ret = %d, sfs.f_bsize = %d, sfs.f_bfree = %d\n", ret, sfs.f_bsize, sfs.f_bfree);
#else
	ret = (1024*1024);
#endif
	return ret;
}

//----------------------------------------------------------------------------//
int ReqDB::fileCopy(char *from, char *to)
{
	char buff[256];
	FILE  *fpTo, *fpFrom;
	unsigned int readlen;
	int ret = 0;
	
	M3D_DebugPrint("fileCopy : from = %s, to = %s\n", from, to);

	//remove to file
	fpTo = fopen(to,"rb");

	if(fpTo != NULL)
	{
		fclose(fpTo);
		M3D_fremove(to);
	}

	//copy
	fpFrom = fopen(from,"rb");
	if(fpFrom != NULL)
	{
		fpTo = fopen(to,"wb");
		if(fpTo != NULL)
		{
			M3D_fseek(fpFrom,0,SEEK_SET);
			while((readlen = fread(buff, 1, 256, fpFrom)) > 0)
			{
				fwrite(buff, 1, readlen, fpTo);
			}
			fclose(fpTo);
			ret = 1;
		}
		fclose(fpFrom);
	}
	return ret;
}


void ReqDB::DecDataX(unsigned char * pData, unsigned EncLength, unsigned char CustNoHigh, unsigned char CustNoLow)
{
	unsigned long Cnt;
	unsigned long Cnt2;
	unsigned char Cnt3;
	unsigned char Cnt4;
	unsigned char SwitchData;

	for(Cnt =0; Cnt < (EncLength/512); Cnt ++)
	{
		for(Cnt2 = 0; Cnt2 < 256; Cnt2 ++)
		{
			// bit 7..0 -> bit 0..7
			Cnt3 = 
				((Cnt2 & (1<<0)?1:0) << 7) +
				((Cnt2 & (1<<1)?1:0) << 6) +
				((Cnt2 & (1<<2)?1:0) << 4) +
				((Cnt2 & (1<<3)?1:0) << 5) +
				((Cnt2 & (1<<4)?1:0) << 2) +
				((Cnt2 & (1<<5)?1:0) << 3) +
				((Cnt2 & (1<<6)?1:0) << 1) +
				((Cnt2 & (1<<7)?1:0) << 0) ;
			// bit 7..0 -> bit 0..7 

			Cnt4 = 
				((Cnt2 & (1<<0)?1:0) << 6) +
				((Cnt2 & (1<<1)?1:0) << 5) +
				((Cnt2 & (1<<2)?1:0) << 7) +
				((Cnt2 & (1<<3)?1:0) << 3) +
				((Cnt2 & (1<<4)?1:0) << 4) +
				((Cnt2 & (1<<5)?1:0) << 0) +
				((Cnt2 & (1<<6)?1:0) << 2) +
				((Cnt2 & (1<<7)?1:0) << 1) ;

			//switch data
			SwitchData = pData[Cnt * 512 + 256 + Cnt3];
			pData[Cnt * 512 + 256 + Cnt3] = pData[Cnt * 512 + Cnt2];
			pData[Cnt * 512 + Cnt2] = SwitchData;
			//xor data
			pData[Cnt * 512 + Cnt2] ^= (Cnt4 ^ CustNoHigh);
			pData[Cnt * 512 + 256 + Cnt3] ^= (Cnt4 ^ CustNoLow);
		}
	}
}

//----------------------------------------------------------------------------//
bool ReqDB::pthreadCreate(void)
{
	int ret;
	if(d_pthread_flag != 0)
{
}
	else
	{
		ret = pthread_create(&tableId, NULL, getDBTableBuffer, this);
		if (ret != 0)
		{
			//error
			if (handle.reqResult.Buffer != NULL)
{
		sqlite3_free_table((char * *)handle.reqResult.Buffer);
		handle.reqResult.Buffer = NULL;
	}
			M3D_DebugPrint("pthread create fail!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
		else
	{
			d_pthread_flag = 1;
		}
	}
		
#ifdef A_BUFFER_FOR_NORMAL_LIST
	//
	if(d_NormalListFlag != 0)
		{
		}
		else
		{
		pLockNormalInfo = new pthread_mutex_t;
		pthread_mutex_init(pLockNormalInfo, NULL);
#ifdef PLATFORM_UNIX
		sem_init(&SemNormalList, 0, 0);
		sem_init(&SemStartBind, 0, 0);
#else
		SemNormalList = CreateSemaphore(NULL, 0, 100, "SemNormalList");
		SemStartBind = CreateSemaphore(NULL, 0, 100, "SemStartBind");
#endif
		ret = pthread_create(&d_ptNormalList, NULL, reqNormalListBuffer, this);
		if (ret != 0)
		{
			//error
			M3D_DebugPrint("NormalList pthread create fail!!!\n");
	}
	else
	{
			d_NormalListFlag = 1;
	}
	}
#endif

	return true;
}

//----------------------------------------------------------------------------//
bool ReqDB::pthreadDestroy(void)
{
	d_pthread_flag = 0;

#ifdef PLATFORM_UNIX
	sem_post(&sem_db_query);
#else
	//ReleaseSemaphore(sem_db_query,1,NULL);
#endif
	pthread_join(tableId, NULL);
	
#ifdef REQ_BY_PREPARE_V2
	prepareBuffer.clear();
#endif

#ifdef A_BUFFER_FOR_NORMAL_LIST
	//
	if(d_NormalListFlag != 0)
			{
		d_NormalListFlag = 0;
#ifdef PLATFORM_UNIX
		sem_post(&SemNormalList);
#else
		ReleaseSemaphore(SemNormalList,1,NULL);
#endif
		pthread_join(d_ptNormalList, NULL);
#ifdef PLATFORM_UNIX
		sem_destroy(&SemStartBind);
		sem_destroy(&SemNormalList);
#else
		CloseHandle(SemStartBind);
		CloseHandle(SemNormalList);
#endif
		pthread_mutex_destroy(pLockNormalInfo);
		delete pLockNormalInfo;
			}
#endif

	return true;
		}

//----------------------------------------------------------------------------//
int ReqDB::reqInit(M3DReqCmd_t& cmd, int onePageItems)
		{
	assert(d_db);

	return M3D_Req::reqInit(cmd, onePageItems);
		}

//----------------------------------------------------------------------------//
int ReqDB::reqDeInit(void)
		{
	if (handle.reqResult.Buffer != NULL) {
		sqlite3_free_table((char * *)handle.reqResult.Buffer);
		handle.reqResult.Buffer = NULL;
	}	
	reqDeInitSongInf();

	return 0;
}

//----------------------------------------------------------------------------//
void ReqDB::refreshDBDataBuffer()
{
	updateDBDataBuffer();
}

//----------------------------------------------------------------------------//
int ReqDB::reqRec(int reqStart, int reqCount)
{
	int ret = 0;
	
	switch (handle.reqCmd.type) {
		
	case REQDB_TYPE_SINGER:
		ret = reqSinger(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_SINGERSONG:
		ret = reqSingerSong(reqStart, reqCount);
		break;
	
	case REQDB_TYPE_ZIBU:
		ret = reqZibuSong(reqStart, reqCount);
		break;
				
	case REQDB_TYPE_PINYIN:
		ret = reqPinyinSong(reqStart, reqCount);
		break;
	
	case REQDB_TYPE_CLASSIC:
		ret = reqClassicSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_MYSONG:
		ret = reqMySong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_RECORDSONG:
		ret = reqRecordSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_EASYSONG:
		ret = reqEasySong(reqStart, reqCount);
		break;

	case REQDB_TYPE_HOTSONG:
		ret = reqHotSong(reqStart, reqCount);
		break;

	case REQDB_TYPE_NEWSONG:
		ret = reqNewSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_FAVSONG:
		ret = reqFavorSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_RESERVED:
		ret = reqReservedSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_MP3SONG:
		ret = reqMp3Song(reqStart, reqCount);
		break;

	case REQDB_TYPE_SHARESONG:
		ret = reqShareSong(reqStart, reqCount);
		break;

	case REQDB_TYPE_WEBNEWSONG:
		ret = reqWebNewSong(reqStart, reqCount);
		break;

	case REQDB_TYPE_WEBHOTSONG:
		ret = reqWebHotSong(reqStart, reqCount);
		break;
	case REQDB_TYPE_WEBCOMPETITIONSONG:
		ret = reqWebCompetitionSong(reqStart, reqCount);
		break;
	case REQDB_TYPE_CUSTOM:
		ret = reqCustomItems(reqStart, reqCount);
		break;
	case REQDB_TYPE_SINGER_TYPE:
		ret = reqSingerType(reqStart, reqCount);
		break;
			
	case REQDB_TYPE_LANGUAGE:
		ret = reqLanguage(reqStart, reqCount);
		break;
	case REQDB_TYPE_LANGUAGE_SONG:
		ret = reqLanguageSong(reqStart, reqCount);
		break;

	case REQDB_TYPE_NUM_SONG:
		ret = reqNumSong(reqStart, reqCount);
		break;
		
	case REQDB_TYPE_MYHOT_SONG:
		ret = reqMyHotSong(reqStart, reqCount);
		break;

	case REQDB_TYPE_DOWNLOAD:
		ret = reqDownload(reqStart, reqCount);
		break;
		
	default :
		ret = reqMySong(reqStart,reqCount);
		break;
	}
	return ret;
}

//----------------------------------------------------------------------------//
bool ReqDB::reqSingerPic(int num)
{
	CPVRTString path = CPVRTResourceFile::GetReadPath();
	CPVRTString fn = path + SingerIconListFile;
	FILE *fp = NULL;
	unsigned int i;
	char SingerIconName[BINDING_SINGERNAME_LEN];
	char SingerIconPath[BINDING_SINGERICON_PATH_LEN];
	char ChangeUncodeName[BINDING_SINGERNAME_LEN];
	char SingerIconPath_UTF8[BINDING_SINGERICON_PATH_LEN];
	char temp[BINDING_SINGERICON_PATH_LEN];
	
	if(num < 0)
		return false;
	if((fp = fopen(fn.c_str(), "r")) == NULL)
	return false;
	else
	{
		while(!feof(fp))
		{
			memset(ChangeUncodeName, '\0', sizeof(ChangeUncodeName));
			memset(SingerIconPath_UTF8, '\0', sizeof(SingerIconPath_UTF8));
			memset(SingerIconName, '\0', sizeof(SingerIconName));
			memset(SingerIconPath, '\0', sizeof(SingerIconPath));
			memset(bindingRec.items[num].singer.SingerIconPath, '\0', sizeof(bindingRec.items[num].singer.SingerIconPath));
			
			fgets(SingerIconPath, sizeof(SingerIconPath), fp);
			for(i = 0; i < strlen(SingerIconPath); i++)
			{
				if(SingerIconPath[i] == '\n')
				{
					SingerIconPath[i] = '\0';
					break;
				}
			}
			strncpy(SingerIconName, SingerIconPath, sizeof(SingerIconName)-1);
			for(i = 0; i < strlen(SingerIconName); i++)
			{
				if(SingerIconName[i] == '.')
				{
					SingerIconName[i] = '\0';
					break;
				}
			}
			for(; i < strlen(SingerIconName); i++)
			{
				SingerIconName[i] = '\0';
			}
			MCodeConvert_GB2312toUTF8(SingerIconName, ChangeUncodeName, strlen(SingerIconName), sizeof(ChangeUncodeName));
			memset(temp, '\0', sizeof(temp));
			strncpy(temp, (char*)SingerIconDirPath, sizeof(temp)-1);
			strcat(temp, SingerIconPath);
			memset(SingerIconPath, '\0', sizeof(SingerIconPath));
			strncpy(SingerIconPath, temp, sizeof(SingerIconPath)-1);
			#ifndef WIN32
			MCodeConvert_GB2312toUTF8(SingerIconPath, SingerIconPath_UTF8, strlen(SingerIconPath), sizeof(SingerIconPath));
			#endif
			if(strcmp(bindingRec.items[num].singer.SingerName, ChangeUncodeName) == 0)
			{
				memset(bindingRec.items[num].singer.SingerIconPath, '\0', sizeof(bindingRec.items[num].singer.SingerIconPath));
				#ifdef WIN32
				strncpy(bindingRec.items[num].singer.SingerIconPath, SingerIconPath, sizeof(bindingRec.items[num].singer.SingerIconPath)-1);
				#else
				strncpy(bindingRec.items[num].singer.SingerIconPath, SingerIconPath_UTF8, sizeof(bindingRec.items[num].singer.SingerIconPath)-1);
				#endif
				break;
			}
			else
			{
				memset(bindingRec.items[num].singer.SingerIconPath, '\0', sizeof(bindingRec.items[num].singer.SingerIconPath));
				strncpy(bindingRec.items[num].singer.SingerIconPath, (char*)SingerIconDefaultPath, sizeof(bindingRec.items[num].singer.SingerIconPath)-1);
			}
		}
		
		fclose(fp);
		return true;
	}
}

//----------------------------------------------------------------------------//
void ReqDB::reqSongExtraInf(SongListBindingStruct_t& song, bool isreserverd)
{
	
}

//----------------------------------------------------------------------------//

int ReqDB::reqSingerCount(int SingerType)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;


	memset(sql_cmd, 0, sizeof(sql_cmd));
	strcpy(strpara, "");
	//strcat(strpara, "%");

	switch(SingerType)
	{
	case REQDB_SUBTYPE_SINGER_MALE:
		if (checkSQLExist(REQDB_SQL_SINGER_MALE))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_MALE), strpara, strpara, -1, 0);
		break;
	case REQDB_SUBTYPE_SINGER_FEMALE:
		if (checkSQLExist(REQDB_SQL_SINGER_FEMALE))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_FEMALE), strpara, strpara, -1, 0);
		break;
	case REQDB_SUBTYPE_SINGER_BAND:
	default:
		if (checkSQLExist(REQDB_SQL_SINGER_BAND))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_BAND), strpara, strpara,-1, 0);
		break;
	}

	sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

	sqlite3_free_table(azResult);
	return nrow;

	
}
//----------------------------------------------------------------------------//
int ReqDB::reqSinger(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;
	//unsigned int singerIndex;

	strncpy(strpara, handle.reqCmd.strPara, sizeof(strpara));

#ifdef USE_LIST_BUFFER_FOR_SOME_LIST
	NeedSingerInfo_t *tmpsingerinfo;
	int bindex;
	int BufferSongType;
	switch(handle.reqCmd.subType)
	{
	case REQDB_SUBTYPE_SINGER_MALE:
		BufferSongType = BUFFER_SINGER_TYPE_MALE;
		break;
	case REQDB_SUBTYPE_SINGER_FEMALE:
		BufferSongType = BUFFER_SINGER_TYPE_FEMALE;
		break;
 	case REQDB_SUBTYPE_SINGER_BAND:
 		BufferSongType = BUFFER_SINGER_TYPE_BAND;
 		break;
	default:
		BufferSongType = BUFFER_SINGER_TYPE_ALL;
		break;
	}
	int retBuffer = reqBufferSingerList(BufferSongType, reqStart, reqCount, strpara, &tmpsingerinfo);
	if(retBuffer != -1)
	{
		if(reqCount == -1)
			return retBuffer;
		else
		{
			for(bindex = 0; bindex<retBuffer; bindex++)
			{
				memset(&bindingRec.items[bindex], 0, sizeof(DBBindingStruct_t));
				bindingRec.items[bindex].singer.dataIndex = reqStart + bindex;
			
				bindingRec.items[bindex].singer.SingerType = tmpsingerinfo[bindex].Sex-1;
				bindingRec.items[bindex].singer.SingerIndex = tmpsingerinfo[bindex].SingerIndex;
				strncpy(bindingRec.items[bindex].singer.SingerName, tmpsingerinfo[bindex].SingerName, sizeof(bindingRec.items[bindex].singer.SingerName));
				bindingRec.items[bindex].singer.SongCount = 0;
			}
			for (; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].singer = SingerRecDummy;
			}
		}
		return retBuffer;
	}
#endif
	
	if (reqCount == -1) {
		memset(sql_cmd, 0, sizeof(sql_cmd));
		//strcat(strpara, "%");
		assert(strlen(strpara) < sizeof(handle.reqCmd.strPara));

		//inquire data from db
		switch(handle.reqCmd.subType)
		{
		case REQDB_SUBTYPE_SINGER_MALE:
			if (checkSQLExist(REQDB_SQL_SINGER_MALE))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_MALE), strpara, strpara, reqCount, reqStart);
			break;
		case REQDB_SUBTYPE_SINGER_FEMALE:
			if (checkSQLExist(REQDB_SQL_SINGER_FEMALE))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_FEMALE), strpara, strpara, reqCount, reqStart);
			break;
		case REQDB_SUBTYPE_SINGER_BAND:
			if (checkSQLExist(REQDB_SQL_SINGER_BAND))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_BAND), strpara, strpara, reqCount, reqStart);
			break;
		default:
			if (checkSQLExist(REQDB_SQL_SINGER_BAND))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_SINGER_BAND), strpara, strpara, reqCount, reqStart);
			break;
		}
		
		assert(strlen(sql_cmd) < SQL_STR_SZ);
		
		if (handle.reqResult.Buffer != NULL)
		{
			sqlite3_free_table((char * *)handle.reqResult.Buffer);
			handle.reqResult.Buffer = NULL;
		}
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
		
		handle.reqResult.Buffer = azResult;
		handle.reqResult.para1 = ncolumn;

#ifdef REQ_TEST		
		for (j = 0; j < MAX_BINDREC_COUNT; j ++)
		{
			bindingRec.items[j].singer = SingerRecDummy;
		}
#endif
		return nrow;
	}
	else if (handle.reqResult.Buffer != NULL) {
				
		azResult = (char **)(handle.reqResult.Buffer);
		ncolumn = handle.reqResult.para1;
#ifdef REQ_TEST		
		reqCount = min(MAX_BINDREC_COUNT-handle.reqCmd.itemIndex, reqCount);
		//memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{ 			
			memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
			bindingRec.items[j+handle.reqCmd.itemIndex].singer.dataIndex = i - 1;
			bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerType = handle.reqCmd.subType;

			bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerIndex = atoi(azResult[i*ncolumn]);
			if(azResult[i*ncolumn + 1] != NULL)
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerName, azResult[i*ncolumn + 1], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerName)-1);
			else
				sprintf(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerName," ");
			//bindingRec.items[j+handle.reqCmd.itemIndex].singer.firstWord = azResult[i*ncolumn + 2][0];
			//if(!reqSingerPic(j)){
			//	//memset(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerIconPath, '\0', sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerIconPath));
			//	strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerIconPath," ",sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].singer.SingerIconPath) - 1);
			//}
			//zhangww add
			bindingRec.items[j+handle.reqCmd.itemIndex].singer.SongCount = 0;//atoi(azResult[i*ncolumn]);
				
			ret ++;
		}
		for (; j < reqCount; j ++)
		{
			bindingRec.items[j+handle.reqCmd.itemIndex].singer = SingerRecDummy;
		}

#else
		reqCount = min(MAX_BINDREC_COUNT, reqCount);
		memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{
			bindingRec.items[j].singer.SingerIndex = atoi(azResult[i*ncolumn]);
			if(azResult[i*ncolumn + 1] != NULL)
				strncpy(bindingRec.items[j].singer.SingerName, azResult[i*ncolumn + 1], sizeof(bindingRec.items[j].singer.SingerName)-1);
			else
				sprintf(bindingRec.items[j].singer.SingerName," ");
			//bindingRec.items[j].singer.firstWord = azResult[i*ncolumn + 2][0];
			if(!reqSingerPic(j)){
				//memset(bindingRec.items[j].singer.SingerIconPath, '\0', sizeof(bindingRec.items[j].singer.SingerIconPath));
				strncpy(bindingRec.items[j].singer.SingerIconPath," ",sizeof(bindingRec.items[j].singer.SingerIconPath) - 1);
			}

			ret ++;
		}

		for (; j < reqCount; j ++)
		{
			bindingRec.items[j].singer = SingerRecDummy;
		}
		
#endif		
	}
	else {
		M3D_DebugPrint("Request dataset is NULL\n");
	}
	return ret;
}

//----------------------------------------------------------------------------//
int ReqDB::reqSingerSong(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;
	
	if (reqCount == -1) {
		
		memset(sql_cmd, 0, sizeof(sql_cmd));
		strcpy(strpara, handle.reqCmd.strPara);
		//strcat(strpara, "%");
		assert(strlen(strpara) < sizeof(handle.reqCmd.strPara));
		
		//inquire data from db
		//sprintf(sql_cmd, "SELECT songName, singerName, songId, degree FROM SongTab WHERE tvExistFlag=1 and songId > 0 and singerNum = %d AND headspell LIKE '%s' ORDER BY headspell LIMIT %d OFFSET %d;", handle.reqCmd.subType, strpara, reqCount, reqStart);
		if (checkSQLExist(REQDB_SQL_SONG_SINGER))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SONG_SINGER), handle.reqCmd.subType, strpara, strpara, reqCount, reqStart);

		assert(strlen(sql_cmd) < SQL_STR_SZ);
		if (handle.reqResult.Buffer != NULL)
		{
			sqlite3_free_table((char * *)handle.reqResult.Buffer);
			handle.reqResult.Buffer = NULL;
		}
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
		
		handle.reqResult.Buffer = azResult;
		handle.reqResult.para1 = ncolumn;
		
#ifdef REQ_TEST		
		for (j = 0; j < MAX_BINDREC_COUNT; j ++)
		{
			bindingRec.items[j].song = SongListRecDummy;
		}
#endif
		return nrow;
	}
	else if (handle.reqResult.Buffer != NULL) {
		
		azResult = (char **)(handle.reqResult.Buffer);
		ncolumn = handle.reqResult.para1;
	
		reqCount = min(MAX_BINDREC_COUNT-handle.reqCmd.itemIndex, reqCount);
		//memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{ 			
			memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
			bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = i - 1;
			bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = atoi(azResult[i*ncolumn]); 
			bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = atoi(azResult[i*ncolumn + 1]);
			bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = atoi(azResult[i*ncolumn + 2]);
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, azResult[i*ncolumn + 3], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);
			//bindingRec.items[j+handle.reqCmd.itemIndex].song.firstWord = azResult[i*ncolumn + 4][0];
			if(azResult[i*ncolumn + 5] != NULL)
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName, azResult[i*ncolumn + 5], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName)-1);
			else
				sprintf(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName," ");
			bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = atoi(azResult[i*ncolumn + 6]);

			reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);

			ret ++;
		}
		for (; j < reqCount; j ++)
		{
			bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
		}
	}
	else {
		for (j =0; j < reqCount; j ++)
		{
			bindingRec.items[j].song = SongListRecDummy;
		}
		M3D_DebugPrint("Request dataset is NULL\n");
	}
	
	return ret;
}


//----------------------------------------------------------------------------//
int ReqDB::reqZibuSong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqPinyinSong(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0, nstart = 0;
	//char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;
	static int queryFirstFlag = 1;
	
	strncpy(strpara, handle.reqCmd.strPara, sizeof(strpara));

	NeedSongInfo_t *tmpsonginfo;
	int bindex;
	int BufferSongType = BUFFER_SONG_TYPE_PINYIN;

	int retBuffer = reqBufferSongList(BufferSongType, reqStart, reqCount, strpara, &tmpsonginfo);
	if(retBuffer != -1)
	{
		if(reqCount == -1)
			return retBuffer;
		else
		{
			for(bindex = 0; bindex<retBuffer; bindex++)
			{
				memset(&bindingRec.items[bindex], 0, sizeof(DBBindingStruct_t));
				bindingRec.items[bindex].song.dataIndex = reqStart + bindex;

				bindingRec.items[bindex].song.SongIndex = tmpsonginfo[bindex].SongIndex;  
				bindingRec.items[bindex].song.OrderIndex = tmpsonginfo[bindex].OrderIndex;
				bindingRec.items[bindex].song.FileType = tmpsonginfo[bindex].FileType;
				bindingRec.items[bindex].song.MediaType = tmpsonginfo[bindex].SubFileType;
				strncpy(bindingRec.items[bindex].song.SongName, tmpsonginfo[bindex].SongName, sizeof(bindingRec.items[bindex].song.SongName));

				reqSongExtraInf(bindingRec.items[bindex].song);
			}
			for (; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return retBuffer;
	}
	else
	{
		if(reqCount != -1)
		{
			for (bindex=0; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return 0;
	}
}

//----------------------------------------------------------------------------//
int ReqDB::reqClassicSong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}


//----------------------------------------------------------------------------//
int ReqDB::reqEasySong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqHotSong(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;

	strncpy(strpara, handle.reqCmd.strPara, sizeof(strpara));

	NeedSongInfo_t *tmpsonginfo;
	int bindex;
	int BufferSongType = BUFFER_SONG_TYPE_POP;

	int retBuffer = reqBufferSongList(BufferSongType, reqStart, reqCount, strpara, &tmpsonginfo);
	if(retBuffer != -1)
	{
		if(reqCount == -1)
			return retBuffer;
		else
		{
			for(bindex = 0; bindex<retBuffer; bindex++)
			{
				memset(&bindingRec.items[bindex], 0, sizeof(DBBindingStruct_t));
				bindingRec.items[bindex].song.dataIndex = reqStart + bindex;

				bindingRec.items[bindex].song.SongIndex = tmpsonginfo[bindex].SongIndex;  
				bindingRec.items[bindex].song.OrderIndex = tmpsonginfo[bindex].OrderIndex;
				bindingRec.items[bindex].song.FileType = tmpsonginfo[bindex].FileType;
				bindingRec.items[bindex].song.MediaType = tmpsonginfo[bindex].SubFileType;
				strncpy(bindingRec.items[bindex].song.SongName, tmpsonginfo[bindex].SongName, sizeof(bindingRec.items[bindex].song.SongName));

				reqSongExtraInf(bindingRec.items[bindex].song);
			}
			for (; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return retBuffer;
	}
	else
	{
		if(reqCount != -1)
		{
			for (bindex=0; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return 0;
	}

	if (reqCount == -1) {
		memset(sql_cmd, 0, sizeof(sql_cmd));
		//strcpy(strpara, handle.reqCmd.strPara);
		//strcat(strpara, "%");
		assert(strlen(strpara) < sizeof(handle.reqCmd.strPara));

		//inquire data from db
			if (checkSQLExist(REQDB_SQL_SONG_HOT))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SONG_HOT), strpara, strpara, reqCount, reqStart);

		assert(strlen(sql_cmd) < SQL_STR_SZ);
		
		if (handle.reqResult.Buffer != NULL)
		{
			sqlite3_free_table((char * *)handle.reqResult.Buffer);
			handle.reqResult.Buffer = NULL;
		}

		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
		handle.reqResult.Buffer = azResult;
		handle.reqResult.para1 = ncolumn;
		
		for (j = 0; j < MAX_BINDREC_COUNT; j ++)
		{
			bindingRec.items[j].song = SongListRecDummy;
		}
		return nrow;
	}
	else if (handle.reqResult.Buffer != NULL) {
		
		azResult = (char **)(handle.reqResult.Buffer);
		ncolumn = handle.reqResult.para1;

		reqCount = min(MAX_BINDREC_COUNT-handle.reqCmd.itemIndex, reqCount);
		//memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{ 							
			memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
			bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = i - 1;
			bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = atoi(azResult[i*ncolumn]); 
			bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = atoi(azResult[i*ncolumn + 1]);
			bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = atoi(azResult[i*ncolumn + 2]);
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, azResult[i*ncolumn + 3], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);
			//bindingRec.items[j+handle.reqCmd.itemIndex].song.firstWord = azResult[i*ncolumn + 4][0];
			if(azResult[i*ncolumn + 5] != NULL)
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName, azResult[i*ncolumn + 5], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName)-1);
			else
				sprintf(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName," ");
			bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = atoi(azResult[i*ncolumn + 6]);

			reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);

			ret ++;
		}
		for (; j < reqCount; j ++)
		{
			bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
		}
	}
	else {
		for (j =0; j < reqCount; j ++)
		{
			bindingRec.items[j].song = SongListRecDummy;
		}
		M3D_DebugPrint("Request dataset is NULL\n");
	}
	return ret;
}

//----------------------------------------------------------------------------//
int ReqDB::reqNewSong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqLangugeSongCount(int LanguageType)
{

	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqLanguageSong(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;

	strncpy(strpara, handle.reqCmd.strPara, sizeof(strpara));

	NeedSongInfo_t *tmpsonginfo;
	int bindex;
	int BufferSongType;
	switch(handle.reqCmd.subType)
	{
	case SONG_SUBTYPE_CN:
		BufferSongType = BUFFER_SONG_TYPE_LAN_CN;
		break;
	case SONG_SUBTYPE_EN:
		BufferSongType = BUFFER_SONG_TYPE_LAN_EN;
		break;
	case SONG_SUBTYPE_JP:
		BufferSongType = BUFFER_SONG_TYPE_LAN_JP;
		break;
	case SONG_SUBTYPE_KR:
		BufferSongType = BUFFER_SONG_TYPE_LAN_KR;
		break;
	case SONG_SUBTYPE_VIE:
		BufferSongType = BUFFER_SONG_TYPE_LAN_VIE;
		break;
	case SONG_SUBTYPE_TH:
		BufferSongType = BUFFER_SONG_TYPE_LAN_TH;
		break;
	case SONG_SUBTYPE_RU:
		BufferSongType = BUFFER_SONG_TYPE_LAN_RU;
		break;
	case SONG_SUBTYPE_SP:
		BufferSongType = BUFFER_SONG_TYPE_LAN_SP;
		break;
	case SONG_SUBTYPE_PHI:
		BufferSongType = BUFFER_SONG_TYPE_LAN_PHI;
		break;
	case SONG_SUBTYPE_FR:
		BufferSongType = BUFFER_SONG_TYPE_LAN_FR;
		break;
	case SONG_SUBTYPE_ID:
		BufferSongType = BUFFER_SONG_TYPE_LAN_ID;
		break;
	case SONG_SUBTYPE_IN:
		BufferSongType = BUFFER_SONG_TYPE_LAN_IN;
		break;
	case SONG_SUBTYPE_MY:
	default:
		BufferSongType = BUFFER_SONG_TYPE_LAN_MY;
		break;
	}
	int retBuffer = reqBufferSongList(BufferSongType, reqStart, reqCount, strpara, &tmpsonginfo);
	if(retBuffer != -1)
	{
		if(reqCount == -1)
			return retBuffer;
		else
		{
			for(bindex = 0; bindex<retBuffer; bindex++)
			{
				memset(&bindingRec.items[bindex], 0, sizeof(DBBindingStruct_t));
				bindingRec.items[bindex].song.dataIndex = reqStart + bindex;

				bindingRec.items[bindex].song.SongIndex = tmpsonginfo[bindex].SongIndex;  
				bindingRec.items[bindex].song.OrderIndex = tmpsonginfo[bindex].OrderIndex;
				bindingRec.items[bindex].song.FileType = tmpsonginfo[bindex].FileType;
				bindingRec.items[bindex].song.MediaType = tmpsonginfo[bindex].SubFileType;
				strncpy(bindingRec.items[bindex].song.SongName, tmpsonginfo[bindex].SongName, sizeof(bindingRec.items[bindex].song.SongName));

				reqSongExtraInf(bindingRec.items[bindex].song);
			}
			for (; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return retBuffer;
	}

	if (reqCount == -1) {
	memset(sql_cmd, 0, sizeof(sql_cmd));
	assert(strlen(strpara) < sizeof(handle.reqCmd.strPara));
		
	//inquire data from db
	switch(handle.reqCmd.subType)
	{
	case SONG_SUBTYPE_CN:
		if (checkSQLExist(REQDB_SQL_LAN_CN))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_CN), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_EN:
		if (checkSQLExist(REQDB_SQL_LAN_EN))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_EN), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_JP:
		if (checkSQLExist(REQDB_SQL_LAN_JP))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_JP), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_KR:
		if (checkSQLExist(REQDB_SQL_LAN_KR))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_KR), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_VIE:
		if (checkSQLExist(REQDB_SQL_LAN_VIE))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_VIE), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_TH:
		if (checkSQLExist(REQDB_SQL_LAN_TH))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_TH), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_RU:
		if (checkSQLExist(REQDB_SQL_LAN_RU))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_RU), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_SP:
		if (checkSQLExist(REQDB_SQL_LAN_SP))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_SP), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_PHI:
		if (checkSQLExist(REQDB_SQL_LAN_PHI))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_PHI), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_FR:
		if (checkSQLExist(REQDB_SQL_LAN_FR))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_FR), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_ID:
		if (checkSQLExist(REQDB_SQL_LAN_ID))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_ID), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_IN:
		if (checkSQLExist(REQDB_SQL_LAN_IN))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_IN), strpara, strpara, reqCount, reqStart);
		break;
	case SONG_SUBTYPE_MY:
	default:
		if (checkSQLExist(REQDB_SQL_LAN_MY))
		sprintf(sql_cmd, getSQLString(REQDB_SQL_LAN_MY), strpara, strpara, reqCount, reqStart);
		break;
	}

	    assert(strlen(sql_cmd) < SQL_STR_SZ);
		
		if (handle.reqResult.Buffer != NULL)
	    {
			sqlite3_free_table((char **)handle.reqResult.Buffer);
		    handle.reqResult.Buffer = NULL;
	    }

	    sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
	    if (errMsg != NULL)
		    sqlite3_free(errMsg);

	    handle.reqResult.Buffer = azResult;
	    handle.reqResult.para1 = ncolumn;
	    
	    for (j = 0; j < MAX_BINDREC_COUNT; j ++)
	    {
		    bindingRec.items[j].song = SongListRecDummy;
	    }
		return nrow;
	}
	else if (handle.reqResult.Buffer != NULL) {
		azResult = (char **)(handle.reqResult.Buffer);
		ncolumn = handle.reqResult.para1;

		reqCount = min(MAX_BINDREC_COUNT-handle.reqCmd.itemIndex, reqCount);
		//memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{
			memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
			bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = i - 1;
			bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = atoi(azResult[i*ncolumn]); 
			bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = atoi(azResult[i*ncolumn + 1]);
			bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = atoi(azResult[i*ncolumn + 2]);
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, azResult[i*ncolumn + 3], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);
			//bindingRec.items[j+handle.reqCmd.itemIndex].song.firstWord = azResult[i*ncolumn + 4][0];
			if(azResult[i*ncolumn + 5] != NULL)
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName, azResult[i*ncolumn + 5], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName)-1);
			else
				sprintf(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName," ");
			bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = atoi(azResult[i*ncolumn + 6]);

			reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);

			ret ++;
		}
		for (; j < reqCount; j ++)
		{
			bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
		}
	}
	else {
		M3D_DebugPrint("Request dataset is NULL\n");
	}
	return ret;
}

//----------------------------------------------------------------------------//
int ReqDB::reqDownload(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	char strpara[M3DREQ_STRPARA_LEN+1];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0, j = 0;
	int ret = 0;
	
	strncpy(strpara, handle.reqCmd.strPara, sizeof(strpara));

	NeedSongInfo_t *tmpsonginfo;
	int bindex;
	int BufferSongType;
	switch(handle.reqCmd.subType)
	{
	case REQDB_SUBTYPE_MP3:
		BufferSongType = BUFFER_SONG_TYPE_MP3;
		break;
	case REQDB_SUBTYPE_MTV:
		BufferSongType = BUFFER_SONG_TYPE_MTV;
		break;
	case REQDB_SUBTYPE_MOVIE:
	default:
		BufferSongType = BUFFER_SONG_TYPE_MOVIE;
		break;
	}
	int retBuffer = reqBufferSongList(BufferSongType, reqStart, reqCount, strpara, &tmpsonginfo);
	if(retBuffer != -1)
	{
		if(reqCount == -1)
			return retBuffer;
		else
		{
			for(bindex = 0; bindex<retBuffer; bindex++)
			{
				memset(&bindingRec.items[bindex], 0, sizeof(DBBindingStruct_t));
				bindingRec.items[bindex].song.dataIndex = reqStart + bindex;

				bindingRec.items[bindex].song.SongIndex = tmpsonginfo[bindex].SongIndex;  
				bindingRec.items[bindex].song.OrderIndex = tmpsonginfo[bindex].OrderIndex;
				bindingRec.items[bindex].song.FileType = tmpsonginfo[bindex].FileType;
				bindingRec.items[bindex].song.MediaType = tmpsonginfo[bindex].SubFileType;
				strncpy(bindingRec.items[bindex].song.SongName, tmpsonginfo[bindex].SongName, sizeof(bindingRec.items[bindex].song.SongName));

				reqSongExtraInf(bindingRec.items[bindex].song);
			}
			for (; bindex < reqCount; bindex++)
			{
				bindingRec.items[bindex].song = SongListRecDummy;
			}
		}
		return retBuffer;
	}

	if (reqCount == -1) {
		memset(sql_cmd, 0, sizeof(sql_cmd));
		//strcat(strpara, "%");
		assert(strlen(strpara) < sizeof(handle.reqCmd.strPara));
		
		//inquire data from db
		switch(handle.reqCmd.subType)
		{
		case REQDB_SUBTYPE_MP3:
			if (checkSQLExist(REQDB_SQL_MP3))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_MP3), strpara, strpara, reqCount, reqStart);
			break;
		case REQDB_SUBTYPE_MTV:
			if (checkSQLExist(REQDB_SQL_MTV))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_MTV), strpara, strpara, reqCount, reqStart);
			break;
		case REQDB_SUBTYPE_MOVIE:
		default:
			if (checkSQLExist(REQDB_SQL_MOVIE))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_MOVIE), strpara, strpara, reqCount, reqStart);
			break;
		}
		M3D_DebugPrint("(download) sql_cmd[%s]\n",sql_cmd);

		assert(strlen(sql_cmd) < SQL_STR_SZ);
		
		if (handle.reqResult.Buffer != NULL)
		{
			sqlite3_free_table((char * *)handle.reqResult.Buffer);
			handle.reqResult.Buffer = NULL;
		}

		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
		handle.reqResult.Buffer = azResult;
		handle.reqResult.para1 = ncolumn;

		for (j = 0; j < MAX_BINDREC_COUNT; j ++)
		{
			bindingRec.items[j].song = SongListRecDummy;
		}
		M3D_DebugPrint("---download--- handle.reqCmd.subType[%d], nrow[%d]\n", handle.reqCmd.subType, nrow);
		return nrow;
	}
	else if (handle.reqResult.Buffer != NULL) {

		azResult = (char **)(handle.reqResult.Buffer);
		ncolumn = handle.reqResult.para1;

		reqCount = min(MAX_BINDREC_COUNT-handle.reqCmd.itemIndex, reqCount);
		//memset(bindingRec.items, 0, reqCount*sizeof(DBBindingStruct_t));
		for(i = reqStart+1, j = 0; i < handle.totalItems+ 1 && j < reqCount; i ++, j ++)
		{ 			
			memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
			bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = i - 1;
			bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = atoi(azResult[i*ncolumn]); 
			bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = atoi(azResult[i*ncolumn + 1]);
			bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = atoi(azResult[i*ncolumn + 2]);
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, azResult[i*ncolumn + 3], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);
			//bindingRec.items[j+handle.reqCmd.itemIndex].song.firstWord = azResult[i*ncolumn + 4][0];
			if(azResult[i*ncolumn + 5] != NULL)
			strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName, azResult[i*ncolumn + 5], sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName)-1);
			else
				sprintf(bindingRec.items[j+handle.reqCmd.itemIndex].song.SingerName," ");
			bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = atoi(azResult[i*ncolumn + 6]);

			reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);

			ret ++;
		}
		for (; j < reqCount; j ++)
		{
			bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
		}
	}
	else {
		M3D_DebugPrint("Request dataset is NULL\n");
	}
	return ret;
}


//----------------------------------------------------------------------------//
int ReqDB::reqMySong(int reqStart, int reqCount)
{
	if(reqCount == -1)
		return 0;
	
	for (int i = 0; i < reqCount; i ++)
	{
		bindingRec.items[i].song = SongListRecDummy;
	}
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqSingerType(int reqStart, int reqCount)
{
	if(reqCount == -1)
		return 0;

	for (int i = 0; i < reqCount; i ++)
	{
		bindingRec.items[i].song = SongListRecDummy;
	}
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqLanguage(int reqStart, int reqCount)
{
	if(reqCount == -1)
		return 0;

	for (int i = 0; i < reqCount; i ++)
	{
		bindingRec.items[i].song = SongListRecDummy;
	}
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqNumSong(int reqStart, int reqCount)
{
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
	
	if (handle.reqCmd.ssType > 0)
	{
		memset(sql_cmd, 0, sizeof(sql_cmd));
		
		//inquire data from db
		if (d_ForeignFlag == SONG_SUBTYPE_FOREIGN_ON)
		{
			if (checkSQLExist(REQDB_SQL_BOOK))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_BOOK), d_PrivacyFlag, handle.reqCmd.ssType);
		}
		else
		{
			if (checkSQLExist(REQDB_SQL_BOOK_NO_FOREIGN))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_BOOK_NO_FOREIGN), d_PrivacyFlag, handle.reqCmd.ssType, FOREIFN_FLAG);
}

		assert(strlen(sql_cmd) < SQL_STR_SZ);
		
		if (handle.reqResult.Buffer != NULL)
		{
			sqlite3_free_table((char * *)handle.reqResult.Buffer);
			handle.reqResult.Buffer = NULL;
		}

		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
		handle.reqResult.Buffer = azResult;
		bindingRec.items[0].song = SongListRecDummy;

		//get song info
		if (nrow > 0)
		{
			bindingRec.items[0].song.OrderIndex = handle.reqCmd.ssType;
			bindingRec.items[0].song.SongIndex = atoi(azResult[ncolumn]); 
			bindingRec.items[0].song.FileType = atoi(azResult[ncolumn + 1]);
			strncpy(bindingRec.items[0].song.SongName, azResult[ncolumn + 2], sizeof(bindingRec.items[0].song.SongName)-1);
			bindingRec.items[0].song.MediaType = atoi(azResult[ncolumn + 3]);

			reqSongExtraInf(bindingRec.items[0].song);
		}
	}
	else {
		bindingRec.items[0].song = SongListRecDummy;
		M3D_DebugPrint("OrderIndex is none!\n");
	}
	return nrow;
}


//----------------------------------------------------------------------------//
int ReqDB::reqMyHotSong(int reqStart, int reqCount)
{
	return 0;
}


//----------------------------------------------------------------------------//
int ReqDB::reqRecordSong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqFavorSong(int reqStart, int reqCount)
{
	return 0;
}


//----------------------------------------------------------------------------//
int ReqDB::reqMp3Song(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqReservedSong(int reqStart, int reqCount)
{
	return reqMySong(reqStart, reqCount);
}

//----------------------------------------------------------------------------//
int ReqDB::reqShareSong(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqWebNewSong(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqWebHotSong(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqWebCompetitionSong(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqCustomItems(int reqStart, int reqCount)
{
	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqResetSongAllExist(void)
{
	char sql_cmd[SQL_STR_SZ];

	sprintf(sql_cmd, "update SongTab set tvExistFlag=1\0");
	sqlite3_exec(d_db, sql_cmd, NULL, NULL, NULL);

	return 1;
}

//----------------------------------------------------------------------------//
int ReqDB::reqResetSingerAllExist(void)
{
	char sql_cmd[SQL_STR_SZ];

	sprintf(sql_cmd, "update SingerTab set songTotal=1\0");
	sqlite3_exec(d_db, sql_cmd, NULL, NULL, NULL);

	return 1;
}
//----------------------------------------------------------------------------//
int ReqDB::reqResetSingerSongTotal(void)
{
	char sql_cmd[SQL_STR_SZ];
	int nrowSingerNum = 0;
	int nrowSongCount = 0;
	int nrow = 0, ncolumn = 0;
	char **azResultSingerNum; //save inquire result from db	
	char **azResultSongCount; //save inquire result from db	
	char * errMsg = NULL;
	int i = 0;
	int ret = 0;
	

	//get singer num
	memset(sql_cmd, 0, sizeof(sql_cmd));
	sprintf(sql_cmd, "SELECT singerNum FROM SingerTab\0");
	sqlite3_get_table(d_db, sql_cmd, &azResultSingerNum, &nrowSingerNum, &ncolumn, &errMsg);
	if (errMsg != NULL)
		sqlite3_free(errMsg);

	//get songTotal by singer num
	for( i = 1; i < nrowSingerNum+1; i++)
	{
		memset(sql_cmd, 0, sizeof(sql_cmd));
		sprintf(sql_cmd, "SELECT songId FROM SongTab WHERE singerNum = %d AND tvExistFlag=1\0", atoi(azResultSingerNum[i*ncolumn]));
		sqlite3_get_table(d_db, sql_cmd, &azResultSongCount, &nrowSongCount, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);

		
		memset(sql_cmd, 0, sizeof(sql_cmd));
		sprintf(sql_cmd, "update SingerTab set songTotal=%d where singerNum=%d", nrowSongCount, atoi(azResultSingerNum[i*ncolumn]));
		sqlite3_exec(d_db, sql_cmd, NULL, NULL, NULL);

		sqlite3_free_table(azResultSongCount);
	}

	sqlite3_free_table(azResultSingerNum);
	return 1;
}


//----------------------------------------------------------------------------//
int ReqDB::reqSyncLocalDB(char* filePath)
{
#ifndef USE_LIST_BUFFER_FOR_SOME_LIST
	freePINYINCount();
	freeABCcount();
#endif
	reqDeInitSongInf();
	
	reqInitSongInf();
#ifndef USE_LIST_BUFFER_FOR_SOME_LIST
	loadABCcount();
	loadPINYINCount();
#endif
	//run only once
	//reqResetSingerSongTotal();
	M3D_DebugPrint("ReqDB::reqSyncLocalDB\n");

	return 0;
}

//----------------------------------------------------------------------------//
int ReqDB::reqInitSongInf(void)
{
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;

	memset(sql_cmd, 0, sizeof(sql_cmd));
	
	if (checkSQLExist(REQDB_SQL_SONGCOUNT))
		sprintf(sql_cmd, "%s", getSQLString(REQDB_SQL_SONGCOUNT));
	sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

	if (nrow)
		result_nrow = atoi(azResult[ncolumn]);
	
	if (errMsg != NULL)
		sqlite3_free(errMsg);

	sqlite3_free_table(azResult);
	
#ifdef A_BUFFER_FOR_NORMAL_LIST
	d_pbNormalBuffer = new ReqDBSongInf_t[result_nrow];
#endif
	return nrow;
}

//----------------------------------------------------------------------------//
int ReqDB::reqSongTotal(bool firstFlag) //0: again; 1: over; 2: do nothing;
{
	return 0;
}

//----------------------------------------------------------------------------//
void ReqDB::reqDeInitSongInf(void)
{
#ifdef A_BUFFER_FOR_NORMAL_LIST
	if(d_pbNormalBuffer != NULL)
	{
		delete [] d_pbNormalBuffer;
		d_pbNormalBuffer = NULL;
	}
#endif
	if (result_buf != NULL)
	{
		sqlite3_free_table(result_buf);
		result_buf = NULL;
	}
}

//----------------------------------------------------------------------------//
int ReqDB::reqDbSongInf(unsigned int songNo, ReqDBSongInf_t* output)
{
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;

	memset(output, 0, sizeof(ReqDBSongInf_t));
	memset(sql_cmd, 0, sizeof(sql_cmd));
	
	if (result_buf != NULL)
	{
		if(atoi(result_buf[result_ncolumn]) == songNo)
		{
			azResult = result_buf;
			ncolumn = result_ncolumn;
			nrow = 1;
		}
		else
		{
			sqlite3_free_table(result_buf);
			result_buf = NULL;
			
			if (checkSQLExist(REQDB_SQL_SONGINF))
				sprintf(sql_cmd, getSQLString(REQDB_SQL_SONGINF), songNo);
			sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
			if (errMsg != NULL)
				sqlite3_free(errMsg);
		}
	}
	else
	{
		if (checkSQLExist(REQDB_SQL_SONGINF))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SONGINF),songNo);
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
		if (errMsg != NULL)
			sqlite3_free(errMsg);
	}

	if (nrow)
	{
		result_buf = azResult;
		result_ncolumn = ncolumn;

		output->SongIndex = atoi(azResult[ncolumn]); 
		output->OrderIndex = atoi(azResult[ncolumn + 1]);
		output->FileType = atoi(azResult[ncolumn + 2]);
		strncpy(output->SongName, azResult[ncolumn + 3], sizeof(output->SongName)-1);
		strncpy(output->FirstWord, azResult[ncolumn + 4], sizeof(output->FirstWord)-1);
		if(azResult[ncolumn + 5] == NULL)
		{
			M3D_DebugPrint("SingerName == NULL \n");
			sprintf(output->SingerName," ");
		}
		else
			
		strncpy(output->SingerName, azResult[ncolumn + 5], sizeof(output->SingerName)-1);
		output->SubFileType = atoi(azResult[ncolumn + 6]);
	}
	
	if (errMsg != NULL)
		sqlite3_free(errMsg);
	
	return nrow;
}

//----------------------------------------------------------------------------//
int ReqDB::reqDbSongIndexByIndex(unsigned int index)
{
	int songIndex = -1;
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
		
	if(index <= (unsigned int)result_nrow)
	{
		memset(sql_cmd, 0, sizeof(sql_cmd));
		if (checkSQLExist(REQDB_SQL_SONGINF_BY_INDEX))
			sprintf(sql_cmd, getSQLString(REQDB_SQL_SONGINF_BY_INDEX),index);
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
	
		songIndex = atoi(azResult[ncolumn*nrow]);
		sqlite3_free_table(azResult);
}

	return songIndex;
	}
	

int ReqDB::reqDbSongindexByOrder(unsigned int index)
{
	int songIndex = -1;
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
		
	if(index <= (unsigned int)result_nrow)
	{
		memset(sql_cmd, 0, sizeof(sql_cmd));
		
		sprintf(sql_cmd, "SELECT SongIndex FROM TableSong ORDER BY OrderIndex LIMIT %d", index);
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

		songIndex = atoi(azResult[ncolumn*nrow]);
		sqlite3_free_table(azResult);
	}
	
	return songIndex;


}


int ReqDB::reqDbSongindexByOrderIndex(unsigned int OrderIndex)
{
	int songIndex = -1;
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
		
	
		memset(sql_cmd, 0, sizeof(sql_cmd));
		
		sprintf(sql_cmd, "SELECT SongIndex FROM TableSong where OrderIndex = %d", OrderIndex);
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

		songIndex = atoi(azResult[ncolumn*nrow]);
		sqlite3_free_table(azResult);

	
	return songIndex;


}

int ReqDB::reqDbOrderindexBySongIndex(unsigned int SongIndex)
{
	int orderindex = -1;
	char sql_cmd[SQL_STR_SZ];
	int nrow = 0, ncolumn = 0;
	char **azResult; //save inquire result from db	
	char * errMsg = NULL;
		
	
		memset(sql_cmd, 0, sizeof(sql_cmd));
		
		sprintf(sql_cmd, "SELECT Orderindex FROM TableSong where SongIndex = %d", SongIndex);
		sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

		orderindex = atoi(azResult[ncolumn*nrow]);
		sqlite3_free_table(azResult);

	
	return orderindex;


}


}


