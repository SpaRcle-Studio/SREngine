//
// Created by Nikita on 19.07.2021.
//

#include <Core/GUI/GUISystem.h>
#include <Core/GUI/VisualScriptEditor.h>
#include <Core/Engine.h>
#include <Core/EngineCommands.h>

#include <Core/GUI/FileBrowser.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/GUI.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/World/Chunk.h>
#include <Utils/Platform/Platform.h>

#include <Graphics/GUI/Editor/MessageBox.h>
#include <Graphics/SRSL/Shader.h>

/// TODO: перевести инклуд
#include <imgui_internal.h> /// взято с #5539 https://github.com/ocornut/imgui/issues/5539

#include <Core/GUI/AnimatorEditor.h>

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
        /*ImGui::SameLine(ImGui::GetWindowWidth() - generatedPos);*/              \
        if (ImGui::SmallButton(label)) { _true } else { _false }              \
        generated_##name##ButtonWidth = ImGui::GetItemRectSize().x;           \
    }                                                                         \

/// TODO: убрать это позорище
using namespace Framework::Core::GUI;

/// drag
bool GUISystem::BeginDockSpace(SR_GRAPH_NS::BasicWindowImpl* pWindow) {
    bool drag = false;

    const float toolbarSize = 0;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
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

    const char *winName = "SpaRcle Engine";
    ImGui::Begin(winName, nullptr, window_flags);
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    ImGuiID dockMain = ImGui::GetID("Dockspace");

    auto context = Graphics::Environment::Get()->GetGUIContext();

    if (ImGui::BeginMainMenuBar()) {
        ImGuiWindow *menu_bar_window = ImGui::FindWindowByName("##MainMenuBar");

        enum class Click {
            None, Drag, Miss
        } static click;

        if (click == Click::None && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            click = menu_bar_window->Rect().Contains(ImGui::GetMousePos()) ? Click::Drag : Click::Miss;
        else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
            click = Click::None;

        if (click == Click::Drag) {
            drag = true;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

        if (ImGui::SmallButton("×")) {
            pWindow->Close();
        }

        if (pWindow->GetState() == Graphics::WindowState::Default && ImGui::SmallButton("[ ]")) {
            pWindow->Maximize();
        }

        if (pWindow->GetState() == Graphics::WindowState::Maximized && ImGui::SmallButton("[=]")) {
            pWindow->Restore();
        }

        if (ImGui::SmallButton("_")) {
            pWindow->Collapse();
        }

        ImGui::PopStyleVar();

        ImGui::Text(" | ");

        ImGui::Text("%s", winName);

        ImGui::Text(" | ");

        BeginMenuBar();
        EndMenuBar();


        //SR_BEGIN_RIGHT_ALIGNMENT()
        //    SR_RIGHT_BUTTON(close, "×", {
        //        pWindow->Close();
        //    }, {})

        //    if (pWindow->GetState() == Graphics::WindowState::Default) SR_RIGHT_BUTTON(maximize, "[ ]",
        //                                                                               { pWindow->Maximize(); }, {})
        //    else if (pWindow->GetState() == Graphics::WindowState::Maximized) SR_RIGHT_BUTTON(restore, "[=]",
        //                                                                                      { pWindow->Restore(); },
        //                                                                                      { })

        //    SR_RIGHT_BUTTON(minimize, "_", {
        //        pWindow->Collapse();
        //    }, {})
        //SR_END_RIGHT_ALIGNMENT()

        {
            ImGui::EndMenuBar();

            // When the user has left the menu layer (typically: closed menus through activation of an item), we restore focus to the previous window
            // FIXME: With this strategy we won't be able to restore a NULL focus.
            ImGuiContext &g = *GImGui;
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

    return drag;
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


bool GUISystem::ImageButton(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding, ImGuiButtonFlags flags) {
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    const bool result = ImageButtonInternal(imageId.data(), descriptor, size, framePadding, flags);

    ImGui::PopStyleColor();

    return result;
}

bool GUISystem::ImageButtonInternal(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding, ImGuiButtonFlags flags) {
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    if (window->SkipItems)
        return false;

    ImVec4 bg_col = ImVec4(0,0,0,0);
    ImVec4 tint_col = ImVec4(1,1,1,1);
    ImVec2 uv0, uv1;

    if (m_pipeLine == Graphics::PipelineType::OpenGL) {
        uv0 = ImVec2(0, 1);
        uv1 = ImVec2(1, 0);
    }
    else {
        uv0 = ImVec2(-1, 0);
        uv1 = ImVec2(0, 1);
    }

    /// Default is to use texture ID as ID. User can still push string/integer prefixes.
    ImGui::PushID((void*)(intptr_t)descriptor);
    const ImGuiID id = window->GetID(imageId.data());
    ImGui::PopID();

    const ImVec2 padding = (framePadding >= 0) ? ImVec2((float)framePadding, (float)framePadding) : g.Style.FramePadding;

    const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(size.x, size.y) + padding * 2);
    ImGui::ItemSize(bb);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    ImGui::RenderNavHighlight(bb, id);
    ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
    if (bg_col.w > 0.0f)
        window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bg_col));
    window->DrawList->AddImage((ImTextureID)descriptor, bb.Min + padding, bb.Max - padding, uv0, uv1, ImGui::GetColorU32(tint_col));

    return pressed;
}

bool GUISystem::ImageButton(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
    return ImageButton(imageId.data(), descriptor, size, framePadding, ImGuiButtonFlags_None);
}

bool GUISystem::ImageButtonDouble(std::string_view&& imageId, void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
    return ImageButton(imageId.data(), descriptor, size, framePadding, ImGuiButtonFlags_PressedOnDoubleClick);
}

bool GUISystem::ImageButton(void *descriptor, const SR_MATH_NS::IVector2 &size, int32_t framePadding) {
    return ImageButton("##image", descriptor, size, framePadding);
}

bool GUISystem::ImageButton(void *descriptor, const SR_MATH_NS::IVector2 &size) {
    return ImageButton(descriptor, size, -1);
}

bool GUISystem::BeginDragDropTargetWindow(const char* payload_type)  //взято с #5539 https://github.com/ocornut/imgui/issues/5539
{
    using namespace ImGui;
    ImRect inner_rect = GetCurrentWindow()->InnerRect;
    if (BeginDragDropTargetCustom(inner_rect, GetID("##WindowBgArea")))
        if (const ImGuiPayload* payload = AcceptDragDropPayload(payload_type, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
        {
            if (payload->IsPreview())
            {
                ImDrawList* draw_list = GetForegroundDrawList();
                draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                draw_list->AddRect(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
            }
            if (payload->IsDelivery())
                return true;
            EndDragDropTarget();
        }
    return false;
}

void GUISystem::DrawTexture(void *descriptor, const SR_MATH_NS::IVector2 &size) {
    if (m_pipeLine == Graphics::PipelineType::OpenGL) {
        DrawImage(descriptor, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
    }
    else {
        DrawImage(descriptor, ImVec2(size.x, size.y), ImVec2(-1, 0), ImVec2(0, 1), {1, 1, 1, 1}, {0, 0, 0, 0}, true);
    }
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

    if (m_pipeLine == Graphics::PipelineType::OpenGL)
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

void GUISystem::DrawComponents(const SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>& gameObject) {
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
            SR_ERROR("GUISystem::SetGuizmoTool() : unknown tool id!");
            return;
    }
}

static SR_UTILS_NS::Path GetNewScenePath() {
    auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scenes/New-scene.scene");

    uint64_t index = 0;
    while (scenePath.Exists()) {
        scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(SR_FORMAT("Scenes/New-scene-%u.scene", index));
        ++index;
    }

    return scenePath;
}

static SR_UTILS_NS::Path GetNewPrefabPath() {
    auto&& scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scenes/new-prefab.prefab");

    uint64_t index = 0;
    while (scenePath.Exists()) {
        scenePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(SR_FORMAT("Scenes/new-prefab-%u.prefab", index));
        ++index;
    }

    return scenePath;
}

bool GUISystem::BeginMenuBar() {
    //if (ImGui::BeginMainMenuBar()) {

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New scene")) {
            Engine::Instance().SetScene(SR_WORLD_NS::Scene::New(GetNewScenePath()));
            Engine::Instance().GetEditor()->CacheScenePath(Engine::Instance().GetScene()->GetPath());
        }

        ImGui::Separator();

        if (ImGui::MenuItem("New prefab")) {
            if (auto&& scene = Engine::Instance().GetScene(); scene.RecursiveLockIfValid()) {
                //TODO: проверку на то, что нынешний префаб не сохранён, чтобы не спамить ими
                scene->Save();
                Engine::Instance().GetEditor()->CacheScenePath(Engine::Instance().GetScene()->GetPath());
                scene.Unlock();
            }

            Engine::Instance().SetScene(SR_WORLD_NS::Scene::New(GetNewPrefabPath()));
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Load")) {
            auto&& scenesPath = Helper::ResourceManager::Instance().GetResPath();
            if (auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.Empty()) {
                if (path.GetExtensionView() == "scene") {
                    auto &&folder = SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath(path);

                    if (auto &&scene = SR_WORLD_NS::Scene::Load(folder)) {
                        Engine::Instance().SetScene(scene);
                        Engine::Instance().GetEditor()->CacheScenePath(folder);
                    }
                }
                else {
                    if (auto &&scene = SR_WORLD_NS::Scene::Load(path)) {
                        Engine::Instance().SetScene(scene);
                        Engine::Instance().GetEditor()->CacheScenePath(path);
                    }
                }
            }
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Save")) {
            if (auto&& scene = Engine::Instance().GetScene(); scene.RecursiveLockIfValid()) {
                scene->Save();
                scene.Unlock();
            }
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Save at")) {
            if (auto&& scene = Engine::Instance().GetScene(); scene.RecursiveLockIfValid()) {
                const auto scenesPath = Helper::ResourceManager::Instance().GetResPath();
                if (auto path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(scenesPath.ToString(), { { "Scene", "scene,prefab" } }); !path.Empty()) {
                    if (scene->SaveAt(path)) {
                        SR_SYSTEM_LOG("GUISystem::BeginMenuBar() : scene is saved as \"" + path.ToString() + "\"");
                    }
                    else {
                        SR_ERROR("GUISystem::BeginMenuBar() : failed to save scene! \n\tPath: \"" + path.ToString() + "\"");
                    }
                }
                scene.Unlock();
                Engine::Instance().GetEditor()->CacheScenePath(scene->GetPath());
            }
            else {
                SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
            }
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Close scene")) {
            if (auto&& scene = Engine::Instance().GetScene()) {
                scene->Save();
            }
            Engine::Instance().SetScene(SR_WORLD_NS::Scene::Empty());
            Engine::Instance().GetEditor()->CacheScenePath("NONE");
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Clear shaders cache")) {
            SR_SRSL_NS::SRSLShader::ClearShadersCache();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            SR_UTILS_NS::EventManager::Instance().Broadcast(SR_UTILS_NS::EventManager::Event::Exit);
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Editor")) {
        if (ImGui::MenuItem("Empty GameObject")) {
            if (auto&& scene = Engine::Instance().GetScene()) {
                scene->Instance("New GameObject");
            }
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Instance from file")) {
            if (auto&& scene = Engine::Instance().GetScene(); scene.RecursiveLockIfValid()) {
                auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                if (auto path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath.ToString(), { { "Any model", "prefab,pmx,fbx,obj,blend,dae,abc,stl,ply,glb,gltf,x3d,sfg,bvh" } }); !path.Empty()) {
                    /// TODO:Сделать обратимость
                    scene->InstanceFromFile(path);
                }
                scene.Unlock();
            }
            else {
                SR_WARN("GUISystem::BeginMenuBar() : scene is not valid!");
            }
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
        if (ImGui::MenuItem("Assets")) {
            Engine::Instance().GetEditor()->GetWidget<FileBrowser>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Hierarchy")) {
            Engine::Instance().GetEditor()->GetWidget<Hierarchy>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Inspector")) {
            Engine::Instance().GetEditor()->GetWidget<Inspector>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Scene")) {
            Engine::Instance().GetEditor()->GetWidget<SceneViewer>()->Open();
        }

        ImGui::Separator();

        //if (ImGui::MenuItem("Visual Script")) {
        //    Engine::Instance().GetEditor()->GetWidget<VisualScriptEditor>()->Open();
        //}

        if (ImGui::MenuItem("Animator")) {
            Engine::Instance().GetEditor()->GetWidget<AnimatorEditor>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("World edit")) {
            Engine::Instance().GetEditor()->GetWidget<WorldEdit>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Settings")) {
            Engine::Instance().GetEditor()->GetWidget<EngineSettings>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Statistics")) {
            Engine::Instance().GetEditor()->GetWidget<EngineStatistics>()->Open();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Reset to default")) {
            Engine::Instance().GetEditor()->ResetToDefault();
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Close all")) {
            Engine::Instance().GetEditor()->CloseAllWidgets();
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("About")) {
        ImGui::EndMenu();
    }

    ImGui::PopStyleVar();

    auto &&io = ImGui::GetIO();

    ImGui::Text("|   FPS: %.2f (%.2gms)", io.Framerate, io.Framerate > 0.f ? 1000.0f / io.Framerate : 0.0f);

    return true;
}

void GUISystem::EndMenuBar() {
    //ImGui::EndMainMenuBar();
}





