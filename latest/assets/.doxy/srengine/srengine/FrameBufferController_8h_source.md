

# File FrameBufferController.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**FrameBufferController.h**](FrameBufferController_8h.md)

[Go to the documentation of this file](FrameBufferController_8h.md)


```C++
//
// Created by Monika on 04.02.2024.
//

#ifndef SR_ENGINE_FRAME_BUFFER_CONTROLLER_H
#define SR_ENGINE_FRAME_BUFFER_CONTROLLER_H

#include <Graphics/Pipeline/FrameBufferFeatures.h>
#include <Graphics/Pipeline/TextureHelper.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Serialization/Serializable.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FrameBufferController final : public SR_HTYPES_NS::SharedPtr<FrameBufferController>, public SR_UTILS_NS::Serializable {
        SR_CLASS()
        using Super = SR_HTYPES_NS::SharedPtr<FrameBufferController>;
        using ColorFormats = std::vector<ImageFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FrameBufferController>;

    public:
        FrameBufferController();
        ~FrameBufferController() override;

    public:
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer>& GetFramebuffer() const noexcept { return m_framebuffer; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer>& GetFramebuffer() noexcept { return m_framebuffer; }
        SR_NODISCARD uint8_t GetLayersCount() const noexcept { return m_layersCount; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept { return m_name; }

        bool InitializeFramebuffer(RenderContext* pContext);

        void OnResize(const SR_MATH_NS::UVector2& size);

    private:
        SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer> m_framebuffer;

    private:
        SR_UTILS_NS::StringAtom m_name;

        bool m_dynamicResizing = true;
        bool m_depthEnabled = true;
        bool m_instanceForEachFrame = false;

        SR_MATH_NS::FVector2 m_preScale = SR_MATH_NS::FVector2(1.f);
        SR_MATH_NS::IVector2 m_size;

        ColorFormats m_colorFormats = { ImageFormat::RGBA8_UNORM };

        FrameBufferFeatures m_features;
        uint8_t m_samples = 0;
        uint32_t m_layersCount = 1;
        uint32_t m_arrayLayersCount = 1;
        ImageFormat m_depthFormat = ImageFormat::Auto;
        ImageAspect m_depthAspect = ImageAspect::DepthStencil;

    };
}

#endif //SR_ENGINE_FRAME_BUFFER_CONTROLLER_H
```


