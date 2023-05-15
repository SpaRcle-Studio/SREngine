//
// Created by Monika on 22.11.2022.
//

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/LibraryImpl.h>
#include <Physics/PhysicsLib.h>

#include <Utils/ECS/ComponentManager.h>

namespace SR_PTYPES_NS {
    SR_REGISTER_COMPONENT_CUSTOM(Rigidbody3D, {
        auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D);

        if (auto&& pRigidbody = pLibrary->CreateRigidbody3D()) {
            pRigidbody->SetType(pLibrary->GetDefaultShape());
            return pRigidbody;
        }

        return (SR_PTYPES_NS::Rigidbody3D*)nullptr;
    });

    Rigidbody3D::Rigidbody3D(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

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

    SR_HTYPES_NS::Marshal::Ptr Rigidbody3D::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        auto&& pComponent = Super::Save(pMarshal, flags);

        pComponent->Write<SR_MATH_NS::BVector3>(m_linearLock);
        pComponent->Write<SR_MATH_NS::BVector3>(m_angularLock);

        return pComponent;
    }

    SR_UTILS_NS::Component *Rigidbody3D::CopyComponent() const {
        auto&& pComponent = m_library->CreateRigidbody3D();

        pComponent->SetType(GetType());

        pComponent->m_linearLock = m_linearLock;
        pComponent->m_angularLock = m_angularLock;

        pComponent->m_isTrigger = m_isTrigger;
        pComponent->m_isStatic = m_isStatic;

        pComponent->m_mass = m_mass;

        pComponent->m_center = m_center;

        pComponent->GetCollisionShape()->SetSize(GetCollisionShape()->GetSize());

        return dynamic_cast<Rigidbody3D*>(pComponent);
    }
}
