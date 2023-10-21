//
// Created by Monika on 02.03.2022.
//

#include <Graphics/GUI/Editor/Theme.h>

#include <Utils/Xml.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_GRAPH_NS::GUI {
    Theme *Theme::Load(const SR_UTILS_NS::Path &path) {
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

    bool Theme::Save(const std::string &path, const ImGuiStyle& style) {
        const ImVec4 * colors = style.Colors;

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

    bool Theme::Save(const SR_UTILS_NS::Path &path) {
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

    SR_MATH_NS::FColor Theme::ImVec4ToColor(ImVec4 imVec4) {
        return SR_MATH_NS::FColor(imVec4.x, imVec4.y, imVec4.z, imVec4.w);
    }

    SR_MATH_NS::FVector2 Theme::ImVec2ToFVector2(ImVec2 imVec2) {
        return SR_MATH_NS::FVector2(imVec2.x, imVec2.y);
    }

    void Theme::SetSize(const std::string &id, const SR_MATH_NS::FVector2 &size) {
        m_sizes[id] = size;
    }

    void Theme::SetFloat(const std::string &id, float_t value) {
        m_floats[id] = value;
    }

    void Theme::SetBool(const std::string &id, bool value)  {
        m_booleans[id] = value;
    }

    bool Theme::Apply(ImGuiStyle& style) const {
        ImVec4 * colors = style.Colors;

        for (const auto& [name, value] : m_colors) {
            if (STYLE_COLORS.count(name) == 0) {
                SRAssert2(false, "Unknown id: " + name);
            }
            else
                colors[STYLE_COLORS.at(name)] = ImVec4(value.r, value.g, value.b, value.a);
        }

        for (const auto& [name, value] : m_sizes) {
            if (STYLE_SIZE_VALUES.count(name) == 0) {
                SRAssert2(false, "Unknown id: " + name);
            }
            else
                style.*(STYLE_SIZE_VALUES.at(name)) = ImVec2(value.x, value.y);
        }

        for (const auto& [name, value] : m_floats) {
            if (STYLE_FLOAT_VALUES.count(name) == 0) {
                SRAssert2(false, "Unknown id: " + name);
            }
            else
                style.*(STYLE_FLOAT_VALUES.at(name)) = value;
        }

        for (const auto& [name, value] : m_booleans) {
            if (STYLE_BOOL_VALUES.count(name) == 0) {
                SRAssert2(false, "Unknown id: " + name);
            }
            else
                style.*(STYLE_BOOL_VALUES.at(name)) = value;
        }

        return true;
    }
}