//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_EDITORSETTINGS_H
#define SR_ENGINE_EDITORSETTINGS_H

#include <Utils/Settings.h>

namespace SR_CORE_NS {
    ///Здесь хранятся названия иконок, движок получает иконку по пути, указанному для названия в файле SREngine/Resources/Editor/Configs/EditorSettings.xml
    SR_ENUM_NS_CLASS_T(EditorIcon, uint32_t,
          Unknown,
          Material,
          File,
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

    class EditorSettings : public SR_UTILS_NS::GlobalSettings<EditorSettings> {
        SR_REGISTER_SINGLETON(EditorSettings)
        friend class SR_UTILS_NS::GlobalSettings<EditorSettings>;
        using Icons = std::map<EditorIcon, SR_UTILS_NS::Path>;
        using Super = SR_UTILS_NS::GlobalSettings<EditorSettings>;
    protected:
        ~EditorSettings() override = default;

    public:
        SR_NODISCARD Icons GetIcons() const;
        SR_NODISCARD SR_UTILS_NS::Path GetRenderTechnique() const;
        SR_NODISCARD SR_UTILS_NS::Path GetPrefabEditorRenderTechnique() const;
        SR_NODISCARD bool IsNeedDebugChunks() const noexcept { return m_debugChunks; }

        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

    protected:
        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

    private:
        Icons m_icons;

        SR_UTILS_NS::Path m_renderTechnique;
        SR_UTILS_NS::Path m_prefabEditorRenderTechnique;

        bool m_debugChunks = false;

    };
}

#endif //SR_ENGINE_EDITORSETTINGS_H
