//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : FormPlay.h
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
#pragma once

#ifndef _FORMPLAY_H_
#define _FORMPLAY_H_

#include "Widgets/M3D_Form.h"
#include <vector>
#include <lib/edb/edb.h>

typedef enum
{
	PLAYBAR_NONE = 0,
	PLAYBAR_PLAYPAUSE = (1<<0),
	PLAYBAR_REC = (1<<1),
	PLAYBAR_VOCAL = (1<<2),
	PLAYBAR_MUTE = (1<<3),
	PLAYBAR_MODE = (1<<4),
	PLAYBAR_ALL = 0xFFFF,
} PLAYBARITEM_t;

class EventListenerCustom;

namespace CEGUI
{
	class M3D_Label;
	class M3D_Log;
	class PlayParam;
	class FormMain;
	class FormPlay:public M3D_Form
	{
	public:

		FormPlay(const String& type, const String& name);
		virtual ~FormPlay();

		static const String EventNamespace; 			//!< Namespace for global events
		static const String WidgetTypeName; 			//!< Window factory name

		virtual void constructWindow(WndRes_t *wndRes);
		virtual void destructWindow();

	    virtual void onShown(WindowEventArgs& e);
		virtual void onHidden(WindowEventArgs& e);

		virtual void onCreated();
		virtual void onDestroyed();

		virtual void onActivated(ActivationEventArgs& e);
		virtual void onDeactivated(ActivationEventArgs& e);

		virtual void onActionStart();
		virtual void onActionEnd();
		virtual void onTimeout(EventArgs& e);

		virtual void onCharacter(KeyEventArgs& e);
		bool playSong(String filepath);
        void playStoped();	
		void setHitInfo();
		void playNextSong(int curSongIndex);
		int MCodeConvert_UTF8toGB2312(const char* in_utf8, char* out_gb2312, int Len1,int Len2);
		int getSongIndex(void);
		std::string getSongName(void);
		void updatePlayerInfo(void);
	private:
		M3D_Log *d_log;
		M3D_Label* d_playSongName;
		M3D_Label* d_nextSongName;
		//player 
		int				d_songIndex;
		std::string		d_songName;
		std::string		d_singer;
		std::string		d_songpath;
		std::string		d_userName;
		std::string		d_userId;
		unsigned int	d_randomId;

		int				d_playStatus;
		int				d_ShowNextInfoFlag;
		String m_curSongName;
		//String m_playSongName;
		String m_nextSongName;
		bool isEnterPressed;
	
		
		int m_typeOfUIbg;
		void refreshPlayerInfo(M3D_Log *eventData);
		void refreshSongInfo(void);
        void setPlayStatus(String playStatus);
		void setPlayStatus(int Status);
		void handleCmdStop();
		bool handleCmdPause(const CEGUI::EventArgs& e);
		bool handleCmdPlay(const CEGUI::EventArgs& e);
		void hidePlayTitle(void);
		bool handleMOVIEClicked(const CEGUI::EventArgs& e);
		bool handleMTVClicked(const CEGUI::EventArgs& e);
		bool handleMP3Clicked(const CEGUI::EventArgs& e);
		int	d_playState;
		int		d_songType;
		int		d_fileType;
		//song info
		SongListBindingStruct_t d_SongInfo;
		SongListBindingStruct_t d_NextInfo;
		//listener
		EventListenerCustom * playerListener;
		std::vector<EventListenerCustom *> listenerList;
		int d_showStatusFlag;
	};
}
#endif
