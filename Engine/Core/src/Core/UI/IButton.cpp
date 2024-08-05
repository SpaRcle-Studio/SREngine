//
// Created by innerviewer on 2024-01-12.
//

#include <Core/UI/IButton.h>

#include <Graphics/Types/Geometry/Mesh3D.h>
#include <Graphics/Types/Camera.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/IRenderTechnique.h>

#include <Graphics/Pass/IColorBufferPass.h>

#include <Utils/Input/InputSystem.h>

namespace SR_CORE_UI_NS {
    IButton::IButton()
        : Super()
    {
        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("Idle")
                .SetLabel("Button is idle.")
                .SetColor(SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f))
                .SetActiveCondition([this] { return IsIdle(); })
                .SetDontSave()
                .SetReadOnly();
        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("Hovered")
                .SetLabel("Button is hovered.")
                .SetColor(SR_MATH_NS::FColor(0.f, 1.f, 0.f, 1.f))
                .SetActiveCondition([this] { return IsHovered(); })
                .SetDontSave()
                .SetReadOnly();
        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("Pressed")
                .SetLabel("Button is pressed.")
                .SetColor(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f))
                .SetActiveCondition([this] { return IsPressed(); })
                .SetDontSave()
                .SetReadOnly();
    }

    void IButton::Update(float_t dt) {
        auto&& pCamera = GetCamera();
        if (!pCamera) {
            return;
        }

        auto&& mousePosition = pCamera->GetMousePos();
        auto&& pRenderTechnique = pCamera->GetRenderTechnique();
        auto&& pMesh = pRenderTechnique->PickMeshAt(mousePosition);
        auto&& pHoveredMesh = dynamic_cast<IRenderComponent*>(pMesh);
        auto&& isPressed = SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft);
        bool isHovered = pHoveredMesh ? CompareObject(pHoveredMesh->GetGameObject()) : false;

        if (isHovered) {
            m_state = ButtonState::Hovered;
            OnHover();
            if (isPressed) {
                m_state = ButtonState::Pressed;
                OnKeyDown();
            }
        }
        else {
            m_state = ButtonState::Idle;
            OnKeyDown();
        }
    }

    bool IButton::InitializeEntity() noexcept {
        /*m_properties.AddEntityRefProperty("Mesh", GetThis())
        .SetWidth(260.0f);*/

        return Entity::InitializeEntity();
    }

    void IButton::OnIdle() {
        if (m_onIdle) {
            m_onIdle();
        }
    }

    void IButton::OnHover() {
        if (m_onHover) {
            m_onHover();
        }
    }

    void IButton::OnKeyDown() {
        if (m_onKeyDown) {
            m_onKeyDown();
        }
    }

    void IButton::OnKeyUp() {
        if (m_onKeyUp) {
            m_onKeyUp();
        }
    }

    bool IButton::CompareObject(GameObjectPtr pObject) const {
        while (pObject) {
            if (pObject == GetGameObject()) {
                return true;
            }
            pObject = pObject->GetParent();
        }

        return false;
    }
}