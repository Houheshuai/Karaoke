#include <algorithm>
#include <iterator>
#include "ReqMICEDB.h"
#include "ReqTableName.h"

#include "appPathManager.h"
//#include "LanguageTableParam.h"

ReqMICEDB *ReqMICEDB::p_instance_ = nullptr;
const std::string pathSeparator[2] = {"/","//"};

std::string FavoDBFiles[DEFAULT_BASICDB_FILES] = {FAVO_EDB_NAME,FAVO_TABLE_NAME};
std::string ProgDBFiles[DEFAULT_BASICDB_FILES] = {PROG_EDB_NAME,PROG_TABLE_NAME};
std::string RecDBFiles[DEFAULT_BASICDB_FILES] = {REC_EDB_NAME,REC_TABLE_NAME};

ReqMICEDB::ReqMICEDB()
{
	m_EdbDirPath = "";
	m_SongEDBPath = "";
	m_FavoEDBPath = "";
	m_ProgEDBPath = "";
	m_RecEDBPath = "";
	
	m_HandleMICEDB = NULL;
	m_HandleFavoEDB = NULL;
	m_HandleProgEDB = NULL;
	m_HandleRecEDB = NULL;
	
	m_ProgSave = false;
	m_TableLan = nullptr;
	
	m_TableVession = "illegal";
	m_CustomerNo = -1;
	
	m_AllLanTypes.clear();
	
	m_AllLanEGName_Map.clear();
	m_AllCountryName_Map.clear();
	m_ResultSongLanList.clear();
	m_ResultSingerLanList.clear();
	m_ResultSingerList.clear();
	
	m_ResultFavoSongList.clear();
	m_ResultProgSongList.clear();
	m_ProgSongInsertList.clear();
	m_ResultRecSongList.clear();

	m_SongInfo = new SongParam();
	//m_RecSongInfo = new RecSongParam();
	m_RecSongInfo = nullptr;

	m_PlayModeList.clear();

	//hindi sub type 
	m_HindiSubTypes.clear();

	//Album
	m_ResultAlbumLanList.clear();
	m_ResultAlbumList.clear();
	
	DBInit(256,128);

}
ReqMICEDB::~ReqMICEDB()
{
	delete m_SongInfo;
	//delete m_RecSongInfo;
	
	EDBClose();
}
int ReqMICEDB::EDBOpen(void)
{
	std::string tablename = "";
	m_HandleMICEDB = DBOpen((DB_UINT8 *)(m_SongEDBPath.c_str()),DB_READ_ONLY);
	if (m_HandleMICEDB != NULL)
	{
		TABLE_HANDLE* table;

		//Vession table
		table = TableOpen(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::TableVession.c_str()),DB_READ_ONLY);
		if (table != NULL)
			getVersionInfo(table);
		
		//language table
		table = TableOpen(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::TableLanguage.c_str()),DB_READ_ONLY);
		if (table != NULL)
			int lannum = getAllLanguageInfo(table);
		
		for (int i=0;i<ReqTableName::SubTableCnt;i++)
		{
			TableOpen(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::SubTableName[i].c_str()),DB_READ_ONLY);
		}
		
		for (int i=0; i<m_AllLanEGName_Map.size();i++)
		{
			int lantype = m_AllLanTypes[i];
			//English.tbl
			tablename = m_AllLanEGName_Map[lantype];
			TableOpen(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()),DB_READ_ONLY);
			//SingerEngland.tbl
			tablename = ReqTableName::SingerTbl_BasicName + reqCountryNameByLanType(lantype);
			TableOpen(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()),DB_READ_ONLY);	 
			//SearchEngland.tbl
			tablename = ReqTableName::SearchSingerTbl_BasicName + reqCountryNameByLanType(lantype);
			TableOpen(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()),DB_READ_ONLY);	 
			if (m_CustomerNo == 1){
				//AlbumEngland.tbl
				tablename = ReqTableName::AlbumTbl_BasicName + reqCountryNameByLanType(lantype);   //just for Persang
				TableOpen(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()),DB_READ_ONLY);	
			}
		}
		if (m_CustomerNo == 1){
			//Album
			TableOpen(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::SubTbl_SongToAlbum.c_str()),DB_READ_ONLY);

			//Persang db need init m_HindiSubType
			for (int i = 0;i<MAX_HINDI_SUBTYPE_NUM;i++){
				std::string tmpstr = ReqTableName::HindiSubTypes[i];
				int namelen = tmpstr.length();
				std::string subtypename = tmpstr.substr(0,namelen-2);
				m_HindiSubTypes.push_back(subtypename);
				tablename = ReqTableName::HindiSubTypeTbl_BasicName + subtypename;
				TableOpen(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()),DB_READ_ONLY);	 
			}
		}
		//favo table
		reqFavoSongList();
		
		if (m_ProgSave)
			reqProgSongList();
		
		// record table
		reqRecSongList();
#if 0
		// Demo for req info by Filter
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB, (DB_UINT8*)(ReqTableName::TableLanguage.c_str())); 
		int tablelannum = table->TableHead->RecNum;
		TableFilterReset(table);
		char V1[20],V2[20];
		memset(V1,0,20);
		memset(V2,0,20);
		V1[0]='E';
		V1[1]='N';
		V2[0]='E';
		V2[1]='N';
		V2[2]=-1;
		
		DB_UINT8 ret = TableFilter(m_HandleMICEDB, table, (DB_UINT8 *)"LanName_EG", (DB_UINT8*)V1, (DB_UINT8*)V2);
		//DB_UINT8 ret = TableFilter(m_HandleMICEDB, table, (DB_UINT8 *)"LanType", (DB_UINT8*)("4"), (DB_UINT8*)("4"));
		int filternum = table->Filter.RecNum;
		int startrec = table->Filter.StartRec;
		if ((filternum > 0) && (startrec < tablelannum))
		{
			for (int i=0; i<filternum; i++)
			{
				table->Cursor = startrec+i;
				unsigned char lantype;
				KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)"LanType",(DB_UINT8*)&(lantype), GET_KEY_VALUE_MODE_INT);
				lantype = lantype;
			}
		}
#endif
		return 0;
	}
	return -1;
}
int ReqMICEDB::EDBClose(void)
{
	if (m_HandleMICEDB != NULL){
		resetAllLanguageInfo();
		DBClose(m_HandleMICEDB);
		m_HandleMICEDB = NULL;
	}
	if (m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	if (m_HandleProgEDB != NULL){
		DBClose(m_HandleProgEDB);
		m_HandleProgEDB = NULL;
	}
	return 0;
}
void ReqMICEDB::setProgramSave(bool progsave)
{
	m_ProgSave = progsave;
	return;
}
int ReqMICEDB::setDataBasePath(const std::string& pathkey)
{
	int ret = 0;
	std::string tmpdirpath = "";
	std::string tmpfilepath = "";
    appPathManager* pathHandle;

	GetAppPathManager(pathHandle);
	
	if (!pathkey.empty()){	
		tmpdirpath = pathHandle->getDefaultFolderPath(pathkey,APP_CUR_DB_FOLDER);
		if (krk_direxist(tmpdirpath.c_str())){
			if ((!m_EdbDirPath.empty()) && (tmpdirpath.compare(m_EdbDirPath)!= 0))
				ret += EDBClose();
			tmpfilepath = tmpdirpath + SONG_EDB_NAME;
			if (krk_fexist(tmpfilepath.c_str())){
				m_EdbDirPath = tmpdirpath;
				m_SongEDBPath = m_EdbDirPath+SONG_EDB_NAME;

				//favo db
				//std::string favdir = pathHandle->getDefaultFolderPath(pathkey,APP_CUR_FAV_FOLDER);
				//m_FavoEDBPath = favdir+FAVO_EDB_NAME;
				m_FavoEDBPath = m_EdbDirPath+FAVO_EDB_NAME;
				if (!krk_fexist(m_FavoEDBPath.c_str())){
					std::string dbpath = pathHandle->getDefaultFolderPath(AppDataPath,APP_CUR_DB_FOLDER);
					if (krk_direxist(dbpath.c_str())){
						for(int i=0;i<DEFAULT_BASICDB_FILES;i++){
							std::string srcfile = dbpath+FavoDBFiles[i];
							std::string destfile = m_EdbDirPath+FavoDBFiles[i];
							if (krk_fexist(srcfile.c_str()))
								krk_fcopy(destfile.c_str(),srcfile.c_str(),EDB_FILECOPY_BUFSZ,NULL);
						}
					}
				}
				//record db
				m_RecEDBPath = m_EdbDirPath+REC_EDB_NAME;
				if (!krk_fexist(m_RecEDBPath.c_str())){
					std::string dbpath = pathHandle->getDefaultFolderPath(AppDataPath,APP_CUR_DB_FOLDER);
					if (krk_direxist(dbpath.c_str())){
						for(int i=0;i<DEFAULT_BASICDB_FILES;i++){
							std::string srcfile = dbpath+RecDBFiles[i];
							std::string destfile = m_EdbDirPath+RecDBFiles[i];
							if (krk_fexist(srcfile.c_str()))
								krk_fcopy(destfile.c_str(),srcfile.c_str(),EDB_FILECOPY_BUFSZ,NULL);
						}
					}
				}
				//prog db
				if (m_ProgSave)    // �ݲ����� m_ProgSave==true�����
					m_ProgEDBPath = pathHandle->getDefaultFolderPath(pathkey,APP_CUR_PROG_FOLDER)+PROG_EDB_NAME;
					
				ret += EDBOpen();
			}
			
		}else{
			ret = EDBClose();
			m_EdbDirPath = "";
			m_SongEDBPath = "";
			m_FavoEDBPath = "";
			m_ProgEDBPath = "";
		}
		

	}else{
		ret = EDBClose();
		m_EdbDirPath = "";
		m_SongEDBPath = "";
		m_FavoEDBPath = "";
		m_ProgEDBPath = "";
	}
	return ret;
}
/*
void ReqMICEDB::setPrePageSize(int pagesize)
{
	m_prePageSize = pagesize;
	return;
}
*/
std::string ReqMICEDB::reqTableVersion(void)
{
	return m_TableVession;
}
int ReqMICEDB::reqCustomerNo(void)
{
	return m_CustomerNo;
}
int ReqMICEDB::reqLanguageList(void)
{
	int ret = 0;
	int totalLanNum = m_AllLanTypes.size();

	if (!m_ResultSongLanList.empty())
		m_ResultSongLanList.clear();
	
	if (totalLanNum > 0){
		for (int i=0; i<totalLanNum; i++){
			int lantype = m_AllLanTypes[i];
			int songnum = getTableRecNum( m_AllLanEGName_Map[lantype]);
			if (songnum > 0)
			{
				m_ResultSongLanList.push_back(lantype);
			}
		}
		ret = m_ResultSongLanList.size();
	}
		    
	return ret; 
}

int ReqMICEDB::reqLanTypeByResultPos(int position)
{
	int lantype = 0;
	if (position < m_ResultSongLanList.size()){
		lantype = m_ResultSongLanList[position];
	}	
	return lantype;
}

std::string ReqMICEDB::reqLanNameEGByLanType(int lantype)
{
	std::string lanname = "";
	auto got = m_AllLanEGName_Map.find(lantype);
	if (got != m_AllLanEGName_Map.end())
	{
		lanname = m_AllLanEGName_Map[lantype];
	}
	return lanname;
}
std::string ReqMICEDB::reqCountryNameByLanType(int lantype)
{
	std::string coutryname = "";
	#if 1
	auto got = m_AllCountryName_Map.find(lantype);
	if (got != m_AllCountryName_Map.end())
	{
		coutryname = m_AllCountryName_Map[lantype];
	}
	#else
	TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8 *)(ReqTableName::TableLanguage).c_str());
	FILTER_PARAM filter;
	
	memset((char *)&filter,0,sizeof(filter));
	strcpy((char *)filter.KeyName,(ReqTableName::KEY_LANGUAGE_TYPE).c_str());
	filter.Reset = 1;
	filter.SelMod = FILTER_MODE_EQUAL;
	setIntFilter(&filter,lantype,lantype,KeyGetLenByName(table,(DB_UINT8*)(ReqTableName::KEY_LANGUAGE_TYPE).c_str()));

	table = getTableByFilter(ReqTableName::TableLanguage,&filter);
	if ((table != NULL) && (table->Filter.RecNum > 0))
	{	
		char keystr[DB_MAX_NAME_LEN];
		int ret = KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_LANGUAGE_COUNTRY_NAME).c_str()),
				(DB_UINT8 *)keystr,GET_KEY_VALUE_MODE_STR);
		if (ERR_NONE == ret)
			coutryname = std::string(keystr);
	}
	#endif
	return coutryname;
}

int ReqMICEDB::reqLanSongQuantity(int lantype)
{
	int songnum = 0;
	std::string tablename = m_AllLanEGName_Map[lantype];
	songnum = getTableRecNum(tablename);
	return songnum;
}
int ReqMICEDB::reqLanSongQuantity(TABLE_HANDLE* table)
{	
	int songnum = 0;
	if (table != NULL)
		songnum = table->Filter.RecNum;
	return songnum;
}

TABLE_HANDLE* ReqMICEDB::reqTableByLanguage(int lantype,std::string inputstr)
{
	FILTER_PARAM filter;
	char tempstr[32];
	memset(tempstr,0,sizeof(tempstr));
	if (inputstr.length()>0){
		memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
	}
 	std::string tablename = m_AllLanEGName_Map[lantype];
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_FIRSTWORD).c_str()));
	filter.Reset = 1; //0;
	setStrFilter(&filter,tempstr,0);
	TABLE_HANDLE* table= getTableByFilter(tablename,&filter);
	
	return table;
}
int ReqMICEDB::reqLanSongList(int lantype,std::string inputstr)
{	
	int songnum = 0;
	TABLE_HANDLE* table = NULL;
	
	table = reqTableByLanguage(lantype,inputstr);
	if (table != NULL){
		songnum = loadPlayModeList(table);
	}
	return songnum;
}

int ReqMICEDB::reqSongIndexByTablePos(TABLE_HANDLE* table,int position)
{
	int songidx = -1;
	
	if (m_HandleMICEDB != NULL){
		int totalNum = table->Filter.RecNum;
		if ((totalNum >0) && (position<totalNum))
		{
			table->Cursor = table->Filter.StartRec+position;
			int ret = KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
						(DB_UINT8*)&songidx, GET_KEY_VALUE_MODE_INT);
			if (ERR_NONE != ret)
			{
				songidx = -1;
			}
		}
	}
	return songidx;
}

std::string ReqMICEDB::reqSongNameBySongIndex(int songindex)
{
	std::string songname = "";

	if (m_SongInfo->getSongIndex() != songindex){
		m_SongInfo->reset();
		getSongParamBySongIndex(songindex,m_SongInfo);
	}
	songname = m_SongInfo->getSongName();
	return songname;
}


int ReqMICEDB::reqFileTypeBySongIndex(int songindex)
{
	int filetype = 0;
	
	if (m_SongInfo->getSongIndex() != songindex){
		m_SongInfo->reset();
		getSongParamBySongIndex(songindex,m_SongInfo);
	}
	filetype = m_SongInfo->getFileType();
	
	return filetype;
}

int ReqMICEDB::reqSubTypeBySongIndex(int songindex)
{
	int subtype = 0;
	
	if (m_SongInfo->getSongIndex() != songindex){
		m_SongInfo->reset();
		getSongParamBySongIndex(songindex,m_SongInfo);
	}
	subtype = m_SongInfo->getSubType();
	return subtype;
}
char ReqMICEDB::reqFirstWordBySongIndex(int songindex)
{
	char firstword[DB_MAX_VALUE_LEN];
	
	memset(firstword,0,sizeof(firstword));	
	if (m_SongInfo->getSongIndex() != songindex){
		m_SongInfo->reset();
		getSongParamBySongIndex(songindex,m_SongInfo);
	}
	sprintf(firstword,"%s",m_SongInfo->getFirstWord().c_str());
	return firstword[0];
}
int ReqMICEDB::reqSingerIndexBySongIndex(int songindex)
{
	int singerindex = 0;
	
	if (m_HandleMICEDB != NULL){
		FILTER_PARAM Filter;
		memset((char *)&Filter,0,sizeof(Filter));
		strcpy((char *)Filter.KeyName,(ReqTableName::KEY_SONG_SONGIDX).c_str());
		Filter.Reset = 1;
		Filter.SelMod = FILTER_MODE_EQUAL;
		*((int*)(Filter.V1)) = songindex;
		*((int*)(Filter.V2)) = songindex;
			
		TABLE_HANDLE* table = getTableByFilter(ReqTableName::SubTbl_SingerToSong,(FILTER_PARAM *)&Filter);
		if ((table != NULL) && table->Filter.RecNum>0)
		{
			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_SONG_SINGERINDEX).c_str()),(DB_UINT8 *)&singerindex,GET_KEY_VALUE_MODE_INT);
		}
	}
	return singerindex;
}
std::string ReqMICEDB::reqSingerNameBySingerIndex(int singerindex,bool Enflag)
{
	std::string singername = ReqTableName::DEFAULT_SINGER_NAME;
	char keystr[DB_MAX_VALUE_LEN];
	FILTER_PARAM Filter;
	int ret;
	
	if (m_HandleMICEDB == NULL)
		return "";
	
	memset((char *)&Filter,0,sizeof(Filter));
	strcpy((char *)Filter.KeyName,(ReqTableName::KEY_SONG_SINGERINDEX).c_str());
	Filter.Reset = 1;
	Filter.SelMod = FILTER_MODE_EQUAL;
	*((int*)(Filter.V1)) = singerindex;
	*((int*)(Filter.V2)) = singerindex;
		
	TABLE_HANDLE* table = getTableByFilter(ReqTableName::SubTbl_Singer,(FILTER_PARAM *)&Filter);
	if ((table != NULL) && table->Filter.RecNum>0)
	{
		memset(keystr,0,sizeof(keystr));
		if (Enflag)
			ret = KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_SONG_SINGERNAMEEN).c_str()),
					(DB_UINT8 *)keystr,GET_KEY_VALUE_MODE_STR);
		else	
			ret = KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_SONG_SINGERNAME).c_str()),
					(DB_UINT8 *)keystr,GET_KEY_VALUE_MODE_STR);
		if (ret == ERR_NONE)
			singername = std::string(keystr);
	}

	return singername;
}

int ReqMICEDB::reqSingerLanTypeByResultPos(int position)
{
	int lantype = 0;
	int totalnum = m_ResultSingerLanList.size();
	if ((totalnum > 0) && (position < totalnum))
		lantype = m_ResultSingerLanList[position];
	return lantype;
}
int ReqMICEDB::reqSingerQuantityByLanType(int lantype)
{
	int singernum = 0; 
	std::string singerTblname = ReqTableName::SingerTbl_BasicName + reqCountryNameByLanType(lantype);

	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8 *)(singerTblname.c_str()));
		if (table != NULL)
			singernum = table->TableHead->RecNum;
	}
	return singernum;
}
int ReqMICEDB::reqSingerLanguageList(void)
{
	int ret = 0;
	int totalLanNum = m_AllLanTypes.size();

	if (!m_ResultSingerLanList.empty())
		m_ResultSingerLanList.clear();
	
	if (totalLanNum > 0){
		for (int i=0; i<totalLanNum; i++){
			int lantype = m_AllLanTypes[i];
			int singernum = reqSingerQuantityByLanType(lantype);
			if (singernum > 0)
			{
				m_ResultSingerLanList.push_back(lantype);
			}
		}
		ret = m_ResultSingerLanList.size();
	}
		    
	return ret; 	
}

TABLE_HANDLE* ReqMICEDB::reqSingerListInLanguage(int lantype,std::string inputstr)
{
	char tempstr[32];
	FILTER_PARAM filter;
	int totalnum;
	TABLE_HANDLE* table= NULL;
	
	if (m_HandleMICEDB != NULL){
		memset(tempstr,0,sizeof(tempstr));
		if (inputstr.length()>0){
			memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
		}
		std::string tablename = ReqTableName::SingerTbl_BasicName+reqCountryNameByLanType(lantype);
		
		memset(&filter,0,sizeof(filter));
		strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_SINGERFW).c_str()));
		filter.Reset = 1; //0;
		setStrFilter(&filter,tempstr,0);
		table= getTableByFilter(tablename,&filter);
		if (table != NULL)
		{
			if (!m_ResultSingerList.empty())
				m_ResultSingerList.clear();
			//totalnum = table->TableHead->RecNum;
			totalnum = table->Filter.RecNum;
			for (int i=0; i<totalnum; i++){
				int singerIdx;
				table->Cursor = table->Filter.StartRec+i;
				KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SINGERINDEX).c_str(),
							(DB_UINT8*)&(singerIdx), GET_KEY_VALUE_MODE_INT);
				m_ResultSingerList.push_back(singerIdx);
			}
		}
	}
	return table;
}

int ReqMICEDB::reqSingerQuantityInLanguage(TABLE_HANDLE* table)
{
	int singernum = 0;
	if (table != NULL)
		singernum = table->Filter.RecNum;
	return singernum;
}
int ReqMICEDB::reqSingerIndexByResultPos(int position)
{
	int singerIdx = 0;
	
	if ((m_ResultSingerList.size()>0)&&(position<m_ResultSingerList.size()))
	{
		singerIdx = m_ResultSingerList[position];
	}
	
	return singerIdx;
}
char ReqMICEDB::reqSingerFirstWordBySingerIndex(int singerindex)
{
	char firstword[DB_MAX_VALUE_LEN];
	FILTER_PARAM filter;

	if (m_HandleMICEDB == NULL)
		return ' ';
	
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_SINGERINDEX).c_str()));
	filter.Reset = 1;
	filter.SelMod = FILTER_MODE_EQUAL;
	*((unsigned int*)(filter.V1)) = singerindex;
	*((unsigned int*)(filter.V2)) = singerindex;

	TABLE_HANDLE* table = getTableByFilter(ReqTableName::SubTbl_Singer,(FILTER_PARAM *)&filter);

	if ((table != NULL) && (table->Filter.RecNum))
	{		
		memset(firstword,0,sizeof(firstword));
		KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_SINGERFW).c_str()),(DB_UINT8*)firstword,GET_KEY_VALUE_MODE_STR);
	}
	return firstword[0];
}

char ReqMICEDB::reqSingerFirstWordBySongIndex(int songindex)
{
	char firstword[DB_MAX_VALUE_LEN];
	FILTER_PARAM filter;
	int ret;
	
	if (m_HandleMICEDB == NULL)
		return ' ';
	
	memset((char *)&filter,0,sizeof(filter));
	strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_SINGERFW).c_str());
	filter.Reset = 1;
	filter.SelMod = FILTER_MODE_EQUAL;
	*((int*)(filter.V1)) = songindex;
	*((int*)(filter.V2)) = songindex;
	TABLE_HANDLE* table = getTableByFilter(ReqTableName::SubTbl_SearchSinger,(FILTER_PARAM *)&filter);

	if ((table != NULL) && (table->Filter.RecNum))
	{		
		memset(firstword,0,sizeof(firstword));
		KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_SINGERFW).c_str()),(DB_UINT8*)firstword,GET_KEY_VALUE_MODE_STR);
	}
	return firstword[0];
}


int ReqMICEDB::reqSingerSongQuantity(int singerindex)
{
	int songnum = 0;
	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,
													(DB_UINT8 *)(ReqTableName::SubTbl_SongToSinger).c_str());
		FILTER_PARAM filter;
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_SINGERINDEX).c_str());
		filter.Reset = 1;
		filter.SelMod = FILTER_MODE_EQUAL;
		setIntFilter(&filter,singerindex,singerindex,KeyGetLenByName(table,(DB_UINT8 *)(ReqTableName::KEY_SONG_SINGERINDEX).c_str()));
		table = getTableByFilter(ReqTableName::SubTbl_SongToSinger,(FILTER_PARAM *)&filter);
		if (table != NULL){
			songnum = table->Filter.RecNum;
		}
	}
	return songnum;
}
int ReqMICEDB::reqSingerSongQuantity(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != NULL)
		songnum = table->Filter.RecNum;
	return songnum;
}
int ReqMICEDB::reqSingerSongList(int singeridx,std::string inputstr)
{
	int songnum = 0;
	TABLE_HANDLE* table = NULL;
	table = reqSingerSongTableBySingerIndex(singeridx,inputstr);
	if (table != NULL){
		songnum = loadPlayModeList(table);
	}
	return songnum;
}
TABLE_HANDLE* ReqMICEDB::reqSingerSongTableBySingerIndex(int singerindex,std::string inputstr)
{
	FILTER_PARAM filter;
	char tempstr[32];
	TABLE_HANDLE* table = NULL;
	
	memset(tempstr,0,sizeof(tempstr));

	if (m_HandleMICEDB != NULL){
		if (inputstr.length()>0)
			memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
		
		table = DBGetTableHandleByName(m_HandleMICEDB,
									(DB_UINT8 *)(ReqTableName::SubTbl_SongToSinger).c_str());
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_SINGERINDEX).c_str());
		filter.Reset = 1;
		filter.SelMod = FILTER_MODE_EQUAL;
		setIntFilter(&filter,singerindex,singerindex,KeyGetLenByName(table,(DB_UINT8 *)(ReqTableName::KEY_SONG_SINGERINDEX).c_str()));
		table = getTableByFilter(ReqTableName::SubTbl_SongToSinger,(FILTER_PARAM *)&filter);
		
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_FIRSTWORD).c_str());
		filter.Reset = 0;
		//filter.SelMod = FILTER_MODE_EQUAL;
		setStrFilter(&filter,tempstr,0);
		table = getTableByFilter(table,(FILTER_PARAM *)&filter);
	}
	return table;
}

int ReqMICEDB::reqFavoSongQuantity(void)
{	
	int favonum = 0;
	favonum = m_ResultFavoSongList.size();
	return favonum;
}

int ReqMICEDB::reqFavoSongList(void)
{
	int favonum = 0;	
	SORT_KEYS skeys;
	//char favoedbfile[128];
	int ret = 0;
	if (m_ResultFavoSongList.size()>0)
		m_ResultFavoSongList.clear();
	
	if (m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	m_HandleFavoEDB = DBOpen((DB_UINT8 *)(m_FavoEDBPath.c_str()),DB_READ_ONLY);
	if (m_HandleFavoEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleFavoEDB,(DB_UINT8*)(ReqTableName::TableFavo.c_str()),DB_READ_ONLY);
		if (table != NULL){
			int recNum = table->TableHead->RecNum;
			if (recNum>0){
				skeys.keyname = (DB_UINT8*)(ReqTableName::KEY_INSERT_ID).c_str();
				skeys.sorttype = TABLE_SORT_ASCEND;
				TableSort(m_HandleFavoEDB, table, &skeys, 1);
				
				for(int i=0; i<recNum; i++){
					table->Cursor = i;
					int songidx;
					ret = KeyGetValue(m_HandleFavoEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
								(DB_UINT8*)&songidx, GET_KEY_VALUE_MODE_INT);
					if (ERR_NONE == ret)
					{
						m_ResultFavoSongList.push_back(songidx);
					}
				}
			}
			TableClose(m_HandleFavoEDB,table);
		}
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}

	favonum = m_ResultFavoSongList.size();
	return favonum;
}

bool ReqMICEDB::isFavoSong(int songIndex)
{
	bool favofg = false;
	
	if (find(m_ResultFavoSongList.begin(),m_ResultFavoSongList.end(),songIndex)!= m_ResultFavoSongList.end())
			favofg = true;
	return favofg;
	
}
int ReqMICEDB::reqFavoSongIndexByResultPos(int position)
{
	int songidx = -1;
	std::list<int>::iterator searchSong;
	if ((position>=0) && (position<m_ResultFavoSongList.size())){
		searchSong = m_ResultFavoSongList.begin();
		for(int i=position;i>0;i--)
		{
			searchSong++;
			if (searchSong == m_ResultFavoSongList.end())
				break;
		}
		if (searchSong != m_ResultFavoSongList.end())
			songidx = *searchSong;
	}
	return songidx;
}

int ReqMICEDB::reqAddFavoSong(int songIndex)
{
	int ret = -1;
	char insertCmd[128];
	int lastInsertId;
	if (m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	if (m_ResultFavoSongList.size()>0)
	{
		std::list<int>::iterator searchSong = m_ResultFavoSongList.end();
		searchSong--;
		lastInsertId = getFavoInsertIDBySongIndex(*searchSong);
	}else
		lastInsertId = 0;
	
	m_HandleFavoEDB = DBOpen((DB_UINT8 *)(m_FavoEDBPath.c_str()),DB_INSERT_MODE);
	if (m_HandleFavoEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleFavoEDB,(DB_UINT8*)(ReqTableName::TableFavo.c_str()),DB_INSERT_MODE);
		if (table != NULL){
			memset(insertCmd,0,sizeof(insertCmd));
			sprintf(insertCmd,"%s%d,%d%s",(ReqTableName::FavoTable_InsertCmd_Prefix).c_str(),
					songIndex,(lastInsertId+1),(ReqTableName::FavoTable_InsertCmd_Suffix).c_str());
			ret = m_HandleFavoEDB->SQLExecute((DB_UINT8*)insertCmd,m_HandleFavoEDB);
			if (ret == ERR_NONE){
				m_ResultFavoSongList.push_back(songIndex);
			}
			TableClose(m_HandleFavoEDB,table);
		}
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	return ret;
}
int ReqMICEDB::reqDeleteFavoSong(int songIndex)
{
	int ret = 0;
	char deleteCmd[128];
	
	if (m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	m_HandleFavoEDB = DBOpen((DB_UINT8 *)(m_FavoEDBPath.c_str()),DB_EDIT_MODE);
	if (m_HandleFavoEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleFavoEDB,(DB_UINT8*)(ReqTableName::TableFavo.c_str()),DB_EDIT_MODE);
		if (table != NULL){
			memset(deleteCmd,0,sizeof(deleteCmd));
			sprintf(deleteCmd,"%s%d",(DB_UINT8 *)(ReqTableName::FavoTable_DeleteCmd).c_str(),songIndex);
			ret = m_HandleFavoEDB->SQLExecute((DB_UINT8*)deleteCmd,m_HandleFavoEDB);
			if (ret == ERR_NONE)
				{
				std::list<int>::iterator searchSong;
				searchSong = find(m_ResultFavoSongList.begin(),m_ResultFavoSongList.end(),songIndex);
				if (searchSong != m_ResultFavoSongList.end()){
					m_ResultFavoSongList.erase(searchSong);
				}	
			}
			TableClose(m_HandleFavoEDB,table);
		}
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	return ret;
}

int ReqMICEDB::reqDeleteAllFavoSongs(void)
{
	int ret = 0;
	if (m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	m_HandleFavoEDB = DBOpen((DB_UINT8 *)(m_FavoEDBPath.c_str()),DB_EDIT_MODE);
	if (m_HandleFavoEDB != NULL){
		ret = m_HandleFavoEDB->SQLExecute((DB_UINT8*)((ReqTableName::FavoTable_DeleteAllCmd).c_str()),m_HandleFavoEDB);
		if (ret == ERR_NONE){
				m_ResultFavoSongList.clear();
		}
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	
	return ret;
}

int ReqMICEDB::reqProgSongList(void)
{
	int prognum = 0;	
	SORT_KEYS skeys;
	int ret = 0;
	
	if (m_ProgSave)
	{
		if ((m_ResultProgSongList.size()>0)||(m_ProgSongInsertList.size()>0)){
			m_ResultProgSongList.clear();
			m_ProgSongInsertList.clear();
		}		
		if (m_HandleProgEDB != NULL){
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
		m_HandleProgEDB = DBOpen((DB_UINT8 *)(m_ProgEDBPath.c_str()),DB_READ_ONLY);
		if (m_HandleProgEDB != NULL){
			TABLE_HANDLE* table;
			table = TableOpen(m_HandleProgEDB,(DB_UINT8*)(ReqTableName::TableProg.c_str()),DB_READ_ONLY);
			if (table != NULL){
				int recNum = table->TableHead->RecNum;
				if (recNum>0){
					skeys.keyname = (DB_UINT8*)(ReqTableName::KEY_INSERT_ID).c_str();
					skeys.sorttype = TABLE_SORT_ASCEND;
					TableSort(m_HandleProgEDB, table, &skeys, 1);
					
					for(int i=0; i<recNum; i++){
						table->Cursor = i;
						int songidx,insertid;
						
						ret = KeyGetValue(m_HandleProgEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
									(DB_UINT8*)&songidx, GET_KEY_VALUE_MODE_INT);
						ret += KeyGetValue(m_HandleProgEDB, table, (DB_UINT8*)(ReqTableName::KEY_INSERT_ID).c_str(),
									(DB_UINT8*)&insertid, GET_KEY_VALUE_MODE_INT);
						if (ERR_NONE == ret){
							m_ResultProgSongList.push_back(songidx);
							m_ProgSongInsertList.push_back(insertid);
						}
					}
				}
				TableClose(m_HandleProgEDB,table);
			}
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
	}
	
	prognum = m_ResultProgSongList.size();
	return prognum;
}

bool ReqMICEDB::isProgSong(int songIndex)
{
	bool progfg = false;
	
	std::list<int>::iterator searchSong;
	searchSong = find(m_ResultProgSongList.begin(),m_ResultProgSongList.end(),songIndex);
	if (searchSong != m_ResultProgSongList.end())
		progfg = true;
	
	return progfg;
}
int ReqMICEDB::reqProgSongQuantity(void)
{
	return m_ResultProgSongList.size();
}

int ReqMICEDB::reqProgSongIndexByResultPos(int position)
{
	int songindex = 0;
	std::list<int>::iterator searchSong;
	if ((position>=0) && (position<m_ResultProgSongList.size())){
		searchSong = m_ResultProgSongList.begin();
		for(int i=position;i>0;i--)
		{
			searchSong++;
			if (searchSong == m_ResultProgSongList.end())
				break;
		}
		if (searchSong != m_ResultProgSongList.end())
			songindex = *searchSong;
	}
	return songindex;
}
/*
	topfg: true ���ϲ��������ͬʱ���������ö�
	
	topfg: default value false
*/
int ReqMICEDB::reqAddProgSong(int songIndex,bool topfg)
{
	int ret = ERR_NONE;
	char insertCmd[128];
	int newInsertId;
	
	if (m_ProgSongInsertList.size()>0){
		if (topfg == true){
			//std::list<int>::iterator firstId = m_ProgSongInsertList.begin();
			//newInsertId = *firstId - 1;
			int minInsertId = getProgInsertIDByResultPos(0);
			newInsertId = minInsertId-1;
		}else{
			//std::list<int>::iterator lastId = m_ProgSongInsertList.end();
			//lastId--;
			int maxInsertId = getProgInsertIDByResultPos(m_ProgSongInsertList.size()-1);
			newInsertId = maxInsertId + 1;
		}
	}else
		newInsertId = 0;
	
	if (m_ProgSave)
	{
		if (m_HandleProgEDB != NULL){
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
		
		m_HandleProgEDB = DBOpen((DB_UINT8 *)(m_ProgEDBPath.c_str()),DB_INSERT_MODE); //su

		if (m_HandleProgEDB != NULL){
			TABLE_HANDLE* table;
			table = TableOpen(m_HandleProgEDB,(DB_UINT8*)(ReqTableName::TableProg.c_str()),DB_INSERT_MODE);
			if (table != NULL){
				memset(insertCmd,0,sizeof(insertCmd));
				sprintf(insertCmd,"%s%d,%d%s",(ReqTableName::ProgTable_InsertCmd_Prefix).c_str(),
						songIndex,newInsertId,(ReqTableName::ProgTable_InsertCmd_Suffix).c_str());
				ret = m_HandleProgEDB->SQLExecute((DB_UINT8*)insertCmd,m_HandleProgEDB);
				
				TableClose(m_HandleProgEDB,table);
			}
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}else{
			ret = -1;     // open edb failed
		}
	}
	if (ret == ERR_NONE){
		if (topfg==true){
			m_ResultProgSongList.push_front(songIndex);
			m_ProgSongInsertList.push_front(newInsertId);
		}else{
			m_ResultProgSongList.push_back(songIndex);
			m_ProgSongInsertList.push_back(newInsertId);
		}
	}
	return ret;
}

/*
	addfg: true    ֧��ͬһ�׸����ɶ��ѡΪԤԼ����
	addfg: default value false
*/
int ReqMICEDB::reqSetTopProgSong(int songIndex,bool addfg)
{
	int ret = ERR_NONE;
	int minInsertId = getProgInsertIDByResultPos(0);
	
	if (addfg == false)
	{
		//���ҵ��ø���,��ɾ��
		reqDeleteProgSong(songIndex);	
	}
	reqAddProgSong(songIndex,true);
	return 0;
}
/*
	������ͬһ�׸���ֻ��ԤԼһ�ε����
*/
int ReqMICEDB::reqDeleteProgSong(int songIndex)
{
	int songpos;
	int ret = ERR_NONE;
	
	songpos = getProgPositionBySongIndex(songIndex);
	if (songpos != -1){
		ret = reqDeleteProgSongByResultPos(songpos);
	}else
		ret = -1;
	return ret;
}

//for program form   fast
// ProgSong Interface XXXByResultPos  just for FormProgram.cpp
int ReqMICEDB::reqAddTopProgSongByResultPos(int position)	//(int songIndex)
{
	int ret = ERR_NONE;
	char insertCmd[128];
	int minInsertId = getProgInsertIDByResultPos(0);
	int songIndex = reqProgSongIndexByResultPos(position);
	
	reqDeleteProgSongByResultPos(position);

	if(m_ProgSave){
		if (m_HandleProgEDB != NULL){
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
		
		m_HandleProgEDB = DBOpen((DB_UINT8 *)(m_ProgEDBPath.c_str()),DB_INSERT_MODE);
		if (m_HandleProgEDB != NULL){
			TABLE_HANDLE* table;
			table = TableOpen(m_HandleProgEDB,(DB_UINT8*)(ReqTableName::TableProg.c_str()),DB_INSERT_MODE);
			if (table != NULL){
				memset(insertCmd,0,sizeof(insertCmd));
				sprintf(insertCmd,"%s%d,%d%s",(ReqTableName::ProgTable_InsertCmd_Prefix).c_str(),
						songIndex,(minInsertId-1),(ReqTableName::ProgTable_InsertCmd_Suffix).c_str());
				ret = m_HandleProgEDB->SQLExecute((DB_UINT8*)insertCmd,m_HandleProgEDB);
				
				TableClose(m_HandleProgEDB,table);
			}
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
	}
	if(ret==ERR_NONE){
		m_ResultProgSongList.push_front(songIndex);
		m_ProgSongInsertList.push_front(minInsertId-1);
	}
	return 0;
}
int ReqMICEDB::reqDeleteProgSongByResultPos(int position)	//(int songIndex)
{
	char deleteCmd[128];
	int insertid;
	int ret = ERR_NONE;
	
	if(m_ProgSave)
	{
		insertid = getProgInsertIDByResultPos(position);
		
		if (m_HandleProgEDB != NULL){
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
		m_HandleProgEDB = DBOpen((DB_UINT8 *)(m_ProgEDBPath.c_str()),DB_EDIT_MODE);
		if (m_HandleProgEDB != NULL){
			TABLE_HANDLE* table;
			table = TableOpen(m_HandleProgEDB,(DB_UINT8*)(ReqTableName::TableProg.c_str()),DB_EDIT_MODE);
			if (table != NULL){
				memset(deleteCmd,0,sizeof(deleteCmd));
				sprintf(deleteCmd,"%s%d",(DB_UINT8 *)(ReqTableName::ProgTable_DeleteCmd).c_str(),insertid);
				ret = m_HandleProgEDB->SQLExecute((DB_UINT8*)deleteCmd,m_HandleProgEDB);
			}
			TableClose(m_HandleProgEDB,table);
		}
		DBClose(m_HandleProgEDB);
		m_HandleProgEDB = NULL;
	}
	if (ret == ERR_NONE)
	{
		deleteProgSongFormList(position);
		deleteProgInsertIdFormList(position);
	}
	return 0;
}
int ReqMICEDB::reqDeleteAllProgSongs(void)
{
	int ret = ERR_NONE;
	
	if(m_ProgSave){
		if (m_HandleProgEDB != NULL){
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
		m_HandleProgEDB = DBOpen((DB_UINT8 *)(m_ProgEDBPath.c_str()),DB_EDIT_MODE);
		if (m_HandleProgEDB != NULL){
			ret = m_HandleProgEDB->SQLExecute((DB_UINT8*)((ReqTableName::ProgTable_DeleteAllCmd).c_str()),m_HandleProgEDB);
			DBClose(m_HandleProgEDB);
			m_HandleProgEDB = NULL;
		}
	}
	if (ret == ERR_NONE){
		m_ResultProgSongList.clear();
		m_ProgSongInsertList.clear();
	}
	return ret;
}

//input string search   �ݲ�ʹ��
TABLE_HANDLE* ReqMICEDB::reqTableByFullSpell(TABLE_HANDLE* table,std::string inputstr)
{
	FILTER_PARAM filter; 
	//char tempstr[32];
	//memset(tempstr,0,sizeof(tempstr));
	//memcpy(tempstr,(char *)(inputstr.c_str()),sizeof(tempstr)-1);
	//int len = strlen(tempstr);
	
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_FIRSTWORD).c_str()));
	filter.Reset = 1;
	setStrFilter(&filter,(char *)(inputstr.c_str()),0);
	
	table= getTableByFilter(table,&filter);
	return table;
}

TABLE_HANDLE* ReqMICEDB::reqSearchSongNoTable(int inputnum)
{
	FILTER_PARAM filter;
	TABLE_HANDLE* table = NULL;

	if (m_HandleMICEDB != NULL){
		table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::SubTbl_BookNumber.c_str()));
		if (table == NULL)	
		 	table = TableOpen(m_HandleMICEDB, (DB_UINT8*)ReqTableName::SubTbl_BookNumber.c_str(), DB_READ_ONLY);
		 
		 memset(&filter,0,sizeof(filter));
		 strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_SONGIDX).c_str()));
		 filter.Reset = 1;
		 filter.SelMod = FILTER_MODE_BIG; 
		 setIntFilter(&filter,inputnum,999999,KeyGetLenByName(table,(DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str()));
		
		 table= getTableByFilter(table,&filter);
	}
	 return table;
}

int ReqMICEDB::reqSearchSongNoQuantity(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != NULL)
		songnum = table->Filter.RecNum;
		//songnum = table->TableHead->RecNum;
	return songnum;
}
TABLE_HANDLE* ReqMICEDB::reqSearchSingerSongTableByLanguage(int lantype,std::string inputstr)
{	
	FILTER_PARAM filter;
	char tempstr[32];
	TABLE_HANDLE* table = nullptr;
	
	memset(tempstr,0,sizeof(tempstr));
	if (inputstr.length()>0){
		memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
	}
	
 	std::string tablename = ReqTableName::SearchSingerTbl_BasicName+reqCountryNameByLanType(lantype);
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_SINGERFW).c_str()));
	filter.Reset = 1; //0;
	setStrFilter(&filter,tempstr,0);
	table= getTableByFilter(tablename,&filter);
	
	return table;
}
int ReqMICEDB::reqSearchSingerSongQuantity(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != nullptr)
		songnum = table->Filter.RecNum;
	return songnum;
}

int ReqMICEDB::reqRecSongList(void)
{
	int recnum = 0;	
	SORT_KEYS skeys;
	int ret = 0;
	if (m_ResultRecSongList.size()>0)
		m_ResultRecSongList.clear();
	
	if (m_HandleRecEDB != NULL){
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	m_HandleRecEDB = DBOpen((DB_UINT8 *)(m_RecEDBPath.c_str()),DB_READ_ONLY);
	if (m_HandleRecEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleRecEDB,(DB_UINT8*)(ReqTableName::TableRecord.c_str()),DB_READ_ONLY);
		if (table != NULL){
			int recNum = table->TableHead->RecNum;
			if (recNum>0){
				skeys.keyname = (DB_UINT8*)(ReqTableName::KEY_INSERT_ID).c_str();
				skeys.sorttype = TABLE_SORT_ASCEND;
				TableSort(m_HandleRecEDB, table, &skeys, 1);
				RecSongParam tmprec;
				for(int i=0; i<recNum; i++){
					table->Cursor = i;
					ret = KeyGetValue(m_HandleRecEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
								(DB_UINT8*)&(tmprec.m_songIndex), GET_KEY_VALUE_MODE_INT);
					ret += KeyGetValue(m_HandleRecEDB, table, (DB_UINT8*)(ReqTableName::KEY_RECORD_RECINDEX).c_str(),
								(DB_UINT8*)&(tmprec.m_recIndex), GET_KEY_VALUE_MODE_INT);
					ret += KeyGetValue(m_HandleRecEDB, table, (DB_UINT8*)(ReqTableName::KEY_RECORD_SCORE).c_str(),
								(DB_UINT8*)&(tmprec.m_score), GET_KEY_VALUE_MODE_INT);
					ret += KeyGetValue(m_HandleRecEDB, table, (DB_UINT8*)(ReqTableName::KEY_RECORD_STORAGE).c_str(),
								(DB_UINT8*)&(tmprec.m_storage), GET_KEY_VALUE_MODE_INT);
					ret += KeyGetValue(m_HandleRecEDB, table, (DB_UINT8*)(ReqTableName::KEY_INSERT_ID).c_str(),
								(DB_UINT8*)&(tmprec.m_insertId), GET_KEY_VALUE_MODE_INT);
					if (ERR_NONE == ret){
						/*
						tmprec.setSongIndex(songidx);
						tmprec.setRecIndex(recidx);
						tmprec.setScore(score);
						tmprec.setStorage(storage);
						tmprec.setInsertId(insertid);
						*/
						m_ResultRecSongList.push_back(tmprec);
					}
				}
			}
			TableClose(m_HandleRecEDB,table);
		}
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}

	recnum = m_ResultRecSongList.size();
	return recnum;
}
int ReqMICEDB::reqRecSongQuantity(void)
{
	return m_ResultRecSongList.size();
}

int ReqMICEDB::reqNextRecIndex(int songindex)
{
	int recidx = 0;
	int recnum = m_ResultRecSongList.size();
	std::vector<int> recindexs;
	std::list<RecSongParam>::iterator item;
	if (recnum>0){
		//��ȡ�ø���������¼�����к�
		RecSongParam recSong;
		item = m_ResultRecSongList.begin();
		recSong = *item; 
		for(int i=0; i<recnum; i++){
			int tmpvalue = recSong.m_songIndex;
			if (tmpvalue== songindex)
				recindexs.push_back(recSong.m_recIndex);
			item++;
		}
		int tmpnum = recindexs.size();
		if(tmpnum == 0){
			recidx = 0;
		}else if(tmpnum == 1){
			if (recindexs[0] == 0)
				recidx = 1;
			else
				recidx = 0;
			
		}else if (tmpnum>1){
			sort(recindexs.begin(),recindexs.end());
			if (recindexs[0] != 0){
				recidx = 0;
			}else{
				for(int i=1; i<tmpnum; i++){
					if (recindexs[i]-recindexs[i-1]>1){
						recidx = recindexs[i-1]+1;
						break;
					}
				}
				if (recidx == 0){
					recidx = recindexs[tmpnum-1]+1;
				}
			}
		}
		
	}
	//M3D_DebugPrint("===reqNextRecIndex==songindex[%d]=recidx[%d]==\n",songindex,recidx);
	return recidx;
}
int ReqMICEDB::reqAddRecSong(RecSongParam* recsong)
{
	char insertCmd[128];
	int lastInsertId;
	int ret = -1;
	if (m_HandleRecEDB != NULL){
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	if (m_ResultRecSongList.size()>0)
	{
		std::list<RecSongParam>::iterator itemRec = m_ResultRecSongList.end();
		itemRec--;
		RecSongParam tmprec = (RecSongParam)*itemRec;
		lastInsertId = tmprec.m_insertId;
	}else
		lastInsertId = 0;
	
	m_HandleRecEDB = DBOpen((DB_UINT8 *)(m_RecEDBPath.c_str()),DB_INSERT_MODE);
	if (m_HandleRecEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleRecEDB,(DB_UINT8*)(ReqTableName::TableRecord.c_str()),DB_INSERT_MODE);
		if (table != NULL){
			//int songidx = recsong->getSongIndex();
			int insertid = lastInsertId +1;
			//int recidx = recsong->getRecIndex();
			//int score = recsong->getScore();
			//int storage = recsong->getStorage();
			
			memset(insertCmd,0,sizeof(insertCmd));
			sprintf(insertCmd,"%s%d,%d,%d,%d,%d%s",(ReqTableName::RecTable_InsertCmd_Prefix).c_str(),
					recsong->m_songIndex,insertid,recsong->m_recIndex,recsong->m_score,recsong->m_storage,
					(ReqTableName::RecTable_InsertCmd_Suffix).c_str());
			ret = m_HandleRecEDB->SQLExecute((DB_UINT8*)insertCmd,m_HandleRecEDB);
			if (ret == ERR_NONE){
				/*
				RecSongParam tmprec;
				tmprec.setSongIndex(songidx);
				tmprec.setInsertId(insertid);
				tmprec.setRecIndex(recidx);
				tmprec.setScore(score);
				tmprec.setStorage(storage);
				*/
				recsong->m_insertId = insertid;
				m_ResultRecSongList.push_back(*recsong);
			}
			TableClose(m_HandleRecEDB,table);
		}
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	return ret;
}
int ReqMICEDB::reqDeleteRecSongByResultPos(int position)
{
	int ret = 0;
	char deleteCmd[128];
	int insertid = 0;
	
	if (m_HandleRecEDB != NULL){
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	m_HandleRecEDB = DBOpen((DB_UINT8 *)(m_RecEDBPath.c_str()),DB_EDIT_MODE);
	if (m_HandleRecEDB != NULL){
		TABLE_HANDLE* table;
		table = TableOpen(m_HandleRecEDB,(DB_UINT8*)(ReqTableName::TableRecord.c_str()),DB_EDIT_MODE);
		if (table != NULL){
			std::list<RecSongParam>::iterator itemrec;
			itemrec = m_ResultRecSongList.begin();
			
			for (int i=0; i<m_ResultRecSongList.size();i++)
			{
				RecSongParam recsong = (RecSongParam)*itemrec;
				if (i == position){
					insertid = recsong.m_insertId;
					memset(deleteCmd,0,sizeof(deleteCmd));
					sprintf(deleteCmd,"%s%d",(DB_UINT8 *)(ReqTableName::RecTable_DeleteCmd).c_str(),insertid);
					ret = m_HandleRecEDB->SQLExecute((DB_UINT8*)deleteCmd,m_HandleRecEDB);
					if (ret == ERR_NONE){
						m_ResultRecSongList.erase(itemrec);
					}
					break;
				}
				itemrec++;
			}
			
			TableClose(m_HandleRecEDB,table);

			DBClose(m_HandleRecEDB);
			m_HandleRecEDB = NULL;
		}
	}
	return ret;
}

RecSongParam* ReqMICEDB::reqRecSongParamByResultPos(int position)
{
	std::list<RecSongParam>::iterator searchRec;
	m_RecSongInfo = nullptr;
	
	if ((position>=0) && (position<m_ResultRecSongList.size())){
		searchRec = m_ResultRecSongList.begin();
		for(int i=position;i>0;i--){
			searchRec++;
			if (searchRec == m_ResultRecSongList.end())
				break;
		}
		if (searchRec != m_ResultRecSongList.end()){
			m_RecSongInfo = &(*searchRec);
		}
	}
	return m_RecSongInfo;
}
int ReqMICEDB::reqRecSongIndexByResultPos(int position)
{
	int songidx = -1;
	std::list<RecSongParam>::iterator searchRec;
	if ((position>=0) && (position<m_ResultRecSongList.size())){
		searchRec = m_ResultRecSongList.begin();
		for(int i=position;i>0;i--){
			searchRec++;
			if (searchRec == m_ResultRecSongList.end())
				break;
		}
		if (searchRec != m_ResultRecSongList.end()){
			RecSongParam tmpRec = *searchRec;
			songidx = tmpRec.m_songIndex;//&(~DEFAULT_RECORDSONG_HEAD);
		}
	}
	return songidx;
}
int ReqMICEDB::reqRecScoreByResultPos(int position)
{
	int recscore = 0;
	std::list<RecSongParam>::iterator searchRec;
	if ((position>=0) && (position<m_ResultRecSongList.size())){
		searchRec = m_ResultRecSongList.begin();
		for(int i=position;i>0;i--){
			searchRec++;
			if (searchRec == m_ResultRecSongList.end())
				break;
		}
		if (searchRec != m_ResultRecSongList.end()){
			RecSongParam tmpRec = *searchRec;
			recscore = tmpRec.m_score;
		}
	}
	return recscore;
}
int ReqMICEDB::reqRecIndexByResultPos(int position)
{
	int recidx = -1;
	std::list<RecSongParam>::iterator searchRec;
	if ((position>=0) && (position<m_ResultRecSongList.size())){
		searchRec = m_ResultRecSongList.begin();
		for(int i=position;i>0;i--){
			searchRec++;
			if (searchRec == m_ResultRecSongList.end())
				break;
		}
		if (searchRec != m_ResultRecSongList.end()){
			RecSongParam tmpRec = *searchRec;
			recidx = tmpRec.m_recIndex;
		}
	}
	return recidx;
}

int ReqMICEDB::reqDeleteAllRecSongs(void)
{
	int ret = 0;
	if (m_HandleRecEDB != NULL){
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	m_HandleRecEDB = DBOpen((DB_UINT8 *)(m_RecEDBPath.c_str()),DB_EDIT_MODE);
	if (m_HandleRecEDB != NULL){
		ret = m_HandleRecEDB->SQLExecute((DB_UINT8*)((ReqTableName::RecTable_DeleteAllCmd).c_str()),m_HandleRecEDB);
		if (ret == ERR_NONE){
				m_ResultRecSongList.clear();
		}
		DBClose(m_HandleRecEDB);
		m_HandleRecEDB = NULL;
	}
	
	return ret;
}

//form SongNo
int ReqMICEDB::reqAllSongList(void)
{
	int songnum = 0;
	FILTER_PARAM filter;
	TABLE_HANDLE* table = NULL;
	//if (m_PlayModeList.size()>0)
	//	m_PlayModeList.clear();

	if (m_HandleMICEDB != NULL){
		table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8*)(ReqTableName::SubTbl_BookNumber.c_str()));
		if (table == NULL)	
		 	table = TableOpen(m_HandleMICEDB, (DB_UINT8*)ReqTableName::SubTbl_BookNumber.c_str(), DB_READ_ONLY);
		 
		 memset(&filter,0,sizeof(filter));
		 strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_SONGIDX).c_str()));
		 filter.Reset = 1;
		 filter.SelMod = FILTER_MODE_NEQUAL; 
		 setIntFilter(&filter,0,999999,KeyGetLenByName(table,(DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str()));
		
		 table= getTableByFilter(table,&filter);
		 if (table != NULL){
		 	/*
		 	int totalNum = table->Filter.RecNum;
		 	for(int i=0; i<totalNum; i++){
				int songidx = 0;
				table->Cursor = table->Filter.StartRec+i;
				int ret = KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
						(DB_UINT8*)&songidx, GET_KEY_VALUE_MODE_INT);
				if (ERR_NONE == ret)
					m_PlayModeList.push_back(songidx);
			}
			*/
			songnum = loadPlayModeList(table);
		 }
	}
	return songnum;
}

int ReqMICEDB::reqPlayListSongByPosition(int position)
{
	int songidx = -1;
	std::list<int>::iterator searchSong;
	
	if ((position>=0) && (position<m_PlayModeList.size())){
		searchSong = m_PlayModeList.begin();
		for(int i=position;i>0;i--)
		{
			searchSong++;
			if (searchSong == m_PlayModeList.end())
				break;
		}
		if (searchSong != m_PlayModeList.end())
			songidx = *searchSong;
	}
	return songidx;
}
int ReqMICEDB::reqHindiSubTypes(void)
{
	return m_HindiSubTypes.size();
}
std::string ReqMICEDB::reqHindiSubTypeByResultPos(int position)
{
	std::string subtypename="";
	
	if ((position>=0)&&(position< m_HindiSubTypes.size())){
		subtypename = m_HindiSubTypes[position];
	}
	
	return subtypename;
}
int ReqMICEDB::reqSongQuantityByHindiSubTypeName(std::string subtypename)
{
	int songnum = 0; 
	std::string tablename = ReqTableName::HindiSubTypeTbl_BasicName + subtypename;

	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8 *)(tablename.c_str()));
		if (table != NULL)
			songnum = table->TableHead->RecNum;
	}
	return songnum;
}

TABLE_HANDLE* ReqMICEDB::reqTableByHindiSubTypeName(std::string subtypename,std::string inputstr)
{
	FILTER_PARAM filter;
	TABLE_HANDLE* table = NULL;
	char tempstr[32];
	memset(tempstr,0,sizeof(tempstr));
	if (inputstr.length()>0){
		memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
	}
 	std::string tablename = ReqTableName::HindiSubTypeTbl_BasicName + subtypename;
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_FIRSTWORD).c_str()));
	filter.Reset = 1; //0;
	setStrFilter(&filter,tempstr,0);
	table= getTableByFilter(tablename,&filter);
	
	return table;
}
int ReqMICEDB::reqHindiSubTypeSongQuantity(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != NULL)
		songnum = table->Filter.RecNum;
	return songnum;
}

std::string ReqMICEDB::reqAlbumNameByAlbumIndex(int albumindex,bool Enflag)
{
	std::string albumname = "";
	char keystr[DB_MAX_VALUE_LEN];
	FILTER_PARAM Filter;
	int ret;
	
	if (m_HandleMICEDB == NULL)
		return "";
	
	memset((char *)&Filter,0,sizeof(Filter));
	strcpy((char *)Filter.KeyName,(ReqTableName::KEY_SONG_ALBUMINDEX).c_str());
	Filter.Reset = 1;
	Filter.SelMod = FILTER_MODE_EQUAL;
	*((int*)(Filter.V1)) = albumindex;
	*((int*)(Filter.V2)) = albumindex;
		
	TABLE_HANDLE* table = getTableByFilter(ReqTableName::AlbumTbl_BasicName,(FILTER_PARAM *)&Filter);
	if ((table != NULL) && table->Filter.RecNum>0)
	{
		memset(keystr,0,sizeof(keystr));
		if (Enflag)
			ret = KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_SONG_ALBUMNAMEEN).c_str()),
					(DB_UINT8 *)keystr,GET_KEY_VALUE_MODE_STR);
		else	
			ret = KeyGetValue(m_HandleMICEDB,table,(DB_UINT8 *)((ReqTableName::KEY_SONG_ALBUMNAME).c_str()),
					(DB_UINT8 *)keystr,GET_KEY_VALUE_MODE_STR);
		if (ret == ERR_NONE)
			albumname = std::string(keystr);
	}

	return albumname;
}


int ReqMICEDB::reqAlbumLanTypeByResultPos(int position)
{
	int lantype = 0;
	int totalnum = m_ResultAlbumLanList.size();
	if ((totalnum > 0) && (position < totalnum))
		lantype = m_ResultAlbumLanList[position];
	return lantype;
}

int ReqMICEDB::reqAlbumQuantityByLanType(int lantype)
{
	int albumnum = 0; 
	std::string albumTblname = ReqTableName::AlbumTbl_BasicName + reqCountryNameByLanType(lantype);

	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8 *)(albumTblname.c_str()));
		if (table != NULL)
			albumnum = table->TableHead->RecNum;
	}
	return albumnum;
}
int ReqMICEDB::reqAlbumLanguageList(void)
{
	int ret = 0;
	int totalLanNum = m_AllLanTypes.size();

	if (!m_ResultAlbumLanList.empty())
		m_ResultAlbumLanList.clear();
	
	if (totalLanNum > 0){
		for (int i=0; i<totalLanNum; i++){
			int lantype = m_AllLanTypes[i];
			int albumnum = reqAlbumQuantityByLanType(lantype);
			if (albumnum > 0)
			{
				m_ResultAlbumLanList.push_back(lantype);
			}
		}
		ret = m_ResultAlbumLanList.size();
	}
		    
	return ret; 	
}
TABLE_HANDLE* ReqMICEDB::reqAlbumListInLanguage(int lantype,std::string inputstr)
{
	char tempstr[32];
	FILTER_PARAM filter;
	int totalnum;
	TABLE_HANDLE* table= NULL;
	
	if (m_HandleMICEDB != NULL){
		memset(tempstr,0,sizeof(tempstr));
		if (inputstr.length()>0){
			memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
		}
		std::string tablename = ReqTableName::AlbumTbl_BasicName+reqCountryNameByLanType(lantype);
		
		memset(&filter,0,sizeof(filter));
		strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_ALBUMFW).c_str()));
		filter.Reset = 1; //0;
		setStrFilter(&filter,tempstr,0);
		table= getTableByFilter(tablename,&filter);
		if (table != NULL)
		{
			if (!m_ResultAlbumList.empty())
				m_ResultAlbumList.clear();
			//totalnum = table->TableHead->RecNum;
			totalnum = table->Filter.RecNum;
			for (int i=0; i<totalnum; i++){
				int albumIdx;
				table->Cursor = table->Filter.StartRec+i;
				KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_ALBUMINDEX).c_str(),
							(DB_UINT8*)&(albumIdx), GET_KEY_VALUE_MODE_INT);
				m_ResultAlbumList.push_back(albumIdx);
			}
		}
	}
	return table;
}
int ReqMICEDB::reqAlbumQuantityInLanguage(TABLE_HANDLE* table)
{
	int albumnum = 0;
	if (table != NULL)
		albumnum = table->Filter.RecNum;
	return albumnum;
}
int ReqMICEDB::reqAlbumIndexByResultPos(int position)
{
	int albumIdx = 0;
	
	if ((position>=0)&&(position<m_ResultAlbumList.size()))
	{
		albumIdx = m_ResultAlbumList[position];
	}
	
	return albumIdx;
}
char ReqMICEDB::reqAlbumFirstWordByAlbumIndex(int albumindex)
{
	char firstword[DB_MAX_VALUE_LEN];
	FILTER_PARAM filter;

	if (m_HandleMICEDB == NULL)
		return ' ';
	
	memset(&filter,0,sizeof(filter));
	strcpy((char *)(filter.KeyName),((ReqTableName::KEY_SONG_ALBUMINDEX).c_str()));
	filter.Reset = 1;
	filter.SelMod = FILTER_MODE_EQUAL;
	*((unsigned int*)(filter.V1)) = albumindex;
	*((unsigned int*)(filter.V2)) = albumindex;

	TABLE_HANDLE* table = getTableByFilter(ReqTableName::AlbumTbl_BasicName,(FILTER_PARAM *)&filter);

	if ((table != NULL) && (table->Filter.RecNum))
	{		
		memset(firstword,0,sizeof(firstword));
		KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_ALBUMFW).c_str()),(DB_UINT8*)firstword,GET_KEY_VALUE_MODE_STR);
	}
	return firstword[0];
}

int ReqMICEDB::reqAlbumSongQuantity(int albumindex)
{
	int songnum = 0;
	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB,
													(DB_UINT8 *)(ReqTableName::SubTbl_SongToAlbum).c_str());
		FILTER_PARAM filter;
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_ALBUMINDEX).c_str());
		filter.Reset = 1;
		filter.SelMod = FILTER_MODE_EQUAL;
		setIntFilter(&filter,albumindex,albumindex,KeyGetLenByName(table,(DB_UINT8 *)(ReqTableName::KEY_SONG_ALBUMINDEX).c_str()));
		table = getTableByFilter(ReqTableName::SubTbl_SongToAlbum,(FILTER_PARAM *)&filter);
		if (table != NULL){
			songnum = table->Filter.RecNum;
		}
	}
	return songnum;
}
int ReqMICEDB::reqAlbumSongQuantity(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != NULL)
		songnum = table->Filter.RecNum;
	return songnum;
}

int ReqMICEDB::reqAlbumSongList(int albumindex,std::string inputstr)
{
	int songnum = 0;
	TABLE_HANDLE* table = NULL;
	table = reqAlbumSongTableByAlbumIndex(albumindex,inputstr);
	if (table != NULL){
		songnum = loadPlayModeList(table);
	}
	return songnum;
}
TABLE_HANDLE* ReqMICEDB::reqAlbumSongTableByAlbumIndex(int albumindex,std::string inputstr)
{
	FILTER_PARAM filter;
	char tempstr[32];
	TABLE_HANDLE* table = NULL;
	
	memset(tempstr,0,sizeof(tempstr));

	if (m_HandleMICEDB != NULL){
		if (inputstr.length()>0)
			memcpy(tempstr,(char*)(inputstr.c_str()),sizeof(tempstr));
		
		table = DBGetTableHandleByName(m_HandleMICEDB,
						(DB_UINT8 *)(ReqTableName::SubTbl_SongToAlbum).c_str());
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_ALBUMINDEX).c_str());
		filter.Reset = 1;
		filter.SelMod = FILTER_MODE_EQUAL;
		setIntFilter(&filter,albumindex,albumindex,KeyGetLenByName(table,(DB_UINT8 *)(ReqTableName::KEY_SONG_ALBUMINDEX).c_str()));
		table = getTableByFilter(ReqTableName::SubTbl_SongToAlbum,(FILTER_PARAM *)&filter);
		
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_FIRSTWORD).c_str());
		filter.Reset = 0;
		//filter.SelMod = FILTER_MODE_EQUAL;
		setStrFilter(&filter,tempstr,0);
		table = getTableByFilter(table,(FILTER_PARAM *)&filter);
	}
	return table;
}

int ReqMICEDB::setIntFilter(FILTER_PARAM *filter,int intPara1,int intPara2,int size)
{
	switch (size) {
		case 1: 
			*((char*)(filter->V1)) = intPara1;
			*((char*)(filter->V2)) = intPara2;
			break;
		case 2: 
			*((short*)(filter->V1)) = intPara1;
			*((short*)(filter->V2)) = intPara2;
			break;
		case 4: 
			*((int*)(filter->V1)) = intPara1;
			*((int*)(filter->V2)) = intPara2;
			break;
	}
	return 0;
}
/*
 * Function name  	: setStrFilter
 * Arguments      	: filter - input filter parameter, this parameter will be modified and output
 *									strPara - string parameter 
 *									crt - 1: find the string equal to strPara, 0: find the string bigger than strPara
 * Return         	: none
 * Description    	: setup filter by string parameter
 *					
*/
void ReqMICEDB::setStrFilter(FILTER_PARAM *Filter, char* strPara, int crt)
{
	//for (int i=0; i<sizeof(Filter->V1); i++) {
	memset(Filter->V1,0,sizeof(Filter->V1));
	if (crt)
		memset(Filter->V2,0,sizeof(Filter->V2));
	else
		memset(Filter->V2,-1,sizeof(Filter->V2));

	for (int i=0; i<strlen(strPara); i++) {
		if (strPara[i] != 0) {
			Filter->V1[i] = strPara[i];
			Filter->V2[i] = strPara[i];
		}
		/*
		else {
			Filter->V1[i] = 0;
			if (crt)
				Filter->V2[i] = 0;
			else
				Filter->V2[i] = -1;
		}
		*/
	}
}

int ReqMICEDB::getVersionInfo(TABLE_HANDLE* table)
{
	int ret = 0;
	char keystr[DB_MAX_VALUE_LEN];
	unsigned char keyval;
	if ((table != NULL)&&(table->TableHead->RecNum > 0))
	{
		table->Cursor = 0;
		KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_Vession).c_str(),
				   (DB_UINT8*)&(keystr), GET_KEY_VALUE_MODE_STR);
		m_TableVession = std::string(keystr);
		KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_Customer).c_str(),
				        (DB_UINT8*)&(keyval), GET_KEY_VALUE_MODE_INT);
		m_CustomerNo = keyval;
	}
	else
	{
		ret = -1;
	}
	return ret;
}

void ReqMICEDB::resetAllLanguageInfo()
{
	if (!m_AllLanTypes.empty())
			m_AllLanTypes.clear();

	if (!m_AllLanEGName_Map.empty())
		m_AllLanEGName_Map.clear();

	if (!m_AllCountryName_Map.empty())
		m_AllLanEGName_Map.clear();
}

//int ReqMICEDB::getAllLanNameEG(TABLE_HANDLE* lantable)
int ReqMICEDB::getAllLanguageInfo(TABLE_HANDLE* lantable)
{
	unsigned char lantype;
	char lanname[DB_MAX_NAME_LEN];
	char countryname[DB_MAX_NAME_LEN];
	int lancnt = lantable->TableHead->RecNum;

	if (lancnt > 0)
	{
		resetAllLanguageInfo();
		
		for (int i=0; i<lancnt;i++)
		{
			lantable->Cursor = i;
			KeyGetValue(m_HandleMICEDB, lantable, (DB_UINT8*)(ReqTableName::KEY_LANGUAGE_TYPE).c_str(),
				        (DB_UINT8*)&(lantype), GET_KEY_VALUE_MODE_INT);
			
			KeyGetValue(m_HandleMICEDB, lantable, (DB_UINT8*)(ReqTableName::KEY_LANGUAGE_EN_NAME).c_str(),
				       (DB_UINT8*)&(lanname), GET_KEY_VALUE_MODE_STR);
			
			KeyGetValue(m_HandleMICEDB, lantable, (DB_UINT8*)(ReqTableName::KEY_LANGUAGE_COUNTRY_NAME).c_str(),
				       (DB_UINT8*)&(countryname), GET_KEY_VALUE_MODE_STR);
			//int templan = lantype;
			m_AllLanTypes.push_back(lantype);
			//std::string tmpstr(lanname) ;
			m_AllLanEGName_Map.insert(std::pair<int,std::string>(lantype,std::string(lanname)));
			m_AllCountryName_Map.insert(std::pair<int,std::string>(lantype,std::string(countryname)));
		}
	}
	return lancnt;
}

int ReqMICEDB::getTableRecNum(std::string& tablename)
{
	if (m_HandleMICEDB != NULL){
		TABLE_HANDLE* table = DBGetTableHandleByName(m_HandleMICEDB, (DB_UINT8*)(tablename.c_str()));	
		if (table != NULL)
			return table->TableHead->RecNum;
	}
    return 0;
}

TABLE_HANDLE* ReqMICEDB::getTableByFilter(TABLE_HANDLE* table,FILTER_PARAM *Filter)
{
	DB_UINT8 ret = ERR_NONE;
	
	if (table != NULL)
	{
	    if (Filter->Reset) {
	        TableFilterReset(table);
	    }

	    ret = TableFilter(m_HandleMICEDB, table, Filter->KeyName, (DB_UINT8 *)(Filter->V1), (DB_UINT8 *)(Filter->V2));
		//if (ret != ERR_NO_RIGHT_REC && ret)
		if (ret != ERR_NONE)
	        return NULL;
	}
	return table;
}

TABLE_HANDLE* ReqMICEDB::getTableByFilter(std::string& tablename,FILTER_PARAM *Filter)
{
	DB_UINT8 ret = ERR_NONE;
	TABLE_HANDLE* table = NULL;
	if (m_HandleMICEDB != NULL){
		DBGetTableHandleByName(m_HandleMICEDB,(DB_UINT8*)(tablename.c_str()));
		if (table == NULL)	
		 	table = TableOpen(m_HandleMICEDB, (DB_UINT8*)tablename.c_str(), DB_READ_ONLY);
		
		if (table != NULL)
		{
		    if (Filter->Reset) {
		        TableFilterReset(table);
		    }

		    ret = TableFilter(m_HandleMICEDB, table, Filter->KeyName, (DB_UINT8 *)(Filter->V1), (DB_UINT8 *)(Filter->V2));
			//if (ret != ERR_NO_RIGHT_REC && ret)
			if (ret != ERR_NONE)
		        return NULL;
		}
	}
	return table;
}

int ReqMICEDB::getSongParamBySongIndex(int songidx,SongParam* songparam)
{
	char keystr[DB_MAX_VALUE_LEN];
	unsigned char keybyte;

	if (m_HandleMICEDB != NULL){
		FILTER_PARAM tFilter;
		memset((void *)&tFilter,0,sizeof(tFilter));
		strcpy((char *)(tFilter.KeyName),((ReqTableName::KEY_SONG_SONGIDX).c_str()));
		tFilter.Reset = 1;
		tFilter.SelMod = FILTER_MODE_EQUAL;
		*((unsigned int*)(tFilter.V1)) = songidx;
		*((unsigned int*)(tFilter.V2)) = songidx;

		TABLE_HANDLE* table = getTableByFilter(ReqTableName::SubTbl_SongName,(FILTER_PARAM *)&tFilter);

		if ((table != NULL) && (table->Filter.RecNum))
		{		
			memset(keystr,0,sizeof(keystr));
			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_SONGNAME).c_str()),(DB_UINT8*)keystr,GET_KEY_VALUE_MODE_STR);
			songparam->setSongName(std::string(keystr));

			//KeyGetValue(m_HandleMICEDB, lantable, (DB_UINT8*)(ReqTableName::KEY_LANGUAGE_TYPE).c_str(),
			//		        (DB_UINT8*)&(lantype), GET_KEY_VALUE_MODE_INT);
			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_LANTYPE).c_str()),(DB_UINT8*)&keybyte,GET_KEY_VALUE_MODE_INT);
			songparam->setSongLan(keybyte);
			
			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_TYPEIDX).c_str()),(DB_UINT8*)&keybyte,GET_KEY_VALUE_MODE_INT);
			songparam->setFileType(keybyte);

			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_SUBTYPEIDX).c_str()),(DB_UINT8*)&keybyte,GET_KEY_VALUE_MODE_INT);
			songparam->setSubType(keybyte);

			memset(keystr,0,sizeof(keystr));
			KeyGetValue(m_HandleMICEDB,table,(DB_UINT8*)((ReqTableName::KEY_SONG_FIRSTWORD).c_str()),(DB_UINT8*)keystr,GET_KEY_VALUE_MODE_STR);
			songparam->setFirstWord(std::string(keystr));
			
			songparam->setSongIndex(songidx);
			return 0;
		}
	}
	return -1;	
}
int ReqMICEDB::getFavoInsertIDBySongIndex(int songIndex)
{
	int ret = -1;	
	int insertId = 0;
	TABLE_HANDLE* table = NULL;
	FILTER_PARAM filter;
	
	if (m_HandleFavoEDB == NULL){
		m_HandleFavoEDB = DBOpen((DB_UINT8 *)(m_FavoEDBPath.c_str()),DB_READ_ONLY);
		if (m_HandleFavoEDB != NULL){
			table = TableOpen(m_HandleFavoEDB,(DB_UINT8*)(ReqTableName::TableFavo.c_str()),DB_READ_ONLY);
		}
	}
	if ((table != NULL)&&(table->TableHead->RecNum>0)){
		
		memset(&filter,0,sizeof(filter));
		strcpy((char *)filter.KeyName,(ReqTableName::KEY_SONG_SONGIDX).c_str());
		filter.Reset = 1;
		filter.SelMod = FILTER_MODE_EQUAL;
		setIntFilter(&filter,songIndex,songIndex,KeyGetLenByName(table,(DB_UINT8 *)(ReqTableName::KEY_SONG_SONGIDX).c_str()));

		if (filter.Reset) {
	        TableFilterReset(table);
	    }

	    ret = TableFilter(m_HandleFavoEDB, table, filter.KeyName, (DB_UINT8 *)(filter.V1), (DB_UINT8 *)(filter.V2));
		if (ret == ERR_NONE && table->Filter.RecNum>0)
			KeyGetValue(m_HandleFavoEDB,table,(DB_UINT8 *)((ReqTableName::KEY_INSERT_ID).c_str()),(DB_UINT8 *)&insertId,GET_KEY_VALUE_MODE_INT);
		TableClose(m_HandleFavoEDB,table);
	}
	if(m_HandleFavoEDB != NULL){
		DBClose(m_HandleFavoEDB);
		m_HandleFavoEDB = NULL;
	}
	
	return insertId;
	
}

int ReqMICEDB::getProgInsertIDByResultPos(int position)
{
	int insertid = 0;
	std::list<int>::iterator searchid;
	if ((position>=0) && (position<m_ProgSongInsertList.size())){
		searchid = m_ProgSongInsertList.begin();
		for(int i=position;i>0;i--)
		{
			searchid++;
			if (searchid == m_ProgSongInsertList.end())
				break;
		}
		if (searchid != m_ProgSongInsertList.end())
			insertid = *searchid;
	}
	return insertid;
}
int ReqMICEDB::getProgPositionBySongIndex(int songindex)
{
	int songpos = -1;
	std::list<int>::iterator searchid;
	searchid = m_ResultProgSongList.begin();
	while(searchid != m_ResultProgSongList.end()){
		songpos++;
		if(*searchid == songindex)
			break;
		searchid++;
	}
	if (searchid == m_ResultProgSongList.end())
		songpos = -1;
	
	return songpos;
}

int ReqMICEDB::deleteProgSongFormList(int position)
{
	std::list<int>::iterator searchSong;
	if ((position>=0) && (position<m_ResultProgSongList.size())){
		searchSong = m_ResultProgSongList.begin();
		for(int i=position;i>0;i--)
		{
			searchSong++;
			if (searchSong == m_ResultProgSongList.end())
				break;
		}
		if (searchSong != m_ResultProgSongList.end())
			m_ResultProgSongList.erase(searchSong);
	}
	return 0;
}
int ReqMICEDB::deleteProgInsertIdFormList(int position)
{
	std::list<int>::iterator searchid;
	if ((position>=0) && (position<m_ProgSongInsertList.size())){
		searchid = m_ProgSongInsertList.begin();
		for(int i=position;i>0;i--)
		{
			searchid++;
			if (searchid == m_ProgSongInsertList.end())
				break;
		}
		if (searchid != m_ProgSongInsertList.end())
			m_ProgSongInsertList.erase(searchid);
	}
	return 0;
}
int ReqMICEDB::loadPlayModeList(TABLE_HANDLE* table)
{
	int songnum = 0;
	if (table != NULL){
		if (m_PlayModeList.size()>0)
			m_PlayModeList.clear();
		
		 	for(int i=0; i< table->Filter.RecNum; i++){
				int songidx = 0;
				table->Cursor = table->Filter.StartRec+i;
				int ret = KeyGetValue(m_HandleMICEDB, table, (DB_UINT8*)(ReqTableName::KEY_SONG_SONGIDX).c_str(),
						(DB_UINT8*)&songidx, GET_KEY_VALUE_MODE_INT);
				if (ERR_NONE == ret)
					m_PlayModeList.push_back(songidx);
		 	}
		songnum = m_PlayModeList.size();
	}
	return songnum;
}

extern "C" void GetDataBaseManager(InterfaceDataBaseManager *&_dataBaseManager)
{
	_dataBaseManager = ReqMICEDB::GetSingleInstance();
}


