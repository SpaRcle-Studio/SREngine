

# File PropertyManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**PropertyManager.h**](PropertyManager_8h.md)

[Go to the documentation of this file](PropertyManager_8h.md)


```C++
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
```


