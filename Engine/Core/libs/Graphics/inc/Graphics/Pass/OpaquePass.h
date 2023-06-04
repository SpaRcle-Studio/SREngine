//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_OPAQUEPASS_H
#define SRENGINE_OPAQUEPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class OpaquePass : public IMeshClusterPass {
        using Super = IMeshClusterPass;
    public:
        explicit OpaquePass(RenderTechnique* pTechnique, BasePass* pParent);
        ~OpaquePass() override = default;

    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseUniforms(SR_GTYPES_NS::Shader* pShader) override;

    };
}

#endif //SRENGINE_OPAQUEPASS_H
