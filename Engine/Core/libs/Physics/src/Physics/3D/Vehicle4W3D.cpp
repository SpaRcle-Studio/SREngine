//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/3D/Vehicle4W3D.h>
#include <Physics/PhysicsMaterial.h>

namespace SR_PTYPES_NS {
    SR_REGISTER_COMPONENT_CUSTOM(Vehicle4W3D, {
        auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D);

        if (auto&& pVehicle4W3D = pLibrary->CreateVehicle4W3D()) {
            return pVehicle4W3D;
        }

        return (SR_PTYPES_NS::Vehicle4W3D*)nullptr;
    });

    Vehicle4W3D::Vehicle4W3D(LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    void Vehicle4W3D::SetCAOffsets(WheelCenterActorOffsets offsets) {
        memcpy(&m_wheelCAOffsets[0], &offsets[0], sizeof(WheelCenterActorOffsets));
    }
}