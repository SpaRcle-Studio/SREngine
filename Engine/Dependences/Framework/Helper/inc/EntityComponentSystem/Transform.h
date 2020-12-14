//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <json/json.hpp>

namespace Framework::Helper {
    class GameObject;
    class Transform {
        friend class GameObject;
    private:
        Transform(GameObject* parent);
        ~Transform();
    public:
        glm::vec3 LocalDirection(const glm::vec3& dir);
    public:
        void SetPosition(glm::vec3 val);
        void SetRotation(glm::vec3 val);
        void SetScale(glm::vec3 val);

        void Translate(glm::vec3 val)   noexcept;
        void Rotate(glm::vec3 val)      noexcept;
        void Scaling(glm::vec3 val)     noexcept;
    public:
        nlohmann::json Save();
    public:
        inline static const glm::vec3 Right     = { 1, 0, 0 };
        inline static const glm::vec3 Up        = { 0, 1, 0 };
        inline static const glm::vec3 Forward   = { 0, 0, 1 };
    private:
        void UpdateChild(Transform* parent);
    private:
        glm::vec3       m_position              = { 0, 0, 0 };
        glm::vec3       m_rotation              = { 0, 0, 0 };
        glm::vec3       m_scale                 = { 1, 1, 1 };

        glm::vec3       m_parent_position       = { 0, 0, 0 };
        glm::vec3       m_parent_rotation       = { 0, 0, 0 };
        glm::vec3       m_parent_scale          = { 0, 0, 0 };

        GameObject*     m_parent                = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
