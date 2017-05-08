//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Form.h
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

#ifndef _M3D_FORM_H
#define _M3D_FORM_H

#include "Widgets/Window_2D.h"
#include "Widgets/M3D_Widgets.h"

namespace CEGUI
{
class M3D_App;

class M3D_Form:public Window_2D
{
public:
	M3D_Form(const String& type, const String& name);
	virtual ~M3D_Form(void);

	void setDefaultWidget(Window_2D* widget){d_defaultWidget = widget;}
	Window_2D* getDefaultWidget(void){return d_defaultWidget;}

	void setApp(M3D_App* app) {d_app = app;}
	M3D_App* getApp(void) {return d_app;}

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void onShown(WindowEventArgs& e);
    virtual void onHidden(WindowEventArgs& e);

	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow();

	virtual void onActionStart(void);
	virtual void onActionEnd(void);

	virtual void updateSelf(float elapsed);

	virtual void setLog(void);

	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);

	virtual void anyKeyDown(void);

	virtual void setLocalZorder(float _order);

	bool  isActionEnd(){return d_actionEnd;};

private:
	//! application handle
	M3D_App* 		d_app;
	//! default active widget
	Window_2D*		d_defaultWidget;
	bool			d_actionEnd;

};

}

#endif
