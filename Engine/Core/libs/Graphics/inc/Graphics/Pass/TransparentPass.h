//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_TRANSPARENTPASS_H
#define SR_ENGINE_TRANSPARENTPASS_H

#include <Graphics/Pass/IMesh3DClusterPass.h>

namespace SR_GRAPH_NS {
    class TransparentPass : public IMesh3DClusterPass {
        SR_REGISTER_LOGICAL_NODE(TransparentPass, Transparent Pass, { "Passes" })
        using Super = IMesh3DClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SR_ENGINE_TRANSPARENTPASS_H
