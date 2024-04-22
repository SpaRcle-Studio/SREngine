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
                ImGui::Text("Camera Speed");
                ImGui::SameLine();
                ImGui::Dummy(ImVec2(10, 0));
                ImGui::SameLine();
                ImGui::PushItemWidth(200.f);
                ImGui::SliderFloat("##", &m_cameraVelocityFactor, 0.01f, 10.f);
                ImGui::PopItemWidth();
            })
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        AddElement("Connect PVD")
            .SetIsActive([]() { return false; })
            .SetOnClick([](bool isActive) {
                auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D);
                if (pLibrary) {
                    pLibrary->ConnectPVD();
                }
            })
            .SetWidth(100.f)
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        AddElement()
            .SetCustomDraw([this](auto&& pElement) {
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
            })
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

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

    void SceneTools::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* pData) {
        switch (pData->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::_1: SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::None); break;
            case SR_UTILS_NS::KeyCode::_2: SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Translate); break;
            case SR_UTILS_NS::KeyCode::_3: SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Rotate); break;
            case SR_UTILS_NS::KeyCode::_4: SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation::Scale); break;
            default:
                break;
        }
        Super::OnKeyDown(pData);
    }
}
