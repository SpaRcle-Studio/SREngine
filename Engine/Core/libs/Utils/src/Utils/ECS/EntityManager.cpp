//
// Created by Monika on 08.01.2022.
//

#include <Utils/ECS/EntityManager.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/VectorUtils.h>

namespace SR_UTILS_NS {
    EntityManager::EntityManager()
        : m_nextId(ENTITY_ID_MAX)
    { }

    bool EntityManager::Reserve(const EntityId &id) {
        SR_SCOPED_LOCK;

    #ifdef SR_DEBUG
        if (m_reserved.count(id)) {
            SRHalt("EntityManager::Reserve() : entity already reserved! Id: " + std::to_string(id));
            return false;
        }
    #endif

        m_reserved.insert(id);

        return true;
    }

    Entity::Ptr EntityManager::GetReserved(const EntityId& id, const EntityAllocator& allocator) {
        SR_SCOPED_LOCK;

    #ifdef SR_DEBUG
        if (m_entities.count(id)) {
            SRHalt("EntityManager::GetReserved() : entity is registered! Something went wrong... \n\tId: " + std::to_string(id));
            return Entity::Ptr();
        }
    #endif

        if (m_reserved.count(id)) {
            m_nextId = id;
            return allocator();
        }

        SRHalt("Entity id isn't reserved! \n\tId: " + std::to_string(id));

        return Entity::Ptr();
    }

    EntityId EntityManager::Register(const Entity::Ptr& entity) {
        SRAssert(entity);

        if (entity->GetEntityId() != ENTITY_ID_MAX) {
            SRHalt("Double entity register!");
            return entity->GetEntityId();
        }

        SR_SCOPED_LOCK;

        EntityId id = m_nextId;

        if (id != ENTITY_ID_MAX) {
            m_reserved.erase(m_nextId);
            m_nextId = ENTITY_ID_MAX;
            goto complete;
        }

    retry:
        id = static_cast<EntityId>(Random::Instance().Int64());

        if (m_entities.count(id) || m_reserved.count(id) || id == ENTITY_ID_MAX) {
            SR_WARN("EntityManager::Register() : collision detected! Id: " + std::to_string(id));
            goto retry;
        }

    complete:
        m_entities.insert(std::make_pair(id, entity));

        return id;
    }

    void EntityManager::Unregister(const EntityId &id) {
        SR_SCOPED_LOCK;

        if (m_entities.count(id) == 0) {
            SRHalt0();
            return;
        }

        m_entities.erase(id);
    }

    void EntityManager::OnSingletonDestroy() {
        SR_SCOPED_LOCK;

        if (!m_entities.empty()) {
            SR_WARN("EntityManager::OnSingletonDestroy() : entities was not be destroyed! Collect data...");

            std::string ids;
            uint32_t index = 0;

            for (const auto& [id, pEntity] : m_entities) {
                ids.append("\n\tId[").append(std::to_string(index++)).append("] = ").append(std::to_string(id)).append("; Info = ").append(pEntity->GetEntityInfo());
            }

            SR_WARN("EntityManager::OnSingletonDestroy() : Ids and info: " + ids);
        }

        Singleton::OnSingletonDestroy();
    }

    Entity::Ptr EntityManager::FindById(const EntityId &id) const {
        SR_SCOPED_LOCK;

        if (!m_entities.count(id)) {
            return Entity::Ptr();
        }

        return m_entities.at(id);
    }

    bool EntityManager::UnReserve(const EntityId &id) {
        if (TryUnReserve(id)) {
            return true;
        }

        SRHalt("Entity isn't reserved! Id: " + std::to_string(id));

        return false;
    }

    bool EntityManager::TryUnReserve(const EntityId &id) {
        SR_SCOPED_LOCK;

        if (m_reserved.count(id) == 0) {
            return false;
        }

        m_reserved.erase(id);

        return true;
    }
}