//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONGRAPH_H
#define SRENGINE_ANIMATIONGRAPH_H

#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph;

    struct AnimationLink {
        uint16_t m_targetNodeIndex = 0;
        uint16_t m_targetPinIndex = 0;
    };

    class AnimationGraphNode : public SR_UTILS_NS::NonCopyable {
    private:
        AnimationGraph* m_graph = nullptr;

        std::vector<AnimationLink> m_inputPins;
        std::vector<AnimationLink> m_outputPins;

        AnimationGraphNodeType m_type = AnimationGraphNodeType::None;

    };

    class AnimationGraphNodeFinal : public AnimationGraphNode {

    };

    class AnimationGraphNodeStateMachine : public AnimationGraphNode {

    };

    class AnimationGraph : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
        using Hash = uint64_t;
    private:
        /// первая нода всегда является Final
        std::vector<AnimationGraphNode*> m_nodes;

    };
}

#endif //SRENGINEANIMATIONRGRAPH_H
