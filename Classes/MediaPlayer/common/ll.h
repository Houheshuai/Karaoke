#ifndef _H_LINKED_LISTS_
#define _H_LINKED_LISTS_
#include "mediaplayer.h"

/* thread safe linked list functions */
typedef	void (*ll_func_destroy)(void* data);
typedef unsigned char (*ll_func_foreach)(void* data, unsigned char *remove, void* loop_data);
typedef struct ll_item	ll_item_t;
typedef struct ll	ll_t;

/* Create a new linked list, optional destroy function for the contained data, limited to the specified size (0 = unlimited) */
ll_t* ll_new(ll_func_destroy f_destroy, unsigned int limit);

/* Free the linked list */
void ll_free(ll_t *ll);

/* Empty the linked list */
void ll_empty(ll_t *ll);

/* Push a new item onto the end of the list */
void ll_push(ll_t *ll, void *data);

/* Shift an item off the front of the list */
void* ll_shift(ll_t *ll);

/* Pop an item off the front of the list */
void* ll_pop(ll_t *ll);

/* Unshift an item onto the front of the list */
void ll_unshift(ll_t *ll, void *data);

/* insert an item into the list */
void ll_insert_after(ll_t *ll, void *after, void *data, unsigned char lock);

/* Itterate the items in the list */
unsigned char ll_foreach(ll_t *ll, unsigned char reverse, ll_func_foreach f_foreach, void *loop_data);

/* Return the number of items in the ll */
unsigned int ll_size(ll_t *ll);

/* Return if the ll is empty */
unsigned char ll_isempty(ll_t *ll);

/* shift left one and return the first element (runs in a circle) */
void* ll_next(ll_t *ll);

/* Tell the ll that we want to drain its contents and not block when empty */
void ll_drain(ll_t *ll);

/* Tell the ll to plug the drain again */
void ll_plug(ll_t *ll);


#endif

