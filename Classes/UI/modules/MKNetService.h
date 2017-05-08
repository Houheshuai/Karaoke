/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKNetService.h
** Revision : 1.00											
**																	
** Description: MKNetService base on net service
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
************************ HOWTO *******************************
** 
*/

#ifndef MKNETSERVICE_H
#define MKNETSERVICE_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{

class MKNetService : public MKService , public MKSingleton <MKNetService>
{
	
public:

	static const std::string m_name;
	
	// - commands
	static const std::string m_cmdInit;
	static const std::string m_cmdDeInit;
	static const std::string m_cmdSetNetConn;
	static const std::string m_cmdGetNetConn;
	static const std::string m_cmdLogin;
	static const std::string m_cmdGetPercent;
	static const std::string m_cmdUpload;
	static const std::string m_cmdDownload;
	static const std::string m_cmdCancelUpload;
	static const std::string m_cmdCancelDownload;
	static const std::string m_cmdQueryUpload;
	static const std::string m_cmdQueryDownload;
	static const std::string m_cmdHttpSyncPost;

	// - parameters
	static const std::string m_paraConn;
	static const std::string m_paraUsrID;
	static const std::string m_paraUUID;
	static const std::string m_paraToken;
	static const std::string m_paraTskName;
	static const std::string m_paraType;
	static const std::string m_paraNickName;
	static const std::string m_paraSingerName;
	static const std::string m_paraFilePath;
	static const std::string m_paraUrl;
	static const std::string m_paraPicIndex;
	static const std::string m_paraSongId;
	static const std::string m_paraIsMTV;
	static const std::string m_paraIsCamera;
	static const std::string m_paraScore;
	static const std::string m_paraIsCanSai;
	static const std::string m_paraBuTui;
	static const std::string m_paraParent;
	static const std::string m_paraMaxDuetNum;
	static const std::string m_paraIsDuet;
	static const std::string m_paraIsStartDuet;
	static const std::string m_paraCmpType;
	static const std::string m_paraCmpId;
	static const std::string m_paraMd5;
	static const std::string m_paraPercent;
	static const std::string m_paraHttpSyncPostUrl;
	
	// - values
	static const std::string m_paraValueOnline;
	static const std::string m_paraValueOffline;
	
	static const std::string m_paraValueSong;
	static const std::string m_paraValuePic;
	
	// events
	static const std::string m_eventUpload;
	static const std::string m_eventDownload;
	
	// event parameters
	static const std::string m_eventUploadId;
	static const std::string m_eventUploadUrl;
	static const std::string m_eventUploadPercent;
	static const std::string m_eventUploadErrorCode;
	
	MKNetService(void* owner);

	virtual ~MKNetService(void);
	
	//----------------------------------------------------------------------------//
	int init();
		
	//----------------------------------------------------------------------------//
	int deinit();
	
	//----------------------------------------------------------------------------//
	int updateSelf(int timeElapsed);

	//----------------------------------------------------------------------------//
	//- conn : online/offline
	//----------------------------------------------------------------------------//
	int setConn(const std::string& conn);
	
	//----------------------------------------------------------------------------//
	std::string getConn();
	
	//----------------------------------------------------------------------------//
	int setLogin(const std::string& UsrId, const std::string& UUID, const std::string& token);
	
	//----------------------------------------------------------------------------//
	int getPercent(int id);

	//----------------------------------------------------------------------------//
	// return value is task id, use this id to query/cancel upload task
	//----------------------------------------------------------------------------//
	int uploadRecSong(const std::string& tskName, 
														const std::string& nickName,
														const std::string& singerName,
														const std::string& filePath,
														const std::string& url,
														int songId,
														int isMTV,
														int isCamera,
														int score,
														int isCanSai,
														int buTui,
														int parent,
														int isDuet,
														int isStartDuet,
														int cmpType,
														int cmpId
														);
	
	//----------------------------------------------------------------------------//
	// return value is task id, use this id to query/cancel upload task
	//----------------------------------------------------------------------------//
	int uploadPic(const std::string& tskName, 
														const std::string& filePath,
														const std::string& url,
														int picIndex
														);
	
	//----------------------------------------------------------------------------//
	// return value is task id, use this id to query/cancel download task
	//----------------------------------------------------------------------------//
	int download(const std::string& tskName, 
														const std::string& filePath,
														const std::string& url,
														const std::string& md5
														);
	
	//----------------------------------------------------------------------------//	
	int cancelUpload(int id);

	//----------------------------------------------------------------------------//	
	int cancelDownload(int id);
	
	//----------------------------------------------------------------------------//	
	std::string queryUploadName(int id);
	
	//----------------------------------------------------------------------------//	
	int queryUploadPercent(int id);

	//----------------------------------------------------------------------------//	
	std::string queryDownloadName(int id);
	
	//----------------------------------------------------------------------------//	
	int queryDownloadPercent(int id);
	
	//----------------------------------------------------------------------------//	
	int httpSyncPostSetData(const std::string& name, const std::string& value);
	
	//----------------------------------------------------------------------------//	
	int httpSyncPost(const std::string& url);
	
};

}
#endif
