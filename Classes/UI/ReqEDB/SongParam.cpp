#include "SongParam.h"
		
SongParam::SongParam()
{	
	reset();
}
SongParam::~SongParam()
{	
}

void SongParam::reset()
{
	m_songName = "";
	m_singerName = "";
	m_songLan = 0;
	m_songIndex = 0;
	m_fileType = 0;
	m_subType = 0;
	m_firstword = "";
	m_sortString = "";
	m_favFlag = 0;
	m_progFlag = 0;
}
void SongParam::setSongIndex(int songidx)
{
	m_songIndex = songidx;
	return;
}
int SongParam::getSongIndex(void)
{
	return m_songIndex;
}

void SongParam::setSongLan(int lantype)
{
	m_songLan = lantype;
	return;
}
int SongParam::getSongLan(void)
{
	return m_songLan;
}

void SongParam::setFileType(int ftype)
{
	m_fileType = ftype;
	return;
}
int SongParam::getFileType(void)
{
	return m_fileType;
}
void SongParam::setSubType(int stype)
{
	m_subType = stype;
	return;
}
int SongParam::getSubType(void)
{
	return m_subType;
}
void SongParam::setFavFlag(int favfg) 
{
	m_favFlag = favfg;
	return;
}
int SongParam::getFavFlag(void)
{
	return m_favFlag;
}

void SongParam::setProgFlag(int progfg)
{
	m_progFlag = progfg;
	return;
}
int SongParam::getProgFlag(void)
{
	return m_progFlag;
}
void SongParam::setSongName(std::string songname)
{
	m_songName = songname;
	return;
}
std::string SongParam::getSongName(void)
{
	return m_songName;
}

void SongParam::setSingerName(std::string singername)
{
	m_singerName = singername;
	return;
}
std::string SongParam::getSingerName(void)
{
	return m_singerName;
}

void SongParam::setFirstWord(std::string fw)
{
	m_firstword = fw;
	return;
}
std::string SongParam::getFirstWord(void)
{
	return m_firstword;
}

void SongParam::setSortString(std::string sortStr)
{
	m_sortString = sortStr;
	return;
}
std::string SongParam::getSortString(void)
{
	return m_sortString;
}


