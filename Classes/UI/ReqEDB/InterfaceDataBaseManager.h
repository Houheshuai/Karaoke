#ifndef _INTERFACE_DATABASE_H
#define _INTERFACE_DATABASE_H

#include <string>
//#include "SongParam.h"

extern "C"
{
#include "../krklib/include/lib/edb/edb.h"
}
#include "RecSongParam.h"
class InterfaceDataBaseManager
{
	public:

        virtual ~InterfaceDataBaseManager(){};

		virtual void setProgramSave(bool progsave)=0;
		virtual int setDataBasePath(const std::string& dirPath)=0;

		//virtual void setPrePageSize(int pagesize)=0;

		virtual std::string reqTableVersion(void)=0;
		virtual int reqCustomerNo(void)=0;
		virtual int reqLanguageList(void)=0;
		//virtual void SortTopLan(int lanId) = 0;
		//virtual void SkipOneLan(int lanId) = 0;

		virtual int reqLanTypeByResultPos(int position)=0;
		virtual std::string reqLanNameEGByLanType(int lantype)=0;

		virtual std::string reqCountryNameByLanType(int lantype)= 0;
		virtual int reqLanSongQuantity(int lantype)=0;
		virtual int reqLanSongQuantity(TABLE_HANDLE* table)=0;
		virtual int reqLanSongList(int lantype,std::string inputstr="")=0;
		//virtual int reqSongInfoInOnePage(int songLan,int startidx)=0;
		virtual TABLE_HANDLE* reqTableByLanguage(int lantype,std::string inputstr="")=0;

		virtual int reqSongIndexByTablePos(TABLE_HANDLE* table,int position)=0;
		virtual std::string reqSongNameBySongIndex(int songindex)=0;

		virtual int reqFileTypeBySongIndex(int songindex) = 0;

		virtual int reqSubTypeBySongIndex(int songindex) = 0;
		virtual char reqFirstWordBySongIndex(int songindex)=0;
		//virtual int reqSongParamBySongIndex(SongParam* songInfo)=0;
	    virtual	int reqSingerIndexBySongIndex(int songindex) = 0;

		/*
			Enflag:true 显示英文名
			          false 显示中/日/韩/印度文暂不支持
		*/
		virtual std::string reqSingerNameBySingerIndex(int singerindex,bool Enflag=true) = 0;

		virtual int reqSingerLanTypeByResultPos(int position)= 0;
		virtual int reqSingerQuantityByLanType(int lantype)= 0;

		virtual int reqSingerLanguageList(void)= 0;

		virtual TABLE_HANDLE* reqSingerListInLanguage(int lantype,std::string inputstr="")=0;
		virtual int reqSingerQuantityInLanguage(TABLE_HANDLE* table)=0;

		//virtual int reqSingerListInLanguage(int lantype)=0;
		virtual int reqSingerIndexByResultPos(int position)=0;

		virtual char reqSingerFirstWordBySingerIndex(int singerindex)=0;
		virtual char reqSingerFirstWordBySongIndex(int songindex)=0;
		virtual int reqSingerSongQuantity(int singerindex)=0;

		virtual int reqSingerSongQuantity(TABLE_HANDLE* table)=0;

		virtual int reqSingerSongList(int singeridx,std::string inputstr="")=0;
		virtual TABLE_HANDLE* reqSingerSongTableBySingerIndex(int singerindex,std::string inputstr="")=0;
		virtual int reqFavoSongQuantity(void)=0;

		virtual int reqFavoSongList(void)=0;
		virtual bool isFavoSong(int songIndex)=0;

		virtual int reqFavoSongIndexByResultPos(int position)=0;
		virtual int reqAddFavoSong(int songIndex) = 0;
		virtual int reqDeleteFavoSong(int songIndex) = 0;
		virtual int reqDeleteAllFavoSongs(void)=0;

		virtual int reqProgSongList(void)=0;
		virtual bool isProgSong(int songIndex)=0;
		virtual int reqProgSongQuantity(void)=0;

		virtual int reqProgSongIndexByResultPos(int position)=0;
		/*
			topfg: true 添加喜爱歌曲的同时，将歌曲置顶

			topfg: default value false
		*/
		virtual int reqAddProgSong(int songIndex,bool topfg=false)=0;

		/*
			addfg: true	 支持同一首歌曲可多次选为预约歌曲

			addfg: default value false
		*/
		virtual int reqSetTopProgSong(int songIndex,bool addfg=false)=0;
		/*
			ProgSong Interface XXXByResultPos  just for Program Form
 		*/
		virtual int reqAddTopProgSongByResultPos(int position)=0;
		virtual int reqDeleteProgSong(int songIndex)=0;
		virtual int reqDeleteProgSongByResultPos(int position)=0;
		virtual int reqDeleteAllProgSongs(void)=0;

		//input string search   暂不使用
		virtual TABLE_HANDLE* reqTableByFullSpell(TABLE_HANDLE* table,std::string inputstr)=0;

		//search
		virtual TABLE_HANDLE* reqSearchSongNoTable(int inputnum = 0)=0;
		virtual int reqSearchSongNoQuantity(TABLE_HANDLE* table)=0;
		virtual TABLE_HANDLE* reqSearchSingerSongTableByLanguage(int lantype,std::string inputstr="")=0;
		virtual int reqSearchSingerSongQuantity(TABLE_HANDLE* table) = 0;
		//record
		virtual int reqRecSongList(void) = 0;
		virtual int reqRecSongQuantity(void) = 0;
		virtual int reqNextRecIndex(int songindex) = 0;
		virtual int reqAddRecSong(RecSongParam* recsong) = 0;
		virtual int reqDeleteRecSongByResultPos(int position) = 0;

		virtual RecSongParam* reqRecSongParamByResultPos(int position) = 0;
		virtual	int reqRecSongIndexByResultPos(int position) = 0;
		virtual	int reqRecScoreByResultPos(int position) = 0;
		virtual int reqRecIndexByResultPos(int position) = 0;
		virtual int reqDeleteAllRecSongs(void)=0;

		virtual int reqAllSongList(void)=0;
		virtual int reqPlayListSongByPosition(int position)=0;

		//hindi sub type
		virtual int reqHindiSubTypes(void)=0;
		virtual std::string reqHindiSubTypeByResultPos(int position)=0;
		virtual int reqSongQuantityByHindiSubTypeName(std::string subtypename)=0;
		virtual TABLE_HANDLE* reqTableByHindiSubTypeName(std::string subtypename,std::string inputstr="")=0;
		virtual int reqHindiSubTypeSongQuantity(TABLE_HANDLE* table)=0;

		//album
		virtual std::string reqAlbumNameByAlbumIndex(int albumindex,bool Enflag=true)=0;

		virtual int reqAlbumLanTypeByResultPos(int position)=0;
		virtual int reqAlbumQuantityByLanType(int lantype)=0;
		virtual int reqAlbumLanguageList(void)=0;

		virtual TABLE_HANDLE* reqAlbumListInLanguage(int lantype,std::string inputstr="")=0;

		virtual int reqAlbumQuantityInLanguage(TABLE_HANDLE* table)=0;
		virtual int reqAlbumIndexByResultPos(int position)=0;
		virtual char reqAlbumFirstWordByAlbumIndex(int albumindex)=0;
		virtual int reqAlbumSongQuantity(int albumindex)=0;
		virtual int reqAlbumSongQuantity(TABLE_HANDLE* table)=0;
		virtual int reqAlbumSongList(int albumindex,std::string inputstr="")=0;
		virtual TABLE_HANDLE* reqAlbumSongTableByAlbumIndex(int albumindex,std::string inputstr="")=0;
	private:
};

extern "C" void GetDataBaseManager(InterfaceDataBaseManager *&_dataBaseManager);

#endif
