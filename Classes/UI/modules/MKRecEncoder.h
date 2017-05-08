/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKRecEncoder.h
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

#ifndef MKRECENCODER_H
#define MKRECENCODER_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"
namespace CEGUI
{

class MKRecEncoder : public MKService, public MKSingleton <MKRecEncoder>
{
public:
	
	static const std::string m_name;
	
	// - commands
	static const std::string m_cmdInit;
	static const std::string m_cmdDeInit;
	static const std::string m_cmdCreate;
	static const std::string m_cmdDestroy;
	static const std::string m_cmdStop;
	static const std::string m_cmdPause;
	static const std::string m_cmdResume;
	static const std::string m_cmdGetPercent;

	// - parameters
	static const std::string m_paraSongName;
	static const std::string m_paraSingerName;
	static const std::string m_paraAlbumName;
	static const std::string m_paraSongIndex;
	static const std::string m_paraSongType;
	static const std::string m_paraFilePath;
	static const std::string m_paraRecPath;
	static const std::string m_paraOutFile;
	static const std::string m_paraCidKey;
	static const std::string m_paraPrivateKey;
	static const std::string m_paraRingFlag;
	static const std::string m_paraLameFlag;
	static const std::string m_paraEcho;
	static const std::string m_paraMusic;
	static const std::string m_paraReverb;
	static const std::string m_paraRhythm;
	static const std::string m_paraTone;
	static const std::string m_paraTempo;
	static const std::string m_paraRec;
	static const std::string m_paraBitrate;
	static const std::string m_paraLatency;
	static const std::string m_paraOutLatency;
	static const std::string m_paraMixFlag;
	static const std::string m_paraSpSound; 	
	// parameter values
	static const std::string m_encSongTypePCM;
	static const std::string m_encSongTypeWAV;
	static const std::string m_encSongTypeMP3;
	static const std::string m_encSongTypeAAC;
	static const std::string m_encSongTypeMIDI;
	static const std::string m_encSongTypeMUS;
	static const std::string m_encSongTypeOKFMP3;
	
	// events
	static const std::string m_encEventPlay;
	static const std::string m_encEventStopped;
	static const std::string m_encEventPaused;
	static const std::string m_encEventResumed;
	static const std::string m_encEventValueID;

	MKRecEncoder(void* owner);

	virtual ~MKRecEncoder(void);
	
	//----------------------------------------------------------------------------//
	int init(int bitrate, int latency, int outlatency);
	
	//----------------------------------------------------------------------------//
	int deinit();
	
	//----------------------------------------------------------------------------//
	//- return value is encoder id
	//- use this id to do destroy/stop/pause/resume
	//----------------------------------------------------------------------------//
	int create(const std::string& songName, 
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
														);
	
	//----------------------------------------------------------------------------//
	int destroy(int id);
	
	//----------------------------------------------------------------------------//
	int stop(int id);
	
	//----------------------------------------------------------------------------//
	int pause(int id);

	//----------------------------------------------------------------------------//
	int resume(int id);
	
	//----------------------------------------------------------------------------//
	int getPercent(int id);
	
};
}
#endif
