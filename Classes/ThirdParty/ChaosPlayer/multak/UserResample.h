/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	UserResample.h
* 	Function:	重采样用户头文件。
*	Writer:		Chen Jiejun
*	version:    2010/06/22 ver 1.00
**********************************************************/

#ifndef USERRESAMPLE_H
#define USERRESAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////// 
// 
// ResampleInit:
//	初始化函数。返回handle以便同时进行多个resample过程。
//
/////////////////////////////////////////////////////////////////////
extern char*	ResampleInit(void);

///////////////////////////////////////////////////////////////////// 
// 
// ResampleFinish:
//	释放resamleple对应handle。
//
/////////////////////////////////////////////////////////////////////
extern int		ResampleFinish(char *handle);

///////////////////////////////////////////////////////////////////// 
//
// Resample: 
//	重采样执行
// 
// input: 
//	short *input		: 输入地址，可以为单通道或双通道
//	int	inputrate		: 输入采样率
//	int	outputrate		: 输出采样率。当输出采样率大于输入采样率时，波形被拉伸。否则被压缩。
//	int	inputlength		: 输入sample数。
//
// output:
//	short *output		: 输出地址，可以为单通道或双通道
//	int					: 输出sample数
//
// 使用注意点			: outputrate * inputlength * 2要小于0x7fffffff，否则运算会溢出。一般inputrate和outputrate尽量约去最大公约数传入就不会有问题
//
///////////////////////////////////////////////////////////////////// 
extern int		Resample(short *input, short *output, int inputrate, int outputrate, int inputlength, int channel, char *handle);

#ifdef __cplusplus
}
#endif

#endif
