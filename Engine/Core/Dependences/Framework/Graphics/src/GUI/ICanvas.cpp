//
// Created by Nikita on 08.01.2021.
//

#include <GUI/ICanvas.h>
#include <Utils/GUI.h>
#include <GUI/Editor/Theme.h>

void Style_1(){
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
    //colors[ImGuiCol_::ImGuiCol_ModalWindowDarkening]   = ImVec4(0.80, 0.80, 0.80, 0.35);
}

void Style_2(){
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    /*colors[ImGuiCol_Text]                   = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border]                 = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button]                 = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header]                 = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);*/

    colors[ImGuiCol_WindowBg]              = ImVec4(0.14, 0.12, 0.16, 1.00);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.30, 0.20, 0.39, 0.00);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.05, 0.05, 0.10, 0.90);
    colors[ImGuiCol_Border]                = ImVec4(0.89, 0.85, 0.92, 0.30);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00, 0.00, 0.00, 0.00);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.30, 0.20, 0.39, 1.00);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.41, 0.19, 0.63, 0.68);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.41, 0.19, 0.63, 0.45);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.41, 0.19, 0.63, 0.35);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.41, 0.19, 0.63, 0.78);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.30, 0.20, 0.39, 0.57);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.30, 0.20, 0.39, 1.00);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.41, 0.19, 0.63, 0.31);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41, 0.19, 0.63, 0.78);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.30, 0.20, 0.39, 1.00);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.56, 0.61, 1.00, 1.00);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.41, 0.19, 0.63, 0.24);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_Button]                = ImVec4(0.41, 0.19, 0.63, 0.44);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.41, 0.19, 0.63, 0.86);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.64, 0.33, 0.94, 1.00);
    colors[ImGuiCol_Header]                = ImVec4(0.41, 0.19, 0.63, 0.76);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.41, 0.19, 0.63, 0.86);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.41, 0.19, 0.63, 0.20);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.41, 0.19, 0.63, 0.78);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.89, 0.85, 0.92, 0.63);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.89, 0.85, 0.92, 0.63);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.41, 0.19, 0.63, 1.00);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.41, 0.19, 0.63, 0.43);
//    colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20, 0.20, 0.20, 0.35);

    //style->ChildRounding = 4.0f;
    style->FrameBorderSize = 1.0f;
    //style->FrameRounding = 2.0f;
    style->GrabMinSize = 7.0f;
    //style->PopupRounding = 2.0f;
    //style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 13.0f;
    style->TabBorderSize = 1.0f;
    //style->TabRounding = 0.0f;
    //style->WindowRounding = 4.0f;


    style->WindowBorderSize = 1;
    style->ChildBorderSize  = 1;
    style->PopupBorderSize  = 1;

    style->WindowRounding    = 3;
    style->ChildRounding     = 3;
    style->FrameRounding     = 3;
    style->ScrollbarRounding = 2;
    style->GrabRounding      = 3;

    style->TabRounding   = 3;

    style->PopupRounding = 3;

    style->WindowPadding = ImVec2(4, 4);
    style->FramePadding  = ImVec2(6, 4);
    style->ItemSpacing   = ImVec2(6, 2);
}

void Style_3(){
    ImGuiStyle & style = ImGui::GetStyle();
    ImVec4 * colors = style.Colors;

    /// 0 = FLAT APPEARENCE
    /// 1 = MORE "3D" LOOK
    int is3D = 1;

    /*colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
    colors[ImGuiCol_Separator]              = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);*/

    style.PopupRounding = 3;

    style.WindowPadding = ImVec2(4, 4);
    style.FramePadding  = ImVec2(6, 4);
    style.ItemSpacing   = ImVec2(6, 2);

    style.ScrollbarSize = 18;

    style.WindowBorderSize = 1;
    style.ChildBorderSize  = 1;
    style.PopupBorderSize  = 1;
    style.FrameBorderSize  = is3D;

    style.WindowRounding    = 3;
    style.ChildRounding     = 3;
    style.FrameRounding     = 3;
    style.ScrollbarRounding = 2;
    style.GrabRounding      = 3;

    style.TabBorderSize = is3D;
    style.TabRounding   = 3;

    colors[ImGuiCol_DockingEmptyBg]     = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_Tab]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered]         = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_TabActive]          = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_DockingPreview]     = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}
