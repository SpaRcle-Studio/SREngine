//
// Created by Monika on 30.11.2022.
//

#include <Utils/ECS/EntityRef.h>

namespace SR_UTILS_NS {
    EntityRef::EntityRef(bool relative)
        : m_relative(relative)
        , m_fromEntityId(SR_ID_INVALID)
        , m_entityId(SR_ID_INVALID)
    { }

    EntityRef::EntityRef()
        : EntityRef(true)
    { }

    EntityRef::EntityRef(EntityRef&& other) noexcept {
        /// TODO
    }

    EntityRef::EntityRef(const EntityRef &other) noexcept
        : m_path(other.m_path)
        , m_relative(other.m_relative)
        , m_fromEntityId(other.m_fromEntityId)
        , m_entityId(other.m_entityId)
    { }

    EntityRef &EntityRef::operator=(const EntityRef &other) {
        m_path = other.m_path;
        m_relative = other.m_relative;
        m_fromEntityId = other.m_fromEntityId;
        m_entityId = other.m_entityId;
        return *this;
    }

    GameObject *EntityRef::GetGameObject(GameObject* pFrom) const {
        auto&& entityManager = EntityManager::Instance();

        if (m_entityId != SR_ID_INVALID) {
            const EntityId fromId = pFrom ? pFrom->GetEntityId() : SR_ID_INVALID;
            if (m_fromEntityId != fromId) {
                m_entityId = SR_ID_INVALID;
                m_fromEntityId = fromId;
            }
        }

        auto&& pGameObject = dynamic_cast<GameObject*>(entityManager.FindById(m_entityId));

        if (!pGameObject) {
            Update();
            return dynamic_cast<GameObject*>(entityManager.FindById(m_entityId));
        }

        return pGameObject;
    }

    void EntityRef::Update() const {
        GameObject* pObject = nullptr;

        if (m_relative) {
            auto&& entityManager = EntityManager::Instance();
            pObject = dynamic_cast<GameObject*>(entityManager.FindById(m_fromEntityId));
            if (!pObject) {
                return;
            }

            for (auto&& pathItem : m_path) {
                if (!pObject) {
                    return;
                }

                switch (pathItem.action) {
                    case EntityRefUtils::Action::Action_Parent:
                        pObject = pObject->GetParent().Get();
                        break;
                    case EntityRefUtils::Action::Action_Child: {
                        if (pathItem.index == static_cast<uint16_t>(SR_ID_INVALID)) {
                            pObject = pObject->Find(pathItem.hashName).Get();
                        }
                        else {
                            SRHalt0();
                        }

                        break;
                    }
                    case EntityRefUtils::Action::Action_Component:
                        break;
                    case EntityRefUtils::Action::Action_GameObject:
                        break;
                }
            }
        }
    }

    void EntityRef::AddPathItem(EntityRefUtils::Action action, const std::string& name) {
        AddPathItem(action, name, SR_ID_INVALID);
    }

    void EntityRef::AddPathItem(EntityRefUtils::Action action, const std::string &name, uint16_t index) {
        EntityRefUtils::PathItem pathItem;

        pathItem.action = action;
        pathItem.index = index;
        pathItem.hashName = SR_HASH_STR(name);

        m_path.emplace_back(pathItem);
    }

    void EntityRef::AddPathItem(EntityRefUtils::Action action) {
        static const std::string string;
        AddPathItem(action, string, SR_ID_INVALID);
    }

    void EntityRef::SetRelative(bool relative) {
        m_relative = relative;
    }
}