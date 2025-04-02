

# File PhysXRigidbody3D.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXRigidbody3D.h**](PhysXRigidbody3D_8h.md)

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


