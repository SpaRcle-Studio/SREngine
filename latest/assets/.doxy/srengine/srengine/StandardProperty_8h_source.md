

# File StandardProperty.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**StandardProperty.h**](StandardProperty_8h.md)

[Go to the documentation of this file](StandardProperty_8h.md)


```C++
//
// Created by Monika on 07.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
#define SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H

#include <Utils/TypeTraits/Property.h>

namespace SR_UTILS_NS {

    class StandardProperty : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(StandardProperty, 1000)
        using SetterFn = SR_HTYPES_NS::Function<void(void*)>;
        using GetterFn = SR_HTYPES_NS::Function<void(void*)>;
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        StandardProperty& SetSetter(SetterFn fn) { m_setter = std::move(fn); return *this; }
        StandardProperty& SetGetter(GetterFn fn) { m_getter = std::move(fn); return *this; }
        StandardProperty& SetType(StandardType type) { m_type = type; return *this; }

        SR_NODISCARD StandardType GetStandardType() const noexcept { return m_type; }

        SR_NODISCARD float_t GetDrag() const noexcept { return m_drag; }
        StandardProperty& SetDrag(float_t value) { m_drag = value; return *this; }

        SR_NODISCARD float_t GetResetValue() const noexcept { return m_resetValue; }
        StandardProperty& SetResetValue(float_t value) { m_resetValue = value; return *this; }

        SR_NODISCARD bool IsMultiline() const noexcept { return m_multiline; }
        void SetMultiline() noexcept { m_multiline = true; }

        SR_NODISCARD bool GetBool() const noexcept { return GetValue<bool, StandardType::Bool>(); }
        void SetBool(bool value) noexcept { SetValue<bool, StandardType::Bool>(value); }

        SR_NODISCARD float_t GetFloat() const noexcept { return GetValue<float_t, StandardType::Float>(); }
        void SetFloat(float_t value) noexcept { SetValue<float_t, StandardType::Float>(value); }

        SR_NODISCARD int32_t GetInt32() const noexcept { return GetValue<int32_t, StandardType::Int32>(); }
        void SetInt32(int32_t value) noexcept { SetValue<int32_t, StandardType::Int32>(value); }

        SR_NODISCARD uint16_t GetUInt16() const noexcept { return GetValue<uint16_t, StandardType::UInt16>(); }
        void SetUInt16(uint16_t value) noexcept { SetValue<uint16_t, StandardType::UInt16>(value); }

        SR_NODISCARD int16_t GetInt16() const noexcept { return GetValue<int16_t, StandardType::Int16>(); }
        void SetInt16(int16_t value) noexcept { SetValue<int16_t, StandardType::Int16>(value); }

        SR_NODISCARD uint32_t GetUInt32() const noexcept { return GetValue<uint32_t, StandardType::UInt32>(); }
        void SetUInt32(uint32_t value) noexcept { SetValue<uint32_t, StandardType::UInt32>(value); }

        SR_NODISCARD std::string GetString() const noexcept { return GetValue<std::string, StandardType::String>(); }
        void SetString(const std::string& value) noexcept { SetValue<std::string, StandardType::String>(value); }

        SR_NODISCARD SR_HTYPES_NS::UnicodeString GetUnicodeString() const noexcept { return GetValue<SR_HTYPES_NS::UnicodeString, StandardType::UnicodeString>(); }
        void SetUnicodeString(const SR_HTYPES_NS::UnicodeString& value) noexcept { SetValue<SR_HTYPES_NS::UnicodeString, StandardType::UnicodeString>(value); }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetStringAtom() const noexcept { return GetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(); }
        void SetStringAtom(const SR_UTILS_NS::StringAtom& value) noexcept { SetValue<SR_UTILS_NS::StringAtom, StandardType::StringAtom>(value); }

        SR_NODISCARD SR_MATH_NS::FVector2 GetFVector2() const noexcept { return GetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(); }
        void SetFVector2(const SR_MATH_NS::FVector2& value) noexcept { SetValue<SR_MATH_NS::FVector2, StandardType::FVector2>(value); }

        SR_NODISCARD SR_MATH_NS::UVector2 GetUVector2() const noexcept { return GetValue<SR_MATH_NS::UVector2, StandardType::UVector2>(); }
        void SetUVector2(const SR_MATH_NS::UVector2& value) noexcept { SetValue<SR_MATH_NS::UVector2, StandardType::UVector2>(value); }

        SR_NODISCARD SR_MATH_NS::FVector3 GetFVector3() const noexcept { return GetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(); }
        void SetFVector3(const SR_MATH_NS::FVector3& value) noexcept { SetValue<SR_MATH_NS::FVector3, StandardType::FVector3>(value); }

        SR_NODISCARD SR_MATH_NS::BVector3 GetBVector3() const noexcept { return GetValue<SR_MATH_NS::BVector3, StandardType::BVector3>(); }
        void SetBVector3(const SR_MATH_NS::BVector3& value) noexcept { SetValue<SR_MATH_NS::BVector3, StandardType::BVector3>(value); }

        SR_NODISCARD SR_MATH_NS::FVector4 GetFVector4() const noexcept { return GetValue<SR_MATH_NS::FVector4, StandardType::FVector4>(); }
        void SetFVector4(const SR_MATH_NS::FVector4& value) noexcept { SetValue<SR_MATH_NS::FVector4, StandardType::FVector4>(value); }

    private:
        template<typename T, StandardType type> SR_NODISCARD T GetValue() const noexcept {
            if (!SRVerifyFalse(m_type != type) || !m_getter) {
                return T(); 
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
        bool m_multiline = false;
        StandardType m_type = StandardType::Unknown;
        SetterFn m_setter;
        GetterFn m_getter;
        float_t m_drag = 1.f;
        float_t m_resetValue = 0.f;

    };


    class PathProperty : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(PathProperty, 1000)
        using Filter = std::vector<std::pair<SR_UTILS_NS::StringAtom, SR_UTILS_NS::StringAtom>>;
        using SetterFn = SR_HTYPES_NS::Function<void(const SR_UTILS_NS::Path&)>;
        using GetterFn = SR_HTYPES_NS::Function<SR_UTILS_NS::Path()>;
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

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


    class EnumProperty : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(EnumProperty, 1000)
        using SetterFn = SR_HTYPES_NS::Function<void(const SR_UTILS_NS::StringAtom&)>;
        using GetterFn = SR_HTYPES_NS::Function<SR_UTILS_NS::StringAtom()>;
        using FilterFn = SR_HTYPES_NS::Function<bool(const SR_UTILS_NS::StringAtom&)>;
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

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


    class ArrayReferenceProperty : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(ArrayReferenceProperty, 1000)
        using Super = Property;
        using OnChancedFn = SR_HTYPES_NS::Function<void()>;
        using AddElementFn = SR_HTYPES_NS::Function<void(uint32_t index)>;
        using RemoveElementFn = SR_HTYPES_NS::Function<void(uint32_t index)>;
        using SaveArrayFn = SR_HTYPES_NS::Function<void(SR_HTYPES_NS::Marshal&)>;
        using LoadArrayFn = SR_HTYPES_NS::Function<void(SR_HTYPES_NS::Marshal&)>;
        using PropertyGetterFn = SR_HTYPES_NS::Function<Property*(uint32_t index)>;
    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        ArrayReferenceProperty& SetOnChanged(const OnChancedFn& value) { m_onChanged = value; return *this; }
        ArrayReferenceProperty& SetAddElement(const AddElementFn& value) { m_addElement = value; return *this; }
        ArrayReferenceProperty& SetRemoveElement(const RemoveElementFn& value) { m_removeElement = value; return *this; }
        ArrayReferenceProperty& SetSaveArray(const SaveArrayFn& value) { m_saveArray = value; return *this; }
        ArrayReferenceProperty& SetLoadArray(const LoadArrayFn& value) { m_loadArray = value; return *this; }
        ArrayReferenceProperty& SetIsProperty() { m_isProperty = true; return *this; }
        ArrayReferenceProperty& SetPropertyGetter(const PropertyGetterFn& value) { m_propertyGetter = value; return *this; }

    private:
        SaveArrayFn m_saveArray;
        LoadArrayFn m_loadArray;
        OnChancedFn m_onChanged;
        AddElementFn m_addElement;
        RemoveElementFn m_removeElement;
        PropertyGetterFn m_propertyGetter;
        bool m_isProperty = false;

    };
}

#endif //SR_ENGINE_TYPE_TRAITS_STANDARD_PROPERTY_H
```


