//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_OPAQUEPASS_H
#define SRENGINE_OPAQUEPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class OpaquePass : public IMeshClusterPass {
        SR_REGISTER_LOGICAL_NODE(OpaquePass, Opaque Pass, { "Passes" })
        using Super = IMeshClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;

    };
}

#endif //SRENGINE_OPAQUEPASS_H
