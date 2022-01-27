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
#include <EntityComponentSystem/EntityManager.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class GameObject;
    class Component : public Entity {
        typedef std::function<void(Component*)> Event;

        friend class GameObject;
        friend class Framework::API;
    public:
        explicit Component(const std::string& name);
        ~Component() override;

    public:
        static Component* CreateComponentOfName(const std::string& name);
        static std::vector<std::string> GetComponentsNames();
        static bool RegisterEvents(const std::string& compName, const Event& onAttach);
        static bool RegisterComponent(const std::string& name, const std::function<Component*(void)>& constructor);

    public:
        virtual void OnRotate(const Math::FVector3& newValue) { };
        virtual void OnMove(const Math::FVector3& newValue) { };
        virtual void OnScaled(const Math::FVector3& newValue) { };
        virtual void OnSkewed(const Math::FVector3& newValue) { };
        virtual void OnSelected(bool value) { this->m_isSelected = value; };
        virtual void OnReady(bool ready) { }
        virtual void OnAttachComponent();
        virtual bool DrawOnInspector() { return false; }
    public:

        void SetActive(bool v) { this->m_isActive = v;  this->OnReady(IsReady()); }
        void SetEnabled(bool v) { this->m_isEnabled = v; this->OnReady(IsReady()); }
        void SetParent(GameObject* parent) { this->m_parent = parent; }

    public:
        [[nodiscard]] virtual Math::FVector3 GetBarycenter() const { return Math::InfinityFV3; }
        [[nodiscard]] SR_INLINE bool IsEnabled()  const { return m_isEnabled;               }
        [[nodiscard]] SR_INLINE bool IsActive()   const { return m_isActive;                }
        [[nodiscard]] SR_INLINE bool IsSelected() const { return m_isSelected;              }
        [[nodiscard]] SR_INLINE bool IsReady()    const { return m_isActive && m_isEnabled; }
        [[nodiscard]] SR_INLINE std::string GetComponentName() const { return this->m_name; }
        [[nodiscard]] SR_INLINE Component* BaseComponent() { return this; }
        [[nodiscard]] SR_INLINE GameObject* GetParent() const { return this->m_parent; }

    protected:
        virtual void OnRemoveComponent() = 0;
        virtual void OnDestroyGameObject() = 0;

    private:
        SR_INLINE static std::vector<std::string> g_compNames = std::vector<std::string>();
        SR_INLINE static std::mutex               g_mutex     = std::mutex();
        SR_INLINE static std::vector<std::string> g_names     = std::vector<std::string>();

        SR_INLINE static std::map<std::string, std::function<Component*(void)>> g_compList =
                std::map<std::string, std::function<Component*(void)>>();

        SR_INLINE static std::map<std::string, Event> g_events = std::map<std::string, Event>();

    protected:
        bool m_isSelected          = false;

        // Задается игровым объектом/движком, когда необходимо принудительно отключить
        bool m_isActive            = true;
        // Задается скриптами и пользователем через инспектор
        bool m_isEnabled           = true;

        const std::string m_name   = "Unknown";
        GameObject*       m_parent = nullptr;

    };
}


#endif //GAMEENGINE_COMPONENT_H
