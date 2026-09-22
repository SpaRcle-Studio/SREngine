//
// Created by Monika on 18.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_MARCHING_CUBES_GENERATOR_H
#define SR_ENGINE_WORLD_TERRAIN_MARCHING_CUBES_GENERATOR_H

#include <Engine/World/Terrain.h>

#include <Utils/FileSystem/PathDataAccessor.h>

namespace SR_CORE_NS {
    class TerrainMarchingCubesGenerator : public ITerrainGenerator {
        using Super = ITerrainGenerator;
        SR_CLASS()
    public:

    private:
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_marchingCubesShader = "Samples/MarchingCubes/MarchingCubes.srsl";
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_densityShader = "Samples/MarchingCubes/Density.srsl";
        /// @property
        /// @customArgs(pick: enabled, filter name: Prefab, relative: resources)
        /// @customArg(filter value: prefab)

        /// @property @group(Density)
        uint32_t m_densityCountAxis = 64;
        /// @property @group(Density)
        uint32_t m_densityComputeGroups = 8;
        /// @property @group(Density)
        float_t m_noiseScale = 10.0f;
        /// @property @group(Density)
        int64_t m_seed = 1;
        /// @property @group(Density)
        float_t m_isoLevel = 0.2f;

        /// @property @group(SSBO)
        uint32_t m_numPointsPerAxis = 16;
        /// @property @group(SSBO)
        uint32_t m_vertexHashTableSize = 65536;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_MARCHING_CUBES_GENERATOR_H
