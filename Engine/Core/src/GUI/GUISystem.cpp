//
// Created by Nikita on 19.07.2021.
//

#include <GUI/GUISystem.h>
#include <GUI/Editor/FileBrowser.h>
#include <GUI/VisualScriptEditor.h>
#include <Input/InputSystem.h>
#include <GUI.h>
#include <string>
#include <ResourceManager/ResourceManager.h>
#include <Engine.h>
#include <World/Chunk.h>
#include <EngineCommands.h>
#include <GUI/Editor/MessageBox.h>

namespace Framework::Core {
    inline static bool Vec4Null(const ImVec4 &v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }

    inline static const ImGuiTreeNodeFlags g_node_flags_with_child = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    inline static const ImGuiTreeNodeFlags g_node_flags_without_child = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
}

#define SR_BEGIN_RIGHT_ALIGNMENT() {                                    \
    const float generatedItemSpacing = ImGui::GetStyle().ItemSpacing.x; \
    float generatedPos = 0;                                             \

#define SR_END_RIGHT_ALIGNMENT() }

#define SR_RIGHT_BUTTON(name, label, _true, _false) {                         \
        static float generated_##name##ButtonWidth = 100.0f;                  \
        generatedPos += generated_##name##ButtonWidth + generatedItemSpacing; \
        ImGui::SameLine(ImGui::GetWindowWidth() - generatedPos);              \
        if (ImGui::SmallButton(label)) { _true } else { _false }              \
        generated_##name##ButtonWidth = ImGui::GetItemRectSize().x;           \
    }                                                                         \

using namespace Framework::Core::GUI;

/*
bool HY_ImGui_BeginMainStatusBar()
{
    ImGuiContext& g = *GImGui;
    ImGuiViewportP* viewport = g.Viewports[0];
    ImGuiWindow* menu_bar_window = ImGui::FindWindowByName("##MainStatusBar");

    // For the main menu bar, which cannot be moved, we honor g.Style.DisplaySafeAreaPadding to ensure text can be visible on a TV set.
    g.NextWindowData.MenuBarOffsetMinVal = ImVec2(g.Style.DisplaySafeAreaPadding.x, ImMax(g.Style.DisplaySafeAreaPadding.y - g.Style.FramePadding.y, 0.0f));

    // Get our rectangle at the top of the work area
    //__debugbreak();
    if (menu_bar_window == NULL || menu_bar_window->BeginCount == 0)
    {
        // Set window position
        // We don't attempt to calculate our height ahead, as it depends on the per-viewport font size. However menu-bar will affect the minimum window size so we'll get the right height.
        ImVec2 menu_bar_pos = viewport->Pos + viewport->CurrWorkOffsetMin;
        ImVec2 menu_bar_size = ImVec2(viewport->Size.x - viewport->CurrWorkOffsetMin.x + viewport->CurrWorkOffsetMax.x, 1.0f);
        ImGui::SetNextWindowPos(menu_bar_pos);
        ImGui::SetNextWindowSize(menu_bar_size);
    }

    // Create window
    ImGui::SetNextWindowViewport(viewport->ID); // Enforce viewport so we don't create our own viewport when ImGuiConfigFlags_ViewportsNoMerge is set.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));    // Lift normal size constraint, however the presence of a menu-bar will give us the minimum height we want.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    bool is_open = ImGui::Begin("##MainStatusBar", NULL, window_flags) && ImGui::BeginMenuBar();
    ImGui::PopStyleVar(2);

    // Report our size into work area (for next frame) using actual window size
    menu_bar_window = ImGui::GetCurrentWindow();
    if (menu_bar_window->BeginCount == 1)
        viewport->CurrWorkOffsetMin.y += menu_bar_window->Size.y;

    g.NextWindowData.MenuBarOffsetMinVal = ImVec2(0.0f, 0.0f);
    if (!is_open)
    {
        ImGui::End();
        return false;
    }
    return true; //-V1020
}
void HY_ImGui_EndMainStatusBar()
{
    ImGui::EndMenuBar();

    // When the user has left the menu layer (typically: closed menus through activation of an item), we restore focus to the previous window
    // FIXME: With this strategy we won't be able to restore a NULL focus.
    ImGuiContext& g = *GImGui;
    if (g.CurrentWindow == g.NavWindow && g.NavLayer == ImGuiNavLayer_Main && !g.NavAnyRequest)
        ImGui::FocusTopMostWindowUnderOne(g.NavWindow, NULL);

    ImGui::End();
}
*/

void GUISystem::BeginDockSpace() {
    const float toolbarSize = 0;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos + ImVec2(0, toolbarSize));
    ImGui::SetNextWindowSize(viewport->Size - ImVec2(0, toolbarSize));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoCollapse
                                    | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
                                    | ImGuiWindowFlags_NoTitleBar
                                    | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    const char* winName = "SpaRcle Engine";
    ImGui::Begin(winName, nullptr, window_flags);
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiID dockMain = ImGui::GetID("Dockspace");

    auto context = Graphics::Environment::Get()->GetGUIContext();

    if (ImGui::BeginMainMenuBar()) {
        ImGuiWindow* menu_bar_window = ImGui::FindWindowByName("##MainMenuBar");

        enum class Click {
            None, Drag, Miss
        } static click;

        if (click == Click::None && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            click = menu_bar_window->Rect().Contains(ImGui::GetMousePos()) ? Click::Drag : Click::Miss;
        else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
            click = Click::None;

        if (click == Click::Drag) {
            auto drag = ImGui::GetMouseDragDelta();
            auto pos = Graphics::Environment::Get()->GetBasicWindow()->GetPosition();

            pos.x += drag.x;
            pos.y += drag.y;

            Graphics::Environment::Get()->GetBasicWindow()->Move(pos.x, pos.y);
        }

        ImGui::Text("%s", winName);
        ImGui::Text(" | ");

        BeginMenuBar();
        EndMenuBar();

        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

        auto pWindow = m_env->GetBasicWindow();

        SR_BEGIN_RIGHT_ALIGNMENT()
            SR_RIGHT_BUTTON(close, "×", {
                SR_UTILS_NS::EventManager::Push(SR_UTILS_NS::EventManager::Event::Exit);
            }, {})

            if (pWindow->GetState() == Graphics::WindowState::Default)
                SR_RIGHT_BUTTON(maximize, "[ ]", { pWindow->Maximize(); }, {})
            else  if (pWindow->GetState() == Graphics::WindowState::Maximized)
                SR_RIGHT_BUTTON(restore, "[=]", { pWindow->Restore(); }, {})

            SR_RIGHT_BUTTON(minimize, "_", {
                pWindow->Collapse();
            }, {})
        SR_END_RIGHT_ALIGNMENT()

        ImGui::PopStyleVar();

        {
            ImGui::EndMenuBar();

            // When the user has left the menu layer (typically: closed menus through activation of an item), we restore focus to the previous window
            // FIXME: With this strategy we won't be able to restore a NULL focus.
            ImGuiContext& g = *GImGui;
            if (g.CurrentWindow == g.NavWindow && g.NavLayer == ImGuiNavLayer_Main && !g.NavAnyRequest)
                ImGui::FocusTopMostWindowUnderOne(g.NavWindow, NULL);

            ImGui::End();
        }
    }

    float button_sz = context->FontSize * 0.5f;
    //if (ImGui::CloseButton(window->GetID(winName), ImVec2(window->DC.LastItemRect.Max.x - context->Style.FramePadding.x - button_sz, window->DC.LastItemRect.Min.y + context->Style.FramePadding.y + button_sz))) {

    //}

    // Save off menu bar height for later.
    //float menuBarHeight = ImGui::GetCurrentWindow()->MenuBarHeight();

    ImGui::DockSpace(dockMain);
    ImGui::End();
    ImGui::PopStyleVar(3);
}

void GUISystem::EndDockSpace() {

}

bool GUISystem::BeginWindow(const char* name) {
    return ImGui::Begin(name);
}

void GUISystem::EndWindow() {
    ImGui::End();
}

bool GUISystem::BeginChildWindow(const char* name) {
    return ImGui::BeginChild(name);
}

void GUISystem::EndChildWindow() {
    ImGui::EndChild();
}

void GUISystem::DrawTexture(
    Framework::Helper::Math::IVector2 winSize,
    Framework::Helper::Math::IVector2 texSize, uint32_t id,
    bool centralize)
{
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

    if (m_pipeLine == Graphics::PipeLine::OpenGL)
        DrawImage(reinterpret_cast<void*>(static_cast<uint64_t>(id)), ImVec2(texSize.x, texSize.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1 }, {0, 0, 0, 0 }, true);
    else {
        DrawImage(m_env->GetDescriptorSetFromTexture(id, true), ImVec2(texSize.x, texSize.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
    }
}

void GUISystem::DrawImage(
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

void GUISystem::DrawHierarchy(Framework::Helper::Types::SafePtr<Framework::Helper::World::Scene> scene) {
    m_shiftPressed = Helper::Input::GetKey(Helper::KeyCode::LShift);

    if (scene.LockIfValid()) {
        unsigned long i = 0;

        if (ImGui::TreeNodeEx(scene->GetName().c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

            scene->ForEachRootObjects([&i, this](const Helper::Types::SafePtr<Helper::GameObject>& gm) {
                if (gm->HasChildren()) {
                    //bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
                    //                              g_node_flags_with_child | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                    //                              "%s", gm->GetName().c_str());
                    //CheckSelected(gm);

                    //if (open)
                    //    this->DrawChild(gm);
                } else {
                    //ImGui::TreeNodeEx((void *) (intptr_t) i,
                    //                  g_node_flags_without_child | (gm->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
                     //                 "%s", gm->GetName().c_str());

                    CheckSelected(gm);
                }
                i++;
            });
            ImGui::TreePop();
            ImGui::PopStyleVar();
        }

        //auto&& selected = scene->GetSelected();
        //if (ImGui::Button("Delete") && selected.LockIfValid()) {
        //    auto cmd = new Framework::Core::Commands::GameObjectDelete(selected);
        //    Engine::Instance().GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);
        //    selected.Unlock();
        //}

        scene.Unlock();
    }
}

void GUISystem::DrawChild(const Framework::Helper::Types::SafePtr<Framework::Helper::GameObject>& root) {
    unsigned long i = 0;

    root->ForEachChild([&i, this](const Helper::Types::SafePtr<Helper::GameObject>& child){
        if (child->HasChildren()) {
            //bool open = ImGui::TreeNodeEx((void *) (intptr_t) i,
            //                              g_node_flags_with_child |
             //                             (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
            ///                             "%s", child->GetName().c_str()
            //);

            //CheckSelected(child);

            //if (open)
            //   DrawChild(child);
        }
        else {
            //ImGui::TreeNodeEx((void *) (intptr_t) i,
            //                  g_node_flags_without_child | (child->IsSelect() ? ImGuiTreeNodeFlags_Selected : 0),
            //                  "%s", child->GetName().c_str()
            //);

            CheckSelected(child);
        }

        i++;
    });

    ImGui::TreePop();
}

bool GUISystem::CollapsingHeader(const char *label, ImGuiTreeNodeFlags flags) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiID id = window->GetID(label);
    flags |= ImGuiTreeNodeFlags_CollapsingHeader;
    flags |= ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_ClipLabelForTrailingButton;
    bool is_open = ImGui::TreeNodeBehavior(id, flags, label);

    return is_open;
}

void GUISystem::DrawComponents(const Helper::Types::SafePtr<SR_UTILS_NS::GameObject>& gameObject) {
    if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
        if (ImGui::BeginMenu("Add component")) {
            for (const auto& [name, id] : SR_UTILS_NS::ComponentManager::Instance().GetComponentsNames()) {
                if (ImGui::MenuItem(name.c_str())) {
                    gameObject->AddComponent(SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(name));
                    break;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

    gameObject->ForEachComponent([gameObject, this](SR_UTILS_NS::Component* component) -> bool {
        if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
            if (ImGui::BeginMenu("Remove component")) {
                if (ImGui::MenuItem(component->GetComponentName().c_str())) {
                    gameObject->RemoveComponent(component);
                    goto exit;
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        ///if (ImGui::CollapsingHeader(component->GetComponentName().c_str()))
        ///    component->DrawOnInspector();

        return true;

        exit:
            ImGui::EndMenu();
            ImGui::EndPopup();
            return false;
    });
}

void GUISystem::DrawInspector(Framework::Helper::Types::SafePtr<Framework::Helper::World::Scene> scene) {
//    Helper::Types::SafePtr<Helper::GameObject> gameObject;
//
//    if (scene.LockIfValid()) {
//        gameObject = scene->GetSelected();
//        scene.Unlock();
//    }
//
//    if (gameObject.LockIfValid()) {
//        if (bool v = gameObject->IsActive(); ImGui::Checkbox("Enabled", &v))
//            gameObject->SetActive(v);
//
//        std::string gm_name = gameObject->GetName();
//        if (ImGui::InputText("Name", &gm_name))
//            gameObject->SetName(gm_name);
//
//        ImGui::Text("Entity id: %llu", gameObject->GetEntityId());
//        //ImGui::Text("Entity path: %s", gameObject->GetEntityPath().CStr());
//
//        ImGui::Separator();
//        DrawTextOnCenter("Transform");
//
//        this->DrawComponents(gameObject);
//
//        /*ImGui::Text("[Parent direction]");
//
//        std::vector<Framework::Helper::Component *> comps = gameObject->GetComponents();
//        for (Framework::Helper::Component *comp : comps) {
//            std::string name = comp->GetComponentName();
//
//            if (ImGui::CollapsingHeader(name.c_str()))
//                comp->DrawOnInspector();
//        }
//
//        ImGui::Separator();
//
//        ImGui::InvisibleButton("void", ImVec2(ImGui::GetCurrentWindow()->Size.x, ImGui::GetCurrentWindow()->Size.y - ImGui::GetItemRectMin().y));
//
//        if (ImGui::BeginPopupContextItem("InspectorMenu", 1)) {
//            if (ImGui::BeginMenu("Add component")) {
//                for (const auto& a : Component::GetComponentsNames()) {
//                    if (ImGui::MenuItem(a.c_str()))
//                        gameObject->AddComponent(Component::CreateComponentOfName(a));
//                }
//                ImGui::EndMenu();
//            }
//            ImGui::EndPopup();
//        }*/
//
//        gameObject.Unlock();
//    }
}

void GUISystem::CheckSelected(const Helper::Types::SafePtr<Helper::GameObject>& gm) const {
    if (ImGui::IsItemClicked()) {
        //if (!m_shiftPressed && gm->GetScene().Valid())
        //    gm->GetScene()->DeSelectAll();

        //gm->SetSelect(true);
    }
}

void GUISystem::DrawGuizmoTools() {
    static const ImVec2 g_sizeB = { 30, 25 };
    static const short  g_space = 3;
    static const ImVec4 g_def = {0.1, 0.1, 0.1, 0.7};
    static const ImVec4 g_act = {0.6, 0.6, 0.6, 0.85};

    if (ButtonWithId("engine_tool_move", "M", g_sizeB, 0, true,
                     ImVec2(g_space, g_space), m_currentGuizmoOperation == ImGuizmo::TRANSLATE ? g_act : g_def)) {
        m_currentGuizmoOperation = ImGuizmo::TRANSLATE;
        m_boundsActive = false;
    }

    if (ButtonWithId("engine_tool_rotate", "R", g_sizeB, 0, true,
                     ImVec2(g_space * 2 + g_sizeB.x, g_space),
                     m_currentGuizmoOperation == ImGuizmo::ROTATE ? g_act : g_def)) {
        m_currentGuizmoOperation = ImGuizmo::ROTATE;
        m_boundsActive = false;
    }

    if (ButtonWithId("engine_tool_scale", m_boundsActive ? "S+" : "S", g_sizeB, 0, true,
                     ImVec2(g_space * 3 + g_sizeB.x * 2, g_space),
                     m_currentGuizmoOperation == ImGuizmo::SCALE ? g_act : g_def)) {
        if (m_currentGuizmoOperation == ImGuizmo::SCALE)
            m_boundsActive = !m_boundsActive;

        m_currentGuizmoOperation = ImGuizmo::SCALE;
    }

    if (ButtonWithId("engine_tool_mode", "L", g_sizeB, 0, true,
                     ImVec2(g_space * 5 + g_sizeB.x * 4, g_space), m_currentGuizmoMode == ImGuizmo::LOCAL ? g_act : g_def)) {
        if (m_currentGuizmoMode == ImGuizmo::LOCAL)
            m_currentGuizmoMode = ImGuizmo::WORLD;
        else
            m_currentGuizmoMode = ImGuizmo::LOCAL;
    }

    if (ButtonWithId("engine_tool_center", "C", g_sizeB, 0, true,
                     ImVec2(g_space * 6 + g_sizeB.x * 5, g_space), m_centerActive ? g_act : g_def)) {
        m_centerActive = !m_centerActive;
    }

    std::string snap_str = std::to_string(m_snapValue / 100.0);
    snap_str.resize(4);
    if (ButtonWithId("engine_tool_snap", (snap_str + "x").c_str(),
                     g_sizeB + ImVec2(5, 0), 0, true,
                     ImVec2(g_space * 7 + g_sizeB.x * 6, g_space), m_snapActive ? g_act : g_def)) {
        if (m_snapValue >= 400) {
            m_snapValue = 25;
            m_snapActive = false;
        } else {
            if (m_snapActive)
                m_snapValue *= 2;
            else
                m_snapActive = true;
        }
    }
}

void GUISystem::DrawWorldEdit(Helper::Types::SafePtr<Helper::World::Scene> scene) {
    if (scene.LockIfValid()) {
        const auto&& observer = scene->GetObserver();
        const auto offset = observer->m_offset;

        ImGui::Separator();
        DrawTextOnCenter("Current");

        ImGui::InputFloat3("Chunk", &observer->m_chunk.ToGLM()[0], "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputFloat2("Region", &observer->m_region.ToGLM()[0], "%.2f", ImGuiInputTextFlags_ReadOnly);

        ImGui::Separator();
        DrawTextOnCenter("Offset");

        auto chunkOffset = offset.m_chunk.ToGLM();
        if (ImGui::InputFloat3("Chunk offset", &chunkOffset[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
            scene->SetWorldOffset(SR_WORLD_NS::Offset(offset.m_region, chunkOffset));

        auto regionOffset = offset.m_region.ToGLM();
        if (ImGui::InputFloat2("Region offset", &regionOffset[0], "%.2f", ImGuiInputTextFlags_EnterReturnsTrue))
            scene->SetWorldOffset(SR_WORLD_NS::Offset(regionOffset, offset.m_chunk));

        if (ImGui::Button("Reload chunks")) {
            scene->ReloadChunks();
        }

        if (auto&& chunk = scene->GetCurrentChunk()) {
            ImGui::Separator();
            int32_t size = -1;// static_cast<int32_t>(chunk->GetContainerSize());
            ImGui::InputInt("Container size", &size, 0, 0, ImGuiInputTextFlags_ReadOnly);
        }

        scene.Unlock();
    }
}

void GUISystem::DrawGuizmo(Framework::Graphics::Camera *camera, Helper::Types::SafePtr<Helper::GameObject> gameObject) {
    if (!camera)
        return;

    /*
    if (gameObject.LockIfValid()) {
        ImGuiWindow *window = ImGui::GetCurrentWindow();
        if (!window || window->SkipItems)
            return;

        auto img_size = camera->GetSize();

        auto win_size = Math::FVector2(window->Size.x, window->Size.y);

        const Helper::Math::Unit dx = win_size.x / img_size.x;
        const Helper::Math::Unit dy = win_size.y / img_size.y;

        if (dy > dx)
            img_size *= dx;
        else
            img_size *= dy;

        static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
        static float boundsSnap[] = {0.1f, 0.1f, 0.1f};

        glm::vec3 snap = glm::vec3(1, 1, 1) * ((float) m_snapValue / 100.f);

        glm::mat4 delta;

        auto barycenter = gameObject->GetBarycenter();

        glm::mat4 mat = [=]() -> auto {
            if (m_centerActive && !barycenter.IsInfinity())
                return gameObject->GetTransform()->GetMatrix(Helper::Graph::PipeLine::OpenGL, barycenter);
            return gameObject->GetTransform()->GetMatrix(Helper::Graph::PipeLine::OpenGL);
        }();

        static float axis[3] = {0, 0, 0};
        static float value = 0.0;
        static float old_rotate = 0.0;
        static float old_scale = 0.0;

        ImGuizmo::SetRect(
                (float)(ImGui::GetWindowPos().x + (win_size.x - img_size.x) / 2.f),
                (float)(ImGui::GetWindowPos().y + (win_size.y - img_size.y) / 2.f),
                img_size.x,
                img_size.y);

        if (ImGuizmo::Manipulate(
                &camera->GetImGuizmoView()[0][0],
                &camera->GetProjection()[0][0],
                m_boundsActive ? ImGuizmo::BOUNDS : m_currentGuizmoOperation, m_currentGuizmoMode,
                &mat[0][0],"F
                &delta[0][0], nullptr, nullptr, boundsSnap,
                &value, &axis[0])) {
            if (m_currentGuizmoOperation == ImGuizmo::OPERATION::ROTATE) {
                if (abs((value - old_rotate)) < 1) {
                    if (m_centerActive && !barycenter.IsInfinity()) {
                        gameObject->GetTransform()->RotateAround(
                                barycenter,
                                FVector3(axis).InverseAxis(1),
                                (value - old_rotate) * 20.0,
                                m_currentGuizmoMode == ImGuizmo::LOCAL);
                    } else {
                        if (m_currentGuizmoMode == ImGuizmo::LOCAL)
                            gameObject->GetTransform()->RotateAxis(FVector3(axis).InverseAxis(1), (value - old_rotate) * 20.0);
                        else
                            gameObject->GetTransform()->GlobalRotateAxis(FVector3(axis).InverseAxis(1), (value - old_rotate) * 20.0);
                    }
                }
            } else if (m_currentGuizmoOperation == ImGuizmo::OPERATION::TRANSLATE) {
                if (value < 1) {
                    if (m_currentGuizmoMode == ImGuizmo::LOCAL)
                        gameObject->GetTransform()->Translate(
                                gameObject->GetTransform()->Direction(FVector3(axis).InverseAxis(0), true) * value);
                    else
                        gameObject->GetTransform()->GlobalTranslate(FVector3(axis).InverseAxis(0) * value);
                }
            } else if (m_currentGuizmoOperation == ImGuizmo::OPERATION::SCALE) {
                if (value == 0)
                    old_scale = 0;

                if (m_currentGuizmoMode == ImGuizmo::MODE::LOCAL)
                    gameObject->GetTransform()->Scaling(FVector3(axis) * (value - old_scale));

                old_scale = value;
            }
        }

        old_rotate = value;

        gameObject.Unlock();
    }*/
}

bool GUISystem::ButtonWithId(
    const char *_id,
    const char *label,
    ImVec2 button_size,
    ImGuiButtonFlags flags,
    bool imposition,
    ImVec2 offset,
    ImVec4 color)
{
    const bool has_color = !Vec4Null(color);

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(_id);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos + offset;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = ImGui::CalcItemSize(button_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);

    if (has_color)
        ImGui::PushStyleColor(ImGuiCol_Button, color);

    if (!imposition)
    {
        ImGui::ItemSize(size, style.FramePadding.y);

        if (!ImGui::ItemAdd(bb, id))
            return false;
    }

    if (window->Flags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    ImGui::RenderNavHighlight(bb, id);
    ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
    ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);

    if (has_color)
        ImGui::PopStyleColor();

    return pressed;
}

void GUISystem::SetGuizmoTool(uint8_t toolId) {
    switch (toolId) {
        case 0: m_currentGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE; break;
        case 1: m_currentGuizmoOperation = ImGuizmo::OPERATION::ROTATE;    break;
        case 2: m_currentGuizmoOperation = ImGuizmo::OPERATION::SCALE;     break;
        default:
            Helper::Debug::Error("GUISystem::SetGuizmoTool() : unknown tool id!");
            return;
    }
}

bool GUISystem::BeginMenuBar() {
    //if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New scene")) {
            if (Engine::Instance().GetScene())
                Graphics::GUI::MessageBoxWidget::Instance().Show("Warning", "Do you want close the current scene?");
        }

        if (ImGui::MenuItem("Load scene")) {

        }

        if (ImGui::MenuItem("Save scene")) {
            if (auto scene = Engine::Instance().GetScene(); scene.LockIfValid()) {
                const auto scenesPath = Helper::ResourceManager::Instance().GetResPath().Concat("/Scenes/");
                if (auto path = SR_UTILS_NS::FileSystem::SaveFileDialog(scenesPath.ToString(), "Scene Files(*.scene)"); !path.empty()) {
                    const auto sceneName = SR_UTILS_NS::StringUtils::GetFileNameFromFullPath(path);
                    const auto folder = SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath(path);

                    scene->SetName(sceneName);

                    if (scene->SaveAt(folder)) {
                        Helper::Debug::System("GUISystem::BeginMenuBar() : scene saved as \"" + path + "\"");
                    }
                    else {
                        SR_ERROR("GUISystem::BeginMenuBar() : failed to save scene! \n\tPath: \"" + path + "\"");
                    }
                }
                scene.Unlock();
            }
            else {
                SR_WARN("GUISystem::BeginMenuBar() : scene isn't valid!");
            }
        }

        if (ImGui::MenuItem("Close scene")) {
            Engine::Instance().CloseScene();
        }

        if (ImGui::MenuItem("Reload")) {
            Engine::Instance().Reload();
        }

        if (ImGui::MenuItem("Exit")) {
            SR_UTILS_NS::EventManager::Push(Helper::EventManager::Event::Exit);
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Editor")) {
        if (ImGui::MenuItem("Empty GameObject")) {
            if (auto&& scene = Engine::Instance().GetScene()) {
                scene->Instance("New GameObject");
            }
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
        if (ImGui::MenuItem("Assets")) {
            Engine::Instance().GetEditor()->GetWindow<FileBrowser>()->Open();
        }

        if (ImGui::MenuItem("Hierarchy")) {
            Engine::Instance().GetEditor()->GetWindow<Hierarchy>()->Open();
        }

        if (ImGui::MenuItem("Inspector")) {
            Engine::Instance().GetEditor()->GetWindow<Inspector>()->Open();
        }

        if (ImGui::MenuItem("Scene")) {
            Engine::Instance().GetEditor()->GetWindow<SceneViewer>()->Open();
        }

        if (ImGui::MenuItem("Visual Script")) {
            Engine::Instance().GetEditor()->GetWindow<VisualScriptEditor>()->Open();
        }

        if (ImGui::MenuItem("World edit")) {
            Engine::Instance().GetEditor()->GetWindow<WorldEdit>()->Open();
        }

        if (ImGui::MenuItem("Settings")) {
            Engine::Instance().GetEditor()->GetWindow<EngineSettings>()->Open();
        }

        if (ImGui::MenuItem("Statistics")) {
            Engine::Instance().GetEditor()->GetWindow<EngineStatistics>()->Open();
        }

        if (ImGui::MenuItem("Close all")) {
            Engine::Instance().GetEditor()->CloseAllWindows();
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("About")) {
        ImGui::EndMenu();
    }

    return true;
}

void GUISystem::EndMenuBar() {
    //ImGui::EndMainMenuBar();
}

