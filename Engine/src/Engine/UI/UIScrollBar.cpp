//
// Created by Monika on 01.02.2026.
//

#include <Engine/UI/UIScrollBar.h>

#include <Graphics/UI/Utils.h>
#include <Graphics/Window/Window.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/ECS/SceneObject.h>

#include <Codegen/UIScrollBar.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIScrollBar::Update(float_t dt) {
        m_handleRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.GetRaw());
        m_containerRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle ? m_handle.Get()->GetParent().Get() : nullptr);
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        auto&& pThisTransformRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(GetSceneObject().Get());

        if (!m_handleRect || !m_containerRect || !pThisTransformRect) {
            return;
        }

        SR_UTILS_NS::TransformRect* pContainerRect = nullptr;
        pContainerRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.Get()->GetParent().Get());
        if (!pContainerRect) {
            return;
        }

        auto&& input = SR_UTILS_NS::Input::Instance();

        const SR_MATH_NS::FVector2 uiMousePos = pCanvas->ScreenToCanvasSpace(input.GetMousePos());

        const bool isDown = m_leftClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)
            || m_rightClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseRight)
            || m_middleClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseMiddle);

        if (isDown && m_state != State::Pressed && OnBeginDrag(*pCanvas, uiMousePos, pCanvas->GetCamera())) {
            m_state = State::Pressed;
        }
        else if (m_state == State::Pressed) {
            const bool isUp = m_leftClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)
                              || m_rightClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseRight)
                              || m_middleClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseMiddle);
            if (isUp) {
                m_state = State::Hovered;
            }

            OnDrag(*pCanvas, uiMousePos, pCanvas->GetCamera());
        }
        else {
            m_state = State::Idle;
        }

        Super::Update(dt);
    }

    void UIScrollBar::SetValue(float_t value) {
        m_value = SR_CLAMP01(value);
        RefreshHandleLayout();
    }

    void UIScrollBar::SetSize(float_t size) {
        m_size = SR_CLAMP(size, 0.001f, 1.f);
        RefreshHandleLayout();
    }

    void UIScrollBar::SetNumberOfSteps(uint32_t steps) {
        m_numberOfSteps = steps;
        RefreshHandleLayout();
    }

    void UIScrollBar::RefreshHandleLayout() {
        SR_TRACY_ZONE;

        if (!IsAttached()) {
            return;
        }

        auto&& pHandleTransform = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.Get().Get());
        if (!pHandleTransform) {
            return;
        }

        SR_UTILS_NS::RectAnchors anchors;
        anchors.min = SR_MATH_NS::FVector2::Zero();
        anchors.max = SR_MATH_NS::FVector2::One();

        const uint8_t axis = GetAxis();
        const float_t value = SR_CLAMP01(GetValue());
        const float_t movement = value * (1.f - m_size);

        if (IsReverseValue()) {
            anchors.min[axis] = 1.f - movement - m_size;
            anchors.max[axis] = 1.f - movement;
        }
        else {
            anchors.min[axis] = movement;
            anchors.max[axis] = movement + m_size;
        }

        pHandleTransform->SetAnchors(anchors);
    }

    UIScrollBar::Axis UIScrollBar::GetAxis() const noexcept {
        return (m_direction == ScrollBarDirection::LeftToRight || m_direction == ScrollBarDirection::RightToLeft) ? Axis::Horizontal : Axis::Vertical;
    }

    bool UIScrollBar::IsReverseValue() const noexcept {
        return m_direction == ScrollBarDirection::RightToLeft || m_direction == ScrollBarDirection::TopToBottom;
    }

    float_t UIScrollBar::GetValue() const noexcept {
        if (m_numberOfSteps > 1) {
            return SR_MATH_NS::Round(m_value * (m_numberOfSteps - 1)) / (m_numberOfSteps - 1);
        }
        return m_value;
    }

    bool UIScrollBar::OnBeginDrag(SR_GRAPH_UI_NS::Canvas& canvas, const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera) {
        if (auto&& pTransform = GetTransformAs<SR_UTILS_NS::TransformRect>()) {
            if (canvas.LayoutToCanvasRect(pTransform->GetLayoutRect()).Contains(screenPosition)) {
                return true;
            }
        }

        return false;
    }

    void UIScrollBar::OnDrag(SR_GRAPH_UI_NS::Canvas& canvas, const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera) {
        auto&& containerRect = canvas.LayoutToCanvasRect(m_containerRect->GetLayoutRect());
        auto&& handleRect = canvas.LayoutToCanvasRect(m_handleRect->GetLayoutRect());

        SR_MATH_NS::FVector2 localCursor = screenPosition;
        auto&& handleCenterRelativeToContainerCorner = localCursor - containerRect.XY();
        auto&& handleCorner = handleCenterRelativeToContainerCorner - (handleRect.Size() - m_handleRect->GetSizeDelta()) * 0.5f;

        const uint8_t axis = GetAxis();
        float parentSize = axis == 0 ? containerRect.Width() : containerRect.Height();
        float remainingSize = parentSize * (1.f - GetSize());
        if (remainingSize <= 0.f) {
            return;
        }

        switch (m_direction) {
            case ScrollBarDirection::LeftToRight:
                SetValue(SR_CLAMP01(handleCorner.x / remainingSize));
                break;
            case ScrollBarDirection::RightToLeft:
                SetValue(SR_CLAMP01(1.f - (handleCorner.x / remainingSize)));
                break;
            case ScrollBarDirection::BottomToTop:
                SetValue(SR_CLAMP01(handleCorner.y / remainingSize));
                break;
            case ScrollBarDirection::TopToBottom:
                SetValue(SR_CLAMP01(1.f - (handleCorner.y / remainingSize)));
                break;
            default:
                SRHalt("Unexpected scrollbar direction!");
                break;
        }
    }
}