//
// Created by Monika on 06.05.2022.
//

#ifndef SRENGINE_FRAMEBUFFER_H
#define SRENGINE_FRAMEBUFFER_H

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>
#include <Utils/ResourceManager/IResource.h>
#include <Memory/IGraphicsResource.h>

namespace SR_GRAPH_NS::Types {
    class Shader;
}

namespace SR_GTYPES_NS {
    class RenderTexture;

    class Framebuffer : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
    public:
        using Ptr = Framebuffer*;
        using Super = SR_UTILS_NS::IResource;
    private:
        Framebuffer();
        ~Framebuffer() override;

    public:
        static Ptr Create(uint32_t images, const SR_MATH_NS::IVector2& size);
        static Ptr Create(uint32_t images, const SR_MATH_NS::IVector2& size, const SR_UTILS_NS::Path& shaderPath);
        static Ptr Create(const std::list<ColorFormat>& colors, DepthFormat depth, const SR_MATH_NS::IVector2& size, const SR_UTILS_NS::Path& shaderPath);

    public:
        bool Bind();
        void Draw();

        bool BeginRender();
        void EndRender();

        void SetSize(const SR_MATH_NS::IVector2& size);

        SR_NODISCARD int32_t GetId();

        void FreeVideoMemory() override;

    protected:
        void OnResourceUpdated(IResource* pResource, int32_t deep) override;

    private:
        bool Init();
        bool OnResize();
        bool InitShader();

    private:
        Shader*                 m_shader         = nullptr;

        bool                    m_isInit         = false;
        bool                    m_dynamicScaling = false;
        std::atomic<bool>       m_hasErrors      = false;
        std::atomic<bool>       m_needResize     = false;
        std::atomic<bool>       m_dirtyShader    = false;

        std::vector<ColorLayer> m_colors         = { };
        DepthLayer              m_depth          = { };
        int32_t                 m_frameBuffer    = SR_ID_INVALID;
        int32_t                 m_virtualUBO     = SR_ID_INVALID;

        SR_MATH_NS::IVector2    m_size           = { };
        SR_UTILS_NS::Path       m_shaderPath     = SR_UTILS_NS::Path();

    };
}

#endif //SRENGINE_FRAMEBUFFER_H
