#ifndef __CustomEvent_H_
#define __CustomEvent_H_

#include <string>
#include "Event/Event.h"


/** @class EventCustom
 * @brief Custom event.
 */
class EventCustom : public Event
{
public:
    /** Constructor.
     *
     * @param eventName A given name of the custom event.
     * @js ctor
     */
    EventCustom(const std::string& eventName);
    
    /** Sets user data.
     *
     * @param data The user data pointer, it's a void*.
     */
    inline void setUserData(void* data) { _userData = data; };
    
    /** Gets user data.
     *
     * @return The user data pointer, it's a void*.
     */
    inline void* getUserData() const { return _userData; };
    
    /** Gets event name.
     *
     * @return The name of the event.
     */
    inline const std::string& getEventName() const { return _eventName; };
protected:
    void* _userData;       ///< User data
    std::string _eventName;
};


#endif //__CustomEvent_H_
