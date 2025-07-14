

# File GraphicsResourceReloader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Utils**](dir_28dae956caee7d361b94ee0c634a2896.md) **>** [**GraphicsResourceReloader.h**](GraphicsResourceReloader_8h.md)

[Go to the documentation of this file](GraphicsResourceReloader_8h.md)


```C++
//
// Created by Monika on 28.03.2023.
//

#ifndef SR_ENGINE_GRAPHICSRESOURCERELOADER_H
#define SR_ENGINE_GRAPHICSRESOURCERELOADER_H

#include <Utils/Resources/IResourceReloader.h>

#include <utility>

namespace SR_GRAPH_NS {
    class RenderContext;
}

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
        void OnResourceReloaded(const SR_UTILS_NS::IResource::Ptr& pResource);

    private:
        ContextGetterFn m_contextGetter;

    };
}

#endif //SR_ENGINE_GRAPHICSRESOURCERELOADER_H
```


