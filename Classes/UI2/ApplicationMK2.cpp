#include "Base/Director.h"
#include "PVRCore/Log.h"
#include "SceneMain.h"
#include "ApplicationMK2.h"
#include "GUIBase/ParamConfig.h"
#include "CEGUI/CEGUI.h"
#include "GUIBase/M3D_Event.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define DESIGN_RESOLUTION_WIDTH			1280
#define DESIGN_RESOLUTION_HEIGHT		720

//静态变量初始化
InterfaceFontManager* ApplicationMK::_FontManager = nullptr;

static SceneMain *scene = nullptr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ApplicationMK::ApplicationMK()
{
	
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Code in initApplication() will be called by pvr::Shell once per run, before the rendering context is created.
		Used to initialize variables that are not dependent on it (e.g. external modules, loading meshes, etc.)
		If the rendering context is lost, initApplication() will not be called again.
***********************************************************************************************************************/
bool ApplicationMK::InitApplication()
{
	//调试内存泄漏,AuthHardware没有Deinit
	//_CrtSetBreakAlloc(221);
	//_CrtSetBreakAlloc(219);
	//_CrtSetBreakAlloc(2566);
	//_CrtSetBreakAlloc(478);
	//_CrtSetBreakAlloc(1025);
	//_CrtSetBreakAlloc(990);
	//_CrtSetBreakAlloc(1025);
	//_CrtSetBreakAlloc(1008);
	//_CrtSetBreakAlloc(4318);
	//_CrtSetBreakAlloc(1135);
	//_CrtSetBreakAlloc(2926);
	//_CrtSetBreakAlloc(383);
	//_CrtSetBreakAlloc(382);
	//_CrtSetBreakAlloc(7293);
	//_CrtSetBreakAlloc(585);
	//_CrtSetBreakAlloc(3544);
	//_CrtSetBreakAlloc(3698);
	//_CrtSetBreakAlloc(626);
	//_CrtSetBreakAlloc(4226);
	
	return true;
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Code in quitApplication() will be called by pvr::Shell once per run, just before exiting the program.
        If the rendering context is lost, QuitApplication() will not be called.
***********************************************************************************************************************/
bool ApplicationMK::QuitApplication()
{

	return true; 
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occured
\brief	Code in initView() will be called by pvr::Shell upon initialization or after a change in the rendering context.
		Used to initialize variables that are dependant on the rendering context (e.g. textures, vertex buffers, etc.)
***********************************************************************************************************************/
#ifdef _WIN32
bool ApplicationMK::InitView()
#else
bool ApplicationMK::InitView(int w, int h)
#endif
{
#ifdef _WIN32
	int w = GetSystemMetrics(SM_CXFULLSCREEN);// SM_CXSCREEN
	int h = GetSystemMetrics(SM_CYFULLSCREEN); //SM_CYSCREEN
#else

#endif

	//UI界面设计分辨率初始化
	CEGUI::ParamConfig::DesignSize.d_width = DESIGN_RESOLUTION_WIDTH;
	CEGUI::ParamConfig::DesignSize.d_height = DESIGN_RESOLUTION_HEIGHT;
	CEGUI::ParamConfig::GetSingleInstance()->SetDisplaySize(w, h);

	/*GetFontManager(_FontManager);
	if(_FontManager != nullptr)
	{
		pvr::Log(pvr::Log.Information, "FontManager Get Succeed\n");
	//	_FontManager->AddFont("ArialUni", std::string(resPath.c_str()) + "ARIALUNI.TTF");
		std::string respath = "E:/Simulator/RES/";
		_FontManager->AddFont("ArialUni", respath + "ARIALUNI.TTF");
	}
	*/

	Director *director = Director::getInstance();
	if(director != nullptr)
	{
		pvr::Log(pvr::Log.Information, "Director Init Succeed\n");
		director->init(w, h, DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT, "ArialUni");
		director->setAnimationInterval(1.0 / 60);

		//scene = SceneMain::create();
		//director->runWithScene(scene);
	}

	return true;
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Code in releaseView() will be called by pvr::Shell when the application quits or before a change in the rendering context.
***********************************************************************************************************************/
bool ApplicationMK::ReleaseView()
{
	Director *director = Director::getInstance();
	if(director != nullptr)
	{
		director->end();
        director->mainLoop();
		director = nullptr;
		pvr::Log(pvr::Log.Information, "Director DeInit Succeed\n");
	}

	return true;
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Main rendering loop function of the program. The shell will call this function every frame.
***********************************************************************************************************************/
bool ApplicationMK::RenderScene()
{
	Director *director = Director::getInstance();

	float DeltaTimeSecs = director->getDeltaTime();
	//M3D_DebugPrint("Render %f\n", DeltaTimeSecs);

	float timeElapsed = DeltaTimeSecs * 1000;

	if(timeElapsed > 60)
		timeElapsed = 60;

	director->mainLoop();

	return true;
}

/*
void ApplicationMK::AddCameraPic(std::string path)
{
	static int _playPicIndex2 = 0;
	if(PicPlayer1 != nullptr)
	{
		PicPlayer1->SetPlayIndex(_playPicIndex2);
		_playPicIndex2++;

		pvr::Log(pvr::Log.Information, "Camera Path %s", path.c_str());
		int nTotal = PicPlayer1->AddCameraFile(path);
		//PicPlayer1->SetCameraIndex(nTotal - 1);
	}
}

void ApplicationMK::AddCameraBuff(unsigned char *_cambuff, int _size)
{
	//static int _playPicIndex2 = 0;
	if(PicPlayer1 != nullptr)
	{
		int nTotal = PicPlayer1->AddCameraBuffer(_cambuff, _size);
		PicPlayer1->SetCameraIndex(nTotal - 1);
		//PicPlayer1->SetPlayIndex(_playPicIndex2);
		//_playPicIndex2++;
	}
}*/

bool ApplicationMK::queueKeyEvent(int key, int state)
{
	M3D_Event_t pushEvent;
	if(state == 0)
	{

	}
	else if(state == 1)
	{
		pushEvent.type = M3D_EVENT_KEYBOARD;
		pushEvent.para.kb.keycode = key;
		//appUI->pushEvent(pushEvent);
		//appUI->checkAnyKeyDown();
	}
	else if(state == 255) 
	{
		//appUI->exit();
	}
	
	return true;
}


bool ApplicationMK::queueMotionEvent(int action, float x, float y, float pressure)
{

	/*
	M3D_Event_t pushEvent;

#ifdef _WIN32
	int w = GetSystemMetrics(SM_CXFULLSCREEN);// SM_CXSCREEN
	int h = GetSystemMetrics(SM_CYFULLSCREEN); //SM_CYSCREEN
	x *= w;
	y *= h;
#endif

	if(action == 0)
	{
		CEGUI::System::getSingleton().injectMousePosition(x, y);
		pushEvent.type = M3D_EVENT_MOUSE;
		pushEvent.para.mouse.button = CEGUI::LeftButton;
		pushEvent.para.mouse.type = M3D_MOUSEEVENT_DOWN;

		pushEvent.para.mouse.x = x;
		pushEvent.para.mouse.y = y;

		StartX = x;
		StartY = y;
	}
	else if(action == 1)
	{
		CEGUI::System::getSingleton().injectMousePosition(x, y);
		pushEvent.type = M3D_EVENT_MOUSE;
		pushEvent.para.mouse.button = CEGUI::LeftButton;
		pushEvent.para.mouse.type = M3D_MOUSEEVENT_UP;

		pushEvent.para.mouse.x = x;
		pushEvent.para.mouse.y = y;

		EndX = x;
		EndY = y;

	}
	else if(action == 2)
	{
		CEGUI::System::getSingleton().injectMousePosition(x, y);
		float dx = x - StartX;
		float dy = y - StartY;
		pushEvent.type = M3D_EVENT_MOUSE;
		pushEvent.para.mouse.button = CEGUI::NoButton;
		pushEvent.para.mouse.type = M3D_MOUSEEVENT_MOVE;
		pushEvent.para.mouse.x = dx;
		pushEvent.para.mouse.y = dy;

		StartX = x;
		StartY = y;
	}
	else if(action == 261) //
	{
		//pushEvent.type = M3D_EVENT_KEYBOARD;
		//pushEvent.para.kb.keycode = M3D_UI_KEY_RETURN; 			
	}
	else if(action == 517)//
	{


	}*/
	return true;
}

#ifdef _WIN32
static PVRShell *AppShell = NULL;
///////////////////////////////////////////////////////////////////////////////////
PVRShell* NewDemo()
{
	if(AppShell == NULL)
	{
		AppShell = new ApplicationMK();
	}
	return AppShell; 
}

PVRShell* FreeDemo(void)
{
	if(AppShell != NULL)
	{
		delete AppShell;
		AppShell = NULL;
	}
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////
#endif