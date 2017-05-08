/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	UserIfunCharacter.h
* 	Function:		用于提供IFun等所关心的语音特征。用户头文件
*	Writer:		Chen Jiejun
*	version:    	2010/04/14 ver 1.10
**********************************************************/
#ifndef USERIFUNCHARACTER_H
#define USERIFUNCHARACTER_H
extern const char	g_pIFunCharacterVersion[16];



///////////////////////////////////////////////////////////////////// 
// 
// IFC_CalcStereoNote: 
//	计算多通道音高，支持单双通道
// 
// input: 
//	short *inputL	:	输入左通道sample首地址
//	short *inputR	:	输入右通道sample首地址
//	int monoframelen:	一帧的一个通道sample数目.一帧至少需要1024个sample!!!
//	int samplestep	:	一个通道sample每两个sample之间隔多少个short(比如最普通的interleave short双通道格式则这个值为2)
//
// output:
//	int *noteL	:	左通道音高音分。辅音则为0
//	int *noteR	:	右通道音高音分。辅音则为0
//	int			:	返回1则说明计算成功，-1说明帧太短。
//
// 特别说明:
//	左或右通道为NULL时则该通道不做，因此这个函数也可用于单通道。
//	该函数也可用于32bit数据，假如是满幅的，首地址为第一个sample高位并合理设置samplestep即可。
//
///////////////////////////////////////////////////////////////////// 
extern int IFC_CalcStereoNote(short *inputL, short *inputR, int monoframelen, int samplestep, int *noteL, int *noteR, int *energyL, int *energyR);

///////////////////////////////////////////////////////////////////// 
// 
// IFC_IFunCharacter_Init: 
//	Ifun 特征值计算初始化。开始新歌时需调用
// 
///////////////////////////////////////////////////////////////////// 
extern int IFC_IFunCharacter_Init(void);

///////////////////////////////////////////////////////////////////// 
// 
// IFC_CalcCharacter: 
//	计算一单通道语音信号帧特征。而特征参数需通过以下各get函数获得
// 
// Input: 
//	short *frame	: 输入帧地址。
//	int length		: 输入帧长度。输入帧长度必须大于1024!否则将无法计算而返回全0值.
// Output:
//	int			: 正数则为成功计算。负数则说明输入长度太短不到1024
//
///////////////////////////////////////////////////////////////////// 
extern int IFC_CalcCharacter(short *frame, int length);

///////////////////////////////////////////////////////////////////// 
// 
// GetPitch: 
//	获得当前帧的周期长度
//
///////////////////////////////////////////////////////////////////// 
extern int	GetPitch();

///////////////////////////////////////////////////////////////////// 
// 
// GetVoice: 
//	当前帧是否为元音。是则返回1，否则返回0
//
///////////////////////////////////////////////////////////////////// 
extern int	GetVoiceOrNot();

///////////////////////////////////////////////////////////////////// 
// 
// GetEnergy: 
//	获得当前帧的能量。此处定义为到sample平均数的差的绝对值的平均数。
//
///////////////////////////////////////////////////////////////////// 
extern int	GetEnergy();

///////////////////////////////////////////////////////////////////// 
// 
// GetNote: 
//	获得当前帧的绝对音分。以midi 0号音符标准音高为0.
//
///////////////////////////////////////////////////////////////////// 
extern int GetNote(void);


#endif

