/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : player_service.h
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
** ----------------------------------------------------------
** ----------------------------------------------------------
** 
** USER STEPS:
** 
** step1: new service
**
**				hdle = ez_serviceNew("player_service", user_xxx, playerService);
**
** step2: register some event handles
**
**				hdle->setEventCallback(hdle, "play", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "stop", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "titleon", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "titleoff", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "setvol", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "setvocal", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "setmute", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "interludebegin", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "interludeend", handleServicePlayerCallback);
**				hdle->setEventCallback(hdle, "lyricchanged", handleServicePlayerCallback);
**
** step3: call service update in your render, timer or some thread, 
**
**				hdle->update(hdle, timeElapsed);
**
**			another way to update service itself: don't need to call hdle->update() anywhere, it's self update
**
**				hdle->setThread(hdle, 1);
**
** step4: you can call exec to execute command now, for player_service, "init" command must be folk first
**
**				hdle->exec(hdle, "init", "/mnt/sdcard/KARAOKE/RES/player720p.res");
**
** step5: call any other commands ......
**
** step6: do something in event handler, normally you need read some feedback message from event, example:
**
**				hdle->getEventParaValue(hdle, "stop", "score");
**
** step7: finish the service
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
**				hdle->exec(hdle, "init", "/mnt/sdcard/KARAOKE/RES/player720p.res");
**
** ----------------------------------------------------------
**	deinit 
**
**				hdle->exec(hdle, "deinit", NULL);
**
** ----------------------------------------------------------
**	initaudio 
**
**				hdle->exec(hdle, "initaudio", "JAVA");
**
** ----------------------------------------------------------
**	deinitaudio 
**
**				hdle->exec(hdle, "deinitaudio", NULL);
**
** ----------------------------------------------------------
**	play 
**
**				hdle->setCmdPara(hdle, "play", "songname", "ENGLISH SONG");
**				hdle->setCmdPara(hdle, "play", "filepath", "G:\\KARAOKE\\SONG\\30\\30617.MUK");
**				hdle->setCmdPara(hdle, "play", "filesize", "0");
**				hdle->setCmdPara(hdle, "play", "recpath", "G:\\KARAOKE\\REC\\30617_0.REC");
**				hdle->setCmdPara(hdle, "play", "songindex", "999999");
**				hdle->setCmdPara(hdle, "play", "songmode", "mus");
**				hdle->setCmdPara(hdle, "play", "scorelevel", "easy");
**				hdle->setCmdPara(hdle, "play", "recon", "on");
**				hdle->setCmdPara(hdle, "play", "staffon", "on");
**				hdle->setCmdPara(hdle, "play", "scoreon", "on");
**				hdle->setCmdPara(hdle, "play", "lyricon", "on");
**				hdle->setCmdPara(hdle, "play", "cidkey", "12345678");
**				hdle->setCmdPara(hdle, "play", "privatekey", "in");
**				hdle->setCmdPara(hdle, "play", "okfproductid", "1");
**				hdle->setCmdPara(hdle, "play", "mussubtype", "midi");
**				hdle->exec(hdle, "play", NULL);
**
** ----------------------------------------------------------
**	stop 
**
**				hdle->exec(hdle, "stop", NULL);
**
** ----------------------------------------------------------
**	pause 
**
**				hdle->exec(hdle, "pause", NULL);
**
** ----------------------------------------------------------
**	seek 
**
**				hdle->exec(hdle, "seek", NULL);
**
** ----------------------------------------------------------
**	setvol , vol[0-100], key[-6,6], tempo[800-1200]
**
**				hdle->setCmdPara(hdle, "setvol", "total", "100");
**				hdle->setCmdPara(hdle, "setvol", "accom", "100");
**				hdle->setCmdPara(hdle, "setvol", "voice", "100");
**				hdle->setCmdPara(hdle, "setvol", "rhythm", "100");
**				hdle->setCmdPara(hdle, "setvol", "tone", "0");
**				hdle->setCmdPara(hdle, "setvol", "tempo", "1000");
**				hdle->setCmdPara(hdle, "setvol", "rec", "100");
**				hdle->setCmdPara(hdle, "setvol", "echo", "100");
**				hdle->setCmdPara(hdle, "setvol", "mic1", "100");
**				hdle->setCmdPara(hdle, "setvol", "mic2", "100");
**				hdle->setCmdPara(hdle, "setvol", "wmic1", "100");
**				hdle->setCmdPara(hdle, "setvol", "wmic2", "100");
**				hdle->exec(hdle, "setvol", NULL);
**
** ----------------------------------------------------------
**	setmute [on/off]
**
**				hdle->exec(hdle, "setmute", "on");
**
** ----------------------------------------------------------
**	setvocal [on/off/auto]
**
**				hdle->exec(hdle, "setvocal", "on");
**
** ----------------------------------------------------------
**	setmic 
**
**				hdle->setCmdPara(hdle, "setmic", "inchannel", "2");
**				hdle->setCmdPara(hdle, "setmic", "outchannel", "2");
**				hdle->setCmdPara(hdle, "setmic", "inrate", "48000");
**				hdle->setCmdPara(hdle, "setmic", "outrate", "48000");
**				hdle->setCmdPara(hdle, "setmic", "latency", "100");
**				hdle->setCmdPara(hdle, "setmic", "wavtable", "/mnt/sdcard/KARAOKE/RES/wavetable.bin");
**				hdle->exec(hdle, "setmic", NULL);
**
** ----------------------------------------------------------
**	setlyric, show[on/off/onlylyric/onlylabel], align[side/middle], effect[default/shadow/frame]
**
**				hdle->setCmdPara(hdle, "setlyric", "show", "on");
**				hdle->setCmdPara(hdle, "setlyric", "align", "side");
**				hdle->setCmdPara(hdle, "setlyric", "effect", "default");
**				hdle->exec(hdle, "setlyric", NULL);
**
** ----------------------------------------------------------
**	setstaff, show[on/off], num[1-2]
**
**				hdle->setCmdPara(hdle, "setstaff", "show", "on");
**				hdle->setCmdPara(hdle, "setstaff", "num", "1");
**				hdle->exec(hdle, "setstaff", NULL);
**
** ----------------------------------------------------------
**	setscore, show[on/off], level[easy/normal/hard], adjcb[MININT-MAXINT]
**
**				hdle->setCmdPara(hdle, "setscore", "show", "on");
**				hdle->setCmdPara(hdle, "setscore", "level", "easy");
**				hdle->setCmdPara(hdle, "setscore", "adjcb", "238498494");
**				hdle->exec(hdle, "setscore", NULL);
**
** ----------------------------------------------------------
**	changeaudioif, plug[default/kkebox/kkemini]
**
**				hdle->setCmdPara(hdle, "changeaudioif", "playrec", "1");
**				hdle->setCmdPara(hdle, "changeaudioif", "audioif", "kkebox");
**				hdle->exec(hdle, "changeaudioif", NULL);
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
** EVENT DEMES
**
** ----------------------------------------------------------
** ----------------------------------------------------------
**
** stop		[-1~100], -1: error stop, no score, [0~100]: score value
**
**				valstr = hdle->getEventParaValue(hdle, "stop", "score");
**				score = atoi(valstr);
**				
** ----------------------------------------------------------
**
** lyricchange		lineno[1~4], linestr[string], linepercent[0~100]
**
**				valstr = hdle->getEventParaValue(hdle, "lyricpercent", "lineno");
**				lineno = atoi(valstr);
**				valstr = hdle->getEventParaValue(hdle, "lyricpercent", "linepercent");
**				linepercent = atoi(valstr);
**				linestr = hdle->getEventParaValue(hdle, "lyricpercent", "linestr");
**				
** ----------------------------------------------------------
**
** lyricpercent		lineno[1~4], linestr[string], linepercent[0~100]
**
**				valstr = hdle->getEventParaValue(hdle, "lyricpercent", "lineno");
**				lineno = atoi(valstr);
**				valstr = hdle->getEventParaValue(hdle, "lyricpercent", "linepercent");
**				linepercent = atoi(valstr);
**				linestr = hdle->getEventParaValue(hdle, "lyricpercent", "linestr");
**				
** ----------------------------------------------------------
*/

#ifndef _PLAYER_SERVICE_H_
#define _PLAYER_SERVICE_H_

#include <lib/ezbase/ez_service.h>

/*
*========================================
*	player service commands
*========================================
*/
#define PLY_CMD_INIT									"init"
#define PLY_CMD_DEINIT								"deinit"
#define PLY_CMD_INITAUDIO						"initaudio"
#define PLY_CMD_DEINITAUDIO					"deinitaudio"
#define PLY_CMD_INITVIEW							"initview"
#define PLY_CMD_DEINITVIEW						"deinitview"
#define PLY_CMD_SETVIEWUPDATE				"setviewupdate"
#define PLY_CMD_SETVIEWVISIBLE				"setviewvisible"
#define PLY_CMD_UPDATEVIEW					"updateview"
#define PLY_CMD_PLAY						"play"
#define PLY_CMD_STOP						"stop"
#define PLY_CMD_PAUSE						"pause"
#define PLY_CMD_RESUME						"resume"
#define PLY_CMD_SEEKTIME					"seektime"
#define PLY_CMD_AUTOSEEK					"autoseek"
#define PLY_CMD_SETVOL						"setvol"
#define PLY_CMD_SETMUTE							"setmute"
#define PLY_CMD_SETVOCAL							"setvocal"
#define PLY_CMD_SETMIC								"setmic"
#define PLY_CMD_SETLYRIC							"setlyric"
#define PLY_CMD_SETSTAFF							"setstaff"
#define PLY_CMD_SETSCORE							"setscore"
#define PLY_CMD_GETVOL								"getvol"
#define PLY_CMD_GETLYRIC							"getlyric"
#define PLY_CMD_GETSCORE							"getscore"
#define PLY_CMD_GETPLAYTIME					"getplaytime"
#define PLY_CMD_GETTOTALTIME				"gettotaltime"
#define PLY_CMD_GETSTATE							"getstate"
#define PLY_CMD_SETFILETYPE						"setfiletype"
#define PLY_CMD_ENABLEEFFECTMUSIC		"enableeffectmusic"
#define PLY_CMD_PLAYEFFECTMUSIC			"playeffectmusic"
#define PLY_CMD_PLAYMIDICHEER				"playmidicheer"
#define PLY_CMD_SETEQFREQ						"seteqfreq"
#define PLY_CMD_SETEQTYPE						"seteqtype"
#define PLY_CMD_GETEQFREQ						"geteqfreq"
#define PLY_CMD_GETEQTYPE						"geteqtype"
#define PLY_CMD_TESTLATENCY					"testlatency"
#define PLY_CMD_ENABLEEXTMIDI				"enableextmidi"
#define PLY_CMD_RESETEXTMIDI					"resetextmidi"
#define PLY_CMD_SETENCODE						"setencode"
#define PLY_CMD_CHANGEAUDIF					"changeaudioif"
#define PLY_CMD_GETBUFFERINGFLAG		"getbufferingflag"
#define PLY_CMD_GETPLAYERTYPE				"getplayertype"
#define PLY_CMD_SETPLAYERTYPE				"setplayertype"
#define PLY_CMD_PLAYBGV							"playbgv"
#define PLY_CMD_STOPBGV							"stopbgv"
#define PLY_CMD_SETBGVTYPE						"setbgvtype"
#define PLY_CMD_INITBGVVIEW					"initbgvview"
#define PLY_CMD_FREEBGVVIEW					"deinitbgvview"
#define PLY_CMD_UPDATEBGVVIEW			"updatebgvview"
#define PLY_CMD_GETBGVSTATE					"getbgvstate"
#define PLY_CMD_VOICERECORD					"voicerecord"
#define PLY_CMD_STOPVOICERECORD		"stopvoicerecord"
#define PLY_CMD_SETSPSOUNDEFFECT		"setspsoundeffect"
#define PLY_CMD_SETRECAUDIOCONFIG	"setrecaudioconfig"
#define PLY_CMD_GETRECAUDIOCONFIG	"getrecaudioconfig"

/*
*	cmd parameters value
*/
#define PLY_CMD_PARA_VALUE_OFF	"off"
#define PLY_CMD_PARA_VALUE_ON		"on"

/*
*	play cmd parameters name
*/
#define PLY_CMD_PLAY_SONG_NAME			"songname"		// format: songname=I love you
#define PLY_CMD_PLAY_FILE_PATH				"filepath"			// format: filepath=/mnt/sdcard/xxx/...
#define PLY_CMD_PLAY_SAVE_PATH			"savepath"			// format: savepath=/mnt/sdcard/xxx/...
#define PLY_CMD_PLAY_FILE_SIZE					"filesize"				// format: filesize=1000
#define PLY_CMD_PLAY_REC_PATH				"recpath"			// format: recpath=/mnt/sdcard/xxx/...
#define PLY_CMD_PLAY_SONG_INDEX			"songindex"		// format: songindex=99999
#define PLY_CMD_PLAY_PLAY_MODE			"playmode"			// format: playmode=song
#define PLY_CMD_PLAY_SCORE_LEVEL			"scorelevel"			// format: scorelevel=easy
#define PLY_CMD_PLAY_REC_ON					"recon"				// format: recon=on
#define PLY_CMD_PLAY_STAFF_ON				"staffon"				// format: staffon=on
#define PLY_CMD_PLAY_SCORE_ON				"scoreon"			// format: scoreon=on
#define PLY_CMD_PLAY_LYRIC_ON				"lyricon"				// format: lyricon=on
#define PLY_CMD_PLAY_CIDKEY					"cidkey"				// format: cidkey=12345678
#define PLY_CMD_PLAY_PRIVATEKEY			"privatekey"		// format: privatekey=in
#define PLY_CMD_PLAY_OKFPRODUCTID	"okfproductid"	// format: okfproductid=1
#define PLY_CMD_PLAY_MEDIATYPE			"mediatype"		// format: mediatype=1
#define PLY_CMD_PLAY_MUSSUBTYPE		"mussubtype"		// format: mussubtype=midi
#define PLY_CMD_PLAY_MIXMODE				"mixmode"			// format: mixmode=1
#define PLY_CMD_PLAY_RECFMT					"recfmt"				// format: recfmt=adpcm
#define PLY_CMD_PLAY_RECENCFMT			"recencfmt"		// format: recfmt=adpcm
#define PLY_CMD_PLAY_NOAUDIO				"noaudio"		// format: noaudio=1
#define PLY_CMD_PLAY_NOVIDEO				"novideo"		// format: novideo=1
#define PLY_CMD_PLAY_HWAUDIO				"hwaudio"		// format: hwaudio=0
#define PLY_CMD_PLAY_HWVIDEO				"hwvideo"		// format: hwvideo=1
#define PLY_CMD_PLAY_PLAYERTYPE			"playertype"		// format: playertype=mus
#define PLY_CMD_PLAY_SDKVERSION			"sdkversion"		// format: sdkversion=16
#define PLY_CMD_PLAY_FILE_PATH_EXT		"filepathext"			// format: filepath=/mnt/sdcard/xxx/...

/*
*	play cmd song mode parameter value
*/
#define PLY_CMD_PLAY_PLAY_MODE_SONG		"song"
#define PLY_CMD_PLAY_PLAY_MODE_REC			"rec"
/*
*	play cmd score level parameter value
*/
#define PLY_CMD_PLAY_SCORE_LEVEL_EASY			"easy"
#define PLY_CMD_PLAY_SCORE_LEVEL_NORMAL	"normal"
#define PLY_CMD_PLAY_SCORE_LEVEL_HARD		"hard"
/*
*	play cmd privatekey parameter value
*/
#define PLY_CMD_PLAY_PRIVATEKEY_IN		"in"
#define PLY_CMD_PLAY_PRIVATEKEY_RU	"ru"
#define PLY_CMD_PLAY_PRIVATEKEY_NK	"nk"
#define PLY_CMD_PLAY_PRIVATEKEY_MC	"mc"
/*
*	play cmd mus sub type parameter value
*/
#define PLY_CMD_PLAY_MUSSUBTYPE_MIDI			"midi"
#define PLY_CMD_PLAY_MUSSUBTYPE_MIDIMP3	"midimp3"
#define PLY_CMD_PLAY_MUSSUBTYPE_KSC			"ksc"
#define PLY_CMD_PLAY_MUSSUBTYPE_CDG			"cdg"
#define PLY_CMD_PLAY_MUSSUBTYPE_LRC			"lrc"
#define PLY_CMD_PLAY_MUSSUBTYPE_KSC_TEXT	"ksctext"
#define PLY_CMD_PLAY_MUSSUBTYPE_LYC			"lyc"
/*
*	play cmd recfmt type parameter value
*/
#define PLY_CMD_PLAY_RECFMT_ADPCM			"adpcm"
#define PLY_CMD_PLAY_RECFMT_SBC					"sbc"
#define PLY_CMD_PLAY_RECFMT_MP3				"mp3"
#define PLY_CMD_PLAY_RECFMT_AAC					"aac"
/*
*	play cmd recencfmt type parameter value
*/
#define PLY_CMD_PLAY_RECENCFMT_WAV				"wav"
#define PLY_CMD_PLAY_RECENCFMT_ADPCM			"adpcm"
#define PLY_CMD_PLAY_RECENCFMT_SBC					"sbc"
#define PLY_CMD_PLAY_RECENCFMT_MP3					"mp3"
#define PLY_CMD_PLAY_RECENCFMT_AAC					"aac"

/*
*	setvol cmd parameters name
*/
#define PLY_CMD_SETVOL_TOTAL				"total"					// format: total=100
#define PLY_CMD_SETVOL_ACCOM				"accom"
#define PLY_CMD_SETVOL_VOICE					"voice"
#define PLY_CMD_SETVOL_REVERB				"reverb"
#define PLY_CMD_SETVOL_MIDI					"midi"
#define PLY_CMD_SETVOL_RHYTHM			"rhythm"
#define PLY_CMD_SETVOL_TONE					"tone"
#define PLY_CMD_SETVOL_TEMPO				"tempo"
#define PLY_CMD_SETVOL_REC						"rec"
#define PLY_CMD_SETVOL_ECHO					"echo"
#define PLY_CMD_SETVOL_DELAY				"delay"
#define PLY_CMD_SETVOL_MICL					"mic1"
#define PLY_CMD_SETVOL_MICR					"mic2"
#define PLY_CMD_SETVOL_WMICL				"wmic1"
#define PLY_CMD_SETVOL_WMICR				"wmic2"

/*
*	setmute cmd parameters name
*/
#define PLY_CMD_SETMUTE_MUTE				"mute"			// format: mute=on
/*
*	setmute cmd parameters value
*/
#define PLY_CMD_SETMUTE_MUTE_ON		PLY_CMD_PARA_VALUE_ON
#define PLY_CMD_SETMUTE_MUTE_OFF	PLY_CMD_PARA_VALUE_OFF

/*
*	setvocal cmd parameters name
*/
#define PLY_CMD_SETVOCAL_VOCAL			"vocal"			// format: mute=off
/*
*	setvocal cmd parameters value
*/
#define PLY_CMD_SETVOCAL_VOCAL_OFF		PLY_CMD_PARA_VALUE_OFF
#define PLY_CMD_SETVOCAL_VOCAL_ON		PLY_CMD_PARA_VALUE_ON
#define PLY_CMD_SETVOCAL_VOCAL_AUTO		"auto"

/*
*	setmic cmd parameters name
*/
#define PLY_CMD_SETMIC_IN_CHN				"inchannel"		// format: inchannel=2
#define PLY_CMD_SETMIC_OUT_CHN			"outchannel"
#define PLY_CMD_SETMIC_IN_FS					"inrate"			// format: inrate=32000
#define PLY_CMD_SETMIC_OUT_FS				"outrate"
#define PLY_CMD_SETMIC_INLATENCY		"inlatency"		// format: inlatency=100
#define PLY_CMD_SETMIC_OUTLATENCY	"outlatency"	// format: outlatency=100
#define PLY_CMD_SETMIC_WAVTBL				"wavtable"		// format: wavtable=/mnt/sdcard/xxx/...
#define PLY_CMD_SETMIC_EMBEDDED		"embedded"		// format: embedded=1

/*
*	setlyric cmd parameters name
*/
#define PLY_CMD_SETLYRIC_SHOW				"show"		// format: show=on
#define PLY_CMD_SETLYRIC_ALIGN				"align"			// format: align=side
#define PLY_CMD_SETLYRIC_EFFECT				"effect"		// format: effect=shadow
#define PLY_CMD_SETLYRIC_ENABLED			"enabled"		// format: enabled=on
#define PLY_CMD_SETLYRIC_FONT				"fontname"		// format: fontname=<fontname>
/*
*	setlyric cmd parameters value
*/
#define PLY_CMD_SETLYRIC_SHOW_ON					PLY_CMD_PARA_VALUE_ON
#define PLY_CMD_SETLYRIC_SHOW_OFF					PLY_CMD_PARA_VALUE_OFF
#define PLY_CMD_SETLYRIC_SHOW_ONLYMAIN	"onlylyric"
#define PLY_CMD_SETLYRIC_SHOW_ONLYLABEL	"onlylabel"
#define PLY_CMD_SETLYRIC_ALIGN_SIDE				"side"
#define PLY_CMD_SETLYRIC_ALIGN_MIDDLE			"middle"
#define PLY_CMD_SETLYRIC_EFFECT_DEFAULT		"default"
#define PLY_CMD_SETLYRIC_EFFECT_SHADOW		"shadow"
#define PLY_CMD_SETLYRIC_EFFECT_FRAME			"frame"

/*
*	setstaff cmd parameters name
*/
#define PLY_CMD_SETSTAFF_SHOW				"show"		// format: show=on
#define PLY_CMD_SETSTAFF_NUM				"num"			// format: num=2
#define PLY_CMD_SETSTAFF_ENABLED			"enabled"			// format: enabled=on
/*
*	setlyric cmd parameters value
*/
#define PLY_CMD_SETSTAFF_SHOW_ON					PLY_CMD_PARA_VALUE_ON
#define PLY_CMD_SETSTAFF_SHOW_OFF				PLY_CMD_PARA_VALUE_OFF

/*
*	setscore cmd parameters name
*/
#define PLY_CMD_SETSCORE_SHOW				"show"		// format: show=on
#define PLY_CMD_SETSCORE_LEVEL					"level"			// format: level=0
#define PLY_CMD_SETSCORE_ADJCB				"adjcb"		// format: adjcb=xxx
/*
*	setscore cmd parameters value
*/
#define PLY_CMD_SETSCORE_SHOW_ON					PLY_CMD_PARA_VALUE_ON
#define PLY_CMD_SETSCORE_SHOW_OFF					PLY_CMD_PARA_VALUE_OFF

/*
*	setfiletype cmd parameters name
*/
#define PLY_CMD_SETFILETYPE_TYPE			"type"		// format: show=on

/*
*	kkdevplug cmd parameter name
*/
#define PLY_CMD_CHANGEAUDIF_AUDIOIF	"audioif"			// format: audioif=default
#define PLY_CMD_CHANGEAUDIF_PLAYREC	"playrec"			// format: playrec=1
/*
*	kkdevplug cmd parameter values
*/
#define PLY_CMD_CHANGEAUDIF_DEFAULT	"default"
#define PLY_CMD_CHANGEAUDIF_KKEBOX	"kkebox"
#define PLY_CMD_CHANGEAUDIF_KKEMINI	"kkemini"

/*
*	setplayertype cmd parameters name
*/
#define PLY_CMD_SETPLAYERTYPE_TYPE			"type"		// format: type=mus
/*
*	setplayertype cmd parameters values
*/
#define PLY_CMD_SETPLAYERTYPE_TYPE_MUS			"mus"		// format: type=mus
#define PLY_CMD_SETPLAYERTYPE_TYPE_VIDEO		"video"		// format: type=video
#define PLY_CMD_SETPLAYERTYPE_TYPE_MUSIC		"music"		// format: type=music
#define PLY_CMD_SETPLAYERTYPE_TYPE_PICTURE	"picture"		// format: type=picture

/*
*	playbgv cmd parameters name
*/
#define PLY_CMD_PLAYBGV_MODE								"mode"
#define PLY_CMD_PLAYBGV_MODE_CURRNET			"current"
#define PLY_CMD_PLAYBGV_MODE_FIRST					"first"
#define PLY_CMD_PLAYBGV_MODE_NEXT					"next"
#define PLY_CMD_PLAYBGV_MODE_RANDOM			"random"

/*
*	voicerecord cmd parameters 
*/
#define PLY_CMD_VOICERECORD_DEVSAMPLERATE		"devsamplerate"
#define PLY_CMD_VOICERECORD_FILESAMPLERATE		"filesamplerate"
#define PLY_CMD_VOICERECORD_CHANNELS			"channels"
#define PLY_CMD_VOICERECORD_MUTETIME				"mutetime"
#define PLY_CMD_VOICERECORD_THRESHOLD			"threshold"
#define PLY_CMD_VOICERECORD_RECFILE					"recfile"

/*
* setspsoundeffect command parameter
*/
#define PLY_CMD_SETSPSOUNDEFFECT_PARA		"spsound"

/*
* setrecaudioconfig command parameter
*/
#define PLY_CMD_SETRECAUDIOCONFIG_RECPATH		"recpath"
#define PLY_CMD_SETRECAUDIOCONFIG_ACCOMVOL		"accomvol"
#define PLY_CMD_SETRECAUDIOCONFIG_RECVOL		"recvol"
#define PLY_CMD_SETRECAUDIOCONFIG_ECHOVOL		"echovol"
#define PLY_CMD_SETRECAUDIOCONFIG_REVERB			"reverb"

/*
*========================================
*	player service events
*========================================
*/
#define PLY_EVENT_INIT										PLY_CMD_INIT
#define PLY_EVENT_DEINIT								PLY_CMD_DEINIT
#define PLY_EVENT_INITAUDIO							PLY_CMD_INITAUDIO
#define PLY_EVENT_DEINITAUDIO					PLY_CMD_DEINITAUDIO
#define PLY_EVENT_INITVIEW							PLY_CMD_INITVIEW
#define PLY_EVENT_DEINITVIEW						PLY_CMD_DEINITVIEW
#define PLY_EVENT_SETVIEWUPDATE				PLY_CMD_SETVIEWUPDATE
#define PLY_EVENT_SETVIEWVISIBLE				PLY_CMD_SETVIEWVISIBLE
#define PLY_EVENT_UPDATEVIEW						PLY_CMD_UPDATEVIEW
#define PLY_EVENT_PLAY									PLY_CMD_PLAY
#define PLY_EVENT_STOP									PLY_CMD_STOP
#define PLY_EVENT_PAUSE									PLY_CMD_PAUSE
#define PLY_EVENT_RESUME								PLY_CMD_RESUME
#define PLY_EVENT_SEEKTIME							PLY_CMD_SEEKTIME
#define PLY_EVENT_AUTOSEEK							PLY_CMD_AUTOSEEK
#define PLY_EVENT_SETVOL								PLY_CMD_SETVOL
#define PLY_EVENT_SETMUTE							PLY_CMD_SETMUTE
#define PLY_EVENT_SETVOCAL							PLY_CMD_SETVOCAL
#define PLY_EVENT_SETMIC								PLY_CMD_SETMIC
#define PLY_EVENT_SETLYRIC							PLY_CMD_SETLYRIC
#define PLY_EVENT_SETSTAFF							PLY_CMD_SETSTAFF
#define PLY_EVENT_SETSCORE							PLY_CMD_SETSCORE
#define PLY_EVENT_GETVOL								PLY_CMD_GETVOL
#define PLY_EVENT_GETLYRIC							PLY_CMD_GETLYRIC
#define PLY_EVENT_GETSCORE							PLY_CMD_GETSCORE
#define PLY_EVENT_GETPLAYTIME					PLY_CMD_GETPLAYTIME
#define PLY_EVENT_GETTOTALTIME					PLY_CMD_GETTOTALTIME
#define PLY_EVENT_GETSTATE							PLY_CMD_GETSTATE
#define PLY_EVENT_SETFILETYPE						PLY_CMD_SETFILETYPE
#define PLY_EVENT_ENABLEEFFECTMUSIC		PLY_CMD_ENABLEEFFECTMUSIC
#define PLY_EVENT_PLAYEFFECTMUSIC			PLY_CMD_PLAYEFFECTMUSIC
#define PLY_EVENT_PLAYMIDICHEER				PLY_CMD_PLAYMIDICHEER
#define PLY_EVENT_SETEQFREQ						PLY_CMD_SETEQFREQ
#define PLY_EVENT_SETEQTYPE							PLY_CMD_SETEQTYPE
#define PLY_EVENT_GETEQFREQ						PLY_CMD_GETEQFREQ
#define PLY_EVENT_GETEQTYPE						PLY_CMD_GETEQTYPE
#define PLY_EVENT_TESTLATENCY					PLY_CMD_TESTLATENCY
#define PLY_EVENT_ENABLEEXTMIDI				PLY_CMD_ENABLEEXTMIDI
#define PLY_EVENT_RESETEXTMIDI					PLY_CMD_RESETEXTMIDI
#define PLY_EVENT_SETENCODE						PLY_CMD_SETENCODE
#define PLY_EVENT_CHANGEAUDIF					PLY_CMD_CHANGEAUDIF
#define PLY_EVENT_GETBUFFERINGFLAG		PLY_CMD_GETBUFFERINGFLAG
#define PLY_EVENT_GETPLAYERTYPE				PLY_CMD_GETPLAYERTYPE
#define PLY_EVENT_SETPLAYERTYPE				PLY_CMD_SETPLAYERTYPE
#define PLY_EVENT_PLAYBGV							PLY_CMD_PLAYBGV
#define PLY_EVENT_STOPBGV							PLY_CMD_STOPBGV
#define PLY_EVENT_SETBGVTYPE						PLY_CMD_SETBGVTYPE
#define PLY_EVENT_INITBGVVIEW					PLY_CMD_INITBGVVIEW
#define PLY_EVENT_FREEBGVVIEW					PLY_CMD_FREEBGVVIEW
#define PLY_EVENT_UPDATEBGVVIEW				PLY_CMD_UPDATEBGVVIEW
#define PLY_EVENT_GETBGVSTATE					PLY_CMD_GETBGVSTATE
#define PLY_EVENT_VOICERECORD					PLY_CMD_VOICERECORD
#define PLY_EVENT_STOPVOICERECORD			PLY_CMD_STOPVOICERECORD
#define PLY_EVENT_SETSPSOUNDEFFECT		PLY_CMD_SETSPSOUNDEFFECT
#define PLY_EVENT_SETRECAUDIOCONFIG		PLY_CMD_SETRECAUDIOCONFIG
#define PLY_EVENT_GETRECAUDIOCONFIG		PLY_CMD_GETRECAUDIOCONFIG

#define PLY_EVENT_ERROR									"error"
#define PLY_EVENT_TITLEINF_BEGIN				"titleon"
#define PLY_EVENT_TITLEINF_END					"titleoff"
#define PLY_EVENT_INTERLUDE_BEGIN			"interludebegin"
#define PLY_EVENT_INTERLUDE_END				"interludeend"
#define PLY_EVENT_STAFFSHOW						"staffshow"
#define PLY_EVENT_STAFFHIDE							"staffhide"
#define PLY_EVENT_LYRICPERCENT					"lyricpercent"
#define PLY_EVENT_LYRICCHANGED				"lyricchanged"
#define PLY_EVENT_STAFFADDSEG					"staffaddseg"
#define PLY_EVENT_SAVE_FILE							"savefile"
#define PLY_EVENT_VOICERECORD_MUTE		"voicerecordmute"
#define PLY_EVENT_VOICERECORD_READ		"voicerecordread"
#define PLY_EVENT_DRAW_HINTBALL				"drawhintball"
#define PLY_EVENT_CLEAR_HINTBALL				"clearhintball"
#define PLY_EVENT_LYRIC_LOADED					"lyricloaded"
//..............
#define PLY_EVENT_SEND_SEXTYPE				"sendsextype"
//..............

/*
*	stop event parameter
*/
#define PLY_EVENT_STOP_PARA_SCORE		"score"

/*
*	seek event parameter
*/
#define PLY_EVENT_AUTOSEEK_ENDPARA				"endpara"
/*
*	seek event parameter value
*/
#define PLY_EVENT_AUTOSEEK_ENDPARA_END		"end"
#define PLY_EVENT_AUTOSEEK_ENDPARA_LAST		"last"
#define PLY_EVENT_AUTOSEEK_ENDPARA_ERR			"error"

/*
*	getstate event parameters name
*/
#define PLY_EVENT_GETSTATE_STATE				"state"				// format: state=playing
/*
*	setscore cmd parameters value
*/
#define PLY_EVENT_GETSTATE_STATE_STOPPED				"stopped"
#define PLY_EVENT_GETSTATE_STATE_STOPPING				"stopping"
#define PLY_EVENT_GETSTATE_STATE_PARSING				"parsing"
#define PLY_EVENT_GETSTATE_STATE_PLAYING				"playing"
#define PLY_EVENT_GETSTATE_STATE_PAUSING				"pausing"
#define PLY_EVENT_GETSTATE_STATE_PAUSED					"paused"
#define PLY_EVENT_GETSTATE_STATE_SEEKING				"seeking"
#define PLY_EVENT_GETSTATE_STATE_DUMMY					"dummy"

/*
*	testlatecny event parameters name
*/
#define PLY_EVENT_TESTLATENCY_LATENCY						"latency"

/*
*	lyricpercent event parameter
*/
#define PLY_EVENT_LYRICPERCENT_PARA_LINENO				"lineno"
#define PLY_EVENT_LYRICPERCENT_PARA_LINESTR				"linestr"
#define PLY_EVENT_LYRICPERCENT_PARA_LINEPERCENT	"linepercent"

/*
*	lyricchange event parameter
*/
#define PLY_EVENT_LYRICCHANGE_PARA_LINENO				"lineno"
#define PLY_EVENT_LYRICCHANGE_PARA_LINESTR				"linestr"
#define PLY_EVENT_LYRICCHANGE_PARA_LINEPERCENT		"linepercent"

/*
*	staff add segment parameter
*/
#define PLY_EVENT_STAFFADDSEG_PARA_MODE					"mode"
#define PLY_EVENT_STAFFADDSEG_PARA_YNOTEKEY			"ynotekey"
#define PLY_EVENT_STAFFADDSEG_PARA_XBEGIN				"xbegin"
#define PLY_EVENT_STAFFADDSEG_PARA_XLEN					"xlen"
#define PLY_EVENT_STAFFADDSEG_PARA_HEADDRAW		"headdraw"

/*
*	draw hint ball event parameters
*/
#define PLY_EVENT_DRAW_HINTBALL_NUM							"num"

/*
*	lyric get string event parameter
*/
#define PLY_EVENT_GETLYRIC_STRING									"string"
#define PLY_EVENT_GETLYRIC_STARTTIME								"starttime"
#define PLY_EVENT_GETLYRIC_ENDTIME									"endtime"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: DECLARE SERVICE REGISTRY */
EZ_SERVICE_REGISTRY_DECLARE(playerService);
/* TODO END */
int player_service_getplayertime(ezServiceHandle_t* hdle);

#ifdef __cplusplus
}
#endif

#endif

