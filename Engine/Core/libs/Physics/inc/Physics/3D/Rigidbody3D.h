//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_RIGIDBODY3D_H
#define SRENGINE_RIGIDBODY3D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody3D : public Rigidbody {
        using Super = Rigidbody;
        SR_ENTITY_SET_VERSION(1005);
        SR_INITIALIZE_COMPONENT(Rigidbody3D);
    public:
        explicit Rigidbody3D(LibraryPtr pLibrary);
        ~Rigidbody3D() override = default;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

        SR_NODISCARD SR_MATH_NS::BVector3 GetLinearLock() const noexcept { return m_linearLock; }
        SR_NODISCARD SR_MATH_NS::BVector3 GetAngularLock() const noexcept { return m_angularLock; }

        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetLinearVelocity() const { return SR_MATH_NS::FVector3(); }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetAngularVelocity() const { return SR_MATH_NS::FVector3(); }

        virtual void SetLinearLock(const SR_MATH_NS::BVector3& lock) { m_linearLock = lock; }
        virtual void SetAngularLock(const SR_MATH_NS::BVector3& lock) { m_angularLock = lock; }

        virtual void AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) { }
        virtual void AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) { }

        virtual void SetLinearVelocity(const SR_MATH_NS::FVector3& velocity) { }
        virtual void SetAngularVelocity(const SR_MATH_NS::FVector3& velocity) { }

        SR_NODISCARD SR_UTILS_NS::Component* CopyComponent() const override;

    protected:
        SR_MATH_NS::BVector3 m_linearLock;
        SR_MATH_NS::BVector3 m_angularLock;

    };
}

#endif //SRENGINE_RIGIDBODY3D_H
