#ifndef _H_ARRAY_
#define _H_ARRAY_

typedef struct array array_t;

array_t* array_new();
void array_free(array_t *a);
void array_push(array_t *a, void* data);
void* array_pop(array_t *a);
void array_unshift(array_t *a, void *data);
void* array_shift(array_t *a);
void* array_get(array_t *a, unsigned int index);
void array_del(array_t *a, unsigned int index, unsigned int count);
void array_ins(array_t *a, unsigned int index, void* data);
void array_empty(array_t *a);
unsigned int array_count(array_t *a);

#endif
