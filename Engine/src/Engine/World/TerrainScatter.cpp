//
// Created by Monika on 28.11.2026.
//

#include <Engine/World/TerrainScatter.h>
#include <Engine/World/Terrain.h>

#include <Utils/Platform/Platform.h>
#include <Utils/FileSystem/PathDataAccessor.h>

#include <Codegen/TerrainScatter.generated.hpp>

namespace SR_CORE_NS {
    /// Ключ ячейки сетки кандидатов: по 21 биту на ось (±10^6 ячеек)
    static uint64_t TerrainScatterCellKey(int32_t x, int32_t y, int32_t z) noexcept {
        static constexpr uint64_t mask = (1ULL << 21U) - 1ULL;
        return (static_cast<uint64_t>(x) & mask) | ((static_cast<uint64_t>(y) & mask) << 21U) | ((static_cast<uint64_t>(z) & mask) << 42U);
    }

    static uint64_t TerrainScatterHashCombine(uint64_t hash, uint64_t value) noexcept {
        return hash ^ (value + 0x9E3779B97F4A7C15ULL + (hash << 6U) + (hash >> 2U));
    }

    /// Занятые точки чанка для проверки свободного радиуса (clearance) между объектами
    struct TerrainScatterClearanceGrid {
        struct Point {
            SR_MATH_NS::FVector3 position;
            float_t radius = 0.f;
            int32_t next = -1;
        };

        float_t cellSize = 1.f;
        SR_HTYPES_NS::FlatHashMap<uint64_t, int32_t> heads;
        SR_UTILS_NS::Vector<Point> points;

        SR_NODISCARD uint64_t KeyOf(const SR_MATH_NS::FVector3& position, int32_t dx, int32_t dy, int32_t dz) const noexcept {
            return TerrainScatterCellKey(
                static_cast<int32_t>(std::floor(position.x / cellSize)) + dx,
                static_cast<int32_t>(std::floor(position.y / cellSize)) + dy,
                static_cast<int32_t>(std::floor(position.z / cellSize)) + dz
            );
        }

        SR_NODISCARD bool IsFree(const SR_MATH_NS::FVector3& position, float_t radius) const {
            for (int32_t dx = -1; dx <= 1; ++dx) {
                for (int32_t dy = -1; dy <= 1; ++dy) {
                    for (int32_t dz = -1; dz <= 1; ++dz) {
                        auto&& pIt = heads.find(KeyOf(position, dx, dy, dz));
                        if (pIt == heads.end()) {
                            continue;
                        }
                        for (int32_t index = pIt->second; index >= 0; index = points[index].next) {
                            const float_t minDistance = radius + points[index].radius;
                            const SR_MATH_NS::FVector3 delta = points[index].position - position;
                            if (delta.Dot(delta) < minDistance * minDistance) {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }

        void Add(const SR_MATH_NS::FVector3& position, float_t radius) {
            const uint64_t key = KeyOf(position, 0, 0, 0);
            Point point;
            point.position = position;
            point.radius = radius;
            if (auto&& pIt = heads.find(key); pIt != heads.end()) {
                point.next = pIt->second;
                pIt->second = static_cast<int32_t>(points.size());
            }
            else {
                heads[key] = static_cast<int32_t>(points.size());
            }
            points.emplace_back(point);
        }
    };

    /// ----------------------------------------------------------------------------------------------------------------

    TerrainScatterPrototype::TerrainScatterPrototype()
        : SR_HTYPES_NS::SharedPtr<TerrainScatterPrototype>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    float_t TerrainScatterPrototype::GetMaxDistance() const noexcept {
        float_t distance = 0.f;
        for (auto&& lod : m_lods) {
            distance = std::max(distance, lod.maxDistance);
        }
        return distance;
    }

    TerrainScatterLayer::TerrainScatterLayer()
        : SR_HTYPES_NS::SharedPtr<TerrainScatterLayer>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    /// ----------------------------------------------------------------------------------------------------------------

    TerrainScatter::TerrainScatter()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    TerrainScatter::~TerrainScatter() {
        StopWorker();
    }

    void TerrainScatter::StartWorker() {
        SR_TRACY_ZONE;

        if (m_worker) {
            return;
        }

        m_stopWorker = false;

        if (!SR_HTYPES_NS::Thread::Factory::Instance().Create(m_worker, &TerrainScatter::WorkerStep, this)) {
            SR_ERROR("TerrainScatter::StartWorker() : failed to create thread!");
            m_worker = nullptr;
            return;
        }

        m_worker->SetName("Terrain scatter");
    }

    void TerrainScatter::StopWorker() {
        {
            std::lock_guard lock(m_queueMutex);
            m_stopWorker = true;
            m_tasks.clear();
        }

        if (m_worker) {
            m_worker->TryJoin();
            m_worker->Free();
            m_worker = nullptr;
        }

        std::lock_guard lock(m_queueMutex);
        m_results.clear();
    }

    bool TerrainScatter::WorkerStep() {
        if (m_stopWorker) {
            return false;
        }

        Task task;
        bool hasTask = false;
        {
            std::lock_guard lock(m_queueMutex);
            if (!m_tasks.empty()) {
                task = std::move(m_tasks.front());
                m_tasks.erase(m_tasks.begin());
                hasTask = true;
            }
        }

        if (!hasTask) {
        #ifdef SR_THREADS_ALLOWED
            SR_PLATFORM_NS::Sleep(5);
        #endif
            return true;
        }

        SR_TRACY_ZONE;

        Result result = Generate(*task.pSettings, task);

        std::lock_guard lock(m_queueMutex);
        if (m_stopWorker) {
            return false;
        }
        m_results.emplace_back(std::move(result));

        return true;
    }

    void TerrainScatter::Shutdown() {
        SR_TRACY_ZONE;

        StopWorker();
        DestroySlots();
        m_entries.clear();
        m_structureHash = 0;
        m_isVisibleDirty = true;
        m_totalInstances = 0;
        m_drawnInstances = 0;
    }

    void TerrainScatter::Regenerate() {
        m_isRegenerateRequested = true;
    }

    bool TerrainScatter::IsLodUsed(uint8_t lod) const {
        if (!m_enabled) {
            return false;
        }

        for (auto&& pLayer : m_layers) {
            if (pLayer && pLayer->IsEnabled() && lod <= pLayer->GetMaxTerrainLod() && !pLayer->GetPrototypes().empty()) {
                return true;
            }
        }

        return false;
    }

    TerrainScatter::SettingsPtr TerrainScatter::MakeSettings(const Terrain& terrain) const {
        SettingsPtr pSettings(new Settings());

        pSettings->isSphere = terrain.GetShape() == TerrainShape::Sphere;
        pSettings->sphereCenter = terrain.GetSphereCenter();
        pSettings->maxInstancesPerChunk = m_maxInstancesPerChunk;

        for (auto&& pLayer : m_layers) {
            LayerSnapshot& layer = pSettings->layers.emplace_back();
            if (!pLayer) {
                continue; /// индексы слоёв должны совпадать с m_layers
            }

            layer.enabled = pLayer->IsEnabled();
            layer.spacing = std::max(0.25f, pLayer->GetSpacing());
            layer.density = std::clamp(pLayer->GetDensity(), 0.f, 1.f);
            layer.seed = static_cast<uint32_t>(pLayer->GetSeed());
            layer.maxTerrainLod = pLayer->GetMaxTerrainLod();
            layer.clearance = std::max(0.f, pLayer->GetClearance());
            layer.alignToNormal = std::clamp(pLayer->GetAlignToNormal(), 0.f, 1.f);
            layer.randomYaw = pLayer->IsRandomYaw();
            layer.scaleMin = std::max(0.001f, pLayer->GetScaleMin());
            layer.scaleMax = std::max(layer.scaleMin, pLayer->GetScaleMax());
            layer.embed = pLayer->GetEmbed();

            for (auto&& pRule : pLayer->GetRules()) {
                if (pRule && pRule->IsEnabled()) {
                    layer.rules.emplace_back(pRule);
                }
            }

            for (auto&& pPrototype : pLayer->GetPrototypes()) {
                PrototypeSnapshot& prototype = layer.prototypes.emplace_back();
                if (!pPrototype) {
                    continue;
                }
                prototype.weight = std::max(0.f, pPrototype->GetWeight());
                prototype.scale = pPrototype->GetScale();
                prototype.verticalOffset = pPrototype->GetVerticalOffset();
                layer.totalWeight += prototype.weight;
            }

            if (layer.enabled) {
                pSettings->maxClearance = std::max(pSettings->maxClearance, layer.clearance);
            }
        }

        return pSettings;
    }

    void TerrainScatter::OnChunkGenerated(Terrain& terrain, ITerrainChunk& chunk, const TerrainGrassSourceMesh& mesh, uint8_t lod) {
        SR_TRACY_ZONE;

        if (!m_enabled) {
            return;
        }

        chunk.SetScatter(this);

        ChunkEntry& entry = m_entries[&chunk];
        entry.generation = ++m_generationCounter;

        {
            std::lock_guard lock(m_queueMutex);
            m_tasks.erase_if([&](const Task& task) { return task.pChunk == &chunk; });
        }

        if (mesh.indices.empty() || !IsLodUsed(lod)) {
            /// Объектов у чанка нет - он сразу готов
            entry.groups.clear();
            entry.hasResult = true;
            m_isVisibleDirty = true;
            return;
        }

        /// Старые объекты (перегенерация того же чанка после деформации) остаются видимыми до результата
        StartWorker();

        Task task;
        task.generation = entry.generation;
        task.pChunk = &chunk;
        task.pMesh = SourceMeshPtr::MakeShared(mesh);
        task.lod = lod;
        task.pSettings = MakeSettings(terrain);

        std::lock_guard lock(m_queueMutex);
        m_tasks.emplace_back(std::move(task));
    }

    void TerrainScatter::OnChunkDeactivated(ITerrainChunk& chunk) {
        {
            std::lock_guard lock(m_queueMutex);
            m_tasks.erase_if([&](const Task& task) { return task.pChunk == &chunk; });
        }

        /// Результаты в полёте отбросятся: записи чанка больше нет
        if (m_entries.erase(&chunk)) {
            m_isVisibleDirty = true;
        }
    }

    bool TerrainScatter::IsChunkReady(const ITerrainChunk& chunk) const {
        if (!m_enabled) {
            return true;
        }
        auto&& pIt = m_entries.find(&chunk);
        return pIt == m_entries.end() || pIt->second.hasResult;
    }

    TerrainScatter::Result TerrainScatter::Generate(const Settings& settings, const Task& task) {
        SR_TRACY_ZONE;

        Result result;
        result.generation = task.generation;
        result.pChunk = task.pChunk;

        auto&& mesh = task.pMesh->data;
        const uint64_t indicesCount = mesh.indices.size() - mesh.indices.size() % 3;

        /// Границы чанка в координатах террейна, полуоткрытые: кандидат на стыке достаётся одному чанку
        const SR_MATH_NS::FVector3 boundsSize = mesh.bounds.max - mesh.bounds.min;
        const bool hasBounds = boundsSize.x > 0.f && boundsSize.y > 0.f && boundsSize.z > 0.f;
        const SR_MATH_NS::FVector3 boundsMin = mesh.origin + mesh.bounds.min;
        const SR_MATH_NS::FVector3 boundsMax = mesh.origin + mesh.bounds.max;
        result.bounds = SR_MATH_NS::AABB(SR_MATH_NS::FVector3(SR_FLOAT_MAX), SR_MATH_NS::FVector3(-SR_FLOAT_MAX));

        const auto upAt = [&](const SR_MATH_NS::FVector3& position) -> SR_MATH_NS::FVector3 {
            if (!settings.isSphere) {
                return SR_MATH_NS::FVector3(0.f, 1.f, 0.f);
            }
            const SR_MATH_NS::FVector3 direction = position - settings.sphereCenter;
            const float_t length = direction.Length();
            return length > 1e-4f ? direction / length : SR_MATH_NS::FVector3(0.f, 1.f, 0.f);
        };

        const auto materialWeight = [&](uint32_t vertex, uint32_t material) -> float_t {
            float_t weight = 0.f;
            const float_t blend = vertex < mesh.blends.size() ? mesh.blends[vertex] : 0.f;
            if (vertex < mesh.materials.size() && mesh.materials[vertex] == material) {
                weight += 1.f - blend;
            }
            if (vertex < mesh.materials2.size() && mesh.materials2[vertex] == material) {
                weight += blend;
            }
            return weight;
        };

        TerrainScatterClearanceGrid clearanceGrid;
        clearanceGrid.cellSize = std::max(1.f, settings.maxClearance * 2.f);

        SR_HTYPES_NS::FlatHashSet<uint64_t> resolvedCells;
        uint32_t totalInstances = 0;

        for (uint32_t layerIndex = 0; layerIndex < settings.layers.size(); ++layerIndex) {
            auto&& layer = settings.layers[layerIndex];
            if (!layer.enabled || task.lod > layer.maxTerrainLod || layer.prototypes.empty() || layer.totalWeight <= 0.f || layer.density <= 0.f) {
                continue;
            }

            const float_t spacing = layer.spacing;
            const float_t invSpacing = 1.f / spacing;
            const uint32_t seed = TerrainScatterNoise::Hash(layer.seed * 0x632BE5ABU + layerIndex);

            /// Индекс группы прототипа в result.groups, создаётся по первому объекту
            SR_UTILS_NS::Vector<int32_t> groupIndices(layer.prototypes.size(), -1);

            resolvedCells.clear();

            for (uint64_t i = 0; i < indicesCount; i += 3) {
                const uint32_t i0 = mesh.indices[i];
                const uint32_t i1 = mesh.indices[i + 1];
                const uint32_t i2 = mesh.indices[i + 2];
                if (i0 >= mesh.positions.size() || i1 >= mesh.positions.size() || i2 >= mesh.positions.size()) SR_UNLIKELY_ATTRIBUTE {
                    continue;
                }

                const SR_MATH_NS::FVector3 p0 = mesh.origin + mesh.positions[i0];
                const SR_MATH_NS::FVector3 p1 = mesh.origin + mesh.positions[i1];
                const SR_MATH_NS::FVector3 p2 = mesh.origin + mesh.positions[i2];

                const SR_MATH_NS::FVector3 e1 = p1 - p0;
                const SR_MATH_NS::FVector3 e2 = p2 - p0;

                if (mesh.maxEdgeLength > 0.f) {
                    const float_t maxEdgeSq = mesh.maxEdgeLength * mesh.maxEdgeLength;
                    if (e1.Dot(e1) > maxEdgeSq || e2.Dot(e2) > maxEdgeSq || (p2 - p1).Dot(p2 - p1) > maxEdgeSq) {
                        continue; /// мусорная вершина на стыке чанков
                    }
                }

                const SR_MATH_NS::FVector3 cross = e1.Cross(e2);
                const float_t crossLength = cross.Length();
                if (crossLength < 1e-8f) {
                    continue;
                }
                const SR_MATH_NS::FVector3 planeNormal = cross / crossLength;

                const SR_MATH_NS::FVector3 triMin(std::min({ p0.x, p1.x, p2.x }), std::min({ p0.y, p1.y, p2.y }), std::min({ p0.z, p1.z, p2.z }));
                const SR_MATH_NS::FVector3 triMax(std::max({ p0.x, p1.x, p2.x }), std::max({ p0.y, p1.y, p2.y }), std::max({ p0.z, p1.z, p2.z }));

                const int32_t minX = static_cast<int32_t>(std::floor(triMin.x * invSpacing));
                const int32_t minY = static_cast<int32_t>(std::floor(triMin.y * invSpacing));
                const int32_t minZ = static_cast<int32_t>(std::floor(triMin.z * invSpacing));
                const int32_t maxX = static_cast<int32_t>(std::floor(triMax.x * invSpacing));
                const int32_t maxY = static_cast<int32_t>(std::floor(triMax.y * invSpacing));
                const int32_t maxZ = static_cast<int32_t>(std::floor(triMax.z * invSpacing));

                /// Треугольник намного больше шага сетки - слой не для этого LOD
                if (static_cast<int64_t>(maxX - minX + 1) * (maxY - minY + 1) * (maxZ - minZ + 1) > 4096) {
                    continue;
                }

                const float_t d00 = e1.Dot(e1);
                const float_t d01 = e1.Dot(e2);
                const float_t d11 = e2.Dot(e2);
                const float_t baryDenominator = d00 * d11 - d01 * d01;
                if (std::abs(baryDenominator) < 1e-12f) {
                    continue;
                }

                for (int32_t cx = minX; cx <= maxX; ++cx) {
                    for (int32_t cy = minY; cy <= maxY; ++cy) {
                        for (int32_t cz = minZ; cz <= maxZ; ++cz) {
                            const uint64_t cellKey = TerrainScatterCellKey(cx, cy, cz);
                            if (resolvedCells.contains(cellKey)) {
                                continue;
                            }

                            /// Кандидат ячейки - случайная точка внутри неё, проецируется на треугольник вдоль "вверх"
                            const uint32_t h0 = TerrainScatterNoise::Hash(cx, cy, cz, seed);
                            const uint32_t h1 = TerrainScatterNoise::Hash(h0 ^ 0x68E31DA4U);
                            const uint32_t h2 = TerrainScatterNoise::Hash(h1 ^ 0xB5297A4DU);

                            const SR_MATH_NS::FVector3 candidate(
                                (static_cast<float_t>(cx) + TerrainScatterNoise::ToFloat(h0)) * spacing,
                                (static_cast<float_t>(cy) + TerrainScatterNoise::ToFloat(h1)) * spacing,
                                (static_cast<float_t>(cz) + TerrainScatterNoise::ToFloat(h2)) * spacing
                            );

                            const SR_MATH_NS::FVector3 candidateUp = upAt(candidate);
                            const float_t denominator = candidateUp.Dot(planeNormal);
                            if (std::abs(denominator) < 0.1f) {
                                continue; /// почти отвесный треугольник
                            }

                            const float_t t = (p0 - candidate).Dot(planeNormal) / denominator;
                            const SR_MATH_NS::FVector3 hit = candidate + candidateUp * t;

                            const SR_MATH_NS::FVector3 v = hit - p0;
                            const float_t d20 = v.Dot(e1);
                            const float_t d21 = v.Dot(e2);
                            const float_t b1 = (d11 * d20 - d01 * d21) / baryDenominator;
                            const float_t b2 = (d00 * d21 - d01 * d20) / baryDenominator;
                            const float_t b0 = 1.f - b1 - b2;
                            static constexpr float_t epsilon = -1e-5f;
                            if (b0 < epsilon || b1 < epsilon || b2 < epsilon) {
                                continue;
                            }

                            /// Объект принадлежит ячейке, только если точка посадки лежит в ней же:
                            /// иначе соседние по высоте ячейки дали бы второй объект в том же месте
                            if (static_cast<int32_t>(std::floor(hit.x * invSpacing)) != cx ||
                                static_cast<int32_t>(std::floor(hit.y * invSpacing)) != cy ||
                                static_cast<int32_t>(std::floor(hit.z * invSpacing)) != cz
                            ) {
                                continue;
                            }

                            if (hasBounds && (
                                hit.x < boundsMin.x || hit.y < boundsMin.y || hit.z < boundsMin.z ||
                                hit.x >= boundsMax.x || hit.y >= boundsMax.y || hit.z >= boundsMax.z
                            )) {
                                continue;
                            }

                            resolvedCells.emplace(cellKey);

                            if (settings.maxInstancesPerChunk > 0 && totalInstances >= settings.maxInstancesPerChunk) {
                                continue;
                            }

                            /// ---- правила
                            TerrainScatterPoint point;
                            point.position = hit;
                            point.up = upAt(hit);

                            SR_MATH_NS::FVector3 normal;
                            if (i0 < mesh.normals.size() && i1 < mesh.normals.size() && i2 < mesh.normals.size()) {
                                normal = mesh.normals[i0] * b0 + mesh.normals[i1] * b1 + mesh.normals[i2] * b2;
                            }
                            if (normal.Dot(normal) < 1e-8f) {
                                normal = planeNormal.Dot(point.up) < 0.f ? planeNormal * -1.f : planeNormal;
                            }
                            point.normal = normal.Normalized();
                            point.slope = point.normal.Dot(point.up);
                            point.height = settings.isSphere ? (hit - settings.sphereCenter).Length() : hit.y;

                            for (uint32_t material = 0; material < point.materialWeights.size(); ++material) {
                                point.materialWeights[material] = materialWeight(i0, material) * b0 + materialWeight(i1, material) * b1 + materialWeight(i2, material) * b2;
                            }

                            float_t probability = layer.density;
                            for (auto&& pRule : layer.rules) {
                                probability *= std::clamp(pRule->Evaluate(point), 0.f, 1.f);
                                if (probability <= 0.f) {
                                    break;
                                }
                            }

                            const uint32_t h3 = TerrainScatterNoise::Hash(h2 ^ 0x1B873593U);
                            if (TerrainScatterNoise::ToFloat(h3) >= probability) {
                                continue;
                            }

                            if (layer.clearance > 0.f && !clearanceGrid.IsFree(hit, layer.clearance)) {
                                continue;
                            }

                            /// ---- прототип по весам
                            const uint32_t h4 = TerrainScatterNoise::Hash(h3 ^ 0xCC9E2D51U);
                            float_t pick = TerrainScatterNoise::ToFloat(h4) * layer.totalWeight;
                            uint32_t prototypeIndex = 0;
                            for (; prototypeIndex + 1 < layer.prototypes.size(); ++prototypeIndex) {
                                pick -= layer.prototypes[prototypeIndex].weight;
                                if (pick < 0.f) {
                                    break;
                                }
                            }
                            auto&& prototype = layer.prototypes[prototypeIndex];
                            if (prototype.weight <= 0.f) {
                                continue;
                            }

                            /// ---- трансформ: ось Y объекта между "вверх" мира и нормалью, поворот вокруг неё
                            SR_MATH_NS::FVector3 axisY = point.up * (1.f - layer.alignToNormal) + point.normal * layer.alignToNormal;
                            axisY = axisY.Dot(axisY) > 1e-8f ? axisY.Normalized() : point.up;

                            const SR_MATH_NS::FVector3 reference = std::abs(axisY.x) < 0.9f ? SR_MATH_NS::FVector3(1.f, 0.f, 0.f) : SR_MATH_NS::FVector3(0.f, 0.f, 1.f);
                            const SR_MATH_NS::FVector3 tangent = axisY.Cross(reference).Normalized();
                            const SR_MATH_NS::FVector3 bitangent = tangent.Cross(axisY);

                            const uint32_t h5 = TerrainScatterNoise::Hash(h4 ^ 0xE6546B64U);
                            const float_t yaw = layer.randomYaw ? TerrainScatterNoise::ToFloat(h5) * 6.28318530718f : 0.f;
                            const SR_MATH_NS::FVector3 axisX = tangent * std::cos(yaw) + bitangent * std::sin(yaw);
                            /// Z = X x Y: правая тройка, модель не зеркалится
                            const SR_MATH_NS::FVector3 axisZ = axisX.Cross(axisY);

                            const uint32_t h6 = TerrainScatterNoise::Hash(h5 ^ 0x85EBCA6BU);
                            const float_t scale = (layer.scaleMin + (layer.scaleMax - layer.scaleMin) * TerrainScatterNoise::ToFloat(h6)) * prototype.scale;

                            const SR_MATH_NS::FVector3 position = hit + axisY * (prototype.verticalOffset * scale - layer.embed);

                            TerrainScatterInstanceGPU instance;
                            instance.row0 = SR_MATH_NS::FVector4(axisX.x * scale, axisY.x * scale, axisZ.x * scale, position.x);
                            instance.row1 = SR_MATH_NS::FVector4(axisX.y * scale, axisY.y * scale, axisZ.y * scale, position.y);
                            instance.row2 = SR_MATH_NS::FVector4(axisX.z * scale, axisY.z * scale, axisZ.z * scale, position.z);

                            int32_t& groupIndex = groupIndices[prototypeIndex];
                            if (groupIndex < 0) {
                                groupIndex = static_cast<int32_t>(result.groups.size());
                                Group& group = result.groups.emplace_back();
                                group.layer = static_cast<uint16_t>(layerIndex);
                                group.prototype = static_cast<uint16_t>(prototypeIndex);
                            }
                            result.groups[groupIndex].instances.emplace_back(instance);
                            ++totalInstances;

                            if (layer.clearance > 0.f) {
                                clearanceGrid.Add(hit, layer.clearance);
                            }

                            result.bounds.min = SR_MATH_NS::FVector3(std::min(result.bounds.min.x, position.x), std::min(result.bounds.min.y, position.y), std::min(result.bounds.min.z, position.z));
                            result.bounds.max = SR_MATH_NS::FVector3(std::max(result.bounds.max.x, position.x), std::max(result.bounds.max.y, position.y), std::max(result.bounds.max.z, position.z));
                        }
                    }
                }
            }
        }

        if (result.groups.empty()) {
            result.bounds = SR_MATH_NS::AABB(mesh.origin, mesh.origin);
        }

        return result;
    }

    uint64_t TerrainScatter::CalculateStructureHash() const {
        uint64_t hash = TerrainScatterHashCombine(0x5CA77E2ULL, m_layers.size());

        for (auto&& pLayer : m_layers) {
            if (!pLayer) {
                hash = TerrainScatterHashCombine(hash, 0);
                continue;
            }

            hash = TerrainScatterHashCombine(hash, pLayer->GetPrototypes().size());

            for (auto&& pPrototype : pLayer->GetPrototypes()) {
                if (!pPrototype) {
                    hash = TerrainScatterHashCombine(hash, 1);
                    continue;
                }

                hash = TerrainScatterHashCombine(hash, pPrototype->GetMesh().GetHash());

                for (auto&& part : pPrototype->GetParts()) {
                    hash = TerrainScatterHashCombine(hash, static_cast<uint64_t>(part.meshId));
                    hash = TerrainScatterHashCombine(hash, part.material.GetHash());
                }

                for (auto&& lod : pPrototype->GetLods()) {
                    uint32_t distanceBits = 0;
                    uint32_t ratioBits = 0;
                    std::memcpy(&distanceBits, &lod.maxDistance, sizeof(float_t));
                    std::memcpy(&ratioBits, &lod.simplifyRatio, sizeof(float_t));
                    hash = TerrainScatterHashCombine(hash, distanceBits);
                    hash = TerrainScatterHashCombine(hash, ratioBits);
                    hash = TerrainScatterHashCombine(hash, lod.castShadows ? 3 : 5);
                }
            }
        }

        return hash;
    }

    void TerrainScatter::DestroySlots() {
        if (m_root && !m_root->IsDestroyed()) {
            m_root->Destroy();
        }
        m_root = nullptr;
        m_slots.clear();
        m_layerSlotOffsets.clear();
    }

    void TerrainScatter::BuildSlots(Terrain& terrain) {
        SR_TRACY_ZONE;

        DestroySlots();

        /// Объекты рендереров живут под пулом чанков: его дочерние объекты не сохраняются со сценой,
        /// а локальные координаты в нём - координаты террейна (сдвиг мира FloatingOrigin переносит их вместе с чанками)
        auto&& pChunkGenerator = terrain.GetChunkGenerator();
        auto&& pPool = pChunkGenerator ? pChunkGenerator->GetPoolObject().DynamicCast<SR_UTILS_NS::GameObject>() : SR_UTILS_NS::GameObject::Ptr();
        if (!pPool) {
            SR_WARN("TerrainScatter::BuildSlots() : terrain chunk generator has no pool object! Scatter is not rendered.");
            return;
        }

        pPool->SetChildrenTransient(true);
        m_root = pPool->CreateChild("Terrain Scatter");
        if (!m_root) {
            return;
        }
        m_root->SetChildrenTransient(true);

        for (uint32_t layerIndex = 0; layerIndex < m_layers.size(); ++layerIndex) {
            m_layerSlotOffsets.emplace_back(static_cast<uint32_t>(m_slots.size()));

            auto&& pLayer = m_layers[layerIndex];
            if (!pLayer) {
                continue;
            }

            for (auto&& pPrototype : pLayer->GetPrototypes()) {
                PrototypeSlot& slot = m_slots.emplace_back();
                if (!pPrototype || pPrototype->GetMesh().empty()) {
                    continue;
                }

                float_t previousDistance = 0.f;
                for (auto&& lod : pPrototype->GetLods()) {
                    /// Уровни идут по возрастанию дистанции; неупорядоченный уровень не рисуется
                    const float_t distance = std::max(previousDistance, lod.maxDistance);
                    previousDistance = distance;

                    slot.lodDistances.emplace_back(distance);
                    slot.lists.emplace_back();
                    auto&& renderers = slot.renderers.emplace_back();

                    for (auto&& part : pPrototype->GetParts()) {
                        auto&& pObject = m_root->CreateChild(SR_FORMAT("{} LOD{} #{}", pPrototype->GetMesh().GetBaseNameView(), slot.lodDistances.size() - 1, part.meshId));
                        if (!pObject) {
                            continue;
                        }

                        auto&& pRenderer = pObject->AddComponent<TerrainScatterRenderer>();
                        if (!pRenderer) {
                            SR_ERROR("TerrainScatter::BuildSlots() : failed to add scatter renderer!");
                            continue;
                        }

                        if (!part.material.empty()) {
                            pRenderer->SetMaterial(part.material);
                        }
                        pRenderer->SetGeometry(pPrototype->GetMesh(), part.meshId, lod.simplifyRatio);
                        pRenderer->SetCastShadows(lod.castShadows);
                        pRenderer->SetUseColorBuffer(false);

                        renderers.emplace_back(pRenderer);
                    }
                }

                slot.maxDistance = previousDistance;
            }
        }
    }

    void TerrainScatter::ApplyResults() {
        SR_TRACY_ZONE;

        static SR_THREAD_LOCAL SR_UTILS_NS::Vector<Result> results;
        {
            std::lock_guard lock(m_queueMutex);
            results.swap(m_results);
        }

        for (auto&& result : results) {
            auto&& pIt = m_entries.find(result.pChunk);
            if (pIt == m_entries.end() || pIt->second.generation != result.generation) {
                continue; /// чанк перегенерирован или выгружен
            }

            pIt->second.groups = std::move(result.groups);
            pIt->second.bounds = result.bounds;
            pIt->second.hasResult = true;
            m_isVisibleDirty = true;
        }

        results.clear();
    }

    void TerrainScatter::UpdateVisibility() {
        SR_TRACY_ZONE;

        /// Новый чанк, ждущий замены (IsHidden), загружается с выключенным объектом - его объекты показывать рано
        for (auto&& [pChunk, entry] : m_entries) {
            auto&& pObject = pChunk->GetObject();
            const bool isVisible = pObject && pObject->IsEnabled();
            if (entry.isVisible != isVisible) {
                entry.isVisible = isVisible;
                m_isVisibleDirty = true;
            }
        }
    }

    void TerrainScatter::RebuildVisible(const Terrain& terrain) {
        SR_TRACY_ZONE;

        const auto observer = terrain.GetObserver();

        TerrainGrassCullCone cone;
        const bool canCull = m_frustumCulling && observer.fovY > 0.f && observer.aspect > 0.f && observer.direction.Length() > 0.5f;
        if (canCull) {
            const float_t tanHalfY = std::tan(observer.fovY * 0.5f);
            const float_t tanHalfX = tanHalfY * observer.aspect;
            const float_t diagonalHalfAngle = std::atan(std::sqrt(tanHalfX * tanHalfX + tanHalfY * tanHalfY));
            cone.position = observer.position;
            cone.direction = observer.direction.Normalized();
            cone.halfAngle = std::min(diagonalHalfAngle + SR_RAD(std::max(0.f, m_cullMarginDegrees)), SR_RAD(179.f));
        }

        for (auto&& slot : m_slots) {
            for (auto&& list : slot.lists) {
                list.clear();
            }
        }

        uint32_t total = 0;
        uint32_t drawn = 0;

        for (auto&& [pChunk, entry] : m_entries) {
            for (auto&& group : entry.groups) {
                total += static_cast<uint32_t>(group.instances.size());
            }

            if (!entry.isVisible || entry.groups.empty()) {
                continue;
            }

            const SR_MATH_NS::FVector3 closest(
                std::clamp(observer.position.x, entry.bounds.min.x, entry.bounds.max.x),
                std::clamp(observer.position.y, entry.bounds.min.y, entry.bounds.max.y),
                std::clamp(observer.position.z, entry.bounds.min.z, entry.bounds.max.z)
            );
            const float_t boundsDistance = (observer.position - closest).Length();

            /// Конус с запасом проверяется по чанку целиком: тени от объектов чуть за кадром не пропадают
            if (canCull && !cone.IsVisible(entry.bounds)) {
                continue;
            }

            for (auto&& group : entry.groups) {
                if (group.layer >= m_layerSlotOffsets.size()) SR_UNLIKELY_ATTRIBUTE {
                    continue;
                }

                const uint32_t slotIndex = m_layerSlotOffsets[group.layer] + group.prototype;
                if (slotIndex >= m_slots.size()) SR_UNLIKELY_ATTRIBUTE {
                    continue;
                }

                auto&& slot = m_slots[slotIndex];
                if (slot.lodDistances.empty() || boundsDistance > slot.maxDistance) {
                    continue;
                }

                const float_t maxDistanceSq = slot.maxDistance * slot.maxDistance;

                for (auto&& instance : group.instances) {
                    const SR_MATH_NS::FVector3 delta = instance.GetPosition() - observer.position;
                    const float_t distanceSq = delta.Dot(delta);
                    if (distanceSq >= maxDistanceSq) {
                        continue;
                    }

                    uint32_t lod = 0;
                    while (lod + 1 < slot.lodDistances.size() && distanceSq >= slot.lodDistances[lod] * slot.lodDistances[lod]) {
                        ++lod;
                    }

                    slot.lists[lod].emplace_back(instance);
                    ++drawn;
                }
            }
        }

        for (auto&& slot : m_slots) {
            for (uint32_t lod = 0; lod < slot.renderers.size(); ++lod) {
                for (auto&& pRenderer : slot.renderers[lod]) {
                    pRenderer->SetInstances(slot.lists[lod]);
                }
            }
        }

        m_totalInstances = total;
        m_drawnInstances = drawn;
        m_lastObserverPosition = observer.position;
        m_lastObserverDirection = observer.direction.Length() > 0.5f ? observer.direction.Normalized() : SR_MATH_NS::FVector3();
        m_isVisibleDirty = false;
    }

    void TerrainScatter::Update(Terrain& terrain, float_t dt) {
        SR_TRACY_ZONE;

        if (!m_enabled) {
            if (m_root || !m_entries.empty()) {
                Shutdown();
            }
            return;
        }

        /// Набор слоёв/прототипов/LOD/частей изменился - рендереры пересоздаются, старые объекты чанков
        /// ссылаются на прежние индексы и выводятся заново
        const uint64_t structureHash = CalculateStructureHash();
        if (structureHash != m_structureHash) {
            const bool hadStructure = m_structureHash != 0;
            m_structureHash = structureHash;
            BuildSlots(terrain);
            m_isVisibleDirty = true;
            if (hadStructure && !m_entries.empty()) {
                /// Группы ссылаются на индексы прежних прототипов
                for (auto&& [pChunk, entry] : m_entries) {
                    entry.groups.clear();
                }
                m_isRegenerateRequested = true;
            }
        }

        if (m_isRegenerateRequested) {
            m_isRegenerateRequested = false;
            /// Старые объекты остаются, пока заменяемые чанки не уйдут
            if (auto&& pChunkGenerator = terrain.GetChunkGenerator()) {
                /// Перегенерация через замену чанков: каждый новый чанк заново пришлёт свою поверхность
                pChunkGenerator->InvalidateRegion(SR_MATH_NS::AABB(SR_MATH_NS::FVector3(-1e9f), SR_MATH_NS::FVector3(1e9f)));
            }
            m_isVisibleDirty = true;
        }

        ApplyResults();
        UpdateVisibility();

        for (auto&& slot : m_slots) {
            for (auto&& renderers : slot.renderers) {
                for (auto&& pRenderer : renderers) {
                    pRenderer->FreeRetired();
                }
            }
        }

        const auto observer = terrain.GetObserver();
        const bool moved = (observer.position - m_lastObserverPosition).Length() > std::max(0.1f, m_rebuildDistance);

        bool rotated = false;
        if (m_frustumCulling && observer.fovY > 0.f && observer.direction.Length() > 0.5f) {
            const float_t cosAngle = std::clamp(observer.direction.Normalized().Dot(m_lastObserverDirection), -1.f, 1.f);
            rotated = std::acos(cosAngle) > SR_RAD(std::max(1.f, m_cullMarginDegrees)) * 0.5f;
        }

        if (moved || rotated || m_isVisibleDirty) {
            RebuildVisible(terrain);
        }
    }
}
