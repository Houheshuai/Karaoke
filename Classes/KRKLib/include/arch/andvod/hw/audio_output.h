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

typedef int (*audout_callback_t )(void*);     /* audio output driver call back function pointer */

/*
* audio out device ioctrl commands
*/
typedef enum
{
	AUDIO_OUT_IOCTL_NONE,
	AUDIO_OUT_IOCTL_START,
	AUDIO_OUT_IOCTL_STOP,
	AUDIO_OUT_IOCTL_SET_PARA,		/* setup audio output device */
	AUDIO_OUT_IOCTL_GET_PARA,
	AUDIO_OUT_IOCTL_READY_SAMPLES,	/* get the valid samples number in dump buffer */
	AUDIO_OUT_IOCTL_FREE_SAMPLES,	/* get the free space of samples number in dump buffer */
	AUDIO_OUT_IOCTL_FLUSH_BUF,	/* flush samples in pcm buffer */
}audio_out_ioctrl_cmd_et;

/*
* audio out device audio channel config
*/
typedef enum
{
	AUDIO_OUT_LEFT_CHANNEL,			/* only left channel data */
	AUDIO_OUT_RIGHT_CHANNEL,			/* only right channel data */
	AUDIO_OUT_LEFT_RIGHT_CHANNEL,		/* first all is left channel data, second all is right channel data */
	AUDIO_OUT_MIX_CHANNEL,			/* every sample is (left sample + right sample)/2 */
	AUDIO_OUT_STEREO_CHANNEL			/* one sample left, one sample right, always left first */
	
}audio_out_channel_et;

/*
* audio out device state
*/
typedef enum
{
	AUDIO_OUT_STATE_STOPPED,
	AUDIO_OUT_STATE_PLAYING
	
}audio_out_state_et;

/*
* audio out device setting parameters
*/
typedef struct 
{
	unsigned int samplerate; /* audio sample rate */
	unsigned int framebits;	/* bit width of one sample frame */
	unsigned int channels;	/* output channel count, mono/stereo */
	audout_callback_t cb;/* dma irg callback */
	unsigned int dmasz;/* dma buffer size in bytes */
	unsigned int cbpara3;/* dma irq callback para3 */
	unsigned int cbpara4;/* dma irq callback para4 */
} audio_out_para_t;

/*
* audio out device configuration
*/
typedef struct 
{
	unsigned int dump_buf;
	unsigned int buf_size;
	audio_out_para_t param;
		
}audio_out_config_t;

/*
* audio out device handle descriptor
*/
typedef struct 
{
	audio_out_config_t 	config;
	int			fp_dev;
	audio_out_state_et 	state;
	
} handle_audout_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
* open audio output device
*
* @param
*		para: audio output parameters
* @return - device handle pointer
*/
extern handle_audout_t* audio_out_open(audio_out_para_t* para);

/*
* close audio output device
*
* @param
*		handle : device handle
* @return - 0 success, -1 fail
*/
extern int audio_out_close(handle_audout_t* handle);

/*
* audio output device io control
*
* @param
*		handle : device handle
* @return - 0 success, -1 fail
*/
extern int audio_out_ioctl(handle_audout_t* handle, audio_out_ioctrl_cmd_et cmd, void *param);

/*
* read real time pcm data from pcm buffer
*
* @param
*		handle : device handle
*		buf: output buffer address
*		samples: request samples number
*		param: none
* @return - read data size in bytes
*/
extern int audio_out_read(handle_audout_t* handle, void *buf, int samples, int param);

/*
* write data from user buffer to dump buffer
*
* @param
*		handle : device handle
*		buf: user buffer
*		samples: user write data size in sample number
*		ch: set the channel you want to read, see enum "audio_out_channel_et"
* @return - dump sample number
*/
extern int audio_out_write(handle_audout_t* handle, void *buf, int samples, audio_out_channel_et ch);

/*
* dump audio output data from dump buffer to mix buffer, recommend call it in high priority task
*
* @param
*		none
* @return - dump data size in bytes
*/
extern int audio_out_dump_service(handle_audout_t* handle);

#ifdef __cplusplus
}
#endif 

#endif



