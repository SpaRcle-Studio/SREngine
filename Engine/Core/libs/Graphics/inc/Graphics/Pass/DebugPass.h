//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_DEBUGPASS_H
#define SRENGINE_DEBUGPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class DebugPass : public IMeshClusterPass {
        SR_REGISTER_LOGICAL_NODE(DebugPass, Debug Pass, { "Passes" })
        using Super = IMeshClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SRENGINE_DEBUGPASS_H
