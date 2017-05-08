#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <cassert>
#else
#include <pthread.h>
#include <semaphore.h>
#include <linux/fb.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h> 
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#endif

#include <time.h>
#include <fcntl.h>

#include "kkinput.h"


#define MAX_T_SN	256		//0-255
#define MAX_M_SN	8		//0-7
#define MAX_S_SN	3		//0-3
#define MCPI		250
#define MM		1000

#define MAX_SN_COUNT	6


#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000


static KK_EVENT_CALLBACK kkInputEventCallback;
static int last_mainsn[MAX_OFN_DEV];
//static int MouseX, MouseY;
//static char Key;


#ifdef _WIN32
#else
static pthread_t pthread_id;
#endif

static unsigned char deInitFlag = 0;


typedef struct
{
	unsigned char touch;		// 1: on, 0: off
	unsigned char key;			// 1: down, 0: up
	//unsigned char last_t_sn;

	int	sn_count;
}OfnState_st;


typedef struct
{
	int device_fd;

	//char firstData;
	OfnNode_st ofnNodeBuffer[MAXBUFFERCNT];
	//OfnNode_st ofnLastNode;
	//OfnNode_st firstMouseData;
	//OfnNode_st lastMouseData;

	//


	OfnState_st state;

}OfnInfo_st;


static OfnInfo_st ofnInfo[MAX_OFN_DEV];





#ifdef _WIN32
//win 32
#define KK_TIMER	2
#define TEST_KK_TIMECALC



#ifdef TEST_KK_TIMECALC
static double dfFreq;
static double lastTime;
#endif

#ifdef KKINPUT_SERIAL
HANDLE hCom;
DWORD dwFileRead;
DWORD dwT;
FILE * fp = NULL;
#endif


static MMRESULT kkTimerID;


#ifdef TEST_KK_TIMECALC
static void KK_InitTimer(void)
{
#ifdef _WIN32
	LARGE_INTEGER Litmp;
	QueryPerformanceFrequency(&Litmp);
	dfFreq = (double)Litmp.QuadPart;			// üʱƵ
#else

#endif
}
#endif

static double KK_GetuSec(void)
{
#ifdef _WIN32
	LARGE_INTEGER Litmp;
	LONGLONG QPart;
	double dfTim;

	QueryPerformanceCounter(&Litmp);
	QPart = Litmp.QuadPart;					// óʼֵ
	dfTim = QPart / dfFreq;					// öӦʱֵλΪ

	return dfTim*1000*1000;
#else
	struct timeval tv;

	gettimeofday (&tv , NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
#endif
}


#ifdef KKINPUT_SERIAL
extern "C" int krk_printf(const char *format, ...);

//unsigned char InData[1024];
//unsigned char OutData[1024];
//size_t writelen;

static unsigned char Key;
static signed int MouseX, MouseY;
static unsigned int total_len = 0;

#define OFFMAINSN			5
//static unsigned short last_mainsn = 0;
static unsigned short current_mainsn = 0;

static unsigned int cnt111 = 0;


static unsigned char lpBuffer[256];

static unsigned GetSync = 0;
static unsigned int LessLength = 1;
static unsigned int Offset = 0;


int Process_Packet(int index)
{
	unsigned char CheckSumV;
	int ret = 0;

	BOOL bReadStatus;
	BOOL bResult;
	DWORD dwError;
	COMSTAT comstat;

	bResult = ClearCommError(hCom, &dwError, &comstat);
	if (comstat.cbInQue == 0)
	{
		return 0;
	}

read_again:
 	bReadStatus = ReadFile(hCom, (void*)&lpBuffer[Offset], LessLength, &dwFileRead, NULL);

	total_len += dwFileRead;
	if(total_len >= (unsigned int)0x4000)
	{
		//return -1;
	}

	if(dwFileRead)
	{
		if(GetSync)
		{
			if(lpBuffer[0] == 0xa5)
			{
				//current_mainsn = lpBuffer[3];
				if (last_mainsn[0] != (lpBuffer[3] >> OFFMAINSN)&0x07)
				{
					last_mainsn[0] = (lpBuffer[3] >> OFFMAINSN)&0x07;
					MouseX = lpBuffer[1];
					if(lpBuffer[3] & BIT2)
						MouseX = -MouseX;
					MouseY = lpBuffer[2];
					if(lpBuffer[3] & BIT1)
						MouseY = -MouseY;
					if(lpBuffer[3]&0x10)
					{
						Key |= (1<<6);//lpBuffer[4];
					}
					else
					{
						Key = ~(1<<6);//lpBuffer[4];
					}
					//krk_printf("X=%4d Y=%4d sn=%1x key=%2x\n", MouseX, MouseY, last_mainsn[0], Key); //subsn = %1x  cpi = %1x,  (lpBuffer[4] >> 3) & 3, (lpBuffer[4]) & 7,
					ret = 1;
				}
				else
				{
					MouseX = NO_MOVE_SIZE;
					MouseY = 0;
				}

				LessLength = 4;
				GetSync = 1;
				Offset = 0;
			}
			else
			{
				LessLength = 1;
				GetSync = 0;
				Offset = 0;
			}
		}
		else
		{
			if(lpBuffer[0] == 0xa5)
			{
				LessLength = 3;
				GetSync = 1;
				Offset = 1;
				goto read_again;
			}
			else
			{
				LessLength = 1;
				GetSync = 0;
				Offset = 0;
			}
		}
	}

#if 0
	if(dwFileRead)
	{
		if(GetSync)
		{
			if(lpBuffer[0] == 0xa5)
			{
				LessLength = 5;
				GetSync = 0;
				Offset = 0;
				goto read_again;
			}
			else
			{
				LessLength = 1;
				GetSync = 1;
				Offset = 0;
			}
		}
		else
		{
			Offset += dwFileRead;
			LessLength -= dwFileRead;

			if(LessLength == 0)
			{
				MouseX = lpBuffer[0];
				if(lpBuffer[2] & BIT2)
					MouseX = -MouseX;
				MouseY = lpBuffer[1];
				if(lpBuffer[2] & BIT1)
					MouseY = -MouseY;
				//Key = lpBuffer[3];

				// 				// ofncfg
				// 				.7---.5       : mainSN
				// 					.4---.3       : subSN
				// 					.2---.0       : cpi_num

				if((unsigned char)(lastframe + 2) == lpBuffer[3])
				{
					ret = 1;
				}
				lastframe = lpBuffer[3];

				/*if(last_mainsn[0] != (lpBuffer[2] >> 5))
				{
					if((last_mainsn[0] & 0xff) == (lpBuffer[2] >> 5))
					{ // just key changed
						MouseX = NO_MOVE_SIZE;
						MouseY = 0;
						Key = 0;
					}
					last_mainsn[0] = (lpBuffer[2] >> 5);
					//log_for_pro("X=%4d Y=%4d sn=%1x key=%2x\n",MouseX, MouseY,  lpBuffer[4] >> 5, Key); //subsn = %1x  cpi = %1x,  (lpBuffer[4] >> 3) & 3, (lpBuffer[4]) & 7,
					ret = 1;
				}*/

				GetSync = 1;
				Offset = 0;
				LessLength = 1;
			}
		}
	}
#endif

	return ret;
}

#endif

unsigned long last_time;
static void KK_Analyse(int dx, int dy, unsigned char keyData, int index )
{
	unsigned char touch;
	unsigned char key;
	unsigned char lasttouch = ofnInfo[index].state.touch;
	unsigned char lastkey = ofnInfo[index].state.key;

	int kk_event = KKINPUT_EVENT_NONE;

	touch = (keyData&(1<<6)) ? 1 : 0;
	key = (keyData&(1<<7)) ? 1 : 0;

	if (touch && !lasttouch){
		kk_event |= KKINPUT_EVENT_TOUCHON;
		//last_time = clock()/CLOCK_2_MS;
	}
	else if (!touch && lasttouch){
		kk_event |= KKINPUT_EVENT_TOUCHOFF;
		//last_time = clock()/CLOCK_2_MS;
	}

	if (key && !lastkey){
		kk_event |= KKINPUT_EVENT_KEYDOWN;
		//last_time = clock()/CLOCK_2_MS;
	}
	else if (!key && lastkey){
		//last_time = clock()/CLOCK_2_MS;
		kk_event |= KKINPUT_EVENT_KEYUP;
	}

	if (dx != 0 || dy != 0)
	{
		if (kk_event == KKINPUT_EVENT_NONE)
			kk_event |= KKINPUT_EVENT_MOVE;

		//kkinput_print(">>> KK_Analyse <<< dx[%d], dy[%d], t[%d], k[%d], tlast[%d], klast[%d] \n", dx, dy, touch, key, lasttouch, lastkey);
	}
	if ((touch == 1) && (kk_event == KKINPUT_EVENT_NONE))
		kk_event |= KKINPUT_EVENT_MOVE;

	if (kk_event != KKINPUT_EVENT_NONE)
	{
		//unsigned long cur_time = clock()/CLOCK_2_MS;
		//log_for_pro("%0x ,%d, %d\n", kk_event, dy, touch);
		if(kkInputEventCallback != NULL){
			(*kkInputEventCallback)(KK_TIMER, dx, dy, kk_event, index);
			//log_for_pro("X=%4d Y=%4d t=%4d key=%2x\n",MouseX, MouseY, KK_TIMER , Key); //subsn = %1x  cpi = %1x,  (lpBuffer[4] >> 3) & 3, (lpBuffer[4]) & 7,
		}

		//last_time = cur_time/CLOCK_2_MS;
	}

	ofnInfo[index].state.touch = touch;
	ofnInfo[index].state.key = key;

}

static void CALLBACK KK_TimeProc( UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
	int i;

	//log_for_pro("1\n");
#ifdef KKINPUT_SERIAL

	if(Process_Packet(0))
	{
		KK_Analyse(MouseX, MouseY, Key, 0);
	}

// 	if(Process_Packet(1)){
// 		KK_Analyse(MouseX, MouseY, Key, 1);
// 	}
#endif

	return;
}



int kkInput_Init( KK_EVENT_CALLBACK callback)
{

	DWORD dwError;

	kkInputEventCallback = callback;
	memset(ofnInfo, 0, sizeof(OfnInfo_st)*MAX_OFN_DEV);

#ifdef TEST_KK_TIMECALC
	KK_InitTimer();
	lastTime = 0.0;
#endif



#ifdef KKINPUT_SERIAL
	int Cnt;
	char output_report[10];
	int i, Size;
	BOOL fSuccess;
	char ComPort[20]; 
	char ComPortn[20];


	printf("\ninput com port number:");

#if 0
	scanf("%s", ComPortn);
#else
	strcpy(ComPortn, "3");
#endif

	sprintf(ComPort, "COM%s", ComPortn);

	printf("Comm open: %s\n",ComPort);

	hCom = CreateFile(ComPort, 
		GENERIC_READ| GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if(hCom == INVALID_HANDLE_VALUE) 
	{
		// Handle the error. 
		printf("Comm open failed  with error %d.\n", GetLastError());
		assert(0);
	}
	printf("Comm open OK!\n");



	//óʱ
	COMMTIMEOUTS m_CommTimeouts;
	m_CommTimeouts.ReadIntervalTimeout = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 500;
	m_CommTimeouts.ReadTotalTimeoutConstant = 500;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 500;
	m_CommTimeouts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &m_CommTimeouts);

	//ûС
	SetupComm(hCom, 1024, 1024);


	DCB dcb;
	dcb.DCBlength = sizeof(DCB);

	if(GetCommState(hCom, &dcb) == 0)
	{
		printf("Comm bnot ready!\n");
		assert(0);
	}

#if 1
	char szBaud[100] = {0};
	sprintf(szBaud,"baud=%d parity=N data=8 stop=1", /*499000*/ /*470588*/ 115200*4 );//1
	//sprintf(szBaud,"baud=%d parity=N data=8 stop=1", /*499000*/ /*470588*/ 115200);

	if (BuildCommDCB(szBaud,&dcb) == 0)
	{
		printf("BuildCommDCB failed\n");
	}
#endif

	/*dcb.BaudRate = CBR_115200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;*/
	//dcb.fDtrControl = DTR_CONTROL_DISABLE;
	//dcb.fRtsControl = RTS_CONTROL_DISABLE;
	//dcb.fDsrSensitivity = FALSE;
	//dcb.fOutxCtsFlow = FALSE;
	//dcb.fOutxCtsFlow = FALSE;
	//dcb.fOutxCtsFlow = FALSE;
	//dcb.fOutxDsrFlow = FALSE;
	//dcb.fAbortOnError = FALSE;

	if(SetCommState(hCom, &dcb) == 0)
	{
		printf("Comm set bit rate error ready!\n");
		//return;
	}


	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	//DWORD dwErrorFlags;
	//COMSTAT ComStat;
	//ClearCommError(hCom,&dwErrorFlags,&ComStat);
	//fSuccess = SetCommMask(hCom, EV_RXCHAR);

	kkTimerID = timeSetEvent(KK_TIMER, 0, KK_TimeProc, 0, (UINT)TIME_PERIODIC);


#endif

	return 0;

}


int kkInput_Deinit( void )
{
#ifdef _WIN32	
	if(kkTimerID)
		timeKillEvent(kkTimerID);
#endif

	return 0;
}
#else

#define KK_TIMER	8
//#define TEST_KK_TIMECALC



#ifdef TEST_KK_TIMECALC
static double dfFreq;
static double lastTime;
#endif

#ifdef KKINPUT_SERIAL
HANDLE hCom;
DWORD dwFileRead;
DWORD dwT;
FILE * fp = NULL;
#endif


#ifdef _WIN32
static MMRESULT kkTimerID;
#endif

#ifdef TEST_KK_TIMECALC
static void KK_InitTimer(void)
{
#ifdef _WIN32
	LARGE_INTEGER Litmp;
	QueryPerformanceFrequency(&Litmp);
	dfFreq = (double)Litmp.QuadPart;			// üʱƵ
#else

#endif
}
#endif

static double KK_GetuSec(void)
{
#ifdef _WIN32
	LARGE_INTEGER Litmp;
	LONGLONG QPart;
	double dfTim;

	QueryPerformanceCounter(&Litmp);
	QPart = Litmp.QuadPart;					// óʼֵ
	dfTim = QPart / dfFreq;					// öӦʱֵλΪ

	return dfTim*1000*1000;
#else
	struct timeval tv;

	gettimeofday (&tv , NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
#endif
}

static void KK_Analyse(int dx, int dy, unsigned char keyData, int index );


static void * KK_Thread_ReadProc(void *Param)
{
	int i, j, k, nodeCount;
	int fixCount;
	int dropTsn, dropMsn;
	OfnInfo_st * ofnInfoP;
	unsigned char Key;
	int MouseX, MouseY;

	while(1)
	{
		usleep(8000);    // sleep 4 ms, best way is sleep 4ms

		for(i = 0; i < MAX_OFN_DEV; i ++)
		{
			ofnInfoP = &(ofnInfo[i]);
			nodeCount = read(ofnInfoP->device_fd, (char *)(ofnInfoP->ofnNodeBuffer), MAXBUFFERCNT * sizeof(OfnNode_st));

			j = 0;
			while(nodeCount >= 1)
			{
				nodeCount -= 1;

				if(last_mainsn[i] != (ofnInfoP->ofnNodeBuffer[j].MainSN) +  (ofnInfoP->ofnNodeBuffer[j].keyData << 8))
				{
					MouseX = ofnInfoP->ofnNodeBuffer[j].mouse_X;
					MouseY = ofnInfoP->ofnNodeBuffer[j].mouse_Y;

					if((last_mainsn[i] & 0xff) == ofnInfoP->ofnNodeBuffer[j].MainSN)
					{ // just key changed
						MouseX = NO_MOVE_SIZE;
						MouseY = 0;
					}
					Key = ofnInfoP->ofnNodeBuffer[j].keyData;
					last_mainsn[i] = (ofnInfoP->ofnNodeBuffer[j].MainSN) + (ofnInfoP->ofnNodeBuffer[j].keyData << 8);

					//log_for_pro("after X=%4d Y=%4d sn=%1x key=%2x\n", MouseX, MouseY, ofnInfoP->ofnNodeBuffer[j].MainSN, Key); 
					KK_Analyse(MouseX, MouseY, Key, i);
				}

				j ++;
			}
		}

		if(deInitFlag)
		{
			break;
		}
	}
	return (void *)0;
}

//unsigned long last_time;
static void KK_Analyse(int dx, int dy, unsigned char keyData, int index )
{
	unsigned char touch;
	unsigned char key;
	unsigned char lasttouch = ofnInfo[index].state.touch;
	unsigned char lastkey = ofnInfo[index].state.key;

	int kk_event = KKINPUT_EVENT_NONE;

	touch = (keyData&(1<<6)) ? 0 : 1;
	key = (keyData&(1<<7)) ? 0 : 1;

	if (touch && !lasttouch)
	{
		kk_event |= KKINPUT_EVENT_TOUCHON;
		//last_time = clock()/CLOCK_2_MS;
	}
	else if (!touch && lasttouch)
	{
		kk_event |= KKINPUT_EVENT_TOUCHOFF;
		//last_time = clock()/CLOCK_2_MS;
	}

	if (key && !lastkey)
	{
		kk_event |= KKINPUT_EVENT_KEYDOWN;
		//last_time = clock()/CLOCK_2_MS;
	}
	else if (!key && lastkey)
	{
		//last_time = clock()/CLOCK_2_MS;
		kk_event |= KKINPUT_EVENT_KEYUP;
	}

	if (dx != 0 || dy != 0)
	{
		if (kk_event == KKINPUT_EVENT_NONE)
			kk_event |= KKINPUT_EVENT_MOVE;

		//kkinput_print(">>> KK_Analyse <<< dx[%d], dy[%d], t[%d], k[%d], tlast[%d], klast[%d] \n", dx, dy, touch, key, lasttouch, lastkey);
	}
	if ((touch == 1) && (kk_event == KKINPUT_EVENT_NONE))
		kk_event |= KKINPUT_EVENT_MOVE;

	if (kk_event != KKINPUT_EVENT_NONE)
	{
		//unsigned long cur_time = clock()/CLOCK_2_MS;
		//log_for_pro("%0x ,%d, %d\n", kk_event, dy, touch);
		if(kkInputEventCallback != NULL)
		{
			(*kkInputEventCallback)(KK_TIMER, dx, dy, kk_event, index);
			//log_for_pro("X=%4d Y=%4d t=%4d key=%2x\n",MouseX, MouseY, KK_TIMER , Key); //subsn = %1x  cpi = %1x,  (lpBuffer[4] >> 3) & 3, (lpBuffer[4]) & 7,
		}

		//last_time = cur_time/CLOCK_2_MS;
	}

	ofnInfo[index].state.touch = touch;
	ofnInfo[index].state.key = key;

}


#ifdef _WIN32
static void CALLBACK KK_TimeProc( UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
	int i;

	//log_for_pro("1\n");
#ifdef KKINPUT_SERIAL

	if(Process_Packet(0)){
		KK_Analyse(MouseX, MouseY, Key, 0);
	}

	// 	if(Process_Packet(1)){
	// 		KK_Analyse(MouseX, MouseY, Key, 1);
	// 	}
#endif

	return;
}

#endif

//ret: 0, ok; 1 , fail
int kkInput_Init( KK_EVENT_CALLBACK callback)
{
	int ret = 1;

	kkinput_print("kkInput_Init init\n");

	deInitFlag = 0;
	kkInputEventCallback = NULL;
	memset(ofnInfo, 0, sizeof(OfnInfo_st)*MAX_OFN_DEV);

#ifdef TEST_KK_TIMECALC
	KK_InitTimer();
	lastTime = 0.0;
#endif

	ofnInfo[0].device_fd = open("/dev/mu_ofn1", O_RDWR, S_IRUSR | S_IWUSR);
	ofnInfo[1].device_fd = open("/dev/mu_ofn2", O_RDWR, S_IRUSR | S_IWUSR);

	if(ofnInfo[0].device_fd != -1)
	{
		if(ofnInfo[1].device_fd != -1)
		{
			ret = pthread_create(&pthread_id, NULL, KK_Thread_ReadProc, NULL);
			if (ret != 0)
			{
				close(ofnInfo[0].device_fd);
				close(ofnInfo[1].device_fd);
				kkinput_print("pthread_create fail\n");
			}
			else
			{
				ret = 0;
				kkInputEventCallback = callback;
			}
		}
		else
		{
			close(ofnInfo[0].device_fd);
			kkinput_print("open device_fd[1] fail\n");
		}
	}
	else
	{
		if(ofnInfo[1].device_fd != -1)
		{
			close(ofnInfo[1].device_fd);
			kkinput_print("open device_fd[0] fail\n");
		}
		else
		{
			kkinput_print("open device_fd both [0] and [1] fail\n");
		}
	}

	if(ret == 0)
		kkinput_print("kkInput_Init ok!");
	else
		kkinput_print("kkInput_Init fail\n");

	return ret;
}


//ret: 0, ok; 1 , fail
int kkInput_Deinit( void )
{
	int ret = 0;

	deInitFlag = 1;
	ret = pthread_join(pthread_id, NULL); //pthread_t id
	if (ret != 0)
	{
		ret = 1;
		kkinput_print("pthread_join error!\n");
	}
	else
	{
		ret = 0;
	}

	close(ofnInfo[0].device_fd);
	close(ofnInfo[1].device_fd);

	kkInputEventCallback = NULL;

	kkinput_print("kkInput_DeInit ok!");

	return ret;

}
#endif
