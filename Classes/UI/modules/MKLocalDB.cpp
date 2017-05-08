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

#include <k_global.h>
#include "MKString.h"
#include "MKLocalDB.h"
#include "MKSystem.h"

namespace CEGUI
{

template<> MKLocalDB* MKSingleton<MKLocalDB>::ms_Singleton = 0;
const std::string MKLocalDB::m_name = "localdb";

// - commands
const std::string MKLocalDB::m_cmdInit = "init";
const std::string MKLocalDB::m_cmdDeinit = "deinit";
const std::string MKLocalDB::m_cmdLoad = "load";
const std::string MKLocalDB::m_cmdUnload= "unload";
const std::string MKLocalDB::m_cmdQuery = "query";
const std::string MKLocalDB::m_cmdUpdate = "update";
const std::string MKLocalDB::m_cmdUpdateRec = "updaterec";
const std::string MKLocalDB::m_cmdReqPage = "reqpage";
const std::string MKLocalDB::m_cmdGetReqRec = "getreqrec";
const std::string MKLocalDB::m_cmdGetSongInf = "getsonginf";
const std::string MKLocalDB::m_cmdGetFilePath = "getfilepath";
const std::string MKLocalDB::m_cmdGetVersion = "getversion";
const std::string MKLocalDB::m_cmdUpdateDev = "updateDev";
const std::string MKLocalDB::m_cmdDetectLocalSong = "detectlocalsong";
const std::string MKLocalDB::m_cmdUpdateLocalSong = "updatelocalsong";

// - parameters
const std::string MKLocalDB::m_ParaType = "type";
const std::string MKLocalDB::m_ParaCmd = "cmd";
const std::string MKLocalDB::m_ParaSubType = "subtype";
const std::string MKLocalDB::m_ParaFirstWord = "firstword";
const std::string MKLocalDB::m_ParaParam= "param";
const std::string MKLocalDB::m_ParaStart = "start";
const std::string MKLocalDB::m_ParaCount = "count";
const std::string MKLocalDB::m_ParaIndex = "index";
const std::string MKLocalDB::m_ParaValue = "value";
const std::string MKLocalDB::m_ParaPath = "path";
const std::string MKLocalDB::m_ParaSongIndex = "songindex";
const std::string MKLocalDB::m_ParaRandom = "random";
const std::string MKLocalDB::m_ParaSongName = "songname";
const std::string MKLocalDB::m_ParaSingerName = "singername";
const std::string MKLocalDB::m_ParaScore = "score";
const std::string MKLocalDB::m_ParaTime = "time";
const std::string MKLocalDB::m_ParaDuration = "duration";
const std::string MKLocalDB::m_ParaDevPath = "devPath";
const std::string MKLocalDB::m_ParaDetectDir = "detectdir";
const std::string MKLocalDB::m_ParaDevId = "devid";
const std::string MKLocalDB::m_ParaSrcDir = "srcdir";
const std::string MKLocalDB::m_ParaLstFile = "lstfile";
const std::string MKLocalDB::m_ParaNameFile = "namefile";
const std::string MKLocalDB::m_ParaIndexFile = "indexfile";
const std::string MKLocalDB::m_ParaChkFile = "chkfile";
const std::string MKLocalDB::m_ParaDBFile = "dbfile";
const std::string MKLocalDB::m_ParaSrcDBDir = "srcdbdir";
const std::string MKLocalDB::m_ParaDstDBDir = "dstdbdir";
const std::string MKLocalDB::m_ParaSrcCnt = "srccnt";
const std::string MKLocalDB::m_ParaIntelligent = "intelligent";

const std::string MKLocalDB::m_ParaIntPara1 = "para1";
const std::string MKLocalDB::m_ParaIntPara2 = "para2";
const std::string MKLocalDB::m_ParaIntPara3 = "para3";
const std::string MKLocalDB::m_ParaIntPara4 = "para4";
const std::string MKLocalDB::m_ParaStrPara1 = "spara1";
const std::string MKLocalDB::m_ParaStrPara2 = "spara2";
const std::string MKLocalDB::m_ParaStrPara3 = "spara3";
const std::string MKLocalDB::m_ParaStrPara4 = "spara4";

MKLocalDB::MKLocalDB(void* owner) : MKService(m_name, owner)
{
}

MKLocalDB::~MKLocalDB(void)
{
}

//----------------------------------------------------------------------------//
int MKLocalDB::init()
{
	return exec(m_cmdInit, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKLocalDB::deinit()
{
	return exec(m_cmdDeinit, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKLocalDB::loadLocalDb(const std::string& DbPath)
{
	return exec(m_cmdLoad, DbPath);
}

//----------------------------------------------------------------------------//
int MKLocalDB::unloadLocalDb()
{
	return exec(m_cmdUnload, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKLocalDB::initDbQuery(int type, int subType, const std::string& firstWord, int param)
{
	setCmdPara(m_cmdQuery,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdQuery,m_ParaSubType, MKString::valueOf(subType));
	setCmdPara(m_cmdQuery,m_ParaFirstWord, firstWord);
	setCmdPara(m_cmdQuery,m_ParaParam, MKString::valueOf(param));
	return exec(m_cmdQuery, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKLocalDB::initDbQueryRecord(int type, int start, int count)
{
	setCmdPara(m_cmdReqPage,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdReqPage,m_ParaStart, MKString::valueOf(start));
	setCmdPara(m_cmdReqPage,m_ParaCount, MKString::valueOf(count));
	return exec(m_cmdReqPage, m_nullstr);
}

//----------------------------------------------------------------------------//
int MKLocalDB::getDbQueryInt(int type, int subType, int index)
{
	setCmdPara(m_cmdGetReqRec,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdGetReqRec,m_ParaSubType, MKString::valueOf(subType));
	setCmdPara(m_cmdGetReqRec,m_ParaIndex, MKString::valueOf(index));
	setCmdPara(m_cmdGetReqRec,m_ParaParam, MKString::valueOf(0));
	return exec(m_cmdGetReqRec, m_nullstr);
}

//----------------------------------------------------------------------------//
std::string MKLocalDB::getDbQueryString(int type, int subType, int index)
{
	setCmdPara(m_cmdGetReqRec,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdGetReqRec,m_ParaSubType, MKString::valueOf(subType));
	setCmdPara(m_cmdGetReqRec,m_ParaIndex, MKString::valueOf(index));
	setCmdPara(m_cmdGetReqRec,m_ParaParam, MKString::valueOf(1));
	if (exec(m_cmdGetReqRec, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetReqRec, m_ParaValue);
	}
	else
	{
		return "";
	}
}

//----------------------------------------------------------------------------//
int MKLocalDB::getSongInfoInt(int type, int songIndex)
{
	setCmdPara(m_cmdGetSongInf,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdGetSongInf,m_ParaSongIndex, MKString::valueOf(songIndex));
	setCmdPara(m_cmdGetSongInf,m_ParaParam, MKString::valueOf(0));
	return exec(m_cmdGetSongInf, m_nullstr);
}

//----------------------------------------------------------------------------//
std::string MKLocalDB::getSongInfoString(int type, int songIndex)
{
	setCmdPara(m_cmdGetSongInf,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdGetSongInf,m_ParaSongIndex, MKString::valueOf(songIndex));
	setCmdPara(m_cmdGetSongInf,m_ParaParam, MKString::valueOf(1));
	if (exec(m_cmdGetSongInf, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetSongInf, m_ParaValue);
	}
	return "";
}

//----------------------------------------------------------------------------//
std::string MKLocalDB::getFilePath(int type, int para1, int para2, int para3, int para4, const std::string& spara1,const std::string& spara2, const std::string& spara3, const std::string& spara4)
{
	setCmdPara(m_cmdGetFilePath,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdGetFilePath,m_ParaIntPara1, MKString::valueOf(para1));
	setCmdPara(m_cmdGetFilePath,m_ParaIntPara2, MKString::valueOf(para2));
	setCmdPara(m_cmdGetFilePath,m_ParaIntPara3, MKString::valueOf(para3));
	setCmdPara(m_cmdGetFilePath,m_ParaIntPara4, MKString::valueOf(para4));
	setCmdPara(m_cmdGetFilePath,m_ParaStrPara1, spara1);
	setCmdPara(m_cmdGetFilePath,m_ParaStrPara2, spara2);
	setCmdPara(m_cmdGetFilePath,m_ParaStrPara3, spara3);
	setCmdPara(m_cmdGetFilePath,m_ParaStrPara4, spara4);
	if (exec(m_cmdGetFilePath, m_nullstr) == 0)
	{
		return getEventParaValue(m_cmdGetFilePath, m_ParaPath);
	}
	return "";
}

//----------------------------------------------------------------------------//
//-remove /add /clean
//----------------------------------------------------------------------------//
int MKLocalDB::devListCmd(int cmd, const std::string& path)
{
	setCmdPara(m_cmdUpdateDev,m_ParaCmd, MKString::valueOf(cmd));
	setCmdPara(m_cmdUpdateDev,m_ParaDevPath, path);

	return exec(m_cmdUpdateDev, m_nullstr);
}

//----------------------------------------------------------------------------//
//-delete/prioriy/add prog/fav/rec
//----------------------------------------------------------------------------//
int MKLocalDB::songListCmd(int type, int cmd, int songIndex, int random, const std::string& songName, const std::string& singerName)
{
	setCmdPara(m_cmdUpdate,m_ParaType, MKString::valueOf(type));
	setCmdPara(m_cmdUpdate,m_ParaCmd, MKString::valueOf(cmd));
	setCmdPara(m_cmdUpdate,m_ParaSongIndex, MKString::valueOf(songIndex));
	setCmdPara(m_cmdUpdate,m_ParaRandom, MKString::valueOf(random));
	setCmdPara(m_cmdUpdate,m_ParaSongName, songName);
	setCmdPara(m_cmdUpdate,m_ParaSingerName, singerName);
	return exec(m_cmdUpdate, m_nullstr);
}

//----------------------------------------------------------------------------//
//-update rec song info
//----------------------------------------------------------------------------//
int MKLocalDB::updateRecordSongInf(int para1, int para2, int para3)
{
	setCmdPara(m_cmdUpdateRec,m_ParaScore, MKString::valueOf(para1));
	setCmdPara(m_cmdUpdateRec,m_ParaTime, MKString::valueOf(para2));
	setCmdPara(m_cmdUpdateRec,m_ParaDuration, MKString::valueOf(para3));
	return exec(m_cmdUpdateRec, m_nullstr);
}

//----------------------------------------------------------------------------//
//-detect local mtv songs in special folder
//- 0: succ, <>0: error code
//----------------------------------------------------------------------------//
int MKLocalDB::detectLocalSong(const std::string& srcDBDir, const std::string& detectDir, int autoSinger)
{
	setCmdPara(m_cmdDetectLocalSong, m_ParaSrcDBDir, srcDBDir);
	setCmdPara(m_cmdDetectLocalSong, m_ParaDetectDir, detectDir);
	setCmdPara(m_cmdDetectLocalSong, m_ParaLstFile, "SONGLIST.BIN");
	setCmdPara(m_cmdDetectLocalSong, m_ParaNameFile, "SONGNAME.BIN");
	setCmdPara(m_cmdDetectLocalSong, m_ParaIndexFile, "SONGINDEX.BIN");
	setCmdPara(m_cmdDetectLocalSong, m_ParaIntelligent, MKString::valueOf(autoSinger));

	return exec(m_cmdDetectLocalSong, m_nullstr);
}

//----------------------------------------------------------------------------//
//-update local mtv songs from multi-source folder to destiny db file
//- 0: succ, <>0: error code
//----------------------------------------------------------------------------//
int MKLocalDB::updateLocalSong(const std::string& srcDBDir, const std::string& dstDBDir, const std::string srcDir[], int count)
{
	if(count==0){
		return 0;
	}
	setCmdPara(m_cmdUpdateLocalSong, m_ParaSrcDBDir, srcDBDir);
	setCmdPara(m_cmdUpdateLocalSong, m_ParaDstDBDir, dstDBDir);
	for (int i=0; i<count; i++) {
		setCmdPara(m_cmdUpdateLocalSong, (m_ParaSrcDir+MKString::valueOf(i)), srcDir[i]);
	}
	setCmdPara(m_cmdUpdateLocalSong, m_ParaSrcCnt, MKString::valueOf(count));
	setCmdPara(m_cmdUpdateLocalSong, m_ParaLstFile, "SONGLIST.BIN");
	setCmdPara(m_cmdUpdateLocalSong, m_ParaNameFile, "SONGNAME.BIN");
	setCmdPara(m_cmdUpdateLocalSong, m_ParaChkFile, "SONGLIST.CHK");
	setCmdPara(m_cmdUpdateLocalSong, m_ParaDBFile, "skym.db");
	return exec(m_cmdUpdateLocalSong, m_nullstr);
}

//----------------------------------------------------------------------------//
//-copy merged big db to source db folder
//----------------------------------------------------------------------------//
void MKLocalDB::flushLocalSongDB(const std::string& srcDBDir, const std::string& dstDBDir)
{
	std::string dst = srcDBDir+"skymBig.db";
	std::string src = dstDBDir+"skym.db";
	krk_fcopy(dst.c_str(), src.c_str(), 1024*512, NULL);
	std::string filepath;
	filepath = srcDBDir+"song_info_buf.bin";
	remove(filepath.c_str());
	filepath = srcDBDir+"singer_info_buf.bin";
	remove(filepath.c_str());
}

//----------------------------------------------------------------------------//
//-delete merged db
//----------------------------------------------------------------------------//
void MKLocalDB::recoverOriginalDB(const std::string& srcDBDir, const std::string& dstDBDir)
{
	std::string filepath = srcDBDir+"skymBig.db";
	if (krk_fexist(filepath.c_str()))
	{
		remove(filepath.c_str());
		filepath = srcDBDir+"song_info_buf.bin";
		remove(filepath.c_str());
		filepath = srcDBDir+"singer_info_buf.bin";
		remove(filepath.c_str());
	}
}

}