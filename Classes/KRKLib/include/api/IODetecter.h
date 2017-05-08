#ifndef _IO_DETECT_H_
#define _IO_DETECT_H_

#include <k_global.h>
#include <lib/ezbase/ez_notify.h>

typedef enum
{
	IODetecter_Notify_None = 0,
	IODetecter_Notify_LowLevel,
	IODetecter_Notify_HighLevel,
	IODetecter_Notify_FallingEdge,
	IODetecter_Notify_RisingEdge,
}IODetecter_Notify_et;

typedef struct tagIODetecter_t IODetecter_t;
typedef int (*IODetecter_Callback_t)(NotifyEventArgs_t*);
typedef ezNotify_t (*IODetecter_Update_t)(IODetecter_t*, unsigned int);

typedef struct 
{
	int IO_id;																	// gpio ID
	int time;																		// circle time to detect gpio
	void* owner;
	
	IODetecter_Callback_t cb_ioevent;
} IODetecter_Para_t;


struct tagIODetecter_t
{
	ezNotifyHandle_t Notify;
	krk_os_task_t task;

	int last_state;
	int cur_state;

	int IO_id;																	// gpio ID
	int time;																		// circle time to detect gpio
	void* owner;

	IODetecter_Update_t Update;
};

#ifdef __cplusplus
extern "C" {
#endif

extern IODetecter_t* IODetecter_Init(IODetecter_Para_t* para);
extern void IODetecter_Deinit(IODetecter_t *p_IODetecter);

#ifdef __cplusplus
}
#endif

#endif
