//
// Created by Monika on 28.03.2023.
//

#include <Core/Utils/GraphicsResourceReloader.h>
#include <Core/Engine.h>

namespace SR_CORE_NS {
    bool GraphicsResourceReloader::Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) {
        auto&& pResource = pResourceInfo->GetResource();
        if (!pResource) {
            return false;
        }

        if (!IsResourceSuitableForReload(pResource)) {
            return true;
        }

        if (!pResource->Reload()) {
            return false;
        }

        OnResourceReloaded(pResource);

        return true;
    }

    void GraphicsResourceReloader::OnResourceReloaded(SR_UTILS_NS::IResource::Ptr pResource) {
        auto&& engine = Engine::Instance();
        auto&& renderScene = engine.GetRenderScene();

        if (renderScene.LockIfValid()) {
            renderScene->OnResourceReloaded(pResource);
            renderScene.Unlock();
        }
    }
}