

# File UniqueMaterial.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Material**](dir_d7c89fdc4b5407f55bdfbb167bac987a.md) **>** [**UniqueMaterial.h**](UniqueMaterial_8h.md)

[Go to the documentation of this file](UniqueMaterial_8h.md)


```C++
//
// Created by Monika on 26.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_UNIQUE_MATERIAL_H
#define SR_ENGINE_GRAPHICS_UNIQUE_MATERIAL_H

#include <Graphics/Material/BaseMaterial.h>

namespace SR_GRAPH_NS {
    class UniqueMaterial : public BaseMaterial {
        SR_CLASS()
        using Super = BaseMaterial;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<UniqueMaterial>;

    public:
        UniqueMaterial();
        ~UniqueMaterial() override;

    public:
        void SetMaterialData(const MaterialData::Ptr& pData) noexcept;
        SR_NODISCARD const MaterialData::Ptr& GetMaterialData() const noexcept override;
        SR_NODISCARD MaterialType GetMaterialType() const noexcept override;

    private:
        mutable SR_GRAPH_NS::MaterialData::Ptr m_data;

    };
}

#endif //SR_ENGINE_GRAPHICS_UNIQUE_MATERIAL_H
```


