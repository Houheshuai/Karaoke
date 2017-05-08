/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : recencoder_service.h
** Revision : 1.00											
**																	
** Description: rec file encoder service module
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
** ----------------------------------------------------------
** ----------------------------------------------------------
** 
** USER STEPS:
** 
** step1: new service
**
**				hdle = ez_serviceNew("recencoder_service", user_xxx, recencoderService);
**
** step2: register some event handles
**
**				hdle->setEventCallback(hdle, "play", handleServiceEncoderCallback);
**				hdle->setEventCallback(hdle, "stopped", handleServiceEncoderCallback);
**				hdle->setEventCallback(hdle, "paused", handleServiceEncoderCallback);
**				hdle->setEventCallback(hdle, "resumed", handleServiceEncoderCallback);
**
** step3: call service update in your render, timer or some thread, 
**
**				hdle->update(hdle, timeElapsed);
**
**			another way to update service itself: don't need to call hdle->update() anywhere, it's self update
**
**				hdle->setThread(hdle, 1);
**
** step4: you can call exec to execute command now, for recencoder_service, "init" command must be folk first
**
**				hdle->setCmdPara(hdle, "init", "cidkey", "12345678");
**				hdle->setCmdPara(hdle, "init", "privatekey", "in");
**				hdle->setCmdPara(hdle, "init", "ringflag", "0");
**				hdle->setCmdPara(hdle, "init", "lameflag", "1");
**				hdle->setCmdPara(hdle, "init", "bitrate", "128");
**				hdle->setCmdPara(hdle, "init", "latency", "200");
**				hdle->setCmdPara(hdle, "init", "outlatency", "100");
**				hdle->exec(hdle, "init", NULL);
**
** step5: create a new encoder:
**
**				hdle->setCmdPara(hdle, "create", "songname", "ENGLISH SONG");
**				hdle->setCmdPara(hdle, "create", "singername", "Nicholas");
**				hdle->setCmdPara(hdle, "create", "albumname", "SuperStar");
**				hdle->setCmdPara(hdle, "create", "songindex", "3");
**				hdle->setCmdPara(hdle, "create", "songtype", "mus");
**				hdle->setCmdPara(hdle, "create", "filepath", "G:\\KARAOKE\\SONG\\30\\30617.MUK");
**				hdle->setCmdPara(hdle, "create", "recpath", "G:\\KARAOKE\\REC\\30617_0.REC");
**				hdle->setCmdPara(hdle, "create", "outfile", "G:\\KARAOKE\\REC_WAVE\\30617_0.MP3");
**				hdle->setCmdPara(hdle, "create", "echo", "50");
**				hdle->setCmdPara(hdle, "create", "music", "100");
**				hdle->setCmdPara(hdle, "create", "vocal", "100");
**				hdle->setCmdPara(hdle, "create", "rhythm", "100");
**				hdle->setCmdPara(hdle, "create", "tone", "0");
**				hdle->setCmdPara(hdle, "create", "tempo", "1000");
**				hdle->setCmdPara(hdle, "create", "rec", "100");
**				id = hdle->exec(hdle, "create", NULL);
**
** step6: read percentage of encode process
**
**				itoa(id, sval, 10);
**				percent = hdle->exec(hdle, "getpercent", sval);
**
** step7: destroy encoder after finished, normally do it in ENC_EVENT_STOPPED callback
**
**				itoa(id, sval, 10);
**				hdle->exec(hdle, "destroy", sval);
**
** step8: finish the service
**
**				hdle->exec(hdle, "deinit", NULL);
**				ez_serviceFree(hdle);
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
** CMD DEMES
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
**	init 
**
**				hdle->setCmdPara(hdle, "init", "cidkey", "12345678");
**				hdle->setCmdPara(hdle, "init", "privatekey", "in");
**				hdle->setCmdPara(hdle, "init", "ringflag", "0");
**				hdle->setCmdPara(hdle, "init", "lameflag", "1");
**				hdle->setCmdPara(hdle, "init", "bitrate", "128");
**				hdle->setCmdPara(hdle, "init", "latency", "200");
**				hdle->setCmdPara(hdle, "init", "outlatency", "100");
**				hdle->exec(hdle, "init", NULL);
**
** ----------------------------------------------------------
**	deinit 
**
**				hdle->exec(hdle, "deinit", NULL);
**
** ----------------------------------------------------------
**	create 
**
**				hdle->setCmdPara(hdle, "create", "songname", "ENGLISH SONG");
**				hdle->setCmdPara(hdle, "create", "singername", "Nicholas");
**				hdle->setCmdPara(hdle, "create", "albumname", "SuperStar");
**				hdle->setCmdPara(hdle, "create", "songindex", "3");
**				hdle->setCmdPara(hdle, "create", "songtype", "mus");
**				hdle->setCmdPara(hdle, "create", "filepath", "G:\\KARAOKE\\SONG\\30\\30617.MUK");
**				hdle->setCmdPara(hdle, "create", "recpath", "G:\\KARAOKE\\REC\\30617_0.REC");
**				hdle->setCmdPara(hdle, "create", "outfile", "G:\\KARAOKE\\REC_WAVE\\30617_0.MP3");
**				hdle->setCmdPara(hdle, "create", "echo", "50");
**				hdle->setCmdPara(hdle, "create", "music", "100");
**				hdle->setCmdPara(hdle, "create", "reverb", "30");
**				hdle->setCmdPara(hdle, "create", "rhythm", "100");
**				hdle->setCmdPara(hdle, "create", "tone", "0");
**				hdle->setCmdPara(hdle, "create", "tempo", "1000");
**				hdle->setCmdPara(hdle, "create", "rec", "100");
**				id = hdle->exec(hdle, "create", NULL);
**
** ----------------------------------------------------------
**	destroy 
**
**				itoa(id, sval, 10);
**				hdle->exec(hdle, "destroy", sval);
**
** ----------------------------------------------------------
**	pause 
**
**				hdle->exec(hdle, "pause", NULL);
**
** ----------------------------------------------------------
**	resume 
**
**				hdle->exec(hdle, "resume", NULL);
**
** ----------------------------------------------------------
**	getpercent
**
**				itoa(id, sval, 10);
**				percent = hdle->exec(hdle, "getpercent", sval);
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
** EVENT DEMES
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
** stopped
**
**				pid = hdle->getEventParaValue(hdle, "stopped", "id");
**				hdle->exec(hdle, "destroy", pid);
**				
** ----------------------------------------------------------
*/

#ifndef _RECENCODER_SERVICE_H_
#define _RECENCODER_SERVICE_H_

#include <lib/ezbase/ez_service.h>

/*
*========================================
*	recencoder service commands
*========================================
*/
#define ENC_CMD_INIT							"init"
#define ENC_CMD_DEINIT						"deinit"
#define ENC_CMD_CREATE						"create"
#define ENC_CMD_DESTROY					"destroy"
#define ENC_CMD_STOP							"stop"
#define ENC_CMD_PAUSE						"pause"
#define ENC_CMD_RESUME					"resume"
#define ENC_CMD_GETPERCENT			"getpercent"

/*
*	createencoder cmd parameters name
*/
#define ENC_CMD_ENCODE_SONG_NAME			"songname"		// format: songname=I love you
#define ENC_CMD_ENCODE_SINGER_NAME		"singername"		// format: singername=andy
#define ENC_CMD_ENCODE_ALBUM_NAME		"albumname"		// format: albumname=winner
#define ENC_CMD_ENCODE_SONG_INDEX			"songindex"		// format: songindex=10000
#define ENC_CMD_ENCODE_SONG_TYPE				"songtype"			// format: songtype=mus
#define ENC_CMD_ENCODE_FILE_PATH				"filepath"			// format: filepath=/mnt/sdcard/KARAOKE/SONG/00001.mus
#define ENC_CMD_ENCODE_REC_PATH				"recpath"			// format: recpath=/mnt/sdcard/KARAOKE/REC/00001.rec
#define ENC_CMD_ENCODE_OUT_FILE					"outfile"				// format: outfile=/mnt/sdcard/KARAOKE/REC/00001.mp3
#define ENC_CMD_ENCODE_CIDKEY						"cidkey"				// format: cidkey=23884844
#define ENC_CMD_ENCODE_PRIVATEKEY			"privatekey"		// format: privatekey=in
#define ENC_CMD_ENCODE_RINGFLAG				"ringflag"			// format: ringflag=1
#define ENC_CMD_ENCODE_LAMEFLAG				"lameflag"			// format: lameflag=1
#define ENC_CMD_ENCODE_ECHO						"echo"					// format: echo=50
#define ENC_CMD_ENCODE_MUSIC						"music"				// format: musicl=80
#define ENC_CMD_ENCODE_REVERB					"reverb"					// format: reverb=30
#define ENC_CMD_ENCODE_RHYTHM					"rhythm"				// format: rhythm=80
#define ENC_CMD_ENCODE_TONE						"tone"					// format: tone=50
#define ENC_CMD_ENCODE_TEMPO						"tempo"				// format: tempo=1000
#define ENC_CMD_ENCODE_REC							"rec"					// format: rec=80
#define ENC_CMD_ENCODE_BITRATE					"bitrate"				// format: bitrate=128
#define ENC_CMD_ENCODE_LATENCY					"latency"				// format: latency=128
#define ENC_CMD_ENCODE_OUTLATENCY			"outlatency"				// format: outlatency=128
#define ENC_CMD_ENCODE_MIXFLAG					"mixflag"				// format: mixflag=1
#define ENC_CMD_ENCODE_SPSOUND				"spsound"				// format: spsound=1

/*
*	createencoder cmd songtype parameter values
*/
#define ENC_CMD_ENCODE_SONG_TYPE_PCM			"pcm"
#define ENC_CMD_ENCODE_SONG_TYPE_WAV			"wav"
#define ENC_CMD_ENCODE_SONG_TYPE_MP3			"mp3"
#define ENC_CMD_ENCODE_SONG_TYPE_AAC			"aac"
#define ENC_CMD_ENCODE_SONG_TYPE_MIDI			"midi"
#define ENC_CMD_ENCODE_SONG_TYPE_MUS			"mus"
#define ENC_CMD_ENCODE_SONG_TYPE_OKFMP3	"okfmp3"

/*
*	createencoder cmd privatekey parameter value
*/
#define ENC_CMD_PLAY_PRIVATEKEY_IN	"in"
#define ENC_CMD_PLAY_PRIVATEKEY_RU	"ru"
#define ENC_CMD_PLAY_PRIVATEKEY_NK	"nk"
#define ENC_CMD_PLAY_PRIVATEKEY_MC	"mc"

/*
*========================================
*	player service events
*========================================
*/
#define ENC_EVENT_INIT							ENC_CMD_INIT
#define ENC_EVENT_DEINIT						ENC_CMD_DEINIT
#define ENC_EVENT_CREATE						ENC_CMD_CREATE
#define ENC_EVENT_DESTROY					ENC_CMD_DESTROY
#define ENC_EVENT_STOP							ENC_CMD_STOP
#define ENC_EVENT_PAUSE						ENC_CMD_PAUSE
#define ENC_EVENT_RESUME						ENC_CMD_RESUME
#define ENC_EVENT_GETPERCENT			ENC_CMD_GETPERCENT

#define ENC_EVENT_PLAY							"play"
#define ENC_EVENT_STOPPED					"stopped"
#define ENC_EVENT_PAUSED						"paused"
#define ENC_EVENT_RESUMED					"resumed"

/*
*	encodend event parameter
*/
#define ENC_EVENT_ENCODER_ID				"id"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: DECLARE SERVICE REGISTRY */
EZ_SERVICE_REGISTRY_DECLARE(recencoderService);
/* TODO END */

#ifdef __cplusplus
}
#endif

#endif

