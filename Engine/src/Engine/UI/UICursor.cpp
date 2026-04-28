//
// Created by Monika on 28.04.2026.
//

#include <Engine/UI/UICursor.h>

#include <Graphics/Window/Window.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/ECS/TransformRect.h>

#include <Codegen/UICursor.generated.hpp>

namespace SR_CORE_UI_NS {
    void UICursor::Update(float_t dt) {
        auto&& pTransformRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(GetSceneObject().Get());
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!pTransformRect || !pCanvas) {
            return;
        }

        auto&& input = SR_UTILS_NS::Input::Instance();

        const SR_MATH_NS::FVector2 uiMousePos = pCanvas->ScreenToCanvasSpace(input.GetMousePos());
        pTransformRect->SetAnchoredPosition(uiMousePos);

        Super::Update(dt);
    }
}