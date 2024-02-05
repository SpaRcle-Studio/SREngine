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
        SR_NODISCARD uint8_t GetCurrentFrameBufferLayer() const noexcept { return m_currentFrameBufferLayer; }

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

        /// режим рендера без кадрового буффера, напрямую
        bool m_isDirectional = false;

        uint8_t m_currentFrameBufferLayer = 0;

        SR_GRAPH_NS::Memory::UBOManager& m_frameBufferUboManager;

    };
}

#endif //SR_ENGINE_IFRAMEBUFFERPASS_H
