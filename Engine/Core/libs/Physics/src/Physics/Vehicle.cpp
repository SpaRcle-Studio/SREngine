//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/Vehicle.h>

namespace SR_PTYPES_NS {
    Vehicle::Vehicle(LibraryPtr pLibrary)
    { }

    SR_UTILS_NS::Component* Vehicle::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return nullptr;
    }

    SR_HTYPES_NS::Marshal::Ptr Vehicle::Save(SR_UTILS_NS::SavableContext data) const {
        return Super::Save(data);
    }

    SR_UTILS_NS::Measurement Vehicle::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Unknown;
    }

    bool Vehicle::InitVehicle() {
        return false;
    }
}
