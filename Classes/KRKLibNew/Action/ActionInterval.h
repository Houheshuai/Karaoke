#ifndef __ACTION_INTERVAL_ACTION_H__
#define __ACTION_INTERVAL_ACTION_H__

#include <vector>

#include "Action/Action.h"
#include "Base/Vector.h"
#include "Base/Types.h"
#include "Renderer/OpenGLESHeaders.h"

class Node;

/** @class ActionInterval
@brief An interval action is an action that takes place within a certain period of time.
It has an start time, and a finish time. The finish time is the parameter
duration plus the start time.

These ActionInterval actions have some interesting properties, like:
- They can run normally (default)
- They can run reversed with the reverse method
- They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.

For example, you can simulate a Ping Pong effect running the action normally and
then running it again in Reverse mode.

Example:

Action *pingPongAction = Sequence::actions(action, action->reverse(), nullptr);
*/
class ActionInterval : public FiniteTimeAction
{
public:
    /** How many seconds had elapsed since the actions started to run.
     *
     * @return The seconds had elapsed since the actions started to run.
     */
    inline float getElapsed(void) { return _elapsed; }

    /** Sets the amplitude rate, extension in GridAction
     *
     * @param amp   The amplitude rate.
     */
    void setAmplitudeRate(float amp);
    
    /** Gets the amplitude rate, extension in GridAction
     *
     * @return  The amplitude rate.
     */
    float getAmplitudeRate(void);

    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    /**
     * @param dt in seconds
     */
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual ActionInterval* reverse() const override
    {
        
        return nullptr;
    }

    virtual ActionInterval *clone() const override
    {
        
        return nullptr;
    }

public:
    /** initializes the action */
    bool initWithDuration(float d);

protected:
    float _elapsed;
    bool   _firstTick;

protected:
    bool sendUpdateEventToScript(float dt, Action *actionObject);
};

/** @class Sequence
 * @brief Runs actions sequentially, one after another.
 */
class Sequence : public ActionInterval
{
public:
    /** Helper constructor to create an array of sequenceable actions.
     *
     * @return An autoreleased Sequence object.
     */
    static Sequence* create(FiniteTimeAction *action1, ...) REQUIRES_NULL_TERMINATION;

    /** Helper constructor to create an array of sequenceable actions given an array.
     * @code
     * When this function bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @param arrayOfActions An array of sequenceable actions.
     * @return An autoreleased Sequence object.
     */
    static Sequence* create(const Vector<FiniteTimeAction*>& arrayOfActions);
    /** Helper constructor to create an array of sequence-able actions.
     *
     * @param action1 The first sequenceable action.
     * @param args The va_list variable.
     * @return An autoreleased Sequence object.
     * @js NA
     */
    static Sequence* createWithVariableList(FiniteTimeAction *action1, va_list args);
    /** Creates the action.
     * @param actionOne The first sequenceable action.
     * @param actionTwo The second sequenceable action.
     * @return An autoreleased Sequence object.
     * @js NA
     */
    static Sequence* createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo);

    //
    // Overrides
    //
    virtual Sequence* clone() const override;
    virtual Sequence* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param t In seconds.
     */
    virtual void update(float t) override;
    
public:
    Sequence() {}
    virtual ~Sequence(void);

    /** initializes the action */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);
    bool init(const Vector<FiniteTimeAction*>& arrayOfActions);

protected:
    FiniteTimeAction *_actions[2];
    float _split;
    int _last;

private:
    DISALLOW_COPY_AND_ASSIGN(Sequence);
};

/** @class Repeat
 * @brief Repeats an action a number of times.
 * To repeat an action forever use the RepeatForever action.
 */
class Repeat : public ActionInterval
{
public:
    /** Creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30).
     *
     * @param action The action needs to repeat.
     * @param times The repeat times.
     * @return An autoreleased Repeat object.
     */
    static Repeat* create(FiniteTimeAction *action, unsigned int times);

    /** Sets the inner action.
     *
     * @param action The inner action.
     */
    inline void setInnerAction(FiniteTimeAction *action)
    {
        if (_innerAction != action)
        {
            SAFE_RETAIN(action);
            SAFE_RELEASE(_innerAction);
            _innerAction = action;
        }
    }

    /** Gets the inner action.
     *
     * @return The inner action.
     */
    inline FiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual Repeat* clone() const override;
    virtual Repeat* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param dt In seconds.
     */
    virtual void update(float dt) override;
    virtual bool isDone(void) const override;
    
public:
    Repeat() {}
    virtual ~Repeat();

    /** initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30) */
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** Inner action */
    FiniteTimeAction *_innerAction;

private:
    DISALLOW_COPY_AND_ASSIGN(Repeat);
};

/** @class RepeatForever
 * @brief Repeats an action for ever.
 To repeat the an action for a limited number of times use the Repeat action.
 * @warning This action can't be Sequenceable because it is not an IntervalAction.
 */
class RepeatForever : public ActionInterval
{
public:
    /** Creates the action.
     *
     * @param action The action need to repeat forever.
     * @return An autoreleased RepeatForever object.
     */
    static RepeatForever* create(ActionInterval *action);

    /** Sets the inner action.
     *
     * @param action The inner action.
     */
    inline void setInnerAction(ActionInterval *action)
    {
        if (_innerAction != action)
        {
            SAFE_RELEASE(_innerAction);
            _innerAction = action;
            SAFE_RETAIN(_innerAction);
        }
    }

    /** Gets the inner action.
     *
     * @return The inner action.
     */
    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual RepeatForever* clone() const override;
    virtual RepeatForever* reverse(void) const override;
    virtual void startWithTarget(Node* target) override;
    /**
     * @param dt In seconds.
     */
    virtual void step(float dt) override;
    virtual bool isDone(void) const override;
    
public:
    RepeatForever()
    : _innerAction(nullptr)
    {}
    virtual ~RepeatForever();

    /** initializes the action */
    bool initWithAction(ActionInterval *action);

protected:
    /** Inner action */
    ActionInterval *_innerAction;

private:
    DISALLOW_COPY_AND_ASSIGN(RepeatForever);
};

/** @class Spawn
 * @brief Spawn a new action immediately
 */
class Spawn : public ActionInterval
{
public:
    /** Helper constructor to create an array of spawned actions.
     * @code
     * When this function bound to the js or lua, the input params changed.
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @return An autoreleased Spawn object.
     */
    static Spawn* create(FiniteTimeAction *action1, ...) REQUIRES_NULL_TERMINATION;

    /** Helper constructor to create an array of spawned actions. 
     *
     * @param action1   The first sequenceable action.
     * @param args  The va_list variable.
     * @return  An autoreleased Spawn object.
     * @js NA
     */
    static Spawn* createWithVariableList(FiniteTimeAction *action1, va_list args);

    /** Helper constructor to create an array of spawned actions given an array.
     *
     * @param arrayOfActions    An array of spawned actions.
     * @return  An autoreleased Spawn object.
     */
    static Spawn* create(const Vector<FiniteTimeAction*>& arrayOfActions);

    /** Creates the Spawn action.
     *
     * @param action1   The first spawned action.
     * @param action2   The second spawned action.
     * @return An autoreleased Spawn object.
     * @js NA
     */
    static Spawn* createWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);

    //
    // Overrides
    //
    virtual Spawn* clone() const override;
    virtual Spawn* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    Spawn() {}
    virtual ~Spawn();

    /** initializes the Spawn action with the 2 actions to spawn */
    bool initWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);
    bool init(const Vector<FiniteTimeAction*>& arrayOfActions);

protected:
    FiniteTimeAction *_one;
    FiniteTimeAction *_two;

private:
    DISALLOW_COPY_AND_ASSIGN(Spawn);
};

/** @class RotateTo
 * @brief Rotates a Node object to a certain angle by modifying it's rotation attribute.
 The direction will be decided by the shortest angle.
*/ 
class RotateTo : public ActionInterval
{
public:
    /** 
     * Creates the action with separate rotation angles.
     *
     * @param duration Duration time, in seconds.
     * @param dstAngleX In degreesCW.
     * @param dstAngleY In degreesCW.
     * @return An autoreleased RotateTo object.
     */
    static RotateTo* create(float duration, float dstAngleX, float dstAngleY);

    /** 
     * Creates the action.
     *
     * @param duration Duration time, in seconds.
     * @param dstAngle In degreesCW.
     * @return An autoreleased RotateTo object.
     */
    static RotateTo* create(float duration, float dstAngle);

    /** 
     * Creates the action with 3D rotation angles.
     * @param duration Duration time, in seconds.
     * @param dstAngle3D A Vec3 angle.
     * @return An autoreleased RotateTo object.
     */
    static RotateTo* create(float duration, const Vec3& dstAngle3D);

    //
    // Overrides
    //
    virtual RotateTo* clone() const override;
    virtual RotateTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    RotateTo();
    virtual ~RotateTo() {}

    /** 
     * initializes the action
     * @param duration in seconds
     * @param dstAngleX in degreesCW
     * @param dstAngleY in degreesCW
     */
    bool initWithDuration(float duration, float dstAngleX, float dstAngleY);
    /**
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec3& dstAngle3D);

    /** 
     * calculates the start and diff angles
     * @param dstAngle in degreesCW
     */
    void calculateAngles(float &startAngle, float &diffAngle, float dstAngle);
    
protected:
    bool _is3D;
    Vec3 _dstAngle;
    Vec3 _startAngle;
    Vec3 _diffAngle;

private:
    DISALLOW_COPY_AND_ASSIGN(RotateTo);
};

/** @class RotateBy
 * @brief Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
*/
class RotateBy : public ActionInterval
{
public:
    /** 
     * Creates the action.
     *
     * @param duration Duration time, in seconds.
     * @param deltaAngle In degreesCW.
     * @return An autoreleased RotateBy object.
     */
    static RotateBy* create(float duration, float deltaAngle);
    /**
     * Creates the action with separate rotation angles.
     *
     * @param duration Duration time, in seconds.
     * @param deltaAngleZ_X In degreesCW.
     * @param deltaAngleZ_Y In degreesCW.
     * @return An autoreleased RotateBy object.
     * @warning The physics body contained in Node doesn't support rotate with different x and y angle.
     */
    static RotateBy* create(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    /** Creates the action with 3D rotation angles.
     *
     * @param duration Duration time, in seconds.
     * @param deltaAngle3D A Vec3 angle.
     * @return An autoreleased RotateBy object.
     */
    static RotateBy* create(float duration, const Vec3& deltaAngle3D);

    //
    // Override
    //
    virtual RotateBy* clone() const override;
    virtual RotateBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    RotateBy();
    virtual ~RotateBy() {}

    /** initializes the action */
    bool initWithDuration(float duration, float deltaAngle);
    /** 
     * @warning The physics body contained in Node doesn't support rotate with different x and y angle.
     * @param deltaAngleZ_X in degreesCW
     * @param deltaAngleZ_Y in degreesCW
     */
    bool initWithDuration(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    bool initWithDuration(float duration, const Vec3& deltaAngle3D);
    
protected:
    bool _is3D;
    Vec3 _deltaAngle;
    Vec3 _startAngle;

private:
    DISALLOW_COPY_AND_ASSIGN(RotateBy);
};

/** @class MoveBy
 * @brief Moves a Node object x,y pixels by modifying it's position attribute.
 x and y are relative to the position of the object.
 Several MoveBy actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class MoveBy : public ActionInterval
{
public:
    /** 
     * Creates the action.
     *
     * @param duration Duration time, in seconds.
     * @param deltaPosition The delta distance in 2d, it's a Vec2 type.
     * @return An autoreleased MoveBy object.
     */
    static MoveBy* create(float duration, const Vec2& deltaPosition);
    /**
     * Creates the action.
     *
     * @param duration Duration time, in seconds.
     * @param deltaPosition The delta distance in 3d, it's a Vec3 type.
     * @return An autoreleased MoveBy object.
     */
    static MoveBy* create(float duration, const Vec3& deltaPosition);

    //
    // Overrides
    //
    virtual MoveBy* clone() const override;
    virtual MoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    
public:
    MoveBy():_is3D(false) {}
    virtual ~MoveBy() {}

    /** initializes the action */
    bool initWithDuration(float duration, const Vec2& deltaPosition);
    bool initWithDuration(float duration, const Vec3& deltaPosition);

protected:
    bool _is3D;
    Vec3 _positionDelta;
    Vec3 _startPosition;
    Vec3 _previousPosition;

private:
    DISALLOW_COPY_AND_ASSIGN(MoveBy);
};

/** @class MoveTo
 * @brief Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several MoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class MoveTo : public MoveBy
{
public:
    /** 
     * Creates the action.
     * @param duration Duration time, in seconds.
     * @param position The destination position in 2d.
     * @return An autoreleased MoveTo object.
     */
    static MoveTo* create(float duration, const Vec2& position);
    /**
     * Creates the action.
     * @param duration Duration time, in seconds.
     * @param position The destination position in 3d.
     * @return An autoreleased MoveTo object.
     */
    static MoveTo* create(float duration, const Vec3& position);

    //
    // Overrides
    //
    virtual MoveTo* clone() const override;
    virtual MoveTo* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    
public:
    MoveTo() {}
    virtual ~MoveTo() {}

    /** 
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec2& position);
    /**
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec3& position);

protected:
    Vec3 _endPosition;

private:
    DISALLOW_COPY_AND_ASSIGN(MoveTo);
};

/** @class SkewTo
 * @brief Skews a Node object to given angles by modifying it's skewX and skewY attributes
@since v1.0
*/
class SkewTo : public ActionInterval
{
public:
    /** 
     * Creates the action.
     * @param t Duration time, in seconds.
     * @param sx Skew x angle.
     * @param sy Skew y angle.
     * @return An autoreleased SkewTo object.
     */
    static SkewTo* create(float t, float sx, float sy);

    //
    // Overrides
    //
    virtual SkewTo* clone() const override;
    virtual SkewTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    SkewTo();
    virtual ~SkewTo() {}
    /**
     * @param t In seconds.
     */
    bool initWithDuration(float t, float sx, float sy);

protected:
    float _skewX;
    float _skewY;
    float _startSkewX;
    float _startSkewY;
    float _endSkewX;
    float _endSkewY;
    float _deltaX;
    float _deltaY;

private:
    DISALLOW_COPY_AND_ASSIGN(SkewTo);
};

/** @class SkewBy
* @brief Skews a Node object by skewX and skewY degrees.
@since v1.0
*/
class SkewBy : public SkewTo
{
public:
    /** 
     * Creates the action.
     * @param t Duration time, in seconds.
     * @param deltaSkewX Skew x delta angle.
     * @param deltaSkewY Skew y delta angle.
     * @return An autoreleased SkewBy object.
     */
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual SkewBy* clone() const  override;
    virtual SkewBy* reverse(void) const override;
    
public:
    SkewBy() {}
    virtual ~SkewBy() {}
    /**
     * @param t In seconds.
     */
    bool initWithDuration(float t, float sx, float sy);

private:
    DISALLOW_COPY_AND_ASSIGN(SkewBy);
};

/** @class JumpBy
 * @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
*/
class JumpBy : public ActionInterval
{
public:
    /** 
     * Creates the action.
     * @param duration Duration time, in seconds.
     * @param position The jumping distance.
     * @param height The jumping height.
     * @param jumps The jumping times.
     * @return An autoreleased JumpBy object.
     */
    static JumpBy* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Overrides
    //
    virtual JumpBy* clone() const override;
    virtual JumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    JumpBy() {}
    virtual ~JumpBy() {}

    /** 
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2           _startPosition;
    Vec2           _delta;
    float           _height;
    int             _jumps;
    Vec2           _previousPos;

private:
    DISALLOW_COPY_AND_ASSIGN(JumpBy);
};

/** @class JumpTo
 * @brief Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
*/ 
class JumpTo : public JumpBy
{
public:
    /** 
     * Creates the action.
     * @param duration Duration time, in seconds.
     * @param position The jumping destination position.
     * @param height The jumping height.
     * @param jumps The jumping times.
     * @return An autoreleased JumpTo object.
     */
    static JumpTo* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Override
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo* clone() const override;
    virtual JumpTo* reverse(void) const override;

public:
    JumpTo() {}
    virtual ~JumpTo() {}

    /** 
     * initializes the action
     * @param duration In seconds.
     */
    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2 _endPosition;

private:
    DISALLOW_COPY_AND_ASSIGN(JumpTo);
};

/** @struct Bezier configuration structure
 */
typedef struct _BezierConfig {
    //! end position of the bezier
    Vec2 endPosition;
    //! Bezier control point 1
    Vec2 controlPoint_1;
    //! Bezier control point 2
    Vec2 controlPoint_2;
} BezierConfig;

/** @class BezierBy
 * @brief An action that moves the target with a cubic Bezier curve by a certain distance.
 */
class BezierBy : public ActionInterval
{
public:
    /** Creates the action with a duration and a bezier configuration.
     * @param t Duration time, in seconds.
     * @param c Bezier config.
     * @return An autoreleased BezierBy object.
     * @code
     * When this function bound to js or lua,the input params are changed.
     * in js: var create(var t,var table)
     * in lua: local create(local t, local table)
     * @endcode
     */
    static BezierBy* create(float t, const BezierConfig& c);

    //
    // Overrides
    //
    virtual BezierBy* clone() const override;
    virtual BezierBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    BezierBy() {}
    virtual ~BezierBy() {}

    /** 
     * initializes the action with a duration and a bezier configuration
     * @param t in seconds
     */
    bool initWithDuration(float t, const BezierConfig& c);

protected:
    BezierConfig _config;
    Vec2 _startPosition;
    Vec2 _previousPosition;

private:
    DISALLOW_COPY_AND_ASSIGN(BezierBy);
};

/** @class BezierTo
 * @brief An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
class BezierTo : public BezierBy
{
public:
    /** Creates the action with a duration and a bezier configuration.
     * @param t Duration time, in seconds.
     * @param c Bezier config.
     * @return An autoreleased BezierTo object.
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: local create(local t, local table)
     * @endcode
     */
    static BezierTo* create(float t, const BezierConfig& c);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual BezierTo* clone() const override;
    virtual BezierTo* reverse(void) const override;
    
public:
    BezierTo() {}
    virtual ~BezierTo() {}
    /**
     * @param t In seconds.
     */
    bool initWithDuration(float t, const BezierConfig &c);

protected:
    BezierConfig _toConfig;

private:
    DISALLOW_COPY_AND_ASSIGN(BezierTo);
};

/** @class ScaleTo
 @brief Scales a Node object to a zoom factor by modifying it's scale attribute.
 @warning This action doesn't support "reverse".
 @warning The physics body contained in Node doesn't support this action.
 */
class ScaleTo : public ActionInterval
{
public:
    /** 
     * Creates the action with the same scale factor for X and Y.
     * @param duration Duration time, in seconds.
     * @param s Scale factor of x and y.
     * @return An autoreleased ScaleTo object.
     */
    static ScaleTo* create(float duration, float s);

    /** 
     * Creates the action with and X factor and a Y factor.
     * @param duration Duration time, in seconds.
     * @param sx Scale factor of x.
     * @param sy Scale factor of y.
     * @return An autoreleased ScaleTo object.
     */
    static ScaleTo* create(float duration, float sx, float sy);

    /** 
     * Creates the action with X Y Z factor.
     * @param duration Duration time, in seconds.
     * @param sx Scale factor of x.
     * @param sy Scale factor of y.
     * @param sz Scale factor of z.
     * @return An autoreleased ScaleTo object.
     */
    static ScaleTo* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual ScaleTo* clone() const override;
    virtual ScaleTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    ScaleTo() {}
    virtual ~ScaleTo() {}

    /** 
     * initializes the action with the same scale factor for X and Y
     * @param duration in seconds
     */
    bool initWithDuration(float duration, float s);
    /** 
     * initializes the action with and X factor and a Y factor 
     * @param duration in seconds
     */
    bool initWithDuration(float duration, float sx, float sy);
    /** 
     * initializes the action with X Y Z factor 
     * @param duration in seconds
     */
    bool initWithDuration(float duration, float sx, float sy, float sz);

protected:
    float _scaleX;
    float _scaleY;
    float _scaleZ;
    float _startScaleX;
    float _startScaleY;
    float _startScaleZ;
    float _endScaleX;
    float _endScaleY;
    float _endScaleZ;
    float _deltaX;
    float _deltaY;
    float _deltaZ;

private:
    DISALLOW_COPY_AND_ASSIGN(ScaleTo);
};

/** @class ScaleBy
 * @brief Scales a Node object a zoom factor by modifying it's scale attribute.
 @warning The physics body contained in Node doesn't support this action.
*/
class ScaleBy : public ScaleTo
{
public:
    /** 
     * Creates the action with the same scale factor for X and Y.
     * @param duration Duration time, in seconds.
     * @param s Scale factor of x and y.
     * @return An autoreleased ScaleBy object.
     */
    static ScaleBy* create(float duration, float s);

    /** 
     * Creates the action with and X factor and a Y factor.
     * @param duration Duration time, in seconds.
     * @param sx Scale factor of x.
     * @param sy Scale factor of y.
     * @return An autoreleased ScaleBy object.
     */
    static ScaleBy* create(float duration, float sx, float sy);

    /** 
     * Creates the action with X Y Z factor.
     * @param duration Duration time, in seconds.
     * @param sx Scale factor of x.
     * @param sy Scale factor of y.
     * @param sz Scale factor of z.
     * @return An autoreleased ScaleBy object.
     */
    static ScaleBy* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual ScaleBy* clone() const override;
    virtual ScaleBy* reverse(void) const override;

public:
    ScaleBy() {}
    virtual ~ScaleBy() {}

private:
    DISALLOW_COPY_AND_ASSIGN(ScaleBy);
};

/** @class Blink
 * @brief Blinks a Node object by modifying it's visible attribute.
*/
class Blink : public ActionInterval
{
public:
    /** 
     * Creates the action.
     * @param duration Duration time, in seconds.
     * @param blinks Blink times.
     * @return An autoreleased Blink object.
     */
    static Blink* create(float duration, int blinks);

    //
    // Overrides
    //
    virtual Blink* clone() const override;
    virtual Blink* reverse() const override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    
public:
    Blink() {}
    virtual ~Blink() {}

    /** 
     * initializes the action 
     * @param duration in seconds
     */
    bool initWithDuration(float duration, int blinks);
    
protected:
    int _times;
    bool _originalState;

private:
    DISALLOW_COPY_AND_ASSIGN(Blink);
};


/** @class FadeTo
 * @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class FadeTo : public ActionInterval
{
public:
    /** 
     * Creates an action with duration and opacity.
     * @param duration Duration time, in seconds.
     * @param opacity A certain opacity, the range is from 0 to 255.
     * @return An autoreleased FadeTo object.
     */
    static FadeTo* create(float duration, GLubyte opacity);

    //
    // Overrides
    //
    virtual FadeTo* clone() const override;
    virtual FadeTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    FadeTo() {}
    virtual ~FadeTo() {}

    /** 
     * initializes the action with duration and opacity 
     * @param duration in seconds
     */
    bool initWithDuration(float duration, GLubyte opacity);

protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
    friend class FadeOut;
    friend class FadeIn;
private:
    DISALLOW_COPY_AND_ASSIGN(FadeTo);
};

/** @class FadeIn
 * @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 */
class FadeIn : public FadeTo
{
public:
    /** 
     * Creates the action.
     * @param d Duration time, in seconds.
     * @return An autoreleased FadeIn object.
     */
    static FadeIn* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeIn* clone() const override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

public:
    FadeIn():_reverseAction(nullptr) {}
    virtual ~FadeIn() {}

private:
    DISALLOW_COPY_AND_ASSIGN(FadeIn);
    FadeTo* _reverseAction;
};

/** @class FadeOut
 * @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
class FadeOut : public FadeTo
{
public:
    /** 
     * Creates the action.
     * @param d Duration time, in seconds.
     */
    static FadeOut* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOut* clone() const  override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

public:
    FadeOut():_reverseAction(nullptr) {}
    virtual ~FadeOut() {}
private:
    DISALLOW_COPY_AND_ASSIGN(FadeOut);
    FadeTo* _reverseAction;
};

/** @class TintTo
 * @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @warning This action doesn't support "reverse"
 @since v0.7.2
*/
class TintTo : public ActionInterval
{
public:
    /** 
     * Creates an action with duration and color.
     * @param duration Duration time, in seconds.
     * @param red Red Color, from 0 to 255.
     * @param green Green Color, from 0 to 255.
     * @param blue Blue Color, from 0 to 255.
     * @return An autoreleased TintTo object.
     */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
    /**
     * Creates an action with duration and color.
     * @param duration Duration time, in seconds.
     * @param color It's a Color3B type.
     * @return An autoreleased TintTo object.
     */
    static TintTo* create(float duration, const Color3B& color);

    //
    // Overrides
    //
    virtual TintTo* clone() const override;
    virtual TintTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    TintTo() {}
    virtual ~TintTo() {}

    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

protected:
    Color3B _to;
    Color3B _from;

private:
    DISALLOW_COPY_AND_ASSIGN(TintTo);
};

/** @class TintBy
 @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
class TintBy : public ActionInterval
{
public:
    /** 
     * Creates an action with duration and color.
     * @param duration Duration time, in seconds.
     * @param deltaRed Delta red color.
     * @param deltaGreen Delta green color.
     * @param deltaBlue Delta blue color.
     * @return An autoreleased TintBy object.
     */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    //
    // Overrides
    //
    virtual TintBy* clone() const override;
    virtual TintBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    TintBy() {}
    virtual ~TintBy() {}

    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

protected:
    GLshort _deltaR;
    GLshort _deltaG;
    GLshort _deltaB;

    GLshort _fromR;
    GLshort _fromG;
    GLshort _fromB;

private:
    DISALLOW_COPY_AND_ASSIGN(TintBy);
};

/** @class DelayTime
 * @brief Delays the action a certain amount of seconds.
*/
class DelayTime : public ActionInterval
{
public:
    /** 
     * Creates the action.
     * @param d Duration time, in seconds.
     * @return An autoreleased DelayTime object.
     */
    static DelayTime* create(float d);

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual DelayTime* reverse() const override;
    virtual DelayTime* clone() const override;

public:
    DelayTime() {}
    virtual ~DelayTime() {}

private:
    DISALLOW_COPY_AND_ASSIGN(DelayTime);
};

/** @class ReverseTime
 * @brief Executes an action in reverse order, from time=duration to time=0
 
 @warning Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
*/
class ReverseTime : public ActionInterval
{
public:
    /** Creates the action.
     *
     * @param action a certain action.
     * @return An autoreleased ReverseTime object.
     */
    static ReverseTime* create(FiniteTimeAction *action);

    //
    // Overrides
    //
    virtual ReverseTime* reverse() const override;
    virtual ReverseTime* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    
public:
    ReverseTime();
    virtual ~ReverseTime(void);

    /** initializes the action */
    bool initWithAction(FiniteTimeAction *action);

protected:
    FiniteTimeAction *_other;

private:
    DISALLOW_COPY_AND_ASSIGN(ReverseTime);
};

#if 0
class Texture2D;
/** @class Animate
 * @brief Animates a Node given the name of an Animation.
 */
class Animate : public ActionInterval
{
public:
    /** Creates the action with an Animation and will restore the original frame when the animation is over.
     *
     * @param animation A certain animation.
     * @return An autoreleased Animate object.
     */
    static Animate* create(Animation *animation);

    /** Sets the Animation object to be animated 
     * 
     * @param animation certain animation.
     */
    void setAnimation( Animation* animation );
    /** returns the Animation object that is being animated 
     *
     * @return Gets the animation object that is being animated.
     */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    /**
     * Gets the index of Node frame currently displayed.
     * @return int  the index of Node frame currently displayed.
     */
    int getCurrentFrameIndex() { return _currFrameIndex; }
    //
    // Overrides
    //
    virtual Animate* clone() const override;
    virtual Animate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param t In seconds.
     */
    virtual void update(float t) override;
    
public:
    Animate();
    virtual ~Animate();

    /** initializes the action with an Animation and will restore the original frame when the animation is over */
    bool initWithAnimation(Animation *animation);

protected:
    std::vector<float>* _splitTimes;
    int             _nextFrame;
    NodeFrame*    _origFrame;
    int _currFrameIndex;
    unsigned int    _executedLoops;
    Animation*      _animation;

    EventCustom*    _frameDisplayedEvent;
    AnimationFrame::DisplayedEventInfo _frameDisplayedEventInfo;
private:
    DISALLOW_COPY_AND_ASSIGN(Animate);
};
#endif

/** @class TargetedAction
 * @brief Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 */
class TargetedAction : public ActionInterval
{
public:
    /** Create an action with the specified action and forced target.
     * 
     * @param target The target needs to override.
     * @param action The action needs to override.
     * @return An autoreleased TargetedAction object.
     */
    static TargetedAction* create(Node* target, FiniteTimeAction* action);

    /** Sets the target that the action will be forced to run with.
     *
     * @param forcedTarget The target that the action will be forced to run with.
     */
    void setForcedTarget(Node* forcedTarget);
    /** returns the target that the action is forced to run with. 
     *
     * @return The target that the action is forced to run with.
     */
    Node* getForcedTarget() { return _forcedTarget; }
    const Node* getForcedTarget() const { return _forcedTarget; }

    //
    // Overrides
    //
    virtual TargetedAction* clone() const override;
    virtual TargetedAction* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    
public:
    TargetedAction();
    virtual ~TargetedAction();

    /** Init an action with the specified action and forced target */
    bool initWithTarget(Node* target, FiniteTimeAction* action);

protected:
    FiniteTimeAction* _action;
    Node* _forcedTarget;

private:
    DISALLOW_COPY_AND_ASSIGN(TargetedAction);
};

/**
 * @class ActionFloat
 * @brief Action used to animate any value in range [from,to] over specified time interval
 */
class ActionFloat : public ActionInterval
{
public:
    /**
     *  Callback function used to report back result
     */
    typedef std::function<void(float value)> ActionFloatCallback;

    /**
     * Creates FloatAction with specified duration, from value, to value and callback to report back
     * results
     * @param duration of the action
     * @param from value to start from
     * @param to value to be at the end of the action
     * @param callback to report back result
     *
     * @return An autoreleased ActionFloat object
     */
    static ActionFloat* create(float duration, float from, float to, ActionFloatCallback callback);

    /**
     * Overridden ActionInterval methods
     */
    void startWithTarget(Node* target) override;
    void update(float delta) override;
    ActionFloat* reverse() const override;
    ActionFloat* clone() const override;

public:
    ActionFloat() {};
    virtual ~ActionFloat() {};

    bool initWithDuration(float duration, float from, float to, ActionFloatCallback callback);

protected:
    /* From value */
    float _from;
    /* To value */
    float _to;
    /* delta time */
    float _delta;

    /* Callback to report back results */
    ActionFloatCallback _callback;
private:
    DISALLOW_COPY_AND_ASSIGN(ActionFloat);
};


class CubeFlip : public ActionInterval
{
public:

    static CubeFlip* create(float duration, int _directionSize, int _direction);

	virtual CubeFlip* clone() const override;
    //virtual CubeFlip* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    
public:
    CubeFlip() {}
    virtual ~CubeFlip() {}

    /** initializes the action */
    bool initWithDuration(float duration, int _directionSize, int _direction);
	bool initWithDuration(float duration, const Vec3& deltaPosition, int _directionSize, int _direction);

protected:
    V3F_C4B_T2F _positionDelta[4];
    V3F_C4B_T2F _startPosition[4];
    V3F_C4B_T2F _previousPosition[4];
	int directionSize;
	int direction;
private:
    DISALLOW_COPY_AND_ASSIGN(CubeFlip);
};


#endif //__ACTION_INTERVAL_ACTION_H__
