#include "EventDispatcher.h"
// from https://github.com/TheCherno/Hazel
namespace lk {
    EventDispatcher::EventDispatcher(Event &event)
            : m_Event(event) {
    }
} // end namespace lk