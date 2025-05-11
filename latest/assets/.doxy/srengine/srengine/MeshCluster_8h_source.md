

# File MeshCluster.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**MeshCluster.h**](MeshCluster_8h.md)

[Go to the documentation of this file](MeshCluster_8h.md)


```C++
//
// Created by Monika on 31.10.2021.
//

#ifndef SR_ENGINE_MESHCLUSTER_H
#define SR_ENGINE_MESHCLUSTER_H

#include <Graphics/macros.h>

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

namespace SR_UTILS_NS {
    class IResource;
}

namespace SR_GRAPH_NS {
    SR_ENUM_NS_STRUCT_T(MeshClusterType, uint64_t,
        None        = 1 << 0,
        Opaque      = 1 << 1,
        Transparent = 1 << 2,
        Debug       = 1 << 3,
        Flat        = 1 << 4
    );

    typedef uint32_t ClusterVBOId;

    typedef std::unordered_set<SR_GTYPES_NS::Mesh*> MeshGroup;
    typedef std::unordered_map<ClusterVBOId, MeshGroup> MeshGroups;

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
            m_groups = SR_UTILS_NS::Exchange(ref.m_groups, {});
            m_shader = SR_UTILS_NS::Exchange(ref.m_shader, {});
        }

        ShadedMeshSubCluster& operator=(ShadedMeshSubCluster&& ref) noexcept {
            m_groups = SR_UTILS_NS::Exchange(ref.m_groups, {});
            m_shader = SR_UTILS_NS::Exchange(ref.m_shader, {});
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

        //bool SR_FASTCALL Add(SR_GTYPES_NS::Mesh *mesh) noexcept;
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
        ~MeshCluster() override {
            SRAssert(m_subClusters.empty());
        }

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
        virtual bool SR_FASTCALL ChangeCluster(MeshPtr pMesh) { return false; }

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

#endif //SR_ENGINE_MESHCLUSTER_H
```


