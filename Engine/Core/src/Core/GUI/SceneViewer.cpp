//
// Created by Monika on 11.02.2022.
//

#include <Core/GUI/SceneViewer.h>
#include <Core/GUI/Hierarchy.h>
#include <Core/GUI/EditorCamera.h>
#include <Core/GUI/EditorGizmo.h>
#include <Core/GUI/Guizmo.h>
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
        if (!m_scene.RecursiveLockIfValid()) {
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
                m_platform->AddSerializationFlags(SR_UTILS_NS::ObjectSerializationFlags::DontSave);
                if (!m_platform->GetChildren().empty()) {
                    if (auto&& pMesh = m_platform->GetChildren()[0]->GetComponent<SR_GTYPES_NS::Mesh3D>()) {
                        auto&& pMaterial = new SR_GRAPH_NS::UniqueMaterial();
                        pMaterial->SetShader("Engine/Shaders/CascadedShadowMap/spatial.srsl");
                        pMaterial->SetTexture("diffuse"_atom, GetRenderScene()->GetRenderStrategy()->GetRenderContext()->GetDefaultTexture());
                        pMesh->SetMaterial(pMaterial);
                    }
                }
                m_platform->GetTransform()->SetScale(2.5, 1.f, 2.5);
            }
        }

        if (m_camera.RecursiveLockIfValid()) {
            m_cameraTranslation = m_camera->GetTransform()->GetTranslation();
            m_cameraRotation = m_camera->GetTransform()->GetRotation();

            auto pCamera = m_camera->GetComponent<SR_GTYPES_NS::Camera>();

            ImGui::BeginGroup();

            for (auto&& pSubWidget : m_subWidgets) {
                pSubWidget->DrawAsSubWindow();
            }

            ImGui::Separator();

            if (auto&& pFrameBuffer = GetContext()->FindFramebuffer("SceneViewFBO"_atom, pCamera.Get())) {
                m_id = pFrameBuffer->GetColorTexture(0);
            }

            if (ImGui::BeginChild("ViewerTexture"))
            {
                m_windowSize = SR_MATH_NS::Vector2(static_cast<int32_t>(ImGui::GetWindowSize().x), static_cast<int32_t>(ImGui::GetWindowSize().y));

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
                ImGui::EndChild();
            }

            ImGui::EndGroup();

            m_camera.Unlock();
        }
        else {
            m_camera = m_scene->Find("Editor camera"_atom).DynamicCast<SR_UTILS_NS::GameObject>();
        }

        m_scene.Unlock();
    }

    void SceneViewer::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        m_scene = scene;
        Enable(m_enabled);
    }

    void SceneViewer::Enable(bool value) {
        m_enabled = value;

        auto&& pLogic = m_scene ? m_scene->GetLogicBase() : SR_WORLD_NS::SceneLogic::Ptr();

        /// если сцена сломана, или это "пустышка", то не создаем камеру, т.к. рендерить нет смыла 
        if (!pLogic || pLogic->IsDefault() || !m_enabled) {
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
        float_t velocityFactor = GetSceneTools()->GetCameraVelocityFactor();
        m_velocity *= 0.8f;

        if (!m_velocity.Empty() && m_camera) {
            m_camera->GetTransform()->Translate(m_velocity);
        }

        if (!IsOpen() || (!IsHovered() && !m_updateNonHoveredSceneViewer)) {
            return;
        }

        if (m_camera && !m_gizmo) {
            SetGizmoEnabled(true); /// если пропал, вернем
        }

        constexpr float_t seekSpeed = 0.1f / 10.f;
        constexpr float_t wheelSpeed = 4.0f / 10.f;
        constexpr float_t rotateSpeed = 1.5f / 10.f;
        constexpr float_t moveSpeed = 2.0f / 10.f;

        const float_t velocitySpeed = moveSpeed * velocityFactor;
        auto&& dir = SR_UTILS_NS::Input::Instance().GetMouseDrag();
        auto&& wheel = SR_UTILS_NS::Input::Instance().GetMouseWheel() * wheelSpeed * velocityFactor;

        if (!SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Ctrl))
        {
            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                m_velocity += SR_UTILS_NS::Transform3D::FORWARD * velocitySpeed;
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::S)) {
                m_velocity -= SR_UTILS_NS::Transform3D::FORWARD * velocitySpeed;
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::A)) {
                m_velocity -= SR_UTILS_NS::Transform3D::RIGHT * velocitySpeed;
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::D)) {
                m_velocity += SR_UTILS_NS::Transform3D::RIGHT * velocitySpeed;
            }

            /// !!!!! НЕ ВОЗВОРАЩАТЬ ЭТОТ КОД !!!!!
            /// if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
            ///     m_velocity += SR_UTILS_NS::Transform3D::UP * velocitySpeed;
            /// }

            /// TODO: странное управление. Нет подходящей удобной комбинации клавиши
            /// if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space) && SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Z)) {
            ///     m_velocity -= SR_UTILS_NS::Transform3D::UP * moveSpeed;
            /// }
        }

        if (m_camera) {
            if (wheel != 0) {
                m_camera->GetTransform()->Translate(SR_UTILS_NS::Transform3D::FORWARD * wheel);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseRight)) {
                m_camera->GetTransform()->GlobalRotate(dir.y * rotateSpeed, dir.x * rotateSpeed, 0.0);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseMiddle)) {
                auto right = SR_UTILS_NS::Transform3D::RIGHT * seekSpeed;
                auto up = SR_UTILS_NS::Transform3D::UP * seekSpeed;

                m_camera->GetTransform()->Translate(
                        (up * dir.y) + (right * -dir.x)
                );
            }
        }

        /// m_velocity = m_velocity.Clamp(SR_MATH_NS::FVector3(1), SR_MATH_NS::FVector3(-1)); ///Зачем-то ограничивало перемещение камеры по клавишам WASD
    }

    void SceneViewer::DrawTexture(SR_MATH_NS::IVector2 winSize, SR_MATH_NS::IVector2 texSize, uint32_t id, bool centralize) {
        if (texSize.HasNegative() || winSize.HasNegative()) {
            return;
        }

        const float_t dx = static_cast<float_t>(winSize.x) / static_cast<float_t>(texSize.x);
        const float_t dy = static_cast<float_t>(winSize.y) / static_cast<float_t>(texSize.y);

        texSize *= dy > dx ? dx : dy;

        m_textureSize = texSize;

        if (centralize) {
            auto windowPosition = ImGui::GetCursorPos();
            auto res = (winSize - m_textureSize) * 0.5f;
            ImVec2 centralizedCursorPos = { (float)res.x, (float)res.y };
            centralizedCursorPos = ImClamp(centralizedCursorPos, windowPosition, centralizedCursorPos);
            ImGui::SetCursorPos(centralizedCursorPos);
        }

        auto&& pPipeline = GetContext()->GetPipeline();
        m_imagePosition = SR_GRAPH_GUI_NS::DrawTexture(pPipeline.Get(), id, m_textureSize, false);
    }

    void SceneViewer::SetCameraEnabled(bool enabled) {
        SR_UTILS_NS::GameObject::Ptr camera;

        if (enabled) {
            /// сцена может быть уже заблокирована до Engine::SetScene
            if (SR_UTILS_NS::Features::Instance().Enabled("EditorCamera", true) && m_scene.RecursiveLockIfValid()) {
                camera = m_scene->InstanceGameObject("Editor camera"_atom);
                camera->AddSerializationFlags(SR_UTILS_NS::ObjectSerializationFlags::DontSave);
                m_isPrefab = m_scene->IsPrefab();
                m_scene.Unlock();
            }
            else {
                return;
            }

            auto&& pCamera = new EditorCamera(this);

            if (m_isPrefab) {
                pCamera->SetRenderTechnique(SR_CORE_NS::EditorSettings::Instance().GetPrefabEditorRenderTechnique());
            }
            else {
                pCamera->SetRenderTechnique(SR_CORE_NS::EditorSettings::Instance().GetRenderTechnique());
            }

            camera->AddComponent(pCamera);

            /// Камера редактора имеет наивысшый закадровый приоритет
            pCamera->SetPriority(SR_INT32_MIN);

            camera->GetTransform()->GlobalTranslate(m_cameraTranslation);
            camera->GetTransform()->GlobalRotate(m_cameraRotation);
        }

        if (m_camera) {
            m_camera->Destroy();
        }

        m_camera = camera;

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

    void SceneViewer::OnMouseDown(const SR_UTILS_NS::MouseInputData *data) {
        if(data->m_code == SR_UTILS_NS::MouseCode::MouseRight) {
            m_cursorLockOpt.emplace();
            m_mousePos = data->m_position;
        }
    }

    void SceneViewer::OnMouseUp(const SR_UTILS_NS::MouseInputData *data) {
        if (!SR_UTILS_NS::Features::Instance().Enabled("ColorBufferPick", false)) {
            Super::OnMouseUp(data);
            return;
        }

        if (data->m_code == SR_UTILS_NS::MouseCode::MouseRight) {
            m_cursorLockOpt = std::nullopt;
            SR_PLATFORM_NS::SetMousePos({ static_cast<int32_t>(m_mousePos.x), static_cast<int32_t>(m_mousePos.y) });
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

        auto&& pCamera = m_camera ? m_camera->GetComponent<SR_GTYPES_NS::Camera>() : nullptr;
        if (!pCamera) {
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
        auto&& pCamera = m_camera->GetComponent<SR_GTYPES_NS::Camera>();
        if (!pCamera) {
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

        SR_UTILS_NS::GameObject::Ptr gizmo;

        if (enabled) {
            if (m_scene.RecursiveLockIfValid()) {
                gizmo = m_scene->InstanceGameObject("Editor gizmo"_atom);
                gizmo->AddSerializationFlags(SR_UTILS_NS::ObjectSerializationFlags::DontSave);
                m_scene.Unlock();
            }
            else {
                return;
            }

            auto&& pComponent = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<EditorGizmo>();
            pComponent->SetOperation(GetSceneTools()->GetGizmoOperation());
            pComponent->SetMode(GetSceneTools()->GetGizmoMode());
            pComponent->SetHierarchy(m_hierarchy);
            gizmo->AddComponent(pComponent);
        }

        if (m_gizmo) {
            m_gizmo->Destroy();
        }

        m_gizmo = gizmo;
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