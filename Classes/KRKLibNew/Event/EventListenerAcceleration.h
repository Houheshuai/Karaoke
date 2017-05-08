#ifndef __AccelerometerListener_H_
#define __AccelerometerListener_H_

#include "Event/EventListener.h"
#include "Base/Types.h"

/** @class EventListenerAcceleration
 * @brief Acceleration event listener.
 * @js NA
 */
class EventListenerAcceleration : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** Create a acceleration EventListener.
     *
     * @param callback The acceleration callback method.
     * @return An autoreleased EventListenerAcceleration object.
     */
    static EventListenerAcceleration* create(const std::function<void(Acceleration*, Event*)>& callback);
    
    /** Destructor.
     */
    virtual ~EventListenerAcceleration();
    
    /// Overrides
    virtual EventListenerAcceleration* clone() override;
    virtual bool checkAvailable() override;
    
    EventListenerAcceleration();
    
    bool init(const std::function<void(Acceleration*, Event* event)>& callback);
    
private:
    std::function<void(Acceleration*, Event*)> onAccelerationEvent;
    
    friend class LuaEventListenerAcceleration;
};


#endif //__AccelerometerListener_H_
