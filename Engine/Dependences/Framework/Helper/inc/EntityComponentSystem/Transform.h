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
        void SetPosition(glm::vec3 val);
        void SetRotation(glm::vec3 val);
        void SetScale(glm::vec3 val);

        [[nodiscard]] inline glm::mat4 GetMatrix(bool local = true) const noexcept {
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), {
                    local ? m_localPosition.x  : m_globalPosition.x,
                    local ? m_localPosition.y  : m_globalPosition.y,
                    local ? -m_localPosition.z : -m_globalPosition.z
            });

            const glm::mat4 rotationMatrix = mat4_cast(glm::quat(glm::radians(glm::vec3(
                   local ? m_localRotation : m_globalRotation
            ))));

            modelMat *= rotationMatrix;

            return glm::scale(modelMat, local ? m_localScale : m_globalScale);
        }
        inline void SetMatrix(glm::mat4 matrix) {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(matrix, scale, rotation, translation, skew, perspective);

            /*this->m_localPosition = translation;
            this->m_localRotation = glm::eulerAngles(rotation);
            this->m_localScale    = scale;*/

            this->m_globalPosition = {translation.x, translation.y, -translation.z};
            this->m_globalRotation = glm::eulerAngles(rotation);
            this->m_localScale     = scale;
        }

        [[nodiscard]] inline glm::vec3 GetPosition(bool local = false) const noexcept { return local ? m_localPosition : m_globalPosition; }
        [[nodiscard]] inline glm::vec3 GetRotation(bool local = false) const noexcept { return local ? m_localRotation : m_globalRotation; }
        [[nodiscard]] inline glm::vec3 GetScale(bool local = false) const noexcept { return local ? m_localScale : m_globalScale; }
        //[[nodiscard]] inline glm::vec3 GetAroundRotation() const noexcept { return m_aroundRotation; }

        /* Left-Center-Right */
        [[nodiscard]] inline Location GetGlobal_LCR_Location(glm::vec3 point) const noexcept {
            if (point.x < m_globalPosition.x)
                return Location::Left;
            else if (point.x > m_globalPosition.x)
                return Location::Right;
            else
                return Location::Center;
        }

        /* Forward-Center-Back */
        [[nodiscard]] inline Location GetGlobal_FCB_Location(glm::vec3 point) const noexcept {
            if (point.z < m_globalPosition.z)
                return Location::Back;
            else if (point.z > m_globalPosition.z)
                return Location::Forward;
            else
                return Location::Center;
        }

        /*
               Yaw
         ==============
         |F   -90    R|
         |            |
         | 0        0 |
         |            |
         |L    90    B|
         ==============
         */
        glm::vec3 GetAngleOfPoint(glm::vec3 point) noexcept;

        /*
                Yaw
         ================
         |F      0     R|
         |              |
         | -90       90 |
         |              |
         |L     180    B|
         ================
         */
        glm::vec3 GetNormalizedAngleOfPoint(glm::vec3 point) noexcept;

        glm::vec3 Direction(glm::vec3 point) noexcept;

        inline static float Len(const glm::vec3& v) noexcept {
            return sqrt(
                    v.x * v.x +
                    v.y * v.y +
                    v.z * v.z
                    );
        }

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

        inline glm::quat Quaternion(bool local = false) noexcept{
            glm::vec3 rot = local ? m_localRotation : m_globalRotation;
            return glm::quat(glm::radians(glm::vec3(
                    rot.x,
                    rot.y,
                    -rot.z
            )));
        }

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

        glm::vec3 GetLookAt(glm::vec3 target, glm::vec3 axis) noexcept;
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
        void CheckNaN_Position() noexcept;
        void CheckNaN_Rotation() noexcept;
        void CheckNaN_Scale()    noexcept;
    private:
        //void UpdateChild(Transform* parent);

        void UpdateChildPosition(Transform* parent) noexcept;
        void UpdateChildRotation(Transform* parent, glm::vec3 delta) noexcept;
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

        glm::vec3       m_childDefRotation           = { 0, 0, 0 };

        GameObject*     m_gameObject            = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
