//
// Created by Monika on 27.01.2024.
//

#include <Engine/GUI/EditorCamera.h>
#include <Engine/GUI/SceneViewer.h>

#include <Codegen/EditorCamera.generated.hpp>

namespace SR_CORE_GUI_NS {
    SR_MATH_NS::FPoint EditorCamera::GetMousePos() const {
        auto&& imMouseGuiPos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
        auto&& mousePos = SR_MATH_NS::FPoint(imMouseGuiPos.x, imMouseGuiPos.y) - m_sceneViewer->GetImagePosition();
        return mousePos / m_sceneViewer->GetTextureSize().Cast<SR_MATH_NS::Unit>();
    }
}
