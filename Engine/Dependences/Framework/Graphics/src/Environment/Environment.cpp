//
// Created by Nikita on 28.06.2021.
//

#include <Environment/Environment.h>

#include <imgui.h>

bool Framework::Graphics::Environment::PreInitGUI(const std::string &fontPath) {
    Helper::Debug::Graph("Environment::InitGUI() : pre-initializing ImGUI library...");

    {
        //IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImFont* pFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f);

        //io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift       = true;
        io.ConfigWindowsResizeFromEdges = true;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigDockingWithShift = true;
        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
    }

    return true;
}

bool Framework::Graphics::Environment::InitWindowFormat(const Framework::Graphics::Types::WindowFormat &windowFormat)  {
    if (m_winFormat)
        return false;
    else {
        this->m_winFormat = Types::WindowFormat::AllocMemory();
        this->m_winFormat->SetFormat(windowFormat);
        return true;
    }
}

