/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	HummingSearch.h
* 	Function:		Head file for Humming Search Module. 给调用者的h文件
*	Writer:		Chen Jiejun, Fu ZhiCheng
*	version:    	2010/7/9 ver 1.02
**********************************************************/

#ifndef USERHUMMINGSEARCH_H
#define USERHUMMINGSEARCH_H


#ifdef _cplusplus
//extern "C"
//{
#endif

/********************************************************
**	采样率为32000
********************************************************/

/***********************************************************
**	哼唱点歌函数调用流程：
	1.	LoadSongsData读入midi文件数据。
	2.	HS_HummingSearchInit初始化模块。
	3.	每次新的哼唱开始前，调用HS_HummingStart。
	4.	对每一帧哼唱，使用HS_InputFrame输入到哼唱模块。帧长不要求。但是必须是连续帧。不得跳帧。
	5.	开始检索，调用HS_HummingStop，获得哼唱检索结果。
	6.	重新哼唱不必重新进出模块，调用HS_HummingStart即可。
	7.	退出模块请调用HS_HummingSearchFinish释放资源。否则重复进入会造成内存溢出。
	8.	最后要释放load的midi文件数据占用的内存请调用HS_FreeHummingData。

出错信息表:
-2000	:	哼唱时间超出系统允许最长时间
-2001	:	哼唱检索过程中有malloc失败
-2002	:	哼唱时间过短
-2003	:	load 哼唱数据失败
-2004	:	load 哼唱数据输入无效buffer
-2005	:	m_nSingLength超出范围，正常情况下不可能发生。除非程序错误

***********************************************************/


/********************************************************
**	进入哼唱模块前数据初始化
**	input:
**		maxHumTime		: 哼唱最长有效时间 ，默认为15s，time单位为毫秒
**	output:
**		int				:返回1为成功，否则为失败，详见出错信息表
********************************************************/
extern int HS_HummingSearchInit(int maxHumTime);

/***********************************************************
**	HS_HummingSearchFinish : 退出哼唱模块时释放空间，与HS_HummingSearchInit对应
**
***********************************************************/
extern void	HS_HummingSearchFinish(void);

/***********************************************************
**	HS_LoadHummingData: load哼唱数据，并解密
**		
**	input:
** 		*buffer		: 存放数据的数组
**		bufferSize	: 数组大小
**	
** 	output:
**		int 			: 返回1为成功，否则为失败，详见出错信息表
***********************************************************/
extern int HS_LoadHummingData(char *buffer, int bufferSize);

/*************************************************************
**	HS_FreeHummingData :	释放载入歌曲的内存，与HS_LoadHummingData对应
**	
*************************************************************/
extern void	HS_FreeHummingData(void);

/********************************************************
**	HS_HummingStart : 每次哼唱的初始化。
**		这里强行要求输入参数waittime，一般外部在哼唱完后，会等待一段时间静音后进入检索。这个waittime为外部等待静音的时间。单位为毫秒。建议等待值为2000ms。
**
********************************************************/
extern void	HS_HummingStart(int waittime);

/***********************************************************
**	HS_InputFrame : 输入一帧数据到哼唱模块
** 	input : 
** 		*frame 	: 一帧数据
**		monolength	: 单通道帧长度
**		channel		: 输入数据通道数，双通道的要interleave
**	output : 
** 		return :	
**		int		:返回1或2为成功，否则为失败，详见出错信息表
**			1	:  计算成功，还未开始哼唱
**			2	:  计算成功，已经开始哼唱
**
***********************************************************/
extern int HS_InputFrame(short *frame, int monolength, int channel);

/****************************************************************
**	HS_HummingStop :	检索出前n个最佳匹配结果存入数组
** 	input : 
**		*SongID		: 外部传入的存放点歌号的数组
**	output :  
**		int 			: 返回1为成功，否则为失败，详见出错信息表
**			特别的，返回-2002，说明哼唱时间过短，应做无效处理，此时应不检索调用HS_HummingStart进行重新哼唱。
**
****************************************************************/
extern int HS_HummingStop(int * SongID);

/****************************************************************
**	HS_SetBestSongNumber :	设置检索多少个最佳结果。不设置的话默认为32.
**
****************************************************************/
extern void HS_SetBestSongNumber(int num);


#ifdef _cplusplus
//}
#endif

#endif

