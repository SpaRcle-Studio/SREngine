//
// Created by Monika on 27.08.2026.
//

#include <Engine/World/Terrain.h>

#include <Codegen/Terrain.generated.hpp>

namespace SR_CORE_NS {
    ITerrainChunk::ITerrainChunk()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    ITerrainGenerator::ITerrainGenerator()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    void Terrain::Update(float dt) {
        Super::Update(dt);
    }
}
