//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : ReqBindingStruct.h
//																	
// Description: data structure used in binding record
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#ifndef REQBINDINGSTRUCT_H
#define REQBINDINGSTRUCT_H

#define BINDING_STR_LEN						256
#define BINDING_SONGNAME_LEN				256
#define BINDING_SINGERNAME_LEN				256
#define BINDING_SINGERICON_PATH_LEN		256
#define BINDING_STRINGDOWNLOAD_LEN		20

#define MAX_BINDREC_COUNT 16
#define MAX_FILE_SUFFIXAL_LEN 10
#define MAX_ORDER_INDEX_LEN 6

#define M3D_MESSAGE_STRLEN1 39
#define M3D_MESSAGE_STRLEN2 56

//! songlist binding struct
typedef struct {
	int	Favo;		//! 0: not favorite song, 1: favorate song
	int	Resv;		//! 0: not reserved song, 1: reserved song
	int	Level;
	int 	SongIndex;	//! song index
	int 	RecState;			//! record song state
	int	Score;		//!highest score
	int 			RecIdx;		//used by record
	int SongType;		//!1:MP3; 2:MTV; 3:MOVIE; 0:OTHER
	int 			LocalDevice;
	int				LocalSongFlag;		//1: localsong , 0:net song
	char SongName[BINDING_SONGNAME_LEN];
	char SingerName[BINDING_SINGERNAME_LEN];
	char firstWord[BINDING_SONGNAME_LEN];
	int SingerIndex;
	int FileType;
	int MediaType;
	char FileSuffixal[MAX_FILE_SUFFIXAL_LEN];
	int dataIndex;		//第几条数据
	int OrderIndex;		//! song id
	char OrderChar[MAX_ORDER_INDEX_LEN];
} SongListBindingStruct_t;

//! singerlist binding struct
typedef struct {
	char SingerName[BINDING_SINGERNAME_LEN];	//! singer name
	unsigned int 	SingerIndex;				//! singer index
	int	SingerType;
	char SingerIconPath[BINDING_SINGERICON_PATH_LEN];
	int SongCount;
	int LanguageType;
	char firstWord;
	int dataIndex;		//第几条数据
} SingerListBindingStruct_t;

#endif

