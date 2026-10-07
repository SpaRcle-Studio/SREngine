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
    /// Вершина меша террейна. Совпадает с layout'ом из GenerateChunkData (VertexLayoutDescription выравнивает атрибуты по 16 байт)
    struct TerrainMeshVertex {
        SR_MATH_NS::FVector3 position;
        float_t pad0;
        SR_MATH_NS::FVector3 normal;
        float_t pad1;
        SR_MATH_NS::FVector4 tangent;
        SR_MATH_NS::FVector4 weights;
    };
    static_assert(sizeof(TerrainMeshVertex) == 64);

    static void ComputeSmoothNormals(TerrainMeshVertex* pVertices, uint64_t vertexCount, const SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices) {
        SR_TRACY_ZONE;

        for (uint64_t i = 0; i < vertexCount; ++i) {
            pVertices[i].normal = SR_MATH_NS::FVector3(0.f);
        }

        for (uint64_t t = 0; t + 2 < indices.size(); t += 3) {
            const uint32_t ia = indices[t + 0];
            const uint32_t ib = indices[t + 1];
            const uint32_t ic = indices[t + 2];

            const SR_MATH_NS::FVector3 a = pVertices[ia].position;
            const SR_MATH_NS::FVector3 b = pVertices[ib].position;
            const SR_MATH_NS::FVector3 c = pVertices[ic].position;

            /// Ненормированное векторное произведение - вклад пропорционален площади треугольника
            const SR_MATH_NS::FVector3 n = SR_MATH_NS::FVector3::Cross(b - a, c - a);

            pVertices[ia].normal += n;
            pVertices[ib].normal += n;
            pVertices[ic].normal += n;
        }

        for (uint64_t i = 0; i < vertexCount; ++i) {
            const SR_MATH_NS::FVector3 normal = pVertices[i].normal.Normalized();
            SR_MATH_NS::FVector3 tangent = SR_MATH_NS::FVector3::Cross(normal, SR_MATH_NS::FVector3(0, 1, 0));
            if (tangent.LengthSq() < 1e-6f) {
                tangent = SR_MATH_NS::FVector3(1, 0, 0);
            }
            tangent = tangent.Normalized();
            pVertices[i].normal = normal;
            pVertices[i].tangent = SR_MATH_NS::FVector4(tangent.x, tangent.y, tangent.z, 1.f);
        }
    }

    /// Юбки на стыках чанков: каждое открытое ребро меша, лежащее на грани чанка, вытягивается внутрь чанка.
    /// Закрывает щели между соседями разного LOD (у них разная сетка, и вершины на общей грани не совпадают).
    static void AddSkirts(SR_UTILS_NS::VertexDataBuffer& vertices, SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices, uint32_t densityCountAxis, float_t skirtDepth, uint32_t facesMask) {
        SR_TRACY_ZONE;

        if (skirtDepth <= 0.f || indices.empty() || facesMask == 0) {
            return;
        }

        auto&& pVertices = reinterpret_cast<TerrainMeshVertex*>(vertices.data.data());
        const uint64_t vertexCount = vertices.GetVertexCount();

        /// Полезная область вокселей чанка [1, N - 1] - вершины на её гранях лежат в локальных координатах 0.5 и N - 1.5
        const float_t minBound = 0.5f;
        const float_t maxBound = static_cast<float_t>(densityCountAxis) - 1.5f;
        constexpr float_t epsilon = 1e-3f;

        auto&& getBorderMask = [&](const SR_MATH_NS::FVector3& position) -> uint32_t {
            uint32_t mask = 0;
            for (uint32_t axis = 0; axis < 3; ++axis) {
                if (position[axis] <= minBound + epsilon) {
                    mask |= 1u << (axis * 2);
                }
                else if (position[axis] >= maxBound - epsilon) {
                    mask |= 1u << (axis * 2 + 1);
                }
            }
            return mask;
        };

        /// Ребро считается открытым, если встречается ровно в одном треугольнике
        static SR_HTYPES_NS::FlatHashMap<uint64_t, uint32_t> edgeCount;
        edgeCount.clear();
        edgeCount.reserve(indices.size());

        auto&& makeKey = [](uint32_t a, uint32_t b) {
            return a < b ? (static_cast<uint64_t>(a) << 32) | b : (static_cast<uint64_t>(b) << 32) | a;
        };

        for (uint64_t t = 0; t + 2 < indices.size(); t += 3) {
            for (uint32_t e = 0; e < 3; ++e) {
                ++edgeCount[makeKey(indices[t + e], indices[t + (e + 1) % 3])];
            }
        }

        static SR_HTYPES_NS::FastMemoryArray<uint32_t> skirtVertex;
        skirtVertex.resize(vertexCount);
        std::memset(skirtVertex.data(), 0xFF, skirtVertex.size() * sizeof(uint32_t));

        static SR_UTILS_NS::Vector<TerrainMeshVertex> newVertices;
        static SR_HTYPES_NS::FastMemoryArray<uint32_t> newIndices;
        newVertices.clear();
        newIndices.clear();

        auto&& getSkirtVertex = [&](uint32_t index) -> uint32_t {
            if (skirtVertex[index] == SR_UINT32_MAX) {
                TerrainMeshVertex vertex = pVertices[index];
                vertex.position.y -= skirtDepth;
                skirtVertex[index] = static_cast<uint32_t>(vertexCount + newVertices.size());
                newVertices.emplace_back(vertex);
            }
            return skirtVertex[index];
        };

        const uint64_t trianglesCount = indices.size();
        for (uint64_t t = 0; t + 2 < trianglesCount; t += 3) {
            for (uint32_t e = 0; e < 3; ++e) {
                const uint32_t a = indices[t + e];
                const uint32_t b = indices[t + (e + 1) % 3];

                /// Оба конца ребра должны лежать на одной и той же грани чанка
                /// Только грани с соседом другого LOD: между чанками одного LOD щелей нет
                const uint32_t commonMask = getBorderMask(pVertices[a].position) & getBorderMask(pVertices[b].position) & facesMask;
                if (commonMask == 0) {
                    continue;
                }

                if (edgeCount[makeKey(a, b)] != 1) {
                    continue;
                }

                const uint32_t sa = getSkirtVertex(a);
                const uint32_t sb = getSkirtVertex(b);

                /// Юбка односторонняя и смотрит наружу, к соседнему чанку: оттуда щель видна из воздуха.
                /// Изнутри чанка (в т.ч. из-под земли) она отсекается как изнанка.
                uint32_t faceBit = 0;
                while ((commonMask & (1u << faceBit)) == 0) {
                    ++faceBit;
                }
                SR_MATH_NS::FVector3 outward(0.f);
                outward[static_cast<int>(faceBit / 2)] = (faceBit % 2) ? 1.f : -1.f;

                /// Лицевая сторона определяется так же, как нормали поверхности в ComputeSmoothNormals
                const SR_MATH_NS::FVector3 pa = pVertices[a].position;
                const SR_MATH_NS::FVector3 pb = pVertices[b].position;
                const SR_MATH_NS::FVector3 psa = pa - SR_MATH_NS::FVector3(0.f, skirtDepth, 0.f);
                const bool isFront = SR_MATH_NS::FVector3::Cross(pb - pa, psa - pa).Dot(outward) > 0.f;

                const uint32_t quad[6] = { a, b, sa, sa, b, sb };
                const uint32_t quadFlipped[6] = { b, a, sa, b, sa, sb };
                for (auto&& index : isFront ? quad : quadFlipped) {
                    newIndices.push_back(index);
                }
            }
        }

        if (newVertices.empty()) {
            return;
        }

        vertices.data.resize((vertexCount + newVertices.size()) * sizeof(TerrainMeshVertex));
        vertices.vertexCount = vertexCount + newVertices.size();
        std::memcpy(vertices.data.data() + vertexCount * sizeof(TerrainMeshVertex), newVertices.data(), newVertices.size() * sizeof(TerrainMeshVertex));

        const uint64_t oldIndicesCount = indices.size();
        indices.resize(oldIndicesCount + newIndices.size());
        std::memcpy(indices.data() + oldIndicesCount, newIndices.data(), newIndices.size() * sizeof(uint32_t));
    }

    void TerrainChunkDataMarchingCubesGenerator::GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) {
        SR_TRACY_ZONE;

        if (!Init()) {
            return;
        }

        auto&& pCubeChunk = dynamic_cast<TerrainChunkCube*>(&chunk);
        if (!pCubeChunk) {
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::GenerateChunkData() : marching cubes generator can only generate data for TerrainChunkCube!");
            return;
        }

        auto&& pChunkGenerator = terrain.GetChunkGenerator();
        if (!pChunkGenerator) {
            return;
        }

        if (!chunk.GetData()) {
            chunk.SetData(new TerrainMarchingCubesChunkData());
            chunk.GetData()->SetChunk(&chunk);
        }

        auto&& pChunkData = chunk.GetData().DynamicCast<TerrainMarchingCubesChunkData>();
        auto&& position = pCubeChunk->GetPosition();
        const int32_t lodScale = pCubeChunk->GetLodScale();
        const uint32_t groups = (m_densityCountAxis + 7) / 8;

        static SR_UTILS_NS::String positionText;
        positionText.clear();
        SR_UTILS_NS::FormatTo(positionText, "{}, {}, {} lod {}", position.x, position.y, position.z, pCubeChunk->GetLod());
        SR_TRACY_ZONE_TEXT(positionText);

        /// Плотность живёт только на GPU: на CPU она не нужна, а хранение кеша стоило по 4 МБ на чанк
        {
            SR_TRACY_ZONE_N("Compute density");

            if (m_pDensityComputeShader->BeginCompute()) {
                m_pDensitySSBO->Bind();
                m_pDensityComputeShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(m_densityCountAxis));
                m_pDensityComputeShader->GetShader()->SetConstInt("seed"_atom, static_cast<int>(m_seed));
                m_pDensityComputeShader->GetShader()->SetConstInt("lodScale"_atom, lodScale);
                m_pDensityComputeShader->GetShader()->SetConstFloat("isoLevel"_atom, m_isoLevel);
                m_pDensityComputeShader->GetShader()->SetConstFloat("noiseScale"_atom, m_noiseScale);
                m_pDensityComputeShader->GetShader()->SetConstIVec3("chunkCoord"_atom, position);
                m_pDensityComputeShader->Dispatch(groups, groups, groups);
                m_pDensityComputeShader->EndCompute();
            }
        }

        {
            SR_TRACY_ZONE_N("Compute geometry");

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
                    m_pMarchingComputeShader->Dispatch(groups, groups, groups);
                    m_pMarchingComputeShader->EndCompute();
                }
            }
        }

        {
            SR_TRACY_ZONE_N("Read indices");

            m_indices.clear();
            if (void* pData = m_pIndicesSSBO->MapData()) {
                const uint32_t indicesCount = m_pIndicesSSBO->GetCounter();
                m_indices.resize(indicesCount);
                std::memcpy(m_indices.data(), pData, sizeof(uint32_t) * indicesCount);
                m_pIndicesSSBO->ResetCounter();
                m_pIndicesSSBO->FlushCounter();
                m_pIndicesSSBO->UnMap();
            }
        }

        uint32_t verticesCount = 0;

        if (!m_indices.empty()) {
            SR_TRACY_ZONE_N("Read vertices");

            m_vertices.SetLayout(SR_UTILS_NS::VertexLayoutDescription()
                .AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                .AddAttribute(SR_UTILS_NS::VertexAttribute::Normal, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                .AddAttribute(SR_UTILS_NS::VertexAttribute::Tangent, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
                .AddAttribute(SR_UTILS_NS::VertexAttribute::MaterialWeights, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
            );

            if (m_vertices.GetLayout().GetStride() != sizeof(TerrainMeshVertex)) {
                SRHalt("TerrainChunkDataMarchingCubesGenerator::GenerateChunkData() : invalid vertex layout stride!");
                return;
            }

            if (auto&& pGpuVertices = reinterpret_cast<TerrainMarchingCubesVertex*>(m_pVerticesSSBO->MapData())) {
                verticesCount = m_pVerticesSSBO->GetCounter();
                m_vertices.Allocate(verticesCount);

                auto&& pVertices = reinterpret_cast<TerrainMeshVertex*>(m_vertices.data.data());
                for (uint32_t i = 0; i < verticesCount; ++i) {
                    pVertices[i].position = pGpuVertices[i].pos;
                    pVertices[i].weights = pGpuVertices[i].weights;
                }

                m_pVerticesSSBO->ResetCounter();
                m_pVerticesSSBO->FlushCounter();
                m_pVerticesSSBO->UnMap();
            }
        }
        else {
            /// Без маппинга ResetCounter сам мапит, флашит и анмапит буфер
            m_pVerticesSSBO->ResetCounter();
        }

        if (verticesCount == 0) {
            /// Пустой чанк: объект сцены и память под меш не нужны, объект возвращается в пул
            pChunkGenerator->ReleaseChunkObject(chunk);
            return;
        }

        auto&& pVertices = reinterpret_cast<TerrainMeshVertex*>(m_vertices.data.data());

        ComputeSmoothNormals(pVertices, verticesCount, m_indices);

        auto&& pChunkObject = pChunkGenerator->AcquireChunkObject(chunk);
        if (!pChunkObject) {
            return;
        }

        auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
        if (!pProceduralMesh) {
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::GenerateChunkData() : chunk object must have ProceduralMesh component!");
            return;
        }

        if (auto&& pGrass = terrain.GetGrass()) {
            /// Трава только для детальных чанков: на дальних LOD она всё равно отсекается дистанцией
            if (pCubeChunk->GetLod() == 0) {
                SR_TRACY_ZONE_N("Prepare grass source");

                /// Трава генерируется по тому же мешу, что рисуется ProceduralMesh (m_geometryScale относится только к физике),
                /// в мировых осях относительно объекта чанка. Поворот объекта чанка не поддерживается.
                SR_MATH_NS::FVector3 scale(1.f);
                SR_MATH_NS::FVector3 chunkOrigin;
                if (auto&& pGameObject = pChunkObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
                    if (auto&& pTransform = pGameObject->GetTransform()) {
                        scale = pTransform->GetScale();
                        chunkOrigin = pTransform->GetTranslation();
                    }
                }

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
                grassMesh.positions.resize(verticesCount);
                grassMesh.normals.resize(verticesCount);
                grassMesh.materials.resize(verticesCount);
                grassMesh.materials2.resize(verticesCount);
                grassMesh.blends.resize(verticesCount);

                for (uint32_t i = 0; i < verticesCount; ++i) {
                    auto&& vertex = pVertices[i];
                    grassMesh.positions[i] = vertex.position * scale;
                    /// неравномерный масштаб: нормаль преобразуется обратным масштабом
                    grassMesh.normals[i] = (vertex.normal / scale).Normalized();

                    /// Два доминирующих материала из весов
                    const float_t w[3] = { vertex.weights.x, vertex.weights.y, vertex.weights.z };
                    uint32_t a = 0;
                    for (uint32_t m = 1; m < 3; ++m) {
                        if (w[m] > w[a]) {
                            a = m;
                        }
                    }
                    uint32_t b = a == 0 ? 1 : 0;
                    for (uint32_t m = 0; m < 3; ++m) {
                        if (m != a && w[m] > w[b]) {
                            b = m;
                        }
                    }
                    grassMesh.materials[i] = a;
                    grassMesh.materials2[i] = b;
                    grassMesh.blends[i] = w[b] / std::max(w[a] + w[b], 1e-6f);
                }

                grassMesh.indices.assign(m_indices.begin(), m_indices.end());

                pGrass->OnChunkGenerated(terrain, chunk, std::move(grassMesh));
            }
            else {
                /// Объект мог прийти из пула с травой и источником прошлого чанка - их нужно сбросить,
                /// иначе перегенерация нарисует траву старого меша на новом месте (двойная трава)
                pGrass->OnChunkGenerated(terrain, chunk, TerrainGrassSourceMesh());
            }
        }

        /// Юбки только в рендер-меше: трава уже скопировала меш, коллизия строится из сетки LOD0 без щелей
        const uint64_t surfaceIndicesCount = m_indices.size();
        AddSkirts(m_vertices, m_indices, m_densityCountAxis, m_skirtDepth, pCubeChunk->GetLodBorders());

        /// Сначала данные, потом включение: так меш регистрируется в рендере сразу готовым, без отложенной перерегистрации
        pProceduralMesh->SetEnabled(false);
        pProceduralMesh->SwapIndices(m_indices);
        pProceduralMesh->SetIndexedVertices(m_vertices);
        pProceduralMesh->SetEnabled(true);

        /// Коллизия нужна только у детальных чанков и строится лениво при входе в зону физики (см. UpdatePhysics генератора чанков):
        /// упрощение меша и кукинг PhysX - самая дорогая часть, для дальних чанков она не нужна вовсе.
        pChunkData->SetCollisionSettings(pCubeChunk->GetLod() == 0, m_geometryScale, m_collisionSimplifyRatio, m_collisionSimplifyError, surfaceIndicesCount);
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

        const uint64_t densitiesCount = static_cast<uint64_t>(m_densityCountAxis) * m_densityCountAxis * m_densityCountAxis;
        if (m_densityCountAxis < 3) {
            SRHalt("TerrainChunkDataMarchingCubesGenerator::Init() : densityCountAxis must be greater than 2!");
            return false;
        }

        const int numVoxelsPerAxis = static_cast<int>(m_numPointsPerAxis) - 1;
        if (numVoxelsPerAxis <= 0) {
            SRHalt("TerrainChunkDataMarchingCubesGenerator::Init() : numPointsPerAxis must be greater than 1!");
            return false;
        }

        const int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
        const int maxTriangleCount = numVoxels * 5;
        const int maxVertexCount = maxTriangleCount * 3;

        m_pDensitySSBO.reset();
        m_pHashTableSSBO.reset();
        m_pVerticesSSBO.reset();
        m_pIndicesSSBO.reset();

        m_pDensitySSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVoxel>(densitiesCount, SR_GRAPH_NS::SSBOUsage::AutoPreferDevice, "voxels");
        m_pHashTableSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(m_vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "hashTable");
        m_pVerticesSSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVertex>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "vertices", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
        m_pIndicesSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "indices", SR_GRAPH_NS::SSBOFlags::Counter);

        m_isInitialized = true;
        return true;
    }

    void TerrainMarchingCubesChunkData::SetCollisionSettings(bool allowed, const SR_MATH_NS::FVector3& scale, float_t simplifyRatio, float_t simplifyError, uint64_t indicesCount) {
        m_collisionIndicesCount = indicesCount;
        /// Объект мог прийти из прототипа с включённой физикой, но без меша коллизии
        if (auto&& pChunkObject = m_chunk->GetObject()) {
            if (auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>()) {
                pCollisionShape->SetEnabled(false);
            }
            if (auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>()) {
                pRigidBody->SetEnabled(false);
            }
        }

        m_isPhysicsEnabled = false;
        m_isCollisionAllowed = allowed;
        m_isCollisionBuilt = false;
        m_collisionScale = scale;
        m_simplifyRatio = simplifyRatio;
        m_simplifyError = simplifyError;
    }

    bool TerrainMarchingCubesChunkData::BuildCollision() {
        SR_TRACY_ZONE;

        auto&& pChunkObject = m_chunk->GetObject();
        if (!pChunkObject) {
            return false;
        }

        auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>();
        auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
        if (!pCollisionShape || !pProceduralMesh) {
            return false;
        }

        auto&& vertices = pProceduralMesh->GetVertices();
        auto&& meshIndices = pProceduralMesh->GetIndices();
        auto&& pPositionDesc = vertices.GetLayout().Find(SR_UTILS_NS::VertexAttribute::Position);
        const uint64_t verticesCount = vertices.GetVertexCount();
        const uint64_t indicesCount = std::min<uint64_t>(m_collisionIndicesCount, meshIndices.size());

        if (!pPositionDesc || verticesCount == 0 || indicesCount == 0) {
            return false;
        }

        /// Юбки в конце индексного буфера в коллизию не попадают
        static SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;
        indices.resize(indicesCount);
        std::memcpy(indices.data(), meshIndices.data(), indicesCount * sizeof(uint32_t));

        static SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3> positions;
        static SR_HTYPES_NS::FastMemoryArray<uint32_t> simplifiedIndices;
        static SR_HTYPES_NS::FastMemoryArray<uint32_t> remap;

        const uint64_t stride = vertices.GetLayout().GetStride();
        auto&& pData = static_cast<const uint8_t*>(vertices.GetRawData()) + pPositionDesc->offset;

        positions.resize(verticesCount);
        for (uint64_t i = 0; i < verticesCount; ++i) {
            positions[i] = *reinterpret_cast<const SR_MATH_NS::FVector3*>(pData + i * stride) * m_collisionScale;
        }

        const uint64_t targetIndices = std::max<uint64_t>(3, static_cast<uint64_t>(static_cast<float_t>(indices.size()) * m_simplifyRatio) / 3 * 3);
        {
            SR_TRACY_ZONE_N("Simplify");
            SR_UTILS_NS::OptimizeVertices(positions, indices, targetIndices, m_simplifyError, simplifiedIndices);
        }

        if (simplifiedIndices.empty()) {
            return false;
        }

        /// Выбрасываем вершины, на которые больше не ссылаются треугольники - иначе PhysX кукает лишнее
        remap.resize(verticesCount);
        std::memset(remap.data(), 0xFF, remap.size() * sizeof(uint32_t));

        SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3> usedPositions;
        usedPositions.reserve(verticesCount);
        for (auto&& index : simplifiedIndices) {
            if (remap[index] == SR_UINT32_MAX) {
                remap[index] = static_cast<uint32_t>(usedPositions.size());
                usedPositions.push_back(positions[index]);
            }
            index = remap[index];
        }

        SR_HTYPES_NS::FastMemoryArray<uint32_t> collisionIndices;
        std::swap(collisionIndices, simplifiedIndices);

        pCollisionShape->SwapCustomTriangleMeshVertices(usedPositions);
        pCollisionShape->SwapCustomTriangleMeshIndices(collisionIndices);

        return true;
    }

    void TerrainMarchingCubesChunkData::SwitchPhysics(bool enable) {
        enable = enable && m_isCollisionAllowed;
        if (enable == m_isPhysicsEnabled) {
            return;
        }

        auto&& pChunkObject = m_chunk->GetObject();
        if (!pChunkObject) {
            m_isPhysicsEnabled = false;
            return;
        }

        if (enable && !m_isCollisionBuilt) {
            m_isCollisionBuilt = true;
            if (!BuildCollision()) {
                /// Геометрия не пригодна для коллизии, больше не пытаемся
                m_isCollisionAllowed = false;
                return;
            }
        }

        if (auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>()) {
            pCollisionShape->SetEnabled(enable);
        }
        if (auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>()) {
            pRigidBody->SetEnabled(enable);
        }

        m_isPhysicsEnabled = enable;
    }

    void TerrainMarchingCubesChunkData::Deactivate() {
        Super::Deactivate();

        m_isCollisionAllowed = false;
        m_isCollisionBuilt = false;
        m_isPhysicsEnabled = false;

        auto&& pChunkObject = m_chunk->GetObject();
        if (!pChunkObject) {
            return;
        }

        if (auto&& pCollisionShape = pChunkObject->GetComponent<SR_PTYPES_NS::CollisionShape>()) {
            pCollisionShape->SetEnabled(false);
            /// Объект уходит в пул: CPU копия меша коллизии больше не нужна
            auto&& meshData = pCollisionShape->GetCustomTriangleMeshData();
            meshData.vertices = SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3>();
            meshData.indices = SR_HTYPES_NS::FastMemoryArray<uint32_t>();
            meshData.isDirty = true;
        }
        if (auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
            pProceduralMesh->SetEnabled(false);
        }
        if (auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>()) {
            pRigidBody->SetEnabled(false);
        }
    }
}
