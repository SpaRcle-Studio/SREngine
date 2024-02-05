//
// Created by Monika on 06.05.2022.
//

#ifndef SR_ENGINE_FRAMEBUFFER_H
#define SR_ENGINE_FRAMEBUFFER_H

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>
#include <Utils/ResourceManager/IResource.h>

#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GTYPES_NS {
    class RenderTexture;

    /**
     * \Usage Bing -> BeginRenderBuffer -> BeginRender -> EndRender -> EndRenderBuffer
     * */
    class Framebuffer : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
    public:
        using Ptr = Framebuffer*;
        using Super = SR_UTILS_NS::IResource;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
    private:
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

        SR_NODISCARD bool IsFileResource() const noexcept override { return false; }
        SR_NODISCARD uint8_t GetSamplesCount() const;
        SR_NODISCARD uint32_t GetColorLayersCount() const noexcept { return m_colors.size(); }
        SR_NODISCARD uint32_t GetLayersCount() const noexcept { return m_layersCount; }
        SR_NODISCARD ImageAspect GetDepthAspect() const noexcept { return m_depth.aspect; }
        SR_NODISCARD bool IsDepthEnabled() const { return m_depthEnabled; }
        SR_NODISCARD bool IsDirty() const { return m_dirty; }

        SR_NODISCARD int32_t GetId();
        SR_NODISCARD int32_t GetColorTexture(uint32_t layer);
        SR_NODISCARD int32_t GetDepthTexture(int32_t layer = -1);

        SR_NODISCARD uint32_t GetWidth() const;
        SR_NODISCARD uint32_t GetHeight() const;
        SR_NODISCARD SR_MATH_NS::IVector2 GetSize() const { return m_size; }

        void FreeVideoMemory() override;
        uint64_t GetFileHash() const override;

    private:
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
