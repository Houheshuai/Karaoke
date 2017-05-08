#ifndef __EventFocus_H_
#define __EventFocus_H_

#include "Event/Event.h"

namespace GUI {
    class Widget;
}

/** @class EventFocus
 * @brief Focus event.
 */
class EventFocus : public Event
{
public:
    /** Constructor.
     *
     * @param widgetLoseFocus The widget which lose focus.
     * @param widgetGetFocus The widget which get focus.
     * @js ctor
     */
    EventFocus(GUI::Widget* widgetLoseFocus, GUI::Widget* widgetGetFocus);
    
private:
    GUI::Widget *_widgetGetFocus;
    GUI::Widget *_widgetLoseFocus;
    
    friend class EventListenerFocus;
};


#endif //__EventFocus_H_
