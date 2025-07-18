

# File EntityController.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**EntityController.h**](EntityController_8h.md)

[Go to the documentation of this file](EntityController_8h.md)


```C++
//
// Created by Monika on 08.01.2022.
//

#ifndef SR_ENGINE_ENTITY_CONTROLLER_H
#define SR_ENGINE_ENTITY_CONTROLLER_H

#include <Utils/ECS/Entity.h>

namespace SR_UTILS_NS {
    typedef std::function<Entity::Ptr(void)> EntityAllocator;

    class EntityController final : public SR_HTYPES_NS::SharedPtr<EntityController> {
        using Super = SR_HTYPES_NS::SharedPtr<EntityController>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EntityController>;

    public:
        EntityController();
        ~EntityController() override;

    public:
        EntityId Register(const Entity::Ptr& pEntity, EntityId wantedId = SR_ID_INVALID);

        void Unregister(const EntityId& id);
        bool Reserve(const EntityId& id);
        bool UnReserve(const EntityId& id);
        bool TryUnReserve(const EntityId& id);

        SR_NODISCARD Entity::Ptr GetReserved(const EntityId& id, const EntityAllocator& allocator);
        SR_NODISCARD Entity::Ptr FindById(const EntityId& id) const;

        SR_NODISCARD bool IsIdUsed(const EntityId& id) const;

    private:
        ska::flat_hash_map<EntityId, Entity::Ptr> m_entities;
        ska::flat_hash_set<EntityId> m_reserved;
        EntityId m_nextId = SR_ID_INVALID;

    };

    class EntityIdList : public SR_UTILS_NS::NonCopyable {
    public:
        using Optional = std::optional<EntityIdList>;

        explicit EntityIdList(EntityController::Ptr pController)
            : m_pController(std::move(pController))
        { }

        ~EntityIdList() override {
            if (m_pController && m_isReserved) {
                UnReserveIds();
            }
        }

        EntityIdList(EntityIdList&& other) noexcept
            : m_entityIds(std::move(other.m_entityIds))
            , m_pController(std::move(other.m_pController))
            , m_isReserved(other.m_isReserved)
        { }

        EntityIdList& operator=(EntityIdList&& other) noexcept {
            if (this != &other) {
                m_entityIds = std::move(other.m_entityIds);
                m_pController = std::move(other.m_pController);
                m_isReserved = other.m_isReserved;
            }
            return *this;
        }

    public:
        SR_NODISCARD bool IsReserved() const { return m_isReserved; }

        void Reserve(const uint64_t size) { m_entityIds.reserve(size); }

        void ReserveIds();
        void UnReserveIds();

        void Clear();

        void Add(EntityId id);
        void Add(const EntityIdList& list);
        void Add(const std::vector<EntityId>& list);

    private:
        std::vector<EntityId> m_entityIds;
        EntityController::Ptr m_pController;
        bool m_isReserved = false;

    };
}

#endif //SR_ENGINE_ENTITY_CONTROLLER_H
```


