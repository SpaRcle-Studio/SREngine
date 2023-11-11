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
#include <Utils/Types/Marshal.h>
#include <Utils/Debug.h>

#define SR_REGISTER_TYPE_TRAITS_PROPERTY(className)                                                                     \
    static SR_UTILS_NS::Property* AllocateBase() { return (SR_UTILS_NS::Property*)new className(); }                    \

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(PropertyPublicity, uint8_t,
        ReadOnly, Private, Public
    );

    class Property : public SR_UTILS_NS::NonCopyable {
        using ActiveConditionFn = SR_HTYPES_NS::Function<bool()>;
    public:
        Property& SetPublicity(PropertyPublicity publicity) { m_publicity = publicity; return *this; }
        Property& SetActiveCondition(ActiveConditionFn value) { m_activeCondition = std::move(value); return *this; }
        Property& SetName(SR_UTILS_NS::StringAtom value) { m_name = value; return *this; }
        Property& SetWidth(float_t value) { m_width = value; return *this; }
        Property& SetReadOnly() { m_publicity = PropertyPublicity::ReadOnly; return *this; }
        Property& SetSameLine() { m_sameLine = true; return *this; }
        Property& SetDontSave() { m_dontSave = true; return *this; }

        SR_NODISCARD PropertyPublicity GetPublicity() const noexcept { return m_publicity; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept { return m_name; }
        SR_NODISCARD float_t GetWidth() const noexcept { return m_width; }
        SR_NODISCARD bool IsSameLine() const noexcept { return m_sameLine; }

        SR_NODISCARD bool IsActive() const noexcept;

    private:
        ActiveConditionFn m_activeCondition;
        PropertyPublicity m_publicity = PropertyPublicity::Public;
        SR_UTILS_NS::StringAtom m_description;
        SR_UTILS_NS::StringAtom m_name;

        bool m_dontSave = false;
        bool m_sameLine = false;
        float_t m_width = 70.f;

    };

    class ExternalProperty : public Property {
        using PropertyGetterFn = SR_HTYPES_NS::Function<Property*()>;
    public:
        SR_NODISCARD const PropertyGetterFn& GetPropertyGetter() const noexcept { return m_getter; }
        ExternalProperty& SetPropertyGetter(const PropertyGetterFn& value) noexcept { m_getter = value; return *this; }

    private:
        PropertyGetterFn m_getter;

    };

    class LabelProperty : public Property {
    public:
        LabelProperty& SetLabel(const SR_UTILS_NS::StringAtom& value) { m_label = value; return *this; }
        LabelProperty& SetColor(const SR_MATH_NS::FColor& value) { m_color = value; return *this; }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetLabel() const noexcept { return m_label; }
        SR_NODISCARD SR_MATH_NS::FColor GetColor() const noexcept { return m_color; }

    private:
        SR_UTILS_NS::StringAtom m_label;
        SR_MATH_NS::FColor m_color;

    };
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTY_H
