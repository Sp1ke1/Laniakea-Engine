#pragma once
#include "Event.h"

// from https://github.com/TheCherno/Hazel

namespace lk {
    class LANIAKEA_API EventDispatcher {
    public:
        EventDispatcher(Event &event);

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F &func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled |= func(static_cast<T &>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.ToString();
    }
} // end namespace lk
