//
// Created by innerviewer on 5/21/2023.
//

#ifndef SRENGINE_SHADOWMAPPASS_H
#define SRENGINE_SHADOWMAPPASS_H

#include <Graphics/Pass/PostProcessPass.h>
#include <Graphics/Pass/IFramebufferPass.h>

#include <Utils/Math/Matrix4x4.h>

namespace SR_GRAPH_NS {
    class ShadowMapPass : public ShaderOverridePass {
        using Super = ShaderOverridePass;
    public:
        ShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent);

    public:
        bool Init() override;
        void DeInit() override;

        bool Load(const SR_XML_NS::Node &passNode) override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    };
}

#endif //SRENGINE_SHADOWMAPPASS_H
