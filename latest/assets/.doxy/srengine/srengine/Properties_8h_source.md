

# File Properties.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**Properties.h**](Properties_8h.md)

[Go to the documentation of this file](Properties_8h.md)


```C++
//
// Created by Monika on 06.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
#define SR_ENGINE_TYPE_TRAITS_PROPERTIES_H

#include <Utils/TypeTraits/StandardProperty.h>
#include <Utils/ECS/EntityRef.h>

namespace SR_UTILS_NS {
    class PropertyContainer : public Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(PropertyContainer, 1000)
        struct PropertyInfo {
            bool isExternal = false;
            Property* pProperty = nullptr;
        };
        using PropertyList = std::vector<PropertyInfo>;
    public:
        PropertyContainer();
        ~PropertyContainer() override;

    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        virtual void ClearContainer();
        virtual void OnPropertyAdded(Property* pProprerty) { }

        SR_NODISCARD PropertyList& GetProperties() noexcept { return m_properties; }
        SR_NODISCARD const PropertyList& GetProperties() const noexcept { return m_properties; }

        template<typename T = Property> SR_NODISCARD T* Find(const SR_UTILS_NS::StringAtom& name) const noexcept;
        template<typename T = Property> SR_NODISCARD T* Find(uint64_t hashName) const noexcept;

        PropertyContainer& AddContainer(const char* name);
        EntityRefProperty& AddEntityRefProperty(SR_UTILS_NS::StringAtom name, const EntityRefUtils::OwnerRef& owner);
        ArrayReferenceProperty& AddArrayReferenceProperty(const char* name);

        void AddExternalProperty(Property* pProperty);

        template<typename T, typename ...Args> T& AddCustomProperty(SR_UTILS_NS::StringAtom name, Args... args);
        template<typename T> StandardProperty& AddStandardProperty(const char* name);
        template<typename T> StandardProperty& AddStandardProperty(const char* name, T* pRawProperty);
        template<typename T> EnumProperty& AddEnumProperty(const char* name, T* pRawProperty);
        template<typename T> EnumProperty& AddEnumProperty(const char* name);

        template<typename T> PropertyContainer& ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function);
        template<typename T> const PropertyContainer& ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) const;

        template<typename T> bool ForEachPropertyRet(const SR_HTYPES_NS::Function<bool(T*)>& function) const;

        void SetShowErrors(bool value) noexcept { m_showErrors = value; }

    private:
        bool m_showErrors = true;
        PropertyList m_properties;

    };

    template<typename T> bool PropertyContainer::ForEachPropertyRet(const SR_HTYPES_NS::Function<bool(T*)>& function) const {
        for (auto&& propertyInfo : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(propertyInfo.pProperty)) {
                if (!function(pCastedProperty)) {
                    return false;
                }
            }
        }

        return true;
    }

    template<typename T> PropertyContainer& PropertyContainer::ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) {
        for (auto&& propertyInfo : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(propertyInfo.pProperty)) {
                function(pCastedProperty);
            }
        }
        return *this;
    }

    template<typename T> const PropertyContainer& PropertyContainer::ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) const {
        for (auto&& propertyInfo : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(propertyInfo.pProperty)) {
                function(pCastedProperty);
            }
        }
        return *this;
    }

    template<typename T> T* PropertyContainer::Find(uint64_t hashName) const noexcept {
        for (auto&& propertyInfo : m_properties) {
            if (propertyInfo.pProperty->GetName().GetHash() != hashName) {
                continue;
            }

            if constexpr (std::is_same_v<T, SR_UTILS_NS::Property>) {
                return propertyInfo.pProperty;
            }

            if (auto&& pCasted = dynamic_cast<T*>(propertyInfo.pProperty)) {
                return pCasted;
            }
        }
        return nullptr;
    }

    template<typename T> T* PropertyContainer::Find(const StringAtom& name) const noexcept {
        SR_TRACY_ZONE;
        return Find<T>(name.GetHash());
    }

    template<typename T> StandardProperty& PropertyContainer::AddStandardProperty(const char* name) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddStandardProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty*>(pProperty);
        }

        auto&& pProperty = new StandardProperty();

        pProperty->SetName(name);
        pProperty->SetType(GetStandardType<T>());

        PropertyInfo info;

        info.pProperty = pProperty;
        m_properties.emplace_back(info);

        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    template<typename T, typename ...Args> T& PropertyContainer::AddCustomProperty(SR_UTILS_NS::StringAtom name, Args... args)  {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddCustomProperty() : property \"" + name.ToStringRef() + "\" already exists!");
            return *dynamic_cast<T*>(pProperty);
        }

        auto&& pProperty = new T(std::forward<Args>(args)...);

        pProperty->SetName(name);

        PropertyInfo info;

        info.pProperty = pProperty;
        m_properties.emplace_back(info);

        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    template<typename T> StandardProperty& PropertyContainer::AddStandardProperty(const char* name, T* pRawProperty) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddStandardProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty*>(pProperty);
        }

        auto&& pProperty = new StandardProperty();

        pProperty->SetName(name);
        pProperty->SetType(GetStandardType<T>());

        pProperty->SetGetter([pRawProperty](void *pData) {
            *reinterpret_cast<T*>(pData) = *pRawProperty;
        });

        pProperty->SetSetter([pRawProperty](void *pData) {
            *pRawProperty = *reinterpret_cast<T*>(pData);
        });

        PropertyInfo info;

        info.pProperty = pProperty;
        m_properties.emplace_back(info);

        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    template<typename T> EnumProperty& PropertyContainer::AddEnumProperty(const char* name, T* pRawProperty) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddEnumProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<EnumProperty*>(pProperty);
        }

        auto&& pProperty = new EnumProperty();

        pProperty->SetName(name);
        pProperty->SetEnumReflector(SR_UTILS_NS::EnumReflector::GetReflector<T>());

        pProperty->SetGetter([pRawProperty]() -> SR_UTILS_NS::StringAtom {
            return SR_UTILS_NS::EnumReflector::ToStringAtom<T>(*pRawProperty);
        });

        pProperty->SetSetter([pRawProperty](const SR_UTILS_NS::StringAtom& value) {
            *pRawProperty = SR_UTILS_NS::EnumReflector::FromString<T>(value);
        });

        PropertyInfo info;

        info.pProperty = pProperty;
        m_properties.emplace_back(info);

        OnPropertyAdded(pProperty);

        return *pProperty;
    }

    template<typename T> EnumProperty& PropertyContainer::AddEnumProperty(const char* name) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddEnumProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<EnumProperty*>(pProperty);
        }

        auto&& pProperty = new EnumProperty();

        pProperty->SetName(name);
        pProperty->SetEnumReflector(SR_UTILS_NS::EnumReflector::GetReflector<T>());

        PropertyInfo info;

        info.pProperty = pProperty;
        m_properties.emplace_back(info);

        OnPropertyAdded(pProperty);

        return *pProperty;
    }
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
```


