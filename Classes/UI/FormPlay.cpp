//----------------------------------------------------------------------------//
// Multak 3D GUI Project
//
// Filename : FormPlay.cpp
//
// Description:
//
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#include <ctime>
#include "Event/EventListenerCustom.h"
#include "Event/EventCustom.h"
#include "KRKPlayer/VideoManager.h"
#include "MKConfig.h"

#include "CEGUI.h"
#include "appKRK.h"

#include "FormID.res.h"
#include "Image.res.h"
#include "Strings.res.h"
#include "FormPlay.h"
#include "FormPlay.res.h"
#include "FormLogParam.h"
#include "appConfig.h"

#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"
#include "Base/StringUtils.h"
#include "KRKLibNew/KRKPlayer/MCodeConvert.h"
#include <krklib.h>

#define MIN_VAILD_SCORE    10
#define DBG_SONGLIST_FILE		"dbgsonglist.txt"
extern std::string g_DownloadPath;


namespace	CEGUI
{
static MKPlayer* playerHandle;
static appKRK*	  eventHandle;
const String FormPlay::EventNamespace("FormPlay");
const String FormPlay::WidgetTypeName("FormPlay");

static String ShowTitle("ShowTitle");
static String HideTitleTimer("HideTitleTimer");
static String ProgCountTimer("ProgCountTimer");
static String HideNumTimer("HideNumTimer");

enum
{
    NEXT_SONGINFO_LOAD_SUCCESS,
    NEXT_SONGINFO_LOAD_FAILED,
    NEXT_SONGINFO_SHOW,
    NEXT_SONGINFO_HIDE,
};
//----------------------------------------------------------------------------//
FormPlay::FormPlay(const String& type, const String& name):
    M3D_Form(type, name),d_playState(0)
{
    d_playSongName = nullptr;
    d_nextSongName = nullptr;
    d_log = nullptr;
    m_curSongName = "";
    //m_playSongName = "";
    m_nextSongName = "";
    m_typeOfUIbg = 0;
    d_ShowNextInfoFlag = 0;
    isEnterPressed = false;
    playerListener = nullptr;
}
//----------------------------------------------------------------------------//
FormPlay::~FormPlay()
{
}
void FormPlay::setPlayStatus(int Status)
{
    if(Status == 0)
    {
        /*static_cast<M3D_ImageLabel*>(d_stateBar->getChild(PlayStatus_ID))->setValue((short)0);
        PauseCoinTimer();*/
    }
    else
    {
        /*static_cast<M3D_ImageLabel*>(d_stateBar->getChild(PlayStatus_ID))->setValue((short)-1);
        ResumeCoinTimer();*/
    }
    String ProgSongTimer("ProgSongTimer");
    createTimer(ProgSongTimer, 1.0f, false, 0);	//next frame do it
}

//----------------------------------------------------------------------------//

void FormPlay::constructWindow(WndRes_t *wndRes)
{
    M3D_Form::constructWindow(wndRes);

    M3D_DebugPrint("constructWindow");
}

//----------------------------------------------------------------------------//
void FormPlay::destructWindow()
{
    M3D_Form::destructWindow();

    M3D_DebugPrint("destructWindow");
}

//----------------------------------------------------------------------------//
void FormPlay::onShown(WindowEventArgs& e)
{
    M3D_Form::onShown(e);
}

//----------------------------------------------------------------------------//
void FormPlay::onHidden(WindowEventArgs& e)
{
    M3D_Form::onHidden(e);
}

//----------------------------------------------------------------------------//
void FormPlay::onCreated()
{
    M3D_Form::onCreated();
    d_playSongName = static_cast<M3D_Label*>(getChild(Res_FormPlay::playSongName));
    d_nextSongName = static_cast<M3D_Label*>(getChild(Res_FormPlay::nextSongName));
}
//----------------------------------------------------------------------------//
void FormPlay::onDestroyed()
{
    M3D_Form::onDestroyed();
    M3D_DebugPrint("onDestroyed");
}

void FormPlay::onActivated(ActivationEventArgs& e)
{
    M3D_Form::onActivated(e);

    //eventHandle = static_cast<appKRK*>(getApp());
//    if(playerListener == nullptr)
//    {
//        //MKConfig* config = MKConfig::getSingletonPtr();
//        playerListener = EventListenerCustom::create(appKRK::Event_BatchPlayer, [=](EventCustom* event)
//        {
//            if(isVisible() == true)
//            {
//                M3D_Log *eventData = (M3D_Log *)(event->getUserData());
//                refreshPlayerInfo(eventData);
//            }
//        });
//        eventHandle->addListener(playerListener);
//    }
//    d_log = getApp()->getFormLog(FrmPlay_ID);
//    m_curSongName = d_log->getParamString(LogParam::fmParam_DLFileName,"");
//	//m_curSongName = "020648.OKF";
//	m_curSongName = "1.mkv";
//    if (m_curSongName != "")
//    {
//#ifdef PLATFORM_UNIX
//		g_DownloadPath = "/mnt/sda1/Karaoke/okf/020/";
//#endif
//
//        String songpath = g_DownloadPath + m_curSongName;
//		M3D_DebugPrint("---------g_DownloadPath:%s-----", g_DownloadPath.c_str());
//        if (krk_fexist(songpath.c_str()))
//        {
//            d_playSongName->hide();
//            d_nextSongName->hide();
//            playSong(songpath);
//        }
//    }

    if(listenerList.size() == 0)
    {
        MKConfig* config = MKConfig::getSingletonPtr();
        appKRK *app = static_cast<appKRK*>(getApp());
        EventListenerCustom *_listener = NULL;

        _listener = EventListenerCustom::create(appKRK::Event_BatchPlayerPlaying, [=](EventCustom* event)
        {
            M3D_DebugPrint("-----appKRK::Event_BatchPlayerPlaying-----------\n");
            if(isVisible() == true)
            {
                M3D_Log *eventData = (M3D_Log *)(event->getUserData());
                refreshPlayerInfo(eventData);
            }
        });
        app->addListener(_listener);
        listenerList.push_back(_listener);
		//17.5.5/houhs: 播放结束时回调到这里
        _listener = EventListenerCustom::create(appKRK::Event_BatchPlayerStopped, [=](EventCustom* event)
        {
            M3D_DebugPrint("---------------appKRK::Event_BatchPlayerStopped---------------\n");
            if(isVisible() == true)
            {
                M3D_Log *eventData = (M3D_Log *)(event->getUserData());
                int score = eventData->getParamInt("score", 0);
                int playerType = eventData->getParamInt("playerType", 0);

                playStoped();
                if(playerType == PLAYER_TYPE_MUS)
                {
                    if(score >= 70)
                    {
                        app->stopUIbg();
                        M3D_Log* log = app->getFormLog(FrmScore_ID);
                        log->setParamInt("Score", score);
                        log->setParamInt("SongIndex", getSongIndex());
                        log->setParamString("SongName", getSongName());
                        app->transitionForm(FrmScore_ID, FrmPlay_ID, FORM_TRANSITION_ANIMATION::ANIMATION_NONE, false);
                    }
                    else
                    {
                        app->playNextSong();
                    }
                }
                else if(playerType == PLAYER_TYPE_VIDEO)
                {
                    if(score != 0)
                    {
                        M3D_Log* log = app->getFormLog(FrmScore_ID);
                        log->setParamInt("Score", score);
                        log->setParamInt("SongIndex", getSongIndex());
                        log->setParamString("SongName", getSongName());
                        app->transitionForm(FrmScore_ID, FrmPlay_ID, FORM_TRANSITION_ANIMATION::ANIMATION_NONE, false);
                    }
                    else
                    {
                        app->playNextSong();
                    }
                }
            }
        });
        app->addListener(_listener);
        listenerList.push_back(_listener);

        _listener = EventListenerCustom::create(appKRK::Event_PlaySong, [=](EventCustom* event)
        {
            M3D_DebugPrint("------------appKRK::Event_PlaySong-------------\n");
            if(isVisible() == true)
            {
                M3D_Log *eventData = (M3D_Log *)(event->getUserData());
                d_songIndex = eventData->getParamInt("songIndex", 0);
                d_songType = eventData->getParamInt("songType", 0);
                d_fileType = eventData->getParamInt("fileType", 0);
                d_songName = eventData->getParamString("songName", "");
                d_userName = eventData->getParamString("userName", "");
                d_userId = eventData->getParamString("userId", "");

                if(d_fileType == SONG_FILETYPE_MTV)
                {
                    //d_track->setImage(TrackImage_ID + config->getValue("VocalType"));
                    //d_track->show();
                }
                else if(d_songType == 2)
                {
                    //d_vocal->setImage(VocalImage_ID + config->getValue("VocalType"));
                    //d_vocal->show();
                }

                refreshSongInfo();
                this->activate();
            }
        });
        app->addListener(_listener);
        listenerList.push_back(_listener);

        _listener = EventListenerCustom::create(appKRK::Event_BatchPlayerError, [=](EventCustom* event)
        {
            M3D_DebugPrint("--------appKRK::Event_BatchPlayerError------------\n");
            if(isVisible() == true)
            {
                M3D_Log *eventData = (M3D_Log *)(event->getUserData());
                int songIndex = eventData->getParamInt("songIndex", -1);

                appKRK *app = static_cast<appKRK*>(getApp());
                if(songIndex < 0)
                {
                    M3D_Log* log = app->getFormLog(FrmPlay_ID);
                    int lastFormID = log->getParamInt("LastForm", FrmNumSong_ID);
                    app->transitionForm(lastFormID, FrmPlay_ID, FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT, false);
                }
                else
                {
                    app->playNextSong();
                }
            }
        });
        app->addListener(_listener);
        listenerList.push_back(_listener);
    }

    //start play
    appKRK *app = static_cast<appKRK*>(getApp());
    app->playNextSong();
}

void FormPlay::onDeactivated(ActivationEventArgs& e)
{
    M3D_Form::onDeactivated(e);
}

void FormPlay::onActionStart()
{
    M3D_Form::onActionStart();
    //M3D_DebugPrint("FormPlay::onActionStart");
}

void FormPlay::onActionEnd()
{
    M3D_Form::onActionEnd();
    //M3D_DebugPrint("FormPlay::onActionEnd");
}
//----------------------------------------------------------------------------//
void FormPlay::onTimeout(EventArgs& e)
{
    TimerEventArgs& te = (TimerEventArgs&)e;
    if (te.d_name == ShowTitle)
    {
        if (d_ShowNextInfoFlag == NEXT_SONGINFO_SHOW)
        {
            d_nextSongName->hide();
            d_playSongName->show();
            d_ShowNextInfoFlag = NEXT_SONGINFO_HIDE;
        }
        else if(d_ShowNextInfoFlag == NEXT_SONGINFO_HIDE)
        {
            d_nextSongName->show();
            d_playSongName->hide();
            d_ShowNextInfoFlag = NEXT_SONGINFO_SHOW;
        }
    }
}
//----------------------------------------------------------------------------//
void FormPlay::onCharacter(KeyEventArgs& e)
{
    if (isDisabled() || !isActive())
    {
        //M3D_Form::onCharacter(e);
        return;
    }
    switch (e.codepoint)
    {
    case M3D_UI_KEY_KARAOKE:
        /*if (getApp()->getForm(FrmShortMain_ID) != NULL && getApp()->getForm(FrmShortMain_ID)->isClosing())
        {
        break;
        }*/
        hidePlayTitle();

        /*if(appKRK::MemoryFormID == FrmShortMain_ID || appKRK::MemoryFormID == 0)
        	getApp()->delFormLog(FrmShortMain_ID);
        else if(appKRK::MemoryFormID == FrmShortSingerSong_ID || appKRK::MemoryFormID == FrmShortDownloadSong_ID || appKRK::MemoryFormID == FrmShortSinger_ID)
        	getApp()->setFormLog(appKRK::MemoryFormID, appKRK::MemoryFormLog);*/

        //getApp()->showForm(appKRK::MemoryFormID);
        getApp()->showForm(FrmShortMain_ID);
        break;
    case M3D_UI_KEY_ENTER:
    {
        isEnterPressed = true;
        handleCmdStop();
    }
    break;
    case M3D_UI_KEY_DOWN:
        break;
    case M3D_UI_KEY_LEFT:
        break;
    case M3D_UI_KEY_RIGHT:
        break;
    case M3D_UI_KEY_RETURN:
    {
        //playStoped();
    }
    break;
    case M3D_UI_KEY_PLAY:
        handleCmdPlay(e);
        break;
    case M3D_UI_KEY_PAUSE:
        handleCmdPause(e);
        break;
    case M3D_UI_KEY_STOP:
        handleCmdStop();
        break;
	case M3D_UI_KEY_MP3:
		hidePlayTitle();
		handleMP3Clicked(e);
		break;
	case M3D_UI_KEY_MTV:
		hidePlayTitle();
		handleMTVClicked(e);
		break;
	case M3D_UI_KEY_MOVIE:
		hidePlayTitle();
		handleMOVIEClicked(e);
		break;
	case M3D_UI_KEY_SETUP:
	{
		M3D_Log* mlog = getApp()->getFormLog(FrmSetup_ID);
		mlog->setParamInt("LastForm", getID());
		getApp()->showForm(FrmSetup_ID);
	}
	break;
    /*
    	case M3D_UI_KEY_N:	//切歌
    	{
    		destroyTimer(ShowTitle);
    		d_playSongName->setString("");
    		d_nextSongName->setString("");
    		d_playSongName->hide();
    		d_nextSongName->hide();

    		int songIndex = d_log->getParamInt(LogParam::fmParam_FocusSongIdx, 0);//歌曲下标
    		//如果这首歌不是最后一首,播放下一首
    		if (songIndex < eventHandle->getDownloadTotalCnt()- 1) {
    			playNextSong(songIndex);
    		}
    	}
    break;
    	case M3D_UI_KEY_P:	//播放/暂停
    	{
    		playerHandle = (MKPlayer*)MKPlayer::getSingletonPtr();
    		playerHandle->pause();
    	}
    	break;*/
    default:
        break;
    }

    M3D_Form::onCharacter(e);
}

bool FormPlay::playSong(String filepath)
{
    bool ret =false;
    PlayParam _playParam;

    _playParam.SongPath = filepath;
    M3D_DebugPrint("-------+++filepath====%s______", filepath.c_str());
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
    //--------------------------------------

    int namelen = m_curSongName.length();
    String suffix = m_curSongName.substr(namelen-4,4);
    if (suffix.compare(".mp3") == 0 || suffix.compare(".wav") == 0)
    {
        _playParam.FileType = SONG_FILETYPE_MP3;
    }
    else if (suffix.compare(".MUS") == 0)
    {
        _playParam.FileType = SONG_FILETYPE_MUS;
    }
    else if (suffix.compare(".okf") == 0)
    {
        appKRK* app = static_cast<appKRK*>(getApp());
        m_typeOfUIbg = app->m_bgvType;
        app->stopUIbg();

        _playParam.FileType = SONG_FILETYPE_MTV;
    }
    else
    {
        _playParam.FileType = SONG_FILETYPE_MTV;
    }

    playerHandle = (MKPlayer*)MKPlayer::getSingletonPtr();
    ret = playerHandle->playSong(_playParam);
    if (ret == true)
    {
        // TODO  hitInfo show Current SongName
    }
    return ret;
}

void FormPlay::refreshPlayerInfo(M3D_Log *eventData)
{
    int ret = eventData->getParamInt(appKRK::Event_BatchPlayer, 0);
    int songIndex;
    if(ret == MKPlayer_Event::TitleHide)
    {
    }
    else if (ret == MKPlayer_Event::Playing)
    {
        //setHitInfo();
        createTimer(ShowTitle, 10000.0f, true, 0);

        playerHandle = (MKPlayer*)MKPlayer::getSingletonPtr();
        String playState = playerHandle->getPlayState();
        setPlayStatus(playState);
    }
    else if (ret == MKPlayer_Event::Stopped)
    {
        destroyTimer(ShowTitle);
        d_playSongName->setString("");
        d_nextSongName->setString("");
        d_playSongName->hide();
        d_nextSongName->hide();
        d_ShowNextInfoFlag = NEXT_SONGINFO_SHOW;
        //songIndex = d_log->getParamInt(LogParam::fmParam_FocusSongIdx, 0);//歌曲下标
        //循环播放，如果这首歌不是最后一首且不是按Enter键停止播放的
        /*if (songIndex < eventHandle->getDownloadTotalCnt()- 1 && isEnterPressed == false)
        {
            playNextSong(songIndex);
            d_log->setParamInt(LogParam::fmParam_FocusSongIdx, songIndex + 1);
        }
        else*/
        {
            playerHandle = (MKPlayer*)MKPlayer::getSingletonPtr();
            String playState = playerHandle->getPlayState();
            setPlayStatus(playState);
        }
    }
    /*
    else if((ret == MKPlayer_Event::Playing) || (ret == MKPlayer_Event::Stopped)){
    	playerHandle = (MKPlayer*)MKPlayer::getSingletonPtr();
    	String playState = playerHandle->getPlayState();
    	setPlayStatus(playState);
    }
    */
    else if (ret == MKPlayer_Event::AutoSeekEnd)
    {

    }
    else if(ret == MKPlayer_Event::StaffShow)
    {

    }
}

void FormPlay::refreshSongInfo(void)
{
    MKConfig* config = MKConfig::getSingletonPtr();
    ReqPhoneDB* reqDb = (ReqPhoneDB*)ReqDB::getSingletonPtr();
    if(static_cast<appKRK*>(getApp())->getPlayState() == PLY_EVENT_GETSTATE_STATE_STOPPED)
    {
        destroyTimer(ShowTitle);
        destroyTimer(HideTitleTimer);
        //setTitleStatus(config->getValue("Title"));
        d_playSongName->setString("");
        d_nextSongName->setString("");
        d_playSongName->show();
        d_nextSongName->hide();
        //d_vocal->hide();
        //d_track->hide();
        //d_record->hide();

        //hideNumber();
    }
    else
    {
        //d_num = 0;
        memset(&d_NextInfo, 0, sizeof(d_NextInfo));
        if (reqDb->ReqReservedSongGetFirstEx(&d_NextInfo))
        {
            d_nextSongName->setString(String("Next : ") + d_NextInfo.SongName);
            d_nextSongName->hide();
            d_ShowNextInfoFlag = NEXT_SONGINFO_HIDE;
        }
        else
        {
            d_ShowNextInfoFlag = NEXT_SONGINFO_LOAD_FAILED;
        }
        d_playSongName->setString(String("Playing : ") + d_songName);
        createTimer(ShowTitle, 10000.0f, true, 0);
        if(d_fileType == SONG_FILETYPE_MTV)
            createTimer(HideTitleTimer, 30000.0f, true, 0);

        /*setStateSexIcon(-1);
        setStateKeyIcon(config->getValue("KeyVol"));
        setStateTempoIcon(config->getValue("Tempo"));
        setStateMelodyIcon(config->getValue("AccomanyVol"));*/

        //netCooKaraLan::ResetPlayInfo();
        //netCooKaraLan::SetCurSongInfo(d_songIndex, 1, d_songName.c_str(), d_NextInfo.SongName, d_userName.c_str(), "");
    }
}
int FormPlay::getSongIndex(void)
{
    return d_songIndex;
}

std::string FormPlay::getSongName(void)
{
    return d_songName;
}
void FormPlay::setPlayStatus(String playStatus)
{
    M3D_DebugPrint("===setPlayStatus=====playStatus[%s]========\n",playStatus.c_str());
    if (playStatus == PLY_EVENT_GETSTATE_STATE_PAUSED)
    {
    }
    else if (playStatus == PLY_EVENT_GETSTATE_STATE_PLAYING)
    {
    }
    else if (playStatus == PLY_EVENT_GETSTATE_STATE_STOPPED)
    {
        isEnterPressed = false;
        //playStoped();
    }
}

void FormPlay::playStoped()
{
    refreshSongInfo();
    appKRK* app = static_cast<appKRK*>(getApp());

    ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
    int nowPlaySongType = reqDB->getPlaySongType();
    if (nowPlaySongType == PLAY_SONG_TYPE_MTV || nowPlaySongType == PLAY_SONG_TYPE_MOVIE)
    {
        app->playUIbg(app->m_bgvType);
    }
    app->transitionForm(FrmNumSong_ID, getID(), FORM_TRANSITION_ANIMATION::RIGHTIN_RIGHTOUT);
}

bool FormPlay::handleCmdPlay(const CEGUI::EventArgs& e)
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(d_playState != 1)
    {
        player->resume();
    }
    return true;
}

bool FormPlay::handleCmdPause(const CEGUI::EventArgs& e)
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    if(d_playState == 1)
    {
        player->pause();
    }
    return true;
}

void FormPlay::handleCmdStop()
{
    appKRK *app = static_cast<appKRK*>(getApp());
    app->stop();
}

bool FormPlay::handleMP3Clicked(const CEGUI::EventArgs& e)
{
	M3D_Log bubbleLog;

	/*bubbleLog.bundingType = REQDB_TYPE_DOWNLOAD;
	bubbleLog.bundingSubType = REQDB_SUBTYPE_MP3;
	bubbleLog.bundingStrPara = "";
	bubbleLog.lastOverlapForm = getID();
	bubbleLog.bundingIntPara = 0;
	bubbleLog.intValue[0] = 0;

	if (getApp()->getForm(FrmShortDownloadSong_ID) != NULL && getApp()->getForm(FrmShortDownloadSong_ID)->isClosing())
	{
	return false;
	}

	getApp()->setFormLog(FrmShortDownloadSong_ID, bubbleLog);
	getApp()->showForm(FrmShortDownloadSong_ID);*/
	getApp()->showForm(FrmShortMp3_ID);
	return true;
}

//----------------------------------------------------------------------------//
bool FormPlay::handleMTVClicked(const CEGUI::EventArgs& e)
{
	M3D_Log bubbleLog;

	/*bubbleLog.bundingType = REQDB_TYPE_DOWNLOAD;
	bubbleLog.bundingSubType = REQDB_SUBTYPE_MTV;
	bubbleLog.bundingStrPara = "";
	bubbleLog.lastOverlapForm = getID();
	bubbleLog.bundingIntPara = 0;
	bubbleLog.intValue[0] = 0;

	if (getApp()->getForm(FrmShortDownloadSong_ID) != NULL && getApp()->getForm(FrmShortDownloadSong_ID)->isClosing())
	{
	return false;
	}

	getApp()->setFormLog(FrmShortDownloadSong_ID, bubbleLog);
	getApp()->showForm(FrmShortDownloadSong_ID);*/
	getApp()->showForm(FrmShortMTV_ID);
	return true;
}

//----------------------------------------------------------------------------//
bool FormPlay::handleMOVIEClicked(const CEGUI::EventArgs& e)
{
	M3D_Log bubbleLog;

	/*bubbleLog.bundingType = REQDB_TYPE_DOWNLOAD;
	bubbleLog.bundingSubType = REQDB_SUBTYPE_MOVIE;
	bubbleLog.bundingStrPara = "";
	bubbleLog.lastOverlapForm = getID();
	bubbleLog.bundingIntPara = 0;
	bubbleLog.intValue[0] = 0;*/

	/*if (getApp()->getForm(FrmShortDownloadSong_ID) != NULL && getApp()->getForm(FrmShortDownloadSong_ID)->isClosing())
	{
		return false;
	}

	getApp()->setFormLog(FrmShortDownloadSong_ID, bubbleLog);
	getApp()->showForm(FrmShortDownloadSong_ID);*/
	getApp()->showForm(FrmShortMovie_ID);
	return true;
}
void FormPlay::updatePlayerInfo(void)
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();

    assert(player != NULL);

    d_playState = player->getPlayState() == PLY_EVENT_GETSTATE_STATE_PAUSED? 0 : 1;
    M3D_DebugPrint("d_playState :%d\n",d_playState);

    setPlayStatus(d_playState);

    if (d_showStatusFlag == 0)
    {
        d_showStatusFlag = 1;
//#ifndef NO_FAVO_ICON
//		d_stateBar->getChild(Favo_ID)->show();
//#endif
//		d_stateBar->getChild(PlayStatus_ID)->show();
//		//d_stateBar->getChild(VocalState_ID)->show();
//		if (static_cast<appKRK*>(getApp())->d_repeatKaraFlag == 1)
//			d_repeatIcon->show();
//
//		if(d_coinType == 1) 	//time mode
//		{
//			static_cast<appKRK*>(getApp())->setCoinIsTimeMode(true);
//			KM_CoinStart(1);	//0 or 1 is the same
//		}
    }
}

void FormPlay::setHitInfo()
{
    d_log = getApp()->getFormLog(FrmPlay_ID);
    int songIndex = d_log->getParamInt(LogParam::fmParam_FocusSongIdx, 0); //歌曲下标
    if (songIndex >= 0 && songIndex < eventHandle->getDownloadTotalCnt())
    {
        m_curSongName = eventHandle->getDLFileNameByPosition(songIndex);
        m_curSongName = m_curSongName.substr(0, m_curSongName.find_last_of('.')); //当前播放歌曲名称

        if (songIndex == eventHandle->getDownloadTotalCnt() - 1)	//如果是最后一首歌曲，下一首的下标应为0
            songIndex = -1;
        m_nextSongName = eventHandle->getDLFileNameByPosition(songIndex + 1); //下一首歌曲名称
        m_nextSongName = m_nextSongName.substr(0, m_nextSongName.find_last_of('.'));
        d_playSongName->setString(m_curSongName);
        d_nextSongName->setString("Next : " + m_nextSongName);
    }
}

void FormPlay::playNextSong(int curSongIndex)
{
    m_curSongName = eventHandle->getDLFileNameByPosition(curSongIndex + 1);
    String songPath = g_DownloadPath + m_curSongName;
    playSong(songPath);
}

void FormPlay::hidePlayTitle(void)
{
    MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
    MKConfig* config = (MKConfig*)MKConfig::getSingletonPtr();
    if(config->getValue("Ifun"))
    {
        player->setStaff(PLY_CMD_PARA_VALUE_ON);
    }
    //player->setScore(PLY_CMD_PARA_VALUE_ON);
    player->setLyric(PLY_CMD_PARA_VALUE_ON);
    d_playSongName->hide();
    d_nextSongName->hide();

    //if (config->getValue("Title"))
    //{
    /*d_stateBar->hide();
    ControlServerPos(CTRL_TYPE_UP, SERVER_MODE_TITLE);*/
    //}
    /*d_repeatIcon->hide();
    d_prog->hide();

    resetTitleShow();*/
}

int FormPlay::MCodeConvert_UTF8toGB2312(const char* in_utf8, char* out_gb2312, int Len1, int Len2)
{
    CodeConverter cc = CodeConverter("UTF-8","gb18030");//use gb18030 to instead of gb2312
    cc.convert(in_utf8, &Len1, out_gb2312, &Len2);
    return Len2;
}
}
