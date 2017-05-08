#ifndef _KRK_MALLOC_H_
#define _KRK_MALLOC_H_

#define KRK_MEM_LEAK_DBG		1

/* memory node in dynamic malloc */
struct heap_t {
	unsigned long size;
	unsigned long gap;
	unsigned long mask;
#if KRK_MEM_LEAK_DBG	
	char					file[256];
	int					lineno;
#endif	
	struct heap_t *prev;
	struct heap_t *next;
};

#ifdef __cplusplus
extern "C" {
#endif 

extern unsigned char krk_heap_init(unsigned long start, unsigned long bytes, unsigned char id);
extern unsigned long krk_heap_freespace(unsigned char id);
extern int krk_heap_good(unsigned char id);
extern unsigned char * krk_malloc(unsigned long bytes, unsigned char id, char* file, int lineno);
extern void krk_free(unsigned long addr, unsigned char id, char* file, int lineno);
extern int krk_check_mem_errors(unsigned char id);

#ifdef __cplusplus
}
#endif 

#endif
