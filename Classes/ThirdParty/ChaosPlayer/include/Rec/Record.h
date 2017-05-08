//�ļ�	Record.h
//����	������¼�����ýӿ�
//����	Chaos
//�汾	V1.00
//����	2011/1/10
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

	int				MidiVolume;			// ����
	int				Mp3Volume;			// ����

	char			FilePath[256];		// file path

	int				CodeType;			// ��������	�˴�ͬSTREAM_TYPE
	int				Channels;			// ����
	int				Rate;				// ������
	int				Latency;			// �ӳ�

	int				UploadStatus;
	int				Res[4];				// ����λ

	int				MediaType;			// ý������
	int				StartTimeMS;		// ��ʼʱ�� MS
	int				EndTimeMS;			// ����ʱ�� MS

	int				MicGetVolResult;	// ��������
	int				MusicGetVolResult;	// ��������

	int				TimeCount;			// ʱ��������
	int				TimeListOffset;		// ʱ����ƫ��

	int				VocalCount;			// ��������
	int				TickCount;			// ������������
	int				KeyListOffset;		// ��������ƫ��
	int				VocalListOffset;	// ��������ƫ��

	int				TotalScore;
	int				MaleScore;
	int				FemaleScore;
}REC_FILE_HEAD;

#endif
