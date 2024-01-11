//
// Created by Monika on 22.07.2022.
//

#ifndef SR_ENGINE_SWAPCHAINPASS_H
#define SR_ENGINE_SWAPCHAINPASS_H

#include <Utils/Math/Vector3.h>
#include <Graphics/Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    class SwapchainPass : public GroupPass {
        SR_REGISTER_LOGICAL_NODE(SwapchainPass, Swapchain Pass, { "Passes" })
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Render() override;
        void Update() override;
        void InitNode() override;

    private:
        float_t m_depth = 1.f;
        SR_MATH_NS::FColor m_color;

    };
}

#endif //SR_ENGINE_SWAPCHAINPASS_H
