//
// Created by Monika on 01.02.2026.
//

#include <Engine/UI/UIScrollbar.h>

#include <Graphics/UI/Utils.h>
#include <Graphics/Window/Window.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/ECS/TransformRect.h>

#include <Codegen/UIScrollbar.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIScrollbar::Update(float_t dt) {
        m_handleRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.GetRaw());
        m_containerRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle ? m_handle.Get()->GetParent().Get() : nullptr);
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        auto&& pWindow = pCanvas ? pCanvas->GetWindow() : nullptr;
        auto&& pThisTransformRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(GetSceneObject().Get());

        if (!m_handleRect || !m_containerRect || !pWindow || !pThisTransformRect) {
            return;
        }

        SR_UTILS_NS::TransformRect* pContainerRect = nullptr;
        pContainerRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.Get()->GetParent().Get());
        if (!pContainerRect) {
            return;
        }

        auto&& input = SR_UTILS_NS::Input::Instance();

        SR_MATH_NS::FVector2 mousePos = pWindow->ScreenToClient(input.GetMousePos().CastToInt()).CastToFloat();
        const SR_MATH_NS::FRect viewportRect = pCanvas->GetViewportRect();

        SR_MATH_NS::FVector2 uiMousePos = (mousePos - viewportRect.XY()) / viewportRect.Size() * pCanvas->GetSize().CastToFloat();
        uiMousePos.y = pCanvas->GetSize().CastToFloat().y - uiMousePos.y;

        const bool isDown = m_leftClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)
            || m_rightClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseRight)
            || m_middleClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseMiddle);

        if (isDown && m_state != State::Pressed && OnBeginDrag(uiMousePos, pCanvas->GetCamera())) {
            m_state = State::Pressed;
        }
        else if (m_state == State::Pressed) {
            const bool isUp = m_leftClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)
                              || m_rightClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseRight)
                              || m_middleClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseMiddle);
            if (isUp) {
                m_state = State::Hovered;
            }

            OnDrag(uiMousePos, pCanvas->GetCamera());
        }
        else {
            m_state = State::Idle;
        }

        Super::Update(dt);
    }

    void UIScrollbar::SetValue(float_t value) {
        m_value = SR_CLAMP01(value);
        RefreshHandleLayout();
    }

    void UIScrollbar::SetSize(float_t size) {
        m_size = SR_CLAMP(size, 0.001f, 1.f);
        RefreshHandleLayout();
    }

    void UIScrollbar::SetNumberOfSteps(uint32_t steps) {
        m_numberOfSteps = steps;
        RefreshHandleLayout();
    }

    void UIScrollbar::RefreshHandleLayout() {
        SR_TRACY_ZONE;

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

    UIScrollbar::Axis UIScrollbar::GetAxis() const noexcept {
        return (m_direction == ScrollbarDirection::LeftToRight || m_direction == ScrollbarDirection::RightToLeft) ? Axis::Horizontal : Axis::Vertical;
    }

    bool UIScrollbar::IsReverseValue() const noexcept {
        return m_direction == ScrollbarDirection::RightToLeft || m_direction == ScrollbarDirection::TopToBottom;
    }

    float_t UIScrollbar::GetValue() const noexcept {
        if (m_numberOfSteps > 1) {
            return SR_MATH_NS::Round(m_value * (m_numberOfSteps - 1)) / (m_numberOfSteps - 1);
        }
        return m_value;
    }

    bool UIScrollbar::OnBeginDrag(const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera) {
        if (auto&& pTransform = GetTransformAs<SR_UTILS_NS::TransformRect>()) {
            if (pTransform->GetLayoutRect().Contains(screenPosition)) {
                return true;
            }
        }

        return false;
    }

    void UIScrollbar::OnDrag(const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera) {
        SR_MATH_NS::FVector2 localCursor = screenPosition;
        auto&& handleCenterRelativeToContainerCorner = localCursor - m_containerRect->GetLayoutRect().XY();
        auto&& handleCorner = handleCenterRelativeToContainerCorner - (m_handleRect->GetLayoutRect().Size() - m_handleRect->GetSizeDelta()) * 0.5f;

        const uint8_t axis = GetAxis();
        float parentSize = axis == 0 ? m_containerRect->GetLayoutRect().Width() : m_containerRect->GetLayoutRect().Height();
        float remainingSize = parentSize * (1.f - GetSize());
        if (remainingSize <= 0.f) {
            return;
        }

        switch (m_direction) {
            case ScrollbarDirection::LeftToRight:
                SetValue(SR_CLAMP01(handleCorner.x / remainingSize));
                break;
            case ScrollbarDirection::RightToLeft:
                SetValue(SR_CLAMP01(1.f - (handleCorner.x / remainingSize)));
                break;
            case ScrollbarDirection::BottomToTop:
                SetValue(SR_CLAMP01(handleCorner.y / remainingSize));
                break;
            case ScrollbarDirection::TopToBottom:
                SetValue(SR_CLAMP01(1.f - (handleCorner.y / remainingSize)));
                break;
            default:
                SRHalt("Unexpected scrollbar direction!");
                break;
        }
    }
}