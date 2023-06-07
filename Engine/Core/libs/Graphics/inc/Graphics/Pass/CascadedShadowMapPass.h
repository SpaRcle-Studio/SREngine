//
// Created by Monika on 06.06.2023.
//

#ifndef SRENGINE_CASCADEDSHADOWMAPPASS_H
#define SRENGINE_CASCADEDSHADOWMAPPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    class CascadedShadowMapPass : public ShaderOverridePass {
        using Super = ShaderOverridePass;
    public:
        CascadedShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent);

    public:
        bool Init() override;
        void DeInit() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    };
}

#endif //SRENGINE_CASCADEDSHADOWMAPPASS_H
