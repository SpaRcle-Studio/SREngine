//
// Created by Nikita on 08.01.2021.
//

#include "GUI/Canvas.h"

#include <imgui.h>
#include <ResourceManager/ResourceManager.h>

bool Framework::Graphics::GUI::Canvas::Init() {
    Helper::Debug::Graph("Canvas::Init() : initializing canvas...");
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    {
        ImFont* pFont = io.Fonts->AddFontFromFileTTF((Helper::ResourceManager::GetResourcesFolder() + "\\Fonts\\CalibriL.ttf").c_str(), 12.0f);

        unsigned char* pixels;
        int width, height, bytes_per_pixels;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytes_per_pixels);
        //GLuint id = loadTexture(pixels, width, height, 4);
        //io.Fonts->SetTexID((void*)id);
    }

    //io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDockingWithShift = true;
    io.ConfigWindowsResizeFromEdges = true;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigDockingWithShift = true;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    //!ImGui_ImplGlfw_InitForOpenGL(m_glfw_window, true);
    //!ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

bool Framework::Graphics::GUI::Canvas::Stop() {
    return false;
}
