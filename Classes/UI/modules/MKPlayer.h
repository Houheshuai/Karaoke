/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKPlayer.h
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

#ifndef MKPLAYER_H
#define MKPLAYER_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{

class MKLyricInfo 
{
public:
	std::string m_lineStr;
	int m_startTime;
	int m_endTime;
};

class PlayParam
{
public:
	PlayParam()
	{
		SongIndex = -1;
		SongPath = "";
		SongName = "";
		FileType = 0;
		MediaType = 0;
		NeedRecord = false;
		RecordPath = "";
		IsRecord = false;
		
		accomVol = -1;
		voiceVol = -1;
		micVolL = -1;
		micVolR = -1;
		wmicVolL = -1;			
		wmicVolR = -1;
		echoVal = -1;
		tempoVal = -1;
		toneVal = -1;
		vocalType = "";
		lyricAlign = "";
		scoreLevel = "";
		cidKey = "";
		privateKey = "";
	}
	~PlayParam(){};

	// song info
	int			SongIndex;
	std::string SongPath;
	std::string SongName;
	int			FileType;
	int			MediaType;
	bool		NeedRecord;
	std::string RecordPath;
	bool        IsRecord;


	//config info
	int accomVol;
	int voiceVol;
	int micVolL;
	int micVolR;
	int wmicVolL;			
	int wmicVolR;
	int echoVal;
	int tempoVal;
	int toneVal;
	std::string vocalType;      // 播放前设置无效
	std::string lyricAlign;
	std::string scoreLevel;
	std::string cidKey;
	std::string privateKey;
};


#define MIN_VOLUME_VALUE	0
#define MAX_VOLUME_VALUE	100

#define MIN_MICVOLUME_VALUE	0
#define MAX_MICVOLUME_VALUE	100

#define MIN_ECHO_VALUE		0
#define MAX_ECHO_VALUE		100

#define MIN_TONE_VALUE		(-6)
#define MAX_TONE_VALUE		6

#define MIN_TEMPO_VALUE 	800
#define MAX_TEMPO_VALUE		1200


/*!
\brief
	PLAY_SONG_TYPE for setup form
	0: no play; 1: MP3 play; 2: MIDI play; 3: AAC play; 4: MTV play; 5: MTV replay; 6: other replay;
*/
enum
{
	PLAY_SONG_TYPE_NONE,
	PLAY_SONG_TYPE_MP3,
	PLAY_SONG_TYPE_MIDI,
	PLAY_SONG_TYPE_AAC,
	PLAY_SONG_TYPE_MTV,
	PLAY_SONG_TYPE_MOVIE,
	PLAY_SONG_TYPE_RECORD_MTV,
	PLAY_SONG_TYPE_RECORD_OTHER,
	PLAY_SONG_TYPE_CDG,
	PLAY_SONG_TYPE_ACC
};

class MKPlayer : public MKService , public MKSingleton <MKPlayer>
{

public:
	
	static const std::string m_name;
	static int m_EndedStop;
	static int m_AuthPass;
	static int m_EmbeddedAudio;
	static int m_effectMusicEnabled;	

	// - commands
	static const std::string  m_cmdInit;
	static const std::string  m_cmdDeInit;
	static const std::string  m_cmdInitAudio;
	static const std::string  m_cmdDeInitAudio;
	static const std::string  m_cmdUpdateAudio;
	static const std::string  m_cmdInitView;
	static const std::string  m_cmdDeInitView;
	static const std::string  m_cmdSetViewUpdate;
	static const std::string  m_cmdSetViewVisible;
	static const std::string  m_cmdViewUpdate;
	static const std::string  m_cmdPlay;
	static const std::string  m_cmdPause;
	static const std::string  m_cmdResume;
	static const std::string  m_cmdStop;
	static const std::string  m_cmdVoiceRecord;
	static const std::string  m_cmdStopVoiceRecord;
	static const std::string  m_cmdSetVol;
	static const std::string  m_cmdSetVocal;
	static const std::string  m_cmdAutoSeek;
	static const std::string  m_cmdSeekTime;
	static const std::string  m_cmdSetStaff;
	static const std::string  m_cmdSetScore;
	static const std::string  m_cmdSetLyric;
	static const std::string  m_cmdSetMIC;
	static const std::string  m_cmdGetState;
	static const std::string  m_cmdGetLyric;
	static const std::string  m_cmdGetScore;
	static const std::string  m_cmdGetBufferingFlag;
	static const std::string  m_cmdGetPlayTime;
	static const std::string  m_cmdGetTotalTime;
	static const std::string  m_cmdTestLatency;
	static const std::string  m_cmdChangeAudioIF;
	static const std::string  m_cmdGetPlayerType;
	static const std::string  m_cmdSetPlayerType;
	static const std::string  m_cmdPlayBgv;
	static const std::string  m_cmdStopBgv;
	static const std::string  m_cmdSetBgvType;
	static const std::string  m_cmdInitBgvView;
	static const std::string  m_cmdDeInitBgvView;
	static const std::string  m_cmdGetBgvState;
	static const std::string  m_cmdEnableEffectMusic;
	static const std::string  m_cmdPlayEffectMusic;
	static const std::string  m_cmdSetSPSoundEffect;

	// - parameters
	static const std::string m_paraState;
	static const std::string m_paraLatency;
	static const std::string m_paraInLatency;
	static const std::string m_paraOutLatency;
	static const std::string m_paraInChannels;
	static const std::string m_paraOutChannels;
	static const std::string m_paraInRate;
	static const std::string m_paraOutRate;
	static const std::string m_paraShow;
	static const std::string m_paraEffect;
	static const std::string m_paraEnabled;
	static const std::string m_paraPlayMode;
	static const std::string m_paraPlayRec;
	static const std::string m_paraStopScore;
	static const std::string m_paraLyricAlign;
	static const std::string m_paraRecFmt;
	static const std::string m_paraRecEncFmt;
	static const std::string m_paraEmbedded;
	static const std::string m_paraLyricFont;
        static const std::string m_paraIfunNum;

	// - parameter value of 'state'
	static const std::string m_statePlaying;
	static const std::string m_stateStopped;
	static const std::string m_stateStopping;
	static const std::string m_statePaused;
	static const std::string m_statePausing;

	// - parameter value of 'changeaudioif'
	static const std::string m_audioIFStandard;
	static const std::string m_audioIFKKEBox;
	static const std::string m_audioIFKKEMini;
	static const std::string m_audioIFEmbedded;

	// - parameter value of 'playmode'
	static const std::string  m_playModeSong;
	static const std::string  m_playModeRec;

	static const int VIEW_NONE;
	static const int VIEW_LYRIC;
	static const int VIEW_STAFF;
	static const int VIEW_ALL;

	MKPlayer(void* owner);

	virtual ~MKPlayer(void);

	//----------------------------------------------------------------------------//
	//- call 'init' on app start up, after 'initAudio'
	//----------------------------------------------------------------------------//
	int init(const std::string& resFile);

	//----------------------------------------------------------------------------//
	//- call 'deinit' on app killed, before 'deinitAudio'
	//----------------------------------------------------------------------------//
	int deinit(void);

	//----------------------------------------------------------------------------//
	//- call 'initAudio' just before 'init', if call it after 'init', do nothing
	//----------------------------------------------------------------------------//
	int initAudio(const std::string& audioIF);

	//----------------------------------------------------------------------------//
	//- call 'deinitAudio' just after 'deinit', if call it before 'deinit', audio output is unknown
	//----------------------------------------------------------------------------//
	int deinitAudio(void);

	//----------------------------------------------------------------------------//
	int updateAudio(void);

	//----------------------------------------------------------------------------//
	//- type: video/music/picture/mus
	//----------------------------------------------------------------------------//
	int initView(const std::string& type);

	//----------------------------------------------------------------------------//
	//- type: video/music/picture/mus
	//----------------------------------------------------------------------------//
	int deinitView(const std::string& type);
		
	//----------------------------------------------------------------------------//
	//- call 'initBgvView' after bgv surface is created
	//----------------------------------------------------------------------------//
	int initBgvView(const std::string& type);

	//----------------------------------------------------------------------------//
	//- call 'deinitBgvView' before bgv surface is destroyed
	//----------------------------------------------------------------------------//
	int deinitBgvView(const std::string& type);

	//----------------------------------------------------------------------------//
	//- true, call viewUpdate by yourself, false, viewupdate will be called automatically
	//----------------------------------------------------------------------------//
	int setSeperateUpdate(int singleUpdate);

	//----------------------------------------------------------------------------//
	//- true, display title/lyric/staff, false, only play music, no title/lyric/staff
	//----------------------------------------------------------------------------//
	int setViewVisible(int visible);

	//----------------------------------------------------------------------------//
	int setPlayPara(const std::string& para, const std::string& value);

	//----------------------------------------------------------------------------//
	std::string getPlayPara(const std::string& para);

	//----------------------------------------------------------------------------//
	int isAuthPassed(void);

	//----------------------------------------------------------------------------//
	int play(void);

	int resume(void);

	//----------------------------------------------------------------------------//
	int pause(void);

	//----------------------------------------------------------------------------//
	int stop(void);

	//----------------------------------------------------------------------------//
	int voiceRecord(const std::string& outfile, int devsamplerate, int filesamplerate, int channels, int mutetime);
	
	//----------------------------------------------------------------------------//
	int stopVoiceRecord(int hdle);

	//----------------------------------------------------------------------------//
	int playEffectMusic(const std::string& path);

	int disableEffectMusic();

	//----------------------------------------------------------------------------//
	int playBgv(const std::string& path);

	//----------------------------------------------------------------------------//
	int stopBgv(const std::string& para = m_nullstr);

	//----------------------------------------------------------------------------//
	int setBgvType(const std::string& type);

	//----------------------------------------------------------------------------//
	void setBgvPlayMode(const std::string& mode);

	//----------------------------------------------------------------------------//
	int isBgvPlaying(void);

	//----------------------------------------------------------------------------//
	int isEndedStop(void);

	//----------------------------------------------------------------------------//
	int autoSeek(void);

	//----------------------------------------------------------------------------//
	int seekTime(int playtime);

	//----------------------------------------------------------------------------//
	int setSPSoundEffect(int setting);

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
	int setVol(const std::string& type, int value);

	//----------------------------------------------------------------------------//
	int setVocal(const std::string& value);

	//----------------------------------------------------------------------------//
	int setStaff(const std::string& value);
	int setStaffNum(int value);
	//----------------------------------------------------------------------------//
	int setScore(const std::string& value);

	//----------------------------------------------------------------------------//
	int setLyric(const std::string& value);

	//----------------------------------------------------------------------------//
	int setLyricEffect(const std::string& value);

	//----------------------------------------------------------------------------//
	int setLyricAlign(const std::string& value);

	//----------------------------------------------------------------------------//
	int setLyricFont(const std::string& value);

	//----------------------------------------------------------------------------//
	int enableStaff(int enabled);
	
	//----------------------------------------------------------------------------//
	int enableLyric(int enabled);

	//----------------------------------------------------------------------------//
	//- only render lyric and staff
	//----------------------------------------------------------------------------//
	int renderView(void);

	//----------------------------------------------------------------------------//
	int updateSelf(int timeElapsed);

	//----------------------------------------------------------------------------//
	std::string getPlayState();

	//----------------------------------------------------------------------------//
	int getTotalTime(void);

	//----------------------------------------------------------------------------//
	int getPlayTime(void);

	//----------------------------------------------------------------------------//
	std::string getLyric(int lineNo);

	//----------------------------------------------------------------------------//
	int getLyric(int lineNo, MKLyricInfo& inf);

	//----------------------------------------------------------------------------//
	int getScore(void);

	//----------------------------------------------------------------------------//
	int getStoppedScore(void);

	//----------------------------------------------------------------------------//
	//- 1 - buffering, 0 - not buffering
	//----------------------------------------------------------------------------//
	int getBufferingFlag(void);

	//----------------------------------------------------------------------------//
	std::string getPlayMode(void);

	//----------------------------------------------------------------------------//
	int testLatency(const std::string& tmpfile);

	//----------------------------------------------------------------------------//
	//- default: java audio
	//- kkebox: box
	//- kkemini: mini
	//----------------------------------------------------------------------------//
	int changeAudioIF(const std::string& audioIF, int playRec);

	//----------------------------------------------------------------------------//
	const std::string& getAudioIF(void);

	//----------------------------------------------------------------------------//
	//- 1: video, 2: music, 3: picture, 4: mus
	//----------------------------------------------------------------------------//
	int getPlayerType(void);

	//----------------------------------------------------------------------------//
	//- type: video/music/picture/mus
	//----------------------------------------------------------------------------//
	int setPlayerType(const std::string& type);

	//----------------------------------------------------------------------------//
	int isMVPlayer(void);

	//----------------------------------------------------------------------------//
	int isMusPlayer(void);

	//----------------------------------------------------------------------------//
	int setAudioPara(int inChannels, int outChannels, int inRate, int outRate, int latency);

	//----------------------------------------------------------------------------//
	int setEmbeddedAudioPara();

	//----------------------------------------------------------------------------//
	int getLatency(void);

	//----------------------------------------------------------------------------//
	int setLatency(int latency);
	//----------------------------------------------------------------------------//
	int getPlayerTime(void);

	bool playSong(PlayParam _playParam);

	PlayParam d_PlayParam;

};

}
#endif

