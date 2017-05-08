//----------------------------------------------------------------------------//
// Multak 3D GUI Project						
//
// Filename : M3D_Label.h
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
#ifndef _M3D_Label_H
#define _M3D_Label_H

#include "Window_2D.h"
#include <lib/ime/df_ime.h>

namespace CEGUI
{

class M3D_Label:public Window_2D
{
public:
	M3D_Label(const String& type, const String& name);
	virtual ~M3D_Label(void);

	static const String EventNamespace; 			//!< Namespace for global events
	static const String WidgetTypeName; 			//!< Window factory name

	virtual void constructWindow(WndRes_t *wndRes, Window_2D *parent = NULL);
	virtual void destructWindow();

	virtual void onCreated(void);
	virtual void onDestroyed(void);

	virtual void onActivated(ActivationEventArgs& e);
	virtual void onDeactivated(ActivationEventArgs& e);

	virtual void updateSelf(float elapsed);

	virtual void onCharacter(KeyEventArgs& e);
	virtual void onMouseClicked(MouseEventArgs& e);
	virtual bool isHit(const Vector2& position, const bool allow_disabled = false) const;

	void	setImage(std::string imgFilePath);
	void	setImage(uint resID);
	void	setAlpha(float alpha);

	void	setIMEStatus(bool enable, ime_keymap_t *keyMap, std::function<void(CEGUI::String)> _onIMEInputEnd = nullptr, ime_language_em language = IME_LANGUAGE_EN, int maxInput = 6);
	void	setIMELanguage(ime_language_em language = IME_LANGUAGE_EN, int maxInput = 6);
	void    inputKey(int keyValue);
	ime_t	*getIME(){return p_ime;};
	void    inputEnd(CEGUI::String inputString);

private:
	std::function<void(CEGUI::String)> onIMEInputEnd;

	bool			d_imeStaus;
	ime_t			*p_ime;
	ime_keymap_t	*d_keyMap;
};

}

#endif
