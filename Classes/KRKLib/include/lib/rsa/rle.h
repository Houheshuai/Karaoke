/************************************************************************************** 
** Copyright (C) 2011 Multak,Inc. All rights reserved
**
** Filename : rle.h
** Revision : 1.00
**
** Author :  yexf
** Date :  2012-08-02
**
** Description: ”Œ≥Ã±‡¬ÎRLE(run-length encoding)
**************************************************************************************/ 
#ifndef _RLE_H_
#define _RLE_H_

#ifdef __cplusplus
extern "C" {
#endif

unsigned long RleUnZip(unsigned char *pbmp_src, 
					   unsigned char *pbmp_dst,
					   unsigned long size);
unsigned long RleZip(unsigned char *pbmp_src, 
					 unsigned char *pbmp_dst, 
					 unsigned long size);

#ifdef __cplusplus
}
#endif

#endif

