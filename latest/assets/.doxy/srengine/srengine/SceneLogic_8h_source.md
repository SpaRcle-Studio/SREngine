

# File SceneLogic.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**SceneLogic.h**](SceneLogic_8h.md)

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


