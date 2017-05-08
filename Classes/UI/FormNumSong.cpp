//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormNumSong.cpp
//																	
// Description: 
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#include "CEGUI.h"
#include "appKRK.h"
#include "FormID.res.h"
#include "FormNumSong.h"
#include "FormNumSong.res.h"
#include "Widgets/M3D_Label.h"
#include "M3D_Config.h"


namespace	CEGUI
{	
static const int NumImage_ID = 0x21a7;
static const int NumLength = 5;
static const int NumShowLenMax = 10000;

static String HideNumTimer("HideNumTimer"); 
static String ProgCountTimer("ProgCountTimer");

const String FormNumSong::EventNamespace("FormNumSong");
const String FormNumSong::WidgetTypeName("FormNumSong");

//----------------------------------------------------------------------------//
FormNumSong::FormNumSong(const String& type, const String& name):
M3D_Form(type, name)
{

}

//----------------------------------------------------------------------------//
FormNumSong::~FormNumSong(void)
{

}

//----------------------------------------------------------------------------//

void FormNumSong::constructWindow(WndRes_t *wndRes)
{
	M3D_Form::constructWindow(wndRes);
}

//----------------------------------------------------------------------------//
void FormNumSong::destructWindow(void)
{
	M3D_Form::destructWindow();
}
	
//----------------------------------------------------------------------------//
void FormNumSong::onShown(WindowEventArgs& e)
{
	M3D_Form::onShown(e);
	
	destroyTimer(ProgCountTimer);
	createTimer(ProgCountTimer, 1000, true, 0);
	//static_cast<appKRK*>(getApp())->resetPowerOffTimer();
}

//----------------------------------------------------------------------------//
void FormNumSong::onHidden(WindowEventArgs& e)
{
	M3D_Form::onHidden(e);

	destroyTimer(HideNumTimer);
	destroyTimer(ProgCountTimer);
}

//----------------------------------------------------------------------------//
void FormNumSong::onCreated(void)
{
	M3D_Form::onCreated();

	d_numbg = static_cast<M3D_Label*>(getChild(Res_FormNumSong::NumBG));
	d_songname = static_cast<M3D_Label*>(d_numbg->getChild(Res_FormNumSong::SongName));
	
	d_progcount = static_cast<M3D_Label*>(getChild(Res_FormNumSong::ProgCount));
	d_count = static_cast<M3D_Label*>(d_progcount->getChild(Res_FormNumSong::Count));

	ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
	d_initCount = reqDB->ReqReservedSongCount();
	char str[16];
	sprintf(str, "%d", d_initCount);
	d_count->setString(str);

	createTimer(ProgCountTimer, 1000, true, 0);
	
}

//----------------------------------------------------------------------------//
void FormNumSong::onDestroyed(void)
{	
	M3D_Form::onDestroyed();
}

//----------------------------------------------------------------------------//
void FormNumSong::onActivated(ActivationEventArgs& e)
{
	M3D_Form::onActivated(e);

	d_num = 0;
	showNumber();
	d_progcount->show();
}

//----------------------------------------------------------------------------//
void FormNumSong::onDeactivated(ActivationEventArgs& e)
{
	M3D_Form::onDeactivated(e);
}

//----------------------------------------------------------------------------//
void FormNumSong::onActionStart(void)
{
	M3D_Form::onActionStart();
}

//----------------------------------------------------------------------------//
void FormNumSong::onActionEnd(void)
{
	M3D_Form::onActionEnd();
}

//----------------------------------------------------------------------------//
void FormNumSong::onTimeout(EventArgs& e)
{
	TimerEventArgs& te = (TimerEventArgs&)e;
	if(te.d_name == HideNumTimer)
	{
		hideNumber();
	}
	else if(te.d_name == ProgCountTimer)
	{
		ReqPhoneDB* reqDB = (ReqPhoneDB*)ReqDB::getSingletonPtr();
		if (d_initCount != reqDB->ReqReservedSongCount())
		{
			d_initCount = reqDB->ReqReservedSongCount();
			char str[16];
			sprintf(str, "%d", d_initCount);
			d_count->setString(str);
		}
	}
}
	
//----------------------------------------------------------------------------//
void FormNumSong::onCharacter(KeyEventArgs& e)
{
	if (isDisabled() || !isActive())
		return;
			
	switch (e.codepoint) 
	{
	case M3D_UI_KEY_NUM_0:	
	case M3D_UI_KEY_NUM_1:
	case M3D_UI_KEY_NUM_2:
	case M3D_UI_KEY_NUM_3:
	case M3D_UI_KEY_NUM_4:
	case M3D_UI_KEY_NUM_5:
	case M3D_UI_KEY_NUM_6:
	case M3D_UI_KEY_NUM_7:
	case M3D_UI_KEY_NUM_8:
	case M3D_UI_KEY_NUM_9:
	{
		int pressNumber = 0;
		#ifdef WIN32
			pressNumber = e.codepoint - M3D_UI_KEY_NUM_0;
		#else
			if (e.codepoint == M3D_UI_KEY_NUM_0)
				pressNumber = 0;
			else
				pressNumber = e.codepoint - M3D_UI_KEY_NUM_1 + 1;
		#endif
		if (d_num < NumShowLenMax)
			d_num = d_num * 10 + pressNumber;
		else
			d_num = (d_num % NumShowLenMax) * 10 + pressNumber;
		showNumber();
	}
	break;
	case M3D_UI_KEY_BKSP:
		if(d_numbg->isVisible())
		{
			d_num /= 10;
			showNumber();
		}
		break;/*
	case M3D_UI_KEY_PROG:
		if(d_numbg->isVisible() && d_showname.size())
			handleProgClicked();
		break;
	case M3D_UI_KEY_ENTER:
		if(d_numbg->isVisible() && d_showname.size())
			handleEnterClicked();
		break;
	case M3D_UI_KEY_PLAY:
		{	
			ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
			if (d_numbg->isVisible() && d_showname.size() && reqDb->ReqReservedSongCount() > 0)
				handleInsertClicked();
			else
				handlePlayClicked();
			break;
		}
		break;*/

	case M3D_UI_KEY_KARAOKE:
	{
		d_numbg->hide();
		d_progcount->hide();
		getApp()->transitionForm(FrmMain_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT, false);
	}
	break;
	case M3D_UI_KEY_SETUP:
	{
		d_numbg->hide();
		d_progcount->hide();
		getApp()->transitionForm(FrmSetup_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT, false);
	}
	break;
	/*
	case M3D_UI_KEY_N:
		{
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmMain_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT, false);
			//getApp()->transitionForm(FrmShortMain_ID, getID(), &action);
		}
		break;
	case M3D_UI_KEY_SEARCH:
		{	
			M3D_Log* mlog = getApp()->getFormLog(FrmSingerSong_ID);
			mlog->setParamInt("Type", REQDB_TYPE_PINYIN);
			mlog->setParamInt("SubType", 0);
			mlog->setParamInt("Position", 0);
			mlog->setParamString("StrPara", "");
			
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmSingerSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_FAVO:
		{
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmFavoSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_SELECTED:
		{
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmProgSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_MTV:
		{
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmMTV_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_NEWSONG:
		{
			d_numbg->hide();
			d_progcount->hide();
			getApp()->transitionForm(FrmNewSong_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		}
		break;
	case M3D_UI_KEY_SETUP:
		{
			getApp()->transitionForm(FrmSetup_ID, getID(), FORM_TRANSITION_ANIMATION::ANIMATION_NONE);
		}
		break;*/
	default:
		break;
	}
		
	M3D_Form::onCharacter(e);
}
//----------------------------------------------------------------------------//
void FormNumSong::showNumber(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
	handleM3DRec* handle = &(reqDb->handle);

	handle->reqCmd.type = REQDB_TYPE_NUM_SONG;
	handle->reqCmd.ssType = d_num;
	reqDb->reqInit(handle->reqCmd, 1);

	d_numbg->show();
	setNumber();
	d_showname = reqDb->bindingRec.items[0].song.SongName;
	d_songname->setString(d_showname);
	
	destroyTimer(HideNumTimer);
	createTimer(HideNumTimer, 30000, false, 0);
}

//----------------------------------------------------------------------------//
void FormNumSong::hideNumber(void)
{
	d_num = 0;
	d_showname.clear();
	setNumber();
	d_songname->setString("");
	d_numbg->hide();
}
//----------------------------------------------------------------------------//
void FormNumSong::setNumber(void)
{
	int temp = 10;
	for(int i = 0; i < NumLength; i++)
	{
		int index = d_num % temp / (temp / 10);
		temp *= 10;
		static_cast<M3D_Label*>(d_numbg->getChildAtIdx(i))->setImage(NumImage_ID + index);
	}
}
//----------------------------------------------------------------------------//
bool FormNumSong::playSong(void)
{
	if (d_showname.size() == 0)
		return false;
	
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());
	int songIndex = reqDb->bindingRec.items[0].song.SongIndex;
	
#ifndef CAN_RESERVED_SAME_SONG
	reqDb->ReqReservedSongDelete(songIndex);
#endif
	if(!reqDb->ReqReservedSongInsert(songIndex))
		return false;

	//return static_cast<appKRK*>(getApp())->playNextSong();
	getApp()->transitionForm(FrmPlay_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);

	return true;
}

//----------------------------------------------------------------------------//
bool FormNumSong::handleProgClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

#ifndef RES_ADD_NOT_REQ_DB
	if (reqDb->ReqReservedSongAdd(reqDb->bindingRec.items[0].song.SongIndex))
#else
	if (reqDb->ReqReservedSongAdd(&reqDb->bindingRec.items[0].song))
#endif
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------//
bool FormNumSong::handlePlayClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	if(d_showname.size())
	{
		reqDb->ReqReservedSongInsert(reqDb->bindingRec.items[0].song.SongIndex);
		//return static_cast<appKRK*>(getApp())->playNextSong();
		getApp()->transitionForm(FrmPlay_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		return true;
	}
	else if(reqDb->ReqReservedSongCount() > 0)
	{
		//return static_cast<appKRK*>(getApp())->playNextSong();
		getApp()->transitionForm(FrmPlay_ID, getID(), FORM_TRANSITION_ANIMATION::LEFTIN_LEFTOUT);
		return true;
	}

	return false;
}


//----------------------------------------------------------------------------//
bool FormNumSong::handleInsertClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

#ifndef CAN_RESERVED_SAME_SONG
	reqDb->ReqReservedSongDelete(reqDb->bindingRec.items[0].song.SongIndex);
#endif
	if(reqDb->ReqReservedSongInsert(reqDb->bindingRec.items[0].song.SongIndex))
		return true;
	
	return false;
}

//----------------------------------------------------------------------------//
bool FormNumSong::handleEnterClicked(void)
{
	ReqPhoneDB* reqDb = (ReqPhoneDB *)(ReqPhoneDB::getSingletonPtr());

	if (reqDb->ReqReservedSongCount() <= 0)
	{
		playSong();
		return true;
	}
	return handleProgClicked();
}

}