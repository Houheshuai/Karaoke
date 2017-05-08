#pragma once
#include <string>

#include "Base/Types.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"

#include "Renderer/GLProgram.h"
#include "Renderer/Texture2D.h"

/**
 * Uniform Value, which is used to store to value send to openGL pipe line by glUniformXXX.
 *
 * @lua NA
 */
class UniformValue
{
    friend class GLProgram;
    friend class GLProgramState;
public:
    /**
     Constructor. The Uniform and Glprogram will be nullptr.
     */
    UniformValue();
    /**
     Constructor with uniform and glprogram.
     @param uniform Uniform to apply the value.
     @param glprogram Specify the owner GLProgram of this uniform and uniform value.
     */
    UniformValue(Uniform *uniform, GLProgram* glprogram);

    /**Destructor.*/
    ~UniformValue();
    /**@{
     Set data to Uniform value. Generally, there are many type of data could be supported,
     including float, int, Vec2/3/4, Mat4.
     @param value Value to be sent, support float, int, Vec2/3/4, Mat4.
     */
    void setFloat(float value);
    void setInt(int value);
    void setFloatv(long size, const float* pointer);
    void setVec2(const Vec2& value);
    void setVec2v(long size, const Vec2* pointer);
    void setVec3(const Vec3& value);
    void setVec3v(long size, const Vec3* pointer);
    void setVec4(const Vec4& value);
    void setVec4v(long size, const Vec4* pointer);
    void setMat4(const Mat4& value);

    /**
     Set call back to uniform value, which could be used for array and struct.
     @param callback Callback function to send data to OpenGL pipeline.
     */
    void setCallback(const std::function<void(GLProgram*, Uniform*)> &callback);
    
    /**
     Set texture to uniform value.
     @param textureId The texture handle.
     @param textureUnit The binding texture unit to be used in shader.
    */
    void setTexture(GLuint textureId, GLuint textureUnit);
    
    /**Apply the uniform value to openGL pipeline.*/
    void apply();

protected:

    enum Type {
        VALUE,
        POINTER,
        CALLBACK_FN     // CALLBACK is already defined in windows, can't use it.
    };

    /**Weak reference to Uniform.*/
	Uniform* _uniform;
    /**Weak reference to GLprogram.*/
    GLProgram* _glprogram;
    /** What kind of type is the Uniform */
    Type _type;

    /**
     @name Uniform Value Uniform
     @{
     */
    union U{
        float floatValue;
        int intValue;
        float v2Value[2];
        float v3Value[3];
        float v4Value[4];
        float matrixValue[16];
        struct {
            GLuint textureId;
            GLuint textureUnit;
        } tex;
        struct {
            const float* pointer;
            GLsizei size;
        } floatv;
        struct {
            const float* pointer;
            GLsizei size;
        } v2f;
        struct {
            const float* pointer;
            GLsizei size;
        } v3f;
        struct {
            const float* pointer;
            GLsizei size;
        } v4f;
        std::function<void(GLProgram*, Uniform*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
    /**
     @}
     */
};

/**
 * Vertex Attribute Value, which is an abstraction of VertexAttribute and data pointer.
 *
 * @lua NA
 */
class VertexAttribValue
{
    friend class GLProgram;
    friend class GLProgramState;
    //friend class VertexAttribBinding;

public:
    /**
     Constructor.
     @param vertexAttrib VertexAttrib from shader.
    */
    VertexAttribValue(VertexAttrib *vertexAttrib);
    /**
     Constructor.
     */
    VertexAttribValue();
    /**
     Destructor.
     */
    ~VertexAttribValue();
    
    /**
     Set the data pointer, which is similar as glVertexAttribPointer.
     @param size The number of type in the vertex attribute.
     @param type The type of data in vertex attribute.
     @param normalized If true, 0-255 data will be mapped to 0.0-1.0.
     @param stride The number of bytes if an interleaved vertex array is used. 0 means array is not interleaved.
     @param pointer The pointer to the vertex data.
     */
	void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**Set a user call back for set VertexAttrib array.*/
    void setCallback(const std::function<void(VertexAttrib*)> &callback);
    /**Apply the vertex attribute to the openGL pipeline.*/
    void apply();

protected:
	VertexAttrib* _vertexAttrib;  // weak ref
    bool _useCallback;
    bool _enabled;

    union U{
        struct {
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid *pointer;
        } pointer;
        std::function<void(VertexAttrib*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
};



class GLProgramState : public Ref
{
public:
	GLProgramState(std::string _className);
	~GLProgramState();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;

	static GLProgramState* create(GLProgram *glprogram);
	GLProgramState* clone() const;

	 /**
     Apply GLProgram, attributes and uniforms.
     @param modelView The applied modelView matrix to shader.
     */
    void apply(const Mat4& modelView);
    /**
     Apply GLProgram, and built in uniforms.
     @param modelView The applied modelView matrix to shader.
     */
    void applyGLProgram(const Mat4& modelView);
    /**
     Apply attributes.
     @param applyAttribFlags Call glenableVertexAttribs(_vertexAttribsFlags) or not.
     */
    void applyAttributes(bool applyAttribFlags = true);
    /**
     Apply user defined uniforms.
     */
    void applyUniforms();
    
    /**@{ 
     Setter and Getter of the owner GLProgram binded in this program state.
     */
    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() const { return _glprogram; }
    
    /**@}*/
    
    /** Get the flag of vertex attribs used by OR operation.*/
    unsigned int getVertexAttribsFlags() const;
    /**Get the number of vertex attributes.*/
    long getVertexAttribCount() const;
    /**@{
     Set the vertex attribute value.
     */
    void setVertexAttribCallback(const std::string& name, const std::function<void(VertexAttrib*)> &callback);
    void setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**@}*/
    
    /**Get the number of user defined uniform count.*/
    long getUniformCount() const { return _uniforms.size(); }
    
    /** @{
     Setting user defined uniforms by uniform string name in the shader.
     */
    void setUniformInt(const std::string& uniformName, int value);
    void setUniformFloat(const std::string& uniformName, float value);
    void setUniformFloatv(const std::string& uniformName, long size, const float* pointer);
    void setUniformVec2(const std::string& uniformName, const Vec2& value);
    void setUniformVec2v(const std::string& uniformName, long size, const Vec2* pointer);
    void setUniformVec3(const std::string& uniformName, const Vec3& value);
    void setUniformVec3v(const std::string& uniformName, long size, const Vec3* pointer);
    void setUniformVec4(const std::string& uniformName, const Vec4& value);
    void setUniformVec4v(const std::string& uniformName, long size, const Vec4* pointer);
    void setUniformMat4(const std::string& uniformName, const Mat4& value);
	void setUniformCallback(const std::string& uniformName, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(const std::string& uniformName, Texture2D *texture);
    void setUniformTexture(const std::string& uniformName, GLuint textureId);
    /**@}*/
    
    /** @{
     Setting user defined uniforms by uniform location in the shader.
     */
    void setUniformInt(GLint uniformLocation, int value);
    void setUniformFloat(GLint uniformLocation, float value);
    void setUniformFloatv(GLint uniformLocation, long size, const float* pointer);
    void setUniformVec2(GLint uniformLocation, const Vec2& value);
    void setUniformVec2v(GLint uniformLocation, long size, const Vec2* pointer);
    void setUniformVec3(GLint uniformLocation, const Vec3& value);
    void setUniformVec3v(GLint uniformLocation, long size, const Vec3* pointer);
    void setUniformVec4(GLint uniformLocation, const Vec4& value);
    void setUniformVec4v(GLint uniformLocation, long size, const Vec4* pointer);
    void setUniformMat4(GLint uniformLocation, const Mat4& value);
	void setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(GLint uniformLocation, Texture2D *texture);
    void setUniformTexture(GLint uniformLocation, GLuint textureId);
	
protected:
	bool init(GLProgram* program);
    void resetGLProgram();
    void updateUniformsAndAttributes();
    VertexAttribValue* getVertexAttribValue(const std::string& attributeName);
    UniformValue* getUniformValue(const std::string& uniformName);
    UniformValue* getUniformValue(GLint uniformLocation);


    bool _uniformAttributeValueDirty;
    std::unordered_map<std::string, GLint> _uniformsByName;
    std::unordered_map<GLint, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;
    std::unordered_map<std::string, int> _boundTextureUnits;

    int _textureUnitIndex;
    unsigned int _vertexAttribsFlags;
    GLProgram* _glprogram;

};

