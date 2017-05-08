#ifndef _RF_MOD_H_
#define _RF_MOD_H_

#if defined(__cplusplus)
extern "C" {
#endif

int RF_OpenWirelessMic(int handle);
int RF_CloseWirelessMic(int handle);

int RF_CheckNeedPair(void);
int RF_LoadUsrCode(void *pRfCode);
int RF_SaveUsrCode(void *pRfCode);
int RF_ReadUsrCode(int handle, void *pRfCode);
int RF_WriteUsrCode(int handle, void *pRfCode);
int RF_OpenRfDevice(int handle, int mode);
int RF_CloseRfDevice(int handle);
int RF_GetWirelessVersion(int handle);
unsigned RF_GetWirelessSN(void);


int RF_StartPair(int handle);
int RF_StopPair(int handle);
int RF_GetPairStatus(int handle);

#if defined(__cplusplus)
}
#endif

#endif
