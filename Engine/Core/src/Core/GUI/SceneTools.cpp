//
// Created by Monika on 21.03.2024.
//

#include <Core/GUI/SceneTools.h>

namespace SR_CORE_GUI_NS {
    void SceneTools::Init() {
        m_gizmoOperationFlag = SR_GRAPH_UI_NS::GizmoOperation::TranslateAll;

        AddElement("L")
            .SetIsActive([this]() { return m_gizmoMode == SR_GRAPH_UI_NS::GizmoMode::Local; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoMode(SR_GRAPH_UI_NS::GizmoMode::Global); }
                else { SetGizmoMode(SR_GRAPH_UI_NS::GizmoMode::Local); }
            });

        AddElement("T")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Translate; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Translate); }
            });

        AddElement("R")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Rotate; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Rotate); }
            });

        AddElement("S")
            .SetIsActive([this]() { return m_gizmoOperationFlag & SR_GRAPH_UI_NS::GizmoOperation::Scale; })
            .SetOnClick([this](bool isActive) {
                if (isActive) { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); }
                else { SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Scale); }
            });

        AddElement()
            .SetCustomDraw([this](auto&& pElement) {
                ImGui::Dummy(ImVec2(10, 0));
                ImGui::SameLine();
                ImGui::Text("Camera Speed");
                ImGui::SameLine();
                ImGui::Dummy(ImVec2(10, 0));
                ImGui::SameLine();
                ImGui::PushItemWidth(200.f);
                ImGui::SliderFloat("##", &m_cameraVelocityFactor, 0.01f, 10.f);
                ImGui::PopItemWidth();
            });

        AddElement()
            .SetCustomDraw([this](auto&& pElement) {
                ImGui::Dummy(ImVec2(10, 0));
                ImGui::SameLine();
                ImGui::PushItemWidth(150.f);

                if (ImGui::BeginCombo("View Mode", SR_UTILS_NS::EnumReflector::ToStringAtom(m_viewMode).c_str())) {
                    auto&& names = SR_UTILS_NS::EnumReflector::GetNames<EditorSceneViewMode>();
                    for (auto&& name : names) {
                        if (ImGui::Selectable(name.c_str())) {
                            ImGui::SetItemDefaultFocus();
                            m_viewMode = SR_UTILS_NS::EnumReflector::FromString<EditorSceneViewMode>(name);
                        }
                    }

                    ImGui::EndCombo();
                }
            });

        Super::Init();
    }

    void SceneTools::SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperationFlag operation) {
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Translate;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Rotate;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Scale;
        m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Bounds;

        if (operation != SR_GRAPH_UI_NS::GizmoOperation::None) {
            m_gizmoOperationFlag |= operation;
        }

        if (auto&& pGizmo = FindGizmo()) {
            pGizmo->SetOperation(m_gizmoOperationFlag);
        }
    }

    void SceneTools::SetGizmo2D(bool isActive) {
        if (isActive) {
            m_gizmoOperationFlag &= ~SR_GRAPH_UI_NS::GizmoOperation::Z;
        }
        else {
            m_gizmoOperationFlag |= SR_GRAPH_UI_NS::GizmoOperation::Z;
        }

        if (auto&& pGizmo = FindGizmo()) {
            pGizmo->SetOperation(m_gizmoOperationFlag);
        }
    }

    void SceneTools::SetGizmoMode(SR_GRAPH_UI_NS::GizmoMode mode) {
        m_gizmoMode = mode;

        if (auto&& pGizmo = FindGizmo()) {
            pGizmo->SetMode(m_gizmoMode);
        }
    }

    SR_HTYPES_NS::SharedPtr<SR_CORE_GUI_NS::EditorGizmo> SceneTools::FindGizmo() const {
        auto&& pEditor = dynamic_cast<SR_CORE_GUI_NS::EditorGUI*>(GetManager());
        if (!pEditor) {
            return nullptr;
        }

        auto&& pScene = pEditor->GetEngine()->GetScene();
        if (!pScene) {
            return nullptr;
        }

        auto&& pGizmoGameObject = pScene->Find("Editor gizmo");
        if (!pGizmoGameObject) {
            return nullptr;
        }

        return pGizmoGameObject->GetComponent<SR_CORE_GUI_NS::EditorGizmo>();
    }
}
