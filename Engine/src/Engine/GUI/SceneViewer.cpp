//
// Created by Monika on 11.02.2022.
//

#include <Engine/GUI/SceneViewer.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorCamera.h>
#include <Engine/GUI/EditorGizmo.h>
#include <Engine/GUI/Guizmo.h>
#include <Graphics/Material/UniqueMaterial.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Common/Features.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/World/SceneLogic.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Pass/ColorBufferPass.h>
#include <Graphics/Pass/FlatColorBufferPass.h>
#include <Utils/Game/CameraFlyMover.h>

namespace SR_CORE_GUI_NS {
    SceneViewer::SceneViewer(const EnginePtr& pEngine, Hierarchy* hierarchy)
        : Widget("Scene")
        , m_engine(pEngine)
        , m_window(pEngine->GetMainWindow())
        , m_hierarchy(hierarchy)
        , m_id(SR_ID_INVALID)
    {
        LoadCameraSettings();
        AddSubWidget(new SceneTools());
    }

    SceneViewer::~SceneViewer() {
        Enable(false);
    }

    void SceneViewer::Draw() {
        if (!m_scene) {
            return;
        }

        /// что-то пошло не так, потеряли камеру
        if (m_enabled && !m_camera) {
            SetCameraEnabled(true);
            SetGizmoEnabled(true);
        }

        if (m_enabled && !m_platform && m_isPrefab) {
            m_platform = m_scene->Find("PREFAB_PLATFORM"_atom).DynamicCast<SR_UTILS_NS::GameObject>();
            if (!m_platform) {
                m_platform = m_scene->InstanceFromFile("Engine/Models/plane_extended.obj").DynamicCast<SR_UTILS_NS::GameObject>();
            }
            if (m_platform) {
                m_platform->SetName("PREFAB_PLATFORM");
                m_platform->AddSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave);
                if (!m_platform->GetChildren().empty()) {
                    if (auto&& pMesh = m_platform->GetChildren()[0]->GetComponent<SR_GTYPES_NS::Mesh3D>()) {
                        auto&& pMaterial = new SR_GRAPH_NS::UniqueMaterial();
                        pMaterial->SetShader("Engine/Shaders/CascadedShadowMap/spatial.srsl");
                        pMaterial->SetTexture("diffuse"_atom, GetRenderScene()->GetRenderStrategy()->GetRenderContext()->GetDefaultTexture());
                        pMesh->SetMaterial(pMaterial);
                    }
                }
                m_platform->GetTransform()->SetScale(5.f, 1.f, 5.f);
                m_platform->AddEditorFlags(SR_UTILS_NS::EditorFlags::Hidden);
            }
        }

        if (!m_camera) {
            m_camera = m_scene->Find("Editor camera"_atom).DynamicCast<SR_UTILS_NS::GameObject>();
        }

        if (!m_camera) {
            return;
        }

        auto&& pCamera = m_camera->GetComponent<EditorCamera>();
        if (!pCamera) {
            SR_WARN("SceneViewer::Draw() : editor camera component not found!");
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::BeginGroup();

        for (auto&& pSubWidget : m_subWidgets) {
            pSubWidget->DrawAsSubWindow();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (auto&& pFrameBuffer = GetContext()->FindFramebuffer("SceneView"_atom, pCamera.Get())) {
            m_id = pFrameBuffer->GetColorTexture(0);
        }
        else {
            m_id = SR_ID_INVALID;
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginChild("ViewerTexture"))
        {
            m_windowSize = SR_MATH_NS::Vector2(static_cast<int32_t>(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x), static_cast<int32_t>(SR_GRAPH_GUI_NS::Immediate::GetWindowSize().y));

            if (!UpdateViewSize() && pCamera && m_id != SR_ID_INVALID && pCamera->IsActive())
            {
                if (GetSceneTools()->GetViewMode() == EditorSceneViewMode::WindowSize) {
                    DrawTexture(m_windowSize, m_window->GetSize().Cast<int32_t>(), m_id, true);
                }
                else {
                    DrawTexture(m_windowSize, m_windowSize, m_id, true);
                }

                CheckFocused();
                CheckHovered();
            }
            SR_GRAPH_GUI_NS::Immediate::EndChild();
        }

        SR_GRAPH_GUI_NS::Immediate::EndGroup();
    }

    void SceneViewer::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        m_scene = scene;
        Enable(m_enabled);
    }

    void SceneViewer::Enable(bool value) {
        m_enabled = value;

        auto&& pLogic = m_scene ? m_scene->GetLogicBase() : SR_WORLD_NS::SceneLogic::Ptr();

        /// если сцена сломана, или это "пустышка", то не создаем камеру, т.к. рендерить нет смыла 
        if (!pLogic || !m_enabled) {
            SetCameraEnabled(false);
            SetGizmoEnabled(false);
            return;
        }

        if (!m_camera.Valid()) {
            SetCameraEnabled(true);
            SetGizmoEnabled(true);
        }
    }

    void SceneViewer::FixedUpdate() {
        const float_t velocityFactor = GetSceneTools()->GetCameraVelocityFactor();
        const bool isDisabled = !IsOpen() || (!IsHovered() && !m_updateNonHoveredSceneViewer);

        auto&& pFocusedWindow = m_engine->GetFocusedWindow();

        const bool isNeedLock = SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseRight) ||
            SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseMiddle);

        if (isNeedLock && !isDisabled) {
            const auto rect = SR_MATH_NS::FRect(
                pFocusedWindow ? pFocusedWindow->GetPosition().CastToFloat() + GetImagePosition() : SR_MATH_NS::FVector2(),
                m_textureSize
            );
            m_cursorLock = SR_UTILS_NS::CursorLock(SR_UTILS_NS::CursorLockMode::Editor, rect);
        }
        else {
            m_cursorLock.reset();
        }

        if (m_camera) {
            if (auto&& pMover = m_camera->GetComponent<SR_UTILS_NS::CameraFlyMover>()) {
                pMover->SetVelocityFactor(velocityFactor);
                pMover->SetActive(!isDisabled);
            }

            m_cameraTranslation = m_camera->GetTransform()->GetTranslation();
            m_cameraRotation = m_camera->GetTransform()->GetRotation();
        }

        if (isDisabled) {
            return;
        }

        if (m_camera && !m_gizmo) {
            SetGizmoEnabled(true); /// если пропал, вернем
        }
    }

    void SceneViewer::DrawTexture(SR_MATH_NS::IVector2 winSize, SR_MATH_NS::IVector2 texSize, uint32_t id, bool centralize) {
        if (texSize.HasNegative() || winSize.HasNegative()) {
            return;
        }

        const float_t dx = static_cast<float_t>(winSize.x) / static_cast<float_t>(texSize.x);
        const float_t dy = static_cast<float_t>(winSize.y) / static_cast<float_t>(texSize.y);

        texSize *= dy > dx ? dx : dy;

        m_textureSize = texSize.Cast<float_t>();

        if (centralize) {
            auto windowPosition = SR_GRAPH_GUI_NS::Immediate::GetCursorPos();
            auto res = (winSize - m_textureSize) * 0.5f;
            SR_MATH_NS::FVector2 centralizedCursorPos = { (float)res.x, (float)res.y };
            centralizedCursorPos = centralizedCursorPos.Clamp(windowPosition, centralizedCursorPos);
            SR_GRAPH_GUI_NS::Immediate::SetCursorPos(centralizedCursorPos);
        }

        auto&& pPipeline = GetContext()->GetPipeline();
        m_imagePosition = SR_GRAPH_GUI_NS::Immediate::DrawTexture(pPipeline.Get(), id, m_textureSize, false);
    }

    void SceneViewer::SetCameraEnabled(bool enabled) {
        SR_UTILS_NS::GameObject::Ptr pCamera;

        if (enabled) {
            /// сцена может быть уже заблокирована до Engine::SetScene
            if (SR_UTILS_NS::Features::Instance().Enabled("EditorCamera", true) && m_scene) {
                pCamera = m_scene->InstanceGameObject("Editor camera"_atom);
                pCamera->AddSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave);
                pCamera->AddEditorFlags(SR_UTILS_NS::EditorFlags::Hidden);

                if (auto&& pMover = pCamera->AddComponent<SR_UTILS_NS::CameraFlyMover>()) {
                    pMover->SetExecuteInEditMode(true);
                    pMover->SetRightMouseButtonToRotate(true);
                }

                m_isPrefab = m_scene->IsPrefab();
            }
            else {
                return;
            }

            EditorCamera::Ptr pCameraComponent = pCamera->AddComponent<EditorCamera>();
            pCameraComponent->SetSceneViewer(this);

            auto&& preset = GetRenderScene()->GetContext()->GetSettingsPreset();

            if (m_isPrefab) {
                pCameraComponent->SetRenderTechnique(preset.prefabCameraRenderTechnique);
            }
            else {
                pCameraComponent->SetRenderTechnique(preset.editorCameraRenderTechnique);
            }

            /// Камера редактора имеет наивысшый закадровый приоритет
            pCameraComponent->SetPriority(SR_INT32_MIN);

            pCamera->GetTransform()->GlobalTranslate(m_cameraTranslation);
            pCamera->GetTransform()->GlobalRotate(m_cameraRotation);
        }

        if (m_camera) {
            m_camera->Destroy();
        }

        m_camera = pCamera;

        BackupCameraSettings();
    }

    void SceneViewer::OnClose() {
        Enable(false);
    }

    void SceneViewer::OnOpen() {
        Enable(true);
    }

    void SceneViewer::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        ////////////////// m_guizmo->OnKeyDown(data);
        Super::OnKeyDown(data);
    }

    void SceneViewer::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) {
        ////////////////////// m_guizmo->OnKeyPress(data);
        Super::OnKeyPress(data);
    }

    void SceneViewer::OnMouseDown(const SR_UTILS_NS::MouseInputData* data) {
    }

    void SceneViewer::OnMouseUp(const SR_UTILS_NS::MouseInputData *data) {
        if (!SR_UTILS_NS::Features::Instance().Enabled("ColorBufferPick", false)) {
            Super::OnMouseUp(data);
            return;
        }

        auto&& pGizmo = m_gizmo ? m_gizmo->GetComponent<EditorGizmo>() : nullptr;
        if (pGizmo && !pGizmo->IsGizmoEnabled()) {
            Super::OnMouseUp(data);
            return;
        }

        if (data->m_code != SR_UTILS_NS::MouseCode::MouseLeft) {
            Super::OnMouseUp(data);
            return;
        }

        auto&& pCamera = m_camera ? m_camera->GetComponent<EditorCamera>() : nullptr;
        if (!pCamera) {
            SR_WARN("SceneViewer::OnMouseUp() : editor camera component not found!");
            return Super::OnMouseUp(data);
        }

        auto&& pRenderTechnique = pCamera->GetRenderTechnique();

        if (pRenderTechnique && IsHovered() && (!pGizmo || (!pGizmo->IsGizmoActive() && !pGizmo->IsGizmoHovered()))) {
            auto&& pMesh = pRenderTechnique->PickMeshAt(pCamera->GetMousePos());
            if (auto&& pRenderComponent = dynamic_cast<SR_GTYPES_NS::IRenderComponent*>(pMesh)) {
                SelectMesh(pRenderComponent);
            }
            else {
                m_hierarchy->ClearSelected();
            }
        }

        Super::OnMouseUp(data);
    }

    void SceneViewer::LoadCameraSettings() {
        m_updateNonHoveredSceneViewer = SR_UTILS_NS::Features::Instance().Enabled("UpdateNonHoveredSceneViewer", true);

        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(CAMERA_XML);
        if (!path.Exists()) {
            return;
        }

        auto&& xmlDocument = SR_XML_NS::Document::Load(path);
        if (!xmlDocument.Valid()) {
            return;
        }

        auto&& settings = xmlDocument.Root().GetNode("Settings");
        if (!settings) {
            return;
        }

        m_cameraTranslation = settings.GetNode("Translation").GetAttribute<SR_MATH_NS::FVector3>();
        m_cameraRotation = settings.GetNode("Rotation").GetAttribute<SR_MATH_NS::FVector3>();
    }

    void SceneViewer::BackupCameraSettings() {
        auto&& xmlDocument = SR_XML_NS::Document::New();
        auto&& settings = xmlDocument.Root().AppendNode("Settings");

        settings.AppendNode("Translation").AppendAttribute<SR_MATH_NS::FVector3>(m_cameraTranslation);
        settings.AppendNode("Rotation").AppendAttribute<SR_MATH_NS::FVector3>(m_cameraRotation);

        if (!xmlDocument.Save(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(CAMERA_XML))) {
            SR_ERROR("SceneViewer::BackupCameraSettings() : failed to save camera settings!");
        }
    }

    bool SceneViewer::UpdateViewSize() {
        auto&& pCamera = m_camera->GetComponent<EditorCamera>();
        if (!pCamera) {
            SR_WARN("SceneViewer::UpdateViewSize() : editor camera component not found!");
            return false;
        }

        EditorSceneViewMode viewMode = GetSceneTools()->GetViewMode();

        if (viewMode == EditorSceneViewMode::WindowSize) {
            if (pCamera->GetSize() == GetContext()->GetWindowSize()) {
                return false;
            }

            m_id = SR_ID_INVALID;
            pCamera->UpdateProjection(GetContext()->GetWindowSize().x, GetContext()->GetWindowSize().y);
            return true;
        }
        if (viewMode == EditorSceneViewMode::FreeAspect) {
            if (pCamera->GetSize() == m_windowSize) {
                return false;
            }

            m_id = SR_ID_INVALID;
            pCamera->UpdateProjection(m_windowSize.x, m_windowSize.y);
            return true;
        }

        return false;
    }

    void SceneViewer::SelectMesh(SR_GTYPES_NS::IRenderComponent* pMesh) {
        if (m_hierarchy->GetSelected().size() != 1) {
            m_hierarchy->SelectGameObject(pMesh->GetRoot());
            return;
        }

        SR_UTILS_NS::SceneObject::Ptr pGameObject = *m_hierarchy->GetSelected().begin();

        if (pGameObject == pMesh->GetRoot()) {
            m_hierarchy->SelectGameObject(pMesh->GetSceneObject());
            return;
        }

        if (pGameObject == pMesh->GetGameObject()) {
            m_hierarchy->SelectGameObject(pMesh->GetRoot());
            return;
        }

        m_hierarchy->SelectGameObject(pMesh->GetRoot());
    }

    SR_MATH_NS::FPoint SceneViewer::GetImagePosition() const {
        return SR_MATH_NS::FPoint(m_imagePosition.x, m_imagePosition.y);
    }

    void SceneViewer::SetGizmoEnabled(bool enabled) {
        if (!SR_UTILS_NS::Features::Instance().Enabled("Gizmo", true)) {
            return;
        }

        SR_UTILS_NS::GameObject::Ptr pGizmo;

        if (enabled) {
            if (m_scene) {
                pGizmo = m_scene->InstanceGameObject("Editor gizmo"_atom);
                pGizmo->AddSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave);
                pGizmo->AddEditorFlags(SR_UTILS_NS::EditorFlags::Hidden);
            }
            else {
                return;
            }

            auto&& pComponent = SR_UTILS_NS::Factory::Instance().Create<EditorGizmo>();
            pComponent->SetOperation(GetSceneTools()->GetGizmoOperation());
            pComponent->SetMode(GetSceneTools()->GetGizmoMode());
            pComponent->SetHierarchy(m_hierarchy);
            pGizmo->AddComponent(pComponent.StaticCast<SR_UTILS_NS::Component>());
        }

        if (m_gizmo) {
            m_gizmo->Destroy();
        }

        m_gizmo = pGizmo;
    }

    SR_CORE_GUI_NS::SceneTools* SceneViewer::GetSceneTools() const {
        for (auto&& pSubWidget : m_subWidgets) {
            if (auto&& pSceneTools = dynamic_cast<SceneTools*>(pSubWidget)) {
                return pSceneTools;
            }
        }

        return nullptr;
    }
}
