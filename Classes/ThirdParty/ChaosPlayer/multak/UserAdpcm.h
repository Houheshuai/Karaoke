/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	UserAdpcm.h
* 	Function:		ADPCM编解码用户头文件
*	Writer:		Chen Jiejun
*	version:    	2010/04/14 ver 1.00
*
**********************************************************/

#ifndef USERADPCM_H
#define USERADPCM_H


#ifdef _cplusplus
extern "C"
{
#endif

#define RECORD_INDEX_AND_VALPRED_SAMPLE_COUNT	8000			//每半秒记录一组数据

extern const char	g_pAdpcmVersion[16];

///////////////////////////////////////////////////////////////////// 
// 
// AE_AdpcmEncode_Init:
//	adpcm编码初始化函数。没开始一次新的adpcm编码都需做。
//
///////////////////////////////////////////////////////////////////// 
extern int	AE_AdpcmEncode_Init(void);

///////////////////////////////////////////////////////////////////// 
// 
// adpcm_encode:
//	单点adpcm编码函数
//
///////////////////////////////////////////////////////////////////// 
extern int	AE_DotEncode(short AP_input);

///////////////////////////////////////////////////////////////////// 
// 
// AE_FrameEncode:
//	多点adpcm编码函数。支持单通道和双通道。
//	short *input		: 输入地址，可以为单通道或双通道
//	short *output		: 输出地址，可以为单通道或双通道
//	int	length			: 输入一个通道sample数
//	int	channels		: 输入的通道数
// output:
//	int					: 输出的byte数
//
///////////////////////////////////////////////////////////////////// 
extern int	AE_FrameEncode(short *input, char *output, int length, int channel);

///////////////////////////////////////////////////////////////////// 
// 
// AE_GetIndex:
//	获取某组的Index
//	int	Count		: 组别，8000一组
// return:
//	int					: Index
//
///////////////////////////////////////////////////////////////////// 
extern int AE_GetIndex(int Count);

///////////////////////////////////////////////////////////////////// 
// 
// AE_GetValPred:
//	获取某组的ValPred
//	int	Count		: 组别，8000一组
// return:
//	int					: ValPred
//
///////////////////////////////////////////////////////////////////// 
extern int AE_GetValPred(int Count);

///////////////////////////////////////////////////////////////////// 
// 
// AE_AdpcmEncode_Init:
//	adpcm解码初始化函数。没开始一次新的adpcm解码都需做。
//
///////////////////////////////////////////////////////////////////// 
extern int	AD_AdpcmDecode_Init(void);

///////////////////////////////////////////////////////////////////// 
// 
// AD_DotDecode:
//	单点adpcm解码函数
//
///////////////////////////////////////////////////////////////////// 
extern short AD_DotDecode(int AP_code);

///////////////////////////////////////////////////////////////////// 
// 
// AD_FrameDecode:
//	多点adpcm编码函数。
//	short *input		: 输入地址，可以为单通道或双通道
//	short *output		: 输出地址，可以为单通道或双通道
//	int	length			: 输入byte数
//	int	channels		: 输入的通道数
// output:
//	int					: 输出的一个通道sample数
//
///////////////////////////////////////////////////////////////////// 
extern int	AD_FrameDecode(char *input, short *output, int length, int channel);

///////////////////////////////////////////////////////////////////// 
// 
// AD_SetIndexAndValPred:
//	设置某组的Index和ValPred
//	int	Index			: 设定的Index值
//	int	ValPred		: 设定的ValPred值
// return:
//	int					: 0表示成功-1表示失败
//
///////////////////////////////////////////////////////////////////// 
extern int AD_SetIndexAndValPred(int Index, int ValPred);

#ifdef _cplusplus
}
#endif

#endif
