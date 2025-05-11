

# File FrameBufferController.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**FrameBufferController.h**](FrameBufferController_8h.md)

[Go to the documentation of this file](FrameBufferController_8h.md)


```C++
//
// Created by Monika on 04.02.2024.
//

#ifndef SR_ENGINE_FRAME_BUFFER_CONTROLLER_H
#define SR_ENGINE_FRAME_BUFFER_CONTROLLER_H

#include <Graphics/macros.h>

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
```


