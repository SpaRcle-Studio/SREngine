//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENTITYMANAGER_H
#define SRENGINE_ENTITYMANAGER_H

#include <Utils/ECS/Entity.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    typedef std::function<Entity::Ptr(void)> EntityAllocator;

    class SR_DLL_EXPORT EntityManager : public Singleton<EntityManager> {
        SR_REGISTER_SINGLETON(EntityManager)
    public:
        EntityManager();
        ~EntityManager() override = default;

    public:
        EntityId Register(const Entity::Ptr& entity);
        void Unregister(const EntityId& id);
        bool Reserve(const EntityId& id);
        bool UnReserve(const EntityId& id);
        bool TryUnReserve(const EntityId& id);
        Entity::Ptr GetReserved(const EntityId& id, const EntityAllocator& allocator);
        Entity::Ptr FindById(const EntityId& id) const;

    private:
        void OnSingletonDestroy() override;

    private:
        std::unordered_map<EntityId, Entity::Ptr> m_entities;
        std::unordered_set<EntityId> m_reserved;
        EntityId m_nextId;

    };
}

#endif //SRENGINE_ENTITYMANAGER_H
