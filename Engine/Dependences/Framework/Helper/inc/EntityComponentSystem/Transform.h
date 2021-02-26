//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <json/json.hpp>
#include <glm/detail/type_quat.hpp>

#include <Math/Mathematics.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#define RAD3(v) glm::vec3(RAD(v.x),RAD(v.y),RAD(v.z))
#define DEG3(v) glm::vec3(DEG(v.x),DEG(v.y),DEG(v.z))

namespace Framework::Helper {
    enum class Location{
        Left, Center, Right, Forward, Back, Up, Down
    };

    class GameObject;
    class Transform {
        friend class GameObject;
    private:
        Transform(GameObject* parent);
        ~Transform() = default;
    public:
        void OnParentSet(Transform* parent) {
            this->m_parent = parent;
        }
        void OnParentRemove(Transform* parent) {
            m_parent = nullptr;
        }

        void SetPosition(glm::vec3 val, bool pivot = false);
        void SetRotation(glm::vec3 val, bool pivot = false);
        void SetScale(glm::vec3 val, bool pivot  = false);

        [[nodiscard]] glm::mat4 GetMatrix() const noexcept;
        void SetMatrix(glm::mat4 matrix, bool pivot) noexcept;

        [[nodiscard]] inline glm::vec3 GetPosition(bool local = false) const noexcept { return local ? m_localPosition : m_globalPosition; }
        [[nodiscard]] inline glm::vec3 GetRotation(bool local = false) const noexcept { return local ? m_localRotation : m_globalRotation; }
        [[nodiscard]] inline glm::vec3 GetScale(bool local = false) const noexcept { return local ? m_localScale : m_globalScale; }

        glm::vec3 Direction(glm::vec3 point) noexcept;

        inline static float Len(const glm::vec3& v) noexcept {
            return sqrt(
                    v.x * v.x +
                    v.y * v.y +
                    v.z * v.z
                    );
        }

        [[nodiscard]] inline float Distance(glm::vec3 point) const noexcept {
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
    public:
        void UpdateLocalPosition();
        void UpdateLocalScale();

        void UpdateChildPosition(glm::vec3 delta, bool pivot);
        void UpdateChildScale(glm::vec3 delta, bool pivot);
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
        glm::vec3       m_localPosition              = { 0, 0, 0 };
        glm::vec3       m_localRotation              = { 0, 0, 0 };
        glm::vec3       m_localScale                 = { 1, 1, 1 };

        glm::vec3       m_globalPosition             = { 0, 0, 0 };
        glm::vec3       m_globalRotation             = { 0, 0, 0 };
        glm::vec3       m_globalScale                = { 1, 1, 1 };

        GameObject*     m_gameObject                 = nullptr;
        Transform*      m_parent                     = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
