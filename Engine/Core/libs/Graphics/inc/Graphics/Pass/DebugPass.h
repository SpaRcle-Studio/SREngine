//
// Created by Monika on 19.09.2022.
//

#ifndef SRENGINE_DEBUGPASS_H
#define SRENGINE_DEBUGPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class DebugPass : public BasePass {
    public:
        explicit DebugPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~DebugPass() override = default;

    public:
        bool PreRender() override;
        bool Render() override;
        void Update() override;

    };
}

#endif //SRENGINE_DEBUGPASS_H
