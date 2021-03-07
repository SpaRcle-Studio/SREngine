//
// Created by Monika on 14.02.2021.
//

#include <vector>
#include <GUI/GUIWindow.h>
#include <EntityComponentSystem/Transform.h>
#include <EntityComponentSystem/Scene.h>
#include <EntityComponentSystem/Component.h>
#include <imgui_stdlib.h>
#include <Render/Camera.h>
#include <Render/PostProcessing.h>
#include <Types/Mesh.h>

#include <glm/gtc/type_ptr.inl>

void Framework::Graphics::GUI::GUIWindow::DrawChild(Framework::Helper::GameObject *root) noexcept {
    unsigned long i = 0;

    for (Helper::GameObject*  child : root->GetChildrenRef()) {
        if (child->HasChildren()) {
            bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                          g_node_flags_with_child |
                                          (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                          "%s", child->GetName().c_str()
            );

            CheckSelected(child);

            if (open)
                DrawChild(child);
        } else {
            ImGui::TreeNodeEx((void *) (intptr_t) i,
                              g_node_flags_without_child | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                              "%s", child->GetName().c_str()
            );

            CheckSelected(child);
        }

        i++;
    }

    ImGui::TreePop();
}

void Framework::Graphics::GUI::GUIWindow::DrawHierarchy(Framework::Helper::Scene *scene) noexcept {
    auto root = scene->GetRootGameObjects();

    unsigned long i = 0;

    GUIWindow::g_shiftPressed = Helper::InputSystem::IsPressed(Helper::KeyCode::LShift);

    if (ImGui::TreeNodeEx(scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

        for (Helper::GameObject* obj : root){
            if (obj->HasChildren()) {
                bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                              g_node_flags_with_child     | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                              "%s", obj->GetName().c_str());

                CheckSelected(obj);

                if (open)
                    DrawChild(obj);
            } else {
                ImGui::TreeNodeEx((void *) (intptr_t) i,
                                  g_node_flags_without_child | (obj->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                  "%s", obj->GetName().c_str());

                CheckSelected(obj);
            }

            i++;
        }

        ImGui::TreePop();
        ImGui::PopStyleVar();
    }
}

void Framework::Graphics::GUI::GUIWindow::CheckSelected(Framework::Helper::GameObject *gm) noexcept {
    if (ImGui::IsItemClicked()) {
        if (!g_shiftPressed)
            gm->GetScene()->UnselectAll();

        gm->SetSelect(true);
    }
}

void Framework::Graphics::GUI::GUIWindow::DrawInspector(Framework::Helper::GameObject *gameObject) noexcept {
    //DrawTextOnCenter(gameObject->GetName());
    //ImGui::Text(("Tag:  " + gameObject->GetTag()).c_str());

    std::string gm_name = gameObject->GetName();
    if (ImGui::InputText("Name", &gm_name))
        gameObject->SetNameFromInspector(gm_name);

    ImGui::Separator();
    DrawTextOnCenter("Transform");

    auto position = gameObject->GetTransform()->GetPosition().ToGLM();
    auto rotation = gameObject->GetTransform()->GetRotation().ToGLM();
    auto scale = gameObject->GetTransform()->GetScale().ToGLM();

    ImGui::Text("[Global]");

    if (ImGui::InputFloat3("G Tr", &position[0])) {
        gameObject->GetTransform()->SetPosition(position, g_currentGuizmoPivot);
    }
    if (ImGui::InputFloat3("G Rt", &rotation[0])) {
        //gameObject->GetTransform()->SetRotation(Vector3::FromGLM(rotation), g_currentGuizmoPivot);
        //gameObject->GetTransform()->SetRotation(Quaternion(glm::quat(glm::radians(rotation))), g_currentGuizmoPivot);
        //gameObject->GetTransform()->SetRotation(glm::radians(rotation), g_currentGuizmoPivot);
        //gameObject->GetTransform()->SetRotation(Vector3(rotation).Radians(), g_currentGuizmoPivot);
        gameObject->GetTransform()->SetRotation(rotation, g_currentGuizmoPivot);
    }
    if (ImGui::InputFloat3("G Sc", &scale[0])) {
        gameObject->GetTransform()->SetScale(scale, g_currentGuizmoPivot);
    }

    ImGui::Text("[Local]");

    position = gameObject->GetTransform()->GetPosition(true).ToGLM();
    rotation = gameObject->GetTransform()->GetRotation(true).ToGLM();
    scale = gameObject->GetTransform()->GetScale(true).ToGLM();

    ImGui::InputFloat3("L Tr", &position[0]);
    if (ImGui::InputFloat3("L Rt", &rotation[0]))
        gameObject->GetTransform()->SetLocalRotation(rotation);
    ImGui::InputFloat3("L Sc", &scale[0]);

    ImGui::Text("[Parent direction]");

    glm::vec3 p_dir = gameObject->GetTransform()->GetParentDir().ToGLM();
    ImGui::InputFloat3("Dir", &p_dir[0]);

    std::vector<Framework::Helper::Component*> comps = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : comps) {
        ImGui::Separator();
        std::string name = comp->GetComponentName();
        DrawTextOnCenter(name);

        if (name == "Camera") {
            ImGui::Separator();

            DrawTextOnCenter("PostProcessing");

            PostProcessing* post = dynamic_cast<Camera*>(comp)->GetPostProcessing();

            float gamma = post->GetGamma();
            if (ImGui::InputFloat("Gamma", &gamma, 0.05))
                post->SetGamma(gamma);

            float exposure = post->GetExposure();
            if (ImGui::InputFloat("Exposure", &exposure, 0.05))
                post->SetExposure(exposure);

            float saturation = post->GetSaturation();
            if (ImGui::InputFloat("Saturation", &saturation, 0.05))
                post->SetSaturation(saturation);

            glm::vec3 color = post->GetColorCorrection();
            if (ImGui::InputFloat3("Color correction", &color[0]))
                post->SetColorCorrection(color);

            ImGui::NewLine();

            bool enabled = post->GetBloomEnabled();
            if (ImGui::Checkbox("Bloom", &enabled))
                post->SetBloom(enabled);

            ImGui::NewLine();

            float bloom_intensity = post->GetBloomIntensity();
            if (ImGui::InputFloat("Bloom intensity", &bloom_intensity, 0.1))
                post->SetBloomIntensity(bloom_intensity);

            color = post->GetBloomColor();
            if (ImGui::InputFloat3("Bloom color", &color[0]))
                post->SetBloomColor(color);

            int bloom_amount = post->GetBloomAmount();
            if (ImGui::InputInt("Bloom amount", &bloom_amount)) {
                if (bloom_amount == 0)
                    bloom_amount = 1;
                post->SetBloomAmount(bloom_amount);
            }
        }
        else if (name == "Mesh") {
            auto* mesh = dynamic_cast<Graphics::Types::Mesh*>(comp);
            auto* mat  = mesh->GetMaterial();

            ImGui::Text("Geometry name: %s", mesh->GetGeometryName().c_str());
            ImGui::Text("Vertices count: %zu", mesh->GetCountVertices());

            ImGui::Separator();

            DrawTextOnCenter("Material");

            glm::vec3 color = mat->GetColor().ToGLM();
            if (ImGui::InputFloat3("Color", &color[0]))
                mat->SetColor(color);

            bool enabled = mat->GetBloomEnabled();
            if (ImGui::Checkbox("Bloom enabled", &enabled))
                mat->SetBloom(enabled);
        }
    }
}

void Framework::Graphics::GUI::GUIWindow::DrawGuizmo(Framework::Graphics::Camera *camera, GameObject *gameObject, glm::vec2 img_size) noexcept {
    if (!camera || !gameObject)
        return;

    //ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

    /*const float *pSource = (const float*)glm::value_ptr(camera->GetAlternativeView());
    float cameraView[16] = {0.f};
    for (int i = 0; i < 16; ++i)
        cameraView[i] = pSource[i];

    const float *p2Source = (const float*)glm::value_ptr(camera->GetProjection());
    float cameraProjection[16] = {0.f};
    for (int i = 0; i < 16; ++i)
        cameraProjection[i] = p2Source[i];

            const float *p3Source = (const float*)glm::value_ptr();
    float matrix[16] = {0.f};
    for (int i = 0; i < 16; ++i)
        matrix[i] = p3Source[i];
*/

    ImGuiWindow *window = ImGui::GetCurrentWindow();
    if (!window || window->SkipItems)
        return;

    glm::vec2 pos = {window->Pos.x, window->Pos.y};
    glm::vec2 win_size = {window->Size.x, window->Size.y};

    const float dx = win_size.x / img_size.x;
    const float dy = win_size.y / img_size.y;

    if (dx > dy)
        img_size *= dy;
    else if (dy > dx)
        img_size *= dx;
    else
        img_size *= dy;

    static const ImVec4 def = {0.1, 0.1, 0.1, 0.7};
    static const ImVec4 act = {0.6, 0.6, 0.6, 0.85};
    static const ImVec2 sizeB = {30, 25};
    static const short space = 3;
    static int snapValue = 100;

    static bool boundsAct = false;
    static bool snapAct = true;
    //static float snap[3] = { 1.f, 1.f, 1.f };

    if (ButtonWithId("engine_tool_move", "M", sizeB, 0, true,
                     ImVec2(space, space), g_currentGuizmoOperation == ImGuizmo::TRANSLATE ? act : def)) {
        g_currentGuizmoOperation = ImGuizmo::TRANSLATE;
        boundsAct = false;
    }

    if (ButtonWithId("engine_tool_rotate", "R", sizeB, 0, true,
                     ImVec2(space * 2 + sizeB.x, space), g_currentGuizmoOperation == ImGuizmo::ROTATE ? act : def)) {
        g_currentGuizmoOperation = ImGuizmo::ROTATE;
        boundsAct = false;
    }

    if (ButtonWithId("engine_tool_scale", boundsAct ? "S+" : "S", sizeB, 0, true,
                     ImVec2(space * 3 + sizeB.x * 2, space), g_currentGuizmoOperation == ImGuizmo::SCALE ? act : def)) {
        if (g_currentGuizmoOperation == ImGuizmo::SCALE)
            boundsAct = !boundsAct;

        g_currentGuizmoOperation = ImGuizmo::SCALE;
    }

    if (ButtonWithId("engine_tool_mode", "L", sizeB, 0, true,
                     ImVec2(space * 5 + sizeB.x * 4, space), g_currentGuizmoMode == ImGuizmo::LOCAL ? act : def)) {
        if (g_currentGuizmoMode == ImGuizmo::LOCAL)
            g_currentGuizmoMode = ImGuizmo::WORLD;
        else
            g_currentGuizmoMode = ImGuizmo::LOCAL;
    }

    if (ButtonWithId("engine_tool_pivot", "P", sizeB, 0, true,
                     ImVec2(space * 6 + sizeB.x * 5, space), g_currentGuizmoPivot ? act : def)) {
        g_currentGuizmoPivot = !g_currentGuizmoPivot;
    }

    std::string snap_str = std::to_string(snapValue / 100.0);
    snap_str.resize(4);
    if (ButtonWithId("engine_tool_snap", (snap_str + "x").c_str(),
                     sizeB + ImVec2(5, 0), 0, true,
                     ImVec2(space * 7 + sizeB.x * 6, space), snapAct ? act : def)) {
        if (snapValue >= 400) {
            snapValue = 25;
            snapAct = false;
        } else {
            if (snapAct)
                snapValue *= 2;
            else
                snapAct = true;
        }
    }

    //ImGuiIO& io = ImGui::GetIO();
    //ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    pos += (win_size - img_size) / 2.f;
    ImGuizmo::SetRect(pos.x, pos.y, img_size.x, img_size.y);


    //glm::vec3 camPos = camera->GetGLPosition();
    //ImGuizmo::SetCameraPos(camPos.x, camPos.y, -camPos.z);

    static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
    static float boundsSnap[] = {0.1f, 0.1f, 0.1f};

    glm::vec3 snap = glm::vec3(1, 1, 1) * ((float) snapValue / 100.f);

    //float angle[3] = {0,0,0};

    glm::mat4 delta;

    glm::mat4 mat = gameObject->GetTransform()->GetMatrix();

    if (ImGuizmo::Manipulate(
            &camera->GetView()[0][0],
            &camera->GetProjection()[0][0],
            boundsAct ? ImGuizmo::BOUNDS : g_currentGuizmoOperation, g_currentGuizmoMode,
            &mat[0][0],
            &delta[0][0], snapAct ? &snap[0] : nullptr, boundsAct ? bounds : nullptr, boundsSnap,
            NULL)) {
        gameObject->GetTransform()->SetMatrix(delta, mat, g_currentGuizmoPivot);
    }

    //ImGuizmo::ViewManipulate(cameraView, 10, ImVec2(0, 0), ImVec2(128, 128), 0x10101010);
}

void Framework::Graphics::GUI::GUIWindow::DebugWindow() {
    static glm::vec3 vec = glm::vec3(0,0,0);
    ImGui::InputFloat3("vec1", &vec[0]);

    //glm::vec3 euler =
    //        Quaternion(glm::quat(glm::radians(vec)))
    //        .EulerAngle().ToGLM();

    glm::vec3 euler = glm::degrees(glm::eulerAngles(glm::inverse(glm::quat(glm::radians(vec)))));

    ImGui::InputFloat3("vec2", &euler[0]);
}
