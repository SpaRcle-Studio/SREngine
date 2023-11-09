//
// Created by Monika on 07.11.2023.
//

#include <Utils/TypeTraits/StandardProperty.h>

namespace SR_UTILS_NS {
    void PathProperty::SetPath(const Path& path) noexcept {
        if (m_setter) {
            m_setter(path);
        }
    }

    SR_UTILS_NS::Path PathProperty::GetPath() const noexcept {
        return m_getter ? m_getter() : SR_UTILS_NS::Path();
    }
}