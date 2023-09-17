#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "Event.h"
#include "eventpp/eventdispatcher.h"



//https://github.com/stwe/MDCII/blob/main/src/event/EventManager.h


//-------------------------------------------------
// EventManager
//-------------------------------------------------

namespace fts::event
{
    /**
     * Static event handling.
     */
    class EventManager
    {
    public:
        //-------------------------------------------------
        // Member
        //-------------------------------------------------

        inline static eventpp::EventDispatcher<MdciiEventType, void(const MdciiEvent&)> event_dispatcher;

        //-------------------------------------------------
        // Ctors. / Dtor.
        //-------------------------------------------------

        EventManager(const EventManager& t_other) = delete;
        EventManager(EventManager&& t_other) noexcept = delete;
        EventManager& operator=(const EventManager& t_other) = delete;
        EventManager& operator=(EventManager&& t_other) noexcept = delete;

        //-------------------------------------------------
        // Init
        //-------------------------------------------------

        // static void SetKeyboardGlfwCallbacks(GLFWwindow* t_windowHandle);
        // static void SetMouseGlfwCallbacks(GLFWwindow* t_windowHandle);
    protected:

    private:
        //-------------------------------------------------
        // Ctors. / Dtor.
        //-------------------------------------------------

        EventManager() = default;
        ~EventManager() noexcept = default;
    };
}


#endif // __EVENTMANAGER_H__