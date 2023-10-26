//
// Created by Monika on 12.12.2022.
//

#ifndef SRENGINE_ICOMPONENTABLE_H
#define SRENGINE_ICOMPONENTABLE_H

#include <Utils/Types/Marshal.h>
#include <Utils/ECS/ISavable.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class Component;

    class IComponentable {
    public:
        using Components = std::vector<Component*>;
        using ComponentList = std::list<Component*>;
        using ScenePtr = SR_WORLD_NS::Scene*;

    protected:
        IComponentable() = default;
        virtual ~IComponentable();

    public:
        SR_NODISCARD SR_INLINE const Components& GetComponents() const noexcept { return m_components; }
        SR_NODISCARD SR_INLINE const std::list<Component*>& GetLoadedComponents() const noexcept { return m_loadedComponents; }
        SR_NODISCARD bool IsDirty() const noexcept;

    public:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr SaveComponents(SavableSaveData data) const;

        /// Вызывает OnAttached у компонентов загруженных через LoadComponent
        virtual bool PostLoad(bool force);

        virtual void CheckActivity(bool force) noexcept;

        virtual void Awake(bool force, bool isPaused) noexcept;
        virtual void Start(bool force) noexcept;

        virtual bool SetDirty(bool dirty) {
            m_dirty = SR_CLAMP(m_dirty + (dirty ? 1 : -1), 3, 0);
            return m_dirty > 0;
        };

        virtual Component* GetOrCreateComponent(const std::string& name);
        virtual Component* GetOrCreateComponent(size_t hashName);
        virtual Component* GetComponent(const std::string& name);
        virtual Component* GetComponent(size_t hashName);

        virtual bool AddComponent(Component* component);

        virtual bool RemoveComponent(Component* component);
        virtual bool ContainsComponent(const std::string& name);
        virtual void ForEachComponent(const std::function<bool(Component*)>& fun);

        virtual void DestroyComponents();

        template<typename T> T* GetComponent() {
            return dynamic_cast<T*>(GetComponent(T::COMPONENT_HASH_NAME));
        }

        virtual void OnPriorityDirty();
        virtual void OnMatrixDirty();

        SR_NODISCARD virtual ScenePtr GetScene() const;

    protected:
        void DestroyComponent(Component* pComponent);

    protected:
        Components m_components = { };
        ComponentList m_loadedComponents = { };

    private:
        int8_t m_dirty = 1;

    };
}

#endif //SRENGINE_ICOMPONENTABLE_H
