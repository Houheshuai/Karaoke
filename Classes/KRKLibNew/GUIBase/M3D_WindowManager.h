//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_WindowManager.h
//																	
// Description: forms/widgets register&create&destroy
// 
//----------------------------------------------------------------------------//
// History:
//
// v1.00 : first release
//
//----------------------------------------------------------------------------//
//

#ifndef _M3D_WINDOWMANAGER_
#define _M3D_WINDOWMANAGER_

#include <map>
#include <vector>
#include "Resource/Readres.h"
#include "GUIBase/M3D_Singleton.h"
#include "CEGUI/CEGUIWindowFactoryManager.h"
#include "CEGUI/CEGUITplWindowFactory.h"

namespace CEGUI
{
class M3D_App;
class Window_2D;

class M3D_WindowManager : public M3D_Singleton<M3D_WindowManager>
{
public:
	Window_2D* createForm(const uint id, M3D_App *app);
	bool destroyForm(Window_2D *window);

	WndRes_t* createWidgets(WndRes_t* parWndRes, Window_2D* parent);
	bool destroyWidgets(Window_2D* parent);
	uint getWidgetTypeID(const String &WidgetName);
	String getWidgetTypeName(int TypeId);
	
	void registerWidgets(void);
	void unregisterWidgets(void);

	bool cleanupForms(void);

	/*!
	\brief
		register a widget to window factory by class ID

	\param TypeId
		widget class ID, must be unique to the class ID in resource file
	*/
	template <typename T>
	void registerWidget(int TypeId);

	Window_2D*	createRootWindow(const String& Name);
	void		destroyRootWindow();

	Window_2D*	getRootWindow(void)  const {return d_root;}

	M3D_App*	getCurApp(void)  const {return d_app;}
	void		setCurApp(M3D_App* app) {d_app = app;}
	
	M3D_WindowManager(void);
	~M3D_WindowManager(void);

private:
	
	typedef std::map<String, int>	WidgetNameTypeMapRegistry;
	typedef std::map<int, String>	WidgetTypeNameMapRegistry;

	//! WidgetName to WidgetType map
	WidgetNameTypeMapRegistry	d_WidgetNameTypeMap;
	//! WidgetType to WidgetName map
	WidgetTypeNameMapRegistry	d_WidgetTypeNameMap;

	//! root window
	Window_2D*		d_root;
	//! last created form
	M3D_App*		d_app;


};


//--------------------------------------------------------------------------------
template <typename T>
void M3D_WindowManager::registerWidget(int TypeId)
{
	WindowFactoryManager::addFactory< TplWindowFactory<T> >();

	//M3D_DebugPrint("M3D_WindowManager::registerWidget %x,  %d", & d_WidgetNameTypeMap, TypeId);
	//M3D_DebugPrint("M3D_WindowManager::registerWidget_err %x", this);

	if(&d_WidgetNameTypeMap != NULL)
	{
		// throw exception if type name for factory is already in use
		if (d_WidgetNameTypeMap.find(T::WidgetTypeName) != d_WidgetNameTypeMap.end())   //  启动退出问题
		{
			//throw AlreadyExistsException("M3D_WindowManager::addFactory - A WindowFactory for type '" + T::WidgetTypeName + "' is already registered.");
			//pvr::Log(pvr::Log.Debug, "M3D_WindowManager::addFactory - A WindowFactory for type 1 is already registered.");
		}

		// add the factory to the registry
		d_WidgetNameTypeMap[T::WidgetTypeName] = TypeId;
	
		// throw exception if type name for factory is already in use
		if (d_WidgetTypeNameMap.find(TypeId) != d_WidgetTypeNameMap.end())
		{
			//throw AlreadyExistsException("M3D_WindowManager::addFactory - A WindowFactory for type '" + T::WidgetTypeName + "' is already registered.");
			//pvr::Log(pvr::Log.Debug, "M3D_WindowManager::addFactory - A WindowFactory for type 2 is already registered.");
		}

		// add the factory to the registry
		d_WidgetTypeNameMap[TypeId] = T::WidgetTypeName;
	}
}


}




#endif

