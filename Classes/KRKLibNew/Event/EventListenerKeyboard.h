#ifndef __KeyboardEventListener_H_
#define __KeyboardEventListener_H_

#include "Event/EventListener.h"
#include "Event/EventKeyboard.h"

class Event;

/** @class EventListenerKeyboard
 * @brief Keyboard event listener.
 * @js cc._EventListenerKeyboard
 */
class EventListenerKeyboard : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** Create a keyboard event listener.
     * 
     * @return An autoreleased EventListenerKeyboard object.
     */
    static EventListenerKeyboard* create();
    
    /// Overrides
    virtual EventListenerKeyboard* clone() override;
    virtual bool checkAvailable() override;
    
    std::function<void(EventKeyboard::KeyCode, Event*)> onKeyPressed;
    std::function<void(EventKeyboard::KeyCode, Event*)> onKeyReleased;

    EventListenerKeyboard();
    bool init();
};


#endif //__KeyboardEventListener_H_
