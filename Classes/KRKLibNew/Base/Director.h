#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include <stack>
//#include <thread>

//#include "Platform/PlatformMacros.h"
#include "Base/Ref.h"
#include "Base/Vector.h"
#include "Math/Math.h"  
//#include "Platform/CCGL.h"
//#include "Platform/GLView.h"

class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
//class EventCustom;
//class EventListenerCustom;
class TextureCache;
class Renderer;
//class Camera;
//class Console;
class Scene;
/**
 @brief Class that creates and handles the main Window and manages how
 and when to execute the Scenes.
 
 The Director is also responsible for:
 - initializing the OpenGL context
 - setting the OpenGL buffer depth (default one is 0-bit)
 - setting the projection (default one is 3D)
 
 Since the Director is a singleton, the standard way to use it is by calling:
 _ Director::getInstance()->methodName();
 */
class Director : public Ref
{
public:
    /** Director will trigger an event when projection type is changed. */
    static const char* EVENT_PROJECTION_CHANGED;
    /** Director will trigger an event before Schedule::update() is invoked. */
    static const char* EVENT_BEFORE_UPDATE;
    /** Director will trigger an event after Schedule::update() is invoked. */
    static const char* EVENT_AFTER_UPDATE;
    /** Director will trigger an event after Scene::render() is invoked. */
    static const char* EVENT_AFTER_VISIT;
    /** Director will trigger an event after a scene is drawn, the data is sent to GPU. */
    static const char* EVENT_AFTER_DRAW;

    /** 
     * Returns a shared instance of the director. 
     * @js _getInstance
     */
    static Director* getInstance();

    /**
     * @js ctor
     */
    Director();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init(int w, int h, int res_w, int res_h, std::string defaultFontName);

    // attribute

    /** Gets current running Scene. Director can only run one Scene at a time. */
    inline Scene* getRunningScene() { return _runningScene; }

    /** Gets the FPS value. */
    inline float getAnimationInterval() { return _animationInterval; }
    /** Sets the FPS value. FPS = 1/interval. */
    virtual void setAnimationInterval(float interval) = 0;

    /** Whether or not displaying the FPS on the bottom-left corner of the screen. */
    inline bool isDisplayStats() { return _displayStats; }
    /** Display the FPS on the bottom-left corner of the screen. */
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** Get seconds per frame. */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /*
     * Gets singleton of TextureCache.
     * @js NA
     */
    TextureCache* getTextureCache() const;

    /** Whether or not `_nextDeltaTimeZero` is set to 0. */
    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    /** 
     * Sets the delta time between current frame and next frame is 0.
     * This value will be used in Schedule, and will affect all functions that are using frame delta time, such as Actions.
     * This value will take effect only one time.
     */
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Whether or not the Director is paused. */
    inline bool isPaused() { return _paused; }

    /** How many frames were called since the director started */
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
   
    /** How many frames were called since the director started */
    
    
    /** Whether or not the replaced scene will receive the cleanup message.
     * If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     * If the new scene replaces the old one, the it will receive the "cleanup" message.
     * @since v0.99.0
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     * This object MUST implement the "visit" function.
     * Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     * @since v0.99.5
     */
    Node* getNotificationNode() { return _notificationNode; }
    /** 
     * Sets the notification node.
     * @see Director::getNotificationNode()
     */
    void setNotificationNode(Node *node);
    
    // Scene Management

    /** 
     * Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     * @js NA
     */
    void runWithScene(Scene *scene);

    /** 
     * Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     */
    void pushScene(Scene *scene);

    /** 
     * Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    void popScene();

    /** 
     * Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`.
     */
    void popToRootScene();

    /** Pops out all scenes from the stack until it reaches `level`.
     If level is 0, it will end the director.
     If level is 1, it will pop all scenes until it reaches to root scene.
     If level is <= than the current stack level, it won't do anything.
     */
 	void popToSceneStackLevel(int level);

    /** Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     * @js NA
     */
    void replaceScene(Scene *scene);

    /** Ends the execution, releases the running scene.
     * @lua endToLua
     */
    void end();

    /** Pauses the running scene.
     * The running scene will be _drawed_ but all scheduled timers will be paused.
     * While paused, the draw rate will be 4 FPS to reduce CPU consumption.
     */
    void pause();

    /** Resumes the paused scene.
     * The scheduled timers will be activated again.
     * The "delta time" will be 0 (as if the game wasn't paused).
     */
    void resume();
    
    /*
     * Restart the director. 
     * @js NA
     */
    void restart();

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     * If you don't want to pause your animation call [pause] instead.
     */
    virtual void stopAnimation() = 0;

    /** The main loop is triggered again.
     * Call this function only if [stopAnimation] was called earlier.
     * @warning Don't call this function to start the main loop. To run the main loop call runWithScene.
     */
    virtual void startAnimation() = 0;

    /** Draw the scene.
     * This method is called every frame. Don't call it manually.
     */
    void drawScene();

    // Memory Helper

    /** Removes all cocos2d cached data.
     * It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     * @since v0.99.3
     */
    void purgeCachedData();

	/** Sets the default values based on the Configuration info. */
    void setDefaultValues();

    // OpenGL Helper

    /** Sets the OpenGL default values.
     * It will enable alpha blending, disable depth test.
     * @js NA
     */
    //void setGLDefaultValues();

    /** Enables/disables OpenGL alpha blending. */
    //void setAlphaBlending(bool on);
    
    /** Sets clear values for the color buffers,
     * value range of each element is [0.0, 1.0].
     * @js NA
     */
    //void setClearColor(const Color4F& clearColor);

    /** Enables/disables OpenGL depth test. */
    //void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** The size in pixels of the surface. It could be different than the screen size.
     * High-res devices might have a higher surface size than the screen size.
     * Only available when compiled using SDK >= 4.0.
     * @since v0.99.4
     */
    //void setContentScaleFactor(float scaleFactor);
    /**
     * Gets content scale factor.
     * @see Director::setContentScaleFactor()
     */
    //float getContentScaleFactor() { return _contentScaleFactor; }

    /** Gets the Scheduler associated with this director.
     * @since v2.0
     */
    Scheduler* getScheduler() { return _scheduler; }
    
    /** Sets the Scheduler associated with this director.
     * @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** Gets the ActionManager associated with this director.
     * @since v2.0
     */
    ActionManager* getActionManager() { return _actionManager; }
    
    /** Sets the ActionManager associated with this director.
     * @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** Gets the EventDispatcher associated with this director.
     * @since v3.0
     * @js NA
     */
    EventDispatcher* getEventDispatcher() { return _eventDispatcher; }
    
    /** Sets the EventDispatcher associated with this director.
     * @since v3.0
     * @js NA
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** Returns the Renderer associated with this director.
     * @since v3.0
     */
    Renderer* getRenderer() { return _renderer; }

    /** Returns the Console associated with this director.
     * @since v3.0
     * @js NA
     */
    //Console* getConsole()  { return _console; }

    /* Gets delta time since last tick to main loop. */
	float getDeltaTime() ;
    
    /**
     *  Gets Frame Rate.
     * @js NA
     */
    float getFrameRate()  { return _frameRate; }


    /** 
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @js NA
     */
    //void pushMatrix(MATRIX_STACK_TYPE type);
    /** Pops the top matrix of the specified type of matrix stack.
     * @js NA
     */
    //void popMatrix(MATRIX_STACK_TYPE type);
    /** Adds an identity matrix to the top of specified type of matrix stack.
     * @js NA
     */
    //void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    /**
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @param type Matrix type.
     * @param mat The matrix that to be added.
     * @js NA
     */
    //void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be multiplied.
     * @js NA
     */
    //void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**
     * Gets the top matrix of specified type of matrix stack.
     * @js NA
     */
    //const Mat4& getMatrix(MATRIX_STACK_TYPE type);
    /**
     * Clear all types of matrix stack, and add identity matrix to these matrix stacks.
     * @js NA
     */
    //void resetMatrixStack();

    /**
     * returns the cocos2d thread id.
     Useful to know if certain code is already running on the cocos2d thread
     */
    //const std::thread::id& getCocos2dThreadId() const { return _cocos2d_thread_id; }

	void HandleKeyUp(int Key);

	void HandleKeyDown(int Key);
	
	void HandleTouchDown(float x, float y, float pressure);
	void HandleTouchMove(float x, float y, float pressure);
	void HandleTouchUp(float x, float y, float pressure);

	void ResetGLRenderer();

protected:
    void reset();
    
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // this flag will be set to true in end()
    
    void restartDirector();
    bool _restartDirectorInNextLoop; // this flag will be set to true in restart()
    
    void setNextScene();
    
    void showStats();
    //void createStatsLabel();
    void calculateMPF();
    //void getFPSImageData(unsigned char** datapointer, unsigned long* length);
    
    /** calculates delta time since last time it was called */    
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    //void initMatrixStack();

    //std::stack<Mat4> _modelViewMatrixStack;
    //std::stack<Mat4> _projectionMatrixStack;
    //std::stack<Mat4> _textureMatrixStack;

    /** Scheduler associated with this director
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** ActionManager associated with this director
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** EventDispatcher associated with this director
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    //EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventBeforeUpdate, *_eventAfterUpdate;
        
    /* delta time since last tick to main loop */
	float _deltaTime;
    
    /* The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl
     which inherit from it as default renderer context,you can have your own by inherit from it*/
    //GLView *_openGLView;

    //texture cache belongs to this director
    TextureCache *_textureCache;

    float _animationInterval;
    float _oldAnimationInterval;

    /* landscape mode ? */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    //LabelAtlas *_FPSLabel;
    //LabelAtlas *_drawnBatchesLabel;
    //LabelAtlas *_drawnVerticesLabel;
    
    /** Whether or not the Director is paused */
    bool _paused;

    /* How many frames were called since the director started */
    unsigned int _totalFrames;
    float _secondsPerFrame;
    
    /* The running scene */
    Scene *_runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    Scene *_nextScene;
    
    /* If true, then "old" scene will receive the cleanup message */
    bool _sendCleanupToScene;

    /* scheduled scenes */
    Vector<Scene*> _scenesStack;
    
    /* last time the main loop was updated */
    struct timeval *_lastUpdate;

    /* whether or not the next delta time will be zero */
    bool _nextDeltaTimeZero;
    
    /* projection used */
    //Projection _projection;

    /* window size in points */
    //Size _winSizeInPoints;
    
    /* content scale factor */
    //float _contentScaleFactor;

    /* This object will be visited after the scene. Useful to hook a notification node */
    Node *_notificationNode;

    /* Renderer for the Director */
    Renderer *_renderer;
    
    /* Default FrameBufferObject*/
    //experimental::FrameBuffer* _defaultFBO;

    /* Console for the director */
    //Console *_console;

    bool _isStatusLabelUpdated;

    /* cocos2d thread id */
    //std::thread::id _cocos2d_thread_id;

    // GLView will recreate stats labels to fit visible rect
    friend class GLView;
};

/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop();
    virtual void setAnimationInterval(float value);
    virtual void startAnimation();
    virtual void stopAnimation();

protected:
    bool _invalid;
};


#endif // __DIRECTOR_H__
