#pragma once
#include <string>
#include "InterfaceKRKPlayer.h"
#include "InterfaceFontManager.h"
#include "KaraokePaintingBrush.h"

#include "Renderer/Layer.h"

class KRKPlayer:public InterfaceKRKPlayer
{
public:
	KRKPlayer(std::string _playerName);
	~KRKPlayer();

	int SetDataSource(std::string _filePath);
	int SetAudioStreamType();
	
	int SetLooping(bool _loopStaus);
	int SetVolume();

	enum KRKPlayerStatus GetPlayStatus();
	bool IsLooping();
	bool IsPlaying();
	
	int SetOnCompletionListener(KRKListener *_ls);
	//int SetOnPreparedListener(KRKListener *ls);
	int SetOnErrorListener(KRKListener *_ls);

	int GetDuration();
	int GetCurrentPosition();

	int	Prepare();
	//int	PrepareAsync();
	int Start();
	int Pause();
	int Stop();
	int StopWaitFinish();
	int SeekNextSegment();

	int Release();
	int Reset();

	void HardwareWaveInit(std::string _wavePath);
	void HardwareWaveDeInit();

	void*		PlayerHandle;
	std::string DataSourcePath;
	std::string WaveTablePath;

	int			AudioInRate;
	int			AudioInLatency;
	int			AudioInChannel;
	int			AudioOutRate;
	int			AudioOutLatency;
	int			AudioOutChannel;

	bool		PlayStatusLoop;
	bool		IsPlayingNow;
	KRKPlayerStatus		PlayStatus;

	KRKListener *ErrorListener;
	KRKListener *CompleteListener;

	int			LastLyricErrCode;

	void		*AudioHandle;
	

	//////////////////////////////////////////////////////
	//���ÿ���Log, 0-�أ�1-��
	void SetLog(int _logFlag);
	//��ȡLog��״̬
	int GetLog();
	int			LogFlag;
	std::string PlayerName;
	static	int ReferenceTimes;
	//////////////////////////////////////////////////////////

	void SetLyricFontStatus(LYRIC_FONT_RENDER_PROP _renderFontProp);
	LYRIC_FONT_RENDER_PROP FontRenderPropNow;
		
	int Draw();

	int SetDisplay(void *LayerView);

	//���ø����Ⱦ
	//����ifun��Ⱦ
	//����ͼ����Ⱦ

	//���ø��Ч��
	//����ifunЧ��
	//����ͼ��Ч��
	/////////////////////////////////////////////////////
	KaraokePaintingBrush *LyricBrushNow;

	Layer		*KaraokeSurface;
};