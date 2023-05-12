//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONGRAPH_H
#define SRENGINE_ANIMATIONGRAPH_H

#include <Graphics/Animations/AnimationGraphNode.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
        using Hash = uint64_t;
        using Super = IAnimationDataSet;
    public:
        explicit AnimationGraph(IAnimationDataSet* pParent);
        ~AnimationGraph() override;

    public:
        SR_NODISCARD AnimationGraphNode* GetNode(uint64_t index) const;
        SR_NODISCARD uint64_t GetNodeIndex(const AnimationGraphNode* pNode) const;
        SR_NODISCARD AnimationGraphNode* GetFinal() const;

        void Update(const UpdateContext& context);

        template<class T, typename... Args> T* AddNode(Args&& ...args) {
            auto&& pNode = new T(this, std::forward<Args>(args)...);
            m_indices.insert(std::make_pair(pNode, static_cast<uint32_t>(m_nodes.size())));
            m_nodes.emplace_back(pNode);
            return pNode;
        }

    private:
        /// первая нода всегда является Final
        std::vector<AnimationGraphNode*> m_nodes;
        ska::flat_hash_map<AnimationGraphNode*, uint32_t> m_indices;

    };
}

#endif //SRENGINEANIMATIONRGRAPH_H
