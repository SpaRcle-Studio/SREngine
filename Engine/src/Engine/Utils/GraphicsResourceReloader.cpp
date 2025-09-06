//
// Created by Monika on 28.03.2023.
//

#include <Engine/Utils/GraphicsResourceReloader.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_CORE_NS {
    bool GraphicsResourceReloader::Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) {
        SR_TRACY_ZONE;

        bool hasErrors = false;

        SR_LOG("GraphicsResourceReloader::Reload() : reload resource \"" + path.ToStringRef() + "\"");

        auto resourcesCopy = pResourceInfo->GetResources();
        for (auto&& pResource : resourcesCopy) {
            if (!pResource) {
                continue;
            }

            if (!IsResourceSuitableForReload(pResource)) {
                continue;
            }

            if (!pResource->Reload()) {
                hasErrors = true;
                continue;
            }

            OnResourceReloaded(pResource);
        }

        return !hasErrors;
    }

    void GraphicsResourceReloader::OnResourceReloaded(const SR_UTILS_NS::IResource::Ptr& pResource) {
        SR_TRACY_ZONE;

        auto&& pContext = m_contextGetter ? m_contextGetter() : RenderContextPtr();

        if (pContext.RecursiveLockIfValid()) {
            for (auto&& [pScene, pRenderScene] : pContext->GetScenes()) {
                if (pRenderScene) {
                    pRenderScene->OnResourceReloaded(pResource);
                }
            }
            pContext.Unlock();
        }
        else {
            SR_WARN("GraphicsResourceReloader::OnResourceReloaded() : render context is not available!");
        }
    }
}