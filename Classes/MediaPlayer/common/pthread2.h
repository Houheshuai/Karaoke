#ifndef _PTHREAD_2_H
#define _PTHREAD_2_H

#include <pthread.h>

typedef struct pthread_rwlock2
{
	int active_readers; /* -1 when writer lock locked, >0 when read lock locked */
	int pending_readers;
	int pending_writers;
	pthread_mutex_t mutex;
	pthread_cond_t	ok_to_read;
	pthread_cond_t ok_to_write;
} pthread_rwlock_t2 ;

int pthread_rwlock_init2(pthread_rwlock_t2 * lock, void *attr);

int pthread_rwlock_destroy2(pthread_rwlock_t2 * lock);

int pthread_rwlock_rdlock2(pthread_rwlock_t2 * lock);

int pthread_rwlock_wrlock2(pthread_rwlock_t2 * lock);

int pthread_rwlock_unlock2(pthread_rwlock_t2 * lock);

#endif
