//
// Created by Monika on 28.03.2023.
//

#ifndef SRENGINE_GRAPHICSRESOURCERELOADER_H
#define SRENGINE_GRAPHICSRESOURCERELOADER_H

#include <Utils/ResourceManager/IResourceReloader.h>

#include <utility>

namespace SR_GRAPH_NS {
    class RenderContext;
}

namespace SR_CORE_NS {
    class SR_DLL_EXPORT GraphicsResourceReloader final : public SR_UTILS_NS::IResourceReloader {
        using Super = SR_UTILS_NS::IResourceReloader;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using ContextGetterFn = SR_HTYPES_NS::Function<RenderContextPtr()>;
    public:
        explicit GraphicsResourceReloader(ContextGetterFn contextGetter)
            : Super()
            , m_contextGetter(std::move(contextGetter))
        { }

        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) override;

    private:
        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);

    private:
        ContextGetterFn m_contextGetter;

    };
}

#endif //SRENGINE_GRAPHICSRESOURCERELOADER_H
