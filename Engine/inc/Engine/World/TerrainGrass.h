//
// Created by Monika on 27.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_GRASS_H
#define SR_ENGINE_WORLD_TERRAIN_GRASS_H

#include <Engine/World/TerrainGrassRenderer.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Math/AABB.h>
#include <Utils/Types/FlatHashMap.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_CORE_NS {
    class Terrain;
    class ITerrainChunk;

    /// Входные данные для генерации травы чанка. Позиции и нормали - в мировых осях относительно
    /// позиции объекта чанка (т.е. уже с учётом масштаба чанка, но без переноса).
    struct TerrainGrassSourceMesh {
        std::vector<SR_MATH_NS::FVector3> positions;
        std::vector<SR_MATH_NS::FVector3> normals;
        std::vector<uint32_t> materials;  /// опционально, по вершине: основной материал
        std::vector<uint32_t> materials2; /// опционально, по вершине: второй материал
        std::vector<float_t> blends;      /// опционально, по вершине: доля второго материала [0, 1]
        std::vector<uint32_t> indices;
        SR_MATH_NS::FVector3 origin;     /// мировая позиция объекта чанка (для детерминированного шума)
        /// Треугольники marching cubes лежат внутри одного вокселя, поэтому ребро длиннее этого значения
        /// означает мусорную вершину (на стыках чанков). Такие треугольники пропускаются. 0 - без проверки.
        float_t maxEdgeLength = 0.f;
        /// Травинки вне этих границ (в тех же осях, что и positions) отбрасываются. Пустые границы - без проверки.
        SR_MATH_NS::AABB bounds = SR_MATH_NS::AABB(SR_MATH_NS::FVector3(0.f), SR_MATH_NS::FVector3(0.f));
    };

    /// Опциональная система травы террейна.
    /// Генерация: травинки рассыпаются прямо по треугольникам marching cubes меша (работает на склонах,
    /// нависаниях и в пещерах), число травинок на треугольник = площадь * плотность * маска.
    /// Маска = плавный фильтр по наклону * многослойный шум (поляны/проплешины) * фильтр по материалу.
    /// Выборка стратифицированная через хеш мировой позиции, поэтому результат детерминирован и не зависит от чанка.
    /// Генерация идёт в фоновом потоке, рендер - см. TerrainGrassRenderer.

    /// @noCopyable @noMovable
    class TerrainGrass : public SR_HTYPES_NS::SharedPtr<TerrainGrass>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<TerrainGrass>;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainGrass>;

    public:
        TerrainGrass();
        ~TerrainGrass() override;

    public:
        SR_NODISCARD bool IsEnabled() const noexcept { return m_enabled; }

        /// Поток сцены. Забирает копию меша, генерация пойдёт в фоне.
        void OnChunkGenerated(Terrain& terrain, ITerrainChunk& chunk, TerrainGrassSourceMesh&& mesh);
        void OnChunkDeactivated(ITerrainChunk& chunk);
        /// Первичная генерация травы чанка завершена (результат применён) или травы у чанка нет
        SR_NODISCARD bool IsChunkReady(const ITerrainChunk& chunk) const;

        void Update(Terrain& terrain, float_t dt);
        /// Останавливает фоновый поток и снимает траву со всех чанков.
        void Shutdown();

        SR_NODISCARD TerrainGrassLodParams GetLodParams() const;

    private:
        /// Исходный меш чанка, общий для задачи генерации и для последующих перегенераций
        class SourceMesh : public SR_HTYPES_NS::SharedPtr<SourceMesh> {
            using Super = SR_HTYPES_NS::SharedPtr<SourceMesh>;
        public:
            explicit SourceMesh(TerrainGrassSourceMesh&& mesh)
                : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
                , data(std::move(mesh))
            { }

            TerrainGrassSourceMesh data;
        };
        using SourceMeshPtr = SR_HTYPES_NS::SharedPtr<SourceMesh>;

        struct Task {
            uint64_t generation = 0;
            SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer> pRenderer;
            SourceMeshPtr pMesh;
            /// Позиция наблюдателя, от которой отбираются травинки по LOD (дальние не генерируются)
            SR_MATH_NS::FVector3 observer;
        };

        struct Source {
            SourceMeshPtr pMesh;
            SR_MATH_NS::FVector3 observer; /// позиция наблюдателя при последней генерации
            /// Задача уже в очереди или в работе. Новая не ставится, иначе при движении результат постоянно
            /// устаревает (поколение растёт) и чанк так и не получает траву
            bool isPending = false;
            /// Результат хотя бы одной генерации уже применён к рендереру
            bool isApplied = false;
        };

        struct Result {
            uint64_t generation = 0;
            SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer> pRenderer;
            SR_UTILS_NS::Vector<TerrainGrassInstance> instances;
            SR_UTILS_NS::Vector<TerrainGrassCell> cells;
        };

        struct Settings {
            float_t density = 0.f;
            float_t cellSize = 0.f;
            float_t slopeMin = 0.f;
            float_t slopeMax = 0.f;
            float_t noiseScale = 0.f;
            float_t noiseThreshold = 0.f;
            float_t noiseContrast = 0.f;
            float_t detailNoiseScale = 0.f;
            uint32_t maxInstancesPerChunk = 0;
            int64_t seed = 0;
            std::vector<uint32_t> allowedMaterials;
            bool materialWeightDensity = true;
            float_t materialWeightThreshold = 0.f;
            TerrainGrassLodParams lod;
            float_t generationMargin = 0.f;
        };

        void StartWorker();
        void StopWorker();
        /// Тело потока движка: одна задача за вызов. false - поток завершается.
        /// Без SR_THREADS_ALLOWED (веб) вызывается из главного цикла через Thread::Factory::ManuallyUpdateThreads
        bool WorkerStep();

        SR_NODISCARD Settings MakeSettings() const;
        SR_NODISCARD static Result Generate(const Settings& settings, Task&& task);

        void UpdateBenders(float_t dt);
        void QueueGeneration(const SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer>& pRenderer, Source& source);
        void UpdateRegeneration(const SR_MATH_NS::FVector3& observer);

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer> GetOrCreateRenderer(ITerrainChunk& chunk);
        SR_NODISCARD uint64_t NextGeneration(TerrainGrassRenderer* pRenderer);

    private:
        /// @property
        bool m_enabled = true;
        /// @property
        /// @customArgs(pick: enabled, filter name: Material, relative: resources)
        /// @customArg(filter value: mat)
        SR_UTILS_NS::Path m_material = "Engine/Materials/terrain-grass.mat";

        /// @property @group(Placement) @tooltip(Травинок на квадратный метр горизонтальной поверхности)
        float_t m_density = 60.f;
        /// @property @group(Placement) @tooltip(Размер ячейки LOD/отсечения в метрах)
        float_t m_cellSize = 8.f;
        /// @property @group(Placement) @tooltip(Ниже этого значения dot(normal, up) травы нет)
        float_t m_slopeMin = 0.55f;
        /// @property @group(Placement) @tooltip(Выше этого значения dot(normal, up) полная плотность)
        float_t m_slopeMax = 0.8f;
        /// @property @group(Placement)
        float_t m_noiseScale = 0.02f;
        /// @property @group(Placement) @tooltip(Порог шума: чем выше, тем больше проплешин)
        float_t m_noiseThreshold = 0.3f;
        /// @property @group(Placement)
        float_t m_noiseContrast = 3.f;
        /// @property @group(Placement)
        float_t m_detailNoiseScale = 0.15f;
        /// @property @group(Placement)
        uint32_t m_maxInstancesPerChunk = 2000000;
        /// @property @group(Placement) @tooltip(Запас дистанции в метрах: травинки генерируются с плотностью LOD на (дистанция - запас). Больше - реже перегенерация, больше памяти)
        float_t m_generationMargin = 24.f;
        /// @property @group(Placement) @tooltip(Перегенерировать траву чанка, когда наблюдатель сместился от точки генерации дальше этого (метры). Должно быть меньше generationMargin)
        float_t m_regenerateDistance = 16.f;
        /// @property @group(Placement)
        int64_t m_seed = 1337;
        /// @property @group(Placement) @tooltip(Пустой список - трава на любом материале)
        SR_UTILS_NS::Vector<uint32_t> m_allowedMaterials = { 0 };
        /// @property @group(Placement) @tooltip(Плотность травы пропорциональна доле разрешённых материалов в точке (с учётом смешивания))
        bool m_materialWeightDensity = true;
        /// @property @group(Placement) @tooltip(Если доля разрешённых материалов меньше этого значения - травы нет)
        float_t m_materialWeightThreshold = 0.1f;

        /// @property @group(LOD)
        float_t m_fullDensityDistance = 12.f;
        /// @property @group(LOD)
        float_t m_maxDistance = 140.f;
        /// @property @group(LOD)
        float_t m_falloff = 1.6f;
        /// @property @group(LOD)
        float_t m_minKeep = 0.04f;
        /// @property @group(LOD)
        float_t m_segmentsLodDistance = 25.f;
        /// @property @group(LOD) @range(1, 7)
        uint32_t m_segments = 5;
        /// @property @group(LOD) @range(1, 7)
        uint32_t m_lowSegments = 2;

        /// @property @group(Render) @tooltip(Работает только если каскады теней рисуются без инстансинга)
        bool m_castShadows = false;
        /// @property @group(Render) @tooltip(Отсекать ячейки по фрустуму камеры. Пересобирает командные буферы при повороте камеры)
        bool m_frustumCulling = true;
        /// @property @group(Render) @tooltip(Запас угла отсечения в градусах. Больше - реже пересборка командных буферов при повороте камеры)
        float_t m_cullMarginDegrees = 20.f;

        /// @property @group(Bending) @tooltip(Шаг между точками следа в метрах)
        float_t m_trailSpacing = 0.3f;
        /// @property @group(Bending) @tooltip(Максимальная дистанция от камеры, на которой учитываются приминающие объекты)
        float_t m_bendMaxDistance = 40.f;

        /// @property @group(Stats) @readOnly @dontSave
        uint32_t m_totalInstances = 0;
        /// @property @group(Stats) @readOnly @dontSave
        uint32_t m_drawnInstances = 0;

    private:
        std::vector<SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer>> m_renderers;
        /// Отключённые рендереры, у которых ещё живы старые буферы инстансов (ждут смены кадров свапчейна)
        std::vector<SR_HTYPES_NS::SharedPtr<TerrainGrassRenderer>> m_retiredRenderers;
        std::unordered_map<TerrainGrassRenderer*, uint64_t> m_generations;
        /// Исходный меш чанка - для перегенерации при смещении наблюдателя
        std::unordered_map<TerrainGrassRenderer*, Source> m_sources;
        uint64_t m_generationCounter = 0;

        std::mutex m_queueMutex;
        std::deque<Task> m_tasks;
        std::vector<Result> m_results;
        SR_HTYPES_NS::Thread::Ptr m_worker = nullptr;
        std::atomic<bool> m_stopWorker = false;

        SR_MATH_NS::FVector3 m_lastObserverPosition = SR_MATH_NS::FVector3(SR_FLOAT_MAX);
        SR_MATH_NS::FVector3 m_lastObserverDirection;
        TerrainGrassLodParams m_lastLodParams;
        bool m_lastCanCull = false;
        bool m_forceLodUpdate = true;

        struct TrailPoint {
            SR_MATH_NS::FVector3 position;
            SR_MATH_NS::FVector3 direction;
            float_t radius = 0.f;
            float_t strength = 0.f;
            float_t age = 0.f;
        };

        /// След одного объекта - полилиния от старых точек к новым. Живёт и после отключения объекта, пока не угаснет.
        struct Trail {
            SR_UTILS_NS::Vector<TrailPoint> points;
            float_t duration = 1.f;
            float_t maxLength = 0.f;
            bool isOwnerAlive = false;
        };

        SR_HTYPES_NS::FlatHashMap<const void*, Trail> m_trails;
        TerrainGrassBenders::Ptr m_pBenders;
        SR_UTILS_NS::Vector<TerrainGrassBenderGPU> m_benderData;
        uint32_t m_lastBendersCount = 0;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_GRASS_H
