/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKPlayer.cpp
** Revision : 1.00											
**																	
** Description: MKPlayer base on player service
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
#include <k_global.h>
#include <serviceMgr.h>

#include "MKString.h"
#include "MKPlayer.h"
#include "MKKKEDev.h"
//#include "MKConfig.h"

namespace	CEGUI
{
  /*
extern const int MusicValueCfg[11]={
	0, 9, 17, 25, 33, 41, 49, 57,
	65,//default
	80, 90
};
*/
template<> MKPlayer* MKSingleton<MKPlayer>::ms_Singleton = 0;
const std::string MKPlayer::m_name = "player";
int MKPlayer::m_EndedStop = true;
int MKPlayer::m_AuthPass = false;
int MKPlayer::m_EmbeddedAudio = false;
int MKPlayer::m_effectMusicEnabled = false;

// - commands
const std::string MKPlayer::m_cmdInit = "init";
const std::string MKPlayer::m_cmdDeInit = "deinit";
const std::string MKPlayer::m_cmdInitAudio = "initaudio";
const std::string MKPlayer::m_cmdDeInitAudio = "deinitaudio";
const std::string MKPlayer::m_cmdUpdateAudio = "updateaudio";
const std::string MKPlayer::m_cmdInitView = "initview";
const std::string MKPlayer::m_cmdDeInitView = "deinitview";
const std::string MKPlayer::m_cmdSetViewUpdate = "setviewupdate";
const std::string MKPlayer::m_cmdSetViewVisible = "setviewvisible";
const std::string MKPlayer::m_cmdViewUpdate = "updateview";
const std::string MKPlayer::m_cmdPlay = "play";
const std::string MKPlayer::m_cmdPause = "pause";
const std::string MKPlayer::m_cmdResume = "resume";
const std::string MKPlayer::m_cmdStop = "stop";
const std::string MKPlayer::m_cmdVoiceRecord = "voicerecord";
const std::string MKPlayer::m_cmdStopVoiceRecord = "stopvoicerecord";
const std::string MKPlayer::m_cmdSetVol = "setvol";
const std::string MKPlayer::m_cmdSetVocal = "setvocal";
const std::string MKPlayer::m_cmdSeekTime = "seektime";
const std::string MKPlayer::m_cmdAutoSeek = "autoseek";
const std::string MKPlayer::m_cmdSetStaff = "setstaff";
const std::string MKPlayer::m_cmdSetScore = "setscore";
const std::string MKPlayer::m_cmdSetLyric = "setlyric";
const std::string MKPlayer::m_cmdSetMIC = "setmic";
const std::string MKPlayer::m_cmdGetState = "getstate";
const std::string MKPlayer::m_cmdGetLyric = "getlyric";
const std::string MKPlayer::m_cmdGetScore = "getscore";
const std::string MKPlayer::m_cmdGetBufferingFlag = "getbufferingflag";
const std::string MKPlayer::m_cmdGetPlayTime = "getplaytime";
const std::string MKPlayer::m_cmdGetTotalTime = "gettotaltime";
const std::string MKPlayer::m_cmdTestLatency = "testlatency";
const std::string MKPlayer::m_cmdChangeAudioIF = "changeaudioif";
const std::string MKPlayer::m_cmdGetPlayerType = "getplayertype";
const std::string MKPlayer::m_cmdSetPlayerType = "setplayertype";
const std::string MKPlayer::m_cmdPlayBgv = "playbgv";
const std::string MKPlayer::m_cmdStopBgv = "stopbgv";
const std::string MKPlayer::m_cmdSetBgvType = "setbgvtype";
const std::string MKPlayer::m_cmdInitBgvView = "initbgvview";
const std::string MKPlayer::m_cmdDeInitBgvView = "deinitbgvview";
const std::string MKPlayer::m_cmdGetBgvState = "getbgvstate";
const std::string MKPlayer::m_cmdEnableEffectMusic = "enableeffectmusic";
const std::string MKPlayer::m_cmdPlayEffectMusic = "playeffectmusic";
const std::string MKPlayer::m_cmdSetSPSoundEffect = "setspsoundeffect";

// - parameters
const std::string MKPlayer::m_paraState = "state";
const std::string MKPlayer::m_paraLatency = "latency";
const std::string MKPlayer::m_paraInLatency = "inlatency";
const std::string MKPlayer::m_paraOutLatency = "outlatency";
const std::string MKPlayer::m_paraInChannels = "inchannel";
const std::string MKPlayer::m_paraOutChannels = "outchannel";
const std::string MKPlayer::m_paraInRate = "inrate";
const std::string MKPlayer::m_paraOutRate = "outrate";
const std::string MKPlayer::m_paraShow = "show";
const std::string MKPlayer::m_paraEffect = "effect";
const std::string MKPlayer::m_paraEnabled = "enabled";
const std::string MKPlayer::m_paraPlayMode = "playmode";
const std::string MKPlayer::m_paraPlayRec = "playrec";
const std::string MKPlayer::m_paraStopScore = "score";
const std::string MKPlayer::m_paraLyricAlign = "align";
const std::string MKPlayer::m_paraRecFmt = "recfmt";
const std::string MKPlayer::m_paraRecEncFmt = "recencfmt";
const std::string MKPlayer::m_paraEmbedded = "embedded";
const std::string MKPlayer::m_paraLyricFont = "fontname";
const std::string MKPlayer::m_paraIfunNum = "num";

// - parameter value of 'state'
const std::string MKPlayer::m_statePlaying = "playing";
const std::string MKPlayer::m_stateStopped = "stopped";
const std::string MKPlayer::m_stateStopping = "stopping";
const std::string MKPlayer::m_statePaused = "paused";
const std::string MKPlayer::m_statePausing = "pausing";

// - parameter value of 'changeaudioif'
const std::string MKPlayer::m_audioIFStandard = "default";
const std::string MKPlayer::m_audioIFKKEBox = "kkebox";
const std::string MKPlayer::m_audioIFKKEMini = "kkemini";
const std::string MKPlayer::m_audioIFEmbedded = "embedded";

// - parameter value of 'playmode'
const std::string MKPlayer::m_playModeSong = "song";
const std::string MKPlayer::m_playModeRec = "rec";

const int MKPlayer::VIEW_NONE = 0;
const int MKPlayer::VIEW_LYRIC = 1;
const int MKPlayer::VIEW_STAFF = 2;
const int MKPlayer::VIEW_ALL = 3;

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

MKPlayer::MKPlayer(void* owner) : MKService(m_name, owner)
{

}

MKPlayer::~MKPlayer(void)
{
	
}

//----------------------------------------------------------------------------//
//- call 'init' on app start up, after 'initAudio'
//----------------------------------------------------------------------------//
int MKPlayer::init(const std::string& resFile)
{
	int ret;

	ret = exec(m_cmdInit, resFile);

	//MKConfig* cfg = MKConfig::getSingletonPtr();

	setCmdPara(m_cmdSetMIC,m_paraInChannels,"2");
	setCmdPara(m_cmdSetMIC,m_paraOutChannels,"2");
	setCmdPara(m_cmdSetMIC,m_paraInRate,"48000");
	setCmdPara(m_cmdSetMIC,m_paraOutRate,"48000");
	exec(m_cmdSetMIC, "");

	setPlayPara("filesize", "0");
	setPlayPara("hwaudio", "0");
	setPlayPara("hwvideo", "1");
	setPlayPara("scorelevel", "normal");
	setPlayPara("cidkey", "12345678");
	setPlayPara("privatekey", "in");
	setPlayPara("okfproductid", "1");
	setPlayPara("mussubtype", "midi");
	setPlayPara("mixmode", "0");
	setPlayPara(m_paraRecFmt, "adpcm");
	setPlayPara(m_paraRecEncFmt, "adpcm");
	
	setPlayPara(m_paraPlayMode, m_playModeSong);

	setVol(PLY_CMD_SETVOL_TOTAL, MAX_VOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_ACCOM, MAX_VOLUME_VALUE); 	//???
	setVol(PLY_CMD_SETVOL_VOICE, MAX_VOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_MIDI, MAX_VOLUME_VALUE);      // F20 not use
	setVol(PLY_CMD_SETVOL_RHYTHM, MAX_VOLUME_VALUE);
	//cfg->setValue("KeyVol", cfg->getDefaultValue("KeyVol"));
	setVol(PLY_CMD_SETVOL_TONE, (MAX_TONE_VALUE+MIN_TONE_VALUE)/2);
	//cfg->setValue("Tempo", cfg->getDefaultValue("Tempo"));
	setVol(PLY_CMD_SETVOL_TEMPO, (MAX_TEMPO_VALUE+MIN_TEMPO_VALUE)/2);
	setVol(PLY_CMD_SETVOL_REC, MAX_VOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_REVERB, 30);      // F20 not use
	setVol(PLY_CMD_SETVOL_MICL, MAX_MICVOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_MICR, MAX_MICVOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_WMICL, MAX_MICVOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_WMICR, MAX_MICVOLUME_VALUE);
	setVol(PLY_CMD_SETVOL_ECHO, MAX_ECHO_VALUE/2);

	//setThread(1);
	//setSeperateUpdate(true);
	return ret;
}

//----------------------------------------------------------------------------//
//- call 'deinit' on app killed, before 'deinitAudio'
//----------------------------------------------------------------------------//
int MKPlayer::deinit(void)
{
	//setThread(0);
	int ret = exec(m_cmdDeInit, m_nullstr);

	return ret;
}

//----------------------------------------------------------------------------//
//- call 'initAudio' just before 'init', if call it after 'init', do nothing
//----------------------------------------------------------------------------//
int MKPlayer::initAudio(const std::string& audioIF)
{
	int ret = exec(m_cmdInitAudio, audioIF);
	m_AuthPass = true;
	if (ret == 2)
		m_EmbeddedAudio = true;
	
	return ret;
}

//----------------------------------------------------------------------------//
//- call 'deinitAudio' just after 'deinit', if call it before 'deinit', audio output is unknown
//----------------------------------------------------------------------------//
int MKPlayer::deinitAudio(void)
{
	return exec(m_cmdDeInitAudio, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::updateAudio(void)
{
	return exec(m_cmdUpdateAudio, m_nullstr);
}

//----------------------------------------------------------------------------//
//- type: video/music/picture/mus
//----------------------------------------------------------------------------//
int MKPlayer::initView(const std::string& type)
{
	return exec(m_cmdInitView, type);
}

//----------------------------------------------------------------------------//
//- type: video/music/picture/mus
//----------------------------------------------------------------------------//
int MKPlayer::deinitView(const std::string& type)
{
	return exec(m_cmdDeInitView, type);
}
	
//----------------------------------------------------------------------------//
//- call 'initBgvView' after bgv surface is created
//----------------------------------------------------------------------------//
int MKPlayer::initBgvView(const std::string& type)
{
	return exec(m_cmdInitBgvView, type);
}

//----------------------------------------------------------------------------//
//- call 'deinitBgvView' before bgv surface is destroyed
//----------------------------------------------------------------------------//
int MKPlayer::deinitBgvView(const std::string& type)
{
	return exec(m_cmdDeInitBgvView, type);
}

//----------------------------------------------------------------------------//
//- true, call viewUpdate by yourself, false, viewupdate will be called automatically
//----------------------------------------------------------------------------//
int MKPlayer::setSeperateUpdate(int singleUpdate)
{
	if (singleUpdate)
		return exec(m_cmdSetViewUpdate, "1");
	else
		return exec(m_cmdSetViewUpdate, "0");
}

//----------------------------------------------------------------------------//
//- true, display title/lyric/staff, false, only play music, no title/lyric/staff
//----------------------------------------------------------------------------//
int MKPlayer::setViewVisible(int visible)
{ 
	return exec(m_cmdSetViewVisible, MKString::valueOf(visible));
}

//----------------------------------------------------------------------------//
int MKPlayer::setPlayPara(const std::string& para, const std::string& value)
{
	return setCmdPara(m_cmdPlay, para, value);
}

//----------------------------------------------------------------------------//
std::string MKPlayer::getPlayPara(const std::string& para)
{
	return getCmdParaValue(m_cmdPlay, para);
}

//----------------------------------------------------------------------------//
int MKPlayer::isAuthPassed(void)
{
	return m_AuthPass;
}

//----------------------------------------------------------------------------//
int MKPlayer::play(void)
{
	if (m_AuthPass) {
		m_EndedStop = true;
		return exec(m_cmdPlay, m_nullstr);
	} else {
		KRK_PRINTF("============ AUTH FAIL, CAN NOT PLAY ===========");
		return -1;
	}
}

int MKPlayer::resume(void)
{
	return exec(m_cmdResume, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::pause(void)
{
	return exec(m_cmdPause, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::stop(void)
{
	m_EndedStop = false;
	int ret = exec(m_cmdStop, m_nullstr);
	return ret;
}

//----------------------------------------------------------------------------//
int MKPlayer::voiceRecord(const std::string& outfile, int devsamplerate, int filesamplerate, int channels, int mutetime)
{
	setCmdPara(m_cmdVoiceRecord,"devsamplerate",MKString::valueOf(devsamplerate));
	setCmdPara(m_cmdVoiceRecord,"filesamplerate",MKString::valueOf(filesamplerate));
	setCmdPara(m_cmdVoiceRecord,"channels",MKString::valueOf(channels));
	setCmdPara(m_cmdVoiceRecord,"mutetime",MKString::valueOf(mutetime));
	setCmdPara(m_cmdVoiceRecord,"threshold","2000");
	setCmdPara(m_cmdVoiceRecord,"recfile",outfile);
	return exec(m_cmdVoiceRecord, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::stopVoiceRecord(int hdle)
{
	return exec(m_cmdStopVoiceRecord, MKString::valueOf(hdle));
}

//----------------------------------------------------------------------------//
int MKPlayer::playEffectMusic(const std::string& path)
{
	if (m_effectMusicEnabled == false) {
		exec(m_cmdEnableEffectMusic, "1");
		m_effectMusicEnabled = true;
	}
	return exec(m_cmdPlayEffectMusic, path);
	//return 0;
}

int MKPlayer::disableEffectMusic()
{
	exec(m_cmdEnableEffectMusic, "0");
	m_effectMusicEnabled = false;

	return 0;
}

//----------------------------------------------------------------------------//
int MKPlayer::playBgv(const std::string& path)
{
	if (exec(m_cmdGetBgvState, m_nullstr) == 0)
		return exec(m_cmdPlayBgv, path);
	return 0;
}

//----------------------------------------------------------------------------//
int MKPlayer::stopBgv(const std::string& para)
{
	int ret = exec(m_cmdStopBgv, para);
	return ret;
}


//----------------------------------------------------------------------------//
int MKPlayer::setBgvType(const std::string& type)
{
	int ret = exec(m_cmdSetBgvType, type);
	if (ret == 0)
		exec(m_cmdInitBgvView, type);
	return ret;
}

//----------------------------------------------------------------------------//
void MKPlayer::setBgvPlayMode(const std::string& mode)
{
	setCmdPara(m_cmdPlayBgv,"mode",mode);
}

//----------------------------------------------------------------------------//
int MKPlayer::isBgvPlaying(void)
{
	if (exec(m_cmdGetBgvState, m_nullstr) == 1)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------------//
int MKPlayer::isEndedStop(void)
{
	return m_EndedStop;
}

//----------------------------------------------------------------------------//
int MKPlayer::autoSeek(void)
{
	return exec(m_cmdAutoSeek, "");
}

//----------------------------------------------------------------------------//
int MKPlayer::seekTime(int playtime)
{
	return exec(m_cmdSeekTime, MKString::valueOf(playtime));
}

//----------------------------------------------------------------------------//
int MKPlayer::setSPSoundEffect(int setting)
{
	if (setting) {
		return exec(m_cmdSetSPSoundEffect, "on");
	} else {
		return exec(m_cmdSetSPSoundEffect, "off");
	}
}

//----------------------------------------------------------------------------//
//- type [min-max]
//- 
//- total [0-100]
//- accom [0-100]
//- voice [0-100]
//- rhythm [0-100]
//- tone [-6-6]
//- tempo [800-1000]
//- rec [0-100]
//- echo [0-100]
//- mic1 [0-100]
//- mic2 [0-100]
//- wmic1 [0-100]
//- wmic2 [0-100]
//----------------------------------------------------------------------------//
int MKPlayer::setVol(const std::string& type, int value)
{
	setCmdPara(m_cmdSetVol, type, MKString::valueOf(value));
	return exec(m_cmdSetVol, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setVocal(const std::string& value)
{
	return exec(m_cmdSetVocal, value);
}

//----------------------------------------------------------------------------//
int MKPlayer::setStaff(const std::string& value)
{
	setCmdPara(m_cmdSetStaff,m_paraShow,value);
	return exec(m_cmdSetStaff, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setStaffNum(int value)
{
	setCmdPara(m_cmdSetStaff, m_paraIfunNum, MKString::valueOf(value));
	return exec(m_cmdSetStaff, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setScore(const std::string& value)
{
	setCmdPara(m_cmdSetScore,m_paraShow,value);
	return exec(m_cmdSetScore, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setLyric(const std::string& value)
{
	setCmdPara(m_cmdSetLyric,m_paraShow,value);
	return exec(m_cmdSetLyric, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setLyricEffect(const std::string& value)
{
	setCmdPara(m_cmdSetLyric,m_paraEffect,value);
	return exec(m_cmdSetLyric, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setLyricAlign(const std::string& value)
{
	setCmdPara(m_cmdSetLyric,m_paraLyricAlign,value);
	return exec(m_cmdSetLyric, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setLyricFont(const std::string& value)
{
	setCmdPara(m_cmdSetLyric,m_paraLyricFont,value);
	return exec(m_cmdSetLyric, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::enableStaff(int enabled)
{ 
	std::string value;
	if (enabled)
		value = "on";
	else
		value = "off";

	setCmdPara(m_cmdSetStaff,m_paraEnabled,value);
	return exec(m_cmdSetStaff, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::enableLyric(int enabled)
{ 
	std::string value;
	if (enabled)
		value = "on";
	else
		value = "off";

	setCmdPara(m_cmdSetLyric,m_paraEnabled,value);
	return exec(m_cmdSetLyric, m_nullstr);
}

//----------------------------------------------------------------------------//
//- only render lyric and staff
//----------------------------------------------------------------------------//
int MKPlayer::renderView(void)
{
	return exec(m_cmdViewUpdate, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::updateSelf(int timeElapsed)
{
	return update(timeElapsed);
}

//----------------------------------------------------------------------------//
std::string MKPlayer::getPlayState(void)
{
	if (exec(m_cmdGetState, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetState, m_paraState);
	}
	return "";
}

//----------------------------------------------------------------------------//
int MKPlayer::getTotalTime(void)
{
	return exec(m_cmdGetTotalTime, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::getPlayTime(void)
{
	return exec(m_cmdGetPlayTime, m_nullstr);
}

//----------------------------------------------------------------------------//
std::string MKPlayer::getLyric(int lineNo)
{
	int ret = exec(m_cmdGetLyric, MKString::valueOf(lineNo));
	return getEventParaValue(m_cmdGetLyric, "string");
}

//----------------------------------------------------------------------------//
int MKPlayer::getLyric(int lineNo, MKLyricInfo& inf)
{
	int ret = exec(m_cmdGetLyric, MKString::valueOf(lineNo));
	if (ret == -1) {
		return -1;
	} else {
		inf.m_lineStr = getEventParaValue(m_cmdGetLyric, "string");
		inf.m_startTime = getEventParaIntValue(m_cmdGetLyric, "starttime");
		inf.m_endTime = getEventParaIntValue(m_cmdGetLyric, "endtime");
		return 0;
	}
}


//----------------------------------------------------------------------------//
int MKPlayer::getScore(void)
{
	return exec(m_cmdGetScore, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::getStoppedScore(void)
{
	return getEventParaIntValue(m_cmdStop, m_paraStopScore);
}

//----------------------------------------------------------------------------//
//- 1 - buffering, 0 - not buffering
//----------------------------------------------------------------------------//
int MKPlayer::getBufferingFlag(void)
{
	return exec(m_cmdGetBufferingFlag, m_nullstr);
}

//----------------------------------------------------------------------------//
std::string MKPlayer::getPlayMode(void)
{
	return getCmdParaValue(m_cmdPlay, m_paraPlayMode);
}

//----------------------------------------------------------------------------//
int MKPlayer::testLatency(const std::string& tmpfile)
{
	std::string sval;
	exec(m_cmdTestLatency, tmpfile);
	return getEventParaIntValue(m_cmdTestLatency, m_paraLatency);
}

//----------------------------------------------------------------------------//
//- default: java audio
//- kkebox: box
//- kkemini: mini
//----------------------------------------------------------------------------//
int MKPlayer::changeAudioIF(const std::string& audioIF, int playRec)
{
	if (audioIF == m_audioIFStandard)
	{
		setAudioPara(2,2,48000,48000,-1);
	}
	else if (audioIF == m_audioIFEmbedded)
	{
		setEmbeddedAudioPara();
	}
	else
	{
		MKKKEDev* dev = (MKKKEDev*)MKKKEDev::getSingletonPtr();
		int inchannels = dev->getInChannels();
		int outchannels = dev->getOutChannels();
		int samplerate;			

		if (dev->is48KSampleRate() == 1)
		{
			samplerate = 48000;
		}
		else if (dev->is44KSampleRate() == 1)
		{
			samplerate = 44100;
		}
		else
		{
			samplerate = 32000;
		}

		if (audioIF == m_audioIFKKEBox)
			setAudioPara(inchannels,2,samplerate,48000,-1);
		else
			setAudioPara(inchannels,outchannels,samplerate,samplerate,-1);
		dev->setSampleRate(samplerate);
	}
	setCmdPara(m_cmdChangeAudioIF, m_paraPlayRec, MKString::valueOf(playRec));
	return exec(m_cmdChangeAudioIF, audioIF);
}

//----------------------------------------------------------------------------//
const std::string& MKPlayer::getAudioIF(void)
{
	MKKKEDev* dev = (MKKKEDev*)MKKKEDev::getSingletonPtr();
	if (m_EmbeddedAudio)
		return m_audioIFEmbedded;
	else if (dev->getStatus() == 0)
		return m_audioIFStandard;
	else
		return dev->getAudioType();
}

//----------------------------------------------------------------------------//
//- 1: video, 2: music, 3: picture, 4: mus
//----------------------------------------------------------------------------//
int MKPlayer::getPlayerType(void)
{
	return exec(m_cmdGetPlayerType, m_nullstr);
}

//----------------------------------------------------------------------------//
//- type: video/music/picture/mus
//----------------------------------------------------------------------------//
int MKPlayer::setPlayerType(const std::string& type)
{
	return exec(m_cmdSetPlayerType, type);
}

//----------------------------------------------------------------------------//
int MKPlayer::isMVPlayer(void)
{
	if (getPlayerType() == 1)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------------//
int MKPlayer::isMusPlayer(void)
{
	if (getPlayerType() == 4)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------------//
int MKPlayer::setAudioPara(int inChannels, int outChannels, int inRate, int outRate, int latency)
{
	int inLatency;
	int outLatency;
	char tmp[256];

	if (latency == -1)
	{
		inLatency = -1;
		outLatency = -1;
	}
	else	if (latency < 100)
	{
		inLatency = 0;
		outLatency = latency;
	}
	else
	{
		inLatency = 100;
		outLatency = latency - inLatency;
	}
	itoa(inChannels, tmp, 10);
	setCmdPara(m_cmdSetMIC,m_paraInChannels,MKString::valueOf(inChannels));
	setCmdPara(m_cmdSetMIC,m_paraOutChannels,MKString::valueOf(outChannels));
	setCmdPara(m_cmdSetMIC,m_paraInRate,MKString::valueOf(inRate));
	setCmdPara(m_cmdSetMIC,m_paraOutRate,MKString::valueOf(outRate));
	setCmdPara(m_cmdSetMIC,m_paraInLatency,MKString::valueOf(inLatency));
	setCmdPara(m_cmdSetMIC,m_paraOutLatency,MKString::valueOf(outLatency));
	setCmdPara(m_cmdSetMIC,m_paraEmbedded,"0");
	return exec(m_cmdSetMIC, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::setEmbeddedAudioPara()
{
	setCmdPara(m_cmdSetMIC,m_paraEmbedded,"1");
	return exec(m_cmdSetMIC, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKPlayer::getLatency(void)
{
	return getEventParaIntValue(m_cmdTestLatency, m_paraLatency);
}

//----------------------------------------------------------------------------//
int MKPlayer::setLatency(int latency)
{
	return setAudioPara(-1, -1, -1, -1, latency);
}

//----------------------------------------------------------------------------//
int MKPlayer::getPlayerTime(void)
{
	return player_service_getplayertime(m_hdle);
}

bool MKPlayer::playSong(PlayParam _playParam)
{
	bool ret = false;
	d_PlayParam = _playParam;
	int pathlen = 0;
	std::string substr = "";
	
	if(_playParam.SongPath.length() == 0)
	{
		return ret;
	}

	//start play
	//MKPlayer* player = MKPlayer::getSingletonPtr();
	//MKConfig* config = MKConfig::getSingletonPtr();

	//init
#if 1
	setVol(PLY_CMD_SETVOL_ACCOM,d_PlayParam.accomVol);
	setVol(PLY_CMD_SETVOL_VOICE,d_PlayParam.voiceVol);
	setVol(PLY_CMD_SETVOL_MICL,d_PlayParam.micVolL);
	setVol(PLY_CMD_SETVOL_MICR,d_PlayParam.micVolR);
	setVol(PLY_CMD_SETVOL_WMICL,d_PlayParam.wmicVolL);
	setVol(PLY_CMD_SETVOL_WMICR,d_PlayParam.wmicVolR);
	setVol(PLY_CMD_SETVOL_ECHO,d_PlayParam.echoVal);
	setVol(PLY_CMD_SETVOL_TEMPO,d_PlayParam.tempoVal);
	setVol(PLY_CMD_SETVOL_TONE,d_PlayParam.toneVal);
#else
	config->setValue("KeyVol", 0);
	config->setValue("Tempo", 50);
	setVol(PLY_CMD_SETVOL_TONE, 0);
	setVol(PLY_CMD_SETVOL_TEMPO, 1000);
#endif

	if(d_PlayParam.FileType == SONG_FILETYPE_MTV || d_PlayParam.FileType == SONG_FILETYPE_MOVIE
		|| d_PlayParam.FileType == SONG_FILETYPE_MP3)
	{
		setPlayerType("video");
		setPlayPara(PLY_CMD_PLAY_FILE_PATH, d_PlayParam.SongPath);	
		setPlayPara(PLY_CMD_PLAY_SONG_NAME, d_PlayParam.SongName);
		setPlayPara(PLY_CMD_PLAY_REC_ON, d_PlayParam.NeedRecord ? "on": "off");
		setPlayPara(PLY_CMD_PLAY_REC_PATH, d_PlayParam.RecordPath);
		setPlayPara(PLY_CMD_PLAY_PLAY_MODE, "song");
#ifdef _WIN32
		setPlayPara(PLY_CMD_PLAY_HWAUDIO, "0");
		setPlayPara(PLY_CMD_PLAY_HWVIDEO, "0");
#else
		setPlayPara(PLY_CMD_PLAY_HWAUDIO, "1");
		setPlayPara(PLY_CMD_PLAY_HWVIDEO, "1");
#endif
		setPlayPara(PLY_CMD_PLAY_PLAYERTYPE, "video");
		setPlayPara(PLY_CMD_PLAY_SDKVERSION, "17");
		/*
		if (d_PlayParam.vocalType.length()> 0)
			setPlayPara(PLY_CMD_SETVOCAL_VOCAL,d_PlayParam.vocalType);
		else
			setPlayPara(PLY_CMD_SETVOCAL_VOCAL,PLY_CMD_PARA_VALUE_OFF);
		*/
	}else{
		setViewVisible(MKPlayer::VIEW_ALL);
		enableStaff(1);
		enableLyric(1);	
		
		if (d_PlayParam.cidKey != "")
 			setPlayPara(PLY_CMD_PLAY_CIDKEY, d_PlayParam.cidKey);
		if (d_PlayParam.privateKey != "")
			setPlayPara(PLY_CMD_PLAY_PRIVATEKEY, d_PlayParam.privateKey);

		if (d_PlayParam.IsRecord){
			setPlayPara(PLY_CMD_PLAY_PLAY_MODE, "rec");
			pathlen = d_PlayParam.SongPath.length();
			substr = d_PlayParam.SongPath.substr(pathlen-3,3);
			if(substr.compare("AAC") == 0)
				setPlayPara(PLY_CMD_PLAY_RECFMT, PLY_CMD_PLAY_RECFMT_AAC);
			else
				setPlayPara(PLY_CMD_PLAY_RECFMT, PLY_CMD_PLAY_RECFMT_MP3);
			
		}else{
			setPlayPara(PLY_CMD_PLAY_PLAY_MODE, "song");
			pathlen = d_PlayParam.RecordPath.length();
			substr = d_PlayParam.RecordPath.substr(pathlen-3,3);
			if(substr.compare("AAC") == 0)
				setPlayPara(PLY_CMD_PLAY_RECENCFMT, PLY_CMD_PLAY_RECENCFMT_AAC);
			else
				setPlayPara(PLY_CMD_PLAY_RECENCFMT, PLY_CMD_PLAY_RECENCFMT_MP3);
		}
		
		setPlayPara(PLY_CMD_PLAY_REC_ON, d_PlayParam.NeedRecord ? "on": "off");
		
		setPlayPara(PLY_CMD_PLAY_FILE_PATH, d_PlayParam.SongPath);
		setPlayPara(PLY_CMD_PLAY_SONG_NAME, d_PlayParam.SongName);
	
		setPlayPara(PLY_CMD_PLAY_REC_PATH, d_PlayParam.RecordPath);
		if (d_PlayParam.scoreLevel.length()> 0)
			setPlayPara(PLY_CMD_PLAY_SCORE_LEVEL, d_PlayParam.scoreLevel);
		else
			setPlayPara(PLY_CMD_PLAY_SCORE_LEVEL, PLY_CMD_PLAY_SCORE_LEVEL_EASY);
		
		setPlayPara(PLY_CMD_PLAY_STAFF_ON, "on");
		setPlayPara(PLY_CMD_PLAY_SCORE_ON, "on");
		setPlayPara(PLY_CMD_PLAY_LYRIC_ON, "on");

		//setPlayPara(PLY_CMD_PLAY_STAFF_ON, "off");
		//setPlayPara(PLY_CMD_PLAY_SCORE_ON, "off");
		//setPlayPara(PLY_CMD_PLAY_LYRIC_ON, "off"); 
		//setPlayPara(PLY_CMD_PLAY_REC_ON, "off");

		if (d_PlayParam.lyricAlign.length()> 0){
			setPlayPara(PLY_CMD_SETLYRIC_ALIGN, d_PlayParam.lyricAlign);
		}else{
			setPlayPara(PLY_CMD_SETLYRIC_ALIGN, PLY_CMD_SETLYRIC_ALIGN_MIDDLE);
		}
		/*
		if (d_PlayParam.vocalType.length()> 0){
			setPlayPara(PLY_CMD_SETVOCAL_VOCAL,d_PlayParam.vocalType);
		}else{
			setPlayPara(PLY_CMD_SETVOCAL_VOCAL,PLY_CMD_PARA_VALUE_OFF);
		}
		*/
		//char mediatype[16] = {0};
		//sprintf(mediatype, "%d", d_playSongType);
		//setPlayPara(PLY_CMD_PLAY_MEDIATYPE, mediatype);
		std::string d_playSongType = "0";
		if(d_PlayParam.FileType == SONG_FILETYPE_CDG)
		{
			setPlayPara(PLY_CMD_PLAY_MUSSUBTYPE, PLY_CMD_PLAY_MUSSUBTYPE_CDG);
			//setPlayPara(PLY_CMD_PLAY_FILE_PATH_EXT, "E:\\Temp\\1\\MP3G_UNZIPPED.CDG");
			d_playSongType = "1";
			setPlayPara(PLY_CMD_PLAY_MEDIATYPE, d_playSongType);
		}
		else if(d_PlayParam.FileType == SONG_FILETYPE_LYC)
		{
			setPlayPara(PLY_CMD_PLAY_MUSSUBTYPE, PLY_CMD_PLAY_MUSSUBTYPE_LYC);
			//setPlayPara(PLY_CMD_PLAY_FILE_PATH_EXT, "E:\\Project\\MK8171\\MU-B\\KaraokeSystem\\Simulator\\sdcard\\KARAOKE\\SONG\\24\\Can You Feel The Love Tonight_lyrics1.lyric"); //Rolling In The Deep·_lyrics
			//setPlayPara(PLY_CMD_PLAY_FILE_PATH_EXT, "E:\\Project\\MK8171\\MU-B\\KaraokeSystem\\Simulator\\sdcard\\KARAOKE\\SONG\\24\\Rolling In The Deep·_lyrics.lyric"); //
			d_playSongType = "1";
			setPlayPara(PLY_CMD_PLAY_MEDIATYPE, d_playSongType);
		}
		else
		{
			setPlayPara(PLY_CMD_PLAY_MUSSUBTYPE, PLY_CMD_PLAY_MUSSUBTYPE_MIDI);
		}
		setPlayPara(PLY_CMD_PLAY_PLAYERTYPE, "mus");
	}
	ret = (play() == 0);

	//show
	/*if(ret == true)
	{
		EventCustom _event(MKPlayer::Event_PlaySong);
		M3D_Log *eventData = new (std::nothrow)M3D_Log();
		if(eventData != NULL)
		{
			eventData->setParamInt("songIndex", d_songIndex);
			_event.setUserData(eventData);
			getEventDispatcher()->dispatchEvent(&_event);
			SAFE_DELETE(eventData);
		}
	}
	else
	{
		EventCustom _event(MKPlayer::Event_BatchPlayerError);
		M3D_Log *eventData = new (std::nothrow)M3D_Log();
		if(eventData != NULL)
		{
			eventData->setParamInt("songIndex", d_songIndex);
			_event.setUserData(eventData);
			getEventDispatcher()->dispatchEvent(&_event);
			SAFE_DELETE(eventData);
		}
	}*/
	
	return ret;
}

}
