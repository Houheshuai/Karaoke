//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : ReqPhoneDB.h
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

#ifndef REQPHONEDB_H
#define REQPHONEDB_H

#include "ReqDB.h"
#include <set>
#include <vector>
#include <map>
#include <pthread.h>
//#include "netCooKaraLan.h"

#define REQ_TEST
#define CAN_RESERVED_SAME_SONG
#define PLAY_MP3_BGV_BY_BGVMP3
#define RES_ADD_NOT_REQ_DB

namespace CEGUI
{
#define MAX_KARAOKE_DEVICE_COUNT	4	//(1+3)

#define PROGSONG_MAX_NUM		100
#define RECORDSONG_MAX_NUM		300
//#define NETSONG_MAX_NUM		100
#define DOWNLOAD_DEVICE_MIN_FREE_SIZE		0x9600000		//150M
#define REC_DEVICE_MIN_FREE_SIZE		0x1400000			//20M

typedef struct
{
	int songindex[MYHOTSONG_MAX_NUM];
	int count;
	std::string userid;

} HotListInfo_t;

class ReqPhoneDB : public ReqDB
{
public:

	
	ReqPhoneDB(void* dbFile, int para);
		
	virtual ~ReqPhoneDB(void);

	virtual void reqSongExtraInf(SongListBindingStruct_t& song,bool isreserved = false);

	virtual int reqRecordSong(int reqStart, int reqCount);
	virtual int reqReservedSong(int reqStart, int reqCount);
	virtual int reqSingerType(int reqStart, int reqCount);
	virtual int reqLanguage(int reqStart, int reqCount);
	int reqMyHotSong(int reqStart, int reqCount);
	int reqFavorSong(int reqStart, int reqCount);
	

	typedef enum
	{
		DISC_NONE,
		DISC_NAND,
		DISC_SDCARD,
		DISC_USER,
		DISC_BG,
	}DiscType_et;
	
	typedef enum
	{
		NO_COIN_MODE_NONE,
		NO_COIN_MODE_COUNT,
		NO_COIN_MODE_TIME,
		NO_COIN_MODE_ALL,
	
	} NoCoinMode_m;

	typedef struct
	{
		unsigned int		DeviceId;
		unsigned int		SongIndex;	
		unsigned int		RecIndex; 
		std::string			username;
		std::string			userid;
		unsigned int		rectotalidx;

		//just for show msg
		int OrderIndex;
		int FileType;
		int SubFileType;
		char SongName[BINDING_SONGNAME_LEN];
	}RecordSongInfo_st;

	typedef struct
	{
		unsigned int		SongIndex;	
		std::string			username;
		std::string			userid;
		unsigned int		randomNum;

		int FileType;
		int SubFileType;
		int OrderIndex;
		char SongName[BINDING_SONGNAME_LEN];
		char FirstWord[BINDING_SONGNAME_LEN];
	}ReservInfo_st;

	typedef struct
	{
		unsigned int		DeviceId;
		std::string			FileName;		//.../karaoke/
	}FileInfo_st;
		
	typedef struct
	{
		int id;		//from 1, not 0
		std::string path;		//.../karaoke/
		unsigned int freeSize;
		DiscType_et type;
	}DeviceInfo_st;
	
	typedef struct
	{
		int SongIndex;
		int Hots;

		int OrderIndex;
		int FileType;
		int SubFileType;
		char SongName[BINDING_SONGNAME_LEN];
	} MyHot_t;

	typedef struct
	{
		int SongIndex;

		int OrderIndex;
		int FileType;
		int SubFileType;
		char SongName[BINDING_SONGNAME_LEN];
		char FirstWord[BINDING_SONGNAME_LEN];
	} Favo_t;

	ReservInfo_st d_cur_reservedSong;

	std::map<std::string, int>			d_deviceNameMap;	//as a matter of convenience to find device id by path
	std::map<int, std::string>			d_deviceIdMap;		//as a matter of convenience to find device path by id
	std::vector<DeviceInfo_st>			d_deviceList;
	int									d_deviceMaxID;		//from 1
	std::map<int, int>					d_SIDMap;		//songid, deviceid
	std::vector<RecordSongInfo_st>		d_recordSong; 
	std::vector<Favo_t>					d_vFavoID;
	std::vector<ReservInfo_st>					d_reservedSong; 
	std::vector<FileInfo_st>					d_picFileList_nand; 
	std::vector<FileInfo_st>					d_videoFileList_nand;
#ifdef PLAY_MP3_BGV_BY_BGVMP3
	std::vector<FileInfo_st>					d_MP3videoFileList_nand;
#endif
	std::vector<FileInfo_st>					d_picFileList; 
	std::vector<FileInfo_st>					d_videoFileList;
#ifdef PLAY_MP3_BGV_BY_BGVMP3
	std::vector<FileInfo_st>					d_MP3videoFileList;
#endif
	std::vector<MyHot_t>						d_vMyHot;

	int			d_netState;

	int _reqSongInf(SongListBindingStruct_t& song,bool isReserved = false);

	bool ReqRecordSongAdd(unsigned int songIndex, std::string *recRootPath, std::string *recFilePath);
	bool ReqRecordSongAddEx(const SongListBindingStruct_t* songInfo, std::string *recRootPath, std::string *recFilePath);
	bool ReqRecordSongDelete(unsigned int index);
	bool ReqRecordSongDeleteAll(void);
	int  ReqRecordSongCount(void);
	bool ReqRecordSongGetFPath2Phone(int songIndex, int recIndex, int deviceId, std::string *fpath);
	bool ReqRecordSongGetFilePath(int index, std::string *filePath);
	bool ReqRecordSongGetFilePath(int index, std::string *rootPath, std::string *filePath);
	bool ReqRecordSongGetFilePath(int songIndex, int recIndex, int deviceId, std::string *rootPath, std::string *filePath,std::string username,std::string userid,int rectotalidx);
	bool ReqRecordSongName(int index, std::string *name);
	bool ReqRecordSongGetInfo(int& songIndex,int& recIndex,int& deviceIndex,std::string& url,int index);
	bool ReqRecordSongGetInfo(int& songIndex,int& recIndex,int& deviceIndex,std::string& url,int index,std::string& userid);
	bool ReqFavoSongLoad(void);
	void ReqFavoSongSave(void);
	bool ReqFavoSongAdd(unsigned int SongNo);
	bool ReqFavoSongDelete(unsigned int SongNo);
	int  ReqFavoSongCount(void);
	bool ReqIsFavoSong(unsigned int SongNo);
	bool ReqMyHotSongAdd(unsigned int SongNo);
	bool ReqMyHotSongAddEx(const SongListBindingStruct_t& SongInfo);
	bool ReqMyHotSongDelete(unsigned int SongNo);
	//bool ReqNetSongAdd(unsigned int SongNo);
	//bool ReqNetSongDelete(unsigned int SongNo);
	//bool ReqNetSongDeleteLastAndSong(void);
#ifndef RES_ADD_NOT_REQ_DB
	bool ReqReservedSongAdd(unsigned int SongNo,int flag = 0);
#else
	bool ReqReservedSongAdd(const SongListBindingStruct_t* songinfo,int flag = 0);
#endif
	bool ReqReservedSongInsert(unsigned int SongNo,int flag = 0);
	bool ReqReservedSongTopByIndex(int index);
#ifndef CAN_RESERVED_SAME_SONG
	bool ReqReservedSongAddEx(unsigned int SongNo, const std::string& username, const std::string& userid, int flag = 0);
	bool ReqReservedSongInsertEx(unsigned int SongNo, const std::string& username, const std::string& userid, int flag = 0);
	bool ReqReservedSongTop(unsigned int SongNo, const std::string& username, const sstd::string& userid);
	bool ReqReservedSongDelete(unsigned int SongNo);
	bool ReqReservedSongGet(int *songIndex,int index, std::string *username, std::string *userid);
#else
	bool ReqReservedSongAddEx(unsigned int SongNo, const std::string& username, const std::string& userid, unsigned int randomnum, int flag = 0);
	bool ReqReservedSongInsertEx(unsigned int SongNo, const std::string& username, const std::string& userid, unsigned int randomnum, int flag = 0);
	bool ReqReservedSongTopEx(unsigned int SongNo,unsigned int randomnum);
	bool ReqReservedSongDelete(unsigned int SongNo,unsigned int randomnum);
	bool ReqReservedSongGet(int *songIndex,int index,std::string *username,std::string *userid,unsigned int *randomnum = NULL);
#endif
	bool ReqReservedSongDeleteByIndex(unsigned int index);
	bool ReqReservedSongGetFirst(int *songIndex);
	bool ReqReservedSongGetFirstEx(SongListBindingStruct_t* songResInfo);
	int  ReqReservedSongCount(void);
	bool ReqReservedSongUp(const int songid, const int randomnum);	
	bool ReqReservedSongDown(const int songid, const int randomnum);
	bool ReqReservedSongDeleteAll(void);
	
	int  ReqRecordSongCount(std::string userid);
		
	void ReqRandomSongModeSet(void);
	int  ReqRandomSongGet(void);
	int  ReqRandomSongGet2(void);
	int  ReqRandomSongGetMP3(void);
	int  ReqRandomSongGetMTV(void);
	void ReqOrdinalSongModeSet(void);
	int  ReqOrdinalSongGet(void);
	bool ReqSongPath(int songIndex, int deviceId, char *suffixal, std::string *Path);
	bool ReqSongPath(int songIndex, std::string *Path);
	bool ReqSongPathEx(SongListBindingStruct_t* songInfo, std::string *Path);
	bool ReqSingerPicPath(int singerIndex,std::string *Path);

	bool ReqSongName(int songIndex, std::string *name);
	bool ReqSongInfo(int songIndex, std::string *name, int *fileType, int *mediaType);
	bool ReqSongInfo(int songIndex, std::string *name, int *fileType, int *mediaType, std::string* singer);
	bool ReqSongFavoFalg(int songIndex);
	bool ReqRootPath(std::string *rootPath);
	
	bool ReqLocalPath(std::string *localPath);
	bool ReqDevicePath(int deviceId, std::string *path);
	int  ReqDeviceCount(void);
	void ReqNetStateSet(int flag);
	int  ReqNetState(void);
	int  ReqDbVersion(void);
	bool ReqDbNewFilePath(std::string *newFilePath);
	int  ReqReservedSongAddAll(void);

        bool isCameraDev(void);
	bool ReqRecordSongGet(int *songIndex,int *recIndex,int *deviceIndex,int index, std::string& userid);
	void setPlaySongType(int playType) {d_playSongType = playType;}
	int  getPlaySongType(void) {return d_playSongType;}

	bool getBroadResFlag(void) {return d_BroadResFlag;}
	void setBroadResFlag(bool tmp) {d_BroadResFlag = tmp;}

	bool getSaveConfigPath(std::string* path);

	// get play state for mtv // check mtv is or not 720+
	bool ReqMTVplayState(int songid, int *playKey, int *channel, int *track);

	//update user name for reserved list by user id
	void updateReservedSongForUserName(const std::string& newusername, const std::string& userid);

	//req hot song list and save in the [hotlist] buffer
	bool reqNewHotsongList(int* hotcount, int* hotlist);

	//req singer name by songid
	bool reqSingerNameBySongId(int songid, std::string* singername);

	//update record song info when app start
	void ReqRecordSongInfo(sqlite3* dbhandle = NULL);

	//
	void resetForeignFlag(void);

	//get db path
	const char* getDbPath(void) {return d_dbPath.c_str();}

	//MTest
	int getRandomSongindex(void);
	int getContinueSongindex(void);
	int getCustomerSongindex(int index);
	int getOrderindexBySongindex(int index);


	std::string			db_root_path;
	int DBVer;
	int ProjectID;
	std::string ProjectName;

	NoCoinMode_m d_noCoinTimeFlag;
private:
	std::string			d_dbPath;
	std::string			d_custid;
	int					d_custverNewest;
	int					d_rootDeviceId;
	int					d_newestDeviceId;
	//std::string			d_dbNewestPath;
	int					d_maxRecTotalIdx;
	
	
	//sqlite3* 			d_dbLocal;		//favoID + netID
	std::string			d_dbLocalPath;

	std::string			d_MyHotPath;
	std::string			d_FavoPath;

//used in radom mode & ordinal
	unsigned int					d_songIdx;

	int d_playSongType;

	unsigned int d_reservedTmp[PROGSONG_MAX_NUM+1];
	//device		add device
	//db		update db to new version
	//			set song localdevice
	//			sync local db
	//record		read recordsong list, add to local recordsong list
	//----------------------------------------------------------------------------//

	//device		add nand + add device(net)
	//----------------------------------------------------------------------------//
	int ReqAddDevice(void);
	int ReqDeleteDevice(char *path);
	void ReqFindRootDeviceAddNewestDevice(int *rootDevice, int *newestDevice);
	int ReqUpdatetoNewVersion(int newestDeviceId);
	bool ReqUpdateNewDbFile(char *dbFile);
	void ReqCheckDbFile(char *dbFile);
	int ReqLoadSID(void);
	//int ReqInitLocalDb(void);
	void ReqLoadRecordSong(void);
	void ReqLoadConfig(void);
	void ReqSaveConfig(void);
	void ReqLoadPic(void);
	void ReqLoadVideo(void);
#ifdef PLAY_MP3_BGV_BY_BGVMP3
	void ReqLoadMP3Video(void);
#endif
	void ReqMyHotSongLoad(void);
	void ReqMyHotSongSave(void);
	
	int _addDevice(std::string *path, DiscType_et type);
	//return add device ID,  ret <= 0:fail
	int _addDeviceName(std::string *path);
	//return delete device ID, ret == 0:fail
	bool _getDevicePath(int deviceID, std::string *devicePath);
	bool _getSDA3Path(std::string *path);
	bool _getSDA2Path(std::string *path);
	//get custid, custver
	int _getDBCustInfo(char * dbFile, int *custver, std::string *custid);
	int _getDBCustInfo(char * dbFile, int *dbver, int *Projectid,std::string *ProjectName);
	int _updateDBtoNewVersion(char* dbPathNew);
	int _loadSIDToMap(char *dbFile, std::map<int, int>*map, int deviceId);

	void _loadReservedID(void);
	void _saveReservedID(bool flag = true);
	//filter folder
	void _filterRecordSongToList(char *path, std::vector<RecordSongInfo_st>*list, int deviceId);
	void _filterFileToList(char *path, std::vector<FileInfo_st>*list, int deviceId, DiscType_et deviceType, int fileType);

#ifndef CAN_RESERVED_SAME_SONG
	bool _addReservedSong(unsigned int SongNo, int insertFlag, const std::string& username, const std::string& userid, bool isload = false);
	bool _addReservedSongEx(const SongListBindingStruct_t* songinfo, int insertFlag, const std::string& username, const std::string& userid, bool isload = false);
#else
	bool _addReservedSong(unsigned int SongNo, int insertFlag, const std::string& username, const std::string& userid, unsigned int randomnum, bool isload = false);
	bool _addReservedSongEx(const SongListBindingStruct_t* songinfo, int insertFlag, const std::string& username, const std::string& userid, unsigned int randomnum, bool isload = false);
#endif


	bool _addLoadReservedSong(SongListBindingStruct_t SongNo, int insertFlag,std::string username,std::string userid,unsigned int randomnum);
	int orderplayflag;
	bool d_BroadResFlag;

	void *d_lockReqSonginf;

	//for req record song info
	enum
	{
		REC_THREAD_MODE_NONE,
		REC_THREAD_MODE_START,
		REC_THREAD_MODE_END,
	};
	int d_RecThreadMode;
	pthread_t d_RecThreadId;
	pthread_mutex_t* d_RecThreadLock;
};

}

#endif

