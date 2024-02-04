//
// Created by Monika on 25.03.2022.
//

#ifndef SR_ENGINE_SKYBOXCONSTANTS_H
#define SR_ENGINE_SKYBOXCONSTANTS_H

#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    /// TODO: use glm?

    struct Vec2 {
        float_t x, y;
    };

    struct Vec3 {
        float_t x, y, z;
    };

    struct Vertex {
        Vertex() = default;

        Vertex(int32_t x, int32_t y, int32_t z)
            : position(Vec3 { static_cast<float_t>(x), static_cast<float_t>(y), static_cast<float_t>(z) })
        { }

        Vertex(Vec3 pos, Vec2 uv, Vec3 norm, Vec3 tang, Vec3 btg)
            : position(pos)
            , uv(uv)
            , normal(norm)
            , tangent(tang)
            , bitangent(btg)
        { }

        Vec3 position;
        Vec2 uv;
        Vec3 normal;
        Vec3 tangent;
        Vec3 bitangent;
        uint8_t weightsNum = 0;
        struct {
            uint32_t boneId = 0;
            float weight = 0.f;
        } weights[SR_MAX_BONES_ON_VERTEX];
    };

    const std::vector<uint32_t> SKYBOX_INDICES = { 0,1,2,0,2,3,2,1,4,5,2,4,6,0,3,6,3,7,5,4,6,7,5,6,3,2,5,3,5,7,4,1,0,6,4,0 };
    const std::vector<Vertex> SKYBOX_INDEXED_VERTICES = {
            Vertex(1, -1, 1),
            Vertex(-1, -1, 1),
            Vertex(-1, 1, 1),
            Vertex(1, 1, 1),
            Vertex(-1, -1, -1),
            Vertex(-1, 1, -1),
            Vertex(1, -1, -1),
            Vertex(1, 1, -1),
    };

    std::vector<SR_MATH_NS::FVector3> ComputeConvexHull(const std::vector<Vertex>& vertices);

    template<typename T> static std::vector<T> IndexedVerticesToNonIndexed(
            const std::vector<T>& vertices,
            const std::vector<uint32_t>& indices)
    {
        auto rawVertices = std::vector<T>();

        for (const auto& index : indices)
            rawVertices.emplace_back(vertices[index]);

        return rawVertices;
    }
}

#endif //SR_ENGINE_SKYBOXCONSTANTS_H
