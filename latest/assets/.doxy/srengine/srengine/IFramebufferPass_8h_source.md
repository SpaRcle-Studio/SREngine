

# File IFramebufferPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**IFramebufferPass.h**](IFramebufferPass_8h.md)

[Go to the documentation of this file](IFramebufferPass_8h.md)


```C++
//
// Created by Monika on 21.01.2023.
//

#ifndef SR_ENGINE_IFRAME_BUFFER_PASS_H
#define SR_ENGINE_IFRAME_BUFFER_PASS_H

#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Memory/UBOManager.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FrameBufferController;
    class RenderContext;
    class IRenderTechnique;
    class Pipeline;

    class IFramebufferPass {
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    public:
        using ColorFormats = std::list<ImageFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;

    public:
        IFramebufferPass();
        virtual ~IFramebufferPass() = default;

    public:
        SR_NODISCARD FramebufferPtr GetFramebuffer() const noexcept;
        SR_NODISCARD bool IsFrameBufferRendered() const noexcept { return m_isFrameBufferRendered; }
        SR_NODISCARD bool IsDirectional() const noexcept { return m_isDirectional; }
        SR_NODISCARD ClearColors GetClearColors() const noexcept { return m_clearColors; }
        SR_NODISCARD std::optional<float_t> GetClearDepth() const noexcept { return m_depth; }
        SR_NODISCARD uint8_t GetLayersCount() const noexcept;

    protected:
        SR_NODISCARD virtual IRenderTechnique* GetFrameBufferRenderTechnique() const = 0;

        void LoadFramebufferSettings(const SR_XML_NS::Node& passNode);

        bool RenderFrameBuffer(const PipelinePtr& pPipeline);
        void UpdateFrameBuffer(const PipelinePtr& pPipeline);

        virtual void RenderFrameBufferInner() { }
        virtual void UpdateFrameBufferInner() { }

    protected:
        bool m_isFrameBufferRendered = false;

    private:
        bool RenderFrameBuffer(const PipelinePtr& pPipeline, uint8_t layers);

    private:
        SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::FrameBufferController> m_frameBufferController;

        SR_UTILS_NS::StringAtom m_frameBufferName;

        ClearColors m_clearColors;
        std::optional<float_t> m_depth;

        bool m_isDirectional = false;

        SR_GRAPH_NS::Memory::UBOManager& m_frameBufferUboManager;

    };
}

#endif //SR_ENGINE_IFRAMEBUFFERPASS_H
```


