

# File EditorSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Settings**](dir_e2003efd86638652fa75d292679631aa.md) **>** [**EditorSettings.h**](EditorSettings_8h.md)

[Go to the documentation of this file](EditorSettings_8h.md)


```C++
//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_EDITORSETTINGS_H
#define SR_ENGINE_EDITORSETTINGS_H

#include <Engine/macros.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(EditorIcon, uint32_t,
          Unknown,
          Material, Prefab, Asset,
          File, Shader, Scene,
          Back, RenderTechnique,
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

        
        SR_UTILS_NS::Path path;
        std::string extensions;
    };

    class EditorSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EditorSettings>;

    public:
        SR_NODISCARD const std::map<EditorIcon, EditorSettingsIconInfo>& GetIcons() const noexcept { return m_icons; }
        SR_NODISCARD bool IsNeedDebugChunks() const noexcept { return m_debugChunks; }

    private:
        std::map<EditorIcon, EditorSettingsIconInfo> m_icons;

        bool m_debugChunks = false;

    };
}

#endif //SR_ENGINE_EDITORSETTINGS_H
```


