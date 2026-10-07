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

        SR_NODISCARD float_t GetDistanceTo(const ITerrainChunk& other) const override;

    private:
        SR_MATH_NS::OctreeNodeId m_node;
        uint8_t m_lodBorders = 0;
        uint32_t m_replaceFrames = 0;

    };

    class TerrainChunkCubeGenerator : public ITerrainChunkGenerator {
        using Super = ITerrainChunkGenerator;
        SR_CLASS()
    public:
        void Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) override;
        void LoadNextChunk(const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& loaderFn) override;

        SR_NODISCARD bool IsCollisionEnabledAt(const ITerrainChunk& chunk) const override;

        SR_NODISCARD const SR_MATH_NS::FVector3& GetChunkSize() const noexcept { return m_chunkSize; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetChunkScale() const noexcept { return m_chunkScale; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetChunkWorldPosition(const TerrainChunkCube& chunk) const;

    protected:
        void SetupChunkObject(ITerrainChunk& chunk, SR_UTILS_NS::SceneObject& object) override;

    private:
        void LoadNearestChunk(const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& loaderFn);
        void RebuildTree();
        void UpdatePhysics();
        void ReleaseReplacedChunks();
        void ReleaseChunk(const TerrainChunkCube::Ptr& pChunk);
        SR_NODISCARD TerrainChunkCube::Ptr CreateChunk(const SR_MATH_NS::OctreeNodeId& node);

        SR_NODISCARD bool IsNodeAllowed(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD bool IsReady(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD uint8_t CalculateLodBorders(const SR_MATH_NS::OctreeNodeId& node) const;
        SR_NODISCARD const SR_MATH_NS::OctreeNodeId* FindLeafAt(const SR_MATH_NS::IVector3& position) const;

    private:
        /// @property @notNull
        TerrainChunkCube::Ptr m_chunkProto;
        /// @property @range(0, 8) @tooltip(Количество уровней детализации. Корневой узел имеет размер 2^lodLevels чанков)
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
        /// @property @range(1, 64) @tooltip(Сколько чанков генерировать за кадр)
        uint32_t m_chunksPerFrame = 1;
        /// @property @range(1, 64) @tooltip(Сколько коллизий чанков можно построить за кадр)
        uint32_t m_maxPhysicsBuildsPerFrame = 1;
        /// @property @range(0.01f, 64.f) @tooltip(Перестраивать дерево, когда наблюдатель сместился на эту долю чанка)
        float_t m_rebuildThreshold = 0.25f;
        /// @property
        SR_MATH_NS::FVector3 m_chunkSize = SR_MATH_NS::FVector3(124.0f, 124.0f, 124.0f);
        /// @property
        SR_MATH_NS::FVector3 m_chunkScale = SR_MATH_NS::FVector3(2.0f, 2.0f, 2.0f);
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
        SR_MATH_NS::FVector3 m_observerNodePosition = SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX);
        SR_MATH_NS::FVector3 m_observerPosition;
        float_t m_currentDrawDistance = 0.f;
        SR_MATH_NS::LodOctree m_octree;
        bool m_physicsDirty = true;

        SR_HTYPES_NS::FlatHashMap<SR_MATH_NS::OctreeNodeId, TerrainChunkCube::Ptr> m_chunks;
        /// Чанки, которые остаются видимыми, пока не загрузятся заменяющие их узлы (без дыр при смене LOD)
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_replacedChunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_freeChunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_chunksToLoad;

    };
}

#endif //SR_ENGINE_TERRAIN_CHUNK_CUBE_H
