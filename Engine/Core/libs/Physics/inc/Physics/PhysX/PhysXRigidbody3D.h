//
// Created by Monika on 25.11.2022.
//

#ifndef SRENGINE_PHYSXRIGIDBODY3D_H
#define SRENGINE_PHYSXRIGIDBODY3D_H

#include <Physics/3D/Rigidbody3D.h>

namespace SR_PTYPES_NS {
    class PhysXRigidbody3DImpl : public Rigidbody3DImpl {
        using Super = Rigidbody3DImpl;
    public:
        ~PhysXRigidbody3DImpl() override;

    public:
        SR_NODISCARD void* GetHandle() const noexcept override;

    public:
        void UpdateInertia() override;
        bool InitBody() override;
        void ClearForces() override;

        void AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) override;
        void AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) override;

        void SetLinearVelocity(const SR_MATH_NS::FVector3& velocity) override;
        void SetAngularVelocity(const SR_MATH_NS::FVector3& velocity) override;

        SR_NODISCARD SR_MATH_NS::FVector3 GetLinearVelocity() const override;
        SR_NODISCARD SR_MATH_NS::FVector3 GetAngularVelocity() const override;

        void Synchronize() override;

        bool UpdateMatrix(bool force) override;
        bool UpdateShapeInternal() override;

        void SetLinearLock(const SR_MATH_NS::BVector3& lock) override;
        void SetAngularLock(const SR_MATH_NS::BVector3& lock) override;

    private:
        void UpdateLocks();

    private:
        physx::PxRigidActor* m_rigidActor = nullptr;

    };
}

#endif //SRENGINE_PHYSXRIGIDBODY3D_H
