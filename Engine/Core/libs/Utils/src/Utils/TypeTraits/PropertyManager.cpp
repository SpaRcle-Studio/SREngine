//
// Created by Monika on 11.11.2023.
//

#include <Utils/TypeTraits/PropertyManager.h>

namespace SR_UTILS_NS {
    void PropertyManager::Register(StringAtom name, PropertyManager::ConstructorFn constructor) {
        m_constructors.insert(std::make_pair(name, std::move(constructor)));
    }

    Property* PropertyManager::Allocate(const StringAtom& name) const noexcept {
        if (auto&& pIt = m_constructors.find(name); pIt != m_constructors.end()) {
            auto&& [foundName, constructor] = *pIt;
            return constructor ? constructor() : nullptr;
        }
        return nullptr;
    }
}