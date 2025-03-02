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
        SR_CLASS()
        SR_REGISTER_NEW_COMPONENT(Vehicle4W3D, 1000);
    public:
        using WheelsData = WheelInternalData[4];

    public:
        SR_NODISCARD WheelsData& GetWheelsData() { return m_wheelsData; }
        SR_NODISCARD void* GetHandle() const noexcept override { return nullptr; }

    private:
        WheelsData m_wheelsData;
    };
}

#endif //SR_ENGINE_VEHICLE4W3D_H
