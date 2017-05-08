//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_App.h
//																	
// Description: multak 3D GUI application base class
//			in base class we load resource , register widgets and create root window
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//
#ifndef _M3D_APP_H_
#define _M3D_APP_H_

#include "GUIBase/M3D_WindowManager.h"
#include "GUIBase/M3D_Event.h"
#include "GUIBase/M3D_Action.h"
#include "GUIBase/M3D_Log.h"

#include <unordered_map>
#include <deque>

namespace CEGUI
{
class M3D_Form;
class M3D_Log;
class M3D_App
{
public:

	typedef enum
	{
		APP_STATE_FIRST,
		APP_STATE_IDLE,
		APP_STATE_STOP,
		APP_STATE_RUN,
	}M3D_AppState_et;

	M3D_App();
	virtual ~M3D_App(void);

	virtual void onFirstInit(){};
	virtual void onRenderUI(float timeElapsed){};
	virtual void onRegisterForms(){};
	virtual void onExit(){};

	//====================================================================//
	bool init(const String& Name, const String& resFile);
	void deInit(void);

	bool renderUI(float timeElapsed);

	void pushEvent(M3D_Event_t& Event);
	int popEvent(void);
	void cleanupEvents(void);
	void fireEvent(M3D_Event_t& Event);

	bool isRunning(){return d_running;};

	void setMainForm(uint wndId) {d_mainForm = wndId;}
	
	//´´½¨É¾³ý
	M3D_Form* createForm(uint formId);
	bool destroyForm(uint formId);
	//ÏÔÊ¾Òþ²Ø
	M3D_Form* showForm(uint formId);
	bool hideForm(uint formId, bool returnLastForm = false);
	//¶¯»­ÏÔÊ¾Òþ²ØForm
	void transitionForm(int newFormID, int oldFormID, FORM_TRANSITION_ANIMATION animationType, bool canReturn = true);

	bool cleanupForms();

	M3D_Log*	getFormLog(uint formId);
	bool cleanupLogs();

	M3D_Form* getForm(uint formId);
	M3D_Form* getLastForm(void);
	M3D_Form* getActiveForm(void);

	Window_2D* getRootWindow(void) {return d_windowManager->getRootWindow();}

private:

	void transitionFormInner(uint inFormID, uint outFormID, M3D_Action *action, bool canReturn);
	void showFormInner(uint formId);
	void showFormNoAdjust(uint formId);
	void hideFormInner(uint formId);

	M3D_WindowManager*						d_windowManager;
	uint									d_mainForm;
	String									d_resFileName;
	std::unordered_map<uint, M3D_Form*>		d_formList;
	std::unordered_map<uint, M3D_Log*>		d_formLogList;

	M3D_Form*								d_lastForm;
	std::deque<M3D_Event_t>					d_eventList;

	M3D_AppState_et							d_runState;
	bool									d_running;

	std::deque<uint>						d_inFormIDList;
	std::deque<uint>						d_outFormIDList;
	std::deque<FORM_TRANSITION_ANIMATION>   d_actionTransitionList;
	std::deque<bool>						d_canReturnList;

	M3D_Form*								d_lastInForm;
	M3D_Form*								d_lastOutForm;

	uint									d_lastInFormID;
	uint									d_lastOutFormID;
};

}

#endif


