//�ļ�	iFunInfo.h
//����	������iFun��Ϣ�Ľṹ
//����	Chaos
//�汾	V1.00
//����	2012/1/18

#ifndef _IFUN_INFO_H_
#define _IFUN_INFO_H_

#define IFUN_DISPLAY_LINE_INVALID	0xFFFFFFFF
#define MAX_SONG_SEGMENT			52
#define MAX_VOCAL_SEGMENT			256
#define MAX_VOCAL_COUNT				2

typedef enum tagIFUN_LEVEL
{
	IFUN_LEVEL_EASY,
	IFUN_LEVEL_NORMAL,
	IFUN_LEVEL_HARD,
	IFUN_LEVEL_CHEAT,
}IFUN_LEVEL;

typedef struct tagIFUN_SCORE
{
	int	iFunCount;							// ����iFun
	int	Score[MAX_VOCAL_COUNT];				// �ٷ��Ʒ���
	int TotalScore[MAX_VOCAL_COUNT];		// �ܷ���
	int MaleScore[MAX_VOCAL_COUNT];		// ��������
	int FemaleScore[MAX_VOCAL_COUNT];		// Ů������
}IFUN_SCORE;

typedef enum tagIFUN_MOVE_TYPE
{
	IFUN_MOVE_SEG,
	IFUN_MOVE_NONE,
	IFUN_MOVE_GOOD,
	IFUN_MOVE_BAD,
}IFUN_MOVE_TYPE;

typedef enum tagIFUN_BONUS_TYPE
{
	IFUN_BONUS_NONE,
	IFUN_BONUS_60POINTS,
	IFUN_BONUS_40POINTS,
	IFUN_BONUS_20POINTS,
	IFUN_BONUS_5POINTS_TYPE1,
	IFUN_BONUS_5POINTS_TYPE2,
	IFUN_BONUS_5POINTS_TYPE3,
	IFUN_BONUS_5POINTS_TYPE4,
}IFUN_BONUS_TYPE;

typedef struct tagIFUN_SONG_SEGMENT
{
	unsigned long		StartX;
	unsigned long		StartY;
	unsigned long		Length;
}IFUN_SONG_SEGMENT;

typedef struct tagIFUN_VOCAL_SEGMENT
{
	unsigned long		StartX;
	unsigned long		StartY;
	unsigned long		Length;
	unsigned long		Move;
	unsigned long		Bonus;
}IFUN_VOCAL_SEGMENT;

typedef struct tagIFUN_DISPLAY_INFO
{
	unsigned long		LineNo;									// ����	����ʾʱ��IFUN_DISPLAY_LINE_INVALID
	unsigned long		FreeStyle;								// 1��ʾ����ʽ0��ʾ��������
	unsigned long		TotalUnit;								// ��ʱ����

	unsigned long		SongSegmentCount;						// ��׼������
	IFUN_SONG_SEGMENT	SongSegmentList[MAX_SONG_SEGMENT];		// ��׼������

	int					VocalCount;												// ��������
	unsigned long		VocalSegmentCount[MAX_VOCAL_COUNT];						// ����������
	IFUN_VOCAL_SEGMENT	VocalSegmentList[MAX_VOCAL_COUNT][MAX_VOCAL_SEGMENT];	// ����������

	signed long			Score[MAX_VOCAL_COUNT];
	signed long			ScoreHundred[MAX_VOCAL_COUNT];
	signed long			ScoreMaleHundred[MAX_VOCAL_COUNT];
	signed long			ScoreFemaleHundred[MAX_VOCAL_COUNT];
	signed long			ScoreStatus[MAX_VOCAL_COUNT];
}IFUN_DISPLAY_INFO;

#endif
