

# File EditorSettings.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Settings**](dir_bcd9d448ba2ac473eba0fd9099274e65.md) **>** [**EditorSettings.h**](EditorSettings_8h.md)

[Go to the documentation of this file](EditorSettings_8h.md)


```C++
//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_EDITORSETTINGS_H
#define SR_ENGINE_EDITORSETTINGS_H

#include <Utils/Settings.h>

namespace SR_CORE_NS {
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
```


