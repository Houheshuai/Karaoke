/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : player_core.c
** Revision : 1.00											
**																	
** Description: player core module
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
#include <lib/ezbase/ez_service.h>
#include <player/player_core.h>
#include <player/player_service.h>
#include <player/audio_config.h>
//#include <kkedev/kkedev_audio_if.h>
//#include "FakeAudio.h"

CP_AudioIFs* gAudioIF = NULL;				// default audio IF
void* gAudioHandle = NULL;					// default audio handle

iMusPlayerExtConfig_t gMusExtConfig = 
{
	{"d:\\ResMIC\\player720p.res"},
	0,
	NULL,
	NULL,
	1,
};

iMediaConfig_t gMMExtConfig = 
{
	0, 0, 1, 0, NULL, NULL
};

static iMusPlayerExtConfig_t *player_mus_config(const char* resFile, int Lan)
{
	iMusPlayerExtConfig_t *iMusExtPara;
	iMusExtPara = &gMusExtConfig;
	memset(iMusExtPara->resFile, 0, sizeof(iMusExtPara->resFile));
	strncpy(iMusExtPara->resFile, resFile, sizeof(iMusExtPara->resFile)-1);
	iMusExtPara->UILanguage = Lan;
	if (iMusExtPara->audioIF == NULL)
		iMusExtPara->audioIF = audioConfig_getDefaultAudioIFs();
	return iMusExtPara;
}

static iMediaConfig_t* player_media_config(void)
{
	iMediaConfig_t *iMMExtPara;
	iMMExtPara = &gMMExtConfig;
	if (iMMExtPara->audioIF == NULL)
		iMMExtPara->audioIF = audioConfig_getDefaultAudioIFs();
	return iMMExtPara;
}

/*
*****************************************************
*	media player registery routines
*****************************************************
*/

static ezPlayer_t* 
cb_MediaPlayerNew(void* para, void* owner)
{
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)(owner);
	ezPlayer_t* player = NULL;

	if (owner != NULL)
	{
		player = (ezPlayer_t*)MediaPlayerNew(para, owner);
	}
	return player;
}

static void 
cb_MediaPlayerFree(ezPlayer_t* player)
{
	MediaPlayerFree((MediaPlayer_t *)player);
}

static void* 
cb_MediaPlayerStartParse(ezPlayer_t* player, void* playPara)
{
	return playPara;
}

static void* 
cb_MediaPlayerEndParse(ezPlayer_t* player, void* para)
{
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)(player->owner);
	return NULL;
}

/*
*	media player registery
*/
static playerRegistry_t regMediaPlayer = 
{
	NULL,//player;
	PLAYER_TYPE_VIDEO,//type;
	1,
	".avi.mpg.mkv.vob.rmvb.rm.mp4.cdg",//suffix;
	NULL,//createPara;
	NULL,//parsePara;
	cb_MediaPlayerNew,//new;
	cb_MediaPlayerFree,//free;
	cb_MediaPlayerStartParse,//startParse;
	cb_MediaPlayerEndParse,//endParse;
};

static ezPlayer_t* 
cb_MusPlayerNew(void* para, void* owner)
{
	ezPlayer_t* player = NULL;
	
	if (owner != NULL)
	{
		player = (ezPlayer_t*)MusPlayerNew(para, owner);
	}
	return player;
}

static void 
cb_MusPlayerFree(ezPlayer_t* player)
{
	MusPlayerFree((MusPlayer_t *)player);
}

static void* 
cb_MusPlayerStartParse(ezPlayer_t* ep, void* playPara)
{
	return playPara;
}

static void* 
cb_MusPlayerStopParse(ezPlayer_t* player, void* para)
{
	return NULL;
}

/*
*	mus player registery
*/
static playerRegistry_t regMusPlayer = 
{
	NULL,//player;
	PLAYER_TYPE_MUS,//type;
	1,
	".mus.muk.dat.mp3.aac.wav.duet",//suffix;
	NULL,//createPara;
	NULL,//parsePara;
	cb_MusPlayerNew,//new;
	cb_MusPlayerFree,//free;
	cb_MusPlayerStartParse,//startParse;
	cb_MusPlayerStopParse,//endParse;
};

/*
*****************************************************
*	register all player to batch player of application MIC
*****************************************************
*/
static void player_register_all(BatchPlayer_t* bp, const char* resFile, int lan)
{
	regMusPlayer.createPara = player_mus_config(resFile, lan);
	regMediaPlayer.createPara = player_media_config();
	
	bp->regPlayer(bp, &regMediaPlayer);
	bp->regPlayer(bp, &regMusPlayer);
}

/*
 * Function name  	: handlePlayerEvent
 * Arguments      	: args - event argument
 * Return         	: none
 * Description    	: player event callback function
 *					
*/
static int handlePlayerEvent(NotifyEventArgs_t* args)
{
	ezPlayer_t* player = (ezPlayer_t*)(args->owner);
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)(player->owner);
	char* eventname;
	char value[32];

	switch (args->notify.notifyId)
	{
		case EZPLAYER_NOTIFY_ERROR:
		{
			eventname = (char*)PLY_EVENT_ERROR;
			break;
		}
		case EZPLAYER_NOTIFY_PLAY:
		{
			eventname = (char*)PLY_EVENT_PLAY;
			break;
		}
		case EZPLAYER_NOTIFY_STOP:
		{
			itoa(args->notify.para[0],value,10);
			eventname = (char*)PLY_EVENT_STOP;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STOP_PARA_SCORE, value);
			mus_printf("EZPLAYER_NOTIFY_STOP: %d, %s\n", args->notify.result, value);
			break;
		}
		case EZPLAYER_NOTIFY_PAUSE:
		{
			eventname = (char*)PLY_EVENT_PAUSE;
			break;
		}
		case EZPLAYER_NOTIFY_RESUME:
		{
			eventname = (char*)PLY_EVENT_RESUME;
			break;
		}
		case EZPLAYER_NOTIFY_SETVOCAL:
		{
			eventname = (char*)PLY_EVENT_SETVOCAL;
			break;
		}
		case EZPLAYER_NOTIFY_SETVOL:
		{
			eventname = (char*)PLY_EVENT_SETVOL;
			break;
		}
		case EZPLAYER_NOTIFY_SETMUTE:
		{
			eventname = (char*)PLY_EVENT_SETMUTE;
			break;
		}
		case MUSPLAYER_NOTIFY_SETMICPARA:
		{
			eventname = (char*)PLY_EVENT_SETMIC;
			break;
		}
		case MUSPLAYER_NOTIFY_SETLYRIC:
		{
			eventname = (char*)PLY_EVENT_SETLYRIC;
			break;
		}
		case MUSPLAYER_NOTIFY_SETSCORE:
		{
			eventname = (char*)PLY_EVENT_SETSCORE;
			break;
		}
		case MUSPLAYER_NOTIFY_SETIFUN:
		{
			eventname = (char*)PLY_EVENT_SETSTAFF;
			break;
		}
		case MUSPLAYER_NOTIFY_TITLEINF_END:
		{
			eventname = (char*)PLY_EVENT_TITLEINF_END;
			break;
		}
		case MUSPLAYER_NOTIFY_INTERLUDE_BEGIN:
		{
			eventname = (char*)PLY_EVENT_INTERLUDE_BEGIN;
			break;
		}
		case MUSPLAYER_NOTIFY_INTERLUDE_END:
		{
			eventname = (char*)PLY_EVENT_INTERLUDE_END;
			break;
		}
		case MUSPLAYER_NOTIFY_AUTOSEEK_END:
		{
			eventname = (char*)PLY_EVENT_AUTOSEEK;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_AUTOSEEK_ENDPARA, (char*)PLY_EVENT_AUTOSEEK_ENDPARA_END);
			break;
		}
		case MUSPLAYER_NOTIFY_AUTOSEEK_LAST:
		{
			eventname = (char*)PLY_EVENT_AUTOSEEK;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_AUTOSEEK_ENDPARA, (char*)PLY_EVENT_AUTOSEEK_ENDPARA_LAST);
			break;
		}
		case MUSPLAYER_NOTIFY_AUTOSEEK_ERR:
		{
			eventname = (char*)PLY_EVENT_AUTOSEEK;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_AUTOSEEK_ENDPARA, (char*)PLY_EVENT_AUTOSEEK_ENDPARA_ERR);
			break;
		}
		case MUSPLAYER_NOTIFY_LATENCYVALUE:
		{
			itoa(args->notify.para[0],value,10);
			eventname = (char*)PLY_EVENT_TESTLATENCY;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_TESTLATENCY_LATENCY, value);
			mus_printf("MUSPLAYER_NOTIFY_LATENCYVALUE: %s\n", value);
			break;
		}
		case MUSPLAYER_NOTIFY_SAVE_FILE:
		{
			eventname = (char*)PLY_EVENT_SAVE_FILE;
			break;
		}
		case MUSPLAYER_NOTIFY_LYRICPERCENT:
		{
			drawLyricInfo_t* info = (drawLyricInfo_t*)(args->notify.para[0]);
			eventname = (char*)PLY_EVENT_LYRICPERCENT;
			itoa(info->LineNumber,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICPERCENT_PARA_LINENO, value);
			itoa(info->LinePercent,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICPERCENT_PARA_LINEPERCENT, value);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICPERCENT_PARA_LINESTR, info->LyricStr.string);
			//mus_printf("MUSPLAYER_NOTIFY_LYRICPERCENT: %s, %d\n", info->LyricStr.string, info->LinePercent);
			hdle->pushEvent(hdle, eventname, args->notify.result);
			hdle->fireEvent(hdle, eventname);
			return KRK_RET_SUCC;
		}
		case MUSPLAYER_NOTIFY_LYRICCHANGE:
		{
			drawLyricInfo_t* info = (drawLyricInfo_t*)(args->notify.para[0]);
			eventname = (char*)PLY_EVENT_LYRICCHANGED;
			itoa(info->LineNumber,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICCHANGE_PARA_LINENO, value);
			itoa(info->LinePercent,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICCHANGE_PARA_LINEPERCENT, value);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_LYRICCHANGE_PARA_LINESTR, info->LyricStr.string);
			//mus_printf("MUSPLAYER_NOTIFY_LYRICCHANGE: %s\n", value);
			break;
		}
		case MUSPLAYER_NOTIFY_STAFF_ADDSEG:
		{
			M_STAFF_SEG_INFO* info = (M_STAFF_SEG_INFO*)(args->notify.para[0]);
			eventname = (char*)PLY_EVENT_STAFFADDSEG;
			itoa(info->SegMode,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STAFFADDSEG_PARA_MODE, value);
			itoa(info->SegYNoteKey,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STAFFADDSEG_PARA_YNOTEKEY, value);
			itoa(info->SegXBegin,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STAFFADDSEG_PARA_XBEGIN, value);
			itoa(info->SegLen,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STAFFADDSEG_PARA_XLEN, value);
			itoa(info->SegHeadDraw,value,10);
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_STAFFADDSEG_PARA_HEADDRAW, value);
			//mus_printf("MUSPLAYER_NOTIFY_STAFF_ADDSEG: %s\n", value);
			break;
		}		
		case MUSPLAYER_NOTIFY_STAFFSHOW:
		{
			eventname = (char*)PLY_EVENT_STAFFSHOW;
			//mus_printf("MUSPLAYER_NOTIFY_STAFFSHOW\n");
			break;
		}
		case MUSPLAYER_NOTIFY_STAFFHIDE:
		{
			eventname = (char*)PLY_EVENT_STAFFHIDE;
			//mus_printf("MUSPLAYER_NOTIFY_STAFFHIDE\n");
			break;
		}
		case MUSPLAYER_NOTIFY_DRAW_HINTBALL:
		{
			itoa(args->notify.para[0],value,10);
			eventname = (char*)PLY_EVENT_DRAW_HINTBALL;
			hdle->setEventPara(hdle, eventname, (char*)PLY_EVENT_DRAW_HINTBALL_NUM, value);
			mus_printf("MUSPLAYER_NOTIFY_DRAW_HINTBALL: %d, %s\n", args->notify.result, value);
			break;
		}
		case MUSPLAYER_NOTIFY_CLEAR_HINTBALL:
		{
			eventname = (char*)PLY_EVENT_CLEAR_HINTBALL;
			//mus_printf("MUSPLAYER_NOTIFY_CLEAR_HINTBALL\n");
			break;
		}
		case MUSPLAYER_NOTIFY_LYRIC_LOADED:
		{
			eventname = (char*)PLY_EVENT_LYRIC_LOADED;
			mus_printf("MUSPLAYER_NOTIFY_LYRIC_LOADED\n");
			break;
		}
		case MUSPLAYER_NOTIFY_SEND_SEXTYPE:
		{
			eventname = (char*)PLY_EVENT_SEND_SEXTYPE;
			break;
		}
		default:
		{
			return KRK_RET_SUCC;
		}
	}
	if (hdle->getEventCallback(hdle, eventname) != NULL) {
		//mus_printf("pushEvent-> %s\n", eventname);
		hdle->pushEvent(hdle, eventname, args->notify.result);
	}
	return KRK_RET_SUCC;
}

/*
 * Function name  	: player_audio_init
 * Arguments      	: audioIFName - audio interface name
 * Return         	: 0 - fail, 1 - standard, 2 - embeded
 * Description    	: initialize audio interface
 *					
*/
int player_audio_init(const char* audioIFName)
{
	CP_AudioIFs* audioIF;
	void* audioHdle;
	int ret;

	mus_printf("player_audio_init\n");
	
	audioIF = audioConfig_initAudioIF(audioIFName);

	if (audioIF != NULL)
	{
		if (audioConfig_isEmbeddedAudioIFs())
			ret = 2;
		else
			ret = 1;
	}
	else {
		audioIF = audioConfig_getDefaultAudioIFs();
		ret = 0;
	}

	if (audioIF != NULL)
	{
		audioHdle = audioIF->init(48000);
		
		gMMExtConfig.audioHdle = audioHdle;
		gMMExtConfig.audioIF = audioIF;
		gMusExtConfig.audioHandle = audioHdle;
		gMusExtConfig.audioIF = audioIF;
		gAudioIF = audioIF;
		gAudioHandle = audioHdle;
	}
	return ret;
}

/*
 * Function name  	: player_audio_deinit
 * Arguments      	: none
 * Return         	: 0 - succ, <>0 error code
 * Description    	: deinitialize audio interface
 *					
*/
int player_audio_deinit(void)
{
	if (gAudioHandle != NULL && gAudioIF != NULL)
	{
		gAudioIF->finish(gAudioHandle);
		mus_printf("player_audio_deinit\n");
	}
	else
	{
		mus_printf("player_audio_deinit already called\n");
	}
	gMMExtConfig.audioHdle = NULL;
	gMMExtConfig.audioIF = NULL;
	gMusExtConfig.audioHandle = NULL;
	gMusExtConfig.audioIF = NULL;
	return 0;
}

/*
 * Function name  	: player_audio_setup
 * Arguments      	: 
 *									inrate - input samplerate
 *									outrate - output samplerate
 *									inchannels - input channels
 *									outchannels - output channels
 * Return         	: 0 - succ, <>0 error code
 * Description    	: setup audio samplerate and channels
 *					
*/
int player_audio_setup(int inrate, int outrate, int inchannels, int outchannels)
{
	audioConfig_setupIF(inrate, outrate, inchannels, outchannels);
	return 0;
}

/*
 * Function name  	: player_audio_get_param
 * Arguments      	: player - player handle
 *									inrate - input samplerate
 *									outrate - output samplerate
 *									inchannels - input channels
 *									outchannels - output channels
 * Return         	: none
 * Description    	: get embedded audio parameters
 *					
*/
void player_audio_get_param(int* inrate, int* outrate, int* inchannels, int* outchannels)
{
	audioConfig_getEmbeddedAudioParam(inrate, outrate, inchannels, outchannels);
}

/*
 * Function name  	: player_audio_change_if
 * Arguments      	: bp - batchplayer, playRec - playback record flag, audioType - audio IF type
 * Return         	: 0 - succ, <>0 error code
 * Description    	: change audio interface
 *					
*/
int player_audio_change_if(BatchPlayer_t* bp, int playRec, int audioType)
{

	if (bp != NULL)
	{
		CP_AudioIFs* audioIF;
		void* audioHdle;
		void* playerHdle;
		ezPlayer_t* player;

		//KKEAudio_SetRecFlag(playRec);

		switch (audioType)
		{
			case AUDIO_TYPE_KKEBOX:
			{
				audioIF = audioConfig_getAudioIFs(AUDIO_IF_KKEBOX);
				audioHdle = gAudioHandle;
				break;
			}
			case AUDIO_TYPE_KKEMINI:
			{
				audioIF = audioConfig_getAudioIFs(AUDIO_IF_KKEMINI);
				audioHdle = audioIF->init(48000);
				break;
			}
			default:
			{
				audioIF = gAudioIF;
				audioHdle = gAudioHandle;
				break;
			}
		}
		mus_printf("player_audio_change_if, audioIF=%x, audioHdle=%x\n", audioIF, audioHdle);
		
		player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			iMusPlayerPlayPara_t *musPara = (iMusPlayerPlayPara_t *)(player->param);
			musPara->audioIF = audioIF;
			musPara->audioHdle = audioHdle;
			playerHdle = musPara->playerHdle;
			if (playerHdle != NULL) {
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_HANDLE,audioHdle);
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_OPEN,(void *)audioIF->srcopen);		 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_CLOSE,(void *)audioIF->srcclose);	 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_READ,(void *)audioIF->srcread);	
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_OPEN,(void *)audioIF->sinkopen);		 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_CLOSE,(void *)audioIF->sinkclose);	 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_WRITE,(void *)audioIF->sinkwrite);
			}
		}

		player = bp->getPlayerByType(bp, PLAYER_TYPE_VIDEO);
		if (player != NULL)
		{
			iMMPlayerPara_t* mmPara = (iMMPlayerPara_t*)(player->param);
			mmPara->audioIF = audioIF;
			mmPara->audioHdle = audioHdle;
			playerHdle = mmPara->playerHdle;
			if (playerHdle != NULL) {
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_HANDLE,audioHdle);
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_OPEN,(void *)audioIF->srcopen);		 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_CLOSE,(void *)audioIF->srcclose);	 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_READ,(void *)audioIF->srcread);	
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_OPEN,(void *)audioIF->sinkopen);		 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_CLOSE,(void *)audioIF->sinkclose);	 
				PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_OUT_WRITE,(void *)audioIF->sinkwrite);
			}
		}

		gMMExtConfig.audioHdle = audioHdle;
		gMMExtConfig.audioIF = audioIF;
		gMusExtConfig.audioHandle = audioHdle;
		gMusExtConfig.audioIF = audioIF;

		//PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_OPEN,(void *)FakeAudioIn_Open);		 
		//PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_CLOSE,(void *)FakeAudioIn_Close);	 
		//PlayerMsg (playerHdle, PLAYER_MSG_SET_AUDIO_IN_READ,(void *)FakeAudioIn_Read);	
		
		mus_printf("player_audio_change_if, playrec=%d, audiotype=%d\n", playRec, audioType);
	}
	return 0;
}

/*
 * Function name  	: player_audio_get_cur_if
 * Arguments      	: none
 * Return         	: audio interface
 * Description    	: get current audio interface
 *					
*/
void* player_audio_get_cur_if(void)
{
	return gMusExtConfig.audioIF;
}

/*
 * Function name  	: player_audio_get_cur_handle
 * Arguments      	: none
 * Return         	: audio handle
 * Description    	: get current audio handle
 *					
*/
void* player_audio_get_cur_handle(void)
{
	return gMusExtConfig.audioHandle;
}

BatchPlayer_t* player_core_init(void* owner, const char* resFile, int lan)
{
	BatchPlayer_t* batchPlayer = BatchPlayerNew(owner);
	
	if (batchPlayer != NULL)
	{
		int id;

		for (id=EZPLAYER_NOTIFY_NONE+1; id<EZPLAYER_NOTIFY_COUNT; id++)
			batchPlayer->addEvent(batchPlayer, id, handlePlayerEvent);
		for (id=MUSPLAYER_NOTIFY_NONE+1; id<MUSPLAYER_NOTIFY_COUNT; id++)
			batchPlayer->addEvent(batchPlayer, id, handlePlayerEvent);
		
		player_register_all(batchPlayer, resFile, lan);
		
		batchPlayer->setPlayer(batchPlayer, PLAYER_TYPE_MUS);
#ifdef	PLAY_MUS_RAMFILE
		ez_ramfile_mount("r:\\");
#endif
	}
	return batchPlayer;
}

/*
 * Function name  	: player_core_deinit
 * Arguments      	: player - player handle
 * Return         	: 0 - succ, <>0 error code
 * Description    	: deinitialize player
 *					
*/
int player_core_deinit(BatchPlayer_t* player)
{
	if (player != NULL)
	{
		if (player->getPlayer(player) != NULL)
		{
			player->getPlayer(player)->reqNotify.clearEvent(&(player->getPlayer(player)->reqNotify));
		}
		player->setPlayer(player, -1);
		BatchPlayerFree(player);
#ifdef	PLAY_MUS_RAMFILE
		ez_ramfile_unmount("r:\\");
#endif
	}
	return 0;
}

