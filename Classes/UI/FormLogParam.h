#ifndef _FORMLOGPARAM_H
#define _FORMLOGPARAM_H

#include <string>

class LogParam
{
public:
	//FormMain
	//static std::string MainFm_ClickedBtn;
	
    static std::string MainFm_StorageDeviceState;
	static std::string DefaultParam_LastForm;
	//FormLanguage
	static std::string fmParam_FocusIdx;
	static std::string fmParam_FocusLanType;
	static std::string fmParam_BackForm;
	static std::string fmParam_FocusSingerIdx;
	static std::string fmParam_FocusSongIdx;
	static std::string fmParam_InputString;
	static std::string fmParam_DLFileName;
	static std::string fmParam_GameName;

	// FormInfomation
	static std::string InfoFm_CallFormID;
	static std::string InfoFm_InfoLineCnt;
	static std::string InfoFm_InfoLine1;
	static std::string InfoFm_InfoLine2;
	static std::string InfoFm_ButtonCnt;
	static std::string InfoFm_ButtonCmd1;
	static std::string InfoFm_ButtonCmd2;
	static std::string InfoFm_ButtonCmd3;
	static std::string InfoFm_Result;
	//static std::string InfoFm_LastFormID;

	// formPlay
	static std::string playFm_RefreshInfoType;
	static std::string playFm_TitleStatus;
	static std::string playFm_PlayStatus;
	static std::string playFm_PopMenu;
	static std::string playFm_PlayNext;
	static std::string playFm_SongIndex;
	static std::string playFm_RecIndex;
	static std::string playFm_Score;
	static std::string playFm_Storage;
    static std::string playFm_PKMode;

	static std::string playFm_ListForm;
	static std::string playFm_ListFormParam;

	// formScore
	static std::string scoreFm_ScoreMode;
	static std::string scoreFm_SingleScore;
	static std::string scoreFm_ScoreLeft;
	static std::string scoreFm_ScoreRight;

	//formRecSave
	static std::string RecSaveFm_Result;

    //formTunning formTunningMTV
	static std::string tunningFm_EnterKey;
	
};
#endif
