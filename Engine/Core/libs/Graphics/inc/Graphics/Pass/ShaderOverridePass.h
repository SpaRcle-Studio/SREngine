//
// Created by Monika on 21.01.2023.
//

#ifndef SR_ENGINE_SHADER_OVERRIDE_PASS_H
#define SR_ENGINE_SHADER_OVERRIDE_PASS_H

#include <Graphics/Pass/IMesh3DClusterPass.h>
#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class MeshCluster;

    class ShaderOverridePass : public IMesh3DClusterPass, public IFramebufferPass {
        SR_REGISTER_LOGICAL_NODE(ShaderOverridePass, Shader Override Pass, { "Passes" })
        using Super = IMesh3DClusterPass;
    public:
        ~ShaderOverridePass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Init() override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;

        bool Render() override;
        void Update() override;

    protected:
        SR_NODISCARD ShaderPtr GetShader(SR_SRSL_NS::ShaderType type) const override;
        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

        void UseSharedUniforms(ShaderPtr pShader) override;

    private:
        std::vector<std::pair<SR_SRSL_NS::ShaderType, ShaderPtr>> m_shaders;

    };
}

#endif //SR_ENGINE_SHADEROVERRIDEPASS_H
