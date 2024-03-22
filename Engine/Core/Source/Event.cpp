//
// Created by NB01 on 6/10/2023.
//

#include "Laniakea/Core/Event.h"

namespace lk {
    std::string Event::ToString() const { return GetName(); }

    bool Event::IsInCategory(EventCategory category) {
        return static_cast<bool> ( static_cast<int> ( GetCategoryFlags() & category ) ); // wtf is this piece of shit?
    }
} // end namespace lk