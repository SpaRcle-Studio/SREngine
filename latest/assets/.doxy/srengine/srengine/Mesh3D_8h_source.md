

# File Mesh3D.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Geometry**](dir_85f7ff9424d99e3bcbc126d4280965b1.md) **>** [**Mesh3D.h**](Mesh3D_8h.md)

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


