//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_TRANSPARENTPASS_H
#define SRENGINE_TRANSPARENTPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class TransparentPass : public IMeshClusterPass {
        using Super = IMeshClusterPass;
    public:
        explicit TransparentPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~TransparentPass() override = default;

    public:
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseUniforms(SR_GTYPES_NS::Shader* pShader) override;

    };
}

#endif //SRENGINE_TRANSPARENTPASS_H
