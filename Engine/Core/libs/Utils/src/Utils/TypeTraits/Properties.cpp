//
// Created by Monika on 06.11.2023.
//

#include <Utils/TypeTraits/Properties.h>

namespace SR_UTILS_NS {
    Properties::~Properties() {
        for (auto&& [name, pProperty] : m_properties) {
            delete pProperty;
        }
        m_properties.clear();
    }
}