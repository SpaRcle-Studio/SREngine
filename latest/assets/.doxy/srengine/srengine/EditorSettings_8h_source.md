

# File EditorSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Settings**](dir_e2003efd86638652fa75d292679631aa.md) **>** [**EditorSettings.h**](EditorSettings_8h.md)

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
          Material, Prefab, Asset,
          File, Shader,
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


