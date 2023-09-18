//
// Created by Monika on 06.05.2023.
//

#include <Graphics/Animations/AnimationGraphNode.h>

namespace SR_ANIMATIONS_NS {
    AnimationGraphNode::AnimationGraphNode(AnimationGraph* pGraph, uint16_t input, uint16_t output)
        : m_graph(pGraph)
    {
        m_inputPins.resize(input);
        m_outputPins.resize(output);
    }

    void AnimationGraphNode::AddInput(AnimationGraphNode* pNode, uint16_t sourcePinIndex, uint16_t targetPinIndex) {
        if (!pNode) {
            SRHalt("Invalid node!");
            return;
        }

        if (sourcePinIndex >= m_inputPins.size()) {
            SRHalt("Out of range!");
            return;
        }

        if (targetPinIndex >= pNode->m_outputPins.size()) {
            SRHalt("Out of range!");
            return;
        }

        m_inputPins[sourcePinIndex] = AnimationLink(pNode->GetIndex(), targetPinIndex);
        pNode->m_outputPins[targetPinIndex] = AnimationLink(GetIndex(), sourcePinIndex);
    }

    uint64_t AnimationGraphNode::GetIndex() const {
        return m_graph->GetNodeIndex(this);
    }

    void AnimationGraphNodeFinal::Update(const UpdateContext& context, const AnimationLink& from) {
        SR_TRACY_ZONE;

        if (m_inputPins.front().has_value()) {
            auto&& pNode = m_graph->GetNode(m_inputPins.front().value().m_targetNodeIndex);
            if (pNode) {
                pNode->Update(context, AnimationLink(0, 0));
            }
        }
    }

    void AnimationGraphNodeStateMachine::Update(const UpdateContext& context, const AnimationLink& from) {
        SR_TRACY_ZONE;

        if (m_stateMachine) {
            m_stateMachine->Update(context);
        }
    }

    AnimationGraphNodeStateMachine::AnimationGraphNodeStateMachine(AnimationGraph *pGraph)
        : Super(pGraph, 0, 1)
        , m_stateMachine(new AnimationStateMachine(dynamic_cast<IAnimationDataSet*>(pGraph)))
    { }

    AnimationGraphNodeStateMachine::~AnimationGraphNodeStateMachine() {
        SR_SAFE_DELETE_PTR(m_stateMachine);
    }
}