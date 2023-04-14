//
// Created by Monika on 30.11.2022.
//

#include <Utils/ECS/EntityRef.h>

namespace SR_UTILS_NS {
    EntityRef::EntityRef(const EntityRefUtils::OwnerRef& owner)
        : m_owner(owner)
    { }

    EntityRef::EntityRef(EntityRef&& other) noexcept
        : m_path(SR_UTILS_NS::Exchange(other.m_path, { }))
        , m_relative(SR_UTILS_NS::Exchange(other.m_relative, { }))
        , m_owner(SR_UTILS_NS::Exchange(other.m_owner, { }))
        , m_target(SR_UTILS_NS::Exchange(other.m_target, { }))
    { }

    EntityRef::EntityRef(const EntityRef &other) noexcept
        : m_path(other.m_path)
        , m_relative(other.m_relative)
        , m_owner(other.m_owner)
        , m_target(other.m_target)
    { }

    EntityRef &EntityRef::operator=(const EntityRef& other) {
        m_path = other.m_path;
        m_relative = other.m_relative;
        m_owner = other.m_owner;
        m_target = other.m_target;
        return *this;
    }

    GameObject::Ptr EntityRef::GetGameObject() const {
        if (!m_target) {
            UpdateTarget();
        }

        return m_target.DynamicCast<GameObject>();
    }

    void EntityRef::UpdatePath() {
        if (!EntityRefUtils::IsOwnerValid(m_owner)) {
            SRHalt("Invalid owner!");
            return;
        }

        if (IsRelative()) {
            m_path = EntityRefUtils::CalculateRelativePath(m_owner, m_target);
        }
        else {
            m_path = EntityRefUtils::CalculatePath(m_target);
        }
    }

    void EntityRef::UpdateTarget() const {
        m_target = EntityRefUtils::GetEntity(m_owner, m_path);
    }

    void EntityRef::SetRelative(bool relative) {
        m_relative = relative;
        UpdatePath();
    }

    void EntityRef::SetPathTo(Entity::Ptr pEntity) {
        m_target = pEntity;
        UpdatePath();
    }

    bool EntityRef::IsValid() const {
        return m_target && EntityRefUtils::IsOwnerValid(m_owner);
    }

    void EntityRef::SetOwner(const EntityRefUtils::OwnerRef& owner) {
        m_owner = owner;
        UpdatePath();
    }
}