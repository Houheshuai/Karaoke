//文件	Record.h
//描述	声明了录音公用接口
//作者	Chaos
//版本	V1.00
//日期	2011/1/10
#ifndef _RECORD_H_
#define _RECORD_H_

#define REC_LOGO				"Multak RecFile"
#define REC_LOGO_LEN			14
#define REC_MOBILE_LOGO		"MultakMobileRec"
#define REC_MOBILE_LOGO_LEN	15
#define REC_VER_1				"Ver00001"
#define REC_VER_2				"Ver00002"
#define REC_VER_3				"Ver00003"
#define REC_VER_4				"Ver00004"
#define REC_VER_5				"Ver00005"
#define REC_VER_LEN			8
#define REC_OFFSET				0x800

typedef struct tagREC_FILE_HEAD
{
	unsigned char	ID[16];				// "Multak RecFile"
	unsigned char	Version[8];			// "Verxxxxx"
	unsigned long	Language;			// Language
	unsigned long	SongNum;			// Song Number
	char			SongName[48];		// Song Name
	unsigned long	MusOffset;			// Mus data offset to file start
	unsigned long	MusSize;			// Mus data size in byte;
	unsigned long	RecordOffset;		// Record data offset to file start
	unsigned long	RecDataSize;		// Record data size in byte
	unsigned long	StartTime;			// start time of record in ticks
	unsigned long	EndTime;			// end time of record in ticks
	
	int				MidiKey;			// midi key volumn
	int				MidiTempo;			// midi speed
	int				MidiRhythm;			// midi melody volumn
	
	unsigned long	Rec_SF;				// 
	unsigned long	Rec_CR;				// 

	char			SerialNumber[16];	// Norflash serial number

	unsigned char	Score;				// Song Score
    unsigned char   KSCSongFlag;		// 
	unsigned char	SongType;			//
	
	unsigned char	Reserved[1];		//

	int				MidiVolume;			// 伴奏
	int				Mp3Volume;			// 人声

	char			FilePath[256];		// file path

	int				CodeType;			// 编码类型	此处同STREAM_TYPE
	int				Channels;			// 声道
	int				Rate;				// 采样率
	int				Latency;			// 延迟

	int				UploadStatus;
	int				Res[4];				// 保留位

	int				MediaType;			// 媒体类型
	int				StartTimeMS;		// 起始时间 MS
	int				EndTimeMS;			// 结束时间 MS

	int				MicGetVolResult;	// 人声能量
	int				MusicGetVolResult;	// 音乐能量

	int				TimeCount;			// 时间轴数量
	int				TimeListOffset;		// 时间轴偏移

	int				VocalCount;			// 人声数量
	int				TickCount;			// 人声数据数量
	int				KeyListOffset;		// 音调数据偏移
	int				VocalListOffset;	// 人声数据偏移

	int				TotalScore;
	int				MaleScore;
	int				FemaleScore;
}REC_FILE_HEAD;

#endif
