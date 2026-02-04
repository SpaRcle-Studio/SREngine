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
