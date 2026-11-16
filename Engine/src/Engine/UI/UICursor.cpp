//
// Created by Monika on 28.04.2026.
//

#include <Engine/UI/UICursor.h>
#include <Engine/Application.h>
#include <Engine/Engine.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/SceneViewer.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Types/Geometry/Sprite.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/TransformRect.h>

#include <Codegen/UICursor.generated.hpp>

namespace SR_CORE_UI_NS {
    void UICursor::AfterLayout() {
        auto&& pTransformRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(GetSceneObject().Get());
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!pTransformRect || !pCanvas) {
            SR_UTILS_NS::Input::Instance().SetCustomCursorActive(this, false);
            return;
        }

        auto&& input = SR_UTILS_NS::Input::Instance();
        auto&& pWindow = pCanvas->GetWindow();
        bool inside = input.IsAppFocused() && !input.IsCursorLocked() && pWindow && pWindow->IsWindowFocus()
            && pCanvas->GetViewportRect().Contains(pWindow->ScreenToClient(input.GetMousePos().CastToInt()).CastToFloat());
        SR_MATH_NS::FVector2 uiMousePos = pCanvas->ScreenToCanvasSpace(input.GetMousePos());
        if (auto&& pApplication = ApplicationManager::Instance().GetApplication()) {
            if (auto&& pEngine = pApplication->GetEngine(); pEngine && pEngine->GetEditor()) {
                auto&& pViewer = pEngine->GetEditor()->GetWidget<SR_CORE_GUI_NS::SceneViewer>();
                inside = input.IsAppFocused() && !input.IsCursorLocked() && pViewer && pViewer->IsOpen()
                    && pViewer->IsHovered() && !pViewer->GetTextureSize().HasZero()
                    && SR_MATH_NS::FRect(pViewer->GetImagePosition(), pViewer->GetTextureSize()).Contains(input.GetMousePos());
                if (inside) {
                    const auto normalized = (input.GetMousePos() - pViewer->GetImagePosition()) / pViewer->GetTextureSize();
                    const auto size = pCanvas->GetSize().CastToFloat() / pCanvas->GetScaleFactor();
                    uiMousePos = SR_MATH_NS::FVector2((normalized.x - 0.5f) * size.x, (0.5f - normalized.y) * size.y);
                }
            }
        }
        input.SetCustomCursorActive(this, inside);
        if (auto&& pSprite = GetGameObject()->GetComponent<SR_GTYPES_NS::Sprite>()) {
            pSprite->SetEnabled(inside);
        }
        if (!inside) {
            return;
        }

        if (!m_positionInitialized) {
            pTransformRect->SetAnchoredPosition(SR_MATH_NS::FVector2::Zero());
            m_positionInitialized = true;
        }
        pTransformRect->SetVisualOffset(uiMousePos);

        SR_UTILS_NS::UIComponent::AfterLayout();
    }

    void UICursor::OnDisable() {
        SR_UTILS_NS::Input::Instance().SetCustomCursorActive(this, false);
        if (auto&& pObject = GetGameObject()) {
            if (auto&& pSprite = pObject->GetComponent<SR_GTYPES_NS::Sprite>()) {
                pSprite->SetEnabled(false);
            }
        }
        SR_UTILS_NS::UIComponent::OnDisable();
    }

    void UICursor::OnDetached() {
        SR_UTILS_NS::Input::Instance().SetCustomCursorActive(this, false);
        SR_UTILS_NS::UIComponent::OnDetached();
    }
}
