#ifndef _SONGPARAM_H
#define _SONGPARAM_H

#include <string>

class SongParam
{
	public:
		
		SongParam();
		~SongParam();
		void reset();
		void setSongIndex(int songidx);
		int getSongIndex(void);		
		
		void setSongLan(int lantype);
		int getSongLan(void);

		void setFileType(int ftype);
		int getFileType(void);

		void setSubType(int stype);
		int getSubType(void);
		
		void setFavFlag(int favfg); 
		int getFavFlag(void);
		
		void setProgFlag(int progfg);
		int getProgFlag(void);
		
		void setSongName(std::string songname);
		std::string getSongName(void);

		void setSingerName(std::string singername);
		std::string getSingerName(void);

		void setFirstWord(std::string fw);
		std::string getFirstWord(void);
		
		void setSortString(std::string sortStr);
		std::string getSortString(void);
		
	private:	
		int m_songIndex;
		int m_songLan;
		int m_fileType;
		int m_subType;
		int m_favFlag;
		int m_progFlag;
		std::string	m_songName;
		std::string	m_singerName;
		std::string m_firstword;
		std::string m_sortString;
		
};
#endif
