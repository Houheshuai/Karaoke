#ifndef __EventListenerFocus_H_
#define __EventListenerFocus_H_

#include "Event/EventListener.h"

namespace GUI {
    class Widget;
}

/** @class EventListenerFocus
 * @brief Focus event listener.
 */
class EventListenerFocus : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** Create a focus event listener.
     *
     * @return An autoreleased EventListenerFocus object.
     */
    static EventListenerFocus* create();
    
    /** Destructor.
     * @js NA
     */
    virtual ~EventListenerFocus();
    
    /// Overrides
    virtual EventListenerFocus* clone() override;
    virtual bool checkAvailable() override;
    //
    
public:
    std::function<void(GUI::Widget*, GUI::Widget*)> onFocusChanged;
    
    EventListenerFocus();
    bool init();
    
    friend class EventDispatcher;
};


#endif //__EventListenerFocus_H_
