//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_SWAPCHAINPASS_H
#define SRENGINE_SWAPCHAINPASS_H

#include <Utils/Math/Vector3.h>
#include <Graphics/Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    class SwapchainPass : public GroupPass {
    public:
        explicit SwapchainPass(RenderTechnique* pTechnique);
        ~SwapchainPass() override = default;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Render() override;
        void Update() override;

    private:
        float_t m_depth = 1.f;
        SR_MATH_NS::FColor m_color;

    };
}

#endif //SRENGINE_SWAPCHAINPASS_H
