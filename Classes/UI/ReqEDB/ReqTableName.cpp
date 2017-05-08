#include "ReqTableName.h"

//Vession Parameter Table
std::string ReqTableName::TableVession = "TableVession";

std::string ReqTableName::KEY_Vession = "Vession";
std::string ReqTableName::KEY_Customer  = "Customer_No";

//Favo Song Table
//Create Table TableFavo(SongIndex long)
//Insert into TableFavo(SongIndex) values()
//Delete from TableFavo where SongIndex=?
//Favo table
std::string ReqTableName::TableFavo = "TableFavo";

std::string ReqTableName::FavoTable_CreateCmd ="CREATE TABLE TableFavo(SongIndex long,InsertId long)";
std::string ReqTableName::FavoTable_InsertCmd_Prefix="INSERT INTO TableFavo(SongIndex,InsertId) VALUES(";
std::string ReqTableName::FavoTable_InsertCmd_Suffix=") ORDER BY InsertId";
std::string ReqTableName::FavoTable_DeleteCmd ="DELETE FROM TableFavo WHERE SongIndex=";
//std::string ReqTableName::FavoTable_DeleteCmd_Suffix =" ORDER BY InsertId";

std::string ReqTableName::FavoTable_DeleteAllCmd ="DELETE FROM TableFavo WHERE SongIndex>0";
std::string ReqTableName::FavoTable_SelectCmd = "SELECT * FROM TableFavo WHERE SongIndex=";

std::string ReqTableName::KEY_INSERT_ID="InsertId";

//Prog table

std::string ReqTableName::TableProg = "TableProg";

std::string ReqTableName::ProgTable_CreateCmd ="CREATE TABLE TableProg(SongIndex long,InsertId long)";
std::string ReqTableName::ProgTable_InsertCmd_Prefix="INSERT INTO TableProg(SongIndex,InsertId) VALUES(";
std::string ReqTableName::ProgTable_InsertCmd_Suffix=") ORDER BY InsertId";
std::string ReqTableName::ProgTable_DeleteCmd ="DELETE FROM TableProg WHERE InsertId=";

std::string ReqTableName::ProgTable_DeleteAllCmd ="DELETE FROM TableProg WHERE SongIndex>0";
std::string ReqTableName::ProgTable_SelectCmd = "SELECT * FROM TableProg WHERE SongIndex=";
//update TableProg set InsertId= where InsertId= 
//std::string ReqTableName::ProgTable_UpdateCmd_Prefix = "UPDATE TableProg SET InsertID=";
//std::string ReqTableName::ProgTable_UpdateCmd_Suffix = " WHERE InsertID=";

//Record table
std::string ReqTableName::TableRecord = "TableRecord";
std::string ReqTableName::RecTable_CreateCmd ="CREATE TABLE TableRecord(SongIndex long,InsertId long,RecIndex long,Score long,Storage long)";
std::string ReqTableName::RecTable_InsertCmd_Prefix="INSERT INTO TableRecord(SongIndex,InsertId,RecIndex,Score,Storage) VALUES(";
std::string ReqTableName::RecTable_InsertCmd_Suffix=") ORDER BY InsertId";
std::string ReqTableName::RecTable_DeleteCmd ="DELETE FROM TableRecord WHERE InsertId=";

std::string ReqTableName::RecTable_DeleteAllCmd ="DELETE FROM TableRecord WHERE SongIndex>0";
std::string ReqTableName::RecTable_SelectCmd = "SELECT * FROM TableRecord WHERE InsertId=";

std::string ReqTableName::KEY_RECORD_RECINDEX="RecIndex";
std::string ReqTableName::KEY_RECORD_SCORE="Score";
std::string ReqTableName::KEY_RECORD_STORAGE="Storage";

//Language Parameter Table
std::string ReqTableName::TableLanguage = "TableLan";

std::string ReqTableName::KEY_LANGUAGE_TYPE="LanType";
std::string ReqTableName::KEY_LANGUAGE_CN_NAME="LanName_CN";
std::string ReqTableName::KEY_LANGUAGE_EN_NAME="LanName_EG";
std::string ReqTableName::KEY_LANGUAGE_COUNTRY_NAME="CountryName";

std::string ReqTableName::KEY_LANGUAGE_SHOW_TYPE="ShowType";
std::string ReqTableName::KEY_LANGUAGE_FONT_TYPE="FontType";
std::string ReqTableName::KEY_LANGUAGE_ALPHAKIND="AlphaKind";

//Song Parameter Table
std::string ReqTableName::KEY_SONG_PRIVACYFG="PrivacyFlag";
std::string ReqTableName::KEY_SONG_SONGIDX="SongIndex";
std::string ReqTableName::KEY_SONG_ORDERIDX="OrderIndex";
std::string ReqTableName::KEY_SONG_TYPEIDX="TypeIndex";
std::string ReqTableName::KEY_SONG_SUBTYPEIDX="SubTypeIndex";
std::string ReqTableName::KEY_SONG_SONGNAME="SongName";
std::string ReqTableName::KEY_SONG_LANTYPE="LanType";
std::string ReqTableName::KEY_SONG_SUBLANTYPE="SubLanType";
std::string ReqTableName::KEY_SONG_WORDS="Words";
std::string ReqTableName::KEY_SONG_FIRSTWORD="FirstWord";
std::string ReqTableName::KEY_SONG_FIRSTSTROKE="FirstStroke";
std::string ReqTableName::KEY_SONG_BACKVIDEO="BackVideo";
std::string ReqTableName::KEY_SONG_VOLUME="Volume";
std::string ReqTableName::KEY_SONG_CHANNEL="Channel";
std::string ReqTableName::KEY_SONG_SINGERINDEX="SingerIndex";
std::string ReqTableName::KEY_SONG_SINGERNAME="SingerName";
std::string ReqTableName::KEY_SONG_SINGERNAMEEN="SingerNameEn";
std::string ReqTableName::KEY_SONG_SINGERFW="SingerFW";
std::string ReqTableName::KEY_SONG_SEX="Sex";

//Persang db function --- Hindi subType  Album
std::string ReqTableName::KEY_SONG_BHAJANFG="Bhajanfg";
std::string ReqTableName::KEY_SONG_PATRIOTICFG="Patrioticfg";
std::string ReqTableName::KEY_SONG_DUETFG="Duetfg";
std::string ReqTableName::KEY_SONG_SOLOFG="Solofg";
std::string ReqTableName::KEY_SONG_SUFIFG="Sufifg";
std::string ReqTableName::KEY_SONG_ROMATICFG="Romaticfg";
std::string ReqTableName::KEY_SONG_GHAZALFG="Ghazalfg";
std::string ReqTableName::KEY_SONG_EVERFG="Everfg";
std::string ReqTableName::KEY_SONG_BIRTHDAYFG="Birthdayfg";
std::string ReqTableName::KEY_SONG_CLASSICALFG="Classicalfg";
std::string ReqTableName::KEY_SONG_POPULARFG="Popularfg";
std::string ReqTableName::KEY_SONG_ALBUMINDEX="AlbumIndex";
std::string ReqTableName::KEY_SONG_ALBUMNAME="AlbumName";
std::string ReqTableName::KEY_SONG_ALBUMNAMEEN="AlbumNameEN";
std::string ReqTableName::KEY_SONG_ALBUMFW="AlbumFW";

//data Table
std::string ReqTableName::SubTbl_SongName = "SongName";
std::string ReqTableName::SubTbl_BookNumber = "BookNumber";
std::string ReqTableName::SubTbl_SongToSinger = "SongToSinger";
std::string ReqTableName::SubTbl_Singer = "Singer";
std::string ReqTableName::SubTbl_SearchTitle = "SearchTitle";
std::string ReqTableName::SubTbl_SearchSinger = "SearchSinger";
std::string ReqTableName::SubTbl_SingerToSong = "SingerToSong";
std::string ReqTableName::SubTbl_SongToAlbum = "SongToAlbum";

//"SingerEnglish.tbl"
std::string ReqTableName::SingerTbl_BasicName="Singer";
//"SearchEngland.tbl"
std::string ReqTableName::SearchSingerTbl_BasicName = "Search";

//default key value
std::string ReqTableName::DEFAULT_SINGER_NAME="UNKNOWN";

//"HindiBhajan.tbl"
std::string ReqTableName::HindiSubTypeTbl_BasicName="Hindi";

//"Album.tbl"
std::string ReqTableName::AlbumTbl_BasicName="Album";

/*
std::string ReqTableName::LanTbl_Chinese = "Chinese";    // 1

std::string ReqTableName::LanTbl_English = "English";    // 4

std::string ReqTableName::LanTbl_Korean = "Korean";      // 6
std::string ReqTableName::LanTbl_Vietnam = "Vietnam";     // 7
std::string ReqTableName::LanTbl_Thai = "Thai";  	//8

std::string ReqTableName::LanTbl_Brazil = "Brazil";  // 10 
std::string ReqTableName::LanTbl_Spanish = "Spanish";  // 11 
std::string ReqTableName::LanTbl_Tagalog = "Tagalog";  // 12
std::string ReqTableName::LanTbl_Italian = "Italian";  // 13
std::string ReqTableName::LanTbl_Germany = "Germany";   // 14
std::string ReqTableName::LanTbl_French = "French";     // 15
std::string ReqTableName::LanTbl_Portuguese = "Portuguese"; // 16

std::string ReqTableName::LanTbl_Indonesian = "Indonesian";  // 18
std::string ReqTableName::LanTbl_Japanese = "Japanese";  // 19
std::string ReqTableName::LanTbl_Russian = "Russian";   // 20
std::string ReqTableName::LanTbl_Dutch = "Dutch";		// 21 ∫…¿º”Ô
std::string ReqTableName::LanTbl_Hindi = "Hindi";   // 22

std::string ReqTableName::LanTbl_Persian = "Persian";   // 24   ≤®Àπ”Ô
std::string ReqTableName::LanTbl_Hebrew = "Hebrew";  // 25  œ£≤Æ¿¥”Ô
std::string ReqTableName::LanTbl_Polish = "Polish";  // 26  ≤®¿º”Ô

std::string ReqTableName::LanTbl_Bhajans = "Bhajans"; // 28 <--> Bhajan
std::string ReqTableName::LanTbl_Malaysia = "Malaysia"; // 29

std::string ReqTableName::LanTbl_Mongolian = "Mongolian";  // 35
std::string ReqTableName::LanTbl_Arabic = "Arabic";     // 36
std::string ReqTableName::LanTbl_Tuikish = "Tuikish";   // 37

std::string ReqTableName::LanTbl_Garba = "Garba";		// 39
std::string ReqTableName::LanTbl_Gujarati = "Gujarati";  // 40
std::string ReqTableName::LanTbl_Malayalam = "Malayalam";	// 41
std::string ReqTableName::LanTbl_Marathi = "Marathi";		// 42
std::string ReqTableName::LanTbl_Tamil = "Tamil";			// 43
std::string ReqTableName::LanTbl_Telugu = "Telugu";			// 44
std::string ReqTableName::LanTbl_Bengali = "Bengali";		// 45
std::string ReqTableName::LanTbl_Kannada = "Kannada";		// 46
std::string ReqTableName::LanTbl_Sinhala = "Sinhala";		// 47
std::string ReqTableName::LanTbl_Konkani = "Konkani";		// 48
std::string ReqTableName::LanTbl_Urdu = "Urdu";				// 49
std::string ReqTableName::LanTbl_Punjabi = "Punjabi";		// 50
std::string ReqTableName::LanTbl_Translate = "Translate";	// 51
std::string ReqTableName::LanTbl_Nepali = "Nepali";			// 52
std::string ReqTableName::LanTbl_Bhojpuri = "Bhojpuri";		// 53

std::string ReqTableName::LanTbl_Foreign = "Foreign";
*/

std::string ReqTableName::SubTableName[ReqTableName::SubTableCnt] = 
{
	ReqTableName::SubTbl_SongName,	
	ReqTableName::SubTbl_BookNumber,  
	ReqTableName::SubTbl_SongToSinger,
	ReqTableName::SubTbl_Singer,	  
	ReqTableName::SubTbl_SearchTitle, 
	ReqTableName::SubTbl_SearchSinger,
	ReqTableName::SubTbl_SingerToSong
};

//Hindi sub type
std::string ReqTableName::HindiSubTypes[MAX_HINDI_SUBTYPE_NUM] = 
{
	ReqTableName::KEY_SONG_BHAJANFG,
	ReqTableName::KEY_SONG_PATRIOTICFG,
	ReqTableName::KEY_SONG_DUETFG,
	ReqTableName::KEY_SONG_SOLOFG,
	ReqTableName::KEY_SONG_SUFIFG,
	ReqTableName::KEY_SONG_ROMATICFG,
	ReqTableName::KEY_SONG_GHAZALFG,
	ReqTableName::KEY_SONG_EVERFG,
	ReqTableName::KEY_SONG_BIRTHDAYFG,
	ReqTableName::KEY_SONG_CLASSICALFG,
	ReqTableName::KEY_SONG_POPULARFG
};


/*
std::string ReqTableName::LanguageTableName[ReqTableName::LanguageTableCnt] = 
{
	ReqTableName::LanTbl_Chinese,
	ReqTableName::LanTbl_English,
	ReqTableName::LanTbl_Korean,
	ReqTableName::LanTbl_Vietnam,
	ReqTableName::LanTbl_Thai,
	ReqTableName::LanTbl_Brazil,
	ReqTableName::LanTbl_Spanish,
	ReqTableName::LanTbl_Tagalog,
	ReqTableName::LanTbl_Italian,
	ReqTableName::LanTbl_Germany,
	ReqTableName::LanTbl_French,
	ReqTableName::LanTbl_Portuguese,
	ReqTableName::LanTbl_Indonesian,
	ReqTableName::LanTbl_Japanese,
	ReqTableName::LanTbl_Russian,
	ReqTableName::LanTbl_Dutch,
	ReqTableName::LanTbl_Hindi,
	ReqTableName::LanTbl_Persian,
	ReqTableName::LanTbl_Hebrew,
	ReqTableName::LanTbl_Polish,
	ReqTableName::LanTbl_Bhajans,
	ReqTableName::LanTbl_Malaysia,
	ReqTableName::LanTbl_Mongolian,
	ReqTableName::LanTbl_Arabic,
	ReqTableName::LanTbl_Tuikish,
	ReqTableName::LanTbl_Garba,
	ReqTableName::LanTbl_Gujarati,
	ReqTableName::LanTbl_Malayalam,
	ReqTableName::LanTbl_Marathi,
	ReqTableName::LanTbl_Tamil,
	ReqTableName::LanTbl_Telugu,
	ReqTableName::LanTbl_Bengali,
	ReqTableName::LanTbl_Kannada,
	ReqTableName::LanTbl_Sinhala,
	ReqTableName::LanTbl_Konkani,
	ReqTableName::LanTbl_Urdu,
	ReqTableName::LanTbl_Punjabi,
	ReqTableName::LanTbl_Nepali,
	ReqTableName::LanTbl_Bhojpuri
};
*/




