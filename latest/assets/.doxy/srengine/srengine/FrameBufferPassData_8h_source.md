

# File FrameBufferPassData.h

[**File List**](files.md) **>** [**Data**](dir_0f42f4e4163da7b79318e6e4fde7c4ea.md) **>** [**FrameBufferPassData.h**](FrameBufferPassData_8h.md)

[Go to the documentation of this file](FrameBufferPassData_8h.md)


```C++
//
// Created by Monika on 21.01.2023.
//

#ifndef SR_ENGINE_IFRAME_BUFFER_PASS_H
#define SR_ENGINE_IFRAME_BUFFER_PASS_H

#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Render/FrameBufferController.h>
#include <Graphics/Memory/UBOManager.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class IRenderTechnique;

    class FrameBufferPassData final : public SR_UTILS_NS::Serializable {
        SR_CLASS()
        using Super = SR_UTILS_NS::Serializable;
    public:
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using FBRenderCallback = SR_HTYPES_NS::Function<bool()>;
        using FBUpdateCallback = SR_HTYPES_NS::Function<void()>;

    public:
        FrameBufferPassData();

    public:
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer>& GetFramebuffer() const noexcept;
        SR_NODISCARD bool IsFrameBufferRendered() const noexcept { return m_isFrameBufferRendered; }
        SR_NODISCARD const ClearColors& GetClearColors() const noexcept { return m_clearColors; }
        SR_NODISCARD std::optional<float_t> GetClearDepth() const noexcept { return m_depth; }
        SR_NODISCARD uint8_t GetLayersCount() const noexcept;

        bool RenderFrameBuffer(const FBRenderCallback& callback);
        void UpdateFrameBuffer(const FBUpdateCallback& callback);

        void SetRenderTechnique(IRenderTechnique* pRenderTechnique) noexcept { m_renderTechnique = pRenderTechnique; }

    private:
        bool RenderFrameBuffer(const FBRenderCallback& callback, uint8_t layers);

        SR_NODISCARD const Pipeline::Ptr& GetPipeline() const noexcept;
        SR_NODISCARD const FrameBufferController::Ptr& GetFrameBufferController() const noexcept;

    private:
        mutable FrameBufferController::Ptr m_frameBufferController;
        IRenderTechnique* m_renderTechnique = nullptr;
        bool m_isFrameBufferRendered = false;

        ClearColors m_clearColors;
        SR_UTILS_NS::StringAtom m_frameBufferName;
        std::optional<float_t> m_depth;

    };
}

#endif //SR_ENGINE_IFRAMEBUFFERPASS_H
```


