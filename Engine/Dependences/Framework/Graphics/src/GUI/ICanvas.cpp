//
// Created by Nikita on 08.01.2021.
//

#include "GUI/ICanvas.h"

#include <GL/glew.h>
#include <imgui.h>
#include <ResourceManager/ResourceManager.h>
#include <Debug.h>

/*
bool Framework::Graphics::GUI::ICanvas::Init() {
    Helper::Debug::Graph("ICanvas::Init() : initializing canvas...");

    g_env = Graphics::Environment::Get();

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
    g_env->InitGUI();

    return true;
}


bool Framework::Graphics::GUI::ICanvas::Stop() {
    Helper::Debug::Graph("ICanvas::Stop() : stopping canvas...");

    g_env->StopGUI();

    ImGui::DestroyContext();

    return false;
}*/

/*
bool Framework::Graphics::GUI::ICanvas::Free() {
    Helper::Debug::Log("ICanvas::Free() : free canvas pointer...");
    delete this;
    return true;
}

void Framework::Graphics::GUI::ICanvas::Draw() {

}

bool Framework::Graphics::GUI::ICanvas::Close() {
    Helper::Debug::Log("ICanvas::Close() : close canvas...");
    return true;
}
*/