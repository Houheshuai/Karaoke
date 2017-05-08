#ifndef _RECSONGPARAM_H
#define _RECSONGPARAM_H

#include <string>

#define DEFAULT_RECORDSONG_HEAD  	0x08000000

//#ifdef _WIN32
#define RECORD_FILE_SUFFIX     ".MP3"
//#else
//#define RECORD_FILE_SUFFIX     ".AAC"
//#endif

#define RECSONG_TEMP_FILE_NAME 	"tmpRec"

class RecSongParam
{
	public:
		
		RecSongParam();
		~RecSongParam();
		void reset(void);
		
		/*
		void setSongIndex(int songidx);
		int getSongIndex(void);		
		void setInsertId(int insertid);
		int getInsertId(void);
		void setRecIndex(int recidx);
		int getRecIndex(void);
		void setScore(int score);
		int getScore(void);
		void setStorage(int storage);
		int getStorage(void);
		*/
		
	//private:	
		int m_songIndex;  			/*book song number*/
		int m_insertId;	
		int m_recIndex;				/* record song id */
		int m_score;				/* singer score */
		int m_storage;				/* 0-not in default storage device, 1-in default storage device */
					
};
#endif
