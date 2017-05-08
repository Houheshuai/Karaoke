/****************************************************************
*	
*	FUNCTION:	����BUFFER��һ����ٻ�ø赥���ݣ��������ļ�
*	FILE:		ReqListBuffer.cpp
*	BY:			chenzh
*
****************************************************************/

//#define NO_DEBUG_PRINT
//#define USE_A_LITTER_BUFFER				//���´���buffer������������

#include "ReqListBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
#include <fstream>

#include "krkplayer/MCodeConvert.h"

#pragma warning(disable:4996)

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN	256
#endif
#ifndef SQL_STR_LEN
#define SQL_STR_LEN		256
#endif
#ifndef TEMP_STR_LEN
#define TEMP_STR_LEN	12
#endif

#ifndef M3D_DebugPrint
#ifndef NO_DEBUG_PRINT
#ifndef WIN32
#include <android/log.h>
#define M3D_DebugPrint(...) __android_log_print(ANDROID_LOG_INFO,"ReqListBuffer",__VA_ARGS__)
#else
#define M3D_DebugPrint printf
#endif
#else
#define M3D_DebugPrint(...)
#endif
#endif

#define _fopen(fn, mode)			fopen(fn, mode)
#define _fclose(fp)					fclose(fp)
#define _fread(buf, size, fp)		fread(buf,1,size,fp)
#define _fwrite(buf, size, fp)		fwrite(buf,1,size,fp)
#ifdef WIN32
#define _fremove(fname)				remove(fname)
#else
#define _fremove(fname)				unlink(fname)
#endif


//----------------------------------����洢�ռ�---------------------------------//
//���徲̬bufferָ��
static SongBufInfo_t BufferSong[BUFFER_SONG_TYPE_COUNT];
static SingerBufInfo_t BufferSinger[BUFFER_SINGER_TYPE_COUNT];

//--------------------------------���������������--------------------------------//
static const char* SqlSongString[BUFFER_SONG_TYPE_COUNT] = 
{
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE (LanType = 4 OR LanType = 12) AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// pinyin
		
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 1 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language CN
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 4 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language EN
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE (LanType = 5 OR LanType = 19) AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language JP
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 6 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language KR
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 7 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language VIE
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 8 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language TH
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE (LanType = 9 OR LanType = 20) AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// song language RU
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 11 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language SP
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 12 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language PHI
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 15 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language FR
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 18 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language ID
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 22 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language IN
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE LanType = 28 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// language MY
	
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE FileType = 4 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// download MP3
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE FileType = 3 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// download MTV
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM TableSong WHERE FileType = 5 AND PrivacyFlag = 0 ORDER BY FirstWord COLLATE NOCASE;",// download MOVIE
	
	"SELECT SongIndex, OrderIndex, FileType, SubFileType, SongName, FirstWord FROM View_Popular ORDER BY FirstWord COLLATE NOCASE;"// popular
};

static const char* SqlSingerString[BUFFER_SINGER_TYPE_COUNT] = 
{
	"SELECT SingerIndex, SingerName, FirstWord, Sex FROM TableSinger WHERE Sex = 1 ORDER BY FirstWord COLLATE NOCASE;",// MALE
	"SELECT SingerIndex, SingerName, FirstWord, Sex FROM TableSinger WHERE Sex = 2 ORDER BY FirstWord COLLATE NOCASE;",// FEMALE
	"SELECT SingerIndex, SingerName, FirstWord, Sex FROM TableSinger WHERE Sex = 3 ORDER BY FirstWord COLLATE NOCASE;",// BAND
	"SELECT SingerIndex, SingerName, FirstWord, Sex FROM TableSinger WHERE (Sex = 1 OR Sex = 2 OR Sex = 3) ORDER BY FirstWord COLLATE NOCASE;"// ALL
};

//���岿�������sql���
enum
{
	BUF_SQL_GET_VER,
	BUF_SQL_GET_SONGCOUNT,
	BUF_SQL_GET_SINGERCOUNT,

	BUF_SQL_COUNT
};
static const char* BufSqlStr[BUF_SQL_COUNT] = 
{
	"SELECT DBVersion FROM TableDBInfo WHERE ProjectName = '%s' COLLATE NOCASE;",
	"SELECT count(SongIndex) FROM TableSong;",
	"SELECT count(SingerIndex) FROM TableSinger;"
};

//���峣���ַ���
static const char* songFileName = "song_info_buf.bin";
static const char* singerFileName = "singer_info_buf.bin";
static const char* ProjectName = "MK-8509-MO-A";
static const char* DBVer = "Ver1.0.bin";

//--------------------------------�������------------------------------------//
static pthread_t ThreadBufSongHandle;
static pthread_t ThreadBufSingerHandle;
static bool ThreadSongFlag = false;
static bool ThreadSingerFlag = false;
static bool ThreadBufferIsUsed = false;

//���һЩ��ʱ����
#define VERSION_STR_LEN 12
static char CodeBufferVer[VERSION_STR_LEN];
static char TmpSongFilePath[MAX_PATH_LEN];
static char TmpSingerFilePath[MAX_PATH_LEN];

//test
static char tmpDBpath[MAX_PATH_LEN];
static char tmpBufferPath[MAX_PATH_LEN];
static bool sqlSongFlag;
static bool sqlSingerFlag;

//--------------------��BUFFER�а�����----------------------//
inline int bundingNeedSongInfo(sqlite3_stmt** pstmt, NeedSongInfo_t* pinfo, int namesize)
{
	pinfo->SongIndex = sqlite3_column_int(*pstmt, 0);
	pinfo->OrderIndex = sqlite3_column_int(*pstmt, 1);
	pinfo->FileType = sqlite3_column_int(*pstmt, 2);
	pinfo->SubFileType = sqlite3_column_int(*pstmt, 3);
	strncpy(pinfo->SongName, (const char*)sqlite3_column_text(*pstmt, 4), namesize);
	return 5;
}

inline int bundingNeedSingerInfo(sqlite3_stmt** pstmt, NeedSingerInfo_t* pinfo, int namesize)
{
	pinfo->SingerIndex = sqlite3_column_int(*pstmt, 0);
	strncpy(pinfo->SingerName, (const char*)sqlite3_column_text(*pstmt, 1), namesize);
	pinfo->Sex = sqlite3_column_int(*pstmt, 3);
	return 2;
}

inline int FirstWordToAlphaIndex(const char* pstr)
{
	int itemp;
	char ctemp = pstr[0];
	if(ctemp >= 'A' && ctemp <= 'Z')
	{
		itemp = ctemp - 'A' + 1;
	}
	else if(ctemp >= 'a' && ctemp <= 'z')
	{
		itemp = ctemp - 'a' + 1;
	}
	else
		itemp = 0;
	return itemp;
}

//-----------------------------------------------------------------------------//
static bool checkDbVersion(FILE* pfBuf, int dbver)
{
	//������汾
	int versize = sizeof(CodeBufferVer);
	if(_fread(CodeBufferVer, versize, pfBuf) != versize)
		return false;
	if(sqlite3_strnicmp(CodeBufferVer, CODE_BUFFER_VER, sizeof(CODE_BUFFER_VER)) != 0)
		return false;

	// ���db�汾��
	int filedbver;
	if(_fread(&filedbver, sizeof(int), pfBuf) != sizeof(int))
		return false;
	if(filedbver != dbver)
		return false;
	return true;
}

//-----------------------------------------------------------------------------//
static bool writeDbVersion(FILE* pfBuf, int dbver)
{
	//������汾
	int versize = sizeof(CodeBufferVer);
	strncpy(CodeBufferVer, CODE_BUFFER_VER, versize);
	if(_fwrite(CodeBufferVer, versize, pfBuf) != versize)
		return false;

	// ���db�汾��
	if(_fwrite(&dbver, sizeof(int), pfBuf) != sizeof(int))
		return false;
	return true;
}

//-----------------------------------------------------------------------------//
static bool initSongBufInfo(FILE* pfBuf, int index)
{
	//��ȡ��������
	SongBufInfo_t* bufinfo = &BufferSong[index];
	int itemp;
	NeedSongInfo_t* tmpinf;
	RefStruct_2_t* tmpalpha;
	int num, infosize;

	//��ʼ�������ڳ����ͷ���Դ����
	bufinfo->count = 0;
	bufinfo->firstWrdCount = 0;

	//��ȡ������Ϣ
	if(_fread(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	if(itemp > 0)
	{
		try
		{
			bufinfo->pListBuffer = new NeedSongInfo_t[itemp];
		}
		catch(const std::bad_alloc& )
		{
			return false;
		}
		bufinfo->count = itemp;

		//�������
		num = 0;
		infosize = sizeof(NeedSongInfo_t);
		while(num < itemp)
		{
			tmpinf = bufinfo->pListBuffer + num;
			if(_fread(tmpinf, infosize, pfBuf) != infosize)
				goto To_error_end0_;
			num++;
		}
	}

	//��ȡALPHA INDEX��Ϣ
	itemp = sizeof(bufinfo->alphaIdxOffset);
	if(_fread(bufinfo->alphaIdxOffset, itemp, pfBuf) != itemp)
		goto To_error_end0_;

	//��ȡFIRST WORD��Ϣ
	if(_fread(&itemp, sizeof(int), pfBuf) != sizeof(int))
		goto To_error_end0_;
	if(itemp > 0)
	{
		try
		{
			bufinfo->firstWord = new RefStruct_2_t[itemp];
		}
		catch(const std::bad_alloc& )
		{
			goto To_error_end0_;
		}
		bufinfo->firstWrdCount = itemp;

		//����FIRST WORD
		num = 0;
		infosize = sizeof(RefStruct_2_t);
		while(num < itemp)
		{
			tmpalpha = bufinfo->firstWord + num;
			if(_fread(tmpalpha, infosize, pfBuf) != infosize)
				goto To_error_end1_;
			num++;
		}
	}
	return true;

To_error_end0_:

	delete [] bufinfo->pListBuffer;
	return false;

To_error_end1_:

	delete [] bufinfo->pListBuffer;
	delete [] bufinfo->firstWord;
	return false;
}

//-----------------------------------------------------------------------------//
static bool initSingerBufInfo(FILE* pfBuf, int index)
{
	//��ȡ��������
	SingerBufInfo_t* bufinfo = &BufferSinger[index];
	int itemp;
	NeedSingerInfo_t* tmpinf;
	RefStruct_2_t* tmpalpha;
	int num, infosize;
	
	//��ʼ�������ڳ����ͷ���Դ����
	bufinfo->count = 0;
	bufinfo->firstWrdCount = 0;

	//��ȡ������Ϣ
	if(_fread(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	if(itemp > 0)
	{
		try
		{
			bufinfo->pListBuffer = new NeedSingerInfo_t[itemp];
		}
		catch(const std::bad_alloc& )
		{
			return false;
		}
		bufinfo->count = itemp;

		//�������
		num = 0;
		infosize = sizeof(NeedSingerInfo_t);
		while(num < itemp)
		{
			tmpinf = bufinfo->pListBuffer + num;
			if(_fread(tmpinf, infosize, pfBuf) != infosize)
				goto To_error_end0_;
			num++;
		}
	}

	//��ȡALPHA INDEX��Ϣ
	itemp = sizeof(bufinfo->alphaIdxOffset);
	if(_fread(bufinfo->alphaIdxOffset, itemp, pfBuf) != itemp)
		goto To_error_end0_;

	//��ȡFIRST WORD��Ϣ
	if(_fread(&itemp, sizeof(int), pfBuf) != sizeof(int))
		goto To_error_end0_;
	if(itemp > 0)
	{
		try
		{
			bufinfo->firstWord = new RefStruct_2_t[itemp];
		}
		catch(const std::bad_alloc& )
		{
			goto To_error_end0_;
		}
		bufinfo->firstWrdCount = itemp;

		//����FIRST WORD
		num = 0;
		infosize = sizeof(RefStruct_2_t);
		while(num < itemp)
		{
			tmpalpha = bufinfo->firstWord + num;
			if(_fread(tmpalpha, infosize, pfBuf) != infosize)
				goto To_error_end1_;
			num++;
		}
	}
	return true;

To_error_end0_:

	delete [] bufinfo->pListBuffer;
	return false;

To_error_end1_:

	delete [] bufinfo->pListBuffer;
	delete [] bufinfo->firstWord;
	return false;
}

//--------------------------------��������д���ļ�--------------------------------//
static bool writeSongBufInfo(FILE* pfBuf, int index)
{
	SongBufInfo_t* bufinfo = &BufferSong[index];
	int itemp;

	//�ж�BUFFER�Ƿ�Ϊ�����ֵ
	if(bufinfo->state != BUFFER_LOAD_STATE_END)
	{
		return false;
	}

	//��������Ϣд���ļ�
	NeedSongInfo_t* ptmpinfo;
	int infosize = sizeof(NeedSongInfo_t);
	itemp = bufinfo->count;
	if(_fwrite(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	for(int i=0; i<itemp; i++)
	{
		ptmpinfo = bufinfo->pListBuffer + i;
		if(_fwrite(ptmpinfo, infosize, pfBuf) != infosize)
			return false;
	}

	//��ȡALPHA INDEX��Ϣ
	itemp = sizeof(bufinfo->alphaIdxOffset);
	if(_fwrite(bufinfo->alphaIdxOffset, itemp, pfBuf) != itemp)
		return false;

	//��FIRST WORDд���ļ�
	RefStruct_2_t* ptmpref;
	int refsize = sizeof(RefStruct_2_t);
	itemp = bufinfo->firstWrdCount;
	if(_fwrite(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	for(int i=0; i<itemp; i++)
	{
		ptmpref = bufinfo->firstWord + i;
		if(_fwrite(ptmpref, refsize, pfBuf) != refsize)
			return false;
	}
	return true;
}

//--------------------------------��������д���ļ�--------------------------------//
static bool writeSingerBufInfo(FILE* pfBuf, int index)
{
	SingerBufInfo_t* bufinfo = &BufferSinger[index];
	int itemp;

	//�ж�BUFFER�Ƿ�Ϊ�����ֵ
	if(bufinfo->state != BUFFER_LOAD_STATE_END)
	{
		return false;
	}

	//��������Ϣд���ļ�
	NeedSingerInfo_t* ptmpinfo;
	int infosize = sizeof(NeedSingerInfo_t);
	itemp = bufinfo->count;
	if(_fwrite(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	for(int i=0; i<itemp; i++)
	{
		ptmpinfo = bufinfo->pListBuffer + i;
		if(_fwrite(ptmpinfo, infosize, pfBuf) != infosize)
			return false;
	}

	//��ȡALPHA INDEX��Ϣ
	itemp = sizeof(bufinfo->alphaIdxOffset);
	if(_fwrite(bufinfo->alphaIdxOffset, itemp, pfBuf) != itemp)
		return false;

	//��FIRST WORDд���ļ�
	RefStruct_2_t* ptmpref;
	int refsize = sizeof(RefStruct_2_t);
	itemp = bufinfo->firstWrdCount;
	if(_fwrite(&itemp, sizeof(int), pfBuf) != sizeof(int))
		return false;
	for(int i=0; i<itemp; i++)
	{
		ptmpref = bufinfo->firstWord + i;
		if(_fwrite(ptmpref, refsize, pfBuf) != refsize)
			return false;
	}
	return true;
}

//--------------------------------�ͷŸ�������--------------------------------//
static bool releaseSongBufInfo(void)
{
	//�ͷŸ���������Դ
	for(int i=0; i<BUFFER_SONG_TYPE_COUNT; i++)
	{
		if(BufferSong[i].state == BUFFER_LOAD_STATE_END)
		{
			delete [] BufferSong[i].pListBuffer;
			delete [] BufferSong[i].firstWord;
			BufferSong[i].state = BUFFER_LOAD_STATE_NONE;
		}
		else if(BufferSong[i].state != BUFFER_LOAD_STATE_NONE)
			return false;
	}
	return true;
}

//---------------------------�ͷŸ��ǻ���---------------------------//
static bool releaseSingerBufInfo(void)
{
	//�ͷŸ���������Դ
	for(int i=0; i<BUFFER_SINGER_TYPE_COUNT; i++)
	{
		if(BufferSinger[i].state == BUFFER_LOAD_STATE_END)
		{
			delete [] BufferSinger[i].pListBuffer;
			delete [] BufferSinger[i].firstWord;
			BufferSinger[i].state = BUFFER_LOAD_STATE_NONE;
		}
		else if(BufferSinger[i].state != BUFFER_LOAD_STATE_NONE)
			return false;
	}
	return true;
}



//-------------------------��ȡ������Ϣ(By File)------------------------------//
bool loadSongBufferByFile(const char* path, int dbver)
{
	FILE* pfBuf;

	pfBuf = _fopen(path, "rb");
	if(!pfBuf)
		return false;

	//���汾
	if(!checkDbVersion(pfBuf, dbver))
		goto To_song_end0_;

	//��ȡ�����б������
	for(int i=0; i<BUFFER_SONG_TYPE_COUNT; i++)
	{
		if(BufferSong[i].state != BUFFER_LOAD_STATE_NONE)
			continue;
		BufferSong[i].state = BUFFER_LOAD_STATE_START;
		if(!initSongBufInfo(pfBuf,i))
		{
			BufferSong[i].state = BUFFER_LOAD_STATE_NONE;
			goto To_song_end0_;
		}
		else
			BufferSong[i].state = BUFFER_LOAD_STATE_END;
	}

	_fclose(pfBuf);
	return true;

To_song_end0_:

	_fclose(pfBuf);
	_fremove(path);
	return false;
}

//-----------------------��ȡ������Ϣ(By File)----------------------------------//
bool loadSingerBufferByFile(const char* path, int dbver)
{
	FILE* pfBuf;

	pfBuf = _fopen(path, "rb");
	if(!pfBuf)
		return false;

	//���汾
	if(!checkDbVersion(pfBuf, dbver))
		goto To_singer_end0_;

	//��ȡ�����б������
	for(int j=0; j<BUFFER_SINGER_TYPE_COUNT; j++)
	{
		if(BufferSinger[j].state != BUFFER_LOAD_STATE_NONE)
			continue;
		BufferSinger[j].state = BUFFER_LOAD_STATE_START;
		if(!initSingerBufInfo(pfBuf,j))
		{
			BufferSinger[j].state = BUFFER_LOAD_STATE_NONE;
			goto To_singer_end0_;
		}
		else
			BufferSinger[j].state = BUFFER_LOAD_STATE_END;
	}

	_fclose(pfBuf);
	return true;

To_singer_end0_:

	_fclose(pfBuf);
	_fremove(path);
	return false;
}

//-------------------------д��������Ϣ(To File)------------------------------//
static bool writeSongBufferToFile(const char* path, int dbver)
{
	FILE* pfBuf;
	int i=0;

	pfBuf = _fopen(path, "wb");
	if(!pfBuf)
		return false;

	//д��汾��
	if(!writeDbVersion(pfBuf, dbver))
		goto To_write_failed_;

	//��ȡ�����б������
	for(i=0; i<BUFFER_SONG_TYPE_COUNT; i++)
	{
		if(!writeSongBufInfo(pfBuf, i))
		{
			goto To_write_failed_;
		}
	}

	_fclose(pfBuf);
	return true;

To_write_failed_:

	_fclose(pfBuf);
	_fremove(path);
	return false;
}

//-------------------------д��������Ϣ(To File)------------------------------//
static bool writeSingerBufferToFile(const char* path, int dbver)
{
	FILE* pfBuf;
	int i=0;

	pfBuf = _fopen(path, "wb");
	if(!pfBuf)
		return false;

	//д��汾��
	if(!writeDbVersion(pfBuf, dbver))
		goto To_write_failed_;

	//��ȡ�����б������
	for(i=0; i<BUFFER_SINGER_TYPE_COUNT; i++)
	{
		if(!writeSingerBufInfo(pfBuf, i))
		{
			goto To_write_failed_;
		}
	}

	_fclose(pfBuf);
	return true;

To_write_failed_:

	_fclose(pfBuf);
	_fremove(path);
	return false;
}


//--------------------��DB�л�ȡ����������Ҫ��Ϣ-----------------------------//
static bool reqSongBufInfo(sqlite3* dbhandle, int index, int totalCount)
{
	SongBufInfo_t* bufinfo;
	sqlite3_stmt* stmt;
	NeedSongInfo_t* ptmpInfo;
	int tmpInfoIdx = 0;
	RefStruct_2_t* ptmpRef;
	int tmpRefIdx = 0;
	int tmpAlphaIdx = 0;
	int itemp;
	int ret;

	bufinfo = &BufferSong[index];

	//������ʱ����
	try
	{
		ptmpInfo = new NeedSongInfo_t[totalCount];		//������Ϣ
	}
	catch(const std::bad_alloc& )
	{
		return false;
	}
	try
	{
		ptmpRef = new RefStruct_2_t[totalCount];		//FirstWord��Ϣ
	}
	catch(const std::bad_alloc& )
	{
		delete [] ptmpInfo;
		return false;
	}

	//INIT(ALPHA INDEX)
	memset(bufinfo->alphaIdxOffset, 0, sizeof(bufinfo->alphaIdxOffset));

	//��ʼ��db��������
	M3D_DebugPrint("<reqSongBufInfo> SqlSongString[%d]: [%s]\n",index,SqlSongString[index]);
	ret = sqlite3_prepare_v2(dbhandle, SqlSongString[index], strlen(SqlSongString[index]), &stmt, 0);
	if(ret != SQLITE_OK)
	{
		delete [] ptmpRef;
		delete [] ptmpInfo;
		return false;
	}
	else
	{
		int namesize = sizeof(ptmpInfo[0].SongName);
		int alphasize = sizeof(ptmpRef[0].alphaData);
		int iretstmt;
		while(sqlite3_step(stmt) == SQLITE_ROW) 
		{
			//�������buffer
			iretstmt = bundingNeedSongInfo(&stmt, &ptmpInfo[tmpInfoIdx], namesize);
			
			//����FirstWord
			if(tmpInfoIdx == 0)
			{
				strncpy(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize);
				ptmpRef[tmpRefIdx].start = 0;
				ptmpRef[tmpRefIdx].count = 1;

				//����ALPHA INDEX
				itemp = FirstWordToAlphaIndex(ptmpRef[tmpRefIdx].alphaData);
				if(itemp >= ALPHA_INDEX_COUNT)
				{
					M3D_DebugPrint("ALPHA_INDEX_COUNT == [%d] is too smaller.\n",ALPHA_INDEX_COUNT);
					delete [] ptmpRef;
					delete [] ptmpInfo;
					return false;
				}
				tmpAlphaIdx = itemp;
			}
			else
			{
				if(sqlite3_strnicmp(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize) == 0)
				{
					ptmpRef[tmpRefIdx].count++;
				}
				else
				{
					tmpRefIdx++;
					strncpy(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize);
					ptmpRef[tmpRefIdx].start = ptmpRef[tmpRefIdx-1].start + ptmpRef[tmpRefIdx-1].count;
					ptmpRef[tmpRefIdx].count = 1;

					//����ALPHA INDEX
					itemp = FirstWordToAlphaIndex(ptmpRef[tmpRefIdx].alphaData);
					if(itemp >= ALPHA_INDEX_COUNT)
					{
						M3D_DebugPrint("ALPHA_INDEX_COUNT == [%d] is too smaller.\n",ALPHA_INDEX_COUNT);
						delete [] ptmpRef;
						delete [] ptmpInfo;
						return false;
					}
					if(tmpAlphaIdx != itemp)
					{
						for(int i=tmpAlphaIdx+1; i<itemp; i++)
						{
							bufinfo->alphaIdxOffset[i] = bufinfo->alphaIdxOffset[i-1];
						}
						tmpAlphaIdx = itemp;
						bufinfo->alphaIdxOffset[tmpAlphaIdx] = tmpRefIdx;
					}
				}
			}
			tmpInfoIdx++;
		}
		sqlite3_finalize(stmt);
	}
	if(tmpInfoIdx > 0)
		tmpRefIdx++;		//����ת��Ϊ��Ŀ

	//�ӻ����н����ݴ洢����(��СBUFFER)
	bufinfo->count = tmpInfoIdx;
	bufinfo->firstWrdCount = tmpRefIdx;
#ifdef USE_A_LITTER_BUFFER
	//������Ϣ����
	bool mallocFlag = true;
	try
	{
		bufinfo->pListBuffer = new NeedSongInfo_t[tmpInfoIdx];
	}
	catch(const std::bad_alloc& )
	{
		bufinfo->pListBuffer = ptmpInfo;
		mallocFlag = false;
	}
	if(mallocFlag)
	{
		memcpy(bufinfo->pListBuffer, ptmpInfo, sizeof(NeedSongInfo_t)*tmpInfoIdx);
		delete [] ptmpInfo;
	}
	//����FirstWord����
	mallocFlag = true;
	try
	{
		bufinfo->firstWord = new RefStruct_2_t[tmpRefIdx];
	}
	catch(const std::bad_alloc& )
	{
		bufinfo->firstWrdCount = tmpRefIdx;
		mallocFlag = false;
	}
	if(mallocFlag)
	{
		memcpy(bufinfo->firstWord, ptmpRef, sizeof(RefStruct_2_t)*tmpRefIdx);
		delete [] ptmpRef;
	}
#else
	bufinfo->pListBuffer = ptmpInfo;
	bufinfo->firstWord = ptmpRef;
#endif
	return true;
}

//------------------��DB�л�ȡ���ǻ�����Ҫ��Ϣ---------------------------//
static bool reqSingerBufInfo(sqlite3* dbhandle, int index, int totalCount)
{
	SingerBufInfo_t* bufinfo;
	sqlite3_stmt* stmt;
	NeedSingerInfo_t* ptmpInfo;
	int tmpInfoIdx = 0;
	RefStruct_2_t* ptmpRef;
	int tmpRefIdx = 0;
	int tmpAlphaIdx = 0;
	int itemp;
	int ret;

	bufinfo = &BufferSinger[index];

	//������ʱ����
	try
	{
		ptmpInfo = new NeedSingerInfo_t[totalCount];		//������Ϣ
	}
	catch(const std::bad_alloc& )
	{
		return false;
	}
	try
	{
		ptmpRef = new RefStruct_2_t[totalCount];		//FirstWord��Ϣ
	}
	catch(const std::bad_alloc& )
	{
		delete [] ptmpInfo;
		return false;
	}

	//INIT(ALPHA INDEX)
	memset(bufinfo->alphaIdxOffset, 0, sizeof(bufinfo->alphaIdxOffset));

	//��ʼ��db��������
	M3D_DebugPrint("<reqSingerBufInfo> SqlSingerString[%d]: [%s]\n",index,SqlSingerString[index]);
	ret = sqlite3_prepare_v2(dbhandle, SqlSingerString[index], strlen(SqlSingerString[index]), &stmt, 0);
	if(ret != SQLITE_OK)
	{
		delete [] ptmpRef;
		delete [] ptmpInfo;
		return false;
	}
	else
	{
		int namesize = sizeof(ptmpInfo[0].SingerName);
		int alphasize = sizeof(ptmpRef[0].alphaData);
		int iretstmt;
		while(sqlite3_step(stmt) == SQLITE_ROW) 
		{
			//�������buffer
			iretstmt = bundingNeedSingerInfo(&stmt, &ptmpInfo[tmpInfoIdx], namesize);

			//����FirstWord
			if(tmpInfoIdx == 0)
			{
				strncpy(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize);
				ptmpRef[tmpRefIdx].start = 0;
				ptmpRef[tmpRefIdx].count = 1;

				//����ALPHA INDEX
				itemp = FirstWordToAlphaIndex(ptmpRef[tmpRefIdx].alphaData);
				if(itemp >= ALPHA_INDEX_COUNT)
				{
					M3D_DebugPrint("ALPHA_INDEX_COUNT == [%d] is too smaller.\n",ALPHA_INDEX_COUNT);
					delete [] ptmpRef;
					delete [] ptmpInfo;
					return false;
				}
				tmpAlphaIdx = itemp;
			}
			else
			{
				if(sqlite3_strnicmp(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize) == 0)
				{
					ptmpRef[tmpRefIdx].count++;
				}
				else
				{
					tmpRefIdx++;
					strncpy(ptmpRef[tmpRefIdx].alphaData, (const char*)sqlite3_column_text(stmt, iretstmt), alphasize);
					ptmpRef[tmpRefIdx].start = ptmpRef[tmpRefIdx-1].start + ptmpRef[tmpRefIdx-1].count;
					ptmpRef[tmpRefIdx].count = 1;
					
					//����ALPHA INDEX
					itemp = FirstWordToAlphaIndex(ptmpRef[tmpRefIdx].alphaData);
					if(itemp >= ALPHA_INDEX_COUNT)
					{
						M3D_DebugPrint("ALPHA_INDEX_COUNT == [%d] is too smaller.\n",ALPHA_INDEX_COUNT);
						delete [] ptmpRef;
						delete [] ptmpInfo;
						return false;
					}
					if(tmpAlphaIdx != itemp)
					{
						for(int i=tmpAlphaIdx+1; i<itemp; i++)
						{
							bufinfo->alphaIdxOffset[i] = bufinfo->alphaIdxOffset[i-1];
						}
						tmpAlphaIdx = itemp;
						bufinfo->alphaIdxOffset[tmpAlphaIdx] = tmpRefIdx;
					}
				}
			}
			tmpInfoIdx++;
		}
		sqlite3_finalize(stmt);
	}
	if(tmpInfoIdx > 0)
		tmpRefIdx++;		//����ת��Ϊ��Ŀ

	//�ӻ����н����ݴ洢����(��СBUFFER)
	bufinfo->count = tmpInfoIdx;
	bufinfo->firstWrdCount = tmpRefIdx;
#ifdef USE_A_LITTER_BUFFER
	//������Ϣ����
	bool mallocFlag = true;
	try
	{
		bufinfo->pListBuffer = new NeedSingerInfo_t[tmpInfoIdx];
	}
	catch(const std::bad_alloc& )
	{
		bufinfo->pListBuffer = ptmpInfo;
		mallocFlag = false;
	}
	if(mallocFlag)
	{
		memcpy(bufinfo->pListBuffer, ptmpInfo, sizeof(NeedSingerInfo_t)*tmpInfoIdx);
		delete [] ptmpInfo;
	}
	//����FirstWord����
	mallocFlag = true;
	try
	{
		bufinfo->firstWord = new RefStruct_2_t[tmpRefIdx];
	}
	catch(const std::bad_alloc& )
	{
		bufinfo->firstWrdCount = tmpRefIdx;
		mallocFlag = false;
	}
	if(mallocFlag)
	{
		memcpy(bufinfo->firstWord, ptmpRef, sizeof(RefStruct_2_t)*tmpRefIdx);
		delete [] ptmpRef;
	}
#else
	bufinfo->pListBuffer = ptmpInfo;
	bufinfo->firstWord = ptmpRef;
#endif
	return true;
}

//-------------------------��ȡ������Ϣ(By DB)------------------------------//
bool loadSongBufferByDB(sqlite3* dbhandle, int total)
{
	char sql_cmd[SQL_STR_LEN];
	sqlite3_stmt* stmt;
	int songtotal = total;
	int ret;

	//��ȡ��������
	if(songtotal <= 0)
	{
		sprintf(sql_cmd, "%s",(char *)BufSqlStr[BUF_SQL_GET_SONGCOUNT]);
		M3D_DebugPrint("<loadSongBufferByDB> sql_cmd: [%s]\n",sql_cmd);
		ret = sqlite3_prepare_v2(dbhandle, sql_cmd, strlen(sql_cmd), &stmt, 0);
		if(ret != SQLITE_OK)
		{
			M3D_DebugPrint("<loadSongBufferByDB>  ---ERROR---.\n");
		}
		else
		{
			if(sqlite3_step(stmt) == SQLITE_ROW)
			{
				songtotal = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
	}
	if(songtotal <= 0)
		return false;

	//��ȡ�����б������
	for(int i=0; i<BUFFER_SONG_TYPE_COUNT; i++)
	{
		if(BufferSong[i].state != BUFFER_LOAD_STATE_NONE)
			continue;
		BufferSong[i].state = BUFFER_LOAD_STATE_START;
		if(!reqSongBufInfo(dbhandle, i, songtotal))
		{
			BufferSong[i].state = BUFFER_LOAD_STATE_NONE;
		}
		else
			BufferSong[i].state = BUFFER_LOAD_STATE_END;
	}
	return true;
}

//-------------------------��ȡ������Ϣ(By DB)------------------------------//
bool loadSingerBufferByDB(sqlite3* dbhandle, int total)
{
	char sql_cmd[SQL_STR_LEN];
	sqlite3_stmt* stmt;
	int singertotal = total;
	int ret;

	//��ȡ��������
	if(singertotal <= 0)
	{
		sprintf(sql_cmd, "%s",(char *)BufSqlStr[BUF_SQL_GET_SINGERCOUNT]);
		M3D_DebugPrint("<loadSingerBufferByDB> sql_cmd: [%s]\n",sql_cmd);
		ret = sqlite3_prepare_v2(dbhandle, sql_cmd, strlen(sql_cmd), &stmt, 0);
		if(ret != SQLITE_OK)
		{
		}
		else
		{
			if(sqlite3_step(stmt) == SQLITE_ROW)
			{
				singertotal = sqlite3_column_int(stmt, 0);
			}
			sqlite3_finalize(stmt);
		}
	}
	if(singertotal <= 0)
		return false;

	//��ȡ�����б������
	for(int i=0; i<BUFFER_SINGER_TYPE_COUNT; i++)
	{
		if(BufferSinger[i].state != BUFFER_LOAD_STATE_NONE)
			continue;
		BufferSinger[i].state = BUFFER_LOAD_STATE_START;
		if(!reqSingerBufInfo(dbhandle, i, singertotal))
		{
			BufferSinger[i].state = BUFFER_LOAD_STATE_NONE;
		}
		else
			BufferSinger[i].state = BUFFER_LOAD_STATE_END;
	}
	return true;
}


//�������崫���̵߳Ļ�����
typedef struct
{
	const char* dbPath;
	int dbversion;
	int dbDataTotal;
} threadBufInfo_t;
static threadBufInfo_t threadInfo;

//------------------����SONG���߳�---------------------------//
static void* threadReqSongBuffer(void* param)
{
	threadBufInfo_t* threadInfo = (threadBufInfo_t*)param;
	const char* dbPath = threadInfo->dbPath;
	int dbver = threadInfo->dbversion;
	int dataTotal = threadInfo->dbDataTotal;
	bool ret;

	//�Ȳ��ļ���ȷ���Ƿ��ܻ��������Ϣ
	ret = loadSongBufferByFile(TmpSongFilePath, dbver);
	if(!ret)								//���ݼ���ʧ��
	{
		//test
		sqlSongFlag = true;
		
		//�߳������´����ݿ�
		sqlite3* dbhandle;
		int dbret = sqlite3_open(dbPath, &dbhandle);
		if(dbret != SQLITE_OK)
		{
			M3D_DebugPrint("<threadReqSongBuffer> OPEN DB FAILED!!!\n");
			return NULL;
		}

		//���ļ���ȡ����ʧ�ܣ���Ĵ�db�л�ȡ����
		ret = loadSongBufferByDB(dbhandle, dataTotal);
		sqlite3_close(dbhandle);
		if(!ret)
			return NULL;					//���ݼ��س���
		//test
		sqlSongFlag = false;

		//db��ȡ���ݳɹ�,�����ļ�
		ret = writeSongBufferToFile(TmpSongFilePath,dbver);
		if(!ret)
			return NULL;					//����д�����
	}
	return NULL;
}

//------------------����SINGER���߳�---------------------------//
static void* threadReqSingerBuffer(void* param)
{
	threadBufInfo_t* threadInfo = (threadBufInfo_t*)param;
	const char* dbPath = threadInfo->dbPath;
	int dbver = threadInfo->dbversion;
	int dataTotal = threadInfo->dbDataTotal;
	bool ret;

	//�Ȳ��ļ���ȷ���Ƿ��ܻ��������Ϣ
	ret = loadSingerBufferByFile(TmpSingerFilePath, dbver);
	if(!ret)									//���ݼ���ʧ��
	{
		//test
		sqlSingerFlag = true;
		
		//�߳������´����ݿ�
		sqlite3* dbhandle;
		int dbret = sqlite3_open(dbPath, &dbhandle);
		if(dbret != SQLITE_OK)
		{
			M3D_DebugPrint("<threadReqSongBuffer> OPEN DB FAILED!!!\n");
			return NULL;
		}

		//���ļ���ȡ����ʧ�ܣ���Ĵ�db�л�ȡ����
		ret = loadSingerBufferByDB(dbhandle, dataTotal);
		sqlite3_close(dbhandle);
		if(!ret)
			return NULL;					//���ݼ��س���
		//test
		sqlSingerFlag = false;

		//db��ȡ���ݳɹ�,�����ļ�
		ret = writeSingerBufferToFile(TmpSingerFilePath, dbver);
		if(!ret)
			return NULL;					//����д�����
	}

	return NULL;
}

#ifndef WIN32
extern int DBStatus;
extern int updateA;
extern int updateB;
#endif
extern int Set_RenderReturn(unsigned long renderval);

void transform(char* str)
{
	int len = strlen(str);	
	for(int i = 0; i < len; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] - 'A' + 'a';
			continue;
		}
		else if(str[i] >= 'a' && str[i] <= 'z' || str[i] >= '0' && str[i]<= '9')
		{
			continue;
		}
		else if(str[i] == ' ')
		{
			if(i == 0)
			{
				for(int j = i; j < len; j++)
				{
					str[j] = str[j+1];
				}
				i--;
				len--;
			}
			continue;
		}
		else
		{
			for(int j = i; j < len; j++)
			{
				str[j] = str[j+1];
			}
			i--;
			len--;
		}
	}
}

void UpdateDB(const char* path, const char* dbPath)
{

	sqlite3* dbhandle;
	int dbret = sqlite3_open(dbPath, &dbhandle);
	if(dbret != SQLITE_OK)
		return;

	char sql_cmd[SQL_STR_LEN];
	int rowA = 0, columnA = 0;
	char **azResultA;
	char * errMsgA = NULL;

	int rowB = 0, columnB = 0;
	char **azResultB;
	char * errMsgB = NULL;

	memset(sql_cmd, 0, sizeof(sql_cmd));
	sprintf(sql_cmd, "SELECT SongName, SongIndex, FirstWord, AlphaIndex FROM TableSong WHERE (LanType = 4 OR LanType = 12 OR LanType = 18 OR LanType = 28) ORDER BY SongName COLLATE NOCASE;");
	sqlite3_get_table(dbhandle, sql_cmd, &azResultA, &rowA, &columnA, &errMsgA);
	if (errMsgA != NULL)
		sqlite3_free(errMsgA);
	
	memset(sql_cmd, 0, sizeof(sql_cmd));
	sprintf(sql_cmd, "SELECT SingerName, SingerIndex, FirstWord, AlphaIndex FROM TableSinger WHERE (LanType = 4 OR LanType = 12 OR LanType = 18 OR LanType = 28) ORDER BY SingerName COLLATE NOCASE;");
	sqlite3_get_table(dbhandle, sql_cmd, &azResultB, &rowB, &columnB, &errMsgB);
	if (errMsgB != NULL)
		sqlite3_free(errMsgB);
#ifndef WIN32
	//updateB = (rowA+rowB > 0)? (rowA+rowB):1;
//	updateA = 0;
#endif	
	char firstWord[128];
	for(int i = 1; i <= rowA; i++)
	{
		sprintf(firstWord, "%s", azResultA[i*columnA]);
		transform(firstWord);
		if(strcmp(firstWord, azResultA[i*columnA+2]))
		{
			sprintf(sql_cmd, "UPDATE TableSong set FirstWord = '%s' WHERE SongIndex = %s;", firstWord, azResultA[i*columnA+1]);
			sqlite3_exec(dbhandle, sql_cmd, NULL, NULL, NULL);
		}
		if((firstWord[0] >= 'a' && firstWord[0] <= 'z') && (firstWord[0]-'a'+1) != atoi(azResultA[i*columnA+3]))
		{
			sprintf(sql_cmd, "UPDATE TableSong set AlphaIndex = %d WHERE SongIndex = %s;", (int)(firstWord[0]-'a'+1), azResultA[i*columnA+1]);
			sqlite3_exec(dbhandle, sql_cmd, NULL, NULL, NULL);
		}
#ifndef WIN32
		//updateA++;
#endif
	}

	for(int i = 1; i <= rowB; i++)
	{
		sprintf(firstWord, "%s", azResultB[i*columnB]);
		transform(firstWord);
		if(strcmp(firstWord, azResultB[i*columnB+2]))
		{
			sprintf(sql_cmd, "UPDATE TableSinger set FirstWord = '%s' WHERE SingerIndex = %s;", firstWord, azResultB[i*columnB+1]);
			sqlite3_exec(dbhandle, sql_cmd, NULL, NULL, NULL);
		}
		if((firstWord[0] >= 'a' && firstWord[0] <= 'z') && (firstWord[0]-'a'+1) != atoi(azResultB[i*columnB+3]))
		{
			sprintf(sql_cmd, "UPDATE TableSinger set AlphaIndex = %d WHERE SingerIndex = %s;", (int)(firstWord[0]-'a'+1), azResultB[i*columnB+1]);
			sqlite3_exec(dbhandle, sql_cmd, NULL, NULL, NULL);
		}
#ifndef WIN32
		//updateA++;
#endif
	}
	
	sqlite3_stmt* stmt;
	int ver = 0;
	sprintf(sql_cmd, BufSqlStr[BUF_SQL_GET_VER], ProjectName);
	int ret = sqlite3_prepare_v2(dbhandle, sql_cmd, strlen(sql_cmd), &stmt, 0);
	if(ret == SQLITE_OK)
	{
		if(sqlite3_step(stmt) == SQLITE_ROW)
		{
			ver = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	sprintf(sql_cmd, "UPDATE TableDBInfo set DBVersion = %d WHERE ProjectName = '%s';", ++ver, ProjectName);
	sqlite3_exec(dbhandle, sql_cmd, NULL, NULL, NULL);

	sqlite3_free_table(azResultA);
	sqlite3_free_table(azResultB);
	sqlite3_close(dbhandle);

}

void checkUpdate(const char* path, const char* dbPath)
{
	FILE* fp;
	char VerPath[MAX_PATH_LEN];
	sprintf(VerPath, "%s%s", path, DBVer);
	
	fp = _fopen(VerPath, "rb");
	if(fp)
	{
		_fclose(fp);
		return;	
	}
		
	fp = _fopen(VerPath, "wb");
	if(!fp)
		return;
	_fclose(fp);

	_fremove(VerPath);
	_fremove(TmpSongFilePath);
	_fremove(TmpSingerFilePath);
#ifndef WIN32
		//DBStatus = 1;	
#endif
	UpdateDB(path, dbPath);
	
	fp = _fopen(VerPath, "wb");
	if(!fp)
		return;
	_fclose(fp);

}


/*
*	���
*	�½��̲߳��������buffer
*	�������:
*	path --------- ���ݻ����ļ����λ��
*	dbPath ------- ���ݿ��ļ�·��
*	total -------- TableSong��������(�� <=0 ��ʾ����)
*/
void openDBDataBuffer(const char* path, const char* dbPath, int total)
{
	M3D_DebugPrint("---openDBDataBuffer([%s],[%s],[%d])---\n",path,dbPath,total);

	int ret;
	sqlite3_stmt* stmt;
	char sql_cmd[SQL_STR_LEN];

	//test
	//dbPath = "/mnt/sda1/KARAOKE/SONG/song.db";
	strncpy(tmpDBpath, dbPath, sizeof(tmpDBpath));
	strncpy(tmpBufferPath, path, sizeof(tmpBufferPath));

	//����·����һ���½�������ļ�֮��
	strncpy(TmpSongFilePath, path, sizeof(TmpSongFilePath));
	strncpy(TmpSingerFilePath, path, sizeof(TmpSingerFilePath));
	strcat(TmpSongFilePath, songFileName);
	strcat(TmpSingerFilePath, singerFileName);
	
	//checkUpdate(path, dbPath);
#ifndef WIN32	
	//DBStatus = 2;
#endif
	//
	threadInfo.dbversion = -1;

	//���DB�汾��
	sqlite3* dbhandle;
	int dbret = sqlite3_open(dbPath, &dbhandle);
	if(dbret != SQLITE_OK)
	{
		M3D_DebugPrint("<openDBDataBuffer> (DB can't open)\n",dbPath);
		return;
	}
	sprintf(sql_cmd, BufSqlStr[BUF_SQL_GET_VER], ProjectName);
	M3D_DebugPrint("<openDBDataBuffer> sql_cmd: [%s]\n",sql_cmd);
	ret = sqlite3_prepare_v2(dbhandle, sql_cmd, strlen(sql_cmd), &stmt, 0);
	if(ret == SQLITE_OK)
	{
		if(sqlite3_step(stmt) == SQLITE_ROW)
		{
			threadInfo.dbversion = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	sqlite3_close(dbhandle);

	//��ʼ��״̬
	for(int i=0; i<BUFFER_SONG_TYPE_COUNT; i++)
	{
		BufferSong[i].state = BUFFER_LOAD_STATE_NONE;
	}
	for(int i=0; i<BUFFER_SINGER_TYPE_COUNT; i++)
	{
		BufferSinger[i].state = BUFFER_LOAD_STATE_NONE;
	}

	//�����߳�
	threadInfo.dbPath = dbPath;
	threadInfo.dbDataTotal = total;
	if(!ThreadSongFlag)
	{
		ret = pthread_create(&ThreadBufSongHandle, NULL, threadReqSongBuffer, &threadInfo);
		if(ret == 0)
			ThreadSongFlag = true;
	}
	if(!ThreadSingerFlag)
	{
		ret = pthread_create(&ThreadBufSingerHandle, NULL, threadReqSingerBuffer, &threadInfo);
		if(ret == 0)
			ThreadSingerFlag = true;
	}

	ThreadBufferIsUsed = true;
}

/*
*	����
*	�ͷ�buffer�����Դ
*/
void closeDBDataBuffer(void)
{
	if(!ThreadBufferIsUsed)
		return;

	//�����߳�
	if(ThreadSongFlag)
	{
		ThreadSongFlag = false;
		pthread_join(ThreadBufSongHandle, NULL);
		
		//�ͷ�buffer
		while(!releaseSongBufInfo())
		{
#ifdef WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}
	}
	if(ThreadSingerFlag)
	{
		ThreadSingerFlag = false;
		pthread_join(ThreadBufSingerHandle, NULL);

		while(!releaseSingerBufInfo())
		{
#ifdef WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}
	}
	ThreadBufferIsUsed = false;

	M3D_DebugPrint("---closeDBDataBuffer---\n");
}

/*
*	��������б�����
*	�������:
*	index ----- BufferSongType_m
*	start ----- reqStart(����������ʼ)
*	count ----- reqCount(������������)
*	para ----- ��ƴ����
*	result ----- ���ݻ���ṹ���ҽ������ʼλ��
*	���ز���:
*	(count == -1) ----- ����
*	(count != -1) ----- ���β���������Ŀ
*/
int reqBufferSongList(int index, int start, int count, const char* para, NeedSongInfo_t** result)
{
	if(!ThreadBufferIsUsed)
		return -1;

	SongBufInfo_t* bufinfo;
	static int reqnum;
	static int begin = 0;
	int end;
	int retcount;
	int paralen = strlen(para);

	bufinfo = &BufferSong[index];

	if(bufinfo->state != BUFFER_LOAD_STATE_END)			//���ݶ�ȡΪ���
		return -1;

	if(count == -1)
	{
		//���±���
		reqnum = bufinfo->count;
		begin = 0;
		//�Ƚ��ҳ�ƴ������ʱ��ƫ����
		if(paralen > 0)
		{
			//ʹ��һ��ALPHA INDEX����
			int itemp = FirstWordToAlphaIndex(para);
			begin = bufinfo->alphaIdxOffset[itemp];
			if(begin >= bufinfo->firstWrdCount)
			{
				reqnum = 0;
				return reqnum;
			}

			while(sqlite3_strnicmp(bufinfo->firstWord[begin].alphaData, para, paralen) != 0)
			{
				begin++;
				if(begin >= bufinfo->firstWrdCount)
				{
					reqnum = 0;
					return reqnum;
				}
			}
			end = begin;
			while(sqlite3_strnicmp(bufinfo->firstWord[end].alphaData, para, paralen) == 0)
			{
				end++;
				if(end >= bufinfo->firstWrdCount)
				{
					end = bufinfo->firstWrdCount - 1;
					reqnum = bufinfo->firstWord[end].start - bufinfo->firstWord[begin].start;
					reqnum += bufinfo->firstWord[end].count;
					return reqnum;
				}
			}
			reqnum = bufinfo->firstWord[end].start - bufinfo->firstWord[begin].start;
		}
		return reqnum;
	}
	else
	{
		if(start < reqnum)
		{
			*result = &bufinfo->pListBuffer[start + bufinfo->firstWord[begin].start];
			retcount = reqnum - start;
			if(retcount > count)
				retcount = count;
			return retcount;
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

/*
*	��������б�����
*	�������:
*	index ----- BufferSingerType_m
*	start ----- reqStart(����������ʼ)
*	count ----- reqCount(������������)
*	para ----- ��ƴ����
*	result ----- ���ݻ���ṹ���ҽ������ʼλ��
*	���ز���:
*	(count == -1) ----- ����
*	(count != -1) ----- ���β���������Ŀ
*/
int reqBufferSingerList(int index, int start, int count, const char* para, NeedSingerInfo_t** result)
{
	if(!ThreadBufferIsUsed)
		return -1;

	SingerBufInfo_t* bufinfo;
	static int reqnum;
	static int begin = 0;
	int end;
	int retcount;
	int paralen = strlen(para);

	bufinfo = &BufferSinger[index];

	if(bufinfo->state != BUFFER_LOAD_STATE_END)			//���ݶ�ȡΪ���
		return -1;

	if(count == -1)
	{
		//���±���
		reqnum = bufinfo->count;
		begin = 0;
		//�Ƚ��ҳ�ƴ������ʱ��ƫ����
		if(paralen > 0)
		{
			//ʹ��һ��ALPHA INDEX����
			int itemp = FirstWordToAlphaIndex(para);
			begin = bufinfo->alphaIdxOffset[itemp];
			if(begin >= bufinfo->firstWrdCount)
			{
				reqnum = 0;
				return reqnum;
			}

			while(sqlite3_strnicmp(bufinfo->firstWord[begin].alphaData, para, paralen) != 0)
			{
				begin++;
				if(begin >= bufinfo->firstWrdCount)
				{
					reqnum = 0;
					return reqnum;
				}
			}
			end = begin;
			while(sqlite3_strnicmp(bufinfo->firstWord[end].alphaData, para, paralen) == 0)
			{
				end++;
				if(end >= bufinfo->firstWrdCount)
				{
					end = bufinfo->firstWrdCount - 1;
					reqnum = bufinfo->firstWord[end].start - bufinfo->firstWord[begin].start;
					reqnum += bufinfo->firstWord[end].count;
					return reqnum;
				}
			}
			reqnum = bufinfo->firstWord[end].start - bufinfo->firstWord[begin].start;
		}
		return reqnum;
	}
	else
	{
		if(start < reqnum)
		{
			*result = &bufinfo->pListBuffer[start + bufinfo->firstWord[begin].start];
			retcount = reqnum - start;
			if(retcount > count)
				retcount = count;
			return retcount;
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

void updateDBDataBuffer()
{
	closeDBDataBuffer();
	_fremove(TmpSongFilePath);
	_fremove(TmpSingerFilePath);
	sqlSingerFlag = true;
	sqlSongFlag = true;
	openDBDataBuffer(tmpBufferPath, tmpDBpath, -1);
	while(sqlSingerFlag || sqlSongFlag)
	{
#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}	
}

