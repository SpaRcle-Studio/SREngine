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

#include <Types/SafePointer.h>
#include <EntityComponentSystem/ISavable.h>

#include <Utils/GraphUtils.h>

namespace Framework::Helper {
    enum class Location{
        Left, Center, Right, Forward, Back, Up, Down
    };

    class GameObject;
    class Transform : public ISavable {
        friend class GameObject;
    private:
        explicit Transform(GameObject* parent);
        ~Transform() override = default;
    public:
        void OnParentSet(Transform* parent);

        void SetLocalPosition(Math::FVector3 val);
        void SetLocalRotation(Math::FVector3 val);
        void SetLocalScale(Math::FVector3 val);

        void SetWorldPosition(Math::FVector3 position);
        void SetWorldRotation(Math::FVector3 rotation);

        //void SetPosition(FVector3 val, bool pivot = false);
        //void SetRotation(const FVector3& val);
        //void SetScale(FVector3 val);
        //void SetSkew(FVector3 val);

        [[nodiscard]] SR_FORCE_INLINE bool HasParent() { return (bool)m_parent; }
        [[nodiscard]] Transform* GetParent() { return m_parent; }

        [[nodiscard]] Xml::Document Save() const override;

        [[nodiscard]] glm::mat4 GetMatrix(Helper::Graph::PipeLine pipeLine, bool local = false) const noexcept;
        [[nodiscard]] glm::mat4 GetMatrix(Helper::Graph::PipeLine pipeLine, Math::FVector3 position, bool local = false) const noexcept;
        [[nodiscard]] Math::Matrix4x4 GetInvWorldMatrix() const;

        void SetMatrix(glm::mat4 delta, glm::mat4 matrix, bool pivot) noexcept;

        SR_NODISCARD Math::FVector3 GetPosition() const { return m_globalPosition; }
        SR_NODISCARD Math::FVector3 GetRotation() const { return m_globalRotation; }
        SR_NODISCARD Math::FVector3 GetScale() const { return m_globalScale; }
        SR_NODISCARD Math::FVector3 GetSkew() const { return m_skew; }

        SR_NODISCARD Math::FVector3 GetLocalPosition() const { return m_localPosition; }
        SR_NODISCARD Math::FVector3 GetLocalRotation() const { return m_localRotation; }
        SR_NODISCARD Math::FVector3 GetLocalScale() const { return m_localScale; }
        SR_NODISCARD Math::FVector3 GetLocalSkew() const { return m_skew; }

        /*inline static float Len(const glm::vec3& v) noexcept {
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

        [[nodiscard]] Math::FVector3 Direction(Math::FVector3 preDir, bool local = false)   const noexcept;
        [[nodiscard]] Math::FVector3 Forward() const noexcept;
        [[nodiscard]] Math::FVector3 Right()   const noexcept;
        [[nodiscard]] Math::FVector3 Up()      const noexcept;

        void Translate(Math::FVector3 val) noexcept;
        void GlobalTranslate(Math::FVector3 axis, double value);
        void GlobalTranslate(Math::FVector3 value);

        void RotateAround(Math::FVector3 point, Math::FVector3 axis, Math::Unit angle, bool local = true) noexcept;
        void Rotate(Math::FVector3 angle);
        void Rotate(Math::FVector3 axis, double angle) noexcept;
        void GlobalRotate(Math::FVector3 axis, double value);
        void GlobalRotate(Math::FVector3 value);

        void Scale(Math::FVector3 val);
    private:
        void UpdateChildPosition(Math::FVector3 delta);
        void UpdateChildScale(Math::FVector3 delta);
        void UpdateChildSkew(Math::FVector3 delta);
        void UpdateChildRotation();
    public:
        inline static const Math::FVector3 right   = Math::FVector3(1, 0, 0);
        inline static const Math::FVector3 up      = Math::FVector3(0, 1, 0);
        inline static const Math::FVector3 forward = Math::FVector3(0, 0, 1);

    private:
        Math::FVector3               m_localPosition              = { 0, 0, 0 };
        Math::FVector3               m_localRotation              = { 0, 0, 0 };
        Math::FVector3               m_localScale                 = { 1, 1, 1 };

        Math::FVector3               m_globalPosition             = { 0, 0, 0 };
        Math::FVector3               m_globalRotation             = { 0, 0, 0 };
        Math::FVector3               m_globalScale                = { 1, 1, 1 };

        Math::FVector3               m_skew                       = { 1, 1, 1 };

        GameObject*                  m_gameObject                 = nullptr;
        Transform*                   m_parent                     = nullptr;

    };
}

#endif //GAMEENGINE_TRANSFORM_H
