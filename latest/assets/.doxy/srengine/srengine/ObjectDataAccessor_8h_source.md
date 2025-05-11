

# File ObjectDataAccessor.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**ObjectDataAccessor.h**](ObjectDataAccessor_8h.md)

[Go to the documentation of this file](ObjectDataAccessor_8h.md)


```C++
//
// Created by Monika on 12.02.2025.
//

#ifndef SR_COMMON_OBJECT_DATA_ACCESSOR_H
#define SR_COMMON_OBJECT_DATA_ACCESSOR_H

#include <Utils/TypeTraits/TypeTraits.h>

namespace SR_UTILS_NS {
    class ISerializer;
    class IDeserializer;


    template<typename T, typename Enable = void> struct ObjectDataAccessor {
        static void Save(ISerializer&, const T&, const SerializationId&) {
            static_assert(AlwaysFalseV<T>, "Unable to save! Need to inherit from Serializable!");
        }

        static void Load(IDeserializer&, T&, const SerializationId&) {
            static_assert(AlwaysFalseV<T>, "Unable to load! Need to inherit from Serializable!");
        }
    };
}

#endif //SR_COMMON_OBJECT_DATA_ACCESSOR_H
```


