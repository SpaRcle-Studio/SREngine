

# File FlatCluster.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**FlatCluster.h**](FlatCluster_8h.md)

[Go to the documentation of this file](FlatCluster_8h.md)


```C++
//
// Created by Monika on 25.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_FLAT_CLUSTER_H
#define SR_ENGINE_GRAPHICS_FLAT_CLUSTER_H

#include <Graphics/macros.h>

#include <Utils/Debug.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Function.h>

namespace SR_GTYPES_NS {
    class Mesh;
}

namespace SR_GRAPH_NS {
    class RenderScene;

    class FlatMeshCluster : public SR_UTILS_NS::NonCopyable {
    public:
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Iterator = std::vector<MeshPtr>::iterator;
        using ConstIterator = std::vector<MeshPtr>::const_iterator;

    public:
        FlatMeshCluster(RenderScene* pRenderScene);
        ~FlatMeshCluster() override;

    public:
        void Add(const MeshPtr& pMesh);
        void Remove(const MeshPtr& pMesh);

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);

        bool Update();

        void Sort();
        void Randomize();

        void MarkDirty();

        SR_NODISCARD Iterator begin() { return m_pool.begin(); }
        SR_NODISCARD Iterator end() { return m_pool.end(); }

        SR_NODISCARD ConstIterator begin() const { return m_pool.begin(); }
        SR_NODISCARD ConstIterator end() const { return m_pool.end(); }

        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept { return m_pool.empty(); }

    private:
        RenderScene* m_renderScene = nullptr;
        std::vector<MeshPtr> m_pool;
        uint32_t m_count = 0;
        uint32_t m_capacity = 0;

        bool m_dirty = true;

    };
}

#endif //SR_ENGINE_GRAPHICS_FLAT_CLUSTER_H
```


