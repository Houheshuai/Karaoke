/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : recencoder_service.c
** Revision : 1.00											
**																	
** Description: player service module
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

#include <k_global.h>
#include <player/customer_keys.h>
#include <recencoder/recencoder.h>
#include <recencoder/recencoder_service.h>

#define _WARN_NO_PLAYER(name) {service_printf("==================================\n");\
															service_printf("= no player in : service[%s]\n", name);\
															service_printf("==================================\n");}

/*
* private key value map
*/
ezServiceValMap_t gValMapEncPrivateKeys[] = 
{
	{(int)(&PRIVATE_KEY_IN_A), ENC_CMD_PLAY_PRIVATEKEY_IN},
	{(int)(&PRIVATE_KEY_RU_A), ENC_CMD_PLAY_PRIVATEKEY_RU},
	{(int)(&PRIVATE_KEY_NK_A), ENC_CMD_PLAY_PRIVATEKEY_NK},
	{(int)(&PRIVATE_KEY_MC_A), ENC_CMD_PLAY_PRIVATEKEY_MC},
};

/*
* lyric draw effect value map
*/
ezServiceValMap_t gValMapEncoderSongType[] = 
{
	{PLAYER_SONG_TYPE_PCM, ENC_CMD_ENCODE_SONG_TYPE_PCM},
	{PLAYER_SONG_TYPE_WAVE, ENC_CMD_ENCODE_SONG_TYPE_WAV},
	{PLAYER_SONG_TYPE_MP3, ENC_CMD_ENCODE_SONG_TYPE_MP3},
	{PLAYER_SONG_TYPE_AAC, ENC_CMD_ENCODE_SONG_TYPE_AAC},
	{PLAYER_SONG_TYPE_MIDI, ENC_CMD_ENCODE_SONG_TYPE_MIDI},
	{PLAYER_SONG_TYPE_MUS, ENC_CMD_ENCODE_SONG_TYPE_MUS},
	{PLAYER_SONG_TYPE_OKF_MP3, ENC_CMD_ENCODE_SONG_TYPE_OKFMP3},
};

//----------------------------------------------------------------------------//
static void recencoder_notify_callback(void* owner, int notify, int result, int id)
{
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)owner;
	char eventname[128];
	
	memset(eventname, 0, sizeof(eventname));

	switch (notify)
	{
		case RECENCODER_NOTIFY_PLAY:
		{
			sprintf(eventname, "%s-%d", ENC_EVENT_PLAY, id);
			break;
		}
		case RECENCODER_NOTIFY_PAUSED:
		{
			sprintf(eventname, "%s-%d", ENC_EVENT_PAUSED, id);
			break;
		}
		case RECENCODER_NOTIFY_RESUMED:
		{
			sprintf(eventname, "%s-%d", ENC_EVENT_RESUMED, id);
			break;
		}
		case RECENCODER_NOTIFY_STOPPED:
		{
			sprintf(eventname, "%s-%d", ENC_EVENT_STOPPED, id);
			break;
		}
		default:
		{
			return;
		}
	}
	
	{
		char sval[32];

		service_printf("recencoder_notify_callback : %s\n", eventname);
		
		itoa(id, sval, 10);
		hdle->setEventPara(hdle, eventname, ENC_EVENT_ENCODER_ID, sval);
		hdle->pushEvent(hdle, eventname, (ezServiceEventResult_et)result);
	}
}

//----------------------------------------------------------------------------//
static int recencoder_service_init(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;

	if (hdle->doer == NULL)
	{
		RecEncoderInitPara_t initPara;
		
		memset(&initPara, 0, sizeof(initPara));
		initPara.cb = recencoder_notify_callback;
		initPara.owner = hdle;
		
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_RINGFLAG, &(initPara.ringFlag));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_LAMEFLAG, &(initPara.lameFlag));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_LATENCY, &(initPara.latency));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_OUTLATENCY, &(initPara.outlatency));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_BITRATE, &(initPara.bitrate));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_SPSOUND, &(initPara.spSound));
		hdle->getCmdParaValueFromMap(hdle, cmdname, ENC_CMD_ENCODE_PRIVATEKEY, gValMapEncPrivateKeys, sizeof(gValMapEncPrivateKeys), (int*)(&(initPara.privateKey)));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_CIDKEY, initPara.cidKey, sizeof(initPara.cidKey));
		
		hdle->doer = recencoder_init(&initPara);
		if (hdle->doer != NULL)
		{
			result = ezServiceEvent_Succ;
			ret = ezService_Succ;
		}
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= recencoder service already initialized\n");
		service_printf("==================================\n");
	}
	
	hdle->pushEvent(hdle, ENC_EVENT_INIT, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int recencoder_service_deinit(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{	
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;
	
	if (hdle->doer != NULL)
	{
		ret = recencoder_deinit(hdle->doer);
		result = ezServiceEvent_Succ;
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= recencoder service already deinitialized\n");
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, ENC_EVENT_DEINIT, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int recencoder_service_createencoder(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		RecEncoderEncPara_t encPara;

		memset(&encPara, 0, sizeof(encPara));

		hdle->getCmdParaValueFromMap(hdle, cmdname, ENC_CMD_ENCODE_SONG_TYPE, gValMapEncoderSongType, sizeof(gValMapEncoderSongType), &(encPara.songType));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_SONG_NAME, encPara.songName, sizeof(encPara.songName));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_SINGER_NAME, encPara.singerName, sizeof(encPara.singerName));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_ALBUM_NAME, encPara.albumName, sizeof(encPara.albumName));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_FILE_PATH, encPara.filePath, sizeof(encPara.filePath));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_REC_PATH, encPara.recPath, sizeof(encPara.recPath));
		hdle->getCmdParaValueStr(hdle, cmdname, ENC_CMD_ENCODE_OUT_FILE, encPara.wavePath, sizeof(encPara.wavePath));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_SONG_INDEX, &(encPara.songIndex));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_ECHO, &(encPara.EchoVol));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_MUSIC, &(encPara.MusVol));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_REVERB, &(encPara.ReverbVol));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_RHYTHM, &(encPara.MelodyVol));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_TONE, &(encPara.Key));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_TEMPO, &(encPara.Tempo));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_REC, &(encPara.RecVol));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_MIXFLAG, &(encPara.mixFlag));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_LATENCY, &(encPara.latency));
		hdle->getCmdParaValueInt(hdle, cmdname, ENC_CMD_ENCODE_OUTLATENCY, &(encPara.outLatency));
		ret = recencoder_create(hdle->doer, &encPara);
		if (ret != 0)
			result = ezServiceEvent_Succ;
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_CREATE, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int recencoder_service_destroyencoder(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		if (para != NULL)
		{
			int id = atoi(para);
			ret = recencoder_destroy(hdle->doer, id);
			if (ret != 0)
				result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, ENC_EVENT_DESTROY);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_DESTROY, result);
	return ret;
}


//----------------------------------------------------------------------------//
static int recencoder_service_stopencoder(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		if (para != NULL)
		{
			int id = atoi(para);
			ret = recencoder_stop(hdle->doer, id);
			if (ret != 0)
				result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, ENC_EVENT_STOP);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_STOP, result);
	return ret;
}


//----------------------------------------------------------------------------//
static int recencoder_service_pauseencoder(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		if (para != NULL)
		{
			int id = atoi(para);
			ret = recencoder_pause(hdle->doer, id);
			if (ret != 0)
				result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, ENC_EVENT_PAUSE);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_PAUSE, result);
	return ret;
}


//----------------------------------------------------------------------------//
static int recencoder_service_resumeencoder(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		if (para != NULL)
		{
			int id = atoi(para);
			ret = recencoder_resume(hdle->doer, id);
			if (ret != 0)
				result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, ENC_EVENT_RESUME);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_RESUME, result);
	return ret;
}


//----------------------------------------------------------------------------//
static int recencoder_service_getpercent(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;
	if (hdle->doer != NULL)
	{
		if (para != NULL)
		{
			int id = atoi(para);
			ret = recencoder_getpercent(hdle->doer, id);
			result = ezServiceEvent_Succ;
		}
		else
		{
			_WARN_NO_PARA(hdle->name, ENC_EVENT_GETPERCENT);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, ENC_EVENT_GETPERCENT, result);
	return ret;
}


//----------------------------------------------------------------------------//
EZ_SERVICE_BEGIN_CMD_EXEC_MAP(recencoderService) 
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_INIT,							recencoder_service_init)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_DEINIT,						recencoder_service_deinit)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_CREATE,						recencoder_service_createencoder)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_DESTROY,					recencoder_service_destroyencoder)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_STOP,							recencoder_service_stopencoder)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_PAUSE,						recencoder_service_pauseencoder)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_RESUME,						recencoder_service_resumeencoder)
	EZ_SERVICE_ADD_CMD_EXEC(ENC_CMD_GETPERCENT,				recencoder_service_getpercent)
EZ_SERVICE_END_CMD_EXEC_MAP()
//----------------------------------------------------------------------------//

