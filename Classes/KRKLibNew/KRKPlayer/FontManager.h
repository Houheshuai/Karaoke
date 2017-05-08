#pragma once
#include <string>
#include <unordered_map>
#include "InterfaceFontManager.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

extern "C"
{
#include <hb-ft.h>
}

//管理所有的ttf文件
class FontManager:public InterfaceFontManager
{ 
public: 
    static FontManager *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static FontManager instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    } 

    void count_increase () {count_ ++;}
    int count () const {return count_;}

	int AddFont(std::string _fontName, std::string _fontPath);
	int GetLibraryFace(std::string _fontName, FT_Library *_nowLibrary, FT_Face *_nowFace, hb_font_t **_now_hb_font);
	void Clear();
	void RemoveLibraryFace(std::string fontName,  FT_Library *_nowLibrary, FT_Face *_nowFace, hb_font_t **_now_hb_font);

private: 
    FontManager ();
    ~FontManager ();

    static FontManager *p_instance_; 
    int count_;

	//Font memory指针和名称对应
	std::unordered_map<std::string, char *>	FontMemoryMap;
	std::unordered_map<std::string, long>		FontMemoryLenMap;

	std::unordered_map<std::string, std::unordered_map<unsigned long, FT_Library> *>	Font_FT_Library_Map_All;
	std::unordered_map<std::string, std::unordered_map<unsigned long, FT_Face> *>		Font_FT_Face_Map_All;
	std::unordered_map<std::string, std::unordered_map<unsigned long, hb_font_t *> *>		Font_HB_FONT_Map_All;
}; 


