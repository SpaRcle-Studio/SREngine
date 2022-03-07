//
// Created by Monika on 02.03.2022.
//

#include <GUI/Editor/Theme.h>
#include <Xml.h>
#include <ResourceManager/ResourceManager.h>

Theme *Theme::Load(const std::string &path) {
    auto&& theme = new Theme();

    const auto&& absPath = Helper::ResourceManager::Instance().GetConfigPath().Concat(path);
    if (!absPath.Exists())
        return nullptr;

    auto&& document = Helper::Xml::Document::Load(absPath);

    auto&& themes = document.Root().GetNode("Theme");

    for (const auto& xml : themes.GetNode("Colors").GetNodes())
        theme->SetColor(xml.Name(), xml.GetAttribute<Math::FColor>());

    for (const auto& xml : themes.GetNode("Sizes").GetNodes())
        theme->SetSize(xml.Name(), xml.GetAttribute<Math::FVector2>());

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

bool Theme::Save(const std::string &path) {
    auto&& document = Helper::Xml::Document::New();
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

    return document.Save(Helper::ResourceManager::Instance().GetConfigPath().Concat(path));
}

void Theme::SetColor(const std::string& id, const Math::FColor& color) {
    m_colors[id] = color;
}

Math::FColor Theme::ImVec4ToColor(ImVec4 imVec4) {
    return Framework::Helper::Math::FColor(imVec4.x, imVec4.y, imVec4.z, imVec4.w);
}

Math::FVector2 Theme::ImVec2ToFVector2(ImVec2 imVec2) {
    return Framework::Helper::Math::FVector2(imVec2.x, imVec2.y);
}

void Theme::SetSize(const std::string &id, const Math::FVector2 &size) {
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
