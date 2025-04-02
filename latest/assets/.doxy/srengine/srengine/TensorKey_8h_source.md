

# File TensorKey.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**TensorKey.h**](TensorKey_8h.md)

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
    struct SR_DLL_EXPORT TensorKey {
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


