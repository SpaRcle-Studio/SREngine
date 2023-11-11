//
// Created by Monika on 11.11.2023.
//

#include <Utils/TypeTraits/PropertyManager.h>

namespace SR_UTILS_NS {
    void PropertyManager::Register(StringAtom name, PropertyManager::ConstructorFn constructor) {
        //m_constructors.insert(std::make_pair(name, std::move(constructor)));
    }
}