//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/Vehicle.h>

#include <Codegen/Vehicle.generated.hpp>

namespace SR_PTYPES_NS {
    SR_UTILS_NS::Measurement Vehicle::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Unknown;
    }

    bool Vehicle::InitVehicle() {
        return false;
    }
}
