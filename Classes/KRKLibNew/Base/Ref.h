#ifndef __BASE_REF_H__
#define __BASE_REF_H__

#define REF_LEAK_DETECTION 0

/** 
  * Interface that defines how to clone an Ref.
  * @lua NA
  * @js NA
  */
class Clonable
{
public:
    /** Returns a copy of the Ref. */
    virtual Clonable* clone() const = 0;
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Clonable() {};
};

/**
 * Ref is used for reference count management. If a class inherits from Ref,
 * then it is easy to be shared in different places.
 * @js NA
 */
class Ref
{
public:
    /**
     * Retains the ownership.
     *
     * This increases the Ref's reference count.
     *
     * @see release, autorelease
     * @js NA
     */
    void retain();

    /**
     * Releases the ownership immediately.
     *
     * This decrements the Ref's reference count.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @see retain, autorelease
     * @js NA
     */
    void release();

	Ref* autorelease();

    /**
     * Returns the Ref's current reference count.
     *
     * @returns The Ref's reference count.
     * @js NA
     */
    unsigned int getReferenceCount() const;

protected:
    /**
     * Constructor
     *
     * The Ref's reference count is 1 after construction.
     * @js NA
     */
    Ref();

public:
    /**
     * Destructor
     *
     * @js NA
     * @lua NA
     */
    virtual ~Ref();

protected:
    /// count of references
    unsigned int _referenceCount;

	friend class AutoreleasePool;

    // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

class Sprite;
typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Sprite*);
typedef void (Ref::*SEL_CallFuncND)(Sprite*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define CALLFUNC_SELECTOR(_SELECTOR) static_cast<SEL_CallFunc>(&_SELECTOR)
#define CALLFUNCN_SELECTOR(_SELECTOR) static_cast<SEL_CallFuncN>(&_SELECTOR)
#define CALLFUNCND_SELECTOR(_SELECTOR) static_cast<SEL_CallFuncND>(&_SELECTOR)
#define CALLFUNCO_SELECTOR(_SELECTOR) static_cast<SEL_CallFuncO>(&_SELECTOR)
#define MENU_SELECTOR(_SELECTOR) static_cast<SEL_MenuHandler>(&_SELECTOR)
#define SCHEDULE_SELECTOR(_SELECTOR) static_cast<SEL_SCHEDULE>(&_SELECTOR)

#endif //
