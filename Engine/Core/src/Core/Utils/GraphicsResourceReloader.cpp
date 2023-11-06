//
// Created by Monika on 28.03.2023.
//

#include <Core/Utils/GraphicsResourceReloader.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

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

        auto&& pContext = m_contextGetter ? m_contextGetter() : RenderContextPtr();

        if (pContext.RecursiveLockIfValid()) {
            for (auto&& [pScene, pRenderScene] : pContext->GetScenes()) {
                if (pRenderScene.LockIfValid()) {
                    pRenderScene->OnResourceReloaded(pResource);
                    pRenderScene.Unlock();
                }
            }
            pContext.Unlock();
        }
        else {
            SR_WARN("GraphicsResourceReloader::OnResourceReloaded() : render context is not available!");
        }
    }
}