//
// Created by Monika on 17.06.2022.
//

#include <Core/Settings/EditorSettings.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::Path EditorSettings::InitializeResourcePath() const {
        return "Editor/Configs/EditorSettings.xml";
    }

    void EditorSettings::ClearSettings() {
        m_icons.clear();
        m_renderTechnique = SR_UTILS_NS::Path();
        m_prefabEditorRenderTechnique = SR_UTILS_NS::Path();
        m_debugChunks = false;
        Settings::ClearSettings();
    }

    bool EditorSettings::LoadSettings(const SR_XML_NS::Node &node) {
        if (auto&& iconsXml = node.GetNode("Icons")) {
            for (auto&& iconNode : iconsXml.GetNodes()) {
                auto icon = SR_UTILS_NS::EnumReflector::FromString<EditorIcon>(iconNode.GetAttribute("First").ToString());
                m_icons[icon] = iconNode.GetAttribute("Second").ToString();
            }
        }

        if (auto&& renderTechniqueXml = node.GetNode("RenderTechnique")) {
            m_renderTechnique = renderTechniqueXml.GetAttribute<SR_UTILS_NS::Path>();
        }

        if (auto&& debugChunksXml = node.GetNode("DebugChunks")) {
            m_debugChunks = debugChunksXml.GetAttribute<bool>();
        }

        return Settings::LoadSettings(node);
    }

    EditorSettings::Icons EditorSettings::GetIcons() const {
        return m_icons;
    }

    SR_UTILS_NS::Path EditorSettings::GetRenderTechnique() const {
        return m_renderTechnique;
    }

    SR_UTILS_NS::Path EditorSettings::GetPrefabEditorRenderTechnique() const {
        return m_prefabEditorRenderTechnique;
    }
}