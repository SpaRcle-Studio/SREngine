

# File Asset.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**Asset.h**](Asset_8h.md)

[Go to the documentation of this file](Asset_8h.md)


```C++
//
// Created by Monika on 11.07.2025.
//

#ifndef SR_ENGINE_COMMON_ASSET_H
#define SR_ENGINE_COMMON_ASSET_H

#include <Utils/Resources/IResource.h>
#include <Utils/Resources/ResourceManager.h>

namespace SR_UTILS_NS {
    class Asset : public IResource {
        SR_CLASS()
        using Super = IResource;
    public:
        SR_INLINE static const char* EXTENSION_NAME = "sras";
        using Ptr = SR_HTYPES_NS::SharedPtr<Asset>;
        using OriginType = Asset;

    public:
        SR_NODISCARD bool SaveAsset(const Path& path) const;
        SR_NODISCARD bool SaveAsset() const;

        template<class AssetT = Asset> SR_NODISCARD static SR_HTYPES_NS::SharedPtr<AssetT> Load(const Path& path);
        template<class AssetT> SR_NODISCARD static SR_HTYPES_NS::SharedPtr<AssetT> CreateNew(const Path& path);

    protected:
        virtual void OnAssetLoaded() { }

    private:
        SR_NODISCARD static Asset::Ptr LoadImpl(const Path& path);

    protected:
        bool Load() override;
        bool Unload() override;

    };

    template<class AssetT> SR_HTYPES_NS::SharedPtr<AssetT> Asset::Load(const Path& path) {
        if constexpr (!std::is_base_of_v<Asset, AssetT>) {
            static_assert(AlwaysFalseV<AssetT>, "AssetT must be derived from Asset!");
        }
        else {
            auto&& pAsset = Asset::LoadImpl(path);
            if (!pAsset) {
                SR_ERROR("Asset::Load() : failed to load asset from path: {}", path);
                return nullptr;
            }

            if constexpr (std::is_same_v<AssetT, Asset>) {
                return pAsset;
            }

            auto&& pImpl = pAsset->DynamicCast<AssetT>();
            if (!pImpl) {
                SRHalt("Asset::Load() : failed to cast asset to type: {}\n\tPath:", AssetT::GetClassStaticName(), path);
                pImpl->CheckResourceUsage();
                return nullptr;
            }

            return pImpl;
        }
    }

    template<class AssetT> SR_HTYPES_NS::SharedPtr<AssetT> Asset::CreateNew(const Path& rawPath) {
        auto&& resourceManager = ResourceManager::Instance();
        SR_UTILS_NS::Path&& path = rawPath.RemoveSubPath(resourceManager.GetResPath());

        if (resourceManager.GetResPath().Concat(path).Exists()) {
            SR_ERROR("Asset::CreateNew() : asset already exists at path: {}", path);
            return nullptr;
        }

        if constexpr (!std::is_base_of_v<Asset, AssetT>) {
            static_assert(AlwaysFalseV<AssetT>, "AssetT must be derived from Asset!");
        }
        else {
            SR_HTYPES_NS::SharedPtr<AssetT> pAsset = AssetT::template MakeShared<AssetT>();
            pAsset->m_loadState = IResource::LoadState::Loaded;

            if (!pAsset->SaveAsset(resourceManager.GetResPath().Concat(path))) {
                SR_ERROR("Asset::CreateNew() : failed to save asset to path: {}", path);
                pAsset->DeleteResource();
                return nullptr;
            }

            pAsset->SetId(path.ToStringRef(), true);
            return pAsset;
        }
    }
}

#endif //SR_ENGINE_COMMON_ASSET_H
```


