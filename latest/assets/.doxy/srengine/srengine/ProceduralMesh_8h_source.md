

# File ProceduralMesh.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**ProceduralMesh.h**](ProceduralMesh_8h.md)

[Go to the documentation of this file](ProceduralMesh_8h.md)


```C++
//
// Created by Monika on 05.04.2022.
//

#ifndef SR_ENGINE_PROCEDURALMESH_H
#define SR_ENGINE_PROCEDURALMESH_H

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class ProceduralMesh final : public IndexedMesh {
        using Super = IndexedMesh;
    public:
        ProceduralMesh() = default;

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Procedural; }

        void SetIndexedVertices(void* pData, uint64_t count);
        void SetIndices(void* pData, uint64_t count);
        void SetVertices(const std::vector<Vertices::StaticMeshVertex>& vertices);

        void UseMaterial() override;
        void UseModelMatrix() override;

        SR_NODISCARD bool IsUniqueMesh() const override { return true; }

        SR_NODISCARD bool IsCalculatable() const override;

    private:
        bool Calculate() override;
        void Draw() override;
        void SetDirtyMesh();

        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;

    private:
        std::vector<Vertices::StaticMeshVertex> m_vertices;
        std::vector<uint32_t> m_indices;

    };
}

#endif //SR_ENGINE_PROCEDURALMESH_H
```


