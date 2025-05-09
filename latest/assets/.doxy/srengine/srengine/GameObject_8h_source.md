

# File GameObject.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**GameObject.h**](GameObject_8h.md)

[Go to the documentation of this file](GameObject_8h.md)


```C++
//
// Created by Nikita on 27.11.2020.
//

#ifndef SR_ENGINE_GAME_OBJECT_H
#define SR_ENGINE_GAME_OBJECT_H

#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/TagManager.h>
#include <Utils/ECS/Prefab.h>
#include <Utils/ECS/Transform.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/SafeVariable.h>

namespace SR_UTILS_NS {
    class Transform3D;
    class Transform;
    class Component;

    class SR_COMMON_DLL_API GameObject final : public SceneObject {
        SR_CLASS()
        using Super = SceneObject;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<GameObject>;

    public:
        GameObject() = default;
        ~GameObject() override;

    public:
        SR_NODISCARD SceneObjectType GetSceneObjectType() const noexcept override { return SceneObjectType::GameObject; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Transform> GetTransform() const noexcept;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Transform> GetParentTransform() const noexcept;

        SR_NODISCARD GameObject::Ptr CreateChild(StringAtom name);
        SR_NODISCARD GameObject::Ptr GetOrCreateChild(StringAtom name);

        void OnAttached() override;
        void SetTransform(const SR_HTYPES_NS::SharedPtr<Transform>& pTransform);

    protected:
        void OnHierarchyChanged() override;

    private:
        SR_HTYPES_NS::SharedPtr<Transform> m_transform;

    };
}

#endif //SR_ENGINE_GAME_OBJECT_H
```


