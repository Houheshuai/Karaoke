#ifndef __AccelerometerEvent_H_
#define __AccelerometerEvent_H_

#include "Event/Event.h"
#include "Base/Types.h"

/** @class EventAcceleration
 * @brief Accelerometer event.
 */
class EventAcceleration : public Event
{
public:
    /** Constructor.
     *
     * @param acc A given Acceleration.
     */
    EventAcceleration(const Acceleration& acc);
    
private:
    Acceleration _acc;
    friend class EventListenerAcceleration;
};


#endif //__AccelerometerEvent_H_
