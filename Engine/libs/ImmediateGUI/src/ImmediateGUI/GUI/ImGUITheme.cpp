//
// Created by Monika on 11.07.2026.
//

#include <ImmediateGUI/GUI/ImGUITheme.h>
#include <ImmediateGUI/Impl/ImGUI.h>

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
}