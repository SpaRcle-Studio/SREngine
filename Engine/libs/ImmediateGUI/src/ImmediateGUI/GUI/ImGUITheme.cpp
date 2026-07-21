//
// Created by Monika on 11.07.2026.
//

#include <ImmediateGUI/GUI/ImGUITheme.h>
#include <ImmediateGUI/Impl/ImGUI.h>

#include <Utils/Resources/Xml.h>

#include <Codegen/ImGUITheme.generated.hpp>

namespace SR_GRAPH_GUI_NS::Immediate {
    SR_MATH_NS::FColor ImVec4ToColor(ImVec4 imVec4) { return SR_MATH_NS::FColor(imVec4.x, imVec4.y, imVec4.z, imVec4.w); }
    SR_MATH_NS::FVector2 ImVec2ToFVector2(ImVec2 imVec2) { return SR_MATH_NS::FVector2(imVec2.x, imVec2.y); }
    ImVec2 FVector2ToImVec2(SR_MATH_NS::FVector2 vec2) { return ImVec2(vec2.x, vec2.y); }
    ImVec4 ColorToImVec4(SR_MATH_NS::FColor color) { return ImVec4(color.r, color.g, color.b, color.a); }

    std::vector<std::pair<ImGUIThemeVec2Var, ImVec2 ImGuiStyle::*>> STYLE_VEC2_VALUES = {
        { ImGUIThemeVec2Var::WindowPadding, &ImGuiStyle::WindowPadding },
        { ImGUIThemeVec2Var::WindowMinSize, &ImGuiStyle::WindowMinSize },
        { ImGUIThemeVec2Var::WindowTitleAlign, &ImGuiStyle::WindowTitleAlign },
        { ImGUIThemeVec2Var::FramePadding, &ImGuiStyle::FramePadding },
        { ImGUIThemeVec2Var::ItemSpacing, &ImGuiStyle::ItemSpacing },
        { ImGUIThemeVec2Var::ItemInnerSpacing, &ImGuiStyle::ItemInnerSpacing },
        { ImGUIThemeVec2Var::CellPadding, &ImGuiStyle::CellPadding },
        { ImGUIThemeVec2Var::TouchExtraPadding, &ImGuiStyle::TouchExtraPadding },
        { ImGUIThemeVec2Var::TableAngledHeadersTextAlign, &ImGuiStyle::TableAngledHeadersTextAlign },
        { ImGUIThemeVec2Var::ButtonTextAlign, &ImGuiStyle::ButtonTextAlign },
        { ImGUIThemeVec2Var::SelectableTextAlign, &ImGuiStyle::SelectableTextAlign },
        { ImGUIThemeVec2Var::SeparatorTextAlign, &ImGuiStyle::SeparatorTextAlign },
        { ImGUIThemeVec2Var::SeparatorTextPadding, &ImGuiStyle::SeparatorTextPadding },
        { ImGUIThemeVec2Var::DisplayWindowPadding, &ImGuiStyle::DisplayWindowPadding },
        { ImGUIThemeVec2Var::DisplaySafeAreaPadding, &ImGuiStyle::DisplaySafeAreaPadding },
    };

    std::vector<std::pair<ImGUIThemeBoolVar, bool ImGuiStyle::*>> STYLE_BOOL_VALUES = {
        { ImGUIThemeBoolVar::AntiAliasedLines, &ImGuiStyle::AntiAliasedLines },
        { ImGUIThemeBoolVar::AntiAliasedLinesUseTex, &ImGuiStyle::AntiAliasedLinesUseTex },
        { ImGUIThemeBoolVar::AntiAliasedFill, &ImGuiStyle::AntiAliasedFill },
        { ImGUIThemeBoolVar::DockingNodeHasCloseButton, &ImGuiStyle::DockingNodeHasCloseButton },
    };

    std::vector<std::pair<ImGUIThemeFloatVar, float_t ImGuiStyle::*>> STYLE_FLOAT_VALUES = {
        { ImGUIThemeFloatVar::FontSizeBase, &ImGuiStyle::FontSizeBase },
        { ImGUIThemeFloatVar::FontScaleMain, &ImGuiStyle::FontScaleMain },
        { ImGUIThemeFloatVar::FontScaleDpi, &ImGuiStyle::FontScaleDpi },
        { ImGUIThemeFloatVar::Alpha, &ImGuiStyle::Alpha },
        { ImGUIThemeFloatVar::DisabledAlpha, &ImGuiStyle::DisabledAlpha },
        { ImGUIThemeFloatVar::WindowRounding, &ImGuiStyle::WindowRounding },
        { ImGUIThemeFloatVar::WindowBorderSize, &ImGuiStyle::WindowBorderSize },
        { ImGUIThemeFloatVar::WindowBorderHoverPadding, &ImGuiStyle::WindowBorderHoverPadding },
        { ImGUIThemeFloatVar::ChildRounding, &ImGuiStyle::ChildRounding },
        { ImGUIThemeFloatVar::ChildBorderSize, &ImGuiStyle::ChildBorderSize },
        { ImGUIThemeFloatVar::PopupRounding, &ImGuiStyle::PopupRounding },
        { ImGUIThemeFloatVar::PopupBorderSize, &ImGuiStyle::PopupBorderSize },
        { ImGUIThemeFloatVar::FrameRounding, &ImGuiStyle::FrameRounding },
        { ImGUIThemeFloatVar::FrameBorderSize, &ImGuiStyle::FrameBorderSize },
        { ImGUIThemeFloatVar::IndentSpacing, &ImGuiStyle::IndentSpacing },
        { ImGUIThemeFloatVar::ColumnsMinSpacing, &ImGuiStyle::ColumnsMinSpacing },
        { ImGUIThemeFloatVar::ScrollbarSize, &ImGuiStyle::ScrollbarSize },
        { ImGUIThemeFloatVar::ScrollbarRounding, &ImGuiStyle::ScrollbarRounding },
        { ImGUIThemeFloatVar::ScrollbarPadding, &ImGuiStyle::ScrollbarPadding },
        { ImGUIThemeFloatVar::GrabMinSize, &ImGuiStyle::GrabMinSize },
        { ImGUIThemeFloatVar::GrabRounding, &ImGuiStyle::GrabRounding },
        { ImGUIThemeFloatVar::LogSliderDeadzone, &ImGuiStyle::LogSliderDeadzone },
        { ImGUIThemeFloatVar::ImageRounding, &ImGuiStyle::ImageRounding },
        { ImGUIThemeFloatVar::ImageBorderSize, &ImGuiStyle::ImageBorderSize },
        { ImGUIThemeFloatVar::TabRounding, &ImGuiStyle::TabRounding },
        { ImGUIThemeFloatVar::TabBorderSize, &ImGuiStyle::TabBorderSize },
        { ImGUIThemeFloatVar::TabMinWidthBase, &ImGuiStyle::TabMinWidthBase },
        { ImGUIThemeFloatVar::TabMinWidthShrink, &ImGuiStyle::TabMinWidthShrink },
        { ImGUIThemeFloatVar::TabCloseButtonMinWidthSelected, &ImGuiStyle::TabCloseButtonMinWidthSelected },
        { ImGUIThemeFloatVar::TabCloseButtonMinWidthUnselected, &ImGuiStyle::TabCloseButtonMinWidthUnselected },
        { ImGUIThemeFloatVar::TabBarBorderSize, &ImGuiStyle::TabBarBorderSize },
        { ImGUIThemeFloatVar::TabBarOverlineSize, &ImGuiStyle::TabBarOverlineSize },
        { ImGUIThemeFloatVar::TableAngledHeadersAngle, &ImGuiStyle::TableAngledHeadersAngle },
        { ImGUIThemeFloatVar::TreeLinesSize, &ImGuiStyle::TreeLinesSize },
        { ImGUIThemeFloatVar::TreeLinesRounding, &ImGuiStyle::TreeLinesRounding },
        { ImGUIThemeFloatVar::MenuItemRounding, &ImGuiStyle::MenuItemRounding },
        { ImGUIThemeFloatVar::SelectableRounding, &ImGuiStyle::SelectableRounding },
        { ImGUIThemeFloatVar::DragDropTargetRounding, &ImGuiStyle::DragDropTargetRounding },
        { ImGUIThemeFloatVar::DragDropTargetBorderSize, &ImGuiStyle::DragDropTargetBorderSize },
        { ImGUIThemeFloatVar::DragDropTargetPadding, &ImGuiStyle::DragDropTargetPadding },
        { ImGUIThemeFloatVar::ColorMarkerSize, &ImGuiStyle::ColorMarkerSize },
        { ImGUIThemeFloatVar::InputTextCursorSize, &ImGuiStyle::InputTextCursorSize },
        { ImGUIThemeFloatVar::SeparatorSize, &ImGuiStyle::SeparatorSize },
        { ImGUIThemeFloatVar::SeparatorTextBorderSize, &ImGuiStyle::SeparatorTextBorderSize },
        { ImGUIThemeFloatVar::DockingSeparatorSize, &ImGuiStyle::DockingSeparatorSize },
        { ImGUIThemeFloatVar::MouseCursorScale, &ImGuiStyle::MouseCursorScale },
        { ImGUIThemeFloatVar::CurveTessellationTol, &ImGuiStyle::CurveTessellationTol },
        { ImGUIThemeFloatVar::CircleTessellationMaxError, &ImGuiStyle::CircleTessellationMaxError },
        { ImGUIThemeFloatVar::HoverStationaryDelay, &ImGuiStyle::HoverStationaryDelay },
        { ImGUIThemeFloatVar::HoverDelayShort, &ImGuiStyle::HoverDelayShort },
        { ImGUIThemeFloatVar::HoverDelayNormal, &ImGuiStyle::HoverDelayNormal },
    };

    void ImGUITheme::Apply() {
        for (const auto& [var, member] : STYLE_VEC2_VALUES) {
            ImGui::GetStyle().*member = FVector2ToImVec2(m_vec2Settings[var]);
        }
        for (const auto& [var, member] : STYLE_BOOL_VALUES) {
            ImGui::GetStyle().*member = m_boolSettings[var];
        }
        for (const auto& [var, member] : STYLE_FLOAT_VALUES) {
            ImGui::GetStyle().*member = m_floatSettings[var];
        }
        for (const auto& [var, color] : m_colorSettings) {
            ImGui::GetStyle().Colors[static_cast<int>(var)] = ColorToImVec4(color);
        }
    }

    void ImGUITheme::StoreCurrentTheme() {
        for (const auto& [var, member] : STYLE_VEC2_VALUES) {
            m_vec2Settings[var] = ImVec2ToFVector2(ImGui::GetStyle().*member);
        }
        for (const auto& [var, member] : STYLE_BOOL_VALUES) {
            m_boolSettings[var] = ImGui::GetStyle().*member;
        }
        for (const auto& [var, member] : STYLE_FLOAT_VALUES) {
            m_floatSettings[var] = ImGui::GetStyle().*member;
        }
        for (const auto& enumerator : SR_UTILS_NS::EnumReflector::GetValues<StyleColor>()) {
            const auto var = static_cast<StyleColor>(enumerator.value);
            m_colorSettings[var] = ImVec4ToColor(ImGui::GetStyle().Colors[enumerator.value]);
        }
    }

    void ImGUITheme::ImportHardcodedTheme() {
        // Future Dark style by rewrking from ImThemes
        ImGuiStyle& style = ImGui::GetStyle();

        style.Alpha = 1.0f;
        style.DisabledAlpha = 1.0f;
        style.WindowPadding = ImVec2(12.0f, 12.0f);
        style.WindowRounding = 0.0f;
        style.WindowBorderSize = 0.0f;
        style.WindowMinSize = ImVec2(20.0f, 20.0f);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_None;
        style.ChildRounding = 0.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupRounding = 0.0f;
        style.PopupBorderSize = 1.0f;
        style.FramePadding = ImVec2(6.0f, 6.0f);
        style.FrameRounding = 0.0f;
        style.FrameBorderSize = 0.0f;
        style.ItemSpacing = ImVec2(12.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 3.0f);
        style.CellPadding = ImVec2(12.0f, 6.0f);
        style.IndentSpacing = 20.0f;
        style.ColumnsMinSpacing = 6.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabMinSize = 12.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.TabBorderSize = 0.0f;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.27450982f, 0.31764707f, 0.4509804f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.23529412f, 0.21568628f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549f, 0.5529412f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.23529412f, 0.21568628f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.23529412f, 0.21568628f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.23529412f, 0.21568628f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.52156866f, 0.6f, 0.7019608f, 1.0f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.039215688f, 0.98039216f, 0.98039216f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.2901961f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.99607843f, 0.4745098f, 0.69803923f, 1.0f);
        style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
        style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
        style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.23529412f, 0.21568628f, 0.59607846f, 1.0f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f);
    }
}
