//
// Created by Monika on 01.02.2026.
//

#include <Engine/UI/UIScrollRect.h>

#include <Utils/Input/InputSystem.h>

#include <Codegen/UIScrollRect.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIScrollRect::Update(float_t dt) {
        SR_TRACY_ZONE;
        Super::Update(dt);

        auto&& pContentTransform = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_content.GetRaw());
        auto&& pViewportTransform = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(m_viewport.GetRaw());
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());

        if (!pContentTransform || !pViewportTransform || !pCanvas) {
            return;
        }

        UIScrollBar* pHScrollBar = m_horizontalScrollBar.GetRaw();
        UIScrollBar* pVScrollBar = m_verticalScrollBar.GetRaw();

        const auto contentSize  = pContentTransform->GetLayoutRect().Size();
        const auto viewportSize = pViewportTransform->GetLayoutRect().Size();

        const SR_MATH_NS::FVector2 scrollableSize = {
            std::max(0.f, contentSize.x - viewportSize.x),
            std::max(0.f, contentSize.y - viewportSize.y)
        };

        auto&& input = SR_UTILS_NS::Input::Instance();

        const SR_MATH_NS::FVector2 uiMousePos = pCanvas->ScreenToCanvasSpace(input.GetMousePos());
        if (const int32_t wheel = input.GetMouseWheel()) {
            auto&& viewportRect = pCanvas->LayoutToCanvasRect(pViewportTransform->GetLayoutRect());
            if (pVScrollBar && viewportRect.Contains(uiMousePos)) {
                float value = pVScrollBar->GetValue();
                value -= wheel * 0.1f;
                pVScrollBar->SetValue(std::clamp(value, 0.f, 1.f));

                float yOffset = scrollableSize.y * (value);
                auto pos = pContentTransform->GetAnchoredPosition();
                pos.y = yOffset;
                pContentTransform->SetAnchoredPosition(pos);
            }
        }

        if (pVScrollBar) {
            float value = pVScrollBar->GetValue();
            float yOffset = scrollableSize.y * (value);

            auto pos = pContentTransform->GetAnchoredPosition();
            pos.y = yOffset;
            pContentTransform->SetAnchoredPosition(pos);

            float size = viewportSize.y / contentSize.y;
            pVScrollBar->SetSize(std::clamp(size, 0.f, 1.f));
        }

        if (pHScrollBar) {
            float value = pHScrollBar->GetValue();
            float xOffset = scrollableSize.x * (value);

            auto pos = pContentTransform->GetAnchoredPosition();
            pos.x = xOffset;
            pContentTransform->SetAnchoredPosition(pos);

            float size = viewportSize.x / contentSize.x;
            pHScrollBar->SetSize(std::clamp(size, 0.f, 1.f));
        }
    }
}