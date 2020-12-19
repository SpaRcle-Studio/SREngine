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

        [[nodiscard]] inline glm::vec3 GetPosition(bool local = false) const noexcept { return local ? m_localPosition : m_globalPosition; }
        [[nodiscard]] inline glm::vec3 GetRotation(bool local = false) const noexcept { return local ? m_localRotation : m_globalRotation; }
        [[nodiscard]] inline glm::vec3 GetAroundRotation() const noexcept { return m_aroundRotation; }

        glm::vec3 Direction(glm::vec3 point) noexcept;

        inline float Distance(glm::vec3 point) const noexcept {
            return sqrt(
                    pow(point.x - m_globalPosition.x, 2) +
                    pow(point.y - m_globalPosition.y, 2) +
                    pow(point.z - m_globalPosition.z, 2)
            );
        }
        inline float Distance(Transform* transform) const noexcept {
            glm::vec3 p2 = transform->m_globalPosition;
            return sqrt(
                pow(p2.x - m_globalPosition.x, 2) +
                pow(p2.y - m_globalPosition.y, 2) +
                pow(p2.z - m_globalPosition.z, 2)
            );
        }

        [[nodiscard]] glm::vec3 Forward(bool local = false) const noexcept;
        [[nodiscard]] glm::vec3 Right(bool local = false)   const noexcept;
        [[nodiscard]] glm::vec3 Up(bool local = false)      const noexcept;

        void Translate(glm::vec3 val = {0,0,0}) noexcept;
        void Rotate(glm::vec3 angle    = {0,0,0}) noexcept;
        inline void Rotate(glm::vec3 axis, float angle) noexcept {
            this->Rotate(axis* angle);
        }
        void Scaling(glm::vec3 val   = {0,0,0}) noexcept;

        //void SetRotationAround(glm::vec3 point, glm::vec3 angle)    noexcept;
        //void RotateAround(glm::vec3 point, glm::vec3 angle)         noexcept;

        void RotateAround(glm::vec3 point, glm::vec3 axis, float angle) noexcept;
        inline void RotateAround(Transform* transform, glm::vec3 axis, float angle) noexcept {
            this->RotateAround(transform->m_globalPosition, axis, angle);
        }

        void SetRotateAround(glm::vec3 point, glm::vec3 angle) noexcept;
        inline void SetRotateAround(Transform* point, glm::vec3 angle) noexcept{
            this->SetRotateAround(point->m_globalPosition, angle);
        }

        void RotateAround(glm::vec3 point, glm::vec3 angle) noexcept;
        inline void RotateAround(Transform* transform, glm::vec3 angle) noexcept {
            this->RotateAround(transform->m_globalPosition, angle);
        }

        void LookAt(GameObject* gameObject) noexcept;
        inline void LookAt(Transform* transform) noexcept{
            this->LookAt(transform->m_globalPosition);
        }
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
        /*glm::vec3       m_position              = { 0, 0, 0 };
        glm::vec3       m_rotation              = { 0, 0, 0 };
        glm::vec3       m_scale                 = { 1, 1, 1 };

        glm::vec3       m_parent_position       = { 0, 0, 0 };
        glm::vec3       m_parent_rotation       = { 0, 0, 0 };
        glm::vec3       m_parent_scale          = { 0, 0, 0 };*/

        glm::vec3       m_localPosition              = { 0, 0, 0 };
        glm::vec3       m_localRotation              = { 0, 0, 0 };
        glm::vec3       m_localScale                 = { 1, 1, 1 };

        glm::vec3       m_globalPosition             = { 0, 0, 0 };
        glm::vec3       m_globalRotation             = { 0, 0, 0 };
        glm::vec3       m_globalScale                = { 1, 1, 1 };

        glm::vec3       m_aroundRotation;

        GameObject*     m_gameObject            = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
