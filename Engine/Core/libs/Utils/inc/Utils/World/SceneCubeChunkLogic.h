//
// Created by Monika on 22.12.2022.
//

#ifndef SRENGINE_SCENECUBECHUNKLOGIC_H
#define SRENGINE_SCENECUBECHUNKLOGIC_H

#include <Utils/World/SceneLogic.h>
#include <Utils/World/TensorKey.h>

namespace SR_WORLD_NS {
    class SceneCubeChunkLogic : public SceneLogic {
        using Super = SceneLogic;
    public:
        explicit SceneCubeChunkLogic(const ScenePtr& scene);
        ~SceneCubeChunkLogic() override;

    public:
        bool Reload() override;
        void Destroy() override;
        void Update(float_t dt) override;

        bool Save(const Path& path) override;
        bool Load(const Path& path) override;

        void SetWorldOffset(const SR_WORLD_NS::Offset& offset);
        void SetObserver(const GameObjectPtr& target);

        bool ReloadChunks();

        SR_NODISCARD const GameObjects& GetGameObjectsAtChunk(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD Chunk* GetCurrentChunk() const;
        SR_NODISCARD Observer* GetObserver() const { return m_observer; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetWorldPosition(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk);
        SR_NODISCARD Region* GetRegion(const SR_MATH_NS::IVector3& region);
        SR_NODISCARD bool IsChunkLoaded(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD bool ScopeCheckFunction(int32_t x, int32_t y, int32_t z) const;
        SR_NODISCARD Path GetRegionsPath() const;

    private:
        SR_NODISCARD SR_MATH_NS::IVector3 CalculateCurrentChunk() const;

        bool ReloadConfig();

        void CheckShift(const SR_MATH_NS::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope(float_t dt);
        void SaveRegion(Region* pRegion, SR_HTYPES_NS::DataStorage* pContext) const;

    private:
        World::Tensor m_tensor;

        Regions m_regions;
        SR_MATH_NS::IVector2 m_chunkSize;
        uint32_t m_regionWidth = 0;

        Observer* m_observer = nullptr;
        Chunk* m_currentChunk = nullptr;

        bool m_updateContainer = false;
        bool m_shiftEnabled = false;
        bool m_scopeEnabled = false;

    };
}

#endif //SRENGINE_SCENECUBECHUNKLOGIC_H
