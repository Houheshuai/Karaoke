/*********************************************************
*	Copyright(c)2001,上海渐华科技发展有限公司
* 		All rights reserved.
* 
*	File Name:	SpeechSearch.h
* 	Function:		给模块使用者调用的外部函数集合。所有函数返回1则正常，返回负值则为出错，不能继续运行模块。出错信息见附注。
*	Writer:		Chen Jiejun
*	version:		2010/03/16 ver 1.00
**********************************************************/
#ifndef USERSPEECHSEARCH_H
#define	USERSPEECHSEARCH_H


#ifdef _cplusplus
//extern "C"
//{
#endif

extern const char	g_pSpeechSearchVersion[16];

/***********************************************************
**	语音点歌函数调用流程：
	可采用两种方式，同步方式和异步方式。
	
一.	同步方式
	每帧输入时根据CPU状况同步进行识别一部分歌曲。将剩下的歌曲放到最后一起识别。
	同步方式使用简单，但是需给CPU留有余量，否则可能出现来不及处理的情况。
	具体步骤:
	1.	SS_LoadFileData载入模型和歌曲文件。
	2.	SS_Init初始化模块。注意这里要指定英文还是中文系统。
		注意根据CPU状况指定多少歌曲实时处理。CPU越慢，in_time_song_num越小。一般实时消耗CPU为0.081 * in_time_song_num(MIPS)。推荐将此数设为CPU MIPS* 10。
	3.	每次新的点歌开始前，调用SS_InputStart
	4.	对每一帧，使用SS_InputFrame输入到语音点歌模块。帧长不要求。但是必须是连续帧。不得跳帧。
	5.	结束时使用SS_SearchSongs进行检索。获得前n名歌曲id
	6.	循环调用SS_GetSongName获得前n名歌曲名

二.异步方式(强烈推荐)
	双线程方式。每帧输入，先调用特征提取函数提取13维特征，然后由使用者放入一个fifo。
	识别过程为另一个线程去读取特征fifo，一旦有特征进入则进行辨识。
	这样可以最大化CPU效率又不用担心来不及做。只要fifo开得足够大(允许输入15秒钟也只需开52k即可)而且可以灵活的优化结尾空白时间的识别
	缺点是需要使用者写比较多的程序去控制，比较复杂。
	具体步骤:
	1.	SS_LoadFileData载入模型和歌曲文件。
	2.	SS_Init初始化模块。注意这里要指定英文还是中文系统。
		切记第一个参数设为-1，所有歌曲均实时识别。并建立识别线程。
	3.	每次新的点歌开始前，调用SS_InputStart
	4.	对每一帧，调用SS_FrameEncode进行特征提取成一个13个int的数组。并存入一个fifo。
		注意，对于中文系统，32k下，一帧长度为800sample.
		对于英文系统，每帧长度都为480sample.
	5.	对识别线程，不停调用SS_InputCharacter去进行特征的识别。
	6.	全部帧识别结束后使用SS_SearchSongs进行检索。获得前n名歌曲id
	7.	循环调用SS_GetSongName获得前n名歌曲名
	8.	特别的，对用户朗读完毕需要等待空白时间的，空白时间不管加几帧不会影响结果。因此对于识别过程比用户输入慢的，当空白时间完毕，识别过程只需进行到用户有效输入时间完毕即可。

PS:	由于各系统不同，需要外部定义系统malloc和free函数：SysAppMalloc，SysFree。以及文件指针格式，打开以及读写方式
***********************************************************/


///////////////////////////////////////////////////////////////////// 
// 
// SS_LoadFileData:
//	从参数路径读入模型数据和字典数据。
// input:
//	modelfn	:	模型数据路径
//	wordfn	:	词库数据路径
//	dictfn	:	总字典路径。用于往字库添加歌曲用，没有此需求的将此参数设为NULL即可。不影响识别使用。
// output:
//	1		:	完全读入成功
//	2		:	没有字典数据
//	负数	:	各种出错信息
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_LoadFileData(char *modelfn, char *wordfn, char *dictfn);

///////////////////////////////////////////////////////////////////// 
// 
// SS_DestroyFileData:
//	释放整个已经load入内存的语音点歌资源。
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_DestroyFileData(void);

///////////////////////////////////////////////////////////////////// 
// 
// SS_Init:
//	初始化函数。在运行一切前必须初始化。
// input:	
//	in_time_song_num	:	根据系统决定多少歌是实时匹配，多少歌留到最后匹配。假如输入-1，则所有歌实时匹配
//	max_input_time	:	假如有歌不是实时匹配，则需要指定系统允许的最大输入时间。单位为毫秒。假如所有歌实时匹配，这个参数不会起到任何作用。
//	EnglishSystem		:	决定将要使用的语音系统是不是英语系统。1则为英语，0则为汉语。
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_Init(int in_time_song_num, int max_input_time, int EnglishSystem);

///////////////////////////////////////////////////////////////////// 
// 
// SR_SpeechSearchFinish:
//	系统结束释放资源。
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_Finish(void);

///////////////////////////////////////////////////////////////////// 
// 
// SS_InputStart:
//	每次新搜索一次语音点歌前需做的初始化
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_InputStart(void);

///////////////////////////////////////////////////////////////////// 
// 
// SS_InputFrame:
//	输入一帧数据
//
// input : 
// 	*frame 	: 一帧数据
//	length	: 帧长度
//	channel	: 输入通道数
// 
///////////////////////////////////////////////////////////////////// 
extern int 	SS_InputFrame(short *frame, int length, int channel);

///////////////////////////////////////////////////////////////////// 
// 
// SS_SearchSongs:
//	输入完毕开始检测歌曲
//
// input : 
// 	bestsongnum	: 需要的最佳答案个数
//	bestsong		: 存放最佳答案歌曲id的buffer，至少需要int[bestsongnum]
//	max_distance	: 存放最佳答案匹配度的buffer，用来调试用。可以提供NULL。
// 
///////////////////////////////////////////////////////////////////// 
extern int	SS_SearchSongs(int bestsongnum, int *bestsong, int *max_distance);

///////////////////////////////////////////////////////////////////// 
// 
//SS_GetSongName:
//	获得对应id的歌曲名
// input:
//	songid	:	歌曲id
// output:
//	char*	:	歌曲名字符串头指针
// 
///////////////////////////////////////////////////////////////////// 
extern char *SS_GetSongName(int songid);

///////////////////////////////////////////////////////////////////// 
// 
// SS_FrameEncode:
//	提取一帧数据的13维MFCC+能量系数。
//	中文识别每帧输入数据必须为800sample。
//	醒目醒目注意：假如是英语系统，第一帧必须输入800sample，以后各帧输入长度必须为480sample。这个和汉语识别不同
// 
// Parameters: 
// input:
//	short *frame	:	输入有效数据的首地址。
//	int samplestep	:	每两个有效sample之间的距离。单通道则为1。双通道则为2。
//  关于以上两个参数的配合。因为语音点歌一般只针对一个通道起作用，因此实际只允许输入一个通道。
//  双通道或多通道的数据，将其首地址设到该通道第一个sample地址，然后将samplestep设为通道数即可。
//  !!!!! 注意::: 出于节省内存的需要，此函数会改变frame里面的值。假如此函数后frame还将做其他用途，请另开buffer专门送这个函数。
//
// output:
//	int *mfcc	: 特征存放内存。至少为13维。
//
///////////////////////////////////////////////////////////////////// 
extern int SS_FrameEncode(short *frame, int *mfcc, int samplestep);


///////////////////////////////////////////////////////////////////// 
// 
// SS_InputCharacter:
//	输入一帧数据的特征系数到识别系统
//
// input : 
// 	*mfcc 	: 一帧数据的13维特征系数
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_InputCharacter(int *character);

///////////////////////////////////////////////////////////////////// 
// 
// SS_AddOneWord:
//	往内存加入一个单词。
//	!!!注意:  该功能必须在SS_Init之前或者SS_Finish之后做!!即语音点歌功能初始化以后就不能做了。否则会退出。
// input:
//	word	:	要加的单词名字
//	dictpath	:	字典数据路径
// output:
//	1		:	加入成功
//	2		:	已载入数据中已有完全相同单词，不加入
//	负数	:	各种出错信息
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_AddOneWord(char* word, char *dictpath);


///////////////////////////////////////////////////////////////////// 
// 
// SS_SaveWordFile:
//	保存词库文件到参数路径
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_SaveWordFile(char *FilePath);


/*===================================================================
 
								出错信息
#define	ERROR_DATA_FILE_NOT_EXIST		-1000		//data数据不存在
#define	ERROR_DICT_FILE_NOT_EXIST		-1001		//dict数据不存在
#define	ERROR_DATA_FILEHEAD_ERROR		-1050		//data数据文件头不对
#define	ERROR_WORD_FILEHEAD_ERROR		-1051		//data数据文件头不对
#define	ERROR_DICT_FILEHEAD_ERROR		-1052		//data数据文件头不对
#define	ERROR_WORD_NUMBER_0				-1053		//load词库时词库里词语个数为0
#define	ERROR_MALLOC_FAILED_STATUSLIST	-1010		//coodinateword时空间不够malloc statuslist.
#define	ERROR_MALLOC_FAILED_COODINATE	-1011		//coodinateword时空间不够malloc 计算空间.
#define	ERROR_MALLOC_FAILED_CALC			-1012		//HMM空间不够
#define	ERROR_MALLOC_FAILED_MODEL		-1013		//载入模型空间不够.
#define	ERROR_MALLOC_FAILED_MAXDIS		-1014		//最后识别时maxdis空间不够
#define	ERROR_FAILED_FINISH				-1020		//finish失败，很可能没有正常init
#define	ERROR_FAILED_FREE_DATA			-1021		//data释放失败
#define	ERROR_INPUT_TIME_EXCEED			-1022		//输入时间超过规定时间
#define	ERROR_NODATA					-1030		//初始化speech时，还未成功载入数据模型文件导致无法初始化
#define	ERROR_INPUT_TOO_SHORT			-1031		//语音过短无法判断(小于100ms)
#define	ERROR_READ_FILE_DATA				-1040		//读文件数据错误，可能文件错误也可能读到一半拔盘
#define	ERROR_WRITE_FILE_DATA			-1041		//写文件数据错误，可能文件错误也可能读到一半拔盘
#define	ERROR_DICT_WORD_NOT_EXIST		-1060		//要添加的id号在字典文件中不存在
#define	ERROR_ADD_WORD_SYSTEM_CLASH	-1061		//添加词语时没有退出语音点歌系统，资源冲突
#define	ERROR_DICT_WORD_DATA_ERROR		-1062		//字典文件很可能数据发生错误
 
===================================================================*/ 

//=================================用户层封装函数=================================

///////////////////////////////////////////////////////////////////// 
// 
// SS_Creat:
//	建立语音点歌模块
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_Creat(void);

///////////////////////////////////////////////////////////////////// 
// 
// SS_Destroy:
//	释放语音点歌模块
// 
///////////////////////////////////////////////////////////////////// 
extern int SS_Destroy(void);


#ifdef _cplusplus
//}
#endif

#endif