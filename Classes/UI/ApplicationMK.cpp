#include "Base/Director.h"
#include "Platform/FileUtils.h"
#include "PVRCore/Log.h"
#include "SceneMain.h"
#include "GUIBase/ParamConfig.h"

#include "ApplicationMK.h"
#include "MultakSettings.h"

#include "appKRK.h"
#include "FormID.res.h"
//#include "ReqEDB/InterfaceDataBaseManager.h"
#include "ReqEDB/ReqMICEDB.h"

#include "M3D_Config.h"

#include "KRKPlayer/VideoManager.h"

//#define FUNC_OFN_ON
#ifdef FUNC_OFN_ON
#include "kkinput/kkinput-ext.h"
#endif

#define DESIGN_RESOLUTION_WIDTH			1280
#define DESIGN_RESOLUTION_HEIGHT		720

//锟斤拷态锟斤拷锟斤拷锟斤拷始锟斤拷
InterfaceFontManager* ApplicationMK::_FontManager = nullptr;

static SceneMain *scene;

static MultakSettings* _pMultakSettings = nullptr;

long RenderIn[6] = {0, 0, 0, 0, 0, 0};
long RenderOut[6] = {0, 0, 0, 0, 0, 0};

using namespace CEGUI;
//just for DemoCode
std::string g_appEnterPath = "";
std::string g_SysDataPath = "";
std::string g_AppDataPath = "";
std::string g_BuildInDataPath = "";
std::string g_fontFilePath = "";
std::string g_DownloadPath = "";

appKRK*	appUI;
#define FONTS_DIR_PATH		"/system/fonts/"	

void start_app(void)
{
#if 1
	appUI = new  appKRK(FrmNumSong_ID);
#else
	appUI = new appKRK(FrmTest_ID);
#endif
	assert(appUI != NULL);
	// detect buildInDev file
	//std::string buildInPath = _pAppPathManager->getRootPath(BuildInDataPath);
	//appUI->buildInDeviceFileDetect(buildInPath);

	//appUI->setUpdateFormID(FrmUpdate_ID);
	std::string respath = g_AppDataPath+String("RES/en/M3D_EN.res");//_pAppPathManager->getResDirFilePath(AppDataPath, APP_SYS_RES_FILE);
	
	//std::string respath = "F:\\KaraokeSystem_170421\\KaraokeSystem\\Simulator\\RES\\en\\M3D_EN.res";
	
	pvr::Log(pvr::Log.Information, "res path %s", respath.c_str());
	appUI->init("appUI", respath);
	M3D_DebugPrint("finish app UI init \n");
	appUI->initDownloadFile();

	new MKSystem(NULL);
	std::string resdir = g_AppDataPath+String("RES/");
	MKSystem::getSingletonPtr()->init(resdir.c_str(), DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);

	new MKPlayer(appUI);
	std::string playres = g_AppDataPath+String("RES/player720p.res");

	MKPlayer::getSingletonPtr()->initAudio("AWJAVA");
	MKPlayer::getSingletonPtr()->init(playres.c_str());
	MKPlayer::getSingletonPtr()->setPlayerType("mus");
	MKPlayer::getSingletonPtr()->initView("mus");
	MKPlayer::getSingletonPtr()->setPlayerType("video");
	MKPlayer::getSingletonPtr()->initView("video");
	//MKPlayer::getSingletonPtr()->initBgvView("picture");
	//MKPlayer::getSingletonPtr()->initBgvView("video");
	// TODO  sudan  
	int inlatency = 260;
	int outlatency = 160; 
	M3D_DebugPrint("start app  inlatency[%d] outlatency[%d] \n",inlatency,outlatency);
	MKPlayer::getSingletonPtr()->setAudioPara(4, 2, 48000, 48000, inlatency);   

	new MKRecEncoder(appUI);
	MKRecEncoder::getSingletonPtr()->init(128, inlatency, outlatency);
	K_PRINT_ON(ALL);

}

void stop_app(void)
{
	//reqMicEDB->deinit();
	//delete reqMicEDB;

	MKPlayer* player = (MKPlayer*)MKPlayer::getSingletonPtr();
	player->disableEffectMusic();

	appUI->deInit();
	delete appUI;

	MKRecEncoder::getSingletonPtr()->deinit();
	MKPlayer::getSingletonPtr()->deinitAudio();
	MKPlayer::getSingletonPtr()->deinit();
	MKConfig::getSingletonPtr()->unload(0);
	MKSystem::getSingletonPtr()->deinit();

	delete MKConfig::getSingletonPtr();
	delete MKSystem::getSingletonPtr();
	delete MKPlayer::getSingletonPtr();
	delete MKRecEncoder::getSingletonPtr();
}

int kkInput_EventCallback_New(int dt, int dx, int dy, unsigned char event, unsigned char index);
void MultakOFNSwitch(int flag)
{
#ifdef FUNC_OFN_ON
	if(flag == 1)
	{
#ifdef _WIN32
		kkInput_Init(kkInput_EventCallback_New);
#else
		kkInput_Init(kkInput_EventCallback_New);
#endif
	}
	else
	{
		kkInput_Deinit();
	}
#endif
}

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
	//�����ڴ�й©,AuthHardwareû��Deinit
	//_CrtSetBreakAlloc(1387);
	//_CrtSetBreakAlloc(103560);
	//_CrtSetBreakAlloc(32469);
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

	if(w == 0 && h == 0)
	{
		Director::getInstance()->ResetGLRenderer();
		return true;
	}

	//UI???????????????
	CEGUI::ParamConfig::DesignSize.d_width = DESIGN_RESOLUTION_WIDTH;
	CEGUI::ParamConfig::DesignSize.d_height = DESIGN_RESOLUTION_HEIGHT;
	CEGUI::ParamConfig::ViewPortW = DESIGN_RESOLUTION_WIDTH;
	CEGUI::ParamConfig::ViewPortH = DESIGN_RESOLUTION_HEIGHT;
	CEGUI::ParamConfig::GetSingleInstance()->SetDisplaySize(w, h);

	//get path form JAVA
#ifdef _WIN32
	char DesPath[512] = {0};
	char *p = _getcwd(DesPath, 512);
	g_appEnterPath = String(p);
	g_SysDataPath = g_appEnterPath + String("/../../Simulator/data-res/");
	g_AppDataPath = g_appEnterPath + String("/../../Simulator/");
	g_BuildInDataPath = g_appEnterPath + String("/../../Simulator/sdcard/");
#else
	g_SysDataPath = ParamConfig::SysDataPath;
	g_AppDataPath = ParamConfig::AppDataPath;
	g_BuildInDataPath = ParamConfig::BuildInPath;
#endif
#ifdef WIN32
	g_DownloadPath = g_BuildInDataPath + String("DOWNLOAD/");
#else
	g_DownloadPath = "/mnt/sda1/Karaoke/SONG/";
#endif
	M3D_DebugPrint("initView --> g_appEnterPath[%s] \n",g_appEnterPath.c_str());
	M3D_DebugPrint("initView --> g_SysDataPath[%s] \n",g_SysDataPath.c_str());
	M3D_DebugPrint("initView --> g_AppDataPath[%s] \n",g_AppDataPath.c_str());
	M3D_DebugPrint("initView --> g_BuildInDataPath[%s] \n",g_BuildInDataPath.c_str());
	M3D_DebugPrint("initView --> g_DownloadPath[%s] \n",g_DownloadPath.c_str());

	//M3D_DebugPrint("initView --> new AppUI SoftwareVession[%s] \n",ParamConfig::SoftwareVession.c_str());

	new MKConfig(NULL);
	std::string confPath = g_AppDataPath + String("RES/config.xml"); //_pAppPathManager->getResDirFilePath(AppDataPath, APP_CONFIG_FILE);
	M3D_DebugPrint("initView --> config file path[%s] \n",confPath.c_str());
	MKConfig::getSingletonPtr()->load(confPath.c_str());

	//UI font file
	/*
#ifdef PLATFORM_UNIX
	CEGUI::ParamConfig::UIFontName = "arialuni";   //ARIALUNI.TTF
#endif
	*/
	GetFontManager(_FontManager);
	if(_FontManager != nullptr)
	{
		pvr::Log(pvr::Log.Information, "FontManager Get Succeed\n");
		//String fontpath = _pAppPathManager->getRootPath(SysDataPath)+"ARIALUNI.TTF";
		//MKConfig* config = (MKConfig*)MKConfig::getSingletonPtr();
		String fontname = String("ARIALUNI.TTF"); //config->getStringValue(ConfigParam::appOption_FontFiles);
#ifdef _WIN32
		g_fontFilePath = g_AppDataPath + "fonts/"+fontname; 
#else
		g_fontFilePath = FONTS_DIR_PATH+fontname;
#endif
		//String fontpath = _pAppPathManager->getRootPath(SysDataPath)+fontname;
		M3D_DebugPrint("initView--> fontpath[%s] \n",g_fontFilePath.c_str());
		/*
#ifdef PLATFORM_UNIX		
		if (krk_fexist(g_fontFilePath.c_str()))
			_FontManager->AddFont(CEGUI::ParamConfig::UIFontName, g_fontFilePath);
#endif*/
	}

	//load edb

	Director *director = Director::getInstance();
	if(director != nullptr)
	{
		pvr::Log(pvr::Log.Information, "Director Init Succeed\n");
		director->init(w, h, DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT, "font");
		director->setAnimationInterval(1.0f / 30);
		scene = SceneMain::create();
		director->runWithScene(scene);

#ifdef _WIN32

#else
		scene->addChild(VideoManager::GetInstance());
#endif
	}

	start_app();
#ifdef FUNC_OFN_ON
	MultakOFNSwitch(1);
#endif
	return true;
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Code in releaseView() will be called by pvr::Shell when the application quits or before a change in the rendering context.
***********************************************************************************************************************/
bool ApplicationMK::ReleaseView()
{
#ifdef FUNC_OFN_ON
	MultakOFNSwitch(0);
#endif
	stop_app();

	VideoManager::destroyInstance();

	Director *director = Director::getInstance();
	if(director != nullptr)
	{
		director->end();
        director->mainLoop();
		director = nullptr;

		pvr::Log(pvr::Log.Information, "Director DeInit Succeed\n");
	}

	FileUtils::destroyInstance();
	return true;
}

/*!*********************************************************************************************************************
\return	Return Result::Success if no error occurred
\brief	Main rendering loop function of the program. The shell will call this function every frame.
***********************************************************************************************************************/
bool ApplicationMK::RenderScene()
{
	if(appUI->getExitFlag()== true)
		return false;

	Director *director = Director::getInstance();

	float DeltaTimeSecs = director->getDeltaTime();
	//M3D_DebugPrint("Render %f\n", DeltaTimeSecs);

	float timeElapsed = DeltaTimeSecs * 1000;

#ifdef _WIN32
	VideoManager::GetInstance()->update(timeElapsed);
#endif
	RenderIn[0]++;

	RenderIn[1]++;
	if(appUI != NULL){
		appUI->renderUI(timeElapsed);
	}
	RenderOut[1]++;

	RenderIn[2]++;
	director->mainLoop();
	RenderOut[2]++;

	if(appUI != NULL && appUI->getExitFlag()== true)
	{
		_pMultakSettings = (MultakSettings*)MultakSettings::GetSingleInstance();
		_pMultakSettings->ResetActivity();
		return false;
	}

	RenderOut[0]++;
	return true;
}

bool ApplicationMK::queueKeyEvent(int key, int state)
{
	if (appUI == NULL)
		return false;

	if (appUI->getExitFlag() == true)
		return false;

	M3D_Event_t pushEvent;
	if(state == 0)
	{

	}
	else if(state == 1)
	{
		pushEvent.type = M3D_EVENT_KEYBOARD;
		pushEvent.para.kb.keycode = key;
		M3D_DebugPrint("=====queueKeyEvent========key[%d]=====\n",key);
		appUI->pushEvent(pushEvent);
		appUI->checkAnyKeyDown();
	}
	else if(state == 255)
	{
		//appUI->exit();
	}

	return true;
}


bool ApplicationMK::queueMotionEvent(int action, float x, float y, float pressure)
{
	if (appUI == NULL)
		return false;

	if (appUI->getExitFlag() == true)
		return false;

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

		appUI->pushEvent(pushEvent);

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

		appUI->pushEvent(pushEvent);

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
		pushEvent.type = M3D_EVENT_KEYBOARD;
		pushEvent.para.kb.keycode = M3D_UI_KEY_RETURN;
	}
	else if(action == 517)//
	{


	}
	return true;
}

int kkInput_EventCallback_New(int dt, int dx, int dy, unsigned char event, unsigned char index)
{
	M3D_Event_t uiEvent;

	//M3D_DebugPrint("kkInput_EventCallback %d, %d, %d\n", dx, dy, event);

	uiEvent.type = M3D_EVENT_OFN;
	uiEvent.para.ofn.dt = dt;
	uiEvent.para.ofn.dx = dx;
	uiEvent.para.ofn.dy = dy;
	uiEvent.para.ofn.index = index;

//	uiEvent.para.ofn.event = M3D_OFNEVENT_NONE;
// 	if (event & KKINPUT_EVENT_MOVE)
// 		uiEvent.para.ofn.event |= M3D_OFNEVENT_MOVE;
// 	if (event & KKINPUT_EVENT_TOUCHON)
// 		uiEvent.para.ofn.event |= M3D_OFNEVENT_TOUCHON;
// 	if (event & KKINPUT_EVENT_TOUCHOFF)
// 		uiEvent.para.ofn.event |= M3D_OFNEVENT_TOUCHOFF;
// 	if (event & KKINPUT_EVENT_KEYDOWN)
// 		uiEvent.para.ofn.event |= M3D_OFNEVENT_KEYDOWN;
// 	if (event & KKINPUT_EVENT_KEYUP)
// 		uiEvent.para.ofn.event |= M3D_OFNEVENT_KEYUP;

	uiEvent.para.ofn.event = event;

	//GameHall *pgShell = (GameHall *)GameHallShell;

	if (appUI != NULL && uiEvent.para.ofn.event != M3D_OFNEVENT_NONE)
		appUI->pushEvent(uiEvent);

	return 1;
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
