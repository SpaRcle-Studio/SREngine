//
// Created by Monika on 01.02.2026.
//

#ifndef SR_ENGINE_UI_SCROLL_RECT_H
#define SR_ENGINE_UI_SCROLL_RECT_H

#include <Engine/UI/UIScrollBar.h>

#include <Graphics/UI/Canvas.h>

#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/TransformRect.h>

namespace SR_CORE_UI_NS {
    /// @category(UI) @displayName(Scroll Rect)
    class UIScrollRect : public SR_UTILS_NS::Component, public SR_GRAPH_NS::UI::IFindCanvasOwner {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

        void SetContent(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pContent) { m_content.SetEntityId(pContent->GetEntityId()); }
        void SetViewport(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pViewport) { m_viewport.SetEntityId(pViewport->GetEntityId()); }
        void SetHorizontalScrollBar(const SR_HTYPES_NS::SharedPtr<UIScrollBar>& pScrollBar) { m_horizontalScrollBar.SetEntityId(pScrollBar->GetSceneObject()->GetEntityId()); }
        void SetVerticalScrollBar(const SR_HTYPES_NS::SharedPtr<UIScrollBar>& pScrollBar) { m_verticalScrollBar.SetEntityId(pScrollBar->GetSceneObject()->GetEntityId()); }

    private:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_content;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_viewport;
        /// @property
        SR_UTILS_NS::EntityRef<UIScrollBar> m_horizontalScrollBar;
        /// @property
        SR_UTILS_NS::EntityRef<UIScrollBar> m_verticalScrollBar;

    };
}

#endif //SR_ENGINE_UI_SCROLL_RECT_H
