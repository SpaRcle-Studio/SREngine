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
#include <GUI.h>

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
    Helper::GUI::DrawTextOnCenter("Transform");

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

//    glm::vec3 p_dir = gameObject->GetTransform()->GetParentDir().ToGLM();
 //   ImGui::InputFloat3("Dir", &p_dir[0]);

    std::vector<Framework::Helper::Component*> comps = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : comps) {
        std::string name = comp->GetComponentName();

        if (ImGui::CollapsingHeader(name.c_str())) {
            //ImGui::Separator();
            //Helper::GUI::DrawTextOnCenter(name);

            comp->DrawOnInspector();
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

    pos += (win_size - img_size) / 2.f;
    ImGuizmo::SetRect(pos.x, pos.y, img_size.x, img_size.y);

    static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
    static float boundsSnap[] = {0.1f, 0.1f, 0.1f};

    glm::vec3 snap = glm::vec3(1, 1, 1) * ((float) snapValue / 100.f);

    //float angle[3] = {0,0,0};

    glm::mat4 delta;

    glm::mat4 mat = gameObject->GetTransform()->GetMatrix();

    static float axis[3] = {0,0,0};

    static float value = 0.0;
    static float old_value = 0.0;

    if (ImGuizmo::Manipulate(
            &camera->GetView()[0][0],
            &camera->GetProjection()[0][0],
            boundsAct ? ImGuizmo::BOUNDS : g_currentGuizmoOperation, g_currentGuizmoMode,
            &mat[0][0],
            &delta[0][0],  nullptr, nullptr, boundsSnap,
            &value, &axis[0]))
    {
        if (g_currentGuizmoOperation == ImGuizmo::OPERATION::ROTATE) {
            if (abs((value - old_value)) < 1) {
                if (g_currentGuizmoMode == ImGuizmo::LOCAL)
                    gameObject->GetTransform()->RotateAxis(Vector3(axis).InverseAxis(2), (value - old_value) * 20.0, true);
                else
                    gameObject->GetTransform()->GlobalRotateAxis(Vector3(axis).InverseAxis(2), (value - old_value) * 20.0);
            }
        } else if (g_currentGuizmoOperation == ImGuizmo::OPERATION::TRANSLATE) {
            if (value < 1) {
                if (g_currentGuizmoMode == ImGuizmo::LOCAL)
                    gameObject->GetTransform()->Translate(
                            gameObject->GetTransform()->Direction(Vector3(axis), true) * value, true);
                else {
                    gameObject->GetTransform()->GlobalTranslate(axis, value);

                    //Quaternion q = Vector3(24, 43, 56);
                    //Vector3 v = q * Vector3(1, 0, 0);
                    //Debug::Log(v.ToString());
                    //Debug::Log((Quaternion(-Vector3(24, 43, 56)) * v).ToString());

                    //Vector3 dir = gameObject->GetTransform()->Direction(axis, false);
                    //gameObject->GetTransform()->Translate(dir * (value / 100.0), true);

                    //if (!gameObject->GetParent())
                    //    gameObject->GetTransform()->Translate(Vector3(axis) * value, true);
                   // else {
                        //Vector3 global = Vector3(axis);//.Rotate(gameObject->GetParent()->GetTransform()->GetRotation());
                        //gameObject->GetTransform()->Translate(global * value, true);
                   // }
                }
            }
            //Matrix4x4 mat4x4 = delta;
            //Vector3 trans = mat4x4.GetTranslate();

            //gameObject->GetTransform()->DeltaTranslate(trans);

                //Vector3 dir = parent->GetTransform()->GetRotation().Radians().ToQuat() * trans.Radians().InverseAxis(2);
                //gameObject->GetTransform()->Translate(-dir, true);

            //Matrix4x4 rotate = Matrix4x4(Vector3(0,0,0), gameObject->GetTransform()->GetRotation(), Vector3(1,1,1));

            //gameObject->GetTransform()->Translate((mat4x4.Rotate(Vector3(0,90,0))).GetTranslate(), true);

            //Matrix4x4 local = Matrix4x4(Vector3(0,0,0), gameObject->GetTransform()->GetRotation(true), Vector3(1,1,1));
            //gameObject->GetTransform()->Translate((mat4x4 * local).GetTranslate(), true);

            /*Vector3 tr = mat4x4.GetTranslate();

            double max = tr.Max();
            double min = tr.Min();

            double val = abs(min) > max ? min : max;

            //Vector3 dir = mat4x4.GetTranslate().Normalize();
            if (val < 1) {
                Vector3 translate = gameObject->GetTransform()->Direction(axis, true) * val;
                //Vector3 translate = mat4x4.GetTranslate().Rotate(gameObject->GetTransform()->GetRotation());


                gameObject->GetTransform()->Translate(translate, true);
            }*/
        }

        //gameObject->GetTransform()->SetMatrix(delta, mat, g_currentGuizmoPivot);
    }

    old_value = value;

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
