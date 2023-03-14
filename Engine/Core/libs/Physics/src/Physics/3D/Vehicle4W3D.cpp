//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/3D/Vehicle4W3D.h>
#include <Physics/PhysicsMaterial.h>

namespace SR_PTYPES_NS {
    Vehicle4W3D::Vehicle4W3D(LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    void Vehicle4W3D::SetCAOffsets(WheelCenterActorOffsets offsets) {
        memcpy(&m_wheelCAOffsets[0], &offsets[0], sizeof(WheelCenterActorOffsets));
    }
}