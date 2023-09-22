#include <spch.h>


#include <Events/Event.h>


namespace fts::evt {
 EventType EventPolicies::getEvent(const Event& e) {
        return e.GetEventType();
    }
}