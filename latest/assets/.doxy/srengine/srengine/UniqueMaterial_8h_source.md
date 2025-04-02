

# File UniqueMaterial.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Material**](dir_2ed0f653e9a17ea2b9386330cebea31f.md) **>** [**UniqueMaterial.h**](UniqueMaterial_8h.md)

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


