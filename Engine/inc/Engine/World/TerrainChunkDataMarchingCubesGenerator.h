//
// Created by Monika on 18.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H
#define SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H

#include <Engine/World/Terrain.h>

#include <Graphics/Memory/SSBO.h>
#include <Graphics/Types/ComputeShader.h>

#include <Utils/FileSystem/PathDataAccessor.h>
#include <Utils/Common/Vertices.h>

namespace SR_CORE_NS {
    struct TerrainMarchingCubesVertex {
        SR_MATH_NS::FVector3 pos;
        float pad0;
        uint32_t materialID;
        uint32_t materialID2;
        float blend;
        float pad1;
    };

    struct TerrainMarchingCubesVoxel {
        float density;        /// текущая плотность
        uint32_t materialID;  /// основной материал
        uint32_t materialID2; /// дополнительный материал
        float blend;          /// смешивание между материалами
    };

    class TerrainMarchingCubesChunkData : public ITerrainChunkData {
        using Super = ITerrainChunkData;
        SR_CLASS()

    public:
        SR_NODISCARD SR_HTYPES_NS::FastMemoryArray<TerrainMarchingCubesVoxel>& GetVoxels() { return voxels; }

    private:
        SR_HTYPES_NS::FastMemoryArray<TerrainMarchingCubesVoxel> voxels;

    };

    /// @noCopyable
    class TerrainChunkDataMarchingCubesGenerator : public ITerrainChunkDataGenerator {
        using Super = ITerrainChunkDataGenerator;
        SR_CLASS()
    public:
        void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk) override;

    private:
        bool Init();

    private:
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_marchingCubesShader = "Samples/MarchingCubes/MarchingCubes.srsl";
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_densityShader = "Samples/MarchingCubes/Density.srsl";

        /// @property @group(Density)
        uint32_t m_densityCountAxis = 64;
        /// @property @group(Density)
        uint32_t m_densityComputeGroups = 8;
        /// @property @group(Density)
        float_t m_noiseScale = 13.0f;
        /// @property @group(Density)
        int64_t m_seed = 0;
        /// @property @group(Density)
        float_t m_isoLevel = 1.f;

        /// @property @group(SSBO)
        uint32_t m_numPointsPerAxis = 32;
        /// @property @group(SSBO)
        uint32_t m_vertexHashTableSize = 800000;

        /// @property
        SR_MATH_NS::FVector3 m_geometryScale = SR_MATH_NS::FVector3(1.0f, 1.0f, 1.0f);

    private:
        bool m_isInitialized = false;

        SR_UTILS_NS::VertexDataBuffer m_vertices;
        SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3> m_verticesPositions;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> m_optimizedIndices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> m_indices;
        SR_HTYPES_NS::FastMemoryArray<uint8_t> m_solidDensities;

        SR_GTYPES_NS::ComputeShader::Ptr m_pMarchingComputeShader = nullptr;
        SR_GTYPES_NS::ComputeShader::Ptr m_pDensityComputeShader = nullptr;

        SR_GRAPH_NS::SSBOInstance::Ptr m_pDensitySSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pHashTableSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pVerticesSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pIndicesSSBO = nullptr;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H
