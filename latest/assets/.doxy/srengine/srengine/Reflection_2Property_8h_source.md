

# File Property.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Reflection**](dir_a5a26934b95143030003946f011a899c.md) **>** [**Property.h**](Reflection_2Property_8h.md)

[Go to the documentation of this file](Reflection_2Property_8h.md)


```C++
//
// Created by Monika on 21.01.2025.
//

#ifndef SR_ENGINE_UTILS_REFLECTION_PROPERTY_H
#define SR_ENGINE_UTILS_REFLECTION_PROPERTY_H

#include <Utils/Reflection/Value.h>
#include <Utils/Common/StringAtomLiterals.h>

namespace SR_UTILS_NS::Reflection {
    class EditorPropertyParams {
    public:
        EditorPropertyParams() = default;

        EditorPropertyParams& SetNoHeader() noexcept { m_noHeader = true; return *this; }
        EditorPropertyParams& SetNotNull() noexcept { m_notNull = true; return *this; }
        EditorPropertyParams& SetDisplayName(const StringAtom& displayName) noexcept { m_displayName = displayName; return *this; }
        EditorPropertyParams& SetTooltip(const StringAtom& tooltip) noexcept { m_tooltip = tooltip; return *this; }
        EditorPropertyParams& SetInspector(const StringAtom& inspector) noexcept { m_inspector = inspector; return *this; }
        EditorPropertyParams& SetDragSpeed(float_t speed) noexcept { m_dragSpeed = speed; return *this; }
        EditorPropertyParams& SetCustomArg(const StringAtom& name, std::string_view value) noexcept { m_customArgs[name] = value; return *this; }

        SR_NODISCARD StringAtom GetDisplayName() const noexcept { return m_displayName; }
        SR_NODISCARD StringAtom GetTooltip() const noexcept { return m_tooltip; }
        SR_NODISCARD float_t GetDragSpeed() const noexcept { return m_dragSpeed; }
        SR_NODISCARD float_t GetEditorWidth() const noexcept { return m_editorWidth; }
        SR_NODISCARD StringAtom GetInspector() const noexcept { return m_inspector; }
        SR_NODISCARD bool IsNoHeader() const noexcept { return m_noHeader; }
        SR_NODISCARD bool IsNotNull() const noexcept { return m_notNull; }

        SR_NODISCARD std::string_view GetCustomArg(const StringAtom& name) const noexcept {
            if (auto&& pIt = m_customArgs.find(name); pIt != m_customArgs.end()) {
                return pIt->second;
            }
            return {};
        }

    private:
        SR_UTILS_NS::StringAtom m_displayName;
        SR_UTILS_NS::StringAtom m_tooltip;
        SR_UTILS_NS::StringAtom m_inspector;
        float_t m_editorWidth = 0.f;
        float_t m_dragSpeed = 1.f;
        bool m_noHeader = false;
        bool m_notNull = false;
        std::map<SR_UTILS_NS::StringAtom, std::string_view> m_customArgs;

    };

    class Property {
        using SetCallbackFn = void(*)(SRClass* pOwner, const Value& value);
        using GetCallbackFn = Value(*)(SRClass* pOwner);
        using ChangeCallbackFn = void(*)(SRClass* pOwner);
        using PropertyActiveCallbackFn = bool(*)(SRClass* pOwner);
    public:
        Property() = default;

        SR_NODISCARD Value Get(SRClass* pOwner) const noexcept { return m_getCallback(pOwner); }
        void Set(SRClass* pOwner, const Value& value) const noexcept { m_setCallback(pOwner, value); }

        void OnChanged(SRClass* pOwner) const noexcept {
            if (m_onChangeCallback) {
                m_onChangeCallback(pOwner);
            }
        }
        SR_NODISCARD StringAtom GetName() const noexcept { return m_name; }
        SR_NODISCARD StringAtom GetSerializeName() const noexcept { return m_serializeName; }
        SR_NODISCARD PropertyPublicity GetPublicity() const noexcept { return m_publicity; }
        SR_NODISCARD const Value& GetDefaultValue() const noexcept { return m_defaultValue; }
        SR_NODISCARD const Value& GetResetValue() const noexcept { return m_resetValue; }
        SR_NODISCARD const EditorPropertyParams& GetEditorParams() const noexcept { return m_editorParams; }
        SR_NODISCARD bool HasExplicitSetter() const noexcept { return m_hasExplicitSetter; }

        SR_NODISCARD bool IsActive(SRClass* pOwner) const noexcept {
            if (pOwner && m_propertyActiveCallback) {
                return m_propertyActiveCallback(pOwner);
            }
            return true;
        }

        SR_NODISCARD bool IsHidden(SRClass* pOwner) const noexcept {
            if (!IsActive(pOwner)) {
                return true;
            }
            return m_publicity == PropertyPublicity::Hidden || m_publicity == PropertyPublicity::HiddenReadOnly;
        }

        SR_NODISCARD bool IsReadOnly() const noexcept {
            return m_publicity == PropertyPublicity::ReadOnly || m_publicity == PropertyPublicity::HiddenReadOnly;
        }

        Property& SetName(const StringAtom& name) noexcept { m_name = name; return *this; }
        Property& SetSerializeName(const StringAtom& serializeName) noexcept { m_serializeName = serializeName; return *this; }
        Property& SetPublicity(PropertyPublicity publicity) noexcept { m_publicity = publicity; return *this; }
        Property& SetSetter(SetCallbackFn callback) noexcept { m_setCallback = callback; return *this; }
        Property& SetGetter(GetCallbackFn callback) noexcept { m_getCallback = callback; return *this; }
        Property& SetDefaultValue(Value&& value) noexcept { m_defaultValue = std::move(value); return *this; }
        Property& SetChangeCallback(ChangeCallbackFn callback) noexcept { m_onChangeCallback = callback; return *this; }
        Property& SetResetValue(Value&& value) noexcept { m_resetValue = std::move(value); return *this; }
        Property& SetEditorParams(const EditorPropertyParams& params) noexcept { m_editorParams = params; return *this; }
        Property& SetPropertyCondition(PropertyActiveCallbackFn callback) noexcept { m_propertyActiveCallback = callback; return *this; }
        Property& SetHasExplicitSetter(bool hasExplicitSetter) noexcept { m_hasExplicitSetter = hasExplicitSetter; return *this; }

    private:
        EditorPropertyParams m_editorParams;
        Reflection::Value m_defaultValue;
        Reflection::Value m_resetValue;
        SR_UTILS_NS::StringAtom m_name;
        SR_UTILS_NS::StringAtom m_serializeName;
        PropertyPublicity m_publicity = PropertyPublicity::Public;
        SetCallbackFn m_setCallback = nullptr;
        GetCallbackFn m_getCallback = nullptr;
        ChangeCallbackFn m_onChangeCallback = nullptr;
        PropertyActiveCallbackFn m_propertyActiveCallback = nullptr;
        bool m_hasExplicitSetter = false;
    };

    template<typename T> SR_UTILS_NS::StringAtom GetPropertyInspector() {
        using Type = SR_UTILS_NS::RemoveQualifiersT<T>;

        if constexpr (SR_MATH_NS::IsBool<Type>()) {
            return "Bool"_atom;
        }
        if constexpr (SR_MATH_NS::IsNumber<Type>()) {
            return "Numeric"_atom;
        }
        if constexpr (SR_UTILS_NS::IsMathVector<Type>()) {
            return "MathVector"_atom;
        }
        if constexpr (SR_UTILS_NS::IsMathSize<Type>()) {
            return "Size"_atom;
        }
        if constexpr (SR_UTILS_NS::IsSREnumV<Type>) {
            return "Enum"_atom;
        }
        if constexpr (SR_UTILS_NS::IsSTLVectorV<Type>) {
            return "Vector"_atom;
        }

        return SR_UTILS_NS::StringAtom();
    }

    SR_UTILS_NS::StringAtom MakeSerializePropertyName(std::string_view name);
    SR_UTILS_NS::StringAtom MakeDisplayName(std::string_view name);
}

#endif //SR_ENGINE_UTILS_REFLECTION_PROPERTY_H
```


