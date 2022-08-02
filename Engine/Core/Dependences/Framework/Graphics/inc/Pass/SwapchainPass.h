//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_SWAPCHAINPASS_H
#define SRENGINE_SWAPCHAINPASS_H

#include <Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    class SwapchainPass : public GroupPass {
    public:
        explicit SwapchainPass(RenderTechnique* pTechnique);
        ~SwapchainPass() override = default;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Render() override;
        void Update() override;

    };
}

#endif //SRENGINE_SWAPCHAINPASS_H
