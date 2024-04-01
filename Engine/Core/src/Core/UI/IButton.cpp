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
        auto&& pHoveredMesh = pCamera->GetRenderTechnique()->PickMeshAt(mousePosition);
        auto&& isPressed = SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft);
        bool isHovered = false;

        /*if (auto&& pMesh = reinterpret_cast<SR_GTYPES_NS::Mesh3D *>(m_properties.Find("Mesh"))) {
            isHovered = pHoveredMesh == pMesh;
        }*/

        if (auto&& pMesh = GetParent()->GetComponent<SR_GTYPES_NS::Mesh3D>()) {
            isHovered = pHoveredMesh == pMesh;
        }

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
            m_onIdle = Callback();
        }
    }

    void IButton::OnHover() {
        if (m_onHover) {
            m_onHover();
            m_onHover = Callback();
        }
    }

    void IButton::OnKeyDown() {
        if (m_onKeyDown) {
            m_onKeyDown();
            m_onKeyDown = Callback();
        }
    }

    void IButton::OnKeyUp() {
        if (m_onKeyUp) {
            m_onKeyUp();
            m_onKeyUp = Callback();
        }
    }
}