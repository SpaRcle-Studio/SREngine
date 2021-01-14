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
void Framework::Graphics::GUI::ICanvas::InitStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.TabRounding = 2.0;
    style.PopupRounding = 2.0;
    style.WindowRounding = 2.0;
    style.WindowTitleAlign = ImVec2(0.5, 0.84);
    //style.ChildWindowRounding = 2.0;
    style.ChildRounding = 2.0;
    style.FrameRounding = 2.0;
    style.ItemSpacing = ImVec2(5.0, 4.0);
    style.ScrollbarSize = 13.0;
    style.ScrollbarRounding = 0;
    style.GrabMinSize = 8.0;
    style.GrabRounding = 1.0;

    colors[ImGuiCol_::ImGuiCol_FrameBg]                = ImVec4(0.16, 0.48, 0.42, 0.54);
    colors[ImGuiCol_::ImGuiCol_FrameBgHovered]         = ImVec4(0.26, 0.98, 0.85, 0.40);
    colors[ImGuiCol_::ImGuiCol_FrameBgActive]          = ImVec4(0.26, 0.98, 0.85, 0.67);
    colors[ImGuiCol_::ImGuiCol_TitleBg]                = ImVec4(0.04, 0.04, 0.04, 1.00);
    colors[ImGuiCol_::ImGuiCol_TitleBgActive]          = ImVec4(0.16, 0.48, 0.42, 1.00);
    colors[ImGuiCol_::ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00, 0.00, 0.00, 0.51);
    colors[ImGuiCol_::ImGuiCol_CheckMark]              = ImVec4(0.26, 0.98, 0.85, 1.00);
    colors[ImGuiCol_::ImGuiCol_SliderGrab]             = ImVec4(0.24, 0.88, 0.77, 1.00);
    colors[ImGuiCol_::ImGuiCol_SliderGrabActive]       = ImVec4(0.26, 0.98, 0.85, 1.00);
    colors[ImGuiCol_::ImGuiCol_Button]                 = ImVec4(0.26, 0.98, 0.85, 0.40);
    colors[ImGuiCol_::ImGuiCol_ButtonHovered]          = ImVec4(0.26, 0.98, 0.85, 1.00);
    colors[ImGuiCol_::ImGuiCol_ButtonActive]           = ImVec4(0.06, 0.98, 0.82, 1.00);
    colors[ImGuiCol_::ImGuiCol_Header]                 = ImVec4(0.26, 0.98, 0.85, 0.31);
    colors[ImGuiCol_::ImGuiCol_HeaderHovered]          = ImVec4(0.26, 0.98, 0.85, 0.80);
    colors[ImGuiCol_::ImGuiCol_HeaderActive]           = ImVec4(0.26, 0.98, 0.85, 1.00);
    colors[ImGuiCol_::ImGuiCol_Separator]              = colors[ImGuiCol_::ImGuiCol_Border];
    colors[ImGuiCol_::ImGuiCol_SeparatorHovered]       = ImVec4(0.10, 0.75, 0.63, 0.78);
    colors[ImGuiCol_::ImGuiCol_SeparatorActive]        = ImVec4(0.10, 0.75, 0.63, 1.00);
    colors[ImGuiCol_::ImGuiCol_ResizeGrip]             = ImVec4(0.26, 0.98, 0.85, 0.25);
    colors[ImGuiCol_::ImGuiCol_ResizeGripHovered]      = ImVec4(0.26, 0.98, 0.85, 0.67);
    colors[ImGuiCol_::ImGuiCol_ResizeGripActive]       = ImVec4(0.26, 0.98, 0.85, 0.95);
    colors[ImGuiCol_::ImGuiCol_PlotLines]              = ImVec4(0.61, 0.61, 0.61, 1.00);
    colors[ImGuiCol_::ImGuiCol_PlotLinesHovered]       = ImVec4(1.00, 0.81, 0.35, 1.00);
    colors[ImGuiCol_::ImGuiCol_TextSelectedBg]         = ImVec4(0.26, 0.98, 0.85, 0.35);
    colors[ImGuiCol_::ImGuiCol_Text]                   = ImVec4(1.00, 1.00, 1.00, 1.00);
    colors[ImGuiCol_::ImGuiCol_TextDisabled]           = ImVec4(0.50, 0.50, 0.50, 1.00);
    colors[ImGuiCol_::ImGuiCol_WindowBg]               = ImVec4(0.06, 0.06, 0.06, 0.94);
    //colors[ImGuiCol_::ImGuiCol_ChildWindowBg]          = ImVec4(1.00, 1.00, 1.00, 0.00);
    colors[ImGuiCol_::ImGuiCol_PopupBg]                = ImVec4(0.08, 0.08, 0.08, 0.94);
    //colors[ImGuiCol_::ImGuiCol_ComboBg]                = colors[ImGuiCol_::ImGuiCol_PopupBg];
    colors[ImGuiCol_::ImGuiCol_Border]                 = ImVec4(0.43, 0.43, 0.50, 0.50);
    colors[ImGuiCol_::ImGuiCol_BorderShadow]           = ImVec4(0.00, 0.00, 0.00, 0.00);
    colors[ImGuiCol_::ImGuiCol_MenuBarBg]              = ImVec4(0.14, 0.14, 0.14, 1.00);
    colors[ImGuiCol_::ImGuiCol_ScrollbarBg]            = ImVec4(0.02, 0.02, 0.02, 0.53);
    colors[ImGuiCol_::ImGuiCol_ScrollbarGrab]          = ImVec4(0.31, 0.31, 0.31, 1.00);
    colors[ImGuiCol_::ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41, 0.41, 0.41, 1.00);
    colors[ImGuiCol_::ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51, 0.51, 0.51, 1.00);
    //colors[ImGuiCol_::ImGuiCol_CloseButton]            = ImVec4(0.41, 0.41, 0.41, 0.50);
    //colors[ImGuiCol_::ImGuiCol_CloseButtonHovered]     = ImVec4(0.98, 0.39, 0.36, 1.00);
    //colors[ImGuiCol_::ImGuiCol_CloseButtonActive]      = ImVec4(0.98, 0.39, 0.36, 1.00);
    colors[ImGuiCol_::ImGuiCol_PlotHistogram]          = ImVec4(0.90, 0.70, 0.00, 1.00);
    colors[ImGuiCol_::ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00, 0.60, 0.00, 1.00);
    colors[ImGuiCol_::ImGuiCol_ModalWindowDarkening]   = ImVec4(0.80, 0.80, 0.80, 0.35);
}
