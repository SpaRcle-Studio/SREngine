//
// Created by Monika on 21.01.2023.
//

#ifndef SRENGINE_SHADEROVERRIDEPASS_H
#define SRENGINE_SHADEROVERRIDEPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
    class Mesh;
}

namespace SR_GRAPH_NS {
    class MeshCluster;

    class ShaderOverridePass : public BasePass, public IFramebufferPass {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = BasePass;
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
        void RenderInternal(const RenderScenePtr& pRenderScene);

        SR_NODISCARD virtual ShaderPtr GetShader(SR_SRSL_NS::ShaderType type) const;

        SR_NODISCARD bool IsDirectional() const noexcept { return m_isDirectional; }

        virtual bool DrawCluster(MeshCluster* pCluster);
        virtual void UpdateCluster(MeshCluster* pCluster);

    private:
        /// режим рендера без кадрового буффера, напрямую
        bool m_isDirectional = false;

        std::vector<std::pair<SR_SRSL_NS::ShaderType, ShaderPtr>> m_shaders;

    };
}

#endif //SRENGINE_SHADEROVERRIDEPASS_H
