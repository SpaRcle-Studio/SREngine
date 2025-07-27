//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_EDITORSETTINGS_H
#define SR_ENGINE_EDITORSETTINGS_H

#include <Engine/macros.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_NS {
    ///Здесь хранятся названия иконок, движок получает иконку по пути, указанному для названия в файле SREngine/Resources/Editor/Configs/EditorSettings.xml
    SR_ENUM_NS_CLASS_T(EditorIcon, uint32_t,
          Unknown,
          Material, Prefab, Asset,
          File, Shader, Scene,
          Back,
          Play,
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
        EditorIcon icon = EditorIcon::Unknown;
        /// @property
        /// @customArgs(pick: enabled, filter name: Image)
        /// @customArg(filter value: png,jpg,jpeg)
        SR_UTILS_NS::Path path;
    };

    class EditorSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EditorSettings>;

    public:
        SR_NODISCARD const std::vector<EditorSettingsIconInfo>& GetIcons() const noexcept { return m_icons; }
        SR_NODISCARD SR_UTILS_NS::Path GetRenderTechnique() const;
        SR_NODISCARD SR_UTILS_NS::Path GetPrefabEditorRenderTechnique() const;
        SR_NODISCARD bool IsNeedDebugChunks() const noexcept { return m_debugChunks; }

    private:
        /// @property
        std::vector<EditorSettingsIconInfo> m_icons;

        /// @property
        /// @customArgs(pick: enabled, filter name: Render Techniques)
        /// @customArg(filter value: srtech)
        SR_UTILS_NS::Path m_renderTechnique;
        /// @property
        /// @customArgs(pick: enabled, filter name: Render Techniques)
        /// @customArg(filter value: srtech)
        SR_UTILS_NS::Path m_prefabEditorRenderTechnique;
        /// @property
        bool m_debugChunks = false;

    };
}

#endif //SR_ENGINE_EDITORSETTINGS_H
