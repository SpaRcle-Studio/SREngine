//
// Created by Monika on 05.05.2023.
//

#include <Graphics/Animations/AnimationGraph.h>

namespace SR_ANIMATIONS_NS {
    AnimationGraph::AnimationGraph(IAnimationDataSet* pParent)
        : Super(pParent)
    {
        AddNode<AnimationGraphNodeFinal>();
    }

    AnimationGraph::~AnimationGraph() {
        for (auto&& pNode : m_nodes) {
            delete pNode;
        }
    }

    uint64_t AnimationGraph::GetNodeIndex(const AnimationGraphNode* pNode) const {
        if (auto&& pIt = m_indices.find(const_cast<AnimationGraphNode*>(pNode)); pIt != m_indices.end()) {
            return pIt->second;
        }

        SRHalt("Node not found!");

        return SR_ID_INVALID;
    }

    AnimationGraphNode* AnimationGraph::GetFinal() const {
        return m_nodes.front();
    }

    void AnimationGraph::Update(const UpdateContext& context) {
        GetFinal()->Update(context, AnimationLink(SR_ID_INVALID, SR_ID_INVALID));
    }

    AnimationGraphNode* AnimationGraph::GetNode(uint64_t index) const {
        if (index < m_nodes.size()) {
            return m_nodes.at(index);
        }

        SRHalt("Out of range!");

        return nullptr;
    }
}