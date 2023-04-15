//
// Created by Monika on 26.11.2022.
//

#ifndef SRENGINE_ENTITYREF_H
#define SRENGINE_ENTITYREF_H

#include <Utils/ECS/EntityRefUtils.h>
#include <Utils/Types/Marshal.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Component;

    class EntityRef final : public SR_UTILS_NS::NonCopyable {
    public:
        EntityRef() = default;
        explicit EntityRef(const EntityRefUtils::OwnerRef& owner);

        EntityRef(EntityRef&& other) noexcept;

        EntityRef& operator=(EntityRef&& other);

    public:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal) const;
        SR_NODISCARD EntityRef Copy(const EntityRefUtils::OwnerRef& owner) const;

        void Save(SR_HTYPES_NS::Marshal& marshal) const;
        void Load(SR_HTYPES_NS::Marshal& marshal);

        SR_NODISCARD GameObject::Ptr GetGameObject() const;
        SR_NODISCARD Component::Ptr GetComponent() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD bool IsRelative() const { return m_relative; }

        void SetRelative(bool relative);
        void SetPathTo(Entity::Ptr pEntity);
        void SetOwner(const EntityRefUtils::OwnerRef& owner);

    private:
        void UpdateTarget() const;
        void UpdatePath() const;

    private:
        mutable SR_UTILS_NS::EntityRefUtils::RefPath m_path;

        bool m_relative = false;

        EntityRefUtils::OwnerRef m_owner;
        mutable Entity::Ptr m_target;

    };
}

#endif //SRENGINE_ENTITYREF_H
