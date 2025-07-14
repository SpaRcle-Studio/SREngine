

# File FileMaterial.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Material**](dir_d7c89fdc4b5407f55bdfbb167bac987a.md) **>** [**FileMaterial.h**](FileMaterial_8h.md)

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
        using Ptr = SR_HTYPES_NS::SharedPtr<FileMaterialResource>;

    public:
        FileMaterialResource();

    public:
        SR_NODISCARD static bool CreateTemplateMaterial(const SR_UTILS_NS::Path& path);
        SR_NODISCARD static FileMaterialResource::Ptr Load(const SR_UTILS_NS::Path& rawPath);

    public:
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

        FileMaterialResource::Ptr m_pResource = nullptr;

        SR_UTILS_NS::Subscription m_reloadBeginSubscription;
        SR_UTILS_NS::Subscription m_reloadDoneSubscription;

    };
}

#endif //SR_ENGINE_GRAPHICS_FILE_MATERIAL_H
```


