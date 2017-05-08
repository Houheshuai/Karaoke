#pragma once
#include <string>

class SpecialFunctionCharCache
{ 
public: 
    static SpecialFunctionCharCache *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static SpecialFunctionCharCache instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    } 

    void count_increase () {count_ ++;} 
    int count () const {return count_;} 

	int InitSpecialChar(std::string _fontName);
	int DeInitSpecialChar();
	void *GetTextureTips(int _index); //获取提唱的字符
	void *GetTransparentTexture();

private: 
    SpecialFunctionCharCache ();
    ~SpecialFunctionCharCache ();

    static SpecialFunctionCharCache *p_instance_; 
    int count_; 
}; 
