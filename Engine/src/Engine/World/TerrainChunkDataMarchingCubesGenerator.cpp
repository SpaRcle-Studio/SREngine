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

        /// Юбка уходит под поверхность против нормали: так она закрывает щель при любой ориентации поверхности (в т.ч. на сфере)
        auto&& getSkirtOffset = [&](uint32_t index) -> SR_MATH_NS::FVector3 {
            return pVertices[index].normal * skirtDepth;
        };

        auto&& getSkirtVertex = [&](uint32_t index) -> uint32_t {
            if (skirtVertex[index] == SR_UINT32_MAX) {
                TerrainMeshVertex vertex = pVertices[index];
                vertex.position -= getSkirtOffset(index);
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
                const SR_MATH_NS::FVector3 psa = pa - getSkirtOffset(a);
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

    TerrainChunkDataMarchingCubesGenerator::~TerrainChunkDataMarchingCubesGenerator() {
        Shutdown();
    }

    void TerrainChunkDataMarchingCubesGenerator::GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) {
        SR_TRACY_ZONE;

        /// Синхронный вариант: та же задача, но результат ждём сразу
        if (!BeginChunkData(terrain, chunk, observer)) {
            return;
        }

        for (auto&& pSlot : m_slots) {
            if (pSlot->isBusy && pSlot->pChunk.Get() == &chunk) {
                if (pSlot->computeTask != SR_ID_INVALID) {
                    pSlot->pDensityShader->GetPipeline()->WaitAsyncCompute(pSlot->computeTask);
                }
                FinishSlot(terrain, *pSlot);
                break;
            }
        }
    }

    bool TerrainChunkDataMarchingCubesGenerator::CanBeginChunkData() const {
        /// До инициализации слотов нет, но первая генерация их создаст
        if (m_slots.empty()) {
            return true;
        }

        /// Слоты устарели - новые задачи не начинаются, пока не завершатся текущие, потом Init пересоздаст слоты
        if (IsSlotsOutdated()) {
            return !HasBusySlots();
        }

        return FindFreeSlot() != nullptr;
    }

    bool TerrainChunkDataMarchingCubesGenerator::HasBusySlots() const {
        for (auto&& pSlot : m_slots) {
            if (pSlot->isBusy) {
                return true;
            }
        }
        return false;
    }

    bool TerrainChunkDataMarchingCubesGenerator::IsSlotsOutdated() const {
        return m_slotsDensityCountAxis != m_densityCountAxis
            || m_slotsHashTableSize != m_vertexHashTableSize
            || m_slotsCount != std::clamp<uint32_t>(m_maxGenerationsInFlight, 1, 32)
            || m_slotsMarchingCubesShader != m_marchingCubesShader
            || m_slotsDensityShader != m_densityShader;
    }

    uint64_t TerrainChunkDataMarchingCubesGenerator::GetMaxVertexCount() const {
        /// Вершины дедуплицируются по рёбрам сетки, поэтому их не больше числа рёбер (3 * N^3, см. getEdgeIndex)
        const uint64_t axis = m_slotsDensityCountAxis;
        return 3 * axis * axis * axis;
    }

    uint64_t TerrainChunkDataMarchingCubesGenerator::GetMaxIndicesCount() const {
        /// MarchingCubes.srsl обходит кубы с вокселями [1, N - 2], до 5 треугольников на куб
        const uint64_t cubesPerAxis = m_slotsDensityCountAxis > 2 ? m_slotsDensityCountAxis - 2 : 0;
        return cubesPerAxis * cubesPerAxis * cubesPerAxis * 5 * 3;
    }

    TerrainChunkDataMarchingCubesGenerator::GenerationSlot* TerrainChunkDataMarchingCubesGenerator::FindFreeSlot() const {
        for (auto&& pSlot : m_slots) {
            if (!pSlot->isBusy) {
                return pSlot.Get();
            }
        }
        return nullptr;
    }

    bool TerrainChunkDataMarchingCubesGenerator::BeginChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer) {
        SR_TRACY_ZONE;

        if (!Init()) {
            return false;
        }

        auto&& pCubeChunk = dynamic_cast<TerrainChunkCube*>(&chunk);
        if (!pCubeChunk) {
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::BeginChunkData() : marching cubes generator can only generate data for TerrainChunkCube!");
            return false;
        }

        GenerationSlot* pSlot = FindFreeSlot();
        if (!pSlot) {
            SRHalt("TerrainChunkDataMarchingCubesGenerator::BeginChunkData() : no free generation slots! Check CanBeginChunkData before.");
            return false;
        }

        if (!chunk.GetData()) {
            chunk.SetData(new TerrainMarchingCubesChunkData());
            chunk.GetData()->SetChunk(&chunk);
        }

        /// Свободный слот не должен держать задачу: иначе две задачи пишут в одни буферы и счётчики
        SRAssert2(pSlot->computeTask == SR_ID_INVALID, "TerrainChunkDataMarchingCubesGenerator::BeginChunkData() : free slot still holds a compute task!");

        pSlot->isBusy = true;
        pSlot->isFailed = false;
        pSlot->pChunk = &chunk;

        if (DispatchSlot(terrain, *pCubeChunk, *pSlot)) {
            return true;
        }

        /// Вычисления прошли синхронно (API без асинхронных вычислений) - результат уже можно читать
        FinishSlot(terrain, *pSlot);
        return false;
    }

    void TerrainChunkDataMarchingCubesGenerator::UpdateChunkData(Terrain& terrain, const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& onLoaded) {
        SR_TRACY_ZONE;

        /// Сборка чанка (чтение с GPU, нормали, юбки, трава, меш) - CPU работа. При десятках слотов все готовые за кадр
        /// не собрать без просадки, остальные подождут следующего кадра (на GPU они уже готовы)
        const auto startTime = std::chrono::steady_clock::now();
        uint32_t finished = 0;

        for (auto&& pSlot : m_slots) {
            if (!pSlot->isBusy || pSlot->computeTask == SR_ID_INVALID) {
                continue;
            }

            if (finished > 0 && m_finishBudgetMs > 0.f) {
                const float_t elapsedMs = std::chrono::duration<float_t, std::milli>(std::chrono::steady_clock::now() - startTime).count();
                if (elapsedMs >= m_finishBudgetMs) {
                    break;
                }
            }

            auto&& pPipeline = pSlot->pDensityShader->GetPipeline();
            if (!pPipeline->IsAsyncComputeComplete(pSlot->computeTask)) {
                continue;
            }

            /// FinishSlot освобождает слот (и обнуляет pChunk), поэтому чанк забираем заранее
            ITerrainChunk::Ptr pChunk = pSlot->pChunk;
            FinishSlot(terrain, *pSlot);

            if (pChunk) {
                onLoaded(*pChunk);
                /// Отменённые задачи почти ничего не стоят и в бюджет не считаются
                ++finished;
            }
        }
    }

    void TerrainChunkDataMarchingCubesGenerator::CancelChunkData(ITerrainChunk& chunk) {
        for (auto&& pSlot : m_slots) {
            if (pSlot->isBusy && pSlot->pChunk.Get() == &chunk) {
                /// Задача на GPU продолжит выполняться, её результат выбросит UpdateChunkData
                pSlot->pChunk = nullptr;
            }
        }
    }

    void TerrainChunkDataMarchingCubesGenerator::Shutdown() {
        SR_TRACY_ZONE;

        for (auto&& pSlot : m_slots) {
            if (!pSlot->isBusy) {
                continue;
            }

            pSlot->pChunk = nullptr;

            if (pSlot->computeTask != SR_ID_INVALID) {
                auto&& pPipeline = pSlot->pDensityShader->GetPipeline();
                pPipeline->WaitAsyncCompute(pSlot->computeTask);
            }

            ReleaseSlot(*pSlot);
        }
    }

    void TerrainChunkDataMarchingCubesGenerator::ReleaseSlot(GenerationSlot& slot) {
        if (slot.computeTask != SR_ID_INVALID) {
            /// Сброс счётчиков и переиспользование буферов под работающей на GPU задачей портит её результат
            SRAssert2(slot.pDensityShader->GetPipeline()->IsAsyncComputeComplete(slot.computeTask),
                "TerrainChunkDataMarchingCubesGenerator::ReleaseSlot() : releasing a slot while its compute task is still running!");
            slot.pDensityShader->GetPipeline()->ReleaseAsyncCompute(slot.computeTask);
            slot.computeTask = SR_ID_INVALID;
        }

        /// Счётчики вершин и индексов должны быть нулевыми к следующему запуску, даже если результат не читали
        if (slot.pIndicesSSBO) {
            slot.pIndicesSSBO->ResetCounter();
        }
        if (slot.pVerticesSSBO) {
            slot.pVerticesSSBO->ResetCounter();
        }

        slot.pChunk = nullptr;
        slot.isBusy = false;
        slot.isFailed = false;
    }

    void TerrainChunkDataMarchingCubesGenerator::FinishSlot(Terrain& terrain, GenerationSlot& slot) {
        SR_TRACY_ZONE;

        if (slot.pChunk && !slot.isFailed) {
            if (auto&& pCubeChunk = dynamic_cast<TerrainChunkCube*>(slot.pChunk.Get())) {
                BuildChunk(terrain, *pCubeChunk, slot);
            }
        }
        else if (slot.pChunk) {
            /// Вычисления не удались - чанк остаётся пустым
            if (auto&& pChunkGenerator = terrain.GetChunkGenerator()) {
                pChunkGenerator->ReleaseChunkObject(*slot.pChunk);
            }
        }

        ReleaseSlot(slot);
    }

    bool TerrainChunkDataMarchingCubesGenerator::DispatchSlot(Terrain& terrain, TerrainChunkCube& chunk, GenerationSlot& slot) {
        SR_TRACY_ZONE;

        auto&& pChunkGenerator = terrain.GetChunkGenerator();
        if (!pChunkGenerator) {
            slot.isFailed = true;
            return false;
        }

        /// Диспатч идёт по сетке, с которой созданы буферы слота. Расхождение с настройками - запись за границы буферов
        SRAssert2(!IsSlotsOutdated(), "TerrainChunkDataMarchingCubesGenerator::DispatchSlot() : generation slots are outdated! Init must recreate them before dispatch.");
        SRAssert2(slot.pVerticesSSBO && slot.pVerticesSSBO->GetCapacity() >=GetMaxVertexCount() * sizeof(TerrainMarchingCubesVertex),
            "TerrainChunkDataMarchingCubesGenerator::DispatchSlot() : vertices buffer is smaller than the chunk grid requires!");
        SRAssert2(slot.pIndicesSSBO && slot.pIndicesSSBO->GetCapacity() >=GetMaxIndicesCount() * sizeof(uint32_t),
            "TerrainChunkDataMarchingCubesGenerator::DispatchSlot() : indices buffer is smaller than the chunk grid requires!");
        SRAssert2(slot.pHashTableSSBO && slot.pHashTableSSBO->GetCapacity() >=3ull * m_slotsDensityCountAxis * m_slotsDensityCountAxis * m_slotsDensityCountAxis * sizeof(uint32_t),
            "TerrainChunkDataMarchingCubesGenerator::DispatchSlot() : edge table is smaller than the edges count of the chunk grid!");

        auto&& pCubeChunk = &chunk;
        auto&& position = pCubeChunk->GetPosition();
        const int32_t lodScale = pCubeChunk->GetLodScale();
        const uint32_t groups = (m_slotsDensityCountAxis + 7) / 8;

        static SR_UTILS_NS::String positionText;
        positionText.clear();
        SR_UTILS_NS::FormatTo(positionText, "{}, {}, {} lod {}", position.x, position.y, position.z, pCubeChunk->GetLod());
        SR_TRACY_ZONE_TEXT(positionText);

        /// Правки плотности от деформаций террейна (см. Terrain::LateUpdate) для сетки этого чанка.
        /// Точка плотности вокселя v по оси: chunkCoord * (N - 2) + 1 + (v - 1) * lodScale - так же, как в Density.srsl
        bool hasDensityOffsets = false;
        {
            SR_TRACY_ZONE_N("Collect density offsets");

            const int32_t axis = static_cast<int32_t>(m_slotsDensityCountAxis);
            const SR_MATH_NS::IVector3 origin = position * (axis - 2) + SR_MATH_NS::IVector3(1) - SR_MATH_NS::IVector3(lodScale);
            const SR_MATH_NS::IVector3 last = origin + SR_MATH_NS::IVector3((axis - 1) * lodScale);

            if (terrain.HasDensityOffsets(origin, last)) {
                const uint64_t count = static_cast<uint64_t>(axis) * axis * axis;
                m_densityOffsets.resize(count);

                for (int32_t z = 0; z < axis; ++z) {
                    for (int32_t y = 0; y < axis; ++y) {
                        for (int32_t x = 0; x < axis; ++x) {
                            const SR_MATH_NS::IVector3 point = origin + SR_MATH_NS::IVector3(x, y, z) * lodScale;
                            const float_t offset = terrain.GetDensityOffset(point);
                            m_densityOffsets[(static_cast<uint64_t>(z) * axis + y) * axis + x] = offset;
                            hasDensityOffsets |= !SR_EQUALS(offset, 0.f);
                        }
                    }
                }

                if (hasDensityOffsets) {
                    slot.pDensityOffsetsSSBO->UpdateSSBO(m_densityOffsets.data(), count * sizeof(float_t));
                }
            }
        }

        /// Все диспатчи пишутся в одну асинхронную задачу (если API поддерживает), между зависимыми - барьеры
        auto&& pPipeline = slot.pDensityShader->GetPipeline();
        slot.computeTask = pPipeline->BeginAsyncCompute();
        const bool isAsync = slot.computeTask != SR_ID_INVALID;

        auto&& dispatchMarching = [&](int32_t stage) {
            auto&& pMarchingShader = slot.marchingShaders[stage];
            if (!pMarchingShader->BeginCompute()) {
                slot.isFailed = true;
                return;
            }
            slot.pDensitySSBO->Bind();
            slot.pHashTableSSBO->Bind();
            slot.pVerticesSSBO->Bind();
            slot.pIndicesSSBO->Bind();
            /// Ёмкости буферов слота: шейдер не пишет за их границы (иначе портит соседние буферы, в т.ч. счётчики других слотов)
            pMarchingShader->GetShader()->SetConstInt("maxVertexCount"_atom, static_cast<int>(GetMaxVertexCount()));
            pMarchingShader->GetShader()->SetConstInt("maxIndicesCount"_atom, static_cast<int>(GetMaxIndicesCount()));
            pMarchingShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(m_slotsDensityCountAxis));
            pMarchingShader->GetShader()->SetConstFloat("isoLevel"_atom, m_isoLevel);
            pMarchingShader->GetShader()->SetConstInt(SR_GRAPH_NS::SHADER_COMPUTE_STAGE, stage);
            pMarchingShader->Dispatch(groups, groups, groups);
            pMarchingShader->EndCompute();
        };

        /// Очистка таблицы рёбер на GPU: не зависит от плотности, барьер нужен только перед этапом 0
        {
            SR_TRACY_ZONE_N("Clear edge table");
            dispatchMarching(2);
        }

        /// Плотность живёт только на GPU: на CPU она не нужна, а хранение кеша стоило по 4 МБ на чанк
        {
            SR_TRACY_ZONE_N("Compute density");

            auto&& pDensityShader = slot.pDensityShader;
            if (pDensityShader->BeginCompute()) {
                slot.pDensitySSBO->Bind();
                slot.pDensityOffsetsSSBO->Bind();
                pDensityShader->GetShader()->SetConstInt("hasDensityOffsets"_atom, hasDensityOffsets ? 1 : 0);
                pDensityShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(m_slotsDensityCountAxis));
                pDensityShader->GetShader()->SetConstInt("seed"_atom, static_cast<int>(m_seed));
                pDensityShader->GetShader()->SetConstInt("lodScale"_atom, lodScale);
                pDensityShader->GetShader()->SetConstFloat("isoLevel"_atom, m_isoLevel);
                pDensityShader->GetShader()->SetConstFloat("noiseScale"_atom, m_noiseScale);
                pDensityShader->GetShader()->SetConstIVec3("chunkCoord"_atom, position);
                pDensityShader->GetShader()->SetConstVec3("voxelSize"_atom, pChunkGenerator->GetVoxelSize());

                const bool isSphere = terrain.GetShape() == TerrainShape::Sphere;
                const SR_MATH_NS::FVector3 sphereCenter = terrain.GetSphereCenter();
                pDensityShader->GetShader()->SetConstVec4("terrainUp"_atom, SR_MATH_NS::FVector4(sphereCenter.x, sphereCenter.y, sphereCenter.z, isSphere ? 1.f : 0.f));

                for (auto&& parameter : m_densityParameters) {
                    pDensityShader->GetShader()->SetConstVec4(parameter.name, parameter.value);
                }

                pDensityShader->Dispatch(groups, groups, groups);
                pDensityShader->EndCompute();
            }
            else {
                slot.isFailed = true;
            }
        }

        {
            SR_TRACY_ZONE_N("Compute geometry");

            for (int32_t stage = 0; stage <= 1; ++stage) {
                /// Этап читает результат предыдущих диспатчей той же задачи (плотность, очищенная таблица, вершины)
                if (isAsync) {
                    pPipeline->WriteMemoryBarrier(SR_GRAPH_NS::MemoryBarrierType::ComputeToCompute);
                }
                dispatchMarching(stage);
            }
        }

        if (!isAsync) {
            return false;
        }

        if (!pPipeline->SubmitAsyncCompute()) {
            /// Задача не отправлена - результата не будет, слот освобождается в UpdateChunkData как неудачный
            slot.isFailed = true;
        }

        return true;
    }

    void TerrainChunkDataMarchingCubesGenerator::BuildChunk(Terrain& terrain, TerrainChunkCube& cubeChunk, GenerationSlot& slot) {
        SR_TRACY_ZONE;

        ITerrainChunk& chunk = cubeChunk;
        auto&& pCubeChunk = &cubeChunk;

        auto&& pChunkGenerator = terrain.GetChunkGenerator();
        if (!pChunkGenerator || !chunk.GetData()) {
            return;
        }

        auto&& pChunkData = chunk.GetData().DynamicCast<TerrainMarchingCubesChunkData>();

        {
            SR_TRACY_ZONE_N("Read indices");

            m_indices.clear();
            if (void* pData = slot.pIndicesSSBO->MapData()) {
                uint64_t indicesCount = slot.pIndicesSSBO->GetCounter();

                /// Счётчик растёт и при пропущенной (из-за переполнения) записи, а не кратный трём - признак чужой записи в него
                SRAssert2(indicesCount <= GetMaxIndicesCount(), "TerrainChunkDataMarchingCubesGenerator::BuildChunk() : indices count {} exceeds the buffer capacity {}!", indicesCount, GetMaxIndicesCount());
                SRAssert2(indicesCount % 3 == 0, "TerrainChunkDataMarchingCubesGenerator::BuildChunk() : indices count {} is not a multiple of 3! The counter is corrupted.", indicesCount);
                indicesCount = std::min<uint64_t>(indicesCount, GetMaxIndicesCount()) / 3 * 3;

                m_indices.resize(indicesCount);
                std::memcpy(m_indices.data(), pData, sizeof(uint32_t) * indicesCount);
                slot.pIndicesSSBO->ResetCounter();
                slot.pIndicesSSBO->FlushCounter();
                slot.pIndicesSSBO->UnMap();
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

            if (auto&& pGpuVertices = reinterpret_cast<TerrainMarchingCubesVertex*>(slot.pVerticesSSBO->MapData())) {
                verticesCount = slot.pVerticesSSBO->GetCounter();
                SRAssert2(verticesCount <= GetMaxVertexCount(), "TerrainChunkDataMarchingCubesGenerator::BuildChunk() : vertices count {} exceeds the buffer capacity {}!", verticesCount, GetMaxVertexCount());
                verticesCount = static_cast<uint32_t>(std::min<uint64_t>(verticesCount, GetMaxVertexCount()));
                m_vertices.Allocate(verticesCount);

                auto&& pVertices = reinterpret_cast<TerrainMeshVertex*>(m_vertices.data.data());
                for (uint32_t i = 0; i < verticesCount; ++i) {
                    pVertices[i].position = pGpuVertices[i].pos;
                    pVertices[i].weights = pGpuVertices[i].weights;
                }

                slot.pVerticesSSBO->ResetCounter();
                slot.pVerticesSSBO->FlushCounter();
                slot.pVerticesSSBO->UnMap();
            }
        }
        else {
            /// Без маппинга ResetCounter сам мапит, флашит и анмапит буфер
            slot.pVerticesSSBO->ResetCounter();
        }

        {
            /// Индекс за пределами вершин - испорченные данные (переполнение буферов, неочищенная таблица рёбер).
            /// Такой меш ломает нормали, юбки и упрощение коллизии, поэтому чанк остаётся пустым
            bool isIndicesValid = true;
            for (const uint32_t index : m_indices) {
                if (index >= verticesCount) {
                    isIndicesValid = false;
                    break;
                }
            }

            if (!isIndicesValid) {
                SRHalt("TerrainChunkDataMarchingCubesGenerator::BuildChunk() : index is out of vertices range ({} vertices)! GPU data is corrupted.", verticesCount);
                m_indices.clear();
                verticesCount = 0;
            }
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
                /// Чанк LOD0 мал относительно планеты, поэтому направление "вверх" одно на весь чанк (по его центру)
                grassMesh.up = terrain.GetLocalUpDirection(chunkOrigin +scale * (0.5f * static_cast<float_t>(m_slotsDensityCountAxis)));
                /// Воксель в локальных осях меша имеет размер 1, диагональ куба - sqrt(3)
                const float_t maxScale = std::max({ std::abs(scale.x), std::abs(scale.y), std::abs(scale.z) });
                grassMesh.maxEdgeLength = 1.8f * maxScale;
                /// Полезная область вокселей чанка: координаты [1, densityCountAxis - 1] -> локальные [0.5, densityCountAxis - 1.5]
                const float_t innerMin = 0.5f;
                const float_t innerMax = static_cast<float_t>(m_slotsDensityCountAxis) - 1.5f;
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
        AddSkirts(m_vertices, m_indices, m_slotsDensityCountAxis, m_skirtDepth, pCubeChunk->GetLodBorders());

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

        if (m_isInitialized && !IsSlotsOutdated()) {
            return true;
        }

        if (HasBusySlots()) {
            /// Сюда не попадаем: CanBeginChunkData не даёт начать задачу, пока устаревшие слоты заняты
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::Init() : can't recreate generation slots while they are busy!");
            return false;
        }

        m_isInitialized = false;
        m_slots.clear();

        if (m_densityCountAxis < 3) {
            SRHalt("TerrainChunkDataMarchingCubesGenerator::Init() : densityCountAxis must be greater than 2!");
            return false;
        }

        const uint32_t slotsCount = std::clamp<uint32_t>(m_maxGenerationsInFlight, 1, 32);

        m_slotsDensityCountAxis = m_densityCountAxis;
        m_slotsHashTableSize = m_vertexHashTableSize;
        m_slotsCount = slotsCount;
        m_slotsMarchingCubesShader = m_marchingCubesShader;
        m_slotsDensityShader = m_densityShader;

        m_slots.reserve(slotsCount);

        for (uint32_t i = 0; i < slotsCount; ++i) {
            m_slots.emplace_back(new GenerationSlot());
            if (!CreateSlotResources(*m_slots.back().Get())) {
                m_slots.clear();
                SRHalt("TerrainChunkDataMarchingCubesGenerator::Init() : failed to create generation resources!");
                return false;
            }
        }

        m_isInitialized = true;
        return true;
    }

    bool TerrainChunkDataMarchingCubesGenerator::CreateSlotResources(GenerationSlot& slot) {
        SR_TRACY_ZONE;

        /// Шейдер (ресурс) общий, у экземпляров ComputeShader - свои наборы дескрипторов
        slot.pDensityShader = SR_GTYPES_NS::ComputeShader::Load(m_slotsDensityShader);
        for (auto&& pMarchingShader : slot.marchingShaders) {
            pMarchingShader = SR_GTYPES_NS::ComputeShader::Load(m_slotsMarchingCubesShader);
            if (!pMarchingShader) {
                SR_ERROR("TerrainChunkDataMarchingCubesGenerator::CreateSlotResources() : failed to load marching cubes shader!");
                return false;
            }
        }

        if (!slot.pDensityShader) {
            SR_ERROR("TerrainChunkDataMarchingCubesGenerator::CreateSlotResources() : failed to load density shader!");
            return false;
        }

        const uint64_t axis = m_slotsDensityCountAxis;
        const uint64_t densitiesCount = axis * axis * axis;

        const uint64_t edgesCount = 3 * densitiesCount;
        const uint64_t maxVertexCount = GetMaxVertexCount();
        const uint64_t maxIndicesCount = GetMaxIndicesCount();

        /// Таблица рёбер адресуется напрямую индексом ребра - меньше числа рёбер нельзя
        const uint64_t hashTableSize = std::max<uint64_t>(m_slotsHashTableSize, edgesCount);

        slot.pDensitySSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVoxel>(densitiesCount, SR_GRAPH_NS::SSBOUsage::AutoPreferDevice, "voxels");
        slot.pDensityOffsetsSSBO = SR_GRAPH_NS::SSBOInstance::Create<float_t>(densitiesCount, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "densityOffsets");
        /// Очищается на GPU (этап 2 MarchingCubes.srsl), с CPU не трогается
        slot.pHashTableSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(hashTableSize, SR_GRAPH_NS::SSBOUsage::AutoPreferDevice, "hashTable");
        slot.pVerticesSSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainMarchingCubesVertex>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "vertices", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
        slot.pIndicesSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(maxIndicesCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "indices", SR_GRAPH_NS::SSBOFlags::Counter);

        return slot.pDensitySSBO && slot.pDensityOffsetsSSBO && slot.pHashTableSSBO && slot.pVerticesSSBO && slot.pIndicesSSBO;
    }

    void TerrainMarchingCubesChunkData::SetCollisionSettings(bool allowed, const SR_MATH_NS::FVector3& scale, float_t simplifyRatio, float_t simplifyError, uint64_t indicesCount) {
        SRAssert2(indicesCount % 3 == 0, "TerrainMarchingCubesChunkData::SetCollisionSettings() : indices count {} is not a multiple of 3!", indicesCount);
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
        SRAssert2(m_collisionIndicesCount <= meshIndices.size(), "TerrainMarchingCubesChunkData::BuildCollision() : collision indices count {} exceeds the mesh indices count {}!", m_collisionIndicesCount, meshIndices.size());
        SRAssert2(m_collisionIndicesCount % 3 == 0, "TerrainMarchingCubesChunkData::BuildCollision() : collision indices count {} is not a multiple of 3!", m_collisionIndicesCount);
        /// meshoptimizer принимает только целые треугольники
        const uint64_t indicesCount = std::min<uint64_t>(m_collisionIndicesCount, meshIndices.size()) / 3 * 3;

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

    bool TerrainMarchingCubesChunkData::IsRenderReady() const {
        auto&& pChunkObject = m_chunk->GetObject();
        if (!pChunkObject) {
            return true;
        }

        auto&& pProceduralMesh = pChunkObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
        if (!pProceduralMesh) {
            return true;
        }

        /// Включение объекта применяется отложенно (CheckActivity), а изменение меша ставит его в очередь перерегистрации
        return pProceduralMesh->IsActive() && pProceduralMesh->IsRenderObjectRegistered() && !pProceduralMesh->IsWaitReRegister();
    }

    bool TerrainMarchingCubesChunkData::IsPhysicsReady() const {
        auto&& pChunkObject = m_chunk->GetObject();
        if (!pChunkObject || !m_isCollisionAllowed) {
            return true;
        }

        if (!m_isPhysicsEnabled) {
            return false;
        }

        auto&& pRigidBody = pChunkObject->GetComponent<SR_PTYPES_NS::Rigidbody>();
        if (!pRigidBody) {
            return true;
        }

        /// Включение применяется отложенно (CheckActivity), тело попадает в мир на Flush физики (InitBody),
        /// треугольный меш кукается в SynchronizeStatic не больше одного за кадр
        return pRigidBody->IsActive() && pRigidBody->GetHandle() && !pRigidBody->IsBodyDirty() && !pRigidBody->IsShapeDirty();
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
