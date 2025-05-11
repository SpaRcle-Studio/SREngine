

# File IGraphicsResource.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Memory**](dir_dc778743e05f6f13753dd9bf5a4bd428.md) **>** [**IGraphicsResource.h**](IGraphicsResource_8h.md)

[Go to the documentation of this file](IGraphicsResource_8h.md)


```C++
//
// Created by Monika on 18.07.2022.
//

#ifndef SR_ENGINE_IGRAHPICSRESOURCE_H
#define SR_ENGINE_IGRAHPICSRESOURCE_H

#include <Graphics/macros.h>

#include <Utils/Debug.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class Pipeline;
}

namespace SR_GRAPH_NS::Memory {
    class IGraphicsResource {
    public:
        using RenderContextPtr = RenderContext*;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    protected:
        IGraphicsResource() = default;
        virtual ~IGraphicsResource();

    public:
        IGraphicsResource(const IGraphicsResource&) = delete;
        IGraphicsResource& operator=(const IGraphicsResource&) = delete;

    public:
        virtual void DeInitGraphicsResource();

        virtual void FreeVideoMemory() {
            m_isCalculated = false;
        }

        void MarkPipelineUnBuild();

        void SetRenderContext(const RenderContextPtr& renderContext);

        SR_NODISCARD PipelinePtr GetPipeline() const noexcept {
            return m_pipeline;
        }

        SR_NODISCARD RenderContextPtr GetRenderContext() const noexcept {
            return m_renderContext;
        }

        SR_NODISCARD SR_FORCE_INLINE bool IsCalculated() const { return m_isCalculated; }
        SR_NODISCARD SR_FORCE_INLINE bool IsGraphicsResourceRegistered() const { return m_pipeline; }

    protected:
        bool m_isCalculated = false;

        PipelinePtr m_pipeline;
        RenderContextPtr m_renderContext = nullptr;

    };
}

#endif //SR_ENGINE_IGRAHPICSRESOURCE_H
```


