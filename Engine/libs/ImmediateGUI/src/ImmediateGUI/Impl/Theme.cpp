//
// Created by Monika on 02.03.2022.
//

#include <ImmediateGUI/Impl/Theme.h>
#include <ImmediateGUI/Impl/ImGUI.h>

#include <Utils/Resources/Xml.h>
#include <Utils/Resources/ResourceManager.h>

#ifdef SR_USE_IMGUI
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
            // { "TabMinWidthForCloseButton", &ImGuiStyle::TabMinWidthForCloseButton },
        { "MouseCursorScale", &ImGuiStyle::MouseCursorScale },
        { "CurveTessellationTol", &ImGuiStyle::CurveTessellationTol },
            // { "CircleSegmentMaxError", &ImGuiStyle::CircleSegmentMaxError },
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

    SR_MATH_NS::FColor ImVec4ToColor(ImVec4 imVec4) {
        return SR_MATH_NS::FColor(imVec4.x, imVec4.y, imVec4.z, imVec4.w);
    }

    SR_MATH_NS::FVector2 ImVec2ToFVector2(ImVec2 imVec2) {
        return SR_MATH_NS::FVector2(imVec2.x, imVec2.y);
    }

    Theme*Theme::Load(const SR_UTILS_NS::Path& path) {
        const auto&& absPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);

        if (!absPath.Exists()) {
            return nullptr;
            SR_ERROR("Theme::Load() : file not found! \n\tPath: " + absPath.ToString());
        }

        auto&& theme = new Theme();

        auto&& document = SR_UTILS_NS::Xml::Document::Load(absPath);

        auto&& themes = document.Root().GetNode("Theme");

        for (const auto& xml : themes.GetNode("Colors").GetNodes())
            theme->SetColor(xml.Name(), xml.GetAttribute<SR_MATH_NS::FColor>());

        for (const auto& xml : themes.GetNode("Sizes").GetNodes())
            theme->SetSize(xml.Name(), xml.GetAttribute<SR_MATH_NS::FVector2>());

        for (const auto& xml : themes.GetNode("Floats").GetNodes())
            theme->SetFloat(xml.Name(), xml.GetAttribute("value").ToFloat());

        for (const auto& xml : themes.GetNode("Booleans").GetNodes())
            theme->SetBool(xml.Name(), xml.GetAttribute("value").ToBool());

        return theme;
    }

    bool Theme::SaveGlobal(const SR_UTILS_NS::Path& path) {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGuiStyle& style = ImGui::GetStyle();

        const ImVec4* colors = style.Colors;

        auto&& theme = new Theme();

        for (const auto& [name, id] : STYLE_COLORS)
            theme->SetColor(name, ImVec4ToColor(colors[id]));

        for (const auto& [name, ref] : STYLE_FLOAT_VALUES)
            theme->SetFloat(name, style.*ref);

        for (const auto& [name, ref] : STYLE_BOOL_VALUES)
            theme->SetBool(name, style.*ref);

        for (const auto& [name, ref] : STYLE_SIZE_VALUES)
            theme->SetSize(name, ImVec2ToFVector2(style.*ref));

        const bool result = theme->Save(path);

        delete theme;

        return result;
    }

    bool Theme::Save(const SR_UTILS_NS::Path& path) {
        auto&& document = SR_UTILS_NS::Xml::Document::New();
        auto&& theme = document.Root().AppendChild("Theme");

        auto&& colors = theme.AppendChild("Colors");
        for (const auto& [name, value] : m_colors)
            colors.AppendChild(name).AppendAttribute(value);

        auto&& sizes = theme.AppendChild("Sizes");
        for (const auto& [name, value] : m_sizes)
            sizes.AppendChild(name).AppendAttribute(value);

        auto&& floats = theme.AppendChild("Floats");
        for (const auto& [name, value] : m_floats)
            floats.AppendChild(name).AppendAttribute("value", value);

        auto&& booleans = theme.AppendChild("Booleans");
        for (const auto& [name, value] : m_booleans)
            booleans.AppendChild(name).AppendAttribute("value", value);

        return document.Save(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path));
    }

    void Theme::SetColor(const std::string& id, const SR_MATH_NS::FColor& color) {
        m_colors[id] = color;
    }

    void Theme::SetSize(const std::string& id, const SR_MATH_NS::FVector2& size) {
        m_sizes[id] = size;
    }

    void Theme::SetFloat(const std::string& id, float_t value) {
        m_floats[id] = value;
    }

    void Theme::SetBool(const std::string& id, bool value)  {
        m_booleans[id] = value;
    }

    bool Theme::Apply() const {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4* colors = style.Colors;

        for (const auto& [name, value] : m_colors) {
            if (STYLE_COLORS.count(name) == 0) {
                SR_ERROR("Theme::Apply() : unknown id: {}", name);
            }
            else
                colors[STYLE_COLORS.at(name)] = ImVec4(value.r, value.g, value.b, value.a);
        }

        for (const auto& [name, value] : m_sizes) {
            if (STYLE_SIZE_VALUES.count(name) == 0) {
                SR_ERROR("Theme::Apply() : unknown id: {}", name);
            }
            else
                style.*(STYLE_SIZE_VALUES.at(name)) = ImVec2(value.x, value.y);
        }

        for (const auto& [name, value] : m_floats) {
            if (STYLE_FLOAT_VALUES.count(name) == 0) {
                SR_ERROR("Theme::Apply() : unknown id: {}", name);
            }
            else
                style.*(STYLE_FLOAT_VALUES.at(name)) = value;
        }

        for (const auto& [name, value] : m_booleans) {
            if (STYLE_BOOL_VALUES.count(name) == 0) {
                SR_ERROR("Theme::Apply() : unknown id: {}", name);
            }
            else
                style.*(STYLE_BOOL_VALUES.at(name)) = value;
        }

        return true;
    }
}
#endif
