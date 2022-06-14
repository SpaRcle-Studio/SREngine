//
// Created by Monika on 08.01.2022.
//

#include <Utils/ECS/EntityManager.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/VectorUtils.h>

namespace SR_UTILS_NS {
    EntityBranch::EntityBranch(EntityId entityId, std::list<EntityBranch> branches)
        : m_branches(std::move(branches))
        , m_id(entityId)
    { }

    void EntityBranch::Reserve() const {
        if (m_id != ENTITY_ID_MAX)
            EntityManager::Instance().Reserve(m_id);

        for (const auto& branch : m_branches)
            branch.Reserve();
    }

    void EntityBranch::UnReserve() const {
        if (m_id != ENTITY_ID_MAX)
            EntityManager::Instance().TryUnReserve(m_id);

        for (const auto& branch : m_branches)
            branch.UnReserve();
    }

    void EntityBranch::Clear() {
        m_id = ENTITY_ID_MAX;
        m_branches.clear();
    }

    ///---------------------------------------------------------------------------------------------------------------------

    EntityPath EntityPath::Concat(const EntityId &id) const {
        auto path = m_path;
        path.emplace_back(id);
        return EntityPath(std::move(path));
    }

    EntityPath EntityPath::ConcatBack(const EntityId &id) const {
        auto path = m_path;
        path.emplace_front(id);
        return EntityPath(std::move(path));
    }

    EntityPath& EntityPath::Concat(const EntityId &id) {
        m_path.emplace_back(id);
        return *this;
    }

    EntityPath& EntityPath::ConcatBack(const EntityId &id) {
        m_path.emplace_front(id);
        return *this;
    }

    EntityId EntityPath::Last() const {
        if (m_path.empty())
            return ENTITY_ID_MAX;
        return m_path.back();
    }

    ///---------------------------------------------------------------------------------------------------------------------

    Entity::Entity()
        : m_entityId(ENTITY_ID_MAX)
    {
        m_entityId = EntityManager::Instance().Register(this);
    }

    Entity::~Entity() {
        EntityManager::Instance().Unregister(m_entityId);
    }

    void Entity::SetEntityPath(const EntityPath &path) {
        m_entityPath = path;
    }

    ///---------------------------------------------------------------------------------------------------------------------

    Framework::Helper::EntityManager::EntityManager()
        : m_nextId(ENTITY_ID_MAX)
    { }

    bool EntityManager::Reserve(const EntityId &id) {
        SR_SCOPED_LOCK

    #ifdef SR_DEBUG
        if (m_reserved.count(id)) {
            SR_ERROR("EntityManager::Reserve() : entity already reserved! Id: " + std::to_string(id));
            SRAssert(false);
            return false;
        }
    #endif

        m_reserved.insert(id);

        return true;
    }

    Entity* EntityManager::GetReserved(const EntityId& id, const EntityAllocator& allocator) {
        SR_SCOPED_LOCK

    #ifdef SR_DEBUG
        if (m_entities.count(id)) {
            SR_ERROR("EntityManager::GetReserved() : entity is registered! Something went wrong... \n\tId: " + std::to_string(id));
            SRAssert(false);
            return nullptr;
        }
    #endif

        if (m_reserved.count(id)) {
            m_nextId = id;
            return allocator();
        }

        SRAssert2(false, "Entity id isn't reserved! \n\tId: " + std::to_string(id));

        return nullptr;
    }


    EntityId EntityManager::Register(Entity* entity) {
        if (entity->GetEntityId() != ENTITY_ID_MAX) {
            SRAssert2(false, "Double entity register!");
            return entity->GetEntityId();
        }

        SR_SCOPED_LOCK

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
        SR_SCOPED_LOCK

        if (m_entities.count(id) == 0) {
            SRAssert(false);
            return;
        }

        m_entities.erase(id);
    }

    void EntityManager::OnSingletonDestroy() {
        SR_SCOPED_LOCK

        if (!m_entities.empty()) {
            std::string ids;
            uint32_t index = 0;
            for (const auto& [id, entity] : m_entities) {
                ids.append("\n\tId[").append(std::to_string(index++)).append("] = ").append(std::to_string(id));
            }

            SR_WARN("EntityManager::OnSingletonDestroy() : " + std::to_string(m_entities.size()) + " entities was not be destroyed! Ids: " + ids);
        }

        Singleton::OnSingletonDestroy();
    }

    Entity *EntityManager::FindById(const EntityId &id) const {
        SR_SCOPED_LOCK

        if (!m_entities.count(id))
            return nullptr;

        return m_entities.at(id);
    }

    bool EntityManager::UnReserve(const EntityId &id) {
        if (TryUnReserve(id))
            return true;

        SRAssert2(false, "Entity isn't reserved! Id: " + std::to_string(id));

        return false;
    }

    bool EntityManager::TryUnReserve(const EntityId &id) {
        SR_SCOPED_LOCK

        if (m_reserved.count(id) == 0)
            return false;

        m_reserved.erase(id);

        return true;
    }
}