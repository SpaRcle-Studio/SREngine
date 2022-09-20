//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_TRANSPARENTPASS_H
#define SRENGINE_TRANSPARENTPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class TransparentPass : public BasePass {
    public:
        explicit TransparentPass(RenderTechnique* pTechnique);
        ~TransparentPass() override = default;

    public:
        bool PreRender() override;
        bool Render() override;
        void Update() override;

    };
}

#endif //SRENGINE_TRANSPARENTPASS_H
