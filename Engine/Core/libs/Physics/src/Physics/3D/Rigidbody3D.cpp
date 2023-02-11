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

    Rigidbody3D::ComponentPtr Rigidbody3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return Super::LoadComponent(SR_UTILS_NS::Measurement::Space3D, marshal, dataStorage);
    }

    SR_UTILS_NS::Measurement Rigidbody3D::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Space3D;
    }

    SR_HTYPES_NS::Marshal::Ptr Rigidbody3D::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }
}
