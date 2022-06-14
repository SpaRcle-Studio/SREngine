//
// Created by Nikita on 28.06.2021.
//

#include <Environment/Environment.h>
#include <Utils/GUI.h>
#include <GUI/Icons.h>
#include <Utils/ResourceManager/ResourceManager.h>

bool SR_GRAPH_NS::Environment::PreInitGUI(const std::string &fontPath) {
    SR_GRAPH("Environment::InitGUI() : pre-initializing ImGUI library...");

    {
        //IMGUI_CHECKVERSION();
        m_guiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        SR_GRAPH("Environment::InitGUI() : load editor font...\n\tPath: " + fontPath);
        ImFont* pFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f);

        const auto&& iconsFont = Helper::ResourceManager::Instance().GetFontsPath().Concat("fa-solid-900.ttf");

        SR_GRAPH("Environment::InitGUI() : load icon font...\n\tPath: " + iconsFont.ToString());
        ImFontConfig config;
        config.MergeMode = false;
        config.GlyphMinAdvanceX = 13.0f;
        static const ImWchar icon_ranges[] = { SR_ICON_MIN, SR_ICON_MAX, 0 };
        m_iconFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(iconsFont.CStr(), 40.0f, &config, icon_ranges);

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

