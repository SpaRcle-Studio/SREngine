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
}

namespace SR_WORLD_NS {
    class Region;
    class Chunk;

    typedef std::unordered_map<TensorKey, std::vector<SR_HTYPES_NS::SharedPtr<GameObject>>> Tensor;
    typedef std::unordered_map<SR_MATH_NS::IVector3, Region*> Regions;
}

#endif //SR_ENGINE_TENSORKEY_H
