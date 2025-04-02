

# File MeshMaterialProperty.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Material**](dir_2ed0f653e9a17ea2b9386330cebea31f.md) **>** [**MeshMaterialProperty.h**](MeshMaterialProperty_8h.md)

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


