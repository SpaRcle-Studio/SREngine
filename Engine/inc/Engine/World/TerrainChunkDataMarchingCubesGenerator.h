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
#include <Utils/Math/Vector4.h>

namespace SR_CORE_NS {
    struct TerrainMarchingCubesVertex {
        SR_MATH_NS::FVector3 pos;
        float pad0;
        SR_MATH_NS::FVector4 weights; /// веса материалов (почва, камень, песок, -)
    };

    struct TerrainMarchingCubesVoxel {
        float density;
        float weights[3]; /// веса материалов (почва, камень, песок)
    };

    class TerrainMarchingCubesChunkData : public ITerrainChunkData {
        using Super = ITerrainChunkData;
        SR_CLASS()

    public:
        void Deactivate() override;
        void SwitchPhysics(bool enable) override;
        SR_NODISCARD bool IsPhysicsEnabled() const override { return m_isPhysicsEnabled; }
        SR_NODISCARD bool IsRenderReady() const override;

        /// Коллизия строится лениво из меша ProceduralMesh при первом включении физики
        void SetCollisionSettings(bool allowed, const SR_MATH_NS::FVector3& scale, float_t simplifyRatio, float_t simplifyError, uint64_t indicesCount);

    private:
        bool BuildCollision();

    private:
        SR_MATH_NS::FVector3 m_collisionScale = SR_MATH_NS::FVector3(1.f);
        float_t m_simplifyRatio = 0.25f;
        float_t m_simplifyError = 1e-2f;
        uint64_t m_collisionIndicesCount = 0; /// индексы меша без юбок
        bool m_isCollisionAllowed = false;
        bool m_isCollisionBuilt = false;
        bool m_isPhysicsEnabled = false;

    };

    /// @noCopyable
    class TerrainChunkDataMarchingCubesGenerator : public ITerrainChunkDataGenerator {
        using Super = ITerrainChunkDataGenerator;
        SR_CLASS()
    public:
        void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) override;

    private:
        bool Init();

    private:
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_marchingCubesShader = "Engine/Shaders/MarchingCubes/MarchingCubes.srsl";
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_densityShader = "Engine/Shaders/MarchingCubes/Density.srsl";

        /// @property @group(Density)
        uint32_t m_densityCountAxis = 64;
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
        SR_MATH_NS::FVector3 m_geometryScale = SR_MATH_NS::FVector3(2.f);
        /// @property @group(Physics) @range(0.01f, 1.f) @tooltip(Доля треугольников, остающаяся в меше коллизии)
        float_t m_collisionSimplifyRatio = 0.25f;
        /// @property @group(Physics) @range(0.f, 1.f)
        float_t m_collisionSimplifyError = 1e-2f;
        /// @property @range(0.f, 16.f) @tooltip(Глубина юбок на стыках чанков в вокселях чанка. Закрывает щели между LOD)
        float_t m_skirtDepth = 1.5f;

    private:
        bool m_isInitialized = false;

        SR_UTILS_NS::VertexDataBuffer m_vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> m_indices;
        SR_HTYPES_NS::FastMemoryArray<float_t> m_densityOffsets;

        SR_GTYPES_NS::ComputeShader::Ptr m_pMarchingComputeShader = nullptr;
        SR_GTYPES_NS::ComputeShader::Ptr m_pDensityComputeShader = nullptr;

        SR_GRAPH_NS::SSBOInstance::Ptr m_pDensitySSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pDensityOffsetsSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pHashTableSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pVerticesSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr m_pIndicesSSBO = nullptr;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H
