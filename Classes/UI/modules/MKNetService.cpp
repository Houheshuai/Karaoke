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

#include "MKString.h"
#include "MKNetService.h"

namespace CEGUI
{
template<> MKNetService* MKSingleton<MKNetService>::ms_Singleton = 0;
const std::string MKNetService::m_name = "net";

// - commands
const std::string MKNetService::m_cmdInit = "init";
const std::string MKNetService::m_cmdDeInit = "deinit";
const std::string MKNetService::m_cmdSetNetConn = "setnetconn";
const std::string MKNetService::m_cmdGetNetConn = "getnetconn";
const std::string MKNetService::m_cmdLogin = "login";
const std::string MKNetService::m_cmdGetPercent = "getpercent";
const std::string MKNetService::m_cmdUpload = "upload";
const std::string MKNetService::m_cmdDownload = "download";
const std::string MKNetService::m_cmdCancelUpload = "cancelupload";
const std::string MKNetService::m_cmdCancelDownload = "canceldownload";
const std::string MKNetService::m_cmdQueryUpload = "queryupload";
const std::string MKNetService::m_cmdQueryDownload = "querydownload";
const std::string MKNetService::m_cmdHttpSyncPost = "httpsyncpost";

// - parameters
const std::string MKNetService::m_paraConn = "conn";
const std::string MKNetService::m_paraUsrID = "userid";
const std::string MKNetService::m_paraUUID = "uuid";
const std::string MKNetService::m_paraToken = "token";
const std::string MKNetService::m_paraTskName = "name";
const std::string MKNetService::m_paraType = "type";
const std::string MKNetService::m_paraNickName = "nickname";
const std::string MKNetService::m_paraSingerName = "singername";
const std::string MKNetService::m_paraFilePath = "filepath";
const std::string MKNetService::m_paraUrl = "url";
const std::string MKNetService::m_paraPicIndex = "picindex";
const std::string MKNetService::m_paraSongId = "songid";
const std::string MKNetService::m_paraIsMTV = "ismtv";
const std::string MKNetService::m_paraIsCamera = "iscamera";
const std::string MKNetService::m_paraScore = "score";
const std::string MKNetService::m_paraIsCanSai = "iscansai";
const std::string MKNetService::m_paraBuTui = "butui";
const std::string MKNetService::m_paraParent = "parent";
const std::string MKNetService::m_paraMaxDuetNum = "maxduetnum";
const std::string MKNetService::m_paraIsDuet = "isduet";
const std::string MKNetService::m_paraIsStartDuet = "isstartduet";
const std::string MKNetService::m_paraCmpType = "cmptype";
const std::string MKNetService::m_paraCmpId = "cmpid";
const std::string MKNetService::m_paraMd5 = "md5";
const std::string MKNetService::m_paraPercent = "percent";
const std::string MKNetService::m_paraHttpSyncPostUrl = "&url";

// - values
const std::string MKNetService::m_paraValueOnline = "online";
const std::string MKNetService::m_paraValueOffline = "offline";

const std::string MKNetService::m_paraValueSong = "song";
const std::string MKNetService::m_paraValuePic = "pic";

// events
const std::string MKNetService::m_eventUpload = "upload";
const std::string MKNetService::m_eventDownload = "download";

// event parameters
const std::string MKNetService::m_eventUploadId = "id";
const std::string MKNetService::m_eventUploadUrl = "url";
const std::string MKNetService::m_eventUploadPercent = "percent";
const std::string MKNetService::m_eventUploadErrorCode = "errorcode";

MKNetService::MKNetService(void* owner) : MKService(m_name, owner)
{
}

MKNetService::~MKNetService(void)
{
}

//----------------------------------------------------------------------------//
int MKNetService::init()
{
	return exec(m_cmdInit, m_nullstr);
}
	
//----------------------------------------------------------------------------//
int MKNetService::deinit()
{			
	return exec(m_cmdDeInit, m_nullstr);
}

//----------------------------------------------------------------------------//
//- conn : online/offline
//----------------------------------------------------------------------------//
int MKNetService::setConn(const std::string& conn)
{			
	return exec(m_cmdSetNetConn, conn);
}

//----------------------------------------------------------------------------//
std::string MKNetService::getConn()
{			
	if (exec(m_cmdGetNetConn, m_nullstr) == 0)
		return getEventParaValue(m_cmdGetNetConn, m_paraConn);
	else
		return m_paraValueOffline;
}

//----------------------------------------------------------------------------//
int MKNetService::setLogin(const std::string& UsrId, const std::string& UUID, const std::string& token)
{			
	setCmdPara(m_cmdLogin, m_paraUsrID, UsrId);
	setCmdPara(m_cmdLogin, m_paraUUID, UUID);
	setCmdPara(m_cmdLogin,  m_paraToken, token);
	return exec(m_cmdLogin, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKNetService::getPercent(int id)
{			
	return exec(m_cmdGetPercent, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//
// return value is task id, use this id to query/cancel upload task
//----------------------------------------------------------------------------//
int MKNetService::uploadRecSong(const std::string& tskName, 
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
													)
{			
	setCmdPara(m_cmdUpload, m_paraType, m_paraValueSong);
	setCmdPara(m_cmdUpload, m_paraTskName, tskName);
	setCmdPara(m_cmdUpload, m_paraNickName, nickName);
	setCmdPara(m_cmdUpload, m_paraSingerName, singerName);
	setCmdPara(m_cmdUpload, m_paraFilePath, filePath);
	setCmdPara(m_cmdUpload, m_paraUrl, url);		
	setCmdPara(m_cmdUpload, m_paraSongId, MKString::valueOf(songId));
	setCmdPara(m_cmdUpload, m_paraIsMTV, MKString::valueOf(isMTV));
	setCmdPara(m_cmdUpload, m_paraIsCamera, MKString::valueOf(isCamera));
	setCmdPara(m_cmdUpload, m_paraScore, MKString::valueOf(score));
	setCmdPara(m_cmdUpload, m_paraIsCanSai, MKString::valueOf(isCanSai));
	setCmdPara(m_cmdUpload, m_paraBuTui, MKString::valueOf(buTui));
	setCmdPara(m_cmdUpload, m_paraParent, MKString::valueOf(parent));
	setCmdPara(m_cmdUpload, m_paraIsDuet, MKString::valueOf(isDuet));
	setCmdPara(m_cmdUpload, m_paraIsStartDuet, MKString::valueOf(isStartDuet));
	setCmdPara(m_cmdUpload, m_paraCmpType, MKString::valueOf(cmpType));
	setCmdPara(m_cmdUpload, m_paraCmpId, MKString::valueOf(cmpId));
	return exec(m_cmdUpload, m_nullstr);
}

//----------------------------------------------------------------------------//
// return value is task id, use this id to query/cancel upload task
//----------------------------------------------------------------------------//
int MKNetService::uploadPic(const std::string& tskName, 
													const std::string& filePath,
													const std::string& url,
													int picIndex
													)
{			
	setCmdPara(m_cmdUpload, m_paraType, m_paraValuePic);
	setCmdPara(m_cmdUpload, m_paraTskName, tskName);
	setCmdPara(m_cmdUpload, m_paraUrl, url);
	setCmdPara(m_cmdUpload, m_paraFilePath, filePath);
	setCmdPara(m_cmdUpload, m_paraPicIndex, MKString::valueOf(picIndex));
	return exec(m_cmdUpload, m_nullstr);
}

//----------------------------------------------------------------------------//
// return value is task id, use this id to query/cancel download task
//----------------------------------------------------------------------------//
int MKNetService::download(const std::string& tskName, 
													const std::string& filePath,
													const std::string& url,
													const std::string& md5
													)
{			
	setCmdPara(m_cmdDownload, m_paraTskName, tskName);
	setCmdPara(m_cmdDownload, m_paraUrl, url);
	setCmdPara(m_cmdDownload, m_paraFilePath, filePath);
	setCmdPara(m_cmdDownload, m_paraMd5, md5);
	return exec(m_cmdDownload, m_nullstr);
}

//----------------------------------------------------------------------------//	
int MKNetService::cancelUpload(int id)
{			
	return exec(m_cmdCancelUpload, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//	
int MKNetService::cancelDownload(int id)
{			
	return exec(m_cmdCancelDownload, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//	
std::string MKNetService::queryUploadName(int id)
{			
	if (exec(m_cmdQueryUpload, MKString::valueOf(id)) == 0)
	{
		return getEventParaValue(m_cmdQueryUpload, m_paraTskName);
	}
	else
		return m_nullstr;
}

//----------------------------------------------------------------------------//	
int MKNetService::queryUploadPercent(int id)
{			
	if (exec(m_cmdQueryUpload, MKString::valueOf(id)) == 0)
	{
		return getEventParaIntValue(m_cmdQueryUpload, m_paraPercent);
	}
	else
		return 0;
}

//----------------------------------------------------------------------------//	
std::string MKNetService::queryDownloadName(int id)
{			
	if (exec(m_cmdQueryDownload, MKString::valueOf(id)) == 0)
	{
		return getEventParaValue(m_cmdQueryDownload, m_paraTskName);
	}
	else
		return m_nullstr;
}

//----------------------------------------------------------------------------//	
int MKNetService::queryDownloadPercent(int id)
{			
	if (exec(m_cmdQueryDownload, MKString::valueOf(id)) == 0)
	{
		return getEventParaIntValue(m_cmdQueryDownload, m_paraPercent);
	}
	else
		return 0;
}

//----------------------------------------------------------------------------//	
int MKNetService::httpSyncPostSetData(const std::string& name, const std::string& value)
{
	return setCmdPara(m_cmdHttpSyncPost, name, value);
}

//----------------------------------------------------------------------------//	
int MKNetService::httpSyncPost(const std::string& url)
{
	setCmdPara(m_cmdHttpSyncPost, m_paraHttpSyncPostUrl, url);
	return exec(m_cmdHttpSyncPost, m_nullstr);
}

}