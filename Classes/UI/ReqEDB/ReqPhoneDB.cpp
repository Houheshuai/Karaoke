//----------------------------------------------------------------------------//
// Multak 3D GUI Project
//
// Filename : ReqPhoneDB.cpp
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

//#define MP3_MTV_MOVIE_PATH_IS_SDA2
#define MP3_MTV_MOVIE_PATH_IS_SDA3

#define OUT_FILE_SET_SDA3

//#define USE_COOKARA

#define USE_SDA4
#define USE_SDA2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "M3D_Config.h"
//#include "M3D_Base.h"
#include "appConfig.h"
#include "appKrk.h"

#include "PVRTString.h"
#include "PVRTResourceFile.h"

#include "krkplayer/MCodeConvert.h"

#include "ReqPhoneDB.h"
//#include "MULShellJni.h"
#include "ReqListBuffer.h"

#ifdef WIN32
#include <dos.h>
#include <io.h>
#include <FCNTL.H>
#include "pthread.h"
#include <windows.h>

#else
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <MProfile.h>
#include <pthread.h>
#endif

#if defined(_WIN32) && !defined(__BADA__)
#define snprintf _snprintf
#endif

#define USE_NAME_LEN 128
#define USE_ID_LEN 128
#define MAX_LYRIC_STR_LEN 128
#define MAX_LYRIC_CNT 4

#define multak_max(a,b)            (((a) > (b)) ? (a) : (b))
#define multak_min(a,b)            (((a) < (b)) ? (a) : (b))

#ifdef PLATFORM_UNIX
#include<semaphore.h>
extern sem_t sem_db_query;
extern sem_t mutex_reserved;
#else

//extern HANDLE sem_db_query;
//extern HANDLE mutex_reserved;
#endif

#ifndef WIN32
extern char IP_id[256];
#endif
bool NoUsedCoin = false;
extern		int d_coinType;

static int stricmpn_ex(const char *dst, const char *src, int len)
{
    int ch1, ch2;
    while (len--)
    {
        if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        {
            ch1 += 0x20;
        }
        if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        {
            ch2 += 0x20;
        }
        if (ch1 > ch2)
            return 1;
        else if(ch1 < ch2)
            return -1;
    }
    return 0;
}
extern std::string g_DownloadPath;
namespace CEGUI
{
#ifndef min
#define min(a, b)		((a>b)? b : a)
#endif

extern 		std::vector<std::string> d_sql_cmd;
extern 		std::vector<int> d_reGetBufferFlag; //0: wait; 1: req table; 2: req total;
extern		bool d_revRefreshFlag;
extern		bool d_tisWorking;

static SingerListBindingStruct_t SingerRecDummy = {"", 0, -1, "", -1, -1, 'a', -1};
static SongListBindingStruct_t SongListRecDummy = {-1, -1, -1, -1, -1, -1, -1, -1, -1,-1, "","", "", -1,-1,-1,"",-1,-1,""};
#define SINGER_TYPE_COUNT 5
#define LANGUAGE_COUNT 5
#define VIDEO_SUFFIX_COUNT	22
#define IMG_SUFFIX_COUNT	4
#define MEDIA_SUFFIX_COUNT 16

#define MAX_PATH_LEN	256


const char *VideoFileSuffix[VIDEO_SUFFIX_COUNT] =
{
    ".avi",
    ".mpg",
    ".mpeg",
    ".vob",
    ".dat",
    ".wmv",
    ".divx",
    ".mp4",
    ".rm",
    ".rmvb",
    ".mkv",

    ".AVI",
    ".MPG",
    ".MPEG",
    ".VOB",
    ".DAT",
    ".WMV",
    ".DIVX",
    ".MP4",
    ".RM",
    ".RMVB",
    ".MKV"
};
const char *ImgFileSuffix[IMG_SUFFIX_COUNT] =
{
    ".jpg",
    ".png",

    ".JPG",
    ".PNG"
};
#ifndef WIN32
//----------------------------------------------------------------------------//
int time_sort(const dirent **sort1, const dirent **sort2)
{
    const char *name1;
    const char *name2;
    struct stat st1;
    struct stat st2;
    int rt1;
    int rt2;

    assert(sort1 != NULL && sort2 != NULL);

    //两个文件名
    name1 = (*sort1)->d_name;
    name2 = (*sort2)->d_name;

    //读文件修改时间等信息
    rt1 = stat(name1, &st1);
    rt2 = stat(name2, &st2);

    assert(rt1 == 0 && rt2 == 0);

    return st2.st_mtime - st1.st_mtime;
}
#endif

//----------------------------------------------------------------------------//
void *updateRecordSongInfo(void *param)
{
    ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqPhoneDB::getSingletonPtr();
    if(reqDB)
    {
        sqlite3* dbhandle;
        if(sqlite3_open(reqDB->getDbPath(), &dbhandle) != SQLITE_OK)
            return (void*)0;
        reqDB->ReqRecordSongInfo(dbhandle);
        sqlite3_close(dbhandle);
        return (void*)1;
    }
    return (void*)0;
}

//----------------------------------------------------------------------------//
ReqPhoneDB::ReqPhoneDB(void* dbFile, int para) : ReqDB(dbFile, para),d_maxRecTotalIdx(0)
    ,d_BroadResFlag(false),d_noCoinTimeFlag(NO_COIN_MODE_NONE)
{
    d_lockReqSonginf = (pthread_mutex_t *)(new pthread_mutex_t);
    pthread_mutex_init((pthread_mutex_t *)d_lockReqSonginf, NULL);
    d_RecThreadLock = new pthread_mutex_t;
    pthread_mutex_init(d_RecThreadLock, NULL);

    int ret;
    orderplayflag = 0;
    d_netState = 0;
    d_custid = "";
    d_rootDeviceId = 0;
    d_deviceIdMap.clear();
    d_deviceList.clear();
    d_deviceMaxID = 0;
    d_songIdx = 0;
    d_RecThreadMode = REC_THREAD_MODE_NONE;
    d_deviceNameMap.clear();
    d_recordSong.clear();
    d_SIDMap.clear();

    //add all device (nand first)
    ReqAddDevice();

    ReqCheckDbFile((char*)dbFile);
#if 0
    _getDBCustInfo((char*)dbFile, &d_custverNewest, &d_custid);
#else
    _getDBCustInfo((char*)dbFile, &DBVer, &ProjectID,&ProjectName);
#ifdef USE_COOKARA
    netCooKaraLan::DbInfostatus = 1;
#endif
#endif
    M3D_DebugPrint("(d_rootDeviceId = %d)\n", d_rootDeviceId);
    //ReqUpdateNewDbFile((char*)dbFile);

    d_rootDeviceId = DISC_NAND;
    //d_newestDeviceId = DISC_USER;

    //find root deviceid and newest Db Device id
    //ReqFindRootDeviceAddNewestDevice(&d_rootDeviceId, &d_newestDeviceId);

    M3D_DebugPrint("(d_rootDeviceId = %d)\n", d_rootDeviceId);
    d_dbPath = (char*)dbFile;
    ret = sqlite3_open(d_dbPath.c_str(), &d_db);
    if(ret != SQLITE_OK) //open failed
    {
        M3D_DebugPrint("Open database failed!\n");
    }
    else
        M3D_DebugPrint("open the database successful!\n");

    assert(ret == SQLITE_OK);

#ifdef USE_LIST_BUFFER_FOR_SOME_LIST
    std::string dbBufferPath;
#ifdef OUT_FILE_SET_SDA3
    if(!_getSDA2Path(&dbBufferPath))
    {
#endif
        std::vector<DeviceInfo_st>::iterator iterId = d_deviceList.begin();
        for(; iterId != d_deviceList.end(); iterId++)
        {
            if (iterId->type == DISC_NAND)
                break;
        }
        if(iterId == d_deviceList.end())
        {
            //save in RES dir
            CPVRTString pathT = CPVRTResourceFile::GetReadPath();
            dbBufferPath = pathT.c_str();
        }
        else
        {
            //save in DISC_NAND dir
            dbBufferPath = iterId->path;
            dbBufferPath += M3D_CONFIG_PATH;
        }
#ifdef OUT_FILE_SET_SDA3
    }
    else
        dbBufferPath += M3D_CONFIG_PATH;
#endif

    openDBDataBuffer(dbBufferPath.c_str(), d_dbPath.c_str(), -1);
#endif

    reqSyncLocalDB(NULL);

    //read each SID to d_SIDMap
    //ReqLoadSID();

    //init local prog song
    _loadReservedID();

    //filter each record song to d_recordSong
    ReqLoadRecordSong();

    //load favo songid
    ReqFavoSongLoad();

    //load karoke config to struct
    ReqLoadConfig();

    //load info for MY HOT LIST
    ReqMyHotSongLoad();

    //load bg
    ReqLoadVideo();
    ReqLoadPic();
#ifdef PLAY_MP3_BGV_BY_BGVMP3
    ReqLoadMP3Video();
#endif

    M3D_DebugPrint("ReqPhoneDB::ReqPhoneDB end!!!\n");


    d_ForeignFlag = SONG_SUBTYPE_FOREIGN_OFF;
#ifndef WIN32
    //ProfileLoadIntValue(ENUM_INT_FOREIGN_SONG, &d_ForeignFlag);
#endif
}


//----------------------------------------------------------------------------//
ReqPhoneDB::~ReqPhoneDB(void)
{
    _saveReservedID(false);

    M3D_DebugPrint("~ReqPhoneDB\n");

    //waite for rec pthread end
    if(d_RecThreadMode == REC_THREAD_MODE_START)
    {
        pthread_join(d_RecThreadId, NULL);
        d_RecThreadMode = REC_THREAD_MODE_END;
    }

#if 1
    ReqSaveConfig();

    reqDeInit();
    //reqDeInitSongInf();

#ifdef USE_LIST_BUFFER_FOR_SOME_LIST
    closeDBDataBuffer();
#endif

    pthread_mutex_destroy(d_RecThreadLock);
    delete d_RecThreadLock;
    pthread_mutex_destroy((pthread_mutex_t *)d_lockReqSonginf);
    delete (pthread_mutex_t *)d_lockReqSonginf;

    //ret = sqlite3_close(d_dbLocal);
    //d_dbLocal = NULL;
    //assert(ret == SQLITE_OK);
    d_custid = "";
    d_rootDeviceId = 0;
    //d_newestDeviceId = 0;
    d_deviceIdMap.clear();
    d_deviceList.clear();
    d_deviceMaxID = 0;
    d_deviceNameMap.clear();
    d_recordSong.clear();
    //d_FavoIDSet.clear();
    //d_NetIDSet.clear();
    //d_NetSong.clear();
    d_SIDMap.clear();
    d_vFavoID.clear();

    M3D_DebugPrint("~ReqPhoneDB end\n");

    int ret = sqlite3_close(d_db);
    d_db = NULL;
    assert(ret == SQLITE_OK);

#endif

}

//device		add device
//db		update db to new version
//			set song localdevice
//			sync local db
//record		read recordsong list, add to local recordsong list
//----------------------------------------------------------------------------//

//device		add nand + add device(net)
//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqAddDevice(void)
{
#ifndef WIN32
//#ifdef WIN32

    //std::multimap<int, std::string> * list = (std::multimap<int, std::string> *)(MultakDeviceGet());
    //std::multimap<int, std::string>::iterator iter;
#endif

#ifdef WIN32
    CPVRTString resPath = CPVRTResourceFile::GetReadPath();
    std::string temp = resPath.c_str();
    temp += "../KARAOKE/";
    _addDevice(&temp, DISC_NAND);

    _addDevice(&temp, DISC_BG);
    _addDevice(&temp, DISC_USER);
#else	// houhs add Android Plat
	std::string temp = "/mnt/sda1/Karaoke/";
	_addDevice(&temp, DISC_NAND);
	_addDevice(&temp, DISC_SDCARD);
#endif

#ifndef WIN32
    //M3D_DebugPrint("ReqAddDevice count = %d\n",list->size());
    /*
    if(list->size() > 0)
    {
    	for(iter = list->begin(); iter != list->end(); iter++)
    	{
    		_addDevice(&iter->second, (DiscType_et)(iter->first));
    	}
    }*/
#endif
    return 1;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqDeleteDevice(char *path)
{
    int ret = 0;
#if 0
    ret = _deleteDevice(path);
    if(ret > 0)
    {
        _clearSongTblLocalDevice(ret);
        reqSyncLocalDB(NULL);
    }
#endif
    return ret;
}


//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqFindRootDeviceAddNewestDevice(int *rootDevice, int *newestDevice)
{
#if 0
    int i = 0, j = 0;
    int nrow = 0, ncolumn = 0;
    char * errMsg = NULL;
    int ret = 0;
    std::string custid;
    int custver;
    std::string dbFile;
    M3D_FILE fp;
    int rootDeviceID = 0;
    int newestDeviceID = *newestDevice;
    DiscType_et type;
    std::vector<int> newestDeviceList;


    newestDeviceList.clear();

    if(appCfg::appCfgGet(appCfg::CFGTYPE_PRIORITY_DISC) == appCfg::CFGPRIORITY_USB)
        type = DISC_USER;
    else
        type = DISC_NAND;


    //find first db, exept nand & net
    std::vector<DeviceInfo_st>::iterator iter;
    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        if(iter->type != DISC_NONE)
        {
            if((iter->type != DISC_NAND) && (iter->type != DISC_NET))
            {
                dbFile = iter->path + M3D_SONG_PATH;
                dbFile += M3D_DATABASE_FILE_NAME;

                fp = M3D_fopen((char *)(dbFile.c_str()),M3D_OM_RD);
                if(fp != NULL)
                {
                    M3D_fclose(fp);

                    _getDBCustInfo((char *)(dbFile.c_str()), &custver, &custid);
                    if(custid == d_custid)
                    {
                        if(rootDeviceID == 0)
                        {
                            if(iter->type == type)
                                rootDeviceID = iter->id;
                            else
                                rootDeviceID = -iter->id;
                        }
                        else if(rootDeviceID < 0)
                        {
                            if(iter->type == type)
                                rootDeviceID = iter->id;
                        }

                        if(custver > d_custverNewest)
                        {
                            d_custverNewest = custver;
                            newestDeviceID = iter->id;
                            newestDeviceList.clear();
                            newestDeviceList.push_back(iter->id);
                        }
                        else if(custver == d_custverNewest)
                        {
                            newestDeviceList.push_back(iter->id);
                        }
                    }
                }
            }
        }
    }

    //no correct db
    if(rootDeviceID == 0)
    {
        //find first device equle type
        for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
        {
            M3D_DebugPrint("iter->type = %d\n", iter->type);
            if(iter->type == type)
            {
                rootDeviceID = iter->id;
                break;
            }
        }
        if(rootDeviceID == 0)
        {
            //find first device except nand & net
            for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
            {
                if((iter->type != DISC_NAND) && (iter->type != DISC_NET))
                {
                    rootDeviceID = iter->id;
                    break;
                }
            }
        }

        //no extend device
        if(rootDeviceID == 0)
        {
            //no root device
            M3D_DebugPrint("no root device!!!!!!!\n");
        }
    }

    if(rootDeviceID < 0)
        rootDeviceID = -rootDeviceID;

    //if rootDevice ver == newest, newest = rootID
    for(int i = 0; i < newestDeviceList.size(); i++)
    {
        if(newestDeviceList[i] == rootDeviceID)
        {
            newestDeviceID = rootDeviceID;
            break;
        }
    }

    *rootDevice = rootDeviceID;
    *newestDevice = newestDeviceID;
#endif
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqUpdatetoNewVersion(int newestDeviceId)
{
    std::string newestDevicePath;

    M3D_DebugPrint("ReqUpdatetoNewVersion, newestDeviceId = %d\n", newestDeviceId);
    if(newestDeviceId != d_rootDeviceId)
    {
        if(_getDevicePath(newestDeviceId, &newestDevicePath))
        {
            newestDevicePath += M3D_SONG_PATH;
            newestDevicePath += M3D_DATABASE_FILE_NAME;
            _updateDBtoNewVersion((char *)newestDevicePath.c_str());
        }
    }

    return 1;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqUpdateNewDbFile(char *dbFile)
{
    std::string newFilePath;
    std::string tempFilePath;
    M3D_FILE fp;
    std::string	custid;
    int	custverNewest = 0;
    bool ret = false;

    newFilePath = dbFile;
    newFilePath += ".new";
    tempFilePath = dbFile;
    tempFilePath += ".temp";

    fp = M3D_fopen((char *)(newFilePath.c_str()), "rb");
    if(fp != NULL)
    {
        M3D_fclose(fp);
#if 0
        _getDBCustInfo((char*)dbFile, &d_custverNewest, &d_custid);
#else
        _getDBCustInfo((char*)dbFile, &DBVer, &ProjectID,&ProjectName);
#endif

        if((custid == d_custid) || (custverNewest > d_custverNewest))
        {
            M3D_fremove((char *)tempFilePath.c_str());
            fileRename(dbFile, (char *)tempFilePath.c_str());
            fileRename((char *)newFilePath.c_str(), dbFile);
            d_custverNewest = custverNewest;
            ret = true;
        }
        else
            M3D_fremove((char *)newFilePath.c_str());
    }


    return ret;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqCheckDbFile(char *dbFile)
{
    std::string tempFilePath;
    M3D_FILE fp;

    tempFilePath = dbFile;
    tempFilePath += ".temp";

    fp = M3D_fopen(dbFile, "rb");
    if(fp == NULL)
    {
        fp = M3D_fopen((char *)tempFilePath.c_str(), "rb");
        if(fp != NULL)
        {
            M3D_fclose(fp);
            fileRename((char *)tempFilePath.c_str(), dbFile);
        }
    }
    else
        M3D_fclose(fp);
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqRecordSongInfo(sqlite3* dbhandle)	//do it only once
{
    pthread_mutex_lock(d_RecThreadLock);

    //check d_recordSong info
    std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin();
    //std::vector<RecordSongInfo_st>::iterator iterTmp;
    std::vector<int> vTmpRecord;
    if(dbhandle == NULL)
    {
        SongListBindingStruct_t song;
        for(; iter != d_recordSong.end(); iter++)
        {
            song.SongIndex = iter->SongIndex;
            if(_reqSongInf(song) == 0)
            {
                vTmpRecord.push_back(iter->SongIndex);
            }
            else
            {
                iter->OrderIndex = song.OrderIndex;
                iter->FileType = song.FileType;
                iter->SubFileType = song.MediaType;
                strncpy(iter->SongName, song.SongName, sizeof(iter->SongName));
            }
        }
    }
    else
    {
        sqlite3_stmt* stmt;
        char sql_cmd[SQL_STR_SZ_S];
        for(; iter != d_recordSong.end(); iter++)
        {
            sprintf(sql_cmd, "SELECT OrderIndex, FileType, SubFileType, SongName FROM TableSong WHERE SongIndex = %d;", iter->SongIndex);
            if(sqlite3_prepare_v2(dbhandle, sql_cmd, strlen(sql_cmd), &stmt, NULL) != SQLITE_OK)
                break;

            if(sqlite3_step(stmt) == SQLITE_ROW)
            {
                iter->OrderIndex = sqlite3_column_int(stmt, 0);
                iter->FileType = sqlite3_column_int(stmt, 1);
                iter->SubFileType = sqlite3_column_int(stmt, 2);
                strncpy(iter->SongName, (char*)sqlite3_column_text(stmt, 3), sizeof(iter->SongName));
            }
            else
            {
                vTmpRecord.push_back(iter->SongIndex);
            }
            sqlite3_finalize(stmt);
        }
    }

    //delete
    if(vTmpRecord.size() > 0)
    {
        std::vector<int>::iterator viTmpDel = vTmpRecord.begin();
        int tmpSongId;
        std::string recFile;

        for(; viTmpDel != vTmpRecord.end(); viTmpDel++)
        {
            tmpSongId = *viTmpDel;
            for(iter=d_recordSong.begin(); iter != d_recordSong.end(); iter++)
            {
                if(iter->SongIndex == tmpSongId)
                    break;
            }
            if(iter == d_recordSong.end())
            {
                continue;
            }

            //delete file and vector
            //remove REC FILE
            if(ReqRecordSongGetFilePath(iter->SongIndex, iter->RecIndex, iter->DeviceId, NULL, &recFile,iter->username,iter->userid,iter->rectotalidx))
                M3D_fremove(recFile.c_str());
            //remove record
            d_recordSong.erase(iter);
        }
    }

    pthread_mutex_unlock(d_RecThreadLock);
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqLoadRecordSong(void)
{
    std::string path;

    M3D_DebugPrint("ReqLoadRecordSong\n");
    pthread_mutex_lock(d_RecThreadLock);
    d_recordSong.clear();
    pthread_mutex_unlock(d_RecThreadLock);

#ifndef OUT_FILE_SET_SDA3
    std::map<int, std::string>::iterator iter;
    if(d_deviceIdMap.size() > 0)
    {
        for(iter = d_deviceIdMap.begin(); iter != d_deviceIdMap.end(); iter++)
        {
            if(iter->first == 1)
            {
                path = iter->second + M3D_RECORDSONG_PATH;
                pthread_mutex_lock(d_RecThreadLock);
                _filterRecordSongToList((char *)path.c_str(), &d_recordSong, iter->first);
                pthread_mutex_unlock(d_RecThreadLock);
            }
        }
    }
#else
    if(_getSDA3Path(&path))
    {
        path += M3D_RECORDSONG_PATH;
        pthread_mutex_lock(d_RecThreadLock);
        _filterRecordSongToList((char *)path.c_str(), &d_recordSong, 3);
        pthread_mutex_unlock(d_RecThreadLock);
    }
#endif

    //create a pthread for update record song info
    //pthread_t d_RecThreadId;
    if(pthread_create(&d_RecThreadId, NULL, updateRecordSongInfo, NULL) == 0)
    {
        d_RecThreadMode = REC_THREAD_MODE_START;
    }
    else
    {
        //pthread create failed
        //update record song info manually
        ReqRecordSongInfo();
    }

    pthread_mutex_lock(d_RecThreadLock);
    for(int i = 0; i < d_recordSong.size(); i++)
    {
        M3D_DebugPrint("REC: -%d- %d, %d", i, d_recordSong[i].SongIndex, d_recordSong[i].RecIndex);
    }
    pthread_mutex_unlock(d_RecThreadLock);
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqLoadConfig(void)
{
#ifndef OUT_FILE_SET_SDA3
    std::string path, path_nand;

    M3D_DebugPrint("ReqLoadConfig\n");
    _getDevicePath(1, &path_nand);
    appCfg::appCfgLoad((char *)path_nand.c_str());

    if(_getDevicePath(d_rootDeviceId, &path))
    {
        appCfg::appCfgLoadKaraoke(&path, &path_nand);
    }
#else
    std::string path;
    M3D_DebugPrint("ReqLoadConfig\n");

    if(_getSDA2Path(&path))
    {
        //	appCfg::appCfgLoad((char *)path.c_str());
        //	appCfg::appCfgLoadKaraoke(&path, &path);
    }
    else
        M3D_DebugPrint("ReqLoadConfig ***ERROR***!!!\n");
#endif
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqSaveConfig(void)
{
    M3D_DebugPrint("ReqSaveConfig\n");

//	appCfg::appCfgSave();
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqLoadVideo(void)
{
    std::vector<DeviceInfo_st>::iterator iter;
    std::string path;

    M3D_DebugPrint("ReqLoadVideo\n");
    d_videoFileList.clear();
    d_videoFileList_nand.clear();

    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        path = iter->path + M3D_BGV_PATH;
        if(iter->type == DISC_BG)
            _filterFileToList((char *)path.c_str(), &d_videoFileList_nand, iter->id, iter->type, 1);
        else if(iter->type == DISC_USER)
            _filterFileToList((char *)path.c_str(), &d_videoFileList, iter->id, iter->type, 1);
    }
}

#ifdef PLAY_MP3_BGV_BY_BGVMP3
//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqLoadMP3Video(void)
{
    std::vector<DeviceInfo_st>::iterator iter;
    std::string path;

    M3D_DebugPrint("ReqLoadMP3Video\n");
    d_MP3videoFileList.clear();
    d_MP3videoFileList_nand.clear();

    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        path = iter->path + M3D_BGVMP3_PATH;
        if(iter->type == DISC_BG)
            _filterFileToList((char *)path.c_str(), &d_MP3videoFileList_nand, iter->id, iter->type, 1);
        else if(iter->type == DISC_USER)
            _filterFileToList((char *)path.c_str(), &d_MP3videoFileList, iter->id, iter->type, 1);
    }
}
#endif

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqLoadPic(void)
{
    std::vector<DeviceInfo_st>::iterator iter;
    std::string path;

    M3D_DebugPrint("ReqLoadPic\n");
    d_picFileList.clear();
    d_picFileList_nand.clear();

    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        path = iter->path + M3D_PIC_PATH;
        if(iter->type == DISC_BG)
            _filterFileToList((char *)path.c_str(), &d_picFileList_nand, iter->id, iter->type, 2);
        else if(iter->type == DISC_USER)
            _filterFileToList((char *)path.c_str(), &d_picFileList, iter->id, iter->type, 2);
    }
}


//----------------------------------------------------------------------------//
int ReqPhoneDB::_addDevice(std::string *path, DiscType_et type)
{
    int ret;

    ret = _addDeviceName(path);
    if(ret !=0)
    {
        DeviceInfo_st temp;

        temp.id = ret;
        temp.path = *path;
        temp.type = type;
        d_deviceList.push_back(temp);
    }

    M3D_DebugPrint("_addDevice path = %s, type = %d, id = %d\n",path->c_str(), type, ret);
    return ret;
}

//----------------------------------------------------------------------------//
//return add device ID,  ret <= 0:fail
int ReqPhoneDB::_addDeviceName(std::string *path)
{
    int ret = 0;
    std::string device = *path;

    if(path != NULL)
    {
        if(path->length() >0)
        {
            if(d_deviceNameMap.size() < MAX_KARAOKE_DEVICE_COUNT)
            {
                //check if has existed, add
                std::map<std::string, int>::const_iterator iter = d_deviceNameMap.find(device);
                if(iter == d_deviceNameMap.end())
                {
                    ++d_deviceMaxID;
                    d_deviceNameMap.insert(make_pair(device, d_deviceMaxID));

                    d_deviceIdMap.insert(make_pair(d_deviceMaxID, device));
                    ret = d_deviceMaxID;
                }
                else
                {
                    ret = iter->second;
                }
            }
        }
    }

    return ret;
}

//----------------------------------------------------------------------------//
//return delete device ID, ret == 0:fail
bool ReqPhoneDB::_getDevicePath(int deviceID, std::string *path)
{
    bool ret = false;

    if(path != NULL)
    {
        if(d_deviceNameMap.size() > 0)
        {
            //check if has existed, add
            std::map<int, std::string>::iterator iter = d_deviceIdMap.find(deviceID);
            if(iter != d_deviceIdMap.end())
            {
                *path = iter->second;
                ret = true;
            }
        }
    }

    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::_getSDA3Path(std::string *path)
{
    std::vector<DeviceInfo_st>::iterator iter;

    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        if(iter->type == DISC_BG)
        {
            *path = iter->path;
            return true;
        }
    }

    return false;
}


bool ReqPhoneDB::_getSDA2Path(std::string *path)
{
    std::vector<DeviceInfo_st>::iterator iter;

    for(iter = d_deviceList.begin(); iter != d_deviceList.end(); iter++)
    {
        if(iter->type == DISC_USER)
        {
            *path = iter->path;
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------------//
//get custid, custver
int ReqPhoneDB::_getDBCustInfo(char * dbFile, int *dbver, int *Projectid,std::string *ProjectName)
{
    char sql_cmd[SQL_STR_SZ];
    int nrow = 0, ncolumn = 0;
    char **azResult; //save inquire result from db
    char * errMsg = NULL;
    int i = 0, j = 0;
    int ret = 0;
    M3D_FILE fp;
    sqlite3* db;

    fp = M3D_fopen(dbFile, M3D_OM_RD);
    if(fp != NULL)
    {
        M3D_fclose(fp);

        ret = sqlite3_open(dbFile, &db);
        if(ret != SQLITE_OK) //open failed
        {
            M3D_DebugPrint("Open database failed!\n");
        }
        else
            M3D_DebugPrint("open the database successful!\n");

        assert(ret == SQLITE_OK);

        if(db != NULL)
        {
            memset(sql_cmd, 0, sizeof(sql_cmd));
            if (checkSQLExist(REQDB_SQL_CUSTINFO))
            {
                M3D_DebugPrint("open the database successful 1111\n");
                sprintf(sql_cmd, "%s", getSQLString(REQDB_SQL_CUSTINFO));
                assert(strlen(sql_cmd) < SQL_STR_SZ);
                sqlite3_get_table(db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);

                if (nrow)
                {

                    M3D_DebugPrint("open the database successful 2222\n");
                    //if((nrow < 1)||(ncolumn < 2))
                    //	_ASSERTE(0);

                    *Projectid = atoi(azResult[1*ncolumn+0]);
                    *dbver = atoi(azResult[1*ncolumn+1]);
                    *ProjectName = azResult[1*ncolumn+2];

                    ret = 1;

                    M3D_DebugPrint("ProjectName = %s, dbver = %d, Projectid = %d\n", ProjectName->c_str(), *dbver,*Projectid);
                }
                if (errMsg != NULL)
                    sqlite3_free(errMsg);
                sqlite3_free_table((char **)azResult);
            }
            ret = sqlite3_close(db);
        }
        else
        {
            assert(0);
        }
    }


    return ret;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::_updateDBtoNewVersion(char* dbPathNew)
{
    int ret = 0;
    std::string dbPathBack;
    std::string custid;


    M3D_DebugPrint("_updateDBtoNewVersion from %s to %s\n", dbPathNew, (char *)d_dbPath.c_str());

    //open new db
    if (dbPathNew != NULL)
    {
        //backup
        dbPathBack = d_dbPath + ".bak";
        M3D_fremove((char *)dbPathBack.c_str());
        fileRename((char *)d_dbPath.c_str(), (char *)dbPathBack.c_str());
        M3D_fremove((char *)d_dbPath.c_str());
        //copy dbPathNew to db
        fileCopy(dbPathNew, (char *)d_dbPath.c_str());

        ret = 1;
    }

    return ret;
}


//----------------------------------------------------------------------------//
int ReqPhoneDB::_loadSIDToMap(char *dbFile, std::map<int, int>*map, int deviceId)
{
    char sql_cmd[SQL_STR_SZ];
    int nrow = 0, ncolumn = 0;
    char * errMsg = NULL;
    int i = 0, j = 0;
    int ret = 0;
    sqlite3* db;
    sqlite3_stmt *stmt;
    M3D_FILE fp;
    int songid;

    fp = M3D_fopen(dbFile, M3D_OM_RD);
    if(fp != NULL)
    {
        M3D_fclose(fp);
    }
    else
        return 0;

    ret = sqlite3_open(dbFile, &db);
    if(ret != SQLITE_OK) //open failed
    {
        M3D_DebugPrint("Open database failed!\n");
    }
    else
        M3D_DebugPrint("open the database successful!\n");

    assert(ret == SQLITE_OK);

    if(db != NULL)
    {
        memset(sql_cmd, 0, sizeof(sql_cmd));
        if (checkSQLExist(REQDB_SQL_SID))
        {
            sprintf(sql_cmd, "%s",(char *)getSQLString(REQDB_SQL_SID));
            assert(strlen(sql_cmd) < SQL_STR_SZ);

            ret= sqlite3_prepare_v2(db, sql_cmd, strlen(sql_cmd), &stmt, 0);
            if(ret != SQLITE_OK)
            {
                M3D_DebugPrint("Can't open statement: %s/n", sqlite3_errmsg(db));
            }
            else
            {
                while(sqlite3_step(stmt)==SQLITE_ROW )
                {
                    songid = sqlite3_column_int(stmt, 0);
#ifndef WIN32
//???					map->insert(make_pair(songid, deviceId));
#endif
                }
                sqlite3_finalize(stmt);
            }
        }
    }
    else
    {
        assert(0);
    }

    sqlite3_close(db);

    return 1;
}


//----------------------------------------------------------------------------//
void ReqPhoneDB::_loadReservedID(void)
{
    FILE *fp;
    unsigned int uitemp;
    int itemp;
    char username[USE_NAME_LEN];
    char userid[USE_ID_LEN];
    char songname[BINDING_SONGNAME_LEN];
    ReservInfo_st songinfo;
    int ret = 1;

#ifndef OUT_FILE_SET_SDA3
    CPVRTString path = CPVRTResourceFile::GetReadPath();
#else
    std::string path;
    if(!_getSDA2Path(&path))
        return;
    path += M3D_CONFIG_PATH;
#endif
    path += M3D_CONFIG_PROG_ID_FILE;

    fp = fopen(path.c_str(), "rb");
    if(fp != NULL)
    {
        while(fread(&uitemp, 1, sizeof(unsigned int), fp) ==  sizeof(unsigned int))
        {
            memset(songinfo.SongName, 0, sizeof(songinfo.SongName));
            memset(songinfo.FirstWord, 0, sizeof(songinfo.FirstWord));
            M3D_DebugPrint("progId = %d\n",uitemp);

            songinfo.SongIndex = uitemp;
            memset(username, 0, USE_NAME_LEN);
            fread(username, sizeof(char), USE_NAME_LEN, fp);
            songinfo.username = username;
            memset(userid, 0, USE_ID_LEN);
            fread(userid, sizeof(char), USE_ID_LEN, fp);
            songinfo.userid = userid;
            fread(&uitemp, 1, sizeof(unsigned int), fp);
            songinfo.randomNum = uitemp;

            fread(&itemp, 1, sizeof(int), fp);
            songinfo.FileType = itemp;
            fread(&itemp, 1, sizeof(int), fp);
            songinfo.SubFileType = itemp;
            fread(&itemp, 1, sizeof(int), fp);
            songinfo.OrderIndex = itemp;
            memset(songname, 0, BINDING_SONGNAME_LEN);
            fread(songname, BINDING_SONGNAME_LEN, sizeof(char), fp);
            strncpy(songinfo.SongName, songname, BINDING_SONGNAME_LEN);
            memset(songname, 0, BINDING_SONGNAME_LEN);
            if(fread(songname, 1, BINDING_SONGNAME_LEN, fp) != BINDING_SONGNAME_LEN)
            {
                ret = 0;
                break;
            }
            strncpy(songinfo.FirstWord, songname, BINDING_SONGNAME_LEN);

            //push_back
            d_reservedSong.push_back(songinfo);
        }
        fclose(fp);
        if(ret == 0)
            M3D_fremove(path.c_str());
    }
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::_saveReservedID(bool flag)
{
    FILE *fp;
    unsigned int uitemp;
    int itemp;
    char username[USE_NAME_LEN];
    char userid[USE_ID_LEN];
    char songName[BINDING_SONGNAME_LEN];

#ifndef OUT_FILE_SET_SDA3
    CPVRTString path = CPVRTResourceFile::GetReadPath();
#else
    std::string path;
    if(!_getSDA2Path(&path))
        return;
    path += M3D_CONFIG_PATH;
#endif
    path += M3D_CONFIG_PROG_ID_FILE;

    M3D_DebugPrint("_saveReservedID size %d \n", d_reservedSong.size());
    fp = fopen(path.c_str(), "wb");
    if(fp != NULL)
    {
        for(int i=0; i < d_reservedSong.size(); i++)
        {
            uitemp = d_reservedSong.at(i).SongIndex;
            fwrite(&uitemp, 1, sizeof(unsigned int), fp);
            memset(username, 0, USE_NAME_LEN);
            strncpy(username, (char *)d_reservedSong.at(i).username.c_str(), USE_NAME_LEN);
            fwrite(username, USE_NAME_LEN, sizeof(char), fp);
            memset(userid, 0, USE_NAME_LEN);
            strncpy(userid, (char *)d_reservedSong.at(i).userid.c_str(), USE_ID_LEN);
            fwrite(userid, USE_ID_LEN, sizeof(char), fp);
            uitemp = d_reservedSong.at(i).randomNum;
            fwrite(&uitemp, 1, sizeof(unsigned int), fp);

            itemp = d_reservedSong.at(i).FileType;
            fwrite(&itemp, 1, sizeof(int), fp);
            itemp = d_reservedSong.at(i).SubFileType;
            fwrite(&itemp, 1, sizeof(int), fp);
            itemp = d_reservedSong.at(i).OrderIndex;
            fwrite(&itemp, 1, sizeof(int), fp);
            memset(songName, 0, BINDING_SONGNAME_LEN);
            strncpy(songName, d_reservedSong.at(i).SongName, BINDING_SONGNAME_LEN);
            fwrite(songName, BINDING_SONGNAME_LEN, sizeof(char), fp);
            memset(songName, 0, BINDING_SONGNAME_LEN);
            strncpy(songName, d_reservedSong.at(i).FirstWord, BINDING_SONGNAME_LEN);
            fwrite(songName, BINDING_SONGNAME_LEN, sizeof(char), fp);
        }
        fclose(fp);
#ifndef WIN32
        system("sync");
#endif
    }
    if(flag)
        d_BroadResFlag = true;
}

//----------------------------------------------------------------------------//
//filter folder
void ReqPhoneDB::_filterRecordSongToList(char *path, std::vector<RecordSongInfo_st>*list, int deviceId)
{
    RecordSongInfo_st temp = {0, 0, 0,"","", 0,   -1,-1,-1,""};
    std::string p_path;
    std::string file_name, str_temp;
    std::string::size_type pos;

    if(list->size() >= RECORDSONG_MAX_NUM)
        return;

    p_path = path;

#ifdef WIN32
    intptr_t DirID;
    struct _finddata_t DirInfo;
    int checki;

    p_path += "*";
    DirID = _findfirst((char *)p_path.c_str(), &DirInfo);
    if (DirID == -1)
    {
        return;
    }
    do
    {
        if (strcmp (DirInfo.name, ".") == 0 || strcmp (DirInfo.name, "..") == 0)
            continue;
        if(strcmp (DirInfo.name, "LOST.DIR") == 0 || strcmp (DirInfo.name, ".LOST.DIR") == 0)
            continue;

        if (strlen(DirInfo.name) < MAX_PATH_LEN)
        {
            if(list->size() >= RECORDSONG_MAX_NUM)
                break;

            //check if file is req?
            if(!(DirInfo.attrib & FILE_ATTRIBUTE_DIRECTORY))
            {
                file_name = DirInfo.name;
                pos = file_name.rfind(M3D_RECORDFILE_SUFFIXAL);
                if(pos != file_name.size()- strlen(M3D_RECORDFILE_SUFFIXAL))
                    continue;

                //userid
                file_name.erase(file_name.size()-strlen(M3D_RECORDFILE_SUFFIXAL), strlen(M3D_RECORDFILE_SUFFIXAL));
                pos = file_name.rfind(".");
                if (pos == std::string::npos)
                    continue;
                str_temp = file_name.substr(pos+1);
                temp.userid = str_temp;
                //M3D_DebugPrint("temp.userid = %s",temp.userid.c_str());

                //recindex
                file_name.erase(pos, str_temp.size()+1);
                pos = file_name.rfind(".");
                if (pos == std::string::npos)
                    continue;
                str_temp = file_name.substr(pos+1);
                temp.RecIndex = atoi((char *)str_temp.c_str());

                //songid
                file_name.erase(pos, str_temp.size()+1);
                pos = file_name.rfind(".");
                if (pos == std::string::npos)
                    continue;
                str_temp = file_name.substr(pos+1);
                temp.SongIndex = atoi((char *)str_temp.c_str());

                //record index
                file_name.erase(pos, str_temp.size()+1);
                pos = file_name.rfind(".");
                if (pos != std::string::npos)
                    continue;
                temp.rectotalidx = atoi((char *)file_name.c_str());

                //device id
                temp.DeviceId = deviceId;

                //list->push_back(temp);
                if (list->size() > 0)
                {
                    if(d_maxRecTotalIdx == temp.rectotalidx)
                        continue;
                    else if(d_maxRecTotalIdx > temp.rectotalidx)
                    {
                        for(checki = 0; checki < list->size(); checki++)
                        {
                            if(list->at(checki).rectotalidx < temp.rectotalidx)
                                break;
                        }
                        if(checki == list->size())
                            list->push_back(temp);
                        else
                            list->insert(list->begin() + checki , 1, temp);
                    }
                    else
                    {
                        d_maxRecTotalIdx = temp.rectotalidx;
                        list->insert(list->begin(), 1, temp);
                    }
                }
                else
                {
                    d_maxRecTotalIdx = temp.rectotalidx;
                    list->push_back(temp);
                }
            }
        }
    }
    while(_findnext(DirID, &DirInfo) == 0);

    _findclose(DirID);

#else
    DIR *dirp = NULL;
    struct dirent *ptr;
    struct	 stat	statbuf;
    int checki;

    //M3D_DebugPrint("zhaolj ReqRemoteGetMediaItemList 1	opendir root filePath = %s\n",p_path.c_str());
    if((dirp = opendir((char *)p_path.c_str())) == NULL)
    {
        M3D_DebugPrint("_filterRecordSongToList 1	opendir fail\n");
        return;
    }
    else
    {
        while (NULL != (ptr = readdir(dirp)))
        {
            if (strcmp (ptr->d_name, ".") == 0 || strcmp (ptr->d_name, "..") == 0)
                continue;
            if(strcmp (ptr->d_name, "LOST.DIR") == 0 || strcmp (ptr->d_name, ".LOST.DIR") == 0)
                continue;

            if (strlen(ptr->d_name) < MAX_PATH_LEN)
            {
                if(list->size() >= RECORDSONG_MAX_NUM)
                    break;

                //check if file is req?
                p_path = path;
                p_path += "/";
                p_path += ptr->d_name;
                if(lstat((char *)p_path.c_str(), &statbuf) != 0)
                {
                    M3D_DebugPrint("_filterRecordSongToList find file ptr->d_name  = %s, statbuf.st_mode get fail\n",(char *)p_path.c_str());
                    continue;
                }
                else
                {
                    if(S_ISDIR(statbuf.st_mode))
                        continue;

                    file_name = ptr->d_name;
                    pos = file_name.rfind(M3D_RECORDFILE_SUFFIXAL);
                    if(pos != file_name.size()- strlen(M3D_RECORDFILE_SUFFIXAL))
                        continue;

                    //userid
                    file_name.erase(file_name.size()-strlen(M3D_RECORDFILE_SUFFIXAL), strlen(M3D_RECORDFILE_SUFFIXAL));
                    pos = file_name.rfind(".");
                    if (pos == std::string::npos)
                        continue;
                    str_temp = file_name.substr(pos+1);
                    temp.userid = str_temp;
                    //M3D_DebugPrint("temp.userid = %s",temp.userid.c_str());

                    //recindex
                    file_name.erase(pos, str_temp.size()+1);
                    pos = file_name.rfind(".");
                    if (pos == std::string::npos)
                        continue;
                    str_temp = file_name.substr(pos+1);
                    temp.RecIndex = atoi((char *)str_temp.c_str());

                    //songid
                    file_name.erase(pos, str_temp.size()+1);
                    pos = file_name.rfind(".");
                    if (pos == std::string::npos)
                        continue;
                    str_temp = file_name.substr(pos+1);
                    temp.SongIndex = atoi((char *)str_temp.c_str());

                    //record index
                    file_name.erase(pos, str_temp.size()+1);
                    pos = file_name.rfind(".");
                    if (pos != std::string::npos)
                        continue;
                    temp.rectotalidx = atoi((char *)file_name.c_str());

                    //device id
                    temp.DeviceId = deviceId;

                    //list->push_back(temp);
                    if (list->size() > 0)
                    {
                        if(d_maxRecTotalIdx == temp.rectotalidx)
                            continue;
                        else if(d_maxRecTotalIdx > temp.rectotalidx)
                        {
                            for(checki = 0; checki < list->size(); checki++)
                            {
                                if(list->at(checki).rectotalidx < temp.rectotalidx)
                                    break;
                            }
                            if(checki == list->size())
                                list->push_back(temp);
                            else
                                list->insert(list->begin() + checki , 1, temp);
                        }
                        else
                        {
                            d_maxRecTotalIdx = temp.rectotalidx;
                            list->insert(list->begin(), 1, temp);
                        }
                    }
                    else
                    {
                        d_maxRecTotalIdx = temp.rectotalidx;
                        list->push_back(temp);
                    }
                }
            }
        }
        closedir(dirp);
    }
#endif
}

//----------------------------------------------------------------------------//
//filter folder
void ReqPhoneDB::_filterFileToList(char *path, std::vector<FileInfo_st>*list, int deviceId, DiscType_et deviceType, int fileType)
{
    FileInfo_st temp;
    std::string p_path;
    std::string file_name;
    std::string::size_type pos;
    int i;
    char **suffixArray;
    char suffix[10];
    int suffixCount;
    char p[256];

    if(fileType == 1)
    {
        suffixArray = (char **)VideoFileSuffix;
        suffixCount = VIDEO_SUFFIX_COUNT;
    }
    else if(fileType == 2)
    {
        suffixArray = (char **)ImgFileSuffix;
        suffixCount = IMG_SUFFIX_COUNT;
    }

    p_path = path;

#ifdef WIN32
    intptr_t DirID;
    struct _finddata_t DirInfo;

    memset(p, 0, sizeof(p));
    MCodeConvert_UTF8toGB2312(path, p, strlen(path),sizeof(p));
    p_path = p;

    p_path += "*";
    DirID = _findfirst((char *)p_path.c_str(), &DirInfo);
    if (DirID == -1)
    {
        return;
    }
    do
    {
        if (strcmp (DirInfo.name, ".") == 0 || strcmp (DirInfo.name, "..") == 0)
            continue;
        if(strcmp (DirInfo.name, "LOST.DIR") == 0 || strcmp (DirInfo.name, ".LOST.DIR") == 0)
            continue;

        if (strlen(DirInfo.name) < MAX_PATH_LEN)
        {
            //check if file is req?
            if(!(DirInfo.attrib & FILE_ATTRIBUTE_DIRECTORY))
            {
                //songname.songnum.recindex.mp3
                file_name = DirInfo.name;
                memset(suffix, 0, sizeof(suffix));
                for(i = 0; i < suffixCount; i++)
                {
                    pos = file_name.rfind(suffixArray[i]);
                    if(pos != file_name.size()- strlen(suffixArray[i]))
                        continue;
                    else
                    {
                        strcpy(suffix, suffixArray[i]);
                        break;
                    }
                }
                if(strlen(suffix) == 0)
                    continue;

                memset(p, 0, sizeof(p));
                MCodeConvert_GB2312toUTF8(DirInfo.name, p, strlen(DirInfo.name),sizeof(p));

                temp.FileName = p;
                temp.DeviceId = deviceId;


                list->push_back(temp);
            }
        }
    }
    while(_findnext(DirID, &DirInfo) == 0);

    _findclose(DirID);

#else
    DIR *dirp = NULL;
    struct dirent *ptr;
    struct	 stat	statbuf;


    //M3D_DebugPrint("zhaolj ReqRemoteGetMediaItemList 1	opendir root filePath = %s\n",p_path);
    if((dirp = opendir((char *)p_path.c_str())) == NULL)
    {
        M3D_DebugPrint("_filterRecordSongToList 1	opendir fail\n");
        return;
    }
    else
    {
        while (NULL != (ptr = readdir(dirp)))
        {
            if (strcmp (ptr->d_name, ".") == 0 || strcmp (ptr->d_name, "..") == 0)
                continue;
            if(strcmp (ptr->d_name, "LOST.DIR") == 0 || strcmp (ptr->d_name, ".LOST.DIR") == 0)
                continue;

            if (strlen(ptr->d_name) < MAX_PATH_LEN)
            {
                //check if file is req?
                p_path = path;
                p_path += "/";
                p_path += ptr->d_name;
                if(lstat((char *)p_path.c_str(), &statbuf) != 0)
                {
                    M3D_DebugPrint("_filterRecordSongToList find file ptr->d_name  = %s, statbuf.st_mode get fail\n",(char *)p_path.c_str());
                    continue;
                }
                else
                {
                    if(S_ISDIR(statbuf.st_mode))
                        continue;

                    file_name = ptr->d_name;
                    memset(suffix, 0, sizeof(suffix));
                    for(i = 0; i < suffixCount; i++)
                    {
                        pos = file_name.rfind(suffixArray[i]);
                        if(pos != file_name.size()- strlen(suffixArray[i]))
                            continue;
                        else
                        {
                            strcpy(suffix, suffixArray[i]);
                            break;
                        }
                    }
                    if(strlen(suffix) == 0)
                        continue;

                    temp.FileName = ptr->d_name;
                    temp.DeviceId = deviceId;
                    //M3D_DebugPrint("_filterRecordSongToList add %s\n",(char *)temp.FileName.c_str());

                    list->push_back(temp);
                }
            }
        }
        closedir(dirp);
    }
#endif
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::_reqSongInf(SongListBindingStruct_t& song,bool isReserved)
{
    int ret = 0;
    if (ReqDB::getSingletonPtr() != NULL)
    {
        ReqDBSongInf_t songInf;

        pthread_mutex_lock((pthread_mutex_t *)d_lockReqSonginf);
        if (reqDbSongInf(song.SongIndex, &songInf))
        {
            strncpy(song.SongName, songInf.SongName, sizeof(song.SongName)-1);
            song.SongName[sizeof(song.SongName)-1] = 0;
            song.OrderIndex = songInf.OrderIndex;
            song.FileType = songInf.FileType;
            song.MediaType = songInf.SubFileType;
            strncpy(song.SingerName, songInf.SingerName, sizeof(song.SingerName)-1);
            song.SingerName[sizeof(song.SingerName)-1] = 0;
            strncpy(song.firstWord, songInf.FirstWord, sizeof(song.firstWord)-1);
            song.Level = 0;
            //song.SongType = 0;
            song.SingerIndex = 0;
            //strncpy(song.FileSuffixal, MediaTypeSuffix[songInf.MediaType-1], sizeof(song.FileSuffixal)-1);
            reqSongExtraInf(song,isReserved);
            ret = 1;
        }
        else
            M3D_DebugPrint("song.SongIndex[%d]. Song Info set error!!!\n",song.SongIndex);
        pthread_mutex_unlock((pthread_mutex_t *)d_lockReqSonginf);
    }
    return ret;
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::_addReservedSong(unsigned int SongNo, int insertFlag, const std::string& username, std::string& userid, bool isload)
#else
bool ReqPhoneDB::_addReservedSong(unsigned int SongNo, int insertFlag, const std::string& username, const std::string& userid, unsigned int randomnum, bool isload)
#endif
{
    ReservInfo_st temp;

    //M3D_DebugPrint("ReqPhoneDB::_addReservedSong SongNo = %d: insert[%d] ",SongNo, insertFlag);

    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
#ifndef CAN_RESERVED_SAME_SONG
            if(iReservedSong->SongIndex == SongNo)
#else
            if(iReservedSong->SongIndex == SongNo && iReservedSong->randomNum == randomnum)
#endif
            {
                M3D_DebugPrint("the same reserved song.\n");
                return false;
            }
        }
    }

    temp.SongIndex = SongNo;
    temp.username = username;
    temp.userid = userid;

#ifdef CAN_RESERVED_SAME_SONG
    temp.randomNum = randomnum;
#else
    temp.randomNum = 0;
#endif

    SongListBindingStruct_t tmpsong;
    tmpsong.SongIndex = SongNo;
    //tmpsong.dataIndex =
    if(_reqSongInf(tmpsong) == 0)
        return false;
    temp.FileType = tmpsong.FileType;
    temp.SubFileType = tmpsong.MediaType;
    temp.OrderIndex = tmpsong.OrderIndex;
    strncpy(temp.SongName,tmpsong.SongName,BINDING_SONGNAME_LEN);
    strncpy(temp.FirstWord,tmpsong.firstWord,BINDING_SONGNAME_LEN);

    if(!NoUsedCoin)
    {
        if(tmpsong.FileType == SONG_FILETYPE_MOVIE)
        {
            if(d_noCoinTimeFlag == NO_COIN_MODE_ALL)
            {
                return false;
            }
            else if(d_noCoinTimeFlag == NO_COIN_MODE_TIME)
            {
                return false;
            }
        }
        else
        {
            if(d_noCoinTimeFlag == NO_COIN_MODE_ALL)
            {
                return false;
            }
            else if(d_noCoinTimeFlag == NO_COIN_MODE_COUNT)
            {
                return false;
            }
            if(d_coinType != 1)
            {
                //KM_CoinStart(0);
                //KM_CoinEnd();
            }
        }
    }

    if(insertFlag == 1)
    {
        if (d_reservedSong.size())
            d_reservedSong.insert(d_reservedSong.begin(), 1, temp);
        else
            d_reservedSong.push_back(temp);
    }
    else
        d_reservedSong.push_back(temp);
    if(!isload)
        _saveReservedID(); //save reserved id

    //M3D_DebugPrint("reserved song success.\n");
    return true;
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::_addReservedSongEx(const SongListBindingStruct_t* songinfo, int insertFlag, const std::string& username, const std::string& userid, bool isload)
#else
bool ReqPhoneDB::_addReservedSongEx(const SongListBindingStruct_t* songinfo, int insertFlag, const std::string& username, const std::string& userid, unsigned int randomnum, bool isload)
#endif
{
    ReservInfo_st temp;
    int SongNo = songinfo->SongIndex;

    //M3D_DebugPrint("ReqPhoneDB::_addReservedSongEx SongNo = %d: insert[%d] ",SongNo, insertFlag);

    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
#ifndef CAN_RESERVED_SAME_SONG
            if(iReservedSong->SongIndex == SongNo)
#else
            if(iReservedSong->SongIndex == SongNo && iReservedSong->randomNum == randomnum)
#endif
            {
                M3D_DebugPrint("the same reserved song.\n");
                return false;
            }
        }
    }

    temp.SongIndex = songinfo->SongIndex;
    temp.username = username;
    temp.userid = userid;

#ifdef CAN_RESERVED_SAME_SONG
    temp.randomNum = randomnum;
#else
    temp.randomNum = 0;
#endif

    SongListBindingStruct_t tmpsong;
    memcpy(&tmpsong, songinfo, sizeof(SongListBindingStruct_t));
    reqSongExtraInf(tmpsong);

    temp.FileType = tmpsong.FileType;
    temp.SubFileType = tmpsong.MediaType;
    temp.OrderIndex = tmpsong.OrderIndex;
    strncpy(temp.SongName,tmpsong.SongName,BINDING_SONGNAME_LEN);
    strncpy(temp.FirstWord,tmpsong.firstWord,BINDING_SONGNAME_LEN);

    if(!NoUsedCoin)
    {
        if(tmpsong.FileType == SONG_FILETYPE_MOVIE)
        {
            if(d_noCoinTimeFlag == NO_COIN_MODE_ALL)
            {
                return false;
            }
            else if(d_noCoinTimeFlag == NO_COIN_MODE_TIME)
            {
                return false;
            }
        }
        else
        {
            if(d_noCoinTimeFlag == NO_COIN_MODE_ALL)
            {
                return false;
            }
            else if(d_noCoinTimeFlag == NO_COIN_MODE_COUNT)
            {
                return false;
            }
            if(d_coinType != 1)
            {
                //KM_CoinStart(0);
                //KM_CoinEnd();
            }
        }
    }

    if(insertFlag == 1)
    {
        if (d_reservedSong.size())
            d_reservedSong.insert(d_reservedSong.begin(), 1, temp);
        else
            d_reservedSong.push_back(temp);
    }
    else
        d_reservedSong.push_back(temp);
    if(!isload)
        _saveReservedID(); //save reserved id

    //M3D_DebugPrint("reserved song EX success.\n");
    return true;
}
bool ReqPhoneDB::_addLoadReservedSong(SongListBindingStruct_t SongNo, int insertFlag,std::string username,std::string userid,unsigned int randomnum)
{
#if 0
    ReservInfo_st temp;

    //M3D_DebugPrint("ReqPhoneDB::_addReservedSong SongNo = %d: insert[%d] ",SongNo.SongIndex, insertFlag);

    temp.SongIndex = SongNo.SongIndex;
    temp.username = username;
    temp.userid = userid;

#if 1
    temp.isfave = SongNo.Favo;
    temp.SongType = SongNo.SongType;
    strncpy(temp.SongName,SongNo.SongName,BINDING_SONGNAME_LEN);
    strncpy(temp.OrderChar,SongNo.OrderChar,MAX_ORDER_INDEX_LEN);
#endif

#ifdef CAN_RESERVED_SAME_SONG
    temp.randomNum = randomnum;
#endif

    if(insertFlag == 1)
    {
        if (d_reservedSong.size())
            d_reservedSong.insert(d_reservedSong.begin(), 1, temp);
        else
            d_reservedSong.push_back(temp);
    }
    else
        d_reservedSong.push_back(temp);

    //M3D_DebugPrint("reserved song success.\n");
#endif
    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGet(int *songIndex, int *recIndex, int *deviceIndex, int index, std::string& userid)
{
    pthread_mutex_lock(d_RecThreadLock);
    bool ret = false;
    int indexcount = 0;
    if (index >= d_recordSong.size())
    {

    }
    else if(d_recordSong.size() > 0)
    {
        for (std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin(); iter != d_recordSong.end(); ++iter)
        {
            if (iter->userid == userid)
            {
                if (index == indexcount)
                {
                    *songIndex = iter->SongIndex;
                    *recIndex = iter->RecIndex;
                    *deviceIndex = iter->DeviceId;
                    ret = true;
                    break;
                }
                else
                {
                    indexcount++;
                }
            }
        }
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongAdd(unsigned int songIndex, std::string *recRootPath, std::string *recFilePath)
{
    RecordSongInfo_st temp;
    int lastIndex = 0;

    if(d_rootDeviceId == 0)
        return false;

    pthread_mutex_lock(d_RecThreadLock);
    int recCount = d_recordSong.size();
    pthread_mutex_unlock(d_RecThreadLock);

    if(recCount >= RECORDSONG_MAX_NUM)
        ReqRecordSongDelete(RECORDSONG_MAX_NUM - 1);

    if(recCount > 0)
    {
        pthread_mutex_lock(d_RecThreadLock);
        for (std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin(); iter != d_recordSong.end(); ++iter)
        {
            if (iter->SongIndex == songIndex)
            {
                if (iter->RecIndex > lastIndex)
                    lastIndex = iter->RecIndex;
            }
        }
        pthread_mutex_unlock(d_RecThreadLock);
    }
    lastIndex++;

    M3D_DebugPrint("ReqPhoneDB::ReqRecordSongAdd, songIndex: %d recIndex: %d\n", songIndex, lastIndex);

    temp.DeviceId = d_rootDeviceId;
    temp.SongIndex = songIndex;
    temp.RecIndex = lastIndex;
    temp.userid = d_cur_reservedSong.userid;
    temp.username = d_cur_reservedSong.username;
    temp.rectotalidx = ++d_maxRecTotalIdx;

    SongListBindingStruct_t song;
    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 0)
    {
        return false;
    }
    temp.OrderIndex = song.OrderIndex;
    temp.FileType = song.FileType;
    temp.SubFileType = song.MediaType;
    memset(temp.SongName, 0, sizeof(temp.SongName));
    strncpy(temp.SongName, song.SongName, sizeof(temp.SongName));

    pthread_mutex_lock(d_RecThreadLock);
    if (d_recordSong.size() > 0)
    {
        d_recordSong.insert(d_recordSong.begin(), 1, temp);
    }
    else
    {
        d_recordSong.push_back(temp);
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ReqRecordSongGetFilePath(songIndex, lastIndex, d_rootDeviceId, recRootPath, recFilePath,d_cur_reservedSong.username,d_cur_reservedSong.userid,temp.rectotalidx);

    //return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongAddEx(const SongListBindingStruct_t* songInfo, std::string *recRootPath, std::string *recFilePath)
{
    RecordSongInfo_st temp;
    int lastIndex = 0;
    unsigned int songIndex = songInfo->SongIndex;

    if(d_rootDeviceId == 0)
        return false;

    pthread_mutex_lock(d_RecThreadLock);
    int recCount = d_recordSong.size();
    pthread_mutex_unlock(d_RecThreadLock);

    if(recCount >= RECORDSONG_MAX_NUM)
        ReqRecordSongDelete(RECORDSONG_MAX_NUM - 1);

    if(recCount > 0)
    {
        pthread_mutex_lock(d_RecThreadLock);
        for (std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin(); iter != d_recordSong.end(); ++iter)
        {
            if (iter->SongIndex == songIndex)
            {
                if (iter->RecIndex > lastIndex)
                    lastIndex = iter->RecIndex;
            }
        }
        pthread_mutex_unlock(d_RecThreadLock);
    }
    lastIndex++;

    M3D_DebugPrint("ReqPhoneDB::ReqRecordSongAdd, songIndex: %d recIndex: %d\n", songIndex, lastIndex);

    temp.DeviceId = d_rootDeviceId;
    temp.SongIndex = songIndex;
    temp.RecIndex = lastIndex;
    temp.userid = d_cur_reservedSong.userid;
    temp.username = d_cur_reservedSong.username;
    temp.rectotalidx = ++d_maxRecTotalIdx;

    // other info
    temp.OrderIndex = songInfo->OrderIndex;
    temp.FileType = songInfo->FileType;
    temp.SubFileType = songInfo->MediaType;
    memset(temp.SongName, 0, sizeof(temp.SongName));
    strncpy(temp.SongName, songInfo->SongName, sizeof(temp.SongName));

    pthread_mutex_lock(d_RecThreadLock);
    if (d_recordSong.size() > 0)
    {
        d_recordSong.insert(d_recordSong.begin(), 1, temp);
    }
    else
    {
        d_recordSong.push_back(temp);
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ReqRecordSongGetFilePath(songIndex, lastIndex, d_rootDeviceId, recRootPath, recFilePath,d_cur_reservedSong.username,d_cur_reservedSong.userid,temp.rectotalidx);
}


//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongDelete(unsigned int index)
{
    bool ret = false;

    pthread_mutex_lock(d_RecThreadLock);
    M3D_DebugPrint(" ReqPhoneDB::ReqRecordSongDelete(unsigned int index) = %d\n", index);
    if(index < d_recordSong.size())
    {
        std::string mp3File;
        std::vector<RecordSongInfo_st>::iterator iter;

        iter = d_recordSong.begin();
        iter += index;
        //remove *.MP3
        if(ReqRecordSongGetFilePath(iter->SongIndex, iter->RecIndex, iter->DeviceId, NULL, &mp3File,iter->username,iter->userid,iter->rectotalidx))
            M3D_fremove(mp3File.c_str());

        //remove record
        d_recordSong.erase(iter);
        ret = true;
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongDeleteAll(void)
{
    for(int i = 0; i < d_recordSong.size(); i++)
    {
        String path;
        if(ReqRecordSongGetFilePath(d_recordSong[i].SongIndex, d_recordSong[i].RecIndex, d_recordSong[i].DeviceId, NULL, &path, d_recordSong[i].username, d_recordSong[i].userid, d_recordSong[i].rectotalidx))
            M3D_fremove(path.c_str());
    }
    d_recordSong.clear();
    return true;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqRecordSongCount(void)
{
    pthread_mutex_lock(d_RecThreadLock);
    int count = d_recordSong.size();
    pthread_mutex_unlock(d_RecThreadLock);

    return count;
}

int ReqPhoneDB::ReqRecordSongCount(std::string userid)
{
    int count = 0;
    pthread_mutex_lock(d_RecThreadLock);
    if(d_recordSong.size() > 0)
    {
        for (std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin(); iter != d_recordSong.end(); ++iter)
        {
            if (iter->userid == userid)
            {
                count++;
                continue;
            }
        }
    }
    pthread_mutex_unlock(d_RecThreadLock);
    return count;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetFPath2Phone(int songIndex, int recIndex, int deviceId, std::string *fpath)
{
    bool ret = false;
    std::vector<RecordSongInfo_st>::iterator iter;
    int index = 0;
    pthread_mutex_lock(d_RecThreadLock);
    int recCount = d_recordSong.size();
    pthread_mutex_unlock(d_RecThreadLock);

    while(index < recCount)
    {
        pthread_mutex_lock(d_RecThreadLock);
        iter = d_recordSong.begin()+index;
        pthread_mutex_unlock(d_RecThreadLock);
        if(songIndex == iter->SongIndex && recIndex == iter->RecIndex && deviceId == iter->DeviceId)
        {
            //if(userid != iter->userid || username != iter->username)
            //	break;
            if(ReqRecordSongGetFilePath(index, fpath))
            {
                if (access(fpath->c_str(), 0) != -1)
                    ret = true;
                else
                    M3D_DebugPrint("REC file not exist [%s].",fpath->c_str());
            }
            break;
        }
        index++;
    }

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetFilePath(int index, std::string *filePath)
{
    bool ret = false;
    std::vector<RecordSongInfo_st>::iterator iter;

    pthread_mutex_lock(d_RecThreadLock);
    if(index < d_recordSong.size())
    {
        iter = d_recordSong.begin()+index;
        if(ReqRecordSongGetFilePath(iter->SongIndex, iter->RecIndex, iter->DeviceId, NULL, filePath,iter->username,iter->userid,iter->rectotalidx))
            ret = true;
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetFilePath(int index, std::string *rootPath, std::string *filePath)
{
    bool ret = false;
    std::vector<RecordSongInfo_st>::iterator iter;

    pthread_mutex_lock(d_RecThreadLock);
    if(index < d_recordSong.size())
    {
        iter = d_recordSong.begin()+index;
        if(ReqRecordSongGetFilePath(iter->SongIndex, iter->RecIndex, iter->DeviceId, rootPath, filePath,iter->username,iter->userid,iter->rectotalidx))
            ret = true;
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetFilePath(int songIndex, int recIndex, int deviceId, std::string *rootPath, std::string *filePath,std::string username,std::string userid,int rectotalidx)
{
    bool ret = false;
    std::string string;
    char fileName[256];
    SongListBindingStruct_t song;

    if(filePath != NULL)
        *filePath = "";
    if(rootPath != NULL)
        *rootPath = "";

    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 1)
    {
#ifndef OUT_FILE_SET_SDA3
        if(_getDevicePath(deviceId, &string))
#else
        if(_getSDA3Path(&string))
#endif
        {
            if(rootPath != NULL)
                *rootPath = string;
            string += M3D_RECORDSONG_PATH;

            memset(fileName, 0, sizeof(fileName));
            snprintf(fileName, sizeof(fileName), "%s%d.%d.%d.%s%s", (char *)string.c_str(), rectotalidx, songIndex, recIndex,(char *)userid.c_str(), M3D_RECORDFILE_SUFFIXAL);
            *filePath = std::string(fileName);
            ret = true;
        }
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongName(int index, std::string *name)
{
    bool ret = false;
    std::vector<RecordSongInfo_st>::iterator iter;

    pthread_mutex_lock(d_RecThreadLock);
    if(index < d_recordSong.size())
    {
        iter = d_recordSong.begin()+index;
        ret = ReqSongName(iter->SongIndex, name);
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetInfo(int& songIndex,int& recIndex,int& deviceIndex,std::string& url,int index)
{
    pthread_mutex_lock(d_RecThreadLock);
    if (index >= 0 && index < d_recordSong.size())
    {
        songIndex = d_recordSong[index].SongIndex;
        recIndex = d_recordSong[index].RecIndex;
        deviceIndex = d_recordSong[index].DeviceId;
        char filename[256] = {0};
        sprintf(filename, "%d.%d.%d.%s%s", d_recordSong[index].rectotalidx, songIndex, recIndex, d_recordSong[index].userid.c_str(), M3D_RECORDFILE_SUFFIXAL);
        url = "http://";
#ifndef WIN32
        //url += IP_id;
#endif
        url += ":8082/";
        url += filename;

        pthread_mutex_unlock(d_RecThreadLock);
        return true;
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRecordSongGetInfo(int& songIndex,int& recIndex,int& deviceIndex,std::string& url,int index,std::string& userid)
{
    pthread_mutex_lock(d_RecThreadLock);
    int indexcount = 0;
    if (index >= 0 && index < d_recordSong.size())
    {
        for (std::vector<RecordSongInfo_st>::iterator iter = d_recordSong.begin(); iter != d_recordSong.end(); ++iter)
        {
            if (iter->userid == userid)
            {
                if (index == indexcount)
                {
                    songIndex = iter->SongIndex;
                    recIndex = iter->RecIndex;
                    deviceIndex = iter->DeviceId;
                    char filename[256] = {0};
                    sprintf(filename, "%d.%d.%d.%s%s", iter->rectotalidx, songIndex, recIndex,(char *)userid.c_str(), M3D_RECORDFILE_SUFFIXAL);
                    url = "http://";
#ifndef WIN32
                    //url += IP_id;
#endif
                    url += ":8082/";
                    url += filename;

                    pthread_mutex_unlock(d_RecThreadLock);
                    return true;
                }
                else
                {
                    indexcount++;
                }
            }
        }
    }
    pthread_mutex_unlock(d_RecThreadLock);

    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqFavoSongLoad(void)
{
    d_vFavoID.clear();
#ifndef OUT_FILE_SET_SDA3
    CPVRTString path = CPVRTResourceFile::GetReadPath();
#else
    std::string path;
    if(!_getSDA2Path(&path))
        return false;
    path += M3D_CONFIG_PATH;
#endif
    path += M3D_CONFIG_FAVO_FILE;

    d_FavoPath = path.c_str();

    M3D_FILE fp;
    fp = M3D_fopen(d_FavoPath.c_str(), M3D_OM_RD);
    if(!fp)
        return false;

    //load
    int count, itemp;
    int int_size = sizeof(int);
    int name_size = BINDING_SONGNAME_LEN;//sizeof(Favo_t::SongName);
    int firstword_size = BINDING_SONGNAME_LEN;//sizeof(Favo_t::FirstWord);
    int favo_size = sizeof(Favo_t);
    Favo_t tmpFavo;
    if(M3D_fread(&count, int_size, fp) != int_size)
    {
        //read error
        count = 0;
    }
    for(int i=0; i<count; i++)
    {
        memset(&tmpFavo, 0, favo_size);
        M3D_fread(&itemp, int_size, fp);
        tmpFavo.SongIndex = itemp;

        M3D_fread(&itemp, int_size, fp);
        tmpFavo.OrderIndex = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpFavo.FileType = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpFavo.SubFileType = itemp;
        M3D_fread(tmpFavo.SongName, name_size, fp);
        M3D_fread(tmpFavo.FirstWord, firstword_size, fp);

        d_vFavoID.push_back(tmpFavo);
    }

    M3D_fclose(fp);

    return true;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqFavoSongSave(void)
{
    if(d_FavoPath.size() == 0)
        return;

    M3D_FILE fp;
    fp = M3D_fopen(d_FavoPath.c_str(), M3D_OM_CREAT);
    if(!fp)
        return;

    //save
    int itemp = d_vFavoID.size();
    int int_size = sizeof(int);
    int name_size = BINDING_SONGNAME_LEN;//sizeof(Favo_t::SongName);
    int firstword_size = BINDING_SONGNAME_LEN;//sizeof(Favo_t::FirstWord);
    std::vector<Favo_t>::iterator iter = d_vFavoID.begin();
    M3D_fwrite(&itemp, int_size, fp);
    for(; iter != d_vFavoID.end(); iter++)
    {
        itemp = iter->SongIndex;
        M3D_fwrite(&itemp, int_size, fp);

        itemp = iter->OrderIndex;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->FileType;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->SubFileType;
        M3D_fwrite(&itemp, int_size, fp);
        M3D_fwrite(iter->SongName, name_size, fp);
        M3D_fwrite(iter->FirstWord, firstword_size, fp);
    }

    M3D_fclose(fp);
#ifndef WIN32
    system("sync");
#endif
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqFavoSongAdd(unsigned int SongNo)
{
    if(ReqIsFavoSong(SongNo))
        return true;
    if(ReqFavoSongCount() >= FAVOSONG_MAX_NUM)
        return false;

    Favo_t temp;
    temp.SongIndex = SongNo;
    SongListBindingStruct_t song;
    song.SongIndex = SongNo;
    if(_reqSongInf(song) == 0)
    {
        return false;
    }
    temp.OrderIndex = song.OrderIndex;
    temp.FileType = song.FileType;
    temp.SubFileType = song.MediaType;
    strncpy(temp.SongName, song.SongName, sizeof(temp.SongName));
    strncpy(temp.FirstWord, song.firstWord, sizeof(temp.FirstWord));

    d_vFavoID.push_back(temp);

    //save favo
    ReqFavoSongSave();
    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqFavoSongDelete(unsigned int SongNo)
{
    std::vector<Favo_t>::iterator iter = d_vFavoID.begin();
    for(; iter != d_vFavoID.end(); iter++)
    {
        if(iter->SongIndex == SongNo)
            break;
    }
    if(iter == d_vFavoID.end())
        return false;

    d_vFavoID.erase(iter);
    //save favo
    ReqFavoSongSave();
    return true;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqFavoSongCount(void)
{
    return d_vFavoID.size();
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqIsFavoSong(unsigned int SongNo)
{
    std::vector<Favo_t>::iterator iter = d_vFavoID.begin();
    for(; iter != d_vFavoID.end(); iter++)
    {
        if(iter->SongIndex == SongNo)
            break;
    }
    if(iter == d_vFavoID.end())
        return false;
    return true;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqMyHotSongLoad(void)
{
    d_MyHotPath.clear();
#ifndef OUT_FILE_SET_SDA3
    CPVRTString path = CPVRTResourceFile::GetReadPath();
#else
    std::string path;
    if(!_getSDA2Path(&path))
        return;
    path += M3D_CONFIG_PATH;
#endif
    path += M3D_CONFIG_MYHOT_FILE;

    d_MyHotPath = path.c_str();

    M3D_FILE fp;
    fp = M3D_fopen(d_MyHotPath.c_str(), M3D_OM_RD);
    if(!fp)
        return;

    //load
    int count, itemp;
    int int_size = sizeof(int);
    int name_size = BINDING_SONGNAME_LEN;//sizeof(MyHot_t::SongName);
    int myhot_size = sizeof(MyHot_t);
    MyHot_t tmpMyHot;
    if(M3D_fread(&count, int_size, fp) != int_size)
    {
        //read error
        count = 0;
    }
    for(int i=0; i<count; i++)
    {
        memset(&tmpMyHot, 0, myhot_size);
        M3D_fread(&itemp, int_size, fp);
        tmpMyHot.SongIndex = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpMyHot.Hots = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpMyHot.OrderIndex = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpMyHot.FileType = itemp;
        M3D_fread(&itemp, int_size, fp);
        tmpMyHot.SubFileType = itemp;
        M3D_fread(tmpMyHot.SongName, name_size, fp);

        d_vMyHot.push_back(tmpMyHot);
    }

    M3D_fclose(fp);
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqMyHotSongSave(void)
{
    if(d_MyHotPath.size() == 0)
        return;

    M3D_FILE fp;
    fp = M3D_fopen(d_MyHotPath.c_str(), M3D_OM_CREAT);
    if(!fp)
        return;

    //save
    int itemp = d_vMyHot.size();
    int int_size = sizeof(int);
    int int_name = BINDING_SONGNAME_LEN;//sizeof(MyHot_t::SongName);
    std::vector<MyHot_t>::iterator iter = d_vMyHot.begin();
    M3D_fwrite(&itemp, int_size, fp);
    for(; iter != d_vMyHot.end(); iter++)
    {
        itemp = iter->SongIndex;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->Hots;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->OrderIndex;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->FileType;
        M3D_fwrite(&itemp, int_size, fp);
        itemp = iter->SubFileType;
        M3D_fwrite(&itemp, int_size, fp);
        M3D_fwrite(iter->SongName, int_name, fp);
    }

    M3D_fclose(fp);
#ifndef WIN32
    system("sync");
#endif
}
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqMyHotSongAdd(unsigned int SongNo)
{
    std::vector<MyHot_t>::iterator iter = d_vMyHot.begin();
    MyHot_t tmpT;

    //find from vector
    for(; iter != d_vMyHot.end(); iter++)
    {
        if(iter->SongIndex == SongNo)
            break;
    }
    if(iter == d_vMyHot.end())
    {
        //not the SongNo song in MyHot list
        tmpT.SongIndex = SongNo;
        tmpT.Hots = 1;

        //set view param
        SongListBindingStruct_t song;
        song.SongIndex = SongNo;
        if(_reqSongInf(song, false) == 0)
            return false;
        tmpT.OrderIndex = song.OrderIndex;
        tmpT.FileType = song.FileType;
        tmpT.SubFileType = song.MediaType;
        strncpy(tmpT.SongName, song.SongName, sizeof(tmpT.SongName));

        //push in the vector
        d_vMyHot.push_back(tmpT);
    }
    else
    {
        //find it,and add the Hots
        iter->Hots++;

        if(iter == d_vMyHot.begin())
        {
            //need do nothing
        }
        else
        {
            tmpT = *iter;
            std::vector<MyHot_t>::iterator iterTmp;
            //need change the pos
            for(iterTmp=iter-1; iterTmp != d_vMyHot.begin(); iterTmp--)
            {
                if(iterTmp->Hots >= tmpT.Hots)
                    break;
            }
            if(iterTmp == d_vMyHot.begin())
            {
                //need cmp to MyHot begin
                if(iterTmp->Hots >= tmpT.Hots)
                {
                    //tmpT is the second
                    d_vMyHot.erase(iter);
                    d_vMyHot.insert(iterTmp+1, tmpT);
                }
                else
                {
                    //tmpT is the first
                    d_vMyHot.erase(iter);
                    d_vMyHot.insert(iterTmp, tmpT);
                }
            }
            else
            {
                //tmpT is next iterTmp
                d_vMyHot.erase(iter);
                d_vMyHot.insert(iterTmp+1, tmpT);
            }
        }
    }

    //save to file
    ReqMyHotSongSave();

    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqMyHotSongAddEx(const SongListBindingStruct_t& SongInfo)
{
    int SongNo = SongInfo.SongIndex;

    std::vector<MyHot_t>::iterator iter = d_vMyHot.begin();
    MyHot_t tmpT;

    //find from vector
    for(; iter != d_vMyHot.end(); iter++)
    {
        if(iter->SongIndex == SongNo)
            break;
    }
    if(iter == d_vMyHot.end())
    {
        //not the SongNo song in MyHot list
        tmpT.SongIndex = SongNo;
        tmpT.Hots = 1;

        //set view param
        tmpT.OrderIndex = SongInfo.OrderIndex;
        tmpT.FileType = SongInfo.FileType;
        tmpT.SubFileType = SongInfo.MediaType;
        strncpy(tmpT.SongName, SongInfo.SongName, sizeof(tmpT.SongName));

        //push in the vector
        d_vMyHot.push_back(tmpT);
    }
    else
    {
        //find it,and add the Hots
        iter->Hots++;

        if(iter == d_vMyHot.begin())
        {
            //need do nothing
        }
        else
        {
            tmpT = *iter;
            std::vector<MyHot_t>::iterator iterTmp;
            //need change the pos
            for(iterTmp=iter-1; iterTmp != d_vMyHot.begin(); iterTmp--)
            {
                if(iterTmp->Hots >= tmpT.Hots)
                    break;
            }
            if(iterTmp == d_vMyHot.begin())
            {
                //need cmp to MyHot begin
                if(iterTmp->Hots >= tmpT.Hots)
                {
                    //tmpT is the second
                    d_vMyHot.erase(iter);
                    d_vMyHot.insert(iterTmp+1, tmpT);
                }
                else
                {
                    //tmpT is the first
                    d_vMyHot.erase(iter);
                    d_vMyHot.insert(iterTmp, tmpT);
                }
            }
            else
            {
                //tmpT is next iterTmp
                d_vMyHot.erase(iter);
                d_vMyHot.insert(iterTmp+1, tmpT);
            }
        }
    }

    //save to file
    ReqMyHotSongSave();

    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqMyHotSongDelete(unsigned int SongNo)
{

    bool ret = false;
    std::vector<MyHot_t>::iterator iter = d_vMyHot.begin();

    //find from vector
    for(; iter != d_vMyHot.end(); iter++)
    {
        if(iter->SongIndex == SongNo)
        {
            d_vMyHot.erase(iter);
            ret = true;
            break;
        }
    }

    //save to file
    ReqMyHotSongSave();

    return ret;
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::ReqReservedSongAddEx(unsigned int SongNo, const std::string& username, const std::string& userid,int flag)
#else
bool ReqPhoneDB::ReqReservedSongAddEx(unsigned int SongNo, const std::string& username, const std::string& userid, unsigned int randomnum, int flag)
#endif
{
    if(d_reservedSong.size() >= PROGSONG_MAX_NUM)
    {
        if(flag == 0)
            return false;
        else
            ReqReservedSongDeleteByIndex(PROGSONG_MAX_NUM - 1);
    }

#ifndef CAN_RESERVED_SAME_SONG
    return _addReservedSong(SongNo, 0,username,userid);
#else
    return _addReservedSong(SongNo, 0,username,userid,randomnum);
#endif
}

//----------------------------------------------------------------------------//
#ifndef RES_ADD_NOT_REQ_DB
bool ReqPhoneDB::ReqReservedSongAdd(unsigned int SongNo,int flag)
#else
bool ReqPhoneDB::ReqReservedSongAdd(const SongListBindingStruct_t* songinfo, int flag)
#endif
{
    if(d_reservedSong.size() >= PROGSONG_MAX_NUM)
    {
        if(flag == 0)
            return false;
        else
            ReqReservedSongDeleteByIndex(PROGSONG_MAX_NUM - 1);
    }

#ifndef CAN_RESERVED_SAME_SONG
#ifndef RES_ADD_NOT_REQ_DB
    return _addReservedSong(SongNo, 0,"local","0");
#else
    return _addReservedSongEx(songinfo, 0,username,userid,(unsigned int)rand());
#endif
#else
    std::string username = "local";
    std::string userid = "0";
#ifndef RES_ADD_NOT_REQ_DB
    return _addReservedSong(SongNo, 0,username,userid,(unsigned int)rand());
#else
    return _addReservedSongEx(songinfo, 0,username,userid,(unsigned int)rand());
#endif
#endif
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::ReqReservedSongInsertEx(unsigned int SongNo,const std::string& username, const std::string& userid, int flag)
#else
bool ReqPhoneDB::ReqReservedSongInsertEx(unsigned int SongNo, const std::string& username, const std::string& userid, unsigned int randomnum, int flag)
#endif
{
    if(d_reservedSong.size() >= PROGSONG_MAX_NUM)
    {
        if(flag == 0)
            return false;
        else
            ReqReservedSongDeleteByIndex(PROGSONG_MAX_NUM - 1);
    }

#ifndef CAN_RESERVED_SAME_SONG
    return _addReservedSong(SongNo, 1,username,userid);
#else
    return _addReservedSong(SongNo, 1,username,userid,randomnum);
#endif
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongInsert(unsigned int SongNo, int flag)
{
    if(d_reservedSong.size() >= PROGSONG_MAX_NUM)
    {
        if(flag == 0)
            return false;
        else
            ReqReservedSongDeleteByIndex(PROGSONG_MAX_NUM - 1);
    }

#ifndef CAN_RESERVED_SAME_SONG
    return _addReservedSong(SongNo, 1,"local","0");
#else
    std::string username = "local";
    std::string userid = "0";
    return _addReservedSong(SongNo, 1,username,userid,(unsigned int)rand());
#endif
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::ReqReservedSongTop(unsigned int SongNo,std::string username,std::string userid)
#else
bool ReqPhoneDB::ReqReservedSongTopEx(unsigned int SongNo,unsigned int randomnum)
#endif
{
    if(d_reservedSong.size() == 0)
        return false;
    std::vector<ReservInfo_st>::iterator iReservedSong;
    for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
    {
        if(iReservedSong->SongIndex == SongNo && iReservedSong->randomNum == randomnum)
        {
            ReservInfo_st ReservedSongTmp = *iReservedSong;
            d_reservedSong.erase(iReservedSong);
            d_reservedSong.insert(d_reservedSong.begin(),1,ReservedSongTmp);
            _saveReservedID(); //save reserved id
            M3D_DebugPrint("ReqPhoneDB::ReqReservedSongTop ok---[%d, %d]\n",SongNo,randomnum);
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongTopByIndex(int index)
{
    if(d_reservedSong.size() <= index)
        return false;
    std::vector<ReservInfo_st>::iterator iReservedSong = d_reservedSong.begin() + index;
    ReservInfo_st ReservedSongTmp = *iReservedSong;
    d_reservedSong.erase(iReservedSong);
    d_reservedSong.insert(d_reservedSong.begin(),1,ReservedSongTmp);
    _saveReservedID(); //save reserved id
    M3D_DebugPrint("ReqPhoneDB::ReqReservedSongTopByIndex ok---[%d]\n",index);
    return true;
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::ReqReservedSongDelete(unsigned int SongNo)
#else
bool ReqPhoneDB::ReqReservedSongDelete(unsigned int SongNo,unsigned int randomnum)
#endif
{
    M3D_DebugPrint("ReqPhoneDB::ReqReservedSongDelete SongNo = %d\n",SongNo);

    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
            if(iReservedSong->SongIndex == SongNo && iReservedSong->randomNum == randomnum)
            {
                d_reservedSong.erase(iReservedSong);
                _saveReservedID(); //save reserved id
                M3D_DebugPrint("ReqPhoneDB::ReqReservedSongDelete tok\n");
                return true;
            }
    }
    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongDeleteByIndex(unsigned int index)
{
    M3D_DebugPrint("ReqPhoneDB::ReqReservedSongDeleteByIndex index = %d\n",index);

    if(index < d_reservedSong.size())
    {
        std::vector<ReservInfo_st>::iterator iReservedSong = d_reservedSong.begin() + index;
        d_reservedSong.erase(iReservedSong);
        _saveReservedID(); //save reserved id
        return true;
    }
    return false;
}


//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongGetFirst(int *songIndex)
{
    bool ret = false;
    //M3D_DebugPrint("ReqPhoneDB::ReqReservedSongGetFirst");

    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong = d_reservedSong.begin() ;
        *songIndex = iReservedSong->SongIndex;
        ret = true;
        d_cur_reservedSong.SongIndex = iReservedSong->SongIndex;
        d_cur_reservedSong.username = iReservedSong->username;
        d_cur_reservedSong.userid = iReservedSong->userid;
#ifdef CAN_RESERVED_SAME_SONG
        d_cur_reservedSong.randomNum = iReservedSong->randomNum;
#endif
    }
    else
    {
        *songIndex = -1;
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongGetFirstEx(SongListBindingStruct_t* songResInfo)
{
    bool ret = false;
    //M3D_DebugPrint("ReqPhoneDB::ReqReservedSongGetFirstEx");

    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong = d_reservedSong.begin() ;
        songResInfo->SongIndex = iReservedSong->SongIndex;
        songResInfo->OrderIndex = iReservedSong->OrderIndex;
        songResInfo->FileType = iReservedSong->FileType;
        songResInfo->MediaType = iReservedSong->SubFileType;
        memset(songResInfo->SongName, 0, sizeof(songResInfo->SongName));
        strncpy(songResInfo->SongName, iReservedSong->SongName, sizeof(songResInfo->SongName));
        reqSongExtraInf(*songResInfo, true);
        ret = true;

        d_cur_reservedSong.SongIndex = iReservedSong->SongIndex;
        d_cur_reservedSong.username = iReservedSong->username;
        d_cur_reservedSong.userid = iReservedSong->userid;
#ifdef CAN_RESERVED_SAME_SONG
        d_cur_reservedSong.randomNum = iReservedSong->randomNum;
#endif
    }
    else
    {
    }
    return ret;
}

//----------------------------------------------------------------------------//
#ifndef CAN_RESERVED_SAME_SONG
bool ReqPhoneDB::ReqReservedSongGet(int *songIndex,int index,std::string *username,std::string *userid)
#else
bool ReqPhoneDB::ReqReservedSongGet(int *songIndex,int index,std::string *username,std::string *userid,unsigned int *randomnum)
#endif
{
    bool ret = false;
    //M3D_DebugPrint("ReqPhoneDB::ReqReservedSongGet d_reservedSong.size() = %d\n",d_reservedSong.size());
    if (index >= d_reservedSong.size())
    {

    }
    else if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong = d_reservedSong.begin() + index;
        *songIndex = iReservedSong->SongIndex;
        *username = iReservedSong->username;
        *userid = iReservedSong->userid;
#ifdef CAN_RESERVED_SAME_SONG
        if(randomnum != NULL)
            *randomnum = iReservedSong->randomNum;
#endif
        ret = true;
    }
    return ret;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqReservedSongCount(void)
{
    return d_reservedSong.size();
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongUp(const int songid, const int randomnum)
{
    ReservInfo_st tmpRes;
    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        std::vector<ReservInfo_st>::iterator iResTmp;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
            if(iReservedSong->SongIndex == songid && iReservedSong->randomNum == randomnum)
            {
                if(iReservedSong == d_reservedSong.begin())
                    return false;
                iResTmp = iReservedSong - 1;
                tmpRes = *iReservedSong;
                d_reservedSong.erase(iReservedSong);
                d_reservedSong.insert(iResTmp,1,tmpRes);
                _saveReservedID(); //save reserved id
                M3D_DebugPrint("ReqPhoneDB::ReqReservedSongUp tok\n");
                return true;
            }
        }
    }
    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongDown(const int songid, const int randomnum)
{
    ReservInfo_st tmpRes;
    if(d_reservedSong.size() > 0)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        std::vector<ReservInfo_st>::iterator iResTmp;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
            if(iReservedSong->SongIndex == songid && iReservedSong->randomNum == randomnum)
            {
                if(iReservedSong == d_reservedSong.end() - 1)
                    return false;
                iResTmp = iReservedSong + 1;
                tmpRes = *iReservedSong;
                d_reservedSong.erase(iReservedSong);
                d_reservedSong.insert(iResTmp,1,tmpRes);
                _saveReservedID(); //save reserved id
                M3D_DebugPrint("ReqPhoneDB::ReqReservedSongUp tok\n");
                return true;
            }
        }
    }
    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqReservedSongDeleteAll(void)
{
    M3D_DebugPrint("ReqPhoneDB::ReqReservedSongDeleteAll\n");
    d_reservedSong.clear();
    return true;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqRandomSongModeSet(void)
{
    d_songIdx = rand()%result_nrow;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqRandomSongGet(void)
{
    d_songIdx = (rand()%result_nrow + d_songIdx)%result_nrow;
    return reqDbSongIndexByIndex(d_songIdx);
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqRandomSongGet2(void)  //random MP3 or MTV
{
    int songIndex = -1, songIdx;
    char sql_cmd[SQL_STR_SZ];
    int nrow = 0, ncolumn = 0;
    char **azResult; //save inquire result from db
    char * errMsg = NULL;

    memset(sql_cmd, 0, sizeof(sql_cmd));
    if (checkSQLExist(REQDB_SQL_MP3_OR_MTV))
        sprintf(sql_cmd, "%s",(char *)getSQLString(REQDB_SQL_MP3_OR_MTV));
    sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
    if (errMsg != NULL)
        sqlite3_free(errMsg);

    srand((unsigned)time(NULL));
    if (nrow > 0)
    {
        songIdx = rand()%nrow;
        songIndex = atoi(azResult[ncolumn * (songIdx + 1)]);
    }

    sqlite3_free_table(azResult);

    return songIndex;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqRandomSongGetMP3(void)  //random MP3
{
    int songIndex = -1, songIdx;
    char sql_cmd[SQL_STR_SZ];
    int nrow = 0, ncolumn = 0;
    char **azResult; //save inquire result from db
    char * errMsg = NULL;

    memset(sql_cmd, 0, sizeof(sql_cmd));
    if (checkSQLExist(REQDB_SQL_GET_MP3))
        sprintf(sql_cmd, "%s",(char *)getSQLString(REQDB_SQL_GET_MP3));
    sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
    if (errMsg != NULL)
        sqlite3_free(errMsg);

    srand((unsigned)time(NULL));
    if (nrow > 0)
    {
        songIdx = rand()%nrow;
        songIndex = atoi(azResult[ncolumn * (songIdx + 1)]);
    }
    sqlite3_free_table(azResult);

    return songIndex;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqRandomSongGetMTV(void)  //random MTV
{
    int songIndex = -1, songIdx;
    char sql_cmd[SQL_STR_SZ];
    int nrow = 0, ncolumn = 0;
    char **azResult; //save inquire result from db
    char * errMsg = NULL;

    memset(sql_cmd, 0, sizeof(sql_cmd));
    if (checkSQLExist(REQDB_SQL_GET_MTV))
        sprintf(sql_cmd, "%s",(char *)getSQLString(REQDB_SQL_GET_MTV));
    sqlite3_get_table(d_db, sql_cmd, &azResult, &nrow, &ncolumn, &errMsg);
    if (errMsg != NULL)
        sqlite3_free(errMsg);

    srand((unsigned)time(NULL));
    if (nrow > 0)
    {
        songIdx = rand()%nrow;
        songIndex = atoi(azResult[ncolumn * (songIdx + 1)]);
    }
    sqlite3_free_table(azResult);

    return songIndex;
}


//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqOrdinalSongModeSet(void)
{
    d_songIdx = -1;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqOrdinalSongGet(void)
{
    d_songIdx++;
    return reqDbSongIndexByIndex(d_songIdx);
}


//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongPath(int songIndex, int deviceId, char * suffixal, std::string *Path)
{
    char file[512];
    char url[512];
    M3D_FILE fp = NULL;
    String divecePath;
#ifdef COMB_ERR_PATH
    int err_fix_flag = 0;
#endif
    *Path = "";
    if(d_deviceList.size() > 0)
    {
        //check if has existed, add
        //std::map<int, std::string>::iterator iterId = d_deviceIdMap.find(deviceId);
        std::vector<DeviceInfo_st>::iterator iterId = d_deviceList.begin();
        for(; iterId != d_deviceList.end(); iterId++)
        {
            if (iterId->type == deviceId)
                break;
        }
        //if(iterId != d_deviceIdMap.end())
        if(iterId != d_deviceList.end())
        {
            //divecePath = iterId->second;
            divecePath = iterId->path.c_str();
            memset(file, 0, sizeof(file));
            memset(url, 0, sizeof(url));
#ifndef WIN32  修改
//#ifdef WIN32
#ifdef TEST_20_SONG
            int testFlag = 0;
            switch(songIndex)
            {
            case 11700:
                testFlag = 1;
                break;
            }
            if (testFlag == 0)
            {
#endif
                sprintf(file, "%s%03d/%06d%s", M3D_OKF_PATH, songIndex/1000, songIndex, suffixal);
error_fix:
                *Path = divecePath + file;
                if (access(Path->c_str(), 0) == -1) //文件不存在或者不能访问
                {
                    sprintf(file, "%s%03d/%05d%s", M3D_OKF_PATH, songIndex/1000, songIndex, suffixal);
                    *Path = divecePath + file;
                    if (access(Path->c_str(), 0) == -1)
                    {
                        sprintf(file, "%s%02d/%05d%s", M3D_SONG_PATH, songIndex/1000, songIndex, suffixal);
                        *Path = divecePath + file;
                        if (access(Path->c_str(), 0) == -1)
                        {
                            sprintf(file, "%s%02d/%06d%s", M3D_SONG_PATH, songIndex/1000, songIndex, suffixal);
                            *Path = divecePath + file;
                            if (access(Path->c_str(), 0) == -1)
                            {
                                //guxm add for song path error from 322000 - 322999
#ifdef COMB_ERR_PATH
                                if(songIndex >= 322000 && songIndex <= 322999 && err_fix_flag == 0)
                                {
                                    err_fix_flag = 1;
                                    M3D_DebugPrint("error path of songindex %d , change another path\n",songIndex);
                                    //sprintf(file, "%s%03d/%06d%s", M3D_OKF_PATH, (songIndex/1000)+1, songIndex, suffixal);
                                    goto error_fix;
                                }
                                else
#endif
                                {
                                    M3D_DebugPrint("no file !!!!!!!!!  error  !!!!!!!!! songindex = [%d]\n",songIndex);
                                    M3D_DebugPrint("no file !!!!!!!!!  deviceId = [%d], Path->c_str() = [%s]\n",deviceId,Path->c_str());
                                }
                                return false;
                            }
                        }
                    }
                }
#ifdef TEST_20_SONG
            }
            else
            {
                sprintf(file, "%s%06d%s", M3D_USB0_PATH, songIndex, suffixal);
                *Path = /*divecePath +*/ file;
                if (access(Path->c_str(), 0) == -1)
                {
                    sprintf(file, "%s%06d%s", M3D_USB1_PATH, songIndex, suffixal);
                    *Path = /*divecePath +*/ file;
                    if (access(Path->c_str(), 0) == -1)
                    {
                        M3D_DebugPrint("no file !!!!!!!!!  error  !!!!!!!!! songindex = [%d]\n",songIndex);
                        return false;
                    }
                }
            }
#endif
#else
            //sprintf(file, "310061.OKF");
            sprintf(file, "320289.OKF");
			*Path =  g_DownloadPath + file;
			//*Path = divecePath + file;
            if (access(Path->c_str(), 0) == -1)
            {
                M3D_DebugPrint("no file !!!!!!!!!  error  !!!!!!!!! songindex = [%d]\n",songIndex);
                M3D_DebugPrint("no file !!!!!!!!!  deviceId = [%d], Path->c_str() = [%s]\n",deviceId,Path->c_str());
                return false;
            }
#endif
        }
    }
    M3D_DebugPrint("songindex = %d, song file = %s, deviceId = %d\n",songIndex, Path->c_str(), deviceId);
    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSingerPicPath(int singerIndex,std::string *Path)
{
    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongPath(int songIndex, std::string *Path)
{
    bool ret = false;
    int deviceId;
    SongListBindingStruct_t song;

    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 1)
    {
        deviceId = song.LocalDevice;

        ret = ReqSongPath(songIndex, deviceId, song.FileSuffixal, Path);
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongPathEx(SongListBindingStruct_t* songInfo, std::string *Path)
{
    bool ret = false;

    ret = ReqSongPath(songInfo->SongIndex, songInfo->LocalDevice, songInfo->FileSuffixal, Path);
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongName(int songIndex, std::string *name)
{
    bool ret = false;
    SongListBindingStruct_t song;

    *name = "";
    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 1)
    {
        *name = std::string(song.SongName);
        ret = true;
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongInfo(int songIndex, std::string *name, int *fileType, int *mediaType)
{
    bool ret = false;
    SongListBindingStruct_t song;

    *name = "";
    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 1)
    {
        *name = std::string(song.SongName);
        *fileType = song.FileType;
        *mediaType = song.MediaType;
        ret = true;
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongInfo(int songIndex, std::string *name, int *fileType, int *mediaType, std::string* singer)
{
    bool ret = false;
    SongListBindingStruct_t song;

    *name = "";
    song.SongIndex = songIndex;
    if(_reqSongInf(song) == 1)
    {
        *name = std::string(song.SongName);
        *fileType = song.FileType;
        *mediaType = song.MediaType;
        *singer = std::string(song.SingerName);
        ret = true;
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqSongFavoFalg(int songIndex)
{
    return ReqIsFavoSong(songIndex);
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqRootPath(std::string *rootPath)
{
    bool ret = false;
    std::string path;

    *rootPath = "";

    if(d_rootDeviceId != 0)
    {
        if(_getDevicePath(d_rootDeviceId ,&path))
            ret = true;
    }
    if(ret)
    {
        *rootPath = std::string( path.c_str());
    }

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqLocalPath(std::string *localPath)
{
    bool ret = false;
    std::string path;

    *localPath = "";

    if(_getDevicePath(1 ,&path))
        ret = true;

    if(ret)
    {
        *localPath = std::string( path.c_str());
    }

    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqDevicePath(int deviceId, std::string *devicePath)
{
    bool ret = false;
    std::string path;

    if(_getDevicePath(deviceId ,&path))
        ret = true;

    if(ret)
        *devicePath = std::string( path.c_str());

    return ret;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqDeviceCount(void)
{
    return d_deviceNameMap.size();
}


//----------------------------------------------------------------------------//
void ReqPhoneDB::ReqNetStateSet(int flag)
{
    M3D_DebugPrint("ReqPhoneDB::ReqNetStateSet flag = %d\n", flag);
    d_netState = flag;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqNetState(void)
{
    M3D_DebugPrint("ReqPhoneDB::ReqNetStateSet d_netState = %d\n", d_netState);
    return d_netState;
}
//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqDbVersion(void)
{
    return d_custverNewest;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqDbNewFilePath(std::string *newFilePath)
{
    bool ret = false;
    std::string path;

    *newFilePath = "";

    if(_getDevicePath(1 ,&path))
        ret = true;

    if(ret)
    {
        path += M3D_SONG_PATH;
        path += M3D_DATABASE_FILE_NAME;
        path += ".new";

        *newFilePath = std::string( path.c_str());
    }

    return ret;
}


//----------------------------------------------------------------------------//
int ReqPhoneDB::ReqReservedSongAddAll(void)
{
    ReservInfo_st temp = {-1, "", "", -1,  -1,-1,-1,"",""};

    M3D_DebugPrint("ReqPhoneDB::ReqReservedSongAddAll");

    std::map<int, int>::iterator iter = d_SIDMap.begin();
    for(; iter != d_SIDMap.end(); iter++)
    {
        temp.SongIndex = iter->first;
        //temp.username = "";
        //temp.userid = "";
        temp.randomNum = 0;
        d_reservedSong.push_back(temp);
    }

    return true;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::reqSongExtraInf(SongListBindingStruct_t& song,bool isreserved)
{
    unsigned int SongNo = song.SongIndex;
    //
    song.Favo = 0;
    song.Resv = 0;
    song.LocalSongFlag = 1;

    sprintf(song.OrderChar, "%05d", song.OrderIndex);

#if 0
    std::set<int>::iterator iFavoSong = d_FavoIDSet.find(SongNo);
    if(iFavoSong != d_FavoIDSet.end())
        song.Favo = 1;
#else
    if (ReqIsFavoSong(song.SongIndex))
        song.Favo = 1;
#endif

    if(isreserved == false)
    {
        std::vector<ReservInfo_st>::iterator iReservedSong;
        for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
            if(iReservedSong->SongIndex == SongNo)
            {
                song.Resv = 1;
                break;
            }
        }
    }
    else
    {
        song.Resv = 1;
    }

    //file type: 1.MP3 2.MTV 3.MOVIE 0.OTHER
    if (song.FileType == SONG_FILETYPE_MTV)
    {
        song.SongType = 1;
#ifdef MP3_MTV_MOVIE_PATH_IS_SDA2
        song.LocalDevice = DISC_USER;
#endif
    }
    else if(song.FileType == SONG_FILETYPE_MP3)
    {
        song.SongType = 2;
#ifdef MP3_MTV_MOVIE_PATH_IS_SDA2
        song.LocalDevice = DISC_USER;
#endif
    }
    else if(song.FileType == SONG_FILETYPE_MOVIE)
    {
        song.SongType = 3;
#ifdef MP3_MTV_MOVIE_PATH_IS_SDA2
        song.LocalDevice = DISC_USER;
#endif
    }
    else if(song.FileType == SONG_FILETYPE_CDG)
    {
        song.SongType = 4;
#ifdef MP3_MTV_MOVIE_PATH_IS_SDA2
        song.LocalDevice = DISC_USER;
#endif
    }
    else
    {
        song.SongType = 0;
#ifdef MP3_MTV_MOVIE_PATH_IS_SDA2
        song.LocalDevice = DISC_NAND;
#endif
    }

#ifndef MP3_MTV_MOVIE_PATH_IS_SDA2
    song.LocalDevice = DISC_NAND;
#endif

    //get file suffixal
    if (song.MediaType < 129)
    {
        if (song.FileType == SONG_FILETYPE_MUS)
        {
            strncpy(song.FileSuffixal, ".MUS", MAX_FILE_SUFFIXAL_LEN-1);
            song.FileSuffixal[MAX_FILE_SUFFIXAL_LEN-1] = 0;
        }
        else if(song.FileType == SONG_FILETYPE_CDG)
        {
            strncpy(song.FileSuffixal, ".MP3", MAX_FILE_SUFFIXAL_LEN-1);
            song.FileSuffixal[MAX_FILE_SUFFIXAL_LEN-1] = 0;
        }
        else/* if(song.FileType == SONG_FILETYPE_MUK)*/
        {
            strncpy(song.FileSuffixal, ".MUK", MAX_FILE_SUFFIXAL_LEN-1);
            song.FileSuffixal[MAX_FILE_SUFFIXAL_LEN-1] = 0;
        }
    }
    else
    {
        strncpy(song.FileSuffixal, ".OKF", MAX_FILE_SUFFIXAL_LEN-1);
        song.FileSuffixal[MAX_FILE_SUFFIXAL_LEN-1] = 0;
    }
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::reqReservedSong(int reqStart, int reqCount)
{
    int ret = 0;
    int bcount = 0;
    int i;
    //SongListBindingStruct_t tmpsong;
    std::vector<ReservInfo_st>::iterator iReservedSong;

    if (reqCount == -1)
    {
        ret = d_reservedSong.size();
        handle.reqCmd.intPara =handle.reqCmd.intPara;
        if(ret > PROGSONG_MAX_NUM)
            ret = PROGSONG_MAX_NUM;
#ifdef REQ_TEST
        for (i = 0; i < MAX_BINDREC_COUNT; i ++)
        {
            bindingRec.items[i].song = SongListRecDummy;
        }
#endif

#if 1
        if(strlen(handle.reqCmd.strPara) == 0)
            return ret;
        i = 0;
        ret = 0;
        for  (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
        {
            int x = min(strlen(handle.reqCmd.strPara),strlen(iReservedSong->FirstWord));
            //M3D_DebugPrint("#############[%s]#################",iReservedSong->SongName);
            if(stricmpn_ex(handle.reqCmd.strPara,iReservedSong->FirstWord,x) == 0)
            {
                ret++;
            }
        }
#endif

        return ret;
    }
    i = 0;
    ret = 0;
    if(d_reservedSong.size() == 0)
    {
        for (i = 0; i<reqCount; i++)
        {
            bindingRec.items[i].song = SongListRecDummy;
        }
        return 0;
    }
    i = 0;
    for (iReservedSong = d_reservedSong.begin(); iReservedSong != d_reservedSong.end(); ++iReservedSong)
    {
        if(strlen(handle.reqCmd.strPara) != 0)
        {
            int x = min(strlen(handle.reqCmd.strPara),strlen(iReservedSong->FirstWord));
            if(stricmpn_ex(handle.reqCmd.strPara,iReservedSong->FirstWord,x) != 0)
            {
                continue;
            }
        }
        if(i >= reqStart)
        {
            if((ret > reqCount)||((ret + reqStart) > PROGSONG_MAX_NUM))
            {
                break;
            }
            bindingRec.items[ret].song.dataIndex = i;
            bindingRec.items[ret].song.SongIndex = iReservedSong->SongIndex;
            bindingRec.items[ret].song.OrderIndex = iReservedSong->OrderIndex;
            bindingRec.items[ret].song.FileType = iReservedSong->FileType;
            bindingRec.items[ret].song.MediaType = iReservedSong->SubFileType;

            strncpy(bindingRec.items[ret].song.SongName,iReservedSong->SongName,BINDING_SONGNAME_LEN);
            //M3D_DebugPrint("&&&&&&&nxl[%d,%s]",ret+handle.reqCmd.itemIndex,bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongName);

            reqSongExtraInf(bindingRec.items[ret].song, true);

            ret++;
        }
        i++;
    }

    for (i = ret; i<reqCount; i++)
    {
        bindingRec.items[i].song = SongListRecDummy;
    }

    if((ret + reqStart) > PROGSONG_MAX_NUM)
        ret = PROGSONG_MAX_NUM - reqStart;

    if(ret < 0)
        ret = 0;

    return ret;
}
//----------------------------------------------------------------------------//
int ReqPhoneDB::reqMyHotSong(int reqStart, int reqCount)
{
    int ret = d_vMyHot.size();
    if(ret > MYHOTSONG_MAX_NUM)
        ret = MYHOTSONG_MAX_NUM;

    if(reqCount == -1)
    {
        return ret;
    }
    else
    {
        int i, j, ret2;
        for(i=reqStart, j=0; i<ret && j<reqCount; i++, j++)
        {
            memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
            bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = j;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = d_vMyHot.at(i).SongIndex;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = d_vMyHot.at(i).OrderIndex;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = d_vMyHot.at(i).FileType;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = d_vMyHot.at(i).SubFileType;
            strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, d_vMyHot.at(i).SongName, sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);

            reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);
        }
        ret2 = j;
        for(; j<reqCount; j++)
        {
            bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
        }
        return ret2;
    }
}
//----------------------------------------------------------------------------//
int ReqPhoneDB::reqFavorSong(int reqStart, int reqCount)
{
    static std::vector<Favo_t> s_ShowFavo;
    char spara[M3DREQ_STRPARA_LEN];
    int spara_len;
    int ret = d_vFavoID.size();

    if(ret > FAVOSONG_MAX_NUM)
        ret = FAVOSONG_MAX_NUM;

    memset(spara, 0, M3DREQ_STRPARA_LEN);
    strncpy(spara, handle.reqCmd.strPara, M3DREQ_STRPARA_LEN);
    spara_len = strlen(spara);

    if(reqCount == -1)
    {
        s_ShowFavo.clear();
        if(spara_len > 0)
        {
            ret = 0;
            std::vector<Favo_t>::iterator iter = d_vFavoID.begin();
            for(; iter != d_vFavoID.end() && ret<=FAVOSONG_MAX_NUM; iter++)
            {
                if(stricmpn_ex(iter->FirstWord, spara, spara_len) == 0)
                {
                    s_ShowFavo.push_back(*iter);
                    ret++;
                }
            }
        }
        return ret;
    }
    else
    {
        int i, j, ret2;
        if(spara_len == 0)
        {
            for(i=reqStart, j=0; i<ret && j<reqCount; i++, j++)
            {
                memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
                bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = j;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = d_vFavoID.at(i).SongIndex;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = d_vFavoID.at(i).OrderIndex;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = d_vFavoID.at(i).FileType;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = d_vFavoID.at(i).SubFileType;
                strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, d_vFavoID.at(i).SongName, sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);

                reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);
            }
        }
        else
        {
            ret = s_ShowFavo.size();
            for(i=reqStart, j=0; i<ret && j<reqCount; i++, j++)
            {
                memset(&bindingRec.items[j+handle.reqCmd.itemIndex], 0, sizeof(DBBindingStruct_t));
                bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = j;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = s_ShowFavo.at(i).SongIndex;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = s_ShowFavo.at(i).OrderIndex;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = s_ShowFavo.at(i).FileType;
                bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = s_ShowFavo.at(i).SubFileType;
                strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, s_ShowFavo.at(i).SongName, sizeof(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName)-1);

                reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);
            }
        }
        ret2 = j;
        for(; j<reqCount; j++)
        {
            bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
        }
        return ret2;
    }
}
//----------------------------------------------------------------------------//
int ReqPhoneDB::reqRecordSong(int reqStart, int reqCount)
{
    int ret = 0;
    int i,j;

    //waite for record song info req over
    if(d_RecThreadMode == REC_THREAD_MODE_START)
    {
        int ret_thread;
        pthread_join(d_RecThreadId, (void**)&ret_thread);
        if(ret_thread == 0)
            ReqRecordSongInfo();
        d_RecThreadMode = REC_THREAD_MODE_END;
    }

    pthread_mutex_lock(d_RecThreadLock);
    int recCount = d_recordSong.size();
    pthread_mutex_unlock(d_RecThreadLock);

    if (reqCount == -1)
    {
#ifdef REQ_TEST
        for (i = 0; i < MAX_BINDREC_COUNT; i ++)
        {
            bindingRec.items[i].song = SongListRecDummy;
        }
#endif
        return recCount;
    }
    pthread_mutex_lock(d_RecThreadLock);
#if 0
    i = 0;
    ret = 0;
    if(recCount == 0)
    {
        for (i = 0; i<reqCount; i++)
        {
            bindingRec.items[i].song = SongListRecDummy;
        }
        return 0;
    }
    std::vector<RecordSongInfo_st>::iterator iRecordSong;
    for (iRecordSong = d_recordSong.begin(); iRecordSong != d_recordSong.end(); ++iRecordSong)
    {
        if(i >= reqStart)
        {
            if((ret > reqCount)||((ret + reqStart) > RECORDSONG_MAX_NUM))
            {
                break;
            }
#if 0
#ifdef REQ_TEST
            //M3D_DebugPrint("dataIndex = %d, %d, %d", i, d_recordSong[reqStart+ret].SongIndex, d_recordSong[reqStart+ret].RecIndex);

            bindingRec.items[ret+handle.reqCmd.itemIndex].song.dataIndex = i;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongIndex = iRecordSong->SongIndex;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.RecIdx = iRecordSong->RecIndex;
            _reqSongInf(bindingRec.items[ret+handle.reqCmd.itemIndex].song);
            //bindingRec.items[ret+handle.reqCmd.itemIndex].song.LocalDevice = iRecordSong->DeviceId;
#else
            bindingRec.items[ret].song.SongIndex = iRecordSong->SongIndex;
            bindingRec.items[ret].song.RecIdx = iRecordSong->RecIndex;
            _reqSongInf(bindingRec.items[ret].song);
            //bindingRec.items[ret].song.LocalDevice = iRecordSong->DeviceId;
#endif
#else
            //M3D_DebugPrint("dataIndex = %d, %d, %d", i, d_recordSong[reqStart+ret].SongIndex, d_recordSong[reqStart+ret].RecIndex);

            bindingRec.items[ret+handle.reqCmd.itemIndex].song.dataIndex = i;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongIndex = iRecordSong->SongIndex;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.RecIdx = iRecordSong->RecIndex;

            bindingRec.items[ret+handle.reqCmd.itemIndex].song.OrderIndex = iRecordSong->OrderIndex;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.FileType = iRecordSong->FileType;
            bindingRec.items[ret+handle.reqCmd.itemIndex].song.MediaType = iRecordSong->SubFileType;
            strncpy(bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongName, iRecordSong->SongName, sizeof(bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongName));
            reqSongExtraInf(bindingRec.items[ret+handle.reqCmd.itemIndex].song);
#endif
            ret++;
        }
        i++;

    }
#else
    j=0;
    if(recCount > 0)
    {
        for(i=reqStart; i < recCount && j < reqCount; i++,j++,ret++)
        {
            bindingRec.items[j+handle.reqCmd.itemIndex].song.dataIndex = i;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.SongIndex = d_recordSong.at(i).SongIndex;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.RecIdx = d_recordSong.at(i).RecIndex;

            bindingRec.items[j+handle.reqCmd.itemIndex].song.OrderIndex = d_recordSong.at(i).OrderIndex;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.FileType = d_recordSong.at(i).FileType;
            bindingRec.items[j+handle.reqCmd.itemIndex].song.MediaType = d_recordSong.at(i).SubFileType;
            strncpy(bindingRec.items[j+handle.reqCmd.itemIndex].song.SongName, d_recordSong.at(i).SongName, sizeof(bindingRec.items[ret+handle.reqCmd.itemIndex].song.SongName));
            reqSongExtraInf(bindingRec.items[j+handle.reqCmd.itemIndex].song);
        }
    }
#endif
    pthread_mutex_unlock(d_RecThreadLock);
    for (; j<reqCount; j++)
    {
        bindingRec.items[j+handle.reqCmd.itemIndex].song = SongListRecDummy;
    }

    if((ret + reqStart) > RECORDSONG_MAX_NUM)
        ret = RECORDSONG_MAX_NUM - reqStart;

    if(ret < 0)
        ret = 0;

    return ret;
}

//----------------------------------------------------------------------------//
int ReqPhoneDB::reqSingerType(int reqStart, int reqCount)
{
    int ret = 0;
    int i;
    char *pstr;
    int index;
    if (reqCount == -1)
    {
        return SINGER_TYPE_COUNT;
    }

    for (i=0; i<reqCount; i++)
    {
        if (reqStart+i < SINGER_TYPE_COUNT)
        {
            index = reqStart + i;
            if (index < 0)
            {
                M3D_DebugPrint("index < 0\n");
            }
            pstr = "";//ReadRes::getSingletonPtr()->GetString(STRING_ID_SINGER_TYPE + index);
            memset(bindingRec.items[i].singer.SingerName,0,sizeof(bindingRec.items[i].singer.SingerName));
            strncpy(bindingRec.items[i].singer.SingerName,pstr,sizeof(bindingRec.items[i].singer.SingerName) - 1);
            bindingRec.items[i].singer.SingerType = reqStart + i;
            bindingRec.items[i].singer.SongCount =  reqSingerCount(reqStart + i);
            ret++;
        }
        else
        {
            bindingRec.items[i].singer = SingerRecDummy;
        }
    }
    return ret;
}

int ReqPhoneDB::reqLanguage(int reqStart, int reqCount)
{
    int ret = 0;
    int i;
    char *pstr;

    if (reqCount == -1)
    {
        return LANGUAGE_COUNT;
    }

    for (i=0; i<reqCount; i++)
    {
        if (reqStart+i < LANGUAGE_COUNT)
        {
            pstr = "";//ReadRes::getSingletonPtr()->GetString(STRING_ID_LANGUAGE + reqStart + i);
            memset(bindingRec.items[i].singer.SingerName,0,sizeof(bindingRec.items[i].singer.SingerName));
            strncpy(bindingRec.items[i].singer.SingerName,pstr,sizeof(bindingRec.items[i].singer.SingerName) - 1);
            bindingRec.items[i].singer.SingerType = reqStart + i;
            bindingRec.items[i].singer.SongCount =  reqLangugeSongCount(reqStart + i);
            ret++;
        }
        else
        {
            bindingRec.items[i].singer = SingerRecDummy;
        }
    }
    return ret;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::isCameraDev(void)
{
#if 0 //ndef WIN32
    int handle;

    handle = open(M3D_CAMERA_DEV, O_RDONLY);
    if(handle < 0)
    {
        M3D_DebugPrint("Have no camera dev!!!");
        return false;
    }
    close(handle);
    M3D_DebugPrint("There is a camera dev!!!");
#endif
    return true;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::ReqMTVplayState(int songid, int *playKey, int *channel, int *track)
{
    int ret = 0;
    sqlite3_stmt *stmt;
    char pcmd[128];

    sprintf(pcmd, "SELECT PlayKey,BackVideo FROM TableSong WHERE SongIndex = %d;", songid);
    assert(strlen(pcmd) < 128);

    ret = sqlite3_prepare_v2(d_db, pcmd, strlen(pcmd), &stmt, 0);
    if(ret != SQLITE_OK)
    {
        return false;
    }
    else
    {
        if(sqlite3_step(stmt) == SQLITE_ROW)
        {
            *playKey = sqlite3_column_int(stmt, 0);
            *track = sqlite3_column_int(stmt, 1);
            *channel = 0;//sqlite3_column_int(stmt, 2);
            sqlite3_finalize(stmt);
            return true;
        }
        sqlite3_finalize(stmt);
    }
    return false;
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::getSaveConfigPath(std::string* path)
{
    if(!_getSDA2Path(path))
        return false;
    *path += M3D_CONFIG_PATH;
    return true;
}

//----------------------------------------------------------------------------//
void ReqPhoneDB::updateReservedSongForUserName(const std::string& newusername, const std::string& userid)
{
    //do this in host render
    //do some thing to change username for reserved list
    std::vector<ReservInfo_st>::iterator viReserved = d_reservedSong.begin();
    for(; viReserved != d_reservedSong.end(); viReserved++)
    {
        if(viReserved->userid == userid)
            viReserved->username = newusername;
    }
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::reqNewHotsongList(int* hotcount, int* hotlist)
{
#if 0
    //do this in another thread
    char sql_cmd[128];
    int ret = 0;
    sqlite3_stmt *stmt;
    int hotlistLen = *hotcount;
    int itemp = 0;
    //M3D_DebugPrint("req num from cookara [%d]",hotlistLen);

    if(checkSQLExist(REQDB_SQL_MY_HOT_SONGID))
        sprintf(sql_cmd, getSQLString(REQDB_SQL_MY_HOT_SONGID));
    assert(strlen(sql_cmd) < 128);

    ret = sqlite3_prepare_v2(d_db, sql_cmd, strlen(sql_cmd), &stmt, 0);
    if(ret != SQLITE_OK)
    {
        return false;
    }
    else
    {
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
            if(itemp >= hotlistLen)
                break;
            hotlist[itemp] = sqlite3_column_int(stmt, 0);
            itemp++;
        }
        sqlite3_finalize(stmt);
    }
    *hotcount = itemp;
    return true;
#else
    int count = d_vMyHot.size();
    if(count > MYHOTSONG_MAX_NUM)
        count = MYHOTSONG_MAX_NUM;
    *hotcount = count;

    for(int i=0; i<count; i++)
    {
        hotlist[i] = d_vMyHot.at(i).SongIndex;
    }
    return true;
#endif
}

//----------------------------------------------------------------------------//
bool ReqPhoneDB::reqSingerNameBySongId(int songid, std::string* singername)
{
    //do this in another thread
    char sql_cmd[256];
    int ret = 0;
    sqlite3_stmt *stmt;

    if(checkSQLExist(REQDB_SQL_SINGER_BY_SONGID))
        sprintf(sql_cmd, "%s%d",getSQLString(REQDB_SQL_SINGER_BY_SONGID),songid);
    assert(strlen(sql_cmd) < 256);

    ret = sqlite3_prepare_v2(d_db, sql_cmd, strlen(sql_cmd), &stmt, 0);
    if(ret != SQLITE_OK)
    {
        return false;
    }
    else
    {
        if(sqlite3_step(stmt) == SQLITE_ROW)
        {
            if(sqlite3_column_text(stmt, 0) != NULL)
                *singername = (char*)sqlite3_column_text(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return true;
}

void ReqPhoneDB::resetForeignFlag(void)
{
#ifndef WIN32
    //ProfileLoadIntValue(ENUM_INT_FOREIGN_SONG, &d_ForeignFlag);
#endif
}

//MTest
int ReqPhoneDB::getRandomSongindex(void)
{
    int index = rand()%result_nrow;
    return reqDbSongIndexByIndex(index);
}

int ReqPhoneDB::getContinueSongindex(void)
{
    static int index = 0;
    index++;
    index %= result_nrow;

    M3D_DebugPrint("-----------index=%d, result_nrow=%d--------------\n",index,result_nrow);

    return reqDbSongindexByOrder(index);
}

int ReqPhoneDB::getCustomerSongindex(int index)
{

    M3D_DebugPrint("-----------orderindex=%d--------------\n",index);
    return reqDbSongindexByOrderIndex(index);
}


int ReqPhoneDB::getOrderindexBySongindex(int index)
{

    M3D_DebugPrint("-----------Songindex=%d--------------\n",index);
    return reqDbOrderindexBySongIndex(index);
}


}