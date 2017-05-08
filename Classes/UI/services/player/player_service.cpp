/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : player_service.c
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
#include <player/player_core.h>
#include <player/player_service.h>
#include <player/voice_record.h>

#define _WARN_NO_PLAYER(name) {service_printf("==================================\n");\
															service_printf("= no player in : service[%s]\n", name);\
															service_printf("==================================\n");}


/*
* vol type name strings
*/
const char* gSetVolTypeNames[EZPLAYER_VOL_COUNT] = 
{
	PLY_CMD_SETVOL_TOTAL,
	PLY_CMD_SETVOL_VOICE,
	PLY_CMD_SETVOL_REVERB,
	PLY_CMD_SETVOL_MIDI,
	PLY_CMD_SETVOL_ACCOM,
	PLY_CMD_SETVOL_MICL,
	PLY_CMD_SETVOL_MICR,
	PLY_CMD_SETVOL_WMICL,
	PLY_CMD_SETVOL_WMICR,
	PLY_CMD_SETVOL_RHYTHM,
	PLY_CMD_SETVOL_REC,
	PLY_CMD_SETVOL_ECHO,
	PLY_CMD_SETVOL_DELAY,
	PLY_CMD_SETVOL_TONE,
	PLY_CMD_SETVOL_TEMPO,
	
	/*
	EZPLAYER_VOL_MUSIC,      // follow  ezPlayerVolType_et
	
	EZPLAYER_VOL_BBEEN,
	EZPLAYER_VOL_BBELEVEL,
	EZPLAYER_VOL_AGCEN,
	EZPLAYER_VOL_AGCGAIN,
	EZPLAYER_VOL_MICIN,
	
	EZPLAYER_VOL_EQ100,
	EZPLAYER_VOL_EQ1K,
	EZPLAYER_VOL_EQ5K,
	*/
};

/*
* songmode value map
*/
ezServiceValMap_t gValMapSongMode[] = 
{
	{MusPlayMode_Song, PLY_CMD_PLAY_PLAY_MODE_SONG},
	{MusPlayMode_Rec, PLY_CMD_PLAY_PLAY_MODE_REC},
};

/*
* score level value map
*/
ezServiceValMap_t gValMapScoreLevel[] = 
{
	{MusScoreLevel_Easy, PLY_CMD_PLAY_SCORE_LEVEL_EASY},
	{MusScoreLevel_Normal, PLY_CMD_PLAY_SCORE_LEVEL_NORMAL},
	{MusScoreLevel_Hard, PLY_CMD_PLAY_SCORE_LEVEL_HARD},
};

/*
* on/off switch value map
*/
ezServiceValMap_t gValMapOnOff[] = 
{
	{0, PLY_CMD_PARA_VALUE_OFF},
	{1, PLY_CMD_PARA_VALUE_ON},
};

/*
* private key value map
*/
ezServiceValMap_t gValMapPrivateKeys[] = 
{
	{(int)(&PRIVATE_KEY_IN_A), PLY_CMD_PLAY_PRIVATEKEY_IN},
	{(int)(&PRIVATE_KEY_RU_A), PLY_CMD_PLAY_PRIVATEKEY_RU},
	{(int)(&PRIVATE_KEY_NK_A), PLY_CMD_PLAY_PRIVATEKEY_NK},
	{(int)(&PRIVATE_KEY_MC_A), PLY_CMD_PLAY_PRIVATEKEY_MC},
};

/*
* mus subtype value map
*/
ezServiceValMap_t gValMapMusSubType[] = 
{
	{MUKSubFileType_MIDI, PLY_CMD_PLAY_MUSSUBTYPE_MIDI},
	{MUKSubFileType_MIDIMP3, PLY_CMD_PLAY_MUSSUBTYPE_MIDIMP3},
	{MUKSubFileType_KSC, PLY_CMD_PLAY_MUSSUBTYPE_KSC},
	{MUKSubFileType_CDG, PLY_CMD_PLAY_MUSSUBTYPE_CDG},
	{MUKSubFileType_LRC, PLY_CMD_PLAY_MUSSUBTYPE_LRC},
	{MUKSubFileType_KSC_TEXT, PLY_CMD_PLAY_MUSSUBTYPE_KSC_TEXT},
	{MUKSubFileType_LYC, PLY_CMD_PLAY_MUSSUBTYPE_LYC},
};

/*
* vocal type value map
*/
ezServiceValMap_t gValMapVocalType[] = 
{
	{EZPLAYER_VOCAL_OFF, PLY_CMD_SETVOCAL_VOCAL_OFF},
	{EZPLAYER_VOCAL_ON, PLY_CMD_SETVOCAL_VOCAL_ON},
	{EZPLAYER_VOCAL_AUTO, PLY_CMD_SETVOCAL_VOCAL_AUTO},
};

/*
* lyric on/off value map
*/
ezServiceValMap_t gValMapLyricOnOff[] = 
{
	{EZPLAYER_LYRIC_OFF, PLY_CMD_SETLYRIC_SHOW_OFF},
	{EZPLAYER_LYRIC_ON, PLY_CMD_SETLYRIC_SHOW_ON},
	{EZPLAYER_LYRIC_MAIN_ON, PLY_CMD_SETLYRIC_SHOW_ONLYMAIN},
	{EZPLAYER_LYRIC_LABEL_ON, PLY_CMD_SETLYRIC_SHOW_ONLYLABEL},
};

/*
* lyric on/off value map
*/
ezServiceValMap_t gValMapLyricAlign[] = 
{
	{LyricAlign_Side, PLY_CMD_SETLYRIC_ALIGN_SIDE},
	{LyricAlign_Middle, PLY_CMD_SETLYRIC_ALIGN_MIDDLE},
};

/*
* lyric draw effect value map
*/
ezServiceValMap_t gValMapLyricDrawEffect[] = 
{
	{LyricDrawEffect_Normal, PLY_CMD_SETLYRIC_EFFECT_DEFAULT},
	{LyricDrawEffect_GLShadow, PLY_CMD_SETLYRIC_EFFECT_SHADOW},
	{LyricDrawEffect_GLFrame, PLY_CMD_SETLYRIC_EFFECT_FRAME},
};

/*
* lyric font
*/
ezServiceValMap_t gValMapLyricFont[] = 
{
	{0, "ArialUni"},
	{1, "Segoe"},
	{2, "Times"},
};

/*
* audioType value map
*/
ezServiceValMap_t gValMapAudioType[] = 
{
	{AUDIO_TYPE_STANDARD, PLY_CMD_CHANGEAUDIF_DEFAULT},
	{AUDIO_TYPE_KKEBOX, PLY_CMD_CHANGEAUDIF_KKEBOX},
	{AUDIO_TYPE_KKEMINI, PLY_CMD_CHANGEAUDIF_KKEMINI},
};

/*
* record format value map
*/
ezServiceValMap_t gValMapRecFmt[] = 
{
	{PLAYER_REC_TYPE_REC_ADPCM, PLY_CMD_PLAY_RECFMT_ADPCM},
	{PLAYER_REC_TYPE_REC_SBC, PLY_CMD_PLAY_RECFMT_SBC},
	{PLAYER_REC_TYPE_MP3, PLY_CMD_PLAY_RECFMT_MP3},
	{PLAYER_REC_TYPE_REC_AAC, PLY_CMD_PLAY_RECFMT_AAC},
};

/*
* record encoder format value map
*/
ezServiceValMap_t gValMapRecEncFmt[] = 
{
	{PLAYER_ENCODER_TYPE_WAVE, PLY_CMD_PLAY_RECENCFMT_WAV},
	{PLAYER_ENCODER_TYPE_REC_ADPCM, PLY_CMD_PLAY_RECENCFMT_ADPCM},
	{PLAYER_ENCODER_TYPE_MP3_LAME, PLY_CMD_PLAY_RECENCFMT_MP3},
	{PLAYER_ENCODER_TYPE_CUSTOM, PLY_CMD_PLAY_RECENCFMT_AAC},
};

/*
* player type value map
*/
ezServiceValMap_t gValMapPlayerType[] = 
{
	{PLAYER_TYPE_VIDEO, PLY_CMD_SETPLAYERTYPE_TYPE_VIDEO},
	{PLAYER_TYPE_MUS, PLY_CMD_SETPLAYERTYPE_TYPE_MUS},
	{PLAYER_TYPE_MUSIC, PLY_CMD_SETPLAYERTYPE_TYPE_MUSIC},
	{PLAYER_TYPE_PICTURE, PLY_CMD_SETPLAYERTYPE_TYPE_PICTURE},
};

/*
* player type value map
*/
ezServiceValMap_t gValMapBgvType[] = 
{
	{BGV_TYPE_NONE, "none"},
	{BGV_TYPE_VIDEO, PLY_CMD_SETPLAYERTYPE_TYPE_VIDEO},
	{BGV_TYPE_PIC, PLY_CMD_SETPLAYERTYPE_TYPE_PICTURE},
};

/*
* player type value map
*/
ezServiceValMap_t gPlayBgvMode[] = 
{
	{BGV_PLAY_FROM_LAST_STOPPED, PLY_CMD_PLAYBGV_MODE_CURRNET},
	{BGV_PLAY_FROM_BEGINNING, PLY_CMD_PLAYBGV_MODE_FIRST},
	{BGV_PLAY_FROM_NEXT, PLY_CMD_PLAYBGV_MODE_NEXT},
	{BGV_PLAY_FROM_RANDOM, PLY_CMD_PLAYBGV_MODE_RANDOM},
};

/*
* player service doer handle
*/
typedef struct {
	BatchPlayer_t* 	bp;
	//BgvPlayer_t* 		bgv;
	int						seperateUpdate;
} playerServiceHandle_t;
 
//----------------------------------------------------------------------------//
static void player_service_voicerecord_mute_cb(void* owner, void* data)
{
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)owner;
	int unmute = *((int*)data);

	if (unmute)
		hdle->pushEvent(hdle, PLY_EVENT_VOICERECORD_MUTE, ezServiceEvent_Succ);
}
 
//----------------------------------------------------------------------------//
static void player_service_voicerecord_read_cb(void* owner, void* data, int size)
{
	ezServiceHandle_t* hdle = (ezServiceHandle_t*)owner;

	hdle->pushEvent(hdle, PLY_EVENT_VOICERECORD_READ, ezServiceEvent_Succ);
}

//----------------------------------------------------------------------------//
static int player_service_update(ezServiceHandle_t* hdle, int timeElapsed)
{
	if (hdle->doer != NULL)
	{
		playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
		/*if (playerHdle->bgv != NULL 
			&& playerHdle->bgv->player != NULL 
			&& playerHdle->bgv->player->update != NULL)
			playerHdle->bgv->player->update(playerHdle->bgv->player, timeElapsed);*/
		if (playerHdle->bp != NULL 
			&& playerHdle->bp->update != NULL)
			playerHdle->bp->update(playerHdle->bp, timeElapsed);
		return 0;
	}
	return -1;
}

//----------------------------------------------------------------------------//
static int player_service_init(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	const char* resFile = para;
	ezServiceEventResult_et result;
	playerServiceHandle_t* playerHdle;
	int ret;

	service_printf("=player_service_init begin=\n");
	
	if (hdle->doer == NULL)
	{
		if (resFile == NULL)
		{
			_WARN_NO_PARA(hdle->name, PLY_CMD_INIT);
		}
		else
		{
			service_printf("=player_core_init begin=\n");
			playerHdle = (playerServiceHandle_t*)calloc(1,sizeof(playerServiceHandle_t));
			KRK_ASSERT(playerHdle != NULL);
			playerHdle->bp = player_core_init(hdle, resFile, 0);
			//playerHdle->bgv = BgvPlayerNew(NULL, NULL, hdle);
			//playerHdle->bgv->setType(playerHdle->bgv, BGV_TYPE_VIDEO);
			hdle->doer = playerHdle;
			hdle->setUserUpdate(hdle, player_service_update);
			service_printf("=player_core_init end=\n");
		}
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= init already: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}

	service_printf("=player_service_init end=\n");

	if (hdle->doer != NULL)
	{
		result = ezServiceEvent_Succ;
		ret = ezService_Succ;
	}
	else
	{
		result = ezServiceEvent_Fail;
		ret = ezService_Err;
	}
	
	hdle->pushEvent(hdle, PLY_EVENT_INIT, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_deinit(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;

	service_printf("=player_service_deinit begin=\n");

	if (hdle->doer != NULL)
	{
		playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
		int ret = (int)player_core_deinit(playerHdle->bp);
		//if (playerHdle->bgv != NULL)
		//	BgvPlayerFree(playerHdle->bgv);
		//playerHdle->bgv = NULL;
		free(hdle->doer);
		hdle->doer = NULL;
		result = ezServiceEvent_Succ;
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= deinit already: service[%s]\n", hdle->name);
		service_printf("==================================\n");
	}
	hdle->pushEvent(hdle, PLY_EVENT_DEINIT, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_initaudio(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Succ;
	int ret = ezService_Err;
	
	if (hdle->doer == NULL)
	{
		int inChannels = 4;
		int outChannels = 2;
		int inRate = 48000;
		int outRate = 48000;
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_IN_CHN, &(inChannels));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_OUT_CHN, &(outChannels));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_IN_FS, &(inRate));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_OUT_FS, &(outRate));
		player_audio_setup(inRate,outRate,inChannels,outChannels);
		ret = player_audio_init(para);
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= WARNNING: initaudio must be before init player: service[%s]\n", hdle->name);
		service_printf("==================================\n");
		result = ezServiceEvent_Fail;
	}
	
	hdle->pushEvent(hdle, PLY_EVENT_INITAUDIO, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_deinitaudio(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Succ;
	
	if (hdle->doer == NULL)
	{
		player_audio_deinit();
	}
	else
	{
		service_printf("==================================\n");
		service_printf("= WARNNING: deinitaudio must be after deinit player: service[%s]\n", hdle->name);
		service_printf("==================================\n");
		result = ezServiceEvent_Fail;
	}
	hdle->pushEvent(hdle, PLY_EVENT_DEINITAUDIO, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_initview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;

	service_printf("=player_service_initview [%s] begin=\n", para);

	if (playerHdle != NULL)
	{
		if (para != NULL)
		{
			BatchPlayer_t* bp = playerHdle->bp;
			ezPlayer_t* player;
			int type;
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapPlayerType, sizeof(gValMapPlayerType), &(type));
			player = bp->getPlayerByType(bp, type);
			if (player != NULL)
			{
				if (type == PLAYER_TYPE_MUS) {
					MusPlayer_t* musPlayer = (MusPlayer_t*)player;
					musPlayer->initView(player, NULL);
				}
				else if (type == PLAYER_TYPE_VIDEO) {
					MediaPlayer_t* mmPlayer = (MediaPlayer_t*)player;
					mmPlayer->initView(player, NULL);
				}
				else if (type == PLAYER_TYPE_PICTURE) {
					PicPlayer_t* picPlayer = (PicPlayer_t*)player;
					picPlayer->initView(player, NULL);
				}
				else {
					hdle->pushEvent(hdle, PLY_EVENT_INITVIEW, ezServiceEvent_Fail);
					service_printf("=player_service_initview [%s] end no type =\n", para);
					return ezService_Err;
				}
				
				hdle->pushEvent(hdle, PLY_EVENT_INITVIEW, ezServiceEvent_Succ);
				service_printf("=player_service_initview [%s] end succ =\n", para);
				return ezService_Succ;
			}
			else
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else {
			_WARN_NO_PARA(hdle->name, cmdname);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_INITVIEW, ezServiceEvent_Fail);
	service_printf("=player_service_initview [%s] end err =\n", para);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_deinitview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;

	service_printf("=player_service_deinitview [%s] begin=\n", para);

	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player;
		int type;
		if (para != NULL)
		{
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapPlayerType, sizeof(gValMapPlayerType), &(type));
			player = bp->getPlayerByType(bp, type);
			if (player != NULL)
			{
				if (type == PLAYER_TYPE_MUS) {
					MusPlayer_t* musPlayer = (MusPlayer_t*)player;
					musPlayer->freeView(player, NULL);
				}
				else if (type == PLAYER_TYPE_VIDEO) {
					MediaPlayer_t* mmPlayer = (MediaPlayer_t*)player;
					mmPlayer->freeView(player, NULL);
				}
				else if (type == PLAYER_TYPE_PICTURE) {
					PicPlayer_t* picPlayer = (PicPlayer_t*)player;
					picPlayer->freeView(player, NULL);
				}
				else {
					hdle->pushEvent(hdle, PLY_EVENT_DEINITVIEW, ezServiceEvent_Fail);
					service_printf("=player_service_deinitview [%s] end no type =\n", para);
				}
				
				hdle->pushEvent(hdle, PLY_EVENT_DEINITVIEW, ezServiceEvent_Succ);
				service_printf("=player_service_deinitview [%s] end succ =\n", para);
				return ezService_Succ;
			}
			else
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else {
			_WARN_NO_PARA(hdle->name, cmdname);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_DEINITVIEW, ezServiceEvent_Fail);
	service_printf("=player_service_deinitview [%s] end err =\n", para);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setviewupdate(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL && para != NULL)
	{
		int value = atoi(para);
		int ret = ezService_Err;
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		
		playerHdle->seperateUpdate = value;
		
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			musPlayer->setSeperateUpdate(player, &value);
			ret = ezService_Succ;
		}

		/*
		if (playerHdle->bgv != NULL) {
			if (playerHdle->bgv->type == BGV_TYPE_VIDEO)
			{
				MediaPlayer_t* mp = (MediaPlayer_t*)playerHdle->bgv->player;
				ret = mp->setSeperateUpdate((ezPlayer_t*)mp, &value);
				ret = ezService_Succ;
			}
			else if (playerHdle->bgv->type == BGV_TYPE_PIC)
			{
				PicPlayer_t* pp = (PicPlayer_t*)playerHdle->bgv->player;
				ret = pp->setSeperateUpdate((ezPlayer_t*)pp, &value);
				ret = ezService_Succ;
			}
		}
		*/
		hdle->pushEvent(hdle, PLY_EVENT_SETVIEWUPDATE, ezServiceEvent_Succ);
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETVIEWUPDATE, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setviewvisible(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL && para != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			int value = atoi(para);
			
			musPlayer->setViewVisible(player, &value);
			hdle->pushEvent(hdle, PLY_EVENT_SETVIEWVISIBLE, ezServiceEvent_Succ);
			return ezService_Succ;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETVIEWVISIBLE, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_updateview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL)
		{
			if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t*)player;
				musPlayer->updateView(player, NULL);
			}
			else if (bp->getPlayerType(bp) == PLAYER_TYPE_VIDEO)
			{
				MediaPlayer_t* mmPlayer = (MediaPlayer_t*)player;
				mmPlayer->updateView(player, NULL);
			}
			hdle->pushEvent(hdle, PLY_EVENT_UPDATEVIEW, ezServiceEvent_Succ);
			return ezService_Succ;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_UPDATEVIEW, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_play(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;

	service_printf("=player_service_play begin=\n");
	
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		const char* filename = hdle->getCmdParaValue(hdle, cmdname, PLY_CMD_PLAY_FILE_PATH);
		int playerType = -1;
		
		hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_PLAYERTYPE, gValMapPlayerType, sizeof(gValMapPlayerType), &(playerType));
		if (playerType == -1)
			playerType = bp->parsePlayerType(bp, filename);
		
		if (playerType == PLAYER_TYPE_MUS) {
			iMusPlayerSongInfo_st songinfo;
				
			memset(&songinfo, 0, sizeof(songinfo));
			
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_SONG_NAME, songinfo.songName, sizeof(songinfo.songName));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_FILE_PATH, songinfo.filePath, sizeof(songinfo.filePath));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_SAVE_PATH, songinfo.savePath, sizeof(songinfo.savePath));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_REC_PATH, songinfo.recPath, sizeof(songinfo.recPath));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_CIDKEY, songinfo.cidKey, sizeof(songinfo.cidKey));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_FILE_SIZE, (int*)&(songinfo.filesize));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_SONG_INDEX, (int*)&(songinfo.songIndex));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_OKFPRODUCTID, &(songinfo.okfProductID));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_MIXMODE, &(songinfo.mixMode));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_MEDIATYPE, &(songinfo.songType));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_PLAY_MODE, gValMapSongMode, sizeof(gValMapSongMode), &(songinfo.playMode));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_SCORE_LEVEL, gValMapScoreLevel, sizeof(gValMapScoreLevel), &(songinfo.scoreLevel));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_REC_ON, gValMapOnOff, sizeof(gValMapOnOff), &(songinfo.recOn));		
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_STAFF_ON, gValMapOnOff, sizeof(gValMapOnOff), &(songinfo.staffOn));		
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_SCORE_ON, gValMapOnOff, sizeof(gValMapOnOff), &(songinfo.scoreOn));		
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_LYRIC_ON, gValMapOnOff, sizeof(gValMapOnOff), &(songinfo.lyricOn));		
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_PRIVATEKEY, gValMapPrivateKeys, sizeof(gValMapPrivateKeys), (int*)(&(songinfo.privateKey)));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_MUSSUBTYPE, gValMapMusSubType, sizeof(gValMapMusSubType), &(songinfo.MukSubFileType));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_RECFMT, gValMapRecFmt, sizeof(gValMapRecFmt), &(songinfo.recFmt));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_RECENCFMT, gValMapRecEncFmt, sizeof(gValMapRecEncFmt), &(songinfo.recEncFmt));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_FILE_PATH_EXT, songinfo.filePathext, sizeof(songinfo.filePathext));

			ret = bp->play(bp, PLAYER_TYPE_MUS, &songinfo);
		}
		else if (playerType == PLAYER_TYPE_VIDEO) {
			iMMPlayerSongInfo_st songinfo;

			memset(&songinfo, 0, sizeof(songinfo));

			// stop bgv before play video mtv
			//if (playerHdle->bgv != NULL)	{
			//	if (playerHdle->bgv->getState(playerHdle->bgv) != BGV_STATE_STOPPED)
			//		playerHdle->bgv->stop(playerHdle->bgv, 0);
			//}

			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_SONG_NAME, songinfo.songName, sizeof(songinfo.songName));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_FILE_PATH, songinfo.filePath, sizeof(songinfo.filePath));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_SAVE_PATH, songinfo.savePath, sizeof(songinfo.savePath));
			hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_PLAY_REC_PATH, songinfo.recPath, sizeof(songinfo.recPath));
			hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAY_REC_ON, gValMapOnOff, sizeof(gValMapOnOff), &(songinfo.recOn));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_NOAUDIO, &(songinfo.noAudio));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_NOVIDEO, &(songinfo.noVideo));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_HWAUDIO, &(songinfo.hwAudio));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_HWVIDEO, &(songinfo.hwVideo));
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_PLAY_SDKVERSION, &(songinfo.sdkVersion));
			
			ret = bp->play(bp, PLAYER_TYPE_VIDEO, &songinfo);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
		hdle->pushEvent(hdle, PLY_EVENT_PLAY, ezServiceEvent_Fail);
	}
	
	service_printf("=player_service_play end=\n");
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_stop(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	BatchPlayer_t* bp = playerHdle->bp;
	int ret = ezService_Err;
	service_printf("=player_service_stop begin=\n");

	if (bp != NULL)
	{
		ret = bp->stop(bp, NULL);
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
		hdle->pushEvent(hdle, PLY_EVENT_STOP, ezServiceEvent_Fail);
	}
	service_printf("=player_service_stop end=\n");
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_pause(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;
	
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL)
			ret =  player->pause(player, NULL);
		else
			_WARN_NO_PLAYER(hdle->name);
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Err)
		hdle->pushEvent(hdle, PLY_EVENT_PAUSE, ezServiceEvent_Fail);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_resume(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL)
			ret = player->play(player, NULL);
		else
			_WARN_NO_PLAYER(hdle->name);
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Err)
		hdle->pushEvent(hdle, PLY_EVENT_RESUME, ezServiceEvent_Fail);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_seektime(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL && para != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
		{
			MusPlayer_t* player = (MusPlayer_t *)(bp->getPlayer(bp));
			int time = atoi(para);
			return player->seekTime((ezPlayer_t*)player, &time);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_SEEKTIME, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_autoseek(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
		{
			MusPlayer_t* player = (MusPlayer_t *)(bp->getPlayer(bp));
			return player->autoSeek((ezPlayer_t*)player, NULL);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_AUTOSEEK, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setvol(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		int np;

		for (np=PLAYER_TYPE_VIDEO; np<PLAYER_TYPE_COUNT; np++)
		{
			ezPlayer_t* player = bp->getPlayerByType(bp, np);
			if (player != NULL)
			{
				ezSetVolPara_t volPara;
				int i, j;

				for (i=0; i<EZPLAYER_VOL_COUNT; i++)
				{
					ezServicePara_t* para = hdle->getCmdPara(hdle, cmdname, i);
					if (para != NULL)
					{
						for (j=0; j<EZPLAYER_VOL_COUNT; j++)
						{
							if (stricmp(gSetVolTypeNames[j], para->name) == 0)
							{
								volPara.volType = j;
								volPara.volValue = atoi(para->value);
								player->setVol(player, &volPara);
								break;
							}
						}
					}
					else
					{
						if (i==0)
							_WARN_NO_PARA(hdle->name, cmdname);
						break;
					}
				}
			}
		}
		hdle->clearCmdPara(hdle, PLY_CMD_SETVOL);
		return ezService_Succ;
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->clearCmdPara(hdle, PLY_CMD_SETVOL);
	hdle->pushEvent(hdle, PLY_EVENT_SETVOL, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setmute(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL)
		{
			if (para != NULL)
			{
				int value;
				
				hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETMUTE_MUTE, para);
				if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETMUTE_MUTE, gValMapOnOff, sizeof(gValMapOnOff), &value) == 0)
				{
					return player->setMute(player, &value);
				}
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETMUTE, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setvocal(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int vocal;
	ezSetVocalPara_t setvocal;

	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL)
		{
			if (para != NULL)
			{
				hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETVOCAL_VOCAL, para);
				if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETVOCAL_VOCAL, gValMapVocalType, sizeof(gValMapVocalType), &vocal) == 0)
				{
					setvocal.vocalChannel = 1;
					setvocal.vocalValue = (short)vocal;
					if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
						player->setVocal(player, &vocal);
					else
						player->setVocal(player, &setvocal);
					return ezService_Succ;
				}
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETVOCAL, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setmic(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezSetMicPara_t micPara = {-1, -1, -1, -1, -1, -1, {0}};

	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player;
		int embedded = 0;
		
		memset(micPara.waveTable, 0, sizeof(micPara.waveTable));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_EMBEDDED, &(embedded));
		if (embedded)
		{
			char intstr[32];
			player_audio_get_param(&(micPara.inRate), &(micPara.outRate), &(micPara.inChannels), &(micPara.outChannels));
			itoa(micPara.inChannels,intstr,10);
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETMIC_IN_CHN, intstr);
			itoa(micPara.outChannels,intstr,10);
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETMIC_OUT_CHN, intstr);
			itoa(micPara.inRate,intstr,10);
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETMIC_IN_FS, intstr);
			itoa(micPara.outRate,intstr,10);
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETMIC_OUT_FS, intstr);
		}
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_IN_CHN, &(micPara.inChannels));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_OUT_CHN, &(micPara.outChannels));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_IN_FS, &(micPara.inRate));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_OUT_FS, &(micPara.outRate));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_INLATENCY, &(micPara.inLatency));
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETMIC_OUTLATENCY, &(micPara.outLatency));
		hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_SETMIC_WAVTBL, micPara.waveTable, sizeof(micPara.waveTable));
		player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			musPlayer->setMicPara(ezPlayer(musPlayer), &micPara);
		}
		player = bp->getPlayerByType(bp, PLAYER_TYPE_VIDEO);
		if (player != NULL)
		{
			MediaPlayer_t* mmPlayer = (MediaPlayer_t*)player;
			mmPlayer->setMicPara(ezPlayer(mmPlayer), &micPara);
		}
		player_audio_setup(micPara.inRate,micPara.outRate,micPara.inChannels,micPara.outChannels);
		return ezService_Succ;
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETMIC, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setlyric(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			int value;
			
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETLYRIC_SHOW, gValMapLyricOnOff, sizeof(gValMapLyricOnOff), &value) == 0)
			{
				musPlayer->setLyric((ezPlayer_t*)player, &value);
			}
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETLYRIC_ALIGN, gValMapLyricAlign, sizeof(gValMapLyricAlign), &value) == 0)
			{
				musPlayer->setLyricAlign(player, &value);
			}
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETLYRIC_EFFECT, gValMapLyricDrawEffect, sizeof(gValMapLyricDrawEffect), &value) == 0)
			{
				musPlayer->setLyricDrawEffect(player, &value);
			}
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETLYRIC_ENABLED, gValMapLyricOnOff, sizeof(gValMapLyricOnOff), &value) == 0)
			{
				musPlayer->setLyricEnabled((ezPlayer_t*)player, &value);
			}
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETLYRIC_FONT, gValMapLyricFont, sizeof(gValMapLyricFont), &value) == 0)
			{
				musPlayer->setLyricFont((ezPlayer_t*)player, &value);
			}
			return ezService_Succ;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETLYRIC, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setstaff(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			ezSetIfunPara_t ifunPara = {MusIfunSet_OnOff, 0};
			int value;
			
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETSTAFF_SHOW, gValMapOnOff, sizeof(gValMapOnOff), &(value)) == 0)
			{
				ifunPara.value = value;
				ifunPara.optionType = MusIfunSet_OnOff;
				musPlayer->setIfun((ezPlayer_t*)player, &ifunPara);
			}
			if (hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETSTAFF_NUM, &(value)) == 0)
			{
				ifunPara.value = value;
				ifunPara.optionType = MusIfunSet_Num;
				musPlayer->setIfun((ezPlayer_t*)player, &ifunPara);
			}
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETSTAFF_ENABLED, gValMapOnOff, sizeof(gValMapOnOff), &(value)) == 0)
			{
				musPlayer->setStaffEnabled((ezPlayer_t*)player, &value);
			}
			return ezService_Succ;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETSTAFF, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_setscore(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			iMusPlayerScorePara_t scorePara = {MusScoreSet_OnOff, 0};
			
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETSCORE_SHOW, gValMapOnOff, sizeof(gValMapOnOff), &(scorePara.value)) == 0)
			{
				scorePara.setOption = MusScoreSet_OnOff;
				musPlayer->setScore((ezPlayer_t*)player, &scorePara);
			}
			if (hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETSCORE_LEVEL, &(scorePara.value)) == 0)
			{
				scorePara.setOption = MusScoreSet_Level;
				musPlayer->setScore((ezPlayer_t*)player, &scorePara);
			}
			if (hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETSCORE_ADJCB, &(scorePara.value)) == 0)
			{
				scorePara.setOption = MusScoreSet_AdjustCB;
				musPlayer->setScore((ezPlayer_t*)player, &scorePara);
			}
			return ezService_Succ;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETSCORE, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_getlyric(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS) {
			if (para != NULL) {
				MusPlayer_t* musPlayer = (MusPlayer_t*)bp->getPlayer(bp);
				int num = atoi(para);
				if (musPlayer != NULL) {
					CHAOS_LYRIC_DISPLAY_INFO* lyricinf = (CHAOS_LYRIC_DISPLAY_INFO*)(musPlayer->getLyricInf(ezPlayer(musPlayer), 0));
					char temp[256];
					int ret = -1;
					if (lyricinf == NULL)
						strcpy(temp, " ");
					else {
						int i;
						int j;

						for (j=0; j<CHAOS_LYRIC_MAX_LINE_COUNT; j++) {
							for (i=0;i<lyricinf->LineInfo[j].LineCount;i++) {
								if (lyricinf->LineInfo[j].LineList[i].Number == num) {
									CHAOS_LYRIC_LINE_INFO_UNIT* cline = &(lyricinf->LineInfo[j].LineList[i]);
									krk_charset_convert(krk_font_language_to_cp(lyricinf->Language), KRK_CHARSET_UTF8, cline->Lyric, temp, strlen(cline->Lyric), sizeof(temp)-2);
									hdle->setEventPara(hdle, PLY_EVENT_GETLYRIC, PLY_EVENT_GETLYRIC_STRING, temp);
									if (lyricinf->Unit == CHAOS_LYRIC_UNIT_TICK)
										itoa(cline->WordList[0].StartTime*125/6,temp,10);
									else
										itoa(cline->WordList[0].StartTime,temp,10);
									hdle->setEventPara(hdle, PLY_EVENT_GETLYRIC, PLY_EVENT_GETLYRIC_STARTTIME, temp);
									if (lyricinf->Unit == CHAOS_LYRIC_UNIT_TICK)
										itoa(cline->EndTime*125/6,temp,10);
									else
										itoa(cline->EndTime,temp,10);
									hdle->setEventPara(hdle, PLY_EVENT_GETLYRIC, PLY_EVENT_GETLYRIC_ENDTIME, temp);
									ret = 0;
									//mus_printf("player_service_getlyric-> %d, %d, %d\n", cline->Number, cline->StartTime, cline->EndTime);
									break;
								}
							}
						}
					}
					hdle->pushEvent(hdle, PLY_EVENT_GETLYRIC, ezServiceEvent_Succ);
					return ret;
				}
			}
			else {
				_WARN_NO_PARA(hdle->name, cmdname);
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETLYRIC, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_getscore(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS) {
			MusPlayer_t* musPlayer = (MusPlayer_t*)bp->getPlayer(bp);
			if (musPlayer != NULL) {
				int ret = musPlayer->getScore(ezPlayer(musPlayer), 0);
				hdle->pushEvent(hdle, PLY_EVENT_GETSCORE, ezServiceEvent_Succ);
				return ret;
			}
		} else if (bp->getPlayerType(bp) == PLAYER_TYPE_VIDEO) {
			MediaPlayer_t* mmPlayer = (MediaPlayer_t*)bp->getPlayer(bp);
			if (mmPlayer != NULL) {
				int ret = mmPlayer->getScore(ezPlayer(mmPlayer), 0);
				hdle->pushEvent(hdle, PLY_EVENT_GETSCORE, ezServiceEvent_Succ);
				return ret;
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETSCORE, ezServiceEvent_Fail);
	return 0;
}

//----------------------------------------------------------------------------//
static int player_service_getbufferingflag(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			int ret = musPlayer->getBufferingFlag(player, 0);
			hdle->pushEvent(hdle, PLY_EVENT_GETBUFFERINGFLAG, ezServiceEvent_Succ);
			return ret;
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETBUFFERINGFLAG, ezServiceEvent_Fail);
	return 0;
}

//----------------------------------------------------------------------------//
static int player_service_getplaytime(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = 0;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		int curtime;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
		{
			MusPlayer_t* player = (MusPlayer_t *)(bp->getPlayer(bp));
			ret = player->getplaytime((ezPlayer_t*)player, &curtime);
		}
		else if (bp->getPlayerType(bp) == PLAYER_TYPE_VIDEO)
		{
			MediaPlayer_t* player = (MediaPlayer_t *)(bp->getPlayer(bp));
			ret = player->getplaytime((ezPlayer_t*)player, &curtime);
		}
		hdle->pushEvent(hdle, PLY_EVENT_GETPLAYTIME, ezServiceEvent_Succ);
		return curtime;
	}
	else
	{
		hdle->pushEvent(hdle, PLY_EVENT_GETPLAYTIME, ezServiceEvent_Fail);
		return 0;
	}
}

//----------------------------------------------------------------------------//
static int player_service_gettotaltime(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = 0;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		int totaltime;
		if (bp->getPlayerType(bp) == PLAYER_TYPE_MUS)
		{
			MusPlayer_t* player = (MusPlayer_t *)(bp->getPlayer(bp));
			ret = player->getTotalTime((ezPlayer_t*)player, &totaltime);
		}
		else if (bp->getPlayerType(bp) == PLAYER_TYPE_VIDEO)
		{
			MediaPlayer_t* player = (MediaPlayer_t *)(bp->getPlayer(bp));
			ret = player->getTotalTime((ezPlayer_t*)player, &totaltime);
		}
		hdle->pushEvent(hdle, PLY_EVENT_GETTOTALTIME, ezServiceEvent_Succ);
		return totaltime;
	}
	else
	{
		hdle->pushEvent(hdle, PLY_EVENT_GETTOTALTIME, ezServiceEvent_Fail);
		return 0;
	}
}

//----------------------------------------------------------------------------//
static int player_service_getstate(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player = bp->getPlayer(bp);
		if (player != NULL) {
			switch (player->playInf.state)
			{
				case EZPLAYER_STATE_STOPPING:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_STOPPING);
					break;
				case EZPLAYER_STATE_STOPPED:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_STOPPED);
					break;
				case EZPLAYER_STATE_PARSING:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_PARSING);
					break;
				case EZPLAYER_STATE_PLAYING:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_PLAYING);
					break;
				case EZPLAYER_STATE_PAUSING:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_PAUSING);
					break;
				case EZPLAYER_STATE_PAUSED:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_PAUSED);
					break;
				default:
					hdle->setEventPara(hdle, PLY_EVENT_GETSTATE, PLY_EVENT_GETSTATE_STATE, PLY_EVENT_GETSTATE_STATE_DUMMY);
					break;
			}
			result = ezServiceEvent_Succ;
		}
		else {
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
		hdle->pushEvent(hdle, PLY_EVENT_GETSTATE, result);
		return ezService_Err;
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETSTATE, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_setfiletype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			MusPlayer_t* musPlayer = (MusPlayer_t*)player;
			int value;
			
			if (para != NULL)
			{
				value = atoi(para);
				musPlayer->setFileParseType(player, &value);
				hdle->pushEvent(hdle, PLY_EVENT_SETFILETYPE, ezServiceEvent_Succ);
				return ezService_Succ;
			}
			else
			{
				_WARN_NO_PARA(hdle->name, PLY_CMD_SETFILETYPE);
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETFILETYPE, ezServiceEvent_Fail);
	return 0;
}


//----------------------------------------------------------------------------//
static int player_service_enableeffectmusic(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (para != NULL)
		{
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t*)player;
				int value = atoi(para);
				musPlayer->enableEffectMusic(player, &value);
				hdle->pushEvent(hdle, PLY_EVENT_ENABLEEFFECTMUSIC, ezServiceEvent_Succ);
				return ezService_Succ;
			}
			else
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_CMD_ENABLEEFFECTMUSIC);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_ENABLEEFFECTMUSIC, ezServiceEvent_Fail);
	return 0;
}


//----------------------------------------------------------------------------//
static int player_service_playeffectmusic(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (para != NULL)
		{
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t*)player;
				musPlayer->playEffectMusic(player, (void*)para);
				hdle->pushEvent(hdle, PLY_EVENT_PLAYEFFECTMUSIC, ezServiceEvent_Succ);
				return ezService_Succ;
			}
			else
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_CMD_PLAYEFFECTMUSIC);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_PLAYEFFECTMUSIC, ezServiceEvent_Fail);
	return 0;
}


//----------------------------------------------------------------------------//
static int player_service_playmidicheer(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_PLAYMIDICHEER, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_seteqfreq(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_SETEQFREQ, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_seteqtype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_SETEQTYPE, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_geteqfreq(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_GETEQFREQ, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_geteqtype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_GETEQTYPE, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_testlatency(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = 0;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (para != NULL)
		{
			ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t *)player;
				ret = musPlayer->testLatency(player, (char*)para);
				return ezService_Succ;
			}
			else 
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_CMD_TESTLATENCY);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_TESTLATENCY, ezServiceEvent_Fail);
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_enableextmidi(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_ENABLEEXTMIDI, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_resetextmidi(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_RESETEXTMIDI, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_setencode(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	hdle->pushEvent(hdle, PLY_EVENT_SETENCODE, result);
	return ezService_Succ;
}

//----------------------------------------------------------------------------//
static int player_service_setspsoundeffect(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (para != NULL)
		{
			ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t *)player;
				int val = 0;
				hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETSPSOUNDEFFECT_PARA, para);
				hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETSPSOUNDEFFECT_PARA, gValMapOnOff, sizeof(gValMapOnOff), &val);		
				ret = musPlayer->setSoundEffect(player, &val);
				if (ret = ezService_Succ)
					result = ezServiceEvent_Succ;
			}
			else 
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_EVENT_SETSPSOUNDEFFECT);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETSPSOUNDEFFECT, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_setrecaudioconfig(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (para != NULL)
		{
			ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t *)player;
				iMusPlayerRecFileAudioConfig_st config;
				
				hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_ACCOMVOL, &config.accomVol);		
				hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_RECVOL, &config.recVol);		
				hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_ECHOVOL, &config.echoVol);		
				hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_REVERB, &config.reverb);		
				hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_RECPATH, config.recPath, sizeof(config.recPath));		
				ret = musPlayer->setRecFileAudioConfig(player, &config);
				if (ret = ezService_Succ)
					result = ezServiceEvent_Succ;
			}
			else 
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_EVENT_SETRECAUDIOCONFIG);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETRECAUDIOCONFIG, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_getrecaudioconfig(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = ezService_Err;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (para != NULL)
		{
			ezPlayer_t* 	player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
			if (player != NULL)
			{
				MusPlayer_t* musPlayer = (MusPlayer_t *)player;
				iMusPlayerRecFileAudioConfig_st config;
				char sval[16];
				
				hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_SETRECAUDIOCONFIG_RECPATH, config.recPath, sizeof(config.recPath));		
				ret = musPlayer->getRecFileAudioConfig(player, &config);
				if (ret = ezService_Succ)
					result = ezServiceEvent_Succ;
				itoa(config.accomVol,sval,10);
				hdle->setEventPara(hdle, PLY_EVENT_GETRECAUDIOCONFIG, PLY_CMD_SETRECAUDIOCONFIG_ACCOMVOL, sval);
				itoa(config.recVol,sval,10);
				hdle->setEventPara(hdle, PLY_EVENT_GETRECAUDIOCONFIG, PLY_CMD_SETRECAUDIOCONFIG_RECVOL, sval);
				itoa(config.echoVol,sval,10);
				hdle->setEventPara(hdle, PLY_EVENT_GETRECAUDIOCONFIG, PLY_CMD_SETRECAUDIOCONFIG_ECHOVOL, sval);
				itoa(config.reverb,sval,10);
				hdle->setEventPara(hdle, PLY_EVENT_GETRECAUDIOCONFIG, PLY_CMD_SETRECAUDIOCONFIG_REVERB, sval);
			}
			else 
			{
				_WARN_NO_PLAYER(hdle->name);
			}
		}
		else
		{
			_WARN_NO_PARA(hdle->name, PLY_EVENT_GETRECAUDIOCONFIG);
		}
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETRECAUDIOCONFIG, result);
	return ret;
}


//----------------------------------------------------------------------------//
static int player_service_changeaudioif(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayer(bp) != NULL)
		{
			int playrec = 0;
			int audioType;
			
			hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_CHANGEAUDIF_PLAYREC, &playrec);
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_CHANGEAUDIF_AUDIOIF, para);
			if (hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_CHANGEAUDIF_AUDIOIF, gValMapAudioType, sizeof(gValMapAudioType), &audioType) == 0)
			{
				player_audio_change_if(bp, playrec, audioType);
				result = ezServiceEvent_Succ;
				ret = ezService_Succ;
			}
		}
		else
		{
			_WARN_NO_PLAYER(hdle->name);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_CMD_CHANGEAUDIF, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_setplayertype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;

	service_printf("=player_service_setplayertype begin=\n");

	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		int type;
		if (para != NULL)
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
		hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapPlayerType, sizeof(gValMapPlayerType), &(type));
		if (type == PLAYER_TYPE_VIDEO) {
			// stop bgv before play video mtv
			//if (playerHdle->bgv != NULL)	{
			//	if (playerHdle->bgv->getState(playerHdle->bgv) != BGV_STATE_STOPPED)
			//		playerHdle->bgv->stop(playerHdle->bgv, 0);
			//}
		}
		if (type != -1) {
			bp->setPlayer(bp, type);
			hdle->pushEvent(hdle, PLY_CMD_SETPLAYERTYPE, ezServiceEvent_Succ);
		}
		else {
			hdle->pushEvent(hdle, PLY_CMD_SETPLAYERTYPE, ezServiceEvent_Fail);
		}
		return type;
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_SETPLAYERTYPE, ezServiceEvent_Fail);
	return -1;
}

//----------------------------------------------------------------------------//
static int player_service_getplayertype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = PLAYER_TYPE_NONE;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		if (bp->getPlayer(bp) != NULL)
		{
			hdle->pushEvent(hdle, PLY_CMD_GETPLAYERTYPE, ezServiceEvent_Succ);
			ret = bp->getPlayerType(bp);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETPLAYERTYPE, ezServiceEvent_Fail);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_playbgv(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;

	/*
	service_printf("=player_service_playbgv begin=\n");
	
	if (para == NULL) {
		_WARN_NO_PARA(hdle->name, cmdname);
	}
	else if (playerHdle != NULL)
	{
		int existFlag;
		
		if (krk_direxist(para)) {
			existFlag = 1;
		}
		else if (krk_fexist(para)){
			existFlag = 2;
		}
		else {
			existFlag = 0;
			service_printf("=player_service_playbgv end no files=\n");
			hdle->pushEvent(hdle, PLY_CMD_PLAYBGV, ezServiceEvent_Fail);
			return -1;
		}
		
		// free mediaplayer
		if (playerHdle->bp->getPlayer(playerHdle->bp) != NULL)
		{
			if (playerHdle->bp->getPlayerType(playerHdle->bp) == PLAYER_TYPE_VIDEO)
				playerHdle->bp->setPlayer(playerHdle->bp, -1);
		}

		// create bgv player
		if (playerHdle->bgv == NULL) {
			playerHdle->bgv = BgvPlayerNew(NULL, para, hdle);
		}
		else {
			if (playerHdle->bgv->getState(playerHdle->bgv) != BGV_STATE_STOPPED)
				playerHdle->bgv->stop(playerHdle->bgv, 0);
		}
		
		if (playerHdle->bgv->type == BGV_TYPE_NONE)
			playerHdle->bgv->setType(playerHdle->bgv, BGV_TYPE_VIDEO);

		if (existFlag == 1) {
			int playmode = BGV_PLAY_FROM_LAST_STOPPED;
			ret = hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_PLAYBGV_MODE, gPlayBgvMode, sizeof(gPlayBgvMode), &(playmode));
			playerHdle->bgv->setPath(playerHdle->bgv, para);
			if (ret == -1)
				ret = playerHdle->bgv->play(playerHdle->bgv, BGV_PLAY_FROM_LAST_STOPPED);
			else
				ret = playerHdle->bgv->play(playerHdle->bgv, playmode);
		}
		else if (existFlag == 2){
			ret = playerHdle->bgv->playFile(playerHdle->bgv, para);
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Succ)
		hdle->pushEvent(hdle, PLY_EVENT_PLAYBGV, ezServiceEvent_Succ);
	else
		hdle->pushEvent(hdle, PLY_EVENT_PLAYBGV, ezServiceEvent_Fail);

	service_printf("=player_service_playbgv end=\n");*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_stopbgv(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;

	/*
	service_printf("=player_service_stopbgv begin=\n");

	if (playerHdle != NULL)
	{
		if (playerHdle->bgv != NULL)
		{
			if (playerHdle->bgv->getState(playerHdle->bgv) != BGV_STATE_STOPPED)
				ret = playerHdle->bgv->stop(playerHdle->bgv, strcmp(para, "next") == 0 ? 1 : 0);
			else
				ret = ezService_Succ;
		}
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Succ)
		hdle->pushEvent(hdle, PLY_EVENT_PLAYBGV, ezServiceEvent_Succ);
	else
		hdle->pushEvent(hdle, PLY_EVENT_PLAYBGV, ezServiceEvent_Fail);

	service_printf("=player_service_stopbgv end=\n");*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_setbgvtype(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;

	/*
	service_printf("=player_service_setbgvtype begin=\n");
	
	if (para == NULL) {
		_WARN_NO_PARA(hdle->name, cmdname);
	}
	else if (playerHdle != NULL)
	{
		int bgvtype;
		
		// create bgv player
		if (playerHdle->bgv == NULL) {
			playerHdle->bgv = BgvPlayerNew(NULL, para, hdle);
		}
		if (playerHdle->bgv->getState(playerHdle->bgv) != BGV_STATE_STOPPED) {
			playerHdle->bgv->stop(playerHdle->bgv, 0);
		}
		
		hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
		ret = hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapBgvType, sizeof(gValMapBgvType), &(bgvtype));
		if (ret != -1) {
			
			// free mediaplayer
			if (playerHdle->bp->getPlayer(playerHdle->bp) != NULL)
			{
				if (playerHdle->bp->getPlayerType(playerHdle->bp) == PLAYER_TYPE_VIDEO && bgvtype == BGV_TYPE_VIDEO)
					playerHdle->bp->setPlayer(playerHdle->bp, -1);
			}
			playerHdle->bgv->setType(playerHdle->bgv, bgvtype);
			
			if (playerHdle->bgv->type == BGV_TYPE_VIDEO)
			{
				MediaPlayer_t* mp = (MediaPlayer_t*)playerHdle->bgv->player;
				ret = mp->setSeperateUpdate((ezPlayer_t*)mp, &(playerHdle->seperateUpdate));
				ret = ezService_Succ;
			}
			else if (playerHdle->bgv->type == BGV_TYPE_PIC)
			{
				PicPlayer_t* pp = (PicPlayer_t*)playerHdle->bgv->player;
				ret = pp->setSeperateUpdate((ezPlayer_t*)pp, &(playerHdle->seperateUpdate));
				ret = ezService_Succ;
			}
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Succ)
		hdle->pushEvent(hdle, PLY_EVENT_SETBGVTYPE, ezServiceEvent_Succ);
	else
		hdle->pushEvent(hdle, PLY_EVENT_SETBGVTYPE, ezServiceEvent_Fail);

	service_printf("=player_service_setbgvtype end=\n");*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_initbgvview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;

	/*
	service_printf("=player_service_initbgvview begin=\n");

	if (playerHdle != NULL)
	{
		if (playerHdle->bgv != NULL)
		{
			int type;
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
			ret = hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapBgvType, sizeof(gValMapBgvType), &(type));

			if (playerHdle->bgv->type == type) {
				if (type == BGV_TYPE_VIDEO)
				{
					MediaPlayer_t* mp = (MediaPlayer_t*)playerHdle->bgv->player;
					ret = mp->initView((ezPlayer_t*)mp, NULL);
				}
				else if (type == BGV_TYPE_PIC)
				{
					PicPlayer_t* pp = (PicPlayer_t*)playerHdle->bgv->player;
					ret = pp->initView((ezPlayer_t*)pp, NULL);
				}
			}
		}
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Succ)
		hdle->pushEvent(hdle, PLY_EVENT_INITBGVVIEW, ezServiceEvent_Succ);
	else
		hdle->pushEvent(hdle, PLY_EVENT_INITBGVVIEW, ezServiceEvent_Fail);*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_freebgvview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = ezService_Err;
	/*
	service_printf("=player_service_freebgvview begin=\n");

	if (playerHdle != NULL)
	{
		if (playerHdle->bgv != NULL)
		{
			int type;
			hdle->setCmdPara(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, para);
			ret = hdle->getCmdParaValueFromMap(hdle, cmdname, PLY_CMD_SETPLAYERTYPE_TYPE, gValMapBgvType, sizeof(gValMapBgvType), &(type));
			if (playerHdle->bgv->type == type) {
				if (type == BGV_TYPE_VIDEO)
				{
					MediaPlayer_t* mp = (MediaPlayer_t*)playerHdle->bgv->player;
					ret = mp->freeView((ezPlayer_t*)mp, NULL);
				}
				else if (type == BGV_TYPE_PIC)
				{
					PicPlayer_t* pp = (PicPlayer_t*)playerHdle->bgv->player;
					ret = pp->freeView((ezPlayer_t*)pp, NULL);
				}
			}
		}
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	if (ret == ezService_Succ)
		hdle->pushEvent(hdle, PLY_EVENT_FREEBGVVIEW, ezServiceEvent_Succ);
	else
		hdle->pushEvent(hdle, PLY_EVENT_FREEBGVVIEW, ezServiceEvent_Fail);
		*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_updatebgvview(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	/*
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		if (playerHdle->bgv != NULL)
		{
			int type;
			int ret = ezService_Err;

			if (playerHdle->bgv->type == BGV_TYPE_VIDEO)
			{
				MediaPlayer_t* mp = (MediaPlayer_t*)playerHdle->bgv->player;
				ret = mp->updateView((ezPlayer_t*)mp, NULL);
			}
			else if (playerHdle->bgv->type == BGV_TYPE_PIC)
			{
				PicPlayer_t* pp = (PicPlayer_t*)playerHdle->bgv->player;
				ret = pp->updateView((ezPlayer_t*)pp, NULL);
			}
			hdle->pushEvent(hdle, PLY_EVENT_UPDATEBGVVIEW, ezServiceEvent_Succ);
			return ret;
		}
	}
	else
	{
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_UPDATEBGVVIEW, ezServiceEvent_Fail);*/
	return ezService_Err;
}

//----------------------------------------------------------------------------//
static int player_service_getbgvstate(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	int ret = BGV_STATE_STOPPED;

	/*
	if (playerHdle != NULL)
	{
		if (playerHdle->bgv != NULL)
		{
			ret = playerHdle->bgv->getState(playerHdle->bgv);
			hdle->pushEvent(hdle, PLY_EVENT_GETBGVSTATE, ezServiceEvent_Succ);
			return ret;
		}
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_GETBGVSTATE, ezServiceEvent_Fail);*/
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_voicerecord(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;

	if (playerHdle != NULL)
	{
		voiceRecordParam_t param;

		param.format = VOICE_REC_WAV;
		param.audioIf = player_audio_get_cur_if();
		param.audioHdle = player_audio_get_cur_handle();
		param.owner = hdle;
		param.mute_cb = player_service_voicerecord_mute_cb;
		param.read_cb = player_service_voicerecord_read_cb;
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_VOICERECORD_DEVSAMPLERATE, &param.devsamplerate);
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_VOICERECORD_FILESAMPLERATE, &param.filesamplerate);
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_VOICERECORD_CHANNELS, &param.channels);
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_VOICERECORD_MUTETIME, &param.mutetime);
		hdle->getCmdParaValueInt(hdle, cmdname, PLY_CMD_VOICERECORD_THRESHOLD, &param.threshold);
		hdle->getCmdParaValueStr(hdle, cmdname, PLY_CMD_VOICERECORD_RECFILE, param.outfile, sizeof(param.outfile));
		ret = (int)voice_record_start(&param);
		if (ret != 0)
			result = ezServiceEvent_Succ;
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_VOICERECORD, result);
	return ret;
}

//----------------------------------------------------------------------------//
static int player_service_stopvoicerecord(ezServiceHandle_t* hdle, const char* cmdname, const char* para)
{
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	ezServiceEventResult_et result = ezServiceEvent_Fail;
	int ret = 0;

	if (playerHdle != NULL)
	{
		int rechdle = 0;
		if (para != NULL)
			rechdle = atoi(para);
		ret = voice_record_stop((voiceRecordHandle_t*)rechdle);
		if (ret != 0)
			result = ezServiceEvent_Succ;
		hdle->removeEvent(hdle, PLY_EVENT_VOICERECORD_MUTE);
	}
	else {
		_WARN_NO_INIT(hdle->name);
	}
	hdle->pushEvent(hdle, PLY_EVENT_STOPVOICERECORD, result);
	return ret;
}

//----------------------------------------------------------------------------//
int player_service_getplayertime(ezServiceHandle_t* hdle)
{
	int ret = 0;
	playerServiceHandle_t* playerHdle = (playerServiceHandle_t*)hdle->doer;
	if (playerHdle != NULL)
	{
		BatchPlayer_t* bp = playerHdle->bp;
		ezPlayer_t* player;
		player = bp->getPlayerByType(bp, PLAYER_TYPE_MUS);
		if (player != NULL)
		{
			iMusPlayerPlayPara_t* musPara = (iMusPlayerPlayPara_t*)(player->param);
			PlayerMsg (musPara->playerHdle, PLAYER_MSG_GET_PLAY_TIME, &ret);
		}
	}
	return ret;
}
//----------------------------------------------------------------------------//
EZ_SERVICE_BEGIN_CMD_EXEC_MAP(playerService) 
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_INIT,										player_service_init)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_DEINIT,									player_service_deinit)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_INITAUDIO,							player_service_initaudio)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_DEINITAUDIO,						player_service_deinitaudio)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_INITVIEW,								player_service_initview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_DEINITVIEW,						player_service_deinitview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETVIEWUPDATE,				player_service_setviewupdate)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETVIEWVISIBLE,					player_service_setviewvisible)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_UPDATEVIEW,						player_service_updateview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_PLAY	,									player_service_play)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_STOP,									player_service_stop)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_PAUSE,									player_service_pause)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_RESUME,								player_service_resume)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SEEKTIME,							player_service_seektime)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_AUTOSEEK,							player_service_autoseek)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETVOL,								player_service_setvol)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETMUTE,								player_service_setmute)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETVOCAL,							player_service_setvocal)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETMIC,								player_service_setmic)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETLYRIC,								player_service_setlyric)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETSTAFF,								player_service_setstaff)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETSCORE,							player_service_setscore)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETLYRIC,								player_service_getlyric)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETSCORE,							player_service_getscore)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETBUFFERINGFLAG,			player_service_getbufferingflag)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETPLAYTIME,						player_service_getplaytime)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETTOTALTIME,					player_service_gettotaltime)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETSTATE,							player_service_getstate)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETFILETYPE,						player_service_setfiletype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_ENABLEEFFECTMUSIC,		player_service_enableeffectmusic)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_PLAYEFFECTMUSIC,			player_service_playeffectmusic)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_PLAYMIDICHEER,					player_service_playmidicheer)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETEQFREQ,							player_service_seteqfreq)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETEQTYPE,							player_service_seteqtype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETEQFREQ,						player_service_geteqfreq)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETEQTYPE,							player_service_geteqtype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_TESTLATENCY,						player_service_testlatency)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_ENABLEEXTMIDI,					player_service_enableextmidi)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_RESETEXTMIDI,					player_service_resetextmidi)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETENCODE,						player_service_setencode)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_CHANGEAUDIF,					player_service_changeaudioif)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETPLAYERTYPE,					player_service_getplayertype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETPLAYERTYPE,					player_service_setplayertype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_PLAYBGV,								player_service_playbgv)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_STOPBGV,								player_service_stopbgv)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETBGVTYPE,						player_service_setbgvtype)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_INITBGVVIEW,						player_service_initbgvview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_FREEBGVVIEW,					player_service_freebgvview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_UPDATEBGVVIEW,				player_service_updatebgvview)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETBGVSTATE,						player_service_getbgvstate)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_VOICERECORD,					player_service_voicerecord)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_STOPVOICERECORD,			player_service_stopvoicerecord)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETSPSOUNDEFFECT,			player_service_setspsoundeffect)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_SETRECAUDIOCONFIG,		player_service_setrecaudioconfig)
	EZ_SERVICE_ADD_CMD_EXEC(PLY_CMD_GETRECAUDIOCONFIG,		player_service_getrecaudioconfig)
EZ_SERVICE_END_CMD_EXEC_MAP()
//----------------------------------------------------------------------------//

