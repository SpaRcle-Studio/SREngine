

# File SceneLogic.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneLogic.h**](SceneLogic_8h.md)

[Go to the documentation of this file](SceneLogic_8h.md)


```C++
//
// Created by Monika on 22.12.2022.
//

#ifndef SR_ENGINE_SCENE_LOGIC_H
#define SR_ENGINE_SCENE_LOGIC_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/World/SceneLogicType.h>

namespace SR_UTILS_NS {
    class SceneObject;
}

namespace SR_WORLD_NS {
    class Scene;

    class SceneLogic : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<SceneLogic> {
        SR_CLASS()
        using Super = SR_HTYPES_NS::SharedPtr<SceneLogic>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<SceneLogic>;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<Scene>;
        using SceneObjectPtr = SR_HTYPES_NS::SharedPtr<SceneObject>;
        using SceneObjects = std::vector<SceneObjectPtr>;
        using OriginType = SceneLogic;

    public:
        SceneLogic();

    public:
        SR_NODISCARD virtual bool IsAllowedRootSave() const noexcept { return true; }
        SR_NODISCARD virtual SceneLogicType GetType() const noexcept = 0;
        SR_NODISCARD virtual StringAtom GetSceneExtension() const noexcept = 0;
        SR_NODISCARD const ScenePtr& GetScene() const noexcept { return m_scene; }
        SR_NODISCARD virtual SR_UTILS_NS::Path GetSceneDataPath(const SR_UTILS_NS::Path& path) const { return path; }

        virtual void SetScene(const ScenePtr& pScene);

        virtual void Update(float_t dt) { }
        virtual void Destroy() { }
        virtual void Prepare() { }

        virtual void InitLogic() { SRAssert(m_scene); }
        virtual bool SaveLogic(ISerializer& serializer, const Path& path) { return true; }
        virtual bool LoadLogic(IDeserializer& deserializer, const Path& path) { return true; }

        virtual bool Reload() { return true; }

    protected:
        ScenePtr m_scene;
        mutable std::recursive_mutex m_mutex;

    };
}

#endif //SR_ENGINE_SCENE_LOGIC_H
```


