//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <Math/Vector3.h>
#include <string>
#include <json/json.hpp>
#include <macros.h>
#include <mutex>
#include <Debug.h>
#include <Types/SafePointer.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class GameObject;
    class Component {
        typedef std::function<void(Component*)> Event;

        friend class GameObject;
        friend class Framework::API;
    public:
        Component(std::string name);
        ~Component();
    public:
        static Component* CreateComponentOfName(const std::string& name) {
            const std::lock_guard<std::mutex> lock(g_mutex);

            auto find = g_compList.find(name);
            if (find == g_compList.end()) {
                Debug::Error("Component::CreateComponentOfName() : component \"" + name + "\" is not exists!");
                return nullptr;
            }
            else
                return find->second();
        }
        static std::vector<std::string> GetComponentsNames() {
            const std::lock_guard<std::mutex> lock(g_mutex);
            return g_names;
        }

        static bool RegisterEvents(const std::string& compName, const Event& onAttach) {
            const std::lock_guard<std::mutex> lock(g_mutex);

            if (auto find = g_events.find(compName); find == g_events.end()) {
                g_events.insert(std::make_pair(compName, onAttach));
                return true;
            } else {
                Debug::Error("Component::RegisterEvents() : events for component \""+compName+"\" already registered!");
                return false;
            }
        }

        static bool RegisterComponent(const std::string& name, const std::function<Component*(void)>& constructor) {
            const std::lock_guard<std::mutex> lock(g_mutex);

            if (auto find = g_compList.find(name); find == g_compList.end()) {
                Debug::System("Component::RegisterComponent() : register \""+name+"\"...");
                g_compList.insert(std::make_pair(name, constructor));
                g_names.emplace_back(name);
                return true;
            }
            else{
                Debug::Error("Component::RegisterComponent() : component \""+name+"\" already registered!");
                return false;
            }
        }
    private:
        inline static std::vector<std::string> g_compNames = std::vector<std::string>();
        inline static std::mutex               g_mutex     = std::mutex();
        inline static std::vector<std::string> g_names     = std::vector<std::string>();

        inline static std::map<std::string, std::function<Component*(void)>> g_compList =
                std::map<std::string, std::function<Component*(void)>>();

        inline static std::map<std::string, Event> g_events = std::map<std::string, Event>();
    protected:
        bool m_isSelected          = false;

        // Задается игровым объектом/движком, когда необходимо принудительно отключить
        bool m_isActive            = true;
        // Задается скриптами и пользователем через инспектор
        bool m_isEnabled           = true;

        const std::string m_name   = "Unknown";
        GameObject*       m_parent = nullptr;
    public:
        [[nodiscard]] inline std::string GetComponentName() const noexcept { return this->m_name; }

        Component* BaseComponent() noexcept { return this; }
        void SetParent(GameObject* parent) noexcept { this->m_parent = parent; }
        [[nodiscard]] inline GameObject* GetParent() const noexcept { return this->m_parent; }

        virtual bool DrawOnInspector() { return false; }
        [[nodiscard]] virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        virtual void OnRotate(const Math::FVector3& newValue) { };
        virtual void OnMove(const Math::FVector3& newValue) { };
        virtual void OnScaled(const Math::FVector3& newValue) { };
        virtual void OnSelected(bool value) { this->m_isSelected = value; };
        virtual void OnReady(bool ready) { }
        virtual void OnAttachComponent() {
            const std::lock_guard<std::mutex> lock(g_mutex);
            if (auto event = g_events.find(m_name); event != g_events.end())
                event->second(this);
        }

        void SetActive(bool v) { this->m_isActive = v;  this->OnReady(IsReady()); }
        void SetEnabled(bool v) { this->m_isEnabled = v; this->OnReady(IsReady()); }

        [[nodiscard]] inline bool IsActive()         const noexcept { return m_isActive;                }
        [[nodiscard]] inline bool IsSelected()       const noexcept { return m_isSelected;              }
        [[nodiscard]] SR_FORCE_INLINE bool IsReady() const noexcept { return m_isActive && m_isEnabled; }
    protected:
        virtual void OnRemoveComponent() = 0;
        virtual void OnDestroyGameObject() = 0;
    };
}


#endif //GAMEENGINE_COMPONENT_H
