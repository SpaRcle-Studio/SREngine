//
// Created by Monika on 04.02.2024.
//

#ifndef SR_ENGINE_FRAME_BUFFER_CONTROLLER_H
#define SR_ENGINE_FRAME_BUFFER_CONTROLLER_H

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SharedPtr.h>
#include <Graphics/Pipeline/FrameBufferFeatures.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FrameBufferController : public SR_HTYPES_NS::SharedPtr<FrameBufferController> {
        using Super = SR_HTYPES_NS::SharedPtr<FrameBufferController>;
        using ColorFormats = std::list<ImageFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
    public:
        FrameBufferController();
        ~FrameBufferController();

    public:
        SR_NODISCARD SR_GTYPES_NS::Framebuffer* GetFramebuffer() const noexcept { return m_framebuffer; }
        SR_NODISCARD uint8_t GetLayersCount() const noexcept { return m_layersCount; }

        bool LoadFramebufferSettings(const SR_XML_NS::Node& settingsNode);
        bool InitializeFramebuffer(RenderContext* pContext);

        void OnResize(const SR_MATH_NS::UVector2& size);

    private:
        bool m_dynamicResizing = false;
        bool m_depthEnabled = true;

        SR_MATH_NS::FVector2 m_preScale = SR_MATH_NS::FVector2(1.f);
        SR_MATH_NS::IVector2 m_size;

        SR_GTYPES_NS::Framebuffer* m_framebuffer = nullptr;

        ColorFormats m_colorFormats;

        FrameBufferFeatures m_features;
        uint8_t m_samples = 0;
        uint32_t m_layersCount = 1;
        ImageFormat m_depthFormat = ImageFormat::Unknown;
        ImageAspect m_depthAspect = ImageAspect::DepthStencil;

    };
}

#endif //SR_ENGINE_FRAME_BUFFER_CONTROLLER_H
