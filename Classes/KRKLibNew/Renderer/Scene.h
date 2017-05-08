#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "Renderer/Node.h"

class Renderer;
//class EventListenerCustom;
//class EventCustom;
#if USE_PHYSICS
class PhysicsWorld;
#endif

/** @class Scene
* @brief Scene is a subclass of Node that is used only as an abstract concept.

Scene and Node are almost identical with the difference that Scene has its
anchor point (by default) at the center of the screen.

For the moment Scene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use a Scene as the parent of all your nodes.
 
Scene will create a default camera for you.
*/
class Scene : public Node
{
public:
    /** Creates a new Scene object. 
     *
     * @return An autoreleased Scene object.
     */
    static Scene *create();

    /** Creates a new Scene object with a predefined Size. 
     *
     * @param size The predefined size of scene.
     * @return An autoreleased Scene object.
     * @js NA
     */
    static Scene *createWithSize(const Size& size);

    using Node::addChild;
    virtual std::string getDescription() const override;
    
    /** Get all cameras.
     * 
     * @return The vector of all cameras, ordered by camera depth.
     * @js NA
     */
    //const std::vector<Camera*>& getCameras();

    /** Get the default camera.
     * @js NA
     * @return The default camera of scene.
     */
    //Camera* getDefaultCamera() const { return _defaultCamera; }

    /** Get lights.
     * @return The vector of lights.
     * @js NA
     */
    //const std::vector<BaseLight*>& getLights() const { return _lights; }
    
    /** Render the scene.
     * @param renderer The renderer use to render the scene.
     * @js NA
     */
    virtual void render(Renderer* renderer);
    
    /** override function */
    virtual void removeAllChildren() override;
    
public:
    Scene();
    virtual ~Scene();
    
    bool init() override;
    bool initWithSize(const Size& size);
    
    void setCameraOrderDirty() { _cameraOrderDirty = true; }
    
    //void onProjectionChanged(EventCustom* event);

protected:
    friend class Node;
    //friend class ProtectedNode;
    //friend class SpriteBatchNode;
    //friend class Camera;
    //friend class BaseLight;
    friend class Renderer;
    
    //std::vector<Camera*> _cameras; //weak ref to Camera
    //Camera*              _defaultCamera; //weak ref, default camera created by scene, _cameras[0], Caution that the default camera can not be added to _cameras before onEnter is called
    bool                 _cameraOrderDirty; // order is dirty, need sort
    //EventListenerCustom*       _event;

    //std::vector<BaseLight *> _lights;
    
private:
    DISALLOW_COPY_AND_ASSIGN(Scene);
    
#if (USE_PHYSICS)
public:
    
#if USE_PHYSICS
    /** Get the physics world of the scene.
     * @return The physics world of the scene.
     * @js NA
     */
    inline PhysicsWorld* getPhysicsWorld() const { return _physicsWorld; }
#endif
    
    /** Create a scene with physics.
     * @return An autoreleased Scene object with physics.
     * @js NA
     */
    static Scene *createWithPhysics();
    
public:
    bool initWithPhysics();
    
protected:
    void addChildToPhysicsWorld(Node* child);

#if USE_PHYSICS
    PhysicsWorld* _physicsWorld;
#endif
    
#endif // (USE_PHYSICS || USE_3D_PHYSICS)
    
   
#if (USE_PHYSICS)
public:
    void stepPhysicsAndNavigation(float deltaTime);
#endif
};

#endif // __SCENE_H__
