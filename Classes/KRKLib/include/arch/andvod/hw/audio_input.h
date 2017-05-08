/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : audio_input.h
** Revision : 1.00											
**																	
** Description: audio input device api
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

#ifndef _AUDIO_INPUT_H_
#define _AUDIO_INPUT_H_

#include <lib/ezbase/ez_vector.h>

#define AUD_IN_DUMP_BUF_SIZE			(32*1024)

#define ONE_BLOCK_SAMPLES		(36*16)
#define SAMPLE_CHECK_VAL  		2000
#define AUDIO_IN_MUTE_THRESHOLD	200
#define AUDIO_IN_MUTE_THRESHOLDN	-200
#define AUDIO_IN_MUTE_TIME			1600 /* 1600 samples, 100 ms*/
#define AUDIO_IN_SAMPLERATE		16000
#define AUDIO_IN_OUT_SAMPLERATE_RATIO	2

typedef int (*audin_callback_t )(void*);     /* audio input driver call back function pointer */

/*
* audio in read mode
*/
typedef enum
{
	AUDIO_IN_NORMAL_READ,
	AUDIO_IN_REALTIME_READ,	
} audio_in_read_mode_et;

/*
* audio in control commands
*/
typedef enum
{
	AUDIO_IN_IOCTL_NONE,
	AUDIO_IN_IOCTL_START,
	AUDIO_IN_IOCTL_STOP,
	AUDIO_IN_IOCTL_CHECK_THRESHOLD,	/* check analog signal input or not. check input data for a while, if no data reach threshold, no signal input */
	AUDIO_IN_IOCTL_READY_SAMPLES,	/* get the valid samples number in dump buffer */
	AUDIO_IN_IOCTL_FREE_SAMPLES,	/* get the free space of samples number in dump buffer */
	AUDIO_IN_IOCTL_FLUSH_BUF,	/* reset read buffer pointer to write pointer */
	AUDIO_IN_IOCTL_CHECK_OVERFLOW,
	AUDIO_IN_IOCTL_SET_PARA,
	AUDIO_IN_IOCTL_GET_PARA,
	AUDIO_IN_IOCTL_SET_WMIC_KEYPAD,
	AUDIO_IN_IOCTL_GET_PAIR_STATE,
	AUDIO_IN_IOCTL_GET_WMIC_GAIN,
	AUDIO_IN_IOCTL_GET_WMIC_RECV_VER,
	
} audio_in_ioctrl_cmd_et;

/*
* audio in channel config
*/
typedef enum
{
	AUDIO_IN_LEFT_CHANNEL,			/* only left channel data */
	AUDIO_IN_RIGHT_CHANNEL,			/* only right channel data */
	AUDIO_IN_LEFT_RIGHT_CHANNEL,		/* first all is left channel data, second all is right channel data */
	AUDIO_IN_MIX_CHANNEL,			/* every sample is (left sample + right sample)/2 */
	AUDIO_IN_STEREO_CHANNEL			/* one sample left, one sample right, always left first */
	
} audio_in_channel_et;

/*
* audio in drive state
*/
typedef enum
{
	AUDIO_IN_STATE_STOPPED,
	AUDIO_IN_STATE_PLAYING
	
} audio_in_state_et;

/*
* audio in data source config
*/
typedef enum
{
	AUDIO_IN_SRC_NONE = 0,
	AUDIO_IN_SRC_MIC,		/* audio data is from MIC input */
	AUDIO_IN_SRC_LINEIN, 	/* audio data is from LINEIN input */
	AUDIO_IN_SRC_FMIN,	/* audio data is from FM input */
	AUDIO_IN_SRC_MIX		/* audio data is from MIX output */
	
} audio_in_src_et;

/*
* audio in parameters
*/
typedef struct 
{
	unsigned int samplerate; /* audio sample rate */
	unsigned char rt_ch;		/* real time samples channel config, see "audio_in_channel_et" */
	unsigned char resample;	/* input audio sample rate */
	unsigned char framebits;	/* bit width of one sample frame */
	unsigned char channels;	/* output channel count, mono/stereo */
	unsigned char bypass;	/* audio output bypass */
	unsigned char half;		/* output gain = AUD_IN/2+AUD_OUT/2 */
	unsigned char audio_src;
	unsigned char wirelessmic;
	audin_callback_t cb;/* dma irq callback */
	unsigned int		dmasz;
	unsigned int		cbpara3;/* dma irq callback para3 */
	unsigned int		cbpara4;/* dma irq callback para4 */
} audio_in_para_t;

/*
* audio in config data
*/
typedef struct 
{
	unsigned int dump_buf;	/* set this buffer to save audio input data */
	unsigned int buf_size;		/* dump buffer size */
	unsigned int threshold; 	/* audio input data check threshold value */
	unsigned int overflow;		/* 1- data in dump buffer is overflow, no reading, 0- reading data before dump buffer overflow */
	audio_in_para_t param;
	
} audio_in_config_t;

/*
* audio out device handle descriptor
*/
typedef struct 
{
	audio_in_config_t 		config;
	int				fp_dev;
	audio_in_state_et 		state;
	ezVector_t*				wmickeys;
	
} handle_audin_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
* open audio input device
*
* @param
*		para : audio input parameters
* @return - device handle
*/
extern handle_audin_t* audio_in_open(audio_in_para_t* para);

/*
* close audio input device
*
* @param
*		handle : device handle
* @return - 0 success, -1 fail
*/
extern int audio_in_close(handle_audin_t* handle);

/*
* audio input device io control
*
* @param
*		handle : device handle
* @return - 0 success, -1 fail
*/
extern int audio_in_ioctl(handle_audin_t* handle, audio_in_ioctrl_cmd_et cmd, void *param);

/*
* read input audio data from dump buffer to user buffer
*
* @param
*		handle : device handle
*		buf: user buffer address
*		samples: user request data size in sample number
*		ch: set the channel you want to read, see enum "audio_in_channel_et"
*		readmode: 0-read continious, 1-only read realtime data, for staff and mic check
*           zeroflag: 1-mic buffer data is all zero
* @return - 0: valid samples number is less than required, otherwise, return required samples number
*/
extern int audio_in_read(handle_audin_t* handle, 
													void *buf, 
                                            int samples, 
                                            audio_in_channel_et ch, 
                                            audio_in_read_mode_et readmode,
                                            int *zeroflag);

extern unsigned char audio_in_check_samples(short * Sample, long Len,char Step,short Limit);

/*
* dump audio input data from MBV buffer to dump buffer, recommend call it in high priority task
*
* @param
*		handle : device handle
* @return - dump data size in bytes
*/
extern int audio_in_dump_service(handle_audin_t* handle);

#ifdef __cplusplus
}
#endif 

#endif


