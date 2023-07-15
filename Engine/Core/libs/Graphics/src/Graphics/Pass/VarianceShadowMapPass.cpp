//
// Created by Monika on 13.07.2023.
//

#include <Graphics/Pass/VarianceShadowMapPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(VarianceShadowMapPass);

    VarianceShadowMapPass::VarianceShadowMapPass(RenderTechnique *pTechnique, BasePass *pParent)
        : Super(pTechnique, pParent)
    { }
}