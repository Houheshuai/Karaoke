#ifndef _CP_AUDIO_H_
#define _CP_AUDIO_H_

typedef void *AUDIO_HANDLE;
typedef void *AUDIO_IN_HANDLE;
typedef void *AUDIO_OUT_HANDLE;

//参数1，用户句柄
//参数2，缓冲地址
//成功返回得到或处理的字节数，失败返回-1
typedef long (*FuncAudioCallBack)(void *, void *);

typedef struct tagAUDIO_PARAM
{
	unsigned long		Channels;		//声道数
	unsigned long		SampleRate;		//采样率
	FuncAudioCallBack	CallBack;		//回调函数模式
	void				*User;			//用户句柄
	unsigned long		FrameCount;		//每次回调函数的样本数
}AUDIO_PARAM;

//参数1，音频句柄
//参数2，音频参数
//成功返回句柄，失败返回NULL
typedef AUDIO_IN_HANDLE(*FuncAudioSrcOpen)(AUDIO_HANDLE, AUDIO_PARAM *Param);

//参数，音频输入句柄
//成功返回0，失败返回-1
typedef long (*FuncAudioSrcClose)(AUDIO_IN_HANDLE);

//参数1，音频输入句柄
//参数2，缓冲地址
//参数3，需求的数据量
//成功返回读取的数据量，失败返回-1
typedef long (*FuncAudioSrcRead)(AUDIO_IN_HANDLE, void *, unsigned long);

//参数1，音频句柄
//参数2，音频参数
//成功返回句柄，失败返回NULL
typedef AUDIO_OUT_HANDLE(*FuncAudioSinkOpen)(AUDIO_HANDLE, AUDIO_PARAM *Param);

//参数，音频输出句柄
//成功返回0，失败返回-1
typedef long (*FuncAudioSinkClose)(AUDIO_OUT_HANDLE);

//参数1，音频输出句柄
//参数2，缓冲地址
//参数3，写入的数据量
//成功返回处理的数据量，失败返回-1
typedef long (*FuncAudioSinkWrite)(AUDIO_OUT_HANDLE, void *, unsigned long);

typedef enum tagCP_AUDIO_CMD
{
	CP_AUDIO_CMD_SET_MIC1_VOL,
	CP_AUDIO_CMD_SET_MIC2_VOL,
	CP_AUDIO_CMD_SET_WMIC1_VOL,
	CP_AUDIO_CMD_SET_WMIC2_VOL,
	CP_AUDIO_CMD_SET_ECHO_VOL,
	CP_AUDIO_CMD_SET_EXT_MIDI_SYNC,
	CP_AUDIO_CMD_SET_EXT_MIDI_SYNC_EN,

	CP_AUDIO_CMD_GET_SPI_STATUS,

	CP_AUDIO_CMD_WIRELESS_OPEN_DEVICE,
	CP_AUDIO_CMD_WIRELESS_CLOSE_DEVICE,
	CP_AUDIO_CMD_WIRELESS_START_PAIR,
	CP_AUDIO_CMD_WIRELESS_GET_PAIR_STATE,
	CP_AUDIO_CMD_WIRELESS_STOP_PAIR,
	CP_AUDIO_CMD_WIRELESS_SET_WORKMODE,
	CP_AUDIO_CMD_WIRELESS_SET_SAMPLERATE,
	
	CP_AUDIO_CMD_SET_,

}CP_AUDIO_CMD;

typedef int (*FuncAudio_Set) (AUDIO_HANDLE Handle, int Cmd, int Data);

typedef AUDIO_HANDLE (*FuncAudio_Init) (int samplerate);

typedef int (*FuncAudio_Finish) (AUDIO_HANDLE Handle);

typedef struct tagAudioIFs
{
	FuncAudioSrcOpen srcopen;
	FuncAudioSrcClose srcclose;
	FuncAudioSrcRead  srcread;
	FuncAudioSinkOpen sinkopen;
	FuncAudioSinkClose sinkclose;
	FuncAudioSinkWrite sinkwrite;

	FuncAudio_Init         init;
	FuncAudio_Finish     finish;
	
	FuncAudio_Set			setAudio;
} CP_AudioIFs;

#endif

