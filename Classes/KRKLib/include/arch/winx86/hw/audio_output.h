/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : audio_output.h
** Revision : 1.00											
**																	
** Description: audio output device api
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

#ifndef _AUDIO_OUTPUT_H_
#define _AUDIO_OUTPUT_H_

#define AUD_OUT_DUMP_BUF_SIZE (32*1024)

#define AUDIO_OUT_SAMPLERATE	32000

typedef enum
{
	AUDIO_OUT_IOCTL_NONE,
	AUDIO_OUT_IOCTL_SET_PARA,		/* setup audio output device */
	AUDIO_OUT_IOCTL_GET_PARA,
	AUDIO_OUT_IOCTL_READY_SAMPLES,	/* get the valid samples number in dump buffer */
	AUDIO_OUT_IOCTL_FREE_SAMPLES,	/* get the free space of samples number in dump buffer */
	
}audio_out_ioctrl_cmd_et;

typedef enum
{
	AUDIO_OUT_LEFT_CHANNEL,			/* only left channel data */
	AUDIO_OUT_RIGHT_CHANNEL,			/* only right channel data */
	AUDIO_OUT_LEFT_RIGHT_CHANNEL,		/* first all is left channel data, second all is right channel data */
	AUDIO_OUT_MIX_CHANNEL,			/* every sample is (left sample + right sample)/2 */
	AUDIO_OUT_STEREO_CHANNEL			/* one sample left, one sample right, always left first */
	
}audio_out_channel_et;

typedef enum
{
	AUDIO_OUT_STATE_OFF,
	AUDIO_OUT_STATE_ON
	
}audio_out_state_et;

typedef struct 
{
	unsigned int samplerate; /* audio sample rate */
	unsigned int framebits;	/* bit width of one sample frame */
	unsigned int channels;	/* output channel count, mono/stereo */
} audio_out_para_t;

typedef struct 
{
	unsigned int dump_buf;
	unsigned int buf_size;
	audio_out_para_t param;
		
}audio_out_config_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
* initialize audio input device
*
* @param
*		buf_size : dump buffer size
* @return - 0 success, -1 fail
*/
extern int audio_out_initialize(int buf_size);

/*
* free audio out device
*
* @param
*		none
* @return - 0 success, -1 fail
*/
extern int audio_out_free(void);

/*
* open audio output device
*
* @param
*		none
* @return - 0 success, -1 fail
*/
extern int audio_out_open(void);

/*
* close audio output device
*
* @param
*		none
* @return - 0 success, -1 fail
*/
extern int audio_out_close(void);

/*
* audio output device io control
*
* @param
*		none
* @return - 0 success, -1 fail
*/
extern int audio_out_ioctl(audio_out_ioctrl_cmd_et cmd, void *param);

/*
* read real time pcm data from pcm buffer
*
* @param
*		buf: output buffer address
*		samples: request samples number
*		param: none
* @return - read data size in bytes
*/
extern int audio_out_read(void *buf, int samples, int param);

/*
* write data from user buffer to dump buffer
*
* @param
*		buf: user buffer
*		samples: user write data size in sample number
*		ch: set the channel you want to read, see enum "audio_out_channel_et"
* @return - dump sample number
*/
extern int audio_out_write(void *buf, int samples, audio_out_channel_et ch);

/*
* dump audio output data from dump buffer to mix buffer, recommend call it in high priority task
*
* @param
*		none
* @return - dump data size in bytes
*/
extern int audio_out_dump_service(void);

#ifdef __cplusplus
}
#endif 

#endif



