//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_DEBUGPASS_H
#define SRENGINE_DEBUGPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class DebugPass : public IMeshClusterPass {
        using Super = IMeshClusterPass;
    public:
        explicit DebugPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~DebugPass() override = default;

    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SRENGINE_DEBUGPASS_H
