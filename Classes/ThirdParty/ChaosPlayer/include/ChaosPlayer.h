//文件	ChaosPlayer.h
//描述	声明了播放器接口
//作者	Chaos
//版本	V1.00
//日期	2011/12/31
//使用方法
//	调用PlayerInit初始化
//	播放歌曲
//		调用PlayerMsg设置歌曲路径、歌曲类型、歌号（打包文件用）、录音路径
//		调用PlayerMsg播放歌曲
//	播放录音
//		调用PlayerMsg设置歌曲路径、歌曲类型、歌号（打包文件用）、录音路径
//		调用PlayerMsg播放录音
//	调用PlayerFinish反初始化

#ifndef _CHAOS_PLAYER_H_
#define _CHAOS_PLAYER_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define CHAOS_PLAYER_VERSION		"Ver 0.80"

	typedef int (*FuncCustomEncOpen)(void *, unsigned long, unsigned long, unsigned long);
	typedef void (*FuncCustomEncClose)(void *);
	typedef void (*FuncCustomEncProc)(void *, void *, unsigned long *, void *, unsigned long *);

	typedef struct tagPLAYER_CUSTOM_ENC_PARAM
	{
		void				*Handle;
		FuncCustomEncOpen 	Open;
		FuncCustomEncClose	Close;
		FuncCustomEncProc 	Proc;
	
		int					SampleRate;
		int					Channels;
		int					BitRate;
	}PLAYER_CUSTOM_ENC_PARAM;

	typedef enum tagPLAYER_RECORD_MODE
	{
		PLAYER_RECORD_MODE_VOCAL_ONLY,
		PLAYER_RECORD_MODE_VOCAL_ONLY_SP,
		PLAYER_RECORD_MODE_MIXED_SONG,
		PLAYER_RECORD_MODE_MIXED_SONG_PROPER,
		PLAYER_MIXED_RECORD_MODE_VOCAL_ONLY,
		PLAYER_RECORD_MODE_VOCAL_ONLY_WITHOUT_BUF,
	}PLAYER_RECORD_MODE;

	typedef enum tagPLAYER_REPLAY_MODE
	{
		PLAYER_REPLAY_MODE_VOCAL_ONLY,
		PLAYER_REPLAY_MODE_MIXED_SONG,
		PLAYER_MIXED_REPLAY_MODE_VOCAL_ONLY,
		PLAYER_REPLAY_MODE_VOCAL_ONLY_WITHOUT_BUF,
	}PLAYER_REPLAY_MODE;

	typedef enum tagPLAYER_VOCAL_STATUS
	{
		PLAYER_VOCAL_ON,
		PLAYER_VOCAL_OFF,
		PLAYER_VOCAL_AUTO,
		PLAYER_VOCAL_STEREO,
	}PLAYER_VOCAL_STATUS;

	typedef enum tagPLAYER_SOURCE_TYPE
	{
		PLAYER_SOURCE_TYPE_FILE,								//文件模式
		PLAYER_SOURCE_TYPE_URL,								//网络模式
		PLAYER_SOURCE_TYPE_MEM,								//内存模式
		PLAYER_SOURCE_TYPE_FUNC,								//函数模式
	}PLAYER_SOURCE_TYPE;

#define PLAYER_MUS_FILE_TYPE_RAW_FLAG			(1 << 0)
#define PLAYER_MUS_FILE_TYPE_TVS_FLAG			(1 << 1)	
#define PLAYER_MUS_FILE_TYPE_TVS_PACK_FLAG		(1 << 2)
#define PLAYER_MUS_FILE_TYPE_MUK_FLAG			(1 << 3)
#define PLAYER_MUS_FILE_TYPE_MUK_PACK_FLAG		(1 << 4)
#define PLAYER_MUS_FILE_TYPE_DAT_FLAG			(1 << 5)
#define PLAYER_MUS_FILE_TYPE_CID_FLAG			(1 << 6)
#define PLAYER_MUS_FILE_TYPE_NAF_FLAG			(1 << 7)
#define PLAYER_MUS_FILE_TYPE_OKF_FLAG			(1 << 8)
#define PLAYER_MUS_FILE_TYPE_HDD_FLAG			(1 << 9)

	typedef enum tagPLAYER_SONG_TYPE
	{
		PLAYER_SONG_TYPE_PCM,									//原始数据
		PLAYER_SONG_TYPE_WAVE,								//WAVE歌曲
		PLAYER_SONG_TYPE_MP3,									//MP3歌曲
		PLAYER_SONG_TYPE_AAC,									//AAC歌曲
		PLAYER_SONG_TYPE_MIDI,								//MIDI歌曲
		PLAYER_SONG_TYPE_MUS,									//MUS歌曲
		PLAYER_SONG_TYPE_OKF_MP3,							//OKF格式的MP3歌曲
	}PLAYER_SONG_TYPE;

	typedef enum tagPLAYER_REC_TYPE
	{
		PLAYER_REC_TYPE_REC_ADPCM,
		PLAYER_REC_TYPE_REC_SBC,
		PLAYER_REC_TYPE_MP3,
		PLAYER_REC_TYPE_REC_AAC,
		PLAYER_REC_TYPE_RECHEAD_AAC,
	}PLAYER_REC_TYPE;

	typedef enum tagPLAYER_PLAY_MODE
	{
		PLAYER_PLAY_MODE_TEST_LATENCY,						//延迟测试模式
		PLAYER_PLAY_MODE_SONG_SIMPLE,						//播放歌曲，无录音
		PLAYER_PLAY_MODE_SONG,								//播放歌曲
		PLAYER_PLAY_MODE_RECORD,								//回放歌曲
		PLAYER_PLAY_MODE_ENCODE_SIMPLE,						//歌曲编码模式
		PLAYER_PLAY_MODE_ENCODE,								//编码歌曲
		PLAYER_PLAY_MODE_SONG_MV_MEDIA, 					//MV播放模式 Media端
		PLAYER_PLAY_MODE_SONG_MV_KARAOKE,					//MV播放模式 Karaoke端
		PLAYER_PLAY_MODE_RECORD_MV_MEDIA,					//MV回放模式 Media端
		PLAYER_PLAY_MODE_RECORD_MV_KARAOKE, 				//MV回放模式 Karaoke端
	}PLAYER_PLAY_MODE;

	typedef enum tagPLAYER_PLAY_STATUS
	{
		PLAYER_PLAY_STATUS_PLAY,							//播放
		PLAYER_PLAY_STATUS_STOP,							//停止
	}PLAYER_PLAY_STATUS;

	typedef enum tagPLAYER_ENCODER_TYPE
	{
		PLAYER_ENCODER_TYPE_WAVE,							//WAVE封装，PCM编码
		PLAYER_ENCODER_TYPE_REC_ADPCM,						//REC封装，ADPCM编码
		PLAYER_ENCODER_TYPE_REC_SBC,							//REC封装，SBC编码
		PLAYER_ENCODER_TYPE_MP3_LAME,						//MP3封装，LAME编码
		PLAYER_ENCODER_TYPE_MP3_SHINE,						//MP3封装，SHINE编码
		PLAYER_ENCODER_TYPE_REC_CUSTOM,						//REC封装，外置编码
		PLAYER_ENCODER_TYPE_CUSTOM,
		PLAYER_ENCODER_TYPE_RECHEAD_CUSTOM,
	}PLAYER_ENCODER_TYPE;

	typedef enum tagPLAYER_RING_MODE
	{
		PLAYER_RING_MODE_OFF,
		PLAYER_RING_MODE_FIRST_HINT,							//第一个提倡符
		PLAYER_RING_MODE_FIRST_LYRIC,						//第一行歌词
	}PLAYER_RING_MODE;

	typedef enum tagPLAYER_PCM_CH_MODE
	{
		PLAYER_PCM_CH_MODE_NORMAL,
		PLAYER_PCM_CH_MODE_LEFT,
		PLAYER_PCM_CH_MODE_RIGHT,
	}PLAYER_PCM_CH_MODE;

	typedef enum tagPLAYER_MSG
	{
		PLAYER_MSG_NULL = 0,
		PLAYER_MSG_GET_VERSION,							//获取当前播放器版本号

		PLAYER_MSG_SET_FEEDBACK_MSG_FUNC = 1000,			//设置消息反馈函数			FuncPlayerMsg
		PLAYER_MSG_SET_FEEDBACK_PRINT_FUNC,				//设置打印反馈函数			FuncPlayerPrint
		PLAYER_MSG_SET_FEEDBACK_USER_DATA,				//设置用户反馈数据			void *

		PLAYER_MSG_SET_RECORD_MODE = 2000,				// 设置录音方式
		PLAYER_MSG_SET_REPLAY_MODE,						// 设置回放方式

		PLAYER_MSG_SET_PLAY_MODE,						//设置播放类型				PLAYER_PLAY_MODE
		PLAYER_MSG_SET_SEEK_TIME,						//设置跳转时间				单位毫秒

		PLAYER_MSG_SET_AUDIO_HANDLE,						//设置音频句柄

		PLAYER_MSG_SET_MIC_LATENCY,						//设置麦克风延迟			[10, 100]
		PLAYER_MSG_SET_MIC_CHANNELS,						//设置麦克风数量			[0, 2]		0表示由系统决定
		PLAYER_MSG_SET_MIC_SAMPLE_RATE,					//设置麦克风采样率			[0, 48000]	0表示由系统决定

		PLAYER_MSG_SET_AUDIO_IN_OPEN,					//设置音频输入打开函数
		PLAYER_MSG_SET_AUDIO_IN_CLOSE,					//设置音频输入关闭函数
		PLAYER_MSG_SET_AUDIO_IN_READ,					//设置音频输入读取函数

		PLAYER_MSG_SET_MIC1_VOLUME,						//设置1号麦克风音量		[0, 100]
		PLAYER_MSG_SET_MIC2_VOLUME,						//设置2号麦克风音量		[0, 100]
		PLAYER_MSG_SET_MIC3_VOLUME,						//设置无线1号麦克风音量	[0, 100]
		PLAYER_MSG_SET_MIC4_VOLUME,						//设置无线1号麦克风音量		[0, 100]

		PLAYER_MSG_SET_SPK_LATENCY,						//设置喇叭延迟
		PLAYER_MSG_SET_SPK_CHANNELS,						//设置喇叭数量				[0, 2]		0表示由系统决定
		PLAYER_MSG_SET_SPK_SAMPLE_RATE,					//设置喇叭采样率			[0, 48000]	0表示由系统决定

		PLAYER_MSG_SET_AUDIO_OUT_OPEN,					//设置音频输出打开函数
		PLAYER_MSG_SET_AUDIO_OUT_CLOSE,					//设置音频输出关闭函数
		PLAYER_MSG_SET_AUDIO_OUT_WRITE,					//设置音频输出写入函数

		PLAYER_MSG_SET_SPK_VOLUME,						//设置喇叭音量				[0, 100]

		PLAYER_MSG_SET_ECHO_VOLUME,						//设置混响音量				[0, 100]

		PLAYER_MSG_SET_LATENCY,							//设置回放延迟				[0, MAX)
		PLAYER_MSG_SET_OUTPUT_LATENCY,					//设置输出延迟				[0, MAX)

		PLAYER_MSG_SET_SONG_SOURCE_TYPE,					//设置歌曲来源				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_SONG_PATH,						//设置歌曲文件路径或网址	路径最多支持255字节
		PLAYER_MSG_SET_SONG_SIZE,						//设置歌曲大小
		PLAYER_MSG_SET_SONG_BUF_ADDR,					//设置歌曲缓存地址
		PLAYER_MSG_SET_SONG_BUF_SIZE,					//设置歌曲缓存大小
		PLAYER_MSG_SET_SONG_BUF_READ,					//设置歌曲缓存读指针
		PLAYER_MSG_SET_SONG_BUF_WRITE,					//设置歌曲缓存写指针
		PLAYER_MSG_SET_SONG_FUNC_DATA,					//设置歌曲句柄
		PLAYER_MSG_SET_SONG_FUNC_OPEN,					//设置歌曲打开函数
		PLAYER_MSG_SET_SONG_FUNC_CLOSE,					//设置歌曲关闭函数
		PLAYER_MSG_SET_SONG_FUNC_READ,					//设置歌曲读取函数
		PLAYER_MSG_SET_SONG_SAVE_PATH,					//设置歌曲保存路径，用于在线播放的本地备份，路径最多支持255字节

		PLAYER_MSG_SET_MUS_REVERB_ENABLE,				//设置音乐混响开关			0关闭，1开启
		PLAYER_MSG_SET_SP_SOUND_ENABLE,					//设置特殊音效使能
		PLAYER_MSG_SET_SP_SOUND_MUSIC_VOL,				//设置特殊音效MUSIC音量
		PLAYER_MSG_SET_SP_SOUND_VOCAL_VOL,				//设置特殊音效VOCAL音量
		PLAYER_MSG_SET_SP_SOUND_REV_VOL,					//设置特殊音效REV音量
		PLAYER_MSG_SET_SP_SOUND_KTV_VOL,					//设置特殊音效KTV音量

		PLAYER_MSG_SET_SONG_LRC_PATH,					//设置音乐LRC路径			路径最多支持255字节
		PLAYER_MSG_SET_SONG_CDG_PATH,					//设置音乐CDG路径			路径最多支持255字节

		PLAYER_MSG_SET_SONG_TYPE,						//设置歌曲类型				PLAYER_SONG_TYPE
		PLAYER_MSG_SET_MUSIC_VOLUME,						//设置音乐音量				[0, 100]
		PLAYER_MSG_SET_PCM_CHANNELS,						//设置PCM歌曲声道
		PLAYER_MSG_SET_PCM_SAMPLE_RATE,					//设置PCM歌曲采样率
		PLAYER_MSG_SET_PCM_CH_MODE,						//设置PCM歌曲声道
		PLAYER_MSG_SET_MUS_FILE_TYPE_FLAG,				//设置MUS文件类型标志
		PLAYER_MSG_SET_MUS_SONG_NUMBER,					//设置MUS歌曲歌号			当歌曲类型为TVS打包时必须设置此项
		PLAYER_MSG_SET_MUS_DATA_OFFSET,					//设置数据偏移				当歌曲类型为MUK打包时必须设置此项
		PLAYER_MSG_SET_MUS_DATA_LENGTH,					//设置数据大小				当歌曲类型为MUK打包时必须设置此项
		PLAYER_MSG_SET_MUS_SERIAL_NUMBER,				//设置序列号					当歌曲类型为CID时必须设置此项
		PLAYER_MSG_SET_MUS_PRIVATE_KEY,					//设置私人密钥				当歌曲类型为CID时必须设置此项
		PLAYER_MSG_SET_MUS_MIDI_VOLUME,					//设置MUS歌曲MIDI主音量		[0, 100]
		PLAYER_MSG_SET_MUS_MELODY_VOLUME,				//设置MUS歌曲旋律音量		[0, 100]
		PLAYER_MSG_SET_MUS_MEDIA_VOLUME,					//设置MUS歌曲人声音量		[0, 100]
		PLAYER_MSG_SET_MUSIC_KEY,						//设置MUS歌曲音调			[-12, 12]
		PLAYER_MSG_SET_MUSIC_TEMPO,						//设置MUS歌曲速度			[800, 1200]
		PLAYER_MSG_SET_MUS_VOCAL_FADE,					//设置MUS歌曲人声状态		PLAYER_VOCAL_STATUS
		PLAYER_MSG_SET_MUS_IFUN_CHANNELS,				//设置MUS歌曲IFUN声道数量	{1, 2}
		PLAYER_MSG_SET_MUS_IFUN_LEVEL,					//设置MUS歌曲IFUN难度		IFUN_LEVEL
		PLAYER_MSG_SET_MUS_IFUN_EASY_LIMIT,				//设置MUS歌曲IFUN简单模式音分判断门限
		PLAYER_MSG_SET_MUS_IFUN_NORMAL_LIMIT,			//设置MUS歌曲IFUN普通模式音分判断门限
		PLAYER_MSG_SET_MUS_IFUN_HARD_LIMIT,				//设置MUS歌曲IFUN困难模式音分判断门限
		PLAYER_MSG_SET_MUS_AUTO_SEEK,					//设置MUS歌曲自动跳转		NULL，自动跳转到下一段开始
		PLAYER_MSG_SET_MIDI_DATABASE_PARAM,
		PLAYER_MSG_SET_SAMPLE_CHECK_VAL,					//设置样本检查门限值		[0, 32768]
		PLAYER_MSG_SET_SAMPLE_CHECK_NUM,					//设置样本检查数			<= 1152
		PLAYER_MSG_SET_MUTE_2_VOCAL_LIMIT,				//设置静音至人声缓冲		MS
		PLAYER_MSG_SET_VOCAL_2_MUTE_LIMIT,				//设置人声至静音缓冲		MS
		PLAYER_MSG_SET_MIDI_MIDI_DATA_BUFFER,			//设置MIDI歌曲				MidiDataBuffer
		PLAYER_MSG_SET_MIDI_MIDI_DATA_SIZE,				//设置MIDI歌曲				MidiDataSize
		PLAYER_MSG_SET_MIDI_ORG_MIDI_TEMPO,				//设置MIDI歌曲				ORGMidiTempo
		PLAYER_MSG_SET_MIDI_STAFF_TOTAL_TICK,			//设置MIDI歌曲				StaffTotalTick
		PLAYER_MSG_SET_MV_FLAG,							//设置MV标志
		PLAYER_MSG_SET_MUSIC_POINT_A,					//设置A点
		PLAYER_MSG_SET_MUSIC_POINT_B,					//设置B点
		PLAYER_MSG_SET_MUSIC_AB_MODE,					//设置AB点模式

		PLAYER_MSG_SET_RECORD_SOURCE_TYPE,				//设置录音来源				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD_PATH,						//设置录音路径				路径最多支持255字节
		PLAYER_MSG_SET_RECORD_SIZE,						//设置录音大小
		PLAYER_MSG_SET_RECORD_BUF_ADDR,					//设置录音缓存地址
		PLAYER_MSG_SET_RECORD_BUF_SIZE,					//设置录音缓存大小
		PLAYER_MSG_SET_RECORD_BUF_READ,					//设置录音缓存读指针
		PLAYER_MSG_SET_RECORD_BUF_WRITE,					//设置录音缓存写指针
		PLAYER_MSG_SET_RECORD_FULL_FLAG,					//录音完整播放标志
		PLAYER_MSG_SET_RECORD_TYPE,						//设置录音类型
		PLAYER_MSG_SET_RECORD_VOLUME,					//设置录音音量				[0, 100]

		PLAYER_MSG_SET_RECORD2_SOURCE_TYPE,				//设置混合模式录音来源				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD2_PATH,						//设置混合模式录音路径				路径最多支持255字节
		PLAYER_MSG_SET_RECORD2_SIZE,						//设置混合模式录音大小
		PLAYER_MSG_SET_RECORD2_BUF_ADDR,					//设置混合模式录音缓存地址
		PLAYER_MSG_SET_RECORD2_BUF_SIZE,					//设置混合模式录音缓存大小
		PLAYER_MSG_SET_RECORD2_BUF_READ,					//设置混合模式录音缓存读指针
		PLAYER_MSG_SET_RECORD2_BUF_WRITE,				//设置混合模式录音缓存写指针
		PLAYER_MSG_SET_RECORD2_TYPE,						//设置混合模式录音类型
		PLAYER_MSG_SET_RECORD2_VOLUME,					//设置混合模式录音音量				[0, 100]

		PLAYER_MSG_SET_RECORD_FLAG,						//设置录音标志				0关闭录音，1开启录音
		PLAYER_MSG_SET_ENCODE_PATH,						//设置编码输出路径
		PLAYER_MSG_SET_ENCODER,							//设置编码器					PLAYER_ENCODER_TYPE
		PLAYER_MSG_SET_ENCODER_BITRATE,						//设置MP3码流率				{32, 48, 64, 96, 128, 192, 256, 320}
		PLAYER_MSG_SET_SONG_NAME,						//设置歌曲标题				索引歌名，最多48字节，录音用，编码用
		PLAYER_MSG_SET_SINGER_NAME,						//设置演唱者					最多48字节，编码用
		PLAYER_MSG_SET_ALBUM_NAME,						//设置专辑					最多48字节，编码用
		PLAYER_MSG_SET_DUET_DATA,						//设置DUET数据地址
		PLAYER_MSG_SET_DUET_SIZE,						//设置DUET数据大小
		PLAYER_MSG_SET_ENCODER_RING_MODE,				//设置编码器为彩铃模式	PLAYER_RING_MODE

		PLAYER_MSG_SET_EQ_100HZ_VOL,						//设置EQ低频增益
		PLAYER_MSG_SET_EQ_1KHZ_VOL,						//设置EQ中频增益
		PLAYER_MSG_SET_EQ_5KHZ_VOL,						//设置EQ高频增益
		PLAYER_MSG_SET_EQ_QFACTOR,						//设置EQ

		PLAYER_MSG_SET_MUS_FORCE_KSC,					//设置MUS文件强制KSC标志
		PLAYER_MSG_SET_ECHO_DELAY,						//设置混响延迟
		PLAYER_MSG_SET_LATENCY_DATA_PATH,				//设置延迟测试数据路径
		PLAYER_MSG_SET_SP_SOUND_AGC_ON,					//开关SPSOUNDPROC的AGC效果
		PLAYER_MSG_SET_SP_SOUND_COMPRESS_ON,			//开关SPSOUNDPROC的COMPRESS效果
		PLAYER_MSG_SET_MUS_MIDI_ENABLE,					//开关MIDI
		PLAYER_MSG_SET_MUS_TVS_PACK_FLAG,				//TVS歌曲打包标志
		PLAYER_MSG_SET_MUS_X_KEY,
		PLAYER_MSG_SET_MUS_MAX_ENCODE_BYTES,

		PLAYER_MSG_SET_AGC_ENABLE,
		PLAYER_MSG_SET_AGC_GAIN,
		PLAYER_MSG_SET_AGC_TARGET,

		PLAYER_MSG_SET_MUTE,

		PLAYER_MSG_SET_CUSTOM_ENC_PARAM,

		PLAYER_MSG_SET_ENCODE_SINK_TYPE,
		PLAYER_MSG_SET_ENCODE_FUNC_DATA,
		PLAYER_MSG_SET_ENCODE_FUNC_OPEN,
		PLAYER_MSG_SET_ENCODE_FUNC_CLOSE,
		PLAYER_MSG_SET_ENCODE_FUNC_WRITE,

		PLAYER_MSG_GET_TIME_INFO_SIZE,
		PLAYER_MSG_GET_TIME_INFO_DATA,

		PLAYER_MSG_SET_EXT_MIDI_FLAG,					//外置MIDI标志

		PLAYER_MSG_SET_PREPARE_MODE,

		PLAYER_MSG_SET_SONG_BUF_TIME,

		PLAYER_MSG_SET_SP_FAST_MODE,

		PLAYER_MSG_SET_OKF_PRODUCTID,				//设置OKF客户编码					当歌曲类型为OKF时必须设置此项

		PLAYER_MSG_SET_NOTE_MIC_HANDLE,

		PLAYER_MSG_SET_NOTE_MIC_LATENCY,						//设置麦克风延迟			[10, 100]
		PLAYER_MSG_SET_NOTE_MIC_CHANNELS,						//设置麦克风数量			[0, 2]		0表示由系统决定
		PLAYER_MSG_SET_NOTE_MIC_SAMPLE_RATE,					//设置麦克风采样率			[0, 48000]	0表示由系统决定

		PLAYER_MSG_SET_NOTE_AUDIO_IN_OPEN,					//设置音频输入打开函数
		PLAYER_MSG_SET_NOTE_AUDIO_IN_CLOSE,					//设置音频输入关闭函数
		PLAYER_MSG_SET_NOTE_AUDIO_IN_READ,					//设置音频输入读取函数

		PLAYER_MSG_SET_RECORD_KEY,

		PLAYER_MSG_SET_RESAMPLE_QT,

		PLAYER_MSG_SET_ENCODE_DATA_PATH,					//设置编码输出路径
		PLAYER_MSG_SET_ENCODE_DATA_SINK_TYPE,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_DATA,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_OPEN,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_CLOSE,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_WRITE,

		PLAYER_MSG_SET_RECORD_DATA_SOURCE_TYPE,			//设置录音数据来源				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD_DATA_PATH,					//设置录音数据路径				路径最多支持255字节
		PLAYER_MSG_SET_RECORD_DATA_SIZE,					//设置录音数据大小
		PLAYER_MSG_SET_RECORD_DATA_BUF_ADDR,			//设置录音数据缓存地址
		PLAYER_MSG_SET_RECORD_DATA_BUF_SIZE,			//设置录音数据缓存大小
		PLAYER_MSG_SET_RECORD_DATA_BUF_READ,			//设置录音数据缓存读指针
		PLAYER_MSG_SET_RECORD_DATA_BUF_WRITE,			//设置录音数据缓存写指针

		PLAYER_MSG_SET_SP_RECORD_FLAG,					//额外的录音来源
		PLAYER_MSG_SET_SP_RECORD_HANDLE,
		PLAYER_MSG_SET_SP_RECORD_CHANNELS,
		PLAYER_MSG_SET_SP_RECORD_SAMPLE_RATE,
		PLAYER_MSG_SET_SP_RECORD_OPEN,
		PLAYER_MSG_SET_SP_RECORD_CLOSE,
		PLAYER_MSG_SET_SP_RECORD_READ,

		PLAYER_MSG_SET_LYRIC_BIN_PATH,					//设置二进制歌词文件路径			路径最多支持255字节

		PLAYER_MSG_GET_PLAY_STATUS = 3000,				//获取当前播放状态			PLAYER_PLAY_STATUS
		PLAYER_MSG_GET_LYRIC_INFO,						//获取当前歌词信息			LYRIC_SHOW_INFO
		PLAYER_MSG_GET_IFUN_INFO,						//获取当前iFun信息			IFUN_DISPLAY_INFO
		PLAYER_MSG_GET_ENCODE_PERCENT,					//获取当前编码进度			百分制
		PLAYER_MSG_GET_BUFFERING_FLAG,					//获取当前缓冲标志			0表示无需缓冲 1表示缓冲中
		PLAYER_MSG_GET_TOTAL_TIME,						//获取播放总时间
		PLAYER_MSG_GET_PLAY_TIME,						//获取当前播放时间
		PLAYER_MSG_GET_SONG_INFO,						//获取歌词中的歌曲信息		LYRIC_SHOW_INFO_SONG_INFO
		PLAYER_MSG_GET_LYRIC_INFO_BY_LINE_NUMBER,		//通过行数来获取歌词信息	LYRIC_SHOW_INFO_LYRIC_INFO	返回0表示成功 返回-1表示未准备好 返回-2表示超过拥有的行数
		PLAYER_MSG_GET_LYRIC_INFO_WHEN_AUTO_SEEK,		//获取歌词中的歌曲信息		LYRIC_SHOW_INFO_SONG_INFO

		PLAYER_MSG_GET_MIC_BUF_ADDR,						//获取麦克风输出缓存地址
		PLAYER_MSG_GET_MIC_BUF_SIZE,						//获取麦克风输出缓存大小
		PLAYER_MSG_GET_MIC_BUF_READ,						//获取麦克风输出缓存读指针
		PLAYER_MSG_GET_MIC_BUF_WRITE,					//获取麦克风输出缓存写指针

		PLAYER_MSG_GET_MUTE_FLAG,						//获取当前静音状态

		PLAYER_MSG_CMD_PLAY = 4000,						//开始播放
		PLAYER_MSG_CMD_STOP,								//停止播放
		PLAYER_MSG_CMD_PAUSE,								//暂停播放
		PLAYER_MSG_CMD_RESUME,							//恢复播放
		PLAYER_MSG_CMD_RECORD,							//开始录音，此命令只能在非STOP状态发送
		PLAYER_MSG_CMD_RECORD_OFF,						//关闭录音
		PLAYER_MSG_CMD_START,
		PLAYER_MSG_CMD_PLAY_SYNC,
		PLAYER_MSG_CMD_STOP_SYNC,

		PLAYER_MSG_FB_CMD_PLAY = 5000,					//消息反馈							开始播放
		PLAYER_MSG_FB_CMD_STOP,							//消息反馈							停止播放
		PLAYER_MSG_FB_CMD_STOP_CAUSED_BY_ERROR,			//消息反馈							因出错停止播放
		PLAYER_MSG_FB_CMD_PAUSE,							//消息反馈							暂停播放
		PLAYER_MSG_FB_CMD_RESUME,						//消息反馈							恢复播放
		PLAYER_MSG_FB_CMD_RECORD_FAILED,					//消息反馈							录音失败
		PLAYER_MSG_FB_SET_MIC1_VOLUME,					//设置1号麦克风音量消息反馈			[0, 100]
		PLAYER_MSG_FB_SET_MIC2_VOLUME,					//设置2号麦克风音量消息反馈			[0, 100]
		PLAYER_MSG_FB_SET_MIC3_VOLUME,					//设置3号麦克风音量消息反馈 		[0, 100]
		PLAYER_MSG_FB_SET_MIC4_VOLUME,					//设置4号麦克风音量消息反馈 		[0, 100]
		PLAYER_MSG_FB_SET_SPK_VOLUME,					//设置喇叭音量消息反馈				[0, 100]
		PLAYER_MSG_FB_SET_ECHO_VOLUME,					//设置混响音量消息反馈				[0, 100]
		PLAYER_MSG_FB_SET_MUSIC_VOLUME,					//设置音乐音量消息反馈				[0, 100]
		PLAYER_MSG_FB_SET_MUS_MIDI_VOLUME,				//设置MUS歌曲主音量消息反馈 	[0, 100]
		PLAYER_MSG_FB_SET_MUS_MELODY_VOLUME,			//设置MUS歌曲旋律音量消息反馈		[0, 100]
		PLAYER_MSG_FB_SET_MUS_VOCAL_VOLUME,				//设置MUS歌曲人声音量消息反馈		[0, 100]
		PLAYER_MSG_FB_SET_MUS_KEY,						//设置MUS歌曲音调消息反馈			[0, 100]
		PLAYER_MSG_FB_SET_MUS_TEMPO,						//设置MUS歌曲速度消息反馈			[800, 1200]
		PLAYER_MSG_FB_SET_MUS_VOCAL_FADE,				//设置MUS歌曲人声状态消息反馈		PLAYER_VOCAL_STATUS	
		PLAYER_MSG_FB_SET_RECORD_VOLUME,					//设置录音音量消息反馈				[0, 100]
		PLAYER_MSG_FB_GET_LATENCY,						//音频设备延迟消息反馈
		PLAYER_MSG_FB_SET_MIDI_USER_DATA,				//消息反馈							设置MIDI用户数据
		PLAYER_MSG_FB_SET_VOCAL_DATA,					//消息反馈							设置人声数据
		PLAYER_MSG_FB_SET_VOCAL_DATA_NULL,				//消息反馈							设置人声数据为空
		PLAYER_MSG_FB_NOTIFICATION_SAVE_FILE_SUCCESS,	//在线文件保存成功
		PLAYER_MSG_FB_NOTIFICATION_SAVE_FILE_FAILED,	//在线文件保存失败
		PLAYER_MSG_FB_NOTIFICATION_REC_FILE_ERROR,		//录音文件错误
		PLAYER_MSG_FB_AUTO_SEEK_LYRIC_INFO,				//自动跳转歌词信息
		PLAYER_MSG_FB_GET_TOTAL_TIME,					//获取音频总时间
		PLAYER_MSG_FB_GET_LYRIC_END_TIME,				//获取歌词结束时间
		PLAYER_MSG_FB_GET_TOTAL_TIME_BY_LYRIC,			//从歌词中获取音频总时间
		PLAYER_MSG_FB_SET_EQ_100HZ_VOLUME,				//设置EQ的低频增益
		PLAYER_MSG_FB_SET_EQ_1KHZ_VOLUME,				//设置EQ的中频增益
		PLAYER_MSG_FB_SET_EQ_5KHZ_VOLUME,				//设置EQ的高频增益
		PLAYER_MSG_FB_SET_EQ_QFACTOR,					//设置EQ
		PLAYER_MSG_FB_SET_ECHO_DELAY,					//设置混响延迟
		PLAYER_MSG_FB_SET_REC_HEAD,						//反馈录音文件头
		PLAYER_MSG_FB_EXT_MIDI_SET_SYNC,					//外置MIDI时间同步
		PLAYER_MSG_FB_EXT_MUS_SET_QJ_ID,
		PLAYER_MSG_FB_CMD_RECORD_OFF,					//录音关闭
		PLAYER_MSG_FB_AUTO_SEEK_LYRIC_INFO_FAILED,
		PLAYER_MSG_FB_OKF_PRODUCTOR_ID,
		PLAYER_MSG_FB_MUTE_PERCENT,
		PLAYER_MSG_FB_LYRIC_AFTER_LOAD,
		PLAYER_MSG_FB_LYRIC_BEFORE_UNLOAD,
		PLAYER_MSG_FB_SET_RECORD_KEY,
	}PLAYER_MSG;

	//反馈消息函数
	//输入	PLAYER_MSG	消息
	//		void *		内容
	//		void *		用户数据
	//返回	0表示成功
	//		-1表示失败
	typedef int (*FuncPlayerMsg)(PLAYER_MSG, void *, void *);

	//反馈打印函数
	//输入	char *		内容
	//		void *		用户数据
	//返回	无
	typedef void (*FuncPlayerPrintf)(char *, void *);

	//数据源打开函数
	//输入	void *	句柄
	//返回	0		表示成功
	//			-1		表示失败
	typedef int (*FuncDataSrcOpen)(void *);

	//数据源关闭函数
	//输入	void *	句柄
	typedef void (*FuncDataSrcClose)(void *);

	//数据源读取函数
	//输入	void *	句柄
	//			void *	地址
	//			int		偏移
	//			int		大小
	//返回	int		实际读取的大小,-1表示出错或结束?
	typedef int (*FuncDataSrcRead)(void *, void *, int, int);

	//数据源写入函数
	//输入	void *	句柄
	//			void *	地址
	//			int		偏移
	//			int		大小
	//返回	int		实际写入的大小
	typedef int (*FuncDataSrcWrite)(void *, void *, int, int);

	//函数	PlayerMsg
	//功能	给播放器模块发消息
	//输入	Msg			消息
	//		Data		内容
	//返回	成功返回0，失败返回-1
	int PlayerMsg (void *Handle, PLAYER_MSG Msg, void *Data);

	//函数	PlayerInit
	//功能	初始化播放器模块
	//返回	成功返回0，失败返回-1
	void *PlayerInit (int iFunLyricFlag);

	//函数	PlayerFinish
	//功能	反初始化播放器模块
	//返回	成功返回0，失败返回-1
	int PlayerFinish (void *Handle);

#if defined(__cplusplus)
}
#endif

#endif

