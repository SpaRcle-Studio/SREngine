

# File FileMaterial.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Material**](dir_2ed0f653e9a17ea2b9386330cebea31f.md) **>** [**FileMaterial.h**](FileMaterial_8h.md)

[Go to the documentation of this file](FileMaterial_8h.md)


```C++
//
// Created by Monika on 19.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_FILE_MATERIAL_H
#define SR_ENGINE_GRAPHICS_FILE_MATERIAL_H

#include <Graphics/Material/BaseMaterial.h>

namespace SR_GRAPH_NS {
    class FileMaterialResource final : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
    public:
        FileMaterialResource();

    public:
        SR_NODISCARD static bool CreateTemplateMaterial(const SR_UTILS_NS::Path& path);
        static FileMaterialResource* Load(const SR_UTILS_NS::Path& rawPath);

    public:
        SR_NODISCARD SR_UTILS_NS::IResource::Ptr CopyResource(SR_UTILS_NS::IResource::Ptr pDestination) const override;
        SR_NODISCARD const SR_GRAPH_NS::MaterialData::Ptr& GetData() const noexcept { return m_data; }

    private:
        bool Load() override;
        bool Unload() override;

    private:
        SR_GRAPH_NS::MaterialData::Ptr m_data;

    };

    class FileMaterial final : public BaseMaterial {
        using Super = BaseMaterial;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FileMaterial>;

        ~FileMaterial() override;

    public:
        SR_NODISCARD static BaseMaterial::Ptr Load(const SR_UTILS_NS::Path& rawPath);
        SR_NODISCARD static BaseMaterial::Ptr LoadAsUnique(const SR_UTILS_NS::Path& rawPath);

    public:
        SR_NODISCARD MaterialType GetMaterialType() const noexcept override { return MaterialType::File; }
        SR_NODISCARD const MaterialData::Ptr& GetMaterialData() const noexcept override;

        SR_NODISCARD SR_UTILS_NS::Path GetMaterialPath() const noexcept { return m_pResource ? m_pResource->GetResourcePath() : SR_UTILS_NS::Path(); }
        SR_NODISCARD void SetMaterialPath(const SR_UTILS_NS::Path& path) noexcept;

    private:
        void Init();

    private:
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

        FileMaterialResource* m_pResource = nullptr;

        SR_UTILS_NS::Subscription m_reloadBeginSubscription;
        SR_UTILS_NS::Subscription m_reloadDoneSubscription;

    };
}

#endif //SR_ENGINE_GRAPHICS_FILE_MATERIAL_H
```


