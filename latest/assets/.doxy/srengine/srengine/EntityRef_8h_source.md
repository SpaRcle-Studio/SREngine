

# File EntityRef.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**EntityRef.h**](EntityRef_8h.md)

[Go to the documentation of this file](EntityRef_8h.md)


```C++
//
// Created by Monika on 16.07.2025.
//

#ifndef SR_ENGINE_UTILS_ENTITY_REF_H
#define SR_ENGINE_UTILS_ENTITY_REF_H

#include <Utils/Serialization/Serializable.h>
#include <Utils/ECS/EntityController.h>

namespace SR_UTILS_NS {
    class EntityRefBase : public SR_UTILS_NS::Serializable {
        using Super = SR_UTILS_NS::Serializable;
        SR_CLASS()
    public:
        EntityRefBase();

    public:
        SR_NODISCARD virtual StringAtom GetTypeName() const noexcept;
        SR_NODISCARD const Entity::Ptr& GetEntity() const noexcept;
        SR_NODISCARD EntityId GetEntityId() const noexcept { return m_entityId; }
        SR_NODISCARD bool IsResolved() const noexcept;

        void OnEntityIdReplaced(const EntityReplaceMap& replaceMap);
        void SetEntityId(EntityId entityId) noexcept;

        void Resolve() const noexcept;

        SR_NODISCARD operator bool() const noexcept;

    private:
        EntityId m_entityId = SR_ID_INVALID;
        mutable Entity::Ptr m_pEntity;

    };

    template<class T> class EntityRef : public EntityRefBase {
        using Super = EntityRefBase;
    public:
        SR_NODISCARD StringAtom GetTypeName() const noexcept override {
            if constexpr (SR_UTILS_NS::IsCompleteTypeV<T>) {
                return T::GetClassStaticName();
            }
            else {
                SRHalt("EntityRef<T>::GetTypeName() : type T is not complete!");
                return SR_UTILS_NS::StringAtom();
            }
        }

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> Get() const noexcept {
            if constexpr (SR_UTILS_NS::IsCompleteTypeV<T>) {
                return GetEntity().template StaticCast<T>();
            }
            else {
                SRHalt("EntityRef<T>::Get() : type T is not complete!");
                return SR_HTYPES_NS::SharedPtr<T>();
            }
        }
    };
}

#endif //SR_ENGINE_UTILS_ENTITY_REF_H
```


