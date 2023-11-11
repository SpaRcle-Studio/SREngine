//
// Created by Monika on 06.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
#define SR_ENGINE_TYPE_TRAITS_PROPERTIES_H

#include <Utils/TypeTraits/StandardProperty.h>

namespace SR_UTILS_NS {
    class PropertyContainer : public Property {
        SR_INLINE_STATIC int16_t VERSION = 1000;
        using PropertyList = std::vector<Property*>;
    public:
        PropertyContainer();
        ~PropertyContainer() override;

    public:
        void ClearContainer();

        SR_NODISCARD PropertyList& GetProperties() noexcept { return m_properties; }
        SR_NODISCARD const PropertyList& GetProperties() const noexcept { return m_properties; }

        template<typename T = Property> SR_NODISCARD T* Find(const SR_UTILS_NS::StringAtom& name) const noexcept;
        template<typename T = Property> SR_NODISCARD T* Find(uint64_t hashName) const noexcept;

        PropertyContainer& AddContainer(const char* name);
        template<typename T> T& AddCustomProperty(const char* name);
        template<typename T> StandardProperty& AddStandardProperty(const char* name, T* pRawProperty);
        template<typename T> EnumProperty& AddEnumProperty(const char* name, T* pRawProperty);
        template<typename T> EnumProperty& AddEnumProperty(const char* name);

        template<typename T> PropertyContainer& ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function);
        template<typename T> const PropertyContainer& ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) const;

        template<typename T> bool ForEachPropertyRet(const SR_HTYPES_NS::Function<bool(T*)>& function) const;

    private:
        PropertyList m_properties;

    };

    template<typename T> bool PropertyContainer::ForEachPropertyRet(const SR_HTYPES_NS::Function<bool(T*)>& function) const {
        for (auto&& pProperty : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(pProperty)) {
                if (!function(pCastedProperty)) {
                    return false;
                }
            }
        }

        return true;
    }

    template<typename T> PropertyContainer& PropertyContainer::ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) {
        for (auto&& pProperty : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(pProperty)) {
                function(pCastedProperty);
            }
        }
        return *this;
    }

    template<typename T> const PropertyContainer& PropertyContainer::ForEachProperty(const SR_HTYPES_NS::Function<void(T*)>& function) const {
        for (auto&& pProperty : m_properties) {
            if (auto&& pCastedProperty = dynamic_cast<T*>(pProperty)) {
                function(pCastedProperty);
            }
        }
        return *this;
    }

    template<typename T> T* PropertyContainer::Find(uint64_t hashName) const noexcept {
        for (auto&& pProperty : m_properties) {
            if (pProperty->GetName().GetHash() != hashName) {
                continue;
            }

            if constexpr (std::is_same_v<T, SR_UTILS_NS::Property>) {
                return pProperty;
            }

            if (auto&& pCasted = dynamic_cast<T*>(pProperty)) {
                return pCasted;
            }
        }
        return nullptr;
    }

    template<typename T> T* PropertyContainer::Find(const StringAtom& name) const noexcept {
        return Find<T>(name.GetHash());
    }

    template<typename T> T& PropertyContainer::AddCustomProperty(const char* name)  {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddCustomProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<T*>(pProperty);
        }

        auto&& pProperty = new T();

        pProperty->SetName(name);

        m_properties.emplace_back(pProperty);

        return *pProperty;
    }

    template<typename T> StandardProperty& PropertyContainer::AddStandardProperty(const char* name, T* pRawProperty) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddStandardProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty*>(pProperty);
        }

        auto &&pProperty = new StandardProperty();

        pProperty->SetName(name);
        pProperty->SetType(GetStandardType<T>());

        pProperty->SetGetter([pRawProperty](void *pData) {
            *reinterpret_cast<T *>(pData) = *pRawProperty;
        });

        pProperty->SetSetter([pRawProperty](void *pData) {
            *pRawProperty = *reinterpret_cast<T *>(pData);
        });

        m_properties.emplace_back(pProperty);

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
            return SR_UTILS_NS::EnumReflector::ToString<T>(*pRawProperty);
        });

        pProperty->SetSetter([pRawProperty](const SR_UTILS_NS::StringAtom& value) {
            *pRawProperty = SR_UTILS_NS::EnumReflector::FromString<T>(value);
        });

        m_properties.emplace_back(pProperty);

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

        m_properties.emplace_back(pProperty);

        return *pProperty;
    }
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
