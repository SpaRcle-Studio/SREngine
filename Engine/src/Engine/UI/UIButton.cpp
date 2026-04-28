//
// Created by Monika on 20.11.2022.
//

#include <Engine/UI/UIButton.h>

#include <Graphics/Window/Window.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/ECS/TransformRect.h>

#include <Codegen/UIButton.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIButton::Update(float_t dt) {
        auto&& pTransformRect = SR_UTILS_NS::ExtractTransformAs<SR_UTILS_NS::TransformRect>(GetSceneObject().Get());
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!pTransformRect || !pCanvas) {
            return;
        }

        auto&& input = SR_UTILS_NS::Input::Instance();

        const SR_MATH_NS::FVector2 uiMousePos = pCanvas->ScreenToCanvasSpace(input.GetMousePos());
        SR_MATH_NS::FRect layoutRect = pCanvas->LayoutToCanvasRect(pTransformRect->GetLayoutRect());

        if (layoutRect.Contains(uiMousePos)) {
            const bool isDown = m_leftClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)
                                || m_rightClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseRight)
                                || m_middleClick && input.GetMouseDown(SR_UTILS_NS::MouseCode::MouseMiddle);

            if (isDown && m_state != State::Pressed) {
                for (auto&& event : m_onClickEvents) {
                    if (auto&& pObject = event.object.Get()) {
                        SR_UTILS_NS::Reflection::InvokeMethodVoid(*pObject, event.method);
                    }
                }
                m_state = State::Pressed;
            }
            else if (m_state == State::Idle || m_state == State::Hovered) {
                m_state = State::Hovered;
            }
            else if (m_state == State::Pressed) {
                const bool isUp = m_leftClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)
                                  || m_rightClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseRight)
                                  || m_middleClick && input.GetMouseUp(SR_UTILS_NS::MouseCode::MouseMiddle);
                if (isUp) {
                    m_state = State::Hovered;
                }
            }
            else {
                m_state = State::Idle;
            }
        }
        else {
            m_state = State::Idle;
        }

        if (auto&& pIdle = m_idle.Get()) {
            pIdle->SetEnabled(m_state == State::Idle);
        }

        if (auto&& pHovered = m_hovered.Get()) {
            pHovered->SetEnabled(m_state == State::Hovered);
        }

        if (auto&& pPressed = m_pressed.Get()) {
            pPressed->SetEnabled(m_state == State::Pressed);
        }

        Super::Update(dt);
    }
}