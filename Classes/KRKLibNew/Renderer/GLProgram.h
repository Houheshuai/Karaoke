#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H
#include <unordered_map>
#include <string>

#include "Base/Macros.h"
#include "Math/Math.h"
#include "OpenGLESHeaders.h"

/**VertexAttrib is a structure to encapsulate data got from glGetActiveAttrib.*/
typedef struct _VertexAttrib
{
    /**Index of attribute, start from 0.*/
    GLuint index;
    /**Number of Data type in the attribute, could range from 0-4.*/
    GLint size;
    /**Data type of the attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.*/
    GLenum type;
    /**The string name in vertex shader.*/
    std::string name;
} VertexAttrib;
/**Uniform is a structure to encapsulate data got from glGetActiveUniform and glGetUniformLocation.*/
typedef struct _Uniform
{
    /**The place where the uniform placed, starts from 0.*/
    GLint location;
    /**Number of data type in attribute.*/
    GLint size;
    /**Data type of the attribute.*/
    GLenum type;
    /**String of the uniform name.*/
    std::string name;
} Uniform;

class GLProgram 
{
public:
	GLProgram(std::string _className);
	~GLProgram();


	/**Enum the preallocated vertex attribute. */
    enum
    {
        /**Index 0 will be used as Position.*/
        VERTEX_ATTRIB_POSITION,
        /**Index 1 will be used as Color.*/
        VERTEX_ATTRIB_COLOR,
        /**Index 2 will be used as Tex coord unit 0.*/
        VERTEX_ATTRIB_TEX_COORD,
        /**Index 3 will be used as Tex coord unit 1.*/
        VERTEX_ATTRIB_TEX_COORD1,
        /**Index 4 will be used as Tex coord unit 2.*/
        VERTEX_ATTRIB_TEX_COORD2,
        /**Index 5 will be used as Tex coord unit 3.*/
        VERTEX_ATTRIB_TEX_COORD3,
        /**Index 6 will be used as Normal.*/
        VERTEX_ATTRIB_NORMAL,
        /**Index 7 will be used as Blend weight for hardware skin.*/
        VERTEX_ATTRIB_BLEND_WEIGHT,
        /**Index 8 will be used as Blend index.*/
        VERTEX_ATTRIB_BLEND_INDEX,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };

    /**Preallocated uniform handle.*/
    enum
    {
        /**Ambient color.*/
        UNIFORM_AMBIENT_COLOR,
        /**Projection matrix.*/
        UNIFORM_P_MATRIX,
        /**Model view matrix.*/
        UNIFORM_MV_MATRIX,
        /**Model view projection matrix.*/
        UNIFORM_MVP_MATRIX,
        /**Normal matrix.*/
        UNIFORM_NORMAL_MATRIX,
        /**Time.*/
        UNIFORM_TIME,
        /**sin(Time).*/
        UNIFORM_SIN_TIME,
        /**cos(Time).*/
        UNIFORM_COS_TIME,
        /**Random number.*/
        UNIFORM_RANDOM01,
        /** @{
        * Sampler 0-3, used for texture.
        */
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,

		UNIFORM_ALPHA,
		/*
		UNIFORM_COLOR1,
		UNIFORM_COLOR2,
		UNIFORM_COLOR3,
		UNIFORM_COLOR4,
		UNIFORM_PERCENT,*/
        /**@}*/
        UNIFORM_MAX,
    };


	/**Ambient Color uniform.*/
    static const char* UNIFORM_NAME_AMBIENT_COLOR;
    /**Projection Matrix uniform.*/
    static const char* UNIFORM_NAME_P_MATRIX;
    /**Model view matrix uniform.*/
    static const char* UNIFORM_NAME_MV_MATRIX;
    /**Model view projection uniform.*/
    static const char* UNIFORM_NAME_MVP_MATRIX;
    /**Normal matrix uniform.*/
    static const char* UNIFORM_NAME_NORMAL_MATRIX;
    /**Time uniform.*/
    static const char* UNIFORM_NAME_TIME;
    /**Sin time uniform.*/
    static const char* UNIFORM_NAME_SIN_TIME;
    /**Cos time uniform.*/
    static const char* UNIFORM_NAME_COS_TIME;
    /**Random number uniform.*/
    static const char* UNIFORM_NAME_RANDOM01;
    /**
    @{ Sampler uniform 0-3, used for textures.
    */
    static const char* UNIFORM_NAME_SAMPLER0;
    static const char* UNIFORM_NAME_SAMPLER1;
	static const char* UNIFORM_NAME_SAMPLER2;
    static const char* UNIFORM_NAME_SAMPLER3;
	//Lyric
	//static const char* UNIFORM_NAME_ALPHA;
	/*
	static const char* UNIFORM_NAME_COLOR1;
	static const char* UNIFORM_NAME_COLOR2;
	static const char* UNIFORM_NAME_COLOR3;
	static const char* UNIFORM_NAME_COLOR4;
	static const char* UNIFORM_NAME_PERCENT;
	*/
	/**Attribute color.*/
    static const char* ATTRIBUTE_NAME_COLOR;
    /**Attribute position.*/
    static const char* ATTRIBUTE_NAME_POSITION;
    /**@{ Attribute Texcoord 0-3.*/
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    static const char* ATTRIBUTE_NAME_TEX_COORD1;
    static const char* ATTRIBUTE_NAME_TEX_COORD2;
    static const char* ATTRIBUTE_NAME_TEX_COORD3;
    /**@}*/
    /**Attribute normal.*/
    static const char* ATTRIBUTE_NAME_NORMAL;
    /**Attribute blend weight.*/
    static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
    /**Attribute blend index.*/
    static const char* ATTRIBUTE_NAME_BLEND_INDEX;

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;

	//外部的Shader初始化函数，暂时不需要定义

	//我们直接使用GLProgramCache缓存所有的

	void link();
	void use();
	void updateUniforms();

	bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
	bool compileShader(GLuint* shader, GLenum type, const GLchar* source);

	inline const GLuint getProgram() const { return _program; }

	/** Reload all shaders, this function is designed for android
    when opengl context lost, so don't call it.
    */
    void reset();

	struct flag_struct {
        unsigned int usesTime:1;
        unsigned int usesNormal:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
        unsigned int usesRandom:1;

		unsigned int usesAlpha:1;

		/*
		unsigned int usesColor1:1;
		unsigned int usesColor2:1;
		unsigned int usesColor3:1;
		unsigned int usesColor4:1;
		unsigned int usesPercent:1;*/
        // handy way to initialize the bitfield
        flag_struct() { memset(this, 0, sizeof(*this)); }
    } _flags;

	/**@{ Get the uniform or vertex attribute by string name in shader, return nullptr if it does not exist.*/
    Uniform* getUniform(const std::string& name);
    VertexAttrib* getVertexAttrib(const std::string& name);
    /**@}*/

	/**Bind the predefined vertex attributes to their specific slot.*/
    void bindPredefinedVertexAttribs();
    /**Parse user defined Vertex Attributes automatically.*/
    void parseVertexAttribs();
    /**Parse user defined uniform automatically.*/
    void parseUniforms();

    /**  It will add a new attribute to the shader by calling glBindAttribLocation. */
    void bindAttribLocation(const std::string& attributeName, GLuint index) const;

    /** Calls glGetAttribLocation. */
    GLint getAttribLocation(const std::string& attributeName) const;

    /** Calls glGetUniformLocation(). */
    GLint getUniformLocation(const std::string& attributeName) const;

 
	bool updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes);
	
	/**
     Update the builtin uniforms if they are different than the previous call for this same shader program.
     */
    void setUniformsForBuiltins();
	void setUniformsForBuiltins(const Mat4 &matrixMV);

    /** Calls glGetAttribLocation. */
    GLint getAttribLocation(const std::string& attributeName);

    /** Calls glGetUniformLocation(). */
    GLint getUniformLocation(const std::string& attributeName);


	 /** calls retrieves the named uniform location for this shader program. */
    GLint getUniformLocationForName(const char* name) const;

    /** calls glUniform1i only if the values are different than the previous call for this same shader program.
     * @js setUniformLocationI32
     * @lua setUniformLocationI32
     */
    void setUniformLocationWith1i(GLint location, GLint i1);

    /** calls glUniform2i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);

    /** calls glUniform3i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);

    /** calls glUniform4i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);

    /** calls glUniform2iv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** calls glUniform3iv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** calls glUniform4iv only if the values are different than the previous call for this same shader program. */

    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** calls glUniform1f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** calls glUniform2f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** calls glUniform3f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** calls glUniform4f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** calls glUniformfv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniformMatrix2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** calls glUniformMatrix3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);


	/**User defined Uniforms.*/
    std::unordered_map<std::string, Uniform> _userUniforms;
    /**User defined vertex attributes.*/
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;

private:

    GLuint            _program;
    GLuint            _vertShader;
    GLuint            _fragShader;

	GLint             _builtInUniforms[UNIFORM_MAX];

};

#endif

