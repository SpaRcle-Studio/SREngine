

# File SceneAssetLogic.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**SceneAssetLogic.h**](SceneAssetLogic_8h.md)

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


