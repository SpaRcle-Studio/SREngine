//
// Created by Monika on 28.03.2023.
//

#ifndef SR_ENGINE_GRAPHICSRESOURCERELOADER_H
#define SR_ENGINE_GRAPHICSRESOURCERELOADER_H

#include <Utils/Resources/IResourceReloader.h>
#include <Utils/Types/SafePointer.h>

namespace SR_GRAPH_NS {
    class RenderContext;
}

/**
 * Creates a GraphicsResourceReloader that obtains a render context via the provided callable.
 * @param contextGetter Callable returning the current render context as a SafePtr; may be invoked when a resource reload is performed.
 */
/**
 * Attempts to reload the graphics resource at the given filesystem path and updates associated resource info.
 * @param path Filesystem path of the resource to reload.
 * @param pResourceInfo Pointer to resource metadata to update during reload; may be null if metadata is not required.
 * @returns `true` if the resource was reloaded successfully, `false` otherwise.
 */
/**
 * Notifies the reloader that a resource has been reloaded.
 * @param pResource Shared pointer to the resource that was reloaded.
 */
namespace SR_CORE_NS {
    class SR_CORE_DLL_API GraphicsResourceReloader final : public SR_UTILS_NS::IResourceReloader {
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
        void OnResourceReloaded(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::IResource>& pResource);

    private:
        ContextGetterFn m_contextGetter;

    };
}

#endif //SR_ENGINE_GRAPHICSRESOURCERELOADER_H