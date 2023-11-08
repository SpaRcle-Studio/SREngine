//
// Created by Monika on 07.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_PROPERTY_H
#define SR_ENGINE_TYPE_TRAITS_PROPERTY_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Common/TypeInfo.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(PropertyPublicity, uint8_t,
        ReadOnly, Private, Public
    );

    class Property : SR_UTILS_NS::NonCopyable {
    public:
        Property& SetPublicity(PropertyPublicity publicity) { m_publicity = publicity; return *this; }
        Property& SetName(SR_UTILS_NS::StringAtom name) { m_name = name; return *this; }
        Property& SetWidth(float_t value) { m_width = value; return *this; }
        Property& SetDrag(float_t value) { m_drag = value; return *this; }
        Property& SetReadOnly() { m_publicity = PropertyPublicity::ReadOnly; return *this; }

        SR_NODISCARD PropertyPublicity GetPublicity() const noexcept { return m_publicity; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept { return m_name; }
        SR_NODISCARD float_t GetWidth() const noexcept { return m_width; }
        SR_NODISCARD float_t GetDrag() const noexcept { return m_drag; }

    private:
        PropertyPublicity m_publicity = PropertyPublicity::Public;
        SR_UTILS_NS::StringAtom m_description;
        SR_UTILS_NS::StringAtom m_name;

        float_t m_width = 70.f;
        float_t m_drag = 1.f;

    };
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTY_H
