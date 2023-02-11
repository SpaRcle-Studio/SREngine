//
// Created by Monika on 25.11.2022.
//

#ifndef SRENGINE_PHYSXRIGIDBODY3D_H
#define SRENGINE_PHYSXRIGIDBODY3D_H

#include <Physics/3D/Rigidbody3D.h>

namespace SR_PTYPES_NS {
    class PhysXRigidbody3D : public Rigidbody3D {
        using Super = Rigidbody3D;
    public:
        explicit PhysXRigidbody3D(LibraryPtr pLibrary);
        ~PhysXRigidbody3D() override;

    public:
        SR_NODISCARD void* GetHandle() const noexcept override;

    public:
        void UpdateInertia() override;
        bool InitBody() override;

        void AddLocalVelocity(const SR_MATH_NS::FVector3& velocity) override;
        void AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity) override;

        bool UpdateMatrix(bool force) override;
        bool UpdateShapeInternal() override;

    private:
        physx::PxRigidActor* m_rigidActor = nullptr;

    };
}

#endif //SRENGINE_PHYSXRIGIDBODY3D_H
