/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : arch.h
** Revision : 1.00											
**																	
** Description: architecture depended head file
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


#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef _ANDROID_PLATFORM_
#include <arch/andvod/andvod.h>
#elif defined _MELIS_PLATFORM_
#include <arch/melis/melis.h>
#else
#include <arch/winx86/winx86.h>
#endif

#endif

