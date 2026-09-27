//
// Created by Monika on 18.09.2026.
//

#include <Engine/World/TerrainChunkDataMarchingCubesGenerator.h>
#include <Engine/World/TerrainChunkCube.h>
#include <Engine/World/TerrainGrass.h>

#include <Utils/ECS/GameObject.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>

#include <Physics/CollisionShape.h>
#include <Physics/3D/Rigidbody3D.h>

#include <Codegen/TerrainChunkDataMarchingCubesGenerator.generated.hpp>

namespace SR_CORE_NS {
    void ComputeSmoothNormals(SR_UTILS_NS::VertexDataBuffer& vertices, const SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices) {
        SR_TRACY_ZONE;

        static SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3> localSums;
        localSums.resize(vertices.GetVertexCount());
        std::memset(localSums.data(), 0, localSums.size() * sizeof(SR_MATH_NS::FVector3));

        // вычисляем нормали по треугольникам
        auto range1 = std::views::iota(SR_UTILS_NS::SizeType(0), SR_UTILS_NS::SizeType(indices.size() / 3));
        SR_UTILS_NS::ForEach<SR_UTILS_NS::ExecutionPolicy::Seq>(range1.begin(), range1.end(), [&](SR_UTILS_NS::SizeType t){
            uint32_t ia = indices[t * 3 + 0];
            uint32_t ib = indices[t * 3 + 1];
            uint32_t ic = indices[t * 3 + 2];

            SR_MATH_NS::FVector3 a = *(SR_MATH_NS::FVector3*)vertices.GetVertex(ia, SR_UTILS_NS::VertexAttribute::Position);
            SR_MATH_NS::FVector3 b = *(SR_MATH_NS::FVector3*)vertices.GetVertex(ib, SR_UTILS_NS::VertexAttribute::Position);
            SR_MATH_NS::FVector3 c = *(SR_MATH_NS::FVector3*)vertices.GetVertex(ic, SR_UTILS_NS::VertexAttribute::Position);

            SR_MATH_NS::FVector3 n = (SR_MATH_NS::FVector3::Cross(b - a, c - a)).Normalized();

            localSums[ia] += n;
            localSums[ib] += n;
            localSums[ic] += n;
        });

        // объединяем локальные суммы
        auto range2 = std::views::iota(SR_UTILS_NS::SizeType(0), SR_UTILS_NS::SizeType(vertices.GetVertexCount()));
        SR_UTILS_NS::ForEach<SR_UTILS_NS::ExecutionPolicy::ParUnSeq>(range2.begin(), range2.end(), [&](SR_UTILS_NS::SizeType index){
            SR_MATH_NS::FVector3 normal = localSums[index].Normalized();
            SR_MATH_NS::FVector3 tangent = SR_MATH_NS::FVector3::Cross(normal, SR_MATH_NS::FVector3(0, 1, 0)).Normalized();
            vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::Normal, &normal);
            vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::Tangent, &tangent);
        });
    }

    void TerrainChunkDataMarchingCubesGenerator::GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, float_t distance) {
        SR_TRACY_ZONE;

        if (!Init()) {
            return;
        }

        auto&& pCubeChunk = dynamic_cast<TerrainChunkCube*>(&chunk);
        if (!pCubeChunk) {
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::GenerateChunkData() : marching cubes generator can only generate data for TerrainChunkCube!");
            return;
        }

        if (!chunk.GetData()) {
            chunk.SetData(new TerrainMarchingCubesChunkData());
            chunk.GetData()->SetChunk(&chunk);
        }

        auto&& pChunkData = chunk.GetData().DynamicCast<TerrainMarchingCubesChunkData>();
        auto&& pChunkObject = chunk.GetObject();
        auto&& voxels = pChunkData->GetVoxels();
        auto&& position = pCubeChunk->GetPosition();

        static SR_UTILS_NS::String positionText;
        positionText.clear();
        SR_UTILS_NS::FormatTo(positionText, "{}, {}, {}", position.x, position.y, position.z);
        SR_TRACY_ZONE_TEXT(positionText);

        if (voxels.empty()) {
            SR_TRACY_ZONE_N("Compute density");

            const auto densitiesCount = static_cast<uint64_t>(std::pow(m_densityCountAxis, 3));
            if (densitiesCount == 0) {
                SR_WARN("ChunkManager::GenerateChunkDensity() : densityCountAxis must be greater than 0!");
                return;
            }

            m_pDensitySSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVoxel>(densitiesCount, SR_GRAPH_NS::SSBOUsage::AutoPreferDevice, "voxels");
            m_pDensitySSBO->Memset(0);

            if (m_pDensityComputeShader->BeginCompute()) {
                m_pDensitySSBO->Bind();
                m_pDensityComputeShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(m_densityCountAxis));
                m_pDensityComputeShader->GetShader()->SetConstInt("seed"_atom, static_cast<int>(m_seed));
                m_pDensityComputeShader->GetShader()->SetConstFloat("isoLevel"_atom, m_isoLevel);
                m_pDensityComputeShader->GetShader()->SetConstFloat("noiseScale"_atom, m_noiseScale);
                m_pDensityComputeShader->GetShader()->SetConstIVec3("chunkCoord"_atom, position);
                m_pDensityComputeShader->Dispatch(m_densityComputeGroups, m_densityComputeGroups, m_densityComputeGroups);
                m_pDensityComputeShader->EndCompute();
            }

            voxels.resize(densitiesCount);
            if (m_pDensitySSBO->Map()) {
                std::memcpy(voxels.data(), m_pDensitySSBO->GetMappedData(), densitiesCount * sizeof(TerrainMarchingCubesVoxel));
                m_pDensitySSBO->UnMap();
            }
        }
        else {
            SR_TRACY_ZONE_N("Upload density");

            if (m_pDensitySSBO->Map()) {
                std::memcpy(m_pDensitySSBO->GetMappedData(), voxels.data(), voxels.size() * sizeof(TerrainMarchingCubesVoxel));
                m_pDensitySSBO->Flush();
                m_pDensitySSBO->UnMap();
            }
        }

        {
            SR_TRACY_ZONE_N("Compute geometry");

            int32_t numVoxelsPerAxis = static_cast<int32_t>(m_numPointsPerAxis) - 1;
            if (numVoxelsPerAxis <= 0) {
                return;
            }

            m_pHashTableSSBO->Memset(-1);

            for (int stage = 0; stage <= 1; ++stage) {
                if (m_pMarchingComputeShader->BeginCompute()) {
                    m_pDensitySSBO->Bind();
                    m_pHashTableSSBO->Bind();
                    m_pVerticesSSBO->Bind();
                    m_pIndicesSSBO->Bind();
                    m_pMarchingComputeShader->GetShader()->SetConstInt("vertexHashTableSize"_atom, static_cast<int>(m_vertexHashTableSize));
                    m_pMarchingComputeShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(m_densityCountAxis));
                    m_pMarchingComputeShader->GetShader()->SetConstFloat("isoLevel"_atom, m_isoLevel);
                    m_pMarchingComputeShader->GetShader()->SetConstInt(SR_GRAPH_NS::SHADER_COMPUTE_STAGE, stage);
                    m_pMarchingComputeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                    m_pMarchingComputeShader->EndCompute();
                }
            }
        }

        {
            SR_TRACY_ZONE_N("Read indices");

            if (void* pData = m_pIndicesSSBO->MapData()) {
                const uint32_t indicesCount = m_pIndicesSSBO->GetCounter();
                m_indices.resize(indicesCount);
                std::memcpy(m_indices.data(), pData, sizeof(uint32_t) * indicesCount);
                m_pIndicesSSBO->ResetCounter();
                m_pIndicesSSBO->FlushCounter();
                m_pIndicesSSBO->UnMap();
            }
        }

        {
            SR_TRACY_ZONE_N("Read vertices");

            if (auto&& pVertices = reinterpret_cast<TerrainMarchingCubesVertex*>(m_pVerticesSSBO->MapData())) {
                m_vertices.SetLayout(SR_UTILS_NS::VertexLayoutDescription()
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::Normal, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::Tangent, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::MaterialID0, SR_UTILS_NS::VertexAttributeFormat::UInt32, 1)
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::MaterialID1, SR_UTILS_NS::VertexAttributeFormat::UInt32, 1)
                    .AddAttribute(SR_UTILS_NS::VertexAttribute::BlendFactor, SR_UTILS_NS::VertexAttributeFormat::Float32, 1)
                );
                const uint32_t verticesCount = m_pVerticesSSBO->GetCounter();
                m_vertices.Allocate(verticesCount);

                auto&& range = std::views::iota(0, static_cast<int>(verticesCount));

                SR_UTILS_NS::ForEach<SR_UTILS_NS::ExecutionPolicy::ParUnSeq>(range.begin(), range.end(), [&](int index) {
                    const TerrainMarchingCubesVertex& vertex = pVertices[index];
                    m_vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::Position, &vertex.pos);
                    m_vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::MaterialID0, &vertex.materialID);
                    m_vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::MaterialID1, &vertex.materialID2);
                    m_vertices.SetVertex(index, SR_UTILS_NS::VertexAttribute::BlendFactor, &vertex.blend);
                });

                m_pVerticesSSBO->ResetCounter();
                m_pVerticesSSBO->FlushCounter();
                m_pVerticesSSBO->UnMap();
            }
        }

        ComputeSmoothNormals(m_vertices, m_indices);

        {
            SR_TRACY_ZONE_N("Update chunk object");

            auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>();
            auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
            auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>();

            if (!pCollisionShape || !pProceduralMesh || !pRigidBody) {
                SR_ERROR("ChunkManager::GenerateChunk() : chunk object must have CollisionShape and ProceduralMesh components!");
                return;
            }

            m_verticesPositions.resize(m_vertices.GetVertexCount());
            auto&& positionsRange = std::views::iota(0, static_cast<int>(m_vertices.GetVertexCount()));
            std::ranges::transform(positionsRange, m_verticesPositions.begin(), [this](uint32_t index) {
                SR_MATH_NS::FVector3 pos = *(SR_MATH_NS::FVector3*)m_vertices.GetVertex(index, SR_UTILS_NS::VertexAttribute::Position);
                return pos * m_geometryScale;
            });

            SR_UTILS_NS::OptimizeVertices(m_verticesPositions, m_indices, m_indices.size() / 4, 1e-2f, m_optimizedIndices);

            if (m_verticesPositions.empty() || m_optimizedIndices.empty()) {
                if (auto&& pGrass = terrain.GetGrass()) {
                    pGrass->OnChunkGenerated(terrain, chunk, TerrainGrassSourceMesh());
                }
                pProceduralMesh->SetEnabled(false);
                pCollisionShape->SetEnabled(false);
                pRigidBody->SetEnabled(false);
                return;
            }

            pProceduralMesh->SetEnabled(true);
            pCollisionShape->SetEnabled(true);
            pRigidBody->SetEnabled(true);

            pCollisionShape->SwapCustomTriangleMeshVertices(m_verticesPositions);
            pCollisionShape->SwapCustomTriangleMeshIndices(m_optimizedIndices);

            if (auto&& pGrass = terrain.GetGrass()) {
                SR_TRACY_ZONE_N("Prepare grass source");

                /// Трава генерируется по тому же мешу, что рисуется ProceduralMesh (m_geometryScale относится только к физике),
                /// в мировых осях относительно объекта чанка. Поворот объекта чанка не поддерживается.
                SR_MATH_NS::FVector3 chunkScale(1.f);
                SR_MATH_NS::FVector3 chunkOrigin;
                if (auto&& pGameObject = pChunkObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
                    if (auto&& pTransform = pGameObject->GetTransform()) {
                        chunkScale = pTransform->GetScale();
                        chunkOrigin = pTransform->GetTranslation();
                    }
                }

                const SR_MATH_NS::FVector3 scale = chunkScale;
                const uint64_t vertexCount = m_vertices.GetVertexCount();

                TerrainGrassSourceMesh grassMesh;
                grassMesh.origin = chunkOrigin;
                /// Воксель в локальных осях меша имеет размер 1, диагональ куба - sqrt(3)
                const float_t maxScale = std::max({ std::abs(scale.x), std::abs(scale.y), std::abs(scale.z) });
                grassMesh.maxEdgeLength = 1.8f * maxScale;
                /// Полезная область вокселей чанка: координаты [1, densityCountAxis - 1] -> локальные [0.5, densityCountAxis - 1.5]
                const float_t innerMin = 0.5f;
                const float_t innerMax = static_cast<float_t>(m_densityCountAxis) - 1.5f;
                grassMesh.bounds = SR_MATH_NS::AABB(
                    SR_MATH_NS::FVector3(innerMin) * scale - SR_MATH_NS::FVector3(0.01f),
                    SR_MATH_NS::FVector3(innerMax) * scale + SR_MATH_NS::FVector3(0.01f)
                );
                grassMesh.positions.resize(vertexCount);
                grassMesh.normals.resize(vertexCount);
                grassMesh.materials.resize(vertexCount);

                for (uint64_t i = 0; i < vertexCount; ++i) {
                    const auto position = *static_cast<SR_MATH_NS::FVector3*>(m_vertices.GetVertex(i, SR_UTILS_NS::VertexAttribute::Position));
                    const auto normal = *static_cast<SR_MATH_NS::FVector3*>(m_vertices.GetVertex(i, SR_UTILS_NS::VertexAttribute::Normal));
                    grassMesh.positions[i] = position * scale;
                    /// неравномерный масштаб: нормаль преобразуется обратным масштабом
                    grassMesh.normals[i] = (normal / scale).Normalized();
                    grassMesh.materials[i] = *static_cast<uint32_t*>(m_vertices.GetVertex(i, SR_UTILS_NS::VertexAttribute::MaterialID0));
                }

                grassMesh.indices.assign(m_indices.begin(), m_indices.end());

                pGrass->OnChunkGenerated(terrain, chunk, std::move(grassMesh));
            }

            pProceduralMesh->SwapIndices(m_indices);
            pProceduralMesh->SetIndexedVertices(m_vertices);
        }
    }

    bool TerrainChunkDataMarchingCubesGenerator::Init() {
        SR_TRACY_ZONE;

        if (m_isInitialized) {
            return true;
        }

        m_pMarchingComputeShader = SR_GTYPES_NS::ComputeShader::Load(m_marchingCubesShader);
        m_pDensityComputeShader = SR_GTYPES_NS::ComputeShader::Load(m_densityShader);

        if (!m_pMarchingComputeShader || !m_pDensityComputeShader) {
            SRHalt("Failed to load compute shaders for Marching Cubes!");
            return false;
        }

        const int numVoxelsPerAxis = static_cast<int>(m_numPointsPerAxis) - 1;
        if (numVoxelsPerAxis <= 0) {
            SRHalt("ChunkManager::ReInit() : numPointsPerAxis must be greater than 1!");
            return false;
        }

        const int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
        const int maxTriangleCount = numVoxels * 5;
        const int maxVertexCount = maxTriangleCount * 3;

        m_pHashTableSSBO.reset();
        m_pVerticesSSBO.reset();
        m_pIndicesSSBO.reset();

        m_pHashTableSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(m_vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "hashTable");
        m_pVerticesSSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVertex>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "vertices", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
        m_pIndicesSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "indices", SR_GRAPH_NS::SSBOFlags::Counter);

        m_isInitialized = true;
        return true;
    }

    void TerrainMarchingCubesChunkData::SwitchPhysics(bool enable) {
        if (auto&& pChunkObject = m_chunk->GetObject()) {
            if (auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>()) {
                pCollisionShape->SetEnabled(enable);
            }
            if (auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>()) {
                pRigidBody->SetEnabled(enable);
            }
        }
    }

    void TerrainMarchingCubesChunkData::Deactivate() {
        Super::Deactivate();
        m_voxels.clear();
        if (auto&& pChunkObject = m_chunk->GetObject()) {
            if (auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>()) {
                pCollisionShape->SetEnabled(false);
            }
            if (auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                pProceduralMesh->SetEnabled(false);
            }
            if (auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>()) {
                pRigidBody->SetEnabled(false);
            }
        }
    }
}