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

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class GameObject;
    class Component {
        friend class GameObject;
        friend class Framework::API;
    public:
        Component(std::string name);
        ~Component();
    public:
        //virtual static Component* Load(const std::string& data) { return nullptr; }
        /*virtual nlohmann::json Save() {
            nlohmann::json json;
            json["BaseComponent"] = { };
            return json;
        }*/
    public:
        inline static Component* CreateComponentOfName(const std::string& name) {
            Component* result = nullptr;
            g_mutexCompList.lock();

            auto find = g_compList.find(name);
            if (find == g_compList.end())
                Debug::Error("Component::CreateComponentOfName() : component \""+name+"\" is not exists!");
            else
                result = find->second();

            g_mutexCompList.unlock();
            return result;
        }
        inline static std::vector<std::string> GetComponentsNames() {
            g_mutexCompList.lock();

            if (g_listHasBeenChanged) {
                g_compNames.clear();
                for (auto &it : g_compList)
                    g_compNames.push_back(it.first);
                g_listHasBeenChanged = false;
            }

            auto names = g_compNames;

            g_mutexCompList.unlock();

            return names;
        }
        inline static bool RegisterComponent(const std::string& name, const std::function<Component*(void)>& constructor) {
            g_mutexCompList.lock();

            auto find = g_compList.find(name);
            if (find == g_compList.end()) {
                Debug::System("Component::RegisterComponent() : register \""+name+"\"...");
                g_compList.insert(std::make_pair(name, constructor));
                g_listHasBeenChanged = true;

                g_mutexCompList.unlock();
                return true;
            }
            else{
                Debug::Error("Component::RegisterComponent() : component \""+name+"\" already registered!");

                g_mutexCompList.unlock();
                return false;
            }
        }
    private:
        inline static std::vector<std::string> g_compNames  = std::vector<std::string>();
        inline static bool g_listHasBeenChanged             = false;
        inline static std::mutex g_mutexCompList            = std::mutex();

        inline static std::map<std::string, std::function<Component*(void)>> g_compList =
                std::map<std::string, std::function<Component*(void)>>();
    protected:
        bool m_isSelected        = false;

        // Задается игровым объектом/движком, когда необходимо принудительно отключить
        bool m_isActive          = true;
        // Задается скриптами и пользователем через инспектор
        bool m_isEnabled         = true;

        const std::string m_name = "Unknown";
        GameObject* m_parent     = nullptr;
    public:
        virtual bool DrawOnInspector() { return false; }

        [[nodiscard]] inline std::string GetComponentName() const noexcept { return this->m_name; } // TODO: maybe unsafe
        inline Component* BaseComponent() noexcept { return this; }

        inline void SetParent(GameObject* parent) noexcept { this->m_parent = parent; }
        [[nodiscard]] inline GameObject* GetParent() const noexcept { return this->m_parent; }

        virtual void OnRotate(Math::Vector3 newValue) noexcept { };
        virtual void OnMove(Math::Vector3 newValue)   noexcept { };
        virtual void OnScaled(Math::Vector3 newValue) noexcept { };
        virtual void OnSelected(bool value) noexcept { this->m_isSelected = value; };
        virtual void OnReady(bool ready) { }

        void SetActive(bool v)  noexcept { this->m_isActive = v;  this->OnReady(IsReady()); }
        void SetEnabled(bool v) noexcept { this->m_isEnabled = v; this->OnReady(IsReady()); }

        [[nodiscard]] inline bool IsActive()         const noexcept { return m_isActive;                }
        [[nodiscard]] inline bool IsSelected()       const noexcept { return m_isSelected;              }
        [[nodiscard]] SR_FORCE_INLINE bool IsReady() const noexcept { return m_isActive && m_isEnabled; }
    protected:
        virtual void OnDestroyComponent() noexcept = 0;
        virtual void OnDestroyGameObject() noexcept = 0;
    };
}


#endif //GAMEENGINE_COMPONENT_H
