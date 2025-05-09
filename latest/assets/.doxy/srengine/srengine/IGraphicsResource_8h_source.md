

# File IGraphicsResource.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**IGraphicsResource.h**](IGraphicsResource_8h.md)

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


