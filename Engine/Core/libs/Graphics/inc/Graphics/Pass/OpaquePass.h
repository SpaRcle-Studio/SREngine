//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_OPAQUEPASS_H
#define SR_ENGINE_OPAQUEPASS_H

#include <Graphics/Pass/IMesh3DClusterPass.h>

namespace SR_GRAPH_NS {
    class OpaquePass : public IMesh3DClusterPass {
        SR_REGISTER_LOGICAL_NODE(OpaquePass, Opaque Pass, { "Passes" })
        using Super = IMesh3DClusterPass;
    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;

    };
}

#endif //SR_ENGINE_OPAQUEPASS_H
