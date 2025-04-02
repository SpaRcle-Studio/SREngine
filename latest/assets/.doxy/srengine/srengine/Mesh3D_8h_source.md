

# File Mesh3D.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Geometry**](dir_5f6ef964ec8b90bf6766130495c7d0d9.md) **>** [**Mesh3D.h**](Mesh3D_8h.md)

[Go to the documentation of this file](Mesh3D_8h.md)


```C++
//
// Created by Nikita on 01.06.2021.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_3D_H
#define SR_ENGINE_GRAPHICS_MESH_3D_H

#include <Utils/Types/IRawMeshHolder.h>

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    class Mesh3D final : public IndexedMesh, public SR_HTYPES_NS::IRawMeshHolder {
        using Super = IndexedMesh;
        SR_CLASS()
    public:
        Mesh3D() = default;

    public:
        typedef Vertices::StaticMeshVertex VertexType;

    public:
        void UseMaterial() override;
        void UseModelMatrix() override;

        void OnRawMeshChanged() override;
        bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource) override;

        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Static; }

        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD std::vector<uint32_t> GetIndices() const override;
        SR_NODISCARD std::string GetMeshIdentifier() const override;

    private:
        bool Calculate() override;

    private:
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_3D_H
```


