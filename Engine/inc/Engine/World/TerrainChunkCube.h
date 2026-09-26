//
// Created by Monika on 25.09.2026.
//

#ifndef SR_ENGINE_TERRAIN_CHUNK_CUBE_H
#define SR_ENGINE_TERRAIN_CHUNK_CUBE_H

#include <Engine/World/Terrain.h>

namespace SR_CORE_NS {
    class TerrainChunkCube : public ITerrainChunk {
        using Super = ITerrainChunk;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainChunkCube>;

    public:
        SR_NODISCARD const SR_MATH_NS::IVector3& GetPosition() const noexcept;
        void SetPosition(const SR_MATH_NS::IVector3& position) noexcept { m_position = position; }

    private:
        SR_MATH_NS::IVector3 m_position;

    };

    struct TerrainChunkCubeLessPredicate {
        SR_NODISCARD bool operator()(const TerrainChunkCube::Ptr& pLeft, const TerrainChunkCube::Ptr& pRight) const noexcept;
    };

    class TerrainChunkCubeGenerator : public ITerrainChunkGenerator {
        using Super = ITerrainChunkGenerator;
        SR_CLASS()
    public:
        void Update(Terrain& terrain, float_t dt) override;
        void LoadNextChunk(SR_HTYPES_NS::Function<void(ITerrainChunk&)> loaderFn);

    private:
        /// @property @notNull
        TerrainChunkCube::Ptr m_chunkProto;
        /// @property @range(1, 512)
        SR_MATH_NS::IVector3 m_minLoadDistance = SR_MATH_NS::IVector3(16, 1, 16);
        /// @property @range(1, 512)
        SR_MATH_NS::IVector3 m_maxLoadDistance = SR_MATH_NS::IVector3(16, 1, 16);
        /// @property @range(1, 512)
        SR_MATH_NS::IVector3 m_unloadDistance = SR_MATH_NS::IVector3(2, 1, 2);
        /// @property
        SR_MATH_NS::FVector3 m_chunkSize = SR_MATH_NS::FVector3(32.0f, 64.0f, 32.0f);
        /// @property
        SR_MATH_NS::FVector3 m_chunkScale = SR_MATH_NS::FVector3(1.0f, 1.0f, 1.0f);

        /// @property @readOnly @dontSave
        SR_MATH_NS::IVector3 m_observerChunkPosition = SR_MATH_NS::IVector3MAX;

    private:
        SR_HTYPES_NS::SortedVector<TerrainChunkCube::Ptr, TerrainChunkCubeLessPredicate> m_chunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_freeChunks;
        SR_UTILS_NS::Vector<TerrainChunkCube::Ptr> m_chunksToLoad;

    };
}

#endif //SR_ENGINE_TERRAIN_CHUNK_CUBE_H
