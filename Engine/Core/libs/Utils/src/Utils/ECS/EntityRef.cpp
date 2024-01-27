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

    EntityRef &EntityRef::operator=(EntityRef&& other) noexcept {
        m_path = SR_UTILS_NS::Exchange(other.m_path, { });
        m_relative = SR_UTILS_NS::Exchange(other.m_relative, { });
        m_owner = SR_UTILS_NS::Exchange(other.m_owner, { });
        m_target = SR_UTILS_NS::Exchange(other.m_target, { });
        return *this;
    }

    GameObject::Ptr EntityRef::GetGameObject() const {
        if (m_path.empty() && m_target) {
            UpdatePath();
        }

        if (!m_target) {
            UpdateTarget();
        }

        return m_target.DynamicCast<GameObject>();
    }

    Component::Ptr EntityRef::GetComponent() const {
        if (m_path.empty() && m_target) {
            UpdatePath();
        }

        if (!m_target) {
            UpdateTarget();
        }

        return m_target.DynamicCast<Component>();
    }

    void EntityRef::UpdatePath() const {
        if (!EntityRefUtils::IsTargetInitialized(m_target)) {
            return;
        }

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

    EntityRef& EntityRef::SetPathTo(const Entity::Ptr& pEntity) {
        if (!EntityRefUtils::IsOwnerValid(m_owner)) {
            SRHalt("Invalid owner!");
            return *this;
        }

        if (!pEntity) {
            m_target = pEntity;
            m_path.clear();
            return *this;
        }

        if (IsRelative()) {
            m_path = EntityRefUtils::CalculateRelativePath(m_owner, pEntity);
        }
        else {
            m_path = EntityRefUtils::CalculatePath(pEntity);
        }

        UpdateTarget();

        return *this;
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
        m_path.clear();

        const auto length = marshal.Read<uint16_t>();

        for (uint16_t i = 0; i < length; ++i) {
            auto&& item = m_path.emplace_back();
            item.index = marshal.Read<uint16_t>();
            item.action = static_cast<EntityRefUtils::Action>(marshal.Read<uint8_t>());
            item.name = marshal.Read<StringAtom>();
        }
    }

    void EntityRef::Save(SR_HTYPES_NS::Marshal& marshal) const {
        UpdatePath();

        marshal.Write<bool>(IsRelative());
        marshal.Write<uint16_t>(m_path.size());

        for (auto&& path : m_path) {
            marshal.Write<uint16_t>(path.index);
            marshal.Write<uint8_t>(static_cast<uint8_t>(path.action));
            marshal.Write<StringAtom>(path.name);
        }
    }

    EntityRef EntityRef::Copy(const EntityRefUtils::OwnerRef& owner) const {
        EntityRef ref(owner);
        ref.m_relative = m_relative;
        ref.m_path = m_path;
        return ref;
    }

    void EntityRefProperty::SaveProperty(MarshalRef marshal) const noexcept {
        if (auto&& pBlock = AllocatePropertyBlock()) {
            m_entityRef.Save(*pBlock);
            SavePropertyBase(marshal, std::move(pBlock));
        }
    }

    void EntityRefProperty::LoadProperty(MarshalRef marshal) noexcept {
        if (auto&& pBlock = LoadPropertyBase(marshal)) {
            m_entityRef.Load(*pBlock);
        }
    }
}