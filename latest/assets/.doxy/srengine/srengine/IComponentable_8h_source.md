

# File IComponentable.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**IComponentable.h**](IComponentable_8h.md)

[Go to the documentation of this file](IComponentable_8h.md)


```C++
//
// Created by Monika on 12.12.2022.
//

#ifndef SR_ENGINE_I_COMPONENTABLE_H
#define SR_ENGINE_I_COMPONENTABLE_H

#include <Utils/Types/Marshal.h>
#include <Utils/Types/Vector.h>
#include <Utils/ECS/Entity.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class IComponentable : public Entity {
        using Super = Entity;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IComponentable>;
        using ScenePtr = SR_WORLD_NS::Scene*;
        using OriginType = IComponentable;

    public:
        IComponentable() = default;
        ~IComponentable() override;

    public:
        SR_NODISCARD bool IsDirty() const noexcept;

    public:
        virtual bool PostLoad(bool force);

        virtual void CheckActivity(bool force) noexcept;

        virtual void Awake(bool force, bool isPaused) noexcept;
        virtual void Start(bool force) noexcept;

        SR_NODISCARD virtual bool IsActive() const noexcept { return true; }
        SR_NODISCARD virtual bool IsDestroyed() const noexcept { return false; }

        virtual bool SetDirty(bool dirty);

        virtual Component::Ptr GetOrCreateComponent(const std::string& name);
        virtual Component::Ptr GetOrCreateComponent(StringAtom name);
        virtual Component::Ptr GetComponent(const std::string& name);
        virtual Component::Ptr GetComponent(StringAtom name);
        virtual bool MoveComponent(const Component::Ptr& pComponent, int32_t offset);

        SR_NODISCARD bool HasComponent(const Component::Ptr& pComponent) const;
        SR_NODISCARD int32_t GetComponentIndex(const Component::Ptr& pComponent) const;
        SR_NODISCARD uint32_t GetComponentsCount() const noexcept { return static_cast<uint32_t>(m_components.size()); }
        SR_NODISCARD const std::vector<Component::Ptr>& GetComponents() const noexcept { return m_components; }

        virtual bool AddComponent(const Component::Ptr& pComponent);

        template<typename T> SR_HTYPES_NS::SharedPtr<T> AddComponent() {
            Component::Ptr pComponent = SR_UTILS_NS::Factory::Instance().Create<Component>(T::GetClassStaticName());
            if (!pComponent) {
                SR_ERROR("IComponentable::AddComponent() : failed to create component of type: {}", T::GetClassStaticName());
                return nullptr;
            }
            if (!AddComponent(pComponent)) {
                SR_ERROR("IComponentable::AddComponent() : failed to add component of type: {}", T::GetClassStaticName());
                return nullptr;
            }
            return pComponent->template DynamicCast<T>();
        }

        void RemoveComponents();
        virtual bool RemoveComponent(const Component::Ptr& pComponent);
        virtual bool ContainsComponent(const std::string& name);

        virtual void ForEachComponent(const std::function<bool(const Component::Ptr&)>& fun) const;
        virtual void ForEachComponent(const std::function<bool(Component::Ptr&)>& fun);

        template<typename T> SR_HTYPES_NS::SharedPtr<T> GetComponent() {
            return GetComponent(T::GetClassStaticName()).template DynamicCast<T>();
        }

        virtual void OnPriorityChanged();
        virtual void OnMatrixDirty();

        SR_NODISCARD virtual bool IsPrefab() const noexcept { return false; }

        SR_NODISCARD virtual ScenePtr GetScene() const;

        void OnPostLoad() override;

    protected:
        void DestroyComponent(const Component::Ptr& pComponent);

    protected:
        std::vector<Component::Ptr> m_components;

    private:
        bool m_hasNotAttachedComponents = false;
        bool m_dirty = true;

    };
}

#endif //SR_ENGINE_I_COMPONENTABLE_H
```


