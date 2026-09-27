//
// Created by Monika on 27.09.2026.
//

#include <Engine/World/TerrainGrass.h>
#include <Engine/World/Terrain.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/FileSystem/PathDataAccessor.h>

#include <Codegen/TerrainGrass.generated.hpp>

namespace SR_CORE_NS {
    namespace {
        SR_NODISCARD SR_FORCE_INLINE uint32_t GrassHash(uint32_t x) noexcept {
            /// lowbias32
            x ^= x >> 16;
            x *= 0x7feb352dU;
            x ^= x >> 15;
            x *= 0x846ca68bU;
            x ^= x >> 16;
            return x;
        }

        SR_NODISCARD SR_FORCE_INLINE uint32_t GrassHash(int32_t x, int32_t y, int32_t z, uint32_t seed) noexcept {
            uint32_t h = GrassHash(static_cast<uint32_t>(x) + seed * 0x9E3779B9U);
            h = GrassHash(h ^ static_cast<uint32_t>(y) * 0x85EBCA6BU);
            h = GrassHash(h ^ static_cast<uint32_t>(z) * 0xC2B2AE35U);
            return h;
        }

        SR_NODISCARD SR_FORCE_INLINE float_t GrassToFloat(uint32_t h) noexcept {
            return static_cast<float_t>(h >> 8) * (1.f / 16777216.f);
        }

        /// Value noise [0, 1] по мировым XZ
        SR_NODISCARD float_t GrassValueNoise(float_t x, float_t z, uint32_t seed) noexcept {
            const float_t fx = std::floor(x);
            const float_t fz = std::floor(z);
            const auto ix = static_cast<int32_t>(fx);
            const auto iz = static_cast<int32_t>(fz);
            float_t tx = x - fx;
            float_t tz = z - fz;
            tx = tx * tx * (3.f - 2.f * tx);
            tz = tz * tz * (3.f - 2.f * tz);

            const float_t a = GrassToFloat(GrassHash(ix, 0, iz, seed));
            const float_t b = GrassToFloat(GrassHash(ix + 1, 0, iz, seed));
            const float_t c = GrassToFloat(GrassHash(ix, 0, iz + 1, seed));
            const float_t d = GrassToFloat(GrassHash(ix + 1, 0, iz + 1, seed));

            const float_t ab = a + (b - a) * tx;
            const float_t cd = c + (d - c) * tx;
            return ab + (cd - ab) * tz;
        }

        SR_NODISCARD float_t GrassFbm(float_t x, float_t z, uint32_t seed) noexcept {
            float_t sum = 0.f;
            float_t amplitude = 0.5f;
            float_t norm = 0.f;
            for (uint32_t octave = 0; octave < 3; ++octave) {
                sum += GrassValueNoise(x, z, seed + octave * 7919U) * amplitude;
                norm += amplitude;
                x *= 2.03f;
                z *= 2.03f;
                amplitude *= 0.5f;
            }
            return sum / norm;
        }

        SR_NODISCARD SR_FORCE_INLINE float_t GrassSmoothStep(float_t edge0, float_t edge1, float_t x) noexcept {
            if (edge1 <= edge0) {
                return x >= edge1 ? 1.f : 0.f;
            }
            const float_t t = std::clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
            return t * t * (3.f - 2.f * t);
        }
    }

    TerrainGrass::TerrainGrass()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    TerrainGrass::~TerrainGrass() {
        StopWorker();
    }

    TerrainGrassLodParams TerrainGrass::GetLodParams() const {
        TerrainGrassLodParams params;
        params.fullDensityDistance = std::max(0.f, m_fullDensityDistance);
        params.maxDistance = std::max(params.fullDensityDistance + 0.01f, m_maxDistance);
        params.falloff = std::max(0.01f, m_falloff);
        params.minKeep = std::clamp(m_minKeep, 0.f, 1.f);
        params.segmentsLodDistance = m_segmentsLodDistance;
        params.segments = std::clamp<uint32_t>(m_segments, 1, 7);
        params.lowSegments = std::clamp<uint32_t>(m_lowSegments, 1, params.segments);
        return params;
    }

    TerrainGrass::Settings TerrainGrass::MakeSettings() const {
        Settings settings;
        settings.density = std::max(0.f, m_density);
        settings.cellSize = std::max(1.f, m_cellSize);
        settings.slopeMin = m_slopeMin;
        settings.slopeMax = m_slopeMax;
        settings.noiseScale = m_noiseScale;
        settings.noiseThreshold = m_noiseThreshold;
        settings.noiseContrast = m_noiseContrast;
        settings.detailNoiseScale = m_detailNoiseScale;
        settings.maxInstancesPerChunk = m_maxInstancesPerChunk;
        settings.seed = m_seed;
        settings.allowedMaterials.assign(m_allowedMaterials.begin(), m_allowedMaterials.end());
        return settings;
    }

    void TerrainGrass::StartWorker() {
        if (m_worker.joinable()) {
            return;
        }
        m_stopWorker = false;
        m_worker = std::thread([this]() { WorkerLoop(); });
    }

    void TerrainGrass::StopWorker() {
        {
            std::lock_guard lock(m_queueMutex);
            m_stopWorker = true;
            m_tasks.clear();
        }
        m_queueCondition.notify_all();
        if (m_worker.joinable()) {
            m_worker.join();
        }
        std::lock_guard lock(m_queueMutex);
        m_results.clear();
    }

    void TerrainGrass::Shutdown() {
        SR_TRACY_ZONE;

        StopWorker();

        for (auto&& pRenderer : m_renderers) {
            if (pRenderer) {
                pRenderer->ClearInstances();
            }
        }

        m_renderers.clear();
        m_generations.clear();
    }

    void TerrainGrass::WorkerLoop() {
        while (true) {
            Task task;
            Settings settings;
            {
                std::unique_lock lock(m_queueMutex);
                m_queueCondition.wait(lock, [this]() { return m_stopWorker || !m_tasks.empty(); });
                if (m_stopWorker) {
                    return;
                }
                task = std::move(m_tasks.front());
                m_tasks.pop_front();
                settings = MakeSettings();
            }

            Result result = Generate(settings, std::move(task));

            std::lock_guard lock(m_queueMutex);
            if (m_stopWorker) {
                return;
            }
            m_results.emplace_back(std::move(result));
        }
    }

    uint64_t TerrainGrass::NextGeneration(TerrainGrassRenderer* pRenderer) {
        const uint64_t generation = ++m_generationCounter;
        m_generations[pRenderer] = generation;
        return generation;
    }

    SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer> TerrainGrass::GetOrCreateRenderer(ITerrainChunk& chunk) {
        auto&& pObject = chunk.GetObject();
        if (!pObject) {
            return nullptr;
        }

        if (auto&& pRenderer = pObject->GetComponent<TerrainGrassRenderer>()) {
            return pRenderer;
        }

        auto&& pRenderer = pObject->AddComponent<TerrainGrassRenderer>();
        if (!pRenderer) {
            SR_ERROR("TerrainGrass::GetOrCreateRenderer() : failed to add grass renderer to chunk object!");
            return nullptr;
        }

        if (!m_material.empty()) {
            pRenderer->SetMaterial(m_material);
        }

        return pRenderer;
    }

    void TerrainGrass::OnChunkGenerated(Terrain& terrain, ITerrainChunk& chunk, TerrainGrassSourceMesh&& mesh) {
        SR_TRACY_ZONE;

        if (!m_enabled) {
            return;
        }

        chunk.SetGrass(this);

        auto&& pRenderer = GetOrCreateRenderer(chunk);
        if (!pRenderer) {
            return;
        }

        if (std::find(m_renderers.begin(), m_renderers.end(), pRenderer) == m_renderers.end()) {
            m_renderers.emplace_back(pRenderer);
        }

        pRenderer->SetCastShadows(m_castShadows);

        const uint64_t generation = NextGeneration(pRenderer.Get());

        if (mesh.indices.empty()) {
            pRenderer->ClearInstances();
            return;
        }

        StartWorker();

        {
            std::lock_guard lock(m_queueMutex);
            /// Если по этому чанку уже стоит задача - она устарела
            std::erase_if(m_tasks, [&](const Task& task) { return task.pRenderer == pRenderer; });
            m_tasks.emplace_back(Task {
                .generation = generation,
                .pRenderer = pRenderer,
                .mesh = std::move(mesh)
            });
        }

        m_queueCondition.notify_one();
    }

    void TerrainGrass::OnChunkDeactivated(ITerrainChunk& chunk) {
        SR_TRACY_ZONE;

        auto&& pObject = chunk.GetObject();
        if (!pObject) {
            return;
        }

        auto&& pRenderer = pObject->GetComponent<TerrainGrassRenderer>();
        if (!pRenderer) {
            return;
        }

        /// Инвалидируем результаты генерации, которые ещё в полёте
        SR_MAYBE_UNUSED_VAR NextGeneration(pRenderer.Get());

        {
            std::lock_guard lock(m_queueMutex);
            std::erase_if(m_tasks, [&](const Task& task) { return task.pRenderer == pRenderer; });
        }

        pRenderer->ClearInstances();
    }

    void TerrainGrass::Update(Terrain& terrain, float_t dt) {
        SR_TRACY_ZONE;

        if (!m_enabled) {
            if (!m_renderers.empty()) {
                Shutdown();
            }
            return;
        }

        /// ---- применяем готовые результаты генерации
        {
            static SR_THREAD_LOCAL std::vector<Result> results;
            {
                std::lock_guard lock(m_queueMutex);
                std::swap(results, m_results);
            }

            for (auto&& result : results) {
                auto&& pIt = m_generations.find(result.pRenderer.Get());
                if (pIt == m_generations.end() || pIt->second != result.generation) {
                    continue; /// чанк успели перегенерировать или выгрузить
                }
                result.pRenderer->SetInstances(std::move(result.instances), std::move(result.cells));
                m_forceLodUpdate = true;
            }

            results.clear();
        }

        /// ---- LOD / отсечение по ячейкам
        const auto observer = terrain.GetObserver();
        const auto lodParams = GetLodParams();

        /// Конус видимости с запасом m_cullMarginDegrees: пока камера поворачивается в его пределах,
        /// отсечение не пересчитывается (и командные буферы не пересобираются).
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

        const float_t margin = SR_RAD(std::max(0.f, m_cullMarginDegrees));
        const bool moved = (observer.position - m_lastObserverPosition).Length() > 0.5f;
        const bool rotated = canCull && std::acos(std::clamp(cone.direction.Dot(m_lastObserverDirection), -1.f, 1.f)) > margin * 0.5f;
        const bool paramsChanged = !(lodParams == m_lastLodParams) || canCull != m_lastCanCull;

        if (!moved && !rotated && !paramsChanged && !m_forceLodUpdate) {
            return;
        }

        m_lastObserverPosition = observer.position;
        m_lastObserverDirection = cone.direction;
        m_lastLodParams = lodParams;
        m_lastCanCull = canCull;
        m_forceLodUpdate = false;

        const TerrainGrassCullCone* pCone = canCull ? &cone : nullptr;

        uint32_t total = 0;
        uint32_t drawn = 0;

        for (auto&& pRenderer : m_renderers) {
            pRenderer->SetCastShadows(m_castShadows);
            pRenderer->UpdateLod(observer.position, lodParams, pCone);
            total += pRenderer->GetInstancesCount();
            drawn += pRenderer->GetDrawnInstancesCount();
        }

        m_totalInstances = total;
        m_drawnInstances = drawn;
    }

    TerrainGrass::Result TerrainGrass::Generate(const Settings& settings, Task&& task) {
        SR_TRACY_ZONE;

        Result result;
        result.generation = task.generation;
        result.pRenderer = task.pRenderer;

        const auto& mesh = task.mesh;
        const auto& positions = mesh.positions;
        const auto& normals = mesh.normals;
        const auto& indices = mesh.indices;
        const bool hasNormals = normals.size() == positions.size();
        const bool hasMaxEdge = mesh.maxEdgeLength > 0.f;
        const bool hasBounds = mesh.bounds.max.x > mesh.bounds.min.x && mesh.bounds.max.z > mesh.bounds.min.z;
        const bool hasMaterials = mesh.materials.size() == positions.size() && !settings.allowedMaterials.empty();

        if (positions.empty() || indices.size() < 3 || settings.density <= 0.f) {
            return result;
        }

        const uint32_t seed = static_cast<uint32_t>(settings.seed) ^ static_cast<uint32_t>(settings.seed >> 32);

        /// ---- границы чанка, чтобы разложить травинки по ячейкам
        SR_MATH_NS::FVector3 boundsMin(SR_FLOAT_MAX);
        SR_MATH_NS::FVector3 boundsMax(-SR_FLOAT_MAX);
        for (auto&& position : positions) {
            boundsMin = SR_MATH_NS::FVector3(std::min(boundsMin.x, position.x), std::min(boundsMin.y, position.y), std::min(boundsMin.z, position.z));
            boundsMax = SR_MATH_NS::FVector3(std::max(boundsMax.x, position.x), std::max(boundsMax.y, position.y), std::max(boundsMax.z, position.z));
        }

        const float_t cellSize = settings.cellSize;
        const auto cellsX = static_cast<uint32_t>(std::max(1.f, std::ceil((boundsMax.x - boundsMin.x) / cellSize)));
        const auto cellsZ = static_cast<uint32_t>(std::max(1.f, std::ceil((boundsMax.z - boundsMin.z) / cellSize)));

        struct RawInstance {
            TerrainGrassInstance instance;
            uint32_t cell;
        };

        std::vector<RawInstance> raw;
        raw.reserve(std::min<size_t>(indices.size() / 3 * 8, settings.maxInstancesPerChunk));

        const auto isMaterialAllowed = [&](uint32_t vertex) {
            if (!hasMaterials) {
                return true;
            }
            const uint32_t material = mesh.materials[vertex];
            return std::find(settings.allowedMaterials.begin(), settings.allowedMaterials.end(), material) != settings.allowedMaterials.end();
        };

        const auto densityMask = [&](const SR_MATH_NS::FVector3& worldPos, float_t up) -> float_t {
            const float_t slope = GrassSmoothStep(settings.slopeMin, settings.slopeMax, up);
            if (slope <= 0.f) {
                return 0.f;
            }

            /// крупные поляны и проплешины
            float_t mask = 1.f;
            if (settings.noiseScale > 0.f) {
                const float_t n = GrassFbm(worldPos.x * settings.noiseScale, worldPos.z * settings.noiseScale, seed + 101U);
                mask = std::clamp((n - settings.noiseThreshold) * settings.noiseContrast + 0.5f, 0.f, 1.f);
            }

            /// мелкая неоднородность густоты внутри поляны
            if (settings.detailNoiseScale > 0.f) {
                const float_t d = GrassValueNoise(worldPos.x * settings.detailNoiseScale, worldPos.z * settings.detailNoiseScale, seed + 202U);
                mask *= 0.55f + 0.45f * d;
            }

            return slope * mask;
        };

        for (size_t t = 0; t + 2 < indices.size(); t += 3) {
            if (raw.size() >= settings.maxInstancesPerChunk) {
                break;
            }

            const uint32_t ia = indices[t + 0];
            const uint32_t ib = indices[t + 1];
            const uint32_t ic = indices[t + 2];

            if (ia >= positions.size() || ib >= positions.size() || ic >= positions.size()) SR_UNLIKELY_ATTRIBUTE {
                continue;
            }

            if (!isMaterialAllowed(ia) && !isMaterialAllowed(ib) && !isMaterialAllowed(ic)) {
                continue;
            }

            const auto& a = positions[ia];
            const auto& b = positions[ib];
            const auto& c = positions[ic];

            if (hasMaxEdge) {
                const float_t maxEdgeSq = mesh.maxEdgeLength * mesh.maxEdgeLength;
                const SR_MATH_NS::FVector3 ab = b - a;
                const SR_MATH_NS::FVector3 bc = c - b;
                const SR_MATH_NS::FVector3 ca = a - c;
                if (ab.Dot(ab) > maxEdgeSq || bc.Dot(bc) > maxEdgeSq || ca.Dot(ca) > maxEdgeSq) {
                    continue;
                }
            }

            const SR_MATH_NS::FVector3 cross = (b - a).Cross(c - a);
            const float_t crossLength = cross.Length();
            if (crossLength <= 1e-8f) {
                continue;
            }

            const float_t area = crossLength * 0.5f;
            SR_MATH_NS::FVector3 faceNormal = cross / crossLength;

            /// Нормаль берётся строго по обходу треугольника - так же её считает ComputeSmoothNormals для рендера.
            /// Разворачивать её по сглаженным нормалям нельзя: на стыках чанков они считаются только по своей
            /// половине треугольников, и трава вырастала бы с нижней стороны поверхности.

            /// быстрый отказ для крутых и перевёрнутых треугольников
            if (faceNormal.y < settings.slopeMin - 0.1f) {
                continue;
            }

            const float_t expected = area * settings.density;

            /// детерминированный сид треугольника по его мировому центру (не зависит от порядка индексов и от чанка)
            const SR_MATH_NS::FVector3 center = (a + b + c) / 3.f + mesh.origin;
            const uint32_t triangleSeed = GrassHash(
                static_cast<int32_t>(std::floor(center.x * 64.f)),
                static_cast<int32_t>(std::floor(center.y * 64.f)),
                static_cast<int32_t>(std::floor(center.z * 64.f)),
                seed
            );

            auto count = static_cast<uint32_t>(expected);
            if (GrassToFloat(GrassHash(triangleSeed ^ 0xA511E9B3U)) < expected - static_cast<float_t>(count)) {
                ++count;
            }

            for (uint32_t i = 0; i < count; ++i) {
                const uint32_t h0 = GrassHash(triangleSeed + i * 0x9E3779B9U);
                const uint32_t h1 = GrassHash(h0 ^ 0x68E31DA4U);
                const uint32_t h2 = GrassHash(h1 ^ 0xB5297A4DU);
                const uint32_t h3 = GrassHash(h2 ^ 0x1B56C4E9U);

                /// равномерная точка в треугольнике
                float_t u = GrassToFloat(h0);
                float_t v = GrassToFloat(h1);
                if (u + v > 1.f) {
                    u = 1.f - u;
                    v = 1.f - v;
                }
                const float_t w = 1.f - u - v;

                const SR_MATH_NS::FVector3 position = a * w + b * u + c * v;
                const SR_MATH_NS::FVector3 worldPos = position + mesh.origin;

                if (hasBounds && (
                    position.x < mesh.bounds.min.x || position.x > mesh.bounds.max.x ||
                    position.y < mesh.bounds.min.y || position.y > mesh.bounds.max.y ||
                    position.z < mesh.bounds.min.z || position.z > mesh.bounds.max.z))
                {
                    continue;
                }

                SR_MATH_NS::FVector3 normal = faceNormal;
                if (hasNormals) {
                    normal = normals[ia] * w + normals[ib] * u + normals[ic] * v;
                    const float_t len = normal.Length();
                    /// На границе чанка сглаженная нормаль считается только по треугольникам своего чанка
                    /// и может сильно расходиться с реальной поверхностью - тогда доверяем нормали грани.
                    normal = (len > 1e-3f && (normal / len).Dot(faceNormal) > 0.5f) ? normal / len : faceNormal;
                }

                /// отбор по маске плотности - на склонах и проплешинах травинки исчезают плавно, а не порогом.
                /// Для наклона берётся худшая из нормалей, чтобы трава не лезла на стены через сглаживание.
                if (GrassToFloat(h2) >= densityMask(worldPos, std::min(normal.y, faceNormal.y + 0.1f))) {
                    continue;
                }

                const auto cellX = std::min(cellsX - 1, static_cast<uint32_t>(std::max(0.f, (position.x - boundsMin.x) / cellSize)));
                const auto cellZ = std::min(cellsZ - 1, static_cast<uint32_t>(std::max(0.f, (position.z - boundsMin.z) / cellSize)));

                RawInstance& instance = raw.emplace_back();
                instance.instance.position = position;
                instance.instance.normal = normal;
                instance.instance.rank = GrassToFloat(h3);
                instance.instance.random = GrassToFloat(GrassHash(h3 ^ 0x2C1B3C6DU));
                instance.cell = cellZ * cellsX + cellX;

                if (raw.size() >= settings.maxInstancesPerChunk) {
                    break;
                }
            }
        }

        if (raw.empty()) {
            return result;
        }

        /// ---- сортировка: ячейка -> корзина rank. Так любой LOD ячейки становится одним непрерывным диапазоном.
        const auto bucketOf = [](float_t rank) {
            return std::min(SR_TERRAIN_GRASS_RANK_BUCKETS - 1, static_cast<uint32_t>(rank * static_cast<float_t>(SR_TERRAIN_GRASS_RANK_BUCKETS)));
        };

        std::sort(raw.begin(), raw.end(), [&](const RawInstance& left, const RawInstance& right) {
            if (left.cell != right.cell) {
                return left.cell < right.cell;
            }
            return left.instance.rank < right.instance.rank;
        });

        result.instances.resize(raw.size());

        size_t begin = 0;
        while (begin < raw.size()) {
            const uint32_t cellIndex = raw[begin].cell;
            size_t end = begin;

            TerrainGrassCell cell;
            cell.start = static_cast<uint32_t>(begin);
            cell.bounds = SR_MATH_NS::AABB(SR_MATH_NS::FVector3(SR_FLOAT_MAX), SR_MATH_NS::FVector3(-SR_FLOAT_MAX));

            std::array<uint32_t, SR_TERRAIN_GRASS_RANK_BUCKETS> histogram = { };

            while (end < raw.size() && raw[end].cell == cellIndex) {
                const auto& instance = raw[end].instance;
                result.instances[end] = instance;
                ++histogram[bucketOf(instance.rank)];

                const SR_MATH_NS::FVector3 worldPos = instance.position + mesh.origin;
                cell.bounds.min = SR_MATH_NS::FVector3(std::min(cell.bounds.min.x, worldPos.x), std::min(cell.bounds.min.y, worldPos.y), std::min(cell.bounds.min.z, worldPos.z));
                cell.bounds.max = SR_MATH_NS::FVector3(std::max(cell.bounds.max.x, worldPos.x), std::max(cell.bounds.max.y, worldPos.y), std::max(cell.bounds.max.z, worldPos.z));
                ++end;
            }

            uint32_t accumulated = 0;
            for (uint32_t i = 0; i < SR_TERRAIN_GRASS_RANK_BUCKETS; ++i) {
                accumulated += histogram[i];
                cell.cumulative[i] = accumulated;
            }

            /// запас на высоту травинок и изгиб ветром, иначе верхушки отсекались бы фрустумом
            cell.bounds.min -= SR_MATH_NS::FVector3(1.5f, 0.5f, 1.5f);
            cell.bounds.max += SR_MATH_NS::FVector3(1.5f, 2.f, 1.5f);

            result.cells.emplace_back(cell);
            begin = end;
        }

        return result;
    }
}
