//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_EDITORSETTINGS_H
#define SR_ENGINE_EDITORSETTINGS_H

#include <Engine/macros.h>

#include <ImmediateGUI/GUI/ImGUITheme.h>

#include <Utils/Resources/Asset.h>
#include <Utils/Resources/ResourceRef.h>

namespace SR_CORE_NS {
    ///Здесь хранятся названия иконок, движок получает иконку по пути, указанному для названия в файле SREngine/Resources/Editor/Configs/EditorSettings.xml
    SR_ENUM_NS_CLASS_T(EditorIcon, uint32_t,
          Unknown,
          Material, Prefab, Asset,
          File, Shader, Scene,
          Back, RenderTechnique, Theme,
          Play, Animation, Animator,
          Stop,
          PauseActive,
          Pause,
          FrameSkip,
          EmptyFolder,
          Folder,
          Script,
          Reset,
          Shapes,
          Game,
          ZIP,
          JPG,
          TXT,
          XML,
          PNG,
          DLL,
          Font,
          Audio
    );

    struct EditorSettingsIconInfo : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        /// @customArgs(pick: enabled, filter name: Image, relative: resources)
        /// @customArg(filter value: png,jpg,jpeg)
        SR_UTILS_NS::Path path;
        /// @property
        SR_UTILS_NS::String extensions;
    };

    class EditorSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EditorSettings>;
        using Theme = SR_UTILS_NS::ResourceRef<SR_GRAPH_GUI_NS::Immediate::ImGUITheme>;

    public:
        SR_NODISCARD const std::map<EditorIcon, EditorSettingsIconInfo>& GetIcons() const noexcept { return m_icons; }
        SR_NODISCARD bool IsNeedDebugChunks() const noexcept { return m_debugChunks; }
        SR_NODISCARD const Theme& GetTheme() const noexcept { return m_theme; }

        void OnThemeChanged();

    private:
        /// @property @onChanged(OnThemeChanged)
        Theme m_theme;
        /// @property
        std::map<EditorIcon, EditorSettingsIconInfo> m_icons;

        /// @property
        bool m_debugChunks = false;

    };
}

#endif //SR_ENGINE_EDITORSETTINGS_H
