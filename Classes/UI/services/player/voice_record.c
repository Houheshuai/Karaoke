/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : voice_record.c
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

#include "CP_Audio.h"
#include "UserResample.h"
#include "voice_record.h"

#define VC_RD_SZ (1024*16)

#define aud_trunk_val(min, max, val)	val = ((val)<(min))? (min) : (((val) > (max))? (max) : (val))

typedef struct __WAVE_HEADER1
{
    char       					uRiffFcc[4];       // four character code, "RIFF"
    unsigned int       uFileLen;       // file total length, don't care it

    char       				uWaveFcc[4];       // four character code, "WAVE"

    char				       uFmtFcc[4];        // four character code, "fmt "
    unsigned int       uFmtDataLen;    // Length of the fmt data (=16)
    unsigned short   uWavEncodeTag;  // WAVE File Encoding Tag
    unsigned short   uChannels;      // Channels: 1 = mono, 2 = stereo
    unsigned int       uSampleRate;    // Samples per second: e.g., 44100
    unsigned int       uBytesPerSec;   // sample rate * block align
    unsigned short    uBlockAlign;    // channels * bits/sample / 8
    unsigned short    uBitsPerSample; // 8 or 16

    char       				uDataFcc[4];       // four character code "data"
    unsigned int       uSampDataSize;  // Sample data size(n)

} __wave_header_t1;

int voice_pcm_resample(short* in_buf, short* out_buf, int in_rate, int out_rate, int in_chn, int out_chn, int in_len, char* hdle)
{
	int i;
	int j;
	int val;

	if (in_chn == out_chn) {
		if (in_rate == out_rate) {
			memcpy(out_buf, in_buf, in_len*2*out_chn);
			return in_len*2*in_chn;
		} else {
			return (2*out_chn)*Resample(in_buf, out_buf, in_rate, out_rate, in_len, out_chn, hdle);
		}
	} else if (in_chn > out_chn) {
		for (i=0; i<in_len; i++) {
			for (j=0; j<out_chn; j++) {
				in_buf[i*out_chn+j] = in_buf[i*in_chn+j];
			}
			val = in_buf[i*out_chn];
			for (; j<in_chn; j++) {
				val += in_buf[i*in_chn+j];
			}
			aud_trunk_val(-32768, 32767, val);
			in_buf[i*out_chn] = val;
		} 
		if (in_rate == out_rate) {
			memcpy(out_buf, in_buf, in_len*2*out_chn);
			return in_len*2*out_chn;
		} else {
			return (2*out_chn)*Resample(in_buf, out_buf, in_rate, out_rate, in_len, out_chn, hdle);
		}
	} else {
		int ret;

		if (in_rate == out_rate) {
			memcpy(out_buf, in_buf, in_len*2*in_chn);
			ret = in_len;
		} else {
			ret = Resample(in_buf, out_buf, in_rate, out_rate, in_len, in_chn, hdle);
		}
		for (i=ret; i--!=0; ) {
			for (j=0; j<in_chn; j++) {
				out_buf[i*out_chn+j] = out_buf[i*in_chn+j];
			}
			val = out_buf[i*out_chn + j -1];
			for (; j<out_chn; j++) {
				out_buf[i*out_chn+j] = val;
			}
		}
		return ret*out_chn*2;
	}
}

static KRK_TASK_RET_TYPE voice_record_thread(KRK_TASK_ENTRY_ARG arg)
{
	voiceRecordHandle_t* hdle = (voiceRecordHandle_t*)arg;
	CP_AudioIFs* audioIF = (CP_AudioIFs*)hdle->param.audioIf;
	AUDIO_PARAM audio_para;
	__wave_header_t1 wavhead;
	AUDIO_HANDLE audio_hdle = (AUDIO_HANDLE)hdle->param.audioHdle;
	AUDIO_IN_HANDLE in_hdle = NULL;
	AUDIO_OUT_HANDLE out_hdle = NULL;
	char* resample = NULL;
	
	int ret;
	int rsret;
	int mutetime = 0;
	int retzerotime = 0;
	int unmute = 0;
	char* buf = malloc(VC_RD_SZ);
	char* rsbuf = malloc(VC_RD_SZ*8);
	FILE* fp = fopen(hdle->param.outfile, "wb+");

	mus_printf("voice_record_thread: %s, %d, %d, %d\n", hdle->param.outfile, hdle->param.devsamplerate, hdle->param.channels, hdle->param.mutetime);

	wavhead.uBitsPerSample = 16;
	wavhead.uBlockAlign = 2*hdle->param.channels;
	wavhead.uBytesPerSec = wavhead.uBlockAlign*hdle->param.filesamplerate;
	wavhead.uChannels = hdle->param.channels;
	memcpy(wavhead.uDataFcc, "data", 4);
	wavhead.uFileLen = 0;
	wavhead.uFmtDataLen = 16;
	memcpy(wavhead.uFmtFcc, "fmt ", 4);
	memcpy(wavhead.uRiffFcc, "RIFF ", 4);
	wavhead.uSampDataSize = 0;
	wavhead.uSampleRate = hdle->param.filesamplerate;
	memcpy(wavhead.uWaveFcc, "WAVE ", 4);
	wavhead.uWavEncodeTag = 1;
	
	audio_para.CallBack = NULL;
	audio_para.Channels = hdle->param.channels;
	audio_para.FrameCount = 0;
	audio_para.SampleRate = hdle->param.devsamplerate;
	audio_para.User = NULL;
	
	if (audio_hdle != NULL) in_hdle = audioIF->srcopen(audio_hdle, &audio_para);
	//if (audio_hdle != NULL) out_hdle = audioIF->sinkopen(audio_hdle, &audio_para);

	mus_printf("%x, %x, %x, %x, %x\n", fp, buf, audio_hdle, in_hdle, out_hdle);

	if (fp != NULL 
		&& buf != NULL
		&& audio_hdle != NULL
		//&& out_hdle != NULL
		&& in_hdle != NULL 
		)
	{
		fwrite(&wavhead, 1, sizeof(__wave_header_t1), fp);

		if (audio_para.SampleRate != hdle->param.filesamplerate || audio_para.Channels != hdle->param.channels)
			resample = ResampleInit();
		
		while (fp != NULL) 
		{
			if (hdle->exitFlag)
				break;
		
			ret = audioIF->srcread(in_hdle, buf, VC_RD_SZ);
			if (ret > 0) {
				retzerotime = 0;
				
				if (hdle->param.read_cb != NULL)
					hdle->param.read_cb(hdle->param.owner, buf, ret);

				if (resample != NULL) {
					rsret = voice_pcm_resample((short *)buf,(short *)rsbuf,audio_para.SampleRate,hdle->param.filesamplerate,audio_para.Channels,hdle->param.channels,ret/2/audio_para.Channels, resample);
					//rsret = 2*hdle->param.channels*Resample((short *)buf,(short *)rsbuf,audio_para.SampleRate,hdle->param.filesamplerate,ret/2/hdle->param.channels,hdle->param.channels,resample);
					fwrite(rsbuf, 1, rsret, fp);
					wavhead.uSampDataSize += rsret;
				} else {
					fwrite(buf, 1, ret, fp);
					wavhead.uSampDataSize += ret;
				}

				// check mute
				if (hdle->param.mutetime != 0 && hdle->param.mute_cb != NULL) {
					int i;
					for (i=0; i<ret/sizeof(short); i++) {
						short sample = *((short*)buf+i);
						if (sample < 0)
							sample = 0-sample;
						if (sample > hdle->param.threshold) {
							mutetime = 0;
							unmute++;
						} else {
							mutetime++;
						}
					}
					if (mutetime*1000/hdle->param.channels/audio_para.SampleRate > hdle->param.mutetime) {
						// mute time fetch
						mutetime = 0;
						hdle->param.mute_cb(hdle->param.owner, &unmute);
					}
				}

				//memset(buf, 0, VC_RD_SZ);
				//audioIF->sinkwrite(out_hdle, buf, VC_RD_SZ);
			} else {
				//mus_printf("audioIF->srcread %d \n", unmute);
				retzerotime++;
				if (retzerotime*10 > hdle->param.mutetime) {
					// mute time fetch
					mutetime = 0;
					retzerotime = 0;
					hdle->param.mute_cb(hdle->param.owner, &unmute);
				}
			}
			krk_os_sys_sleep(10, NULL);
		}
	}

	wavhead.uFileLen = wavhead.uSampDataSize + sizeof(__wave_header_t1) - 8;

	if (resample != NULL) ResampleFinish(resample);
	if (in_hdle != NULL) audioIF->srcclose(in_hdle);
	//if (out_hdle != NULL) audioIF->sinkclose(out_hdle);
	if (buf != NULL) free(buf);
	if (rsbuf != NULL) free(rsbuf);
	if (fp != NULL) {
		fseek(fp, 0, SEEK_SET);
		fwrite(&wavhead, 1, sizeof(__wave_header_t1), fp);
		fclose(fp);
	}
	
	mus_printf("voice_record_thread exit here!\n");
	krk_os_task_selfdel();

	return KRK_TASK_RET_VAL;
}

/*
 * Function name  	: voice_record_start
 * Arguments      	: param - voice record parameters
 * Return         	: voice record handle
 * Description    	: start voice record
 *					
*/
voiceRecordHandle_t* voice_record_start(voiceRecordParam_t* param)
{
	voiceRecordHandle_t* hdle = calloc(1, sizeof(voiceRecordHandle_t));
	
	memcpy(&(hdle->param), param, sizeof(voiceRecordParam_t));
	
	/* create main thread */
	if (krk_os_task_create(&(hdle->task), "voicerec",voice_record_thread,0x4000,KRK_TASK_PRIORITY_LOW, (void*)hdle) == KRK_OS_RET_FAIL)
	{
		mus_printf("Fail to create voice record task\n");
		KRK_ASSERT(0);
	}
	mus_printf("voice_record_start\n");
	
	return hdle;
}

/*
 * Function name  	: voice_record_stop
 * Arguments      	: hdle - voice record handle
 * Return         	: 0 - succ, <> - error code
 * Description    	: stop voice record
 *					
*/
int voice_record_stop(voiceRecordHandle_t* hdle)
{
	if (hdle != NULL) {
		hdle->exitFlag = 1;
		krk_os_task_destroy(&(hdle->task), NULL);
		free(hdle);
		mus_printf("voice_record_stop\n");
		return 0;
	} else {
		return -1;
	}
}


