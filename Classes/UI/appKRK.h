//----------------------------------------------------------------------------//
// Multak 3D GUI Project
//
// Filename : appKRK.h
//
// Description: karaoke application
//
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#pragma once

#ifndef _APPKRK_H_
#define _APPKRK_H_


//#include "appConfig.h"
#include "GUIBase/M3D_App.h"

#include <MKConfig.h>

#include <MKSystem.h>
#include <MKKKEDev.h>
#include <MKPlayer.h>
#include <MKNetService.h>
#include <MKLocalDB.h>
#include <MKRecEncoder.h>
#include <player/player_service.h>
#include <player/player_core.h>
#include "InterfacePicPlayer.h"
#include "ReqEDB/ReqPhoneDB.h"
class EventDispatcher;
class EventListenerCustom;
class PicPlayer;

#define MULTAK_SONG_FILE_SUFFIX ".MUK"
#define DEFAULT_DOWNLOAD_HEAD    0x04000000
#define DOWNLOADFILE_START_ID    100000

namespace CEGUI
{

	//static const int SingerTypeImage_ID = 0x2230;
	static const int SingerTypeImage_ID = 0x2178;
	static const int SongTypeImage_ID = 0x2052;
	static const int FavoImage_ID = 0x2015;
	static const int ProgImage_ID = 0x201a;
	
#ifdef WIN32
	static const char* Key_T9[10] = 
	{
		"0","1","2","3","4","5","6","7","8","9",
	};
#else   //Android平台，遥控器
	static const char* Key_T9[11] = 
	{
		"1",
		"ABC2",
		"DEF3",
		"GHI4",
		"JKL5",
		"MNO6",
		"PQRS7",
		"TUV8",
		"WXYZ9",
		"",
		"0 "
	};
#endif
	static const char Key_T26[27] = 
	{
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	};
	static const int Max_StrPara = 16;	
	//==============for UI show======================
	// no need
	enum{
		PLAYSTATUS_NONE = -1,
		PLAYSTATUS_PLAYING,
		PLAYSTATUS_PAUSED,
		PLAYSTATUS_STOPPED,
	};
	//==========================================
	enum{
		PLAYMODE_SINGLE = 1,
		PLAYMODE_PK,
	};

	enum MKPlayer_Event
	{
		Playing = 1,
		Stopped,
		InterludeBegin,
		InterludeEnd,
		LyricChanged,
		SendSexType,
		TitleHide,
		AutoSeekEnd,
		AutoSeekLast,
		AutoSeekError,
		StaffShow,
	};

	//--------------------------------------------------------------//
	//storage device
	enum{
	    NochangeSDCard = -1,
		DEVICE_DELETE = 0,
		DEVICE_INSERT = 1,
	};


//==========================================
class appKRK : public M3D_App
{
public: 

	appKRK(int _startUpFormID);

	~appKRK();

	virtual void onFirstInit();
	virtual void onRenderUI(float timeElapsed);
	virtual void onRegisterForms();

	//Play control
	int initUIbg();
	void playUIbg(int bgvtype);
	void switchUIbg();
	void stopUIbg();
	bool playNextSong();
	bool playSongBySongIndex(int songIndex, int reservIndex, SongListBindingStruct_t& SongInfo);
	void pause();
	void stop();
	std::string getPlayState();
	//Download
	int initDownloadFile();
	int getDownloadTotalCnt(){return m_totalDownload;};
	std::string getDLFileNameByPosition(int position);

	//UI
	void checkAnyKeyDown();

	//bool ExitFlag;

	//Listener
	static std::string Event_BatchPlayerPlaying;
	static std::string Event_BatchPlayerStopped;
	static std::string Event_PlaySong;
	static std::string Event_BatchPlayerError;
	static std::string Event_BatchPlayer;
	static std::string Event_StorageDevice;

	EventDispatcher* getEventDispatcher() { return d_eventDispatcher; }
	void addListener(EventListenerCustom *listener);
	void removeListener(EventListenerCustom *listener);

	void setUpdateFormID(int updateform){m_updateFormID = updateform;};

	int buildInDeviceFileDetect(String devpath);
	int externDeviceFileDetect(String devpath);

	int appDetectUpdate();
	int detectSongListBinUpdate();
	void showDeviceDeleteHint( );

	void storageDeviceSendEvent(int eventtype);
	int storageDeviceInsertExternal(std::string _path);
	//int storageDeviceDeleteExternal();

	void onVideoStop(int _fileIndex, std::string _filePath);
	void onVideoError(int _fileIndex, std::string _filePath, int code);

	void setExitFlag(bool flag){m_exitFlag = flag;};
	bool getExitFlag(){return m_exitFlag;};

	int getBGVType(){return m_bgvType;};
	
	void playBgvPic();
	int     m_bgvType;
	static int MemoryFormID;
	
private:
	int		m_startUpFormID;
	EventDispatcher *d_eventDispatcher;
	int 	m_updateFormID;
	int 	m_devCnt;
	int     m_bgvIndex;
	bool 	m_exitFlag;
	int 	m_bgvPicIndex;
	std::vector<std::string> m_BGVPicList;
	InterfacePicPlayer* d_BGVPicHandle;

	String  m_sdCid;
	int 	m_sdcardStatus;
	int  m_dspVersion;
	bool m_onlineUpdateEnable;
	int m_totalDownload;
	
	int matchBGVPicFile(std::string filepath);
	int scanBGVPicFile(std::string dirpath);
	bool handleUpdateSelfEvent(const CEGUI::EventArgs& e);

	int m_numberOfRender;
	//player
	bool			m_repeatFlag;
	int				d_songIndex;
	std::string		d_songName; 
	std::string		d_singer;
	std::string		d_songPath;
	std::string		d_userName;
	std::string		d_userId;
	unsigned int	d_randomId;
	int				d_songType;
	int				d_fileType;
	int				d_mediaType;
	bool			d_interruptFlag;
	//sex
	int				d_sexType;
	bool			d_sexStatus;
	bool			d_sexChange;
	//record
	std::string		d_recRootPath;
	std::string 	d_recFilePath;
	bool			d_recordStatus;
	bool 			d_recordFlag;
	bool			d_deleteRecordFlag;
};

}

#endif