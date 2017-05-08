#include "AudioPlatformRecord.h"

#ifdef _WIN32
long OutRaw_Avalible()
{
	return 0;
}

AUDIO_IN_HANDLE OutRaw_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	return (void *)0;
}

long OutRaw_Close (AUDIO_IN_HANDLE Handle)
{
	return 0;
}

long OutRaw_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	return 0;
}

#else
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <termios.h>
#include <sys/ioctl.h>

#define CHAOS_AUDIO_PROCED_OUT_DEV                        "/dev/ChaosProcOut"

typedef struct tagOUT_RAW_INFO
{
	int fd;
}OUT_RAW_INFO;

long OutRaw_Avalible()
{
	return 1;
}

AUDIO_IN_HANDLE OutRaw_Open (AUDIO_HANDLE Handle, AUDIO_PARAM *Param)
{
	OUT_RAW_INFO *pInfo;

	pInfo = (OUT_RAW_INFO *)malloc (sizeof(OUT_RAW_INFO));

	if (pInfo == NULL)
	{
		return (void *)0;
	}

	pInfo->fd = open(CHAOS_AUDIO_PROCED_OUT_DEV, O_RDWR);
	if (pInfo->fd == -1)
	{
		free (pInfo);
		return (void *)0;
	}

	return pInfo;
}

long OutRaw_Close (AUDIO_IN_HANDLE Handle)
{
	OUT_RAW_INFO *pInfo = (OUT_RAW_INFO *)Handle;

	close (pInfo->fd);
	free (pInfo);
	return 0;
}

long OutRaw_Read (AUDIO_IN_HANDLE Handle, void *BufAddr, unsigned long Size)
{
	OUT_RAW_INFO *pInfo = (OUT_RAW_INFO *)Handle;
	int i;
	int Ret;
	signed short *tBuf;
	int Count;
	int cursysvol = 1, maxsysvol = 1;
	signed int tVal;

	Ret = read (pInfo->fd, BufAddr, Size);
	Count = Ret / 2;
	tBuf = (signed short *)BufAddr;

	/*if(g_musVol == 0)
	{
		memset(BufAddr, 0, Size);
	}
	else*/
	{
		for (i = 0; i < Count; i++)
		{
			tVal = *tBuf;
			//tVal = tVal * maxsysvol * 180 / (cursysvol*g_musVol);
			tVal = tVal * maxsysvol * 2 / cursysvol;
			if (tVal > 32767)
			{
				tVal = 32767;
			}
			else if (tVal < -32768)
			{
				tVal = -32768;
			}
			*tBuf++ = tVal;
		}
	}
	return Ret;
}

#endif
