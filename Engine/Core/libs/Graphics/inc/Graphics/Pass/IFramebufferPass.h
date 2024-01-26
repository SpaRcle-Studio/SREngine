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
    class RenderContext;
    class Pipeline;

    class IFramebufferPass {
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    public:
        using ColorFormats = std::list<ImageFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;

    public:
        IFramebufferPass();
        virtual ~IFramebufferPass();

    public:
        SR_NODISCARD FramebufferPtr GetFramebuffer() const noexcept { return m_framebuffer; }
        SR_NODISCARD bool IsFrameBufferRendered() const noexcept { return m_isFrameBufferRendered; }
        SR_NODISCARD bool IsDirectional() const noexcept { return m_isDirectional; }

    protected:
        void LoadFramebufferSettings(const SR_XML_NS::Node& passNode);

        bool InitializeFramebuffer(RenderContext* pContext);

        void ResizeFrameBuffer(const SR_MATH_NS::UVector2 &size);

        bool RenderFrameBuffer(const PipelinePtr& pPipeline);
        void UpdateFrameBuffer(const PipelinePtr& pPipeline);

        virtual void RenderFrameBufferInner() { }
        virtual void UpdateFrameBufferInner() { }

    private:
        bool RenderFrameBuffer(const PipelinePtr& pPipeline, uint8_t layers);

    protected:
        /// TODO: move all to private

        bool m_isFrameBufferRendered = false;
        bool m_dynamicResizing = false;
        bool m_depthEnabled = true;

        SR_MATH_NS::FVector2 m_preScale = SR_MATH_NS::FVector2(1.f);
        SR_MATH_NS::IVector2 m_size;

        ColorFormats m_colorFormats;
        ClearColors m_clearColors;

        FramebufferPtr m_framebuffer = nullptr;

        float_t m_depth = 1.f;
        uint8_t m_samples = 0;
        uint32_t m_layersCount = 1;
        ImageFormat m_depthFormat = ImageFormat::Unknown;
        ImageAspect m_depthAspect = ImageAspect::DepthStencil;

        /// режим рендера без кадрового буффера, напрямую
        bool m_isDirectional = false;

        uint8_t m_currentFrameBufferLayer = 0;

    private:
        SR_GRAPH_NS::Memory::UBOManager& m_frameBufferUboManager;

    };
}

#endif //SR_ENGINE_IFRAMEBUFFERPASS_H
