#ifndef _AUTH_HARDWARE_H_
#define _AUTH_HARDWARE_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct tagAUTH_HARDWARE_PARAM
{
	char	*WaveTablePath;
}AUTH_HARDWARE_PARAM;

int AuthHardware_Init (AUTH_HARDWARE_PARAM *Param);
void AuthHardware_Finish (void);

#if defined(__cplusplus)
}
#endif

#endif
