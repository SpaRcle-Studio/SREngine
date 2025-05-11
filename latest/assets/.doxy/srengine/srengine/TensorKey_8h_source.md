

# File TensorKey.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**TensorKey.h**](TensorKey_8h.md)

[Go to the documentation of this file](TensorKey_8h.md)


```C++
//
// Created by Monika on 23.08.2022.
//

#ifndef SR_ENGINE_TENSORKEY_H
#define SR_ENGINE_TENSORKEY_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_WORLD_NS {
    struct SR_COMMON_DLL_API TensorKey {
        TensorKey() = default;

        TensorKey(const SR_MATH_NS::IVector3& _region, const SR_MATH_NS::IVector3& _chunk)
            : region(_region)
            , chunk(_chunk)
        { }

        SR_MATH_NS::IVector3 region;
        SR_MATH_NS::IVector3 chunk;

        bool operator==(const TensorKey &other) const noexcept {
            return region == other.region && chunk == other.chunk;
        }
    };
}

namespace std {
    template<> struct hash<SR_WORLD_NS::TensorKey> {
        size_t operator()(SR_WORLD_NS::TensorKey const& vecPair) const {
            std::size_t res = 0;

            std::hash<SR_MATH_NS::IVector3> hFirst;
            std::hash<SR_MATH_NS::IVector3> hSecond;

            res ^= hFirst(vecPair.region) + 0x9e3779b9 + (res << 6u) + (res >> 2u);
            res ^= hSecond(vecPair.chunk) + 0x9e3779b9 + (res << 6u) + (res >> 2u);

            return res;
        }
    };
}

namespace SR_UTILS_NS {
    class GameObject;
    class SceneObject;
}

namespace SR_WORLD_NS {
    class Region;
    class Chunk;

    typedef std::unordered_map<TensorKey, std::vector<SR_HTYPES_NS::SharedPtr<SceneObject>>> Tensor;
    typedef std::list<Region*> Regions;
}

#endif //SR_ENGINE_TENSORKEY_H
```


