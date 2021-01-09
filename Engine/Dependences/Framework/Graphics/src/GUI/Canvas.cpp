//
// Created by Nikita on 08.01.2021.
//

#include "GUI/Canvas.h"

#include <GL/glew.h>
#include <imgui.h>
#include <ResourceManager/ResourceManager.h>

Framework::Graphics::GUI::Canvas::Canvas() : m_env(Graphics::Environment::Get()) {

}

bool Framework::Graphics::GUI::Canvas::Init() {
    Helper::Debug::Graph("Canvas::Init() : initializing canvas...");
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Set font
    ImFont* pFont = io.Fonts->AddFontFromFileTTF((Helper::ResourceManager::GetResourcesFolder() + "\\Fonts\\CalibriL.ttf").c_str(), 12.0f);

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
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    this->m_env->InitGUI();

    return true;
}

bool Framework::Graphics::GUI::Canvas::Stop() {
    Helper::Debug::Graph("Canvas::Stop() : stopping canvas...");

    this->m_env->StopGUI();

    ImGui::DestroyContext();

    return false;
}


