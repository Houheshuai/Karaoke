//�ļ�	iFun.h
//����	������iFunģ��Ľӿ�
//����	Chaos
//�汾	V1.00
//����	2012/1/18
//ʹ�÷���
//		����iFun_Init��ʼ��ģ��
//		����iFun_Load��������
//		���ϵ���iFun_GetInfoClassic��iFun_GetInfoModern��ȡiFun��Ϣ
//		����iFun_Unloadж������
//		����iFun_Finish����ʼ��ģ��

#ifndef _IFUN_H_
#define _IFUN_H_

#include "iFunInfo.h"

typedef void *IFUN_HANDLE;

typedef struct tagNOTE_INFO
{
	cp_uint16	SongNote;		//����
	cp_uint16	SongUnit;		//ʱ��
}NOTE_INFO;

typedef struct tagIFUN_STAFF_INFO
{
	NOTE_INFO	*NoteInfo;		//ԭʼ����
	cp_sint32	*NoteWrite;		//ԭʼ���ݵ�дָ��
}IFUN_STAFF_INFO;

typedef struct tagIFUN_LYRIC_INFO
{
	unsigned long	Language;			//������Ϣ
	char			*LyricLine1Info;	//��һ�и����Ϣ
	char			*LyricLine2Info;	//�ڶ��и����Ϣ
}IFUN_LYRIC_INFO;

typedef struct tagIFUN_VOCAL_INFO
{
	cp_Mutex	Mutex;
	cp_sint32	VocalCount;			//�ж��ٸ���������
	cp_sint32	TickCount;			//�ж��ٸ����ֲ�����
	cp_sint8	*KeyList;			//��������
	cp_sint32	*VocalList;			//��������
}IFUN_VOCAL_INFO;

typedef struct tagIFUN_LEVEL_INFO
{
	IFUN_LEVEL	Level;
	int			EasyLimit;
	int			NormalLimit;
	int			HardLimit;
}IFUN_LEVEL_INFO;

//����	iFun_Init
//����	��ʼ��iFunģ��
//����	�ɹ�����iFunģ������ʧ�ܷ���NULL
IFUN_HANDLE iFun_Init (void *Feedback);

//����	iFun_Finish
//����	����ʼ��iFunģ��
//����	Handle	iFunģ����
//����	�ɹ�����0��ʧ�ܷ���-1
int iFun_Finish (IFUN_HANDLE Handle);

//����	iFun_Load
//����	����iFun����
//����	Handle		iFunģ����
//		pKey		������ָ��
//		pStaffInfo	��������Ϣ
//		pLyricInfo	�����Ϣ
//		pVocalInfo	������Ϣ
//����	�ɹ�����0��ʧ�ܷ���-1
int iFun_Load (IFUN_HANDLE Handle, IFUN_LEVEL_INFO *pLevelInfo, IFUN_STAFF_INFO *pStaffInfo, IFUN_LYRIC_INFO *pLyricInfo, IFUN_VOCAL_INFO *pVocalInfo);

//����	iFun_Unload
//����	ж��iFun����
//����	Handle		iFunģ����
//����	�ɹ�����0��ʧ�ܷ���-1
int iFun_Unload (IFUN_HANDLE Handle);

//����	iFun_GetInfo
//����	��ȡiFun��Ϣ
//����	Handle		iFunģ����
//���	piFunInfo	��ǰ��Ҫ��ʾ��iFun��Ϣ
//����	�ɹ�����0��ʧ�ܷ���-1
int iFun_GetInfo (IFUN_HANDLE Handle, unsigned long Ticks, IFUN_DISPLAY_INFO *piFunInfo, unsigned long InputLatency);

//����	iFun_GetScore
//����	��ȡiFun����
//����	Handle		iFunģ����
//���	Score		����
void iFun_GetScore (IFUN_HANDLE Handle, IFUN_SCORE *Score);

#endif
