//
// Created by Monika on 21.03.2024.
//

#include <Engine/GUI/SceneTools.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>

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
                SR_GRAPH_GUI_NS::Immediate::Text("Camera Speed");
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(10, 0));
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(200.f);
                SR_GRAPH_GUI_NS::Immediate::SliderFloat("##", &m_cameraVelocityFactor, 0.01f, 10.f);
                SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
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
            .SetWidth(120.f)
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        AddElement()
            .SetCustomDraw([this](auto&& pElement) {
                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(150.f);

                if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("View Mode", SR_UTILS_NS::EnumReflector::ToStringAtom(m_viewMode).c_str())) {
                    auto&& names = SR_UTILS_NS::EnumReflector::GetNames<EditorSceneViewMode>();
                    for (auto&& name : names) {
                        if (SR_GRAPH_GUI_NS::Immediate::Selectable(name.c_str())) {
                            SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                            m_viewMode = SR_UTILS_NS::EnumReflector::FromString<EditorSceneViewMode>(name);
                        }
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndCombo();
                }
            })
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        AddElement("Re-Draw")
            .SetIsActive([]() { return false; })
            .SetOnClick([&](bool isActive) {
                GetRenderScene()->GetPipeline()->SetDirty(true);
            })
            .SetWidth(80.f)
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        AddElement()
            .SetCustomDraw([this](auto&& pElement) {
                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(150.f);

                auto optionFn = [this](SR_UTILS_NS::StringAtom macro, const char* label) {
                    auto&& pContext = GetRenderScene()->GetContext();
                    bool value = pContext->IsMacroDefined(macro);
                    if (value) {
                        SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor::Green());
                    }
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(label)) {
                        pContext->SwitchMacro(macro, !value);
                        pContext->ReloadShaders();
                    }
                    if (value) {
                        SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
                    }
                };

                if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("##Options", "Options")) {
                    optionFn("DEBUG_RENDER", "Debug draw");

                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    optionFn("SR_DEFINE_DEBUG_CASCADED_SHADOW_MAP_PASS", "Debug shadow cascades");

                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    optionFn("SR_DEFINE_WIREFRAME", "Wireframe");

                    SR_GRAPH_GUI_NS::Immediate::EndCombo();
                }
            })
            .SetItemSpacing(SR_MATH_NS::FVector2(10.f, 0.f));

        Super::Init();
    }

    void SceneTools::SetGizmoOperation(SR_GRAPH_UI_NS::GizmoOperation operation) {
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
