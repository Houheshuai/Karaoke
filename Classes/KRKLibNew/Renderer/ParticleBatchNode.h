#ifndef __PARTICLEBATCHNODE_H__
#define __PARTICLEBATCHNODE_H__

#include "Renderer/Node.h"
#include "Renderer/Protocols.h"
#include "Renderer/BatchCommand.h"

class Texture2D;
class TextureAtlas;
class ParticleSystem;

/**
 * @addtogroup _2d
 * @{
 */

#define kParticleDefaultCapacity 500

/** @class ParticleBatchNode
 * @brief ParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A ParticleBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the ParticleSystems that are contained in that texture can be added to the SpriteBatchNode.
 * All ParticleSystems added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
 * If the ParticleSystems are not added to a ParticleBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 * - At the moment only ParticleSystemQuad is supported
 * - All systems need to be drawn with the same parameters, blend function, aliasing, texture
 *
 * Most efficient usage
 * - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems
 * - Initialize all particle systems and add them as child to the batch node
 * @since v1.1
 */

class ParticleBatchNode : public Node, public TextureProtocol
{
public:
    /** Create the particle system with Texture2D, a capacity of particles, which particle system to use.
     *
     * @param tex A given texture.
     * @param capacity A capacity of particles.
     * @return An autoreleased ParticleBatchNode object.
     * @js NA
     */
    static ParticleBatchNode* createWithTexture(Texture2D *tex, int capacity = kParticleDefaultCapacity);

    /** Create the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles.
     *
     * @param fileImage A given file name.
     * @param capacity A capacity of particles.
     * @return An autoreleased ParticleBatchNode object.
     */
    static ParticleBatchNode* create(const std::string& fileImage, int capacity = kParticleDefaultCapacity);

    /** Inserts a child into the ParticleBatchNode.
     *
     * @param system A given particle system.
     * @param index The insert index.
     */
    void insertChild(ParticleSystem* system, int index);

    /** Remove a child of the ParticleBatchNode.
     *
     * @param index The index of the child.
     * @param doCleanup True if all actions and callbacks on this node should be removed, false otherwise.
     */
    void removeChildAtIndex(int index, bool doCleanup);
    void removeAllChildrenWithCleanup(bool doCleanup) override;

    /** Disables a particle by inserting a 0'd quad into the texture atlas.
     *
     * @param particleIndex The index of the particle.
     */
    void disableParticle(int particleIndex);

    /** Gets the texture atlas used for drawing the quads.
     *
     * @return The texture atlas used for drawing the quads.
     */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; };
    
    /** Sets the texture atlas used for drawing the quads.
     *
     * @param atlas The texture atlas used for drawing the quads.
     */
    inline void setTextureAtlas(TextureAtlas* atlas) { _textureAtlas = atlas; };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, unsigned int parentFlags) override;

    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void reorderChild(Node * child, int zOrder) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, unsigned int flags) override;
    virtual Texture2D* getTexture(void) const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc(void) const override;
    
public:
    /**
     * @js ctor
     */
    ParticleBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleBatchNode();
    
    /** initializes the particle system with Texture2D, a capacity of particles */
    bool initWithTexture(Texture2D *tex, int capacity);
    
    /** initializes the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles */
    bool initWithFile(const std::string& fileImage, int capacity);
    
private:
    void updateAllAtlasIndexes();
    void increaseAtlasCapacityTo(long quantity);
    int searchNewPositionInChildrenForZ(int z);
    void getCurrentIndex(int* oldIndex, int* newIndex, Node* child, int z);
    int addChildHelper(ParticleSystem* child, int z, int aTag, const std::string &name, bool setTag);
    void addChildByTagOrName(ParticleSystem* child, int z, int tag, const std::string &name, bool setTag);
    void updateBlendFunc(void);
    /** the texture atlas used for drawing the quads */
    TextureAtlas* _textureAtlas;

    /** the blend function used for drawing the quads */
    BlendFunc _blendFunc;
    // quad command
    BatchCommand _batchCommand;
};

#endif // __PARTICLEBATCHNODE_H__ 

