/****************************************************************
*	
*	FUNCTION:	BUFFER
*	FILE:		ReqListBuffer.h
*	BY:			chenzh
*
****************************************************************/

#ifndef _REQ_LIST_BUFFER_
#define _REQ_LIST_BUFFER_

#define CODE_BUFFER_VER		"Ver 0.07"
#include <sqlite3.h>
#include <pthread.h>

#define MAX_NAME_LEN		128
#define MAX_ALPHA_INDEX		32
#define ALPHA_INDEX_COUNT	32

//buffer
enum
{
	BUFFER_SONG_TYPE_PINYIN,

	BUFFER_SONG_TYPE_LAN_CN,			//
	BUFFER_SONG_TYPE_LAN_EN,			//Ӣ
	BUFFER_SONG_TYPE_LAN_JP,			//
	BUFFER_SONG_TYPE_LAN_KR,			//
	BUFFER_SONG_TYPE_LAN_VIE,			//Խ
	BUFFER_SONG_TYPE_LAN_TH,			//̩
	BUFFER_SONG_TYPE_LAN_RU,			//
	BUFFER_SONG_TYPE_LAN_SP,			//
	BUFFER_SONG_TYPE_LAN_PHI,			//ɱ
	BUFFER_SONG_TYPE_LAN_FR,			//
	BUFFER_SONG_TYPE_LAN_ID,			//ӡ
	BUFFER_SONG_TYPE_LAN_IN,			//ӡ
	BUFFER_SONG_TYPE_LAN_MY,			//

	BUFFER_SONG_TYPE_MP3,
	BUFFER_SONG_TYPE_MTV,
	BUFFER_SONG_TYPE_MOVIE,

	BUFFER_SONG_TYPE_POP,				//popular

	BUFFER_SONG_TYPE_COUNT
};

//buffer
enum
{
	BUFFER_SINGER_TYPE_MALE,
	BUFFER_SINGER_TYPE_FEMALE,
	BUFFER_SINGER_TYPE_BAND,
	BUFFER_SINGER_TYPE_ALL,

	BUFFER_SINGER_TYPE_COUNT
};

//state
typedef enum
{
	BUFFER_LOAD_STATE_NONE,
	BUFFER_LOAD_STATE_START,
	BUFFER_LOAD_STATE_END

} BufLoadState_m;


//-----------------------------------------------------------------------//
//
typedef struct
{
	int start;
	int count;
} RefStruct_1_t;

//
typedef struct
{
	int start;
	int count;
	char alphaData[MAX_ALPHA_INDEX];
} RefStruct_2_t;

//Info
typedef struct
{
	int SongIndex;
	int OrderIndex;
	int FileType;
	int SubFileType;
	char SongName[MAX_NAME_LEN];

} NeedSongInfo_t;

//Info
typedef struct
{
	int SingerIndex;
	int Sex;
	char SingerName[MAX_NAME_LEN];

} NeedSingerInfo_t;

//buffer
typedef struct
{
	BufLoadState_m state;
	int count;
	NeedSongInfo_t* pListBuffer;
	int alphaIdxOffset[ALPHA_INDEX_COUNT];			//һALPHA INDEX
	int firstWrdCount;
	RefStruct_2_t* firstWord;

} SongBufInfo_t;

//buffer
typedef struct
{
	BufLoadState_m state;
	int count;
	NeedSingerInfo_t* pListBuffer;
	int alphaIdxOffset[ALPHA_INDEX_COUNT];			//һALPHA INDEX
	int firstWrdCount;
	RefStruct_2_t* firstWord;

} SingerBufInfo_t;


//--------------------------------------ʵ------------------------------------//
/*
*	
*	½̲߳buffer
*	:
*	path --------- ݻļλ
*	dbPath ------- ݿļ·
*	total -------- TableSong( <=0 ʾ)
*/
void openDBDataBuffer(const char* path, const char* dbPath, int total);

/*
*	
*	ͷbufferԴ
*/
void closeDBDataBuffer(void);

/*
*	б
*	:
*	index ----- BufferSongType_m
*	start ----- reqStart(ʼ)
*	count ----- reqCount()
*	para ----- ƴ
*	result ----- ݻṹҽʼ�?
*	ز:
*	(count == -1) ----- 
*	(count != -1) ----- βĿ
*/
int reqBufferSongList(int index, int start, int count, const char* para, NeedSongInfo_t** result);

/*
*	б
*	:
*	index ----- BufferSingerType_m
*	start ----- reqStart(ʼ)
*	count ----- reqCount()
*	para ----- ƴ
*	result ----- ݻṹҽʼ�?
*	ز:
*	(count == -1) ----- 
*	(count != -1) ----- βĿ
*/
int reqBufferSingerList(int index, int start, int count, const char* para, NeedSingerInfo_t** result);


//add for test
void updateDBDataBuffer();


#endif
