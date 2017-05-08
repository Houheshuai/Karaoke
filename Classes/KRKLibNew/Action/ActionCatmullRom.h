#ifndef __ACTION_CATMULLROM_H__
#define __ACTION_CATMULLROM_H__

#include <vector>

#include "Action/ActionInterval.h"
#include "Math/Geometry.h"

class Node;

/** An Array that contain control points.
 * Used by CardinalSplineTo and (By) and CatmullRomTo (and By) actions.
 * @ingroup Actions
 * @js NA
 */
class PointArray : public Ref, public Clonable
{
public:

    /** Creates and initializes a Points array with capacity.
     * @js NA
     * @param capacity The size of the array.
     */
    static PointArray* create(long capacity);

    /**
     * @js NA
     * @lua NA
     */
    virtual ~PointArray();
    /**
     * @js NA
     * @lua NA
     */
    PointArray();

    /** Initializes a Catmull Rom config with a capacity hint.
     *
     * @js NA
     * @param capacity The size of the array.
     * @return True.
     */
    bool initWithCapacity(long capacity);

    /** Appends a control point.
     *
     * @js NA
     * @param controlPoint A control point.
     */
    void addControlPoint(Vec2 controlPoint);

    /** Inserts a controlPoint at index.
     *
     * @js NA
     * @param controlPoint A control point.
     * @param index Insert the point to array in index.
     */
    void insertControlPoint(Vec2 &controlPoint, long index);

    /** Replaces an existing controlPoint at index.
     *
     * @js NA
     * @param controlPoint A control point.
     * @param index Replace the point to array in index.
     */
    void replaceControlPoint(Vec2 &controlPoint, long index);

    /** Get the value of a controlPoint at a given index.
     *
     * @js NA
     * @param index Get the point in index.
     * @return A Vec2.
     */
    Vec2 getControlPointAtIndex(long index);

    /** Deletes a control point at a given index
     *
     * @js NA
     * @param index Remove the point in index.
     */
    void removeControlPointAtIndex(long index);

    /** Returns the number of objects of the control point array.
     *
     * @js NA
     * @return The number of objects of the control point array.
     */
    long count() const;

    /** Returns a new copy of the array reversed. User is responsible for releasing this copy.
     *
     * @js NA
     * @return A new copy of the array reversed.
     */
    PointArray* reverse() const;

    /** Reverse the current control point array inline, without generating a new one.
     * @js NA
     */
    void reverseInline();
    /**
     * @js NA
     * @lua NA
     */
    virtual PointArray* clone() const;
    /**
     * @js NA
     */
    const std::vector<Vec2*>* getControlPoints() const;
    /**
     * @js NA
     */
    void setControlPoints(std::vector<Vec2*> *controlPoints);
private:
    /** Array that contains the control points. */
    std::vector<Vec2*> *_controlPoints;
};

/** @class CardinalSplineTo
 * Cardinal Spline path.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @ingroup Actions
 */
class CardinalSplineTo : public ActionInterval
{
public:

    /** Creates an action with a Cardinal Spline array of points and tension.
     * @param duration In seconds.
     * @param points An PointArray.
     * @param tension Goodness of fit.
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var t,var table)
     * In lua: local create(local t, local table)
     * @endcode
     */
    static CardinalSplineTo* create(float duration, PointArray* points, float tension);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CardinalSplineTo();
    /**
     * @js ctor
     * @lua NA
     */
    CardinalSplineTo();

    /** 
     * Initializes the action with a duration and an array of points.
     *
     * @param duration In seconds.
     * @param points An PointArray.
     * @param tension Goodness of fit.
     */
    bool initWithDuration(float duration, PointArray* points, float tension);
    /** It will update the target position and change the _previousPosition to newPos
     *
     * @param newPos The new position.
     */
    virtual void updatePosition(Vec2 &newPos);
    /** Return a PointArray.
     *
     * @return A PointArray.
     */
    inline PointArray* getPoints() { return _points; }
    /**
     * @js NA
     * @lua NA
     */
    inline void setPoints(PointArray* points)
    {
        SAFE_RETAIN(points);
        SAFE_RELEASE(_points);
        _points = points;
    }

    // Overrides
    virtual CardinalSplineTo *clone() const override;
    virtual CardinalSplineTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;

protected:
    /** Array of control points */
    PointArray *_points;
    float _deltaT;
    float _tension;
    Vec2	_previousPosition;
    Vec2	_accumulatedDiff;
};

/** @class CardinalSplineBy
 * Cardinal Spline path.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @ingroup Actions
 */
class CardinalSplineBy : public CardinalSplineTo
{
public:

    /** Creates an action with a Cardinal Spline array of points and tension.
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var t,var table).
     * In lua: local create(local t, local table).
     * @param duration In seconds.
     * @param point An PointArray.
     * @param tension Goodness of fit.
     * @endcode
     */
    static CardinalSplineBy* create(float duration, PointArray* points, float tension);

    CardinalSplineBy();

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void updatePosition(Vec2 &newPos) override;
    virtual CardinalSplineBy *clone() const override;
    virtual CardinalSplineBy* reverse() const override;

protected:
    Vec2 _startPosition;
};

/** @class CatmullRomTo
 * An action that moves the target with a CatmullRom curve to a destination point.
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @ingroup Actions
 */
class CatmullRomTo : public CardinalSplineTo
{
public:

    /** Creates an action with a Cardinal Spline array of points and tension.
     * @param dt In seconds.
     * @param points An PointArray.
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var dt,var table).
     * In lua: local create(local dt, local table).
     * @endcode
     */
    static CatmullRomTo* create(float dt, PointArray* points);

    /** 
     * Initializes the action with a duration and an array of points.
     *
     * @param dt In seconds.
     * @param points An PointArray.
     */
    bool initWithDuration(float dt, PointArray* points);

    // Override
    virtual CatmullRomTo *clone() const override;
    virtual CatmullRomTo *reverse() const override;
};

/** @class CatmullRomBy
 * An action that moves the target with a CatmullRom curve by a certain distance.
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @ingroup Actions
 */
class CatmullRomBy : public CardinalSplineBy
{
public:
    /** Creates an action with a Cardinal Spline array of points and tension.
     * @param dt In seconds.
     * @param points An PointArray.
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var dt,var table).
     * In lua: local create(local dt, local table).
     * @endcode
     */
    static CatmullRomBy* create(float dt, PointArray* points);

    /** Initializes the action with a duration and an array of points.
     *
     * @param dt In seconds.
     * @param points An PointArray.
     */
    bool initWithDuration(float dt, PointArray* points);

    // Override
    virtual CatmullRomBy *clone() const override;
    virtual CatmullRomBy *reverse() const override;

};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern Vec2 CardinalSplineAt(Vec2 &p0, Vec2 &p1, Vec2 &p2, Vec2 &p3, float tension, float t);


#endif // __ACTION_CATMULLROM_H__
