/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : iLyric.h
** Revision : 1.00											
**																	
** Description: Lyric player module
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by zhaolj
** 1.01
**       modified by yucx
**
*/

#ifndef _I_CDG_LYRIC_H___
#define _I_CDG_LYRIC_H___

#include <k_global.h>
#include <gui/iapi/GuiString.h>
#include <gui/iapi/GuiImage.h>
#include <lib/ezbase/ez_notify.h>
#include <lib/ezbase/ez_player.h>

#include <Lyric/ChaosLyric.h>
#include <Lyric/LyricInfo.h>
#include <Lyric/ChaosCDG.h>
#include <ChaosPlayer.h>

enum
{

	CDG_LYRIC_RET_SUCC = 0,
};


#ifdef __cplusplus
extern "C" {
#endif


extern int CDGLyricReset(void);
extern int CDGLyricUpdateView(void *chaosHandle);


#ifdef __cplusplus
}
#endif


#endif

