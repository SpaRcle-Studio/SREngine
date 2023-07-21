//
// Created by Monika on 21.01.2023.
//

#ifndef SRENGINE_SHADEROVERRIDEPASS_H
#define SRENGINE_SHADEROVERRIDEPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>
#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class MeshCluster;

    class ShaderOverridePass : public IMeshClusterPass, public IFramebufferPass {
        using Super = IMeshClusterPass;
    public:
        explicit ShaderOverridePass(RenderTechnique* pTechnique, BasePass* pParent);
        ~ShaderOverridePass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Init() override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;

        bool Render() override;
        void Update() override;

    protected:
        SR_NODISCARD ShaderPtr GetShader(SR_SRSL_NS::ShaderType type) const override;
        SR_NODISCARD bool IsDirectional() const noexcept { return m_isDirectional; }
        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

        void UseSharedUniforms(ShaderPtr pShader) override;

    private:
        /// режим рендера без кадрового буффера, напрямую
        bool m_isDirectional = false;

        std::vector<std::pair<SR_SRSL_NS::ShaderType, ShaderPtr>> m_shaders;

    };
}

#endif //SRENGINE_SHADEROVERRIDEPASS_H
