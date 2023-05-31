//
// Created by Monika on 28.03.2023.
//

#include <Core/Utils/GraphicsResourceReloader.h>
#include <Core/Engine.h>

namespace SR_CORE_NS {
    bool GraphicsResourceReloader::Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) {
        SR_TRACY_ZONE;

        auto&& pResource = pResourceInfo->GetResource();
        if (!pResource) {
            return false;
        }

        if (!IsResourceSuitableForReload(pResource)) {
            return true;
        }

        SR_LOG("GraphicsResourceReloader::Reload() : reload resource \"" + path.ToStringRef() + "\"");

        if (!pResource->Reload()) {
            return false;
        }

        OnResourceReloaded(pResource);

        return true;
    }

    void GraphicsResourceReloader::OnResourceReloaded(SR_UTILS_NS::IResource::Ptr pResource) {
        SR_TRACY_ZONE;

        auto&& engine = Engine::Instance();
        auto&& renderScene = engine.GetRenderScene();

        if (renderScene.LockIfValid()) {
            renderScene->OnResourceReloaded(pResource);
            renderScene.Unlock();
        }
    }
}