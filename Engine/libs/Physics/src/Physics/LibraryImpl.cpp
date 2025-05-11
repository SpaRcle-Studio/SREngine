//
// Created by Monika on 22.11.2022.
//

#include <Physics/LibraryImpl.h>
#include <Utils/Common/Features.h>

namespace SR_PHYSICS_NS {
    LibraryImpl::LibraryImpl()
        : Super()
    { }

    bool LibraryImpl::Initialize() {
        SR_TRACY_ZONE;

        if (SR_UTILS_NS::Features::Instance().Enabled("Vehicles", true)) {
            m_isVehicleSupported = true;
        }

        return true;
    }
}