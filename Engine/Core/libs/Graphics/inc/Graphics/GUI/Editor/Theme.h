//
// Created by Monika on 02.03.2022.
//

#ifndef SRENGINE_THEME_H
#define SRENGINE_THEME_H

#include <Utils/GUI.h>
#include <Utils/Math/Vector4.h>

namespace SR_GRAPH_NS::GUI {
    inline static const std::unordered_map<std::string, float ImGuiStyle::*> STYLE_FLOAT_VALUES = {
            { "Alpha", &ImGuiStyle::Alpha },
            { "WindowRounding", &ImGuiStyle::WindowRounding },
            { "WindowBorderSize", &ImGuiStyle::WindowBorderSize },
            { "ChildRounding", &ImGuiStyle::ChildRounding },
            { "ChildBorderSize", &ImGuiStyle::ChildBorderSize },
            { "PopupRounding", &ImGuiStyle::PopupRounding },
            { "PopupBorderSize", &ImGuiStyle::PopupBorderSize },
            { "FrameRounding", &ImGuiStyle::FrameRounding },
            { "FrameBorderSize", &ImGuiStyle::FrameBorderSize },
            { "IndentSpacing", &ImGuiStyle::IndentSpacing },
            { "ColumnsMinSpacing", &ImGuiStyle::ColumnsMinSpacing },
            { "ScrollbarSize", &ImGuiStyle::ScrollbarSize },
            { "ScrollbarRounding", &ImGuiStyle::ScrollbarRounding },
            { "GrabMinSize", &ImGuiStyle::GrabMinSize },
            { "GrabRounding", &ImGuiStyle::GrabRounding },
            { "LogSliderDeadzone", &ImGuiStyle::LogSliderDeadzone },
            { "TabRounding", &ImGuiStyle::TabRounding },
            { "TabBorderSize", &ImGuiStyle::TabBorderSize },
            { "TabMinWidthForCloseButton", &ImGuiStyle::TabMinWidthForCloseButton },
            { "MouseCursorScale", &ImGuiStyle::MouseCursorScale },
            { "CurveTessellationTol", &ImGuiStyle::CurveTessellationTol },
            //{ "CircleSegmentMaxError", &ImGuiStyle::CircleSegmentMaxError },
    };

    inline static const std::unordered_map<std::string, bool ImGuiStyle::*> STYLE_BOOL_VALUES = {
            { "AntiAliasedLines", &ImGuiStyle::AntiAliasedLines },
            { "AntiAliasedLinesUseTex", &ImGuiStyle::AntiAliasedLinesUseTex },
            { "AntiAliasedFill", &ImGuiStyle::AntiAliasedFill },
    };

    inline static const std::unordered_map<std::string, ImVec2 ImGuiStyle::*> STYLE_SIZE_VALUES = {
            { "WindowPadding", &ImGuiStyle::WindowPadding },
            { "WindowMinSize", &ImGuiStyle::WindowMinSize },
            { "WindowTitleAlign", &ImGuiStyle::WindowTitleAlign },
            { "FramePadding", &ImGuiStyle::FramePadding },
            { "ItemSpacing", &ImGuiStyle::ItemSpacing },
            { "ItemInnerSpacing", &ImGuiStyle::ItemInnerSpacing },
            { "TouchExtraPadding", &ImGuiStyle::TouchExtraPadding },
            { "ButtonTextAlign", &ImGuiStyle::ButtonTextAlign },
            { "SelectableTextAlign", &ImGuiStyle::SelectableTextAlign },
            { "DisplayWindowPadding", &ImGuiStyle::DisplayWindowPadding },
            { "DisplaySafeAreaPadding", &ImGuiStyle::DisplaySafeAreaPadding },
    };

    inline static const std::unordered_map<std::string, ImGuiCol_> STYLE_COLORS = {
            { "ImGuiCol_Text", ImGuiCol_Text },
            { "ImGuiCol_TextDisabled", ImGuiCol_TextDisabled },
            { "ImGuiCol_ChildBg", ImGuiCol_ChildBg },
            { "ImGuiCol_WindowBg", ImGuiCol_WindowBg },
            { "ImGuiCol_PopupBg", ImGuiCol_PopupBg },
            { "ImGuiCol_Border", ImGuiCol_Border },
            { "ImGuiCol_BorderShadow", ImGuiCol_BorderShadow },
            { "ImGuiCol_FrameBg", ImGuiCol_FrameBg },
            { "ImGuiCol_FrameBgHovered", ImGuiCol_FrameBgHovered },
            { "ImGuiCol_FrameBgActive", ImGuiCol_FrameBgActive },
            { "ImGuiCol_TitleBg", ImGuiCol_TitleBg },
            { "ImGuiCol_TitleBgActive", ImGuiCol_TitleBgActive },
            { "ImGuiCol_TitleBgCollapsed", ImGuiCol_TitleBgCollapsed },
            { "ImGuiCol_MenuBarBg", ImGuiCol_MenuBarBg },
            { "ImGuiCol_ScrollbarBg", ImGuiCol_ScrollbarBg },
            { "ImGuiCol_ScrollbarGrab", ImGuiCol_ScrollbarGrab },
            { "ImGuiCol_ScrollbarGrabHovered", ImGuiCol_ScrollbarGrabHovered },
            { "ImGuiCol_ScrollbarGrabActive", ImGuiCol_ScrollbarGrabActive },
            { "ImGuiCol_CheckMark", ImGuiCol_CheckMark },
            { "ImGuiCol_SliderGrab", ImGuiCol_SliderGrab },
            { "ImGuiCol_SliderGrabActive", ImGuiCol_SliderGrabActive },
            { "ImGuiCol_Button", ImGuiCol_Button },
            { "ImGuiCol_ButtonHovered", ImGuiCol_ButtonHovered },
            { "ImGuiCol_ButtonActive", ImGuiCol_ButtonActive },
            { "ImGuiCol_Header", ImGuiCol_Header },
            { "ImGuiCol_HeaderHovered", ImGuiCol_HeaderHovered },
            { "ImGuiCol_HeaderActive", ImGuiCol_HeaderActive },
            { "ImGuiCol_Separator", ImGuiCol_Separator },
            { "ImGuiCol_SeparatorHovered", ImGuiCol_SeparatorHovered },
            { "ImGuiCol_SeparatorActive", ImGuiCol_SeparatorActive },
            { "ImGuiCol_ResizeGrip", ImGuiCol_ResizeGrip },
            { "ImGuiCol_ResizeGripHovered", ImGuiCol_ResizeGripHovered },
            { "ImGuiCol_ResizeGripActive", ImGuiCol_ResizeGripActive },
            { "ImGuiCol_PlotLines", ImGuiCol_PlotLines },
            { "ImGuiCol_PlotLinesHovered", ImGuiCol_PlotLinesHovered },
            { "ImGuiCol_PlotHistogram", ImGuiCol_PlotHistogram },
            { "ImGuiCol_PlotHistogramHovered", ImGuiCol_PlotHistogramHovered },
            { "ImGuiCol_TextSelectedBg", ImGuiCol_TextSelectedBg },
            { "ImGuiCol_ModalWindowDimBg", ImGuiCol_ModalWindowDimBg },
            { "ImGuiCol_DragDropTarget", ImGuiCol_DragDropTarget },
            { "ImGuiCol_NavHighlight", ImGuiCol_NavHighlight },
            { "ImGuiCol_NavWindowingHighlight", ImGuiCol_NavWindowingHighlight },
            { "ImGuiCol_NavWindowingDimBg", ImGuiCol_NavWindowingDimBg },

            { "ImGuiCol_DockingEmptyBg", ImGuiCol_DockingEmptyBg },
            { "ImGuiCol_Tab", ImGuiCol_Tab },
            { "ImGuiCol_TabHovered", ImGuiCol_TabHovered },
            { "ImGuiCol_TabActive", ImGuiCol_TabActive },
            { "ImGuiCol_TabUnfocused", ImGuiCol_TabUnfocused },
            { "ImGuiCol_TabUnfocusedActive", ImGuiCol_TabUnfocusedActive },
            { "ImGuiCol_DockingPreview", ImGuiCol_DockingPreview },
    };

    class Theme : public SR_UTILS_NS::NonCopyable {
    public:
        ~Theme() override = default;

    public:
        static Theme* Load(const SR_UTILS_NS::Path& path);
        static bool Save(const std::string& path, const ImGuiStyle& style);
        static SR_MATH_NS::FColor ImVec4ToColor(ImVec4 imVec4);
        static SR_MATH_NS::FVector2 ImVec2ToFVector2(ImVec2 imVec2);

    public:
        bool Save(const SR_UTILS_NS::Path& path);

        bool Apply(ImGuiStyle& style) const;

        void SetColor(const std::string& id, const SR_MATH_NS::FColor& color);
        void SetSize(const std::string& id, const SR_MATH_NS::FVector2& size);
        void SetFloat(const std::string& id, float_t value);
        void SetBool(const std::string& id, bool value);

    private:
        std::unordered_map<std::string, SR_MATH_NS::FColor> m_colors;
        std::unordered_map<std::string, SR_MATH_NS::FVector2> m_sizes;
        std::unordered_map<std::string, float_t> m_floats;
        std::unordered_map<std::string, float_t> m_booleans;

    };
}

#endif //SRENGINE_THEME_H
