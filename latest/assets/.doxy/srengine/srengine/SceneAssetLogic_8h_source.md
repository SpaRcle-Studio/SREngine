

# File SceneAssetLogic.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneAssetLogic.h**](SceneAssetLogic_8h.md)

[Go to the documentation of this file](SceneAssetLogic_8h.md)


```C++
//
// Created by Monika on 02.03.2025.
//

#ifndef SR_ENGINE_SCENE_ASSET_LOGIC_H
#define SR_ENGINE_SCENE_ASSET_LOGIC_H

#include <Utils/World/SceneLogic.h>

namespace SR_WORLD_NS {
    class SceneAssetLogic final : public SceneLogic {
        SR_CLASS()
        using Super = SceneLogic;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<SceneAssetLogic>;

    public:
        SR_NODISCARD StringAtom GetSceneExtension() const noexcept override { return "scene"; }
        SR_NODISCARD SceneLogicType GetType() const noexcept override { return SceneLogicType::Asset; }

    };
}

#endif //SR_ENGINE_SCENE_ASSET_LOGIC_H
```


