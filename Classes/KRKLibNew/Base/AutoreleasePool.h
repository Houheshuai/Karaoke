#ifndef __AUTORELEASEPOOL_H__
#define __AUTORELEASEPOOL_H__

#include <vector>
#include <string>
#include "Base/Ref.h"

class AutoreleasePool
{
public:
    /**
     * @warning Don't create an autorelease pool in heap, create it in stack.
     * @js NA
     * @lua NA
     */
    AutoreleasePool();
    
    /**
     * Create an autorelease pool with specific name. This name is useful for debugging.
     * @warning Don't create an autorelease pool in heap, create it in stack.
     * @js NA
     * @lua NA
     *
     * @param name The name of created autorelease pool.
     */
    AutoreleasePool(const std::string &name);
    
    /**
     * @js NA
     * @lua NA
     */
    ~AutoreleasePool();

    /**
     * Add a given object to this autorelease pool.
     *
     * The same object may be added several times to an autorelease pool. When the
     * pool is destructed, the object's `Ref::release()` method will be called
     * the same times as it was added.
     *
     * @param object    The object to be added into the autorelease pool.
     * @js NA
     * @lua NA
     */
    void addObject(Ref *object);

    /**
     * Clear the autorelease pool.
     *
     * It will invoke each element's `release()` function.
     *
     * @js NA
     * @lua NA
     */
    void clear();
    
    /**
     * Checks whether the autorelease pool contains the specified object.
     *
     * @param object The object to be checked.
     * @return True if the autorelease pool contains the object, false if not
     * @js NA
     * @lua NA
     */
    bool contains(Ref* object) const;

    /**
     * Dump the objects that are put into the autorelease pool. It is used for debugging.
     *
     * The result will look like:
     * Object pointer address     object id     reference count
     *
     * @js NA
     * @lua NA
     */
    void dump();
    
private:
    /**
     * The underlying array of object managed by the pool.
     *
     * Although Array retains the object once when an object is added, proper
     * Ref::release() is called outside the array to make sure that the pool
     * does not affect the managed object's reference count. So an object can
     * be destructed properly by calling Ref::release() even if the object
     * is in the pool.
     */
    std::vector<Ref*> _managedObjectArray;
    std::string _name;
    
};

class PoolManager
{
public:

    static PoolManager* getInstance();
    
    static void destroyInstance();
    
    /**
     * Get current auto release pool, there is at least one auto release pool that created by engine.
     * You can create your own auto release pool at demand, which will be put into auto release pool stack.
     */
    AutoreleasePool *getCurrentPool() const;

    bool isObjectInPools(Ref* obj) const;


    friend class AutoreleasePool;
    
private:
    PoolManager();
    ~PoolManager();
    
    void push(AutoreleasePool *pool);
    void pop();
    
    static PoolManager* s_singleInstance;
    
    std::vector<AutoreleasePool*> _releasePoolStack;
};

#endif //__AUTORELEASEPOOL_H__
