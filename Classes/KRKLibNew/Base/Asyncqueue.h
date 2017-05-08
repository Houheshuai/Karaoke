/* ===========================================
	�첽������� ���й���
============================================= */

#ifndef _ASYNCQUEUE_H
#define _ASYNCQUEUE_H

#define 	tAsyncQueue	void			// �첽����
#define 	tAsyncItem	void			// ���������

typedef enum tarAsyncState	//		�������״̬
{							//					Current State		Next State
	AS_IDEL,				//	����			X					
	AS_WAITCREATE,			//	�ȴ�����		X					X
	AS_CREATING,			//	������			X					
	AS_CREATED,				//	�������		X
	AS_WAITDESTROY,			//	�ȴ�����							X				 
	AS_DESTROYING			//	������			Note: Ver 1.00 destroy at once no destroying state
} tAsyncState;

/* ----------------------------------------
		���� �첽����
	������
		ItemNum									����������
		InputItemSize							�������ί�з���������Ĳ�������
		void *(*pItemCreate)(void *pInput)		�������ί�з���
		void (*pItemDestroy)(void *pOutput)		�������ί�з���
	��� ����ָ��
---------------------------------------- */ 
tAsyncQueue *AllocAsyncItemCreateQueue(int ItemNum, int InputItemSize, void *(*pItemCreate)(void *pInput), void (*pItemDestroy)(void *pOutput));

/***
	���������� CallBack
***/
int AIC_SetCreateCallback(void (*p)(tAsyncItem *pItem), tAsyncQueue *pAsyncQueue);

/***
	������ٽ������ CallBack
***/
int AIC_SetDestroyCallback(void (*p)(tAsyncItem *pItem), tAsyncQueue *pAsyncQueue);

/* ----------------------------------------
	������ ���󴴽����
---------------------------------------- */ 
tAsyncItem *CreateAsyncItem(void *pInput, tAsyncQueue *pAsyncQueue, int pri);

/* ----------------------------------------
	������ �����������
---------------------------------------- */ 
int DestroyAsyncItem(tAsyncItem *pItem, tAsyncQueue *pAsyncQueue);

/* ----------------------------------------
	������ ��ѯ�������״̬
---------------------------------------- */ 
tAsyncState GetAsyncItemState(tAsyncItem *pItem);

/* ----------------------------------------
	�õ��������
---------------------------------------- */ 
void *GetAsyncItemData(tAsyncItem *pItem);

/* ----------------------------------------
	�ͷ��첽���У�
	����:
		�첽����:			pAsyncQueue
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
