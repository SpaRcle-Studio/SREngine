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
        SR_NODISCARD PropertyList& GetProperties() { return m_properties; }

        template<typename T = Property> SR_NODISCARD T* Find(const SR_UTILS_NS::StringAtom& name) const noexcept;

        PropertyContainer& AddContainer(const char* name);
        template<typename T> T& AddCustomProperty(const char* name);
        template<typename T> StandardProperty& AddStandardProperty(const char* name, T* pRawProperty);
        template<typename T> StandardProperty& AddEnumProperty(const char* name, T* pRawProperty);

    private:
        PropertyList m_properties;

    };

    template<typename T> T* PropertyContainer::Find(const StringAtom& name) const noexcept {
        for (auto&& pProperty : m_properties) {
            if (pProperty->GetName() != name) {
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

    template<typename T> StandardProperty& PropertyContainer::AddEnumProperty(const char* name, T* pRawProperty) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddEnumProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty*>(pProperty);
        }

        auto&& pProperty = new StandardProperty();

        pProperty->SetName(name);
        pProperty->SetType(StandardType::Enum);
        pProperty->SetEnumReflector(SR_UTILS_NS::EnumReflector::GetReflector<T>());

        pProperty->SetGetter([pRawProperty](void* pData) {
            *reinterpret_cast<SR_UTILS_NS::StringAtom*>(pData) = SR_UTILS_NS::EnumReflector::ToString<T>(*pRawProperty);
        });

        pProperty->SetSetter([pRawProperty](void* pData) {
            auto&& value = *reinterpret_cast<SR_UTILS_NS::StringAtom*>(pData);
            *pRawProperty = SR_UTILS_NS::EnumReflector::FromString<T>(value);
        });

        m_properties.emplace_back(pProperty);

        return *pProperty;
    }
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
