#ifndef _KKINPUT_H_
#define _KKINPUT_H_

#include "kkinput-ext.h"

#ifdef _WIN32
#define KKINPUT_SERIAL

/////////////////////////////////////////////
/*
// mouseX, mouseY
.7---.0       : Mouse data Low 8 bits
//mouseHead
.7---.6       : mouseX high 2 bits
.5---.4       : mouseY high 2 bits
// ofncfg
.7---.5       : mainSN
.4---.3       : subSN
.2---.0       : cpi_num
*/
#endif

#define MAX_OFN_DEV		2
#define NO_MOVE_SIZE	10000
#define MAXBUFFERCNT	20

#pragma pack(1)
typedef struct
{
	unsigned char Intime;
	unsigned char RFID;
	unsigned char T_SN;
	unsigned char MainSN;
	unsigned char SubSN;
	unsigned char CPI;
	signed short mouse_X;
	signed short mouse_Y;
	unsigned char keyData;
	unsigned char Resv;
	//unsigned int CurTime;
}OfnNode_st;
#pragma pack()


#endif
