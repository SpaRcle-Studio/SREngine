

# File MeshMaterialProperty.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Material**](dir_d7c89fdc4b5407f55bdfbb167bac987a.md) **>** [**MeshMaterialProperty.h**](MeshMaterialProperty_8h.md)

[Go to the documentation of this file](MeshMaterialProperty_8h.md)


```C++
//
// Created by Monika on 26.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_MATERIAL_PROPERTY_H
#define SR_ENGINE_GRAPHICS_MESH_MATERIAL_PROPERTY_H

#include <Utils/TypeTraits/Properties.h>
#include <Graphics/Material/MaterialType.h>

namespace SR_GTYPES_NS {
    class Mesh;
}

namespace SR_GRAPH_NS {
    class BaseMaterial;

    class MeshMaterialProperty final : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(MeshMaterialProperty, 1000)
        using Super = SR_UTILS_NS::Property;
    public:
        MeshMaterialProperty();
        ~MeshMaterialProperty() override;

    public:
        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

    public:
        SR_NODISCARD MaterialType GetMaterialType() const noexcept;
        SR_NODISCARD BaseMaterial* GetMaterial() const noexcept { return m_pMaterial; }
        void SetMaterial(BaseMaterial* pMaterial) noexcept;
        void SetMaterial(const SR_UTILS_NS::Path& path) noexcept;
        void SetMesh(SR_GTYPES_NS::Mesh* pMesh) noexcept { m_pMesh = pMesh; }

    private:
        SR_GTYPES_NS::Mesh* m_pMesh = nullptr;
        BaseMaterial* m_pMaterial = nullptr;
        uint32_t m_materialRegisterId = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_MATERIAL_PROPERTY_H
```


