#ifndef _CUSTOM_WIDGETS_H_
#define _CUSTOM_WIDGETS_H_

#ifndef CID_M3D_Max_Widgets
#define CID_M3D_Max_Widgets 0x1000
#endif


#define M3D_REGISTER_FORMS() {\
	M3D_REGISTER_FORM(FormMain);\
	M3D_REGISTER_FORM(FormSingerSong);\
	M3D_REGISTER_FORM(FormProgSong);\
	M3D_REGISTER_FORM(FormSinger);\
	M3D_REGISTER_FORM(FormLanguage);\
	M3D_REGISTER_FORM(FormDownload);\
	M3D_REGISTER_FORM(FormDownloadMp3);\
	M3D_REGISTER_FORM(FormDownloadMTV);\
	M3D_REGISTER_FORM(FormDownloadMovie);\
	M3D_REGISTER_FORM(FormNumSong);\
	M3D_REGISTER_FORM(FormSetup);\
	M3D_REGISTER_FORM(FormPlay);\
	M3D_REGISTER_FORM(FormShortMain);\
	M3D_REGISTER_FORM(FormShortSingerSong);\
	M3D_REGISTER_FORM(FormShortProgSong);\
	M3D_REGISTER_FORM(FormShortMTV);\
	M3D_REGISTER_FORM(FormShortFavoSong);\
	M3D_REGISTER_FORM(FormShortSinger);\
	M3D_REGISTER_FORM(FormShortLanguage);\
	M3D_REGISTER_FORM(FormShortDownload);\
	M3D_REGISTER_FORM(FormShortMp3);\
	M3D_REGISTER_FORM(FormShortMovie);\
}

enum
{
	CID_AppKRK = CID_M3D_Max_Widgets,
	CID_FormMain,
	CID_FormLanguage = 0x1003,
	CID_FormSinger = 0x1004,
	CID_FormSingerSong = 0x1005,
	CID_FormNumSong = 0x1006,
	CID_FormProgSong = 0x1008,
	CID_FormPlay = 0x100a,
	CID_FormSetup = 0x100c,
	CID_FormDownload = 0x1011,
	CID_FormDownloadMp3 = 0x1012,
	CID_FormDownloadMTV = 0x1013,
	CID_FormDownloadMovie = 0x1014,
	CID_FormShortSingerSong = 0x1016,
	CID_FormShortFavoSong = 0x1017,
	CID_FormShortProgSong = 0x1018,
	CID_FormShortMTV = 0x1019,
	CID_FormShortMain = 0x101E,
	CID_FormShortLanguage = 0x101F,
	CID_FormShortSinger = 0x1020,
	CID_FormShortDownload = 0x1022,
	CID_FormShortMp3 = 0x1023,
	CID_FormShortMovie = 0x1024,
};

#include "FormMain.h"
#include "FormSingerSong.h"
#include "FormProgSong.h"
#include "FormSinger.h"
#include "FormLanguage.h"
#include "FormDownload.h"
#include "FormDownloadMp3.h"
#include "FormDownloadMTV.h"
#include "FormDownloadMovie.h"
#include "FormNumSong.h"
#include "FormSetup.h"
#include "FormPlay.h"
#include "FormShortMain.h"
#include "FormShortSingerSong.h"
#include "FormShortMTV.h"
#include "FormShortFavoSong.h"
#include "FormShortProgSong.h"
#include "FormShortSinger.h"
#include "FormShortLanguage.h"
#include "FormShortDownload.h"
#include "FormShortMp3.h"
#include "FormShortMovie.h"
#endif