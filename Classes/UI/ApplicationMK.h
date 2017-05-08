/*!*********************************************************************************************************************
\file         
\author       
\copyright    
\brief        
***********************************************************************************************************************/

#pragma once

#ifdef _WIN32
#include "PVRShell.h"
#else

#endif
#include "PVRCore/PVRCore.h"

#include "InterfaceFontManager.h"

#ifdef _WIN32
class ApplicationMK : public PVRShell
#else
class ApplicationMK
#endif
{
private:
	float 				StartX, StartY;
	float 				EndX, EndY;

public:
	ApplicationMK();
	virtual bool InitApplication();
	virtual bool QuitApplication();

#ifdef _WIN32
	virtual bool InitView();
#else
	virtual bool InitView(int w, int h);
#endif

	virtual bool ReleaseView();
	virtual bool RenderScene();
	virtual bool queueKeyEvent(int key, int state);
	virtual bool queueMotionEvent(int action, float x, float y, float pressure);

	//void AddCameraPic(std::string path);
	//void AddCameraBuff(unsigned char *_cambuff, int _size);

	static InterfaceFontManager* _FontManager;
	
};