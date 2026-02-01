//
// Created by Monika on 01.02.2026.
//

#ifndef SR_ENGINE_UI_SCROLLBAR_H
#define SR_ENGINE_UI_SCROLLBAR_H

#include <Engine/stdInclude.h>

#include <Graphics/UI/Canvas.h>

#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/TransformRect.h>

namespace SR_CORE_UI_NS {
    SR_ENUM_NS_CLASS_T(ScrollbarDirection, uint8_t,
        LeftToRight,
        RightToLeft,
        BottomToTop,
        TopToBottom
    );

    /// @category(UI)
    class UIScrollbar : public SR_UTILS_NS::Component, public SR_GRAPH_NS::UI::IFindCanvasOwner {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
        enum class State : uint8_t {
            Idle,
            Hovered,
            Pressed
        };
    public:
        enum Axis : uint8_t {
            Horizontal = 0,
            Vertical = 1
        };
    public:
        void Update(float_t dt) override;

        void SetValue(float_t value);
        void SetSize(float_t size);
        void SetNumberOfSteps(uint32_t steps);

        SR_NODISCARD float_t GetValue() const noexcept;
        SR_NODISCARD float_t GetSize() const noexcept { return m_size; }
        SR_NODISCARD uint32_t GetNumberOfSteps() const noexcept { return m_numberOfSteps; }
        SR_NODISCARD Axis GetAxis() const noexcept;
        SR_NODISCARD bool IsReverseValue() const noexcept;

    private:
        void RefreshHandleLayout();
        bool OnBeginDrag(const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera);
        void OnDrag(const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera);

    private:
        State m_state = State::Idle;

        SR_UTILS_NS::TransformRect::Ptr m_handleRect;
        SR_UTILS_NS::TransformRect::Ptr m_containerRect;

    private:
        /// @property
        ScrollbarDirection m_direction = ScrollbarDirection::LeftToRight;
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

#endif //SR_ENGINE_UI_SCROLLBAR_H

