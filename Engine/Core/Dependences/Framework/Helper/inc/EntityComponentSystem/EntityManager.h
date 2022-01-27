//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENTITYMANAGER_H
#define SRENGINE_ENTITYMANAGER_H

#include <EntityComponentSystem/ISavable.h>
#include <Utils/Singleton.h>
#include <Utils/Numeric.h>
#include <Debug.h>

#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <vector>
#include <functional>
#include <utility>
#include <list>

namespace Framework::Helper {
    class GameObject;
    class Component;
    class Entity;

    typedef uint64_t EntityId;
    typedef std::function<Entity*(void)> EntityAllocator;

    class EntityPath {
    public:
        explicit EntityPath(std::list<EntityId> path)
            : m_path(std::move(path))
        { }

        EntityPath()
            : EntityPath(std::list<EntityId>())
        { }

        ~EntityPath() {
            m_path.clear();
        }

        explicit EntityPath(const EntityId& id)
            : EntityPath()
        {
            Concat(id);
        }

        EntityPath(const EntityPath& copy)
            : EntityPath(copy.m_path)
        { }

    public:
        //operator std::string() const { return m_path; }

    public:
        [[nodiscard]] std::list<EntityId> ToEntityIds() const { return m_path; }

        [[nodiscard]] EntityId Last() const;
        [[nodiscard]] EntityPath Concat(const EntityId& id) const;
        [[nodiscard]] EntityPath ConcatBack(const EntityId& id) const;

        EntityPath& Concat(const EntityId& id);
        EntityPath& ConcatBack(const EntityId& id);

        //[[nodiscard]] const char* CStr() const { return m_path.c_str(); }

    private:
        std::list<EntityId> m_path;

    };

    static const EntityId ENTITY_ID_MAX = UINT64_MAX;

    class Entity : public ISavable {
    public:
        ~Entity() override;
        Entity();

    public:
        [[nodiscard]] EntityId GetEntityId() const { return m_entityId; }
        [[nodiscard]] EntityPath GetEntityPath() const { return m_entityPath; }

    protected:
        void SetEntityPath(const EntityPath& path);

    private:
        EntityId m_entityId;
        EntityPath m_entityPath;

    };

    class EntityManager : public Singleton<EntityManager> {
        friend class Singleton<EntityManager>;
    private:
        typedef std::recursive_mutex Mutex;

    public:
        EntityManager();
        ~EntityManager() override = default;

    public:
        EntityId Register(Entity* entity);
        void Unregister(const EntityId& id);
        bool Reserve(const EntityId& id);
        Entity* GetReserved(const EntityId& id, const EntityAllocator& allocator);
        Entity* FindById(const EntityId& id) const;

    private:
        void OnSingletonDestroy() override;

    private:
        std::unordered_map<EntityId, Entity*> m_entities;
        std::unordered_set<EntityId> m_reserved;
        EntityId m_nextId;
        mutable Mutex m_mutex;

    };
}

#endif //SRENGINE_ENTITYMANAGER_H
