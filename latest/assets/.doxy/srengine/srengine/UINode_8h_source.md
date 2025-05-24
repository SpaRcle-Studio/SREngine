

# File UINode.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**UINode.h**](UINode_8h.md)

[Go to the documentation of this file](UINode_8h.md)


```C++
//
// Created by Monika on 17.05.2025.
//

#ifndef SR_GRAPHICS_UI_UI_NODE_H
#define SR_GRAPHICS_UI_UI_NODE_H

#include <Graphics/macros.h>

#include <Utils/Math/Rect.h>
#include <Utils/ECS/Node.h>

namespace SR_GRAPH_NS {
    class RenderScene;
}

namespace SR_GTYPES_NS {
    class Camera;
}

struct YGNode;

namespace SR_GRAPH_UI_NS {
    class UINode : public SR_UTILS_NS::Node {
        SR_CLASS()
        using Super = SR_UTILS_NS::Node;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<UINode>;

    public:
        UINode();
        ~UINode() override;

    public:
        virtual void Prepare(uint64_t& priority);
        virtual void Layout(const SR_MATH_NS::FRect& available) = 0;
        virtual void Compile();

        void OnParentChanged(const SR_UTILS_NS::SceneObject::Ptr& pOldParent) override;

        SR_NODISCARD virtual SR_MATH_NS::FVector2 CalculateContentSize() const = 0;
        SR_NODISCARD SR_UTILS_NS::ECSNodeType GetNodeType() const noexcept override;
        SR_NODISCARD const SR_MATH_NS::FRect& GetFinalRect() const noexcept { return m_finalRect; }
        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetMatrix() const noexcept override;
        SR_NODISCARD SR_MATH_NS::FVector4 GetNDCVector() const noexcept;
        SR_NODISCARD uint64_t GetNodePriority() const noexcept override { return m_priority; }

        SR_NODISCARD SR_GTYPES_NS::Camera* GetCamera() const;
        SR_NODISCARD RenderScene* TryGetRenderScene() const;
        SR_NODISCARD RenderScene* GetRenderScene() const;

        SR_NODISCARD const SR_MATH_NS::FVector2& GetViewportSize() const noexcept { return m_viewportSize; }

        void SetViewportSize(const SR_MATH_NS::FVector2& size) noexcept;

    protected:
        SR_NODISCARD YGNode* GetYGNode() const noexcept { return m_implNode; }

    protected:
        YGNode* m_implNode = nullptr;

        uint64_t m_priority = 0;

        SR_MATH_NS::FRect m_finalRect;
        bool m_hasParent = false;
        SR_UTILS_NS::StringAtom m_parentName;

        SR_MATH_NS::FVector2 m_viewportSize;

        mutable SR_MATH_NS::Matrix4x4 m_matrix;

    protected:
        mutable RenderScene* m_renderScene = nullptr;

    };
}

#endif //SR_GRAPHICS_UI_UI_NODE_H
```


