

# File EntityRefUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**EntityRefUtils.h**](EntityRefUtils_8h.md)

[Go to the documentation of this file](EntityRefUtils_8h.md)


```C++
//
// Created by Monika on 30.11.2022.
//

#ifndef SR_ENGINE_UTILS_ENTITY_REF_UTILS_H
#define SR_ENGINE_UTILS_ENTITY_REF_UTILS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class Entity;
}

namespace SR_UTILS_NS::EntityRefUtils {
    struct OwnerRef final {
        OwnerRef() = default;
        SR_MAYBE_UNUSED OwnerRef(const SR_HTYPES_NS::SharedPtr<Entity>& ptr); 
        SR_MAYBE_UNUSED OwnerRef(const SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& ptr); 

        SR_HTYPES_NS::SharedPtr<Entity> pEntity;
        SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> pScene;
    };

    SR_ENUM_NS_CLASS_T(Action, uint8_t,
        Action_Parent, Action_Child, Action_Component
    );

    struct PathItem final : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        PathItem() = default;
        PathItem(const StringAtom name, const uint16_t index, const Action action)
            : name(name), index(index), action(action)
        { }

        StringAtom name;
        uint16_t index = 0;
        Action action = Action::Action_Parent;

        bool operator==(const PathItem& other) const noexcept {
            return
                name == other.name &&
                index == other.index &&
                action == other.action;
        }
    };

    typedef std::vector<PathItem> RefPath;

    SR_MAYBE_UNUSED SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> GetSceneFromOwner(const OwnerRef& owner);

    SR_MAYBE_UNUSED SR_HTYPES_NS::SharedPtr<Entity> GetEntity(const OwnerRef& owner, const RefPath& path);

    SR_MAYBE_UNUSED RefPath CalculatePath(const OwnerRef& from);
    SR_MAYBE_UNUSED RefPath CalculateRelativePath(const OwnerRef& from, const OwnerRef& target);

    SR_MAYBE_UNUSED bool IsOwnerValid(const OwnerRef& owner);
    SR_MAYBE_UNUSED bool IsTargetInitialized(const OwnerRef& owner);
}

#endif //SR_ENGINE_UTILS_ENTITY_REF_UTILS_H
```


