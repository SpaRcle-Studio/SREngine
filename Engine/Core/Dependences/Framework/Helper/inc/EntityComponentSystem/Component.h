//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <Math/Vector3.h>
#include <string>
#include <unordered_map>
#include <mutex>
#include <Types/DataStorage.h>
#include <Types/SafePointer.h>
#include <Utils/Singleton.h>
#include <Utils/NonCopyable.h>
#include <Utils/StringUtils.h>
#include <EntityComponentSystem/EntityManager.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class Component;

    class ComponentManager : public Singleton<ComponentManager>, public NonCopyable {
        friend class Singleton<ComponentManager>;
        typedef std::function<void(Component*)> Event;
        typedef std::function<Component*(const MarshalDecodeNode& node, const Helper::Types::DataStorage* dataStorage)> Loader;
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

            m_loaders.insert(std::make_pair(code, [](const MarshalDecodeNode& node, const Helper::Types::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(node, dataStorage);
            }));

            return RegisterComponentImpl(code, StringUtils::BackRead(typeid(T).name(), ':'), constructor);
        }

        bool LoadComponents(const std::function<bool(Types::DataStorage& context)>& loader) {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            const bool result = loader(m_context);

            m_context.Clear();

            return result;
        }

        Component* Load(const MarshalDecodeNode& node);

        Types::DataStorage* GetContext() { return &m_context; }

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
        Types::DataStorage m_context;

    };

    class GameObject;
    class Component : public Entity {
        friend class GameObject;
        friend class Framework::API;
    public:
        ~Component() override = default;

    public:
        virtual void OnRotate(const Math::FVector3& newValue) { };
        virtual void OnMove(const Math::FVector3& newValue) { };
        virtual void OnScaled(const Math::FVector3& newValue) { };
        virtual void OnSkewed(const Math::FVector3& newValue) { };
        virtual void OnSelected(bool value) { this->m_isSelected = value; };
        virtual void OnReady(bool ready) { }
        virtual void OnAttachComponent();

    public:
        void SetActive(bool value) { m_isActive = value; OnReady(IsReady()); }
        void SetEnabled(bool value) { m_isEnabled = value; OnReady(IsReady()); }
        void SetParent(GameObject* parent) { m_parent = parent; }

    public:
        [[nodiscard]] virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        [[nodiscard]] SR_INLINE bool IsEnabled()  const { return m_isEnabled;               }
        [[nodiscard]] SR_INLINE bool IsActive()   const { return m_isActive;                }
        [[nodiscard]] SR_INLINE bool IsSelected() const { return m_isSelected;              }
        [[nodiscard]] SR_INLINE bool IsReady()    const { return m_isActive && m_isEnabled; }
        [[nodiscard]] SR_INLINE std::string GetComponentName() const { return m_name; }
        [[nodiscard]] SR_INLINE size_t GetComponentId() const { return m_componentId; }
        [[nodiscard]] SR_INLINE Component* BaseComponent() { return this; }
        [[nodiscard]] SR_INLINE GameObject* GetParent() const { return this->m_parent; }

    protected:
        template<typename T> void Init() {
            m_componentId = typeid(T).hash_code();
            m_name = StringUtils::BackRead(typeid(T).name(), ':');
        }

        virtual void OnRemoveComponent() = 0;
        virtual void OnDestroyGameObject() = 0;

    protected:
        bool m_isSelected          = false;

        // Задается игровым объектом/движком, когда необходимо принудительно отключить
        bool m_isActive            = true;
        // Задается скриптами и пользователем через инспектор
        bool m_isEnabled           = true;

        std::string m_name = "Unknown";
        size_t m_componentId = SIZE_MAX;
        GameObject* m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
