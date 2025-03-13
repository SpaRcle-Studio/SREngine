//
// Created by Monika on 27.01.2024.
//

#include <Core/GUI/EditorCamera.h>
#include <Core/GUI/SceneViewer.h>

#include <Codegen/EditorCamera.generated.hpp>

namespace SR_CORE_GUI_NS {
    SR_MATH_NS::FPoint EditorCamera::GetMousePos() const {
        auto&& imMouseGuiPos = ImGui::GetMousePos();
        auto&& mousePos = SR_MATH_NS::FPoint(imMouseGuiPos.x, imMouseGuiPos.y) - m_sceneViewer->GetImagePosition();
        return mousePos / m_sceneViewer->GetTextureSize().Cast<SR_MATH_NS::Unit>();
    }
}
