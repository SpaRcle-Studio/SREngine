

# File Entity.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**Entity.h**](Entity_8h.md)

[Go to the documentation of this file](Entity_8h.md)


```C++
//
// Created by Monika on 12.04.2023.
//

#ifndef SR_ENGINE_UTILS_ENTITY_H
#define SR_ENGINE_UTILS_ENTITY_H

#include <Utils/Serialization/Serializable.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/Common/Numeric.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/Properties.h>
#include <Utils/TypeTraits/SRClass.h>

namespace SR_UTILS_NS {
    class Entity;
    class EntityController;

    typedef uint64_t EntityId;

    SR_ENUM_NS_STRUCT_T(EditorFlags, uint64_t,
        None       = 1 << 0,
        DontDelete = 1 << 1,
        ReadOnly   = 1 << 2,
        Hidden     = 1 << 4
    )

    class SR_DLL_EXPORT Entity : public Serializable, public SR_HTYPES_NS::SharedPtr<Entity> {
        SR_CLASS()
        using Super = Serializable;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Entity>;
        using OriginType = Entity;

    public:
        Entity();
        ~Entity() override;

    public:
        SR_NODISCARD const SR_UTILS_NS::PropertyContainer& GetEntityMessages() const { return m_entityMessages; }

        SR_NODISCARD bool IsEntityRegistered() const noexcept { return m_pEntityController; }
        SR_NODISCARD EntityId GetEntityId() const { return m_entityId; }
        SR_NODISCARD EntityRef GetRef() const noexcept { return EntityRef(GetThis()); }
        SR_NODISCARD Entity::Ptr GetEntity() const noexcept { return GetThis(); }

        SR_NODISCARD virtual bool InitializeEntity() noexcept { return true; }

        void SetEntityController(EntityController* pEntityController);
        void SetEntityId(EntityId id);
        void UnregisterEntity();

        virtual void OnEntityIdReplaced(const std::map<EntityId, EntityId>& replaceMap) { }

        void AddEditorFlags(EditorFlags flags) noexcept { m_editorFlags |= flags; }
        void RemoveEditorFlags(EditorFlags flags) noexcept { m_editorFlags &= ~flags; }

        SR_NODISCARD bool HasEditorFlags(EditorFlags flags) const noexcept {
            return SR_MATH_NS::IsMaskIncludedSubMask(m_editorFlags, flags);
        }

        SR_NODISCARD virtual bool IsPrefabLoadingState() const noexcept { return false; }

    protected:
        SR_UTILS_NS::PropertyContainer m_entityMessages;

    private:
        EntityId m_entityId = SR_ID_INVALID;

        EntityController* m_pEntityController = nullptr;
        EditorFlags m_editorFlags = EditorFlags::None;

    };
}

#endif //SR_ENGINE_UTILS_ENTITY_H
```


