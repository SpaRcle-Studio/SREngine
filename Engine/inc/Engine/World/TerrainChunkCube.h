//
// Created by Monika on 25.09.2026.
//

#ifndef SR_ENGINE_TERRAIN_CHUNK_CUBE_H
#define SR_ENGINE_TERRAIN_CHUNK_CUBE_H

#include <Engine/World/Terrain.h>

#include <Utils/Math/LodOctree.h>
#include <Utils/Types/FlatHashMap.h>

namespace SR_CORE_NS {
    /// Чанк - лист LOD октодерева. Позиция в единицах чанков нулевого уровня, размер = 2^lod чанков.
    class TerrainChunkCube : public ITerrainChunk {
        using Super = ITerrainChunk;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainChunkCube>;

    public:
        SR_NODISCARD const SR_MATH_NS::IVector3& GetPosition() const noexcept { return m_node.position; }
        SR_NODISCARD uint8_t GetLod() const noexcept { return m_node.level; }
        SR_NODISCARD int32_t GetLodScale() const noexcept { return m_node.GetSize(); }
        SR_NODISCARD const SR_MATH_NS::OctreeNodeId& GetNode() const noexcept { return m_node; }
        void SetNode(const SR_MATH_NS::OctreeNodeId& node) noexcept { m_node = node; }
        /// Грани, за которыми сосед другого LOD: бит axis * 2 - грань min, axis * 2 + 1 - грань max
        SR_NODISCARD uint8_t GetLodBorders() const noexcept { return m_lodBorders; }
        void SetLodBorders(uint8_t mask) noexcept { m_lodBorders = mask; }
        /// Сколько кадров заменённый чанк ещё показывается после готовности замены
        SR_NODISCARD uint32_t GetReplaceFrames() const noexcept { return m_replaceFrames; }
        void SetReplaceFrames(uint32_t frames) noexcept { m_replaceFrames = frames; }
        /// Данные чанка устарели (деформация), но перегенерировать сейчас нельзя: его место ещё закрыто заменяемым чанком
        SR_NODISCARD bool IsDirty() const noexcept { return m_isDirty; }
        void SetDirty(bool dirty) noexcept { m_isDirty = dirty; }
        /// Чанк загружен, но его объект выключен: его место ещё закрывает заменяемый чанк, а остальная замена не загружена.
        /// Показывается вместе со всей заменой, иначе старый и новый LOD долго видны одновременно и пересекаются
        SR_NODISCARD bool IsHidden() const noexcept { return m_isHidden; }
        void SetHidden(bool hidden) noexcept { m_isHidden = hidden; }

        SR_NODISCARD float_t GetDistanceTo(const ITerrainChunk& other) const override;

    private:
        SR_MATH_NS::OctreeNodeId m_node;
        uint8_t m_lodBorders = 0;
        uint32_t m_replaceFrames = 0;
        bool m_isDirty = false;
        bool m_isHidden = false;

    };

    class TerrainChunkCubeGenerator : public ITerrainChunkGenerator {
        using Super = ITerrainChunkGenerator;
        SR_CLASS()
    public:
        void Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) override;
        void LoadNextChunk(const SR_HTYPES_NS::Function<bool(ITerrainChunk&)>& loaderFn) override;
        void OnChunkLoaded(ITerrainChunk& chunk) override;

        SR_NODISCARD bool IsCollisionEnabledAt(const ITerrainChunk& chunk) const override;
        void InvalidateRegion(const SR_MATH_NS::AABB& bounds) override;
        SR_NODISCARD SR_MATH_NS::FVector3 GetVoxelSize() const override { return m_chunkScale; }

        SR_NODISCARD const SR_MATH_NS::FVector3& GetChunkSize() const noexcept { return m_chunkSize; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetChunkScale() const noexcept { return m_chunkScale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetChunkWorldPosition(const TerrainChunkCube& chunk) const;

    protected:
        void SetupChunkObject(ITerrainChunk& chunk, SR_UTILS_NS::SceneObject& object) override;

    private:
        /// false - генерацию начать нельзя (нет свободных задач)
        bool LoadNearestChunk(const SR_HTYPES_NS::Function<bool(ITerrainChunk&)>& loaderFn);
        void RebuildTree();
        void UpdatePhysics();
        void ReleaseReplacedChunks();
        void RegenerateChunk(TerrainChunkCube::Ptr& pChunk);
        SR_NODISCARD bool IsCoveredByReplaced(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD bool IntersectsReplaced(const SR_MATH_NS::OctreeNodeId& node) const;
        /// Все текущие чанки в области узла загружены
        SR_NODISCARD bool IsAreaLoaded(const SR_MATH_NS::OctreeNodeId& node) const;
        void RevealHiddenChunks();
        /// Пересобирает множества незагруженных и неготовых чанков (для IsReady/IsAreaLoaded)
        void UpdateChunkSets();
        SR_NODISCARD uint8_t GetMaxLevel() const noexcept { return static_cast<uint8_t>(std::min<uint32_t>(m_lodLevels, 12)); }
        SR_NODISCARD const SR_MATH_NS::OctreeNodeSet& GetReplacedSet() const;
        /// Чанк перестал быть нужен: видимый остаётся до загрузки замены, скрытый освобождается сразу
        void RetireChunk(const TerrainChunkCube::Ptr& pChunk);
        void ReleaseChunk(const TerrainChunkCube::Ptr& pChunk);
        SR_NODISCARD TerrainChunkCube::Ptr CreateChunk(const SR_MATH_NS::OctreeNodeId& node);

        SR_NODISCARD bool IsNodeAllowed(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD bool IsReady(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD uint8_t CalculateLodBorders(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD const SR_MATH_NS::OctreeNodeId* FindLeafAt(const SR_MATH_NS::IVector3& position) const;

    private:
        /// @property @notNull
        TerrainChunkCube::Ptr m_chunkProto;
        /// @property @range(0, 12) @tooltip(Количество уровней детализации. Корневой узел имеет размер 2^lodLevels чанков)
        uint32_t m_lodLevels = 3;
        /// @property @range(1.f, 8.f) @tooltip(Узел делится, пока наблюдатель ближе чем размер узла * splitDistance)
        float_t m_splitDistance = 1.5f;
        /// @property @range(1, 64) @tooltip(Сколько корневых узлов загружать в каждую сторону)
        SR_MATH_NS::IVector3 m_rootRadius = SR_MATH_NS::IVector3(2, 1, 2);
        /// @property @tooltip(Чанки не создаются ниже этой высоты в чанках нулевого уровня. Для планет - отключить через useHeightLimits)
        int32_t m_minHeight = -2;
        /// @property
        int32_t m_maxHeight = 3;
        /// @property
        bool m_useHeightLimits = true;
        /// @property @tooltip(Максимальная дальность прорисовки в метрах. 0 - дальность far камеры)
        float_t m_drawDistance = 0.f;
        /// @property @range(0, 512) @tooltip(Коллизия строится только для чанков нулевого LOD на этом расстоянии в чанках)
        uint32_t m_physicsDistance = 1;
        /// @property @range(1, 64) @tooltip(Максимум чанков, генерируемых за кадр)
        uint32_t m_chunksPerFrame = 1;
        /// @property @range(0.f, 100.f) @tooltip(Бюджет времени генерации чанков за кадр, мс. Генерация идёт, пока бюджет не исчерпан (но не больше chunksPerFrame и хотя бы один чанк). 0 - без бюджета, ровно chunksPerFrame)
        float_t m_generationBudgetMs = 0.f;
        /// @property @range(1, 64) @tooltip(Сколько коллизий чанков можно построить за кадр)
        uint32_t m_maxPhysicsBuildsPerFrame = 1;
        /// @property @range(0.01f, 64.f) @tooltip(Перестраивать дерево, когда наблюдатель сместился на эту долю чанка)
        float_t m_rebuildThreshold = 0.25f;
        /// @property
        SR_MATH_NS::FVector3 m_chunkSize = SR_MATH_NS::FVector3(30.0f, 30.0f, 30.0f);
        /// @property
        SR_MATH_NS::FVector3 m_chunkScale = SR_MATH_NS::FVector3(1.0f, 1.0f, 1.0f);
        /// @property @range(0, 16) @tooltip(Сколько кадров старый чанк ещё виден после загрузки замены. Новый объект попадает в рендер не в тот же кадр)
        uint32_t m_replaceDelayFrames = 2;
        /// @property @range(0, 4096) @tooltip(Сколько свободных объектов чанков держать в памяти)
        uint32_t m_maxFreeChunks = 64;

        /// @property @readOnly @dontSave
        SR_MATH_NS::IVector3 m_observerChunkPosition = SR_MATH_NS::IVector3MAX;
        /// @property @readOnly @dontSave
        uint32_t m_activeChunksCount = 0;
        /// @property @readOnly @dontSave
        uint32_t m_chunksWithObjectCount = 0;

    private:
        /// Террейн, которому принадлежит генератор (выставляется в Update). Нужен для формы мира при построении дерева
        const Terrain* m_terrain = nullptr;
        SR_MATH_NS::FVector3 m_observerNodePosition = SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX);
        SR_MATH_NS::FVector3 m_observerPosition;
        float_t m_currentDrawDistance = 0.f;
        SR_MATH_NS::LodOctree m_octree;
        bool m_physicsDirty = true;

        SR_HTYPES_NS::FlatHashMap<SR_MATH_NS::OctreeNodeId, TerrainChunkCube::Ptr> m_chunks;

        /// Запросы "есть ли среди чанков в области узла ..." раньше перебирали все чанки на каждый заменяемый/скрытый
        /// чанк (сотни x тысячи за кадр). Теперь это множества узлов, пересобираемые раз за проход
        SR_MATH_NS::OctreeNodeSet m_notLoadedSet;
        SR_MATH_NS::OctreeNodeSet m_notReadySet;
        /// Заменяемые чанки. Пересобирается лениво, когда m_replacedChunks изменился
        mutable SR_MATH_NS::OctreeNodeSet m_replacedSet;
        mutable bool m_isReplacedSetDirty = true;
        /// Заменяемые чанки, чья замена ещё не загружена целиком (RevealHiddenChunks)
        SR_MATH_NS::OctreeNodeSet m_unrevealableSet;
        /// Чанки, которые остаются видимыми, пока не загрузятся заменяющие их узлы (без дыр при смене LOD)
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_replacedChunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_freeChunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_chunksToLoad;

    };
}

#endif //SR_ENGINE_TERRAIN_CHUNK_CUBE_H
