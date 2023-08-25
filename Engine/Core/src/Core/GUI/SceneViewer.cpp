//
// Created by Monika on 11.02.2022.
//

#include <Core/GUI/SceneViewer.h>
#include <Core/GUI/Hierarchy.h>
#include <Core/GUI/EditorCamera.h>
#include <Core/GUI/Guizmo.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Common/Features.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/World/SceneLogic.h>

#include <Graphics/Window/Window.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Pass/ColorBufferPass.h>

namespace SR_CORE_NS::GUI {
    SceneViewer::SceneViewer(const WindowPtr& window, Hierarchy* hierarchy)
        : Widget("Scene")
        , m_window(window)
        , m_hierarchy(hierarchy)
        , m_guizmo(new Guizmo())
        , m_id(-1)
    {
        LoadCameraSettings();
    }

    SceneViewer::~SceneViewer() {
        Enable(false);
        SR_SAFE_DELETE_PTR(m_guizmo);
    }

    void SceneViewer::SetCamera(const GameObjectPtr& camera) {
        if (m_camera) {
            m_camera->Destroy();
        }

        m_camera.Replace(camera);

        BackupCameraSettings();
    }

    void SceneViewer::Draw() {
        if (!m_scene.RecursiveLockIfValid()) {
            return;
        }

        if (m_camera.RecursiveLockIfValid()) {
            m_translation = m_camera->GetTransform()->GetTranslation();
            m_rotation = m_camera->GetTransform()->GetRotation();

            auto pCamera = m_camera->GetComponent<SR_GTYPES_NS::Camera>();

            if (auto&& pFramebuffer = GetContext()->FindFramebuffer("SceneViewFBO", pCamera)) {
                m_id = pFramebuffer->GetColorTexture(0);
            }

            if (pCamera && m_id != SR_ID_INVALID && pCamera->IsActive()) 
            {
                m_guizmo->DrawTools(); //Отрисовка панели с переключателями

                ImGui::BeginGroup();

                ImGui::Separator();

                if (ImGui::BeginChild("ViewerTexture")) {
                    const auto winSize = ImGui::GetWindowSize();

                    DrawTexture(SR_MATH_NS::IVector2(winSize.x, winSize.y), m_window->GetSize().Cast<int32_t>(), m_id, true);

                    if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1)
                        m_guizmo->Draw(*selected.begin(), m_camera);

                    CheckFocused();
                    CheckHovered();
                }
                ImGui::EndChild();

                ImGui::EndGroup();
            }

            m_camera.Unlock();
        }
        else {
            m_camera = m_scene->Find("Editor camera");
        }

        m_scene.Unlock();
    }

    void SceneViewer::SetScene(const SR_WORLD_NS::Scene::Ptr& scene) {
        SetCamera(GameObjectPtr());
        m_scene.Replace(scene);
        Enable(m_enabled);
    }

    void SceneViewer::Enable(bool value) {
        m_enabled = value;

        if (!m_scene) {
            SetCamera(GameObjectPtr());
            return;
        }

        auto&& pLogic = m_scene->GetLogicBase();

        /// если сцена сломана, или это "пустышка", то не создаем камеру, т.к. рендерить нет смыла 
        if (!pLogic || pLogic->IsDefault()) {
            SetCamera(GameObjectPtr());
            return;
        }

        if (m_enabled) {
            if (!m_camera.Valid()) {
                InitCamera();
            }
        }
        else {
            SetCamera(GameObjectPtr());
        }
    }

    void SceneViewer::FixedUpdate() {
        float_t velocityFactor = m_guizmo->GetCameraVelocityFactor();
        m_velocity *= 0.8f;

        if (!m_velocity.Empty() && m_camera) {
            m_camera->GetTransform()->Translate(m_velocity);
        }

        if (!IsOpen() || (!IsHovered() && !m_updateNonHoveredSceneViewer)) {
            return;
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

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
                m_velocity += SR_UTILS_NS::Transform3D::UP * velocitySpeed;
            }

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

        //m_velocity = m_velocity.Clamp(SR_MATH_NS::FVector3(1), SR_MATH_NS::FVector3(-1)); ///Зачем-то ограничивало перемещение камеры по клавишам WASD
    }

    void SceneViewer::DrawTexture(SR_MATH_NS::IVector2 winSize, SR_MATH_NS::IVector2 texSize, uint32_t id, bool centralize) {
        const float_t dx = static_cast<float_t>(winSize.x) / texSize.x;
        const float_t dy = static_cast<float_t>(winSize.y) / texSize.y;

        if (dy > dx) {
            texSize *= dx;
        }
        else
            texSize *= dy;

        m_textureSize = texSize;

        if (centralize) {
            auto windowPosition = ImGui::GetCursorPos();
            auto res = (winSize - m_textureSize) * 0.5f;
            ImVec2 centralizedCursorPos = { (float)res.x, (float)res.y };
            centralizedCursorPos = ImClamp(centralizedCursorPos, windowPosition, centralizedCursorPos);
            ImGui::SetCursorPos(centralizedCursorPos);
        }

        auto&& env = SR_GRAPH_NS::Environment::Get();
        if (env->GetType() == Graphics::PipelineType::OpenGL) {
            DrawImage(reinterpret_cast<void*>(static_cast<uint64_t>(id)), ImVec2(m_textureSize.x, m_textureSize.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1 }, {0, 0, 0, 0 }, true);
        }
        else if (auto&& pDescriptor = env->TryGetDescriptorSetFromTexture(id, true)) {
            DrawImage(pDescriptor, ImVec2(m_textureSize.x, m_textureSize.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
        }
    }

    void SceneViewer::DrawImage(ImTextureID user_texture_id, const ImVec2 &size, const ImVec2 &uv0, const ImVec2 &uv1, const ImVec4 &tint_col, const ImVec4 &border_col, bool imposition) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
        if (border_col.w > 0.0f)
            bb.Max = bb.Max + ImVec2(2, 2);

        if (!imposition) {
            ImGui::ItemSize(bb);
            if (!ImGui::ItemAdd(bb, 0))
                return;
        }

        m_imagePosition = bb.GetTL();

        if (border_col.w > 0.0f) {
            window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
            window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
        }
        else
            window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
    }

    void SceneViewer::InitCamera() {
        SR_UTILS_NS::GameObject::Ptr camera;

        /// сцена может быть уже заблокирована до Engine::SetScene
        if (SR_UTILS_NS::Features::Instance().Enabled("EditorCamera", true) && m_scene.RecursiveLockIfValid()) {
            camera = m_scene->Instance("Editor camera");
            camera->SetFlags(SR_UTILS_NS::GAMEOBJECT_FLAG_NO_SAVE);
            m_isPrefab = m_scene->IsPrefab();
            m_scene.Unlock();
        }
        else {
            return;
        }

        const auto size = m_window->GetSize();

        auto&& pCamera = new EditorCamera(size.x, size.y);

        if (m_isPrefab) {
            pCamera->SetRenderTechnique(SR_CORE_NS::EditorSettings::Instance().GetPrefabEditorRenderTechnique());
        }
        else {
            pCamera->SetRenderTechnique(SR_CORE_NS::EditorSettings::Instance().GetRenderTechnique());
        }

        camera->AddComponent(pCamera);

        /// Камера редактора имеет наивысшый закадровый приоритет
        pCamera->SetPriority(SR_INT32_MIN);

        camera->GetTransform()->GlobalTranslate(m_translation);
        camera->GetTransform()->GlobalRotate(m_rotation);

        SetCamera(camera);
    }

    void SceneViewer::OnClose() {
        Enable(false);
    }

    void SceneViewer::OnOpen() {
        Enable(true);
    }

    void SceneViewer::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        m_guizmo->OnKeyDown(data);
        Widget::OnKeyDown(data);
    }

    void SceneViewer::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) {
        m_guizmo->OnKeyPress(data);
        Widget::OnKeyPress(data);
    }

    void SceneViewer::OnMouseDown(const SR_UTILS_NS::MouseInputData *data) {
        Super::OnMouseDown(data);
    }

    void SceneViewer::OnMouseUp(const SR_UTILS_NS::MouseInputData *data) {
        if (!SR_UTILS_NS::Features::Instance().Enabled("ColorBufferPick", false)) {
            Super::OnMouseUp(data);
            return;
        }

        if (data->m_code != SR_UTILS_NS::MouseCode::MouseLeft || m_guizmo->IsUse()) {
            Super::OnMouseUp(data);
            return;
        }

        auto&& mousePos = ImGui::GetMousePos() - m_imagePosition;

        const float_t x = mousePos.x / m_textureSize.x;
        const float_t y = mousePos.y / m_textureSize.y;

        auto&& pCamera = m_camera ? m_camera->GetComponent<SR_GTYPES_NS::Camera>() : nullptr;
        if (!pCamera) {
            return Super::OnMouseUp(data);
        }

        auto&& pRenderTechnique = pCamera->GetRenderTechnique();
        if (!pRenderTechnique) {
            return Super::OnMouseUp(data);
        }

        if (auto&& pColorPass = dynamic_cast<Graphics::ColorBufferPass*>(pRenderTechnique->FindPass("ColorBufferPass"))) {
            /// auto&& color = pColorPass->GetColor(x, y);
            /// auto&& index = pColorPass->GetIndex(x, y);
            /// SR_LOG(SR_FORMAT("%f, %f, %f, %f - %i", color.r, color.g, color.b, color.a, index));

            if (auto&& pMesh = dynamic_cast<SR_GTYPES_NS::MeshComponent*>(pColorPass->GetMesh(x, y))) {
                m_hierarchy->SelectGameObject(pMesh->GetRoot());
            }
            else if (IsHovered()) { ///список выделенных объектов не должен очищаться, если клик не прожат по самой сцене, вероятно стоит сам клик обрабатывать с этим условием
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

        m_translation = settings.GetNode("Translation").GetAttribute<SR_MATH_NS::FVector3>();
        m_rotation = settings.GetNode("Rotation").GetAttribute<SR_MATH_NS::FVector3>();
    }

    void SceneViewer::BackupCameraSettings() {
        auto&& xmlDocument = SR_XML_NS::Document::New();
        auto&& settings = xmlDocument.Root().AppendNode("Settings");

        settings.AppendNode("Translation").AppendAttribute<SR_MATH_NS::FVector3>(m_translation);
        settings.AppendNode("Rotation").AppendAttribute<SR_MATH_NS::FVector3>(m_rotation);

        if (!xmlDocument.Save(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(CAMERA_XML))) {
            SR_ERROR("SceneViewer::BackupCameraSettings() : failed to save camera settings!");
        }
    }
}