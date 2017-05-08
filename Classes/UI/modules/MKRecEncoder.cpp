/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKRecEncoder.cpp
** Revision : 1.00											
**																	
** Description: MKRecEncoder base on recencoder service
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
#include "MKRecEncoder.h"

namespace CEGUI
{
template<> MKRecEncoder* MKSingleton<MKRecEncoder>::ms_Singleton = 0;
const std::string MKRecEncoder::m_name = "recencoder";

// - commands
const std::string MKRecEncoder::m_cmdInit = "init";
const std::string MKRecEncoder::m_cmdDeInit = "deinit";
const std::string MKRecEncoder::m_cmdCreate = "create";
const std::string MKRecEncoder::m_cmdDestroy = "destroy";
const std::string MKRecEncoder::m_cmdStop = "stop";
const std::string MKRecEncoder::m_cmdPause = "pause";
const std::string MKRecEncoder::m_cmdResume = "resume";
const std::string MKRecEncoder::m_cmdGetPercent = "getpercent";

// - parameters
const std::string MKRecEncoder::m_paraSongName = "songname";
const std::string MKRecEncoder::m_paraSingerName = "singername";
const std::string MKRecEncoder::m_paraAlbumName = "albumname";
const std::string MKRecEncoder::m_paraSongIndex = "songindex";
const std::string MKRecEncoder::m_paraSongType = "songtype";
const std::string MKRecEncoder::m_paraFilePath = "filepath";
const std::string MKRecEncoder::m_paraRecPath = "recpath";
const std::string MKRecEncoder::m_paraOutFile = "outfile";
const std::string MKRecEncoder::m_paraCidKey = "cidkey";
const std::string MKRecEncoder::m_paraPrivateKey = "privatekey";
const std::string MKRecEncoder::m_paraRingFlag = "ringflag";	
const std::string MKRecEncoder::m_paraLameFlag = "lameflag";	
const std::string MKRecEncoder::m_paraEcho = "echo";	
const std::string MKRecEncoder::m_paraMusic = "music";	
const std::string MKRecEncoder::m_paraReverb = "reverb";	
const std::string MKRecEncoder::m_paraRhythm = "rhythm";	
const std::string MKRecEncoder::m_paraTone = "tone";	
const std::string MKRecEncoder::m_paraTempo = "tempo";	
const std::string MKRecEncoder::m_paraRec = "rec";	
const std::string MKRecEncoder::m_paraBitrate = "bitrate";	
const std::string MKRecEncoder::m_paraLatency = "latency";	
const std::string MKRecEncoder::m_paraOutLatency = "outlatency";	
const std::string MKRecEncoder::m_paraMixFlag = "mixflag";	
const std::string MKRecEncoder::m_paraSpSound = "spsound"; 

// parameter values
const std::string MKRecEncoder::m_encSongTypePCM = "pcm";
const std::string MKRecEncoder::m_encSongTypeWAV = "wav";
const std::string MKRecEncoder::m_encSongTypeMP3 = "mp3";
const std::string MKRecEncoder::m_encSongTypeAAC = "aac";
const std::string MKRecEncoder::m_encSongTypeMIDI = "midi";
const std::string MKRecEncoder::m_encSongTypeMUS = "mus";
const std::string MKRecEncoder::m_encSongTypeOKFMP3 = "okfmp3";

// events
const std::string MKRecEncoder::m_encEventPlay = "play";
const std::string MKRecEncoder::m_encEventStopped = "stopped";
const std::string MKRecEncoder::m_encEventPaused = "paused";
const std::string MKRecEncoder::m_encEventResumed = "resumed";
const std::string MKRecEncoder::m_encEventValueID = "id";

MKRecEncoder::MKRecEncoder(void* owner) : MKService(m_name, owner)
{
}

MKRecEncoder::~MKRecEncoder(void)
{
}

//----------------------------------------------------------------------------//
int MKRecEncoder::init(int bitrate, int latency, int outlatency)
{	
	setCmdPara(m_cmdInit, m_paraCidKey, "12345678");
	setCmdPara(m_cmdInit, m_paraPrivateKey, "in");
	setCmdPara(m_cmdInit, m_paraRingFlag, "0");
	setCmdPara(m_cmdInit, m_paraLameFlag, "1");
	setCmdPara(m_cmdInit, m_paraSpSound, "1");
	setCmdPara(m_cmdInit, m_paraBitrate, MKString::valueOf(bitrate));
	setCmdPara(m_cmdInit, m_paraLatency, MKString::valueOf(latency));
	setCmdPara(m_cmdInit, m_paraOutLatency, MKString::valueOf(outlatency));	
	return exec(m_cmdInit, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKRecEncoder::deinit()
{			
	return exec(m_cmdDeInit, m_nullstr);
}

//----------------------------------------------------------------------------//
//- return value is encoder id
//- use this id to do destroy/stop/pause/resume
//----------------------------------------------------------------------------//
int MKRecEncoder::create(const std::string& songName, 
													const std::string& singerName,
													const std::string& albumName,
													int songIndex,
													const std::string& songType,
													const std::string& filePath,
													const std::string& recPath,
													const std::string& outFile,
													int echo,
													int music,
													int reverb, 
													int rhythm,
													int tone,
													int tempo,
													int rec,
													int duet
													)
{			
	setCmdPara(m_cmdCreate, m_paraSongName, songName);
	setCmdPara(m_cmdCreate, m_paraSingerName, singerName);
	setCmdPara(m_cmdCreate, m_paraAlbumName, albumName);
	setCmdPara(m_cmdCreate, m_paraSongIndex, MKString::valueOf(songIndex));
	setCmdPara(m_cmdCreate, m_paraSongType, songType);
	setCmdPara(m_cmdCreate, m_paraFilePath, filePath);
	setCmdPara(m_cmdCreate, m_paraRecPath, recPath);
	setCmdPara(m_cmdCreate, m_paraOutFile, outFile);
	setCmdPara(m_cmdCreate, m_paraEcho, MKString::valueOf(echo));
	setCmdPara(m_cmdCreate, m_paraMusic, MKString::valueOf(music));
	setCmdPara(m_cmdCreate, m_paraReverb, MKString::valueOf(reverb));
	setCmdPara(m_cmdCreate, m_paraRhythm, MKString::valueOf(rhythm));
	setCmdPara(m_cmdCreate, m_paraTone, MKString::valueOf(tone));
	setCmdPara(m_cmdCreate, m_paraTempo, MKString::valueOf(tempo));
	setCmdPara(m_cmdCreate, m_paraRec, MKString::valueOf(rec));
	setCmdPara(m_cmdCreate, m_paraMixFlag, MKString::valueOf(duet));
	
	return exec(m_cmdCreate, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKRecEncoder::destroy(int id)
{
	return exec(m_cmdDestroy, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//
int MKRecEncoder::stop(int id)
{			
	return exec(m_cmdStop, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//
int MKRecEncoder::pause(int id)
{			
	return exec(m_cmdPause, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//
int MKRecEncoder::resume(int id)
{			
	return exec(m_cmdResume, MKString::valueOf(id));
}

//----------------------------------------------------------------------------//
int MKRecEncoder::getPercent(int id)
{			
	return exec(m_cmdGetPercent, MKString::valueOf(id));
}

}