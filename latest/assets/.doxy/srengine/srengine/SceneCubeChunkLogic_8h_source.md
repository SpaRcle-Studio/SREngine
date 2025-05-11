

# File SceneCubeChunkLogic.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneCubeChunkLogic.h**](SceneCubeChunkLogic_8h.md)

[Go to the documentation of this file](SceneCubeChunkLogic_8h.md)


```C++
//
// Created by Monika on 22.12.2022.
//

#ifndef SR_ENGINE_SCENECUBECHUNKLOGIC_H
#define SR_ENGINE_SCENECUBECHUNKLOGIC_H

#include <Utils/World/SceneLogic.h>
#include <Utils/World/TensorKey.h>

#include <Utils/ECS/SceneObject.h>

namespace SR_WORLD_NS {
    class SceneCubeChunkLogic : public SceneLogic {
        using Super = SceneLogic;
    public:
        ~SceneCubeChunkLogic() override;

    public:
        void SetScene(const ScenePtr& pScene) override;

        void InitLogic() override;
        bool Reload() override;
        void Destroy() override;
        void Update(float_t dt) override;

        void Prepare() override;

        bool SaveLogic(ISerializer& serializer, const Path& path) override;
        bool LoadLogic(IDeserializer& deserializer, const Path& path) override;

        void SetWorldOffset(const SR_WORLD_NS::Offset& offset);
        void SetObserver(const SceneObject::Ptr& target);

        bool ReloadChunks();
        void UpdateDebug();

        SR_NODISCARD const std::vector<SceneObject::Ptr>& GetGameObjectsAtChunk(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD Chunk* GetCurrentChunk() const;
        SR_NODISCARD Observer* GetObserver() const { return m_observer; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetWorldPosition(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD Region* GetRegion(const SR_MATH_NS::IVector3& region) const;
        SR_NODISCARD Region* GetOrLoadRegion(const SR_MATH_NS::IVector3& region);
        SR_NODISCARD bool IsChunkLoaded(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD bool ScopeCheckFunction(int32_t x, int32_t y, int32_t z) const;
        SR_NODISCARD Path GetRegionsPath() const;
        SR_NODISCARD std::pair<SR_MATH_NS::IVector3, SR_MATH_NS::IVector3> GetRegionAndChunk(const SR_MATH_NS::FVector3& pos) const;
        SR_NODISCARD SR_UTILS_NS::Path GetSceneDataPath(const SR_UTILS_NS::Path& path) const override;

        SR_NODISCARD StringAtom GetSceneExtension() const noexcept override { return "cubeChunk"; }
        SR_NODISCARD SceneLogicType GetType() const noexcept override { return SceneLogicType::CubeChunk; }

    private:
        SR_NODISCARD SR_MATH_NS::IVector3 CalculateCurrentChunk() const;

        bool ReloadConfig();

        void UpdateChunk(const SR_MATH_NS::IVector3& chunk, float_t dt);
        void UpdateChunks(float_t dt);
        void UpdateRegions(float_t dt);

        void CheckShift(const SR_MATH_NS::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope(float_t dt);
        void SaveRegion(const SR_UTILS_NS::Path& path, Region* pRegion, SR_HTYPES_NS::DataStorage* pContext) const;

    private:
        std::list<int64_t> m_cubesIds;
        std::list<int64_t> m_planesIds;
        bool m_debugDirty = false;

        std::atomic<bool> m_isAlive = false;

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

#endif //SR_ENGINE_SCENECUBECHUNKLOGIC_H
```


