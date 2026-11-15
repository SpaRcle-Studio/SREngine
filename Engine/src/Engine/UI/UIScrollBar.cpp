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
    bool UIScrollBar::AcceptsButton(SR_UTILS_NS::PointerButton button) const {
        return (m_leftClick && button == SR_UTILS_NS::PointerButton::Primary)
            || (m_rightClick && button == SR_UTILS_NS::PointerButton::Secondary)
            || (m_middleClick && button == SR_UTILS_NS::PointerButton::Middle);
    }

    void UIScrollBar::AfterLayout() {
        RefreshHandleLayout();
    }

    void UIScrollBar::PointerDown(const SR_UTILS_NS::PointerEvent& event) {
        m_handleRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.GetRaw());
        m_containerRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle ? m_handle.Get()->GetParent().Get() : nullptr);
        m_dragOffset = 0.f;
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!m_handleRect || !m_containerRect || !pCanvas) {
            return;
        }
        const uint32_t axis = GetAxis();
        const auto point = pCanvas->CanvasToLayoutPoint(*m_containerRect, pCanvas->PointerToCanvasSpace(event));
        if (pCanvas->ContainsPointer(*m_handleRect, event)) {
            const auto local = m_containerRect->GetLayoutRect();
            const float_t handleStart = local.Min()[axis] + local.Size()[axis] * (IsReverseValue() ? (1.f - GetValue()) : GetValue()) * (1.f - m_size);
            m_dragOffset = point[axis] - handleStart - local.Size()[axis] * m_size * 0.5f;
        }
        PointerDrag(event);
    }

    void UIScrollBar::PointerDrag(const SR_UTILS_NS::PointerEvent& event) {
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (pCanvas && m_handleRect && m_containerRect) {
            OnDrag(*pCanvas, pCanvas->PointerToCanvasSpace(event), pCanvas->GetCamera());
        }
    }

    bool UIScrollBar::Navigate(int32_t direction) {
        const float_t step = m_numberOfSteps > 1 ? 1.f / static_cast<float_t>(m_numberOfSteps - 1) : 0.1f;
        SetValue(GetValue() + static_cast<float_t>(IsReverseValue() ? -direction : direction) * step);
        return true;
    }

    void UIScrollBar::SetValue(float_t value) {
        if (!std::isfinite(value)) {
            return;
        }
        m_value = SR_CLAMP01(value);
        RefreshHandleLayout();
    }

    void UIScrollBar::SetSize(float_t size) {
        if (!std::isfinite(size)) {
            return;
        }
        m_size = SR_CLAMP(size, 0.001f, 1.f);
        RefreshHandleLayout();
    }

    void UIScrollBar::SetHandle(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>& pHandle) {
        m_handle.SetEntityId(pHandle->GetEntityId());
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
        auto size = pHandleTransform->GetSizeDelta();
        size[axis] = 0.f;
        pHandleTransform->SetSize(size);
        auto position = pHandleTransform->GetAnchoredPosition();
        position[axis] = 0.f;
        pHandleTransform->SetAnchoredPosition(position);
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

    void UIScrollBar::OnDrag(SR_GRAPH_UI_NS::Canvas& canvas, const SR_MATH_NS::FVector2& screenPosition, SR_GTYPES_NS::Camera* pCamera) {
        if (m_containerRect->GetGlobalScale().HasZero()) {
            return;
        }
        auto&& containerRect = m_containerRect->GetLayoutRect();
        auto&& handleRect = m_handleRect->GetLayoutRect();

        SR_MATH_NS::FVector2 localCursor = canvas.CanvasToLayoutPoint(*m_containerRect, screenPosition);
        auto&& handleCenterRelativeToContainerCorner = localCursor - containerRect.XY();
        auto&& handleCorner = handleCenterRelativeToContainerCorner - (handleRect.Size() - m_handleRect->GetSizeDelta()) * 0.5f;

        const uint8_t axis = GetAxis();
        handleCorner[axis] -= m_dragOffset;
        float_t parentSize = axis == 0 ? containerRect.Width() : containerRect.Height();
        float_t remainingSize = parentSize * (1.f - GetSize());
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
