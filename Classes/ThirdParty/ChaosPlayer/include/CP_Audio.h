#ifndef _CP_AUDIO_H_
#define _CP_AUDIO_H_

typedef void *AUDIO_HANDLE;
typedef void *AUDIO_IN_HANDLE;
typedef void *AUDIO_OUT_HANDLE;

//����1���û����
//����2�������ַ
//�ɹ����صõ�������ֽ�����ʧ�ܷ���-1
typedef long (*FuncAudioCallBack)(void *, void *);

typedef struct tagAUDIO_PARAM
{
	unsigned long		Channels;		//������
	unsigned long		SampleRate;		//������
	FuncAudioCallBack	CallBack;		//�ص�����ģʽ
	void				*User;			//�û����
	unsigned long		FrameCount;		//ÿ�λص�������������
}AUDIO_PARAM;

//����1����Ƶ���
//����2����Ƶ����
//�ɹ����ؾ����ʧ�ܷ���NULL
typedef AUDIO_IN_HANDLE(*FuncAudioSrcOpen)(AUDIO_HANDLE, AUDIO_PARAM *Param);

//��������Ƶ������
//�ɹ�����0��ʧ�ܷ���-1
typedef long (*FuncAudioSrcClose)(AUDIO_IN_HANDLE);

//����1����Ƶ������
//����2�������ַ
//����3�������������
//�ɹ����ض�ȡ����������ʧ�ܷ���-1
typedef long (*FuncAudioSrcRead)(AUDIO_IN_HANDLE, void *, unsigned long);

//����1����Ƶ���
//����2����Ƶ����
//�ɹ����ؾ����ʧ�ܷ���NULL
typedef AUDIO_OUT_HANDLE(*FuncAudioSinkOpen)(AUDIO_HANDLE, AUDIO_PARAM *Param);

//��������Ƶ������
//�ɹ�����0��ʧ�ܷ���-1
typedef long (*FuncAudioSinkClose)(AUDIO_OUT_HANDLE);

//����1����Ƶ������
//����2�������ַ
//����3��д���������
//�ɹ����ش������������ʧ�ܷ���-1
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

