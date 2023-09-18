//
// Created by Monika on 13.07.2023.
//

#ifndef SRENGINE_VARIANCESHADOWMAPPASS_H
#define SRENGINE_VARIANCESHADOWMAPPASS_H

#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    class VarianceShadowMapPass : public CascadedShadowMapPass {
        using Super = CascadedShadowMapPass;
    public:
        VarianceShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent);

    };
}


#endif //SRENGINE_VARIANCESHADOWMAPPASS_H
