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
struct alpha_sort_list_t			//�����
{
	int charset;					//�ַ���
	int lan_type;					//��������
	int alpha_num;					//��ĸ����
	short alpha_list[64];			//��ĸ��
	int exalpha_num;				//������־����ĸ����
	short exalpha_map[32];			//������־����ĸ
	char sort_map[32];				//����ӳ���
	int sort_map_num;				//������ϵĸ���
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

