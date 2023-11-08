//
// Created by Monika on 06.11.2023.
//

#ifndef SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
#define SR_ENGINE_TYPE_TRAITS_PROPERTIES_H

#include <Utils/TypeTraits/StandardProperty.h>

namespace SR_UTILS_NS {
    class Properties : SR_UTILS_NS::NonCopyable {
        SR_INLINE_STATIC int16_t VERSION = 1000;
        using PropertyList = std::map<SR_UTILS_NS::StringAtom, Property*>;
    public:
        ~Properties() override;

    public:
        SR_NODISCARD PropertyList& GetProperties() { return m_properties; }

        template<typename T> T& AddCustomProperty(const char* name);
        template<typename T> StandardProperty& AddStandardProperty(const char* name, T* pRawProperty);
        template<typename T> StandardProperty& AddEnumProperty(const char* name, T* pRawProperty);

    private:
        PropertyList m_properties;

    };

    template<typename T> T& Properties::AddCustomProperty(const char *name)  {
        if (auto&& pIt = m_properties.find(name); pIt != m_properties.end()) {
            SRHalt("Properties::AddCustomProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<T*>(pIt->second);
        }

        auto&& pProperty = new T();

        pProperty->SetName(name);

        m_properties[SR_UTILS_NS::StringAtom(name)] = pProperty;

        return *pProperty;
    }

    template<typename T> StandardProperty& Properties::AddStandardProperty(const char* name, T* pRawProperty) {
        if (auto &&pIt = m_properties.find(name); pIt != m_properties.end()) {
            SRHalt("Properties::AddStandardProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty *>(pIt->second);
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

        m_properties[SR_UTILS_NS::StringAtom(name)] = pProperty;

        return *pProperty;
    }

    template<typename T> StandardProperty& Properties::AddEnumProperty(const char* name, T* pRawProperty) {
        if (auto&& pIt = m_properties.find(name); pIt != m_properties.end()) {
            SRHalt("Properties::AddEnumProperty() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<StandardProperty*>(pIt->second);
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

        m_properties[SR_UTILS_NS::StringAtom(name)] = pProperty;

        return *pProperty;
    }
}

#endif //SR_ENGINE_TYPE_TRAITS_PROPERTIES_H
