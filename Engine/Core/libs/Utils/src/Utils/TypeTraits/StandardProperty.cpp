//
// Created by Monika on 07.11.2023.
//

#include <Utils/TypeTraits/StandardProperty.h>

namespace SR_UTILS_NS {
    PathProperty& PathProperty::SetPath(const Path& path) noexcept {
        if (m_setter) {
            m_setter(path);
        }
        return *this;
    }

    SR_UTILS_NS::Path PathProperty::GetPath() const noexcept {
        return m_getter ? m_getter() : SR_UTILS_NS::Path();
    }

    SR_UTILS_NS::StringAtom EnumProperty::GetEnum() const noexcept {
        return m_getter ? m_getter() : SR_UTILS_NS::StringAtom();
    }

    EnumProperty& EnumProperty::SetEnum(const StringAtom& value) noexcept {
        if (m_setter) {
            m_setter(value);
        }
        return *this;
    }
}