/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	UserEcho.h
* 	Function:		人声Echo用户使用头文件
*	Writer:		Chen Jiejun
*	version:    2009/10/22 ver 1.00
*               2012/07/25 ver 1.01	Update Create/Desroy Interface     
**********************************************************/
#ifndef USERECHO_H
#define USERECHO_H
extern const char CP_g_pEchoVersion[16];

#define ECHO_MORE_DELAY

#define	FIRST_ADJUST
#define	DEFAULT_DELAY			6909	// 9522
#define	DEFAULT_MULTITAP1		2278	// 3139
#define	DEFAULT_MULTITAP2		4592	// 6329
#define	DEFAULT_GAIN			512		// 512

#ifndef ECHO_MORE_DELAY
#define MAX_DELAY				(6909 * 48 / 32)
#else
#define MAX_DELAY				(10049 * 48 / 32)
#endif

#define ECHOID					0x010001
#define MAXCHANNEL				4
#define MAX_DELAY_NO			16

typedef struct tagEcho			// Echo struct
{
#ifdef _DEBUG
	int	EchoID;
#endif 
	int m_pDelayLine[MAX_DELAY];	// Data line

	int *m_pCombDelayLine;			//comb delay
	int	*m_pCombDelayLineEnd;
	int *m_pCombPoint;				
	int *m_pSampleWrPoint;
	int *m_pMultiTapPoint1;			//multi tap	
	int *m_pMultiTapPoint2;
	int	m_iLPFilterMem;				//low pass filter of comb
	int	m_iCombOutSample;			//comb output sample

	int	echo_volume[MAXCHANNEL];				
	int	dry_volume[MAXCHANNEL];
	int	AMP[MAXCHANNEL];

	int	echo_channel;
	int	SampleRate;
	int FirstAdjust;

	int	DelayNo;
	int	NewDelayNo;
	int	FadeSample;

	int	Gain;

	void * pEQ;

	int (*Echo)(short *input, short *outputL, int Samples, struct tagEcho *pEcho);
} tEcho;
/////////////////////////////////////////////////////////////////////
/*

         |------------------------------|  
   Gain  |   ----------------------     |  Dry / Wet
-----|--(+)--|                    |-----------(+)---------
     |       ----------------------            |
     |       |      Delay         |            | 
	 -------------------------------------------


*/
/////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////// 
// 
//  CreateEcho & Init:
// 
///////////////////////////////////////////////////////////////////// 
extern tEcho* CP_CreateEcho(int Channel, int SampleRate, int FirstAdjust);

///////////////////////////////////////////////////////////////////// 
// 
//  DestroyEcho
// 
///////////////////////////////////////////////////////////////////// 
extern int CP_DestroyEcho(tEcho* pEcho);

///////////////////////////////////////////////////////////////////// 
// 
//  Set Echo Parameter
// 
///////////////////////////////////////////////////////////////////// 
// Delay:	[0..15] Time is (6.75ms - 216ms)
// Gain:	Gain / 1024
// Volume:	echo_volume, dry_volume, PreAmp / 256;
extern int CP_SetEchoDelay(int Delay, tEcho *pEcho);
extern int CP_SetEchoGain(int Gain, tEcho *pEcho); 
extern int CP_SetEchoChannelVolume(int Channel, int echo_volume, int dry_volume, int AMP256, tEcho *pEcho);
extern int CP_SetEQ(void *eq, int pEcho);

///////////////////////////////////////////////////////////////////// 
//
// EchoProcess: 
//	Echo函数
// 
// Parameters: 
//	short *input	: 输入地址，可以为单通道或双通道
//	short *output	: 输出地址，可以为单通道或双通道
//	int	sample		: 采样数
//  pEcho			: Echo 结构
///////////////////////////////////////////////////////////////////// 
extern int CP_ProcessEcho(short *input, short *output,  int samples, tEcho *pEcho);

#ifdef __cplusplus
}
#endif

#endif

