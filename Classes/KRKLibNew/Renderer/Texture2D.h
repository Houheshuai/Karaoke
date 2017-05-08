#pragma once
#include <string>
#include <map>
#include "Base/Ref.h"
#include "Renderer/OpenGLESHeaders.h"
#include "Renderer/GLProgram.h"
#include "Math/Geometry.h"


typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
    _MipmapInfo():address(nullptr),len(0){}
}MipmapInfo;

class Image;
class Texture2D : public Ref
{
public:
	enum PixelFormat
    {
        //! auto detect the type
        AUTO,
        //! 32-bit texture: BGRA8888
        BGRA8888,
        //! 32-bit texture: RGBA8888
        RGBA8888,
        //! 24-bit texture: RGBA888
        RGB888,
        //! 16-bit texture without Alpha channel
        RGB565,
        //! 8-bit textures used as masks
        A8,
        //! 8-bit intensity texture
        I8,
        //! 16-bit textures used as masks
        AI88,
        //! 16-bit textures: RGBA4444
        RGBA4444,
        //! 16-bit textures: RGB5A1
        RGB5A1,
        //! 4-bit PVRTC-compressed texture: PVRTC4
        PVRTC4,
        //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        PVRTC4A,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PVRTC2,
        //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        PVRTC2A,
        //! ETC-compressed texture: ETC
        ETC,
        //! S3TC-compressed texture: S3TC_Dxt1
        S3TC_DXT1,
        //! S3TC-compressed texture: S3TC_Dxt3
        S3TC_DXT3,
        //! S3TC-compressed texture: S3TC_Dxt5
        S3TC_DXT5,
        //! ATITC-compressed texture: ATC_RGB
        ATC_RGB,
        //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        ATC_EXPLICIT_ALPHA,
        //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
        ATC_INTERPOLATED_ALPHA,
        //! Default texture format: AUTO
        DEFAULT = AUTO,
		
        NONE = -1
    };

	struct PixelFormatInfo {

        PixelFormatInfo(GLenum anInternalFormat, GLenum aFormat, GLenum aType, int aBpp, bool aCompressed, bool anAlpha)
            : internalFormat(anInternalFormat)
            , format(aFormat)
            , type(aType)
            , bpp(aBpp)
            , compressed(aCompressed)
            , alpha(anAlpha)
        {}

        GLenum internalFormat;
        GLenum format;
        GLenum type;
        int bpp;
        bool compressed;
        bool alpha;
    };

	typedef struct _TexParams {
        GLuint    minFilter;
        GLuint    magFilter;
        GLuint    wrapS;
        GLuint    wrapT;
    }TexParams;
    
    typedef std::map<Texture2D::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;

	Texture2D();
	~Texture2D();

	void SetLog(int _logFlag);

	int			LogFlag;
	//std::string MyClassName;
	static	int ReferenceTimes;

	//内部格式和OpenGL ES的对应关系
    static const PixelFormatInfoMap& getPixelFormatInfoMap();
	static const PixelFormatInfoMap _pixelFormatInfoTables;

	//释放TextureID
	void releaseGLTexture();			

	//利用数据Buffer初始化
	bool initWithImageFileName(std::string fileName);
	bool initWithImageClass(Image *img);
	bool initWithData(const void *data, long dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
	bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
	//更新内容
	bool updateWithData(const void *data,int offsetX,int offsetY,int width,int height);

    void setGLProgram(GLProgram* program);

	void setTexParameters(const TexParams& texParams);

	bool hasPremultipliedAlpha();
	//测试代码
	void drawAtPoint(const Vec2& point);
    void drawInRect(const Rect& rect);
	GLuint getName() const;

	/** Get the texture content size.*/
    Size getContentSize() const;
	const Size& getContentSizeInPixels();
	PixelFormat getPixelFormat() const;
	int getPixelsWide() const;
	int getPixelsHigh() const;

private:

	Size _contentSize;
	enum Texture2D::PixelFormat _pixelFormat;
    int _pixelsWide;
    int _pixelsHigh;
	GLfloat _maxS;
	GLfloat _maxT;

	GLuint _name;
	GLProgram* _shaderProgram;

	bool _antialiasEnabled;
	
	//九宫格图片存储
	bool _hasPremultipliedAlpha;
	
};
