//
// Created by Monika on 11.11.2023.
//

#ifndef SR_ENGINE_UTILS_PROPERTY_MANAGER_H
#define SR_ENGINE_UTILS_PROPERTY_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/StringAtom.h>

namespace SR_UTILS_NS {
    class Property;

    class PropertyManager : public Singleton<PropertyManager> {
        SR_REGISTER_SINGLETON(PropertyManager)
        using ConstructorFn = SR_HTYPES_NS::Function<Property*(void)>;
    public:
        void Register(StringAtom name, ConstructorFn constructor);
        SR_NODISCARD Property* Allocate(const StringAtom& name) const noexcept;

    private:
        ska::flat_hash_map<StringAtom, ConstructorFn> m_constructors;

    };
}

#endif //SR_ENGINE_UTILS_PROPERTY_MANAGER_H
