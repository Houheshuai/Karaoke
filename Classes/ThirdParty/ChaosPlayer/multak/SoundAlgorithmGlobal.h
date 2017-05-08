/*********************************************************
*	Copyright(c)2009,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	SoundAlgorithmGlobal.c
* 	Function:	音频算法global头文件，接口转换和常用函数。以及定义系统函数。移植时需要用户在这里定义系统函数。
*	Writer:		Chen Jiejun
*	version:    2010/7/9 ver 1.03
**********************************************************/

#ifndef SOUNDALGORITHMGLOBAL_H
#define SOUNDALGORITHMGLOBAL_H
#include "UserSoundAlgorithmGlobal.h"


#define	AS_Malloc							malloc
#define	AS_FREE								free


#define	SafeFree(buffer)			if(buffer != NULL){AS_FREE((char*)(buffer));buffer = NULL;}
#define	SHORTDISTRICT(b, a)		if(a > 32767)b = 32767;else if(a < -32768)b = -32768;else b = (short)a;
#define	SHORTDISTRICT2(b, a)		b=a;

#ifndef MAX
#define	MAX(a, b)				((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define	MIN(a, b)				((a)>(b)?(b):(a))
#endif

#ifndef NULL
#define NULL	0
#endif

#define	MEMMALLOC_HEAD			"ASMALOC"
//出错信息
#define	ERROR_MALLOC_FAILED						-9000		//malloc空间失败
#define	ERROR_INPUT_DATA_NULL					-100		//转换接口时输入数据为NULL
#define	ERROR_OUTPUT_DATA_NULL					-101		//转换接口时输出数据为NULL

typedef struct tagKPoolMallocInfo
{
	int	addr;
	int	size;
}KPoolMallocInfo;




///////////////////////////////////////////////////////////////////// 
// 
// SafeMalloc:
//	打印出错信息的Malloc
// 
///////////////////////////////////////////////////////////////////// 
extern void *SafeMalloc(int size);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Memset:
//	同系统memset。
// 
///////////////////////////////////////////////////////////////////// 
extern void SA_Memset(char *target, unsigned char num, int memlen);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Memcpy:
//	同系统memcpy。
// 
///////////////////////////////////////////////////////////////////// 
extern void SA_Memcpy(char *target, char *source, int memlen);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Sort_List:
//	对序列is进行从大到小的排序
// input:	
//	len:		序列长度
// output:
//	int :		原来的0位置的新位置
// 
///////////////////////////////////////////////////////////////////// 
extern int SA_SortList(int *is, int len, int *newposition);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Strcmp:
//	同系统strcmp。
//
///////////////////////////////////////////////////////////////////// 
extern int SA_Strcmp(unsigned char *str1, unsigned char *str2);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Strlen:
//	同系统strlen。
// 
///////////////////////////////////////////////////////////////////// 
extern int SA_Strlen(unsigned char *str1);

///////////////////////////////////////////////////////////////////// 
// 
// SA_Strlwr:
//	同系统strlwr。将字符串改为小写
// 
///////////////////////////////////////////////////////////////////// 
extern void SA_Strlwr(unsigned char *str);


///////////////////////////////////////////////////////////////////// 
// 
// SA_GetFileSize:
//	同系统strlwr。将字符串改为小写
// 
///////////////////////////////////////////////////////////////////// 
extern int SA_GetFileSize(AS_ReadFileType fd);


///////////////////////////////////////////////////////////////////// 
// 
// CjjLog:
//	自定义log函数，输出log(x)*1024
//
///////////////////////////////////////////////////////////////////// 
extern int	CjjLog(int x);


///////////////////////////////////////////////////////////////////// 
// 
// CjjExp:
//	自定义exp函数，输出exp(x / 1024)
// 
///////////////////////////////////////////////////////////////////// 
extern int	CjjExp(int x);


#endif

