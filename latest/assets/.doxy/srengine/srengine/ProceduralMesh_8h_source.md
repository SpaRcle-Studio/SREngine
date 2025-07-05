

# File ProceduralMesh.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**ProceduralMesh.h**](ProceduralMesh_8h.md)

[Go to the documentation of this file](ProceduralMesh_8h.md)


```C++
//
// Created by Monika on 05.04.2022.
//

#ifndef SR_ENGINE_PROCEDURALMESH_H
#define SR_ENGINE_PROCEDURALMESH_H

#include <Graphics/Types/Geometry/MeshComponent.h>

#include <Utils/Types/FastMemoryArray.h>

namespace SR_GTYPES_NS {
    class ProceduralMesh final : public IndexedMesh {
        using Super = IndexedMesh;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ProceduralMesh>;
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        ProceduralMesh() = default;

    public:
        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Procedural; }

        void SwapIndexedVertices(SR_HTYPES_NS::FastMemoryArray<Vertices::StaticMeshVertexAligned>& vertices);

        void SwapIndexedVertices(SR_HTYPES_NS::FastMemoryArray<Vertices::StaticMeshVertex>& vertices);
        void SwapIndices(SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices);

        void SetIndexedVertices(void* pData, uint64_t count);
        void SetIndices(void* pData, uint64_t count);

        void SetVertices(const std::vector<Vertices::StaticMeshVertex>& vertices);
        void SetVertices(const SR_HTYPES_NS::FastMemoryArray<Vertices::StaticMeshVertex>& vertices);

        void UseMaterial() override;
        void UseModelMatrix() override;

        SR_NODISCARD bool IsUniqueMesh() const override { return true; }
        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD bool IsSupportVBO() const override;

    private:
        void FreeVideoMemory() override;
        bool Calculate() override;
        void SetDirtyMesh();
        void UseSSBO() override;

        SR_NODISCARD const SR_HTYPES_NS::FastMemoryArray<uint32_t>& GetIndices() const override;

    private:
        bool m_useSSBOInsteadOfVertices = false;

        int32_t m_ssbo = SR_ID_INVALID;
        uint32_t m_ssboSize = 0;

        SR_HTYPES_NS::FastMemoryArray<Vertices::StaticMeshVertexAligned> m_verticesAligned;

        SR_HTYPES_NS::FastMemoryArray<Vertices::StaticMeshVertex> m_vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> m_indices;

    };
}

#endif //SR_ENGINE_PROCEDURALMESH_H
```


