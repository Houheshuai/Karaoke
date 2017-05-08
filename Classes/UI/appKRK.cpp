//----------------------------------------------------------------------------//
// Multak 3D GUI Project
//
// Filename : appKRK.cpp
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
#include "Event/EventDispatcher.h"
#include "Event/EventListenerCustom.h"
#include "Event/EventCustom.h"
#include "KRKPlayer/VideoManager.h"
#include "rf/RFmod.h"
//#include "picplayer/PicPlayer.h"

#include "Strings.res.h"

#include "FormLogParam.h"
//#include "GUIBase/M3D_Log.h"

#include "CEGUI.h"
//#include "ConfigParam.h"
#include "appKRK.h"
#include "ConfigParam.h"
/*
#include "appUICommon.h"
#include "appPathManager.h"
#include "ListBinManager.h"
*/
#include "FormID.res.h"
//#include "../ReqEDB/InterfaceDataBaseManager.h"
//#include "MultakSettings.h"

#include "Widgets/M3D_Widgets.h"
#include "CustomWidgets.h"
#include "Resource/Readres.h"
#include "Base/StringUtils.h"
#include "GUIBase/M3D_ConfigBase.h"
#include "GUIBase/ParamConfig.h"

#include "PVRTString.h"
#include "PVRTResourcefile.h"
#include "appConfig.h"
/*
#include "CooKaraServer/netCooKaraServer.h"
#include "CooKaraServer/MD5.h"

#include "CooKara/CooKaraFunction.h"
*/
extern long RenderIn[6];
extern long RenderOut[6];

extern std::string g_BuildInDataPath;
std::string ConfigParam::appOption_Bgv;
//for test
#define MAX_TESTFILE_CNT	2
std::string TestFileName[MAX_TESTFILE_CNT]=
{
    "1.mkv",
    "2.mp3"
};

enum
{
    OFF,
    ON,
};

static const char *PLY_SWITCH[] =
{
    PLY_CMD_PARA_VALUE_OFF,
    PLY_CMD_PARA_VALUE_ON,
};

static const char *PLY_SETVOCAL[] =
{
    PLY_CMD_SETVOCAL_VOCAL_OFF,
    PLY_CMD_SETVOCAL_VOCAL_ON,
    PLY_CMD_SETVOCAL_VOCAL_AUTO,
};

static const char *PLY_STATUS[] =
{
    PLY_EVENT_GETSTATE_STATE_STOPPED,
    PLY_EVENT_GETSTATE_STATE_STOPPING,
    PLY_EVENT_GETSTATE_STATE_PARSING,
    PLY_EVENT_GETSTATE_STATE_PLAYING,
    PLY_EVENT_GETSTATE_STATE_PAUSING,
    PLY_EVENT_GETSTATE_STATE_PAUSED,
    PLY_EVENT_GETSTATE_STATE_SEEKING,
};

static const char *PLY_SCORELEVEL[] =
{
    PLY_CMD_PLAY_SCORE_LEVEL_EASY,
    PLY_CMD_PLAY_SCORE_LEVEL_NORMAL,
    PLY_CMD_PLAY_SCORE_LEVEL_HARD,
};

static const char *PLY_LYRICMID[] =
{
    PLY_CMD_SETLYRIC_ALIGN_SIDE,
    PLY_CMD_SETLYRIC_ALIGN_MIDDLE,
};
extern std::string g_DownloadPath;
namespace	CEGUI
{
//String BuildInDevice = "BuildInDevice";
//String ExtDeviceBaseName = "ExternalDevice";
std::string appKRK::Event_BatchPlayerPlaying = "BatchPlayerPlaying";
std::string appKRK::Event_BatchPlayerStopped = "BatchPlayerStopped";
std::string appKRK::Event_PlaySong = "PlaySong";
std::string appKRK::Event_BatchPlayerError = "BatchPlayerError";
static MKConfig* configHandle;

static unsigned lastLyricNum = 0xFFFFFFFF;
static unsigned fourLineMode = 0;

bool appKRK::handleUpdateSelfEvent(const CEGUI::EventArgs& e)
{
	FormPlay* formPlay = (FormPlay*)getForm(FrmPlay_ID);
	//FormPlayRec* formPlayRec = (FormPlayRec*)getForm(FrmPlayRec_ID);
	M3D_DebugPrint("MUS_Player::handleUpdateSelfEvent\n");
	
	if (formPlay != NULL)
	{
		formPlay->updatePlayerInfo();
	}
	/*else if(formPlayRec != NULL)
	{
	formPlayRec->updatePlayerInfo();
	}*/
	return false;		
}
//----------------------------------------------------------------------------//
static int handleBatchPlayerPlaying(ServiceEventCBArgs_t* args)
{
	ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
	appKRK* app = (appKRK*)(player->owner);
	FormPlay* formplay = (FormPlay*)app->getForm(FrmPlay_ID);
	if (formplay != NULL)
	{
		formplay->updatePlayerInfo();
	}
	/*ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
	appKRK* app = (appKRK*)(player->owner);

	EventCustom _event(appKRK::Event_BatchPlayer);
	M3D_Log *eventData = new (std::nothrow)M3D_Log();
	if(eventData != NULL)
	{
		eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::Playing);
		_event.setUserData(eventData);
		app->getEventDispatcher()->dispatchEvent(&_event);
	}
	SAFE_DELETE(eventData);*/
    return 0;
}

//17.5.5/houhs:MKPlayer播放状态为stoped时回调到这里
static int handleBatchPlayerStopped(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);
	MKPlayer* bp = (MKPlayer*)MKPlayer::getSingletonPtr();

	/*if(app->getPowerOffStatus())
	{
		FormPathPlay* formPathPlay = (FormPathPlay*)app->getForm(FrmPathPlay_ID);
		formPathPlay->playStoped();
		return 0;
	}
	netCooKaraLan::ResetPlayInfo();*/

	/*int score = 0;
	int playerType = bp->getPlayerType();
	if(playerType == PLAYER_TYPE_MUS) 
	{	
		if(bp->getPlayMode() == "rec")
		{
			if(app->getActiveForm()->getID() != FrmPlayRec_ID)
				app->hideForm(app->getActiveForm()->getID());

			FormPlayRec* formplayrec = (FormPlayRec*)app->getForm(FrmPlayRec_ID);
			formplayrec->playStoped();
		}
		else
		{
			if(app->getShowScoreState() && app->shouldShowScore())
			{
				int value = 0;
#ifndef WIN32
				if(app->getRandomScoreState())
				{
					score = rand()%23 + 80;
				}
				else
#endif
				{
					score = bp->getStoppedScore();
					if(score >= 5)
						score = score > 70? score:70;
					else
						score = 0;
				}
				if(score > 100)
					score = 100;
			}

			if(app->shouldDelRecord())
				((ReqPhoneDB*)ReqPhoneDB::getSingletonPtr())->ReqRecordSongDelete(0);
		}
	}
	else if(playerType == PLAYER_TYPE_VIDEO)
	{
		if(app->getShowScoreState() && app->shouldShowScore())
		{
			score = rand()%23 + 80;
			if(score > 100)
				score = 100;
		}
	}*/
    std::string m_playState = MKPlayer::getSingletonPtr()->getPlayState();
	M3D_DebugPrint("--------Warning:handleBatchPlayerStopped===m_playState[%s]===\n",m_playState.c_str());
    if(m_playState == PLY_EVENT_GETSTATE_STATE_STOPPED)
    {
		EventCustom _event(appKRK::Event_BatchPlayerStopped);
		M3D_Log *eventData = new (std::nothrow)M3D_Log();
		if(eventData != NULL)
		{
			//eventData->setParamInt("score", score);
			//eventData->setParamInt("playerType", playerType);
			_event.setUserData(eventData);
			//17.5.5/houhs:调用appKRK的Event_BatchPlayerStopped在FormPlay里
			app->getEventDispatcher()->dispatchEvent(&_event); 
			SAFE_DELETE(eventData);
		}
		/*
        EventCustom _event(appKRK::Event_BatchPlayer);
        M3D_Log *eventData = new (std::nothrow)M3D_Log();
        if(eventData != NULL)
        {
            eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::Stopped);
            _event.setUserData(eventData);
            app->getEventDispatcher()->dispatchEvent(&_event);
        }
        SAFE_DELETE(eventData);*/
    }
    else
    {
        M3D_DebugPrint("Warning:handleBatchPlayerStopped===m_playState[%s]===\n",m_playState.c_str());
    }
    return 0;
}

//----------------------------------------------------------------------------//
static int handleBatchPlayerInterludeBegin(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);

    EventCustom _event(appKRK::Event_BatchPlayer);
    M3D_Log *eventData = new (std::nothrow)M3D_Log();
    if(eventData != NULL)
    {
        eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::InterludeBegin);
        _event.setUserData(eventData);
        app->getEventDispatcher()->dispatchEvent(&_event);
    }
    SAFE_DELETE(eventData);
    return 0;
}

//----------------------------------------------------------------------------//
static int handleBatchPlayerInterludeEnd(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);

    EventCustom _event(appKRK::Event_BatchPlayer);
    M3D_Log *eventData = new (std::nothrow)M3D_Log();
    if(eventData != NULL)
    {
        eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::InterludeEnd);
        _event.setUserData(eventData);
        app->getEventDispatcher()->dispatchEvent(&_event);
    }
    SAFE_DELETE(eventData);

    return 0;
}

//----------------------------------------------------------------------------//
static int handleBatchPlayerLyricBrushPercent(ServiceEventCBArgs_t* args)
{
    int lineno, percent;
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    player->getEventParaValueInt(player,PLY_EVENT_LYRICCHANGED, PLY_EVENT_LYRICCHANGE_PARA_LINENO, &lineno);
    player->getEventParaValueInt(player,PLY_EVENT_LYRICPERCENT, PLY_EVENT_LYRICPERCENT_PARA_LINEPERCENT, &percent);
    //player->getEventParaValueStr(player,PLY_EVENT_LYRICCHANGED, PLY_EVENT_LYRICCHANGE_PARA_LINESTR, lyric, sizeof(lyric));
    if(fourLineMode)
    {
        lineno /= 2;
    }
    lineno %= 2;

    return 0;
}

//----------------------------------------------------------------------------//
static int handleBatchPlayerLyricChanged(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    int lineno, percent;
    char lyric[256] = {0};
    player->getEventParaValueInt(player,PLY_EVENT_LYRICCHANGED, PLY_EVENT_LYRICCHANGE_PARA_LINENO, &lineno);
    player->getEventParaValueInt(player,PLY_EVENT_LYRICPERCENT, PLY_EVENT_LYRICPERCENT_PARA_LINEPERCENT, &percent);
    player->getEventParaValueStr(player,PLY_EVENT_LYRICCHANGED, PLY_EVENT_LYRICCHANGE_PARA_LINESTR, lyric, sizeof(lyric));

    if(lineno == 0)
    {
        fourLineMode = 0;
    }
    else if(lastLyricNum == 1)
    {
        if(lineno == 4)
        {
            fourLineMode = 1;
        }
        else
        {
            fourLineMode = 0;
        }
    }
    lastLyricNum = lineno;

    if(fourLineMode)
    {
        lineno /= 2;
    }
    lineno %= 2;
    return 0;
}

//----------------------------------------------------------------------------//
static int handleBatchPlayerSendSexType(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);

    EventCustom _event(appKRK::Event_BatchPlayer);
    M3D_Log *eventData = new (std::nothrow)M3D_Log();
    if(eventData != NULL)
    {
        eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::SendSexType);
        _event.setUserData(eventData);
        app->getEventDispatcher()->dispatchEvent(&_event);
    }
    SAFE_DELETE(eventData);
    return 0;
}
//----------------------------------------------------------------------------//
static int handleBatchPlayerTitleHide(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);

    EventCustom _event(appKRK::Event_BatchPlayer);
    M3D_Log *eventData = new (std::nothrow)M3D_Log();
    if(eventData != NULL)
    {
        eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::TitleHide);
        _event.setUserData(eventData);
        app->getEventDispatcher()->dispatchEvent(&_event);
    }
    SAFE_DELETE(eventData);
    return 0;
}
//----------------------------------------------------------------------------//
static int handleBatchPlayerAutoSeek(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);
    char seekresult[32] = {0};
    int eventid = 0;

    player->getEventParaValueStr(player,PLY_EVENT_AUTOSEEK, PLY_EVENT_AUTOSEEK_ENDPARA, seekresult, sizeof(seekresult));
    if (!memcmp(seekresult,PLY_EVENT_AUTOSEEK_ENDPARA_END,strlen(seekresult)))
        eventid = MKPlayer_Event::AutoSeekEnd;
    else if (!memcmp(seekresult,PLY_EVENT_AUTOSEEK_ENDPARA_LAST,strlen(seekresult)))
        eventid = MKPlayer_Event::AutoSeekLast;
    else if (!memcmp(seekresult,PLY_EVENT_AUTOSEEK_ENDPARA_ERR,strlen(seekresult)))
        eventid = MKPlayer_Event::AutoSeekError;
    else
        eventid = 0;

    if (eventid>0)
    {
        EventCustom _event(appKRK::Event_BatchPlayer);
        M3D_Log *eventData = new (std::nothrow)M3D_Log();
        if(eventData != NULL)
        {
            eventData->setParamInt(appKRK::Event_BatchPlayer, eventid);
            _event.setUserData(eventData);
            app->getEventDispatcher()->dispatchEvent(&_event);
        }
        SAFE_DELETE(eventData);
    }
    return 0;
}
//----------------------------------------------------------------------------//
static int handleBatchPlayerStaffShow(ServiceEventCBArgs_t* args)
{
    ezServiceHandle_t* player = (ezServiceHandle_t*)(args->owner);
    appKRK* app = (appKRK*)(player->owner);

    EventCustom _event(appKRK::Event_BatchPlayer);
    M3D_Log *eventData = new (std::nothrow)M3D_Log();
    if(eventData != NULL)
    {
        eventData->setParamInt(appKRK::Event_BatchPlayer, MKPlayer_Event::StaffShow);
        _event.setUserData(eventData);
        app->getEventDispatcher()->dispatchEvent(&_event);
    }
    SAFE_DELETE(eventData);
    return 0;
}

std::string appKRK::Event_StorageDevice = "StorageDeviceChanged";
std::string appKRK::Event_BatchPlayer= "BatchPlayerPlayer";

//----------------------------------------------------------------------------//
appKRK::appKRK(int _startUpFormID) : M3D_App(), m_exitFlag(false), m_startUpFormID(_startUpFormID)
{
    m_updateFormID = 0;
    m_devCnt = 0;
    d_eventDispatcher = nullptr;

    m_bgvType = -1;
    m_bgvPicIndex = 0;
    m_BGVPicList.clear();
    d_BGVPicHandle = nullptr;

    m_sdCid ="";
    m_sdcardStatus = 0;
    m_dspVersion = 0;
    m_totalDownload = 0;
    m_numberOfRender = 0;
}

//----------------------------------------------------------------------------//
appKRK::~appKRK()
{
    if (d_eventDispatcher)
    {
        d_eventDispatcher->removeAllEventListeners();
    }

    SAFE_RELEASE(d_eventDispatcher);
    DestroyPicPlayer(d_BGVPicHandle);
    //SAFE_DELETE(d_BGVPicHandle);
}

//----------------------------------------------------------------------------//
void appKRK::onFirstInit()
{
    CPVRTString resPath = CPVRTResourceFile::GetReadPath();
    char db_pathFile[256] = {0};

    d_eventDispatcher = new (std::nothrow)EventDispatcher();
    if (d_eventDispatcher)
    {
        d_eventDispatcher->setEnabled(true);
    }

#ifdef PLATFORM_UNIX
    sprintf(db_pathFile,"/mnt/sda1/KARAOKE/SONG/song.db");
#else
    sprintf(db_pathFile, "%s%s%s%s", resPath.c_str(), M3D_LOCALINFO_PATH, M3D_SONG_PATH, M3D_DATABASE_FILE_NAME);

#endif

    M3D_DebugPrint("db_pathFile = %s\n",db_pathFile);
    ReqPhoneDB* reqDb = new ReqPhoneDB(db_pathFile,0);

    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(player != NULL)	//17.5.5/houhs: 为player设置回调函数
    {
        player->setEventCallback(PLY_EVENT_PLAY,   handleBatchPlayerPlaying);
        player->setEventCallback(PLY_EVENT_STOP,   handleBatchPlayerStopped);
        player->setEventCallback(PLY_EVENT_PAUSE,  handleBatchPlayerPlaying);
        player->setEventCallback(PLY_EVENT_RESUME, handleBatchPlayerPlaying);
        player->setEventCallback(PLY_EVENT_INTERLUDE_BEGIN, handleBatchPlayerInterludeBegin);
        player->setEventCallback(PLY_EVENT_INTERLUDE_END, handleBatchPlayerInterludeEnd);
        player->setEventCallback(PLY_EVENT_LYRICPERCENT, handleBatchPlayerLyricBrushPercent);
        player->setEventCallback(PLY_EVENT_LYRICCHANGED, handleBatchPlayerLyricChanged);
        player->setEventCallback(PLY_EVENT_SEND_SEXTYPE, handleBatchPlayerSendSexType);
        player->setEventCallback(PLY_EVENT_TITLEINF_END, handleBatchPlayerTitleHide);
        player->setEventCallback(PLY_EVENT_AUTOSEEK, handleBatchPlayerAutoSeek);
        player->setEventCallback(PLY_EVENT_STAFFSHOW,handleBatchPlayerStaffShow);
    }

    VideoManager::GetInstance()->SetOnStopListener(CALLBACK_2(appKRK::onVideoStop, this));
    VideoManager::GetInstance()->SetOnErrorListener(CALLBACK_3(appKRK::onVideoError, this));

    m_bgvIndex = -1;

    //d_BGVPicHandle = new PicPlayer("BGVPic");
    CreatePicPlayer(d_BGVPicHandle,"BGVPic");

    initUIbg();
    playUIbg(BGVTypeValue_video); 
}

void appKRK::onRenderUI(float timeElapsed)
{
    if ((d_BGVPicHandle != nullptr)&&(m_bgvType == BGVTypeValue_images))
    {
        d_BGVPicHandle->Draw(timeElapsed);
        M3D_DebugPrint("onRenderUI BGVPIC timeElapsed = %f\n",timeElapsed);
    }
    RenderIn[3]++;
    if(MKPlayer::getSingletonPtr())
        MKPlayer::getSingletonPtr()->updateSelf((int)timeElapsed);
    RenderOut[3]++;
	//String playState = MKPlayer::getSingletonPtr()->getPlayState();
	//M3D_DebugPrint("----------play status = %s\n----------",(char *)playState.c_str());
    ++m_numberOfRender;
    if (m_numberOfRender == 300)
    {
        m_numberOfRender = 0;
        //playUIbg(BGVTypeValue_images);
        if (m_bgvType == BGVTypeValue_images)
        {
            playBgvPic();
        }
    }
}

//----------------------------------------------------------------------------//
void appKRK::addListener(EventListenerCustom *listener)
{
    if (d_eventDispatcher && listener)
    {
        d_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    }
}

void appKRK::removeListener(EventListenerCustom *listener)
{
    if (d_eventDispatcher && listener)
    {
        d_eventDispatcher->removeEventListener(listener);
    }
}

//----------------------------------------------------------------------------//
void appKRK::onRegisterForms()
{
    M3D_REGISTER_FORMS();

    setMainForm(m_startUpFormID);
}

//////////////////////////////////////////////////////////////////////
void appKRK::onVideoStop(int _fileIndex, std::string _filePath)
{
    //If fileIndex >= 0   bgv
    M3D_DebugPrint("===onVideoStop=====_fileIndex[%d]=====\n",_fileIndex);
    M3D_DebugPrint("===onVideoStop=====_filePath[%s]=====\n",_filePath.c_str());
    if(_fileIndex >= 0)
    {
        m_bgvIndex++;
        m_bgvIndex = m_bgvIndex % VideoManager::GetInstance()->GetBgvCount();
        M3D_DebugPrint("===onVideoStop=====m_bgvIndex[%d]=====\n",m_bgvIndex);
        VideoManager::GetInstance()->Play(m_bgvIndex, 0);
    }

    //mtv or special bgv
}

void appKRK::onVideoError(int _fileIndex, std::string _filePath, int code)
{

}
int appKRK::matchBGVPicFile(std::string filepath)
{
    std::string picfilter = ".jpg";

    std::string::size_type pos = filepath.rfind('.');
    std::string ext = filepath.substr(pos == std::string::npos ? filepath.length() : pos + 1);
    //std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
    char lowerstr[8];
    sprintf(lowerstr,"%s",ext.c_str());
    krk_lowcase(lowerstr);
    if(picfilter.find(std::string(lowerstr)) != std::string::npos)
    {
        auto result = std::find(m_BGVPicList.begin( ), m_BGVPicList.end( ), filepath);
        if(result != m_BGVPicList.end())
        {
        }
        else
        {
            m_BGVPicList.push_back(filepath);
            //m_totalBgvCount++;
            M3D_DebugPrint("==matchBGVPicFile==filepath[%s]==\n",filepath.c_str());
        }
    }
    return m_BGVPicList.size();
}
int appKRK::scanBGVPicFile(std::string dirpath)
{
    int piccnt = 0;
#ifdef _WIN32
    _finddata_t FileInfo;
    //int filetype = MediaFile_Type_None;
    std::string strfind = dirpath + "\\*";
    long Handle = _findfirst(strfind.c_str(), &FileInfo);

    if (Handle == -1L)
    {
        return 0;
    }
    do
    {
        if (FileInfo.attrib & _A_SUBDIR)
        {
            /*
                if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0)){
                    std::string newPath = dirpath + "\\" + FileInfo.name;
                    scanBGVPicFile(newPath);
                }
            		*/
        }
        else
        {
            std::string filepath = (dirpath + FileInfo.name);
            matchBGVPicFile(filepath);
        }
    }
    while (_findnext(Handle, &FileInfo) == 0);

    _findclose(Handle);

#else
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dirpath.c_str())) == NULL)
    {
        M3D_DebugPrint("cannot open pic directory: %s\n", dirpath.c_str());
        return 0;
    }
    chdir(dirpath.c_str());
    while((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(".",entry->d_name) == 0 ||
                    strcmp("..",entry->d_name) == 0)
                continue;
            M3D_DebugPrint("==scanBGVPicFile=dir===%s/======\n",entry->d_name);
            scanBGVPicFile(entry->d_name);
        }
        else
        {
            std::string filepath = (dirpath + std::string(entry->d_name));
            //M3D_DebugPrint("==scanBGVPicFile====filepath[%s]/======\n",filepath.c_str());
            matchBGVPicFile(filepath);
        }
    }
    chdir("..");
    closedir(dp);
#endif
    return 1;
}

void appKRK::playBgvPic()
{
    int piccnt = m_BGVPicList.size();
    if (piccnt > 0)
    {
        m_bgvPicIndex++;
        m_bgvPicIndex = m_bgvPicIndex % piccnt;
        //m_bgvPicIndex = (m_bgvPicIndex++) % piccnt;  // H3 board not support
        //M3D_DebugPrint("==playBgvPic====m_bgvPicIndex[%d]======\n",m_bgvPicIndex);
        String picpath = m_BGVPicList[m_bgvPicIndex];
        //M3D_DebugPrint("==playBgvPic====picpath[%s]======\n",picpath.c_str());
        d_BGVPicHandle->ShowPictureFile(picpath);
    }
}

int appKRK::initUIbg()
{
    int bgcnt = 0;
    VideoManager* videoHandle = VideoManager::GetInstance();

    if (videoHandle->GetBgvCount()>0)
    {
        videoHandle->ClearBgvList();
        videoHandle->Stop();
    }
    videoHandle->SetVideoFilter(".avi");//(".mkv;.mpg;.mp4;.avi");

    String bgvpath = "";
    //GetAppPathManager(pathHandle);
    //bgvpath = pathHandle->getDefaultFolderPath(BuildInDataPath,APP_CUR_BGV_FOLDER);
#ifdef WIN32
    bgvpath = "F:\\KaraokeSystem_170421\\KaraokeSystem\\Simulator\\sdcard\\DOWNLOAD\\";
#else
    bgvpath = "/mnt/sda3/KARAOKE/BGV/";
#endif

    if (bgvpath != "")
        VideoManager::GetInstance()->ScanFolderRecrusive(bgvpath, 0,UseFor_Background);

    //bgvpath = pathHandle->getDefaultFolderPath(ExternalDataPath,APP_CUR_BGV_FOLDER);
    //if (bgvpath != "")
    //VideoManager::GetInstance()->ScanFolderRecrusive(bgvpath, 0,UseFor_Background);
    bgcnt = VideoManager::GetInstance()->GetBgvCount();

    // BGV picture
    //bgvpath = pathHandle->getDefaultFolderPath(SysDataPath,APP_DEFAULT_BGVPIC_FOLDER);
#ifdef WIN32
    bgvpath = "F:\\KaraokeSystem_170421\\KaraokeSystem\\Simulator\\sdcard\\DOWNLOAD\\";
#else
    bgvpath = "/mnt/sda3/KARAOKE/PIC/";
#endif

    M3D_DebugPrint("=====initUIbg====bgvpath[%s]=====\n",bgvpath.c_str());
    if (bgvpath != "")
        scanBGVPicFile(bgvpath);

    return bgcnt;
}
void appKRK::playUIbg(int bgvtype)
{
    //configHandle = (CEGUI::MKConfig*)(CEGUI::MKConfig::getSingletonPtr());
    //int configval = configHandle->getValue(ConfigParam::appOption_Bgv);
    if (bgvtype == BGVTypeValue_images)
    {
        playBgvPic();
    }
    else if (bgvtype == BGVTypeValue_video)
    {
        int bgvcnt = VideoManager::GetInstance()->GetBgvCount();
        if(bgvcnt > 0)
        {
            if(m_bgvIndex == -1)
            {
                srand((unsigned int)time(NULL));
                m_bgvIndex = rand() % bgvcnt;
            }
            VideoManager::GetInstance()->Play(m_bgvIndex, 0);
        }
    }
    m_bgvType = bgvtype;
}

//----------------------------------------------------------------------------//
void appKRK::switchUIbg()
{
    int configval;
    MKConfig* configHandle = (MKConfig*)MKConfig::getSingletonPtr();
    configval = configHandle->getValue(ConfigParam::appOption_Bgv);
    M3D_CHANGEVALUE(configval,BGVTypeValue_video);
    configHandle->setValue(ConfigParam::appOption_Bgv,configval);
    configHandle->save();

    if (configval != m_bgvType)
    {
        stopUIbg();
        playUIbg((BackGroundTypeValue_et)configval);
    }
}
//----------------------------------------------------------------------------//
void appKRK::stopUIbg()
{
    switch (m_bgvType)
    {
    case BGVTypeValue_images:

        break;
    case BGVTypeValue_video:
        VideoManager::GetInstance()->Stop();
        break;
    default:
        break;
    };
    m_bgvType = BGVTypeValue_off;
}
/*
int appKRK::initDownloadFile()
{
	int mediacnt = 0;
	VideoManager* videoHandle = VideoManager::GetInstance();

	if (videoHandle->GetVideoCount()>0){
		videoHandle->ClearVideoList();
		videoHandle->Stop();
	}
	//videoHandle->SetFileFilter(".mkv;.mpg;.mp4;.avi;.mp3;.wav");
	videoHandle->SetVideoFilter(".mkv;.mpg;.mp4;.avi");
	videoHandle->SetAudioFilter(".mp3;.wav");
	String mediapath = "";
	GetAppPathManager(pathHandle);
	mediapath = pathHandle->getDefaultFolderPath(ExternalDataPath,APP_CUR_DOWNLOAD_FOLDER);
	M3D_DebugPrint("==initDownloadFile======mediapath[%s]=====\n",mediapath.c_str());
	if (mediapath != "")
		VideoManager::GetInstance()->ScanFolderRecrusive(mediapath, 0,UseFor_MediaPlay);

	mediacnt = VideoManager::GetInstance()->GetVideoCount();

	return mediacnt;
}*/
//Download

int appKRK::initDownloadFile()
{
    m_totalDownload = MAX_TESTFILE_CNT;
    return m_totalDownload;
}
std::string appKRK::getDLFileNameByPosition(int position)
{
    std::string filename = "";
    if (position < m_totalDownload)
    {
        filename = TestFileName[position];
    }
    return filename;
}
//----------------------------------------------------------------------------//
void appKRK::checkAnyKeyDown()
{
    M3D_Form *aForm = getActiveForm();
    if(aForm != nullptr)
        aForm->anyKeyDown();
}

bool appKRK::playNextSong()
{
    MKPlayer* player = MKPlayer::getSingletonPtr();
    bool ret = false;
    int l_playerType = player->getPlayerType();
    String l_playerState = player->getPlayState();
	M3D_DebugPrint("---playNextSong---playerStata=%s------", l_playerState.c_str());
    if(player && (player->getPlayerType() == PLAYER_TYPE_VIDEO || player->getPlayerType() == PLAYER_TYPE_MUS) )
	{
		if (l_playerState != PLY_EVENT_GETSTATE_STATE_STOPPED )
			return ret;
	}

    ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
    MKConfig* config = (MKConfig*)MKConfig::getSingletonPtr();
    if (config->getValue("Random"))
    {
        int songIndex = 0;
        if (!reqDB->ReqReservedSongGetFirst(&songIndex))
        {
            songIndex = reqDB->ReqRandomSongGet();
            reqDB->ReqReservedSongInsert(songIndex);
        }
    }

    if(reqDB != NULL && reqDB->ReqReservedSongCount() > 0)
    {
        int songIndex = 0;
        if(reqDB->ReqReservedSongGetFirst(&songIndex))
        {
            reqDB->ReqReservedSongDeleteByIndex(0);

            SongListBindingStruct_t SongInfo;
            ret = playSongBySongIndex(songIndex, 0, SongInfo);
            reqDB->ReqMyHotSongAddEx(SongInfo);
        }
    }
    else
    {
        playUIbg(m_bgvType);

        EventCustom _event(appKRK::Event_BatchPlayerError);
        M3D_Log *eventData = new (std::nothrow)M3D_Log();
        if(eventData != NULL)
        {
            eventData->setParamInt("songIndex", -1);
            _event.setUserData(eventData);
            getEventDispatcher()->dispatchEvent(&_event);
            SAFE_DELETE(eventData);
        }
    }
    return ret;
}

bool appKRK::playSongBySongIndex(int songIndex, int reservIndex, SongListBindingStruct_t& SongInfo)
{
    d_fileType = 0, d_mediaType = 0;
    bool ret = true;
    std::string funcName = "playSongBySongIndex";
    int funcStep = 0;
    d_songName = "";
    d_userName = "";
    d_userId = "";
    d_randomId = 0;
    d_sexStatus = false;
    d_sexChange = false;
    d_recordStatus = false;
    d_deleteRecordFlag = true;
    d_recordFlag = false;
    d_interruptFlag = false;

    ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
    reqDB->ReqSongInfo(songIndex, &d_songName, &d_fileType, &d_mediaType);

    //start play
    MKPlayer* player = MKPlayer::getSingletonPtr();
    MKConfig* config = MKConfig::getSingletonPtr();
    d_songPath = "";

    if (d_fileType == SONG_FILETYPE_MTV)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_MTV);
    }
    else if(d_fileType == SONG_FILETYPE_MOVIE)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_MOVIE);
    }
    else if(d_fileType == SONG_FILETYPE_MP3)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_MP3);
    }
    else if(d_fileType == SONG_FILETYPE_CDG)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_CDG);
    }
    else if(d_fileType == SONG_FILETYPE_KSC)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_MIDI);
    }
    else if(d_fileType == SONG_FILETYPE_MUK)
    {
        reqDB->setPlaySongType(PLAY_SONG_TYPE_MIDI);
    }
    else
    {
        if(d_mediaType == SONG_MEDIATYPE_MIDI)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_MIDI);
        }
        else if(d_mediaType == SONG_MEDIATYPE_MIDI_MP3)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_MP3);
        }
        else if(d_mediaType == SONG_MEDIATYPE_MP3)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_MP3);
        }
        else if(d_mediaType == SONG_MEDIATYPE_ACC)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_ACC);
        }
        else if(d_mediaType == SONG_MEDIATYPE_OKF_MIDI)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_MIDI);
        }
        else if(d_mediaType == SONG_MEDIATYPE_OKF_ACC)
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_ACC);
        }
        else
        {
            reqDB->setPlaySongType(PLAY_SONG_TYPE_NONE);
        }
    }

    if(d_fileType == SONG_FILETYPE_MTV || d_fileType == SONG_FILETYPE_MOVIE)
    {

    }
    else
    {
        //init
        config->setValue("KeyVol", 0);
        config->setValue("Tempo", 50);
        player->setVol(PLY_CMD_SETVOL_TONE, 0);
        player->setVol(PLY_CMD_SETVOL_TEMPO, 1000);
    }
    SongInfo.SongIndex = songIndex;
    ret = reqDB->_reqSongInf(SongInfo);
    if(ret == false)
    {
        funcStep = 1;
    }
    else
    {
        ret = reqDB->ReqSongPathEx(&SongInfo, &d_songPath);
        if(ret == false)
        {
            funcStep = 2;
        }
        else
        {
            int songIndexTemp;
            if(reservIndex >= 0)
            {
                reqDB->ReqReservedSongGet(&songIndexTemp, reservIndex, &d_userName, &d_userId, &d_randomId);
            }
            if(d_songPath.length() > 0)
            {
#ifdef USE_COOKARA_FUNC
                netCooKaraLan::SetVol(CooKaraVol_Total, 100);
                netCooKaraLan::SetVol(CooKaraVol_Accompany, config->getValue("AccomanyVol"));
                netCooKaraLan::SetVol(CooKaraVol_Tone, config->getValue("KeyVol")*8+50);
                netCooKaraLan::SetVol(CooKaraVol_Tempo, config->getValue("Tempo"));
                netCooKaraLan::SetVol(CooKaraState_Vocal, config->getValue("VocalType"));
                //netCooKaraLan::SetVol(CooKaraState_Play, d_playStatus);
#endif			
                if(d_fileType == SONG_FILETYPE_MTV || d_fileType == SONG_FILETYPE_MOVIE)
                {
                    player->setPlayerType("video");
                    player->setPlayPara(PLY_CMD_PLAY_FILE_PATH, d_songPath);
                    player->setPlayPara(PLY_CMD_PLAY_SONG_NAME, d_songName);
                    player->setPlayPara(PLY_CMD_PLAY_REC_PATH, "");
                    player->setPlayPara(PLY_CMD_PLAY_PLAY_MODE, "song");
                    player->setPlayPara(PLY_CMD_PLAY_REC_ON, "off");
                    player->setPlayPara(PLY_CMD_PLAY_HWAUDIO, "1");
                    player->setPlayPara(PLY_CMD_PLAY_HWVIDEO, "1");
                    player->setPlayPara(PLY_CMD_PLAY_PLAYERTYPE, "video");
                    player->setPlayPara(PLY_CMD_PLAY_SDKVERSION, "17");
                    player->setPlayPara(PLY_CMD_PLAY_PLAYERTYPE, "video");
                    player->setVocal(PLY_SETVOCAL[config->getValue("VocalType")]);
                    int nowBgvType = m_bgvType;
                    stopUIbg();
                    m_bgvType = nowBgvType;
                }
                else
                {
                    d_songType = SongInfo.MediaType;
                    if(reqDB->ReqRecordSongAddEx(&SongInfo, &d_recRootPath, &d_recFilePath))
                        d_recordStatus = true;

                    player->setPlayerType("mus");
                    player->setViewVisible(MKPlayer::VIEW_ALL);
                    player->enableStaff(1);
                    player->enableLyric(1);
                    player->setPlayPara(PLY_CMD_PLAY_PLAY_MODE, "song");
                    player->setPlayPara(PLY_CMD_PLAY_REC_ON, PLY_SWITCH[d_recordStatus? ON:OFF]);
                    player->setPlayPara(PLY_CMD_PLAY_RECENCFMT, PLY_CMD_PLAY_RECFMT_MP3);

                    player->setPlayPara(PLY_CMD_PLAY_FILE_PATH, d_songPath);
                    player->setPlayPara(PLY_CMD_PLAY_SONG_NAME, d_songName);

                    player->setPlayPara(PLY_CMD_PLAY_REC_PATH, d_recFilePath);
                    player->setPlayPara(PLY_CMD_PLAY_SCORE_LEVEL, PLY_SCORELEVEL[1]);
                    player->setPlayPara(PLY_CMD_PLAY_STAFF_ON, PLY_SWITCH[OFF]);
                    player->setPlayPara(PLY_CMD_PLAY_SCORE_ON, PLY_SWITCH[OFF]);
                    player->setPlayPara(PLY_CMD_PLAY_LYRIC_ON, PLY_SWITCH[ON]);
                    player->setPlayPara(PLY_CMD_SETLYRIC_ALIGN, PLY_LYRICMID[config->getValue("Center")]);

                    char mediatype[16] = {0};
                    sprintf(mediatype, "%d", reqDB->getPlaySongType());
                    player->setPlayPara(PLY_CMD_PLAY_MEDIATYPE, mediatype);
                    player->setPlayPara(PLY_CMD_PLAY_MUSSUBTYPE, "midi");
                    player->setPlayPara(PLY_CMD_PLAY_PLAYERTYPE, "mus");
                    player->setVocal(PLY_SETVOCAL[config->getValue("VocalType")]);
                }
                //------------------------------------------------//
                PlayParam _playParam;
                _playParam.SongPath = d_songPath;
                M3D_DebugPrint("-------+++filepath====%s______", d_songPath.c_str());
                _playParam.RecordPath = g_DownloadPath + "tmpRec.MP3";
                //------need not change------------------
                _playParam.IsRecord = false;
                _playParam.NeedRecord = false;
                _playParam.accomVol = 100;
                _playParam.voiceVol = 100;
                _playParam.micVolL = 100;
                _playParam.micVolR = 100;
                _playParam.wmicVolL = 100;
                _playParam.wmicVolR = 100;
                _playParam.echoVal = 100;
                _playParam.tempoVal = 1000;
                _playParam.toneVal = 0;
         
				_playParam.FileType = d_fileType;

                ret = (player->playSong(_playParam) == true);
                //------------------------------------------------//
                //ret = (player->play() == 0);
            }
        }
    }
	M3D_DebugPrint("----playSongBySongIndex---return ret=%s-----", ret==true?"true":"false");
    //show
    if(ret == true)
    {
        EventCustom _event(appKRK::Event_PlaySong);
        M3D_Log *eventData = new (std::nothrow)M3D_Log();
        if(eventData != NULL)
        {
            eventData->setParamInt("songIndex", songIndex);
            eventData->setParamString("songName", d_songName);
            eventData->setParamInt("mediaType", d_mediaType);
            eventData->setParamInt("fileType",d_fileType);
            eventData->setParamInt("songType", SongInfo.MediaType);
            eventData->setParamString("userName", d_userName);
            eventData->setParamString("userId", d_userId);
            eventData->setParamInt("randomId", d_randomId);

            _event.setUserData(eventData);
            getEventDispatcher()->dispatchEvent(&_event);
            SAFE_DELETE(eventData);
        }
    }
    else
    {
        EventCustom _event(appKRK::Event_BatchPlayerError);
        M3D_Log *eventData = new (std::nothrow)M3D_Log();
        if(eventData != NULL)
        {
            eventData->setParamInt("songIndex", songIndex);
            eventData->setParamString("funcName", funcName);
            eventData->setParamInt("funcStep", funcStep);
            _event.setUserData(eventData);
            getEventDispatcher()->dispatchEvent(&_event);
            SAFE_DELETE(eventData);
        }
    }
    return ret;
}

void appKRK::pause()
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(player != NULL)
        player->pause();
}

void appKRK::stop()
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(player != NULL)
        player->stop();
    d_interruptFlag = true;
}

std::string appKRK::getPlayState()
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(player != NULL)
    {
        return player->getPlayState();
    }
    return "";
}
}