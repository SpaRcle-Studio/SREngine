//
// Created by Monika on 12.04.2023.
//

#ifndef SRENGINE_ENTITY_H
#define SRENGINE_ENTITY_H

#include <Utils/ECS/ISavable.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/Common/Numeric.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/Properties.h>

#define SR_ENTITY_SET_VERSION(version)                                                       \
    public:                                                                                  \
        SR_INLINE static const uint16_t VERSION = version;                                   \
        SR_NODISCARD uint16_t GetEntityVersion() const noexcept override { return VERSION; } \

namespace SR_UTILS_NS {
    class Entity;

    typedef uint64_t EntityId;

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

    class SR_DLL_EXPORT Entity : public SR_HTYPES_NS::SharedPtr<Entity>, public ISavable, public NonCopyable {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Entity>;

    public:
        ~Entity() override;
        Entity();

    public:
        SR_NODISCARD const SR_UTILS_NS::PropertyContainer& GetEntityMessages() const { return m_entityMessages; }

        SR_NODISCARD EntityId GetEntityId() const { return m_entityId; }
        SR_NODISCARD EntityPath GetEntityPath() const { return m_entityPath; }

        SR_NODISCARD EntityBranch GetEntityTree() const { return EntityBranch(m_entityId, GetEntityBranches()); }
        SR_NODISCARD EntityRef GetRef() const noexcept { return EntityRef(GetThis()); }
        SR_NODISCARD Entity::Ptr GetEntity() const noexcept { return GetThis(); }

        SR_NODISCARD virtual std::string GetEntityInfo() const { return "None"; }
        SR_NODISCARD virtual uint16_t GetEntityVersion() const noexcept = 0;

        SR_NODISCARD virtual bool InitializeEntity() noexcept { return true; }

    protected:
        void SetEntityPath(const EntityPath& path);

        SR_NODISCARD virtual std::list<EntityBranch> GetEntityBranches() const { return {}; }

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SavableSaveData data) const override {
            data.pMarshal = ISavable::Save(data);

            if (!(data.flags & SAVABLE_FLAG_ECS_NO_ID)) {
                data.pMarshal->Write(static_cast<uint64_t>(GetEntityId()));
            }
            else {
                data.pMarshal->Write(static_cast<uint64_t>(ENTITY_ID_MAX));
            }

            return data.pMarshal;
        }

    protected:
        SR_UTILS_NS::PropertyContainer m_entityMessages;

    private:
        EntityId m_entityId;
        EntityPath m_entityPath;

    };
}

#endif //SRENGINE_ENTITY_H
