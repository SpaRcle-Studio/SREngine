//
// Created by Monika on 25.09.2023.
//

#include <Graphics/Render/FlatCluster.h>

namespace SR_GRAPH_NS {
    int32_t FlatMeshClusterComparator(const void* one, const void* two)
    {
        auto&& a = *((FlatMeshCluster::MeshPtr*)one);
        auto&& b = *((FlatMeshCluster::MeshPtr*)two);

        if (a == b) {
            return 0;
        }

        if (a && !b) {
            return 1;
        }

        if (!a && b) {
            return -1;
        }

        /// --------------

        const int64_t aP = a->GetSortingPriority();
        const int64_t bP = b->GetSortingPriority();

        if (aP < bP) {
            return -1;
        }

        if (aP == bP) {
            return 0;
        }

        return 1;
    }

    FlatMeshCluster::FlatMeshCluster() {
        m_pool.reserve(1024);
    }

    FlatMeshCluster::~FlatMeshCluster() {
        SRAssert(m_count == 0);
    }

    void FlatMeshCluster::Add(const FlatMeshCluster::MeshPtr& pMesh) {
        if (m_capacity > m_count) {
            /// пробуем получить оптимальное начало для поиска свободной ячейки памяти
            /// vector: 0 0 0 0 1 1 1 0 1 => 0 0 0 1 1 1 1 0 1
            /// 4 - count
            /// 9 - capacity
            /// 4 = (9 - 4) - 1
            const auto start = static_cast<int32_t>((m_capacity - m_count) - 1);

            for (int32_t i = start; i >= 0; --i) {
                if (m_pool[i]) {
                    continue;
                }

                ++m_count;
                m_pool[i] = pMesh;
                m_dirty = true;
                return;
            }
        }

        ++m_count;
        ++m_capacity;
        m_pool.emplace_back(pMesh);
        m_dirty = true;
    }

    void FlatMeshCluster::Remove(const FlatMeshCluster::MeshPtr& pMesh) {
        for (auto&& pMeshIteration : m_pool) {
            if (pMeshIteration == pMesh) {
                pMeshIteration = nullptr;
                SRAssert(m_count > 0);
                --m_count;
                return;
            }
        }
    }

    void FlatMeshCluster::Sort() {
        if (!m_dirty) {
            return;
        }

        SR_TRACY_ZONE;

        std::qsort(m_pool.data(), m_pool.size(), sizeof(void*), FlatMeshClusterComparator);

        m_dirty = false;
    }

    void FlatMeshCluster::Randomize() {
        SR_UTILS_NS::Random::Instance().Shuffle(m_pool);
        m_dirty = true;
    }

    void FlatMeshCluster::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        for (auto&& pMesh : m_pool) {
            if (!pMesh) {
                continue;
            }
            pMesh->OnResourceReloaded(pResource);
        }
    }

    bool FlatMeshCluster::Update() {
        bool changed = false;

        for (auto&& pMesh : m_pool) {
            if (!pMesh) {
                continue;
            }

            if (pMesh->IsMeshDestroyed()) {
                auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();
                SR_MAYBE_UNUSED SR_HTYPES_NS::SingletonRecursiveLockGuard lock(&resourceManager);

                if (pMesh->IsCalculated()) {
                    pMesh->FreeVideoMemory();
                    pMesh->DeInitGraphicsResource();
                }

                pMesh->FreeMesh();
                pMesh = nullptr;
                changed = true;
            }
        }

        return changed;
    }
}