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

    EntityRef &EntityRef::operator=(EntityRef&& other) {
        m_path = SR_UTILS_NS::Exchange(other.m_path, { });
        m_relative = SR_UTILS_NS::Exchange(other.m_relative, { });
        m_owner = SR_UTILS_NS::Exchange(other.m_owner, { });
        m_target = SR_UTILS_NS::Exchange(other.m_target, { });
        return *this;
    }

    GameObject::Ptr EntityRef::GetGameObject() const {
        if (!m_target) {
            UpdateTarget();
        }

        return m_target.DynamicCast<GameObject>();
    }

    Component::Ptr EntityRef::GetComponent() const {
        if (!m_target) {
            UpdateTarget();
        }

        return m_target.DynamicCast<Component>();
    }

    void EntityRef::UpdatePath() const {
        if (!EntityRefUtils::IsOwnerValid(m_owner)) {
            SRHalt("Invalid owner!");
            return;
        }

        if (!m_target) {
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
        SRAssert(EntityRefUtils::IsOwnerValid(m_owner));

        if (IsRelative()) {
            m_target = EntityRefUtils::GetEntity(m_owner, m_path);
        }
        else {
            auto&& pScene = EntityRefUtils::GetSceneFromOwner(m_owner);
            m_target = EntityRefUtils::GetEntity(pScene, m_path);
        }
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

    SR_HTYPES_NS::Marshal::Ptr EntityRef::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal) const {
        if (!pMarshal) {
            pMarshal = new SR_HTYPES_NS::Marshal();
        }

        Save(*pMarshal);

        return pMarshal;
    }

    void EntityRef::Load(SR_HTYPES_NS::Marshal& marshal) {
        m_relative = marshal.Read<bool>();
        m_path = marshal.Read<EntityRefUtils::RefPath>();
    }

    void EntityRef::Save(SR_HTYPES_NS::Marshal& marshal) const {
        marshal.Write<bool>(IsRelative());
        marshal.Write<EntityRefUtils::RefPath>(m_path);
    }

    EntityRef EntityRef::Copy(const EntityRefUtils::OwnerRef& owner) const {
        EntityRef ref(owner);
        ref.m_relative = m_relative;
        ref.m_path = m_path;
        return ref;
    }
}