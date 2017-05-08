/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : k_global.h
** Revision : 1.00											
**																	
** Description: karaoke global head file, include normal low level api head files
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
*/

#ifndef _K_GLOBAL_H_
#define _K_GLOBAL_H_

#include <k_define.h>

#include <arch/arch.h>
#include <k_debug.h>
#include <lib/common/krk_common.h>


struct tDRect
{
	float xmin;
	float ymin;
	float xmax;
	float ymax;
};

#ifndef m3d_min
#define m3d_min(a, b)		(((a)>(b))? (b) : (a))
#endif

#ifndef m3d_max
#define m3d_max(a, b)		(((a)>(b))? (a) : (b))
#endif

#endif
