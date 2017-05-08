/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : os.h
** Revision : 1.00											
**																	
** Description: linux os
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
*/


#ifndef _OS_H_
#define _OS_H_

#include <pthread.h>
#include <semaphore.h>

/* TODO: OS SCHEDULE LOCK API */
#define KRK_OS_ENABLE_SCHEDULE()	
#define KRK_OS_DISABLE_SCHEDULE()	
/* TODO: END */

/* TODO: OS CRITICAL REGION PROTECT API */
#define KRK_OS_ENTER_CRITICAL(cpu_sr)		krk_os_enter_critical()
#define KRK_OS_EXIT_CRITICAL(cpu_sr)		krk_os_exit_critical()
/* TODO: END */

/* TODO: OS THREAD ENTRY DEFINE */
#define KRK_TASK_ENTRY_ARG		void *
#define KRK_TASK_RET_TYPE		void *
#define KRK_TASK_RET_VAL	NULL
#define KRK_TASK_GET_ARGV(argv)	argv

/* 
* following parameter only use in fake multi-thread platform, 
* if you use real thread, don't need to change it 
*/
#define KRK_OS_LOCDEF
#define KRK_OS_INIT_LOOP    1
#define KRK_OS_LOOP         1
/* TODO: END */

/* TODO: PROVITE A MICRO-SECOND TIMER */
#define krk_curTime()		GetTickCount()
/* TODO: END */

/* TODO: OS SPECIAL HEAP MALLOC API, NORMALLY IT USES COMMON HEAP MALLOC */
#define krk_os_malloc(a)		malloc(a)
#define krk_os_free(a)			free(a)
/* TODO: END */

/* TODO: PROVITE A MILLI-SECOND TIMER IF YOU NEED IT */
#define KRK_SYSTIMER_X_US		       
#define KRK_SYSTIMER_US_TO_MS(us)		
/* TODO: END */

/* TODO: TYPE OF OS THREAD ENTRY FUNCTION */
typedef void* (*krk_os_task_entry_t)(void *);
/* TODO: END */

/* TODO: TYPE OF OS THREAD */
#define krk_os_task_t pthread_t
/* TODO: END */

/* TODO: TYPE OF OS MSG QUEUE */
#define krk_os_msgqueue_t int
/* TODO: END */

/* TODO: TYPE OF OS SEMAPHORE */
#define krk_os_sema_t sem_t
/* TODO: END */

/* TODO: TYPE OF OS TIMER */
#define krk_os_timer_t int
/* TODO: END */

/* TODO: TYPE OF OS TIMER EXPIRE FUNCTION */
typedef int(*	krk_os_timer_expire_t)(int);
/* TODO: END */

/* TODO: TYPE OF OS TIMER TICK DATA, NORMALLY IT'S INTEGER */
#define krk_os_timetick_t int
/* TODO: END */

#define KRK_OS_RET_SUCC	0
#define KRK_OS_RET_FAIL	-1

#define KRK_OS_NOWAIT		0
#define KRK_OS_WAIT		    -1

#define KRK_OS_TIMER_ENABLE		0
#define KRK_OS_TIMER_DISABLE		1

/* TODO: TASK PRIORITY CONFIG */
typedef enum
{
	KRK_TASK_PRIORITY_HIGHHIGH = 1,			//higher
	KRK_TASK_PRIORITY_HIGH = 2,					//high
	KRK_TASK_PRIORITY_HIGHMID = 3,			//high~middle
	KRK_TASK_PRIORITY_MID = 4,						//middle
	KRK_TASK_PRIORITY_MIDLOW = 5,			//middle~low
	KRK_TASK_PRIORITY_LOW = 6,					//low
	KRK_TASK_PRIORITY_LOWLOW = 7,			//lower
	
} krk_task_priority_t;
/* TODO: END */

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: ALL THE FOLLOWING OS API MUST BE PROVITED */

/*
* win32 critical section rountine
*/
extern void krk_os_enter_critical(void);

extern void krk_os_exit_critical(void);

extern unsigned long krk_curTime_us(void);

/*
* This function create a new task
*
* @param Entry - task entry function
* @param TaskName - Task Name string 
* @param Prio - Task priority
* @param StackSize - Task allocated stack size 
* @param inData - input data to task
* @return - task pointer
*/
extern int krk_os_task_create(krk_os_task_t *task, 
							const char *TaskName, 
							krk_os_task_entry_t Entry, 
							int StackSize,
							int Prio,
							void *inData);

/*
* This function Delete a task
*
* @param Task - Task handle 
* @return - 0 success, 1 fail
*/
extern int krk_os_task_destroy(krk_os_task_t *Task, void *Reserved);

/*
* This function suspend a task
*
* @param task - task handle
*		param - reserved
* @return - 0 success, 1 fail
*/
extern int krk_os_task_suspend(krk_os_task_t * task, void *param);

/*
* This function resume a task
*
* @param task - task handle
* @return - 0 success, 1 fail
*/
extern int krk_os_task_resume(krk_os_task_t * task);

/*
* This function Delete a task in task entry function
*
* @return - 0 success, 1 fail
*/
extern int krk_os_task_selfdel(void);

/*
* This function check a task delete request 
*
* @return - 0 success, 1 fail
*/
extern int krk_os_task_del_req(void);

/*
* This function return task thread id
*
* @param task - task handle
* @return - thread id
*/
extern int krk_os_task_gettid(krk_os_task_t * task);

extern int krk_os_task_change_prio(int oldprio, int newprio);

/*
* This function create a new Queue
*
* @param QueueName - message queue name string
* @param MsgCount - maximum number of message in Queue
* @return - message queue pointer
*/
extern int krk_os_msgqueue_create(krk_os_msgqueue_t *MsgQ, const char *QueueName, 
								int MsgCount, int MsgSize);

/*
* This function Delete a message queue
*
* @param Queue - Queue handle 
* @return - 0 success, 1 fail
*/
extern int krk_os_msgqueue_destroy(krk_os_msgqueue_t *MsgQ, void *Reserved);


/*
* This function Accept a message from queue
*
* @param Queue - Queue handle 
* @param Pend - 1: pend task if no message, 0: not pend 
* @return - 0 success, 1 fail
*/
extern int krk_os_msgqueue_query(krk_os_msgqueue_t *Queue, void *Msg, int MsgSize, int Wait, void *Reserved);

/*
* This function send a message from queue
*
* @param Queue - Queue handle 
* @return - 0 success, 1 fail
*/
extern int krk_os_msgqueue_send(krk_os_msgqueue_t *Queue, void *Msg, int MsgSize, int Wait, void *Reserved);

/*
* This function create a new Semaphore
*
* @param SemaName - semaphore name string
* @return - Semaphore pointer
*/
extern int krk_os_sema_create(krk_os_sema_t *Sema, const char *SemaName, int InitCount, void *Reserved);

/*
* This function delete a Semaphore
*
* @param Sema - semaphore pointer
* @return - 0 success, 1 fail
*/
extern int krk_os_sema_destroy(krk_os_sema_t *Sema, void *Reserved);

/*
* This function pend a Semaphore
*
* @param Sema - semaphore pointer
* @return - 0 success, 1 fail
*/
extern int krk_os_sema_pend(krk_os_sema_t *Sema, int Wait, void *Reserved);

/*
* This function post a Semaphore
*
* @param Sema - semaphore pointer
* @return - 0 success, 1 fail
*/
extern int krk_os_sema_post(krk_os_sema_t *Sema, void *Reserved);

/*
* This function query a Semaphore
*
* @param Sema - semaphore pointer
* @return - count of semaphore
*/
extern int krk_os_sema_query(krk_os_sema_t *Sema, void *Reserved);

/*
* This function switch the task to sleep mode for time of "ticks"
* ticks is the os tick, 0.5ms for samsung and 1ms for amlogic os
*
* @param Ticks - os tick time, 1ms 
* @param Param - input data, most of time it's useless
* @return - none
*/
extern void krk_os_sys_sleep(krk_os_timetick_t Ticks, void *Param);

extern int krk_os_timer_create( krk_os_timer_t *timer,
					char *name,
					krk_os_timer_expire_t func,
					krk_os_timetick_t init_time,
					krk_os_timetick_t resched_time,
					int enable, 
					void *reserved);

extern int krk_os_timer_kill( krk_os_timer_t *timer, void *reserved);

extern int krk_os_timer_control( krk_os_timer_t *timer,	int enable, void *reserved );

extern int krk_os_timer_reset( krk_os_timer_t *timer,
                    krk_os_timer_expire_t func,
					krk_os_timetick_t init_time,
					krk_os_timetick_t resched_time,
					int enable, 
					void *reserved);

extern void krk_os_init(void);

extern void krk_os_deinit(void);

/* TODO: END */

#ifdef __cplusplus
}
#endif 

#endif

