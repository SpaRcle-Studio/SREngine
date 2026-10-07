//
// Created by Monika on 27.09.2026.
//

#include <Engine/World/TerrainGrass.h>
#include <Engine/World/Terrain.h>
#include <Engine/World/TerrainGrassBender.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/FileSystem/PathDataAccessor.h>
#include <Utils/Platform/Platform.h>

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
        settings.materialWeightDensity = m_materialWeightDensity;
        settings.materialWeightThreshold = std::clamp(m_materialWeightThreshold, 0.f, 1.f);
        settings.lod = GetLodParams();
        settings.generationMargin = std::max(0.f, m_generationMargin);
        return settings;
    }

    void TerrainGrass::StartWorker() {
        if (m_worker) {
            return;
        }

        m_stopWorker = false;

        if (!SR_HTYPES_NS::Thread::Factory::Instance().Create(m_worker, &TerrainGrass::WorkerStep, this)) {
            SR_ERROR("TerrainGrass::StartWorker() : failed to create thread!");
            m_worker = nullptr;
            return;
        }

        m_worker->SetName("Terrain grass");
    }

    void TerrainGrass::StopWorker() {
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
        m_sources.clear();
        m_retiredRenderers.clear();
        m_trails.clear();
        m_benderData.clear();
        if (m_pBenders) {
            m_pBenders->SetBenders(m_benderData);
        }
    }

    bool TerrainGrass::WorkerStep() {
        if (m_stopWorker) {
            return false;
        }

        Task task;
        Settings settings;
        bool hasTask = false;
        {
            std::lock_guard lock(m_queueMutex);
            if (!m_tasks.empty()) {
                task = std::move(m_tasks.front());
                m_tasks.pop_front();
                settings = MakeSettings();
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

        Result result = Generate(settings, std::move(task));

        std::lock_guard lock(m_queueMutex);
        if (m_stopWorker) {
            return false;
        }
        m_results.emplace_back(std::move(result));

        return true;
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

        if (mesh.indices.empty()) {
            /// Травы у чанка нет. Рендерер не создаём, а оставшийся от прошлого владельца объекта - сбрасываем
            OnChunkDeactivated(chunk);
            return;
        }

        auto&& pRenderer = GetOrCreateRenderer(chunk);
        if (!pRenderer) {
            return;
        }

        if (std::find(m_renderers.begin(), m_renderers.end(), pRenderer) == m_renderers.end()) {
            m_renderers.emplace_back(pRenderer);
        }
        /// Активный рендерер сам досвобождает старые буферы в UpdateLod
        std::erase(m_retiredRenderers, pRenderer);

        pRenderer->SetCastShadows(m_castShadows);

        if (!m_pBenders) {
            m_pBenders = new TerrainGrassBenders();
        }
        pRenderer->SetBenders(m_pBenders);

        Source& source = m_sources[pRenderer.Get()];
        source.isApplied = false;
        source.pMesh = SourceMeshPtr::MakeShared(std::move(mesh));
        source.observer = terrain.GetObserver().position;

        QueueGeneration(pRenderer, source);
    }

    void TerrainGrass::QueueGeneration(const SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer>& pRenderer, Source& source) {
        source.isPending = true;
        const uint64_t generation = NextGeneration(const_cast<TerrainGrassRenderer*>(pRenderer.Get()));

        StartWorker();

        std::lock_guard lock(m_queueMutex);
        /// Если по этому чанку уже стоит задача - она устарела
        std::erase_if(m_tasks, [&](const Task& task) { return task.pRenderer == pRenderer; });
        m_tasks.emplace_back(Task {
            .generation = generation,
            .pRenderer = pRenderer,
            .pMesh = source.pMesh,
            .observer = source.observer
        });
    }

    void TerrainGrass::UpdateRegeneration(const SR_MATH_NS::FVector3& observer) {
        SR_TRACY_ZONE;

        /// Травинки сгенерированы с плотностью LOD относительно точки генерации с запасом generationMargin.
        /// Пока наблюдатель в пределах regenerateDistance от неё - запаса хватает, иначе вблизи станет редко.
        const float_t threshold = std::max(1.f, std::min(m_regenerateDistance, m_generationMargin));
        for (auto&& pRenderer : m_renderers) {
            auto&& pIt = m_sources.find(pRenderer.Get());
            if (pIt == m_sources.end() || pIt->second.isPending) {
                continue;
            }
            if (pIt->second.observer.Distance(observer) < threshold) {
                continue;
            }
            pIt->second.observer = observer;
            QueueGeneration(pRenderer, pIt->second);
        }
    }

    bool TerrainGrass::IsChunkReady(const ITerrainChunk& chunk) const {
        auto&& pObject = chunk.GetObject();
        if (!pObject || !m_enabled) {
            return true;
        }

        auto&& pRenderer = pObject->GetComponent<TerrainGrassRenderer>();
        if (!pRenderer) {
            return true;
        }

        auto&& pIt = m_sources.find(pRenderer.Get());
        /// Нет источника - травы у чанка нет (пустой меш или LOD без травы)
        return pIt == m_sources.end() || pIt->second.isApplied;
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

        {
            std::lock_guard lock(m_queueMutex);
            std::erase_if(m_tasks, [&](const Task& task) { return task.pRenderer == pRenderer; });
        }

        pRenderer->ClearInstances();

        /// Объект чанка может быть уничтожен пулом, поэтому рендерер больше не отслеживается.
        /// Результаты генерации, которые ещё в полёте, отбросятся: поколения для рендерера больше нет.
        m_generations.erase(pRenderer.Get());
        m_sources.erase(pRenderer.Get());
        std::erase(m_renderers, pRenderer);

        if (!pRenderer->FreeRetired()) {
            m_retiredRenderers.emplace_back(pRenderer);
        }
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
                if (auto&& pSource = m_sources.find(result.pRenderer.Get()); pSource != m_sources.end()) {
                    pSource->second.isPending = false;
                    pSource->second.isApplied = true;
                }
                result.pRenderer->SetInstances(std::move(result.instances), std::move(result.cells));
                m_forceLodUpdate = true;
            }

            results.clear();
        }

        UpdateBenders(dt);

        std::erase_if(m_retiredRenderers, [](const SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer>& pRenderer) {
            return !pRenderer || pRenderer->FreeRetired();
        });

        /// ---- LOD / отсечение по ячейкам
        const auto observer = terrain.GetObserver();

        UpdateRegeneration(observer.position);

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

    void TerrainGrass::UpdateBenders(float_t dt) {
        SR_TRACY_ZONE;

        struct Candidate {
            TerrainGrassBenderGPU data;
            float_t priority = 0.f;
        };

        static SR_THREAD_LOCAL SR_UTILS_NS::Vector<Candidate> candidates;
        candidates.clear();

        const SR_MATH_NS::FVector3 observer = m_lastObserverPosition;
        const float_t maxDistanceSq = m_bendMaxDistance * m_bendMaxDistance;
        const float_t spacing = std::max(0.05f, m_trailSpacing);

        const auto distanceSqToObserver = [&](const SR_MATH_NS::FVector3& point) {
            const SR_MATH_NS::FVector3 delta = point - observer;
            return delta.Dot(delta);
        };

        const auto flatDirection = [](const SR_MATH_NS::FVector3& from, const SR_MATH_NS::FVector3& to) {
            SR_MATH_NS::FVector3 direction = to - from;
            direction.y = 0.f;
            const float_t length = direction.Length();
            return length > 1e-4f ? direction / length : SR_MATH_NS::FVector3(0.f);
        };

        for (auto&& [pOwner, trail] : m_trails) {
            trail.isOwnerAlive = false;
        }

        /// ---- живые объекты
        for (auto&& pBender : TerrainGrassBender::GetActiveBenders()) {
            const SR_MATH_NS::FVector3 position = pBender->GetBendPosition();
            const float_t radius = pBender->GetRadius();
            const float_t strength = pBender->GetStrength();

            if (radius <= 0.f || strength <= 0.f) {
                continue;
            }

            SR_MATH_NS::FVector3 direction(0.f);

            if (pBender->IsTrailEnabled()) {
                auto&& trail = m_trails[pBender];
                trail.isOwnerAlive = true;
                trail.duration = std::max(0.1f, pBender->GetTrailDuration());
                trail.maxLength = std::max(0.f, pBender->GetTrailLength());

                /// точки следа неподвижны: новая добавляется только когда объект отошёл на spacing
                if (trail.points.empty() || (position - trail.points.back().position).Length() >= spacing) {
                    trail.points.emplace_back(TrailPoint {
                        .position = position,
                        .direction = trail.points.empty() ? SR_MATH_NS::FVector3(0.f) : flatDirection(trail.points.back().position, position),
                        .radius = radius,
                        .strength = strength,
                        .age = 0.f
                    });
                }

                if (trail.points.size() > 1) {
                    direction = trail.points.back().direction;
                }
            }

            const float_t distanceSq = distanceSqToObserver(position);
            if (distanceSq <= maxDistanceSq) {
                /// живые объекты всегда важнее следов
                candidates.emplace_back(Candidate {
                    .data = TerrainGrassBenderGPU { .position = position, .radius = radius, .direction = direction, .strength = strength },
                    .priority = 1000000.f - distanceSq
                });
            }
        }

        /// ---- следы: старение, обрезка по длине
        for (auto pIt = m_trails.begin(); pIt != m_trails.end(); ) {
            auto&& trail = pIt->second;
            auto&& points = trail.points;

            for (auto&& point : points) {
                point.age += dt;
            }

            /// угасшие точки в начале следа
            size_t firstAlive = 0;
            while (firstAlive < points.size() && points[firstAlive].age >= trail.duration) {
                ++firstAlive;
            }

            /// обрезка по длине, считая от самой новой точки
            if (trail.maxLength > 0.f && points.size() > 1) {
                float_t length = 0.f;
                for (size_t i = points.size() - 1; i > firstAlive; --i) {
                    length += (points[i].position - points[i - 1].position).Length();
                    if (length > trail.maxLength) {
                        firstAlive = std::max(firstAlive, i);
                        break;
                    }
                }
            }

            if (firstAlive > 0) {
                points.erase(points.begin(), points.begin() + static_cast<std::ptrdiff_t>(firstAlive));
            }

            if (points.empty() && !trail.isOwnerAlive) {
                pIt = m_trails.erase(pIt);
                continue;
            }

            for (auto&& point : points) {
                /// трава распрямляется быстро в начале и медленно в конце
                const float_t life = 1.f - point.age / trail.duration;
                const float_t strength = point.strength * life * life * 0.85f;
                if (strength <= 0.01f) {
                    continue;
                }

                const float_t distanceSq = distanceSqToObserver(point.position);
                if (distanceSq > maxDistanceSq) {
                    continue;
                }

                candidates.emplace_back(Candidate {
                    .data = TerrainGrassBenderGPU { .position = point.position, .radius = point.radius, .direction = point.direction, .strength = strength },
                    .priority = strength * 1000.f - std::sqrt(distanceSq)
                });
            }

            ++pIt;
        }

        const size_t count = std::min<size_t>(candidates.size(), SR_TERRAIN_GRASS_MAX_BENDERS);
        if (count < candidates.size()) {
            std::partial_sort(candidates.begin(), candidates.begin() + static_cast<std::ptrdiff_t>(count), candidates.end(), [](const Candidate& left, const Candidate& right) {
                return left.priority > right.priority;
            });
        }

        m_benderData.clear();
        for (size_t i = 0; i < count; ++i) {
            m_benderData.emplace_back(candidates[i].data);
        }

        if (m_pBenders) {
            m_pBenders->SetBenders(m_benderData);
        }

        /// SSBO текущего кадра заливается при обновлении uniform'ов рендерера, там же выставляется количество точек
        const uint32_t count32 = static_cast<uint32_t>(count);
        if (count32 > 0 || count32 != m_lastBendersCount) {
            for (auto&& pRenderer : m_renderers) {
                pRenderer->MarkUniformsDirty();
            }
        }
        m_lastBendersCount = count32;
    }

    TerrainGrass::Result TerrainGrass::Generate(const Settings& settings, Task&& task) {
        SR_TRACY_ZONE;

        Result result;
        result.generation = task.generation;
        result.pRenderer = task.pRenderer;

        if (!task.pMesh) {
            return result;
        }

        const auto& mesh = task.pMesh->data;
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
        raw.reserve(std::min<size_t>(indices.size() / 3 * 8, static_cast<size_t>(settings.maxInstancesPerChunk) * 2));

        const bool hasBlend = hasMaterials && mesh.materials2.size() == positions.size() && mesh.blends.size() == positions.size();

        const auto isAllowed = [&](uint32_t material) {
            return std::find(settings.allowedMaterials.begin(), settings.allowedMaterials.end(), material) != settings.allowedMaterials.end();
        };

        /// Доля разрешённых материалов в вершине [0, 1] с учётом смешивания основного и второго материала
        const auto materialWeight = [&](uint32_t vertex) -> float_t {
            if (!hasMaterials) {
                return 1.f;
            }
            const float_t weight1 = isAllowed(mesh.materials[vertex]) ? 1.f : 0.f;
            if (!hasBlend) {
                return weight1;
            }
            const float_t weight2 = isAllowed(mesh.materials2[vertex]) ? 1.f : 0.f;
            const float_t blend = std::clamp(mesh.blends[vertex], 0.f, 1.f);
            return weight1 * (1.f - blend) + weight2 * blend;
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
            const uint32_t ia = indices[t + 0];
            const uint32_t ib = indices[t + 1];
            const uint32_t ic = indices[t + 2];

            if (ia >= positions.size() || ib >= positions.size() || ic >= positions.size()) SR_UNLIKELY_ATTRIBUTE {
                continue;
            }

            const float_t weightA = materialWeight(ia);
            const float_t weightB = materialWeight(ib);
            const float_t weightC = materialWeight(ic);

            /// Без плотности по весу материала точка либо годится целиком, либо нет
            const float_t weightCutoff = settings.materialWeightDensity ? settings.materialWeightThreshold : std::max(settings.materialWeightThreshold, 0.5f);
            if (std::max({ weightA, weightB, weightC }) < weightCutoff || std::max({ weightA, weightB, weightC }) <= 0.f) {
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

            /// Треугольник целиком дальше дальности травы - пропускаем. Треугольники marching cubes не больше вокселя (maxEdgeLength).
            if (center.Distance(task.observer) - mesh.maxEdgeLength - settings.generationMargin >= settings.lod.maxDistance) {
                continue;
            }
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
                const float_t rank = GrassToFloat(h3);

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

                /// вес материала в точке травинки
                float_t materialFactor = 1.f;
                if (hasMaterials) {
                    const float_t weight = weightA * w + weightB * u + weightC * v;
                    if (weight < weightCutoff || weight <= 0.f) {
                        continue;
                    }
                    materialFactor = settings.materialWeightDensity ? weight : 1.f;
                }

                /// отбор по маске плотности - на склонах и проплешинах травинки исчезают плавно, а не порогом.
                /// Для наклона берётся худшая из нормалей, чтобы трава не лезла на стены через сглаживание.
                if (GrassToFloat(h2) >= materialFactor * densityMask(worldPos, std::min(normal.y, faceNormal.y + 0.1f))) {
                    continue;
                }

                /// Дальше дальности травы (с запасом generationMargin на движение) травинка никогда не будет видна.
                /// Отбор по LOD-кривой здесь не делается: при движении наблюдателя вблизи становилось бы редко,
                /// плотность по дистанции применяет рендерер при отрисовке.
                if (worldPos.Distance(task.observer) - settings.generationMargin >= settings.lod.maxDistance) {
                    continue;
                }

                const auto cellX = std::min(cellsX - 1, static_cast<uint32_t>(std::max(0.f, (position.x - boundsMin.x) / cellSize)));
                const auto cellZ = std::min(cellsZ - 1, static_cast<uint32_t>(std::max(0.f, (position.z - boundsMin.z) / cellSize)));

                RawInstance& instance = raw.emplace_back();
                instance.instance.position = position;
                instance.instance.normal = normal;
                instance.instance.rank = rank;
                instance.instance.random = GrassToFloat(GrassHash(h3 ^ 0x2C1B3C6DU));
                instance.cell = cellZ * cellsX + cellX;
            }
        }

        if (raw.empty()) {
            return result;
        }

        /// Лимит отбрасывает самые дальние от наблюдателя травинки. Срезать по rank нельзя: плотность вблизи
        /// падала бы и скакала при каждой перегенерации (выглядит как задвоение). Порядок обхода треугольников
        /// тоже не подходит - часть чанка оставалась бы без травы.
        if (settings.maxInstancesPerChunk > 0 && raw.size() > settings.maxInstancesPerChunk) {
            const SR_MATH_NS::FVector3 observer = task.observer - mesh.origin;
            std::nth_element(raw.begin(), raw.begin() + settings.maxInstancesPerChunk, raw.end(), [&observer](const RawInstance& left, const RawInstance& right) {
                return (left.instance.position - observer).LengthSq() < (right.instance.position - observer).LengthSq();
            });
            raw.resize(settings.maxInstancesPerChunk);
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
