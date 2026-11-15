//
// Created by Monika on 01.02.2026.
//

#ifndef SR_ENGINE_UI_SCROLL_BAR_H
#define SR_ENGINE_UI_SCROLL_BAR_H

#include <Engine/UI/UIControl.h>

#include <Graphics/UI/Canvas.h>

namespace SR_UTILS_NS {
    class TransformRect;
    class SceneObject;
}

namespace SR_CORE_UI_NS {
    SR_ENUM_NS_CLASS_T(ScrollBarDirection, uint8_t,
        LeftToRight,
        RightToLeft,
        BottomToTop,
        TopToBottom
    );

    /// @category(UI) @displayName(Scroll Bar)
    class UIScrollBar : public UIControl {
        SR_CLASS()
    public:
        enum Axis : uint8_t {
            Horizontal = 0,
            Vertical = 1
        };
    public:
        void PointerDown(const SR_UTILS_NS::PointerEvent& event) override;
        bool CanDrag() const override { return true; }
        bool AcceptsButton(SR_UTILS_NS::PointerButton button) const override;
        void PointerDrag(const SR_UTILS_NS::PointerEvent& event) override;
        bool Navigate(int32_t direction) override;
        void AfterLayout() override;

        /// @method
        void SetValue(float_t value);
        /// @method
        void SetSize(float_t size);
        void SetNumberOfSteps(uint32_t steps);
        void SetDirection(ScrollBarDirection direction) { m_direction = direction; }
        void SetHandle(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pHandle);

        /// @method @evaluate
        SR_NODISCARD float_t GetValue() const noexcept;
        SR_NODISCARD float_t GetSize() const noexcept { return m_size; }
        SR_NODISCARD uint32_t GetNumberOfSteps() const noexcept { return m_numberOfSteps; }
        SR_NODISCARD Axis GetAxis() const noexcept;
        SR_NODISCARD bool IsReverseValue() const noexcept;

    private:
        void RefreshHandleLayout();
        void OnDrag(SR_GRAPH_UI_NS::Canvas& canvas, const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera);

    private:
        float_t m_dragOffset = 0.f;

        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::TransformRect> m_handleRect;
        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::TransformRect> m_containerRect;

    private:
        /// @property
        ScrollBarDirection m_direction = ScrollBarDirection::LeftToRight;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_handle;

        /// @property @setter(SetValue)
        float_t m_value = 0.f;
        /// @property @setter(SetSize)
        float_t m_size = 0.5f;
        /// @property @setter(SetNumberOfSteps)
        uint32_t m_numberOfSteps = 0;

        /// @property @group(Mouse Events)
        bool m_leftClick = true;
        /// @property @group(Mouse Events)
        bool m_rightClick = false;
        /// @property @group(Mouse Events)
        bool m_middleClick = false;

    };
}

#endif //SR_ENGINE_UI_SCROLL_BAR_H

