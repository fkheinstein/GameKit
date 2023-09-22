#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include <Events/Event.h>
#include <eventpp/eventdispatcher.h>


//https://github.com/stwe/MDCII/blob/main/src/event/EventManager.h


namespace fts::evt
{
    /**
     * Static event handling.
     */
    class EventManager
    {
    public:
        //inline static eventpp::EventDispatcher<FtsEventType, void(const FtsEvent&)> event_dispatcher;


        inline static eventpp::EventDispatcher<EventType, void(const Event&), EventPolicies> eventDispatcher;

        //-------------------------------------------------
        // Ctors. / Dtor.
        //-------------------------------------------------

        EventManager(const EventManager& t_other) = delete;
        EventManager(EventManager&& t_other) noexcept = delete;
        EventManager& operator=(const EventManager& t_other) = delete;
        EventManager& operator=(EventManager&& t_other) noexcept = delete;


    private:
        //-------------------------------------------------
        // Ctors. / Dtor.
        //-------------------------------------------------
        EventManager() = default;
        ~EventManager() noexcept = default;
    };
}


#endif // __EVENTMANAGER_H__