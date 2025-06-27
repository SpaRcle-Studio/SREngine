

# File IndexedMesh.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**IndexedMesh.h**](IndexedMesh_8h.md)

[Go to the documentation of this file](IndexedMesh_8h.md)


```C++
//
// Created by Monika on 30.10.2021.
//

#ifndef SR_ENGINE_GRAPHICS_INDEXEDMESH_H
#define SR_ENGINE_GRAPHICS_INDEXEDMESH_H

#include <Graphics/Memory/MeshManager.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Types/FastMemoryArray.h>

namespace SR_GTYPES_NS {
    class IndexedMesh : public Mesh {
        SR_CLASS()
    protected:
        IndexedMesh() = default;

    public:
        ~IndexedMesh() override;

    public:
        SR_NODISCARD int32_t GetIBO() override;
        SR_NODISCARD int32_t GetVBO() override;

        SR_NODISCARD uint32_t GetVerticesCount() const override { return m_countVertices; }
        SR_NODISCARD uint32_t GetIndicesCount() const override { return m_countIndices; }

        SR_NODISCARD virtual const SR_HTYPES_NS::FastMemoryArray<uint32_t>& GetIndices() const {
            static SR_HTYPES_NS::FastMemoryArray<uint32_t> empty;
            return empty;
        }

        SR_NODISCARD bool IsSupportVBO() const override { return true; }

        bool Calculate() override;

        bool CalculateIBO();

        void FreeVideoMemory() override;

        template<Vertices::VertexType type, typename Vertex> bool CalculateVBO(const SR_HTYPES_NS::FastMemoryArray<Vertex>& vertices);
        template<Vertices::VertexType type, typename Vertex> bool CalculateVBO(const SR_HTYPES_NS::Function<SR_HTYPES_NS::FastMemoryArray<Vertex>()>& getter);

        bool FreeVBO();
        bool FreeIBO();

    protected:
        int32_t m_IBO = SR_ID_INVALID;
        int32_t m_VBO = SR_ID_INVALID;
        uint32_t m_countIndices = 0;
        uint32_t m_countVertices = 0;

    };


    template<Vertices::VertexType type, typename Vertex> bool IndexedMesh::CalculateVBO(const SR_HTYPES_NS::Function<SR_HTYPES_NS::FastMemoryArray<Vertex>()>& getter) {
        SR_TRACY_ZONE;

        SRAssert(m_pipeline);
        SRAssert(m_VBO == SR_ID_INVALID);

        using namespace Memory;

        if (!IsUniqueMesh()) {
            m_VBO = MeshManager::Instance().CopyIfExists<type, MeshMemoryType::VBO>(GetMeshIdentifier());
        }

        if (m_VBO == SR_ID_INVALID) {
            auto&& vertices = getter();
            return CalculateVBO<type>(vertices);
        }

        if (!IsUniqueMesh()) {
            m_countVertices = MeshManager::Instance().Size<type, MeshMemoryType::VBO>(
                GetMeshIdentifier()
            );
        }

        return true;
    }

    template<Vertices::VertexType type, typename Vertex> bool IndexedMesh::CalculateVBO(const SR_HTYPES_NS::FastMemoryArray<Vertex>& vertices) {
        SR_TRACY_ZONE;

        SRAssert(m_pipeline);
        SRAssert(m_VBO == SR_ID_INVALID);

        using namespace Memory;

        if (!IsUniqueMesh()) {
            m_VBO = MeshManager::Instance().CopyIfExists<type, MeshMemoryType::VBO>(GetMeshIdentifier());
        }

        if (m_VBO == SR_ID_INVALID) {
            if ((m_countVertices = vertices.size()) == 0) {
                SR_ERROR("IndexedMesh::CalculateVBO() : invalid vertices! \n\tIdentifier: " + GetMeshIdentifier());
                return false;
            }

            if (m_VBO = m_pipeline->AllocateVBO(static_cast<const void*>(vertices.data()), type, m_countVertices); m_VBO == SR_ID_INVALID) {
                SR_ERROR("IndexedMesh::CalculateVBO() : failed calculate VBO \"" + GetMeshIdentifier() + "\" mesh!");
                m_hasErrors = true;
                return false;
            }
            else if (IsUniqueMesh()) {
                return true;
            }

            return MeshManager::Instance().Register<type, MeshMemoryType::VBO>(
                GetMeshIdentifier(),
                m_countVertices,
                m_VBO
            );
        }

        if (!IsUniqueMesh()) {
            m_countVertices = MeshManager::Instance().Size<type, MeshMemoryType::VBO>(
                GetMeshIdentifier()
            );
        }

        return true;
    }
}

#endif //SR_ENGINE_GRAPHICS_INDEXEDMESH_H
```


