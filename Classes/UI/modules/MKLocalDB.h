/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : MKLocalDB.h
** Revision : 1.00											
**																	
** Description: MKLocalDB base on localdb service
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

#ifndef MKLOCALDB_H
#define MKLOCALDB_H

#include <string>
#include <lib/ezbase/ez_service.h>
#include "MKService.h"

namespace CEGUI
{

class MKLocalDB : public MKService , public MKSingleton <MKLocalDB>
{
public:

	static const std::string m_name;

	// - commands
	static const std::string m_cmdInit;
	static const std::string m_cmdDeinit;
	static const std::string m_cmdLoad;
	static const std::string m_cmdUnload;
	static const std::string m_cmdQuery;
	static const std::string m_cmdUpdate;
	static const std::string m_cmdUpdateRec;
	static const std::string m_cmdReqPage;
	static const std::string m_cmdGetReqRec;
	static const std::string m_cmdGetSongInf;
	static const std::string m_cmdGetFilePath;
	static const std::string m_cmdGetVersion;
	static const std::string m_cmdUpdateDev;
	static const std::string m_cmdDetectLocalSong;
	static const std::string m_cmdUpdateLocalSong;

	// - parameters
	static const std::string m_ParaType;
	static const std::string m_ParaCmd;
	static const std::string m_ParaSubType;
	static const std::string m_ParaFirstWord;
	static const std::string m_ParaParam;
	static const std::string m_ParaStart;
	static const std::string m_ParaCount;
	static const std::string m_ParaIndex;
	static const std::string m_ParaValue;
	static const std::string m_ParaPath;
	static const std::string m_ParaSongIndex;
	static const std::string m_ParaRandom;
	static const std::string m_ParaSongName;
	static const std::string m_ParaSingerName;
	static const std::string m_ParaScore;
	static const std::string m_ParaTime;
	static const std::string m_ParaDuration;
	static const std::string m_ParaDevPath;
	static const std::string m_ParaDetectDir;
	static const std::string m_ParaDevId;
	static const std::string m_ParaSrcDir;
	static const std::string m_ParaLstFile;
	static const std::string m_ParaNameFile;
	static const std::string m_ParaIndexFile;
	static const std::string m_ParaChkFile;
	static const std::string m_ParaDBFile;
	static const std::string m_ParaSrcDBDir;
	static const std::string m_ParaDstDBDir;
	static const std::string m_ParaSrcCnt;
	static const std::string m_ParaIntelligent;

	static const std::string m_ParaIntPara1;
	static const std::string m_ParaIntPara2;
	static const std::string m_ParaIntPara3;
	static const std::string m_ParaIntPara4;
	static const std::string m_ParaStrPara1;
	static const std::string m_ParaStrPara2;
	static const std::string m_ParaStrPara3;
	static const std::string m_ParaStrPara4;

	MKLocalDB(void* owner);

	virtual ~MKLocalDB(void);

	//----------------------------------------------------------------------------//
	int init();

	//----------------------------------------------------------------------------//
	int deinit();

	//----------------------------------------------------------------------------//
	int loadLocalDb(const std::string& DbPath);

	//----------------------------------------------------------------------------//
	int unloadLocalDb();

	//----------------------------------------------------------------------------//
	int initDbQuery(int type, int subType, const std::string& firstWord, int param);

	//----------------------------------------------------------------------------//
	int initDbQueryRecord(int type, int start, int count);

	//----------------------------------------------------------------------------//
	int getDbQueryInt(int type, int subType, int index);

	//----------------------------------------------------------------------------//
	std::string getDbQueryString(int type, int subType, int index);

	//----------------------------------------------------------------------------//
	int getSongInfoInt(int type, int songIndex);

	//----------------------------------------------------------------------------//
	std::string getSongInfoString(int type, int songIndex);

	//----------------------------------------------------------------------------//
	std::string getFilePath(int type, int para1, int para2, int para3, int para4, const std::string& spara1,const std::string& spara2, const std::string& spara3, const std::string& spara4);

	//----------------------------------------------------------------------------//
	//-remove /add /clean
	//----------------------------------------------------------------------------//
	int devListCmd(int cmd, const std::string& path);

	//----------------------------------------------------------------------------//
	//-delete/prioriy/add prog/fav/rec
	//----------------------------------------------------------------------------//
	int songListCmd(int type, int cmd, int songIndex, int random, const std::string& songName, const std::string& singerName);

	//----------------------------------------------------------------------------//
	//-update last rec song info
	//----------------------------------------------------------------------------//
	int updateRecordSongInf(int para1, int para2, int para3);

	//----------------------------------------------------------------------------//
	//-detect local mtv songs in special folder
	//- 0: succ, <>0: error code
	//----------------------------------------------------------------------------//
	int detectLocalSong(const std::string& srcDBDir, const std::string& detectDir, int autoSinger);

	//----------------------------------------------------------------------------//
	//-update local mtv songs from multi-source folder to destiny db file
	//- 0: succ, <>0: error code
	//----------------------------------------------------------------------------//
	int updateLocalSong(const std::string& srcDBDir, const std::string& dstDBDir, const std::string srcDir[], int count = 0);

	//----------------------------------------------------------------------------//
	//-copy merged big db to source db folder
	//----------------------------------------------------------------------------//
	void flushLocalSongDB(const std::string& srcDBDir, const std::string& dstDBDir);

	//----------------------------------------------------------------------------//
	//-delete merged db
	//----------------------------------------------------------------------------//
	void recoverOriginalDB(const std::string& srcDBDir, const std::string& dstDBDir);
};

}

#endif

