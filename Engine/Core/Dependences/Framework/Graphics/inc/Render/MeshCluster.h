//
// Created by Monika on 31.10.2021.
//

#ifndef GAMEENGINE_MESHCLUSTER_H
#define GAMEENGINE_MESHCLUSTER_H

#include <Utils/Debug.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Map.h>

namespace SR_GRAPH_NS {
    namespace Types {
        class IndexedMesh;
        class Mesh;
        class Shader;
    }

    typedef uint32_t ClusterVBOId;

    typedef std::unordered_set<Types::IndexedMesh *> MeshGroup;
    typedef std::unordered_map<ClusterVBOId, MeshGroup> MeshGroups;
    typedef std::unordered_map<uint32_t, uint32_t> MeshGroupCounters;

    struct ShadedMeshSubCluster : public SR_UTILS_NS::NonCopyable {
        ShadedMeshSubCluster() = default;
        ~ShadedMeshSubCluster() override = default;

        ShadedMeshSubCluster(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
            m_counters = std::exchange(ref.m_counters, {});
            m_total = std::exchange(ref.m_total, {});
        }

        ShadedMeshSubCluster& operator=(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
            m_counters = std::exchange(ref.m_counters, {});
            m_total = std::exchange(ref.m_total, {});
            return *this;
        }

        MeshGroups        m_groups   = MeshGroups();
        MeshGroupCounters m_counters = MeshGroupCounters();
        uint32_t          m_total    = 0;

        bool SR_FASTCALL Add(Types::Mesh *mesh) noexcept;
        bool SR_FASTCALL Remove(Types::Mesh *mesh) noexcept;

        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;
    };

    struct MeshCluster : public SR_UTILS_NS::NonCopyable {
        MeshCluster();
        ~MeshCluster() override = default;

        ska::flat_hash_map<Types::Shader*, ShadedMeshSubCluster> m_subClusters;

        bool SR_FASTCALL Add(Types::Mesh *mesh) noexcept;
        bool SR_FASTCALL Remove(Types::Mesh *mesh) noexcept;
        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;
    };
}

#endif //GAMEENGINE_MESHCLUSTER_H
