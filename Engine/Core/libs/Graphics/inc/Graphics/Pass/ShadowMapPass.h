//
// Created by innerviewer on 5/21/2023.
//

#ifndef SRENGINE_SHADOWMAPPASS_H
#define SRENGINE_SHADOWMAPPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    class ShadowMapPass : public ShaderOverridePass {
        SR_REGISTER_LOGICAL_NODE(ShadowMapPass, Shadow Map Pass, { "Passes" })
        using Super = ShaderOverridePass;
    public:
        bool Init() override;
        void DeInit() override;

        bool Render() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD SR_MATH_NS::Matrix4x4 GetLightSpaceMatrix() const noexcept { return m_lightSpaceMatrix; }

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    private:
        SR_MATH_NS::Matrix4x4 m_lightSpaceMatrix;

    };
}

#endif //SRENGINE_SHADOWMAPPASS_H
