

# File RenderSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Settings**](dir_a48bca76098a55b82b6b979c436fb568.md) **>** [**RenderSettings.h**](RenderSettings_8h.md)

[Go to the documentation of this file](RenderSettings_8h.md)


```C++
//
// Created by Monika on 31.08.2025.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_SETTINGS_H
#define SR_ENGINE_GRAPHICS_RENDER_SETTINGS_H

#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/SRSL/ShaderVariables.h>

#include <Utils/Resources/Asset.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(Quality, uint8_t,
        None,
        Low,
        Medium,
        High,
        Ultra,
        Extreme
    );

    struct RenderSettingsPreset : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        SR_UTILS_NS::StringAtom name;
        std::set<SR_UTILS_NS::StringAtom> shaderDefines;
        SR_UTILS_NS::Path mainCameraRenderTechnique;
        SR_UTILS_NS::Path editorCameraRenderTechnique;

    };

    class RenderSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<RenderSettings>;

    public:
        SR_NODISCARD const RenderSettingsPreset& GetPreset(SR_UTILS_NS::StringAtom name) const;

    public:
        SR_UTILS_NS::StringAtom appName = "SpaRcle Engine";
        SR_UTILS_NS::StringAtom engineName = "SREngine";
        SR_UTILS_NS::Path overlayRenderTechnique = "Editor/Render/Overlay.srtech";
        SR_UTILS_NS::Path editorPrefabSkybox = "Engine/Skyboxes/Gray.png";
        SR_UTILS_NS::Path defaultShader = "Engine/Shaders/standard.srsl";
        SR_UTILS_NS::Path defaultMaterial = "Engine/Materials/default.mat";

        std::vector<RenderSettingsPreset> presets;
        RenderSettingsPreset defaultPreset;

    };
}

#endif //SR_ENGINE_GRAPHICS_RENDER_SETTINGS_H
```


