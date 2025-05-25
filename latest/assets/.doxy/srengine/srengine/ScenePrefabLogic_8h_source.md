

# File ScenePrefabLogic.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**ScenePrefabLogic.h**](ScenePrefabLogic_8h.md)

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

        static bool SaveSOAsPrefab(ISerializer& serializer, const SR_HTYPES_NS::SharedPtr<SceneObject>& pSO);

        void SetCustomSOData(IDeserializer::UniquePtr pCustomData);

    private:
        bool LoadSOData(IDeserializer& deserializer);

    private:
        IDeserializer::UniquePtr m_pSOCustomData;

    };
}

#endif //SR_ENGINE_SCENE_PREFAB_LOGIC_H
```


