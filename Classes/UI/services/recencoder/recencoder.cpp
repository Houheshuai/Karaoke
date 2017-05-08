/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : recencoder.cpp
** Revision : 1.00											
**																	
** Description: rec file encoder module
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

#include <k_global.h>
#include "recencoder.h"

/*
* rec encoder handle
*/
typedef struct s_RecEncHandle 
{
	ezVector_t* 					cbhdles;
	krk_os_sema_t 				vtlock;
	void*								owner;
	
	char									cidKey[12];
	void*								privateKey;
	int									ringFlag;				// 1, PLAYER_RING_MODE_FIRST_LYRIC, 0, PLAYER_RING_MODE_OFF
	int									lameFlag;			// 1, mp3 lame encoder, 0, mp3 shine encoder
	int									latency;
	int									outlatency;
	int									bitrate;
	int									spSound;
	
	recEncNotifyCallback_t 	cb;
	
} RecEncHandle_t;

/*
* rec encoder callback handle
*/
typedef struct s_RecEncCBHandle 
{
	void* 						chaosHdle;
	void*						owner;
	RecEncHandle_t*	recHdle;
} RecEncCBHandle_t;

void *chaos_printf(char* data, void *user)
{
	cp_printf(" %s", data);
	return (void *)0;
}

void * chaos_msg_cb(PLAYER_MSG ID, void *data, void *user)
{
	RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)user;
	int result = true;
	
	if (ID != PLAYER_MSG_FB_EXT_MIDI_SET_SYNC)
		mus_printf("chaos_msg_cb-> ID=%d\n", ID);

	switch(ID)
	{
		case PLAYER_MSG_FB_CMD_PLAY:
		{
			mus_printf("chaos_msg_cb-> Play\n");
			cbhdle->recHdle->cb(cbhdle->recHdle->owner, RECENCODER_NOTIFY_PLAY, result, (int)cbhdle);
			break;
		}
		case PLAYER_MSG_FB_CMD_STOP_CAUSED_BY_ERROR:
		{
			// wait for app registered callback, for some very fast error stop callback
			krk_os_sys_sleep(3000, NULL);
			result = false;
		}
		case PLAYER_MSG_FB_CMD_STOP:
		{
			mus_printf("chaos_msg_cb-> STOP \n");
			cbhdle->recHdle->cb(cbhdle->recHdle->owner, RECENCODER_NOTIFY_STOPPED, result, (int)cbhdle);
			break;
		}
		case PLAYER_MSG_FB_CMD_PAUSE:
		{
			mus_printf("chaos_msg_cb-> Pause\n");
			cbhdle->recHdle->cb(cbhdle->recHdle->owner, RECENCODER_NOTIFY_PAUSED, result, (int)cbhdle);
			break;
		}
		case PLAYER_MSG_FB_CMD_RESUME:
		{
			mus_printf("chaos_msg_cb-> Resume\n");
			cbhdle->recHdle->cb(cbhdle->recHdle->owner, RECENCODER_NOTIFY_RESUMED, result, (int)cbhdle);
			break;
		}
		default:
		{
			break;
		}
	}
	return (void *)0;
}

static void recenc_lock(RecEncHandle_t* hdle)
{
	krk_os_sema_pend(&(hdle->vtlock), KRK_OS_WAIT, NULL);
}

static void recenc_unlock(RecEncHandle_t* hdle)
{
	krk_os_sema_post(&(hdle->vtlock), NULL);
}

void* recencoder_init(RecEncoderInitPara_t* para)
{
	RecEncHandle_t* hdle = (RecEncHandle_t*)calloc(1, sizeof(RecEncHandle_t));

	hdle->cbhdles = ez_vector_new(sizeof(RecEncCBHandle_t*), 0);
	
	if (krk_os_sema_create(&(hdle->vtlock), "enclock", 1, NULL) == KRK_OS_RET_FAIL)
	{
		mus_printf("Fail to create recenc lock\n");
		KRK_ASSERT(0);
	}
	memcpy(hdle->cidKey, para->cidKey, sizeof(hdle->cidKey));
	hdle->privateKey = para->privateKey;
	hdle->lameFlag = para->lameFlag;
	hdle->ringFlag = para->ringFlag;
	hdle->latency = para->latency;
	hdle->outlatency = para->outlatency;
	hdle->bitrate = para->bitrate;
	hdle->spSound = para->spSound;
	hdle->cb = para->cb;
	hdle->owner = para->owner;
	
	return hdle;
}

int recencoder_deinit(void* hdle)
{
	RecEncHandle_t* h = (RecEncHandle_t*)hdle;

	while (ez_vector_size(h->cbhdles))
	{
		RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)ez_vector_get(h->cbhdles, 0);
		
		PlayerFinish(cbhdle->chaosHdle);
		
		recenc_lock(h);
		ez_vector_erase(h->cbhdles, 0);
		recenc_unlock(h);
	}
	recenc_lock(h);
	ez_vector_free(h->cbhdles);
	recenc_unlock(h);
	krk_os_sema_destroy(&h->vtlock, NULL);
	free(h);
	return 0;
}

int recencoder_create(void* hdle, RecEncoderEncPara_t* para)
{
	RecEncHandle_t* h = (RecEncHandle_t*)hdle;
	PLAYER_PLAY_MODE PlayMode;
	int value = 0;
	PLAYER_VOCAL_STATUS VocalFade;
	PLAYER_ENCODER_TYPE Encoder;
	PLAYER_SOURCE_TYPE	SongSourceType;
	PLAYER_SOURCE_TYPE	RecSourceType;
	PLAYER_REC_TYPE RecType = PLAYER_REC_TYPE_REC_ADPCM;
	int inChannel = 2;
	int outChannel = 2;
	int inRate = 44100;
	int outRate = 44100;
	RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)calloc(1, sizeof(RecEncCBHandle_t));	
	void* chaosHdle = PlayerInit(0);
	PLAYER_RECORD_MODE recordmode = PLAYER_RECORD_MODE_MIXED_SONG;
	PLAYER_REPLAY_MODE replaymode = PLAYER_REPLAY_MODE_MIXED_SONG;

	cbhdle->chaosHdle = chaosHdle;
	cbhdle->recHdle = h;
	
	recenc_lock(h);
	ez_vector_pushback(h->cbhdles, &cbhdle);
	if (para->latency != 0) {
		h->latency = para->latency;
		h->outlatency = para->outLatency;
	}
	recenc_unlock(h);

	mus_printf("recencoder_create->\n");
	mus_printf("    >mixFlag=%d\n", para->mixFlag);
	mus_printf("    >MusVol=%d\n", para->MusVol);
	mus_printf("    >MelodyVol=%d\n", para->MelodyVol);
	mus_printf("    >RecVol=%d\n", para->RecVol);
	mus_printf("    >ReverbVol=%d\n", para->ReverbVol);
	mus_printf("    >spSound=%d\n", h->spSound);
	mus_printf("    >latency=%d\n", h->latency);
	mus_printf("    >outlatency=%d\n", h->outlatency);

	if (para->mixFlag)
	{
		recordmode = PLAYER_MIXED_RECORD_MODE_VOCAL_ONLY;
		replaymode = PLAYER_MIXED_REPLAY_MODE_VOCAL_ONLY;
	}

	PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_MODE, &recordmode);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_REPLAY_MODE, &replaymode);
	
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_LATENCY, &(h->latency));
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_OUTPUT_LATENCY, &(h->outlatency));

	PlayerMsg(chaosHdle, PLAYER_MSG_SET_FEEDBACK_PRINT_FUNC, (void *)chaos_printf); 
	PlayerMsg(chaosHdle, PLAYER_MSG_SET_FEEDBACK_MSG_FUNC,(void *)chaos_msg_cb);
	PlayerMsg(chaosHdle, PLAYER_MSG_SET_FEEDBACK_USER_DATA,(void *)cbhdle);
	value = 0;
	PlayerMsg(chaosHdle, PLAYER_MSG_SET_MUS_MIDI_ENABLE, (void *)&value);

	if (strlen(h->cidKey) != 0)
	{
		mus_printf("imusplayer _MusPlayerCreateRecEncoder, cidkey:%s\n", h->cidKey);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_SERIAL_NUMBER, (void*)h->cidKey);//����CID�����ܳ�
	}
	if (h->privateKey != NULL)
	{
		mus_printf("imusplayer _MusPlayerCreateRecEncoder, privateKey:%x\n", (unsigned int)(h->privateKey));
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_PRIVATE_KEY, (void*)h->privateKey);//����CID�����ܳ�
	}
	
	PlayMode = PLAYER_PLAY_MODE_ENCODE;
	VocalFade = PLAYER_VOCAL_OFF;
	if (krk_checksuffix(para->wavePath, "wav") == 0)
	{
		Encoder = PLAYER_ENCODER_TYPE_WAVE;
	}
	else if (krk_checksuffix(para->wavePath, "mp3") == 0)
	{
		if (h->lameFlag)
			Encoder = PLAYER_ENCODER_TYPE_MP3_LAME;
		else
			Encoder = PLAYER_ENCODER_TYPE_MP3_SHINE;
	}
	SongSourceType = PLAYER_SOURCE_TYPE_FILE;
	RecSourceType = PLAYER_SOURCE_TYPE_FILE;
	
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MIC_CHANNELS, &(inChannel));
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MIC_SAMPLE_RATE, &(inRate));
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SPK_CHANNELS, &(outChannel));
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SPK_SAMPLE_RATE, &(outRate));

	PlayerMsg (chaosHdle, PLAYER_MSG_SET_ECHO_VOLUME, &para->EchoVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SONG_SOURCE_TYPE, &SongSourceType);
	if (krk_checksuffix(para->filePath, "okf") == 0)
	{
		value = 1;
		PlayerMsg(chaosHdle, PLAYER_MSG_SET_MUS_FORCE_KSC, &value);
	}
	value = 0;
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUSIC_VOLUME, &para->MusVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_MIDI_VOLUME, &para->MusVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_MEDIA_VOLUME, &para->MusVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_MELODY_VOLUME, &para->MelodyVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUSIC_KEY, &para->Key);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUSIC_TEMPO, &para->Tempo);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_VOCAL_FADE, &VocalFade);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_SOURCE_TYPE, &RecSourceType);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_VOLUME, &para->RecVol);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODER_BITRATE, &h->bitrate);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SONG_NAME, para->songName);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SINGER_NAME, para->singerName);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_ALBUM_NAME, para->albumName);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_PLAY_MODE, &PlayMode);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODER_RING_MODE, &h->ringFlag);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_ENABLE, &h->spSound);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUS_REVERB_ENABLE, &value);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_AGC_ON, &h->spSound);
	PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_COMPRESS_ON, &h->spSound);

	if (h->spSound)
	{
		value = 100;
		if (para->mixFlag)
		{
			PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_MUSIC_VOL, &value);
			PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUSIC_VOLUME, &para->MusVol);
		}
		else 
		{
			PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_MUSIC_VOL, &para->MusVol);
			PlayerMsg (chaosHdle, PLAYER_MSG_SET_MUSIC_VOLUME, &value);
		}
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_KTV_VOL, &para->EchoVol);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_VOCAL_VOL, &para->RecVol);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_SP_SOUND_REV_VOL, &para->ReverbVol);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_VOLUME, &value);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD2_VOLUME, &value);
		value = 0;
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_ECHO_VOLUME, &value);
	}

	if (para->mixFlag)
	{
		RecType = PLAYER_REC_TYPE_MP3;
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_PATH, para->filePath);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_TYPE, &RecType);
		RecType = PLAYER_REC_TYPE_REC_ADPCM;
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD2_PATH, para->recPath);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD2_TYPE, &RecType);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODER, &Encoder);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODE_PATH, para->wavePath);
	}
	else
	{
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_SONG_PATH, para->filePath);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_SONG_TYPE, &(para->songType));
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_TYPE, &RecType);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_RECORD_PATH, para->recPath);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODER, &Encoder);
		PlayerMsg (chaosHdle, PLAYER_MSG_SET_ENCODE_PATH, para->wavePath);
	}

	PlayerMsg (chaosHdle, PLAYER_MSG_CMD_PLAY, NULL);

	return (int)cbhdle;
}


int recencoder_destroy(void* hdle, int id)
{
	RecEncHandle_t* h = (RecEncHandle_t*)hdle;
	RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)id;
	
	PlayerFinish(cbhdle->chaosHdle);
	
	recenc_lock(h);
	id = ez_vector_find_pos(h->cbhdles, &cbhdle);
	if (id != -1)
	{
		ez_vector_erase(h->cbhdles, id);
		free(cbhdle);
		recenc_unlock(h);
		return 0;
	}
	recenc_unlock(h);
	return -1;
}

int recencoder_pause(void* hdle, int id)
{
	if (id != 0)
	{
		RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)id;
		return PlayerMsg (cbhdle->chaosHdle, PLAYER_MSG_CMD_PAUSE, NULL);
	}
	return -1;
}

int recencoder_resume(void* hdle, int id)
{
	if (id != 0)
	{
		RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)id;
		return PlayerMsg (cbhdle->chaosHdle, PLAYER_MSG_CMD_RESUME, NULL);
	}
	return -1;
}

int recencoder_stop(void* hdle, int id)
{
	if (id != 0)
	{
		RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)id;
		return PlayerMsg (cbhdle->chaosHdle, PLAYER_MSG_CMD_STOP, NULL);
	}
	return -1;
}

int recencoder_getpercent(void* hdle, int id)
{
	if (id != 0)
	{
		RecEncCBHandle_t* cbhdle = (RecEncCBHandle_t*)id;
		int percent = 0;
		PlayerMsg (cbhdle->chaosHdle, PLAYER_MSG_GET_ENCODE_PERCENT, &percent);
		return percent;
	}
	return 0;
}

