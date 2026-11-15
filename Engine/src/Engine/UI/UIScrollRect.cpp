//
// Created by Monika on 01.02.2026.
//

#include <Engine/UI/UIScrollRect.h>
#include <Codegen/UIScrollRect.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIScrollRect::SetNormalizedPosition(const SR_MATH_NS::FVector2& position) {
        if (!std::isfinite(position.x) || !std::isfinite(position.y)) {
            SR_ERROR("UIScrollRect::SetNormalizedPosition() : non-finite position");
            return;
        }
        m_normalizedPosition = { std::clamp(position.x, 0.f, 1.f), std::clamp(position.y, 0.f, 1.f) };
        if (auto pBar = m_horizontalScrollBar.Get()) {
            pBar->SetValue(m_normalizedPosition.x);
        }
        if (auto pBar = m_verticalScrollBar.Get()) {
            pBar->SetValue(m_normalizedPosition.y);
        }
        AfterLayout();
    }

    void UIScrollRect::AfterLayout() {
        SR_TRACY_ZONE;
        auto&& pContent = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_content.GetRaw());
        auto&& pViewport = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_viewport.GetRaw());
        if (!pContent || !pViewport || pContent->GetGlobalScale().HasZero() || pViewport->GetGlobalScale().HasZero()) {
            return;
        }
        const auto contentRect = pContent->GetLayoutRect();
        const auto viewportRect = pViewport->GetLayoutRect();
        const auto contentToViewport = pViewport->GetMatrix().Inverse() * pContent->GetMatrix();
        SR_MATH_NS::FVector2 minimum(std::numeric_limits<float_t>::max());
        SR_MATH_NS::FVector2 maximum(std::numeric_limits<float_t>::lowest());
        for (uint32_t i = 0; i < 4; ++i) {
            const auto point = contentToViewport.TransformPoint({ i & 1 ? contentRect.Right() : contentRect.Left(), i & 2 ? contentRect.Top() : contentRect.Bottom(), 0.f });
            minimum.x = std::min(minimum.x, point.x);
            minimum.y = std::min(minimum.y, point.y);
            maximum.x = std::max(maximum.x, point.x);
            maximum.y = std::max(maximum.y, point.y);
        }
        const auto contentSize = maximum - minimum;
        const auto viewportSize = viewportRect.Size();
        m_overflow = { std::max(0.f, contentSize.x - viewportSize.x), std::max(0.f, contentSize.y - viewportSize.y) };
        if (auto pBar = m_horizontalScrollBar.Get()) {
            pBar->SetSize(contentSize.x > 0.f ? std::clamp(viewportSize.x / contentSize.x, 0.f, 1.f) : 1.f);
            m_normalizedPosition.x = pBar->GetValue();
        }
        if (auto pBar = m_verticalScrollBar.Get()) {
            pBar->SetSize(contentSize.y > 0.f ? std::clamp(viewportSize.y / contentSize.y, 0.f, 1.f) : 1.f);
            m_normalizedPosition.y = pBar->GetValue();
        }
        const SR_MATH_NS::FVector3 delta(
            m_horizontal ? viewportRect.Left() - m_overflow.x * m_normalizedPosition.x - minimum.x : 0.f,
            m_vertical ? viewportRect.Top() + m_overflow.y * m_normalizedPosition.y - maximum.y : 0.f,
            0.f);
        if (auto&& pParent = pContent->GetParentTransform()) {
            const auto viewportToParent = pParent->GetMatrix().Inverse() * pViewport->GetMatrix();
            const auto converted = viewportToParent.TransformPoint(delta) - viewportToParent.TransformPoint(SR_MATH_NS::FVector3::Zero());
            auto position = pContent->GetAnchoredPosition();
            position.x += converted.x;
            position.y += converted.y;
            if (std::abs(converted.x) > 0.001f || std::abs(converted.y) > 0.001f) {
                pContent->SetAnchoredPosition(position);
            }
        }
    }

    void UIScrollRect::PointerDown(const SR_UTILS_NS::PointerEvent& event) {
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        auto&& pViewport = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_viewport.GetRaw());
        if (pCanvas && pViewport) {
            m_dragStart = pCanvas->CanvasToLayoutPoint(*pViewport, pCanvas->PointerToCanvasSpace(event));
            m_dragNormalized = m_normalizedPosition;
        }
    }

    void UIScrollRect::PointerDrag(const SR_UTILS_NS::PointerEvent& event) {
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        auto&& pViewport = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_viewport.GetRaw());
        if (!pCanvas || !pViewport) {
            return;
        }
        const auto delta = pCanvas->CanvasToLayoutPoint(*pViewport, pCanvas->PointerToCanvasSpace(event)) - m_dragStart;
        auto normalized = m_dragNormalized;
        if (m_horizontal && m_overflow.x > 0.f) {
            normalized.x -= delta.x / m_overflow.x;
        }
        if (m_vertical && m_overflow.y > 0.f) {
            normalized.y += delta.y / m_overflow.y;
        }
        SetNormalizedPosition(normalized);
    }

    bool UIScrollRect::Scroll(const SR_MATH_NS::FVector2& delta) {
        auto normalized = m_normalizedPosition;
        if (m_horizontal) {
            normalized.x -= delta.x * m_scrollSensitivity;
        }
        if (m_vertical) {
            normalized.y -= delta.y * m_scrollSensitivity;
        }
        SetNormalizedPosition(normalized);
        return true;
    }
}
