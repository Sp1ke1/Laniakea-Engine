//
// Created by NB01 on 6/10/2023.
//

#include "Event.h"

namespace lk {
    std::string Event::ToString() const { return GetName(); }

    bool Event::IsInCategory(EventCategory category) {
        return GetCategoryFlags() & category;
    }
} // end namespace lk