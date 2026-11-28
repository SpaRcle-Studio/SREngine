//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_SCATTER_H
#define SR_ENGINE_WORLD_TERRAIN_SCATTER_H

#include <Engine/World/TerrainGrass.h>
#include <Engine/World/TerrainScatterRules.h>
#include <Engine/World/TerrainScatterRenderer.h>

#include <Utils/ECS/GameObject.h>

namespace SR_CORE_NS {
    class Terrain;
    class ITerrainChunk;

    /// Часть модели: меш файла (meshId) со своим материалом. Например, кора и листва дерева
    struct TerrainScatterMeshPart : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    public:
        /// @property @tooltip(Номер меша в файле модели (по порядку материалов))
        int32_t meshId = 0;
        /// @property
        /// @customArgs(pick: enabled, filter name: Material, relative: resources)
        /// @customArg(filter value: mat)
        SR_UTILS_NS::Path material;
    };

    /// Уровень детализации прототипа. Уровни идут по возрастанию maxDistance
    struct TerrainScatterLod : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    public:
        /// @property @tooltip(Уровень рисуется до этой дистанции от наблюдателя (метры))
        float_t maxDistance = 100.f;
        /// @property @tooltip(Доля треугольников исходного меша (meshoptimizer). 1 - без упрощения)
        float_t simplifyRatio = 1.f;
        /// @property
        bool castShadows = true;
    };

    /// Вариант объекта слоя: модель, её части и LOD
    /// @noCopyable
    class TerrainScatterPrototype : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<TerrainScatterPrototype> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainScatterPrototype>;

    public:
        TerrainScatterPrototype();

    public:
        SR_NODISCARD const SR_UTILS_NS::Path& GetMesh() const noexcept { return m_mesh; }
        SR_NODISCARD const SR_UTILS_NS::Vector<TerrainScatterMeshPart>& GetParts() const noexcept { return m_parts; }
        SR_NODISCARD const SR_UTILS_NS::Vector<TerrainScatterLod>& GetLods() const noexcept { return m_lods; }
        SR_NODISCARD float_t GetWeight() const noexcept { return m_weight; }
        SR_NODISCARD float_t GetScale() const noexcept { return m_scale; }
        SR_NODISCARD float_t GetVerticalOffset() const noexcept { return m_verticalOffset; }
        /// Дальность самого дальнего LOD
        SR_NODISCARD float_t GetMaxDistance() const noexcept;

    private:
        /// @property
        SR_UTILS_NS::StringAtom m_name;
        /// @property @tooltip(Относительная частота варианта внутри слоя)
        float_t m_weight = 1.f;
        /// @property
        /// @customArgs(pick: enabled, filter name: Meshes, relative: resources)
        /// @customArg(filter value: glb,fbx,obj,blend,dae)
        SR_UTILS_NS::Path m_mesh;
        /// @property
        SR_UTILS_NS::Vector<TerrainScatterMeshPart> m_parts;
        /// @property
        SR_UTILS_NS::Vector<TerrainScatterLod> m_lods;
        /// @property @tooltip(Множитель масштаба модели)
        float_t m_scale = 1.f;
        /// @property @tooltip(Сдвиг вдоль оси объекта (метры): поправка, если начало модели не у основания)
        float_t m_verticalOffset = 0.f;

    };

    /// Слой размещения: что ставить (прототипы), где (правила) и как часто (шаг сетки, плотность).
    /// Кандидаты - по одному на ячейку мировой 3D-сетки с шагом spacing, проецируются на поверхность
    /// вдоль "вверх" формы мира. Поэтому набор объектов не зависит от чанка и его LOD: дальний чанк даёт
    /// те же объекты, что и детальный, меняется только высота посадки.
    /// @noCopyable
    class TerrainScatterLayer : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<TerrainScatterLayer> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainScatterLayer>;

    public:
        TerrainScatterLayer();

    public:
        SR_NODISCARD bool IsEnabled() const noexcept { return m_enabled; }
        SR_NODISCARD const SR_UTILS_NS::Vector<TerrainScatterPrototype::Ptr>& GetPrototypes() const noexcept { return m_prototypes; }
        SR_NODISCARD const SR_UTILS_NS::Vector<TerrainScatterRule::Ptr>& GetRules() const noexcept { return m_rules; }
        SR_NODISCARD float_t GetSpacing() const noexcept { return m_spacing; }
        SR_NODISCARD float_t GetDensity() const noexcept { return m_density; }
        SR_NODISCARD int64_t GetSeed() const noexcept { return m_seed; }
        SR_NODISCARD uint32_t GetMaxTerrainLod() const noexcept { return m_maxTerrainLod; }
        SR_NODISCARD float_t GetAlignToNormal() const noexcept { return m_alignToNormal; }
        SR_NODISCARD bool IsRandomYaw() const noexcept { return m_randomYaw; }
        SR_NODISCARD float_t GetScaleMin() const noexcept { return m_scaleMin; }
        SR_NODISCARD float_t GetScaleMax() const noexcept { return m_scaleMax; }
        SR_NODISCARD float_t GetEmbed() const noexcept { return m_embed; }
        SR_NODISCARD float_t GetClearance() const noexcept { return m_clearance; }

    private:
        /// @property
        SR_UTILS_NS::StringAtom m_name;
        /// @property
        bool m_enabled = true;
        /// @property @group(Placement) @tooltip(Шаг сетки кандидатов в метрах: не больше одного объекта на ячейку)
        float_t m_spacing = 8.f;
        /// @property @group(Placement) @tooltip(Вероятность объекта в ячейке до правил [0, 1])
        float_t m_density = 0.5f;
        /// @property @group(Placement)
        int64_t m_seed = 1;
        /// @property @group(Placement) @tooltip(Чанки террейна дальше этого LOD слой не генерируют (мелочь не нужна на дальних чанках))
        uint32_t m_maxTerrainLod = 4;
        /// @property @group(Placement) @tooltip(Свободный радиус объекта (метры): не ставится ближе к объектам предыдущих слоёв и своего слоя)
        float_t m_clearance = 0.f;
        /// @property @group(Placement) @tooltip(Правила перемножаются. Пусто - везде)
        SR_UTILS_NS::Vector<TerrainScatterRule::Ptr> m_rules;

        /// @property @group(Transform) @tooltip(0 - объект стоит по "вверх" мира (деревья), 1 - по нормали поверхности (камни))
        float_t m_alignToNormal = 0.f;
        /// @property @group(Transform)
        bool m_randomYaw = true;
        /// @property @group(Transform)
        float_t m_scaleMin = 0.8f;
        /// @property @group(Transform)
        float_t m_scaleMax = 1.2f;
        /// @property @group(Transform) @tooltip(Насколько утопить объект в землю (метры), чтобы на склонах не висел основанием в воздухе)
        float_t m_embed = 0.2f;

        /// @property
        SR_UTILS_NS::Vector<TerrainScatterPrototype::Ptr> m_prototypes;

    };

    /// Опциональная система размещения объектов на террейне (деревья, камни, кусты...).
    /// Движок даёт механизм: детерминированные кандидаты на поверхности чанков (любого LOD), правила, генерацию
    /// в фоновом потоке, инстансинг, LOD по дистанции с упрощением мешей, отсечение по дистанции и конусу камеры.
    /// Что, где и по каким правилам ставить - решает игра: слои, прототипы и правила лежат в сцене игры.
    /// Объекты не сохраняются: каждый раз выводятся из сида и поверхности.
    /// @noCopyable @noMovable
    class TerrainScatter : public SR_HTYPES_NS::SharedPtr<TerrainScatter>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<TerrainScatter>;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainScatter>;

    public:
        TerrainScatter();
        ~TerrainScatter() override;

    public:
        SR_NODISCARD bool IsEnabled() const noexcept { return m_enabled; }

        /// Поток сцены. Меш поверхности чанка (до юбок) - для чанков любого LOD
        void OnChunkGenerated(Terrain& terrain, ITerrainChunk& chunk, const TerrainGrassSourceMesh& mesh, uint8_t lod);
        void OnChunkDeactivated(ITerrainChunk& chunk);
        /// Объекты чанка уже сгенерированы (или их нет). Пока нет - заменяемый чанк держит свои
        SR_NODISCARD bool IsChunkReady(const ITerrainChunk& chunk) const;
        /// Нужна ли поверхность чанка этого LOD хотя бы одному слою
        SR_NODISCARD bool IsLodUsed(uint8_t lod) const;

        void Update(Terrain& terrain, float_t dt);
        /// Останавливает фоновый поток и удаляет рендереры
        void Shutdown();

        /// Перегенерировать объекты всех чанков (после правки слоёв, правил, прототипов)
        /// @method @editorButton
        void Regenerate();

    private:
        struct PrototypeSnapshot {
            float_t weight = 0.f;
            float_t scale = 1.f;
            float_t verticalOffset = 0.f;
        };

        struct LayerSnapshot {
            bool enabled = false;
            float_t spacing = 8.f;
            float_t density = 0.f;
            uint32_t seed = 0;
            uint32_t maxTerrainLod = 0;
            float_t clearance = 0.f;
            float_t alignToNormal = 0.f;
            bool randomYaw = true;
            float_t scaleMin = 1.f;
            float_t scaleMax = 1.f;
            float_t embed = 0.f;
            float_t totalWeight = 0.f;
            /// Правила читаются из фонового потока. Копия списка держит их живыми, даже если слой правят в редакторе
            SR_UTILS_NS::Vector<TerrainScatterRule::Ptr> rules;
            SR_UTILS_NS::Vector<PrototypeSnapshot> prototypes;
        };

        struct Settings : public SR_HTYPES_NS::SharedPtr<Settings> {
            using Super = SR_HTYPES_NS::SharedPtr<Settings>;
            Settings() : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic) { }

            SR_UTILS_NS::Vector<LayerSnapshot> layers;
            bool isSphere = false;
            SR_MATH_NS::FVector3 sphereCenter;
            uint32_t maxInstancesPerChunk = 0;
            float_t maxClearance = 0.f;
        };
        using SettingsPtr = SR_HTYPES_NS::SharedPtr<Settings>;

        class SourceMesh : public SR_HTYPES_NS::SharedPtr<SourceMesh> {
            using Super = SR_HTYPES_NS::SharedPtr<SourceMesh>;
        public:
            explicit SourceMesh(const TerrainGrassSourceMesh& mesh)
                : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
                , data(mesh)
            { }

            TerrainGrassSourceMesh data;
        };
        using SourceMeshPtr = SR_HTYPES_NS::SharedPtr<SourceMesh>;

        /// Инстансы одного прототипа слоя в чанке (координаты террейна)
        struct Group {
            uint16_t layer = 0;
            uint16_t prototype = 0;
            SR_UTILS_NS::Vector<TerrainScatterInstanceGPU> instances;
        };

        struct Task {
            uint64_t generation = 0;
            /// Только ключ, в фоновом потоке не разыменовывается
            const ITerrainChunk* pChunk = nullptr;
            SourceMeshPtr pMesh;
            uint8_t lod = 0;
            SettingsPtr pSettings;
        };

        struct Result {
            uint64_t generation = 0;
            const ITerrainChunk* pChunk = nullptr;
            SR_UTILS_NS::Vector<Group> groups;
            SR_MATH_NS::AABB bounds;
        };

        struct ChunkEntry {
            uint64_t generation = 0;
            bool hasResult = false;
            bool isVisible = false;
            SR_UTILS_NS::Vector<Group> groups;
            SR_MATH_NS::AABB bounds;
        };

        /// Рендереры одного прототипа слоя: [LOD][часть модели]
        struct PrototypeSlot {
            float_t maxDistance = 0.f;
            SR_UTILS_NS::Vector<float_t> lodDistances;
            SR_UTILS_NS::Vector<SR_UTILS_NS::Vector<SR_HTYPES_NS::SharedPtr<TerrainScatterRenderer>>> renderers;
            /// Видимые инстансы по LOD, собираются в RebuildVisible
            SR_UTILS_NS::Vector<SR_UTILS_NS::Vector<TerrainScatterInstanceGPU>> lists;
        };

        void StartWorker();
        void StopWorker();
        bool WorkerStep();

        SR_NODISCARD SettingsPtr MakeSettings(const Terrain& terrain) const;
        SR_NODISCARD static Result Generate(const Settings& settings, const Task& task);

        SR_NODISCARD uint64_t CalculateStructureHash() const;
        void BuildSlots(Terrain& terrain);
        void DestroySlots();

        void ApplyResults();
        void UpdateVisibility();
        void RebuildVisible(const Terrain& terrain);

    private:
        /// @property
        bool m_enabled = true;
        /// @property
        SR_UTILS_NS::Vector<TerrainScatterLayer::Ptr> m_layers;

        /// @property @group(Render) @tooltip(Пересобирать видимые объекты, когда наблюдатель сместился дальше этого (метры))
        float_t m_rebuildDistance = 4.f;
        /// @property @group(Render) @tooltip(Отсекать чанки по конусу камеры (с запасом - для теней от объектов за кадром))
        bool m_frustumCulling = true;
        /// @property @group(Render) @tooltip(Запас угла отсечения в градусах)
        float_t m_cullMarginDegrees = 35.f;
        /// @property @group(Render) @tooltip(Ограничение числа объектов одного чанка)
        uint32_t m_maxInstancesPerChunk = 200000;

        /// @property @group(Stats) @readOnly @dontSave
        uint32_t m_totalInstances = 0;
        /// @property @group(Stats) @readOnly @dontSave
        uint32_t m_drawnInstances = 0;

    private:
        SR_HTYPES_NS::FlatHashMap<const ITerrainChunk*, ChunkEntry> m_entries;
        uint64_t m_generationCounter = 0;

        std::mutex m_queueMutex;
        SR_UTILS_NS::Vector<Task> m_tasks;
        SR_UTILS_NS::Vector<Result> m_results;
        SR_HTYPES_NS::Thread::Ptr m_worker = nullptr;
        std::atomic<bool> m_stopWorker = false;

        SR_UTILS_NS::GameObject::Ptr m_root;
        SR_UTILS_NS::Vector<PrototypeSlot> m_slots;
        /// Индекс первого слота слоя в m_slots
        SR_UTILS_NS::Vector<uint32_t> m_layerSlotOffsets;
        uint64_t m_structureHash = 0;

        bool m_isVisibleDirty = true;
        bool m_isRegenerateRequested = false;
        SR_MATH_NS::FVector3 m_lastObserverPosition = SR_MATH_NS::FVector3(SR_FLOAT_MAX);
        SR_MATH_NS::FVector3 m_lastObserverDirection;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_SCATTER_H
