

# File PropertyManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**PropertyManager.h**](PropertyManager_8h.md)

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


