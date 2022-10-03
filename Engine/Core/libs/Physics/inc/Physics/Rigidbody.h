//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY_H
#define SRENGINE_RIGIDBODY_H

#include <Physics/PhysicsLib.h>
#include <Physics/CollisionShape.h>

#include <Utils/ECS/Component.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Matrix4x4.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
}

namespace SR_PHYSICS_NS::Types {
    class Rigidbody : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
        SR_ENTITY_SET_VERSION(1001);
        using Super = SR_UTILS_NS::Component;
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;

    public:
        explicit Rigidbody(ShapeType type);
        Rigidbody();
        ~Rigidbody() override;

    public:
        static ComponentPtr LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        virtual void UpdateMatrix();
        void UpdateShape();

        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenter() const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenterDirection() const noexcept;
        SR_NODISCARD float_t GetMass() const noexcept;

        void AddLocalVelocity(const SR_MATH_NS::FVector3& velocity);
        void AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity);

        void SetVelocity(const SR_MATH_NS::FVector3& velocity);

        void SetCenter(const SR_MATH_NS::FVector3& center);
        void SetMass(float_t mass);
        void SetType(ShapeType type);

    protected:
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDestroy() override;

        void UpdateDebugShape();

        void OnMatrixDirty() override;

        virtual bool InitBody();
        virtual void DeInitBody();

        PhysicsScenePtr GetPhysicsScene();

    protected:
        ShapeType m_type = ShapeType::Unknown;
        CollisionShape::Ptr m_shape = nullptr;

        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::FVector3 m_scale;

        PhysicsScenePtr m_physicsScene;

        btRigidBody* m_rigidbody = nullptr;
        btMotionState* m_motionState = nullptr;

        SR_MATH_NS::FVector3 m_center;

        bool m_dirty = false;

        float_t m_mass = 1.f;
        uint64_t m_debugId = SR_ID_INVALID;

    };
}

#endif //SRENGINE_RIGIDBODY_H
