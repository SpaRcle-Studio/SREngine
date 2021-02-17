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

    GUIWindow::m_shiftPressed = Helper::InputSystem::IsPressed(Helper::KeyCode::LShift);

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
        if (!m_shiftPressed)
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

    glm::vec3 position = gameObject->GetTransform()->GetPosition();
    glm::vec3 rotation = gameObject->GetTransform()->GetRotation();
    glm::vec3 scale = gameObject->GetTransform()->GetScale();

    if (ImGui::InputFloat3("Tr", &position[0]))
        gameObject->GetTransform()->SetPosition(position);
    if (ImGui::InputFloat3("Rt", &rotation[0]))
        gameObject->GetTransform()->SetRotation(rotation);
    if (ImGui::InputFloat3("Sc", &scale[0]))
        gameObject->GetTransform()->SetScale(scale);

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
            if (ImGui::InputFloat("Gamma", &gamma))
                post->SetGamma(gamma);

            float exposure = post->GetExposure();
            if (ImGui::InputFloat("Exposure", &exposure))
                post->SetExposure(exposure);

            glm::vec3 color = post->GetColorCorrection();
            if (ImGui::InputFloat3("Color correction", &color[0]))
                post->SetColorCorrection(color);

            ImGui::NewLine();

            bool enabled = post->GetBloomEnabled();
            if (ImGui::Checkbox("Bloom", &enabled))
                post->SetBloom(enabled);

            ImGui::NewLine();

            float bloom_intensity = post->GetBloomIntensity();
            if (ImGui::InputFloat("Bloom intensity", &bloom_intensity))
                post->SetBloomIntensity(bloom_intensity);

            int bloom_amount = post->GetBloomAmount();
            if (ImGui::InputInt("Bloom amount", &bloom_amount)) {
                if (bloom_amount == 0)
                    bloom_amount = 1;
                post->SetBloomAmount(bloom_amount);
            }
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

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (!window || window->SkipItems)
        return;

    glm::vec2 pos = { window->Pos.x, window->Pos.y };
    glm::vec2 win_size = { window->Size.x, window->Size.y };

    const float dx = win_size.x / img_size.x;
    const float dy = win_size.y / img_size.y;

    if (dx > dy)
        img_size *= dy;
    else
        if (dy > dx)
            img_size *= dx;
        else
            img_size *= dy;

    static const ImVec4 def = { 0.1, 0.1, 0.1, 0.7 };
    static const ImVec4 act = { 0.6, 0.6, 0.6, 0.85 };
    static const ImVec2 sizeB = { 30,25 };
    static const short space = 3;

    if (ButtonWithId("engine_tool_move", "M", sizeB, 0, true,
            ImVec2(space, space), g_currentGuizmoOperation == ImGuizmo::TRANSLATE ? act : def)) {
        g_currentGuizmoOperation = ImGuizmo::TRANSLATE;
    }

    if (ButtonWithId("engine_tool_rotate", "R", sizeB, 0, true,
            ImVec2(space * 2 + sizeB.x, space), g_currentGuizmoOperation == ImGuizmo::ROTATE ? act : def)) {
        g_currentGuizmoOperation = ImGuizmo::ROTATE;
    }

    if (ButtonWithId("engine_tool_scale", "S", sizeB, 0, true,
            ImVec2(space * 3 + sizeB.x * 2, space), g_currentGuizmoOperation == ImGuizmo::SCALE ? act : def)) {
        g_currentGuizmoOperation = ImGuizmo::SCALE;
    }

    //ImGuiIO& io = ImGui::GetIO();
    //ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    pos = pos + (win_size - img_size) / 2.f;
    ImGuizmo::SetRect(pos.x, pos.y, img_size.x, img_size.y);

    glm::mat4 mat = gameObject->GetTransform()->GetMatrix(false);

    if (ImGuizmo::Manipulate(
            &camera->GetView()[0][0],
            &camera->GetProjection()[0][0],
            g_currentGuizmoOperation, ImGuizmo::LOCAL,
            &mat[0][0],
            NULL, NULL, NULL, NULL))
    {
        gameObject->GetTransform()->SetMatrix(mat);

        gameObject->UpdateComponents();
    }



    //ImGuizmo::ViewManipulate(cameraView, 10, ImVec2(0, 0), ImVec2(128, 128), 0x10101010);
}
