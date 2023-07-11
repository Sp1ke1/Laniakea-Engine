#include "EventDispatcher.h"
// from https://github.com/TheCherno/Hazel
namespace lk {
    EventHandle EventDispatcher::Bind( EventDispatcher::Callback cb )
    {
        for (auto i = 0; i < m_BoundCallbacks.size(); i ++ )
        {
            if (m_BoundCallbacks[i] == nullptr )
            {
                m_BoundCallbacks[i] = cb;
                return i;
            }
        }
        m_BoundCallbacks.push_back(cb );
        return m_BoundCallbacks.size() - 1;
    }

    bool EventDispatcher::Unbind( const EventHandle & handle)
    {
        if (m_BoundCallbacks.size() >= handle )
            return false;
        m_BoundCallbacks[handle] = nullptr;
        return true;
    }

    bool EventDispatcher::Dispatch( Event & e ) {
        bool Handled = false ;
        for ( auto & cb : m_BoundCallbacks )
        {
            Handled |= cb ( e );
        }
        return Handled;
    }

/*    const Event &EventDispatcher::GetEvent() const {
        return m_Event;
    }

    void EventDispatcher::SetEvent(Event &e) {
        m_Event = e;
    }
*/
} // end namespace lk