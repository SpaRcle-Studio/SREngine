//
// Created by Nikita on 19.07.2021.
//

#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>

#include <GUI/GUISystem.h>
#include <Input/InputSystem.h>

void Framework::Graphics::GUI::GUISystem::BeginDockSpace() {
    const float toolbarSize = 0;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos + ImVec2(0, toolbarSize));
    ImGui::SetNextWindowSize(viewport->Size - ImVec2(0, toolbarSize));
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGuiWindowFlags window_flags = 0
                                    | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
                                    | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
                                    | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Master DockSpace", nullptr, window_flags);
    ImGuiID dockMain = ImGui::GetID("MyDockspace");

    // Save off menu bar height for later.
    //float menuBarHeight = ImGui::GetCurrentWindow()->MenuBarHeight();

    ImGui::DockSpace(dockMain);
    ImGui::End();
    ImGui::PopStyleVar(3);
}

void Framework::Graphics::GUI::GUISystem::EndDockSpace() {

}

bool Framework::Graphics::GUI::GUISystem::BeginWindow(const char* name) {
    return ImGui::Begin(name);
}

void Framework::Graphics::GUI::GUISystem::EndWindow() {
    ImGui::End();
}

bool Framework::Graphics::GUI::GUISystem::BeginChildWindow(const char* name) {
    return ImGui::BeginChild(name);
}

void Framework::Graphics::GUI::GUISystem::EndChildWindow() {
    ImGui::EndChild();
}

void Framework::Graphics::GUI::GUISystem::DrawTexture(
    Framework::Helper::Math::Vector2 winSize,
    Framework::Helper::Math::Vector2 texSize, uint32_t id,
    bool centralize)
{
    const auto dx = winSize.x / texSize.x;
    const auto dy = winSize.y / texSize.y;

    if (dy > dx)
        texSize *= (Helper::Math::Unit)dx;
    else
        texSize *= (Helper::Math::Unit)dy;

    // Because I use the texture from OpenGL, I need to invert the V from the UV.

    if (centralize) {
        ImVec2 initialCursorPos = ImGui::GetCursorPos();
        auto res = (winSize - texSize) * 0.5f;
        ImVec2 centralizedCursorPos = { (float)res.x, (float)res.y };
        centralizedCursorPos = ImClamp(centralizedCursorPos, initialCursorPos, centralizedCursorPos);
        ImGui::SetCursorPos(centralizedCursorPos);
    }

    if (m_pipeLine == PipeLine::OpenGL)
        DrawImage(reinterpret_cast<ImTextureID>(id), ImVec2(texSize.x, texSize.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1 }, {0, 0, 0, 0 }, true);
    else {
        DrawImage(m_env->GetDescriptorSetFromTexture(id, true), ImVec2(texSize.x, texSize.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
    }
}

void Framework::Graphics::GUI::GUISystem::DrawImage(
    ImTextureID user_texture_id,
    const ImVec2& size,
    const ImVec2& uv0,
    const ImVec2& uv1,
    const ImVec4& tint_col,
    const ImVec4& border_col,
    bool imposition)
{
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

void Framework::Graphics::GUI::GUISystem::DrawHierarchy(Framework::Helper::Types::SafePtr<Framework::Helper::Scene> scene) {
    m_shiftPressed = Helper::Input::GetKey(Helper::KeyCode::LShift);

    if (scene.LockIfValid()) {
        unsigned long i = 0;

        if (ImGui::TreeNodeEx(scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

            scene->ForEachRootObjects([&i, this](Helper::Types::SafePtr<Helper::GameObject> gm) {
                if (gm->HasChildren()) {
                    bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                                                  g_node_flags_with_child | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                                  "%s", gm->GetName().c_str());
                    CheckSelected(gm);

                    if (open)
                        this->DrawChild(gm);
                } else {
                    ImGui::TreeNodeEx((void *) (intptr_t) i,
                                      g_node_flags_without_child | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                                      "%s", gm->GetName().c_str());

                    CheckSelected(gm);
                }
                i++;
            });
            ImGui::TreePop();
            ImGui::PopStyleVar();
        }

        scene.Unlock();
    }
}

void Framework::Graphics::GUI::GUISystem::DrawChild(Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> root) {
    unsigned long i = 0;

    root->ForEachChild([&i, this](Helper::Types::SafePtr<Helper::GameObject> child){
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
    });

    ImGui::TreePop();
}

void Framework::Graphics::GUI::GUISystem::DrawInspector(Framework::Helper::Types::SafePtr<Framework::Helper::Scene> scene) {
    Helper::Types::SafePtr<Helper::GameObject> gameObject;
    if (scene.LockIfValid()) {
        gameObject = scene->GetSelected();
        scene.Unlock();
    }

    if (gameObject.LockIfValid()) {
        if (bool v = gameObject->IsActive(); ImGui::Checkbox("Enabled", &v))
            gameObject->SetActive(v);

        std::string gm_name = gameObject->GetName();
        if (ImGui::InputText("Name", &gm_name))
            gameObject->SetNameFromInspector(gm_name);

        ImGui::Separator();
        DrawTextOnCenter("Transform");

        auto position = gameObject->GetTransform()->GetPosition().ToGLM();
        auto rotation = gameObject->GetTransform()->GetRotation().ToGLM();
        auto scale    = gameObject->GetTransform()->GetScale().ToGLM();

        ImGui::Text("[Global]");

        if (ImGui::InputFloat3("G Tr", &position[0], "%.3f", ImGuiInputTextFlags_ReadOnly))
            gameObject->GetTransform()->SetPosition(position);

        if (ImGui::InputFloat3("G Rt", &rotation[0], "%.3f", ImGuiInputTextFlags_ReadOnly))
            gameObject->GetTransform()->SetRotation(rotation);

        if (ImGui::InputFloat3("G Sc", &scale[0], "%.3f", ImGuiInputTextFlags_ReadOnly))
            gameObject->GetTransform()->SetScale(scale);

        ImGui::Text("[Local]");

        position = gameObject->GetTransform()->GetPosition(true).ToGLM();
        rotation = gameObject->GetTransform()->GetRotation(true).ToGLM();
        scale    = gameObject->GetTransform()->GetScale(true).ToGLM();

        if (ImGui::InputFloat3("L Tr", &position[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
            gameObject->GetTransform()->SetLocalPosition(position);

        if (ImGui::InputFloat3("L Rt", &rotation[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
            gameObject->GetTransform()->SetLocalRotation(rotation);

        if (ImGui::InputFloat3("L Sc", &scale[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
            gameObject->GetTransform()->SetLocalScale(position);

        /*
        ImGui::Text("[Parent direction]");

        std::vector<Framework::Helper::Component *> comps = gameObject->GetComponents();
        for (Framework::Helper::Component *comp : comps) {
            std::string name = comp->GetComponentName();

            if (ImGui::CollapsingHeader(name.c_str()))
                comp->DrawOnInspector();
        }

        ImGui::Separator();

        ImGui::InvisibleButton("void", ImVec2(ImGui::GetCurrentWindow()->Size.x, ImGui::GetCurrentWindow()->Size.y - ImGui::GetItemRectMin().y));

        if (ImGui::BeginPopupContextItem("InspectorMenu", 1)) {
            if (ImGui::BeginMenu("Add component")) {
                for (const auto& a : Component::GetComponentsNames()) {
                    if (ImGui::MenuItem(a.c_str()))
                        gameObject->AddComponent(Component::CreateComponentOfName(a));
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }*/

        gameObject.Unlock();
    }
}

void Framework::Graphics::GUI::GUISystem::CheckSelected(const Helper::Types::SafePtr<Helper::GameObject>& gm) {
    if (ImGui::IsItemClicked()) {
        if (!m_shiftPressed && gm->GetScene().Valid())
            gm->GetScene()->UnselectAll();

        gm->SetSelect(true);
    }
}
