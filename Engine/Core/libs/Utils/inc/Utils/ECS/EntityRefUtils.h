//
// Created by Monika on 30.11.2022.
//

#ifndef SR_ENGINE_UTILS_ENTITY_REF_UTILS_H
#define SR_ENGINE_UTILS_ENTITY_REF_UTILS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class Entity;
}

namespace SR_UTILS_NS::EntityRefUtils {
    struct OwnerRef {
        OwnerRef() = default;
        SR_MAYBE_UNUSED OwnerRef(const SR_HTYPES_NS::SharedPtr<Entity>& ptr); /// NOLINT
        SR_MAYBE_UNUSED OwnerRef(const SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>& ptr); /// NOLINT

        OwnerRef(OwnerRef&& other) noexcept
            : pEntity(SR_UTILS_NS::Exchange(other.pEntity, { }))
            , pScene(SR_UTILS_NS::Exchange(other.pScene, { }))
        { }

        OwnerRef(const OwnerRef& other) noexcept /** NOLINT */
            : pEntity(other.pEntity)
            , pScene(other.pScene)
        { }

        OwnerRef& operator=(OwnerRef&& other) noexcept {
            pEntity = (SR_UTILS_NS::Exchange(other.pEntity, { }));
            pScene = (SR_UTILS_NS::Exchange(other.pScene, { }));
            return *this;
        }

        OwnerRef& operator=(const OwnerRef& other) noexcept {
            pEntity = other.pEntity;
            pScene = other.pScene;
            return *this;
        }

        SR_HTYPES_NS::SharedPtr<Entity> pEntity;
        SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> pScene;

    };

    SR_ENUM_NS_CLASS_T(Action, uint8_t,
        Action_Parent, Action_Child, Action_Component
    );

    struct PathItem {
        StringAtom name;
        uint16_t index;
        Action action;

        bool operator==(const PathItem& other) const noexcept {
            return
                name == other.name &&
                index == other.index &&
                action == other.action;
        }
    };

    typedef std::vector<PathItem> RefPath;

    SR_MAYBE_UNUSED SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> GetSceneFromOwner(const OwnerRef& owner);

    SR_MAYBE_UNUSED SR_HTYPES_NS::SharedPtr<Entity> GetEntity(const OwnerRef& owner, const RefPath& path);

    SR_MAYBE_UNUSED RefPath CalculatePath(const OwnerRef& from);
    SR_MAYBE_UNUSED RefPath CalculateRelativePath(const OwnerRef& from, const OwnerRef& target);

    SR_MAYBE_UNUSED bool IsOwnerValid(const OwnerRef& owner);
    SR_MAYBE_UNUSED bool IsTargetInitialized(const OwnerRef& owner);
}

#endif //SR_ENGINE_UTILS_ENTITY_REF_UTILS_H
