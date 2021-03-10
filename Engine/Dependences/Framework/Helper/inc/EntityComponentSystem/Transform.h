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

#include <Math/Vector3.h>
#include <Math/Quaternion.h>


namespace Framework::Helper {
    using namespace Framework::Helper::Math;

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
            this->UpdateDefParentDir();
        }
        void OnParentRemove(Transform* parent) {
            m_parent = nullptr;
        }

        static glm::vec3 checkVec3Zero(const glm::vec3& v) {
            glm::vec3 vec = v;
            if (vec.x == 0)
                vec.x += 0.001;
            else if (vec.x == 90)
                vec.x -= 0.001;

            if (vec.y == 0)
                vec.y += 0.001;
            else if (vec.y == 90)
                vec.y -= 0.001;

            if (vec.z == 0)
                vec.z += 0.001;
            else if (vec.z == 90)
                vec.z -= 0.001;

            return vec;
        }

        void SetLocalPosition(Vector3 val, bool pivot = false);
        void SetLocalRotation(Vector3 val, bool pivot = false);
        void SetLocalScale(Vector3 val, bool pivot = false);

        void SetPosition(Vector3 val, bool pivot = false);
        void SetRotation(const Vector3& val, bool pivot = false);
        void SetScale(Vector3 val, bool pivot  = false);

        [[nodiscard]] inline bool HasParent() { return (bool)this->m_parent; }

        [[nodiscard]] glm::mat4 GetMatrix(bool local = false) const noexcept;
        void SetMatrix(glm::mat4 delta, glm::mat4 matrix, bool pivot) noexcept;

        [[nodiscard]] inline Vector3 GetPosition(bool local = false) const noexcept {
            return local ? m_localPosition : m_globalPosition;
            //glm::vec3 pos = glm::vec3();
            //return glm::vec3();
        }
        [[nodiscard]] inline Vector3 GetRotation(bool local = false) const noexcept {
           // return glm::degrees(glm::eulerAngles(local ? m_localRotation : m_globalRotation)); }
           // return (local ? m_localRotation : m_globalRotation).EulerAngle().Degrees();
            return (local ? m_localRotation : m_globalRotation);
           // return glm::vec3();
        }
        [[nodiscard]] inline Vector3 GetScale(bool local = false) const noexcept {
            return local ? m_localScale : m_globalScale;
            //return glm::vec3();
        }
        [[nodiscard]] inline Vector3 GetParentDir() const noexcept {
            return m_defParentDir;
        }

        /*glm::vec3 Direction(glm::vec3 point) noexcept;

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
        }*/

        [[nodiscard]] Vector3 Direction(Vector3 preDir, bool local = false)   const noexcept;
        [[nodiscard]] Vector3 Forward(bool local = false) const noexcept;
        [[nodiscard]] Vector3 Right(bool local = false)   const noexcept;
        [[nodiscard]] Vector3 Up(bool local = false)      const noexcept;

        void Translate(Vector3 val, bool local = false) noexcept;
        void Rotate(Vector3 angle, bool local = false) noexcept;
        void RotateAxis(Vector3 axis, double angle, bool local = false) noexcept;
    public:
        void UpdateLocalPosition(Vector3 delta);
        void UpdateLocalScale(Vector3 delta);
        void UpdateLocalRotation(Vector3 delta);

        void UpdateDefParentDir();

        void UpdateChildPosition(Vector3 delta, bool pivot);
        void UpdateChildScale(Vector3 delta, bool pivot);
        //void UpdateChildRotation(glm::vec3 delta, bool pivot);
        void UpdateChildRotation(bool pivot);
    public:
        /*inline static const glm::vec3 right     = { 1, 0, 0 };
        inline static const glm::vec3 forward   = { 0, 0, 1 };
        inline static const glm::vec3 up        = { 0, 1, 0 };

        inline static const glm::vec3 down      = {  0, -1,  0 };
        inline static const glm::vec3 left      = { -1,  0,  0 };
        inline static const glm::vec3 back      = {  0,  0, -1 };

        inline static const glm::vec3 pitch     = { 1, 0, 0 };
        inline static const glm::vec3 yaw       = { 0, 1, 0 };
        inline static const glm::vec3 roll      = { 0, 0, 1 };*/

        inline static const Vector3 right     = Vector3(1, 0, 0);
        inline static const Vector3 forward   = Vector3(0, 0, 1 );
        inline static const Vector3 up        = Vector3( 0, 1, 0 );
    private:
        Vector3         m_localPosition              = { 2, 2, 2 };
        //Quaternion      m_localRotation              = Quaternion(Vector3(0,0,0));
        Vector3         m_localRotation              = { 0, 0, 0 };
        Vector3         m_localScale                 = { 1, 1, 1 };

        Vector3         m_globalPosition             = { 0, 0, 0 };
        //Quaternion      m_globalRotation             = Quaternion(Vector3(0,0,0));
        Vector3         m_globalRotation             = { 0, 0, 0 };
        Vector3         m_globalScale                = { 1, 1, 1 };

        /*glm::vec3       m_localPosition              = { 0, 0, 0 };
        glm::vec3       m_localRotation              = { 0, 0, 0 };
        //glm::quat       m_localRotation              = glm::quat(glm::radians(glm::vec3(0,0,0)));
        glm::vec3       m_localScale                 = { 1, 1, 1 };

        glm::vec3       m_globalPosition             = { 0, 0, 0 };
        glm::vec3       m_globalRotation             = { 0, 0, 0 };
        //glm::quat       m_globalRotation             = glm::quat(glm::radians(glm::vec3(0,0,0)));
        glm::vec3       m_globalScale                = { 1, 1, 1 };*/

        Vector3         m_defParentDir               = forward;
        GameObject*     m_gameObject                 = nullptr;
        Transform*      m_parent                     = nullptr;
    };
}

#endif //GAMEENGINE_TRANSFORM_H
