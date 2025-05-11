

# File AnimationGraph.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationGraph.h**](AnimationGraph_8h.md)

[Go to the documentation of this file](AnimationGraph_8h.md)


```C++
//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONGRAPH_H
#define SR_ENGINE_ANIMATIONGRAPH_H

#include <Graphics/Animations/AnimationGraphNode.h>

namespace SR_ANIMATIONS_NS {
    class Animator;

    class AnimationGraph : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
        using Hash = uint64_t;
        using Super = IAnimationDataSet;
    public:
        explicit AnimationGraph(Animator* pAnimator);
        ~AnimationGraph() override;

    public:
        SR_NODISCARD static AnimationGraph* Load(Animator* pAnimator, const SR_UTILS_NS::Path& path);

        SR_NODISCARD AnimationGraphNode* GetNode(uint64_t index) const;
        SR_NODISCARD uint64_t GetNodeIndex(const AnimationGraphNode* pNode) const;
        SR_NODISCARD AnimationGraphNode* GetFinal() const;
        SR_NODISCARD bool IsStateActive(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD uint32_t GetNodesCount() const noexcept { return static_cast<uint32_t>(m_nodes.size()); }
        SR_NODISCARD const std::vector<AnimationGraphNode*>& GetNodes() const noexcept { return m_nodes; }
        SR_NODISCARD const SR_UTILS_NS::Path& GetPath() const noexcept { return m_path; }

        void Update(UpdateContext& context);

        template<class T, typename... Args> T* CreateNode(Args&& ...args) {
            return AddNode(new T(std::forward<Args>(args)...));
        }

        template<class T> T* AddNode(T* pNode) {
            SR_STATIC_ASSERT2((std::is_base_of_v<AnimationGraphNode, T>), "T must be derived from AnimationGraphNode");
            m_indices.insert(std::make_pair(pNode, static_cast<uint32_t>(m_nodes.size())));
            m_nodes.emplace_back(pNode);
            pNode->SetGraph(this);
            return pNode;
        }

    private:
        void Apply(AnimationPose* pPose);
        void Compile();

    public:
        SR_UTILS_NS::Path m_path;

        bool m_isCompiled = false;

        Animator* m_pAnimator = nullptr;

        std::vector<SR_UTILS_NS::GameObject::Ptr> m_gameObjects;

        std::vector<AnimationGraphNode*> m_nodes;
        ska::flat_hash_map<AnimationGraphNode*, uint32_t> m_indices;

    };
}

#endif //SRENGINEANIMATIONRGRAPH_H
```


