//
// Created by Monika on 11.03.2023.
//

#include <Utils/ResourceManager/IResourceReloader.h>
#include <Utils/ResourceManager/ResourceInfo.h>

namespace SR_UTILS_NS {
    bool DefaultResourceReloader::Reload(const SR_UTILS_NS::Path& /** path */, ResourceInfo* pResourceInfo) {
        SR_TRACY_ZONE;

        for (auto&& pResource : pResourceInfo->m_loaded) {
            if (!IsResourceSuitableForReload(pResource)) {
                continue;
            }

            pResource->Reload();
        }

        return true;
    }

    bool IResourceReloader::IsResourceSuitableForReload(IResource *pResource) const {
        SR_TRACY_ZONE;

        if (pResource->IsDestroyed()) {
            return false;
        }

        auto&& loadState = pResource->GetResourceLoadState();

        using LS = IResource::LoadState;
        if (loadState == LS::Reloading || loadState == LS::Loading || loadState == LS::Unloading) {
            return false;
        }

        SR_NOOP;

        return true;
    }
}
