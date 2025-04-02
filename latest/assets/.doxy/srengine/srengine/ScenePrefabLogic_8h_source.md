

# File ScenePrefabLogic.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**ScenePrefabLogic.h**](ScenePrefabLogic_8h.md)

[Go to the documentation of this file](ScenePrefabLogic_8h.md)


```C++
//
// Created by Monika on 24.12.2022.
//

#ifndef SR_ENGINE_SCENE_PREFAB_LOGIC_H
#define SR_ENGINE_SCENE_PREFAB_LOGIC_H

#include <Utils/World/SceneLogic.h>

namespace SR_WORLD_NS {
    class ScenePrefabLogic : public SceneLogic {
        SR_CLASS()
        using Super = SceneLogic;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ScenePrefabLogic>;

    public:
        void InitLogic() override;
        bool SaveLogic(ISerializer& serializer, const Path& path) override;
        bool LoadLogic(IDeserializer& deserializer, const Path& path) override;

        SR_NODISCARD SceneLogicType GetType() const noexcept override { return SceneLogicType::Prefab; }
        SR_NODISCARD StringAtom GetSceneExtension() const noexcept override { return "prefab"; }
        SR_NODISCARD bool IsAllowedRootSave() const noexcept override { return false; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<SceneObject> GetPrefabRoot() const noexcept;

    };
}

#endif //SR_ENGINE_SCENE_PREFAB_LOGIC_H
```


