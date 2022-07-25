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

    class ShadedMeshSubCluster : public SR_UTILS_NS::NonCopyable {
    public:
        using Iterator = MeshGroups::iterator;
        using ConstIterator = MeshGroups::const_iterator;

    public:
        ShadedMeshSubCluster() = default;
        ~ShadedMeshSubCluster() override = default;

        ShadedMeshSubCluster(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
        }

        ShadedMeshSubCluster& operator=(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
            return *this;
        }

    public:
        Iterator erase(const Iterator& iterator) {
            return m_groups.erase(iterator);
        }

        SR_NODISCARD Iterator begin() { return m_groups.begin(); }
        SR_NODISCARD Iterator end() { return m_groups.end(); }

        SR_NODISCARD ConstIterator begin() const { return m_groups.begin(); }
        SR_NODISCARD ConstIterator end() const { return m_groups.end(); }

        bool SR_FASTCALL Add(Types::Mesh *mesh) noexcept;
        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;

    private:
        MeshGroups m_groups = MeshGroups();

    };

    class MeshCluster : public SR_UTILS_NS::NonCopyable {
    public:
        using Iterator = ska::flat_hash_map<Types::Shader*, ShadedMeshSubCluster>::iterator;
        using ConstIterator = ska::flat_hash_map<Types::Shader*, ShadedMeshSubCluster>::const_iterator;
        using MeshPtr = SR_GTYPES_NS::Mesh*;

    public:
        MeshCluster();
        ~MeshCluster() override = default;

    public:
        Iterator erase(const Iterator& iterator) {
            return m_subClusters.erase(iterator);
        }

        SR_NODISCARD Iterator begin() { return m_subClusters.begin(); }
        SR_NODISCARD Iterator end() { return m_subClusters.end(); }

        SR_NODISCARD ConstIterator begin() const { return m_subClusters.begin(); }
        SR_NODISCARD ConstIterator end() const { return m_subClusters.end(); }

        bool SR_FASTCALL Add(Types::Mesh *mesh) noexcept;
        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;

        void Update();

    protected:
        virtual bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) = 0;

    protected:
        ska::flat_hash_map<Types::Shader*, ShadedMeshSubCluster> m_subClusters;

    };

    class OpaqueMeshCluster;
    class TransparentMeshCluster;

    class OpaqueMeshCluster : public MeshCluster {
    public:
        OpaqueMeshCluster(TransparentMeshCluster* pTransparentCluster)
            : m_transparent(pTransparentCluster)
        { }

        ~OpaqueMeshCluster() override = default;

    private:
        bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) final;

    private:
        TransparentMeshCluster* m_transparent;

    };

    class TransparentMeshCluster : public MeshCluster {
    public:
        TransparentMeshCluster(OpaqueMeshCluster* pOpaqueCluster)
            : m_opaque(pOpaqueCluster)
        { }

        ~TransparentMeshCluster() override = default;

    private:
        bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) final;

    private:
        OpaqueMeshCluster* m_opaque;

    };
}

#endif //GAMEENGINE_MESHCLUSTER_H
