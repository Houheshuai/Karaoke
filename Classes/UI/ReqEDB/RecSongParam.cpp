
#include "RecSongParam.h"

RecSongParam::RecSongParam()
{	
	reset();
}
RecSongParam::~RecSongParam()
{	
}
void RecSongParam::reset(void)
{
	m_songIndex = 0;
	m_recIndex = 0;
	m_score = 0;
	m_storage = 0;
	m_insertId = 0;
}

/*
void RecSongParam::setSongIndex(int songidx)
{
	m_songIndex = songidx;
	return;
}
int RecSongParam::getSongIndex(void)
{
	return m_songIndex;
}
void RecSongParam::setInsertId(int insertid)
{
	m_insertId = insertid;
	return;
}
int RecSongParam::getInsertId(void)
{
	return m_insertId;
}
void RecSongParam::setRecIndex(int recidx)
{
	m_recIndex = recidx;
	return;
}
int RecSongParam::getRecIndex(void)
{
	return m_recIndex;
}
void RecSongParam::setScore(int score)
{
	m_score = score;
	return;
}
int RecSongParam::getScore(void)
{
	return m_score;
}

void RecSongParam::setStorage(int storage)
{
	m_storage = storage;
	return;
}
int RecSongParam::getStorage(void)
{
	return m_storage;
}
*/


