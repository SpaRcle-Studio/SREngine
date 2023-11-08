//
// Created by Monika on 07.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
#define SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    class StandardProperty : public Property {
        using SetterFn = SR_HTYPES_NS::Function<void(void*)>;
        using GetterFn = SR_HTYPES_NS::Function<void(void*)>;
    public:
        StandardProperty& SetSetter(SetterFn fn) { m_setter = std::move(fn); return *this; }
        StandardProperty& SetGetter(GetterFn fn) { m_getter = std::move(fn); return *this; }
        StandardProperty& SetType(StandardType type) { m_type = type; return *this; }
        StandardProperty& SetEnumReflector(SR_UTILS_NS::EnumReflector* pReflector) { m_reflector = pReflector; return *this; }

        SR_NODISCARD StandardType GetStandardType() const noexcept { return m_type; }
        SR_NODISCARD SR_UTILS_NS::EnumReflector* GetEnumReflector() const noexcept { return m_reflector; }

        SR_NODISCARD bool GetBool() const noexcept { return GetValue<bool, StandardType::Bool>(); }
        void SetBool(bool value) noexcept { SetValue<bool, StandardType::Bool>(value); }

        SR_NODISCARD std::string GetString() const noexcept { return GetValue<std::string, StandardType::String>(); }
        void SetString(const std::string& value) noexcept { SetValue<std::string, StandardType::String>(value); }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetEnum() const noexcept { return GetValue<SR_UTILS_NS::StringAtom, StandardType::Enum>(); }
        void SetEnum(const SR_UTILS_NS::StringAtom& value) noexcept { SetValue<SR_UTILS_NS::StringAtom, StandardType::Enum>(value); }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetStringAtom() const noexcept { return GetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(); }
        void SetStringAtom(const SR_UTILS_NS::StringAtom& value) noexcept { SetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(value); }

        SR_NODISCARD SR_MATH_NS::FVector2 GetFVector2() const noexcept { return GetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(); }
        void SetFVector2(const SR_MATH_NS::FVector2& value) noexcept { SetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(value); }

        SR_NODISCARD SR_MATH_NS::FVector3 GetFVector3() const noexcept { return GetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(); }
        void SetFVector3(const SR_MATH_NS::FVector3& value) noexcept { SetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(value); }

        SR_NODISCARD SR_MATH_NS::FVector4 GetFVector4() const noexcept { return GetValue<SR_MATH_NS::FVector4, StandardType::FVector4>(); }
        void SetFVector4(const SR_MATH_NS::FVector4& value) noexcept { SetValue<SR_MATH_NS::FVector4, StandardType::FVector4>(value); }

    private:
        template<typename T, StandardType type> SR_NODISCARD T GetValue() const noexcept {
            if (!SRVerifyFalse(m_type != type) || !m_getter) {
                return T(); /// NOLINT
            }

            T value;
            m_getter((void*)&value);
            return value;
        }

        template<typename T, StandardType type> void SetValue(const T& value) noexcept {
            if (!SRVerifyFalse(m_type != type) || !m_setter) {
                return;
            }
            m_setter((void*)&value);
        }

    private:
        SR_UTILS_NS::EnumReflector* m_reflector = nullptr;
        StandardType m_type = StandardType::Unknown;
        SetterFn m_setter;
        GetterFn m_getter;

    };
}

#endif //SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
