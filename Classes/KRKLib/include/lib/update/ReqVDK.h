/************************************************************************************** 
** Copyright (C) 2011 Multak,Inc. All rights reserved
**
** Filename : ReqVDK.h
** Revision : 1.00
**
** Author :  yexf
** Date :  2013-03-13
**
** Description:
**************************************************************************************/ 
#ifndef _REQVDK_H_
#define _REQVDK_H_

#define VDK_SN_LEN 12

/*
* vdk data request parameter
*/
typedef struct 
{
	char				 	sn[VDK_SN_LEN];
	int					charset;
	int					sort_default_lan;				/* default sort language */
	int					usedef_lanlist[8];			/* language in this list will use default sort language */
	char*				mukPath;							/* if muk path is not NULL, decode files when request data */
	void*				userdata;
	void*				decode_cb;
	int					cn_firstword;
} vdk_req_para_t;

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************* 
** Function name  : VDK_ReqData
** Arguments      : prt - req date table 
**                  			dir_path - vdk files folder
**								para - request parameters
** Return         : int 
** Date&Time      : 2012-09-17  10:45:09
** Description    : request data table from vdk file head
*********************************************************************************************/ 
extern int VDK_ReqData(req_table_t *prt,const char *dir_path,vdk_req_para_t *para);

/********************************************************************************************* 
** Function name  : VDK_DecodeFiles
** Arguments      : src_dir - vdk files folder
**                  			dst_dir - muk files folder
**								userdata - callback parameter
**								cb - callback function
**								sn - serial number
** Return         : int 
** Date&Time      : 2012-09-17  10:45:09
** Description    : decode VDK file to MUK files
*********************************************************************************************/ 
extern int VDK_DecodeFiles(char *src_dir,char *dst_dir, void* userdata, void* cb, char* sn);

#ifdef __cplusplus
}
#endif

#endif
