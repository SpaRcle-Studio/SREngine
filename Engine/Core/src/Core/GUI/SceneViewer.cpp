//
// Created by Monika on 11.02.2022.
//

#include <Core/GUI/SceneViewer.h>
#include <Core/GUI/Hierarchy.h>

#include <Utils/Input/InputSystem.h>
#include <GUI/Editor/Guizmo.h>
#include <Utils/Common/Features.h>
#include <Utils/ECS/Transform3D.h>
#include <Window/Window.h>
#include <Render/Camera.h>

void SceneViewer::SetCamera(const GameObjectPtr& camera) {
    m_camera.AutoFree([this](SR_UTILS_NS::GameObject* camera) {
        m_translation = camera->GetTransform()->GetTranslation();
        m_rotation = camera->GetTransform()->GetRotation();
        camera->Destroy();
    });

    m_camera.Replace(camera);
}

void SceneViewer::Draw() {
    if (m_camera.LockIfValid()) {
        auto camera = m_camera->GetComponent<SR_GRAPH_NS::Camera>();
        //if (m_id = camera->GetPostProcessing()->GetFinally(); m_id >= 0 && camera->IsReady()) {
        if (m_id = SR_ID_INVALID; m_id >= 0 && camera->IsActive()) {
            m_guizmo->DrawTools();

            ImGui::BeginGroup();

            ImGui::Separator();

            if (ImGui::BeginChild("ViewerTexture")) {
                const auto winSize = ImGui::GetWindowSize();

                //DrawTexture(SR_MATH_NS::IVector2(winSize.x, winSize.y), m_window->GetWindowSize(), m_id, true);

                //if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1)
                //    m_guizmo->Draw(*selected.begin(), m_camera);

                CheckFocused();
                CheckHovered();
            }
            ImGui::EndChild();

            ImGui::EndGroup();
        }

        m_camera.Unlock();
    }
}

void SceneViewer::SetScene(SR_WORLD_NS::Scene::Ptr scene) {
    m_scene.Replace(scene);
    SetCameraActive(m_cameraActive);
}

SceneViewer::SceneViewer(Graphics::Window* window, Hierarchy* hierarchy)
    : Widget("Scene")
    , m_window(window)
    , m_hierarchy(hierarchy)
    , m_guizmo(new Guizmo())
    , m_id(-1)
{
    m_updateNonHoveredSceneViewer = SR_UTILS_NS::Features::Instance().Enabled("UpdateNonHoveredSceneViewer", true);
}

SceneViewer::~SceneViewer() {
    SetCameraActive(false);
    SR_SAFE_DELETE_PTR(m_guizmo);
}

void SceneViewer::Enable(bool value) {
    m_enabled = value;

    if (m_camera.LockIfValid()) {
        if (auto* camera = m_camera->GetComponent<SR_GRAPH_NS::Camera>()) {
            //camera->SetDirectOutput(!m_enabled);
        }
        m_camera.Unlock();
    }
}

void SceneViewer::Update() {
    if (!IsOpen() || (!IsHovered() && !m_updateNonHoveredSceneViewer))
        return;

    float_t speed = 0.1f;
    auto dir = SR_UTILS_NS::Input::Instance().GetMouseDrag() * speed;
    auto wheel = SR_UTILS_NS::Input::Instance().GetMouseWheel() * speed;

    if (m_camera.LockIfValid()) {
        if (wheel != 0) {
            m_camera->GetTransform()->Translate(SR_UTILS_NS::Transform3D::FORWARD * wheel);
        }

        if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseRight)) {
            m_camera->GetTransform()->GlobalRotate(dir.y, dir.x, 0.0);
        }

        if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseMiddle)) {
            auto right = SR_UTILS_NS::Transform3D::RIGHT * speed;
            auto up = SR_UTILS_NS::Transform3D::UP * speed;

            m_camera->GetTransform()->Translate(
                    (up * dir.y) + (right * -dir.x)
            );
        }

        m_camera.Unlock();
    }
}

void SceneViewer::DrawTexture(SR_MATH_NS::IVector2 winSize, SR_MATH_NS::IVector2 texSize, uint32_t id, bool centralize)        {
    const float_t dx = static_cast<float_t>(winSize.x) / texSize.x;
    const float_t dy = static_cast<float_t>(winSize.y) / texSize.y;

    if (dy > dx)
        texSize *= dx;
    else
        texSize *= dy;

    // Because I use the texture from OpenGL, I need to invert the V from the UV.

    if (centralize) {
        ImVec2 initialCursorPos = ImGui::GetCursorPos();
        auto res = (winSize - texSize) * 0.5f;
        ImVec2 centralizedCursorPos = { (float)res.x, (float)res.y };
        centralizedCursorPos = ImClamp(centralizedCursorPos, initialCursorPos, centralizedCursorPos);
        ImGui::SetCursorPos(centralizedCursorPos);
    }

    auto&& env = SR_GRAPH_NS::Environment::Get();
    if (env->GetPipeLine() == Graphics::PipeLine::OpenGL)
        DrawImage(reinterpret_cast<void*>(static_cast<uint64_t>(id)), ImVec2(texSize.x, texSize.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1 }, {0, 0, 0, 0 }, true);
    else {
        DrawImage(env->GetDescriptorSetFromTexture(id, true), ImVec2(texSize.x, texSize.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
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

    if (border_col.w > 0.0f) {
        window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
        window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
    }
    else
        window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
}

void SceneViewer::InitCamera() {
    Helper::GameObject::Ptr camera;

    /// сцена может быть уже заблокирована до Engine::SetScene
    if (m_scene.RecursiveLockIfValid()) {
        camera = m_scene->Instance("Editor camera");
        m_scene.Unlock();
    }
    else
        return;

    const auto size = m_window->GetWindowSize();
    auto component = SR_GRAPH_NS::Camera::Allocate(size.x, size.y);
    //component->SetDirectOutput(true);
    camera->AddComponent(component);

    camera->GetTransform()->GlobalTranslate(m_translation);
    camera->GetTransform()->GlobalRotate(m_rotation);

    SetCamera(camera);
}

void SceneViewer::OnClose() {
    SetCameraActive(false);
}

void SceneViewer::OnOpen() {
    SetCameraActive(true);
}

void SceneViewer::SetCameraActive(bool value) {
    m_window->BeginSync();

    if ((m_cameraActive = value)) {
        if (!m_camera.Valid()) {
            InitCamera();
            Enable(m_enabled);
        }
    }
    else
        SetCamera(GameObjectPtr());

    m_window->EndSync();
}

void SceneViewer::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
    m_guizmo->OnKeyDown(data);
}

void SceneViewer::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) {
    m_guizmo->OnKeyPress(data);
}
