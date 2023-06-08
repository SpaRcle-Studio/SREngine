//
// Created by Monika on 06.05.2022.
//

#ifndef SRENGINE_FRAMEBUFFER_H
#define SRENGINE_FRAMEBUFFER_H

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>
#include <Utils/ResourceManager/IResource.h>

#include <Graphics/Memory/IGraphicsResource.h>

namespace SR_GRAPH_NS {
    class Environment;
}

namespace SR_GRAPH_NS::Types {
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
        using PipelinePtr = Environment*;
    private:
        Framebuffer();
        ~Framebuffer() override;

    public:
        static Ptr Create(uint32_t images, const SR_MATH_NS::IVector2& size);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth, const SR_MATH_NS::IVector2& size);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples, uint32_t layersCount);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth, const SR_MATH_NS::IVector2& size, uint8_t samples, uint32_t layersCount, ImageAspect depthAspect);

    public:
        bool Update();
        bool Bind();

        bool BeginCmdBuffer();
        bool BeginCmdBuffer(const ClearColors& clearColors, float_t depth);
        bool BeginCmdBuffer(const SR_MATH_NS::FColor& clearColor, float_t depth);

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
        SR_NODISCARD bool IsDepthEnabled() const { return m_depthEnabled; }
        SR_NODISCARD bool IsDirty() const { return m_dirty; }

        SR_NODISCARD int32_t GetId();
        SR_NODISCARD int32_t GetColorTexture(uint32_t layer);
        SR_NODISCARD int32_t GetDepthTexture() const;

        SR_NODISCARD uint32_t GetWidth() const;
        SR_NODISCARD uint32_t GetHeight() const;

        void FreeVideoMemory() override;
        uint64_t GetFileHash() const override;

    private:
        PipelinePtr m_pipeline = nullptr;

        std::atomic<bool> m_dirty = true;
        std::atomic<bool> m_hasErrors = false;

        ImageAspect m_depthAspect = ImageAspect::DepthStencil;

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

#endif //SRENGINE_FRAMEBUFFER_H
