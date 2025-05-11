

# File PhysXRigidbody3D.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXRigidbody3D.h**](PhysXRigidbody3D_8h.md)

[Go to the documentation of this file](PhysXRigidbody3D_8h.md)


```C++
//
// Created by Monika on 25.11.2022.
//

#ifndef SR_ENGINE_PHYSXRIGIDBODY3D_H
#define SR_ENGINE_PHYSXRIGIDBODY3D_H

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

#endif //SR_ENGINE_PHYSXRIGIDBODY3D_H
```


