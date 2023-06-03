//
// Created by Monika on 31.10.2021.
//

#ifndef GAMEENGINE_MESHCLUSTER_H
#define GAMEENGINE_MESHCLUSTER_H

#include <Utils/Debug.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Function.h>

namespace SR_SRSL_NS {
    enum class ShaderType;
}

namespace SR_GTYPES_NS {
    class IndexedMesh;
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    typedef uint32_t ClusterVBOId;

    typedef std::unordered_set<SR_GTYPES_NS::Mesh*> MeshGroup;
    typedef std::unordered_map<ClusterVBOId, MeshGroup> MeshGroups;
    typedef std::unordered_map<uint32_t, uint32_t> MeshGroupCounters;

    class ShadedMeshSubCluster : public SR_UTILS_NS::NonCopyable {
    public:
        using Iterator = MeshGroups::iterator;
        using ConstIterator = MeshGroups::const_iterator;
        using Super = SR_UTILS_NS::NonCopyable;

    public:
        ShadedMeshSubCluster() = default;
        explicit ShadedMeshSubCluster(SR_GTYPES_NS::Shader* pShader);
        ~ShadedMeshSubCluster() override = default;

        ShadedMeshSubCluster(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
            m_shader = std::exchange(ref.m_shader, {});
        }

        ShadedMeshSubCluster& operator=(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = std::exchange(ref.m_groups, {});
            m_shader = std::exchange(ref.m_shader, {});
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

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);

        bool SR_FASTCALL Add(SR_GTYPES_NS::Mesh *mesh) noexcept;
        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;

        SR_NODISCARD SR_SRSL_NS::ShaderType GetShaderType() const noexcept;

    private:
        MeshGroups m_groups;
        SR_GTYPES_NS::Shader* m_shader = nullptr;

    };

    class MeshCluster : public SR_UTILS_NS::NonCopyable {
    public:
        using Iterator = ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster>::iterator;
        using ConstIterator = ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster>::const_iterator;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using ClusterCallback = SR_HTYPES_NS::Function<void(MeshPtr)>;

    public:
        MeshCluster();
        ~MeshCluster() override = default;

    public:
        Iterator erase(const Iterator& iterator) {
            return m_subClusters.erase(iterator);
        }

        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);

        SR_NODISCARD Iterator begin() { return m_subClusters.begin(); }
        SR_NODISCARD Iterator end() { return m_subClusters.end(); }

        SR_NODISCARD ConstIterator begin() const { return m_subClusters.begin(); }
        SR_NODISCARD ConstIterator end() const { return m_subClusters.end(); }

        bool SR_FASTCALL Add(SR_GTYPES_NS::Mesh *mesh) noexcept;
        SR_NODISCARD bool SR_FASTCALL Empty() const noexcept;

        bool Update();

    protected:
        virtual bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) = 0;

    protected:
        ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster> m_subClusters;

    };

    class OpaqueMeshCluster;
    class TransparentMeshCluster;

    class OpaqueMeshCluster : public MeshCluster {
    public:
        explicit OpaqueMeshCluster(TransparentMeshCluster* pTransparentCluster)
            : m_transparent(pTransparentCluster)
        { }

        ~OpaqueMeshCluster() override = default;

    private:
        bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) final;

    private:
        TransparentMeshCluster* m_transparent;

    };

    class DebugMeshCluster : public MeshCluster {
    public:
        ~DebugMeshCluster() override = default;

    private:
        bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) final { return false; }

    };

    class TransparentMeshCluster : public MeshCluster {
    public:
        explicit TransparentMeshCluster(OpaqueMeshCluster* pOpaqueCluster)
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
