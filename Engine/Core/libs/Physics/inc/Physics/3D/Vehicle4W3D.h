//
// Created by innerviewer on 2/28/2023.
//

#ifndef SR_ENGINE_VEHICLE4W3D_H
#define SR_ENGINE_VEHICLE4W3D_H

#include <Physics/Vehicle.h>
#include <Physics/WheelInternalData.h>

namespace SR_PTYPES_NS {
    class Vehicle4W3D : public Vehicle {
        using Super = Vehicle;
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Vehicle4W3D);
    public:
        using WheelsData = WheelInternalData[4];

    public:
        explicit Vehicle4W3D(LibraryPtr pLibrary);
        ~Vehicle4W3D() override = default;

    public:
        SR_NODISCARD WheelsData& GetWheelsData() { return m_wheelsData; }

    private:
        WheelsData m_wheelsData;
    };
}

#endif //SR_ENGINE_VEHICLE4W3D_H
