

# File ObjectDataAccessor.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**ObjectDataAccessor.h**](ObjectDataAccessor_8h.md)

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


