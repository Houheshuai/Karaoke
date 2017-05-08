#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Base/Ref.h"
#include "Renderer/Texture2D.h"

// premultiply alpha, or the effect will wrong when want to use other pixel format in Texture2D,
// such as RGB888, RGB5A1
#define RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))


class Image : public Ref
{
public:
    friend class TextureCache;
    /**
     * @js ctor
     */
    Image();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Image();

    /**
    @brief Load the image from the specified path.
    @param path   the absolute file path.
    @return true if loaded correctly.
    */
    bool initWithImageFile(const std::string& path);
	bool initWithImageData(const unsigned char * data, long dataLen);
	bool initWithRawData(const unsigned char * data, unsigned long dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    // Getters
    inline unsigned char *   getData()               { return _data; }
    inline unsigned long     getDataLen()            { return _dataLen; }
    inline Texture2D::PixelFormat getRenderFormat()  { return _renderFormat; }
    inline int               getWidth()              { return _width; }
    inline int               getHeight()             { return _height; }
    inline bool              hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
    inline std::string		 getFilePath() const { return _filePath; }

    //int                      getBitPerPixel();
    //bool                     hasAlpha();
    //bool                     isCompressed();

    /**
     @brief    Save Image data to the specified file, with specified format.
     @param    filePath        the file's absolute path, including file suffix.
     @param    isToRGB        whether the image is saved as RGB format.
     */
    bool saveToFile(const std::string &filename, bool isToRGB = true);
    
    void premultipliedAlpha();
    
protected:
    unsigned char *_data;
    unsigned long _dataLen;
    int _width;
    int _height;
    bool _unpack;
    Texture2D::PixelFormat _renderFormat;
    bool _hasPremultipliedAlpha;
    std::string _filePath;

protected:
    // noncopyable
    Image(const Image&    rImg);
    Image & operator=(const Image&);
    
};

#endif    // __IMAGE_H__
