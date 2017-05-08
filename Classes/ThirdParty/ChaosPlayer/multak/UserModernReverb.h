/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	ModernReverb.h
* 	Function:	现代混响用户头文件。
*	Writer:		Chen Jiejun
*	version:    2010/04/06 ver 1.00
**********************************************************/

#ifndef USERMODERNREVERB2_H
#define USERMODERNREVERB2_H

extern const char	g_pModernReverbVersion2[16];

///////////////////////////////////////////////////////////////////// 
// 
// MR_Init:
//	现代reverb初始化函数。
//
///////////////////////////////////////////////////////////////////// 
extern void* MR_Init2();
extern void* MR_Init_16K();

///////////////////////////////////////////////////////////////////// 
// 
// MR_Finish:
//	现代reverb释放资源
//
///////////////////////////////////////////////////////////////////// 
extern int MR_Finish2(void* mr_hdle);


///////////////////////////////////////////////////////////////////// 
// 
// MR_Reset:
//	现代reverb重置参数函数。每次重新开始使用都要运行一下
//
///////////////////////////////////////////////////////////////////// 
extern int MR_Reset2(void* mr_hdle);

///////////////////////////////////////////////////////////////////// 
// 
// MR_ModernReverbTable:
//	现代reverb。双通道int。根据一个level自动调整干湿比
// input:
//	in		:	输入sample，为左右交叉双通道int格式
//	length	:	单通道sample数
//	nchannel:	输入输出通道数
//	ReverbLevel:	干湿比。0则输出纯干声，128则输出纯湿声。40-60效果较好。
// output:
//	out		:	输出buffer。输出为左右交叉双通道int。输入输出可以是一个buffer
//
///////////////////////////////////////////////////////////////////// 
extern int MR_ModernReverbTable2(void* mr_hdle, int *in, int *out, int length, int nchannel, int ReverbLevel);

///////////////////////////////////////////////////////////////////// 
// 
// MR_ModernReverbShort:
//	现代reverb。支持双通道或单通道short
// input:
//	in		:	输入sample，为左右交叉双通道short格式
//	length	:	单通道sample数
//	nchannel:	通道数
//	dryvolume:	输出的干声音量，0为无声，256为原声的两倍
//	reverbvolume:输出的湿声音量，0为无声，256为放大到原来的两倍
// output:
//	out		:	输出buffer。输出为左右交叉双通道int。输入输出可以是一个buffer
//
///////////////////////////////////////////////////////////////////// 
extern int MR_ModernReverbShort2(void* mr_hdle, short *in, short *out, int length, int nchannel, int dryvolume, int reverbvolume);

///////////////////////////////////////////////////////////////////// 
// 
// MR_ModernReverbStereo:
//	现代reverb。双通道int
// input:
//	in		:	输入sample，为左右交叉双通道int格式
//	length	:	单通道sample数
//	nchannel:	通道数
//	dryvolume:	输出的干声音量，0为无声，256为原声的两倍，
//	reverbvolume:输出的湿声音量，0为无声，256为放大到原来的两倍，
// output:
//	out		:	输出buffer。输出为左右交叉双通道int
//
///////////////////////////////////////////////////////////////////// 
extern int MR_ModernReverbStereo2(void* mr_hdle, int *in, int *out, int length, int nchannel, int dryvolume, int reverbvolume);


///////////////////////////////////////////////////////////////////// 
// 
// MR_ModernReverbTableShort:
//	现代reverb。单双通道short。根据一个level自动调整干湿比
// input:
//	in		:	输入sample，为左右交叉双通道short格式
//	length	:	单通道sample数
//	nchannel:	通道数
//	ReverbLevel:	干湿比。0则输出纯干声，128则输出纯湿声。40-60效果较好。
// output:
//	out		:	输出buffer。输出为左右交叉双通道int。输入输出可以是一个buffer
//
///////////////////////////////////////////////////////////////////// 
extern int MR_ModernReverbTableShort2(void* mr_hdle, short *in, short *out, int length, int nchannel, int ReverbLevel);

#endif

