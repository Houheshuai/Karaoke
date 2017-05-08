#ifndef __TEXTURE_ATLAS_H__
#define __TEXTURE_ATLAS_H__

#include <string>

#include "Base/Types.h"
#include "Base/Ref.h"

class Texture2D;
class EventCustom;

/** @brief A class that implements a Texture Atlas.
Supported features:
* The atlas file can be a PVRTC, PNG or any other format supported by Texture2D
* Quads can be updated in runtime
* Quads can be added in runtime
* Quads can be removed in runtime
* Quads can be re-ordered in runtime
* The TextureAtlas capacity can be increased or decreased in runtime
* OpenGL component: V3F, C4B, T2F.
The quads are rendered using an OpenGL ES VBO.
To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file 

@warning If you want to use TextureAtlas, you'd better setup GL status before it's rendered.
         Otherwise, the effect of TextureAtlas will be affected by the GL status of other nodes.
*/
class TextureAtlas : public Ref 
{
public:
    /** Creates a TextureAtlas with an filename and with an initial capacity for Quads.

     * The TextureAtlas capacity can be increased in runtime.
     @param file A null terminated string contains the file path.
     @param capacity Capacity for Quads.
    */
    static TextureAtlas* create(const std::string& file , unsigned long capacity);

    /** Creates a TextureAtlas with a previously initialized Texture2D object, and
     * with an initial capacity for n Quads.

     * The TextureAtlas capacity can be increased in runtime.
     @param texture A texture2D object pointer.
     @param capacity Capacity for Quads.
     */
    static TextureAtlas* createWithTexture(Texture2D *texture, unsigned long capacity);
    /**
     * @js ctor
     */
    TextureAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureAtlas();

    /** Initializes a TextureAtlas with a filename and with a certain capacity for Quads.
    * The TextureAtlas capacity can be increased in runtime.
    *
     @attention Do not reinitialize the TextureAtlas because it will leak memory (issue #706).
     @param file A null terminated string contains the file path.
     @param capacity Capacity for Quads.
    */
    bool initWithFile(const std::string& file, unsigned long capacity);

    /** Initializes a TextureAtlas with a previously initialized Texture2D object, and
    * with an initial capacity for Quads. 
    * The TextureAtlas capacity can be increased in runtime.
     @attention: Do not reinitialize the TextureAtlas because it will leak memory (issue #706).
     @param texture A texture2D object pointer.
     @param capacity Capacity for Quads.
    */
    bool initWithTexture(Texture2D *texture, unsigned long capacity);

    /** Updates a Quad (texture, vertex and color) at a certain index.
    @param quad Quad that are going to be rendered.
    @param index Index must be between 0 and the atlas capacity - 1.
    @since v0.8
    */
    void updateQuad(V3F_C4B_T2F_Quad* quad, unsigned long index);

    /** Inserts a Quad (texture, vertex and color) at a certain index.
     @param quad Quad that are going to be rendered.
     @param index Index must be between 0 and the atlas capacity - 1.
     @since v0.8
    */
    void insertQuad(V3F_C4B_T2F_Quad* quad, unsigned long index);

    /** Inserts a c array of quads at a given index.
     @param quads Quad that are going to be rendered.
     @param index Index must be between 0 and the atlas capacity - 1.
     @param amount The quads array amount.
     @attention This method doesn't enlarge the array when amount + index > totalQuads.
     @since v1.1
    */
    void insertQuads(V3F_C4B_T2F_Quad* quads, unsigned long index, unsigned long amount);

    /** Removes the quad that is located at a certain index and inserts it at a new index.
    This operation is faster than removing and inserting in a quad in 2 different steps.
     @since v0.7.2
    */
    void insertQuadFromIndex(unsigned long fromIndex, unsigned long newIndex);

    /** Removes a quad at a given index number.
    The capacity remains the same, but the total number of quads to be drawn is reduced in 1.
    @since v0.7.2
    */
    void removeQuadAtIndex(unsigned long index);

    /** Removes a amount of quads starting from index.
        @since 1.1
     */
    void removeQuadsAtIndex(unsigned long index, unsigned long amount);
    /** Removes all Quads.
    The TextureAtlas capacity remains untouched. No memory is freed.
    The total number of quads to be drawn will be 0.
    @since v0.7.2
    */
    void removeAllQuads();

    /** Resize the capacity of the TextureAtlas.
    * The new capacity can be lower or higher than the current one.
    * It returns true if the resize was successful.
    * If it fails to resize the capacity it will return false with a new capacity of 0.
     
     @param capacity Capacity for Quads.
    */
    bool resizeCapacity(unsigned long capacity);

    /**
     Used internally by ParticleBatchNode.
     don't use this unless you know what you're doing.
     @since 1.1
    */
    void increaseTotalQuadsWith(unsigned long amount);

    /** Moves an amount of quads from oldIndex at newIndex.
     @since v1.1
     */
    void moveQuadsFromIndex(unsigned long oldIndex, unsigned long amount, unsigned long newIndex);

    /**
     Moves quads from index till totalQuads to the newIndex.
     Used internally by ParticleBatchNode.
     This method doesn't enlarge the array if newIndex + quads to be moved > capacity.
     @since 1.1
    */
    void moveQuadsFromIndex(unsigned long index, unsigned long newIndex);

    /**
     Ensures that after a realloc quads are still empty.
     Used internally by ParticleBatchNode.
     @since 1.1
    */
    void fillWithEmptyQuadsFromIndex(unsigned long index, unsigned long amount);

    /** Draws n quads.
    * N can't be greater than the capacity of the Atlas.
    */
    void drawNumberOfQuads(unsigned long n);

    /** Draws n quads from an index (offset).
    N + start can't be greater than the capacity of the atlas.

    @since v1.0
    */
    void drawNumberOfQuads(unsigned long numberOfQuads, unsigned long start);

    /** Draws all the Atlas's Quads.
    */
    void drawQuads();
    /** Listen the event that renderer was recreated on Android.
     */
    void listenRendererRecreated(EventCustom* event);

    /** Whether or not the array buffer of the VBO needs to be updated.*/
    inline bool isDirty(void) { return _dirty; }
    /** Specify if the array buffer of the VBO needs to be updated. */
    inline void setDirty(bool bDirty) { _dirty = bDirty; }

    /**Get quads total amount.
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /** Gets the quantity of quads that are going to be drawn. */
    unsigned long getTotalQuads() const;
    
    /** Gets the quantity of quads that can be stored with the current texture atlas size. */
    unsigned long getCapacity() const;
    
    /** Gets the texture of the texture atlas. */
    Texture2D* getTexture() const;
    
    /** Sets the texture for the texture atlas. */
    void setTexture(Texture2D* texture);
    
    /** Gets the quads that are going to be rendered. */
    V3F_C4B_T2F_Quad* getQuads();
    
    /** Sets the quads that are going to be rendered. */
    void setQuads(V3F_C4B_T2F_Quad* quads);
    
private:
    void renderCommand();

    void setupIndices();
    void mapBuffers();
    void setupVBOandVAO();
    void setupVBO();

protected:
    GLushort*           _indices;
    GLuint              _VAOname;
    GLuint              _buffersVBO[2]; //0: vertex  1: indices
    bool                _dirty; //indicates whether or not the array buffer of the VBO needs to be updated
    /** quantity of quads that are going to be drawn */
    unsigned long _totalQuads;
    /** quantity of quads that can be stored with the current texture atlas size */
    unsigned long _capacity;
    /** Texture of the texture atlas */
    Texture2D* _texture;
    /** Quads that are going to be rendered */
    V3F_C4B_T2F_Quad* _quads;
    
};

#endif //__TEXTURE_ATLAS_H__


