#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include <string>
#include <queue>
#include <string>
#include <unordered_map>

#include "Base/Ref.h"
#include "Renderer/Texture2D.h"
#include "Platform/Image.h"

/*
* From version 3.0, TextureCache will never to treated as a singleton, it will be owned by director.
* All call by TextureCache::getInstance() should be replaced by Director::getInstance()->getTextureCache().
*/

/** @brief Singleton that handles the loading of textures.
* Once the texture is loaded, the next time it will return.
* A reference of the previously loaded texture reducing GPU & CPU memory.
*/
class TextureCache : public Ref
{
public:
    /**
     * @js ctor
     */
    TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

//    Dictionary* snapshotTextures();

    /** Returns a Texture2D object given an filename.
    * If the filename was not previously loaded, it will create a new Texture2D.
    * Object and it will return it. It will use the filename as a key.
    * Otherwise it will return a reference of a previously loaded image.
    * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr.
     @param filepath A null terminated string.
    */
    Texture2D* addImage(const std::string &filepath);

    /** Returns a Texture2D object given a file image.
    * If the file image was not previously loaded, it will create a new Texture2D object and it will return it.
    * Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with the Texture2D as a parameter.
    * The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
    * Supported image extensions: .png, .jpg
     @param filepath A null terminated string.
     @param callback A callback function would be invoked after the image is loaded.
     @since v0.8
    */
    //virtual void addImageAsync(const std::string &filepath, const std::function<void(Texture2D*)>& callback);
    
    /** Unbind a specified bound image asynchronous callback.
     * In the case an object who was bound to an image asynchronous callback was destroyed before the callback is invoked,
     * the object always need to unbind this callback manually.
     * @param filename It's the related/absolute path of the file image.
     * @since v3.1
     */
    //virtual void unbindImageAsync(const std::string &filename);
    
    /** Unbind all bound image asynchronous load callbacks.
     * @since v3.1
     */
    //virtual void unbindAllImageAsync();

    /** Returns a Texture2D object given an Image.
    * If the image was not previously loaded, it will create a new Texture2D object and it will return it.
    * Otherwise it will return a reference of a previously loaded image.
    * @param key The "key" parameter will be used as the "key" for the cache.
    * If "key" is nil, then a new texture will be created each time.
    */
    Texture2D* addImage(Image *image, const std::string &key);

    /** Returns an already created texture. Returns nil if the texture doesn't exist.
    @param key It's the related/absolute path of the file image.
    @since v0.99.5
    */
    Texture2D* getTextureForKey(const std::string& key) const;

    /** Reload texture from the image file.
    * If the file image hasn't loaded before, load it.
    * Otherwise the texture will be reloaded from the file image.
    * @param fileName It's the related/absolute path of the file image.
    * @return True if the reloading is succeed, otherwise return false.
    */
    bool reloadTexture(const std::string& fileName);

    /** Purges the dictionary of loaded textures.
    * Call this method if you receive the "Memory Warning".
    * In the short term: it will free some resources preventing your app from being killed.
    * In the medium term: it will allocate more resources.
    * In the long term: it will be the same.
    */
    void removeAllTextures();

    /** Removes unused textures.
    * Textures that have a retain count of 1 will be deleted.
    * It is convenient to call this method after when starting a new Scene.
    * @since v0.8
    */
    void removeUnusedTextures();

    /** Deletes a texture from the cache given a texture.
    */
    void removeTexture(Texture2D* texture);

    /** Deletes a texture from the cache given a its key name.
    @param key It's the related/absolute path of the file image.
    @since v0.99.4
    */
    void removeTextureForKey(const std::string &key);

    /** Output to CCLOG the current contents of this TextureCache.
    * This will attempt to calculate the size of each texture, and the total texture memory in use.
    *
    * @since v1.0
    */
    std::string getCachedTextureInfo() const;

    //Wait for texture cache to quit before destroy instance.
    /**Called by director, please do not called outside.*/
    void waitForQuit();

    /**
     * Get the file path of the texture
     *
     * @param texture A Texture2D object pointer.
     *
     * @return The full path of the file.
     */
    const std::string getTextureFilePath(Texture2D* texture)const;

    /** Reload texture from a new file.
    * This function is mainly for editor, won't suggest use it in game for performance reason.
    *
    * @param srcName Original texture file name.
    * @param dstName New texture file name.
    *
    * @since v3.10
    */
    void renameTextureWithKey(const std::string srcName, const std::string dstName);


private:
    //void addImageAsyncCallBack(float dt);
    void loadImage();
    //void parseNinePatchImage(Image* image, Texture2D* texture, const std::string& path);
public:
protected:
    bool _needQuit;
    std::unordered_map<std::string, Texture2D*> _textures;
};

#endif //__TEXTURE_CACHE_H__

