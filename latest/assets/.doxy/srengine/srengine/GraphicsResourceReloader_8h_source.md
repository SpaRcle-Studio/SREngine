

# File GraphicsResourceReloader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Utils**](dir_d35469fe832a0ac18d8831284d386406.md) **>** [**GraphicsResourceReloader.h**](GraphicsResourceReloader_8h.md)

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

#endif //SR_ENGINE_GRAPHICSRESOURCERELOADER_H
```


