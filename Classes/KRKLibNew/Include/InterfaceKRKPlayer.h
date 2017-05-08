#ifndef _INTERFACE_KRK_H
#define _INTERFACE_KRK_H
#include <string>
#include "CommonDefine.h"

class KRKListener
{    
 public:    
    KRKListener(){};    
    virtual ~KRKListener(){};    
    virtual void ActionPerformed(int ResultCode, std::string InfomationString);
};


enum KRKPlayerMsgCode
{
	FUNC_SUCCESS,
	ERROR_HANDLE_INIT,
	ERROR_SYSTEM_AUDIO_HANDLE_INIT,
	ERROR_HANDLE_NULL,
	ERROR_ISPLAYING,

	ERROR_MAX_NUM
};

enum KRKPlayerStatus
{
	PLAY_IDLE,
	PLAY_PREPARE,
	PLAY_PLAYING,
	PLAY_STOPPING,
	PLAY_STOPPED
};

class InterfaceKRKPlayer
{
public:
	virtual ~InterfaceKRKPlayer(){};

	virtual int SetDataSource(std::string _filePath) = 0;
	virtual int SetAudioStreamType() = 0;
	virtual int Draw() = 0;
	virtual int SetDisplay(void *LayerView) = 0;
	virtual int SetLooping(bool _loopStaus) = 0;
	virtual int SetVolume() = 0;

	virtual enum KRKPlayerStatus GetPlayStatus() = 0;
	virtual bool IsLooping() = 0;
	virtual bool IsPlaying() = 0;
	
	
	virtual int SetOnCompletionListener(KRKListener *_ls) = 0;
	//int SetOnPreparedListener(KRKListener *ls);
	virtual int SetOnErrorListener(KRKListener *_ls) = 0;

	virtual int GetDuration() = 0;
	virtual int GetCurrentPosition() = 0;

	virtual int	Prepare() = 0;
	//int	PrepareAsync();
	virtual int Start() = 0;
	virtual int Pause() = 0;
	virtual int Stop() = 0;
	virtual int StopWaitFinish() = 0;
	virtual int SeekNextSegment() = 0;

	virtual int Release() = 0;
	virtual int Reset() = 0;

	//设置开关Log, 0-关，1-开
	virtual void SetLog(int _logFlag) = 0;
	virtual int GetLog() = 0;

	virtual void HardwareWaveInit(std::string _wavePath) = 0;
	virtual void HardwareWaveDeInit() = 0;

	//歌词相关
	virtual void SetLyricFontStatus(LYRIC_FONT_RENDER_PROP _renderFontProp) = 0;

};

extern "C" void CreateKRKPlayer(InterfaceKRKPlayer *&_krkPlayer, std::string PlayerName);

extern "C" void DestroyKRKPlayer(InterfaceKRKPlayer *_krkPlayer);


#endif