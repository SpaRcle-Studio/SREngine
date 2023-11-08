//
// Created by Monika on 07.11.2023.
//

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    bool Property::IsVisible() const noexcept {
        if (!m_visibleCondition) {
            return true;
        }
        return m_visibleCondition();
    }
}