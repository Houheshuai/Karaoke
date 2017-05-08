#ifndef _REQTABLENAME_H
#define _REQTABLENAME_H

#include <string>
#include <unordered_map>

//using namespace std;
#define MAX_HINDI_SUBTYPE_NUM 11

class ReqTableName
{
	public:
	static	std::string TableVession;
		
	static	std::string KEY_Vession;
	static	std::string KEY_Customer;
	
	static std::string TableFavo;
	//static std::string KEY_FAVO_ID;
	static std::string FavoTable_CreateCmd;
	static std::string FavoTable_InsertCmd_Prefix;
	static std::string FavoTable_InsertCmd_Suffix;
	static std::string FavoTable_DeleteCmd;
	//static std::string FavoTable_DeleteCmd_Suffix;
	static std::string FavoTable_DeleteAllCmd;
	static std::string FavoTable_SelectCmd; 

	static std::string KEY_INSERT_ID;
	
	static std::string TableProg;
	
	static std::string ProgTable_CreateCmd;
	static std::string ProgTable_InsertCmd_Prefix;
	static std::string ProgTable_InsertCmd_Suffix;
	static std::string ProgTable_DeleteCmd;
	
	static std::string ProgTable_DeleteAllCmd;
	static std::string ProgTable_SelectCmd;
	static std::string TableRecord;
	static std::string RecTable_CreateCmd;
	static std::string RecTable_InsertCmd_Prefix;
	static std::string RecTable_InsertCmd_Suffix;
	static std::string RecTable_DeleteCmd;
	
	static std::string RecTable_DeleteAllCmd;
	static std::string RecTable_SelectCmd;
	static std::string KEY_RECORD_RECINDEX;
	static std::string KEY_RECORD_SCORE;
	static std::string KEY_RECORD_STORAGE;

	static std::string TableLanguage;
	
	static std::string KEY_LANGUAGE_TYPE;
	static std::string KEY_LANGUAGE_CN_NAME;
	static std::string KEY_LANGUAGE_EN_NAME;
	static std::string KEY_LANGUAGE_COUNTRY_NAME;
	static std::string KEY_LANGUAGE_SHOW_TYPE;
	static std::string KEY_LANGUAGE_FONT_TYPE;
	static std::string KEY_LANGUAGE_ALPHAKIND;

	
	static std::string KEY_SONG_PRIVACYFG;
	static std::string KEY_SONG_SONGIDX;
	static std::string KEY_SONG_ORDERIDX;
	static std::string KEY_SONG_TYPEIDX;
	static std::string KEY_SONG_SUBTYPEIDX;
	static std::string KEY_SONG_SONGNAME;
	static std::string KEY_SONG_LANTYPE;
	static std::string KEY_SONG_SUBLANTYPE;
	static std::string KEY_SONG_WORDS;
	static std::string KEY_SONG_FIRSTWORD;
	static std::string KEY_SONG_FIRSTSTROKE;
	static std::string KEY_SONG_BACKVIDEO;
	static std::string KEY_SONG_VOLUME;
	static std::string KEY_SONG_CHANNEL;
	static std::string KEY_SONG_SINGERINDEX;
	static std::string KEY_SONG_SINGERNAME;
	static std::string KEY_SONG_SINGERNAMEEN;
	static std::string KEY_SONG_SINGERFW;
	static std::string KEY_SONG_SEX;
	
	//Persang db function --- Hindi subType  Album
	static std::string KEY_SONG_BHAJANFG;
	static std::string KEY_SONG_PATRIOTICFG;
	static std::string KEY_SONG_DUETFG;
	static std::string KEY_SONG_SOLOFG;
	static std::string KEY_SONG_SUFIFG;
	static std::string KEY_SONG_ROMATICFG;
	static std::string KEY_SONG_GHAZALFG;
	static std::string KEY_SONG_EVERFG;
	static std::string KEY_SONG_BIRTHDAYFG;
	static std::string KEY_SONG_CLASSICALFG;
	static std::string KEY_SONG_POPULARFG;
	static std::string KEY_SONG_ALBUMINDEX;
	static std::string KEY_SONG_ALBUMNAME;
	static std::string KEY_SONG_ALBUMNAMEEN;
	static std::string KEY_SONG_ALBUMFW;


	static const int SubTableCnt = 7;
	static std::string SubTbl_SongName;
	static std::string SubTbl_BookNumber;
	static std::string SubTbl_SongToSinger;
	static std::string SubTbl_Singer;
	static std::string SubTbl_SearchTitle;
	static std::string SubTbl_SearchSinger;
	static std::string SubTbl_SingerToSong;

	static std::string SingerTbl_BasicName;
	static std::string SearchSingerTbl_BasicName;

	//default value for some key
	static std::string DEFAULT_SINGER_NAME;
	
	//"HindiBhajan.tbl"
	static std::string HindiSubTypeTbl_BasicName;
	
	static std::string SubTbl_SongToAlbum;
	//"Album.tbl"
	static std::string AlbumTbl_BasicName;
/*
	static const int LanguageTableCnt = 39;
	
	static std::string LanTbl_Chinese;
	static std::string LanTbl_English;
	static std::string LanTbl_Korean;
	static std::string LanTbl_Vietnam;
	static std::string LanTbl_Thai;
	static std::string LanTbl_Brazil;
	static std::string LanTbl_Spanish;
	static std::string LanTbl_Tagalog;
	static std::string LanTbl_Italian;
	static std::string LanTbl_Germany;
	static std::string LanTbl_French;
	static std::string LanTbl_Portuguese;
	static std::string LanTbl_Indonesian;
	static std::string LanTbl_Japanese;
	static std::string LanTbl_Russian;
	static std::string LanTbl_Dutch;
	static std::string LanTbl_Hindi;
	static std::string LanTbl_Persian;
	static std::string LanTbl_Hebrew;
	static std::string LanTbl_Polish;
	static std::string LanTbl_Bhajans;
	static std::string LanTbl_Malaysia;
	static std::string LanTbl_Mongolian;
	static std::string LanTbl_Arabic;
	static std::string LanTbl_Tuikish;
	static std::string LanTbl_Garba;
	static std::string LanTbl_Gujarati;
	static std::string LanTbl_Malayalam;
	static std::string LanTbl_Marathi;
	static std::string LanTbl_Tamil;
	static std::string LanTbl_Telugu;
	static std::string LanTbl_Bengali;
	static std::string LanTbl_Kannada;
	static std::string LanTbl_Sinhala;
	static std::string LanTbl_Konkani;
	static std::string LanTbl_Urdu;
	static std::string LanTbl_Punjabi;
	static std::string LanTbl_Translate;
	static std::string LanTbl_Nepali;
	static std::string LanTbl_Bhojpuri;
	static std::string LanTbl_Foreign;
*/
	static std::string SubTableName[ReqTableName::SubTableCnt];
	static std::string HindiSubTypes[MAX_HINDI_SUBTYPE_NUM];

	//static std::string LanguageTableName[ReqTableName::LanguageTableCnt];

};
#endif
