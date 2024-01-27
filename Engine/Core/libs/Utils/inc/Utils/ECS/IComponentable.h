//
// Created by Monika on 12.12.2022.
//

#ifndef SR_ENGINE_ICOMPONENTABLE_H
#define SR_ENGINE_ICOMPONENTABLE_H

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

        SR_NODISCARD virtual bool IsActive() const noexcept { return true; }

        virtual bool SetDirty(bool dirty) {
            if (!m_loadedComponents.empty()) {
                m_dirty = true;
                return true;
            }
            return (m_dirty = dirty);
        };

        virtual Component* GetOrCreateComponent(const std::string& name);
        virtual Component* GetOrCreateComponent(StringAtom name);
        virtual Component* GetComponent(const std::string& name);
        virtual Component* GetComponent(StringAtom name);

        virtual bool AddComponent(Component* component);

        virtual bool RemoveComponent(Component* component);
        virtual bool ContainsComponent(const std::string& name);
        virtual void ForEachComponent(const std::function<bool(Component*)>& fun);

        virtual void DestroyComponents();

        template<typename T> T* GetComponent() {
            return dynamic_cast<T*>(GetComponent(T::COMPONENT_NAME));
        }

        virtual void OnPriorityChanged();
        virtual void OnMatrixDirty();

        SR_NODISCARD virtual ScenePtr GetScene() const;

    protected:
        void DestroyComponent(Component* pComponent);

    protected:
        Components m_components = { };
        ComponentList m_loadedComponents = { };

    private:
        bool m_dirty = true;

    };
}

#endif //SR_ENGINE_ICOMPONENTABLE_H
