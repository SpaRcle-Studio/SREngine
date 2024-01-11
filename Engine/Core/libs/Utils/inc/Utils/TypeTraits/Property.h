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

#define SR_REGISTER_TYPE_TRAITS_PROPERTY(className, version)                                                            \
    static SR_UTILS_NS::Property* AllocateBase() { return (SR_UTILS_NS::Property*)new className(); }                    \
    SR_INLINE_STATIC const uint16_t VESION = version;                                                                   \
    SR_INLINE_STATIC const SR_UTILS_NS::StringAtom PROPERTY_TYPE_NAME = #className;                                     \
    SR_NODISCARD SR_UTILS_NS::StringAtom GetPropertyTypeName() const noexcept final { return PROPERTY_TYPE_NAME; }      \
    SR_NODISCARD uint16_t GetPropertyVersion() const noexcept final { return VESION; }                                  \

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(PropertyPublicity, uint8_t,
        ReadOnly, Private, Public
    );

    class Property : public SR_UTILS_NS::NonCopyable {
    public:
        using Base = Property;
        using ActiveConditionFn = SR_HTYPES_NS::Function<bool()>;
        using MarshalPtr = SR_HTYPES_NS::Marshal::Ptr;
        using MarshalRef = SR_HTYPES_NS::Marshal&;
        using MarshalUniquePtr = std::unique_ptr<SR_HTYPES_NS::Marshal>;
    public:
        Property() = default;

        Property(Property&& other) noexcept
            : m_activeCondition(SR_EXCHANGE(other.m_activeCondition, ActiveConditionFn()))
            , m_publicity(SR_EXCHANGE(other.m_publicity, { }))
            , m_description(SR_EXCHANGE(other.m_description, { }))
            , m_name(SR_EXCHANGE(other.m_name, { }))
            , m_dontSave(SR_EXCHANGE(other.m_dontSave, { }))
            , m_sameLine(SR_EXCHANGE(other.m_sameLine, { }))
            , m_width(SR_EXCHANGE(other.m_width, { }))
        { }

        Property& operator=(Property&& other) noexcept {
            m_activeCondition = SR_EXCHANGE(other.m_activeCondition, ActiveConditionFn());
            m_publicity = SR_EXCHANGE(other.m_publicity, { });
            m_description = SR_EXCHANGE(other.m_description, { });
            m_name = SR_EXCHANGE(other.m_name, { });
            m_dontSave = SR_EXCHANGE(other.m_dontSave, { });
            m_sameLine = SR_EXCHANGE(other.m_sameLine, { });
            m_width = SR_EXCHANGE(other.m_width, { });
            return *this;
        }

        virtual void SaveProperty(MarshalRef marshal) const noexcept { /** nothing */ }
        virtual void LoadProperty(MarshalRef marshal) noexcept { /** nothing */ }

        Property& SetPublicity(PropertyPublicity publicity) { m_publicity = publicity; return *this; }
        Property& SetActiveCondition(ActiveConditionFn value) { m_activeCondition = std::move(value); return *this; }
        Property& SetName(SR_UTILS_NS::StringAtom value) { m_name = value; return *this; }
        Property& SetWidth(float_t value) { m_width = value; return *this; }
        Property& SetReadOnly() { m_publicity = PropertyPublicity::ReadOnly; return *this; }
        Property& SetSameLine() { m_sameLine = true; return *this; }
        Property& SetDontSave() { m_dontSave = true; return *this; }

        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetPropertyTypeName() const noexcept = 0;
        SR_NODISCARD virtual uint16_t GetPropertyVersion() const noexcept = 0;
        SR_NODISCARD PropertyPublicity GetPublicity() const noexcept { return m_publicity; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept { return m_name; }
        SR_NODISCARD float_t GetWidth() const noexcept { return m_width; }
        SR_NODISCARD bool IsSameLine() const noexcept { return m_sameLine; }
        SR_NODISCARD bool IsDontSave() const noexcept { return m_dontSave; }

        SR_NODISCARD bool IsActive() const noexcept;

    protected:
        SR_NODISCARD MarshalUniquePtr AllocatePropertyBlock() const;
        SR_NODISCARD MarshalUniquePtr LoadPropertyBase(MarshalRef marshal) const;

        void SavePropertyBase(MarshalRef marshal, MarshalUniquePtr pBlock) const;

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
        SR_REGISTER_TYPE_TRAITS_PROPERTY(ExternalProperty, 1000)
        using PropertyGetterFn = SR_HTYPES_NS::Function<Property*()>;
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        SR_NODISCARD Property* GetExternalProperty() const noexcept;

        SR_NODISCARD const PropertyGetterFn& GetPropertyGetter() const noexcept { return m_getter; }
        ExternalProperty& SetPropertyGetter(const PropertyGetterFn& value) noexcept { m_getter = value; return *this; }

    private:
        PropertyGetterFn m_getter;

    };

    class LabelProperty : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(LabelProperty, 1000)
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
