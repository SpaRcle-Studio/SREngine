//
// Created by Monika on 26.11.2022.
//

#ifndef SRENGINE_ENTITYREF_H
#define SRENGINE_ENTITYREF_H

#include <Utils/ECS/EntityRefUtils.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Component;

    class EntityRef final {
    public:
        explicit EntityRef(const EntityRefUtils::OwnerRef& owner);

        EntityRef(const EntityRef& other) noexcept;
        EntityRef(EntityRef&& other) noexcept;

        EntityRef& operator=(const EntityRef& other);

    public:
        SR_NODISCARD GameObject::Ptr GetGameObject() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD bool IsRelative() const { return m_relative; }

        void SetRelative(bool relative);
        void SetPathTo(Entity::Ptr pEntity);
        void SetOwner(const EntityRefUtils::OwnerRef& owner);

    private:
        void UpdateTarget() const;
        void UpdatePath();

    private:
        SR_UTILS_NS::EntityRefUtils::RefPath m_path;

        bool m_relative = false;

        EntityRefUtils::OwnerRef m_owner;
        mutable Entity::Ptr m_target;

    };
}

#endif //SRENGINE_ENTITYREF_H
