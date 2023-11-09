//
// Created by Monika on 07.11.2023.
//

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    bool Property::IsActive() const noexcept {
        if (!m_activeCondition) {
            return true;
        }
        return m_activeCondition();
    }
}