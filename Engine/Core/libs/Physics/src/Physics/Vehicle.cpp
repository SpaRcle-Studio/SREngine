//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/Vehicle.h>

namespace SR_PTYPES_NS {
    Vehicle::Vehicle(LibraryPtr pLibrary) {

    }

    Vehicle::ComponentPtr Vehicle::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return nullptr;
    }

    SR_HTYPES_NS::Marshal::Ptr Vehicle::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }

    SR_UTILS_NS::Measurement Vehicle::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Unknown;
    }

    bool Vehicle::InitVehicle() {
        return false;
    }
}
