#ifndef __SPRITE_SPRITE_FRAME_H__
#define __SPRITE_SPRITE_FRAME_H__

#include "Renderer/Node.h"
#include "Renderer/PolygonInfo.h"
#include "Base/Ref.h"
#include "Math/Geometry.h"

class Texture2D;

/** @class SpriteFrame
 * @brief A SpriteFrame has:
    - texture: A Texture2D that will be used by the Sprite
    - rectangle: A rectangle of the texture


 You can modify the frame of a Sprite by doing:
 
    SpriteFrame *frame = SpriteFrame::frameWithTexture(texture, rect, offset);
    sprite->setDisplayFrame(frame);
 */
class SpriteFrame : public Ref, public Clonable
{
public:

    /** Create a SpriteFrame with a texture filename, rect in points.
     It is assumed that the frame was not trimmed.
     *
     * @param filename Texture file name.
     * @param rect A specified rect.
     * @return An autoreleased SpriteFrame object.
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect);
    
    /** Create a SpriteFrame with a texture filename, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     *
     * @param filename Texture filename
     * @param rect A specified rect.
     * @param rotated Is rotated if true.
     * @param offset A specified offset.
     * @param originalSize A specified original size.
     * @return An autoreleased SpriteFrame object.
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** Create a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     * @param pobTexture The texture pointer.
     * @param rect A specified rect.
     * @return An autoreleased SpriteFrame object.
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** Create a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     * @param pobTexture The texture pointer.
     * @param rect A specified rect.
     * @param rotated Is rotated if true.
     * @param offset A specified offset.
     * @param originalSize A specified original size.
     * @return An autoreleased SpriteFrame object.
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

    // attributes
    /** Get rect of the sprite frame.
     *
     * @return The rect of the sprite frame, in pixels.
     */
    inline const Rect& getRectInPixels() const { return _rectInPixels; }
    /** Set rect of the sprite frame.
     *
     * @param rectInPixels The rect of the sprite frame, in pixels.
     */
    void setRectInPixels(const Rect& rectInPixels);

    /**Is the sprite frame rotated or not.
     *
     * @return Is rotated if true.
     */
    inline bool isRotated() const { return _rotated; }
    /** Set rotated of the sprite frame.
     *
     * @param rotated Rotated the sprite frame if true.
     */
    inline void setRotated(bool rotated) { _rotated = rotated; }

    /** Get rect of the frame.
     *
     * @return The rect of the sprite frame.
     */
    inline const Rect& getRect() const { return _rect; }
    /** Set rect of the frame.
     *
     * @param rect The rect of the sprite.
     */
    void setRect(const Rect& rect);

    /** Get offset of the frame.
     * 
     * @return The offset of the sprite frame, in pixels.
     */
    const Vec2& getOffsetInPixels() const;
    /** Set offset of the frame.
     * 
     * @param offsetInPixels The offset of the sprite frame, in pixels.
     */
    void setOffsetInPixels(const Vec2& offsetInPixels);

    /** Get original size of the trimmed image.
     *
     * @return The original size of the trimmed image, in pixels.
     */
    inline const Size& getOriginalSizeInPixels() const { return _originalSizeInPixels; }
    /** Set original size of the trimmed image.
     *
     * @param sizeInPixels The original size of the trimmed image, in pixels.
     */
    inline void setOriginalSizeInPixels(const Size& sizeInPixels) { _originalSizeInPixels = sizeInPixels; }

    /** Get original size of the trimmed image.
     *
     * @return The original size of the trimmed image.
     */
    inline const Size& getOriginalSize() const { return _originalSize; }
    /** Set original size of the trimmed image.
     *
     * @param sizeInPixels The original size of the trimmed image.
     */
    inline void setOriginalSize(const Size& sizeInPixels) { _originalSize = sizeInPixels; }

    /** Get texture of the frame.
     *
     * @return The texture of the sprite frame.
     */
    Texture2D* getTexture();
    /** Set texture of the frame, the texture is retained.
     *
     * @param pobTexture The texture of the sprite frame.
     */
    void setTexture(Texture2D* pobTexture);

    /** Get offset of the frame.
     *
     * @return The offset of the sprite frame.
     */
    const Vec2& getOffset() const;
    /** Set offset of the frame.
     *
     * @param offsets The offset of the sprite frame.
     */
    void setOffset(const Vec2& offsets);

    // Overrides
	virtual SpriteFrame *clone() const override;

    /** Set the polygon info for polygon mesh sprites
     *
     * @param polygonInfo triangle mesh of the sprite
     */
    void setPolygonInfo(const PolygonInfo &polygonInfo);

    /** Get the polygonInfo for this sprite
     *
     * @return polygonInfo structure
     */
    const PolygonInfo &getPolygonInfo() const;

    /** Check if sprite frame is a polygon sprite
     *
     * @return true if polygonInfo is available
     */
    bool hasPolygonInfo() const;

public:
    /**
     * @lua NA
     */
    SpriteFrame();
    
    /**
     * @lua NA
     */
    virtual ~SpriteFrame();
    
    /** Initializes a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect);
    
    /** Initializes a SpriteFrame with a texture filename, rect in points;
     It is assumed that the frame was not trimmed.
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect);
    
    /** Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     
     @since v1.1
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

protected:
    Vec2 _offset;
    Size _originalSize;
    Rect _rectInPixels;
    bool   _rotated;
    Rect _rect;
    Vec2 _offsetInPixels;
    Size _originalSizeInPixels;
    Texture2D *_texture;
    std::string  _textureFilename;
    PolygonInfo _polygonInfo;
};

#endif //__SPRITE_SPRITE_FRAME_H__
