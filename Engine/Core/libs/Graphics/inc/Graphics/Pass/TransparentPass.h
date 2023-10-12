//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_TRANSPARENTPASS_H
#define SRENGINE_TRANSPARENTPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class TransparentPass : public IMeshClusterPass {
        SR_REGISTER_LOGICAL_NODE(TransparentPass, Transparent Pass, { "Passes" })
        using Super = IMeshClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SRENGINE_TRANSPARENTPASS_H
