//
// Created by Monika on 22.11.2022.
//

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsLib.h>

#include <Utils/ECS/ComponentManager.h>

namespace SR_PTYPES_NS {
    SR_REGISTER_COMPONENT(Rigidbody3D);

    SR_UTILS_NS::Component* Rigidbody3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = Super::LoadComponent(SR_UTILS_NS::Measurement::Space3D, marshal, dataStorage);

        if (auto&& pRigidbody3D = dynamic_cast<Rigidbody3D*>(pComponent)) {
            pRigidbody3D->SetLinearLock(marshal.Read<SR_MATH_NS::BVector3>());
            pRigidbody3D->SetAngularLock(marshal.Read<SR_MATH_NS::BVector3>());
        }
        else {
            SRHalt("Rigidbody3D::LoadComponent : unsolved situation.");
        }

        return pComponent;
    }

    SR_UTILS_NS::Measurement Rigidbody3D::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Space3D;
    }

    SR_HTYPES_NS::Marshal::Ptr Rigidbody3D::Save(SR_UTILS_NS::SavableSaveData data) const {
        auto&& pMarshal = Super::Save(data);

        pMarshal->Write<SR_MATH_NS::BVector3>(m_linearLock);
        pMarshal->Write<SR_MATH_NS::BVector3>(m_angularLock);

        return pMarshal;
    }

    SR_UTILS_NS::Component* Rigidbody3D::CopyComponent() const {
        auto&& pComponent = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Rigidbody3D>();

        pComponent->SetType(GetType());

        pComponent->m_linearLock = m_linearLock;
        pComponent->m_angularLock = m_angularLock;

        pComponent->m_isTrigger = m_isTrigger;
        pComponent->m_isStatic = m_isStatic;

        pComponent->m_mass = m_mass;

        pComponent->m_center = m_center;

        pComponent->GetCollisionShape()->SetBounds(GetCollisionShape()->GetBounds());

        return dynamic_cast<Rigidbody3D*>(pComponent);
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
