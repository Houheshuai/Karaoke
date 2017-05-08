#include "ll.h"
#include "player.h"
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

/* linked list */
struct ll {
	struct ll_item	*first;
	struct ll_item	*last;
	unsigned int	size;
	unsigned int	limit;
	ll_func_destroy	f_destroy;

	int		blocked;
	unsigned char		free, empty, drain;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
};

/* linked list item */
struct ll_item {
	struct ll_item	*prev;
	struct ll_item	*next;
	void		*data;
};

/* lock the linked list to add ONE item */
unsigned char _ll_write_lock(ll_t *ll);

/* unlock the linked list */
void _ll_write_unlock(ll_t *ll);


/* Internal remove & free item function */
void _ll_remove_item(ll_t *ll, ll_item_t *item) {
	if (ll->first == item) ll->first = item->next;
	if (ll->last  == item) ll->last  = item->prev;
	if (item->prev) item->prev->next = item->next;
	if (item->next) item->next->prev = item->prev;
	if (ll->f_destroy) ll->f_destroy(item->data);
	ll->size--;
	free(item);
}

/* Internal emtpy function */
void _ll_empty(ll_t *ll) {
	ll_item_t *item, *last;
	if (ll->first) {
		item = ll->first;
		while(item) {
			if (ll->f_destroy)
				ll->f_destroy(item->data);
			last = item;
			item = item->next;
			free(last);
		}
	}
	ll->size	= 0;
	ll->first	= NULL;
	ll->last	= NULL;
	ll->empty	= 1;
}

ll_t *ll_new(ll_func_destroy f_destroy, unsigned int limit) {
	ll_t *ll	= (ll_t *)calloc(sizeof(ll_t), 1);
	ll->f_destroy	= f_destroy;
	ll->limit	= limit;

	pthread_mutex_init(&ll->mutex, NULL);
	pthread_cond_init (&ll->cond, NULL);

	return ll;
}

unsigned char _ll_write_lock(ll_t *ll) {
	pthread_mutex_lock(&ll->mutex);

	/* Block until there is room in the list or the ll is freed */
	if (ll->limit > 0)
		while(ll->size == ll->limit) {
			++ll->blocked;
			pthread_cond_wait(&ll->cond, &ll->mutex);
			/* If we are being freed */
			if (ll->free || ll->empty) {
				ll->empty = 0;
				--ll->blocked;
				pthread_cond_broadcast(&ll->cond);
				pthread_mutex_unlock(&ll->mutex);
				return 0;
			}
			--ll->blocked;
		}

	return 1;
}

void _ll_write_unlock(ll_t *ll) {
	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);
}

void ll_empty(ll_t *ll) {
	pthread_mutex_lock(&ll->mutex);
	_ll_empty(ll);
	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);
}

void ll_free(ll_t *ll) {
	pthread_mutex_lock(&ll->mutex);
	_ll_empty(ll);

	/* Tell all blocked threads to free and wait until they are done */
	ll->free = 1;
	pthread_cond_broadcast(&ll->cond);
	while((ll->blocked) && (pthread_cond_wait(&ll->cond, &ll->mutex) != 0)) {}
	pthread_mutex_unlock(&ll->mutex);

	pthread_mutex_destroy(&ll->mutex);
	pthread_cond_destroy (&ll->cond);
	free(ll);
}

void ll_push(ll_t *ll, void *data) {
	ll_item_t *item;

	item = (ll_item_t *)malloc(sizeof(ll_item_t));
	item->data = data;
	item->next = NULL;

	if (!_ll_write_lock(ll)) {
		free(item);
		if (ll->f_destroy) ll->f_destroy(data);
		return;
	}

	item->prev = ll->last;
	if (ll->last  ) ll->last->next	= item;
	if (!ll->first) ll->first	= item;
	ll->last = item;
	ll->size++;

	_ll_write_unlock(ll);
}

void ll_unshift(ll_t *ll, void *data) {
	ll_item_t *item;

	item = (ll_item_t *)malloc(sizeof(ll_item_t));
	item->data = data;
	item->prev = NULL;

	if (!_ll_write_lock(ll)) {
		free(item);
		if (ll->f_destroy) ll->f_destroy(data);
		return;
	}

	item->next = ll->first;
	if (ll->first) ll->first->prev	= item;
	if (!ll->last) ll->last		= item;
	ll->first = item;	
	ll->size++;

	_ll_write_unlock(ll);
}

void ll_insert_after(ll_t *ll, void *after, void *data, unsigned char lock) {
	ll_item_t *search, *item;

	item = (ll_item_t *)malloc(sizeof(ll_item_t));
	item->data = data;
	item->next = NULL;

	if (lock)
		if (!_ll_write_lock(ll)) {
			free(item);
			if (ll->f_destroy) ll->f_destroy(data);
			return;
		}

	//find the point to insert the item
	search = ll->first;
	while(search && (search->data != data))
		search = search->next;

	//if we didnt find it, then append it
	if (!search) {
		item->prev = ll->last;
		if (ll->last  ) ll->last->next	= item;
		if (!ll->first) ll->first	= item;
		ll->last = item;
	} else {
		item->prev	= search;
		item->next	= search->next;
		search->next	= item;
		if (ll->last == search)
			ll->last = item;
	}
	ll->size++;

	if (lock) _ll_write_unlock(ll);
}

void* ll_pop(ll_t *ll) {
	ll_item_t	*item;
	void		*ret;

	pthread_mutex_lock(&ll->mutex);
	/* Block until there is an item to shift */
	while(!ll->first) {		
		if ((ll->free) || (ll->drain)) {
			pthread_mutex_unlock(&ll->mutex);
			return NULL;
		} else
			pthread_cond_wait(&ll->cond, &ll->mutex);
	}

	item		= ll->last;
	ll->last	= item->prev;
	if (ll->last)	ll->last->next	= NULL;
	else		ll->first	= NULL;
	ll->size--;

	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);

	ret = item->data;
	free(item);
	return ret;
}

void* ll_shift(ll_t *ll) {
	ll_item_t	*item;
	void		*ret;

	pthread_mutex_lock(&ll->mutex);
	/* Block until there is an item to shift */
	while(!ll->first) {		
		if ((ll->free) || (ll->drain)) {
			pthread_mutex_unlock(&ll->mutex);
			return NULL;
		} else
			pthread_cond_wait(&ll->cond, &ll->mutex);
	}

	item		= ll->first;
	ll->first	= item->next;
	if (ll->first)	ll->first->prev	= NULL;
	else		ll->last	= NULL;
	ll->size--;

	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);

	ret = item->data;
	free(item);
	return ret;
}

unsigned char ll_foreach(ll_t *ll, unsigned char reverse, ll_func_foreach f_foreach, void *loop_data) {
	ll_item_t	*item, *next;
	unsigned char		remove, ret;

	ret = 0;
	pthread_mutex_lock(&ll->mutex);
	if (reverse) {
		item = ll->last;
		while(item) {
			next	= item->prev;
			remove	= 0;
			if (!(ret = f_foreach(item->data, &remove, loop_data))) {
				if (remove) _ll_remove_item(ll, item);
				break;
			}
			if (remove) _ll_remove_item(ll, item);
			item = next;
		}
	} else {
		item = ll->first;
		while(item) {
			next	= item->next;
			remove	= 0;
			if (!(ret = f_foreach(item->data, &remove, loop_data))) {
				if (remove) _ll_remove_item(ll, item);
				break;
			}
			if (remove) _ll_remove_item(ll, item);
			item = next;
		}
	}
	pthread_mutex_unlock(&ll->mutex);

	return ret;
}

unsigned int ll_size(ll_t *ll) {return ll->size;}
unsigned char ll_isempty(ll_t *ll) {return ((!ll->first) && (!ll->last));}

void* ll_next(ll_t *ll) {
	ll_item_t	*item;
	void		*ret;

	pthread_mutex_lock(&ll->mutex);	
	if (!ll->first) {
		return NULL;
		pthread_mutex_unlock(&ll->mutex);
	}

	/* Shift the list left one */
	if (ll->last != ll->first) {
		item		= ll->first;
		ll->first	= ll->first->next;
		ll->first->prev	= NULL;
		ll->last->next	= item;
		ll->last	= item;
		ll->last->next	= NULL;
	}

	ret = ll->first->data;
	pthread_mutex_unlock(&ll->mutex);

	return ret;
}

void ll_drain(ll_t *ll) {
	pthread_mutex_lock(&ll->mutex);	
	ll->drain = 1;
	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);
}

void ll_plug(ll_t *ll) {
	pthread_mutex_lock(&ll->mutex);	
	ll->drain = 0;
	pthread_cond_broadcast(&ll->cond);
	pthread_mutex_unlock(&ll->mutex);
}

