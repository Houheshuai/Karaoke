/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : voice_record.h
** Revision : 1.00											
**																	
** Description: voice record module
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
************************ HOWTO *******************************
** 
*/

#ifndef _VOICE_RECORD_H_
#define _VOICE_RECORD_H_

#include <k_global.h>

/*
* voice record format
*/
typedef enum
{
	VOICE_REC_PCM,
	VOICE_REC_WAV,
	VOICE_REC_MP3,
	VOICE_REC_ADPCM,
	VOICE_REC_AAC,
	
} voiceRecordFormat_t;

/*
* buffer mute callback
*/
typedef void (*voiceMuteCallback_t)(void* owner, void* data);
/*
* buffer read callback
*/
typedef void (*voiceReadCallback_t)(void* owner, void* data, int size);

/*
* voice record input parameters
*/
typedef struct {
	int devsamplerate;
	int filesamplerate;
	int channels;
	int format;
	int mutetime;
	int threshold;
	void* audioIf;
	void* audioHdle;
	void* owner;
	voiceMuteCallback_t mute_cb;
	voiceReadCallback_t read_cb;
	char outfile[256];
	
} voiceRecordParam_t;

/*
* voice record handle
*/
typedef struct 
{
	krk_os_task_t task;
	int					exitFlag;
	voiceRecordParam_t param;
	
} voiceRecordHandle_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: voice_record_start
 * Arguments      	: param - voice record parameters
 * Return         	: voice record handle
 * Description    	: start voice record
 *					
*/
extern voiceRecordHandle_t* voice_record_start(voiceRecordParam_t* param);

/*
 * Function name  	: voice_record_stop
 * Arguments      	: hdle - voice record handle
 * Return         	: 0 - succ, <> - error code
 * Description    	: stop voice record
 *					
*/
extern int voice_record_stop(voiceRecordHandle_t* hdle);

#ifdef __cplusplus
}
#endif

#endif

