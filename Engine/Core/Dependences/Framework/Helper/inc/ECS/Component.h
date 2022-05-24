//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <ECS/EntityManager.h>

#include <Debug.h>

#include <Math/Vector3.h>
#include <Types/SafePointer.h>
#include <Utils/Singleton.h>
#include <Utils/NonCopyable.h>
#include <Utils/StringUtils.h>
#include <Types/DataStorage.h>

namespace SR_UTILS_NS {
    class Component;
    class GameObject;

    class ComponentManager : public Singleton<ComponentManager>, public NonCopyable {
        friend class Singleton<ComponentManager>;
        typedef std::function<void(Component*)> Event;
        typedef std::function<Component*(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage)> Loader;
    public:
        Component* CreateComponentOfName(const std::string& name);

        template<typename T> Component* CreateComponent() {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            return CreateComponentImpl(typeid(T).hash_code());
        }

        std::unordered_map<std::string, size_t> GetComponentsNames() {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            return m_ids;
        }

        void DoEvent(Component* caller, size_t hash_id) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            if (m_events.count(hash_id) == 1)
                m_events.at(hash_id)(caller);
        }

        template<typename T> bool RegisterEvents(const Event& onAttach) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            m_events.insert(std::make_pair(typeid(T).hash_code(), onAttach));
            return true;
        }

        template<typename T> bool RegisterComponent(const std::function<Component*(void)>& constructor) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            const auto&& code = typeid(T).hash_code();

            m_loaders.insert(std::make_pair(code, [](SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(marshal, dataStorage);
            }));

            return RegisterComponentImpl(code, StringUtils::BackRead(typeid(T).name(), ':'), constructor);
        }

        bool LoadComponents(const std::function<bool(Types::DataStorage& context)>& loader) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            const bool result = loader(m_context);

            m_context.Clear();

            return result;
        }

        SR_NODISCARD std::string GetLastComponentName() const {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            return m_lastComponent;
        }

        Component* Load(SR_HTYPES_NS::Marshal& marshal);

        SR_HTYPES_NS::DataStorage* GetContext() { return &m_context; }

    private:
        bool RegisterComponentImpl(size_t id, const std::string& name, const std::function<Component*(void)>& constructor);
        Component* CreateComponentImpl(size_t id);

    private:
        mutable std::recursive_mutex m_mutex = std::recursive_mutex();
        std::unordered_map<size_t, std::function<Component*(void)>> m_creators;
        std::unordered_map<size_t, Loader> m_loaders;
        std::unordered_map<size_t, Event> m_events;
        std::unordered_map<size_t, std::string> m_names;
        std::unordered_map<std::string, size_t> m_ids;
        SR_HTYPES_NS::DataStorage m_context;
        std::string m_lastComponent;

    };

    class Component : public Entity {
        friend class GameObject;
    public:
        ~Component() override = default;

    public:
        virtual void OnRotate(const Math::FVector3& newValue) { };
        virtual void OnMove(const Math::FVector3& newValue) { };
        virtual void OnScaled(const Math::FVector3& newValue) { };
        virtual void OnSkewed(const Math::FVector3& newValue) { };
        virtual void OnReady(bool ready) { }
        virtual void OnAttachComponent();

    public:
        void SetActive(bool value) { m_isActive = value; OnReady(IsReady()); }
        void SetEnabled(bool value) { m_isEnabled = value; OnReady(IsReady()); }
        void SetParent(GameObject* parent) { m_parent = parent; }

    public:
        SR_NODISCARD virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        SR_NODISCARD SR_INLINE bool IsEnabled() const { return m_isEnabled; }
        SR_NODISCARD SR_INLINE bool IsActive() const { return m_isActive; }
        SR_NODISCARD SR_INLINE bool IsReady() const { return m_isActive && m_isEnabled; }
        SR_NODISCARD SR_INLINE std::string GetComponentName() const { return m_name; }
        SR_NODISCARD SR_INLINE size_t GetComponentId() const { return m_componentId; }
        SR_NODISCARD SR_INLINE Component* BaseComponent() { return this; }
        SR_NODISCARD SR_INLINE GameObject* GetParent() const { return m_parent; }

    protected:
        template<typename T> void Init() {
            m_componentId = typeid(T).hash_code();
            m_name = StringUtils::BackRead(typeid(T).name(), ':');
        }

        virtual void OnRemoveComponent() = 0;
        virtual void OnDestroyGameObject() = 0;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SavableFlags flags) const override;

    protected:
        /// Задается игровым объектом/движком, когда необходимо принудительно отключить
        bool m_isActive = true;
        /// Задается скриптами и пользователем через инспектор
        bool m_isEnabled = true;

        std::string m_name = "Unknown";
        uint64_t m_componentId = SIZE_MAX;
        GameObject* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
