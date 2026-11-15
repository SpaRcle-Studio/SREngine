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
    class UIScrollRect : public UIControl {
        SR_CLASS()
    public:
        void AfterLayout() override;
        void PointerDown(const SR_UTILS_NS::PointerEvent& event) override;
        bool CanDrag() const override { return true; }
        void PointerDrag(const SR_UTILS_NS::PointerEvent& event) override;
        bool Scroll(const SR_MATH_NS::FVector2& delta) override;

        /// @method
        void SetNormalizedPosition(const SR_MATH_NS::FVector2& position);
        /// @method @evaluate
        SR_MATH_NS::FVector2 GetNormalizedPosition() const noexcept { return m_normalizedPosition; }

        void SetContent(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pContent) { m_content.SetEntityId(pContent ? pContent->GetEntityId() : SR_UTILS_NS::SR_INVALID_ENTITY_ID); }
        void SetViewport(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pViewport) { m_viewport.SetEntityId(pViewport ? pViewport->GetEntityId() : SR_UTILS_NS::SR_INVALID_ENTITY_ID); }
        void SetHorizontalScrollBar(const SR_HTYPES_NS::SharedPtr<UIScrollBar>& pScrollBar) { m_horizontalScrollBar.SetEntityId(pScrollBar ? pScrollBar->GetEntityId() : SR_UTILS_NS::SR_INVALID_ENTITY_ID); }
        void SetVerticalScrollBar(const SR_HTYPES_NS::SharedPtr<UIScrollBar>& pScrollBar) { m_verticalScrollBar.SetEntityId(pScrollBar ? pScrollBar->GetEntityId() : SR_UTILS_NS::SR_INVALID_ENTITY_ID); }

    private:
        SR_MATH_NS::FVector2 m_normalizedPosition;
        SR_MATH_NS::FVector2 m_dragStart;
        SR_MATH_NS::FVector2 m_dragNormalized;
        SR_MATH_NS::FVector2 m_overflow;
        /// @property
        float_t m_scrollSensitivity = 0.1f;
        /// @property
        bool m_horizontal = true;
        /// @property
        bool m_vertical = true;
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
