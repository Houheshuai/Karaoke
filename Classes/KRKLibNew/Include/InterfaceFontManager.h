#ifndef _INTERFACE_FONT_H
#define _INTERFACE_FONT_H
#include <string>

class InterfaceFontManager
{
public:
	virtual ~InterfaceFontManager(){};
	virtual int AddFont(std::string _fontName, std::string _fontPath) = 0;
	virtual void Clear() = 0;

};

extern "C" void GetFontManager(InterfaceFontManager *&_fontManager);

#endif