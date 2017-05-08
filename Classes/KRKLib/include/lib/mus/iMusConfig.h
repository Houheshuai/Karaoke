/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : iMusConfig.h
** Revision : 1.00											
**																	
** Description: mus player configurations
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

#ifndef _IMUSCONFIG_H_
#define _IMUSCONFIG_H_

/*
* include externel midi decode module, recommend you set this marco in makefile
*/
//#define EXTERNEL_MIDI_DEC

/*
* mus player default sample rate, normally it's set by res file, if not, use this marco as default
*/
#ifndef MUS_SAMPLE_RATE
#define MUS_SAMPLE_RATE 48000
#endif

/*
* mus player default output latency, normally it's set by res file, if not, use this marco as default
*/
#ifndef AUD_OUTPUT_LATENCY
#define AUD_OUTPUT_LATENCY 528
#endif

/*
* mus player default input latency, normally it's set by res file, if not, use this marco as default
*/
#ifndef AUD_INPUT_LATENCY
#define AUD_INPUT_LATENCY 100
#endif

/*
* chaosplayer fast mode
*/
#ifndef MUS_CP_FAST_MODE
#define MUS_CP_FAST_MODE 0
#endif

/*
* chaosplayer seperate audio input buffer for scoring
*/
#ifndef MUS_SCORE_SINGLE_BUF
#define MUS_SCORE_SINGLE_BUF 0
#endif

/*
* lyric drawer effects, set it in makefile if you don't want all effects on
*	b.0 : normal effect, use by microsystem
*	b.1 : shadow effect, use by win32&android, opengles must be supported
*	b.2 : frame effect, use by win32&android, opengles must be supported
*/
#ifndef LYRIC_DRAWER_MASK
#define LYRIC_DRAWER_MASK ((1 << 2))  //(1 << 0) | (1 << 1) | 
#endif

/*
* staff drawer effects, set it in makefile if you don't want all effects on
*	b.0 : normal effect, use by microsystem
*	b.1 : particle effect, use by win32&android, opengles must be supported
*/
#ifndef STAFF_DRAWER_MASK
#define STAFF_DRAWER_MASK ( (1 << 1)) //(1 << 0)| 
#endif

/*
*	Lyric brush methods
*/
#define BRUSH_BY_LAYER_MASK		1				// need multi graphic layer support
#define BRUSH_BY_BITBLT					2				// need bitblt support
#define BRUSH_BY_TEXTURE_CLIP		3				// need render support

/*
*	Lyric brush method, set it in makefile if you want to change method
*/
#ifndef LYRIC_BRUSH_BY
#define LYRIC_BRUSH_BY			BRUSH_BY_TEXTURE_CLIP
#endif

#endif

