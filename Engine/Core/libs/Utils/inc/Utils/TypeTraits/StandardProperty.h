//
// Created by Monika on 07.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
#define SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {
    class StandardProperty : public Property {
        SR_INLINE_STATIC int16_t VERSION = 1000;
        using SetterFn = SR_HTYPES_NS::Function<void(void*)>;
        using GetterFn = SR_HTYPES_NS::Function<void(void*)>;
    public:
        StandardProperty& SetSetter(SetterFn fn) { m_setter = std::move(fn); return *this; }
        StandardProperty& SetGetter(GetterFn fn) { m_getter = std::move(fn); return *this; }
        StandardProperty& SetType(StandardType type) { m_type = type; return *this; }

        SR_NODISCARD StandardType GetStandardType() const noexcept { return m_type; }

        SR_NODISCARD float_t GetDrag() const noexcept { return m_drag; }
        StandardProperty& SetDrag(float_t value) { m_drag = value; return *this; }

        SR_NODISCARD float_t GetResetValue() const noexcept { return m_resetValue; }
        StandardProperty& SetResetValue(float_t value) { m_resetValue = value; return *this; }

        SR_NODISCARD bool GetBool() const noexcept { return GetValue<bool, StandardType::Bool>(); }
        void SetBool(bool value) noexcept { SetValue<bool, StandardType::Bool>(value); }

        SR_NODISCARD float_t GetFloat() const noexcept { return GetValue<float_t, StandardType::Float>(); }
        void SetFloat(float_t value) noexcept { SetValue<float_t, StandardType::Float>(value); }

        SR_NODISCARD int32_t GetInt32() const noexcept { return GetValue<int32_t, StandardType::Int32>(); }
        void SetInt32(int32_t value) noexcept { SetValue<int32_t, StandardType::Int32>(value); }

        SR_NODISCARD uint32_t GetUInt32() const noexcept { return GetValue<uint32_t, StandardType::UInt32>(); }
        void SetUInt32(uint32_t value) noexcept { SetValue<uint32_t, StandardType::UInt32>(value); }

        SR_NODISCARD std::string GetString() const noexcept { return GetValue<std::string, StandardType::String>(); }
        void SetString(const std::string& value) noexcept { SetValue<std::string, StandardType::String>(value); }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetStringAtom() const noexcept { return GetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(); }
        void SetStringAtom(const SR_UTILS_NS::StringAtom& value) noexcept { SetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(value); }

        SR_NODISCARD SR_MATH_NS::FVector2 GetFVector2() const noexcept { return GetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(); }
        void SetFVector2(const SR_MATH_NS::FVector2& value) noexcept { SetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(value); }

        SR_NODISCARD SR_MATH_NS::FVector3 GetFVector3() const noexcept { return GetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(); }
        void SetFVector3(const SR_MATH_NS::FVector3& value) noexcept { SetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(value); }

        SR_NODISCARD SR_MATH_NS::BVector3 GetBVector3() const noexcept { return GetValue<SR_MATH_NS::BVector3, StandardType::BVector3>(); }
        void SetBVector3(const SR_MATH_NS::BVector3& value) noexcept { SetValue<SR_MATH_NS::BVector3, StandardType::BVector3>(value); }

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
        StandardType m_type = StandardType::Unknown;
        SetterFn m_setter;
        GetterFn m_getter;
        float_t m_drag = 1.f;
        float_t m_resetValue = 0.f;

    };

    class EnumProperty : public Property {
        using SetterFn = SR_HTYPES_NS::Function<void(const SR_UTILS_NS::StringAtom&)>;
        using GetterFn = SR_HTYPES_NS::Function<SR_UTILS_NS::StringAtom()>;
        using FilterFn = SR_HTYPES_NS::Function<bool(const SR_UTILS_NS::StringAtom&)>;
    public:
        EnumProperty& SetEnumReflector(SR_UTILS_NS::EnumReflector* pReflector) noexcept { m_reflector = pReflector; return *this; }
        SR_NODISCARD SR_UTILS_NS::EnumReflector* GetEnumReflector() const noexcept { return m_reflector; }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetEnum() const noexcept;

        SR_NODISCARD const FilterFn& GetFilter() const noexcept { return m_filter; }
        EnumProperty& SetEnum(const SR_UTILS_NS::StringAtom& value) noexcept;

        EnumProperty& SetSetter(const SetterFn& value) { m_setter = value; return *this; }
        EnumProperty& SetGetter(const GetterFn& value) { m_getter = value; return *this; }
        EnumProperty& SetFilter(const FilterFn& value) { m_filter = value; return *this; }

    private:
        SR_UTILS_NS::EnumReflector* m_reflector = nullptr;
        SetterFn m_setter;
        GetterFn m_getter;
        FilterFn m_filter;

    };

    class PathProperty : public Property {
        using Filter = std::vector<std::pair<SR_UTILS_NS::StringAtom, SR_UTILS_NS::StringAtom>>;
        using SetterFn = SR_HTYPES_NS::Function<void(const SR_UTILS_NS::Path&)>;
        using GetterFn = SR_HTYPES_NS::Function<SR_UTILS_NS::Path()>;
    public:
        PathProperty& AddFileFilter(SR_UTILS_NS::StringAtom description, SR_UTILS_NS::StringAtom extension) {
            m_filter.emplace_back(std::make_pair(description, extension));
            return *this;
        }

        PathProperty& SetPath(const SR_UTILS_NS::Path& path) noexcept;
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const noexcept;
        SR_NODISCARD SR_UTILS_NS::StringAtom GetWidgetEditor() const noexcept { return m_widgetEditor; }

        PathProperty& SetSetter(const SetterFn& value) { m_setter = value; return *this; }
        PathProperty& SetGetter(const GetterFn& value) { m_getter = value; return *this; }
        PathProperty& SetWidgetEditor(const SR_UTILS_NS::StringAtom& value) { m_widgetEditor = value; return *this; }

        SR_NODISCARD const Filter& GetFileFilter() const noexcept { return m_filter; }

    private:
        SR_UTILS_NS::StringAtom m_widgetEditor;
        Filter m_filter;
        SetterFn m_setter;
        GetterFn m_getter;

    };
}

#endif //SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
