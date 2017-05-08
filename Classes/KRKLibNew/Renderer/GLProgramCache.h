#pragma once
#include <string>
#include <unordered_map>
#include "Renderer/OpenGLESHeaders.h"
#include "Renderer/GLProgram.h"

#define SHADER_PROGRAM_LYRIC										0
#define SHADER_PROGRAM_UI											1
#define SHADER_PROGRAM_YUV											2
#define SHADER_PROGRAM_POSITION_TEXTURE								3
#define SHADER_PROGRAM_FONT_ONECOLOR								4
#define SHADER_PROGRAM_CHROMA										5
#define SHADER_PROGRAM_POSITION_LENGTH_TEXTURE_COLOR				6
#define SHADER_PROGRAM_POINT_COLOR									7
#define SHADER_PROGRAM_U_COLOR										8
#define SHADER_PROGRAM_UI_BGRA										9
#define SHADER_PROGRAM_POSITION_TEXTURE_COLOR						10

//单独一个实例的类
class GLProgramCache
{ 
public: 
    static GLProgramCache *GetSingleInstance() 
    { 
        if (p_instance_ == nullptr) { 
            static GLProgramCache instance; 
            p_instance_ = &instance; 
        }
        return p_instance_; 
    } 

    void count_increase () {count_ ++;} 
    int count () const {return count_;} 

	GLProgram* getGLProgram(int ProgramIndex);
	void loadDefaultProgram();

	void clearDefaultProgram();

private: 
    GLProgramCache ();
    ~GLProgramCache ();

    static GLProgramCache *p_instance_; 
    int count_; 

	std::unordered_map<int, GLProgram *> _programs;

}; 
