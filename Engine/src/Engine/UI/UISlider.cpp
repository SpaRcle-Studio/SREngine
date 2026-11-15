//
// Created by Codex on 15.11.2026.
//

#include <Engine/UI/UISlider.h>
#include <Utils/ECS/TransformRect.h>
#include <Codegen/UISlider.generated.hpp>

namespace SR_CORE_UI_NS {
    void UISlider::SetValue(float_t value) {
        if (!std::isfinite(value) || !std::isfinite(m_minValue) || !std::isfinite(m_maxValue) || m_maxValue < m_minValue) {
            SR_ERROR("UISlider::SetValue() : invalid value or range");
            return;
        }
        value = std::clamp(m_wholeNumbers ? std::round(value) : value, m_minValue, m_maxValue);
        if (m_value != value) {
            m_value = value;
            RefreshVisual();
            InvokeEvents(m_onValueChanged);
        }
    }

    void UISlider::RefreshVisual() {
        auto&& pRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_handle.GetRaw());
        if (!pRect) {
            return;
        }
        float_t value = m_maxValue > m_minValue ? (m_value - m_minValue) / (m_maxValue - m_minValue) : 0.f;
        value = std::clamp(m_reverse ? 1.f - value : value, 0.f, 1.f);
        auto anchors = pRect->GetAnchors();
        const uint32_t axis = m_vertical ? 1 : 0;
        anchors.min[axis] = value;
        anchors.max[axis] = value;
        pRect->SetAnchors(anchors);
        auto position = pRect->GetAnchoredPosition();
        position[axis] = 0.f;
        pRect->SetAnchoredPosition(position);
    }

    void UISlider::OnRangeChanged() {
        SetValue(m_value);
        RefreshVisual();
    }

    void UISlider::OnPostLoad() {
        UIControl::OnPostLoad();
        RefreshVisual();
    }

    void UISlider::PointerDown(const SR_UTILS_NS::PointerEvent& event) {
        PointerDrag(event);
    }

    void UISlider::PointerDrag(const SR_UTILS_NS::PointerEvent& event) {
        auto&& pRect = GetTransformAs<SR_UTILS_NS::TransformRect>();
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!pRect || !pCanvas || !IsInteractable()) {
            return;
        }
        const auto point = pCanvas->CanvasToLayoutPoint(*pRect, pCanvas->PointerToCanvasSpace(event));
        const auto rect = pRect->GetLayoutRect();
        const auto size = rect.Size();
        const uint32_t axis = m_vertical ? 1 : 0;
        if (size[axis] <= 0.f) {
            return;
        }
        float_t normalized = std::clamp((point[axis] - rect.Min()[axis]) / size[axis], 0.f, 1.f);
        if (m_reverse) {
            normalized = 1.f - normalized;
        }
        SetValue(m_minValue + normalized * (m_maxValue - m_minValue));
    }

    bool UISlider::Navigate(int32_t direction) {
        SetValue(m_value + static_cast<float_t>(m_reverse ? -direction : direction) * (m_wholeNumbers ? 1.f : m_keyboardStep));
        return true;
    }
}
