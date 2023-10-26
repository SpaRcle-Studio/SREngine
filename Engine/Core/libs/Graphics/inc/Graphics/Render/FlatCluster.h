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
