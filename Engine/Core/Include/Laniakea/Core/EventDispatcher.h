#pragma once
#include "Event.h"
#include <functional>
// from https://github.com/TheCherno/Hazel

typedef size_t EventHandle;

namespace lk {
    class LANIAKEA_CORE_API EventDispatcher {
    public:
        using Callback = std::function<bool ( Event &)>;

        bool Dispatch ( Event & e );

        EventHandle Bind (  Callback cb );

        bool Unbind ( const EventHandle & handle );

/*
        const Event & GetEvent () const;

        void SetEvent ( Event & e );
*/

    private:
        std::vector <Callback> m_BoundCallbacks;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.ToString();
    }
} // end namespace lk
