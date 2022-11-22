//
// Created by Monika on 22.11.2022.
//

#include <Physics/3D/Rigidbody3D.h>

namespace SR_PTYPES_NS {
    Rigidbody3D::Rigidbody3D(Rigidbody::LibraryPtr pLibrary)
        : Super(pLibrary)
    {
        SR_UTILS_NS::Component::InitComponent<Rigidbody3D>();
    }

    Rigidbody3D::ComponentPtr Rigidbody3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return Super::LoadComponent(marshal, dataStorage);
    }

    SR_UTILS_NS::Measurement Rigidbody3D::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Space3D;
    }
}
