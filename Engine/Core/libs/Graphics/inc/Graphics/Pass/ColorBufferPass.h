//
// Created by Monika on 10.10.2022.
//

#ifndef SRENGINE_COLORBUFFERPASS_H
#define SRENGINE_COLORBUFFERPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Environment/PipeLine.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class MeshCluster;

    class ColorBufferPass : public BasePass {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
    public:
        explicit ColorBufferPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~ColorBufferPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Init() override;
        void OnResize(const SR_MATH_NS::IVector2 &size) override;

        bool PreRender() override;
        bool Render() override;
        void Update() override;

        SR_NODISCARD SR_MATH_NS::FColor GetColor(float_t x, float_t y) const;

    private:
        void LoadSettings(const SR_XML_NS::Node& settingsNode);
        SR_NODISCARD ShaderPtr GetShader(SRSL::ShaderType type) const;

        bool DrawCluster(MeshCluster* pCluster);
        void UpdateCluster(MeshCluster* pCluster);

        void NextColor();

    private:
        bool m_directional = false;
        bool m_depthEnabled = true;

        SR_MATH_NS::IVector3 m_color;
        ShaderPtr m_shaders[3] = { };

        SR_MATH_NS::FVector2 m_preScale;

        FramebufferPtr m_framebuffer = nullptr;
        uint8_t m_samples = 0;

    };
}

#endif //SRENGINE_COLORBUFFERPASS_H
