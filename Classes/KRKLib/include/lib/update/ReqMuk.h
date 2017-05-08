#ifndef _REQMUK_H_
#define _REQMUK_H_

#define MUK_MARK_NAME_LEN						4
#define MUK_MARK_FIX_LEN						8
#define MUK_DATA_BUF_LEN						0x10000

typedef struct tag_muk_mark_t muk_mark_t;
typedef struct tag_muk_t muk_t;
typedef struct tag_mark_head_t mark_head_t;
typedef struct tag_muk_req_para_t muk_req_para_t;

#ifdef WIN32
#pragma pack(push,1)
#elif (defined _ARMRVDS_)
__packed
#else
#pragma pack(1)
#endif

struct tag_mark_head_t
{
	unsigned int	EncodeFlag;			//0表示没有，其余表示加密的类型
	unsigned char	EncodeKey[128];		//对于需要自解密的歌曲保留使用
	unsigned int	Buffer_Len;			//数据的长度
	unsigned int	Buffer_Offset;		//具体数据相对于标签头的偏移
	unsigned int	Buffer_Real_Len;	//加密之前的实际长度
};

#ifdef WIN32
#pragma pack(pop)
#elif (defined _ARMRVDS_)
#else
#pragma pack()
#endif

struct tag_muk_mark_t
{
	char name[MUK_MARK_NAME_LEN];
	unsigned int len;

	char *data;
	unsigned int data_len;	

	char *xdata;
	
	muk_mark_t *next;
};

struct tag_muk_t
{
	char path[128];
	unsigned int mark_num;
	muk_mark_t head;
	
	unsigned int data_len;
	char *data_buf;
};

struct tag_muk_req_para_t
{
	int req_charset;
	int default_chaset;
	int cn_firstword;
};

typedef struct 
{
	muk_t* muk;
	mark_head_t* mark;
	
} reqMukMark_t;

#ifdef __cplusplus
extern "C" {
#endif

extern	int Muk_ReqData(req_table_t *prt,const char *dir_path, muk_req_para_t* para);

extern reqMukMark_t* Muk_ReqMark(const char *mukfile, const char* mark);

extern void Muk_RelMark(reqMukMark_t* req);

#ifdef __cplusplus
}
#endif

#endif
