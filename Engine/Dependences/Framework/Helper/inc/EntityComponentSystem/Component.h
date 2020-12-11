//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H
#include <glm/glm.hpp>
#include <string>

namespace Framework::Helper {
    class GameObject;
    class Component {
        friend class GameObject;
    public:
        Component(std::string name);
        ~Component();
    public:
        virtual bool Load(const std::string& data) { return false; }
        virtual std::string Save() { return "Base component"; }
    protected:
        bool m_isActive = true;
        const std::string m_name = "Unknown";
        GameObject* m_parent = nullptr;
    public:
        inline void SetParent(GameObject* parent) noexcept { this->m_parent = parent; }

        virtual void OnRotate(glm::vec3 newValue) noexcept { };
        virtual void OnMove(glm::vec3 newValue) noexcept { };
        virtual void OnScaled(glm::vec3 newValue) noexcept { };

        inline void SetActive(bool v) { m_isActive = v; }
        [[nodiscard]] inline bool IsActive() const noexcept { return m_isActive; }
    protected:
        virtual void OnDestroyGameObject() noexcept = 0;
    };
}


#endif //GAMEENGINE_COMPONENT_H
