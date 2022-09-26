//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY_H
#define SRENGINE_RIGIDBODY_H

#include <Physics/PhysicsLib.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
}

namespace SR_PHYSICS_NS::Types {
    class Rigidbody : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;

    public:
        Rigidbody();
        ~Rigidbody() override;

    public:
        virtual void UpdateMatrix();

        SR_NODISCARD SR_MATH_NS::FVector3 GetSize() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenter() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetSizeDirection() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenterDirection() const noexcept;
        SR_NODISCARD float_t GetMass() const noexcept;

        void SetSize(const SR_MATH_NS::FVector3& size);
        void SetCenter(const SR_MATH_NS::FVector3& center);
        void SetMass(float_t mass);

    protected:
        void OnAttached() override;
        void OnDestroy() override;

        void UpdateDebugShape();

        void OnMatrixDirty() override;

        virtual bool InitShape();
        virtual bool InitBody();

        PhysicsScenePtr GetPhysicsScene();

    private:
        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::FVector3 m_scale;

        PhysicsScenePtr m_physicsScene;

        btRigidBody* m_rigidbody = nullptr;
        btCollisionShape* m_shape = nullptr;
        btMotionState* m_motionState = nullptr;

        SR_MATH_NS::FVector3 m_size;
        SR_MATH_NS::FVector3 m_center;

        bool m_dirty = false;

        float_t m_mass = 0.1f;
        uint64_t m_debugId = SR_ID_INVALID;

    };
}

#endif //SRENGINE_RIGIDBODY_H
