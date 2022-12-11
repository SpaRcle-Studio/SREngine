//
// Created by Monika on 12.12.2022.
//

#ifndef SRENGINE_ICOMPONENTABLE_H
#define SRENGINE_ICOMPONENTABLE_H

namespace SR_UTILS_NS {
    class Component;

    class IComponentable {
    public:
        using Components = std::vector<Component*>;

    protected:
        virtual ~IComponentable() = default;
        IComponentable() = default;

    public:
        SR_NODISCARD SR_INLINE const Components& GetComponents() const noexcept { return m_components; }

    public:
        virtual Component* GetOrCreateComponent(const std::string& name);
        virtual Component* GetComponent(const std::string& name);
        virtual Component* GetComponent(size_t id);

        /** Отличие от AddComponent в том, что используется только при загрузке объекта,
        * не вызывая при этом OnAttached -> Awake -> OnEnable -> Start, а делая это отложенно */
        virtual bool LoadComponent(Component* component);

        /** Добавляет новый компонент на объект, вызывает у компонента
         * последовательность Awake -> OnEnable -> Start */
        virtual bool AddComponent(Component* component);

        virtual bool RemoveComponent(Component* component);
        virtual bool ReplaceComponent(Component* source, Component* destination);
        virtual bool ContainsComponent(const std::string& name);
        virtual void ForEachComponent(const std::function<bool(Component*)>& fun);

        template<typename T> T* GetComponent() {
            return dynamic_cast<T*>(GetComponent(typeid(T).hash_code()));
        }

    protected:
        uint16_t m_componentsCount = 0;
        uint16_t m_childrenCount = 0;

        Components m_components = { };
        std::list<Component*> m_loadedComponents = { };

    };
}

#endif //SRENGINE_ICOMPONENTABLE_H
