//
// Created by Nikita on 28.06.2021.
//

#include <Environment/Environment.h>
#include <GUI.h>
#include <GUI/Icons.h>
#include <ResourceManager/ResourceManager.h>

bool Framework::Graphics::Environment::PreInitGUI(const std::string &fontPath) {
    SR_GRAPH("Environment::InitGUI() : pre-initializing ImGUI library...");

    {
        //IMGUI_CHECKVERSION();
        m_guiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImFont* pFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f);

        ImFontConfig config;
        config.MergeMode = false;
        config.GlyphMinAdvanceX = 13.0f;
        static const ImWchar icon_ranges[] = { SR_ICON_MIN, SR_ICON_MAX, 0 };
        m_iconFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(
                (Helper::ResourceManager::Instance().GetResPath().Concat("/Fonts/fa-solid-900.ttf")).CStr(),
                40.0f, &config, icon_ranges);

        //io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift       = true;
        io.ConfigWindowsResizeFromEdges = true;
        //TODO: io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigDockingWithShift = true;
        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
    }

    return true;
}

void Framework::Graphics::Environment::SetWinCallBack(const std::function<void(WinEvents, void * , void * , void * )>& callback) {
    g_callback = std::move(callback);
}

