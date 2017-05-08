#ifndef __LAYER_H__
#define __LAYER_H__

#include "Renderer/Node.h"
#include "Renderer/Protocols.h"
#include "Renderer/CustomCommand.h"
#include "Base/Macros.h"

/*
class __Set;
class TouchScriptHandlerEntry;
*/

class Event;
class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;
class EventListener;

#include "Event/Touch.h"
#include "Event/EventKeyboard.h"
//
// Layer
//
/** @class Layer
 * @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class Layer : public Node
{
public:    
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased Layer object.
     */
    static Layer *create();

    /* Callback function should not be deprecated, it will generate lots of warnings.
       Since 'setTouchEnabled' was deprecated, it will make warnings if developer s onTouchXXX and invokes setTouchEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for touch began.
     *
     * @param touch Touch information.
     * @param unused_event Event information.
     * @return if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
     * @js NA
     */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    /** Callback function for touch moved.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    /** Callback function for touch ended.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    /** Callback function for touch cancelled.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    /** Callback function for multiple touches began.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches moved.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches ended.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches cancelled.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setAccelerometerEnabled' was deprecated, it will make warnings if developer s onAcceleration and invokes setAccelerometerEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for acceleration.
     * @param acc Acceleration information.
     * @param unused_event Event information.
     * @js NA
     */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);

    /** If isTouchEnabled, this method is called onEnter.  it to change the
    way Layer receives touch events.
    ( Default: TouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
    Example:
    void Layer::registerWithTouchDispatcher()
    {
    TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    }
	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setKeyboardEnabled' was deprecated, it will make warnings if developer s onKeyXXX and invokes setKeyboardEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for key pressed.
     * @param keyCode KeyCode information.
     * @param event Event information.
     * @js NA
     */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    /** Callback function for key released.
    * @param keyCode KeyCode information.
    * @param event Event information.
    * @js NA
    */
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	// s
    virtual std::string getDescription() const ;

public:
    Layer();
    virtual ~Layer();

    virtual bool init() ;

protected:
    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keyboardEnabled;
    EventListener* _touchListener;
    EventListenerKeyboard* _keyboardListener;
    EventListenerAcceleration* _accelerationListener;

    Touch::DispatchMode _touchMode;
    bool _swallowsTouches;

private:
    DISALLOW_COPY_AND_ASSIGN(Layer);

};


/** @class __LayerRGBA
 * @brief LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 
 All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 - opacity
 - RGB colors
 @since 2.1
 @js NA
 */
class __LayerRGBA : public Layer, public __RGBAProtocol
{
public:
    CREATE_FUNC(__LayerRGBA);
    
    
    //
    // s
    //
    virtual GLubyte getOpacity() const  { return Layer::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const  { return Layer::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity)  { Layer::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity)  { Layer::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const  { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled)  { Layer::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor() const  { return Layer::getColor(); }
    virtual const Color3B& getDisplayedColor() const  { return Layer::getDisplayedColor(); }
    virtual void setColor(const Color3B& color)  { Layer::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor)  { Layer::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const  { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled)  { Layer::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue)  { Layer::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const  { return Layer::isOpacityModifyRGB(); }

public:
    __LayerRGBA();
    virtual ~__LayerRGBA() {}

private:
    DISALLOW_COPY_AND_ASSIGN(__LayerRGBA);
};

//
// LayerColor
//
/** @class LayerColor
 * @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

All features from Layer are valid, plus the following new features:
- opacity
- RGB colors
*/
class LayerColor : public Layer, public BlendProtocol
{
public:
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased LayerColor object.
     */
    static LayerColor* create();
    /** Creates a Layer with color, width and height in Points.
     *
     * @param color The color of layer.
     * @param width The width of layer.
     * @param height The height of layer.
     * @return An autoreleased LayerColor object.
     */
    static LayerColor * create(const Color4B& color, GLfloat width, GLfloat height);
    /** Creates a Layer with color. Width and height are the window size.
     *
     * @param color The color of layer.
     * @return An autoreleased LayerColor object.
     */
    static LayerColor * create(const Color4B& color);

    /** Change width in Points.
     * 
     * @param w The width of layer.
     */
    void changeWidth(GLfloat w);
    /** Change height in Points.
     *
     * @param h The height of layer.
     */
    void changeHeight(GLfloat h);
    /** Change width and height in Points.
     * 
     * @param w The width of layer.
     * @param h The Height of layer.
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    //
    // s
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, unsigned int flags);

    virtual void setContentSize(const Size & var) ;
    /** BlendFunction. Conforms to BlendProtocol protocol */
    /**
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const ;
    /**
    *@code
    *When this function bound into js or lua,the parameter will be changed
    *In js: var setBlendFunc(var src, var dst)
    *In lua: local setBlendFunc(local src, local dst)
    *@endcode
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) ;

    virtual std::string getDescription() const ;
    
public:
    LayerColor();
    virtual ~LayerColor();
    
    bool init() ;
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    bool initWithColor(const Color4B& color);

protected:
    void onDraw(const Mat4& transform, unsigned int flags);

    virtual void updateColor() ;

    BlendFunc _blendFunc;
    Vec2 _squareVertices[4];
    Color4F  _squareColors[4];
    CustomCommand _customCommand;
    Vec3 _noMVPVertices[4];
private:
    DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @class LayerGradient
 * @brief LayerGradient is a subclass of LayerColor that draws gradients across the background.

All features from LayerColor are valid, plus the following new features:
- direction
- final color
- interpolation mode

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.

If 'compressedInterpolation' is disabled, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.

If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.

@since v0.99.5
*/
class LayerGradient : public LayerColor
{
public:
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create();

    /** Creates a full-screen Layer with a gradient between start and end.
     *
     * @param start The start color.
     * @param end The end color.
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** Creates a full-screen Layer with a gradient between start and end in the direction of v.
     *
     * @param start The start color.
     * @param end The end color.
     * @param v The direction of gradient color.
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Vec2& v);
    
    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors.
     Default: true.
     *
     * @param compressedInterpolation The interpolation will be compressed if true.
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    /** Get the compressedInterpolation
     *
     * @return The interpolation will be compressed if true.
     */
    bool isCompressedInterpolation() const;

    /** Sets the start color of the gradient.
     * 
     * @param startColor The start color.
     */
    void setStartColor( const Color3B& startColor );
    /** Returns the start color of the gradient.
     *
     * @return The start color.
     */
    const Color3B& getStartColor() const;

    /** Sets the end color of the gradient.
     *
     * @param endColor The end color.
     */
    void setEndColor( const Color3B& endColor );
    /** Returns the end color of the gradient.
     *
     * @return The end color.
     */
    const Color3B& getEndColor() const;

    /** Returns the start opacity of the gradient.
     *
     * @param startOpacity The start opacity, from 0 to 255.
     */
    void setStartOpacity( GLubyte startOpacity );
    /** Returns the start opacity of the gradient.
     *
     * @return The start opacity.
     */
    GLubyte getStartOpacity() const;

    /** Returns the end opacity of the gradient.
     *
     * @param endOpacity The end opacity, from 0 to 255.
     */
    void setEndOpacity( GLubyte endOpacity );
    /** Returns the end opacity of the gradient.
     *
     * @return The end opacity.
     */
    GLubyte getEndOpacity() const;

    /** Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     *
     * @param alongVector The direction of gradient.
     */
    void setVector(const Vec2& alongVector);
    /** Returns the directional vector used for the gradient.
     *
     * @return The direction of gradient.
     */
    const Vec2& getVector() const;

    virtual std::string getDescription() const ;
    
public:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init() ;
    /** Initializes the Layer with a gradient between start and end.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** Initializes the Layer with a gradient between start and end in the direction of v.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Vec2& v);

protected:
    virtual void updateColor() ;

    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Vec2   _alongVector;
    bool    _compressedInterpolation;
};


/** @class LayerMultiplex
 * @brief MultipleLayer is a Layer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class LayerMultiplex : public Layer
{
public:
    /** Creates and initializes a LayerMultiplex object.
     * @lua NA
     * 
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex* create();

    /** Creates a LayerMultiplex with an array of layers.
     @since v2.1
     * @js NA
     *
     * @param arrayOfLayers An array of layers.
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** Creates a LayerMultiplex with one or more layers using a variable argument list.
     * @code
     * When this function bound to lua or js,the input params are changed.
     * In js:var create(...)
     * In lua:local create(...)
     * @endcode
     */
#if (TARGET_PLATFORM == PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef Layer* M;
    static LayerMultiplex* create(M m1, std::nullptr_t listEnd) { return createVariadic(m1, NULL); }
    static LayerMultiplex* create(M m1, M m2, std::nullptr_t listEnd) { return createVariadic(m1, m2, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use createWithArray or createVariadic with NULL as the last argument
    static LayerMultiplex* createVariadic(Layer* item, ...) REQUIRES_NULL_TERMINATION;
#else
    static LayerMultiplex * create(Layer* layer, ... );
#endif

    /** Creates a LayerMultiplex with one layer.
     * Lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     * @js NA
     * @lua NA
     *
     * @param layer A certain layer.
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    /** Add a certain layer to LayerMultiplex.
     *
     * @param layer A layer need to be added to the LayerMultiplex.
     */
    void addLayer(Layer* layer);

    /** Switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @param n The layer indexed by n will display.
     */
    void switchTo(int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @param n The layer indexed by n will display.
     */
    void switchToAndReleaseMe(int n);

    virtual std::string getDescription() const ;
    
public:
    /**
     * @js ctor
     */
    LayerMultiplex();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerMultiplex();
    
    virtual bool init() ;
    /** initializes a MultiplexLayer with one or more layers using a variable argument list.
     * @js NA
     * @lua NA
     */
    bool initWithLayers(Layer* layer, va_list params);
    
    /** initializes a MultiplexLayer with an array of layers
     @since v2.1
     */
    bool initWithArray(const Vector<Layer*>& arrayOfLayers);

protected:
    unsigned int _enabledLayer;
    Vector<Layer*>    _layers;

private:
    DISALLOW_COPY_AND_ASSIGN(LayerMultiplex);
};

#endif // __LAYER_H__

