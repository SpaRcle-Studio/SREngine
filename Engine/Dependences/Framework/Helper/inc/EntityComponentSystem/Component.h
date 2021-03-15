//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H
#include <glm/glm.hpp>
#include <string>
#include <json/json.hpp>

namespace Framework::Helper {
    class GameObject;
    class Component {
        friend class GameObject;
    public:
        Component(std::string name);
        ~Component();
    public:
        //virtual static Component* Load(const std::string& data) { return nullptr; }
        virtual nlohmann::json Save() {
            nlohmann::json json;
            json["BaseComponent"] = { };
            return json;
        }
    protected:
        bool m_isSelected        = false;
        bool m_isActive          = true;
        const std::string m_name = "Unknown";
        GameObject* m_parent     = nullptr;
    public:
        virtual bool DrawOnInspector() { return false; }

        [[nodiscard]] inline std::string GetComponentName() const noexcept { return this->m_name; }
        inline Component* BaseComponent() noexcept { return this; }

        inline void SetParent(GameObject* parent) noexcept { this->m_parent = parent; }
        [[nodiscard]] inline GameObject* GetParent() const noexcept { return this->m_parent; }

        virtual void OnRotate(glm::vec3 newValue)   noexcept { };
        virtual void OnMove(glm::vec3 newValue)     noexcept { };
        virtual void OnScaled(glm::vec3 newValue)   noexcept { };
        virtual void OnSelected(bool value)         noexcept {
            this->m_isSelected = value;
        };

        inline void SetActive(bool v) { m_isActive = v; }
        [[nodiscard]] inline bool IsActive() const noexcept { return m_isActive; }
        [[nodiscard]] inline bool IsSelected() const noexcept { return m_isSelected; }
    protected:
        virtual void OnDestroyGameObject() noexcept = 0;
    };
}


#endif //GAMEENGINE_COMPONENT_H
