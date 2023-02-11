//
// Created by Monika on 21.01.2023.
//

#ifndef SRENGINE_IFRAMEBUFFERPASS_H
#define SRENGINE_IFRAMEBUFFERPASS_H

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class RenderContext;

    class IFramebufferPass {
    public:
        using ColorFormats = std::list<ColorFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;

    public:
        IFramebufferPass();
        virtual ~IFramebufferPass();

    public:
        SR_NODISCARD FramebufferPtr GetFramebuffer() const noexcept { return m_framebuffer; }

    protected:
        void LoadFramebufferSettings(const SR_XML_NS::Node& settingsNode);

        bool InitializeFramebuffer(RenderContext* pContext);

        void ResizeFrameBuffer(const SR_MATH_NS::UVector2 &size);

    protected:
        bool m_dynamicResizing = false;
        bool m_depthEnabled = true;

        SR_MATH_NS::FVector2 m_preScale;
        SR_MATH_NS::IVector2 m_size;

        ColorFormats m_colorFormats;
        ClearColors m_clearColors;

        FramebufferPtr m_framebuffer = nullptr;

        float_t m_depth = 1.f;
        uint8_t m_samples = 0;
        DepthFormat m_depthFormat = DepthFormat::Unknown;

    };
}

#endif //SRENGINE_IFRAMEBUFFERPASS_H
