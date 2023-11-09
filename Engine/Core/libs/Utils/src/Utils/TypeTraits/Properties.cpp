//
// Created by Monika on 06.11.2023.
//

#include <Utils/TypeTraits/Properties.h>

namespace SR_UTILS_NS {
    PropertyContainer::PropertyContainer() {
        m_properties.reserve(8);
    }

    PropertyContainer::~PropertyContainer() {
        ClearContainer();
    }

    PropertyContainer& PropertyContainer::AddContainer(const char* name) {
        if (auto&& pProperty = Find(name)) {
            SRHalt("Properties::AddContainer() : property \"" + std::string(name) + "\" already exists!");
            return *dynamic_cast<PropertyContainer*>(pProperty);
        }

        auto&& pProperty = new PropertyContainer();

        pProperty->SetName(name);

        m_properties.emplace_back(pProperty);

        return *pProperty;
    }

    void PropertyContainer::ClearContainer() {
        for (auto&& pProperty : m_properties) {
            delete pProperty;
        }
        m_properties.clear();
    }
}