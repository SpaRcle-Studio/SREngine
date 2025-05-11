//
// Created by Monika on 22.11.2022.
//

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsLib.h>

#include <Utils/ECS/ComponentManager.h>

#include <Codegen/Rigidbody3D.generated.hpp>

namespace SR_PTYPES_NS {
    SR_UTILS_NS::Measurement Rigidbody3D::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Space3D;
    }

    void Rigidbody3D::SetLinearLock(const SR_MATH_NS::BVector3& lock) {
        m_linearLock = lock;
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            pImpl->SetLinearLock(lock);
        }
    }

    void Rigidbody3D::SetAngularLock(const SR_MATH_NS::BVector3& lock) {
        m_angularLock = lock;
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            pImpl->SetAngularLock(lock);
        }
    }

    void Rigidbody3D::SetLinearVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            pImpl->SetLinearVelocity(velocity);
        }
    }

    void Rigidbody3D::AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            pImpl->AddAngularVelocity(velocity);
        }
    }

    SR_MATH_NS::FVector3 Rigidbody3D::GetLinearVelocity() const {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            return pImpl->GetLinearVelocity();
        }
        return SR_MATH_NS::FVector3();
    }

    SR_MATH_NS::FVector3 Rigidbody3D::GetAngularVelocity() const {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            return pImpl->GetAngularVelocity();
        }
        return SR_MATH_NS::FVector3();
    }

    void Rigidbody3D::AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            return pImpl->AddLinearVelocity(velocity);
        }
    }

    void Rigidbody3D::SetAngularVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pImpl = GetImpl<Rigidbody3DImpl>()) {
            return pImpl->SetAngularVelocity(velocity);
        }
    }
}
