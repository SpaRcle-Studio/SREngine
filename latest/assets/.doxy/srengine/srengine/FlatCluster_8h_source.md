

# File FlatCluster.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**FlatCluster.h**](FlatCluster_8h.md)

[Go to the documentation of this file](FlatCluster_8h.md)


```C++
//
// Created by Monika on 25.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_FLAT_CLUSTER_H
#define SR_ENGINE_GRAPHICS_FLAT_CLUSTER_H

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


