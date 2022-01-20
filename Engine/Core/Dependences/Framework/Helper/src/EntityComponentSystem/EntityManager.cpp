//
// Created by Monika on 08.01.2022.
//

#include <EntityComponentSystem/EntityManager.h>
#include <Utils/StringUtils.h>
#include <Utils/VectorUtils.h>

using namespace Framework::Helper;

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

Entity::Entity() {
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
    std::lock_guard<Mutex> lock(m_mutex);

    if (m_entities.count(id) || m_reserved.count(id)) {
        Helper::Debug::Error("EntityManager::Reserve() : entity already registered or reserved! Id: " + std::to_string(id));
        SRAssert(false);
        return false;
    }

    m_reserved.insert(id);

    return true;
}

Entity* EntityManager::GetReserved(const EntityId& id, const EntityAllocator& allocator) {
    std::lock_guard<Mutex> lock(m_mutex);

    if (m_entities.count(id)) {
        Helper::Debug::Error("EntityManager::Register() : entity already is registered! Something went wrong... \n\tId: " + std::to_string(id));
        SRAssert(false);
        return nullptr;
    }

    if (m_reserved.count(id)) {
        m_nextId = id;
        Entity* entity = allocator();
        Register(entity);
        return entity;
    }

    Helper::Debug::Error("EntityManager::Register() : entity id isn't reserved! \n\tId: " + std::to_string(id));
    SRAssert(false);

    return nullptr;
}


EntityId EntityManager::Register(Entity* entity) {
    std::lock_guard<Mutex> lock(m_mutex);

    EntityId id = m_nextId;

    if (id != ENTITY_ID_MAX) {
        m_reserved.erase(m_nextId);
        m_nextId = ENTITY_ID_MAX;
        goto complete;
    }

retry:
    id = static_cast<EntityId>(Random::Instance().Int64());

    if (m_entities.count(id) || m_reserved.count(id) || id == ENTITY_ID_MAX) {
        Helper::Debug::Warn("EntityManager::Register() : collision detected! Id: " + std::to_string(id));
        goto retry;
    }

complete:
    m_entities.insert(std::make_pair(id, entity));

    return id;
}

void EntityManager::Unregister(const EntityId &id) {
    std::lock_guard<Mutex> lock(m_mutex);
    m_entities.erase(id);
}

void EntityManager::OnSingletonDestroy() {
    std::lock_guard<Mutex> lock(m_mutex);

    if (!m_entities.empty()) {
        std::string ids;
        uint32_t index = 0;
        for (const auto& [id, entity] : m_entities) {
            ids.append("\n\tId[").append(std::to_string(index++)).append("] = ").append(std::to_string(id));
        }

        Helper::Debug::Warn("EntityManager::OnSingletonDestroy() : " + std::to_string(m_entities.size()) + " entities was not be destroyed! Ids: " + ids);
    }

    Singleton::OnSingletonDestroy();
}

Entity *EntityManager::FindById(const EntityId &id) const {
    std::lock_guard<Mutex> lock(m_mutex);

    if (!m_entities.count(id))
        return nullptr;

    return m_entities.at(id);
}


