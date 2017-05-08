/*********************************************************
*	Copyright(c)2001,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	MSE_Effect.h
* 	Function:	MSE Sound Effect.
*	Writer:		Chen Jiejun
*	version:    2010/04/02 ver 1.00
**********************************************************/

#ifndef USERMSEEFFECT2_H
#define USERMSEEFFECT2_H

extern const char	g_pMSEEffectVersion2[16];
///////////////////////////////////////////////////////////////////// 
// 
//MSE_Init:
// 初始化MSE全局参数。每次重新打开MSE或者切换歌曲需要重新初始化
// 
///////////////////////////////////////////////////////////////////// 
extern int	MSE_Init2();

///////////////////////////////////////////////////////////////////// 
// 
//MSE_Stereo_Bass32K_Int:
// 为强化歌曲中低音所做的MSE音效。输入输出皆为int。为双通道。
//	int *input		:	输入帧
//	int *output		:	输出帧。
//	int	length		:	输入帧的一个单独通道的sample个数
// 
///////////////////////////////////////////////////////////////////// 
extern int MSE_Stereo_Bass32K_Int2(int *input, int *output, int length);

///////////////////////////////////////////////////////////////////// 
// 
//MSE_Stereo_Bass32K:
// 定点化后的MSE算法。为四通道。其中0，2为有效sample
//	short *inputL	:	输入帧左通道起始地址。为NULL时则该通道无效
//	short *inputR	:	输入帧右通道起始地址。为NULL时则该通道无效
//	int inputstep	:	输入帧单通道每两个sample间隔（普通双通道则为2）
//	short *outputL	:	输出帧左通道起始地址。为NULL时则该通道无效
//	short *outputR	:	输出帧右通道起始地址。为NULL时则该通道无效
//	int outstep		:	输出帧单通道每两个sample间隔（普通双通道则为2）
//	int	length		:	输入帧一个通道sample个数
//	使用此函数，输出必须与输入对应。即inputL == NULL，则必需且需要outputL == NULL，同样inputR == NULL，则必需且需要outputR == NULL，
// 
///////////////////////////////////////////////////////////////////// 
extern int MSE_Stereo_Bass32K2(short *inputL, short *inputR, int inputstep, short *outputL, short *outputR, int outstep, int length);

///////////////////////////////////////////////////////////////////// 
// 
//MSE_Stereo_Bass32K_Nolimit:
// 为强化歌曲中低音所做的MSE音效。int输出不做short限制。为双通道。
//	short *input	:	输入帧
//	int *output		:	输出帧。
//	int	length		:	输入帧的一个单独通道的sample个数
// 
///////////////////////////////////////////////////////////////////// 
extern int MSE_Stereo_Bass32K_Nolimit2(short *input, int *output, int length);

#endif

