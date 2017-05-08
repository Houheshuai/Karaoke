#ifndef SORT_H
#define SORT_H

#define SORT_DESCEND	0
#define SORT_ASCEND	1
#define SORT_BIG_ENDIAN	0x10
#define SORT_SMALL_ENDIAN	0x00

typedef int (*merge_sort_cb_t)(unsigned char*, unsigned char*, int);

typedef struct 
{
	unsigned int   sort_offset;
	unsigned int   record_len;
	unsigned int   record_num;
	unsigned short sort_len;
	unsigned char  sort_type;   // 0: sort descending, 1: sort ascending
							// 0x10 : big endian, 0x00 : small endian

	merge_sort_cb_t cb;
	int							cb_para;
	
}SORT_PARA; 

#ifdef __cplusplus
extern "C" {
#endif

extern void merge_sort(char * list_p, char * swap_list_p, SORT_PARA *sort_para);

#ifdef __cplusplus
}
#endif

#endif

