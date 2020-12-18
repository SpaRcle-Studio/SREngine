//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <json/json.hpp>
#include <glm/detail/type_quat.hpp>

namespace Framework::Helper {
    class GameObject;
    class Transform {
        friend class GameObject;
    private:
        Transform(GameObject* parent);
        ~Transform() = default;
    //public:
    //   glm::vec3 LocalDirection(const glm::vec3& dir);
    public:
        void SetPosition(glm::vec3 val);
        void SetRotation(glm::vec3 val);
        void SetScale(glm::vec3 val);

        [[nodiscard]] inline glm::vec3 GetPosition() const noexcept { return m_position; }
        [[nodiscard]] inline glm::vec3 GetRotation() const noexcept { return m_rotation; }

        inline float Distance(glm::vec3 point) const noexcept {
            return sqrt(
                    pow(point.x - m_position.x, 2) +
                    pow(point.y - m_position.y, 2) +
                    pow(point.z - m_position.z, 2)
            );
        }
        inline float Distance(Transform* transform) const noexcept {
            //return glm::distance(m_position, transform->m_position);
            glm::vec3 p2 = transform->m_position;
            return sqrt(
                pow(p2.x - m_position.x, 2) +
                pow(p2.y - m_position.y, 2) +
                pow(p2.z - m_position.z, 2)
            );
        }

        glm::vec3 Forward() const noexcept;
        glm::vec3 Right()   const noexcept;
        glm::vec3 Up()    const noexcept;

        void Translate(glm::vec3 val = {0,0,0})         noexcept;
        void Rotate(glm::vec3 val    = {0,0,0})         noexcept;
        void Scaling(glm::vec3 val   = {0,0,0})         noexcept;

        //void SetRotationAround(glm::vec3 point, glm::vec3 angle)    noexcept;
        //void RotateAround(glm::vec3 point, glm::vec3 angle)         noexcept;
        void RotateAround(glm::vec3 point, glm::vec3 axis, float angle) noexcept;

        void LookAt(glm::vec3 target);
    public:
        nlohmann::json Save();
    public:
        inline static const glm::vec3 right     = { 1, 0, 0 };
        inline static const glm::vec3 forward   = { 0, 0, 1 };
        inline static const glm::vec3 up        = { 0, 1, 0 };

        inline static const glm::vec3 down      = {  0, -1,  0 };
        inline static const glm::vec3 left      = { -1,  0,  0 };
        inline static const glm::vec3 back      = {  0,  0, -1 };

        inline static const glm::vec3 pitch     = { 1, 0, 0 };
        inline static const glm::vec3 yaw       = { 0, 1, 0 };
        inline static const glm::vec3 roll      = { 0, 0, 1 };
    private:
        //void UpdateChild(Transform* parent);

        void UpdateChildPosition(Transform* parent) noexcept;
        void UpdateChildRotation(Transform* parent) noexcept;
        void UpdateChildScale(Transform* parent)    noexcept;
    private:
        glm::vec3       m_position              = { 0, 0, 0 };
        glm::vec3       m_rotation              = { 0, 0, 0 };
        glm::vec3       m_scale                 = { 1, 1, 1 };

        glm::vec3       m_parent_position       = { 0, 0, 0 };
        glm::vec3       m_parent_rotation       = { 0, 0, 0 };
        glm::vec3       m_parent_scale          = { 0, 0, 0 };

        GameObject*     m_gameObject            = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
