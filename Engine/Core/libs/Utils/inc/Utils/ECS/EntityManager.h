//
// Created by Monika on 08.01.2022.
//

#ifndef SRENGINE_ENTITYMANAGER_H
#define SRENGINE_ENTITYMANAGER_H

#include <Utils/ECS/ISavable.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Numeric.h>

#define SR_ENTITY_SET_VERSION(version)                     \
    public:                                                \
        SR_INLINE static const uint16_t VERSION = version; \

namespace SR_UTILS_NS {
    class GameObject;
    class Component;
    class Entity;

    typedef uint64_t EntityId;
    typedef std::function<Entity*(void)> EntityAllocator;

    static const EntityId ENTITY_ID_MAX = UINT64_MAX;

    class SR_DLL_EXPORT EntityBranch {
    public:
        EntityBranch(EntityId entityId, std::list<EntityBranch> branches);

        EntityBranch()
            : EntityBranch(ENTITY_ID_MAX, {})
        { }

    public:
        void Reserve() const;
        void UnReserve() const;
        void Clear();

    private:
        std::list<EntityBranch> m_branches;
        EntityId m_id;

    };

    class SR_DLL_EXPORT EntityPath {
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
        void Reserve() const;
        void UnReserve() const;
        void Clear();

        SR_NODISCARD std::list<EntityId> ToEntityIds() const { return m_path; }

        SR_NODISCARD EntityId Last() const;
        SR_NODISCARD EntityPath Concat(const EntityId& id) const;
        SR_NODISCARD EntityPath ConcatBack(const EntityId& id) const;

        EntityPath& Concat(const EntityId& id);
        EntityPath& ConcatBack(const EntityId& id);

    private:
        std::list<EntityId> m_path;

    };

    class SR_DLL_EXPORT Entity : public ISavable, public NonCopyable {
    public:
        ~Entity() override;
        Entity();

    public:
        SR_NODISCARD EntityId GetEntityId() const { return m_entityId; }
        SR_NODISCARD EntityPath GetEntityPath() const { return m_entityPath; }

        SR_NODISCARD EntityBranch GetEntityTree() const { return EntityBranch(m_entityId, GetEntityBranches()); }

        SR_NODISCARD virtual std::string GetEntityInfo() const { return "None"; }

    protected:
        void SetEntityPath(const EntityPath& path);

        SR_NODISCARD virtual std::list<EntityBranch> GetEntityBranches() const { return {}; }

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const override {
            pMarshal = ISavable::Save(pMarshal, flags);

            if (!(flags & SAVABLE_FLAG_ECS_NO_ID)) {
                pMarshal->Write(static_cast<uint64_t>(GetEntityId()));
            }
            else
                pMarshal->Write(static_cast<uint64_t>(ENTITY_ID_MAX));

            return pMarshal;
        }

    private:
        EntityId m_entityId;
        EntityPath m_entityPath;

    };

    class SR_DLL_EXPORT EntityManager : public Singleton<EntityManager> {
        friend class Singleton<EntityManager>;
    public:
        EntityManager();
        ~EntityManager() override = default;

    public:
        EntityId Register(Entity* entity);
        void Unregister(const EntityId& id);
        bool Reserve(const EntityId& id);
        bool UnReserve(const EntityId& id);
        bool TryUnReserve(const EntityId& id);
        Entity* GetReserved(const EntityId& id, const EntityAllocator& allocator);
        Entity* FindById(const EntityId& id) const;

    private:
        void OnSingletonDestroy() override;

    private:
        std::unordered_map<EntityId, Entity*> m_entities;
        std::unordered_set<EntityId> m_reserved;
        EntityId m_nextId;

    };
}

#endif //SRENGINE_ENTITYMANAGER_H
