//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_RIGIDBODY3D_H
#define SR_ENGINE_RIGIDBODY3D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody3DImpl : public RigidbodyImpl {
        using Super = RigidbodyImpl;
    public:
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetLinearVelocity() const = 0;
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetAngularVelocity() const = 0;

        virtual void AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) { }
        virtual void AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) { }

        virtual void SetLinearVelocity(const SR_MATH_NS::FVector3& velocity) { }
        virtual void SetAngularVelocity(const SR_MATH_NS::FVector3& velocity) { }

        virtual void SetLinearLock(const SR_MATH_NS::BVector3& lock) { }
        virtual void SetAngularLock(const SR_MATH_NS::BVector3& lock) { }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class Rigidbody3D final : public Rigidbody {
        using Super = Rigidbody;
        SR_REGISTER_NEW_COMPONENT(Rigidbody3D, 1013);
    public:
        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

        SR_NODISCARD SR_MATH_NS::BVector3 GetLinearLock() const noexcept { return m_linearLock; }
        SR_NODISCARD SR_MATH_NS::BVector3 GetAngularLock() const noexcept { return m_angularLock; }

        SR_NODISCARD SR_MATH_NS::FVector3 GetLinearVelocity() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetAngularVelocity() const;

        SR_NODISCARD bool InitializeEntity() noexcept override;

        void SetLinearLock(const SR_MATH_NS::BVector3& lock);
        void SetAngularLock(const SR_MATH_NS::BVector3& lock);

        void AddLinearVelocity(const SR_MATH_NS::FVector3& velocity);
        void AddAngularVelocity(const SR_MATH_NS::FVector3& velocity);

        void SetLinearVelocity(const SR_MATH_NS::FVector3& velocity);
        void SetAngularVelocity(const SR_MATH_NS::FVector3& velocity);

    protected:
        SR_MATH_NS::BVector3 m_linearLock;
        SR_MATH_NS::BVector3 m_angularLock;

    };
}

#endif //SR_ENGINE_RIGIDBODY3D_H
