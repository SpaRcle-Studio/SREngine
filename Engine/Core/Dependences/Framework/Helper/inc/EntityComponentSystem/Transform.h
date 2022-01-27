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
    using namespace Framework::Helper::Math;

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

        void SetLocalPosition(FVector3 val);
        void SetLocalRotation(FVector3 val);
        void SetLocalScale(FVector3 val);

        void SetPosition(FVector3 val, bool pivot = false);
        void SetRotation(const FVector3& val, bool pivot = false);
        void SetScale(FVector3 val);
        void SetSkew(FVector3 val);

        [[nodiscard]] SR_FORCE_INLINE bool HasParent() { return (bool)this->m_parent; }

        [[nodiscard]] Xml::Document Save() const override;
        bool Load(const Xml::Node& xml) override;

        [[nodiscard]] glm::mat4 GetMatrix(Helper::Graph::PipeLine pipeLine, bool local = false) const noexcept;
        [[nodiscard]] glm::mat4 GetMatrix(Helper::Graph::PipeLine pipeLine, FVector3 position, bool local = false) const noexcept;

        void SetMatrix(glm::mat4 delta, glm::mat4 matrix, bool pivot) noexcept;

        [[nodiscard]] FVector3 GetPosition(bool local = false) const {
            return local ? m_localPosition : m_globalPosition;
        }
        [[nodiscard]] FVector3 GetRotation(bool local = false) const {
            return (local ? m_localRotation : m_globalRotation);
        }
        [[nodiscard]] FVector3 GetScale(bool local = false) const {
            return local ? m_localScale : m_globalScale;
        }
        [[nodiscard]] FVector3 GetSkew() const { return m_skew; }

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

        [[nodiscard]] FVector3 Direction(FVector3 preDir, bool local = false)   const noexcept;
        [[nodiscard]] FVector3 Forward() const noexcept;
        [[nodiscard]] FVector3 Right()   const noexcept;
        [[nodiscard]] FVector3 Up()      const noexcept;

        void SetGlobalPosition(FVector3 position);

        void Translate(FVector3 val) noexcept;
        void GlobalTranslate(FVector3 axis, double value);
        void GlobalTranslate(FVector3 value);

        void RotateAround(FVector3 point, FVector3 axis, Unit angle, bool local = true) noexcept;
        void Rotate(FVector3 angle) noexcept;
        void RotateAxis(FVector3 axis, double angle) noexcept;
        void GlobalRotateAxis(FVector3 axis, double value);

        void Scale(FVector3 val);
        void Scaling(FVector3 val);
    private:
        void UpdateChildPosition(FVector3 delta);
        void UpdateChildScale(FVector3 delta);
        void UpdateChildSkew(FVector3 delta);
        void UpdateChildRotation();
    public:
        inline static const FVector3 right   = FVector3(1, 0, 0);
        inline static const FVector3 up      = FVector3(0, 1, 0);
        inline static const FVector3 forward = FVector3(0, 0, 1);

    private:
        FVector3                     m_localPosition              = { 0, 0, 0 };
        FVector3                     m_localRotation              = { 0, 0, 0 };
        FVector3                     m_localScale                 = { 1, 1, 1 };

        FVector3                     m_globalPosition             = { 0, 0, 0 };
        FVector3                     m_globalRotation             = { 0, 0, 0 };
        FVector3                     m_globalScale                = { 1, 1, 1 };

        FVector3                     m_skew                       = { 1, 1, 1 };

        GameObject*                  m_gameObject                 = nullptr;
        Transform*                   m_parent                     = nullptr;

    };
}

#endif //GAMEENGINE_TRANSFORM_H
