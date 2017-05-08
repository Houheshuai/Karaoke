#ifndef _REQMICEDB_H
#define _REQMICEDB_H

#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include "InterfaceDataBaseManager.h"
#include "ResultLanParam.h"
#include "SongParam.h"
//#include "RecSongParam.h"

extern "C"
{
#include "../krklib/include/lib/edb/edb.h"
}

#ifdef _WIN32
extern void DebugMsg2(char* szMessage, ...);
#define EDB_DebugPrint 			DebugMsg2
#else
#ifdef RELEASE_VERSION
#define EDB_DebugPrint(...)
#else
#include <android/log.h>
#undef  EDB_DebugPrint
#define EDB_DebugPrint(...) __android_log_print(ANDROID_LOG_INFO, "MICEDB", __VA_ARGS__)
#endif
#endif

#define SONG_EDB_NAME "vod.edb"

#define DEFAULT_BASICDB_FILES    2
//favo_db
#define FAVO_EDB_NAME "favo.edb"
#define FAVO_TABLE_NAME "TableFavo.tbl"
//prog_db
#define PROG_EDB_NAME "prog.edb"
#define PROG_TABLE_NAME "TableProg.tbl"
//rec_db
#define REC_EDB_NAME "record.edb"
#define REC_TABLE_NAME "TableRecord.tbl"


#define EDB_FILECOPY_BUFSZ  (1024*1024)
#define DEFAULT_MAX_RECSONG_COUNT	100

/*
*	record info
*/

//typedef struct
//{
//	int				songIndex;					/*book song number*/
//	int				recIndex;					/* record song id */
//	int				score;							/* singer score */
//	int				storage;						/* 0-not in default storage device, 1-in default storage device */
//} RecSongInfo_t;

//using namespace std;
class ReqMICEDB:public InterfaceDataBaseManager
{
	public:
		static ReqMICEDB *GetSingleInstance() 
	    { 
	        if (p_instance_ == nullptr) { 
	            static ReqMICEDB instance; 
	            p_instance_ = &instance; 
	        }
	        return p_instance_; 
	    } 
		
		void setProgramSave(bool progsave);
		int setDataBasePath(const std::string& dirPath);		
		std::string reqTableVersion(void);
		int reqCustomerNo(void);
		
		int reqLanguageList(void);
		int reqLanTypeByResultPos(int position);
		std::string reqLanNameEGByLanType(int lantype);
		
		std::string reqCountryNameByLanType(int lantype);
		int reqLanSongQuantity(int lantype);
		int reqLanSongQuantity(TABLE_HANDLE* table);
		int reqLanSongList(int lantype,std::string inputstr="");
		
		TABLE_HANDLE* reqTableByLanguage(int lantype,std::string inputstr="");
		int reqSongIndexByTablePos(TABLE_HANDLE* table,int position);
		std::string reqSongNameBySongIndex(int songindex);
		int reqFileTypeBySongIndex(int songindex);
		
		int reqSubTypeBySongIndex(int songindex);
		
		char reqFirstWordBySongIndex(int songindex);
		//int reqSongParamBySongIndex(SongParam* songInfo);
		int reqSingerIndexBySongIndex(int songindex);
		std::string reqSingerNameBySingerIndex(int singerindex,bool Enflag=true);
				
		int reqSingerLanTypeByResultPos(int position);
		int reqSingerQuantityByLanType(int lantype);
		int reqSingerLanguageList(void);
		
		//*********************************************************
		
		TABLE_HANDLE* reqSingerListInLanguage(int lantype,std::string inputstr="");		
		int reqSingerQuantityInLanguage(TABLE_HANDLE* table);
		int reqSingerIndexByResultPos(int position);
		char reqSingerFirstWordBySingerIndex(int singerindex);
		char reqSingerFirstWordBySongIndex(int songindex);
		int reqSingerSongQuantity(int singerindex);
		int reqSingerSongQuantity(TABLE_HANDLE* table);
		int reqSingerSongList(int singeridx,std::string inputstr="");
		TABLE_HANDLE* reqSingerSongTableBySingerIndex(int singerindex,std::string inputstr="");

		int reqFavoSongQuantity(void);
		int reqFavoSongList(void);
		bool isFavoSong(int songIndex);
		int reqFavoSongIndexByResultPos(int position);
		int reqAddFavoSong(int songIndex);
		int reqDeleteFavoSong(int songIndex);
		int reqDeleteAllFavoSongs(void);

		int reqProgSongList(void);
		bool isProgSong(int songIndex);
		int reqProgSongQuantity(void);
		
		int reqProgSongIndexByResultPos(int position);
		/*
			topfg: true 添加喜爱歌曲的同时，将歌曲置顶
			
			topfg: default value false
		*/
		int reqAddProgSong(int songIndex,bool topfg=false);
		
		/*
			addfg: true	 支持同一首歌曲可多次选为预约歌曲
			
			addfg: default value false
		*/
		int reqSetTopProgSong(int songIndex,bool addfg=false);
		int reqAddTopProgSongByResultPos(int position);
		
		int reqDeleteProgSong(int songIndex);
		int reqDeleteProgSongByResultPos(int position);
		int reqDeleteAllProgSongs(void);

		//input string search   暂不使用
		TABLE_HANDLE* reqTableByFullSpell(TABLE_HANDLE* table,std::string inputstr);

		//search
		TABLE_HANDLE* reqSearchSongNoTable(int inputnum = 0);
		int reqSearchSongNoQuantity(TABLE_HANDLE* table);
		
		TABLE_HANDLE* reqSearchSingerSongTableByLanguage(int lantype,std::string inputstr="");
		
		int reqSearchSingerSongQuantity(TABLE_HANDLE* table);
		
		//record
		int reqRecSongList(void);
		int reqRecSongQuantity(void);
		int reqNextRecIndex(int songindex);
		int reqAddRecSong(RecSongParam* recsong);
		int reqDeleteRecSongByResultPos(int position);
		RecSongParam* reqRecSongParamByResultPos(int position);
		int reqRecSongIndexByResultPos(int position);
		int reqRecScoreByResultPos(int position);
		int reqRecIndexByResultPos(int position);
		int reqDeleteAllRecSongs(void);
		
		int reqAllSongList(void);
		int reqPlayListSongByPosition(int position);

		//Hindi Sub Type
		
		int reqHindiSubTypes(void);
	 	std::string reqHindiSubTypeByResultPos(int position);
		
		int reqSongQuantityByHindiSubTypeName(std::string subtypename);		
		TABLE_HANDLE* reqTableByHindiSubTypeName(std::string subtypename,std::string inputstr="");
			
		int reqHindiSubTypeSongQuantity(TABLE_HANDLE* table);
		//Album
		
		//*********************************************************
		int reqAlbumIndexBySongIndex(int songindex);
		std::string reqAlbumNameByAlbumIndex(int albumindex,bool Enflag=true);
				
		int reqAlbumLanTypeByResultPos(int position);
		int reqAlbumQuantityByLanType(int lantype);
		int reqAlbumLanguageList(void);
		

		TABLE_HANDLE* reqAlbumListInLanguage(int lantype,std::string inputstr="");		
		int reqAlbumQuantityInLanguage(TABLE_HANDLE* table);
		int reqAlbumIndexByResultPos(int position);
		char reqAlbumFirstWordByAlbumIndex(int albumindex);
		char reqAlbumFirstWordBySongIndex(int songindex);
		int reqAlbumSongQuantity(int albumindex);
		int reqAlbumSongQuantity(TABLE_HANDLE* table);
		int reqAlbumSongList(int albumindex,std::string inputstr="");
		TABLE_HANDLE* reqAlbumSongTableByAlbumIndex(int albumindex,std::string inputstr="");
	private:
		ReqMICEDB();

        ~ReqMICEDB();

		int EDBOpen(void);
		int EDBClose(void);
		
		
		int setIntFilter(FILTER_PARAM *filter,int intPara1,int intPara2,int size);
		
		void setStrFilter(FILTER_PARAM *Filter, char* strPara, int crt);
		
		int getVersionInfo(TABLE_HANDLE* table);
		
		void resetAllLanguageInfo();
		int getAllLanguageInfo(TABLE_HANDLE* lantable);
		
		int getTableRecNum(std::string& tablename);
		
		TABLE_HANDLE* getTableByFilter(TABLE_HANDLE* table,FILTER_PARAM *Filter);
		TABLE_HANDLE* getTableByFilter(std::string& tablename,FILTER_PARAM *Filter);
		int getSongParamBySongIndex(int songidx,SongParam* songparam);
		
		int getFavoInsertIDBySongIndex(int songIndex);
		int getProgInsertIDByResultPos(int position);
		int getProgPositionBySongIndex(int songindex);
		int deleteProgSongFormList(int position);
		int deleteProgInsertIdFormList(int position);
		int loadPlayModeList(TABLE_HANDLE* table);

		static ReqMICEDB *p_instance_;
		DB_HANDLE* m_HandleMICEDB;
		DB_HANDLE* m_HandleFavoEDB;
		DB_HANDLE* m_HandleProgEDB;
		DB_HANDLE* m_HandleRecEDB;
		
		bool m_ProgSave;
		TABLE_HANDLE* m_TableLan;
		std::string m_EdbDirPath;
		std::string m_SongEDBPath;
		std::string m_FavoEDBPath;
		std::string m_ProgEDBPath;
		std::string m_RecEDBPath;
		SongParam* m_SongInfo;
		
		std::string m_TableVession;
		int m_CustomerNo;
		std::vector<int> m_AllLanTypes;
		std::unordered_map<int,std::string> m_AllLanEGName_Map;   // LanType <-->LanName_EG
		std::unordered_map<int,std::string> m_AllCountryName_Map;
		std::vector<int> m_ResultSongLanList;
		std::vector<int> m_ResultSingerLanList;
		std::vector<int> m_ResultSingerList;
		//favo
		std::list<int> m_ResultFavoSongList;
		//prog
		std::list<int> m_ResultProgSongList;    // 记录预约歌曲歌号
		std::list<int> m_ProgSongInsertList;    // 记录预约歌曲序号
		//record
		std::list<RecSongParam> m_ResultRecSongList;
		RecSongParam* m_RecSongInfo;
		//play mode list
		std::list<int> m_PlayModeList;

		//hindi sub type
		std::vector<std::string> m_HindiSubTypes;

		//Album
		std::vector<int> m_ResultAlbumLanList;
		std::vector<int> m_ResultAlbumList;
		
};
#endif
