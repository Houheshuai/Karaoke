#ifndef _ALPHA_SORT_H_
#define _ALPHA_SORT_H_

#define krk_lenof(x)		(sizeof(x)/sizeof(*x))

typedef struct
{
	char *src;
	char *sort;
	char *utf8;
}alpha_ss;

typedef struct alpha_sort_list_t alpha_sl;
struct alpha_sort_list_t			//排序表
{
	int charset;					//字符集
	int lan_type;					//语言类型
	int alpha_num;					//字母个数
	short alpha_list[64];			//字母表
	int exalpha_num;				//重音标志的字母个数
	short exalpha_map[32];			//重音标志的字母
	char sort_map[32];				//排序映射表
	int sort_map_num;				//排序表集合的个数
};

#ifdef __cplusplus
extern "C" {
#endif

int alpha_hasmap(int lan_type);
int alpha_getsp(const char *src_str,char *dst_str,int lan_type,int dst_num);
int alpha_getfp(const char *src_str,char *dst_str,int lan_type,int dst_num);
int alpha_sortmap(const char *src_str,char *dst_str,int lan_type,int dst_num);

#ifdef __cplusplus
}
#endif

#endif

