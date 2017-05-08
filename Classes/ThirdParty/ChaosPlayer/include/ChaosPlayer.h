//�ļ�	ChaosPlayer.h
//����	�����˲������ӿ�
//����	Chaos
//�汾	V1.00
//����	2011/12/31
//ʹ�÷���
//	����PlayerInit��ʼ��
//	���Ÿ���
//		����PlayerMsg���ø���·�����������͡���ţ�����ļ��ã���¼��·��
//		����PlayerMsg���Ÿ���
//	����¼��
//		����PlayerMsg���ø���·�����������͡���ţ�����ļ��ã���¼��·��
//		����PlayerMsg����¼��
//	����PlayerFinish����ʼ��

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
		PLAYER_SOURCE_TYPE_FILE,								//�ļ�ģʽ
		PLAYER_SOURCE_TYPE_URL,								//����ģʽ
		PLAYER_SOURCE_TYPE_MEM,								//�ڴ�ģʽ
		PLAYER_SOURCE_TYPE_FUNC,								//����ģʽ
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
		PLAYER_SONG_TYPE_PCM,									//ԭʼ����
		PLAYER_SONG_TYPE_WAVE,								//WAVE����
		PLAYER_SONG_TYPE_MP3,									//MP3����
		PLAYER_SONG_TYPE_AAC,									//AAC����
		PLAYER_SONG_TYPE_MIDI,								//MIDI����
		PLAYER_SONG_TYPE_MUS,									//MUS����
		PLAYER_SONG_TYPE_OKF_MP3,							//OKF��ʽ��MP3����
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
		PLAYER_PLAY_MODE_TEST_LATENCY,						//�ӳٲ���ģʽ
		PLAYER_PLAY_MODE_SONG_SIMPLE,						//���Ÿ�������¼��
		PLAYER_PLAY_MODE_SONG,								//���Ÿ���
		PLAYER_PLAY_MODE_RECORD,								//�طŸ���
		PLAYER_PLAY_MODE_ENCODE_SIMPLE,						//��������ģʽ
		PLAYER_PLAY_MODE_ENCODE,								//�������
		PLAYER_PLAY_MODE_SONG_MV_MEDIA, 					//MV����ģʽ Media��
		PLAYER_PLAY_MODE_SONG_MV_KARAOKE,					//MV����ģʽ Karaoke��
		PLAYER_PLAY_MODE_RECORD_MV_MEDIA,					//MV�ط�ģʽ Media��
		PLAYER_PLAY_MODE_RECORD_MV_KARAOKE, 				//MV�ط�ģʽ Karaoke��
	}PLAYER_PLAY_MODE;

	typedef enum tagPLAYER_PLAY_STATUS
	{
		PLAYER_PLAY_STATUS_PLAY,							//����
		PLAYER_PLAY_STATUS_STOP,							//ֹͣ
	}PLAYER_PLAY_STATUS;

	typedef enum tagPLAYER_ENCODER_TYPE
	{
		PLAYER_ENCODER_TYPE_WAVE,							//WAVE��װ��PCM����
		PLAYER_ENCODER_TYPE_REC_ADPCM,						//REC��װ��ADPCM����
		PLAYER_ENCODER_TYPE_REC_SBC,							//REC��װ��SBC����
		PLAYER_ENCODER_TYPE_MP3_LAME,						//MP3��װ��LAME����
		PLAYER_ENCODER_TYPE_MP3_SHINE,						//MP3��װ��SHINE����
		PLAYER_ENCODER_TYPE_REC_CUSTOM,						//REC��װ�����ñ���
		PLAYER_ENCODER_TYPE_CUSTOM,
		PLAYER_ENCODER_TYPE_RECHEAD_CUSTOM,
	}PLAYER_ENCODER_TYPE;

	typedef enum tagPLAYER_RING_MODE
	{
		PLAYER_RING_MODE_OFF,
		PLAYER_RING_MODE_FIRST_HINT,							//��һ���ᳫ��
		PLAYER_RING_MODE_FIRST_LYRIC,						//��һ�и��
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
		PLAYER_MSG_GET_VERSION,							//��ȡ��ǰ�������汾��

		PLAYER_MSG_SET_FEEDBACK_MSG_FUNC = 1000,			//������Ϣ��������			FuncPlayerMsg
		PLAYER_MSG_SET_FEEDBACK_PRINT_FUNC,				//���ô�ӡ��������			FuncPlayerPrint
		PLAYER_MSG_SET_FEEDBACK_USER_DATA,				//�����û���������			void *

		PLAYER_MSG_SET_RECORD_MODE = 2000,				// ����¼����ʽ
		PLAYER_MSG_SET_REPLAY_MODE,						// ���ûطŷ�ʽ

		PLAYER_MSG_SET_PLAY_MODE,						//���ò�������				PLAYER_PLAY_MODE
		PLAYER_MSG_SET_SEEK_TIME,						//������תʱ��				��λ����

		PLAYER_MSG_SET_AUDIO_HANDLE,						//������Ƶ���

		PLAYER_MSG_SET_MIC_LATENCY,						//������˷��ӳ�			[10, 100]
		PLAYER_MSG_SET_MIC_CHANNELS,						//������˷�����			[0, 2]		0��ʾ��ϵͳ����
		PLAYER_MSG_SET_MIC_SAMPLE_RATE,					//������˷������			[0, 48000]	0��ʾ��ϵͳ����

		PLAYER_MSG_SET_AUDIO_IN_OPEN,					//������Ƶ����򿪺���
		PLAYER_MSG_SET_AUDIO_IN_CLOSE,					//������Ƶ����رպ���
		PLAYER_MSG_SET_AUDIO_IN_READ,					//������Ƶ�����ȡ����

		PLAYER_MSG_SET_MIC1_VOLUME,						//����1����˷�����		[0, 100]
		PLAYER_MSG_SET_MIC2_VOLUME,						//����2����˷�����		[0, 100]
		PLAYER_MSG_SET_MIC3_VOLUME,						//��������1����˷�����	[0, 100]
		PLAYER_MSG_SET_MIC4_VOLUME,						//��������1����˷�����		[0, 100]

		PLAYER_MSG_SET_SPK_LATENCY,						//���������ӳ�
		PLAYER_MSG_SET_SPK_CHANNELS,						//������������				[0, 2]		0��ʾ��ϵͳ����
		PLAYER_MSG_SET_SPK_SAMPLE_RATE,					//�������Ȳ�����			[0, 48000]	0��ʾ��ϵͳ����

		PLAYER_MSG_SET_AUDIO_OUT_OPEN,					//������Ƶ����򿪺���
		PLAYER_MSG_SET_AUDIO_OUT_CLOSE,					//������Ƶ����رպ���
		PLAYER_MSG_SET_AUDIO_OUT_WRITE,					//������Ƶ���д�뺯��

		PLAYER_MSG_SET_SPK_VOLUME,						//������������				[0, 100]

		PLAYER_MSG_SET_ECHO_VOLUME,						//���û�������				[0, 100]

		PLAYER_MSG_SET_LATENCY,							//���ûط��ӳ�				[0, MAX)
		PLAYER_MSG_SET_OUTPUT_LATENCY,					//��������ӳ�				[0, MAX)

		PLAYER_MSG_SET_SONG_SOURCE_TYPE,					//���ø�����Դ				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_SONG_PATH,						//���ø����ļ�·������ַ	·�����֧��255�ֽ�
		PLAYER_MSG_SET_SONG_SIZE,						//���ø�����С
		PLAYER_MSG_SET_SONG_BUF_ADDR,					//���ø��������ַ
		PLAYER_MSG_SET_SONG_BUF_SIZE,					//���ø��������С
		PLAYER_MSG_SET_SONG_BUF_READ,					//���ø��������ָ��
		PLAYER_MSG_SET_SONG_BUF_WRITE,					//���ø�������дָ��
		PLAYER_MSG_SET_SONG_FUNC_DATA,					//���ø������
		PLAYER_MSG_SET_SONG_FUNC_OPEN,					//���ø����򿪺���
		PLAYER_MSG_SET_SONG_FUNC_CLOSE,					//���ø����رպ���
		PLAYER_MSG_SET_SONG_FUNC_READ,					//���ø�����ȡ����
		PLAYER_MSG_SET_SONG_SAVE_PATH,					//���ø�������·�����������߲��ŵı��ر��ݣ�·�����֧��255�ֽ�

		PLAYER_MSG_SET_MUS_REVERB_ENABLE,				//�������ֻ��쿪��			0�رգ�1����
		PLAYER_MSG_SET_SP_SOUND_ENABLE,					//����������Чʹ��
		PLAYER_MSG_SET_SP_SOUND_MUSIC_VOL,				//����������ЧMUSIC����
		PLAYER_MSG_SET_SP_SOUND_VOCAL_VOL,				//����������ЧVOCAL����
		PLAYER_MSG_SET_SP_SOUND_REV_VOL,					//����������ЧREV����
		PLAYER_MSG_SET_SP_SOUND_KTV_VOL,					//����������ЧKTV����

		PLAYER_MSG_SET_SONG_LRC_PATH,					//��������LRC·��			·�����֧��255�ֽ�
		PLAYER_MSG_SET_SONG_CDG_PATH,					//��������CDG·��			·�����֧��255�ֽ�

		PLAYER_MSG_SET_SONG_TYPE,						//���ø�������				PLAYER_SONG_TYPE
		PLAYER_MSG_SET_MUSIC_VOLUME,						//������������				[0, 100]
		PLAYER_MSG_SET_PCM_CHANNELS,						//����PCM��������
		PLAYER_MSG_SET_PCM_SAMPLE_RATE,					//����PCM����������
		PLAYER_MSG_SET_PCM_CH_MODE,						//����PCM��������
		PLAYER_MSG_SET_MUS_FILE_TYPE_FLAG,				//����MUS�ļ����ͱ�־
		PLAYER_MSG_SET_MUS_SONG_NUMBER,					//����MUS�������			����������ΪTVS���ʱ�������ô���
		PLAYER_MSG_SET_MUS_DATA_OFFSET,					//��������ƫ��				����������ΪMUK���ʱ�������ô���
		PLAYER_MSG_SET_MUS_DATA_LENGTH,					//�������ݴ�С				����������ΪMUK���ʱ�������ô���
		PLAYER_MSG_SET_MUS_SERIAL_NUMBER,				//�������к�					����������ΪCIDʱ�������ô���
		PLAYER_MSG_SET_MUS_PRIVATE_KEY,					//����˽����Կ				����������ΪCIDʱ�������ô���
		PLAYER_MSG_SET_MUS_MIDI_VOLUME,					//����MUS����MIDI������		[0, 100]
		PLAYER_MSG_SET_MUS_MELODY_VOLUME,				//����MUS������������		[0, 100]
		PLAYER_MSG_SET_MUS_MEDIA_VOLUME,					//����MUS������������		[0, 100]
		PLAYER_MSG_SET_MUSIC_KEY,						//����MUS��������			[-12, 12]
		PLAYER_MSG_SET_MUSIC_TEMPO,						//����MUS�����ٶ�			[800, 1200]
		PLAYER_MSG_SET_MUS_VOCAL_FADE,					//����MUS��������״̬		PLAYER_VOCAL_STATUS
		PLAYER_MSG_SET_MUS_IFUN_CHANNELS,				//����MUS����IFUN��������	{1, 2}
		PLAYER_MSG_SET_MUS_IFUN_LEVEL,					//����MUS����IFUN�Ѷ�		IFUN_LEVEL
		PLAYER_MSG_SET_MUS_IFUN_EASY_LIMIT,				//����MUS����IFUN��ģʽ�����ж�����
		PLAYER_MSG_SET_MUS_IFUN_NORMAL_LIMIT,			//����MUS����IFUN��ͨģʽ�����ж�����
		PLAYER_MSG_SET_MUS_IFUN_HARD_LIMIT,				//����MUS����IFUN����ģʽ�����ж�����
		PLAYER_MSG_SET_MUS_AUTO_SEEK,					//����MUS�����Զ���ת		NULL���Զ���ת����һ�ο�ʼ
		PLAYER_MSG_SET_MIDI_DATABASE_PARAM,
		PLAYER_MSG_SET_SAMPLE_CHECK_VAL,					//���������������ֵ		[0, 32768]
		PLAYER_MSG_SET_SAMPLE_CHECK_NUM,					//�������������			<= 1152
		PLAYER_MSG_SET_MUTE_2_VOCAL_LIMIT,				//���þ�������������		MS
		PLAYER_MSG_SET_VOCAL_2_MUTE_LIMIT,				//������������������		MS
		PLAYER_MSG_SET_MIDI_MIDI_DATA_BUFFER,			//����MIDI����				MidiDataBuffer
		PLAYER_MSG_SET_MIDI_MIDI_DATA_SIZE,				//����MIDI����				MidiDataSize
		PLAYER_MSG_SET_MIDI_ORG_MIDI_TEMPO,				//����MIDI����				ORGMidiTempo
		PLAYER_MSG_SET_MIDI_STAFF_TOTAL_TICK,			//����MIDI����				StaffTotalTick
		PLAYER_MSG_SET_MV_FLAG,							//����MV��־
		PLAYER_MSG_SET_MUSIC_POINT_A,					//����A��
		PLAYER_MSG_SET_MUSIC_POINT_B,					//����B��
		PLAYER_MSG_SET_MUSIC_AB_MODE,					//����AB��ģʽ

		PLAYER_MSG_SET_RECORD_SOURCE_TYPE,				//����¼����Դ				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD_PATH,						//����¼��·��				·�����֧��255�ֽ�
		PLAYER_MSG_SET_RECORD_SIZE,						//����¼����С
		PLAYER_MSG_SET_RECORD_BUF_ADDR,					//����¼�������ַ
		PLAYER_MSG_SET_RECORD_BUF_SIZE,					//����¼�������С
		PLAYER_MSG_SET_RECORD_BUF_READ,					//����¼�������ָ��
		PLAYER_MSG_SET_RECORD_BUF_WRITE,					//����¼������дָ��
		PLAYER_MSG_SET_RECORD_FULL_FLAG,					//¼���������ű�־
		PLAYER_MSG_SET_RECORD_TYPE,						//����¼������
		PLAYER_MSG_SET_RECORD_VOLUME,					//����¼������				[0, 100]

		PLAYER_MSG_SET_RECORD2_SOURCE_TYPE,				//���û��ģʽ¼����Դ				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD2_PATH,						//���û��ģʽ¼��·��				·�����֧��255�ֽ�
		PLAYER_MSG_SET_RECORD2_SIZE,						//���û��ģʽ¼����С
		PLAYER_MSG_SET_RECORD2_BUF_ADDR,					//���û��ģʽ¼�������ַ
		PLAYER_MSG_SET_RECORD2_BUF_SIZE,					//���û��ģʽ¼�������С
		PLAYER_MSG_SET_RECORD2_BUF_READ,					//���û��ģʽ¼�������ָ��
		PLAYER_MSG_SET_RECORD2_BUF_WRITE,				//���û��ģʽ¼������дָ��
		PLAYER_MSG_SET_RECORD2_TYPE,						//���û��ģʽ¼������
		PLAYER_MSG_SET_RECORD2_VOLUME,					//���û��ģʽ¼������				[0, 100]

		PLAYER_MSG_SET_RECORD_FLAG,						//����¼����־				0�ر�¼����1����¼��
		PLAYER_MSG_SET_ENCODE_PATH,						//���ñ������·��
		PLAYER_MSG_SET_ENCODER,							//���ñ�����					PLAYER_ENCODER_TYPE
		PLAYER_MSG_SET_ENCODER_BITRATE,						//����MP3������				{32, 48, 64, 96, 128, 192, 256, 320}
		PLAYER_MSG_SET_SONG_NAME,						//���ø�������				�������������48�ֽڣ�¼���ã�������
		PLAYER_MSG_SET_SINGER_NAME,						//�����ݳ���					���48�ֽڣ�������
		PLAYER_MSG_SET_ALBUM_NAME,						//����ר��					���48�ֽڣ�������
		PLAYER_MSG_SET_DUET_DATA,						//����DUET���ݵ�ַ
		PLAYER_MSG_SET_DUET_SIZE,						//����DUET���ݴ�С
		PLAYER_MSG_SET_ENCODER_RING_MODE,				//���ñ�����Ϊ����ģʽ	PLAYER_RING_MODE

		PLAYER_MSG_SET_EQ_100HZ_VOL,						//����EQ��Ƶ����
		PLAYER_MSG_SET_EQ_1KHZ_VOL,						//����EQ��Ƶ����
		PLAYER_MSG_SET_EQ_5KHZ_VOL,						//����EQ��Ƶ����
		PLAYER_MSG_SET_EQ_QFACTOR,						//����EQ

		PLAYER_MSG_SET_MUS_FORCE_KSC,					//����MUS�ļ�ǿ��KSC��־
		PLAYER_MSG_SET_ECHO_DELAY,						//���û����ӳ�
		PLAYER_MSG_SET_LATENCY_DATA_PATH,				//�����ӳٲ�������·��
		PLAYER_MSG_SET_SP_SOUND_AGC_ON,					//����SPSOUNDPROC��AGCЧ��
		PLAYER_MSG_SET_SP_SOUND_COMPRESS_ON,			//����SPSOUNDPROC��COMPRESSЧ��
		PLAYER_MSG_SET_MUS_MIDI_ENABLE,					//����MIDI
		PLAYER_MSG_SET_MUS_TVS_PACK_FLAG,				//TVS���������־
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

		PLAYER_MSG_SET_EXT_MIDI_FLAG,					//����MIDI��־

		PLAYER_MSG_SET_PREPARE_MODE,

		PLAYER_MSG_SET_SONG_BUF_TIME,

		PLAYER_MSG_SET_SP_FAST_MODE,

		PLAYER_MSG_SET_OKF_PRODUCTID,				//����OKF�ͻ�����					����������ΪOKFʱ�������ô���

		PLAYER_MSG_SET_NOTE_MIC_HANDLE,

		PLAYER_MSG_SET_NOTE_MIC_LATENCY,						//������˷��ӳ�			[10, 100]
		PLAYER_MSG_SET_NOTE_MIC_CHANNELS,						//������˷�����			[0, 2]		0��ʾ��ϵͳ����
		PLAYER_MSG_SET_NOTE_MIC_SAMPLE_RATE,					//������˷������			[0, 48000]	0��ʾ��ϵͳ����

		PLAYER_MSG_SET_NOTE_AUDIO_IN_OPEN,					//������Ƶ����򿪺���
		PLAYER_MSG_SET_NOTE_AUDIO_IN_CLOSE,					//������Ƶ����رպ���
		PLAYER_MSG_SET_NOTE_AUDIO_IN_READ,					//������Ƶ�����ȡ����

		PLAYER_MSG_SET_RECORD_KEY,

		PLAYER_MSG_SET_RESAMPLE_QT,

		PLAYER_MSG_SET_ENCODE_DATA_PATH,					//���ñ������·��
		PLAYER_MSG_SET_ENCODE_DATA_SINK_TYPE,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_DATA,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_OPEN,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_CLOSE,
		PLAYER_MSG_SET_ENCODE_DATA_FUNC_WRITE,

		PLAYER_MSG_SET_RECORD_DATA_SOURCE_TYPE,			//����¼��������Դ				PLAYER_SOURCE_TYPE
		PLAYER_MSG_SET_RECORD_DATA_PATH,					//����¼������·��				·�����֧��255�ֽ�
		PLAYER_MSG_SET_RECORD_DATA_SIZE,					//����¼�����ݴ�С
		PLAYER_MSG_SET_RECORD_DATA_BUF_ADDR,			//����¼�����ݻ����ַ
		PLAYER_MSG_SET_RECORD_DATA_BUF_SIZE,			//����¼�����ݻ����С
		PLAYER_MSG_SET_RECORD_DATA_BUF_READ,			//����¼�����ݻ����ָ��
		PLAYER_MSG_SET_RECORD_DATA_BUF_WRITE,			//����¼�����ݻ���дָ��

		PLAYER_MSG_SET_SP_RECORD_FLAG,					//�����¼����Դ
		PLAYER_MSG_SET_SP_RECORD_HANDLE,
		PLAYER_MSG_SET_SP_RECORD_CHANNELS,
		PLAYER_MSG_SET_SP_RECORD_SAMPLE_RATE,
		PLAYER_MSG_SET_SP_RECORD_OPEN,
		PLAYER_MSG_SET_SP_RECORD_CLOSE,
		PLAYER_MSG_SET_SP_RECORD_READ,

		PLAYER_MSG_SET_LYRIC_BIN_PATH,					//���ö����Ƹ���ļ�·��			·�����֧��255�ֽ�

		PLAYER_MSG_GET_PLAY_STATUS = 3000,				//��ȡ��ǰ����״̬			PLAYER_PLAY_STATUS
		PLAYER_MSG_GET_LYRIC_INFO,						//��ȡ��ǰ�����Ϣ			LYRIC_SHOW_INFO
		PLAYER_MSG_GET_IFUN_INFO,						//��ȡ��ǰiFun��Ϣ			IFUN_DISPLAY_INFO
		PLAYER_MSG_GET_ENCODE_PERCENT,					//��ȡ��ǰ�������			�ٷ���
		PLAYER_MSG_GET_BUFFERING_FLAG,					//��ȡ��ǰ�����־			0��ʾ���軺�� 1��ʾ������
		PLAYER_MSG_GET_TOTAL_TIME,						//��ȡ������ʱ��
		PLAYER_MSG_GET_PLAY_TIME,						//��ȡ��ǰ����ʱ��
		PLAYER_MSG_GET_SONG_INFO,						//��ȡ����еĸ�����Ϣ		LYRIC_SHOW_INFO_SONG_INFO
		PLAYER_MSG_GET_LYRIC_INFO_BY_LINE_NUMBER,		//ͨ����������ȡ�����Ϣ	LYRIC_SHOW_INFO_LYRIC_INFO	����0��ʾ�ɹ� ����-1��ʾδ׼���� ����-2��ʾ����ӵ�е�����
		PLAYER_MSG_GET_LYRIC_INFO_WHEN_AUTO_SEEK,		//��ȡ����еĸ�����Ϣ		LYRIC_SHOW_INFO_SONG_INFO

		PLAYER_MSG_GET_MIC_BUF_ADDR,						//��ȡ��˷���������ַ
		PLAYER_MSG_GET_MIC_BUF_SIZE,						//��ȡ��˷���������С
		PLAYER_MSG_GET_MIC_BUF_READ,						//��ȡ��˷���������ָ��
		PLAYER_MSG_GET_MIC_BUF_WRITE,					//��ȡ��˷��������дָ��

		PLAYER_MSG_GET_MUTE_FLAG,						//��ȡ��ǰ����״̬

		PLAYER_MSG_CMD_PLAY = 4000,						//��ʼ����
		PLAYER_MSG_CMD_STOP,								//ֹͣ����
		PLAYER_MSG_CMD_PAUSE,								//��ͣ����
		PLAYER_MSG_CMD_RESUME,							//�ָ�����
		PLAYER_MSG_CMD_RECORD,							//��ʼ¼����������ֻ���ڷ�STOP״̬����
		PLAYER_MSG_CMD_RECORD_OFF,						//�ر�¼��
		PLAYER_MSG_CMD_START,
		PLAYER_MSG_CMD_PLAY_SYNC,
		PLAYER_MSG_CMD_STOP_SYNC,

		PLAYER_MSG_FB_CMD_PLAY = 5000,					//��Ϣ����							��ʼ����
		PLAYER_MSG_FB_CMD_STOP,							//��Ϣ����							ֹͣ����
		PLAYER_MSG_FB_CMD_STOP_CAUSED_BY_ERROR,			//��Ϣ����							�����ֹͣ����
		PLAYER_MSG_FB_CMD_PAUSE,							//��Ϣ����							��ͣ����
		PLAYER_MSG_FB_CMD_RESUME,						//��Ϣ����							�ָ�����
		PLAYER_MSG_FB_CMD_RECORD_FAILED,					//��Ϣ����							¼��ʧ��
		PLAYER_MSG_FB_SET_MIC1_VOLUME,					//����1����˷�������Ϣ����			[0, 100]
		PLAYER_MSG_FB_SET_MIC2_VOLUME,					//����2����˷�������Ϣ����			[0, 100]
		PLAYER_MSG_FB_SET_MIC3_VOLUME,					//����3����˷�������Ϣ���� 		[0, 100]
		PLAYER_MSG_FB_SET_MIC4_VOLUME,					//����4����˷�������Ϣ���� 		[0, 100]
		PLAYER_MSG_FB_SET_SPK_VOLUME,					//��������������Ϣ����				[0, 100]
		PLAYER_MSG_FB_SET_ECHO_VOLUME,					//���û���������Ϣ����				[0, 100]
		PLAYER_MSG_FB_SET_MUSIC_VOLUME,					//��������������Ϣ����				[0, 100]
		PLAYER_MSG_FB_SET_MUS_MIDI_VOLUME,				//����MUS������������Ϣ���� 	[0, 100]
		PLAYER_MSG_FB_SET_MUS_MELODY_VOLUME,			//����MUS��������������Ϣ����		[0, 100]
		PLAYER_MSG_FB_SET_MUS_VOCAL_VOLUME,				//����MUS��������������Ϣ����		[0, 100]
		PLAYER_MSG_FB_SET_MUS_KEY,						//����MUS����������Ϣ����			[0, 100]
		PLAYER_MSG_FB_SET_MUS_TEMPO,						//����MUS�����ٶ���Ϣ����			[800, 1200]
		PLAYER_MSG_FB_SET_MUS_VOCAL_FADE,				//����MUS��������״̬��Ϣ����		PLAYER_VOCAL_STATUS	
		PLAYER_MSG_FB_SET_RECORD_VOLUME,					//����¼��������Ϣ����				[0, 100]
		PLAYER_MSG_FB_GET_LATENCY,						//��Ƶ�豸�ӳ���Ϣ����
		PLAYER_MSG_FB_SET_MIDI_USER_DATA,				//��Ϣ����							����MIDI�û�����
		PLAYER_MSG_FB_SET_VOCAL_DATA,					//��Ϣ����							������������
		PLAYER_MSG_FB_SET_VOCAL_DATA_NULL,				//��Ϣ����							������������Ϊ��
		PLAYER_MSG_FB_NOTIFICATION_SAVE_FILE_SUCCESS,	//�����ļ�����ɹ�
		PLAYER_MSG_FB_NOTIFICATION_SAVE_FILE_FAILED,	//�����ļ�����ʧ��
		PLAYER_MSG_FB_NOTIFICATION_REC_FILE_ERROR,		//¼���ļ�����
		PLAYER_MSG_FB_AUTO_SEEK_LYRIC_INFO,				//�Զ���ת�����Ϣ
		PLAYER_MSG_FB_GET_TOTAL_TIME,					//��ȡ��Ƶ��ʱ��
		PLAYER_MSG_FB_GET_LYRIC_END_TIME,				//��ȡ��ʽ���ʱ��
		PLAYER_MSG_FB_GET_TOTAL_TIME_BY_LYRIC,			//�Ӹ���л�ȡ��Ƶ��ʱ��
		PLAYER_MSG_FB_SET_EQ_100HZ_VOLUME,				//����EQ�ĵ�Ƶ����
		PLAYER_MSG_FB_SET_EQ_1KHZ_VOLUME,				//����EQ����Ƶ����
		PLAYER_MSG_FB_SET_EQ_5KHZ_VOLUME,				//����EQ�ĸ�Ƶ����
		PLAYER_MSG_FB_SET_EQ_QFACTOR,					//����EQ
		PLAYER_MSG_FB_SET_ECHO_DELAY,					//���û����ӳ�
		PLAYER_MSG_FB_SET_REC_HEAD,						//����¼���ļ�ͷ
		PLAYER_MSG_FB_EXT_MIDI_SET_SYNC,					//����MIDIʱ��ͬ��
		PLAYER_MSG_FB_EXT_MUS_SET_QJ_ID,
		PLAYER_MSG_FB_CMD_RECORD_OFF,					//¼���ر�
		PLAYER_MSG_FB_AUTO_SEEK_LYRIC_INFO_FAILED,
		PLAYER_MSG_FB_OKF_PRODUCTOR_ID,
		PLAYER_MSG_FB_MUTE_PERCENT,
		PLAYER_MSG_FB_LYRIC_AFTER_LOAD,
		PLAYER_MSG_FB_LYRIC_BEFORE_UNLOAD,
		PLAYER_MSG_FB_SET_RECORD_KEY,
	}PLAYER_MSG;

	//������Ϣ����
	//����	PLAYER_MSG	��Ϣ
	//		void *		����
	//		void *		�û�����
	//����	0��ʾ�ɹ�
	//		-1��ʾʧ��
	typedef int (*FuncPlayerMsg)(PLAYER_MSG, void *, void *);

	//������ӡ����
	//����	char *		����
	//		void *		�û�����
	//����	��
	typedef void (*FuncPlayerPrintf)(char *, void *);

	//����Դ�򿪺���
	//����	void *	���
	//����	0		��ʾ�ɹ�
	//			-1		��ʾʧ��
	typedef int (*FuncDataSrcOpen)(void *);

	//����Դ�رպ���
	//����	void *	���
	typedef void (*FuncDataSrcClose)(void *);

	//����Դ��ȡ����
	//����	void *	���
	//			void *	��ַ
	//			int		ƫ��
	//			int		��С
	//����	int		ʵ�ʶ�ȡ�Ĵ�С,-1��ʾ��������?
	typedef int (*FuncDataSrcRead)(void *, void *, int, int);

	//����Դд�뺯��
	//����	void *	���
	//			void *	��ַ
	//			int		ƫ��
	//			int		��С
	//����	int		ʵ��д��Ĵ�С
	typedef int (*FuncDataSrcWrite)(void *, void *, int, int);

	//����	PlayerMsg
	//����	��������ģ�鷢��Ϣ
	//����	Msg			��Ϣ
	//		Data		����
	//����	�ɹ�����0��ʧ�ܷ���-1
	int PlayerMsg (void *Handle, PLAYER_MSG Msg, void *Data);

	//����	PlayerInit
	//����	��ʼ��������ģ��
	//����	�ɹ�����0��ʧ�ܷ���-1
	void *PlayerInit (int iFunLyricFlag);

	//����	PlayerFinish
	//����	����ʼ��������ģ��
	//����	�ɹ�����0��ʧ�ܷ���-1
	int PlayerFinish (void *Handle);

#if defined(__cplusplus)
}
#endif

#endif

