#ifndef _VIDEO_MANAGER_H
#define _VIDEO_MANAGER_H

#include "Renderer/Layer.h"
#include <string>
#include <vector>

#define VIDEO_CODE_SUCCESS	0
#define VIDEO_CODE_NOFILE	1
enum{
	UseFor_Background = 0,
	UseFor_MediaPlay,
};
enum{
	MediaFile_Type_None = -1,
	MediaFile_Type_Video,
	MediaFile_Type_Audio 
};
#define MEDIAFILE_FIRSTWORD_LENGTH  8
class MyDownItemInfo
{
public:
	unsigned char firstword[MEDIAFILE_FIRSTWORD_LENGTH];
	std::string name;
	std::string path;
	//int bookNumber;
	int sub_type;		//0 -- audio  1 -- video
	//int index;
	//int selected;

	bool operator==(const MyDownItemInfo& a)
	{
		return path==a.path;
	}
};

class VideoManager : public Layer
{
public:
	~VideoManager();
    static VideoManager * GetInstance(void);
	static void destroyInstance();

	void SetFileFilter(std::string _filter);
	void SetVideoFilter(std::string _filter);
	void SetAudioFilter(std::string _filter);
	int	GetVideoCount(int startidx = 0);//{return VideoList.size();};   // startidx : video index
	
	int GetVideoIndexByPosition(int position);
	std::string GetVideoNameByPosition(int position);
	int GetVideoTypeByPosition(int position);
	int GetVideoFirstWordByPosition(int position,unsigned char* buf);
/*
	std::string GetVideoNameByBookNumber(int number);
	int GetVideoTypeByBookNumber(int number);
	int GetVideoFirstWordByBookNumber(int number,unsigned char* buf);
*/
	int	GetBgvCount(){return BgvList.size();};   
	
	//void ClearVideoSubList();
	void ClearVideoList();
	void ClearBgvList();
	
	void SetOnStopListener(std::function<void(int _fileIndex, std::string _filePath)> _onStop);
	void SetOnErrorListener(std::function<void(int _fileIndex, std::string _filePath, int code)> _onError);

	void Play(int _fileIndex, int _volume = -1);
	void Play(std::string _filePath, int _volume = -1);
	void Stop();
	void Pause();
	void Resume();
	void ChangeAudioChannel();
	int	 GetAudioChannel();

	void SetKey(int key);

	void update(float dt);
	int ScanFolderRecrusive(std::string _folderPath, int depth = 0,int usetype=UseFor_Background);
protected:
    VideoManager();

private:
	bool init();
    static VideoManager * _instance;

	std::vector<MyDownItemInfo *> VideoList;
	std::vector<std::string> BgvList;
	
	int m_totalVideoCount;
	int m_totalBgvCount;

	std::string m_filter;
	std::string m_videofilter;
	std::string m_audiofilter;
	
	int	m_fileIndex;
	std::string m_filePath;
	int m_DLStartPos;
	MyDownItemInfo* m_downItemInfo;
	int m_stopManual;

	int	m_playerStatus;

	std::function<void(int _fileIndex, std::string _filePath)> onVideoStop;
	std::function<void(int _fileIndex, std::string _filePath, int code)> onVideoError;
	
	void string_uppercase(char *str);
	void string_lowcase(char *str);
	int Get_FirstWord_FullSpell(unsigned char* name, unsigned char* fp, int maxlen);
	void MediaFileMatch(std::string _folderPath,std::string _filename,int usetype);

	int ScanFolder(std::string _folderPath, int depth = 0,int usetype=UseFor_Background);
	MyDownItemInfo* GetVideoFileInfoByPosition(int position);

};


#endif
