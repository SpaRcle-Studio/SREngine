

# File Framebuffer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Framebuffer.h**](Framebuffer_8h.md)

[Go to the documentation of this file](Framebuffer_8h.md)


```C++
//
// Created by Monika on 06.05.2022.
//

#ifndef SR_ENGINE_FRAMEBUFFER_H
#define SR_ENGINE_FRAMEBUFFER_H

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Resources/IResource.h>

#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Pipeline/FrameBufferFeatures.h>

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GTYPES_NS {
    class RenderTexture;

    class Framebuffer : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        SR_CLASS()
        using Super = SR_UTILS_NS::IResource;
    public:
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Framebuffer>;

    public:
        Framebuffer();
        ~Framebuffer() override;

    public:
        static Ptr Create(uint32_t images, const SR_MATH_NS::IVector2& size);
        static Ptr Create(const std::list<ImageFormat>& colors, ImageFormat depth);
        static Ptr Create(const std::list<ImageFormat>& colors, ImageFormat depth, const SR_MATH_NS::IVector2& size);
        static Ptr Create(const std::list<ImageFormat>& colors, ImageFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples);
        static Ptr Create(const std::list<ImageFormat>& colors, ImageFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples, uint32_t layersCount);
        static Ptr Create(const std::list<ImageFormat>& colors, ImageFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples, uint32_t layersCount, ImageAspect depthAspect);

    public:
        bool Update();
        bool Bind();

        bool BeginCmdBuffer();
        bool BeginCmdBuffer(const ClearColors& clearColors, std::optional<float_t> depth);
        bool BeginCmdBuffer(const SR_MATH_NS::FColor& clearColor, float_t depth);

        void SetViewportScissor();
        bool BeginRender();

        void EndCmdBuffer();
        void EndRender();

        void SetDirty();
        void SetSize(const SR_MATH_NS::IVector2& size);
        void SetDepthEnabled(bool depthEnabled);
        void SetSampleCount(uint8_t samples);
        void SetLayersCount(uint32_t layersCount);
        void SetDepthAspect(ImageAspect depthAspect);
        void SetFeatures(const FrameBufferFeatures& features);

        SR_NODISCARD bool IsFileResource() const noexcept override { return false; }
        SR_NODISCARD bool IsAllowedMultiInstance() const override { return true; }
        SR_NODISCARD uint8_t GetSamplesCount() const;
        SR_NODISCARD uint32_t GetColorLayersCount() const noexcept { return m_colors.size(); }
        SR_NODISCARD uint32_t GetLayersCount() const noexcept { return m_layersCount; }
        SR_NODISCARD ImageAspect GetDepthAspect() const noexcept { return m_depth.aspect; }
        SR_NODISCARD bool IsDepthEnabled() const { return m_depthEnabled; }
        SR_NODISCARD bool IsDirty() const { return m_dirty; }
        SR_NODISCARD bool IsValid() const { return m_frameBuffer != SR_ID_INVALID && !m_hasErrors && !IsDirty(); }
        SR_NODISCARD const FrameBufferFeatures& GetFeatures() const { return m_features; }

        SR_NODISCARD int32_t GetId() const;
        SR_NODISCARD int32_t GetColorTexture(uint32_t layer);
        SR_NODISCARD int32_t GetDepthTexture(int32_t layer = -1);

        SR_NODISCARD uint32_t GetWidth() const;
        SR_NODISCARD uint32_t GetHeight() const;
        SR_NODISCARD SR_MATH_NS::IVector2 GetSize() const { return m_size; }

        void FreeVMemory() override;
        uint64_t GetFileHash() const override;

    private:
        FrameBufferFeatures m_features;

        std::atomic<bool> m_dirty = true;
        std::atomic<bool> m_hasErrors = false;

        std::vector<ColorLayer> m_colors = { };
        DepthLayer m_depth = { };
        int32_t m_frameBuffer = SR_ID_INVALID;

        SR_MATH_NS::IVector2 m_size = { };

        uint8_t m_layersCount = 1;

        uint8_t m_sampleCount = 0;
        uint8_t m_currentSampleCount = 0;
        bool m_depthEnabled = true;

    };
}

#endif //SR_ENGINE_FRAMEBUFFER_H
```


