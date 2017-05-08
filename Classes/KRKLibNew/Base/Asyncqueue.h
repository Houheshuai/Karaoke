/* ===========================================
	异步创建物件 队列管理
============================================= */

#ifndef _ASYNCQUEUE_H
#define _ASYNCQUEUE_H

#define 	tAsyncQueue	void			// 异步队列
#define 	tAsyncItem	void			// 物件管理构件

typedef enum tarAsyncState	//		物件创建状态
{							//					Current State		Next State
	AS_IDEL,				//	空闲			X					
	AS_WAITCREATE,			//	等待创建		X					X
	AS_CREATING,			//	创建中			X					
	AS_CREATED,				//	创建完成		X
	AS_WAITDESTROY,			//	等待销毁							X				 
	AS_DESTROYING			//	销毁中			Note: Ver 1.00 destroy at once no destroying state
} tAsyncState;

/* ----------------------------------------
		创建 异步队列
	参数：
		ItemNum									队列最大个数
		InputItemSize							物件创建委托方法的输入的参数长度
		void *(*pItemCreate)(void *pInput)		物件创建委托方法
		void (*pItemDestroy)(void *pOutput)		物件销毁委托方法
	输出 队列指针
---------------------------------------- */ 
tAsyncQueue *AllocAsyncItemCreateQueue(int ItemNum, int InputItemSize, void *(*pItemCreate)(void *pInput), void (*pItemDestroy)(void *pOutput));

/***
	物件建立完成 CallBack
***/
int AIC_SetCreateCallback(void (*p)(tAsyncItem *pItem), tAsyncQueue *pAsyncQueue);

/***
	物件销毁建立完成 CallBack
***/
int AIC_SetDestroyCallback(void (*p)(tAsyncItem *pItem), tAsyncQueue *pAsyncQueue);

/* ----------------------------------------
	队列中 请求创建物件
---------------------------------------- */ 
tAsyncItem *CreateAsyncItem(void *pInput, tAsyncQueue *pAsyncQueue, int pri);

/* ----------------------------------------
	队列中 请求销毁物件
---------------------------------------- */ 
int DestroyAsyncItem(tAsyncItem *pItem, tAsyncQueue *pAsyncQueue);

/* ----------------------------------------
	队列中 查询物件创建状态
---------------------------------------- */ 
tAsyncState GetAsyncItemState(tAsyncItem *pItem);

/* ----------------------------------------
	得到物件数据
---------------------------------------- */ 
void *GetAsyncItemData(tAsyncItem *pItem);

/* ----------------------------------------
	释放异步队列：
	参数:
		异步队列:			pAsyncQueue
---------------------------------------- */
int FreeAsyncItemCreateQueue(tAsyncQueue *pAsyncQueue);


#if 0			// Sample
tAsyncQueue *queue;
tAsyncItem *item[10];

void *testCreat(void *pinput)
{
	int *pInt;
	char *pOut;
	int i, j;

	pInt = (int *) pinput;

	pOut = malloc(100);
	if (pOut)
	{
		sprintf(pOut, "OUT TEST = %d <%p>", *pInt, pOut );
	}
	return pOut;
}

void testDestroy(void *pOut)
{
	if (pOut)
	{
		free(pOut);
	}
	return;
}

main()
{
	int i;
	int loop;

	queue = AllocAsyncItemCreateQueue(10, 4, testCreat, testDestroy);
	if (queue == NULL) return 0;

	for (i = 0; i < 20; i ++)
	{
		item[i] = CreateAsyncItem(&i, queue);
		printf("%d = %p\n", i, item[i]);
	}
	DestroyAsyncItem(item[5], queue);
	item[5] = 0;
	
	loop = 1;

	while (loop)
	{
		loop = 0;
		for (i = 0; i < 20; i ++)
		{	
			if (item[i] != 0)
			{
				if ((item[i] != 0) && (GetAsyncItemState(item[i]) == AS_CREATED))
				{
					printf("==%s==\n", GetAsyncItemData(item[i]));
					DestroyAsyncItem(item[i], queue);
					item[i] = 0;
				} 
				else
				{
					loop = 1;
				}
			}
		}
	}


	FreeAsyncItemCreateQueue(queue);

	getch();
}
#endif
#endif
