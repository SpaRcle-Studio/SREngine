#pragma once

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>

namespace SpaRcle::Scripts::Samples {
    enum class BlockSide {
        Top,
        Bottom,
        Front,
        Back,
        Right,
        Left
    };

    struct BlockFaceDef {
        SR_MATH_NS::FVector3 originOffset;
        SR_MATH_NS::FVector3 normal;
        SR_MATH_NS::FVector3 offsetU;
        SR_MATH_NS::FVector3 offsetV;
        BlockSide side;
    };

    static const BlockFaceDef BLOCK_FACES[] = {
            {{0, 1, 0}, {0,  1,  0},  {1, 0, 0}, {0, 0,  1},  BlockSide::Top},
            {{0, 0, 1}, {0,  -1, 0},  {1, 0, 0}, {0, 0,  -1}, BlockSide::Bottom},
            {{0, 1, 1}, {0,  0,  1},  {1, 0, 0}, {0, -1, 0},  BlockSide::Front},
            {{0, 0, 0}, {0,  0,  -1}, {1, 0, 0}, {0, 1,  0},  BlockSide::Back},
            {{1, 0, 0}, {1,  0,  0},  {0, 0, 1}, {0, 1,  0},  BlockSide::Right},
            {{0, 1, 0}, {-1, 0,  0},  {0, 0, 1}, {0, -1, 0},  BlockSide::Left}
    };

    static const SR_MATH_NS::IVector3 BLOCK_FACE_OFFSETS[] = {
            SR_MATH_NS::IVector3(0, 1, 0), // Top
            SR_MATH_NS::IVector3(0, -1, 0), // Bottom
            SR_MATH_NS::IVector3(0, 0, 1), // Front
            SR_MATH_NS::IVector3(0, 0, -1), // Back
            SR_MATH_NS::IVector3(1, 0, 0), // Right
            SR_MATH_NS::IVector3(-1, 0, 0)  // Left
    };

    struct BlockInfo {
        bool exists = false;
        uint8_t sides = 0;
        uint32_t offset = 0;
    };
}